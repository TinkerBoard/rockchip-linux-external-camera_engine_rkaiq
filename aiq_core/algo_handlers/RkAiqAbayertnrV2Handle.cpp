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

void RkAiqAbayertnrV2HandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAbayertnrV2Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAbayertnrV2Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAbayertnrV2Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAbayertnrV2Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAbayertnrV2Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAbayertnrV2Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAbayertnrV2Int());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAbayertnrV2HandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_abayertnrV2_SetAttrib(mAlgoCtx, &mCurAtt, false);
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
        rk_aiq_uapi_abayertnrV2_SetStrength(mAlgoCtx, mCurStrength);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayertnrV2HandleInt::setAttrib(rk_aiq_bayertnr_attrib_v2_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_bayertnr_attrib_v2_t))) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayertnrV2HandleInt::getAttrib(rk_aiq_bayertnr_attrib_v2_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_abayertnrV2_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayertnrV2HandleInt::setIQPara(rk_aiq_bayertnr_IQPara_V2_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_bayertnr_IQPara_V2_t))) {
        mNewIQPara   = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayertnrV2HandleInt::getIQPara(rk_aiq_bayertnr_IQPara_V2_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayertnrV2HandleInt::setStrength(float fPercent) {
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

XCamReturn RkAiqAbayertnrV2HandleInt::getStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_abayertnrV2_GetStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayertnrV2HandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "arawnr handle prepare failed");

    RkAiqAlgoConfigAbayertnrV2Int* abayertnr_config_int = (RkAiqAlgoConfigAbayertnrV2Int*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAbayertnrV2HandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAbayertnrV2Int* abayertnr_pre_int = (RkAiqAlgoPreAbayertnrV2Int*)mPreInParam;
    RkAiqAlgoPreResAbayertnrV2Int* abayertnr_pre_res_int =
        (RkAiqAlgoPreResAbayertnrV2Int*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->amfnr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "arawnr handle preProcess failed");
    }

    comb->amfnr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo pre_process failed");
    // set result to mAiqCore
    comb->amfnr_pre_res = (RkAiqAlgoPreResAmfnr*)abayertnr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAbayertnrV2HandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAbayertnrV2Int* abayertnr_proc_int = (RkAiqAlgoProcAbayertnrV2Int*)mProcInParam;
    RkAiqAlgoProcResAbayertnrV2Int* abayertnr_proc_res_int =
        (RkAiqAlgoProcResAbayertnrV2Int*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;
    static int abayertnr_proc_framecnt          = 0;
    abayertnr_proc_framecnt++;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->amfnr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aynr handle processing failed");
    }

    comb->amfnr_proc_res = NULL;

    // TODO: fill procParam
    abayertnr_proc_int->iso      = sharedCom->iso;
    abayertnr_proc_int->hdr_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aynr algo processing failed");

    comb->amfnr_proc_res = (RkAiqAlgoProcResAmfnr*)abayertnr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayertnrV2HandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAbayer2dnrV2Int* abayertnr_post_int = (RkAiqAlgoPostAbayer2dnrV2Int*)mPostInParam;
    RkAiqAlgoPostResAbayer2dnrV2Int* abayertnr_post_res_int =
        (RkAiqAlgoPostResAbayer2dnrV2Int*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->amfnr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "arawnr handle postProcess failed");
        return ret;
    }

    comb->amfnr_post_res      = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo post_process failed");
    // set result to mAiqCore
    comb->amfnr_post_res = (RkAiqAlgoPostResAmfnr*)abayertnr_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayertnrV2HandleInt::genIspResult(RkAiqFullParams* params,
                                                   RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAmfnr* atnr_com = shared->procResComb.amfnr_proc_res;

    if (!atnr_com) {
        LOGD_ANALYZER("no abayertnr result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAbayertnrV2Int* atnr_rk = (RkAiqAlgoProcResAbayertnrV2Int*)atnr_com;

        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);
        rk_aiq_isp_tnr_params_v3x_t* tnr_param = params->mTnrV3xParams->data().ptr();
        if (sharedCom->init) {
            tnr_param->frame_id = 0;
        } else {
            tnr_param->frame_id = shared->frameId;
        }
        memcpy(&tnr_param->result, &atnr_rk->stAbayertnrProcResult.st3DFix,
               sizeof(RK_Bayertnr_Fix_V2_t));
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    cur_params->mTnrV3xParams = params->mTnrV3xParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
