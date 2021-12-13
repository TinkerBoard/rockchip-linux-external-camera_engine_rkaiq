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

void RkAiqAr2yHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAr2yInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAr2yInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAr2yInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAr2yInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAr2yInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAr2yInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAr2yInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAr2yHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "ar2y handle prepare failed");

    RkAiqAlgoConfigAr2yInt* ar2y_config_int = (RkAiqAlgoConfigAr2yInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "ar2y algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAr2yHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAr2yInt* ar2y_pre_int        = (RkAiqAlgoPreAr2yInt*)mPreInParam;
    RkAiqAlgoPreResAr2yInt* ar2y_pre_res_int = (RkAiqAlgoPreResAr2yInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->ar2y_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ar2y handle preProcess failed");
    }

    comb->ar2y_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "ar2y algo pre_process failed");

    // set result to mAiqCore
    comb->ar2y_pre_res = (RkAiqAlgoPreResAr2y*)ar2y_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAr2yHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAr2yInt* ar2y_proc_int        = (RkAiqAlgoProcAr2yInt*)mProcInParam;
    RkAiqAlgoProcResAr2yInt* ar2y_proc_res_int = (RkAiqAlgoProcResAr2yInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->ar2y_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ar2y handle processing failed");
    }

    comb->ar2y_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "ar2y algo processing failed");

    comb->ar2y_proc_res = (RkAiqAlgoProcResAr2y*)ar2y_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAr2yHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAr2yInt* ar2y_post_int        = (RkAiqAlgoPostAr2yInt*)mPostInParam;
    RkAiqAlgoPostResAr2yInt* ar2y_post_res_int = (RkAiqAlgoPostResAr2yInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->ar2y_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ar2y handle postProcess failed");
        return ret;
    }

    comb->ar2y_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "ar2y algo post_process failed");
    // set result to mAiqCore
    comb->ar2y_post_res = (RkAiqAlgoPostResAr2y*)ar2y_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

};  // namespace RkCam
