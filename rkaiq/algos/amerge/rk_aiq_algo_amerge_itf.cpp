/*
 * rk_aiq_algo_amerge_itf.c
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

#include "amerge/rk_aiq_algo_amerge_itf.h"
#include "xcam_log.h"
#if RKAIQ_HAVE_MERGE_V10
#include "amerge/rk_aiq_amerge_algo_v10.h"
#endif
#if RKAIQ_HAVE_MERGE_V11
#include "amerge/rk_aiq_amerge_algo_v11.h"
#endif
#if RKAIQ_HAVE_MERGE_V12
#include "amerge/rk_aiq_amerge_algo_v12.h"
#endif
#include "amerge/rk_aiq_types_amerge_algo_prvt.h"
#include "rk_aiq_algo_types.h"


RKAIQ_BEGIN_DECLARE


static XCamReturn AmergeCreateCtx(RkAiqAlgoContext **context, const AlgoCtxInstanceCfg* cfg)
{

    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AmergeContext_t* pAmergeCtx = NULL;

    ret = AmergeInit(&pAmergeCtx, (CamCalibDbV2Context_t*)(cfg->calibv2));

    if (ret != XCAM_RETURN_NO_ERROR) {
        LOGE_AMERGE("%s Amerge Init failed: %d", __FUNCTION__, ret);
        return(XCAM_RETURN_ERROR_FAILED);
    }
    *context = (RkAiqAlgoContext *)(pAmergeCtx);

    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(ret);
}

static XCamReturn AmergeDestroyCtx(RkAiqAlgoContext *context)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if(context != NULL) {
        AmergeContext_t* pAmergeCtx = (AmergeContext_t*)context;
        ret = AmergeRelease(pAmergeCtx);
        if (ret != XCAM_RETURN_NO_ERROR) {
            LOGE_AMERGE("%s Amerge Release failed: %d", __FUNCTION__, ret);
            return(XCAM_RETURN_ERROR_FAILED);
        }
        context = NULL;
    }

    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

static XCamReturn AmergePrepare(RkAiqAlgoCom* params)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    AmergeContext_t* pAmergeCtx = (AmergeContext_t*)params->ctx;
    RkAiqAlgoConfigAmerge* AhdrCfgParam = (RkAiqAlgoConfigAmerge*)params; //come from params in html
    const CamCalibDbV2Context_t* pCalibDb = AhdrCfgParam->com.u.prepare.calibv2;

    if (AhdrCfgParam->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAmergeCtx->FrameNumber = LINEAR_NUM;
    else if (AhdrCfgParam->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR3 &&
             AhdrCfgParam->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAmergeCtx->FrameNumber = HDR_2X_NUM;
    else
        pAmergeCtx->FrameNumber = HDR_3X_NUM;

    if(!!(params->u.prepare.conf_type & RK_AIQ_ALGO_CONFTYPE_UPDATECALIB )) {
        LOGI_AMERGE("%s: Amerge Reload Para!\n", __FUNCTION__);
#if RKAIQ_HAVE_MERGE_V10
        CalibDbV2_merge_V10_t* calibv2_amerge_calib =
            (CalibDbV2_merge_V10_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, amerge_calib));
        memcpy(&pAmergeCtx->mergeAttrV10.stAuto, calibv2_amerge_calib,
               sizeof(CalibDbV2_merge_V10_t));  // set stAuto
#endif
#if RKAIQ_HAVE_MERGE_V11
        CalibDbV2_merge_V11_t* calibv2_amerge_calib =
            (CalibDbV2_merge_V11_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, amerge_calib));
        memcpy(&pAmergeCtx->mergeAttrV11.stAuto, calibv2_amerge_calib,
               sizeof(CalibDbV2_merge_V11_t));  // set stAuto
#endif
#if RKAIQ_HAVE_MERGE_V12
        CalibDbV2_merge_V12_t* calibv2_amerge_calib =
            (CalibDbV2_merge_V12_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, amerge_calib));
        memcpy(&pAmergeCtx->mergeAttrV12.stAuto, calibv2_amerge_calib,
               sizeof(CalibDbV2_merge_V12_t));  // set stAuto
#endif
    }

    if(/* !params->u.prepare.reconfig*/true) {
        AmergeStop(pAmergeCtx); // stop firstly for re-preapre
        ret = AmergeStart(pAmergeCtx);
        if (ret != XCAM_RETURN_NO_ERROR) {
            LOGE_AMERGE("%s Amerge Start failed: %d\n", __FUNCTION__, ret);
            return(XCAM_RETURN_ERROR_FAILED);
        }
    }

    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

