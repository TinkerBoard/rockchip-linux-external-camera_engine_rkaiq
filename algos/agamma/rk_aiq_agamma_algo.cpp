/*
 * rk_aiq_algo_acprc_itf.c
 *
 *  Copyright (c) 2019 Rockchip Corporation
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
#include <string.h>
#include "rk_aiq_algo_types_int.h"
#include "xcam_common.h"
#include "rk_aiq_agamma_algo.h"

RKAIQ_BEGIN_DECLARE

XCamReturn AgammaInit(AgammaHandle_t** pGammaCtx, CamCalibDbV2Context_t* pCalib)
{
    LOG1_AGAMMA("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AgammaHandle_t* handle = (AgammaHandle_t*)calloc(sizeof(AgammaHandle_t), 1);
    if (NULL == handle)
        return XCAM_RETURN_ERROR_MEM;

    if(CHECK_ISP_HW_V21()) {
        CalibDbV2_gamma_t* calibv2_agamma_calib =
            (CalibDbV2_gamma_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, agamma_calib));

        if (!calibv2_agamma_calib) {
            free(handle);
            return XCAM_RETURN_ERROR_MEM;
        }
        memcpy(&handle->agammaAttr.stTool, calibv2_agamma_calib, sizeof(CalibDbV2_gamma_t));
        memcpy(&handle->CalibDb.Gamma_v20, calibv2_agamma_calib, sizeof(CalibDbV2_gamma_t));
    }
    else if(CHECK_ISP_HW_V30()) {
        CalibDbV2_gamma_V30_t* calibv2_agamma_calib =
            (CalibDbV2_gamma_V30_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, agamma_calib));

        if (!calibv2_agamma_calib) {
            free(handle);
            return XCAM_RETURN_ERROR_MEM;
        }
        //memcpy(&handle->agammaAttr.stTool, calibv2_agamma_calib, sizeof(CalibDbV2_gamma_t));
        memcpy(&handle->CalibDb.Gamma_v30, calibv2_agamma_calib, sizeof(CalibDbV2_gamma_V30_t));
    }

    *pGammaCtx = handle;
    LOG1_AGAMMA("EXIT: %s \n", __func__);
    return(ret);

}

XCamReturn AgammaRelease(AgammaHandle_t* pGammaCtx)
{
    LOG1_AGAMMA("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (pGammaCtx)
        free(pGammaCtx);
    LOG1_AGAMMA("EXIT: %s \n", __func__);
    return(ret);

}

XCamReturn AgammaPreProc(AgammaHandle_t* pGammaCtx)
{
    LOG1_AGAMMA("ENTER: %s \n", __func__);

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    LOG1_AGAMMA("EXIT: %s \n", __func__);
    return(ret);

}

void AgammaAutoProc(AgammaHandle_t* pGammaCtx)
{
    LOG1_AGAMMA("ENTER: %s \n", __func__);

    if(CHECK_ISP_HW_V21()) {
        pGammaCtx->agamma_config.gamma_out_segnum = pGammaCtx->CalibDb.Gamma_v20.GammaTuningPara.Gamma_out_segnum;
        pGammaCtx->agamma_config.gamma_out_offset = pGammaCtx->CalibDb.Gamma_v20.GammaTuningPara.Gamma_out_offset;

        for(int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM; i++)
        {
            int tmp = pGammaCtx->CalibDb.Gamma_v20.GammaTuningPara.Gamma_curve[i];
            pGammaCtx->agamma_config.gamma_table[i] = tmp;
        }
    }
    else if(CHECK_ISP_HW_V30()) {
        pGammaCtx->agamma_config.gamma_out_segnum = ISP3X_SEGNUM_LOG_49;
        pGammaCtx->agamma_config.gamma_out_offset = pGammaCtx->CalibDb.Gamma_v30.GammaTuningPara.Gamma_out_offset;

        for(int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM_V30; i++)
        {
            int tmp = pGammaCtx->CalibDb.Gamma_v30.GammaTuningPara.Gamma_curve[i];
            pGammaCtx->agamma_config.gamma_table[i] = tmp;
        }
    }

    LOG1_AGAMMA("EXIT: %s \n", __func__);
}

void AgammaApiManualProc(AgammaHandle_t* pGammaCtx)
{
    LOG1_AGAMMA("ENTER: %s \n", __func__);
    LOGD_AGAMMA(" %s: Agamma api manual !!!\n", __func__);

    if(CHECK_ISP_HW_V21()) {
        pGammaCtx->agamma_config.gamma_en = pGammaCtx->agammaAttr.stManual.en ;
        if(pGammaCtx->agammaAttr.stManual.CurveType == RK_GAMMA_CURVE_TYPE_DEFUALT)
            AgammaAutoProc(pGammaCtx);
        else if(pGammaCtx->agammaAttr.stManual.CurveType == RK_GAMMA_CURVE_TYPE_SRGB)
        {
            float x[CALIBDB_AGAMMA_KNOTS_NUM] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 24, 28, 32, 40, 48, 56,
                                                  64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 448, 512, 640, 768, 896, 1024,
                                                  1280, 1536, 1792, 2048, 2560, 3072, 3584, 4095
                                                };
            float y[CALIBDB_AGAMMA_KNOTS_NUM];

            pGammaCtx->agamma_config.gamma_out_segnum = 0;
            pGammaCtx->agamma_config.gamma_out_offset = 0;
            for(int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM; i++)
            {
                y[i] = 4095 * pow(x[i] / 4095, 1 / 2.2) + pGammaCtx->agamma_config.gamma_out_offset;
                y[i] = LIMIT_VALUE(y[i], 4095, 0);
                pGammaCtx->agamma_config.gamma_table[i] = (int)(y[i] + 0.5);
            }
        }
        else if(pGammaCtx->agammaAttr.stManual.CurveType == RK_GAMMA_CURVE_TYPE_HDR)
        {
            float x[CALIBDB_AGAMMA_KNOTS_NUM] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 24, 28, 32, 40, 48, 56,
                                                  64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 448, 512, 640, 768, 896, 1024,
                                                  1280, 1536, 1792, 2048, 2560, 3072, 3584, 4095
                                                };
            float y[CALIBDB_AGAMMA_KNOTS_NUM];

            pGammaCtx->agamma_config.gamma_out_segnum = 0;
            pGammaCtx->agamma_config.gamma_out_offset = 0;
            for(int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM; i++)
            {
                y[i] = 4095 * pow(x[i] / 4095, 1 / 2.2) + pGammaCtx->agamma_config.gamma_out_offset;
                y[i] = LIMIT_VALUE(y[i], 4095, 0);
                pGammaCtx->agamma_config.gamma_table[i] = (int)(y[i] + 0.5);
            }
        }
        else if(pGammaCtx->agammaAttr.stManual.CurveType == RK_GAMMA_CURVE_TYPE_USER_DEFINE1)
        {
            float x[CALIBDB_AGAMMA_KNOTS_NUM] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 24, 28, 32, 40, 48, 56,
                                                  64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, 448, 512, 640, 768, 896, 1024,
                                                  1280, 1536, 1792, 2048, 2560, 3072, 3584, 4095
                                                };
            float y[CALIBDB_AGAMMA_KNOTS_NUM];
            float coef1 = pGammaCtx->agammaAttr.stManual.user1.coef1;
            float coef2 = pGammaCtx->agammaAttr.stManual.user1.coef2;

            coef2 = LIMIT_VALUE(coef2, 0.05, -0.05);
            pGammaCtx->agamma_config.gamma_out_segnum = 0;
            pGammaCtx->agamma_config.gamma_out_offset = 0;
            for(int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM; i++)
            {
                y[i] = 4095 * pow(x[i] / 4095, 1 / coef1 + coef2) + pGammaCtx->agamma_config.gamma_out_offset;
                y[i] = LIMIT_VALUE(y[i], 4095, 0);
                pGammaCtx->agamma_config.gamma_table[i] = (int)(y[i] + 0.5);
            }
        }
        else if(pGammaCtx->agammaAttr.stManual.CurveType == RK_GAMMA_CURVE_TYPE_USER_DEFINE2)
        {
            pGammaCtx->agamma_config.gamma_out_segnum = pGammaCtx->agammaAttr.stManual.user2.gamma_out_segnum;
            pGammaCtx->agamma_config.gamma_out_offset = pGammaCtx->agammaAttr.stManual.user2.gamma_out_offset;
            memcpy(pGammaCtx->agamma_config.gamma_table, pGammaCtx->agammaAttr.stManual.user2.gamma_table, sizeof(pGammaCtx->agamma_config.gamma_table));
        }
        else
            LOGE_AGAMMA(" %s: Wrong gamma api manual CurveType!!!\n", __func__);
    }
    else if(CHECK_ISP_HW_V30()) {
        //todo

    }

    LOG1_AGAMMA("EXIT: %s \n", __func__);
}

void AgammaApiToolProc(AgammaHandle_t* pGammaCtx)
{
    LOG1_AGAMMA("ENTER: %s \n", __func__);

    LOGD_AGAMMA(" %s: Agamma api tool !!!\n", __func__);

    if(CHECK_ISP_HW_V21()) {
        pGammaCtx->agamma_config.gamma_en = pGammaCtx->agammaAttr.stTool.GammaTuningPara.Gamma_en;
        pGammaCtx->agamma_config.gamma_out_segnum = pGammaCtx->agammaAttr.stTool.GammaTuningPara.Gamma_out_segnum;
        pGammaCtx->agamma_config.gamma_out_offset = pGammaCtx->agammaAttr.stTool.GammaTuningPara.Gamma_out_offset;
        for(int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM; i++) {
            int tmp = pGammaCtx->agammaAttr.stTool.GammaTuningPara.Gamma_curve[i];
            pGammaCtx->agamma_config.gamma_table[i] = tmp;
        }
    }
    else if(CHECK_ISP_HW_V30()) {
        //todo

    }

    LOG1_AGAMMA("EXIT: %s \n", __func__);
}

void AgammaProcessing(AgammaHandle_t* pGammaCtx)
{
    LOG1_AGAMMA("ENTER: %s \n", __func__);

    if(pGammaCtx->agammaAttr.mode == RK_AIQ_GAMMA_MODE_OFF)//run iq gamma
    {
        LOGD_AGAMMA(" %s: Agamma api off !!!\n", __func__);
        pGammaCtx->agamma_config.gamma_en = pGammaCtx->CalibDb.Gamma_v20.GammaTuningPara.Gamma_en;
        AgammaAutoProc(pGammaCtx);
    }
    else if(pGammaCtx->agammaAttr.mode == RK_AIQ_GAMMA_MODE_MANUAL)//run manual gamma, for client api
        AgammaApiManualProc( pGammaCtx);
    else if(pGammaCtx->agammaAttr.mode == RK_AIQ_GAMMA_MODE_TOOL)//run tool gamma,for tool
        AgammaApiToolProc( pGammaCtx);
    else
        LOGE_AGAMMA(" %s: Wrong gamma mode !!!\n", __func__);

    LOGD_AGAMMA(" %s: gamma_en:%d gamma_out_segnum:%d gamma_out_offset:%d\n", __func__, pGammaCtx->agamma_config.gamma_en, pGammaCtx->agamma_config.gamma_out_segnum
                , pGammaCtx->agamma_config.gamma_out_offset);

    LOG1_AGAMMA("EXIT: %s \n", __func__);
}

void AgammaSetProcRes(AgammaProcRes_t* AgammaProcRes, rk_aiq_gamma_cfg_t* agamma_config)
{
    LOG1_AGAMMA("ENTER: %s \n", __func__);

    if(CHECK_ISP_HW_V21()) {
        AgammaProcRes->Gamma_v20.gamma_en = agamma_config->gamma_en;
        AgammaProcRes->Gamma_v20.equ_segm = agamma_config->gamma_out_segnum;
        AgammaProcRes->Gamma_v20.offset = agamma_config->gamma_out_offset;
        for(int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM; i++)
            AgammaProcRes->Gamma_v20.gamma_y[i] = agamma_config->gamma_table[i];
    }
    else if(CHECK_ISP_HW_V30()) {
        AgammaProcRes->Gamma_v30.gamma_en = agamma_config->gamma_en;
        AgammaProcRes->Gamma_v30.EnableDot49 = agamma_config->gamma_out_segnum == ISP3X_SEGNUM_LOG_49 ? true : false;
        AgammaProcRes->Gamma_v30.equ_segm = agamma_config->gamma_out_segnum > 1 ? ISP3X_SEGNUM_LOG_45 : agamma_config->gamma_out_segnum;
        AgammaProcRes->Gamma_v30.offset = agamma_config->gamma_out_offset;
        for(int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM_V30; i++)
            AgammaProcRes->Gamma_v30.gamma_y[i] = agamma_config->gamma_table[i];
    }

    LOG1_AGAMMA("EXIT: %s \n", __func__);
}

RKAIQ_END_DECLARE
