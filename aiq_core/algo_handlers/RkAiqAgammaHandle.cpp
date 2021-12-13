/*
 * Copyright (c) 2019-2021 Rockchip Eletronics Co., Ltd.
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
 */
#include "RkAiqCore.h"
#include "RkAiqHandle.h"
#include "RkAiqHandleInt.h"

namespace RkCam {

void RkAiqAgammaHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAgammaInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAgammaInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAgammaInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAgammaInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAgammaInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAgammaInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAgammaInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAgammaHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_agamma_SetAttrib(mAlgoCtx, mCurAtt, false);
        waitSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgammaHandleInt::setAttrib(rk_aiq_gamma_attrib_V2_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(rk_aiq_gamma_attrib_V2_t))) {
        mNewAtt   = att;
        updateAtt = true;
        sendSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgammaHandleInt::getAttrib(rk_aiq_gamma_attrib_V2_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_agamma_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgammaHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "agamma handle prepare failed");

    RkAiqAlgoConfigAgammaInt* agamma_config_int = (RkAiqAlgoConfigAgammaInt*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqIspStats* ispStats = shared->ispStats;

    agamma_config_int->calib = sharedCom->calib;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "agamma algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAgammaHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAgammaInt* agamma_pre_int        = (RkAiqAlgoPreAgammaInt*)mPreInParam;
    RkAiqAlgoPreResAgammaInt* agamma_pre_res_int = (RkAiqAlgoPreResAgammaInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->agamma_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agamma handle preProcess failed");
    }

    comb->agamma_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "agamma algo pre_process failed");

    // set result to mAiqCore
    comb->agamma_pre_res = (RkAiqAlgoPreResAgamma*)agamma_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAgammaHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAgammaInt* agamma_proc_int        = (RkAiqAlgoProcAgammaInt*)mProcInParam;
    RkAiqAlgoProcResAgammaInt* agamma_proc_res_int = (RkAiqAlgoProcResAgammaInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->agamma_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agamma handle processing failed");
    }

    comb->agamma_proc_res  = NULL;
    agamma_proc_int->calib = sharedCom->calib;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "agamma algo processing failed");

    comb->agamma_proc_res = (RkAiqAlgoProcResAgamma*)agamma_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgammaHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAgammaInt* agamma_post_int        = (RkAiqAlgoPostAgammaInt*)mPostInParam;
    RkAiqAlgoPostResAgammaInt* agamma_post_res_int = (RkAiqAlgoPostResAgammaInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->agamma_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agamma handle postProcess failed");
        return ret;
    }

    comb->agamma_post_res     = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "agamma algo post_process failed");
    // set result to mAiqCore
    comb->agamma_post_res = (RkAiqAlgoPostResAgamma*)agamma_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgammaHandleInt::genIspResult(RkAiqFullParams* params,
                                              RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAgamma* agamma_com = shared->procResComb.agamma_proc_res;
    rk_aiq_isp_agamma_params_v20_t* agamma_param = params->mAgammaParams->data().ptr();

    if (!agamma_com) {
        LOGD_ANALYZER("no agamma result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAgammaInt* agamma_int = (RkAiqAlgoProcResAgammaInt*)agamma_com;
        if (sharedCom->init) {
            agamma_param->frame_id = 0;
        } else {
            agamma_param->frame_id = shared->frameId;
        }

        agamma_param->result = agamma_int->GammaProcRes;
    }

    cur_params->mAgammaParams = params->mAgammaParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
