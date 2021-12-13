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

void RkAiqAmergeHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAmergeInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAmergeInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAmergeInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAmergeInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAmergeInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAmergeInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAmergeInt());

    EXIT_ANALYZER_FUNCTION();
}
XCamReturn RkAiqAmergeHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_amerge_SetAttrib(mAlgoCtx, mCurAtt, true);
        sendSignal();
    }
    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmergeHandleInt::setAttrib(amerge_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(amerge_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn RkAiqAmergeHandleInt::getAttrib(amerge_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_amerge_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmergeHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "amerge handle prepare failed");

    RkAiqAlgoConfigAmergeInt* amerge_config_int = (RkAiqAlgoConfigAmergeInt*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    // TODO
    amerge_config_int->rawHeight    = sharedCom->snsDes.isp_acq_height;
    amerge_config_int->rawWidth     = sharedCom->snsDes.isp_acq_width;
    amerge_config_int->working_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "amerge algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAmergeHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAmergeInt* amerge_pre_int        = (RkAiqAlgoPreAmergeInt*)mPreInParam;
    RkAiqAlgoPreResAmergeInt* amerge_pre_res_int = (RkAiqAlgoPreResAmergeInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqIspStats* ispStats                     = shared->ispStats;
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->amerge_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "amerge handle preProcess failed");
    }

    comb->amerge_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "amerge algo pre_process failed");

    // set result to mAiqCore
    comb->amerge_pre_res = (RkAiqAlgoPreResAmerge*)amerge_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAmergeHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAmergeInt* amerge_proc_int        = (RkAiqAlgoProcAmergeInt*)mProcInParam;
    RkAiqAlgoProcResAmergeInt* amerge_proc_res_int = (RkAiqAlgoProcResAmergeInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqIspStats* ispStats                     = shared->ispStats;
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->amerge_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "amerge handle processing failed");
    }

    comb->amerge_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "amerge algo processing failed");

    comb->amerge_proc_res = (RkAiqAlgoProcResAmerge*)amerge_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmergeHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAmergeInt* amerge_post_int        = (RkAiqAlgoPostAmergeInt*)mPostInParam;
    RkAiqAlgoPostResAmergeInt* amerge_post_res_int = (RkAiqAlgoPostResAmergeInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqIspStats* ispStats                     = shared->ispStats;
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->amerge_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "amerge handle postProcess failed");
        return ret;
    }

    comb->amerge_post_res     = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "amerge algo post_process failed");
    // set result to mAiqCore
    comb->amerge_post_res = (RkAiqAlgoPostResAmerge*)amerge_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmergeHandleInt::genIspResult(RkAiqFullParams* params,
                                              RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAmerge* amerge_com          = shared->procResComb.amerge_proc_res;

    rk_aiq_isp_merge_params_v20_t* merge_param = params->mMergeParams->data().ptr();

    if (!amerge_com) {
        LOGD_ANALYZER("no amerge result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAmergeInt* amerge_rk = (RkAiqAlgoProcResAmergeInt*)amerge_com;

        if (sharedCom->init) {
            merge_param->frame_id = 0;
        } else {
            merge_param->frame_id = shared->frameId;
        }

        merge_param->result = amerge_rk->AmergeProcRes;
    }

    cur_params->mMergeParams = params->mMergeParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
