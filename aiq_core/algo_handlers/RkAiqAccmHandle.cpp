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

void RkAiqAccmHandleInt::init() {
    ENTER_ANALYZER_FUNCTION();

    RkAiqHandle::deInit();
    mConfig       = (RkAiqAlgoCom*)(new RkAiqAlgoConfigAccmInt());
    mPreInParam   = (RkAiqAlgoCom*)(new RkAiqAlgoPreAccmInt());
    mPreOutParam  = (RkAiqAlgoResCom*)(new RkAiqAlgoPreResAccmInt());
    mProcInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoProcAccmInt());
    mProcOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoProcResAccmInt());
    mPostInParam  = (RkAiqAlgoCom*)(new RkAiqAlgoPostAccmInt());
    mPostOutParam = (RkAiqAlgoResCom*)(new RkAiqAlgoPostResAccmInt());

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn RkAiqAccmHandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        // TODO
        rk_aiq_uapi_accm_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }

    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAccmHandleInt::setAttrib(rk_aiq_ccm_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurAtt, &att, sizeof(rk_aiq_ccm_attrib_t))) {
        mNewAtt   = att;
        updateAtt = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAccmHandleInt::getAttrib(rk_aiq_ccm_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_accm_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAccmHandleInt::queryCcmInfo(rk_aiq_ccm_querry_info_t* ccm_querry_info) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapi_accm_QueryCcmInfo(mAlgoCtx, ccm_querry_info);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAccmHandleInt::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = RkAiqHandle::prepare();
    RKAIQCORE_CHECK_RET(ret, "accm handle prepare failed");

    RkAiqAlgoConfigAccmInt* accm_config_int = (RkAiqAlgoConfigAccmInt*)mConfig;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->prepare(mConfig);
    RKAIQCORE_CHECK_RET(ret, "accm algo prepare failed");

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAccmHandleInt::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPreAccmInt* accm_pre_int        = (RkAiqAlgoPreAccmInt*)mPreInParam;
    RkAiqAlgoPreResAccmInt* accm_pre_res_int = (RkAiqAlgoPreResAccmInt*)mPreOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPreResComb* comb                       = &shared->preResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::preProcess();
    if (ret) {
        comb->accm_pre_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "accm handle preProcess failed");
    }

    comb->accm_pre_res = NULL;

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->pre_process(mPreInParam, mPreOutParam);
    RKAIQCORE_CHECK_RET(ret, "accm algo pre_process failed");

    // set result to mAiqCore
    comb->accm_pre_res = (RkAiqAlgoPreResAccm*)accm_pre_res_int;

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqAccmHandleInt::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoProcAccmInt* accm_proc_int        = (RkAiqAlgoProcAccmInt*)mProcInParam;
    RkAiqAlgoProcResAccmInt* accm_proc_res_int = (RkAiqAlgoProcResAccmInt*)mProcOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqProcResComb* comb                      = &shared->procResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::processing();
    if (ret) {
        comb->accm_proc_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "accm handle processing failed");
    }

    comb->accm_proc_res = NULL;
    // TODO should check if the rk awb algo used
