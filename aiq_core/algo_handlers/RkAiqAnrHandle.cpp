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
 *
 */
#include "RkAiqCore.h"
#include "RkAiqHandle.h"
#include "RkAiqHandleInt.h"

namespace RkCam {

void RkAiqAnrHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAnrInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAnrInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAnrInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAnrInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAnrInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAnrInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAnrInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAnrHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_anr_SetAttrib(mAlgoCtx, &mCurAtt, false);
        sendSignal();
    }

    if (UpdateIQpara) {
        mCurIQpara   = mNewIQpara;
        UpdateIQpara = false;
        rk_aiq_uapi_anr_SetIQPara(mAlgoCtx, &mCurIQpara, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::setAttrib(rk_aiq_nr_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, att, sizeof(rk_aiq_nr_attrib_t))) {
        RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
        CalibDbV2_MFNR_t* mfnr =
            (CalibDbV2_MFNR_t*)CALIBDBV2_GET_MODULE_PTR((void*)(sharedCom->calibv2), mfnr_v1);
        if (mfnr && mfnr->TuningPara.enable && mfnr->TuningPara.motion_detect_en) {
            if ((att->eMode == ANR_OP_MODE_AUTO) && (!att->stAuto.mfnrEn)) {
                att->stAuto.mfnrEn = !att->stAuto.mfnrEn;
                LOGE("motion detect is running, operate not permit!");
                goto EXIT;
            } else if ((att->eMode == ANR_OP_MODE_MANUAL) && (!att->stManual.mfnrEn)) {
                att->stManual.mfnrEn = !att->stManual.mfnrEn;
                LOGE("motion detect is running, operate not permit!");
                goto EXIT;
            }
        }
        mNewAtt   = *att;
        updateAtt = true;
        waitSignal();
    }
EXIT:
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::getAttrib(rk_aiq_nr_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = rk_aiq_uapi_anr_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::setIQPara(rk_aiq_nr_IQPara_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurIQpara, para, sizeof(rk_aiq_nr_IQPara_t))) {
        RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
        CalibDbV2_MFNR_t* mfnr =
            (CalibDbV2_MFNR_t*)CALIBDBV2_GET_MODULE_PTR((void*)(sharedCom->calibv2), mfnr_v1);
        if (mfnr && mfnr->TuningPara.enable && mfnr->TuningPara.motion_detect_en) {
            if ((para->module_bits & (1 << ANR_MODULE_MFNR)) && !para->stMfnrPara.enable) {
                para->stMfnrPara.enable = !para->stMfnrPara.enable;
                LOGE("motion detect is running, disable mfnr is not permit!");
            }
        }
        mNewIQpara   = *para;
        UpdateIQpara = true;
        waitSignal();
    }
EXIT:
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::getIQPara(rk_aiq_nr_IQPara_t* para) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = rk_aiq_uapi_anr_GetIQPara(mAlgoCtx, para);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::setLumaSFStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_SetLumaSFStrength(mAlgoCtx, fPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::setLumaTFStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_SetLumaTFStrength(mAlgoCtx, fPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::getLumaSFStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_GetLumaSFStrength(mAlgoCtx, pPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::getLumaTFStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_GetLumaTFStrength(mAlgoCtx, pPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::setChromaSFStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_SetChromaSFStrength(mAlgoCtx, fPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::setChromaTFStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_SetChromaTFStrength(mAlgoCtx, fPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::getChromaSFStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_GetChromaSFStrength(mAlgoCtx, pPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::getChromaTFStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_GetChromaTFStrength(mAlgoCtx, pPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::setRawnrSFStrength(float fPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_SetRawnrSFStrength(mAlgoCtx, fPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::getRawnrSFStrength(float* pPercent) {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    ret            = rk_aiq_uapi_anr_GetRawnrSFStrength(mAlgoCtx, pPercent);
    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "anr handle prepare failed");

    RkAiqAlgoConfigAnrInt* anr_config_int = (RkAiqAlgoConfigAnrInt*)mConfig;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "anr algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAnrHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAnrInt* anr_pre_int        = (RkAiqAlgoPreAnrInt*)mPreInParam;
    RkAiqAlgoPreResAnrInt* anr_pre_res_int = (RkAiqAlgoPreResAnrInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->anr_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "anr handle preProcess failed");
    }

    comb->anr_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "anr algo pre_process failed");

    // set result to mAiqCore
    comb->anr_pre_res = (RkAiqAlgoPreResAnr*)anr_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAnrHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAnrInt* anr_proc_int        = (RkAiqAlgoProcAnrInt*)mProcInParam;
    RkAiqAlgoProcResAnrInt* anr_proc_res_int = (RkAiqAlgoProcResAnrInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;
    static int anr_proc_framecnt                = 0;
    anr_proc_framecnt++;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->anr_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "anr handle processing failed");
    }
    comb->anr_proc_res = NULL;

    // TODO: fill procParam
    anr_proc_int->iso = sharedCom->iso;

    anr_proc_int->hdr_mode = sharedCom->working_mode;

    LOGD("%s:%d anr hdr_mode:%d  \n", __FUNCTION__, __LINE__, anr_proc_int->hdr_mode);

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "anr algo processing failed");

    comb->anr_proc_res = (RkAiqAlgoProcResAnr*)anr_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAnrInt* anr_post_int        = (RkAiqAlgoPostAnrInt*)mPostInParam;
    RkAiqAlgoPostResAnrInt* anr_post_res_int = (RkAiqAlgoPostResAnrInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->anr_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "anr handle postProcess failed");
        return ret;
    }

    comb->anr_post_res        = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "anr algo post_process failed");
    // set result to mAiqCore
    comb->anr_post_res = (RkAiqAlgoPostResAnr*)anr_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAnrHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAnr* anr_com                = shared->procResComb.anr_proc_res;

    if (!anr_com /*|| !params->mIsppOtherParams.ptr()*/) {
        LOGD_ANALYZER("no anr result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAnrInt* anr_rk = (RkAiqAlgoProcResAnrInt*)anr_com;
        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);

        rk_aiq_isp_rawnr_params_v20_t* rawnr_params = params->mRawnrParams->data().ptr();
        rawnr_params->update_mask |= RKAIQ_ISPP_NR_ID;
        memcpy(&rawnr_params->result, &anr_rk->stAnrProcResult.stBayernrFix,
               sizeof(rk_aiq_isp_rawnr_t));

        rk_aiq_isp_gain_params_v20_t* gain_params = params->mGainParams->data().ptr();
        memcpy(&gain_params->result, &anr_rk->stAnrProcResult.stGainFix, sizeof(rk_aiq_isp_gain_t));

        rk_aiq_isp_motion_params_v20_t* motion_params = params->mMotionParams->data().ptr();
        memcpy(&motion_params->result, &anr_rk->stAnrProcResult.stMotion,
               sizeof(anr_rk->stAnrProcResult.stMotion));

        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);

        LOGD_ANR("oyyf: %s:%d output ispp param start\n", __FUNCTION__, __LINE__);

        rk_aiq_isp_ynr_params_v20_t* ynr_params = params->mYnrParams->data().ptr();
        memcpy(&ynr_params->result, &anr_rk->stAnrProcResult.stYnrFix, sizeof(RKAnr_Ynr_Fix_t));

        rk_aiq_isp_uvnr_params_v20_t* uvnr_params = params->mUvnrParams->data().ptr();
        uvnr_params->update_mask |= RKAIQ_ISPP_NR_ID;
        memcpy(&uvnr_params->result, &anr_rk->stAnrProcResult.stUvnrFix, sizeof(RKAnr_Uvnr_Fix_t));

        rk_aiq_isp_tnr_params_v20_t* tnr_params = params->mTnrParams->data().ptr();
        memcpy(&tnr_params->result, &anr_rk->stAnrProcResult.stMfnrFix, sizeof(RKAnr_Mfnr_Fix_t));
        LOGD_ANR("oyyf: %s:%d output ispp param end \n", __FUNCTION__, __LINE__);

        if (sharedCom->init) {
            rawnr_params->frame_id  = 0;
            gain_params->frame_id   = 0;
            motion_params->frame_id = 0;
            ynr_params->frame_id    = 0;
            uvnr_params->frame_id   = 0;
            tnr_params->frame_id    = 0;
        } else {
            rawnr_params->frame_id  = shared->frameId;
            gain_params->frame_id   = shared->frameId;
            motion_params->frame_id = shared->frameId;
            ynr_params->frame_id    = shared->frameId;
            uvnr_params->frame_id   = shared->frameId;
            tnr_params->frame_id    = shared->frameId;
        }
    }

    cur_params->mRawnrParams  = params->mRawnrParams;
    cur_params->mUvnrParams   = params->mUvnrParams;
    cur_params->mYnrParams    = params->mYnrParams;
    cur_params->mTnrParams    = params->mTnrParams;
    cur_params->mYnrParams    = params->mYnrParams;
    cur_params->mGainParams   = params->mGainParams;
    cur_params->mMotionParams = params->mMotionParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
