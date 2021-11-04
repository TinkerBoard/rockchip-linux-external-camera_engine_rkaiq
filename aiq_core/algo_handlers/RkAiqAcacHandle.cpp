/*
 * RkAiqAcacHandle.h
 *
 *  Copyright (c) 2019-2021 Rockchip Eletronics Co., Ltd.
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

XCamReturn RkAiqAcacHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqAcacHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "acac handle prepare failed");

    RkAiqAlgoConfigAcacInt* acac_config_int = (RkAiqAlgoConfigAcacInt*)mConfig;
    RkAiqAlgoDescription* des               = (RkAiqAlgoDescription*)mDes;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared = nullptr;
    int groupId                                = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_ACAC);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;
    RkAiqPreResComb* comb = &shared->preResComb;

    acac_config_int->mem_ops = mAiqCore->mShareMemOps;
    acac_config_int->width = sharedCom->snsDes.isp_acq_width;
    acac_config_int->height = sharedCom->snsDes.isp_acq_height;
    acac_config_int->is_multi_sensor = sharedCom->is_multi_sensor;
    acac_config_int->is_multi_isp = sharedCom->is_multi_isp_mode;
    acac_config_int->multi_isp_extended_pixel = sharedCom->multi_isp_extended_pixels;

    ret = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "acac algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

void RkAiqAcacHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqAcacHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAcacInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAcacInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAcacInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAcacInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAcacInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAcacInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAcacInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAcacHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAcacInt* acac_pre_int          = (RkAiqAlgoPreAcacInt*)mPreInParam;
    RkAiqAlgoPreResAcacInt* acac_pre_res_int   = (RkAiqAlgoPreResAcacInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared = nullptr;
    int groupId                                = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_ACAC);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;
    RkAiqPreResComb* comb = &shared->preResComb;

    ret = RkAiqAcacHandle::preProcess();
    if (ret) {
        comb->acac_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acac handle preProcess failed");
    }

    comb->acac_pre_res        = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;

    ret = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "acac algo pre_process failed");
    comb->acac_pre_res = (RkAiqAlgoPreResAcac*)acac_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAcacHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAcacInt* acac_proc_int        = (RkAiqAlgoProcAcacInt*)mProcInParam;
    RkAiqAlgoProcResAcacInt* acac_proc_res_int = (RkAiqAlgoProcResAcacInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared = nullptr;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    int groupId = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_ACAC);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;

    RkAiqProcResComb* comb = &shared->procResComb;

    RKAiqAecExpInfo_t* aeCurExp = &shared->curExp;
    if (aeCurExp != NULL) {
        if((rk_aiq_working_mode_t)sharedCom->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
            acac_proc_int->iso = aeCurExp->LinearExp.exp_real_params.analog_gain * 50;
            LOGD_ACAC("%s:NORMAL:iso=%d,again=%f\n", __FUNCTION__, acac_proc_int->iso,
                      aeCurExp->LinearExp.exp_real_params.analog_gain);
        } else if ((rk_aiq_working_mode_t)sharedCom->working_mode == RK_AIQ_WORKING_MODE_ISP_HDR2) {
            acac_proc_int->iso = aeCurExp->HdrExp[1].exp_real_params.analog_gain * 50;
            LOGD_ACAC("%s:HDR2:iso=%d,again=%f\n", __FUNCTION__, acac_proc_int->iso,
                      aeCurExp->HdrExp[1].exp_real_params.analog_gain);
        } else if ((rk_aiq_working_mode_t)sharedCom->working_mode == RK_AIQ_WORKING_MODE_ISP_HDR3) {
            acac_proc_int->iso = aeCurExp->HdrExp[2].exp_real_params.analog_gain * 50;
            LOGD_ACAC("%s:HDR3:iso=%d,again=%f\n", __FUNCTION__, acac_proc_int->iso,
                      aeCurExp->HdrExp[2].exp_real_params.analog_gain);
        }
    } else {
        acac_proc_int->iso = 50;
        LOGE_ACAC("%s: pAEPreRes is NULL, so use default instead \n", __FUNCTION__);
    }



    ret = RkAiqAcacHandle::processing();
    if (ret) {
        comb->acac_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acac handle processing failed");
    }

    comb->acac_proc_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;

    ret = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "acac algo processing failed");
    comb->acac_proc_res = (RkAiqAlgoProcResAcac*)acac_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcacHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAcacInt* acac_post_int        = (RkAiqAlgoPostAcacInt*)mPostInParam;
    RkAiqAlgoPostResAcacInt* acac_post_res_int = (RkAiqAlgoPostResAcacInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared = nullptr;

    int groupId = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_ACAC);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;

    RkAiqPostResComb* comb = &shared->postResComb;

    ret = RkAiqAcacHandle::postProcess();
    if (ret) {
        comb->acac_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "acac handle postProcess failed");
        return ret;
    }

    comb->acac_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;

    ret = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "acac algo post_process failed");
    comb->acac_post_res = (RkAiqAlgoPostResAcac*)acac_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcacHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_acac_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcacHandleInt::setAttrib(rk_aiq_cac_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    if (0 != memcmp(&mCurAtt, &att, sizeof(rk_aiq_cac_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }
    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcacHandleInt::getAttrib(rk_aiq_cac_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_acac_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

void RkAiqAcacHandle::init() {
    ENTER_ANALYZER_FUNCTION();

    deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAcac());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAcac());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAcac());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAcac());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAcac());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAcac());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAcac());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAcacHandle::prepare() {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret            = XCAM_RETURN_NO_ERROR;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "acac handle prepare failed");

    if (mDes->id != 0) {
        ret = des->prepare(mConfig);
        RKAIQCORE_CHECK_RET(ret, "acac algo prepare failed");
    }

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcacHandle::preProcess() {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret                              = XCAM_RETURN_NO_ERROR;
    RkAiqAlgoDescription* des                   = (RkAiqAlgoDescription*)mDes;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared  = nullptr;

    int groupId = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_ACAC);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;

    ret = RkAiqHandle::preProcess();
    RKAIQCORE_CHECK_RET(ret, "acac handle preProcess failed");

    if (mDes->id != 0) {
        ret = des->pre_process(mPreInParam, mPreOutParam);
        RKAIQCORE_CHECK_RET(ret, "acac handle pre_process failed");
    }

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcacHandle::processing() {
    XCamReturn ret                              = XCAM_RETURN_NO_ERROR;
    RkAiqAlgoDescription* des                   = (RkAiqAlgoDescription*)mDes;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared  = nullptr;

    int groupId = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_ACAC);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;
    RkAiqIspStats* ispStats = shared->ispStats;

    ret = RkAiqHandle::processing();
    RKAIQCORE_CHECK_RET(ret, "acac handle processing failed");

    if (mDes->id != 0) {
        ret = des->processing(mProcInParam, mProcOutParam);
        RKAIQCORE_CHECK_RET(ret, "acac algo processing failed");
    }

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAcacHandle::postProcess() {
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret                              = XCAM_RETURN_NO_ERROR;
    RkAiqAlgoDescription* des                   = (RkAiqAlgoDescription*)mDes;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared  = nullptr;

    int groupId = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_ACAC);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;

    ret = RkAiqHandle::postProcess();
    RKAIQCORE_CHECK_RET(ret, "acac handle postProcess failed");

    if (mDes->id != 0) {
        ret = des->post_process(mPostInParam, mPostOutParam);
        RKAIQCORE_CHECK_RET(ret, "acac algo postProcess failed");
    }

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

};  // namespace RkCam
