/*
 * rk_aiq_algo_adhaz_itf.c
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
/* for rockchip v2.0.0*/

#include "rk_aiq_algo_types_int.h"
#include "rk_aiq_algo_adhaz_itf.h"
#include "RkAiqCalibDbTypes.h"
#include "adehaze/rk_aiq_adehaze_algo.h"
#include "RkAiqCalibDbTypes.h"
#include "xcam_log.h"

RKAIQ_BEGIN_DECLARE

static XCamReturn
create_context(RkAiqAlgoContext **context, const AlgoCtxInstanceCfg* cfg)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t *AdehazeHandle = NULL;
    AlgoCtxInstanceCfgInt* instanc_int = (AlgoCtxInstanceCfgInt*)cfg;

    ret = AdehazeInit(&AdehazeHandle, (CamCalibDbV2Context_t*)(instanc_int->calibv2));

    if (ret != XCAM_RETURN_NO_ERROR) {
        LOGE_ADEHAZE("%s Adehaze Init failed: %d", __FUNCTION__, ret);
        return(XCAM_RETURN_ERROR_FAILED);
    }

    *context = (RkAiqAlgoContext *)(AdehazeHandle);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return ret;
}

static XCamReturn
destroy_context(RkAiqAlgoContext *context)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t *AdehazeHandle = (AdehazeHandle_t *)context;

    ret = AdehazeRelease(AdehazeHandle);

    return ret;
}

static XCamReturn
prepare(RkAiqAlgoCom* params)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoConfigAdhazInt* config = (RkAiqAlgoConfigAdhazInt*)params;
    AdehazeHandle_t * AdehazeHandle = (AdehazeHandle_t *)params->ctx;
    const CamCalibDbV2Context_t* pCalibDb = config->rk_com.u.prepare.calibv2;

    AdehazeHandle->working_mode = config->adhaz_config_com.com.u.prepare.working_mode;
    AdehazeHandle->is_multi_isp_mode = config->is_multi_isp_mode;

    if (AdehazeHandle->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR2)
        AdehazeHandle->FrameNumber = 1;
    else if (AdehazeHandle->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR3 &&
             AdehazeHandle->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2)
        AdehazeHandle->FrameNumber = 2;
    else
        AdehazeHandle->FrameNumber = 3;

    if(!!(params->u.prepare.conf_type & RK_AIQ_ALGO_CONFTYPE_UPDATECALIB )) {
        LOGD_ADEHAZE("%s: Adehaze Reload Para!\n", __FUNCTION__);

        if(AdehazeHandle->HWversion == ADEHAZE_ISP21) {
            CalibDbV2_dehaze_V20_t* calibv2_adehaze_calib_V20 =
                (CalibDbV2_dehaze_V20_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adehaze_calib_v20));
            if (calibv2_adehaze_calib_V20)
                memcpy(&AdehazeHandle->Calib.Dehaze_v20, calibv2_adehaze_calib_V20, sizeof(CalibDbV2_dehaze_V20_t));
        }
        else if(AdehazeHandle->HWversion == ADEHAZE_ISP21) {
            CalibDbV2_dehaze_V21_t* calibv2_adehaze_calib_V21 =
                (CalibDbV2_dehaze_V21_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adehaze_calib_v21));
            if (calibv2_adehaze_calib_V21)
                memcpy(&AdehazeHandle->Calib.Dehaze_v21, calibv2_adehaze_calib_V21, sizeof(CalibDbV2_dehaze_V21_t));
        }
        else if(AdehazeHandle->HWversion == ADEHAZE_ISP30) {
            CalibDbV2_dehaze_V30_t* calibv2_adehaze_calib_V30 =
                (CalibDbV2_dehaze_V30_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adehaze_calib_v30));
            if (calibv2_adehaze_calib_V30)
                memcpy(&AdehazeHandle->Calib.Dehaze_v30, calibv2_adehaze_calib_V30, sizeof(CalibDbV2_dehaze_V30_t));
        }
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return ret;

}

static XCamReturn
pre_process(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    AdehazeHandle_t * AdehazeHandle = (AdehazeHandle_t *)inparams->ctx;
    AdehazeHandle->FrameID = inparams->frame_id;
    RkAiqAlgoPreAdhazInt* config = (RkAiqAlgoPreAdhazInt*)inparams;

    AdehazeHandle->width = config->rawWidth;
    AdehazeHandle->height = config->rawHeight;

    AdehazeGetStats(AdehazeHandle, &config->stats);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
processing(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t * AdehazeHandle = (AdehazeHandle_t *)inparams->ctx;
    RkAiqAlgoProcAdhazInt* procPara = (RkAiqAlgoProcAdhazInt*)inparams;
    RkAiqAlgoProcResAdhaz* procResPara = (RkAiqAlgoProcResAdhaz*)outparams;

    LOGD_ADEHAZE("/*************************Adehaze Start******************/ \n");

    AdehazeGetCurrData(AdehazeHandle, procPara);

    //process
    if(!(AdehazeByPassProcessing(AdehazeHandle)))
        ret = AdehazeProcess(AdehazeHandle, AdehazeHandle->HWversion);

    //store data
    if(AdehazeHandle->HWversion == ADEHAZE_ISP20)
        AdehazeHandle->PreData.V20.ApiMode = AdehazeHandle->AdehazeAtrr.AdehazeAtrrV20.mode;
    else if(AdehazeHandle->HWversion == ADEHAZE_ISP21)
        AdehazeHandle->PreData.V21.ApiMode = AdehazeHandle->AdehazeAtrr.AdehazeAtrrV21.mode;
    else if(AdehazeHandle->HWversion == ADEHAZE_ISP30)
        AdehazeHandle->PreData.V30.ApiMode = AdehazeHandle->AdehazeAtrr.AdehazeAtrrV30.mode;


    //proc res
    if(AdehazeHandle->HWversion == ADEHAZE_ISP20) {
        AdehazeHandle->ProcRes.ProcResV20.enable = true;
        AdehazeHandle->ProcRes.ProcResV20.update = !(AdehazeHandle->byPassProc) ;
    }
    else if(AdehazeHandle->HWversion == ADEHAZE_ISP21) {
        AdehazeHandle->ProcRes.ProcResV21.enable = true;
        AdehazeHandle->ProcRes.ProcResV21.update = !(AdehazeHandle->byPassProc);
    }
    else if(AdehazeHandle->HWversion == ADEHAZE_ISP30) {
        AdehazeHandle->ProcRes.ProcResV30.enable = true;
        AdehazeHandle->ProcRes.ProcResV30.update = !(AdehazeHandle->byPassProc);
    }
    memcpy(&procResPara->AdehzeProcRes, &AdehazeHandle->ProcRes, sizeof(RkAiqAdehazeProcResult_t));

    LOGD_ADEHAZE("/*************************Adehaze over******************/ \n");

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return ret;
}

static XCamReturn
post_process(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    return XCAM_RETURN_NO_ERROR;
}

RkAiqAlgoDescription g_RkIspAlgoDescAdhaz = {
    .common = {
        .version = RKISP_ALGO_ADHAZ_VERSION,
        .vendor  = RKISP_ALGO_ADHAZ_VENDOR,
        .description = RKISP_ALGO_ADHAZ_DESCRIPTION,
        .type    = RK_AIQ_ALGO_TYPE_ADHAZ,
        .id      = 0,
        .create_context  = create_context,
        .destroy_context = destroy_context,
    },
    .prepare = prepare,
    .pre_process = pre_process,
    .processing = processing,
    .post_process = post_process,
};

RKAIQ_END_DECLARE