#if 0
    RkAiqAlgoProcResAwb* awb_res =
        (RkAiqAlgoProcResAwb*)(shared->procResComb.awb_proc_res);
    RkAiqAlgoProcResAwbInt* awb_res_int =
        (RkAiqAlgoProcResAwbInt*)(shared->procResComb.awb_proc_res);

    if(awb_res ) {
        if(awb_res->awb_gain_algo.grgain < DIVMIN ||
                awb_res->awb_gain_algo.gbgain < DIVMIN ) {
            LOGE("get wrong awb gain from AWB module ,use default value ");
        } else {
            accm_proc_int->accm_sw_info.awbGain[0] =
                awb_res->awb_gain_algo.rgain / awb_res->awb_gain_algo.grgain;

            accm_proc_int->accm_sw_info.awbGain[1] = awb_res->awb_gain_algo.bgain / awb_res->awb_gain_algo.gbgain;
        }
        accm_proc_int->accm_sw_info.awbIIRDampCoef =  awb_res_int->awb_smooth_factor;
        accm_proc_int->accm_sw_info.varianceLuma = awb_res_int->varianceLuma;
        accm_proc_int->accm_sw_info.awbConverged = awb_res_int->awbConverged;
    } else {
        LOGE("fail to get awb gain form AWB module,use default value ");
    }
    RkAiqAlgoPreResAeInt *ae_int = (RkAiqAlgoPreResAeInt*)shared->preResComb.ae_pre_res;
    if( ae_int) {
        if(sharedCom->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
            accm_proc_int->accm_sw_info.sensorGain = ae_int->ae_pre_res_rk.LinearExp.exp_real_params.analog_gain
                    * ae_int->ae_pre_res_rk.LinearExp.exp_real_params.digital_gain
                    * ae_int->ae_pre_res_rk.LinearExp.exp_real_params.isp_dgain;
        } else if((rk_aiq_working_mode_t)sharedCom->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2
                  && (rk_aiq_working_mode_t)sharedCom->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR3)  {
            LOGD("%sensor gain choose from second hdr frame for accm");
            accm_proc_int->accm_sw_info.sensorGain = ae_int->ae_pre_res_rk.HdrExp[1].exp_real_params.analog_gain
                    * ae_int->ae_pre_res_rk.HdrExp[1].exp_real_params.digital_gain
                    * ae_int->ae_pre_res_rk.HdrExp[1].exp_real_params.isp_dgain;
        } else if((rk_aiq_working_mode_t)sharedCom->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2
                  && (rk_aiq_working_mode_t)sharedCom->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR3)  {
            LOGD("sensor gain choose from third hdr frame for accm");
            accm_proc_int->accm_sw_info.sensorGain = ae_int->ae_pre_res_rk.HdrExp[2].exp_real_params.analog_gain
                    * ae_int->ae_pre_res_rk.HdrExp[2].exp_real_params.digital_gain
                    * ae_int->ae_pre_res_rk.HdrExp[2].exp_real_params.isp_dgain;
        } else {
            LOGE("working_mode (%d) is invaild ,fail to get sensor gain form AE module,use default value ",
                 sharedCom->working_mode);
        }
    } else {
        LOGE("fail to get sensor gain form AE module,use default value ");
    }
