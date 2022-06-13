/*
 *  Copyright (c) 2022 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "rk_smart_ir_api.h"
#include "uAPI2/rk_aiq_user_api2_ae.h"
#include "uAPI2/rk_aiq_user_api2_awb.h"
#include "uAPI2/rk_aiq_user_api2_sysctl.h"

RKAIQ_BEGIN_DECLARE

#ifndef Android
#ifndef NDEBUG
#define SMARTIR_LOG printf
#else //NDEBUG
#define SMARTIR_LOG
#endif
#else //Android
#define SMARTIR_LOG LOGD
#endif

typedef struct rk_smart_ir_ctx_s {
    const rk_aiq_sys_ctx_t* aiq_ctx;
    int cur_working_mode;
    rk_smart_ir_params_t ir_configs;
    RK_SMART_IR_STATUS_t state;
    uint16_t switch_cnts;
} rk_smart_ir_ctx_t;

rk_smart_ir_ctx_t*
rk_smart_ir_init(const rk_aiq_sys_ctx_t* ctx)
{
    SMARTIR_LOG("%s: (enter)\n", __FUNCTION__ );
    rk_smart_ir_ctx_t* ir_ctx = (rk_smart_ir_ctx_t*)malloc(sizeof(rk_smart_ir_ctx_t));
    if (ir_ctx) {
        memset(ir_ctx, 0, sizeof(rk_smart_ir_ctx_t));
        ir_ctx->aiq_ctx = ctx;
        ir_ctx->ir_configs.d2n_envL_th = 0.007f;
        ir_ctx->ir_configs.n2d_envL_th = 1.0f;
        ir_ctx->ir_configs.BG_gain_max = 1.08f;
        ir_ctx->ir_configs.BG_gain_min = 0.98f;
        ir_ctx->ir_configs.RG_gain_max = 1.07f;
        ir_ctx->ir_configs.RG_gain_min = 1.0f;
        ir_ctx->cur_working_mode = -1;
    }

    SMARTIR_LOG("%s: (exit)\n", __FUNCTION__ );
    return ir_ctx;
}

XCamReturn
rk_smart_ir_deInit(const rk_smart_ir_ctx_t* ctx)
{
    SMARTIR_LOG("%s: (enter)\n", __FUNCTION__ );
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (ctx)
        free((void*)ctx);

    SMARTIR_LOG("%s: (exit)\n", __FUNCTION__ );

    return ret;
}

XCamReturn
rk_smart_ir_config(rk_smart_ir_ctx_t* ctx, rk_smart_ir_params_t* config)
{
    SMARTIR_LOG("%s: (enter)\n", __FUNCTION__ );

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ctx->ir_configs = *config;

    ctx->switch_cnts = 0;
    ctx->cur_working_mode = -1;

    SMARTIR_LOG("ir configs: \n"
             "d2n_envL_th: %0.3f, n2d_envL_th: %0.3f\n"
             "BG_gain_max: %0.3f, BG_gain_min: %0.3f\n"
             "RG_gain_max: %0.3f, RG_gain_min: %0.3f\n"
             "switch_cnts_th: %d",
            config->d2n_envL_th, config->n2d_envL_th,
            config->BG_gain_max, config->BG_gain_min,
            config->RG_gain_max, config->RG_gain_min,
            config->switch_cnts_th);
    SMARTIR_LOG("%s: (exit)\n", __FUNCTION__ );

    return ret;
}

enum RK_SMART_IR_ALGO_RESULT_e {
    RK_SMART_IR_ALGO_RESULT_KEEP = 0,
    RK_SMART_IR_ALGO_RESULT_DAY,
    RK_SMART_IR_ALGO_RESULT_NIGHT,
};

#define RK_SMART_IR_BLK_NUM_D2N_THRES (0.8 * RK_AIQ_AWB_GRID_NUM_TOTAL) // 200
#define RK_SMART_IR_BLK_NUM_N2D_THRES (0.1 * RK_AIQ_AWB_GRID_NUM_TOTAL) // 22

static int
_rk_smart_ir_day_or_night(rk_smart_ir_ctx_t* ctx, float envL, float RGgain, float BGgain)
{
    int ret = RK_SMART_IR_ALGO_RESULT_KEEP;
    rk_smart_ir_params_t* ir_configs = &ctx->ir_configs;

    if (envL < ctx->ir_configs.d2n_envL_th) {
        ret = RK_SMART_IR_ALGO_RESULT_NIGHT;
    } else if (envL > ctx->ir_configs.n2d_envL_th) {
        if (ctx->state == RK_SMART_IR_STATUS_NIGHT) {
            if ((RGgain > ctx->ir_configs.RG_gain_min) &&
                (RGgain < ctx->ir_configs.RG_gain_max) &&
                (BGgain > ctx->ir_configs.BG_gain_min) &&
                (BGgain < ctx->ir_configs.BG_gain_max)) {
                ret = RK_SMART_IR_ALGO_RESULT_NIGHT;
            } else {
                ret = RK_SMART_IR_ALGO_RESULT_DAY;
            }
        } else {
            ret = RK_SMART_IR_ALGO_RESULT_KEEP;
        }
    } else {
        ret = RK_SMART_IR_ALGO_RESULT_KEEP;
    }
    return ret;
}

XCamReturn
rk_smart_ir_runOnce(rk_smart_ir_ctx_t* ctx, rk_aiq_isp_stats_t* stats_ref, rk_smart_ir_result_t* result)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (ctx->cur_working_mode  == -1) {
        rk_aiq_working_mode_t working_mode;

        ret = rk_aiq_uapi2_sysctl_getWorkingMode(ctx->aiq_ctx, &working_mode);
        if (ret == XCAM_RETURN_NO_ERROR)
            ctx->cur_working_mode = working_mode;
    }

    float avg_envL = 0;

    SMARTIR_LOG("===== runOnce for stats frame id %d \n", stats_ref->frame_id);
    int blk_res[3];
    memset(blk_res, 0, sizeof(blk_res));
    if (stats_ref->awb_hw_ver == 4) { //isp32
        double Rvalue = 0, Gvalue = 0,Bvalue = 0, wpNo = 0;
        float int_time = 0, again = 0, envL_blk = 0;
        int algo_status = 0;
        for (int i = 0; i < RK_AIQ_AWB_GRID_NUM_TOTAL; i++) {
           Rvalue = stats_ref->awb_stats_v32.blockResult[i].Rvalue;
           Gvalue = stats_ref->awb_stats_v32.blockResult[i].Gvalue;
           Bvalue = stats_ref->awb_stats_v32.blockResult[i].Bvalue;
           if (ctx->cur_working_mode  == RK_AIQ_WORKING_MODE_NORMAL) {
               int_time = stats_ref->aec_stats.ae_exp.LinearExp.exp_real_params.integration_time * 1000;
               again = stats_ref->aec_stats.ae_exp.LinearExp.exp_real_params.analog_gain;
               envL_blk = stats_ref->aec_stats.ae_data.chn[0].rawae_big.channely_xy[i] / (int_time * again);
           } else if (ctx->cur_working_mode  == RK_AIQ_WORKING_MODE_ISP_HDR2) { // using long frame
               int_time = stats_ref->aec_stats.ae_exp.HdrExp[1].exp_real_params.integration_time * 1000;
               again = stats_ref->aec_stats.ae_exp.HdrExp[1].exp_real_params.analog_gain;
               envL_blk = stats_ref->aec_stats.ae_data.chn[1].rawae_big.channely_xy[i] / (int_time * again);
           } else {
               // hdr3
               int_time = stats_ref->aec_stats.ae_exp.HdrExp[2].exp_real_params.integration_time * 1000;
               again = stats_ref->aec_stats.ae_exp.HdrExp[2].exp_real_params.analog_gain;
               envL_blk = stats_ref->aec_stats.ae_data.chn[2].rawae_big.channely_xy[i] / (int_time * again);
           }
           //SMARTIR_LOG("blk[%d]:RGgain:%0.3f, BGgain:%0.3f, envL: %0.3f\n",
           //            i , Rvalue/Gvalue, Bvalue/Gvalue, envL_blk);
           algo_status = _rk_smart_ir_day_or_night(ctx, envL_blk, Rvalue/Gvalue, Bvalue/Gvalue);
           blk_res[algo_status]++;
           avg_envL += envL_blk;
        }

        avg_envL /= RK_AIQ_AWB_GRID_NUM_TOTAL;

        SMARTIR_LOG(">>> avg_envL:%0.3f, Cur:%s, Night:%d, Day:%d, keep:%d \n", avg_envL,
           ctx->state == RK_SMART_IR_STATUS_DAY ? "Day" : "Night",
           blk_res[2], blk_res[1], blk_res[0]);
    }

    if (ctx->state == RK_SMART_IR_STATUS_DAY) {
         if (blk_res[RK_SMART_IR_ALGO_RESULT_NIGHT] > blk_res[RK_SMART_IR_ALGO_RESULT_DAY] &&
             blk_res[RK_SMART_IR_ALGO_RESULT_NIGHT] > RK_SMART_IR_BLK_NUM_D2N_THRES)
             ctx->switch_cnts++;
         else
             ctx->switch_cnts = 0;
    } else {
         if (blk_res[RK_SMART_IR_ALGO_RESULT_DAY] > blk_res[RK_SMART_IR_ALGO_RESULT_NIGHT] &&
             blk_res[RK_SMART_IR_ALGO_RESULT_DAY] > RK_SMART_IR_BLK_NUM_N2D_THRES)
             ctx->switch_cnts++;
         else
             ctx->switch_cnts = 0;
    }

#if 0
    Uapi_ExpQueryInfo_t exp_info;

    ret = rk_aiq_user_api2_ae_queryExpResInfo(ctx->aiq_ctx, &exp_info);
    if (ret == XCAM_RETURN_NO_ERROR) {
        SMARTIR_LOG("Ae converge:%d, EnvL:%0.3f, avg_envL:%0.03f\n",
               exp_info.IsConverged, exp_info.GlobalEnvLv, avg_envL);

        SMARTIR_LOG("Ae time:%0.3f , gain:%0.3f, meanluma:%0.3f, LumaDeviation:%0.3f \n",
               exp_info.LinAeInfo.LinearExp.integration_time,
               exp_info.LinAeInfo.LinearExp.analog_gain,
               exp_info.LinAeInfo.MeanLuma,
               exp_info.LinAeInfo.LumaDeviation);
    } else
        return XCAM_RETURN_ERROR_FAILED;

    rk_aiq_wb_querry_info_t wb_info;
    float RGgain = 0.0f, BGgain = 0.0f;
    ret = rk_aiq_user_api2_awb_QueryWBInfo(ctx->aiq_ctx, &wb_info);
    if (ret == XCAM_RETURN_NO_ERROR) {
        RGgain = 1.0 / wb_info.stat_gain_blk.rgain;
        BGgain = 1.0 / wb_info.stat_gain_blk.bgain;
        SMARTIR_LOG("Awb converge:%d, RGgain:%0.3f, BGgain: %0.3f\n",
               wb_info.awbConverged, RGgain, BGgain);
    } else
        return XCAM_RETURN_ERROR_FAILED;

#endif
    if (ctx->switch_cnts > ctx->ir_configs.switch_cnts_th) {
        ctx->state = ctx->state == RK_SMART_IR_STATUS_DAY ? RK_SMART_IR_STATUS_NIGHT : RK_SMART_IR_STATUS_DAY;
        ctx->switch_cnts = 0;
        SMARTIR_LOG("++++++ switch status: %s ! \n", ctx->state == RK_SMART_IR_STATUS_DAY ? "Day" : "Night");
    }

    result->status = ctx->state;

    return ret;
}

RKAIQ_END_DECLARE
