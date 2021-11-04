/*
 * RkAiqCamGroupManager.cpp
 *
 *  Copyright (c) 2021 Rockchip Corporation
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

#include "RkAiqCamGroupManager.h"
#include "RkAiqManager.h"
#include "aiq_core/RkAiqCore.h"
#include "algos_camgroup/ae/rk_aiq_algo_camgroup_ae_itf.h"
#include "algos_camgroup/awb/rk_aiq_algo_camgroup_awb_itf.h"
#include "algos_camgroup/misc/rk_aiq_algo_camgroup_misc_itf.h"
#include "algos_camgroup/aynr/rk_aiq_algo_camgroup_aynr_itf.h"
#include "algos_camgroup/acnr/rk_aiq_algo_camgroup_acnr_itf.h"
#include "algos_camgroup/atnr/rk_aiq_algo_camgroup_atnr_itf.h"
#include "algos_camgroup/abayernr/rk_aiq_algo_camgroup_abayernr_itf.h"
#include "algos_camgroup/again/rk_aiq_algo_camgroup_again_itf.h"
#include "algos_camgroup/asharp/rk_aiq_algo_camgroup_asharp_itf.h"




#include "smart_buffer_priv.h"

namespace RkCam {

const static struct RkAiqAlgoDesCommExt g_camgroup_algos[] = {
    { &g_RkIspAlgoDescCamgroupAe.common, RK_AIQ_CORE_ANALYZE_AE, 0, 1, 0},
    { &g_RkIspAlgoDescCamgroupAwb.common, RK_AIQ_CORE_ANALYZE_AWB, 1, 1, 0},
    { &g_RkIspAlgoDescCamgroupAlsc.common, RK_AIQ_CORE_ANALYZE_AWB, 0, 0, 0},
    { &g_RkIspAlgoDescCamgroupAccm.common, RK_AIQ_CORE_ANALYZE_AWB, 0, 0, 0},
    { &g_RkIspAlgoDescCamgroupA3dlut.common, RK_AIQ_CORE_ANALYZE_AWB, 0, 0, 0},
    /* dpcc group algo is not mandatory now */
    //{ &g_RkIspAlgoDescCamgroupAdpcc.common, RK_AIQ_CORE_ANALYZE_AWB, 0, 0, 0},
    { & g_RkIspAlgoDescCamgroupAdhaz.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 1, 0},
    /* gamma group algo is not mandatory now */
    //{ &g_RkIspAlgoDescamgroupAgamma.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, 0 },
    { & g_RkIspAlgoDescCamgroupAdrc.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 1, 0},
    //{ & g_RkIspAlgoDescCamgroupAmerge.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, 0},
    { &g_RkIspAlgoDescCamgroupAynr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, 0},
    { &g_RkIspAlgoDescCamgroupAcnr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, 0},
#if defined(ISP_HW_V30)
    { &g_RkIspAlgoDescCamgroupAbayertnr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, 0},
#endif
    { &g_RkIspAlgoDescCamgroupAbayernr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, 0},
    { &g_RkIspAlgoDescCamgroupAsharp.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, 0},
#if defined(ISP_HW_V30)
    { &g_RkIspAlgoDescCamgroupAgain.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, 0},
#endif
    { &g_RkIspAlgoDescCamgroupAblc.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, 0},
    { NULL, RK_AIQ_CORE_ANALYZE_ALL, 0, 0 },
};

bool
RkAiqCamGroupReprocTh::loop ()
{
    const static int32_t timeout = -1;
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<rk_aiq_groupcam_result_wrapper_t> camGroupRes_wrapper = mMsgQueue.pop (timeout);

    if (!camGroupRes_wrapper.ptr()) {
        return true;
    }

    rk_aiq_groupcam_result_t* camGroupRes = camGroupRes_wrapper->_gc_result;
    if (camGroupRes->_ready) {
        ret = mCamGroupManager->reProcess(camGroupRes);
        if (ret) {
            LOGW_CAMGROUP("reprocess error, ignore!");
        }

        mCamGroupManager->relayToHwi(camGroupRes);

        // delete the processed result
        mCamGroupManager->clearGroupCamResult(camGroupRes->_frameId);
    }

    return true;
}

RkAiqCamGroupManager::RkAiqCamGroupManager()
{
    ENTER_CAMGROUP_FUNCTION();
    mCamGroupReprocTh = new RkAiqCamGroupReprocTh(this);
    mRequiredMsgsMask = (1 << XCAM_MESSAGE_AWB_STATS_OK) | (1 << XCAM_MESSAGE_AWB_PROC_RES_OK) | (1 << XCAM_MESSAGE_SOF_INFO_OK) |
                        (1 << XCAM_MESSAGE_AEC_STATS_OK) | (1 << XCAM_MESSAGE_AE_PRE_RES_OK) | (1 << XCAM_MESSAGE_AE_PROC_RES_OK);

    mGroupAlgosDesArray = g_camgroup_algos;
    mState = CAMGROUP_MANAGER_INVALID;
    memset(mGroupAlgoCtxArray, 0, sizeof(mGroupAlgoCtxArray));
    mRequiredCamsResMask = 0;
    mRequiredAlgoResMask = 0;
    mInit = false;
    mCamgroupCalib = NULL;

    EXIT_CAMGROUP_FUNCTION();
}

RkAiqCamGroupManager::~RkAiqCamGroupManager()
{
    ENTER_CAMGROUP_FUNCTION();
    EXIT_CAMGROUP_FUNCTION();
}

