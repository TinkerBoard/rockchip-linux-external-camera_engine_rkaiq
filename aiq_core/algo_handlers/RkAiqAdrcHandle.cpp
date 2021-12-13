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

XCamReturn RkAiqAdrcHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "adrc handle prepare failed");

    RkAiqAlgoConfigAdrcInt* adrc_config_int     = (RkAiqAlgoConfigAdrcInt*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    adrc_config_int->rawHeight    = sharedCom->snsDes.isp_acq_height;
    adrc_config_int->rawWidth     = sharedCom->snsDes.isp_acq_width;
    adrc_config_int->working_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "adrc algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

void RkAiqAdrcHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAdrcInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAdrcInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAdrcInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAdrcInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAdrcInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAdrcInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAdrcInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAdrcHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_adrc_SetAttrib(mAlgoCtx, mCurAtt, true);
        sendSignal();
    }
    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdrcHandleInt::setAttrib(drc_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(drc_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}
XCamReturn RkAiqAdrcHandleInt::getAttrib(drc_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_adrc_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdrcHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAdrcInt* adrc_pre_int        = (RkAiqAlgoPreAdrcInt*)mPreInParam;
    RkAiqAlgoPreResAdrcInt* adrc_pre_res_int = (RkAiqAlgoPreResAdrcInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->adrc_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adrc handle preProcess failed");
    }

    comb->adrc_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "adrc algo pre_process failed");

    // set result to mAiqCore
    comb->adrc_pre_res = (RkAiqAlgoPreResAdrc*)adrc_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAdrcHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAdrcInt* adrc_proc_int        = (RkAiqAlgoProcAdrcInt*)mProcInParam;
    RkAiqAlgoProcResAdrcInt* adrc_proc_res_int = (RkAiqAlgoProcResAdrcInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->adrc_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adrc handle processing failed");
    }

    comb->adrc_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "adrc algo processing failed");

    comb->adrc_proc_res = (RkAiqAlgoProcResAdrc*)adrc_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdrcHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAdrcInt* adrc_post_int        = (RkAiqAlgoPostAdrcInt*)mPostInParam;
    RkAiqAlgoPostResAdrcInt* adrc_post_res_int = (RkAiqAlgoPostResAdrcInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->adrc_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adrc handle postProcess failed");
        return ret;
    }

    comb->adrc_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "adrc algo post_process failed");
    // set result to mAiqCore
    comb->adrc_post_res = (RkAiqAlgoPostResAdrc*)adrc_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdrcHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAdrc* adrc_com = shared->procResComb.adrc_proc_res;

    if (!adrc_com) {
        LOGD_ANALYZER("no adrc result");
        return XCAM_RETURN_NO_ERROR;
    }

    RkAiqAlgoProcResAdrc* adrc_rk = (RkAiqAlgoProcResAdrc*)adrc_com;
    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAdrcInt* ahdr_rk = (RkAiqAlgoProcResAdrcInt*)adrc_com;

        rk_aiq_isp_drc_params_v21_t* drc_param = params->mDrcParams->data().ptr();
        if (sharedCom->init) {
            drc_param->frame_id = 0;
        } else {
            drc_param->frame_id = shared->frameId;
        }
        drc_param->result.DrcProcRes = ahdr_rk->AdrcProcRes.DrcProcRes;

        drc_param->result.CompressMode = ahdr_rk->AdrcProcRes.CompressMode;
        drc_param->result.update = ahdr_rk->AdrcProcRes.update;
        drc_param->result.LongFrameMode = ahdr_rk->AdrcProcRes.LongFrameMode;
        drc_param->result.isHdrGlobalTmo = ahdr_rk->AdrcProcRes.isHdrGlobalTmo;
        drc_param->result.bTmoEn = ahdr_rk->AdrcProcRes.bTmoEn;
        drc_param->result.isLinearTmo = ahdr_rk->AdrcProcRes.isLinearTmo;
    }

    cur_params->mDrcParams = params->mDrcParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;

}

};  // namespace RkCam
