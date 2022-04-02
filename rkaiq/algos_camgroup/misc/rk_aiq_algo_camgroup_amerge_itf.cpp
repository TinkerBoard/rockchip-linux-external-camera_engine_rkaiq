/*
 * rk_aiq_algo_camgroup_amerge_itf.c
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

#include "rk_aiq_algo_camgroup_types.h"
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
#include "algos/amerge/rk_aiq_types_amerge_algo_prvt.h"
#include "algos/amerge/rk_aiq_algo_amerge_itf.h"



RKAIQ_BEGIN_DECLARE


static XCamReturn AmergeCreateCtx(RkAiqAlgoContext **context, const AlgoCtxInstanceCfg* cfg)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    AlgoCtxInstanceCfgCamGroup* instanc_int = (AlgoCtxInstanceCfgCamGroup*)cfg;
    AmergeContext_t* pAmergeGrpCtx = NULL;

    ret = AmergeInit(&pAmergeGrpCtx, (CamCalibDbV2Context_t*)(instanc_int->s_calibv2));

    if (ret != XCAM_RETURN_NO_ERROR) {
        LOGE_AMERGE("%s Amerge Init failed: %d", __FUNCTION__, ret);
        return(XCAM_RETURN_ERROR_FAILED);
    }
    *context = (RkAiqAlgoContext *)(pAmergeGrpCtx);

    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(ret);
}

static XCamReturn AmergeDestroyCtx(RkAiqAlgoContext *context)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if(context != NULL) {
        AmergeContext_t* pAmergeGrpCtx = (AmergeContext_t*)context;
        ret = AmergeRelease(pAmergeGrpCtx);
        if (ret != XCAM_RETURN_NO_ERROR) {
            LOGE_AMERGE("%s Amerge Release failed: %d", __FUNCTION__, ret);
            return(XCAM_RETURN_ERROR_FAILED);
        }
        context = NULL;
    }

    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(ret);
}

static XCamReturn AmergePrepare(RkAiqAlgoCom* params)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    AmergeContext_t* pAmergeGrpCtx = (AmergeContext_t*)params->ctx;
    RkAiqAlgoCamGroupPrepare* pAmergePrepParams = (RkAiqAlgoCamGroupPrepare*)params; //come from params in html
    const CamCalibDbV2Context_t* pCalibDb = pAmergePrepParams->s_calibv2;

    if (pAmergePrepParams->gcom.com.u.prepare.working_mode < RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAmergeGrpCtx->FrameNumber = LINEAR_NUM;
    else if (pAmergePrepParams->gcom.com.u.prepare.working_mode < RK_AIQ_WORKING_MODE_ISP_HDR3 &&
             pAmergePrepParams->gcom.com.u.prepare.working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAmergeGrpCtx->FrameNumber = HDR_2X_NUM;
    else
        pAmergeGrpCtx->FrameNumber = HDR_3X_NUM;

    if(!!(params->u.prepare.conf_type & RK_AIQ_ALGO_CONFTYPE_UPDATECALIB )) {
        LOGD_AMERGE("%s: Amerge Reload Para!\n", __FUNCTION__);
#if RKAIQ_HAVE_MERGE_V10
        CalibDbV2_merge_V10_t* calibv2_amerge_calib =
            (CalibDbV2_merge_V10_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, amerge_calib));
        memcpy(&pAmergeGrpCtx->CalibDBV10, calibv2_amerge_calib,
               sizeof(CalibDbV2_merge_V10_t));  // load iq paras
        memcpy(&pAmergeGrpCtx->mergeAttrV10.stAuto, calibv2_amerge_calib,
               sizeof(CalibDbV2_merge_V10_t));  // set stAuto
#endif
#if RKAIQ_HAVE_MERGE_V11
        CalibDbV2_merge_V11_t* calibv2_amerge_calib =
            (CalibDbV2_merge_V11_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, amerge_calib));
        memcpy(&pAmergeGrpCtx->CalibDBV11, calibv2_amerge_calib,
               sizeof(CalibDbV2_merge_V11_t));  // load iq paras
        memcpy(&pAmergeGrpCtx->mergeAttrV11.stAuto, calibv2_amerge_calib,
               sizeof(CalibDbV2_merge_V11_t));  // set stAuto
#endif
#if RKAIQ_HAVE_MERGE_V12
        CalibDbV2_merge_V12_t* calibv2_amerge_calib =
            (CalibDbV2_merge_V12_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, amerge_calib));
        memcpy(&pAmergeGrpCtx->CalibDBV12, calibv2_amerge_calib,
               sizeof(CalibDbV2_merge_V12_t));  // load iq paras
        memcpy(&pAmergeGrpCtx->mergeAttrV12.stAuto, calibv2_amerge_calib,
               sizeof(CalibDbV2_merge_V12_t));  // set stAuto
#endif
    }

    if(/* !params->u.prepare.reconfig*/true) {
        AmergeStop(pAmergeGrpCtx); // stop firstly for re-preapre
        ret = AmergeStart(pAmergeGrpCtx);
        if (ret != XCAM_RETURN_NO_ERROR) {
            LOGE_AMERGE("%s Amerge Start failed: %d\n", __FUNCTION__, ret);
            return(XCAM_RETURN_ERROR_FAILED);
        }
    }

    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(ret);
}

