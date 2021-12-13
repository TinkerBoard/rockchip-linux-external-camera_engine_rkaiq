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

void RkAiqAynrHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAynrInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAynrInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAynrInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAynrInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAynrInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAynrInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAynrInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAynrHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_aynr_SetAttrib_v1(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if (updateIQpara) {
        mCurIQPara   = mNewIQPara;
        updateIQpara = false;
        // TODO
        rk_aiq_uapi_aynr_SetIQPara_v1(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if (updateJsonpara) {
        mCurJsonPara   = mNewJsonPara;
        updateJsonpara = false;
        // TODO
        rk_aiq_uapi_aynr_SetJsonPara_v1(mAlgoCtx, &mCurJsonPara, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::setAttrib(rk_aiq_ynr_attrib_v1_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_ynr_attrib_v1_t))) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::getAttrib(rk_aiq_ynr_attrib_v1_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aynr_GetAttrib_v1(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::setIQPara(rk_aiq_ynr_IQPara_V1_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_ynr_IQPara_V1_t))) {
        mNewIQPara   = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::getIQPara(rk_aiq_ynr_IQPara_V1_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aynr_GetIQPara_v1(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::setJsonPara(rk_aiq_ynr_JsonPara_V1_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_ynr_JsonPara_V1_t))) {
        mNewJsonPara   = *para;
        updateJsonpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::getJsonPara(rk_aiq_ynr_JsonPara_V1_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aynr_GetJsonPara_v1(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::setStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aynr_SetLumaSFStrength_v1(mAlgoCtx, fPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::getStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aynr_GetLumaSFStrength_v1(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "aynr handle prepare failed");

    RkAiqAlgoConfigAynrInt* aynr_config_int = (RkAiqAlgoConfigAynrInt*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "aynr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAynrHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAynrInt* aynr_pre_int        = (RkAiqAlgoPreAynrInt*)mPreInParam;
    RkAiqAlgoPreResAynrInt* aynr_pre_res_int = (RkAiqAlgoPreResAynrInt*)mPreOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->aynr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle preProcess failed");
    }

    comb->aynr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo pre_process failed");
    // set result to mAiqCore
    comb->aynr_pre_res = (RkAiqAlgoPreResAynr*)aynr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAynrHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAynrInt* aynr_proc_int        = (RkAiqAlgoProcAynrInt*)mProcInParam;
    RkAiqAlgoProcResAynrInt* aynr_proc_res_int = (RkAiqAlgoProcResAynrInt*)mProcOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    static int aynr_proc_framecnt = 0;
    aynr_proc_framecnt++;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->aynr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle processing failed");
    }

    comb->aynr_proc_res = NULL;

    // TODO: fill procParam
    aynr_proc_int->iso      = sharedCom->iso;
    aynr_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo processing failed");

    comb->aynr_proc_res = (RkAiqAlgoProcResAynr*)aynr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAynrInt* aynr_post_int        = (RkAiqAlgoPostAynrInt*)mPostInParam;
    RkAiqAlgoPostResAynrInt* aynr_post_res_int = (RkAiqAlgoPostResAynrInt*)mPostOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->aynr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle postProcess failed");
        return ret;
    }

    comb->aynr_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo post_process failed");
    // set result to mAiqCore
    comb->aynr_post_res = (RkAiqAlgoPostResAynr*)aynr_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAynr* aynr_com              = shared->procResComb.aynr_proc_res;

    if (!aynr_com) {
        LOGD_ANALYZER("no asharp result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAynrInt* aynr_rk = (RkAiqAlgoProcResAynrInt*)aynr_com;

        if (params->mYnrParams.ptr()) {
            rk_aiq_isp_ynr_params_v20_t* ynr_param = params->mYnrParams->data().ptr();
            LOGD_ANR("oyyf: %s:%d output ispp param start\n", __FUNCTION__, __LINE__);

            if (sharedCom->init) {
                ynr_param->frame_id = 0;
            } else {
                ynr_param->frame_id = shared->frameId;
            }
            memcpy(&ynr_param->result, &aynr_rk->stAynrProcResult.stFix, sizeof(RK_YNR_Fix_V1_t));
        }
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    cur_params->mYnrParams = params->mYnrParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
