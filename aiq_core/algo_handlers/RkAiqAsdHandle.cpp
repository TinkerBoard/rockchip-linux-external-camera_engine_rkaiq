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

void RkAiqAsdHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAsdInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAsdInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAsdInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAsdInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAsdInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAsdInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAsdInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAsdHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_asd_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsdHandleInt::setAttrib(asd_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(asd_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsdHandleInt::getAttrib(asd_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_asd_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsdHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "asd handle prepare failed");

    RkAiqAlgoConfigAsdInt* asd_config_int = (RkAiqAlgoConfigAsdInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "asd algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAsdHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAsdInt* asd_pre_int        = (RkAiqAlgoPreAsdInt*)mPreInParam;
    RkAiqAlgoPreResAsdInt* asd_pre_res_int = (RkAiqAlgoPreResAsdInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->asd_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asd handle preProcess failed");
    }

    comb->asd_pre_res                        = NULL;
    asd_pre_int->pre_params.cpsl_mode        = sharedCom->cpslCfg.mode;
    asd_pre_int->pre_params.cpsl_on          = sharedCom->cpslCfg.u.m.on;
    asd_pre_int->pre_params.cpsl_sensitivity = sharedCom->cpslCfg.u.a.sensitivity;
    asd_pre_int->pre_params.cpsl_sw_interval = sharedCom->cpslCfg.u.a.sw_interval;
    RkAiqAlgoDescription* des                = (RkAiqAlgoDescription*)mDes;
    ret                                      = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "asd algo pre_process failed");

    // set result to mAiqCore
    comb->asd_pre_res = (RkAiqAlgoPreResAsd*)asd_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAsdHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAsdInt* asd_proc_int        = (RkAiqAlgoProcAsdInt*)mProcInParam;
    RkAiqAlgoProcResAsdInt* asd_proc_res_int = (RkAiqAlgoProcResAsdInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->asd_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asd handle processing failed");
    }

    comb->asd_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "asd algo processing failed");

    comb->asd_proc_res = (RkAiqAlgoProcResAsd*)asd_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsdHandleInt::postProcess() {
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

#if 0
XCamReturn RkAiqAsdHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAsd* asd_com                = shared->procResComb.asd_proc_res;

    if (!asd_com) {
        LOGD_ANALYZER("no asd result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAsdInt* asd_rk = (RkAiqAlgoProcResAsdInt*)asd_com;

#if 0  // flash test
        RkAiqAlgoPreResAsdInt* asd_pre_rk = (RkAiqAlgoPreResAsdInt*)shared->preResComb.asd_pre_res;
        if (asd_pre_rk->asd_result.fl_on) {
            fl_param->flash_mode = RK_AIQ_FLASH_MODE_TORCH;
            fl_param->power[0] = 1000;
            fl_param->strobe = true;
        } else {
            fl_param->flash_mode = RK_AIQ_FLASH_MODE_OFF;
            fl_param->power[0] = 0;
            fl_param->strobe = false;
        }
#endif
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}
#endif

};  // namespace RkCam
