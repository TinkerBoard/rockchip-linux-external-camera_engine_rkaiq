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
#define SMARTIR_LOG(...) printf(##__VA_ARGS__)
#else //NDEBUG
#define SMARTIR_LOG
#endif
#else //Android
#define SMARTIR_LOG LOGD
#endif

typedef struct rk_smart_ir_ctx_s {
    const rk_aiq_sys_ctx_t* aiq_ctx;
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

XCamReturn
rk_smart_ir_runOnce(rk_smart_ir_ctx_t* ctx, rk_smart_ir_result_t* result)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

#if 0
    rk_aiq_isp_stats_t *stats_ref = NULL;
    ret = rk_aiq_uapi2_sysctl_get3AStatsBlk(ctx, &stats_ref, -1);
    if (ret == XCAM_RETURN_NO_ERROR && stats_ref != NULL) {
        printf("get one stats frame id %d \n", stats_ref->frame_id);
        rk_aiq_uapi2_sysctl_release3AStatsRef(ctx, stats_ref);
    } else {
        if (ret == XCAM_RETURN_NO_ERROR) {
            printf("aiq has stopped !\n");
        } else if (ret == XCAM_RETURN_ERROR_TIMEOUT) {
            printf("aiq timeout!\n");
        } else if (ret == XCAM_RETURN_ERROR_FAILED) {
            printf("aiq failed!\n");
        }
    }
#endif

    Uapi_ExpQueryInfo_t exp_info;

    ret = rk_aiq_user_api2_ae_queryExpResInfo(ctx->aiq_ctx, &exp_info);
    if (ret == XCAM_RETURN_NO_ERROR) {
        SMARTIR_LOG("Ae converge:%d, EnvL:%0.3f,HlPdf:%f, llPdf:%0.3f, meanluma:%0.3f\n",
               exp_info.IsConverged, exp_info.GlobalEnvLv,
               exp_info.HighLightROIPdf, exp_info.LowLightROIPdf,
               exp_info.MeanLuma);
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

    rk_smart_ir_params_t* ir_configs = &ctx->ir_configs;

    if (exp_info.GlobalEnvLv < ctx->ir_configs.d2n_envL_th) {
        if (ctx->state == RK_SMART_IR_STATUS_DAY) {
             ctx->switch_cnts++;
        } else {
             ctx->switch_cnts = 0;
        }
    } else if (exp_info.GlobalEnvLv > ctx->ir_configs.n2d_envL_th) {
        if (ctx->state == RK_SMART_IR_STATUS_NIGHT) {
            if ((RGgain > ctx->ir_configs.RG_gain_min) &&
                (RGgain < ctx->ir_configs.RG_gain_max) &&
                (BGgain > ctx->ir_configs.BG_gain_min) &&
                (BGgain < ctx->ir_configs.BG_gain_max)) {
                 ctx->switch_cnts = 0;
                SMARTIR_LOG("envL > n2d_envL_th, but wb not satisfied , keep Night !\n");
            } else if (exp_info.HighLightROIPdf > 0) { // TODO
                 ctx->switch_cnts++;
            } else {
                 // check if strong reflection case
                 ctx->switch_cnts++;
            }
        } else {
             ctx->switch_cnts = 0;
        }
    } else {
        //printf("keep status: %s ! \n", ctx->state == RK_SMART_IR_STATUS_DAY ? "Day" : "Night");
    }

    if (ctx->switch_cnts > ctx->ir_configs.switch_cnts_th) {
        ctx->state = ctx->state == RK_SMART_IR_STATUS_DAY ? RK_SMART_IR_STATUS_NIGHT : RK_SMART_IR_STATUS_DAY;
        ctx->switch_cnts = 0;
        SMARTIR_LOG("switch status: %s ! \n", ctx->state == RK_SMART_IR_STATUS_DAY ? "Day" : "Night");
    }

    result->status = ctx->state;

    return ret;
}

RKAIQ_END_DECLARE