rk_aiq_groupcam_result_t*
RkAiqCamGroupManager::getGroupCamResult(uint32_t frameId, bool alloc)
{
    SmartLock locker (mCamGroupResMutex);
    rk_aiq_groupcam_result_t* camGroupRes = NULL;

    if (mCamGroupResMap.find(frameId) != mCamGroupResMap.end()) {
        camGroupRes = mCamGroupResMap[frameId];
        LOG1_CAMGROUP("camgroup res of frame: %d exists", frameId);
    } else {
        if (!alloc)
            return NULL;
        camGroupRes = new rk_aiq_groupcam_result_t();
        if (!camGroupRes) {
            LOGE_CAMGROUP("malloc camGroup Res failed !");
            return NULL;
        }
        camGroupRes->reset();
        camGroupRes->_frameId = frameId;
        mCamGroupResMap[frameId] = camGroupRes;
        LOGD_CAMGROUP("malloc camgroup res for frame: %d success", frameId);
    }

    return camGroupRes;
}

void
RkAiqCamGroupManager::clearGroupCamResult(uint32_t frameId) {

    SmartLock locker (mCamGroupResMutex);
    if (frameId == (uint32_t)(-1)) {
        // clear all
        LOGD_CAMGROUP("clear all camgroup res");
        for (auto it : mCamGroupResMap) {
            (it.second)->reset();
            delete it.second;
        }
        mCamGroupResMap.clear();
    } else {
        rk_aiq_groupcam_result_t* camGroupRes = NULL;

        if (mCamGroupResMap.find(frameId) != mCamGroupResMap.end()) {
            LOGD_CAMGROUP("clear camgroup res of frame: %d", frameId);
            camGroupRes = mCamGroupResMap[frameId];
            camGroupRes->reset();
            delete camGroupRes;
            mCamGroupResMap.erase(frameId);
        }
        if (mCamGroupResMap.size() > 10) {
            LOGW_CAMGROUP("camgroup unready size > 10", (mCamGroupResMap.begin())->first);
            for (auto iter : mCamGroupResMap) {
                LOGW_CAMGROUP("unready frameId: %d, valid:0x%x", iter.first, (iter.second)->_validCamResBits);
            }
        }
    }
}

rk_aiq_groupcam_sofsync_t*
RkAiqCamGroupManager::getGroupCamSofsync(uint32_t frameId, bool alloc)
{
    SmartLock locker (mCamGroupResMutex);
    rk_aiq_groupcam_sofsync_t* camGroupSofsync = NULL;

    if (mCamGroupSofsyncMap.find(frameId) != mCamGroupSofsyncMap.end()) {
        camGroupSofsync = mCamGroupSofsyncMap[frameId];
        LOG1_CAMGROUP("camgroup sofSync of frame: %d exists", frameId);
    } else {
        if (!alloc)
            return NULL;
        camGroupSofsync = new rk_aiq_groupcam_sofsync_t();
        if (!camGroupSofsync ) {
            LOGE_CAMGROUP("malloc camGroup sofSync failed !");
            return NULL;
        }
        camGroupSofsync->reset();
        mCamGroupSofsyncMap[frameId] = camGroupSofsync;
        LOGD_CAMGROUP("malloc camgroup sofSync for frame: %d success", frameId);
    }

    return camGroupSofsync;
}

void
RkAiqCamGroupManager::clearGroupCamSofsync(uint32_t frameId) {

    SmartLock locker (mCamGroupResMutex);
    if (frameId == (uint32_t)(-1)) {
        // clear all
        LOGD_CAMGROUP("clear all camgroup sofSync res");
        for (auto it : mCamGroupSofsyncMap) {
            (it.second)->reset();
            delete it.second;
        }
        mCamGroupSofsyncMap.clear();
    } else {
        rk_aiq_groupcam_sofsync_t* camGroupSofsync = NULL;

        if (mCamGroupSofsyncMap.find(frameId) != mCamGroupSofsyncMap.end()) {
            LOGD_CAMGROUP("clear camgroup sofSync of frame: %d", frameId);
            camGroupSofsync = mCamGroupSofsyncMap[frameId];
            camGroupSofsync->reset();
            delete camGroupSofsync;
            mCamGroupSofsyncMap.erase(frameId);
        }
        if (mCamGroupSofsyncMap.size() > 10) {
            LOGW_CAMGROUP("camgroup sofSync unready size > 10", (mCamGroupSofsyncMap.begin())->first);
            for (auto iter : mCamGroupSofsyncMap) {
                LOGW_CAMGROUP("unready sofSync frameId: %d, valid:0x%x", iter.first, (iter.second)->_validCamSofSyncBits);
            }
        }
    }
}

