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

#include "rk_aiq_algo_adhaz_itf.h"
#include "RkAiqCalibDbTypes.h"
#if RKAIQ_HAVE_DEHAZE_V1
#include "adehaze/rk_aiq_adehaze_algo_v1.h"
#endif
#if RKAIQ_HAVE_DEHAZE_V2
#include "adehaze/rk_aiq_adehaze_algo_v2.h"
#endif
#if RKAIQ_HAVE_DEHAZE_V3
#include "adehaze/rk_aiq_adehaze_algo_v3.h"
#endif
#include "RkAiqCalibDbTypes.h"
#include "rk_aiq_algo_types.h"
#include "xcam_log.h"

RKAIQ_BEGIN_DECLARE

static XCamReturn
create_context(RkAiqAlgoContext **context, const AlgoCtxInstanceCfg* cfg)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t *pAdehazeHandle = NULL;

    ret = AdehazeInit(&pAdehazeHandle, (CamCalibDbV2Context_t*)(cfg->calibv2));

    if (ret != XCAM_RETURN_NO_ERROR) {
        LOGE_ADEHAZE("%s Adehaze Init failed: %d", __FUNCTION__, ret);
        return(XCAM_RETURN_ERROR_FAILED);
    }

    *context = (RkAiqAlgoContext *)(pAdehazeHandle);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return ret;
}

static XCamReturn
destroy_context(RkAiqAlgoContext *context)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t *pAdehazeHandle = (AdehazeHandle_t *)context;

    ret = AdehazeRelease(pAdehazeHandle);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return ret;
}

static XCamReturn
prepare(RkAiqAlgoCom* params)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoConfigAdhaz* config = (RkAiqAlgoConfigAdhaz*)params;
    AdehazeHandle_t * pAdehazeHandle = (AdehazeHandle_t *)params->ctx;
    const CamCalibDbV2Context_t* pCalibDb = config->com.u.prepare.calibv2;

    pAdehazeHandle->working_mode = config->com.u.prepare.working_mode;
    pAdehazeHandle->is_multi_isp_mode = config->is_multi_isp_mode;

    if (pAdehazeHandle->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAdehazeHandle->FrameNumber = LINEAR_NUM;
    else if (pAdehazeHandle->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR3 &&
             pAdehazeHandle->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAdehazeHandle->FrameNumber = HDR_2X_NUM;
    else
        pAdehazeHandle->FrameNumber = HDR_3X_NUM;

    if(!!(params->u.prepare.conf_type & RK_AIQ_ALGO_CONFTYPE_UPDATECALIB )) {
        LOGD_ADEHAZE("%s: Adehaze Reload Para!\n", __FUNCTION__);
#if RKAIQ_HAVE_DEHAZE_V1
        CalibDbV2_dehaze_V20_t* calibv2_adehaze_calib_V20 =
            (CalibDbV2_dehaze_V20_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adehaze_calib_v20));
        if (calibv2_adehaze_calib_V20)
            memcpy(&pAdehazeHandle->Calib.Dehaze_v20, calibv2_adehaze_calib_V20, sizeof(CalibDbV2_dehaze_V20_t));
#endif
#if RKAIQ_HAVE_DEHAZE_V2
        CalibDbV2_dehaze_V21_t* calibv2_adehaze_calib_V21 =
            (CalibDbV2_dehaze_V21_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adehaze_calib_v21));
        if (calibv2_adehaze_calib_V21)
            memcpy(&pAdehazeHandle->Calib.Dehaze_v21, calibv2_adehaze_calib_V21, sizeof(CalibDbV2_dehaze_V21_t));
#endif
#if RKAIQ_HAVE_DEHAZE_V3
        CalibDbV2_dehaze_V30_t* calibv2_adehaze_calib_V30 =
            (CalibDbV2_dehaze_V30_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adehaze_calib_v30));
        if (calibv2_adehaze_calib_V30)
            memcpy(&pAdehazeHandle->Calib.Dehaze_v30, calibv2_adehaze_calib_V30, sizeof(CalibDbV2_dehaze_V30_t));

        //dehaze local gain
        CalibDbV2_YnrV3_t*  calibv2_Ynr =
            (CalibDbV2_YnrV3_t *)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, ynr_v3));
        if (calibv2_Ynr)
            memcpy(&pAdehazeHandle->Calib.Dehaze_v30.YnrCalibPara, &calibv2_Ynr->CalibPara, sizeof(CalibDbV2_YnrV3_CalibPara_t));
