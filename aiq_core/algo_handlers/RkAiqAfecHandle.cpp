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

void RkAiqAfecHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAfecInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAfecInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAfecInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAfecInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAfecInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAfecInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAfecInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAfecHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "afec handle prepare failed");

    RkAiqAlgoConfigAfecInt* afec_config_int     = (RkAiqAlgoConfigAfecInt*)mConfig;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqIspStats* ispStats = shared->ispStats;

    /* memcpy(&afec_config_int->afec_calib_cfg, &shared->calib->afec, sizeof(CalibDb_FEC_t)); */
    afec_config_int->resource_path = sharedCom->resourcePath;
    afec_config_int->mem_ops_ptr   = mAiqCore->mShareMemOps;
    RkAiqAlgoDescription* des      = (RkAiqAlgoDescription*)mDes;
    ret                            = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "afec algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAfecHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAfecInt* afec_pre_int        = (RkAiqAlgoPreAfecInt*)mPreInParam;
    RkAiqAlgoPreResAfecInt* afec_pre_res_int = (RkAiqAlgoPreResAfecInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->afec_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "afec handle preProcess failed");
    }

    comb->afec_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "afec algo pre_process failed");

    // set result to mAiqCore
    comb->afec_pre_res = (RkAiqAlgoPreResAfec*)afec_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAfecHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAfecInt* afec_proc_int        = (RkAiqAlgoProcAfecInt*)mProcInParam;
    RkAiqAlgoProcResAfecInt* afec_proc_res_int = (RkAiqAlgoProcResAfecInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->afec_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "afec handle processing failed");
    }

    comb->afec_proc_res = NULL;
    // fill procParam
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "afec algo processing failed");

    comb->afec_proc_res = (RkAiqAlgoProcResAfec*)afec_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAfecHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAfecInt* afec_post_int        = (RkAiqAlgoPostAfecInt*)mPostInParam;
    RkAiqAlgoPostResAfecInt* afec_post_res_int = (RkAiqAlgoPostResAfecInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->afec_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "afec handle postProcess failed");
        return ret;
    }

    comb->afec_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "afec algo post_process failed");
    // set result to mAiqCore
    comb->afec_post_res = (RkAiqAlgoPostResAfec*)afec_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAfecHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_afec_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAfecHandleInt::setAttrib(rk_aiq_fec_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(rk_aiq_fec_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAfecHandleInt::getAttrib(rk_aiq_fec_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_afec_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAfecHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                 = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAfec* afec_com = shared->procResComb.afec_proc_res;

    if (!afec_com) {
        LOGD_ANALYZER("no afec result");
        return XCAM_RETURN_NO_ERROR;
    }

    rk_aiq_isp_fec_params_v20_t* fec_params = params->mFecParams->data().ptr();

    if (fec_params->result.usage == RKAIQ_ISPP_FEC_ST_ID) {
        LOGD_ANALYZER("afec not update because EIS enabled");
        return XCAM_RETURN_NO_ERROR;
    }

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAfecInt* afec_rk = (RkAiqAlgoProcResAfecInt*)afec_com;

        if (sharedCom->init) {
            fec_params->frame_id = 0;
        } else {
            fec_params->frame_id = shared->frameId;
        }
        if (afec_rk->afec_result.update) {
            fec_params->update_mask |= RKAIQ_ISPP_FEC_ID;
            fec_params->result.fec_en = afec_rk->afec_result.sw_fec_en;
            if (fec_params->result.fec_en) {
                fec_params->result.crop_en      = afec_rk->afec_result.crop_en;
                fec_params->result.crop_width   = afec_rk->afec_result.crop_width;
                fec_params->result.crop_height  = afec_rk->afec_result.crop_height;
                fec_params->result.mesh_density = afec_rk->afec_result.mesh_density;
                fec_params->result.mesh_size    = afec_rk->afec_result.mesh_size;
                fec_params->result.mesh_buf_fd  = afec_rk->afec_result.mesh_buf_fd;
                // memcpy(fec_params->result.sw_mesh_xi, afec_rk->afec_result.meshxi,
                // sizeof(fec_params->result.sw_mesh_xi)); memcpy(fec_params->result.sw_mesh_xf,
                // afec_rk->afec_result.meshxf, sizeof(fec_params->result.sw_mesh_xf));
                // memcpy(fec_params->result.sw_mesh_yi, afec_rk->afec_result.meshyi,
                // sizeof(fec_params->result.sw_mesh_yi)); memcpy(fec_params->result.sw_mesh_yf,
                // afec_rk->afec_result.meshyf, sizeof(fec_params->result.sw_mesh_yf));
            }
        } else {
            fec_params->update_mask &= ~RKAIQ_ISPP_FEC_ID;
        }
    }

    cur_params->mFecParams = params->mFecParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