void
RkAiqCamGroupManager::setSingleCamStatusReady(rk_aiq_singlecam_result_status_t* status, rk_aiq_groupcam_result_t* gc_result)
{
    if (((status->_validCoreMsgsBits & mRequiredMsgsMask) == mRequiredMsgsMask) &&
            ((status->_validAlgoResBits & mRequiredAlgoResMask) == mRequiredAlgoResMask)) {
        status->_ready = true;
        LOGD_CAMGROUP("camgroup single cam res ready, camId:%d, frameId:%d",
                      status->_singleCamResults._3aResults._camId,
                      status->_singleCamResults._3aResults._frameId);
        gc_result->_validCamResBits |= 1 << status->_singleCamResults._3aResults._camId;
        if (!gc_result->_ready && (gc_result->_validCamResBits == mRequiredCamsResMask)) {
            gc_result->_ready = true;
            LOGD_CAMGROUP("camgroup all cam res ready, frameId:%d",
                          status->_singleCamResults._3aResults._frameId);

            // force to ready
            uint32_t lastFrameId = status->_singleCamResults._3aResults._frameId - 1;
            rk_aiq_groupcam_result_t* last_gc_result = getGroupCamResult(lastFrameId, false);
            if (last_gc_result && (mState == CAMGROUP_MANAGER_STARTED)) {
                last_gc_result->_ready = true;
                last_gc_result->_validCamResBits = mRequiredCamsResMask;
                rk_aiq_singlecam_result_status_t* last_scam_status = NULL;
                for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
                    if ((last_gc_result->_validCamResBits >> i) & 1) {
                        last_scam_status = &last_gc_result->_singleCamResultsStatus[i];
                        last_scam_status->_validAlgoResBits = mRequiredMsgsMask;
                        last_scam_status->_validCoreMsgsBits = mRequiredAlgoResMask;
                    }
                }
                LOGW_CAMGROUP("camgroup res frameId disorder, unready frameId:%d < cur ready frame %d",
                              lastFrameId, status->_singleCamResults._3aResults._frameId);
                mCamGroupReprocTh->sendFrame(last_gc_result);
            }
            // init params is reprocessed in func prepare
            if (mState == CAMGROUP_MANAGER_STARTED)
                mCamGroupReprocTh->sendFrame(gc_result);
        }
    } else {
        if (status->_singleCamResults._fullIspParam.ptr()) {
            RkAiqFullParams* scam_aiqParams = status->_singleCamResults._fullIspParam->data().ptr();
            LOG1_CAMGROUP("scam_aiqParams %p ", scam_aiqParams);
            \
        }
        LOG1_CAMGROUP("camgroup result status: validCams:0x%x(req:0x%x), camId:%d, frameId:%d, "
                      "validAlgoResBits:0x%" PRIx64 "(req:0x%" PRIx64 "), validMsgBits:0x%" PRIx64 "(req:0x%" PRIx64 ")",
                      gc_result->_validCamResBits, mRequiredCamsResMask,
                      status->_singleCamResults._3aResults._camId,
                      status->_singleCamResults._3aResults._frameId,
                      status->_validAlgoResBits, mRequiredAlgoResMask,
                      status->_validCoreMsgsBits, mRequiredMsgsMask);
    }
}

void
RkAiqCamGroupManager::processAiqCoreMsgs(RkAiqCore* src, SmartPtr<XCamMessage> &msg)
{
    int camId = src->getCamPhyId();
    uint32_t frameId = msg->frame_id;

    // check if the msg is required firstly
    if (!(mRequiredMsgsMask & (1 << msg->msg_id))) {
        LOG1_CAMGROUP("camgroup: not required core msg :%s of frameId: %d, ignore",
                      MessageType2Str[msg->msg_id], msg->frame_id);
        return;
    }

    switch (msg->msg_id) {
    case XCAM_MESSAGE_AWB_STATS_OK :
    case XCAM_MESSAGE_AEC_STATS_OK :
        // TODO: should get from RkAiqAnalyzerGroup::getMsgDelayCnt
        frameId += 2;
    default:
        break;
    }
    rk_aiq_groupcam_result_t* camGroupRes = getGroupCamResult(frameId);
    rk_aiq_singlecam_result_status_t* singleCamStatus = &camGroupRes->_singleCamResultsStatus[camId];
    rk_aiq_singlecam_result_t* singleCamRes = &singleCamStatus->_singleCamResults;

    SmartPtr<RkAiqCoreVdBufMsg> vdBufMsg;
    SmartPtr<RkAiqCoreExpMsg> sofInfoMsg;

    switch (msg->msg_id) {
    case XCAM_MESSAGE_AWB_STATS_OK :
        vdBufMsg = msg.dynamic_cast_ptr<RkAiqCoreVdBufMsg>();
        if (vdBufMsg.ptr())
            singleCamRes->_3aResults.awb._awbStats = convert_to_XCamVideoBuffer(vdBufMsg->msg);
        break;
    case XCAM_MESSAGE_AWB_PROC_RES_OK :
        vdBufMsg = msg.dynamic_cast_ptr<RkAiqCoreVdBufMsg>();
        if (vdBufMsg.ptr())
            singleCamRes->_3aResults.awb._awbProcRes = convert_to_XCamVideoBuffer(vdBufMsg->msg);
        break;
    case XCAM_MESSAGE_AEC_STATS_OK :
        vdBufMsg = msg.dynamic_cast_ptr<RkAiqCoreVdBufMsg>();
        if (vdBufMsg.ptr())
            singleCamRes->_3aResults.aec._aecStats = convert_to_XCamVideoBuffer(vdBufMsg->msg);
        break;
    case XCAM_MESSAGE_AE_PRE_RES_OK :
        vdBufMsg = msg.dynamic_cast_ptr<RkAiqCoreVdBufMsg>();
        if (vdBufMsg.ptr())
            singleCamRes->_3aResults.aec._aePreRes = convert_to_XCamVideoBuffer(vdBufMsg->msg);
        break;
    case XCAM_MESSAGE_AE_PROC_RES_OK :
        vdBufMsg = msg.dynamic_cast_ptr<RkAiqCoreVdBufMsg>();
        if (vdBufMsg.ptr())
            singleCamRes->_3aResults.aec._aeProcRes = convert_to_XCamVideoBuffer(vdBufMsg->msg);
    case XCAM_MESSAGE_SOF_INFO_OK :
        sofInfoMsg = msg.dynamic_cast_ptr<RkAiqCoreExpMsg>();
        if (sofInfoMsg.ptr()) {
            singleCamRes->_3aResults.aec._effAecExpInfo =
                sofInfoMsg->msg->data()->curExp->data()->aecExpInfo;
            singleCamRes->_3aResults.aec._bEffAecExpValid = true;
        }
        break;
    default:
        break;
    }

    // check if all requirements are satisfied, if so,
    // notify the reprocess procedure
    {
        SmartLock locker (mCamGroupResMutex);
        singleCamStatus->_validCoreMsgsBits |= ((uint64_t)1) << msg->msg_id;
        singleCamRes->_3aResults._camId = camId;
        singleCamRes->_3aResults._frameId = frameId;
    }
    LOGD_CAMGROUP("camgroup: got required core msg :%s of camId:%d, frameId: %d, ",
                  MessageType2Str[msg->msg_id], camId, frameId);
    setSingleCamStatusReady(singleCamStatus, camGroupRes);
}

