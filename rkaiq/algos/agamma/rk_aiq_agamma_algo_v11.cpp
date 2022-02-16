/*
 * rk_aiq_agamma_algo_v2.cp
 *
 *  Copyright (c) 2019-2022 Rockchip Eletronics Co., Ltd.
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
#include "rk_aiq_agamma_algo_v11.h"

#include <string.h>

#include "rk_aiq_types_agamma_algo_int.h"
#include "rk_aiq_types_agamma_algo_prvt.h"
#include "xcam_common.h"

RKAIQ_BEGIN_DECLARE

XCamReturn AgammaInit(AgammaHandle_t** pGammaCtx, CamCalibDbV2Context_t* pCalib) {
    LOG1_AGAMMA("ENTER: %s \n", __func__);
    XCamReturn ret         = XCAM_RETURN_NO_ERROR;
    AgammaHandle_t* handle = (AgammaHandle_t*)calloc(sizeof(AgammaHandle_t), 1);
    if (NULL == handle) return XCAM_RETURN_ERROR_MEM;

    CalibDbV2_gamma_V11_t* calibv2_agamma_calib =
        (CalibDbV2_gamma_V11_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, agamma_calib));

    if (!calibv2_agamma_calib) {
        free(handle);
        return XCAM_RETURN_ERROR_MEM;
    }
    memcpy(&handle->agammaAttrV11.stAuto, calibv2_agamma_calib, sizeof(CalibDbV2_gamma_V11_t));

    // default para
    handle->agammaAttrV11.mode              = RK_AIQ_GAMMA_MODE_AUTO;
    handle->agammaAttrV11.stManual.Gamma_en = handle->agammaAttrV11.stAuto.GammaTuningPara.Gamma_en;
    handle->agammaAttrV11.stManual.Gamma_out_offset =
        handle->agammaAttrV11.stAuto.GammaTuningPara.Gamma_out_offset;
    for (int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM_V11; i++)
        handle->agammaAttrV11.stManual.Gamma_curve[i] =
            handle->agammaAttrV11.stAuto.GammaTuningPara.Gamma_curve[i];

    *pGammaCtx = handle;
    LOG1_AGAMMA("EXIT: %s \n", __func__);
    return (ret);
}

XCamReturn AgammaRelease(AgammaHandle_t* pGammaCtx) {
    LOG1_AGAMMA("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (pGammaCtx) free(pGammaCtx);

    LOG1_AGAMMA("EXIT: %s \n", __func__);
    return (ret);
}

void AgammaProcessing(AgammaHandle_t* pGammaCtx) {
    LOG1_AGAMMA("ENTER: %s \n", __func__);

    if (pGammaCtx->agammaAttrV11.mode == RK_AIQ_GAMMA_MODE_AUTO) {  // run iq gamma
        LOGD_AGAMMA(" %s: Agamma api Auto !!!\n", __func__);
        pGammaCtx->agamma_config.gamma_en =
            pGammaCtx->agammaAttrV11.stAuto.GammaTuningPara.Gamma_en;
        if (pGammaCtx->agamma_config.gamma_en) {
            pGammaCtx->agamma_config.gamma_out_segnum = ISP3X_SEGNUM_LOG_49;
            pGammaCtx->agamma_config.gamma_out_offset =
                pGammaCtx->agammaAttrV11.stAuto.GammaTuningPara.Gamma_out_offset;

            for (int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM_V11; i++) {
                int tmp = pGammaCtx->agammaAttrV11.stAuto.GammaTuningPara.Gamma_curve[i];
                pGammaCtx->agamma_config.gamma_table[i] =
                    LIMIT_VALUE(tmp, GAMMA_CRUVE_MAX, GAMMA_CRUVE_MIN);
            }
        }
    } else if (pGammaCtx->agammaAttrV11.mode ==
               RK_AIQ_GAMMA_MODE_MANUAL) {  // run manual gamma, for client api
        LOGD_AGAMMA(" %s: Agamma api Manu !!!\n", __func__);
        pGammaCtx->agamma_config.gamma_en = pGammaCtx->agammaAttrV11.stManual.Gamma_en;
        if (pGammaCtx->agamma_config.gamma_en) {
            pGammaCtx->agamma_config.gamma_out_segnum = ISP3X_SEGNUM_LOG_49;
            pGammaCtx->agamma_config.gamma_out_offset =
                pGammaCtx->agammaAttrV11.stManual.Gamma_out_offset;

            for (int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM_V11; i++) {
                int tmp = pGammaCtx->agammaAttrV11.stManual.Gamma_curve[i];
                pGammaCtx->agamma_config.gamma_table[i] =
                    LIMIT_VALUE(tmp, GAMMA_CRUVE_MAX, GAMMA_CRUVE_MIN);
            }
        }
    } else
        LOGE_AGAMMA(" %s: Wrong gamma mode !!!\n", __func__);

    LOGD_AGAMMA(" %s: gamma_en:%d gamma_out_segnum:%d gamma_out_offset:%d\n", __func__,
                pGammaCtx->agamma_config.gamma_en, pGammaCtx->agamma_config.gamma_out_segnum,
                pGammaCtx->agamma_config.gamma_out_offset);

    LOG1_AGAMMA("EXIT: %s \n", __func__);
}

void AgammaSetProcRes(AgammaProcRes_t* AgammaProcRes, rk_aiq_gamma_cfg_t* agamma_config) {
    LOG1_AGAMMA("ENTER: %s \n", __func__);

    AgammaProcRes->Gamma_v11.gamma_en = agamma_config->gamma_en;
    if (AgammaProcRes->Gamma_v11.gamma_en) {
        AgammaProcRes->Gamma_v11.EnableDot49 =
            agamma_config->gamma_out_segnum == ISP3X_SEGNUM_LOG_49 ? true : false;
        AgammaProcRes->Gamma_v11.equ_segm = agamma_config->gamma_out_segnum > 1
                                                ? ISP3X_SEGNUM_LOG_45
                                                : agamma_config->gamma_out_segnum;
        AgammaProcRes->Gamma_v11.offset = agamma_config->gamma_out_offset;
        for (int i = 0; i < CALIBDB_AGAMMA_KNOTS_NUM_V11; i++)
            AgammaProcRes->Gamma_v11.gamma_y[i] = agamma_config->gamma_table[i];
    }

    LOG1_AGAMMA("EXIT: %s \n", __func__);
}

RKAIQ_END_DECLARE
