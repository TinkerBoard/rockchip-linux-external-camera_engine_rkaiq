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

#include "rk_aiq_algo_types_int.h"
#include "rk_aiq_algo_camgroup_types.h"
#include "algos/adrc/rk_aiq_algo_adrc_itf.h"
#include "xcam_log.h"
#include "algos/adrc/rk_aiq_adrc_algo.h"

RKAIQ_BEGIN_DECLARE


static XCamReturn
create_context(RkAiqAlgoContext **context, const AlgoCtxInstanceCfg* cfg)
{
    LOG1_ATMO(" %s:Enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    AlgoCtxInstanceCfgCamGroup* instanc_int = (AlgoCtxInstanceCfgCamGroup*)cfg;
    AdrcContext_t* pAdrcCtx = NULL;

    result = AdrcInit(&pAdrcCtx, (CamCalibDbV2Context_t*)(instanc_int->s_calibv2));

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
    RkAiqAlgoCamGroupPrepare* AdrcCfgParam = (RkAiqAlgoCamGroupPrepare*)params; //come from params in html
    const CamCalibDbV2Context_t* pCalibDb = AdrcCfgParam->s_calibv2;

    if (AdrcCfgParam->gcom.com.u.prepare.working_mode < RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAdrcCtx->FrameNumber = 1;
    else if (AdrcCfgParam->gcom.com.u.prepare.working_mode < RK_AIQ_WORKING_MODE_ISP_HDR3 &&
             AdrcCfgParam->gcom.com.u.prepare.working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2)
        pAdrcCtx->FrameNumber = 2;
    else
        pAdrcCtx->FrameNumber = 3;

    if(!!(params->u.prepare.conf_type & RK_AIQ_ALGO_CONFTYPE_UPDATECALIB )) {
        LOGI_ATMO("%s: Adrc Reload Para!\n", __FUNCTION__);

        if(CHECK_ISP_HW_V21()) {
            CalibDbV2_drc_t* calibv2_adrc_calib =
                (CalibDbV2_drc_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adrc_calib));

            memcpy(&pAdrcCtx->pCalibDB.Drc_v20, calibv2_adrc_calib, sizeof(CalibDbV2_drc_t)); //reload iq paras
        }
        else if(CHECK_ISP_HW_V30()) {
            CalibDbV2_drc_V2_t* calibv2_adrc_calib =
                (CalibDbV2_drc_V2_t*)(CALIBDBV2_GET_MODULE_PTR((void*)pCalibDb, adrc_calib));

            memcpy(&pAdrcCtx->pCalibDB.Drc_v21, calibv2_adrc_calib, sizeof(CalibDbV2_drc_t)); //reload iq paras
        }
    }

    if(/* !params->u.prepare.reconfig*/true) {
        AdrcStop(pAdrcCtx); // stop firstly for re-preapre
        result = AdrcStart(pAdrcCtx);
        if (result != XCAM_RETURN_NO_ERROR) {
            LOGE_ATMO("%s Adrc Start failed: %d", __FUNCTION__, result);
            return(XCAM_RETURN_ERROR_FAILED);
        }
    }

    //update
    DrcNewMalloc(&pAdrcCtx->Config, &pAdrcCtx->pCalibDB);
    AdrcUpdateConfig(pAdrcCtx, &pAdrcCtx->pCalibDB);

    LOG1_ATMO("%s:Exit!\n", __FUNCTION__);
    return result;
}

static XCamReturn
processing(const RkAiqAlgoCom* inparams, RkAiqAlgoResCom* outparams)
{
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;
    bool bypass = false;

    AdrcContext_t* pAdrcCtx = (AdrcContext_t*)inparams->ctx;
    pAdrcCtx->frameCnt = inparams->frame_id;
    RkAiqAlgoCamGroupProcIn* pAdrcGrpParams = (RkAiqAlgoCamGroupProcIn*)inparams;
    RkAiqAlgoCamGroupProcOut* pAdrcGrpProcRes = (RkAiqAlgoCamGroupProcOut*)outparams;

    LOGD_ATMO("%s://////////////////////////////////////ADRC Group Start////////////////////////////////////// \n", __func__);

    //get Sensor Info
    XCamVideoBuffer* xCamAeProcRes = pAdrcGrpParams->camgroupParmasArray[0]->aec._aeProcRes;
    RkAiqAlgoProcResAeInt* pAEProcRes = NULL;
    if (xCamAeProcRes) {
        pAEProcRes = (RkAiqAlgoProcResAeInt*)xCamAeProcRes->map(xCamAeProcRes);
        AdrcGetSensorInfo(pAdrcCtx, pAEProcRes->ae_proc_res_rk);
    }
    else {
        AecProcResult_t AeProcResult;
        memset(&AeProcResult, 0x0, sizeof(AecProcResult_t));
        LOGW_ATMO("%s: Ae Proc result is null!!!\n", __FUNCTION__);
        AdrcGetSensorInfo(pAdrcCtx, AeProcResult);
    }

    //get ae pre res and proc
    XCamVideoBuffer* xCamAePreRes = pAdrcGrpParams->camgroupParmasArray[0]->aec._aePreRes;
    RkAiqAlgoPreResAeInt* pAEPreRes = NULL;
    if (xCamAePreRes) {
        pAEPreRes = (RkAiqAlgoPreResAeInt*)xCamAePreRes->map(xCamAePreRes);
        bypass = AdrcByPassProcessing(pAdrcCtx, pAEPreRes->ae_pre_res_rk);
    }
    else {
        AecPreResult_t AecHdrPreResult;
        memset(&AecHdrPreResult, 0x0, sizeof(AecPreResult_t));
        bypass = AdrcByPassProcessing(pAdrcCtx, AecHdrPreResult);
        bypass = false;
        LOGW_ATMO("%s: ae Pre result is null!!!\n", __FUNCTION__);
    }

    if(!bypass)
        AdrcProcessing(pAdrcCtx);

    pAdrcCtx->PrevData.ApiMode = pAdrcCtx->drcAttr.opMode;
    //output ProcRes
    for(int i = 0; i < pAdrcGrpProcRes->arraySize; i++) {
        pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->update = false ;
        pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->CompressMode = pAdrcCtx->AdrcProcRes.CompressMode;
        pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->LongFrameMode = pAdrcCtx->AdrcProcRes.LongFrameMode;
        pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->isHdrGlobalTmo = pAdrcCtx->AdrcProcRes.isHdrGlobalTmo;
        pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->bTmoEn = pAdrcCtx->AdrcProcRes.bTmoEn;
        pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->isLinearTmo = pAdrcCtx->AdrcProcRes.isLinearTmo;
        memcpy(&pAdrcGrpProcRes->camgroupParmasArray[i]->_adrcConfig->DrcProcRes, &pAdrcCtx->AdrcProcRes.DrcProcRes, sizeof(DrcProcRes_t));
    }

    LOGD_ATMO("%s://////////////////////////////////////ADRC Group Over////////////////////////////////////// \n", __func__);

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
