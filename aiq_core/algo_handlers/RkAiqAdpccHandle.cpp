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

void RkAiqAdpccHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAdpccInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAdpccInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAdpccInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAdpccInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAdpccInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAdpccInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAdpccInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAdpccHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_adpcc_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdpccHandleInt::setAttrib(rk_aiq_dpcc_attrib_V20_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_dpcc_attrib_V20_t))) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdpccHandleInt::getAttrib(rk_aiq_dpcc_attrib_V20_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_adpcc_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdpccHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "adpcc handle prepare failed");

    RkAiqAlgoConfigAdpccInt* adpcc_config_int = (RkAiqAlgoConfigAdpccInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "adpcc algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAdpccHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAdpccInt* adpcc_pre_int        = (RkAiqAlgoPreAdpccInt*)mPreInParam;
    RkAiqAlgoPreResAdpccInt* adpcc_pre_res_int = (RkAiqAlgoPreResAdpccInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->adpcc_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adpcc handle preProcess failed");
    }

    comb->adpcc_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "adpcc algo pre_process failed");

    // set result to mAiqCore
    comb->adpcc_pre_res = (RkAiqAlgoPreResAdpcc*)adpcc_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAdpccHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAdpccInt* adpcc_proc_int        = (RkAiqAlgoProcAdpccInt*)mProcInParam;
    RkAiqAlgoProcResAdpccInt* adpcc_proc_res_int = (RkAiqAlgoProcResAdpccInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->adpcc_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adpcc handle processing failed");
    }

    comb->adpcc_proc_res = NULL;
    // TODO: fill procParam
    adpcc_proc_int->iso      = sharedCom->iso;
    adpcc_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "adpcc algo processing failed");

    comb->adpcc_proc_res = (RkAiqAlgoProcResAdpcc*)adpcc_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdpccHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAsdInt* asd_post_int        = (RkAiqAlgoPostAsdInt*)mPostInParam;
    RkAiqAlgoPostResAsdInt* asd_post_res_int = (RkAiqAlgoPostResAsdInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->asd_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asd handle postProcess failed");
        return ret;
    }

    comb->asd_post_res        = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "asd algo post_process failed");
    // set result to mAiqCore
    comb->asd_post_res = (RkAiqAlgoPostResAsd*)asd_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdpccHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAdpcc* adpcc_com            = shared->procResComb.adpcc_proc_res;
    rk_aiq_isp_dpcc_params_v20_t* dpcc_param    = params->mDpccParams->data().ptr();

    if (!adpcc_com) {
        LOGD_ANALYZER("no adpcc result");
        return XCAM_RETURN_NO_ERROR;
    }

#if 0
    // gen rk adpcc result
    exp_param->SensorDpccInfo.enable = adpcc_com->SenDpccRes.enable;
    exp_param->SensorDpccInfo.cur_single_dpcc = adpcc_com->SenDpccRes.cur_single_dpcc;
    exp_param->SensorDpccInfo.cur_multiple_dpcc = adpcc_com->SenDpccRes.cur_multiple_dpcc;
    exp_param->SensorDpccInfo.total_dpcc = adpcc_com->SenDpccRes.total_dpcc;
#endif

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAdpccInt* adpcc_rk = (RkAiqAlgoProcResAdpccInt*)adpcc_com;

        if (sharedCom->init) {
            dpcc_param->frame_id = 0;
        } else {
            dpcc_param->frame_id = shared->frameId;
        }
        memcpy(&dpcc_param->result, &adpcc_rk->stAdpccProcResult, sizeof(rk_aiq_isp_dpcc_t));
    }

    cur_params->mDpccParams = params->mDpccParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
