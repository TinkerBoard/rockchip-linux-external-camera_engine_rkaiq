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
#include "RkAiqHandleIntV3x.h"

namespace RkCam {

void RkAiqAynrV3HandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAynrV3Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAynrV3Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAynrV3Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAynrV3Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAynrV3Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAynrV3Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAynrV3Int());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAynrV3HandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_aynrV3_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if (updateIQpara) {
        mCurIQPara   = mNewIQPara;
        updateIQpara = false;
        // TODO
        // rk_aiq_uapi_asharp_SetIQpara_V3(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if (updateStrength) {
        mCurStrength   = mNewStrength;
        updateStrength = false;
        rk_aiq_uapi_aynrV3_SetLumaSFStrength(mAlgoCtx, mCurStrength);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrV3HandleInt::setAttrib(rk_aiq_ynr_attrib_v3_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_ynr_attrib_v3_t))) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrV3HandleInt::getAttrib(rk_aiq_ynr_attrib_v3_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aynrV3_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrV3HandleInt::setIQPara(rk_aiq_ynr_IQPara_V3_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_ynr_IQPara_V3_t))) {
        mNewIQPara   = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrV3HandleInt::getIQPara(rk_aiq_ynr_IQPara_V3_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrV3HandleInt::setStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();

    mNewStrength   = fPercent;
    updateStrength = true;
    waitSignal();

    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrV3HandleInt::getStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aynrV3_GetLumaSFStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAynrV3HandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "aynr handle prepare failed");

    RkAiqAlgoConfigAynrV3Int* aynr_config_int   = (RkAiqAlgoConfigAynrV3Int*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    aynr_config_int->stAynrConfig.rawWidth  = sharedCom->snsDes.isp_acq_width;
    aynr_config_int->stAynrConfig.rawHeight = sharedCom->snsDes.isp_acq_height;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "aynr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAynrV3HandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAynrV3Int* aynr_pre_int        = (RkAiqAlgoPreAynrV3Int*)mPreInParam;
    RkAiqAlgoPreResAynrV3Int* aynr_pre_res_int = (RkAiqAlgoPreResAynrV3Int*)mPreOutParam;
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

XCamReturn RkAiqAynrV3HandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAynrV3Int* aynr_proc_int        = (RkAiqAlgoProcAynrV3Int*)mProcInParam;
    RkAiqAlgoProcResAynrV3Int* aynr_proc_res_int = (RkAiqAlgoProcResAynrV3Int*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;
    static int aynr_proc_framecnt               = 0;
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

XCamReturn RkAiqAynrV3HandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAynrV3Int* aynr_post_int        = (RkAiqAlgoPostAynrV3Int*)mPostInParam;
    RkAiqAlgoPostResAynrV3Int* aynr_post_res_int = (RkAiqAlgoPostResAynrV3Int*)mPostOutParam;
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

XCamReturn RkAiqAynrV3HandleInt::genIspResult(RkAiqFullParams* params,
                                              RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAynr* aynr_com              = shared->procResComb.aynr_proc_res;

    if (!aynr_com) {
        LOGD_ANALYZER("no aynr result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAynrV3Int* aynr_rk = (RkAiqAlgoProcResAynrV3Int*)aynr_com;

        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);
        rk_aiq_isp_ynr_params_v3x_t* ynr_param = params->mYnrV3xParams->data().ptr();
        if (sharedCom->init) {
            ynr_param->frame_id = 0;
        } else {
            ynr_param->frame_id = shared->frameId;
        }
        memcpy(&ynr_param->result, &aynr_rk->stAynrProcResult.stFix, sizeof(RK_YNR_Fix_V3_t));
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    cur_params->mYnrV3xParams = params->mYnrV3xParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
