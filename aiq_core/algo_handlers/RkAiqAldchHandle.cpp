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

void RkAiqAldchHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAldchInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAldchInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAldchInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAldchInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAldchInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAldchInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAldchInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAldchHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "aldch handle prepare failed");

    RkAiqAlgoConfigAldchInt* aldch_config_int   = (RkAiqAlgoConfigAldchInt*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    // memcpy(&aldch_config_int->aldch_calib_cfg, &shared->calib->aldch, sizeof(CalibDb_LDCH_t));
    aldch_config_int->resource_path = sharedCom->resourcePath;
    aldch_config_int->mem_ops_ptr   = mAiqCore->mShareMemOps;
    RkAiqAlgoDescription* des       = (RkAiqAlgoDescription*)mDes;
    ret                             = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "aldch algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAldchHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAldchInt* aldch_pre_int        = (RkAiqAlgoPreAldchInt*)mPreInParam;
    RkAiqAlgoPreResAldchInt* aldch_pre_res_int = (RkAiqAlgoPreResAldchInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->aldch_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aldch handle preProcess failed");
    }

    comb->aldch_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "aldch algo pre_process failed");

    // set result to mAiqCore
    comb->aldch_pre_res = (RkAiqAlgoPreResAldch*)aldch_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAldchHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAldchInt* aldch_proc_int        = (RkAiqAlgoProcAldchInt*)mProcInParam;
    RkAiqAlgoProcResAldchInt* aldch_proc_res_int = (RkAiqAlgoProcResAldchInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->aldch_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aldch handle processing failed");
    }

    comb->aldch_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aldch algo processing failed");

    comb->aldch_proc_res = (RkAiqAlgoProcResAldch*)aldch_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAldchHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAldchInt* aldch_post_int        = (RkAiqAlgoPostAldchInt*)mPostInParam;
    RkAiqAlgoPostResAldchInt* aldch_post_res_int = (RkAiqAlgoPostResAldchInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->aldch_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aldch handle postProcess failed");
        return ret;
    }

    comb->aldch_post_res      = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "aldch algo post_process failed");
    // set result to mAiqCore
    comb->aldch_post_res = (RkAiqAlgoPostResAldch*)aldch_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAldchHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_aldch_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAldchHandleInt::setAttrib(rk_aiq_ldch_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be efldchtive later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(rk_aiq_ldch_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAldchHandleInt::getAttrib(rk_aiq_ldch_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aldch_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAldchHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAldch* aldch_com         = shared->procResComb.aldch_proc_res;
    rk_aiq_isp_ldch_params_v20_t* ldch_param = params->mLdchParams->data().ptr();

    if (!aldch_com) {
        LOGD_ANALYZER("no aldch result");
        return XCAM_RETURN_NO_ERROR;
    }

    RkAiqAlgoProcResAldchInt* aldch_rk = (RkAiqAlgoProcResAldchInt*)aldch_com;

    if (sharedCom->init) {
        ldch_param->frame_id = 0;
    } else {
        ldch_param->frame_id = shared->frameId;
    }

    if (aldch_rk->ldch_result.update) {
        ldch_param->update_mask |= RKAIQ_ISP_LDCH_ID;
        ldch_param->result.ldch_en = aldch_rk->ldch_result.sw_ldch_en;
        if (ldch_param->result.ldch_en) {
            ldch_param->result.lut_h_size = aldch_rk->ldch_result.lut_h_size;
            ldch_param->result.lut_v_size = aldch_rk->ldch_result.lut_v_size;
            ldch_param->result.lut_size   = aldch_rk->ldch_result.lut_map_size;
            ldch_param->result.lut_mem_fd = aldch_rk->ldch_result.lut_mapxy_buf_fd;
        }
    } else {
        ldch_param->update_mask &= ~RKAIQ_ISP_LDCH_ID;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAldchInt* aldch_rk = (RkAiqAlgoProcResAldchInt*)aldch_com;
    }

    cur_params->mLdchParams = params->mLdchParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
