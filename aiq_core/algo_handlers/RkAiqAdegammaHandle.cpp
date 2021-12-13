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

void RkAiqAdegammaHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAdegammaInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAdegammaInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAdegammaInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAdegammaInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAdegammaInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAdegammaInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAdegammaInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAdegammaHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_adegamma_SetAttrib(mAlgoCtx, mCurAtt, false);
        waitSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdegammaHandleInt::setAttrib(rk_aiq_degamma_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(rk_aiq_degamma_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        sendSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdegammaHandleInt::getAttrib(rk_aiq_degamma_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_adegamma_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdegammaHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "adegamma handle prepare failed");

    RkAiqAlgoConfigAdegammaInt* adegamma_config_int = (RkAiqAlgoConfigAdegammaInt*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom     = &mAiqCore->mAlogsComSharedParams;

    adegamma_config_int->calib = sharedCom->calib;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "adegamma algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAdegammaHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAdegammaInt* adegamma_pre_int        = (RkAiqAlgoPreAdegammaInt*)mPreInParam;
    RkAiqAlgoPreResAdegammaInt* adegamma_pre_res_int = (RkAiqAlgoPreResAdegammaInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->adegamma_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adegamma handle preProcess failed");
    }

    comb->adegamma_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "adegamma algo pre_process failed");

    // set result to mAiqCore
    comb->adegamma_pre_res = (RkAiqAlgoPreResAdegamma*)adegamma_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAdegammaHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAdegammaInt* adegamma_proc_int = (RkAiqAlgoProcAdegammaInt*)mProcInParam;
    RkAiqAlgoProcResAdegammaInt* adegamma_proc_res_int =
        (RkAiqAlgoProcResAdegammaInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->adegamma_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adegamma handle processing failed");
    }

    comb->adegamma_proc_res  = NULL;
    adegamma_proc_int->calib = sharedCom->calib;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "adegamma algo processing failed");

    comb->adegamma_proc_res = (RkAiqAlgoProcResAdegamma*)adegamma_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdegammaHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAdegammaInt* adegamma_post_int = (RkAiqAlgoPostAdegammaInt*)mPostInParam;
    RkAiqAlgoPostResAdegammaInt* adegamma_post_res_int =
        (RkAiqAlgoPostResAdegammaInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->adegamma_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adegamma handle postProcess failed");
        return ret;
    }

    comb->adegamma_post_res   = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "agamma algo post_process failed");
    // set result to mAiqCore
    comb->adegamma_post_res = (RkAiqAlgoPostResAdegamma*)adegamma_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdegammaHandleInt::genIspResult(RkAiqFullParams* params,
                                                RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom     = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAdegamma* adegamma_com          = shared->procResComb.adegamma_proc_res;
    rk_aiq_isp_adegamma_params_v20_t* degamma_param = params->mAdegammaParams->data().ptr();

    if (!adegamma_com) {
        LOGD_ANALYZER("no adegamma result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAdegammaInt* adegamma_rk = (RkAiqAlgoProcResAdegammaInt*)adegamma_com;
        if (sharedCom->init) {
            degamma_param->frame_id = 0;
        } else {
            degamma_param->frame_id = shared->frameId;
        }

        degamma_param->result.degamma_en   = adegamma_rk->adegamma_proc_res.degamma_en;
        degamma_param->result.degamma_X_d0 = adegamma_rk->adegamma_proc_res.degamma_X_d0;
        degamma_param->result.degamma_X_d1 = adegamma_rk->adegamma_proc_res.degamma_X_d1;
        for (int i = 0; i < DEGAMMA_CRUVE_Y_KNOTS; i++) {
            degamma_param->result.degamma_tableR[i] =
                adegamma_rk->adegamma_proc_res.degamma_tableR[i];
            degamma_param->result.degamma_tableG[i] =
                adegamma_rk->adegamma_proc_res.degamma_tableG[i];
            degamma_param->result.degamma_tableB[i] =
                adegamma_rk->adegamma_proc_res.degamma_tableB[i];
        }
    }

    cur_params->mAdegammaParams = params->mAdegammaParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