#endif
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return ret;
}

static XCamReturn
pre_process(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    AdehazeHandle_t * pAdehazeHandle = (AdehazeHandle_t *)inparams->ctx;
    pAdehazeHandle->FrameID = inparams->frame_id;
    RkAiqAlgoPreAdhaz* config = (RkAiqAlgoPreAdhaz*)inparams;

    pAdehazeHandle->width = config->rawWidth;
    pAdehazeHandle->height = config->rawHeight;

    AdehazeGetStats(pAdehazeHandle, &config->stats);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
processing(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t * pAdehazeHandle = (AdehazeHandle_t *)inparams->ctx;
    RkAiqAlgoProcAdhaz* pProcPara = (RkAiqAlgoProcAdhaz*)inparams;
    RkAiqAlgoProcResAdhaz* pProcRes = (RkAiqAlgoProcResAdhaz*)outparams;

    LOGD_ADEHAZE("/*************************Adehaze Start******************/ \n");

    AdehazeGetCurrData(pAdehazeHandle, pProcPara);

#if RKAIQ_HAVE_DEHAZE_V3
    //get ynr snr mode
    if(pProcPara->com.u.proc.curExp->CISFeature.SNR == 0)
        pAdehazeHandle->CurrData.V30.SnrMode = YNRSNRMODE_LSNR;
    else if(pProcPara->com.u.proc.curExp->CISFeature.SNR == 1)
        pAdehazeHandle->CurrData.V30.SnrMode = YNRSNRMODE_HSNR;
    else {
        LOGI_ADEHAZE("%s(%d) Adehaze Get Wrong Snr Mode!!!, Using LSNR Params \n", __func__, __LINE__);
        pAdehazeHandle->CurrData.V30.SnrMode = YNRSNRMODE_LSNR;
    }
#endif

    //process
    if(!(AdehazeByPassProcessing(pAdehazeHandle)))
        ret = AdehazeProcess(pAdehazeHandle);

    //store data
#if RKAIQ_HAVE_DEHAZE_V1
    pAdehazeHandle->PreData.V20.ApiMode = pAdehazeHandle->AdehazeAtrr.mode;
#endif
#if RKAIQ_HAVE_DEHAZE_V2
    pAdehazeHandle->PreData.V21.ApiMode = pAdehazeHandle->AdehazeAtrr.mode;
#endif
#if RKAIQ_HAVE_DEHAZE_V3
    pAdehazeHandle->PreData.V30.ApiMode = pAdehazeHandle->AdehazeAtrr.mode;
#endif

    //proc res
#if RKAIQ_HAVE_DEHAZE_V1
    pAdehazeHandle->ProcRes.ProcResV20.enable = true;
    pAdehazeHandle->ProcRes.ProcResV20.update = !(pAdehazeHandle->byPassProc) ;
#endif
#if RKAIQ_HAVE_DEHAZE_V2
    pAdehazeHandle->ProcRes.ProcResV21.enable = pAdehazeHandle->ProcRes.ProcResV21.enable;
    pAdehazeHandle->ProcRes.ProcResV21.update = !(pAdehazeHandle->byPassProc);
#endif
#if RKAIQ_HAVE_DEHAZE_V3
    pAdehazeHandle->ProcRes.ProcResV30.enable = pAdehazeHandle->ProcRes.ProcResV30.enable;
    pAdehazeHandle->ProcRes.ProcResV30.update = !(pAdehazeHandle->byPassProc);
#endif
    memcpy(&pProcRes->AdehzeProcRes, &pAdehazeHandle->ProcRes, sizeof(RkAiqAdehazeProcResult_t));

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
