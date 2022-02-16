/*
 * rk_aiq_algo_camgroup_adrc_itf.c
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
#include "algos/adrc/rk_aiq_algo_adrc_itf.h"
#include "xcam_log.h"
#if RKAIQ_HAVE_DRC_V10
#include "adrc/rk_aiq_adrc_algo_v10.h"
#endif
#if RKAIQ_HAVE_DRC_V11
#include "adrc/rk_aiq_adrc_algo_v11.h"
#endif
#if RKAIQ_HAVE_DRC_V12
#include "adrc/rk_aiq_adrc_algo_v12.h"
#endif

RKAIQ_BEGIN_DECLARE

static XCamReturn
create_context(RkAiqAlgoContext **context, const AlgoCtxInstanceCfg* cfg)
{
    LOG1_ATMO(" %s:Enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    AlgoCtxInstanceCfgCamGroup* instanc_int = (AlgoCtxInstanceCfgCamGroup*)cfg;
    AdrcContext_t* pAdrcGrpCtx = NULL;

    result = AdrcInit(&pAdrcGrpCtx, (CamCalibDbV2Context_t*)(instanc_int->s_calibv2));

    if (result != XCAM_RETURN_NO_ERROR) {
        LOGE_ATMO("%s Adrc Init failed: %d", __FUNCTION__, result);
        return(XCAM_RETURN_ERROR_FAILED);
    }
    *context = (RkAiqAlgoContext *)(pAdrcGrpCtx);

    LOG1_ATMO(" %s:Exit!\n", __FUNCTION__);
    return result;
}

static XCamReturn
destroy_context(RkAiqAlgoContext *context)
{
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    if(context != NULL) {

        AdrcContext_t* pAdrcGrpCtx = (AdrcContext_t*)context;
        result = AdrcRelease(pAdrcGrpCtx);
        if (result != XCAM_RETURN_NO_ERROR) {
            LOGE_ATMO("%s Adrc Release failed: %d", __FUNCTION__, result);
            return(XCAM_RETURN_ERROR_FAILED);
        }
        context = NULL;
    }

    LOG1_ATMO("%s:Exit!\n", __FUNCTION__);
    return result;
}

static XCamReturn
prepare(RkAiqAlgoCom* params)
{
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    AdrcContext_t* pAdrcGrpCtx = (AdrcContext_t*)params->ctx;
    RkAiqAlgoCamGroupPrepare* AdrcCfgParam = (RkAiqAlgoCamGroupPrepare*)params; //come from params in html
    const CamCalibDbV2Context_t* pCalibDb = AdrcCfgParam->s_calibv2;

    if (AdrcCfgParam->gcom.com.u.prepare.working_mode < RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAdrcGrpCtx->FrameNumber = LINEAR_NUM;
    else if (AdrcCfgParam->gcom.com.u.prepare.working_mode < RK_AIQ_WORKING_MODE_ISP_HDR3 &&
             AdrcCfgParam->gcom.com.u.prepare.working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAdrcGrpCtx->FrameNumber = HDR_2X_NUM;
    else
        pAdrcGrpCtx->FrameNumber = HDR_3X_NUM;

    if(!!(params->u.prepare.conf_type & RK_AIQ_ALGO_CONFTYPE_UPDATECALIB )) {
        LOGI_ATMO("%s: Adrc Reload Para!\n", __FUNCTION__);
#if RKAIQ_HAVE_DRC_V10
        CalibDbV2_drc_V10_t* calibv2_adrc_calib =
            (CalibDbV2_drc_V10_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adrc_calib));
        memcpy(&pAdrcGrpCtx->CalibDBV10, calibv2_adrc_calib,
               sizeof(CalibDbV2_drc_V10_t));  // reload iq paras
        memcpy(&pAdrcGrpCtx->drcAttrV10.stAuto, calibv2_adrc_calib,
               sizeof(CalibDbV2_drc_V10_t));  // reload stAuto
#endif
#if RKAIQ_HAVE_DRC_V11
        CalibDbV2_drc_V11_t* calibv2_adrc_calib =
            (CalibDbV2_drc_V11_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adrc_calib));
        memcpy(&pAdrcGrpCtx->CalibDBV11, calibv2_adrc_calib,
               sizeof(CalibDbV2_drc_V11_t));  // reload iq paras
        memcpy(&pAdrcGrpCtx->drcAttrV11.stAuto, calibv2_adrc_calib,
               sizeof(CalibDbV2_drc_V11_t));  // reload stAuto
#endif
#if RKAIQ_HAVE_DRC_V12
        CalibDbV2_drc_V12_t* calibv2_adrc_calib =
            (CalibDbV2_drc_V12_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adrc_calib));
        memcpy(&pAdrcGrpCtx->CalibDBV12, calibv2_adrc_calib,
               sizeof(CalibDbV2_drc_V12_t));  // reload iq paras
        memcpy(&pAdrcGrpCtx->drcAttrV12.stAuto.DrcTuningPara, &calibv2_adrc_calib->DrcTuningPara,
               sizeof(CalibDbV2_Adrc_V12_t));  // reload stAuto
#endif
    }

    if(/* !params->u.prepare.reconfig*/true) {
        AdrcStop(pAdrcGrpCtx); // stop firstly for re-preapre
        result = AdrcStart(pAdrcGrpCtx);
        if (result != XCAM_RETURN_NO_ERROR) {
            LOGE_ATMO("%s Adrc Start failed: %d", __FUNCTION__, result);
            return(XCAM_RETURN_ERROR_FAILED);
        }
    }

    LOG1_ATMO("%s:Exit!\n", __FUNCTION__);
    return result;
}

