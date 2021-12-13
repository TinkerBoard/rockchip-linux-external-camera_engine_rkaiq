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

void RkAiqAcpHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAcpInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAcpInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAcpInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAcpInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAcpInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAcpInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAcpInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAcpHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_acp_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }
    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcpHandleInt::setAttrib(acp_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore
    if (0 != memcmp(&mCurAtt, &att, sizeof(acp_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcpHandleInt::getAttrib(acp_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_acp_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcpHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "acp handle prepare failed");

    RkAiqAlgoConfigAcpInt* acp_config_int = (RkAiqAlgoConfigAcpInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "acp algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAcpHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAcpInt* acp_pre_int        = (RkAiqAlgoPreAcpInt*)mPreInParam;
    RkAiqAlgoPreResAcpInt* acp_pre_res_int = (RkAiqAlgoPreResAcpInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->acp_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acp handle preProcess failed");
    }

    comb->acp_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "acp algo pre_process failed");

    // set result to mAiqCore
    comb->acp_pre_res = (RkAiqAlgoPreResAcp*)acp_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAcpHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAcpInt* acp_proc_int        = (RkAiqAlgoProcAcpInt*)mProcInParam;
    RkAiqAlgoProcResAcpInt* acp_proc_res_int = (RkAiqAlgoProcResAcpInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->acp_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acp handle processing failed");
    }

    comb->acp_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "acp algo processing failed");

    comb->acp_proc_res = (RkAiqAlgoProcResAcp*)acp_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcpHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAcpInt* acp_post_int        = (RkAiqAlgoPostAcpInt*)mPostInParam;
    RkAiqAlgoPostResAcpInt* acp_post_res_int = (RkAiqAlgoPostResAcpInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->acp_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acp handle postProcess failed");
        return ret;
    }

    comb->acp_post_res        = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "acp algo post_process failed");
    // set result to mAiqCore
    comb->acp_post_res = (RkAiqAlgoPostResAcp*)acp_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcpHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAcp* acp_com = shared->procResComb.acp_proc_res;
    rk_aiq_isp_cp_params_v20_t* cp_param = params->mCpParams->data().ptr();

    if (sharedCom->init) {
        cp_param->frame_id = 0;
    } else {
        cp_param->frame_id = shared->frameId;
    }

    if (!acp_com) {
        LOGD_ANALYZER("no acp result");
        return XCAM_RETURN_NO_ERROR;
    }

    rk_aiq_acp_params_t* isp_cp = &cp_param->result;

    *isp_cp = acp_com->acp_res;

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAcpInt* acp_rk = (RkAiqAlgoProcResAcpInt*)acp_com;
    }

    cur_params->mCpParams = params->mCpParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam

