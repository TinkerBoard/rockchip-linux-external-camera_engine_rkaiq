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

XCamReturn RkAiqAeisHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "aeis handle prepare failed");

    RkAiqAlgoConfigAeisInt* aeis_config_int     = (RkAiqAlgoConfigAeisInt*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    aeis_config_int->mem_ops = mAiqCore->mShareMemOps;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "aeis algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

void RkAiqAeisHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAeisInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAeisInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAeisInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAeisInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAeisInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAeisInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAeisInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAeisHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAeisInt* aeis_pre_int          = (RkAiqAlgoPreAeisInt*)mPreInParam;
    RkAiqAlgoPreResAeisInt* aeis_pre_res_int   = (RkAiqAlgoPreResAeisInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared = nullptr;
    int groupId                                = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_ADRC);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->aeis_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aeis handle preProcess failed");
    }

    comb->aeis_pre_res = NULL;

    if (!shared->orbStats && !sharedCom->init) {
        LOGE_AEIS("no orb stats, ignore!");
        return XCAM_RETURN_BYPASS;
    }

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "aeis algo pre_process failed");

    // set result to mAiqCore
    comb->aeis_pre_res = (RkAiqAlgoPreResAeis*)aeis_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAeisHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAeisInt* aeis_proc_int         = (RkAiqAlgoProcAeisInt*)mProcInParam;
    RkAiqAlgoProcResAeisInt* aeis_proc_res_int  = (RkAiqAlgoProcResAeisInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;

    RkAiqCore::RkAiqAlgosGroupShared_t* shared = nullptr;
    int groupId                                = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_AEIS);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;

    RkAiqProcResComb* comb = &shared->procResComb;
    aeis_proc_int->orb_stats_buf = shared->orbStats;
    aeis_proc_int->nr_img_buf    = shared->nrImg;
    aeis_proc_int->common.sof    = shared->sof;

    // Formula:
    // ΔTs : reset time duration per row
    // ΔTr : readout time duration per row
    // ΔTe : expsure time duration per row
    // M : image sensor total row count
    // Y : the Yth row, 1 < Y < M
    // Ts(y) : the reset time(point) of Y row
    // Tr(y) : the readout time(point) of Y row
    // Ts(y) = Tr(y) - ΔTe - ΔTr - ΔTs
    //
    // ΔTv-blanking : Vertical Blanking Time
    // ΔTv-blanking = Tr((N-1)last) - Tr((N)first)
    // ΔTframe = Tr((N-1)first) - Tr((N)first)
    //
    // ΔTline = HTS / PCLK
    // PPL : Pixels Per Line
    // LPF : Lines Per Frame
    // HTS : Horizental Total Size
    // VTS : Vertical Total Size
    //
    // PCLK = VTS * HTS * FPS
    // ΔTskew : Rolling Shutter Skew
    // ΔTline : line readout time
    // ΔTskew = ΔTline * height

    constexpr const uint64_t nano_seconds_per_second = 1000000000ULL;

    // TODO(Cody): Assume that the sensor is a seamless sensor
    // HDR, Coded Rolling Shutter is not included in this case
    aeis_proc_int->common.rolling_shutter_skew =
        sharedCom->snsDes.line_length_pck * nano_seconds_per_second /
        sharedCom->snsDes.vt_pix_clk_freq_hz * sharedCom->snsDes.sensor_output_height;

    // TODO(Cody): The exposure time is identical to integration time
    aeis_proc_int->common.integration_time =
        shared->curExp.LinearExp.exp_real_params.integration_time;
    aeis_proc_int->common.analog_gain  = shared->curExp.LinearExp.exp_real_params.analog_gain;
    aeis_proc_int->common.frame_width  = sharedCom->snsDes.sensor_output_width;
    aeis_proc_int->common.frame_height = sharedCom->snsDes.sensor_output_height;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->aeis_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aeis handle processing failed");
    }

    if (!shared->orbStats && !sharedCom->init) {
        LOGE_AEIS("no orb stats, ignore!");
        return XCAM_RETURN_BYPASS;
    }

    comb->aeis_proc_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "aeis algo processing failed");

    comb->aeis_proc_res = (RkAiqAlgoProcResAeis*)aeis_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeisHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAeisInt* aeis_post_int        = (RkAiqAlgoPostAeisInt*)mPostInParam;
    RkAiqAlgoPostResAeisInt* aeis_post_res_int = (RkAiqAlgoPostResAeisInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared = nullptr;
    int groupId                                = mAiqCore->getGroupId(RK_AIQ_ALGO_TYPE_AEIS);
    if (groupId >= 0) {
        if (mAiqCore->getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
            return XCAM_RETURN_BYPASS;
    } else
        return XCAM_RETURN_BYPASS;
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->aeis_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "aeis handle postProcess failed");
        return ret;
    }

    if (!shared->orbStats && !sharedCom->init) {
        LOGE_AEIS("no orb stats, ignore!");
        return XCAM_RETURN_BYPASS;
    }

    comb->aeis_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "aeis algo post_process failed");
    // set result to mAiqCore
    comb->aeis_post_res = (RkAiqAlgoPostResAeis*)aeis_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeisHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_aeis_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeisHandleInt::setAttrib(rk_aiq_eis_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be efeistive later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(rk_aiq_eis_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeisHandleInt::getAttrib(rk_aiq_eis_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_aeis_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAeisHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAeis* aeis_com              = shared->procResComb.aeis_proc_res;

    if (!aeis_com) {
        LOGD_ANALYZER("no aeis result");
        return XCAM_RETURN_NO_ERROR;
    }

    rk_aiq_isp_fec_params_v20_t* fec_params = params->mFecParams->data().ptr();
    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAeisInt* aeis_rk = (RkAiqAlgoProcResAeisInt*)aeis_com;
        if (sharedCom->init) {
            fec_params->frame_id = 0;
        } else {
            fec_params->frame_id = shared->frameId;
        }

        if (aeis_rk->update) {
            fec_params->update_mask |= RKAIQ_ISPP_FEC_ST_ID;
            fec_params->result.fec_en = aeis_rk->fec_en;
            fec_params->result.usage  = RKAIQ_ISPP_FEC_ST_ID;
            if (fec_params->result.fec_en) {
#if 1
                if (1) {
#else
                if (aeis_rk->fd >= 0) {
#endif
                    fec_params->result.config        = true;
                    fec_params->result.frame_id      = aeis_rk->frame_id;
                    fec_params->frame_id             = aeis_rk->frame_id;
                    fec_params->result.mesh_density  = aeis_rk->mesh_density;
                    fec_params->result.mesh_size     = aeis_rk->mesh_size;
                    fec_params->result.mesh_buf_fd   = aeis_rk->fd;
                    fec_params->result.img_buf_index = aeis_rk->img_buf_index;
                    fec_params->result.img_buf_size  = aeis_rk->img_size;
                } else {
                    fec_params->result.config = false;
                }
            } else {
                fec_params->update_mask &= ~RKAIQ_ISPP_FEC_ST_ID;
            }
        }
        LOGD_AEIS("eis update %d, id %d, fec: en %d, config %d, fd %d, idx %d", aeis_rk->update,
                  fec_params->result.frame_id, fec_params->result.fec_en, fec_params->result.config,
                  fec_params->result.mesh_buf_fd, fec_params->result.img_buf_index);
    }

    cur_params->mFecParams = params->mFecParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
