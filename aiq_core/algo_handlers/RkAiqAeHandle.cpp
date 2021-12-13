/*
 * RkAiqHandle.h
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

#include "RkAiqCore.h"
#include "RkAiqHandle.h"
#include "RkAiqHandleInt.h"

namespace RkCam {

void RkAiqAeHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAeInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAeInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAeInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAeInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAeInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAeInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAeInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAeHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (needSync) mCfgMutex.lock();
    // if something changed, api will modify aecCfg in mAlgoCtx
    if (updateExpSwAttr) {
        mCurExpSwAttr   = mNewExpSwAttr;
        updateExpSwAttr = false;
        updateAttr |= UPDATE_EXPSWATTR;

        rk_aiq_uapi_ae_convExpSwAttr_v1Tov2(&mCurExpSwAttr, &mCurExpSwAttrV2);
        rk_aiq_uapi_ae_setExpSwAttr(mAlgoCtx, &mCurExpSwAttrV2, false);
        sendSignal();
    }

    if (updateLinExpAttr) {
        mCurLinExpAttr   = mNewLinExpAttr;
        updateLinExpAttr = false;
        updateAttr |= UPDATE_LINEXPATTR;

        rk_aiq_uapi_ae_convLinExpAttr_v1Tov2(&mCurLinExpAttr, &mCurLinExpAttrV2);
        rk_aiq_uapi_ae_setLinExpAttr(mAlgoCtx, &mCurLinExpAttrV2, false);
        sendSignal();
    }

    if (updateHdrExpAttr) {
        mCurHdrExpAttr   = mNewHdrExpAttr;
        updateHdrExpAttr = false;
        updateAttr |= UPDATE_HDREXPATTR;

        rk_aiq_uapi_ae_convHdrExpAttr_v1Tov2(&mCurHdrExpAttr, &mCurHdrExpAttrV2);
        rk_aiq_uapi_ae_setHdrExpAttr(mAlgoCtx, &mCurHdrExpAttrV2, false);
        sendSignal();
    }

    // TODO: update v2

    if (updateExpSwAttrV2) {
        mCurExpSwAttrV2   = mNewExpSwAttrV2;
        updateExpSwAttrV2 = false;
        updateAttr |= UPDATE_EXPSWATTR;

        rk_aiq_uapi_ae_setExpSwAttr(mAlgoCtx, &mCurExpSwAttrV2, false);
        sendSignal();
    }

    if (updateLinExpAttrV2) {
        mCurLinExpAttrV2   = mNewLinExpAttrV2;
        updateLinExpAttrV2 = false;
        updateAttr |= UPDATE_LINEXPATTR;

        rk_aiq_uapi_ae_setLinExpAttr(mAlgoCtx, &mCurLinExpAttrV2, false);
        sendSignal();
    }

    if (updateHdrExpAttrV2) {
        mCurHdrExpAttrV2   = mNewHdrExpAttrV2;
        updateHdrExpAttrV2 = false;
        updateAttr |= UPDATE_HDREXPATTR;

        rk_aiq_uapi_ae_setHdrExpAttr(mAlgoCtx, &mCurHdrExpAttrV2, false);
        sendSignal();
    }

    if (updateLinAeRouteAttr) {
        mCurLinAeRouteAttr   = mNewLinAeRouteAttr;
        updateLinAeRouteAttr = false;
        updateAttr |= UPDATE_LINAEROUTEATTR;
        rk_aiq_uapi_ae_setLinAeRouteAttr(mAlgoCtx, &mCurLinAeRouteAttr, false);
        sendSignal();
    }
    if (updateHdrAeRouteAttr) {
        mCurHdrAeRouteAttr   = mNewHdrAeRouteAttr;
        updateHdrAeRouteAttr = false;
        updateAttr |= UPDATE_HDRAEROUTEATTR;
        rk_aiq_uapi_ae_setHdrAeRouteAttr(mAlgoCtx, &mCurHdrAeRouteAttr, false);
        sendSignal();
    }
    if (updateIrisAttr) {
        mCurIrisAttr   = mNewIrisAttr;
        updateIrisAttr = false;
        updateAttr |= UPDATE_IRISATTR;
        rk_aiq_uapi_ae_setIrisAttr(mAlgoCtx, &mCurIrisAttr, false);
        sendSignal();
    }
    if (updateSyncTestAttr) {
        mCurAecSyncTestAttr = mNewAecSyncTestAttr;
        updateSyncTestAttr  = false;
        updateAttr |= UPDATE_SYNCTESTATTR;
        rk_aiq_uapi_ae_setSyncTest(mAlgoCtx, &mCurAecSyncTestAttr, false);
        sendSignal();
    }
    if (updateExpWinAttr) {
        mCurExpWinAttr   = mNewExpWinAttr;
        updateExpWinAttr = false;
        updateAttr |= UPDATE_EXPWINATTR;
        rk_aiq_uapi_ae_setExpWinAttr(mAlgoCtx, &mCurExpWinAttr, false);
        sendSignal();
    }

    // once any params are changed, run reconfig to convert aecCfg to paectx
    AeInstanceConfig_t* pAeInstConfig = (AeInstanceConfig_t*)mAlgoCtx;
    AeConfig_t pAecCfg                = pAeInstConfig->aecCfg;
    pAecCfg->IsReconfig |= updateAttr;
    updateAttr = 0;
    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::lock() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();

    rk_aiq_uapi_ae_lock(mAlgoCtx);

    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::unlock() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();

    rk_aiq_uapi_ae_unlock(mAlgoCtx);

    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setExpSwAttr(Uapi_ExpSwAttr_t ExpSwAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurExpSwAttr, &ExpSwAttr, sizeof(Uapi_ExpSwAttr_t))) {
        mNewExpSwAttr   = ExpSwAttr;
        updateExpSwAttr = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getExpSwAttr(Uapi_ExpSwAttr_t* pExpSwAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    Uapi_ExpSwAttrV2_t ExpSwAttrV2;

    rk_aiq_uapi_ae_getExpSwAttr(mAlgoCtx, &mCurExpSwAttrV2);
    rk_aiq_uapi_ae_convExpSwAttr_v2Tov1(&mCurExpSwAttrV2, pExpSwAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setExpSwAttr(Uapi_ExpSwAttrV2_t ExpSwAttrV2) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurExpSwAttrV2, &ExpSwAttrV2, sizeof(Uapi_ExpSwAttrV2_t))) {
        mNewExpSwAttrV2   = ExpSwAttrV2;
        updateExpSwAttrV2 = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getExpSwAttr(Uapi_ExpSwAttrV2_t* pExpSwAttrV2) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getExpSwAttr(mAlgoCtx, pExpSwAttrV2);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setLinExpAttr(Uapi_LinExpAttr_t LinExpAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurLinExpAttr, &LinExpAttr, sizeof(Uapi_LinExpAttr_t))) {
        mNewLinExpAttr   = LinExpAttr;
        updateLinExpAttr = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getLinExpAttr(Uapi_LinExpAttr_t* pLinExpAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getLinExpAttr(mAlgoCtx, &mCurLinExpAttrV2);
    rk_aiq_uapi_ae_convLinExpAttr_v2Tov1(&mCurLinExpAttrV2, pLinExpAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setLinExpAttr(Uapi_LinExpAttrV2_t LinExpAttrV2) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurLinExpAttrV2, &LinExpAttrV2, sizeof(Uapi_LinExpAttrV2_t))) {
        mNewLinExpAttrV2   = LinExpAttrV2;
        updateLinExpAttrV2 = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getLinExpAttr(Uapi_LinExpAttrV2_t* pLinExpAttrV2) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getLinExpAttr(mAlgoCtx, pLinExpAttrV2);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setHdrExpAttr(Uapi_HdrExpAttr_t HdrExpAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurHdrExpAttr, &HdrExpAttr, sizeof(Uapi_HdrExpAttr_t))) {
        mNewHdrExpAttr   = HdrExpAttr;
        updateHdrExpAttr = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getHdrExpAttr(Uapi_HdrExpAttr_t* pHdrExpAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getHdrExpAttr(mAlgoCtx, &mCurHdrExpAttrV2);
    rk_aiq_uapi_ae_convHdrExpAttr_v2Tov1(&mCurHdrExpAttrV2, pHdrExpAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setHdrExpAttr(Uapi_HdrExpAttrV2_t HdrExpAttrV2) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurHdrExpAttrV2, &HdrExpAttrV2, sizeof(Uapi_HdrExpAttrV2_t))) {
        mNewHdrExpAttrV2   = HdrExpAttrV2;
        updateHdrExpAttrV2 = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getHdrExpAttr(Uapi_HdrExpAttrV2_t* pHdrExpAttrV2) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getHdrExpAttr(mAlgoCtx, pHdrExpAttrV2);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setLinAeRouteAttr(Uapi_LinAeRouteAttr_t LinAeRouteAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed

    if (0 != memcmp(&mCurLinAeRouteAttr, &LinAeRouteAttr, sizeof(Uapi_LinAeRouteAttr_t))) {
        mNewLinAeRouteAttr   = LinAeRouteAttr;
        updateLinAeRouteAttr = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getLinAeRouteAttr(Uapi_LinAeRouteAttr_t* pLinAeRouteAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getLinAeRouteAttr(mAlgoCtx, pLinAeRouteAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setHdrAeRouteAttr(Uapi_HdrAeRouteAttr_t HdrAeRouteAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurHdrAeRouteAttr, &HdrAeRouteAttr, sizeof(Uapi_HdrAeRouteAttr_t))) {
        mNewHdrAeRouteAttr   = HdrAeRouteAttr;
        updateHdrAeRouteAttr = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getHdrAeRouteAttr(Uapi_HdrAeRouteAttr_t* pHdrAeRouteAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getHdrAeRouteAttr(mAlgoCtx, pHdrAeRouteAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setIrisAttr(Uapi_IrisAttrV2_t IrisAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed

    if (0 != memcmp(&mCurIrisAttr, &IrisAttr, sizeof(Uapi_IrisAttrV2_t))) {
        mNewIrisAttr   = IrisAttr;
        updateIrisAttr = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getIrisAttr(Uapi_IrisAttrV2_t* pIrisAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getIrisAttr(mAlgoCtx, pIrisAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setSyncTestAttr(Uapi_AecSyncTest_t SyncTestAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed

    if (0 != memcmp(&mCurAecSyncTestAttr, &SyncTestAttr, sizeof(Uapi_AecSyncTest_t))) {
        mNewAecSyncTestAttr = SyncTestAttr;
        updateSyncTestAttr  = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getSyncTestAttr(Uapi_AecSyncTest_t* pSyncTestAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getSyncTest(mAlgoCtx, pSyncTestAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setExpWinAttr(Uapi_ExpWin_t ExpWinAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed

    if (0 != memcmp(&mCurExpWinAttr, &ExpWinAttr, sizeof(Uapi_ExpWin_t))) {
        mNewExpWinAttr   = ExpWinAttr;
        updateExpWinAttr = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::getExpWinAttr(Uapi_ExpWin_t* pExpWinAttr) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_getExpWinAttr(mAlgoCtx, pExpWinAttr);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::queryExpInfo(Uapi_ExpQueryInfo_t* pExpQueryInfo) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ae_queryExpInfo(mAlgoCtx, pExpQueryInfo);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::setLockAeForAf(bool lock_ae) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mLockAebyAfMutex.lock();
    lockaebyaf = lock_ae;
    mLockAebyAfMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "ae handle prepare failed");

    RkAiqAlgoConfigAeInt* ae_config_int = (RkAiqAlgoConfigAeInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    // TODO config ae common params:
    RkAiqAlgoConfigAe* ae_config                = (RkAiqAlgoConfigAe*)(&ae_config_int->ae_cfg_com);

    /*****************AecConfig Sensor Exp related info*****************/
    ae_config->LinePeriodsPerField = (float)sharedCom->snsDes.frame_length_lines;
    ae_config->PixelPeriodsPerLine = (float)sharedCom->snsDes.line_length_pck;
    ae_config->PixelClockFreqMHZ   = (float)sharedCom->snsDes.pixel_clock_freq_mhz;

    /*****************AecConfig pic-info params*****************/
    ae_config_int->RawWidth  = sharedCom->snsDes.isp_acq_width;
    ae_config_int->RawHeight = sharedCom->snsDes.isp_acq_height;
    ae_config_int->nr_switch = sharedCom->snsDes.nr_switch;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "ae algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAeHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAeInt* ae_pre_int        = (RkAiqAlgoPreAeInt*)mPreInParam;
    RkAiqAlgoPreResAeInt* ae_pre_res_int = nullptr;
    if (mAiqCore->mAlogsComSharedParams.init) {
        ae_pre_res_int = (RkAiqAlgoPreResAeInt*)mPreOutParam;
    } else {
        mPreResShared = new RkAiqAlgoPreResAeIntShared();
        if (!mPreResShared.ptr()) {
            LOGE("new ae mPreOutParam failed, bypass!");
            return XCAM_RETURN_BYPASS;
        }
        ae_pre_res_int = &mPreResShared->result;
    }

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;
    RkAiqPreResComb* comb                       = &shared->preResComb;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->ae_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ae handle preProcess failed");
    }

    RkAiqAecStats* xAecStats = nullptr;
    if (shared->aecStatsBuf) {
        xAecStats = (RkAiqAecStats*)shared->aecStatsBuf->map(shared->aecStatsBuf);
        if (!xAecStats) LOGE_AEC("aec stats is null");
    } else {
        LOGW_AEC("the xcamvideobuffer of aec stats is null");
    }
    if ((!xAecStats || !xAecStats->aec_stats_valid) && !sharedCom->init) {
        LOGW("no aec stats, ignore!");
        return XCAM_RETURN_BYPASS;
    }

    comb->ae_pre_res = NULL;

    ae_pre_int->aecStatsBuf = shared->aecStatsBuf;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    if (mAiqCore->mAlogsComSharedParams.init)
        ret = des->pre_process(mPreInParam, mPreOutParam);
    else
        ret = des->pre_process(mPreInParam, (RkAiqAlgoResCom*)ae_pre_res_int);
    RKAIQCORE_CHECK_RET(ret, "ae algo pre_process failed");

    // set result to mAiqCore
    comb->ae_pre_res = (RkAiqAlgoPreResAe*)ae_pre_res_int;

    if (!mAiqCore->mAlogsComSharedParams.init) {
        mPreResShared->set_sequence(shared->frameId);
        SmartPtr<XCamMessage> msg =
            new RkAiqCoreVdBufMsg(XCAM_MESSAGE_AE_PRE_RES_OK, shared->frameId, mPreResShared);
        mAiqCore->post_message(msg);
    }

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAeHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAeInt* ae_proc_int        = (RkAiqAlgoProcAeInt*)mProcInParam;
    RkAiqAlgoProcResAeInt* ae_proc_res_int = nullptr;
    if (mAiqCore->mAlogsComSharedParams.init) {
        ae_proc_res_int = (RkAiqAlgoProcResAeInt*)mProcOutParam;
    } else {
        mProcResShared = new RkAiqAlgoProcResAeIntShared();
        if (!mProcResShared.ptr()) {
            LOGE("new ae mProcOutParam failed, bypass!");
            return XCAM_RETURN_BYPASS;
        }
        ae_proc_res_int = &mProcResShared->result;
        // mProcOutParam = (RkAiqAlgoResCom*)ae_proc_res_int;
    }

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;
    AeInstanceConfig_t* pAeInstConfig           = (AeInstanceConfig_t*)mAlgoCtx;

    mLockAebyAfMutex.lock();
    pAeInstConfig->lockaebyaf = lockaebyaf;
    mLockAebyAfMutex.unlock();

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->ae_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ae handle processing failed");
    }

    comb->ae_proc_res = NULL;

    RkAiqAecStats* xAecStats = nullptr;
    if (shared->aecStatsBuf) {
        xAecStats = (RkAiqAecStats*)shared->aecStatsBuf->map(shared->aecStatsBuf);
        if (!xAecStats) LOGE_AEC("aec stats is null");
    } else {
        LOGW_AEC("the xcamvideobuffer of aec stats is null");
    }
    if ((!xAecStats || !xAecStats->aec_stats_valid) && !sharedCom->init) {
        LOGW("no aec stats, ignore!");
        return XCAM_RETURN_BYPASS;
    }

    // TODO config common ae processing params
    ae_proc_int->ae_proc_com.aecStatsBuf = shared->aecStatsBuf;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    if (mAiqCore->mAlogsComSharedParams.init)
        ret = des->processing(mProcInParam, mProcOutParam);
    else
        ret = des->processing(mProcInParam, (RkAiqAlgoResCom*)ae_proc_res_int);
    RKAIQCORE_CHECK_RET(ret, "ae algo processing failed");

    comb->ae_proc_res = (RkAiqAlgoProcResAe*)ae_proc_res_int;

    if (mAiqCore->mAlogsComSharedParams.init) {
        RkAiqCore::RkAiqAlgosGroupShared_t* measGroupshared = nullptr;
        if (mAiqCore->getGroupSharedParams(RK_AIQ_CORE_ANALYZE_MEAS, measGroupshared) !=
            XCAM_RETURN_NO_ERROR)
            LOGW("get the shared of meas failed");
        if (measGroupshared) {
            measGroupshared->frameId                 = shared->frameId;
            measGroupshared->preResComb.ae_pre_res   = shared->preResComb.ae_pre_res;
            measGroupshared->procResComb.ae_proc_res = shared->procResComb.ae_proc_res;
            measGroupshared->postResComb.ae_post_res = shared->postResComb.ae_post_res;
        }
    } else {
        mProcResShared->set_sequence(shared->frameId);
        SmartPtr<XCamMessage> msg =
            new RkAiqCoreVdBufMsg(XCAM_MESSAGE_AE_PROC_RES_OK, shared->frameId, mProcResShared);
        mAiqCore->post_message(msg);
    }

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAeInt* ae_post_int        = (RkAiqAlgoPostAeInt*)mPostInParam;
    RkAiqAlgoPostResAeInt* ae_post_res_int = (RkAiqAlgoPostResAeInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->ae_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ae handle postProcess failed");
        return ret;
    }

    comb->ae_post_res         = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "ae algo post_process failed");
    // set result to mAiqCore
    comb->ae_post_res = (RkAiqAlgoPostResAe*)ae_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAe* ae_proc                 = shared->procResComb.ae_proc_res;
    RkAiqAlgoPostResAe* ae_post                 = shared->postResComb.ae_post_res;
    if (!ae_proc) {
        LOGD_ANALYZER("no ae_proc result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!ae_post) {
        LOGD_ANALYZER("no ae_post result");
        return XCAM_RETURN_NO_ERROR;
    }

    rk_aiq_isp_aec_params_v20_t* aec_param   = params->mAecParams->data().ptr();
    rk_aiq_isp_hist_params_v20_t* hist_param = params->mHistParams->data().ptr();

    SmartPtr<rk_aiq_exposure_params_wrapper_t> exp_param = params->mExposureParams->data();
    SmartPtr<rk_aiq_iris_params_wrapper_t> iris_param    = params->mIrisParams->data();

    int algo_id = this->getAlgoId();

    exp_param->aecExpInfo.LinearExp = ae_proc->new_ae_exp.LinearExp;
    memcpy(exp_param->aecExpInfo.HdrExp, ae_proc->new_ae_exp.HdrExp,
           sizeof(ae_proc->new_ae_exp.HdrExp));
    exp_param->aecExpInfo.frame_length_lines   = ae_proc->new_ae_exp.frame_length_lines;
    exp_param->aecExpInfo.line_length_pixels   = ae_proc->new_ae_exp.line_length_pixels;
    exp_param->aecExpInfo.pixel_clock_freq_mhz = ae_proc->new_ae_exp.pixel_clock_freq_mhz;
    exp_param->aecExpInfo.Iris.PIris           = ae_proc->new_ae_exp.Iris.PIris;

    // TODO Merge
    // iris_param->IrisType = ae_proc->new_ae_exp.Iris.IrisType;
    iris_param->PIris.step   = ae_proc->new_ae_exp.Iris.PIris.step;
    iris_param->PIris.update = ae_proc->new_ae_exp.Iris.PIris.update;

#if 0
    isp_param->aec_meas = ae_proc->ae_meas;
    isp_param->hist_meas = ae_proc->hist_meas;
#else
    if (sharedCom->init) {
        aec_param->frame_id  = 0;
        hist_param->frame_id = 0;
        exp_param->frame_id  = 0;
    } else {
        aec_param->frame_id  = shared->frameId;
        hist_param->frame_id = shared->frameId;
        exp_param->frame_id  = shared->frameId;
    }

    aec_param->result  = ae_proc->ae_meas;
    hist_param->result = ae_proc->hist_meas;
#endif

    if (algo_id == 0) {
        RkAiqAlgoProcResAeInt* ae_rk = (RkAiqAlgoProcResAeInt*)ae_proc;
        memcpy(exp_param->exp_tbl, ae_rk->ae_proc_res_rk.exp_set_tbl, sizeof(exp_param->exp_tbl));
        exp_param->exp_tbl_size = ae_rk->ae_proc_res_rk.exp_set_cnt;
        exp_param->algo_id      = algo_id;

        RkAiqAlgoPostResAeInt* ae_post_rk = (RkAiqAlgoPostResAeInt*)ae_post;
        iris_param->DCIris.update         = ae_post_rk->ae_post_res_rk.DCIris.update;
        iris_param->DCIris.pwmDuty        = ae_post_rk->ae_post_res_rk.DCIris.pwmDuty;
    }

    cur_params->mExposureParams = params->mExposureParams;
    cur_params->mAecParams      = params->mAecParams;
    cur_params->mHistParams     = params->mHistParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
