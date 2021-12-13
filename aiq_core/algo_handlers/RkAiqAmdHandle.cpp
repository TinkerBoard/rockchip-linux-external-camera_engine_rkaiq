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
#include "common/media_buffer/media_buffer.h"

namespace RkCam {

XCamReturn RkAiqAmdHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "amd handle prepare failed");

    RkAiqAlgoConfigAmdInt* amd_config_int = (RkAiqAlgoConfigAmdInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    amd_config_int->amd_config_com.spWidth    = sharedCom->spWidth;
    amd_config_int->amd_config_com.spHeight   = sharedCom->spHeight;
    amd_config_int->amd_config_com.spAlignedW = sharedCom->spAlignedWidth;
    amd_config_int->amd_config_com.spAlignedH = sharedCom->spAlignedHeight;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "amd algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

void RkAiqAmdHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig      = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAmdInt());
    mPreInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPreAmdInt());
    mPreOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAmdInt());
    mProcInParam = (RkAiqAlgoCom*)(new RkAiqAlgoProcAmdInt());
    // mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAmdInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAmdInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAmdInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAmdHandleInt::updateConfig(bool needSync) { return XCAM_RETURN_NO_ERROR; }

XCamReturn RkAiqAmdHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAmdInt* amd_pre_int        = (RkAiqAlgoPreAmdInt*)mPreInParam;
    RkAiqAlgoPreResAmdInt* amd_pre_res_int = (RkAiqAlgoPreResAmdInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->amd_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "amd handle preProcess failed");
    }

    comb->amd_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "amd algo pre_process failed");

    // set result to mAiqCore
    comb->amd_pre_res = (RkAiqAlgoPreResAmd*)amd_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAmdHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAmdInt* amd_proc_int = (RkAiqAlgoProcAmdInt*)mProcInParam;

    mProcResShared = new RkAiqAlgoProcResAmdIntShared();
    if (!mProcResShared.ptr()) {
        LOGE("new amd mProcOutParam failed, bypass!");
        return XCAM_RETURN_BYPASS;
    }
    RkAiqAlgoProcResAmdInt* amd_proc_res_int = &mProcResShared->result;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->amd_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "amd handle processing failed");
    }

    comb->amd_proc_res = NULL;
    memset(&amd_proc_res_int->amd_proc_res_com.amd_proc_res, 0,
           sizeof(amd_proc_res_int->amd_proc_res_com.amd_proc_res));
    amd_proc_int->stats.spImage = shared->sp;
    amd_proc_int->stats.ispGain = shared->ispGain;
    RkAiqAlgoDescription* des   = (RkAiqAlgoDescription*)mDes;
    ret                         = des->processing(mProcInParam, (RkAiqAlgoResCom*)amd_proc_res_int);
    RKAIQCORE_CHECK_RET(ret, "amd algo processing failed");

    comb->amd_proc_res = (RkAiqAlgoProcResAmd*)amd_proc_res_int;

    MediaBuffer_t* mbuf = amd_proc_res_int->amd_proc_res_com.amd_proc_res.st_ratio;
    if (mbuf) {
        MotionBufMetaData_t* metadata = (MotionBufMetaData_t*)mbuf->pMetaData;
        SmartPtr<XCamMessage> msg =
            new RkAiqCoreVdBufMsg(XCAM_MESSAGE_AMD_PROC_RES_OK, metadata->frame_id, mProcResShared);
        mAiqCore->post_message(msg);
    }

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmdHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAmdInt* amd_post_int        = (RkAiqAlgoPostAmdInt*)mPostInParam;
    RkAiqAlgoPostResAmdInt* amd_post_res_int = (RkAiqAlgoPostResAmdInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->amd_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "amd handle postProcess failed");
        return ret;
    }

    comb->amd_post_res        = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "amd algo post_process failed");
    // set result to mAiqCore
    comb->amd_post_res = (RkAiqAlgoPostResAmd*)amd_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmdHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAmd* amd_com = shared->procResComb.amd_proc_res;

    rk_aiq_isp_md_params_v20_t* md_param = params->mMdParams->data().ptr();
    if (sharedCom->init) {
        md_param->frame_id = 0;
    } else {
        md_param->frame_id = shared->frameId;
    }

    if (!amd_com) {
        LOGD_ANALYZER("no amd result");
        return XCAM_RETURN_NO_ERROR;
    }

    md_param->result = amd_com->amd_proc_res;

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAmdInt* amd_rk = (RkAiqAlgoProcResAmdInt*)amd_com;
    }

    cur_params->mMdParams = params->mMdParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