void
RkAiqCamGroupManager::RelayAiqCoreResults(RkAiqCore* src, SmartPtr<RkAiqFullParamsProxy> &results)
{
    // only support v3x now
    int camId = src->getCamPhyId();
    uint32_t frame_id = -1;

    if (!CHECK_ISP_HW_V3X() && !CHECK_ISP_HW_V21()) {
        LOGE_CAMGROUP("only support isp 3x and 21 now");
        return;
    }

    RkAiqFullParams* aiqParams = results->data().ptr();

#define SET_TO_CAMGROUP(lc, BC) \
    if (aiqParams->m##lc##Params.ptr()) { \
        frame_id = aiqParams->m##lc##Params->data()->frame_id; \
        rk_aiq_groupcam_result_t* camGroupRes = getGroupCamResult(frame_id); \
        rk_aiq_singlecam_result_status_t* singleCamStatus = \
            &camGroupRes->_singleCamResultsStatus[camId]; \
        rk_aiq_singlecam_result_t* singleCamRes = &singleCamStatus->_singleCamResults; \
        /* compose single aiq params to one */ \
        { \
            SmartLock locker (mCamGroupResMutex); \
            if (!singleCamRes->_fullIspParam.ptr()) { \
                singleCamRes->_fullIspParam = results; \
                LOGD_CAMGROUP("init scam_aiqParams_proxy : %p for camId:%d, frameId: %d",\
                              singleCamRes->_fullIspParam.ptr(), camId, frame_id); \
            } \
            RkAiqFullParams* scam_aiqParams = singleCamRes->_fullIspParam->data().ptr();\
            if (scam_aiqParams != aiqParams) \
                scam_aiqParams->m##lc##Params = aiqParams->m##lc##Params; \
            singleCamStatus->_validAlgoResBits |= ((uint64_t)1) << RESULT_TYPE_##BC##_PARAM; \
            singleCamRes->_3aResults._camId = camId; \
            singleCamRes->_3aResults._frameId = frame_id; \
        } \
        LOG1_CAMGROUP("%s: relay results: camId:%d, frameId:%d, type:%s", \
                      __FUNCTION__, camId, frame_id, #BC); \
        setSingleCamStatusReady(singleCamStatus, camGroupRes); \
    } \

    SET_TO_CAMGROUP(Exposure, EXPOSURE);
    SET_TO_CAMGROUP(Focus, FOCUS);
    SET_TO_CAMGROUP(Aec, AEC);
    SET_TO_CAMGROUP(Hist, HIST);
    SET_TO_CAMGROUP(AwbGain, AWBGAIN);
    SET_TO_CAMGROUP(Dpcc, DPCC);
    SET_TO_CAMGROUP(Ccm, CCM);
    SET_TO_CAMGROUP(Lsc, LSC);
    SET_TO_CAMGROUP(Debayer, DEBAYER);
    SET_TO_CAMGROUP(Ldch, LDCH);
    SET_TO_CAMGROUP(Lut3d, LUT3D);
    SET_TO_CAMGROUP(Adegamma, ADEGAMMA);
    SET_TO_CAMGROUP(Wdr, WDR);
    SET_TO_CAMGROUP(Csm, CSM);
    SET_TO_CAMGROUP(Cgc, CGC);
    SET_TO_CAMGROUP(Conv422, CONV422);
    SET_TO_CAMGROUP(Yuvconv, YUVCONV);
    SET_TO_CAMGROUP(Cp, CP);
    SET_TO_CAMGROUP(Ie, IE);
    SET_TO_CAMGROUP(Cpsl, CPSL);
    SET_TO_CAMGROUP(Motion, MOTION);
    // TODO: special for fec ?
    SET_TO_CAMGROUP(Fec, FEC);
    // ispv21 and ispv3x common
    SET_TO_CAMGROUP(BlcV21, BLC);
    SET_TO_CAMGROUP(GicV21, GIC);

    if (CHECK_ISP_HW_V21()) {
        // ispv21
        SET_TO_CAMGROUP(AwbV21, AWB);
        SET_TO_CAMGROUP(DrcV21, DRC);
        SET_TO_CAMGROUP(DehazeV21, DEHAZE);
        SET_TO_CAMGROUP(BaynrV21, RAWNR);
        SET_TO_CAMGROUP(YnrV21, YNR);
        SET_TO_CAMGROUP(CnrV21, UVNR);
        SET_TO_CAMGROUP(SharpenV21, SHARPEN);
        SET_TO_CAMGROUP(Af, AF);
        SET_TO_CAMGROUP(Agamma, AGAMMA);
        SET_TO_CAMGROUP(Merge, MERGE);
        SET_TO_CAMGROUP(Gain, GAIN);
    } else {
        // ispv3x
        SET_TO_CAMGROUP(AwbV3x, AWB);
        SET_TO_CAMGROUP(AfV3x, AF);
        SET_TO_CAMGROUP(AgammaV3x, AGAMMA);
        SET_TO_CAMGROUP(DrcV3x, DRC);
        SET_TO_CAMGROUP(MergeV3x, MERGE);
        SET_TO_CAMGROUP(DehazeV3x, DEHAZE);
        SET_TO_CAMGROUP(BaynrV3x, RAWNR);
        SET_TO_CAMGROUP(YnrV3x, YNR);
        SET_TO_CAMGROUP(CnrV3x, UVNR);
        SET_TO_CAMGROUP(SharpenV3x, SHARPEN);
        SET_TO_CAMGROUP(CacV3x, CAC);
        SET_TO_CAMGROUP(GainV3x, GAIN);
        SET_TO_CAMGROUP(TnrV3x, TNR);
    }
}

XCamReturn
RkAiqCamGroupManager::sofSync(RkAiqManager* aiqManager, SmartPtr<VideoBuffer>& sof_evt)
{
    int camId = aiqManager->getCamPhyId();
    uint32_t frameId = sof_evt->get_sequence();

    if (mState != CAMGROUP_MANAGER_STARTED) {
        LOGE_CAMGROUP("wrong state %d, ignore sofSync event \n", mState);
        return XCAM_RETURN_NO_ERROR;
    }

    LOGD_CAMGROUP("sofSync event camId: %d, frameId: %d ...\n", camId, frameId);

    rk_aiq_groupcam_sofsync_t* camGroupSofsync = getGroupCamSofsync(frameId);
    camGroupSofsync->_singleCamSofEvt[camId] = sof_evt;

    {
        SmartLock locker (mCamGroupResMutex);
        camGroupSofsync->_validCamSofSyncBits |= ((uint8_t)1) << camId;
    }

    if (camGroupSofsync->_validCamSofSyncBits == mRequiredCamsResMask) {
        {
            SmartLock locker (mCamGroupApiSyncMutex);
            for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
                if ((camGroupSofsync->_validCamSofSyncBits >> i) & 1) {
                    mBindAiqsMap[i]->syncSofEvt(camGroupSofsync->_singleCamSofEvt[i]);
                }
            }
        }
        clearGroupCamSofsync(frameId);
    }

    LOGD_CAMGROUP("sofSync event camId: %d, frameId: %d done\n", camId, frameId);

    return XCAM_RETURN_NO_ERROR;
}

