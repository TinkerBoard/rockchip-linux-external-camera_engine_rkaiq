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

void RkAiqAblcHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAblcInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAblcInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAblcInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAblcInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAblcInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAblcInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAblcInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAblcHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_ablc_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAblcHandleInt::setAttrib(rk_aiq_blc_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_blc_attrib_t))) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAblcHandleInt::getAttrib(rk_aiq_blc_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_ablc_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAblcHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "ablc handle prepare failed");

    RkAiqAlgoConfigAblcInt* ablc_config_int = (RkAiqAlgoConfigAblcInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "ablc algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAblcHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAblcInt* ablc_pre_int        = (RkAiqAlgoPreAblcInt*)mPreInParam;
    RkAiqAlgoPreResAblcInt* ablc_pre_res_int = (RkAiqAlgoPreResAblcInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->ablc_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ablc handle preProcess failed");
    }

    comb->ablc_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "ablc algo pre_process failed");

    // set result to mAiqCore
    comb->ablc_pre_res = (RkAiqAlgoPreResAblc*)ablc_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAblcHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAblcInt* ablc_proc_int        = (RkAiqAlgoProcAblcInt*)mProcInParam;
    RkAiqAlgoProcResAblcInt* ablc_proc_res_int = (RkAiqAlgoProcResAblcInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->ablc_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ablc handle processing failed");
    }

    comb->ablc_proc_res     = NULL;
    ablc_proc_int->iso      = sharedCom->iso;
    ablc_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "ablc algo processing failed");

    comb->ablc_proc_res = (RkAiqAlgoProcResAblc*)ablc_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAblcHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAblcInt* ablc_post_int        = (RkAiqAlgoPostAblcInt*)mPostInParam;
    RkAiqAlgoPostResAblcInt* ablc_post_res_int = (RkAiqAlgoPostResAblcInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->ablc_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "ablc handle postProcess failed");
        return ret;
    }

    comb->ablc_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "ablc algo post_process failed");
    // set result to mAiqCore
    comb->ablc_post_res = (RkAiqAlgoPostResAblc*)ablc_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAblcHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAblc* ablc_com              = shared->procResComb.ablc_proc_res;
#if defined(ISP_HW_V21) || defined(ISP_HW_V30)
    rk_aiq_isp_blc_params_v21_t* blc_param = params->mBlcV21Params->data().ptr();
#else
    rk_aiq_isp_blc_params_v20_t* blc_param = params->mBlcParams->data().ptr();
#endif

    if (!ablc_com) {
        LOGD_ANALYZER("no ablc result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAblcInt* ablc_rk = (RkAiqAlgoProcResAblcInt*)ablc_com;

        if (sharedCom->init) {
            blc_param->frame_id = 0;
        } else {
            blc_param->frame_id = shared->frameId;
        }

#if defined(ISP_HW_V21) || defined(ISP_HW_V30)
        memcpy(&blc_param->result.v0, &ablc_rk->ablc_proc_res, sizeof(rk_aiq_isp_blc_t));
#else
        memcpy(&blc_param->result, &ablc_rk->ablc_proc_res, sizeof(rk_aiq_isp_blc_t));
#endif
    }

#if defined(ISP_HW_V21) || defined(ISP_HW_V30)
    cur_params->mBlcV21Params = params->mBlcV21Params;
#else
    cur_params->mBlcParams = params->mBlcParams;
#endif

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
