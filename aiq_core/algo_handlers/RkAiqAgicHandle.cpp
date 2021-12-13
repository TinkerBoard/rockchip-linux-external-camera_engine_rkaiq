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

void RkAiqAgicHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAgicInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAgicInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAgicInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAgicInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAgicInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAgicInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAgicInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAgicHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_agic_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }
    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgicHandleInt::setAttrib(agic_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore
    if (0 != memcmp(&mCurAtt, &att, sizeof(agic_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgicHandleInt::getAttrib(agic_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_agic_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgicHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "agic handle prepare failed");

    RkAiqAlgoConfigAgicInt* agic_config_int = (RkAiqAlgoConfigAgicInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "agic algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAgicHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAgicInt* agic_pre_int        = (RkAiqAlgoPreAgicInt*)mPreInParam;
    RkAiqAlgoPreResAgicInt* agic_pre_res_int = (RkAiqAlgoPreResAgicInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->agic_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agic handle preProcess failed");
    }

    comb->agic_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "agic algo pre_process failed");

    // set result to mAiqCore
    comb->agic_pre_res = (RkAiqAlgoPreResAgic*)agic_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAgicHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAgicInt* agic_proc_int        = (RkAiqAlgoProcAgicInt*)mProcInParam;
    RkAiqAlgoProcResAgicInt* agic_proc_res_int = (RkAiqAlgoProcResAgicInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->agic_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agic handle processing failed");
    }

    comb->agic_proc_res     = NULL;
    agic_proc_int->hdr_mode = sharedCom->working_mode;
    switch (sharedCom->snsDes.sensor_pixelformat) {
        case V4L2_PIX_FMT_SBGGR14:
        case V4L2_PIX_FMT_SGBRG14:
        case V4L2_PIX_FMT_SGRBG14:
        case V4L2_PIX_FMT_SRGGB14:
            agic_proc_int->raw_bits = 14;
            break;
        case V4L2_PIX_FMT_SBGGR12:
        case V4L2_PIX_FMT_SGBRG12:
        case V4L2_PIX_FMT_SGRBG12:
        case V4L2_PIX_FMT_SRGGB12:
            agic_proc_int->raw_bits = 12;
            break;
        case V4L2_PIX_FMT_SBGGR10:
        case V4L2_PIX_FMT_SGBRG10:
        case V4L2_PIX_FMT_SGRBG10:
        case V4L2_PIX_FMT_SRGGB10:
            agic_proc_int->raw_bits = 10;
            break;
        default:
            agic_proc_int->raw_bits = 8;
    }

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "agic algo processing failed");

    comb->agic_proc_res = (RkAiqAlgoProcResAgic*)agic_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgicHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAgicInt* agic_post_int        = (RkAiqAlgoPostAgicInt*)mPostInParam;
    RkAiqAlgoPostResAgicInt* agic_post_res_int = (RkAiqAlgoPostResAgicInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->agic_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "agic handle postProcess failed");
        return ret;
    }

    comb->agic_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "agic algo post_process failed");
    // set result to mAiqCore
    comb->agic_post_res = (RkAiqAlgoPostResAgic*)agic_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgicHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAgic* agic_com              = shared->procResComb.agic_proc_res;
    rk_aiq_isp_gic_params_v20_t* gic_param = params->mGicParams->data().ptr();

    if (!agic_com) {
        LOGD_ANALYZER("no agic result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAgicInt* agic_rk = (RkAiqAlgoProcResAgicInt*)agic_com;
        if (sharedCom->init) {
            gic_param->frame_id = 0;
        } else {
            gic_param->frame_id = shared->frameId;
        }
        memcpy(&gic_param->result, &agic_rk->gicRes, sizeof(AgicProcResult_t));
    }

    cur_params->mGicParams = params->mGicParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
