/*
 * RkAiqHandle.h
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

#include "RkAiqHandle.h"

#include "RkAiqCore.h"

namespace RkCam {

RkAiqHandle::RkAiqHandle(RkAiqAlgoDesComm* des, RkAiqCore* aiqCore)
    : mDes(des), mAiqCore(aiqCore), mEnable(true), mReConfig(false) {
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    mDes->create_context(&mAlgoCtx, (const _AlgoCtxInstanceCfg*)(&sharedCom->ctxCfigs[des->type]));
    mConfig       = NULL;
    mPreInParam   = NULL;
    mPreOutParam  = NULL;
    mProcInParam  = NULL;
    mProcOutParam = NULL;
    mPostInParam  = NULL;
    mPostOutParam = NULL;
    updateAtt = false;
}

RkAiqHandle::~RkAiqHandle() {
    if (mDes) mDes->destroy_context(mAlgoCtx);
}

XCamReturn RkAiqHandle::configInparamsCom(RkAiqAlgoCom* com, int type) {
    ENTER_ANALYZER_FUNCTION();

    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)(getGroupShared());
    RkAiqCore::RkAiqAlgosComShared_t* sharedCom = &mAiqCore->mAlogsComSharedParams;
    xcam_mem_clear(*com);

    RkAiqAlgoComInt* rk_com = NULL;

#define GET_RK_COM(algo) \
    { \
        if (type == RKAIQ_CONFIG_COM_PREPARE) \
            rk_com = &(((RkAiqAlgoConfig##algo##Int*)com)->rk_com); \
        else if (type == RKAIQ_CONFIG_COM_PRE) \
            rk_com = &(((RkAiqAlgoPre##algo##Int*)com)->rk_com); \
        else if (type == RKAIQ_CONFIG_COM_PROC) \
            rk_com = &(((RkAiqAlgoProc##algo##Int*)com)->rk_com); \
        else if (type == RKAIQ_CONFIG_COM_POST) \
            rk_com = &(((RkAiqAlgoPost##algo##Int*)com)->rk_com); \
    } \

    switch (mDes->type) {
    case RK_AIQ_ALGO_TYPE_AE:
        GET_RK_COM(Ae);
        break;
    case RK_AIQ_ALGO_TYPE_AWB:
        GET_RK_COM(Awb);
        break;
    case RK_AIQ_ALGO_TYPE_AF:
        GET_RK_COM(Af);
        break;
    case RK_AIQ_ALGO_TYPE_ABLC:
        GET_RK_COM(Ablc);
        break;
    case RK_AIQ_ALGO_TYPE_ADPCC:
        GET_RK_COM(Adpcc);
        break;
    case RK_AIQ_ALGO_TYPE_AMERGE:
        GET_RK_COM(Amerge);
        break;
    case RK_AIQ_ALGO_TYPE_ATMO:
        GET_RK_COM(Atmo);
        break;
    case RK_AIQ_ALGO_TYPE_ANR:
        GET_RK_COM(Anr);
        break;
    case RK_AIQ_ALGO_TYPE_ALSC:
        GET_RK_COM(Alsc);
        break;
    case RK_AIQ_ALGO_TYPE_AGIC:
        GET_RK_COM(Agic);
        break;
    case RK_AIQ_ALGO_TYPE_ADEBAYER:
        GET_RK_COM(Adebayer);
        break;
    case RK_AIQ_ALGO_TYPE_ACCM:
        GET_RK_COM(Accm);
        break;
    case RK_AIQ_ALGO_TYPE_AGAMMA:
        GET_RK_COM(Agamma);
        break;
    case RK_AIQ_ALGO_TYPE_ADEGAMMA:
        GET_RK_COM(Adegamma);
        break;
    case RK_AIQ_ALGO_TYPE_AWDR:
        GET_RK_COM(Awdr);
        break;
    case RK_AIQ_ALGO_TYPE_ADHAZ:
        GET_RK_COM(Adhaz);
        break;
    case RK_AIQ_ALGO_TYPE_A3DLUT:
        GET_RK_COM(A3dlut);
        break;
    case RK_AIQ_ALGO_TYPE_ALDCH:
        GET_RK_COM(Aldch);
        break;
    case RK_AIQ_ALGO_TYPE_AR2Y:
        GET_RK_COM(Ar2y);
        break;
    case RK_AIQ_ALGO_TYPE_ACP:
        GET_RK_COM(Acp);
        break;
    case RK_AIQ_ALGO_TYPE_AIE:
        GET_RK_COM(Aie);
        break;
    case RK_AIQ_ALGO_TYPE_ASHARP:
        GET_RK_COM(Asharp);
        break;
    case RK_AIQ_ALGO_TYPE_AORB:
        GET_RK_COM(Aorb);
        break;
    case RK_AIQ_ALGO_TYPE_AFEC:
        GET_RK_COM(Afec);
        break;
    case RK_AIQ_ALGO_TYPE_ACGC:
        GET_RK_COM(Acgc);
        break;
    case RK_AIQ_ALGO_TYPE_ASD:
        GET_RK_COM(Asd);
        break;
    case RK_AIQ_ALGO_TYPE_ADRC:
        GET_RK_COM(Adrc);
        break;
    case RK_AIQ_ALGO_TYPE_AYNR:
        GET_RK_COM(Aynr);
        break;
    case RK_AIQ_ALGO_TYPE_ACNR:
        GET_RK_COM(Acnr);
        break;
    case RK_AIQ_ALGO_TYPE_ARAWNR:
        GET_RK_COM(Arawnr);
        break;
    case RK_AIQ_ALGO_TYPE_AEIS:
        GET_RK_COM(Aeis);
        break;
    case RK_AIQ_ALGO_TYPE_AMD:
        GET_RK_COM(Amd);
        break;
    case RK_AIQ_ALGO_TYPE_AMFNR:
        GET_RK_COM(Amfnr);
        break;
    case RK_AIQ_ALGO_TYPE_AGAIN:
        GET_RK_COM(Again);
        break;
    case RK_AIQ_ALGO_TYPE_ACAC:
        GET_RK_COM(Acac);
        break;
    default:
        LOGE_ANALYZER("wrong algo type !");
    }

    if (!rk_com)
        goto out;

    xcam_mem_clear(*rk_com);


    if (type == RKAIQ_CONFIG_COM_PREPARE) {
        com->ctx                     = mAlgoCtx;
        com->frame_id                = shared->frameId;
        com->u.prepare.working_mode  = sharedCom->working_mode;
        com->u.prepare.sns_op_width  = sharedCom->snsDes.isp_acq_width;
        com->u.prepare.sns_op_height = sharedCom->snsDes.isp_acq_height;
        com->u.prepare.conf_type     = sharedCom->conf_type;
        rk_com->u.prepare.calib = (CamCalibDbContext_t*)(sharedCom->calib);
        rk_com->u.prepare.calibv2 = (CamCalibDbV2Context_t*)(sharedCom->calibv2);
    } else {
        com->ctx         = mAlgoCtx;
        com->frame_id    = shared->frameId;
        com->u.proc.init = sharedCom->init;
        rk_com->u.proc.pre_res_comb = &shared->preResComb;
        rk_com->u.proc.proc_res_comb = &shared->procResComb;
        rk_com->u.proc.post_res_comb = &shared->postResComb;
        rk_com->u.proc.iso = sharedCom->iso;
        rk_com->u.proc.fill_light_on = sharedCom->fill_light_on;
        rk_com->u.proc.gray_mode = sharedCom->gray_mode;
        rk_com->u.proc.is_bw_sensor = sharedCom->is_bw_sensor;
        rk_com->u.proc.preExp = &shared->preExp;
        rk_com->u.proc.curExp = &shared->curExp;
        rk_com->u.proc.nxtExp = &shared->nxtExp;
        rk_com->u.proc.res_comb = &shared->res_comb;
    }
out:
    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqHandle::prepare() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (mConfig == NULL) init();
    // build common configs
    RkAiqAlgoCom* cfgParam = mConfig;
    configInparamsCom(cfgParam, RKAIQ_CONFIG_COM_PREPARE);

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqHandle::preProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret         = XCAM_RETURN_NO_ERROR;
    RkAiqAlgoCom* preParam = mPreInParam;

    configInparamsCom(preParam, RKAIQ_CONFIG_COM_PRE);

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqHandle::processing() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret          = XCAM_RETURN_NO_ERROR;
    RkAiqAlgoCom* procParam = mProcInParam;

    configInparamsCom(procParam, RKAIQ_CONFIG_COM_PROC);

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqHandle::postProcess() {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret          = XCAM_RETURN_NO_ERROR;
    RkAiqAlgoCom* postParam = mPostInParam;

    configInparamsCom(postParam, RKAIQ_CONFIG_COM_POST);

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

void RkAiqHandle::deInit() {
    ENTER_ANALYZER_FUNCTION();

#define RKAIQ_DELLET(a) \
    if (a) {            \
        delete a;       \
        a = NULL;       \
    }

    RKAIQ_DELLET(mConfig);
    RKAIQ_DELLET(mPreInParam);
    RKAIQ_DELLET(mPreOutParam);
    RKAIQ_DELLET(mProcInParam);
    RKAIQ_DELLET(mProcOutParam);
    RKAIQ_DELLET(mPostInParam);
    RKAIQ_DELLET(mPostOutParam);

    EXIT_ANALYZER_FUNCTION();
}

void
RkAiqHandle::waitSignal()
{
    if (mAiqCore->isRunningState()) {
        mUpdateCond.timedwait(mCfgMutex, 100000);
    } else {
        updateConfig(false);
    }
}

void
RkAiqHandle::sendSignal()
{
    if (mAiqCore->isRunningState())
        mUpdateCond.signal();
}



};  // namespace RkCam