static XCamReturn AmergePreProcess(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    AmergeContext_t* pAmergeCtx = (AmergeContext_t*)inparams->ctx;
    RkAiqAlgoConfigAmerge* AhdrCfgParam = (RkAiqAlgoConfigAmerge*)inparams;


    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

static XCamReturn AmergeProcess(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    bool bypass = false;

    AmergeContext_t* pAmergeCtx = (AmergeContext_t*)inparams->ctx;
    pAmergeCtx->frameCnt = inparams->frame_id > 2 ? (inparams->frame_id - 2) : 0;
    RkAiqAlgoProcAmerge* pAmergeParams = (RkAiqAlgoProcAmerge*)inparams;
    RkAiqAlgoProcResAmerge* pAmergeProcRes = (RkAiqAlgoProcResAmerge*)outparams;

    if(pAmergeCtx->FrameNumber == HDR_2X_NUM || pAmergeCtx->FrameNumber == HDR_3X_NUM) {
        LOGD_AMERGE("%s:/#####################################Amerge Start#####################################/ \n", __func__);

        //get Sensor Info
        XCamVideoBuffer* xCamAeProcRes = pAmergeParams->com.u.proc.res_comb->ae_proc_res;
        RkAiqAlgoProcResAe* pAEProcRes = NULL;
        if (xCamAeProcRes) {
            pAEProcRes = (RkAiqAlgoProcResAe*)xCamAeProcRes->map(xCamAeProcRes);
            pAmergeCtx->SensorInfo.LongFrmMode =
                pAEProcRes->ae_proc_res_rk.LongFrmMode && (pAmergeCtx->FrameNumber != LINEAR_NUM);
        }
        else {
            if (!(pAmergeCtx->frameCnt))
                return XCAM_RETURN_NO_ERROR;
            else {
                AecProcResult_t AeProcResult;
                memset(&AeProcResult, 0x0, sizeof(AecProcResult_t));
                LOGE_AMERGE("%s: Ae Proc result is null!!!\n", __FUNCTION__);
                pAmergeCtx->SensorInfo.LongFrmMode = false;
            }
        }

        //get ae pre res and proc
        XCamVideoBuffer* xCamAePreRes = pAmergeParams->com.u.proc.res_comb->ae_pre_res;
        RkAiqAlgoPreResAe* pAEPreRes = NULL;
        if (xCamAePreRes) {
            pAEPreRes = (RkAiqAlgoPreResAe*)xCamAePreRes->map(xCamAePreRes);
            bypass = AmergeByPassProcessing(pAmergeCtx, pAEPreRes->ae_pre_res_rk);
        }
        else {
            if (!(pAmergeCtx->frameCnt))
                return XCAM_RETURN_NO_ERROR;
            else {
                AecPreResult_t AecHdrPreResult;
                memset(&AecHdrPreResult, 0x0, sizeof(AecPreResult_t));
                bypass = AmergeByPassProcessing(pAmergeCtx, AecHdrPreResult);
                bypass = false;
                LOGE_AMERGE("%s: ae Pre result is null!!!\n", __FUNCTION__);
            }
        }

        //merge tuning para process
        if(!bypass)
            AmergeTuningProcessing(pAmergeCtx);

        //expo para process
        MergeExpoData_t ExpoData;
        memset(&ExpoData, 0, sizeof(MergeExpoData_t));
        if(pAmergeCtx->FrameNumber == HDR_2X_NUM) {
            ExpoData.nextSExpo = pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.analog_gain *
                                 pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.digital_gain * pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.integration_time;
            ExpoData.nextMExpo = pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain *
                                 pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain * pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.integration_time;
            ExpoData.nextLExpo = ExpoData.nextMExpo;

            ExpoData.nextSGain = pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.analog_gain * pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.digital_gain;
            ExpoData.nextMGain = pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain * pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain;

        }
        else if(pAmergeCtx->FrameNumber == HDR_3X_NUM) {
            ExpoData.nextSExpo = pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.analog_gain *
                                 pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.digital_gain * pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.integration_time;
            ExpoData.nextMExpo = pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain *
                                 pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain * pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.integration_time;
            ExpoData.nextLExpo = pAmergeParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.analog_gain *
                                 pAmergeParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.digital_gain * pAmergeParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.integration_time;

            ExpoData.nextSGain = pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.analog_gain * pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.digital_gain;
            ExpoData.nextMGain = pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain * pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain;
        }
        LOGV_AMERGE("%s: nextFrame: sexp: %f-%f, mexp: %f-%f, lexp: %f-%f\n", __FUNCTION__,
                    pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.analog_gain,
                    pAmergeParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.integration_time,
                    pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain,
                    pAmergeParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.integration_time,
                    pAmergeParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.analog_gain,
                    pAmergeParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.integration_time);
        if(ExpoData.nextSExpo > 0 )
            ExpoData.nextRatioLS = ExpoData.nextLExpo / ExpoData.nextSExpo;
        else
            LOGE_AMERGE("%s: Short frame for merge expo sync is ERROR!!!\n", __FUNCTION__);
        if(ExpoData.nextMExpo > 0 )
            ExpoData.nextRatioLM = ExpoData.nextLExpo / ExpoData.nextMExpo;
        else
            LOGE_AMERGE("%s: Middle frame for merge expo sync is ERROR!!!\n", __FUNCTION__);
        //clip for long frame mode
        if (pAmergeCtx->SensorInfo.LongFrmMode) {
            ExpoData.nextRatioLS = 1.0;
            ExpoData.nextRatioLM = 1.0;
        }

        if(ExpoData.nextRatioLS >= 1 && ExpoData.nextRatioLM >= 1)
            AmergeExpoProcessing(pAmergeCtx, &ExpoData);
        else
            LOGE_AMERGE("%s: AE ratio for merge expo sync is under one!!!\n", __FUNCTION__);

#if RKAIQ_HAVE_MERGE_V10
        pAmergeCtx->PrevData.CtrlData.ApiMode = pAmergeCtx->mergeAttrV10.opMode;
#endif
#if RKAIQ_HAVE_MERGE_V11
        pAmergeCtx->PrevData.CtrlData.ApiMode = pAmergeCtx->mergeAttrV11.opMode;
#endif
#if RKAIQ_HAVE_MERGE_V12
        pAmergeCtx->PrevData.CtrlData.ApiMode = pAmergeCtx->mergeAttrV12.opMode;
#endif
        pAmergeCtx->ProcRes.update = !bypass;
        pAmergeProcRes->AmergeProcRes.update = pAmergeCtx->ProcRes.update;
#if RKAIQ_HAVE_MERGE_V10
        memcpy(&pAmergeProcRes->AmergeProcRes.Merge_v10, &pAmergeCtx->ProcRes.Merge_v10,
               sizeof(MgeProcResV10_t));
#endif
#if RKAIQ_HAVE_MERGE_V11
        memcpy(&pAmergeProcRes->AmergeProcRes.Merge_v11, &pAmergeCtx->ProcRes.Merge_v11,
               sizeof(MgeProcResV11_t));
#endif
#if RKAIQ_HAVE_MERGE_V12
        memcpy(&pAmergeProcRes->AmergeProcRes.Merge_v12, &pAmergeCtx->ProcRes.Merge_v12,
               sizeof(MgeProcResV12_t));
#endif

        LOGD_AMERGE("%s:/#####################################Amerge Over#####################################/ \n", __func__);
    } else {
        LOGD_AMERGE("%s FrameID:%d, It's in Linear Mode, Merge function bypass\n", __FUNCTION__, pAmergeCtx->frameCnt);
    }

    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

static XCamReturn AmergePostProcess(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    //TODO

    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(XCAM_RETURN_NO_ERROR);
}

RkAiqAlgoDescription g_RkIspAlgoDescAmerge = {
    .common = {
        .version = RKISP_ALGO_AMERGE_VERSION,
        .vendor  = RKISP_ALGO_AMERGE_VENDOR,
        .description = RKISP_ALGO_AMERGE_DESCRIPTION,
        .type    = RK_AIQ_ALGO_TYPE_AMERGE,
        .id      = 0,
        .create_context  = AmergeCreateCtx,
        .destroy_context = AmergeDestroyCtx,
    },
    .prepare = AmergePrepare,
    .pre_process = NULL,
    .processing = AmergeProcess,
    .post_process = NULL,
};

RKAIQ_END_DECLARE
