/*
 * rk_aiq_algo_adrc_itf.c
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

#include "adrc/rk_aiq_algo_adrc_itf.h"
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
#include "adrc/rk_aiq_types_adrc_algo_prvt.h"

RKAIQ_BEGIN_DECLARE


static XCamReturn
create_context(RkAiqAlgoContext **context, const AlgoCtxInstanceCfg* cfg)
{
    LOG1_ATMO(" %s:Enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;
    AdrcContext_t* pAdrcCtx = NULL;

    result = AdrcInit(&pAdrcCtx, (CamCalibDbV2Context_t*)(cfg->calibv2));

    if (result != XCAM_RETURN_NO_ERROR) {
        LOGE_ATMO("%s Adrc Init failed: %d", __FUNCTION__, result);
        return(XCAM_RETURN_ERROR_FAILED);
    }
    *context = (RkAiqAlgoContext *)(pAdrcCtx);

    LOG1_ATMO(" %s:Exit!\n", __FUNCTION__);
    return result;
}

static XCamReturn
destroy_context(RkAiqAlgoContext *context)
{
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    if(context != NULL) {

        AdrcContext_t* pAdrcCtx = (AdrcContext_t*)context;
        result = AdrcRelease(pAdrcCtx);
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

    AdrcContext_t* pAdrcCtx = (AdrcContext_t*)params->ctx;
    RkAiqAlgoConfigAdrc* AdrcCfgParam = (RkAiqAlgoConfigAdrc*)params; //come from params in html
    const CamCalibDbV2Context_t* pCalibDb = AdrcCfgParam->com.u.prepare.calibv2;

    if (AdrcCfgParam->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAdrcCtx->FrameNumber = LINEAR_NUM;
    else if (AdrcCfgParam->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR3 &&
             AdrcCfgParam->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAdrcCtx->FrameNumber = HDR_2X_NUM;
    else
        pAdrcCtx->FrameNumber = HDR_3X_NUM;

    if(!!(params->u.prepare.conf_type & RK_AIQ_ALGO_CONFTYPE_UPDATECALIB )) {
        LOGI_ATMO("%s: Adrc Reload Para!\n", __FUNCTION__);
#if RKAIQ_HAVE_DRC_V10
        CalibDbV2_drc_V10_t* calibv2_adrc_calib =
            (CalibDbV2_drc_V10_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adrc_calib));
        memcpy(&pAdrcCtx->drcAttrV10.stAuto, calibv2_adrc_calib,
               sizeof(CalibDbV2_drc_V10_t));  // reload stAuto
#endif
#if RKAIQ_HAVE_DRC_V11
        CalibDbV2_drc_V11_t* calibv2_adrc_calib =
            (CalibDbV2_drc_V11_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adrc_calib));
        memcpy(&pAdrcCtx->drcAttrV11.stAuto, calibv2_adrc_calib,
               sizeof(CalibDbV2_drc_V11_t));  // reload stAuto
#endif
#if RKAIQ_HAVE_DRC_V12
        CalibDbV2_drc_V12_t* calibv2_adrc_calib =
            (CalibDbV2_drc_V12_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adrc_calib));
        memcpy(&pAdrcCtx->drcAttrV12.stAuto, calibv2_adrc_calib,
               sizeof(CalibDbV2_drc_V12_t));  // reload stAuto
#endif
    }

    if(/* !params->u.prepare.reconfig*/true) {
        AdrcStop(pAdrcCtx); // stop firstly for re-preapre
        result = AdrcStart(pAdrcCtx);
        if (result != XCAM_RETURN_NO_ERROR) {
            LOGE_ATMO("%s Adrc Start failed: %d", __FUNCTION__, result);
            return(XCAM_RETURN_ERROR_FAILED);
        }
    }

    LOG1_ATMO("%s:Exit!\n", __FUNCTION__);
    return result;
}

