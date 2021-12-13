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

void RkAiqAbayer2dnrV2HandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAbayer2dnrV2Int());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAbayer2dnrV2Int());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAbayer2dnrV2Int());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAbayer2dnrV2Int());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAbayer2dnrV2Int());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAbayer2dnrV2Int());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAbayer2dnrV2Int());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAbayer2dnrV2HandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_abayer2dnrV2_SetAttrib(mAlgoCtx, &mCurAtt, false);
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
        rk_aiq_uapi_abayer2dnrV2_SetStrength(mAlgoCtx, mCurStrength);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayer2dnrV2HandleInt::setAttrib(rk_aiq_bayer2dnr_attrib_v2_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_bayer2dnr_attrib_v2_t))) {
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayer2dnrV2HandleInt::getAttrib(rk_aiq_bayer2dnr_attrib_v2_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_abayer2dnrV2_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayer2dnrV2HandleInt::setIQPara(rk_aiq_bayer2dnr_IQPara_V2_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQPara, para, sizeof(rk_aiq_bayer2dnr_IQPara_V2_t))) {
        mNewIQPara   = *para;
        updateIQpara = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayer2dnrV2HandleInt::getIQPara(rk_aiq_bayer2dnr_IQPara_V2_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // rk_aiq_uapi_asharp_GetIQpara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayer2dnrV2HandleInt::setStrength(float fPercent) {
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

XCamReturn RkAiqAbayer2dnrV2HandleInt::getStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_abayer2dnrV2_GetStrength(mAlgoCtx, pPercent);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayer2dnrV2HandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "arawnr handle prepare failed");

    RkAiqAlgoConfigAbayer2dnrV2Int* aynr_config_int = (RkAiqAlgoConfigAbayer2dnrV2Int*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAbayer2dnrV2HandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAbayer2dnrV2Int* arawnr_pre_int = (RkAiqAlgoPreAbayer2dnrV2Int*)mPreInParam;
    RkAiqAlgoPreResAbayer2dnrV2Int* arawnr_pre_res_int =
        (RkAiqAlgoPreResAbayer2dnrV2Int*)mPreOutParam;
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

XCamReturn RkAiqAbayer2dnrV2HandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAbayer2dnrV2Int* arawnr_proc_int = (RkAiqAlgoProcAbayer2dnrV2Int*)mProcInParam;
    RkAiqAlgoProcResAbayer2dnrV2Int* arawnr_proc_res_int =
        (RkAiqAlgoProcResAbayer2dnrV2Int*)mProcOutParam;
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

XCamReturn RkAiqAbayer2dnrV2HandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAbayer2dnrV2Int* arawnr_post_int = (RkAiqAlgoPostAbayer2dnrV2Int*)mPostInParam;
    RkAiqAlgoPostResAbayer2dnrV2Int* arawnr_post_res_int =
        (RkAiqAlgoPostResAbayer2dnrV2Int*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->arawnr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "arawnr handle postProcess failed");
        return ret;
    }

    comb->arawnr_post_res     = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "arawnr algo post_process failed");
    // set result to mAiqCore
    comb->arawnr_post_res = (RkAiqAlgoPostResArawnr*)arawnr_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAbayer2dnrV2HandleInt::genIspResult(RkAiqFullParams* params,
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
        RkAiqAlgoProcResAbayer2dnrV2Int* arawnr_rk = (RkAiqAlgoProcResAbayer2dnrV2Int*)arawnr_com;

        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);
        rk_aiq_isp_baynr_params_v3x_t* rawnr_param = params->mBaynrV3xParams->data().ptr();
        if (sharedCom->init) {
            rawnr_param->frame_id = 0;
        } else {
            rawnr_param->frame_id = shared->frameId;
        }
        memcpy(&rawnr_param->result, &arawnr_rk->stArawnrProcResult.st2DFix,
               sizeof(RK_Bayer2dnr_Fix_V2_t));
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    cur_params->mBaynrV3xParams = params->mBaynrV3xParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
