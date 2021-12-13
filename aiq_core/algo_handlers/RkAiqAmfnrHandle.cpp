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

void RkAiqAmfnrHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAmfnrInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAmfnrInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAmfnrInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAmfnrInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAmfnrInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAmfnrInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAmfnrInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAmfnrHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_amfnr_SetAttrib_v1(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if (updateIQpara) {
        mCurIQPara   = mNewIQPara;
        updateIQpara = false;
        // TODO
        rk_aiq_uapi_amfnr_SetIQPara_v1(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if (updateJsonpara) {
        mCurJsonPara   = mNewJsonPara;
        updateJsonpara = false;
        // TODO
        rk_aiq_uapi_amfnr_SetJsonPara_v1(mAlgoCtx, &mCurJsonPara, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::setAttrib(rk_aiq_mfnr_attrib_v1_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_mfnr_attrib_v1_t))) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::getAttrib(rk_aiq_mfnr_attrib_v1_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_amfnr_GetAttrib_v1(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::setIQPara(rk_aiq_mfnr_IQPara_V1_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_mfnr_IQPara_V1_t))) {
        mNewIQPara   = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::getIQPara(rk_aiq_mfnr_IQPara_V1_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_amfnr_GetIQPara_v1(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::setJsonPara(rk_aiq_mfnr_JsonPara_V1_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_mfnr_JsonPara_V1_t))) {
        mNewJsonPara   = *para;
        updateJsonpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::getJsonPara(rk_aiq_mfnr_JsonPara_V1_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_amfnr_GetJsonPara_v1(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::setLumaStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_amfnr_SetLumaTFStrength_v1(mAlgoCtx, fPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::getLumaStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_amfnr_GetLumaTFStrength_v1(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::setChromaStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_amfnr_SetChromaTFStrength_v1(mAlgoCtx, fPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::getChromaStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_amfnr_GetChromaTFStrength_v1(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "amfnr handle prepare failed");

    RkAiqAlgoConfigAmfnrInt* amfnr_config_int = (RkAiqAlgoConfigAmfnrInt*)mConfig;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "amfnr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAmfnrHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAmfnrInt* amfnr_pre_int        = (RkAiqAlgoPreAmfnrInt*)mPreInParam;
    RkAiqAlgoPreResAmfnrInt* amfnr_pre_res_int = (RkAiqAlgoPreResAmfnrInt*)mPreOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->amfnr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "amfnr handle preProcess failed");
    }

    comb->amfnr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "amfnr algo pre_process failed");

    // set result to mAiqCore
    comb->amfnr_pre_res = (RkAiqAlgoPreResAmfnr*)amfnr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAmfnrHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAmfnrInt* amfnr_proc_int        = (RkAiqAlgoProcAmfnrInt*)mProcInParam;
    RkAiqAlgoProcResAmfnrInt* amfnr_proc_res_int = (RkAiqAlgoProcResAmfnrInt*)mProcOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->amfnr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "amfnr handle processing failed");
    }

    comb->amfnr_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "amfnr algo processing failed");

    comb->amfnr_proc_res = (RkAiqAlgoProcResAmfnr*)amfnr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAmfnrInt* amfnr_post_int        = (RkAiqAlgoPostAmfnrInt*)mPostInParam;
    RkAiqAlgoPostResAmfnrInt* amfnr_post_res_int = (RkAiqAlgoPostResAmfnrInt*)mPostOutParam;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->amfnr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "amfnr handle postProcess failed");
        return ret;
    }

    comb->amfnr_post_res      = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "amfnr algo post_process failed");
    // set result to mAiqCore
    comb->amfnr_post_res = (RkAiqAlgoPostResAmfnr*)amfnr_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAmfnrHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAmfnr* amfnr_com = shared->procResComb.amfnr_proc_res;

    if (!amfnr_com) {
        LOGD_ANALYZER("no asharp result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAmfnrInt* amfnr_rk = (RkAiqAlgoProcResAmfnrInt*)amfnr_com;
        if (params->mTnrParams.ptr()) {
            rk_aiq_isp_tnr_params_v20_t* tnr_param = params->mTnrParams->data().ptr();
            LOGD_ANR("oyyf: %s:%d output ispp param start\n", __FUNCTION__, __LINE__);

            if (sharedCom->init) {
                tnr_param->frame_id = 0;
            } else {
                tnr_param->frame_id = shared->frameId;
            }
            tnr_param->update_mask |= RKAIQ_ISPP_TNR_ID;
            memcpy(&tnr_param->result, &amfnr_rk->stAmfnrProcResult.stFix,
                   sizeof(RK_MFNR_Fix_V1_t));
        }
        LOGD_ASHARP("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    cur_params->mTnrParams = params->mTnrParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
