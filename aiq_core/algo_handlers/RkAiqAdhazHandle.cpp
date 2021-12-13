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

void RkAiqAdhazHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAdhazInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAdhazInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAdhazInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAdhazInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAdhazInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAdhazInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAdhazInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAdhazHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "adhaz handle prepare failed");

    RkAiqAlgoConfigAdhazInt* adhaz_config_int   = (RkAiqAlgoConfigAdhazInt*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    adhaz_config_int->calib = sharedCom->calib;

    adhaz_config_int->working_mode      = sharedCom->working_mode;
    adhaz_config_int->is_multi_isp_mode = sharedCom->is_multi_isp_mode;
    // adhaz_config_int->rawHeight = sharedCom->snsDes.isp_acq_height;
    // adhaz_config_int->rawWidth = sharedCom->snsDes.isp_acq_width;
    // adhaz_config_int->working_mode = sharedCom->working_mode;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "adhaz algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAdhazHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAdhazInt* adhaz_pre_int         = (RkAiqAlgoPreAdhazInt*)mPreInParam;
    RkAiqAlgoPreResAdhazInt* adhaz_pre_res_int  = (RkAiqAlgoPreResAdhazInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqIspStats* ispStats = shared->ispStats;
    RkAiqPreResComb* comb   = &shared->preResComb;

    adhaz_pre_int->rawHeight = sharedCom->snsDes.isp_acq_height;
    adhaz_pre_int->rawWidth  = sharedCom->snsDes.isp_acq_width;

    if (!shared->ispStats->adehaze_stats_valid && !sharedCom->init) {
        LOG1("no adehaze stats, ignore!");
        // TODO: keep last result ?
        //
        //
        // return XCAM_RETURN_BYPASS;
    } else {
        // dehaze stats
        if (CHECK_ISP_HW_V20())
            memcpy(&adhaz_pre_int->stats.dehaze_stats_v20,
                   &ispStats->adehaze_stats.dehaze_stats_v20, sizeof(dehaze_stats_v20_t));
        else if (CHECK_ISP_HW_V21())
            memcpy(&adhaz_pre_int->stats.dehaze_stats_v21,
                   &ispStats->adehaze_stats.dehaze_stats_v21, sizeof(dehaze_stats_v21_t));
        else if (CHECK_ISP_HW_V30())
            memcpy(&adhaz_pre_int->stats.dehaze_stats_v30,
                   &ispStats->adehaze_stats.dehaze_stats_v30, sizeof(dehaze_stats_v21_t));

        // other stats
        memcpy(adhaz_pre_int->stats.other_stats.tmo_luma,
               ispStats->aec_stats.ae_data.extra.rawae_big.channelg_xy,
               sizeof(adhaz_pre_int->stats.other_stats.tmo_luma));

        if (sharedCom->working_mode == RK_AIQ_ISP_HDR_MODE_3_FRAME_HDR ||
            sharedCom->working_mode == RK_AIQ_ISP_HDR_MODE_3_LINE_HDR) {
            memcpy(adhaz_pre_int->stats.other_stats.short_luma,
                   ispStats->aec_stats.ae_data.chn[0].rawae_big.channelg_xy,
                   sizeof(adhaz_pre_int->stats.other_stats.short_luma));
            memcpy(adhaz_pre_int->stats.other_stats.middle_luma,
                   ispStats->aec_stats.ae_data.chn[1].rawae_lite.channelg_xy,
                   sizeof(adhaz_pre_int->stats.other_stats.middle_luma));
            memcpy(adhaz_pre_int->stats.other_stats.long_luma,
                   ispStats->aec_stats.ae_data.chn[2].rawae_big.channelg_xy,
                   sizeof(adhaz_pre_int->stats.other_stats.long_luma));
        } else if (sharedCom->working_mode == RK_AIQ_ISP_HDR_MODE_2_FRAME_HDR ||
                   sharedCom->working_mode == RK_AIQ_ISP_HDR_MODE_2_LINE_HDR) {
            memcpy(adhaz_pre_int->stats.other_stats.short_luma,
                   ispStats->aec_stats.ae_data.chn[0].rawae_big.channelg_xy,
                   sizeof(adhaz_pre_int->stats.other_stats.short_luma));
            memcpy(adhaz_pre_int->stats.other_stats.long_luma,
                   ispStats->aec_stats.ae_data.chn[1].rawae_big.channelg_xy,
                   sizeof(adhaz_pre_int->stats.other_stats.long_luma));
        } else
            LOGD("Wrong working mode!!!");
    }

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->adhaz_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adhaz handle preProcess failed");
    }

    comb->adhaz_pre_res = NULL;

#ifdef RK_SIMULATOR_HW
    // nothing todo
#endif
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "adhaz algo pre_process failed");

    // set result to mAiqCore
    comb->adhaz_pre_res = (RkAiqAlgoPreResAdhaz*)adhaz_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAdhazHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAdhazInt* adhaz_proc_int        = (RkAiqAlgoProcAdhazInt*)mProcInParam;
    RkAiqAlgoProcResAdhazInt* adhaz_proc_res_int = (RkAiqAlgoProcResAdhazInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    adhaz_proc_int->hdr_mode = sharedCom->working_mode;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->adhaz_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adhaz handle processing failed");
    }

    adhaz_proc_int->pCalibDehaze = sharedCom->calib;

    comb->adhaz_proc_res = NULL;

#ifdef RK_SIMULATOR_HW
    // nothing todo
#endif
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "adhaz algo processing failed");

    comb->adhaz_proc_res = (RkAiqAlgoProcResAdhaz*)adhaz_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdhazHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAdhazInt* adhaz_post_int        = (RkAiqAlgoPostAdhazInt*)mPostInParam;
    RkAiqAlgoPostResAdhazInt* adhaz_post_res_int = (RkAiqAlgoPostResAdhazInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->adhaz_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "adhaz handle postProcess failed");
        return ret;
    }

    comb->adhaz_post_res      = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "adhaz algo post_process failed");
    // set result to mAiqCore
    comb->adhaz_post_res = (RkAiqAlgoPostResAdhaz*)adhaz_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdhazHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_adehaze_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdhazHandleInt::setSwAttrib(adehaze_sw_s att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(adehaze_sw_s))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdhazHandleInt::getSwAttrib(adehaze_sw_s* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_adehaze_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAdhazHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom  = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAdhaz* adhaz_com             = shared->procResComb.adhaz_proc_res;
    rk_aiq_isp_dehaze_params_v20_t* dehaze_param = params->mDehazeParams->data().ptr();

    if (!adhaz_com) {
        LOGD_ANALYZER("no adhaz result");
        return XCAM_RETURN_NO_ERROR;
    }

    if (sharedCom->init) {
        dehaze_param->frame_id = 0;
    } else {
        dehaze_param->frame_id = shared->frameId;
    }
    dehaze_param->result = adhaz_com->AdehzeProcRes;

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAdhazInt* adhaz_rk = (RkAiqAlgoProcResAdhazInt*)adhaz_com;
    }

    cur_params->mDehazeParams = params->mDehazeParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
