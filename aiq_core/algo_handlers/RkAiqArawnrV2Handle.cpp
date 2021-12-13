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
#include "RkAiqHandleIntV21.h"

namespace RkCam {

void RkAiqArawnrV2HandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigArawnrV2Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreArawnrV2Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResArawnrV2Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcArawnrV2Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResArawnrV2Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostArawnrV2Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResArawnrV2Int());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqArawnrV2HandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_arawnrV2_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if (updateIQpara) {
        mCurIQPara   = mNewIQPara;
        updateIQpara = false;
        // TODO
        // rk_aiq_uapi_asharp_SetIQpara_V3(mAlgoCtx, &mCurIQPara, false);
        sendSignal();
    }

    if (update2DStrength) {
        mCur2DStrength   = mNew2DStrength;
        update2DStrength = false;
        rk_aiq_uapi_rawnrV2_SetSFStrength(mAlgoCtx, mCur2DStrength);
        sendSignal();
    }

    if (update3DStrength) {
        mCur3DStrength   = mNew3DStrength;
        update3DStrength = false;
        rk_aiq_uapi_rawnrV2_SetTFStrength(mAlgoCtx, mCur3DStrength);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::setAttrib(rk_aiq_bayernr_attrib_v2_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_bayernr_attrib_v2_t))) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::getAttrib(rk_aiq_bayernr_attrib_v2_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_arawnrV2_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::setIQPara(rk_aiq_bayernr_IQPara_V2_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_bayernr_IQPara_V2_t))) {
        mNewIQPara   = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::getIQPara(rk_aiq_bayernr_IQPara_V2_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::setSFStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();

    mNew2DStrength   = fPercent;
    update2DStrength = true;
    waitSignal();

    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::getSFStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_rawnrV2_GetSFStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::setTFStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();

    mNew3DStrength   = fPercent;
    update3DStrength = true;
    waitSignal();

    mCfgMutex.unlock();
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::getTFStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_rawnrV2_GetTFStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "arawnr handle prepare failed");

    RkAiqAlgoConfigArawnrV2Int* aynr_config_int = (RkAiqAlgoConfigArawnrV2Int*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqArawnrV2HandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreArawnrV2Int* arawnr_pre_int        = (RkAiqAlgoPreArawnrV2Int*)mPreInParam;
    RkAiqAlgoPreResArawnrV2Int* arawnr_pre_res_int = (RkAiqAlgoPreResArawnrV2Int*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->arawnr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "arawnr handle preProcess failed");
    }

    comb->arawnr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo pre_process failed");
    // set result to mAiqCore
    comb->arawnr_pre_res = (RkAiqAlgoPreResArawnr*)arawnr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqArawnrV2HandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcArawnrV2Int* arawnr_proc_int        = (RkAiqAlgoProcArawnrV2Int*)mProcInParam;
    RkAiqAlgoProcResArawnrV2Int* arawnr_proc_res_int = (RkAiqAlgoProcResArawnrV2Int*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;
    static int arawnr_proc_framecnt             = 0;
    arawnr_proc_framecnt++;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->arawnr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle processing failed");
    }

    comb->arawnr_proc_res = NULL;

    // TODO: fill procParam
    arawnr_proc_int->iso      = sharedCom->iso;
    arawnr_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo processing failed");

    comb->arawnr_proc_res = (RkAiqAlgoProcResArawnr*)arawnr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostArawnrV2Int* arawnr_post_int        = (RkAiqAlgoPostArawnrV2Int*)mPostInParam;
    RkAiqAlgoPostResArawnrV2Int* arawnr_post_res_int = (RkAiqAlgoPostResArawnrV2Int*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->aynr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "arawnr handle postProcess failed");
        return ret;
    }

    comb->aynr_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo post_process failed");
    // set result to mAiqCore
    comb->arawnr_post_res = (RkAiqAlgoPostResArawnr*)arawnr_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqArawnrV2HandleInt::genIspResult(RkAiqFullParams* params,
                                                RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResArawnr* arawnr_com = shared->procResComb.arawnr_proc_res;

    if (!arawnr_com) {
        LOGD_ANALYZER("no arawnr result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResArawnrV2Int* arawnr_rk = (RkAiqAlgoProcResArawnrV2Int*)arawnr_com;

        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);

        rk_aiq_isp_baynr_params_v21_t* rawnr_param = params->mBaynrV21Params->data().ptr();
        if (sharedCom->init) {
            rawnr_param->frame_id = 0;
        } else {
            rawnr_param->frame_id = shared->frameId;
        }
        memcpy(&rawnr_param->result.st2DParam, &arawnr_rk->stArawnrProcResult.st2DFix,
               sizeof(RK_Bayernr_2D_Fix_V2_t));
        memcpy(&rawnr_param->result.st3DParam, &arawnr_rk->stArawnrProcResult.st3DFix,
               sizeof(RK_Bayernr_3D_Fix_V2_t));
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    cur_params->mBaynrV21Params = params->mBaynrV21Params;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