static XCamReturn AmergeProcess(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    bool bypass = false;

    AmergeContext_t* pAmergeGrpCtx = (AmergeContext_t*)inparams->ctx;
    pAmergeGrpCtx->frameCnt = inparams->frame_id > 2 ? (inparams->frame_id - 2) : 0;
    RkAiqAlgoCamGroupProcIn* pAmergeGrpParams = (RkAiqAlgoCamGroupProcIn*)inparams;
    RkAiqAlgoCamGroupProcOut* pAmergeGrpProcRes = (RkAiqAlgoCamGroupProcOut*)outparams;

    if(pAmergeGrpCtx->FrameNumber == HDR_2X_NUM || pAmergeGrpCtx->FrameNumber == HDR_3X_NUM || pAmergeGrpCtx->SensorInfo.LongFrmMode) {
        LOGD_AMERGE("/#####################################Amerge Group Start#####################################/ \n");

        //get Sensor Info
        XCamVideoBuffer* xCamAeProcRes = pAmergeGrpParams->camgroupParmasArray[0]->aec._aeProcRes;
        RkAiqAlgoProcResAe* pAEProcRes = NULL;
        if (xCamAeProcRes) {
            pAEProcRes = (RkAiqAlgoProcResAe*)xCamAeProcRes->map(xCamAeProcRes);
            AmergeGetSensorInfo(pAmergeGrpCtx, pAEProcRes->ae_proc_res_rk);
        }
        else {
            if (!(pAmergeGrpCtx->frameCnt))
                return XCAM_RETURN_NO_ERROR;
            else {
                AecProcResult_t AeProcResult;
                memset(&AeProcResult, 0x0, sizeof(AecProcResult_t));
                LOGE_AMERGE("%s: Ae Proc result is null!!!\n", __FUNCTION__);
                AmergeGetSensorInfo(pAmergeGrpCtx, AeProcResult);
            }
        }

        //get ae pre res and proc
        XCamVideoBuffer* xCamAePreRes = pAmergeGrpParams->camgroupParmasArray[0]->aec._aePreRes;
        RkAiqAlgoPreResAe* pAEPreRes = NULL;
        if (xCamAePreRes) {
            pAEPreRes = (RkAiqAlgoPreResAe*)xCamAePreRes->map(xCamAePreRes);
            bypass = AmergeByPassProcessing(pAmergeGrpCtx, pAEPreRes->ae_pre_res_rk);
        }
        else {
            if (!(pAmergeGrpCtx->frameCnt))
                return XCAM_RETURN_NO_ERROR;
            else {
                AecPreResult_t AecHdrPreResult;
                memset(&AecHdrPreResult, 0x0, sizeof(AecPreResult_t));
                bypass = AmergeByPassProcessing(pAmergeGrpCtx, AecHdrPreResult);
                bypass = false;
                LOGE_AMERGE("%s: ae Pre result is null!!!\n", __FUNCTION__);
            }
        }

        //merge tuning para process
        if(!bypass)
            AmergeTuningProcessing(pAmergeGrpCtx);

        //expo para process
        MergeExpoData_t ExpoData;
        memset(&ExpoData, 0, sizeof(MergeExpoData_t));
        if(pAmergeGrpCtx->FrameNumber == HDR_2X_NUM) {
            ExpoData.nextSExpo = pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.analog_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.digital_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.integration_time;
            ExpoData.nextMExpo = pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.analog_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.digital_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.integration_time;
            ExpoData.nextLExpo = ExpoData.nextMExpo;

            ExpoData.nextSGain = pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.analog_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.digital_gain;
            ExpoData.nextMGain = pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.analog_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.digital_gain;
        }
        else if(pAmergeGrpCtx->FrameNumber == HDR_3X_NUM) {
            ExpoData.nextSExpo = pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.analog_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.digital_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.integration_time;
            ExpoData.nextMExpo = pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.analog_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.digital_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.integration_time;
            ExpoData.nextLExpo = pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[2].exp_real_params.analog_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[2].exp_real_params.digital_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[2].exp_real_params.integration_time;

            ExpoData.nextSGain = pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.analog_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.digital_gain;
            ExpoData.nextMGain = pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.analog_gain *
                                 pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.digital_gain;
        }
        LOGV_AMERGE("%s: nextFrame: sexp: %f-%f, mexp: %f-%f, lexp: %f-%f\n", __FUNCTION__,
                    pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.analog_gain,
                    pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.integration_time,
                    pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.analog_gain,
                    pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.integration_time,
                    pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[2].exp_real_params.analog_gain,
                    pAmergeGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[2].exp_real_params.integration_time);
        if(ExpoData.nextSExpo > 0 )
            ExpoData.nextRatioLS = ExpoData.nextLExpo / ExpoData.nextSExpo;
        else
            LOGE_AMERGE("%s: Short frame for merge expo sync is ERROR!!!\n", __FUNCTION__);
        if(ExpoData.nextMExpo > 0 )
            ExpoData.nextRatioLM = ExpoData.nextLExpo / ExpoData.nextMExpo;
        else
            LOGE_AMERGE("%s: Middle frame for merge expo sync is ERROR!!!\n", __FUNCTION__);
        //clip for long frame mode
        if (pAmergeGrpCtx->SensorInfo.LongFrmMode) {
            ExpoData.nextRatioLS = 1.0;
            ExpoData.nextRatioLM = 1.0;
        }

        //clip for Longframe mode
        if(pAmergeGrpCtx->SensorInfo.LongFrmMode) {
            ExpoData.nextRatioLS = 1;
            ExpoData.nextRatioLM = 1;
        }

        if(ExpoData.nextRatioLS >= 1 && ExpoData.nextRatioLM >= 1)
            AmergeExpoProcessing(pAmergeGrpCtx, &ExpoData);
        else
            LOGE_AMERGE("%s: AE ratio for merge expo sync is under one!!!\n", __FUNCTION__);

#if RKAIQ_HAVE_MERGE_V10
        pAmergeGrpCtx->PrevData.CtrlData.ApiMode = pAmergeGrpCtx->mergeAttrV10.opMode;
#endif
#if RKAIQ_HAVE_MERGE_V11
        pAmergeGrpCtx->PrevData.CtrlData.ApiMode = pAmergeGrpCtx->mergeAttrV11.opMode;
#endif
#if RKAIQ_HAVE_MERGE_V12
        pAmergeGrpCtx->PrevData.CtrlData.ApiMode = pAmergeGrpCtx->mergeAttrV12.opMode;
#endif
        pAmergeGrpCtx->ProcRes.update = !bypass;
        for(int i = 0; i < pAmergeGrpProcRes->arraySize; i++) {
            pAmergeGrpProcRes->camgroupParmasArray[i]->_amergeConfig->update = pAmergeGrpCtx->ProcRes.update;
#if RKAIQ_HAVE_MERGE_V10
            memcpy(&pAmergeGrpProcRes->camgroupParmasArray[i]->_amergeConfig->Merge_v10,
                   &pAmergeGrpCtx->ProcRes.Merge_v10, sizeof(MgeProcResV10_t));
#endif
#if RKAIQ_HAVE_MERGE_V11
            memcpy(&pAmergeGrpProcRes->camgroupParmasArray[i]->_amergeConfig->Merge_v11,
                   &pAmergeGrpCtx->ProcRes.Merge_v11, sizeof(MgeProcResV11_t));
#endif
#if RKAIQ_HAVE_MERGE_V12
            memcpy(&pAmergeGrpProcRes->camgroupParmasArray[i]->_amergeConfig->Merge_v12,
                   &pAmergeGrpCtx->ProcRes.Merge_v12, sizeof(MgeProcResV12_t));
#endif
        }

        LOGD_AMERGE("/#####################################Amerge Group Over#####################################/ \n");
    } else {
        LOGD_AMERGE("%s FrameID:%d, It's in Linear Mode, Merge function bypass\n", __FUNCTION__, pAmergeGrpCtx->frameCnt);
    }

    LOG1_AMERGE("%s:Exit!\n", __FUNCTION__);
    return(ret);
}

RkAiqAlgoDescription g_RkIspAlgoDescCamgroupAmerge = {
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
