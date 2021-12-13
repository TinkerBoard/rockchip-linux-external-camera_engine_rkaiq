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

void RkAiqAsharpHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAsharpInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAsharpInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAsharpInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAsharpInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAsharpInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAsharpInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAsharpInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAsharpHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_asharp_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if (updateIQpara) {
        mCurIQPara   = mNewIQPara;
        updateIQpara = false;
        // TODO
        rk_aiq_uapi_asharp_SetIQpara(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsharpHandleInt::setAttrib(rk_aiq_sharp_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_sharp_attrib_t))) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsharpHandleInt::getAttrib(rk_aiq_sharp_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_asharp_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsharpHandleInt::setIQPara(rk_aiq_sharp_IQpara_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_sharp_IQpara_t))) {
        mNewIQPara   = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsharpHandleInt::getIQPara(rk_aiq_sharp_IQpara_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsharpHandleInt::setStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_asharp_SetStrength(mAlgoCtx, fPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsharpHandleInt::getStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_asharp_GetStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsharpHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "asharp handle prepare failed");

    RkAiqAlgoConfigAsharpInt* asharp_config_int = (RkAiqAlgoConfigAsharpInt*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "asharp algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAsharpHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAsharpInt* asharp_pre_int        = (RkAiqAlgoPreAsharpInt*)mPreInParam;
    RkAiqAlgoPreResAsharpInt* asharp_pre_res_int = (RkAiqAlgoPreResAsharpInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->asharp_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asharp handle preProcess failed");
    }

    comb->asharp_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "asharp algo pre_process failed");
    // set result to mAiqCore
    comb->asharp_pre_res = (RkAiqAlgoPreResAsharp*)asharp_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAsharpHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAsharpInt* asharp_proc_int        = (RkAiqAlgoProcAsharpInt*)mProcInParam;
    RkAiqAlgoProcResAsharpInt* asharp_proc_res_int = (RkAiqAlgoProcResAsharpInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;
    static int asharp_proc_framecnt             = 0;
    asharp_proc_framecnt++;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->asharp_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asharp handle processing failed");
    }

    comb->asharp_proc_res = NULL;

    // TODO: fill procParam
    asharp_proc_int->iso      = sharedCom->iso;
    asharp_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "asharp algo processing failed");

    comb->asharp_proc_res = (RkAiqAlgoProcResAsharp*)asharp_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsharpHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAsharpInt* asharp_post_int        = (RkAiqAlgoPostAsharpInt*)mPostInParam;
    RkAiqAlgoPostResAsharpInt* asharp_post_res_int = (RkAiqAlgoPostResAsharpInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->asharp_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "asharp handle postProcess failed");
        return ret;
    }

    comb->asharp_post_res     = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "asharp algo post_process failed");
    // set result to mAiqCore
    comb->asharp_post_res = (RkAiqAlgoPostResAsharp*)asharp_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAsharpHandleInt::genIspResult(RkAiqFullParams* params,
                                              RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAsharp* asharp_com = shared->procResComb.asharp_proc_res;

    if (!asharp_com) {
        LOGD_ANALYZER("no asharp result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAsharpInt* asharp_rk = (RkAiqAlgoProcResAsharpInt*)asharp_com;

        LOGD_ASHARP("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);
        rk_aiq_isp_sharpen_params_v20_t* sharpen_params = params->mSharpenParams->data().ptr();
        sharpen_params->update_mask |= RKAIQ_ISPP_SHARP_ID;
        memcpy(&sharpen_params->result, &asharp_rk->stAsharpProcResult.stSharpFix,
               sizeof(rk_aiq_isp_sharpen_t));

        rk_aiq_isp_edgeflt_params_v20_t* edgeflt_params = params->mEdgefltParams->data().ptr();
        memcpy(&edgeflt_params->result, &asharp_rk->stAsharpProcResult.stEdgefltFix,
               sizeof(rk_aiq_isp_edgeflt_t));

        if (sharedCom->init) {
            sharpen_params->frame_id = 0;
            edgeflt_params->frame_id = 0;
        } else {
            sharpen_params->frame_id = shared->frameId;
            edgeflt_params->frame_id = shared->frameId;
        }
        LOGD_ASHARP("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    cur_params->mSharpenParams = params->mSharpenParams;
    cur_params->mEdgefltParams = params->mEdgefltParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
