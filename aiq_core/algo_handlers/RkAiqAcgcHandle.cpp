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

void RkAiqAcgcHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAcgcInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAcgcInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAcgcInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAcgcInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAcgcInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAcgcInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAcgcInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAcgcHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "acgc handle prepare failed");

    RkAiqAlgoConfigAcgcInt* acgc_config_int = (RkAiqAlgoConfigAcgcInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "acgc algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAcgcHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAcgcInt* acgc_pre_int        = (RkAiqAlgoPreAcgcInt*)mPreInParam;
    RkAiqAlgoPreResAcgcInt* acgc_pre_res_int = (RkAiqAlgoPreResAcgcInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->acgc_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acgc handle preProcess failed");
    }

    comb->acgc_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "acgc algo pre_process failed");

    // set result to mAiqCore
    comb->acgc_pre_res = (RkAiqAlgoPreResAcgc*)acgc_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAcgcHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAcgcInt* acgc_proc_int        = (RkAiqAlgoProcAcgcInt*)mProcInParam;
    RkAiqAlgoProcResAcgcInt* acgc_proc_res_int = (RkAiqAlgoProcResAcgcInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->acgc_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acgc handle processing failed");
    }

    comb->acgc_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "acgc algo processing failed");

    comb->acgc_proc_res = (RkAiqAlgoProcResAcgc*)acgc_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcgcHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAcgcInt* acgc_post_int        = (RkAiqAlgoPostAcgcInt*)mPostInParam;
    RkAiqAlgoPostResAcgcInt* acgc_post_res_int = (RkAiqAlgoPostResAcgcInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->acgc_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acgc handle postProcess failed");
        return ret;
    }

    comb->acgc_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "acgc algo post_process failed");
    // set result to mAiqCore
    comb->acgc_post_res = (RkAiqAlgoPostResAcgc*)acgc_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcgcHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAcgc* acgc_com              = shared->procResComb.acgc_proc_res;
    rk_aiq_isp_cgc_params_v20_t* cgc_param      = params->mCgcParams->data().ptr();

    if (sharedCom->init) {
        cgc_param->frame_id = 0;
    } else {
        cgc_param->frame_id = shared->frameId;
    }

    if (!acgc_com) {
        LOGD_ANALYZER("no acgc result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAcgcInt* acgc_rk = (RkAiqAlgoProcResAcgcInt*)acgc_com;
    }

    cur_params->mCgcParams = params->mCgcParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
