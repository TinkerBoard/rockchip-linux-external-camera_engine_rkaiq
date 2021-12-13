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

XCamReturn RkAiqAwdrHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "awdr handle prepare failed");

    RkAiqAlgoConfigAwdrInt* awdr_config_int = (RkAiqAlgoConfigAwdrInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "awdr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

void RkAiqAwdrHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAwdrInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAwdrInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAwdrInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAwdrInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAwdrInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAwdrInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAwdrInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAwdrHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAwdrInt* awdr_pre_int        = (RkAiqAlgoPreAwdrInt*)mPreInParam;
    RkAiqAlgoPreResAwdrInt* awdr_pre_res_int = (RkAiqAlgoPreResAwdrInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->awdr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "awdr handle preProcess failed");
    }

    comb->awdr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "awdr algo pre_process failed");

    // set result to mAiqCore
    comb->awdr_pre_res = (RkAiqAlgoPreResAwdr*)awdr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAwdrHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAwdrInt* awdr_proc_int        = (RkAiqAlgoProcAwdrInt*)mProcInParam;
    RkAiqAlgoProcResAwdrInt* awdr_proc_res_int = (RkAiqAlgoProcResAwdrInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->awdr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "awdr handle processing failed");
    }

    comb->awdr_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "awdr algo processing failed");

    comb->awdr_proc_res = (RkAiqAlgoProcResAwdr*)awdr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAwdrHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAwdrInt* awdr_post_int        = (RkAiqAlgoPostAwdrInt*)mPostInParam;
    RkAiqAlgoPostResAwdrInt* awdr_post_res_int = (RkAiqAlgoPostResAwdrInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->awdr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "awdr handle postProcess failed");
        return ret;
    }

    comb->awdr_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "awdr algo post_process failed");
    // set result to mAiqCore
    comb->awdr_post_res = (RkAiqAlgoPostResAwdr*)awdr_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAwdrHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAwdr* awdr_com = shared->procResComb.awdr_proc_res;
    rk_aiq_isp_wdr_params_v20_t* wdr_param = params->mWdrParams->data().ptr();

    if (sharedCom->init) {
        wdr_param->frame_id = 0;
    } else {
        wdr_param->frame_id = shared->frameId;
    }

    if (!awdr_com) {
        LOGD_ANALYZER("no awdr result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAwdrInt* awdr_rk = (RkAiqAlgoProcResAwdrInt*)awdr_com;
    }

    cur_params->mWdrParams = params->mWdrParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