void
RkAiqCamGroupManager::addDefaultAlgos(const struct RkAiqAlgoDesCommExt* algoDes)
{
    if (mBindAiqsMap.empty()) {
        LOGD_CAMGROUP("no group cam, bypass");
        return ;
    }

    RkAiqManager* aiqManager = (mBindAiqsMap.begin())->second;
    RkAiqCore* aiqCore = aiqManager->mRkAiqAnalyzer.ptr();
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &aiqCore->mAlogsComSharedParams;

    mGroupAlgoCtxCfg.s_calibv2 = sharedCom->calibv2;
    mGroupAlgoCtxCfg.pCamgroupCalib = mCamgroupCalib;
    mGroupAlgoCtxCfg.cfg_com.isp_hw_version = aiqCore->mIspHwVer;

    mGroupAlgoCtxCfg.camIdArrayLen = mBindAiqsMap.size();

    int i = 0;
    for (auto it : mBindAiqsMap)
        mGroupAlgoCtxCfg.camIdArray[i++] = it.first;

    for (int i = 0; algoDes[i].des != NULL; i++) {
        RkAiqAlgoDesComm* algo_des = algoDes[i].des;
        mGroupAlgoCtxCfg.cfg_com.module_hw_version = algoDes[i].module_hw_ver;

        XCamReturn ret = algo_des->create_context(&mGroupAlgoCtxArray[algo_des->type],
                         (const _AlgoCtxInstanceCfg*)(&mGroupAlgoCtxCfg));
        if (ret) {
            LOGE_CAMGROUP("camgroup: add algo: %d failed", algo_des->type);
            continue;
        }
        LOGD_CAMGROUP("camgroup: add algo: %d", algo_des->type);
    }
}

