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

void RkAiqAgainHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAgainInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAgainInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAgainInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAgainInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAgainInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAgainInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAgainInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAgainHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgainHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "again handle prepare failed");

    RkAiqAlgoConfigAgainInt* again_config_int = (RkAiqAlgoConfigAgainInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "again algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAgainHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAgainInt* again_pre_int        = (RkAiqAlgoPreAgainInt*)mPreInParam;
    RkAiqAlgoPreResAgainInt* again_pre_res_int = (RkAiqAlgoPreResAgainInt*)mPreOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->again_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "again handle preProcess failed");
    }

    comb->again_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "again algo pre_process failed");
    // set result to mAiqCore
    comb->again_pre_res = (RkAiqAlgoPreResAgain*)again_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAgainHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAgainInt* again_proc_int        = (RkAiqAlgoProcAgainInt*)mProcInParam;
    RkAiqAlgoProcResAgainInt* again_proc_res_int = (RkAiqAlgoProcResAgainInt*)mProcOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    static int auvnr_proc_framecnt = 0;
    auvnr_proc_framecnt++;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->again_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "again handle processing failed");
    }

    comb->again_proc_res = NULL;

    // TODO: fill procParam
    again_proc_int->iso      = sharedCom->iso;
    again_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "again algo processing failed");

    comb->again_proc_res = (RkAiqAlgoProcResAgain*)again_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgainHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAgainInt* again_post_int        = (RkAiqAlgoPostAgainInt*)mPostInParam;
    RkAiqAlgoPostResAgainInt* again_post_res_int = (RkAiqAlgoPostResAgainInt*)mPostOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->again_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "auvnr handle postProcess failed");
        return ret;
    }

    comb->again_post_res      = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "auvnr algo post_process failed");
    // set result to mAiqCore
    comb->again_post_res = (RkAiqAlgoPostResAgain*)again_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAgainHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAgain* again_com            = shared->procResComb.again_proc_res;

    if (!again_com) {
        LOGD_ANALYZER("no asharp result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAgainInt* again_rk = (RkAiqAlgoProcResAgainInt*)again_com;

        if (params->mGainParams.ptr()) {
            rk_aiq_isp_gain_params_v20_t* gain_param = params->mGainParams->data().ptr();
            if (sharedCom->init) {
                gain_param->frame_id = 0;
            } else {
                gain_param->frame_id = shared->frameId;
            }
            LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);
            memcpy(&gain_param->result, &again_rk->stAgainProcResult.stFix,
                   sizeof(RK_GAIN_Fix_V1_t));
        }
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    cur_params->mGainParams = params->mGainParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