static XCamReturn
pre_process(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    RESULT ret = XCAM_RETURN_NO_ERROR;


    LOG1_ATMO("%s:Exit!\n", __FUNCTION__);
    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
processing(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;
    bool bypass = false;
    AdrcContext_t* pAdrcCtx = (AdrcContext_t*)inparams->ctx;
    RkAiqAlgoProcAdrc* pAdrcParams = (RkAiqAlgoProcAdrc*)inparams;
    RkAiqAlgoProcResAdrc* pAdrcProcRes = (RkAiqAlgoProcResAdrc*)outparams;
    pAdrcCtx->frameCnt                 = inparams->frame_id > 2 ? (inparams->frame_id - 2) : 0;

#if RKAIQ_HAVE_DRC_V12
    memcpy(&pAdrcCtx->ablcV32_proc_res, &pAdrcParams->ablcV32_proc_res, sizeof(AblcProc_V32_t));
    if (pAdrcCtx->ablcV32_proc_res.blc_ob_enable &&
        pAdrcCtx->ablcV32_proc_res.isp_ob_predgain < 1.0f) {
        LOGE_ATMO("%s: ob_enable ON , and ob_predgain[%f]<1.0f!!!\n", __FUNCTION__,
                  pAdrcCtx->ablcV32_proc_res.isp_ob_predgain);
        pAdrcCtx->ablcV32_proc_res.isp_ob_predgain = 1.0f;
    }
#endif

    //update config
    bool Enable = DrcEnableSetting(pAdrcCtx);

    if(Enable) {
        LOGD_ATMO("%s://////////////////////////////////////ADRC Start////////////////////////////////////// \n", __func__);

        //get Sensor Info
        XCamVideoBuffer* xCamAeProcRes = pAdrcParams->com.u.proc.res_comb->ae_proc_res;
        RkAiqAlgoProcResAe* pAEProcRes = NULL;
        if (xCamAeProcRes) {
            pAEProcRes = (RkAiqAlgoProcResAe*)xCamAeProcRes->map(xCamAeProcRes);
            pAdrcCtx->AeResult.LongFrmMode = pAEProcRes->ae_proc_res_rk.LongFrmMode;
        }
        else {
            if (!(pAdrcCtx->frameCnt))
                return XCAM_RETURN_NO_ERROR;
            else {
                pAdrcCtx->AeResult.LongFrmMode = false;
                LOGW_ATMO("%s: Ae Proc result is null!!!\n", __FUNCTION__);
            }
        }

        //get ae pre res and proc
        XCamVideoBuffer* xCamAePreRes = pAdrcParams->com.u.proc.res_comb->ae_pre_res;
        RkAiqAlgoPreResAe* pAEPreRes = NULL;
        if (xCamAePreRes) {
            pAEPreRes = (RkAiqAlgoPreResAe*)xCamAePreRes->map(xCamAePreRes);
            bypass = AdrcByPassProcessing(pAdrcCtx, pAEPreRes->ae_pre_res_rk);
        }
        else {
            if (!(pAdrcCtx->frameCnt))
                return XCAM_RETURN_NO_ERROR;
            else {
                AecPreResult_t AecHdrPreResult;
                memset(&AecHdrPreResult, 0x0, sizeof(AecPreResult_t));
                bypass = AdrcByPassProcessing(pAdrcCtx, AecHdrPreResult);
                bypass = false;
                LOGW_ATMO("%s: ae Pre result is null!!!\n", __FUNCTION__);
            }
        }

        // get eff expo data
        if(pAdrcCtx->FrameNumber == LINEAR_NUM) {
            pAdrcCtx->AeResult.Next.SExpo =
                pAdrcParams->com.u.proc.nxtExp->LinearExp.exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.nxtExp->LinearExp.exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.nxtExp->LinearExp.exp_real_params.integration_time;
            pAdrcCtx->AeResult.Next.MExpo = pAdrcCtx->AeResult.Next.SExpo;
            pAdrcCtx->AeResult.Next.LExpo = pAdrcCtx->AeResult.Next.SExpo;
            pAdrcCtx->AeResult.Next.ISO =
                pAdrcParams->com.u.proc.nxtExp->LinearExp.exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.nxtExp->LinearExp.exp_real_params.digital_gain * ISOMIN;

            pAdrcCtx->AeResult.Curr.SExpo =
                pAdrcParams->com.u.proc.curExp->LinearExp.exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.curExp->LinearExp.exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.curExp->LinearExp.exp_real_params.integration_time;
            pAdrcCtx->AeResult.Curr.MExpo = pAdrcCtx->AeResult.Curr.SExpo;
            pAdrcCtx->AeResult.Curr.LExpo = pAdrcCtx->AeResult.Curr.SExpo;
            pAdrcCtx->AeResult.Curr.ISO =
                pAdrcParams->com.u.proc.curExp->LinearExp.exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.curExp->LinearExp.exp_real_params.digital_gain * ISOMIN;
        }
        else if(pAdrcCtx->FrameNumber == HDR_2X_NUM) {
            pAdrcCtx->AeResult.Next.SExpo =
                pAdrcParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Next.MExpo =
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Next.LExpo = pAdrcCtx->AeResult.Next.MExpo;
            pAdrcCtx->AeResult.Next.ISO =
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain * ISOMIN;

            pAdrcCtx->AeResult.Curr.SExpo =
                pAdrcParams->com.u.proc.curExp->HdrExp[0].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[0].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[0].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Curr.MExpo =
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Curr.LExpo = pAdrcCtx->AeResult.Curr.MExpo;
            pAdrcCtx->AeResult.Curr.ISO =
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.digital_gain * ISOMIN;
        }
        else if(pAdrcCtx->FrameNumber == HDR_3X_NUM) {
            pAdrcCtx->AeResult.Next.SExpo =
                pAdrcParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Next.MExpo =
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Next.LExpo =
                pAdrcParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Next.ISO =
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain * ISOMIN;

            pAdrcCtx->AeResult.Curr.SExpo =
                pAdrcParams->com.u.proc.curExp->HdrExp[0].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[0].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[0].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Curr.MExpo =
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Curr.LExpo =
                pAdrcParams->com.u.proc.curExp->HdrExp[2].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[2].exp_real_params.digital_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[2].exp_real_params.integration_time;
            pAdrcCtx->AeResult.Curr.ISO =
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.analog_gain *
                pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.digital_gain * ISOMIN;
        }
        if (pAdrcCtx->FrameNumber == HDR_2X_NUM || pAdrcCtx->FrameNumber == HDR_2X_NUM) {
            LOGV_ATMO("%s: nextFrame: sexp: %f-%f, mexp: %f-%f, lexp: %f-%f\n", __FUNCTION__,
                      pAdrcParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.analog_gain,
                      pAdrcParams->com.u.proc.nxtExp->HdrExp[0].exp_real_params.integration_time,
                      pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain,
                      pAdrcParams->com.u.proc.nxtExp->HdrExp[1].exp_real_params.integration_time,
                      pAdrcParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.analog_gain,
                      pAdrcParams->com.u.proc.nxtExp->HdrExp[2].exp_real_params.integration_time);
            LOGV_ATMO("%s: CurrFrame: sexp: %f-%f, mexp: %f-%f, lexp: %f-%f\n", __FUNCTION__,
                      pAdrcParams->com.u.proc.curExp->HdrExp[0].exp_real_params.analog_gain,
                      pAdrcParams->com.u.proc.curExp->HdrExp[0].exp_real_params.integration_time,
                      pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.analog_gain,
                      pAdrcParams->com.u.proc.curExp->HdrExp[1].exp_real_params.integration_time,
                      pAdrcParams->com.u.proc.curExp->HdrExp[2].exp_real_params.analog_gain,
                      pAdrcParams->com.u.proc.curExp->HdrExp[2].exp_real_params.integration_time);
        } else if (pAdrcCtx->FrameNumber == LINEAR_NUM) {
            LOGV_ATMO("%s: nextFrame: exp: %f-%f CurrFrame: exp: %f-%f\n", __FUNCTION__,
                      pAdrcParams->com.u.proc.nxtExp->LinearExp.exp_real_params.analog_gain,
                      pAdrcParams->com.u.proc.nxtExp->LinearExp.exp_real_params.integration_time,
                      pAdrcParams->com.u.proc.curExp->LinearExp.exp_real_params.analog_gain,
                      pAdrcParams->com.u.proc.curExp->LinearExp.exp_real_params.integration_time);
        }
        if (pAdrcCtx->AeResult.Next.SExpo > 0) {
            pAdrcCtx->AeResult.Next.L2S_Ratio =
                pAdrcCtx->AeResult.Next.LExpo / pAdrcCtx->AeResult.Next.SExpo;
            pAdrcCtx->AeResult.Next.M2S_Ratio =
                pAdrcCtx->AeResult.Next.MExpo / pAdrcCtx->AeResult.Next.SExpo;
        } else
            LOGE_ATMO("%s: Next Short frame for drc expo sync is %f!!!\n", __FUNCTION__,
                      pAdrcCtx->AeResult.Next.SExpo);
        if (pAdrcCtx->AeResult.Next.MExpo > 0)
            pAdrcCtx->AeResult.Next.L2M_Ratio =
                pAdrcCtx->AeResult.Next.LExpo / pAdrcCtx->AeResult.Next.MExpo;
        else
            LOGE_ATMO("%s: Next Midlle frame for drc expo sync is %f!!!\n", __FUNCTION__,
                      pAdrcCtx->AeResult.Next.MExpo);
        if (pAdrcCtx->AeResult.Curr.SExpo > 0) {
            pAdrcCtx->AeResult.Curr.L2S_Ratio =
                pAdrcCtx->AeResult.Curr.LExpo / pAdrcCtx->AeResult.Curr.SExpo;
            pAdrcCtx->AeResult.Curr.M2S_Ratio =
                pAdrcCtx->AeResult.Curr.MExpo / pAdrcCtx->AeResult.Curr.SExpo;
        } else
            LOGE_ATMO("%s: Curr Short frame for drc expo sync is %f!!!\n", __FUNCTION__,
                      pAdrcCtx->AeResult.Curr.SExpo);
        if (pAdrcCtx->AeResult.Curr.MExpo > 0)
            pAdrcCtx->AeResult.Curr.L2M_Ratio =
                pAdrcCtx->AeResult.Curr.LExpo / pAdrcCtx->AeResult.Curr.MExpo;
        else
            LOGE_ATMO("%s: Curr Midlle frame for drc expo sync is %f!!!\n", __FUNCTION__,
                      pAdrcCtx->AeResult.Curr.MExpo);
        //clip for long frame mode
        if (pAdrcCtx->AeResult.LongFrmMode) {
            pAdrcCtx->AeResult.Next.L2S_Ratio = 1.0;
            pAdrcCtx->AeResult.Next.M2S_Ratio = 1.0;
            pAdrcCtx->AeResult.Next.L2M_Ratio = 1.0;
        }

        // get tuning paras
        if (!bypass) AdrcTuningParaProcessing(pAdrcCtx);

        // get expo related paras
        if (pAdrcCtx->AeResult.Next.L2S_Ratio >= 1 && pAdrcCtx->AeResult.Next.L2M_Ratio >= 1)
            AdrcExpoParaProcessing(pAdrcCtx);
        else
            LOGE_ATMO("%s: AE ratio for drc expo sync is under one!!!\n", __FUNCTION__);

#if RKAIQ_HAVE_DRC_V10
        pAdrcCtx->PrevData.ApiMode = pAdrcCtx->drcAttrV10.opMode;
#endif
#if RKAIQ_HAVE_DRC_V11
        pAdrcCtx->PrevData.ApiMode = pAdrcCtx->drcAttrV11.opMode;
#endif
        LOGD_ATMO("%s://////////////////////////////////////ADRC Over////////////////////////////////////// \n", __func__);
    } else {
        LOGD_ATMO("%s: Drc Enable if OFF, Bypass Drc !!! \n", __func__);
    }

    // output ProcRes
    pAdrcProcRes->AdrcProcRes.update = !bypass;  // not use in isp3xparams for now
    pAdrcProcRes->AdrcProcRes.CompressMode   = pAdrcCtx->AdrcProcRes.CompressMode;
    pAdrcProcRes->AdrcProcRes.LongFrameMode  = pAdrcCtx->AdrcProcRes.LongFrameMode;
    pAdrcProcRes->AdrcProcRes.isHdrGlobalTmo = pAdrcCtx->AdrcProcRes.isHdrGlobalTmo;
    pAdrcProcRes->AdrcProcRes.bTmoEn         = Enable;
    pAdrcProcRes->AdrcProcRes.isLinearTmo    = pAdrcCtx->AdrcProcRes.isLinearTmo;
    memcpy(&pAdrcProcRes->AdrcProcRes.DrcProcRes, &pAdrcCtx->AdrcProcRes.DrcProcRes,
           sizeof(DrcProcRes_t));

    LOG1_ATMO("%s:Exit!\n", __FUNCTION__);
    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
post_process(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    LOG1_ATMO("%s:Exit!\n", __FUNCTION__);
    return XCAM_RETURN_NO_ERROR;
}

RkAiqAlgoDescription g_RkIspAlgoDescAdrc = {
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