#else
    XCamVideoBuffer* xCamAwbProcRes = shared->res_comb.awb_proc_res;
    if (xCamAwbProcRes) {
        RkAiqAlgoProcResAwbInt* awb_res_int =
            (RkAiqAlgoProcResAwbInt*)xCamAwbProcRes->map(xCamAwbProcRes);
        RkAiqAlgoProcResAwb* awb_res = &awb_res_int->awb_proc_res_com;
        if (awb_res) {
            if (awb_res->awb_gain_algo.grgain < DIVMIN || awb_res->awb_gain_algo.gbgain < DIVMIN) {
                LOGW("get wrong awb gain from AWB module ,use default value ");
            } else {
                accm_proc_int->accm_sw_info.awbGain[0] =
                    awb_res->awb_gain_algo.rgain / awb_res->awb_gain_algo.grgain;

                accm_proc_int->accm_sw_info.awbGain[1] =
                    awb_res->awb_gain_algo.bgain / awb_res->awb_gain_algo.gbgain;
            }
            accm_proc_int->accm_sw_info.awbIIRDampCoef = awb_res_int->awb_smooth_factor;
            accm_proc_int->accm_sw_info.varianceLuma   = awb_res_int->varianceLuma;
            accm_proc_int->accm_sw_info.awbConverged   = awb_res_int->awbConverged;
        } else {
            LOGW("fail to get awb gain form AWB module,use default value ");
        }
    } else {
        LOGW("fail to get awb gain form AWB module,use default value ");
    }
    RKAiqAecExpInfo_t* pCurExp = &shared->curExp;
    if (pCurExp) {
        if ((rk_aiq_working_mode_t)sharedCom->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
            accm_proc_int->accm_sw_info.sensorGain =
                pCurExp->LinearExp.exp_real_params.analog_gain *
                pCurExp->LinearExp.exp_real_params.digital_gain *
                pCurExp->LinearExp.exp_real_params.isp_dgain;
        } else if ((rk_aiq_working_mode_t)sharedCom->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2 &&
                   (rk_aiq_working_mode_t)sharedCom->working_mode < RK_AIQ_WORKING_MODE_ISP_HDR3) {
            LOGD("sensor gain choose from second hdr frame for accm");
            accm_proc_int->accm_sw_info.sensorGain =
                pCurExp->HdrExp[1].exp_real_params.analog_gain *
                pCurExp->HdrExp[1].exp_real_params.digital_gain *
                pCurExp->HdrExp[1].exp_real_params.isp_dgain;
        } else if ((rk_aiq_working_mode_t)sharedCom->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR2 &&
                   (rk_aiq_working_mode_t)sharedCom->working_mode >= RK_AIQ_WORKING_MODE_ISP_HDR3) {
            LOGD("sensor gain choose from third hdr frame for accm");
            accm_proc_int->accm_sw_info.sensorGain =
                pCurExp->HdrExp[2].exp_real_params.analog_gain *
                pCurExp->HdrExp[2].exp_real_params.digital_gain *
                pCurExp->HdrExp[2].exp_real_params.isp_dgain;
        } else {
            LOGE(
                "working_mode (%d) is invaild ,fail to get sensor gain form AE module,use default "
                "value ",
                sharedCom->working_mode);
        }
    } else {
        LOGE("fail to get sensor gain form AE module,use default value ");
    }
#endif

    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->processing(mProcInParam, mProcOutParam);
    RKAIQCORE_CHECK_RET(ret, "accm algo processing failed");

    comb->accm_proc_res = (RkAiqAlgoProcResAccm*)accm_proc_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAccmHandleInt::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RkAiqAlgoPostAccmInt* accm_post_int        = (RkAiqAlgoPostAccmInt*)mPostInParam;
    RkAiqAlgoPostResAccmInt* accm_post_res_int = (RkAiqAlgoPostResAccmInt*)mPostOutParam;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqPostResComb* comb                      = &shared->postResComb;
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqIspStats* ispStats                     = shared->ispStats;

    ret = RkAiqHandle::postProcess();
    if (ret) {
        comb->accm_post_res = NULL;
        RKAIQCORE_CHECK_RET(ret, "accm handle postProcess failed");
        return ret;
    }

    comb->accm_post_res       = NULL;
    RkAiqAlgoDescription* des = (RkAiqAlgoDescription*)mDes;
    ret                       = des->post_process(mPostInParam, mPostOutParam);
    RKAIQCORE_CHECK_RET(ret, "accm algo post_process failed");
    // set result to mAiqCore
    comb->accm_post_res = (RkAiqAlgoPostResAccm*)accm_post_res_int;

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAccmHandleInt::genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret                = XCAM_RETURN_NO_ERROR;
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    RkAiqAlgoProcResAccm* accm_com = shared->procResComb.accm_proc_res;
    rk_aiq_isp_ccm_params_v20_t* ccm_param = params->mCcmParams->data().ptr();

    if (!accm_com) {
        LOGD_ANALYZER("no accm result");
        return XCAM_RETURN_NO_ERROR;
    }

    RkAiqAlgoProcResAccm* accm_rk = (RkAiqAlgoProcResAccm*)accm_com;

    if (sharedCom->init) {
        ccm_param->frame_id = 0;
    } else {
        ccm_param->frame_id = shared->frameId;
    }
    ccm_param->result = accm_rk->accm_hw_conf;

    if (!this->getAlgoId()) {
        RkAiqAlgoProcResAccmInt* accm_rk_int = (RkAiqAlgoProcResAccmInt*)accm_com;
    }

    cur_params->mCcmParams = params->mCcmParams;

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

};  // namespace RkCam