static XCamReturn
processing(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;
    bool bypass = false;

    AdrcContext_t* pAdrcGrpCtx = (AdrcContext_t*)inparams->ctx;
    pAdrcGrpCtx->frameCnt = inparams->frame_id > 2 ? (inparams->frame_id - 2) : 0;
    RkAiqAlgoCamGroupProcIn* pAdrcGrpParams = (RkAiqAlgoCamGroupProcIn*)inparams;
    RkAiqAlgoCamGroupProcOut* pAdrcGrpProcRes = (RkAiqAlgoCamGroupProcOut*)outparams;

    //update config
    bool Enable = DrcEnableSetting(pAdrcGrpCtx);

    if(Enable) {
        LOGD_ATMO("%s://////////////////////////////////////ADRC Group Start////////////////////////////////////// \n", __func__);

        //get Sensor Info
        XCamVideoBuffer* xCamAeProcRes = pAdrcGrpParams->camgroupParmasArray[0]->aec._aeProcRes;
        RkAiqAlgoProcResAe* pAEProcRes = NULL;
        if (xCamAeProcRes) {
            pAEProcRes = (RkAiqAlgoProcResAe*)xCamAeProcRes->map(xCamAeProcRes);
            pAdrcGrpCtx->AeResult.LongFrmMode = pAEProcRes->ae_proc_res_rk.LongFrmMode;
        }
        else {
            pAdrcGrpCtx->AeResult.LongFrmMode = false;
            LOGW_ATMO("%s: Ae Proc result is null!!!\n", __FUNCTION__);
        }

        //get ae pre res and proc
        XCamVideoBuffer* xCamAePreRes = pAdrcGrpParams->camgroupParmasArray[0]->aec._aePreRes;
        RkAiqAlgoPreResAe* pAEPreRes = NULL;
        if (xCamAePreRes) {
            pAEPreRes = (RkAiqAlgoPreResAe*)xCamAePreRes->map(xCamAePreRes);
            bypass = AdrcByPassProcessing(pAdrcGrpCtx, pAEPreRes->ae_pre_res_rk);
        }
        else {
            AecPreResult_t AecHdrPreResult;
            memset(&AecHdrPreResult, 0x0, sizeof(AecPreResult_t));
            bypass = AdrcByPassProcessing(pAdrcGrpCtx, AecHdrPreResult);
            bypass = false;
            LOGW_ATMO("%s: ae Pre result is null!!!\n", __FUNCTION__);
        }

        // get eff expo
        if(pAdrcGrpCtx->FrameNumber == LINEAR_NUM) {
            pAdrcGrpCtx->AeResult.Next.SExpo =
                pAdrcGrpParams->camgroupParmasArray[0]
                    ->aec._effAecExpInfo.LinearExp.exp_real_params.analog_gain *
                pAdrcGrpParams->camgroupParmasArray[0]
                    ->aec._effAecExpInfo.LinearExp.exp_real_params.digital_gain *
                pAdrcGrpParams->camgroupParmasArray[0]
                    ->aec._effAecExpInfo.LinearExp.exp_real_params.integration_time;
            pAdrcGrpCtx->AeResult.Next.MExpo = pAdrcGrpCtx->AeResult.Next.SExpo;
            pAdrcGrpCtx->AeResult.Next.LExpo = pAdrcGrpCtx->AeResult.Next.SExpo;
            pAdrcGrpCtx->AeResult.Next.ISO =
                pAdrcGrpParams->camgroupParmasArray[0]
                    ->aec._effAecExpInfo.LinearExp.exp_real_params.analog_gain *
                pAdrcGrpParams->camgroupParmasArray[0]
                    ->aec._effAecExpInfo.LinearExp.exp_real_params.digital_gain *
                ISOMIN;
        }
        else if(pAdrcGrpCtx->FrameNumber == HDR_2X_NUM) {
            pAdrcGrpCtx->AeResult.Next.SExpo = pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[0]
                                                   .exp_real_params.analog_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[0]
                                                   .exp_real_params.digital_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[0]
                                                   .exp_real_params.integration_time;
            pAdrcGrpCtx->AeResult.Next.MExpo = pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[1]
                                                   .exp_real_params.analog_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[1]
                                                   .exp_real_params.digital_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[1]
                                                   .exp_real_params.integration_time;
            pAdrcGrpCtx->AeResult.Next.LExpo = pAdrcGrpCtx->AeResult.Next.MExpo;
            pAdrcGrpCtx->AeResult.Next.ISO   = pAdrcGrpParams->camgroupParmasArray[0]
                                                 ->aec._effAecExpInfo.HdrExp[0]
                                                 .exp_real_params.analog_gain *
                                             pAdrcGrpParams->camgroupParmasArray[0]
                                                 ->aec._effAecExpInfo.HdrExp[0]
                                                 .exp_real_params.digital_gain *
                                             ISOMIN;
        }
        else if(pAdrcGrpCtx->FrameNumber == HDR_3X_NUM) {
            pAdrcGrpCtx->AeResult.Next.SExpo = pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[0]
                                                   .exp_real_params.analog_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[0]
                                                   .exp_real_params.digital_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[0]
                                                   .exp_real_params.integration_time;
            pAdrcGrpCtx->AeResult.Next.MExpo = pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[1]
                                                   .exp_real_params.analog_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[1]
                                                   .exp_real_params.digital_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[1]
                                                   .exp_real_params.integration_time;
            pAdrcGrpCtx->AeResult.Next.LExpo = pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[2]
                                                   .exp_real_params.analog_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[2]
                                                   .exp_real_params.digital_gain *
                                               pAdrcGrpParams->camgroupParmasArray[0]
                                                   ->aec._effAecExpInfo.HdrExp[2]
                                                   .exp_real_params.integration_time;
            pAdrcGrpCtx->AeResult.Next.ISO = pAdrcGrpParams->camgroupParmasArray[0]
                                                 ->aec._effAecExpInfo.HdrExp[0]
                                                 .exp_real_params.analog_gain *
                                             pAdrcGrpParams->camgroupParmasArray[0]
                                                 ->aec._effAecExpInfo.HdrExp[0]
                                                 .exp_real_params.digital_gain *
                                             ISOMIN;
        }
        LOGV_ATMO("%s: nextFrame: sexp: %f-%f, mexp: %f-%f, lexp: %f-%f\n", __FUNCTION__,
                  pAdrcGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.analog_gain,
                  pAdrcGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[0].exp_real_params.integration_time,
                  pAdrcGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.analog_gain,
                  pAdrcGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[1].exp_real_params.integration_time,
                  pAdrcGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[2].exp_real_params.analog_gain,
                  pAdrcGrpParams->camgroupParmasArray[0]->aec._effAecExpInfo.HdrExp[2].exp_real_params.integration_time);
        if (pAdrcGrpCtx->AeResult.Next.SExpo > 0) {
            pAdrcGrpCtx->AeResult.Next.L2S_Ratio =
                pAdrcGrpCtx->AeResult.Next.LExpo / pAdrcGrpCtx->AeResult.Next.SExpo;
            pAdrcGrpCtx->AeResult.Next.M2S_Ratio =
                pAdrcGrpCtx->AeResult.Next.MExpo / pAdrcGrpCtx->AeResult.Next.SExpo;
        } else
            LOGE_ATMO("%s: Next frame for drc expo sync is ERROR!!!\n", __FUNCTION__);
        if (pAdrcGrpCtx->AeResult.Next.MExpo > 0)
            pAdrcGrpCtx->AeResult.Next.L2M_Ratio =
                pAdrcGrpCtx->AeResult.Next.LExpo / pAdrcGrpCtx->AeResult.Next.MExpo;
        else
            LOGE_ATMO("%s: Next Midlle frame for drc expo sync is ERROR!!!\n", __FUNCTION__);
        //clip for long frame mode
        if (pAdrcGrpCtx->AeResult.LongFrmMode) {
            pAdrcGrpCtx->AeResult.Next.L2S_Ratio = 1.0;
            pAdrcGrpCtx->AeResult.Next.M2S_Ratio = 1.0;
            pAdrcGrpCtx->AeResult.Next.L2M_Ratio = 1.0;
        }

        // get tuning paras
        if (!bypass) AdrcTuningParaProcessing(pAdrcGrpCtx);

        // expo para process
        if (pAdrcGrpCtx->AeResult.Next.L2S_Ratio >= 1 && pAdrcGrpCtx->AeResult.Next.L2M_Ratio >= 1)
            AdrcExpoParaProcessing(pAdrcGrpCtx);
        else
            LOGE_ATMO("%s: AE ratio for drc expo sync is under one!!!\n", __FUNCTION__);

#if RKAIQ_HAVE_DRC_V10
        pAdrcGrpCtx->PrevData.ApiMode = pAdrcGrpCtx->drcAttrV10.opMode;
#endif
#if RKAIQ_HAVE_DRC_V11
        pAdrcGrpCtx->PrevData.ApiMode = pAdrcGrpCtx->drcAttrV11.opMode;
#endif
        //output ProcRes
        for(int i = 0; i < pAdrcGrpProcRes->arraySize; i++) {
            pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->update = !bypass ;//not use in isp3xparams for now
            pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->CompressMode = pAdrcGrpCtx->AdrcProcRes.CompressMode;
            pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->LongFrameMode = pAdrcGrpCtx->AdrcProcRes.LongFrameMode;
            pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->isHdrGlobalTmo = pAdrcGrpCtx->AdrcProcRes.isHdrGlobalTmo;
            pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->bTmoEn = pAdrcGrpCtx->AdrcProcRes.bTmoEn;
            pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->isLinearTmo = pAdrcGrpCtx->AdrcProcRes.isLinearTmo;
            memcpy(&pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->DrcProcRes, &pAdrcGrpCtx->AdrcProcRes.DrcProcRes, sizeof(DrcProcRes_t));
        }

        LOGD_ATMO("%s://////////////////////////////////////ADRC Group Over////////////////////////////////////// \n", __func__);
    } else {
        LOGD_ATMO("%s: Group Drc Enable if OFF, Bypass Drc !!! \n", __func__);
    }

    LOG1_ATMO("%s:Exit!\n", __FUNCTION__);
    return XCAM_RETURN_NO_ERROR;
}

RkAiqAlgoDescription g_RkIspAlgoDescCamgroupAdrc = {
    .common = {
        .version = RKISP_ALGO_ADRC_VERSION,
        .vendor  = RKISP_ALGO_ADRC_VENDOR,
        .description = RKISP_ALGO_ADRC_DESCRIPTION,
        .type    = RK_AIQ_ALGO_TYPE_ADRC,
        .id      = 0,
        .create_context  = create_context,
        .destroy_context = destroy_context,
    },
    .prepare = prepare,
    .pre_process = NULL,
    .processing = processing,
    .post_process = NULL,
};

RKAIQ_END_DECLARE