XCamReturn
RkAiqCamGroupManager::setCamgroupCalib(CamCalibDbCamgroup_t* camgroup_calib)
{
    ENTER_CAMGROUP_FUNCTION();
    if (mState == CAMGROUP_MANAGER_STARTED ||
            mState == CAMGROUP_MANAGER_INVALID) {
        LOGE_CAMGROUP("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_FAILED;
    }
    // update groupcalib
    mCamgroupCalib = camgroup_calib;
    EXIT_CAMGROUP_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCamGroupManager::init()
{
    ENTER_CAMGROUP_FUNCTION();
    addDefaultAlgos(mGroupAlgosDesArray);

    if (mState != CAMGROUP_MANAGER_BINDED) {
        LOGE_CAMGROUP("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_FAILED;
    }
    mState = CAMGROUP_MANAGER_INITED;
    EXIT_CAMGROUP_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCamGroupManager::deInit()
{
    ENTER_CAMGROUP_FUNCTION();
    if (mState != CAMGROUP_MANAGER_UNBINDED) {
        LOGE_CAMGROUP("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_FAILED;
    }

    for (int i = 0; mGroupAlgosDesArray[i].des != NULL; i++) {
        RkAiqAlgoDesComm* algo_des = mGroupAlgosDesArray[i].des;

        if (mGroupAlgoCtxArray[algo_des->type]) {
            algo_des->destroy_context(mGroupAlgoCtxArray[algo_des->type]);
            LOGD_CAMGROUP("camgroup: add algo: %d", algo_des->type);
        }
    }

    mState = CAMGROUP_MANAGER_INVALID;
    EXIT_CAMGROUP_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCamGroupManager::start()
{
    ENTER_CAMGROUP_FUNCTION();
    if (mState != CAMGROUP_MANAGER_PREPARED) {
        LOGE_CAMGROUP("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_FAILED;
    }

    mCamGroupReprocTh->triger_start();
    mCamGroupReprocTh->start();

    mState = CAMGROUP_MANAGER_STARTED;
    EXIT_CAMGROUP_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCamGroupManager::stop()
{
    ENTER_CAMGROUP_FUNCTION();
    if (mState == CAMGROUP_MANAGER_INVALID) {
        LOGE_CAMGROUP("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_FAILED;
    }

    mCamGroupReprocTh->triger_stop();
    mCamGroupReprocTh->stop();
    clearGroupCamResult(-1);
    clearGroupCamSofsync(-1);

    if (mState == CAMGROUP_MANAGER_STARTED) {
        mState = CAMGROUP_MANAGER_PREPARED;
    }
    EXIT_CAMGROUP_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCamGroupManager::prepare()
{
    ENTER_CAMGROUP_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (mState != CAMGROUP_MANAGER_INITED &&
            mState != CAMGROUP_MANAGER_BINDED) {
        LOGE_CAMGROUP("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_FAILED;
    }

    if (mBindAiqsMap.empty()) {
        LOGD_CAMGROUP("no group cam, bypass");
        return XCAM_RETURN_NO_ERROR;
    }

    // assume all single cam runs same algos
    RkAiqManager* aiqManager = (mBindAiqsMap.begin())->second;
    RkAiqCore* aiqCore = aiqManager->mRkAiqAnalyzer.ptr();

    // reprocess initial params
    RkAiqAlgoCamGroupPrepare prepareCfg;

    RkAiqAlgoComCamGroup* gcom = &prepareCfg.gcom;
    RkAiqAlgoCom *com = &gcom->com;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &aiqCore->mAlogsComSharedParams;

    // TODO: should deal with the case of eanbled algos changed dynamically
    mRequiredAlgoResMask = aiqCore->mAllReqAlgoResMask;

    int i = 0;
    prepareCfg.camIdArrayLen = mBindAiqsMap.size();

    rk_aiq_groupcam_result_t* camGroupRes = getGroupCamResult(0);

    LOGD_CAMGROUP("camgroup: prepare: relay init params ...");
    for (auto it : mBindAiqsMap) {
        prepareCfg.camIdArray[i++] = it.first;
        RkAiqManager* sAiqManager = it.second;
        RkAiqCore* sAiqCore = sAiqManager->mRkAiqAnalyzer.ptr();
        // initial params has no stats
        camGroupRes->_singleCamResultsStatus[it.first]._validCoreMsgsBits = mRequiredMsgsMask;
        RelayAiqCoreResults(sAiqCore, sAiqCore->mAiqCurParams);
    }

    prepareCfg.aec.LinePeriodsPerField =
        (float)sharedCom->snsDes.frame_length_lines;
    prepareCfg.aec.PixelClockFreqMHZ =
        (float)sharedCom->snsDes.pixel_clock_freq_mhz;
    prepareCfg.aec.PixelPeriodsPerLine =
        (float)sharedCom->snsDes.line_length_pck;
    prepareCfg.s_calibv2 = mGroupAlgoCtxCfg.s_calibv2;

    prepareCfg.pCamgroupCalib = mCamgroupCalib;
    prepareCfg.aec.nr_switch = sharedCom->snsDes.nr_switch;

    LOGD_CAMGROUP("camgroup: prepare: prepare algos ...");
    for (i = 0; mGroupAlgosDesArray[i].des != NULL; i++) {
        RkAiqAlgoDesComm* algo_des = mGroupAlgosDesArray[i].des;
        if (mGroupAlgoCtxArray[algo_des->type]) {
            com->ctx                     = mGroupAlgoCtxArray[algo_des->type];
            com->frame_id                = 0;
            com->u.prepare.working_mode  = sharedCom->working_mode;
            com->u.prepare.sns_op_width  = sharedCom->snsDes.isp_acq_width;
            com->u.prepare.sns_op_height = sharedCom->snsDes.isp_acq_height;
            com->u.prepare.conf_type     = sharedCom->conf_type;
            ret = ((RkAiqAlgoDescription*)algo_des)->prepare(com);
            if (ret) {
                goto failed;
            }
        }
    }

    LOGD_CAMGROUP("camgroup: reprocess init params ...");

    mInit = true;

    ret = reProcess(camGroupRes);
    if (ret) {
        goto failed;
    }
    mInit = false;

    LOGD_CAMGROUP("camgroup: send init params to hwi ...");
    relayToHwi(camGroupRes);

    LOGD_CAMGROUP("camgroup: clear init params ...");
    // delete the processed result
    clearGroupCamResult(0);

    LOGD_CAMGROUP("camgroup: prepare done");

    mState = CAMGROUP_MANAGER_PREPARED;
    return XCAM_RETURN_NO_ERROR;
    EXIT_CAMGROUP_FUNCTION();
failed:
    clearGroupCamResult(-1);
    return ret;
}

XCamReturn
RkAiqCamGroupManager::bind(RkAiqManager* ctx)
{
    ENTER_CAMGROUP_FUNCTION();

    if (mState != CAMGROUP_MANAGER_INVALID &&
            mState != CAMGROUP_MANAGER_BINDED) {
        LOGE_CAMGROUP("in error state %d", mState);
        return XCAM_RETURN_ERROR_FAILED;
    }

    int camId = ctx->getCamPhyId();
    std::map<uint8_t, RkAiqManager*>::iterator it =
        mBindAiqsMap.find(camId);

    LOGD_CAMGROUP("camgroup: bind camId: %d to group", camId);

    if (it != mBindAiqsMap.end()) {
        return XCAM_RETURN_NO_ERROR;
    } else {
        mBindAiqsMap[camId] = ctx;
        mRequiredCamsResMask |= 1 << camId;
    }

    mState = CAMGROUP_MANAGER_BINDED;

    LOGD_CAMGROUP("camgroup: binded cams mask: 0x%x", mRequiredCamsResMask);

    EXIT_CAMGROUP_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCamGroupManager::unbind(int camId)
{
    ENTER_CAMGROUP_FUNCTION();

    if (mState == CAMGROUP_MANAGER_STARTED) {
        LOGE_CAMGROUP("in error state %d", mState);
        return XCAM_RETURN_ERROR_FAILED;
    }

    LOGD_CAMGROUP("camgroup: unbind camId: %d from group", camId);

    std::map<uint8_t, RkAiqManager*>::iterator it =
        mBindAiqsMap.find(camId);

    if (it != mBindAiqsMap.end()) {
        mBindAiqsMap.erase(it);
        mRequiredCamsResMask &= ~(1 << camId);
        if (mBindAiqsMap.empty())
            mState = CAMGROUP_MANAGER_UNBINDED;
    } else {
        return XCAM_RETURN_NO_ERROR;
    }

    LOGD_CAMGROUP("camgroup: binded cams mask: 0x%x", mRequiredCamsResMask);

    EXIT_CAMGROUP_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCamGroupManager::reProcess(rk_aiq_groupcam_result_t* gc_res)
{
    ENTER_CAMGROUP_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (mBindAiqsMap.empty()) {
        LOGW_CAMGROUP("no group cam, bypass");
        return XCAM_RETURN_NO_ERROR;
    }

    // assume all single cam runs same algos
    RkAiqManager* aiqManager = (mBindAiqsMap.begin())->second;
    RkAiqCore* aiqCore = aiqManager->mRkAiqAnalyzer.ptr();
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &aiqCore->mAlogsComSharedParams;

    RkAiqAlgoCamGroupProcOut procOut;
    RkAiqAlgoCamGroupProcIn procIn;

    memset(&procIn, 0, sizeof(procIn));
    memset(&procOut, 0, sizeof(procOut));

    RkAiqAlgoComCamGroup* gcom = &procIn.gcom;
    RkAiqAlgoCom *com = &gcom->com;

    procIn.arraySize = mBindAiqsMap.size();
    procOut.arraySize = mBindAiqsMap.size();

    LOGD_CAMGROUP("camgroup: set reprocess params ... ");

    rk_aiq_singlecam_3a_result_t* camgroupParmasArray[procIn.arraySize];

    memset(camgroupParmasArray, 0, sizeof(camgroupParmasArray));

    procIn.camgroupParmasArray = camgroupParmasArray;
    procOut.camgroupParmasArray = camgroupParmasArray;
    procIn._gray_mode = sharedCom->gray_mode;
    procIn.working_mode = sharedCom->working_mode;
    procIn._is_bw_sensor = sharedCom->is_bw_sensor;

    int i = 0, vaild_cam_ind = 0;
    rk_aiq_singlecam_3a_result_t* scam_3a_res = NULL;
    rk_aiq_singlecam_result_t* scam_res = NULL;
    RkAiqFullParams* aiqParams = NULL;

    for (i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
        if ((gc_res->_validCamResBits >> i) & 1) {
            scam_res = &gc_res->_singleCamResultsStatus[i]._singleCamResults;
            scam_3a_res = &scam_res->_3aResults;
            if (!scam_res->_fullIspParam.ptr())
                return XCAM_RETURN_NO_ERROR;
            aiqParams = scam_res->_fullIspParam->data().ptr();
            // fill 3a params
            if ((aiqParams->mExposureParams.ptr())) {
                scam_3a_res->aec.exp_tbl = aiqParams->mExposureParams->data()->exp_tbl;
                scam_3a_res->aec.exp_tbl_size = &aiqParams->mExposureParams->data()->exp_tbl_size;
            } else {
                LOGW_CAMGROUP("camId:%d, framId:%d, exp is null", i, gc_res->_frameId);
                // frame 1,2 exp may be null now
                //if (gc_res->_frameId == 1)
                return XCAM_RETURN_NO_ERROR;
            }
            scam_3a_res->aec._aeMeasParams = &aiqParams->mAecParams->data()->result;
            scam_3a_res->aec._aeHistMeasParams = &aiqParams->mHistParams->data()->result;

            if (CHECK_ISP_HW_V21()) {
                if (!aiqParams->mAwbV21Params.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->awb._awbCfgV201 = &aiqParams->mAwbV21Params->data()->result;
                scam_3a_res->_adehazeConfig = &aiqParams->mDehazeV21Params->data()->result;
                scam_3a_res->_agammaConfig = &aiqParams->mAgammaParams->data()->result;
                scam_3a_res->_adrcConfig = &aiqParams->mDrcV21Params->data()->result;
                scam_3a_res->_amergeConfig = &aiqParams->mMergeParams->data()->result;
            } else {
                if (!aiqParams->mAwbV3xParams.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->awb._awbCfgV3x = &aiqParams->mAwbV3xParams->data()->result;
                scam_3a_res->_adehazeConfig = &aiqParams->mDehazeV3xParams->data()->result;
                scam_3a_res->_agammaConfig = &aiqParams->mAgammaV3xParams->data()->result;
                scam_3a_res->_adrcConfig = &aiqParams->mDrcV3xParams->data()->result;
                scam_3a_res->_amergeConfig = &aiqParams->mMergeV3xParams->data()->result;
            }
            scam_3a_res->awb._awbGainParams = &aiqParams->mAwbGainParams->data()->result;
            scam_3a_res->_lscConfig = &aiqParams->mLscParams->data()->result;
            scam_3a_res->_dpccConfig = &aiqParams->mDpccParams->data()->result;
            scam_3a_res->_ccmCfg = &aiqParams->mCcmParams->data()->result;
            scam_3a_res->_lut3dCfg = &aiqParams->mLut3dParams->data()->result;
            scam_3a_res->_blcConfig = &aiqParams->mBlcV21Params->data()->result;


            if (CHECK_ISP_HW_V21()) {
                if (!aiqParams->mYnrV21Params.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->aynr._aynr_procRes_v2 = &aiqParams->mYnrV21Params->data()->result;
            } else {
                if (!aiqParams->mYnrV3xParams.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->aynr._aynr_procRes_v3 = &aiqParams->mYnrV3xParams->data()->result;
            }

            if (CHECK_ISP_HW_V21()) {
                if (!aiqParams->mCnrV21Params.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->acnr._acnr_procRes_v1 = &aiqParams->mCnrV21Params->data()->result;
            } else {
                if (!aiqParams->mCnrV3xParams.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->acnr._acnr_procRes_v2 = &aiqParams->mCnrV3xParams->data()->result;
            }

            if (CHECK_ISP_HW_V21()) {
                if (!aiqParams->mSharpenV21Params.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->asharp._asharp_procRes_v3 = &aiqParams->mSharpenV21Params->data()->result;
            } else {
                if (!aiqParams->mSharpenV3xParams.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->asharp._asharp_procRes_v4 = &aiqParams->mSharpenV3xParams->data()->result;
            }


            if (CHECK_ISP_HW_V21()) {
                if (!aiqParams->mBaynrV21Params.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->abayernr._abayernr_procRes_v1 = &aiqParams->mBaynrV21Params->data()->result;
            } else {
                if (!aiqParams->mBaynrV3xParams.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->abayernr._abayer2dnr_procRes_v2 = &aiqParams->mBaynrV3xParams->data()->result;
            }

            if (CHECK_ISP_HW_V30()) {
                if (!aiqParams->mTnrV3xParams.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->abayertnr._abayertnr_procRes_v2 = &aiqParams->mTnrV3xParams->data()->result;
            }

            if (CHECK_ISP_HW_V30()) {
                if (!aiqParams->mGainV3xParams.ptr())
                    return XCAM_RETURN_NO_ERROR;
                scam_3a_res->again._again_procRes_v2 = &aiqParams->mGainV3xParams->data()->result;
            }
            camgroupParmasArray[vaild_cam_ind++] = scam_3a_res;
        }
    }

    if (vaild_cam_ind != procIn.arraySize) {
        LOGW_CAMGROUP("wrong num of valid cam res:%d,exp:%d",
                      vaild_cam_ind, procIn.arraySize);
    }

    uint32_t frameId = camgroupParmasArray[0]->_frameId;
    LOGD_CAMGROUP("camgroup: frameId:%d reprocessing ... ", frameId);
    for (i = 0; mGroupAlgosDesArray[i].des != NULL; i++) {
        RkAiqAlgoDesComm* algo_des = mGroupAlgosDesArray[i].des;
        if (mGroupAlgoCtxArray[algo_des->type]) {
            com->ctx         = mGroupAlgoCtxArray[algo_des->type];
            com->frame_id    = frameId;
            // TODO: remove init info ? algo can maintain the state itself
            com->u.proc.init = mInit;
            ret = ((RkAiqAlgoDescription*)algo_des)->processing((const RkAiqAlgoCom*)&procIn,
                    (RkAiqAlgoResCom*)&procOut);
            if (ret) {
                LOGW_CAMGROUP("group algo %d proc error !", i);
                continue;
            }
        }
    }

    EXIT_CAMGROUP_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

void
RkAiqCamGroupManager::relayToHwi(rk_aiq_groupcam_result_t* gc_res)
{
    rk_aiq_singlecam_result_t* singlecam_res = NULL;
    {
        SmartLock locker (mCamGroupApiSyncMutex);
        for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
            // apply exposure directly
            if ((gc_res->_validCamResBits >> i) & 1) {
                singlecam_res = &gc_res->_singleCamResultsStatus[i]._singleCamResults;
                SmartPtr<RkAiqFullParams> fullParam = new RkAiqFullParams();
                SmartPtr<RkAiqFullParamsProxy> fullParamProxy = new RkAiqFullParamsProxy(fullParam );
                fullParamProxy->data()->mExposureParams = singlecam_res->_fullIspParam->data()->mExposureParams;
                if (fullParamProxy->data()->mExposureParams.ptr()) {
                    LOGD_CAMGROUP("camgroup: camId:%d, frameId:%d, exp_tbl_size:%d",
                                  i, gc_res->_frameId, fullParamProxy->data()->mExposureParams->data()->exp_tbl_size);
                }
                singlecam_res->_fullIspParam->data()->mExposureParams.release();
                mBindAiqsMap[i]->applyAnalyzerResult(fullParamProxy);
            }
        }
    }

    for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
        if ((gc_res->_validCamResBits >> i) & 1) {
            singlecam_res = &gc_res->_singleCamResultsStatus[i]._singleCamResults;
            if (mState == CAMGROUP_MANAGER_STARTED) {
                LOGD_CAMGROUP("camgroup: relay camId %d params to aiq manager !", i);
                mBindAiqsMap[i]->rkAiqCalcDone(singlecam_res->_fullIspParam);
            } else {
                LOGD_CAMGROUP("camgroup: apply camId %d params to hwi directly !", i);
                mBindAiqsMap[i]->applyAnalyzerResult(singlecam_res->_fullIspParam);
            }
        }
    }
}

}; //namespace
