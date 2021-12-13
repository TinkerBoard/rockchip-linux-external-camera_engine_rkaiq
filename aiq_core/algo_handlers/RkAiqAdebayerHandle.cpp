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

void RkAiqAdebayerHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAdebayerInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAdebayerInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAdebayerInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAdebayerInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAdebayerInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAdebayerInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAdebayerInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAdebayerHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_adebayer_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }
    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdebayerHandleInt::setAttrib(adebayer_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore
    if (0 != memcmp(&mCurAtt, &att, sizeof(adebayer_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdebayerHandleInt::getAttrib(adebayer_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_adebayer_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdebayerHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "adebayer handle prepare failed");

    RkAiqAlgoConfigAdebayerInt* adebayer_config_int = (RkAiqAlgoConfigAdebayerInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "adebayer algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAdebayerHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAdebayerInt* adebayer_pre_int        = (RkAiqAlgoPreAdebayerInt*)mPreInParam;
    RkAiqAlgoPreResAdebayerInt* adebayer_pre_res_int = (RkAiqAlgoPreResAdebayerInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->adebayer_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adebayer handle preProcess failed");
    }

    comb->adebayer_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "adebayer algo pre_process failed");

    // set result to mAiqCore
    comb->adebayer_pre_res = (RkAiqAlgoPreResAdebayer*)adebayer_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAdebayerHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAdebayerInt* adebayer_proc_int = (RkAiqAlgoProcAdebayerInt*)mProcInParam;
    RkAiqAlgoProcResAdebayerInt* adebayer_proc_res_int =
        (RkAiqAlgoProcResAdebayerInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->adebayer_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adebayer handle processing failed");
    }

    comb->adebayer_proc_res = NULL;
    // TODO: fill procParam
    adebayer_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "adebayer algo processing failed");

    comb->adebayer_proc_res = (RkAiqAlgoProcResAdebayer*)adebayer_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdebayerHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAdebayerInt* adebayer_post_int = (RkAiqAlgoPostAdebayerInt*)mPostInParam;
    RkAiqAlgoPostResAdebayerInt* adebayer_post_res_int =
        (RkAiqAlgoPostResAdebayerInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->adebayer_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adebayer handle postProcess failed");
        return ret;
    }

    comb->adebayer_post_res   = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "adebayer algo post_process failed");
    // set result to mAiqCore
    comb->adebayer_post_res = (RkAiqAlgoPostResAdebayer*)adebayer_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdebayerHandleInt::genIspResult(RkAiqFullParams* params,
                                                RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAdebayer* adebayer_com = shared->procResComb.adebayer_proc_res;
    rk_aiq_isp_debayer_params_v20_t* debayer_param = params->mDebayerParams->data().ptr();

    if (!adebayer_com) {
        LOGD_ANALYZER("no adebayer result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAdebayerInt* adebayer_rk = (RkAiqAlgoProcResAdebayerInt*)adebayer_com;
        if (sharedCom->init) {
            debayer_param->frame_id = 0;
        } else {
            debayer_param->frame_id = shared->frameId;
        }
        memcpy(&debayer_param->result, &adebayer_rk->debayerRes.config, sizeof(AdebayerConfig_t));
    }

    cur_params->mDebayerParams = params->mDebayerParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
