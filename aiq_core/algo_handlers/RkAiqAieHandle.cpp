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

XCamReturn RkAiqAieHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_aie_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }
    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAieHandleInt::setAttrib(aie_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore
    if (0 != memcmp(&mCurAtt, &att, sizeof(aie_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAieHandleInt::getAttrib(aie_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aie_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void RkAiqAieHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAieInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAieInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAieInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAieInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAieInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAieInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAieInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAieHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "aie handle prepare failed");

    RkAiqAlgoConfigAieInt* aie_config_int = (RkAiqAlgoConfigAieInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "aie algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAieHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAieInt* aie_pre_int        = (RkAiqAlgoPreAieInt*)mPreInParam;
    RkAiqAlgoPreResAieInt* aie_pre_res_int = (RkAiqAlgoPreResAieInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->aie_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aie handle preProcess failed");
    }

    comb->aie_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "aie algo pre_process failed");

    // set result to mAiqCore
    comb->aie_pre_res = (RkAiqAlgoPreResAie*)aie_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAieHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAieInt* aie_proc_int        = (RkAiqAlgoProcAieInt*)mProcInParam;
    RkAiqAlgoProcResAieInt* aie_proc_res_int = (RkAiqAlgoProcResAieInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->aie_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aie handle processing failed");
    }

    comb->aie_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aie algo processing failed");

    comb->aie_proc_res = (RkAiqAlgoProcResAie*)aie_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAieHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAieInt* aie_post_int        = (RkAiqAlgoPostAieInt*)mPostInParam;
    RkAiqAlgoPostResAieInt* aie_post_res_int = (RkAiqAlgoPostResAieInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->aie_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aie handle postProcess failed");
        return ret;
    }

    comb->aie_post_res        = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "aie algo post_process failed");
    // set result to mAiqCore
    comb->aie_post_res = (RkAiqAlgoPostResAie*)aie_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAieHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAie* aie_com = shared->procResComb.aie_proc_res;

    rk_aiq_isp_ie_params_v20_t* ie_param = params->mIeParams->data().ptr();
    if (sharedCom->init) {
        ie_param->frame_id = 0;
    } else {
        ie_param->frame_id = shared->frameId;
    }

    if (!aie_com) {
        LOGD_ANALYZER("no aie result");
        return XCAM_RETURN_NO_ERROR;
    }

    rk_aiq_isp_ie_t* isp_ie = &ie_param->result;
    isp_ie->base            = aie_com->params;

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAieInt* aie_rk = (RkAiqAlgoProcResAieInt*)aie_com;
        isp_ie->extra = aie_rk->params;
    }

    cur_params->mIeParams = params->mIeParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
