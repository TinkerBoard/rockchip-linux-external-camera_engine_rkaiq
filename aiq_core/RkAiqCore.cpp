/*
 * rkisp_aiq_core.h
 *
 *  Copyright (c) 2019 Rockchip Corporation
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

#include <iostream>
#include <fstream>

#include "RkAiqHandleInt.h"
#include "v4l2_buffer_proxy.h"
#include "acp/rk_aiq_algo_acp_itf.h"
#include "ae/rk_aiq_algo_ae_itf.h"
#include "awb/rk_aiq_algo_awb_itf.h"
#include "af/rk_aiq_algo_af_itf.h"
#include "anr/rk_aiq_algo_anr_itf.h"
#include "asd/rk_aiq_algo_asd_itf.h"
#include "amerge/rk_aiq_algo_amerge_itf.h"
#include "atmo/rk_aiq_algo_atmo_itf.h"
#include "adrc/rk_aiq_algo_adrc_itf.h"
#include "asharp/rk_aiq_algo_asharp_itf.h"
#include "adehaze/rk_aiq_algo_adhaz_itf.h"
#include "ablc/rk_aiq_algo_ablc_itf.h"
#include "adpcc/rk_aiq_algo_adpcc_itf.h"
#include "alsc/rk_aiq_algo_alsc_itf.h"
#include "agic/rk_aiq_algo_agic_itf.h"
#include "adebayer/rk_aiq_algo_adebayer_itf.h"
#include "accm/rk_aiq_algo_accm_itf.h"
#include "agamma/rk_aiq_algo_agamma_itf.h"
#include "adegamma/rk_aiq_algo_adegamma_itf.h"
#include "awdr/rk_aiq_algo_awdr_itf.h"
#include "a3dlut/rk_aiq_algo_a3dlut_itf.h"
#include "aldch/rk_aiq_algo_aldch_itf.h"
#include "ar2y/rk_aiq_algo_ar2y_itf.h"
#include "aie/rk_aiq_algo_aie_itf.h"
#include "aorb/rk_aiq_algo_aorb_itf.h"
#include "afec/rk_aiq_algo_afec_itf.h"
#include "acgc/rk_aiq_algo_acgc_itf.h"
#include "aeis/rk_aiq_algo_aeis_itf.h"
#include "amd/rk_aiq_algo_amd_itf.h"
#include "arawnr/rk_aiq_abayernr_algo_itf_v1.h"
#include "aynr/rk_aiq_aynr_algo_itf_v1.h"
#include "auvnr/rk_aiq_auvnr_algo_itf_v1.h"
#include "amfnr/rk_aiq_amfnr_algo_itf_v1.h"
#include "again/rk_aiq_again_algo_itf.h"


#ifdef RK_SIMULATOR_HW
#include "simulator/isp20_hw_simulator.h"
#else
#include "isp20/Isp20Evts.h"
#include "isp20/Isp20StatsBuffer.h"
#include "common/rkisp2-config.h"
#include "isp20/rkispp-config.h"
#endif
#include <fcntl.h>
#include <unistd.h>
#include "SPStreamProcUnit.h"
// #include "MessageBus.h"
#include "shared_data_api_wrapper.h"
#include "RkAiqAnalyzeGroupManager.h"
#ifdef RKAIQ_ENABLE_CAMGROUP
#include "RkAiqCamGroupManager.h"
#endif

namespace RkCam {
#define EPSINON 0.0000001

/*
 * isp/ispp pipeline algos ordered array, and the analyzer
 * will run these algos one by one.
 */
/*
 * isp gets the stats from frame n-1,
 * and the new parameters take effect on frame n+1
 */
#define ISP_PARAMS_EFFECT_DELAY_CNT 2

static RkAiqGrpCondition_t aeGrpCond[]     = {
    [0] = { XCAM_MESSAGE_AEC_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t aeGrpConds     = { grp_conds_array_info(aeGrpCond) };

static RkAiqGrpCondition_t awbGrpCond[]    = {
    [0] = {XCAM_MESSAGE_AE_PRE_RES_OK,      0},
    [1] = {XCAM_MESSAGE_AWB_STATS_OK,       ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t awbGrpConds    = {grp_conds_array_info(awbGrpCond) };

static RkAiqGrpCondition_t measGrpCond[]   = {
    [0] = { XCAM_MESSAGE_ISP_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t measGrpConds   = { grp_conds_array_info(measGrpCond) };

static RkAiqGrpCondition_t otherGrpCond[]  = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
};
static RkAiqGrpConditions_t otherGrpConds  = { grp_conds_array_info(otherGrpCond) };

static RkAiqGrpCondition_t amdGrpCond[]    = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
    [1] = { XCAM_MESSAGE_ISP_POLL_SP_OK,    0 },
    [2] = { XCAM_MESSAGE_ISP_GAIN_OK,       0 },
};
static RkAiqGrpConditions_t amdGrpConds    = { grp_conds_array_info(amdGrpCond) };

static RkAiqGrpCondition_t amfnrGrpCond[]  = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
    [1] = { XCAM_MESSAGE_ISP_GAIN_OK,       0 },
    [2] = { XCAM_MESSAGE_ISPP_GAIN_KG_OK,   0 },
    [3] = { XCAM_MESSAGE_AMD_PROC_RES_OK,   0 },
};
static RkAiqGrpConditions_t amfnrGrpConds  = { grp_conds_array_info(amfnrGrpCond) };

static RkAiqGrpCondition_t aynrGrpCond[]   = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
    [1] = { XCAM_MESSAGE_ISP_GAIN_OK,       0 },
    [2] = { XCAM_MESSAGE_ISPP_GAIN_WR_OK,   0 },
    [3] = { XCAM_MESSAGE_AMD_PROC_RES_OK,   0 },
};
static RkAiqGrpConditions_t aynrGrpConds   = { grp_conds_array_info(aynrGrpCond) };

static RkAiqGrpCondition_t lscGrpCond[]    = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
    [1] = { XCAM_MESSAGE_ISP_POLL_TX_OK,    0 },
    [2] = { XCAM_MESSAGE_AWB_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
    [3] = { XCAM_MESSAGE_AE_PROC_RES_OK,    0 },
};
static RkAiqGrpConditions_t lscGrpConds    = { grp_conds_array_info(lscGrpCond) };

static RkAiqGrpCondition_t eisGrpCond[]    = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
    [1] = { XCAM_MESSAGE_ORB_STATS_OK,      0 },
    [2] = { XCAM_MESSAGE_NR_IMG_OK,         0 },
};
static RkAiqGrpConditions_t eisGrpConds    = { grp_conds_array_info(eisGrpCond) };

static RkAiqGrpCondition_t orbGrpCond[]    = {
    [0] = { XCAM_MESSAGE_ORB_STATS_OK,      0 },
};
static RkAiqGrpConditions_t orbGrpConds    = { grp_conds_array_info(orbGrpCond) };


const static struct RkAiqAlgoDesCommExt g_default_3a_des[] = {
    { &g_RkIspAlgoDescAe.common, RK_AIQ_CORE_ANALYZE_AE, 0, 0, aeGrpConds },
    { &g_RkIspAlgoDescAwb.common, RK_AIQ_CORE_ANALYZE_AWB, 0, 0, awbGrpConds },
    { &g_RkIspAlgoDescAf.common, RK_AIQ_CORE_ANALYZE_MEAS, 0, 0, measGrpConds },
    { &g_RkIspAlgoDescAblc.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAdegamma.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAdpcc.common, RK_AIQ_CORE_ANALYZE_MEAS, 0, 0, measGrpConds },
    { &g_RkIspAlgoDescAmerge.common, RK_AIQ_CORE_ANALYZE_MEAS, 0, 0, measGrpConds },
    { &g_RkIspAlgoDescAtmo.common, RK_AIQ_CORE_ANALYZE_MEAS, 0, 0, measGrpConds },
#if ANR_NO_SEPERATE_MARCO
    { &g_RkIspAlgoDescAnr.common, RK_AIQ_CORE_ANALYZE_MEAS, 0, 0, measGrpConds },
#else
#if 0
    { &g_RkIspAlgoDescArawnr.common, RK_AIQ_CORE_ANALYZE_MEAS, 0, 0, measGrpConds },
    { &g_RkIspAlgoDescAynr.common, RK_AIQ_CORE_ANALYZE_AYNR, 0, 0, aynrGrpConds },
    { &g_RkIspAlgoDescAcnr.common, RK_AIQ_CORE_ANALYZE_MEAS, 0, 0, measGrpConds },
    { &g_RkIspAlgoDescAmfnr.common, RK_AIQ_CORE_ANALYZE_AMFNR, 0, 0, amfnrGrpConds },
    { &g_RkIspAlgoDescAgain.common, RK_AIQ_CORE_ANALYZE_AMFNR, 0, 0, amfnrGrpConds },
#else
    { &g_RkIspAlgoDescArawnr.common, RK_AIQ_CORE_ANALYZE_MEAS, 0, 0, measGrpConds},
    { &g_RkIspAlgoDescAynr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds},
    { &g_RkIspAlgoDescAcnr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds},
    { &g_RkIspAlgoDescAmfnr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds},
    { &g_RkIspAlgoDescAgain.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds},
#endif
#endif
    { &g_RkIspAlgoDescAlsc.common, RK_AIQ_CORE_ANALYZE_LSC, 0, 0, lscGrpConds },
    { &g_RkIspAlgoDescAgic.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAdebayer.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAccm.common, RK_AIQ_CORE_ANALYZE_MEAS, 0, 0, measGrpConds },
    { &g_RkIspAlgoDescAgamma.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAwdr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAdhaz.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescA3dlut.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAldch.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAr2y.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAcp.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAie.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAsharp.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAorb.common, RK_AIQ_CORE_ANALYZE_ORB, 0, 0, orbGrpConds },
    { &g_RkIspAlgoDescAcgc.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAsd.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    //{ &g_RkIspAlgoDescAfec.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpConds },
    { &g_RkIspAlgoDescAeis.common, RK_AIQ_CORE_ANALYZE_EIS, 0, 0, eisGrpConds },
#if 0
    { &g_RkIspAlgoDescAmd.common, RK_AIQ_CORE_ANALYZE_AMD, 0, 0, amdGrpConds },
#endif
    { NULL, RK_AIQ_CORE_ANALYZE_ALL, 0, 0 },
};

bool
RkAiqCoreThread::loop()
{
    ENTER_ANALYZER_FUNCTION();

    const static int32_t timeout = -1;
    SmartPtr<VideoBuffer> stats = mStatsQueue.pop (timeout);

    if (!stats.ptr()) {
        LOGW_ANALYZER("RkAiqCoreThread got empty stats, stop thread");
        return false;
    }

    XCamReturn ret = mRkAiqCore->analyze (stats);
    if (ret == XCAM_RETURN_NO_ERROR || ret == XCAM_RETURN_BYPASS)
        return true;

    LOGE_ANALYZER("RkAiqCoreThread failed to analyze 3a stats");

    EXIT_ANALYZER_FUNCTION();

    return false;
}

bool
RkAiqCoreEvtsThread::loop()
{
    ENTER_ANALYZER_FUNCTION();

    const static int32_t timeout = -1;

    SmartPtr<ispHwEvt_t> evts = mEvtsQueue.pop (timeout);
    if (!evts.ptr()) {
        LOGW_ANALYZER("RkAiqCoreEvtsThread got empty stats, stop thread");
        return false;
    }

    XCamReturn ret = mRkAiqCore->events_analyze (evts);
    if (ret == XCAM_RETURN_NO_ERROR || ret == XCAM_RETURN_BYPASS)
        return true;

    LOGE_ANALYZER("RkAiqCoreEvtsThread failed to analyze events");

    EXIT_ANALYZER_FUNCTION();

    return false;
}

// notice that some pool shared items may be cached by other
// modules(e.g. CamHwIsp20), so here should consider the cached number
uint16_t RkAiqCore::DEFAULT_POOL_SIZE = 15;

RkAiqCore::RkAiqCore()
    : mRkAiqCoreTh(new RkAiqCoreThread(this))
    , mRkAiqCorePpTh(new RkAiqCoreThread(this))
    , mRkAiqCoreEvtsTh(new RkAiqCoreEvtsThread(this))
    , mState(RK_AIQ_CORE_STATE_INVALID)
    , mRkAiqCoreMsgTh(new MessageThread(this))
    , mCb(NULL)
    , mAiqParamsPool(new RkAiqFullParamsPool("RkAiqFullParams", 32))
    , mAiqCpslParamsPool(new RkAiqCpslParamsPool("RkAiqCpslParamsPool", 4))
    , mAiqStatsPool(new RkAiqStatsPool("RkAiqStatsPool", 4))
    , mAiqIspStatsIntPool(new RkAiqIspStatsIntPool("RkAiqIspStatsIntPool", 10))
    , mAiqSofInfoWrapperPool(new RkAiqSofInfoWrapperPool("RkAiqSofPoolWrapper", 16))
    , mAiqAecStatsPool(new RkAiqAecStatsPool("RkAiqAecStatsPool", 16))
    , mAiqAwbStatsPool(new RkAiqAwbStatsPool("RkAiqAwbStatsPool", 16))
    , mAiqAtmoStatsPool(new RkAiqAtmoStatsPool("RkAiqAtmoStatsPool", 10))
    , mAiqAdehazeStatsPool(new RkAiqAdehazeStatsPool("RkAiqAdehazeStatsPool", 10))
    , mAiqAfStatsPool(new RkAiqAfStatsPool("RkAiqAfStatsPool", 10))
    , mAiqOrbStatsIntPool(new RkAiqOrbStatsPool("RkAiqOrbStatsPool", 10))
    , mCustomEnAlgosMask(0xffffffff)
{
    ENTER_ANALYZER_FUNCTION();
    // mAlogsSharedParams.reset();
    mAlogsComSharedParams.reset();
    xcam_mem_clear(mHwInfo);
    mCurCpslOn = false;
    mStrthLed = 0.0f;
    mStrthIr = 0.0f;
    mGrayMode = RK_AIQ_GRAY_MODE_CPSL;
    firstStatsReceived = false;

    SmartPtr<RkAiqFullParams> fullParam = new RkAiqFullParams();
    mAiqCurParams = new RkAiqFullParamsProxy(fullParam );
    mHasPp = true;
    mIspOnline = false;
    mAlgosDesArray = g_default_3a_des;
    mIspHwVer  = 0;
    mSafeEnableAlgo = true;
    mLastAnalyzedId = 0;
#ifdef RKAIQ_ENABLE_CAMGROUP
    mCamGroupCoreManager = NULL;
#endif
    mAllReqAlgoResMask = 0;

    mTranslator = new RkAiqResourceTranslator();
    EXIT_ANALYZER_FUNCTION();
}

RkAiqCore::~RkAiqCore()
{
    ENTER_ANALYZER_FUNCTION();
    if (mAlogsComSharedParams.resourcePath) {
        xcam_free((void*)(mAlogsComSharedParams.resourcePath));
        mAlogsComSharedParams.resourcePath = NULL;
    }
    EXIT_ANALYZER_FUNCTION();
}

void RkAiqCore::initCpsl()
{
    queryCpsLtCap(mCpslCap);

    rk_aiq_cpsl_cfg_t* cfg = &mAlogsComSharedParams.cpslCfg;
    const CamCalibDbContext_t* aiqCalib = mAlogsComSharedParams.calibv2;
    CalibDbV2_Cpsl_t* calibv2_cpsl_db =
        (CalibDbV2_Cpsl_t*)(CALIBDBV2_GET_MODULE_PTR((void*)aiqCalib, cpsl));
    CalibDbV2_Cpsl_Param_t* calibv2_cpsl_calib = &calibv2_cpsl_db->param;
    // TODO: something from calib
    if (mCpslCap.modes_num > 0 && calibv2_cpsl_calib->enable) {
        if (calibv2_cpsl_calib->mode == 0) {
            cfg->mode = RK_AIQ_OP_MODE_AUTO;
        } else if (calibv2_cpsl_calib->mode == 1) {
            cfg->mode = RK_AIQ_OP_MODE_MANUAL;
        } else {
            cfg->mode = RK_AIQ_OP_MODE_INVALID;
        }

        if (calibv2_cpsl_calib->light_src == 0) {
            cfg->lght_src = RK_AIQ_CPSLS_LED;
        } else if (calibv2_cpsl_calib->light_src == 1) {
            cfg->lght_src = RK_AIQ_CPSLS_IR;
        } else if (calibv2_cpsl_calib->light_src == 2) {
            cfg->lght_src = RK_AIQ_CPSLS_MIX;
        } else {
            cfg->lght_src = RK_AIQ_CPSLS_INVALID;
        }
        cfg->gray_on = calibv2_cpsl_calib->force_gray;
        if (cfg->mode == RK_AIQ_OP_MODE_AUTO) {
            cfg->u.a.sensitivity = calibv2_cpsl_calib->auto_adjust_sens;
            cfg->u.a.sw_interval = calibv2_cpsl_calib->auto_sw_interval;
            LOGI_ANALYZER("mode sensitivity %f, interval time %d s\n",
                          cfg->u.a.sensitivity, cfg->u.a.sw_interval);
        } else {
            cfg->u.m.on = calibv2_cpsl_calib->manual_on;
            cfg->u.m.strength_ir = calibv2_cpsl_calib->manual_strength;
            cfg->u.m.strength_led = calibv2_cpsl_calib->manual_strength;
            LOGI_ANALYZER("on %d, strength_led %f, strength_ir %f \n",
                          cfg->u.m.on, cfg->u.m.strength_led, cfg->u.m.strength_ir);
        }
    } else {
        cfg->mode = RK_AIQ_OP_MODE_INVALID;
        LOGI_ANALYZER("not support light compensation \n");
    }
}

XCamReturn
RkAiqCore::init(const char* sns_ent_name, const CamCalibDbContext_t* aiqCalib,
                const CamCalibDbV2Context_t* aiqCalibv2)
{
    ENTER_ANALYZER_FUNCTION();

    if (mState != RK_AIQ_CORE_STATE_INVALID) {
        LOGE_ANALYZER("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_ANALYZER;
    }

    mAlogsComSharedParams.calib = aiqCalib;
    mAlogsComSharedParams.calibv2 = aiqCalibv2;

    const CalibDb_AlgoSwitch_t *algoSwitch = &aiqCalibv2->sys_cfg->algoSwitch;
    if (algoSwitch->enable && algoSwitch->enable_algos) {
        mCustomEnAlgosMask = 0x0;
        for (uint16_t i = 0; i < algoSwitch->enable_algos_len; i++)
            mCustomEnAlgosMask |= 1 << algoSwitch->enable_algos[i];
    }
    LOGI_ANALYZER("mCustomEnAlgosMask: 0x%x\n", mCustomEnAlgosMask);
    addDefaultAlgos(mAlgosDesArray);
    initCpsl();
    newAiqParamsPool();
    newAiqGroupAnayzer();

    mState = RK_AIQ_CORE_STATE_INITED;
    return XCAM_RETURN_NO_ERROR;

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqCore::deInit()
{
    ENTER_ANALYZER_FUNCTION();

    for (auto mapIt = mAlogsGroupSharedParamsMap.begin(); \
            mapIt != mAlogsGroupSharedParamsMap.end();) {
        delete mapIt->second;
        mAlogsGroupSharedParamsMap.erase(mapIt++);
    }
    mAlogsGroupList.clear();

    if (mState == RK_AIQ_CORE_STATE_STARTED || mState == RK_AIQ_CORE_STATE_RUNNING) {
        LOGE_ANALYZER("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_ANALYZER;
    }

    mState = RK_AIQ_CORE_STATE_INVALID;

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::start()
{
    ENTER_ANALYZER_FUNCTION();

    if ((mState != RK_AIQ_CORE_STATE_PREPARED) &&
            (mState != RK_AIQ_CORE_STATE_STOPED)) {
        LOGE_ANALYZER("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_ANALYZER;
    }

    mRkAiqCoreTh->triger_start();
    mRkAiqCoreTh->start();
    if (mHasPp) {
        mRkAiqCorePpTh->triger_start();
        mRkAiqCorePpTh->start();
    }
    mRkAiqCoreEvtsTh->triger_start();
    mRkAiqCoreEvtsTh->start();
    mRkAiqCoreMsgTh->triger_start();
    mRkAiqCoreMsgTh->start();
    mRkAiqCoreGroupManager->start();
    if (mThumbnailsService.ptr()) {
        mThumbnailsService->Start();
    }

    mState = RK_AIQ_CORE_STATE_STARTED;

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::stop()
{
    ENTER_ANALYZER_FUNCTION();

    if (mState != RK_AIQ_CORE_STATE_STARTED && mState != RK_AIQ_CORE_STATE_RUNNING) {
        LOGW_ANALYZER("in state %d\n", mState);
        return XCAM_RETURN_NO_ERROR;
    }

    mRkAiqCoreTh->triger_stop();
    mRkAiqCoreTh->stop();

    if (mHasPp) {
        mRkAiqCorePpTh->triger_stop();
        mRkAiqCorePpTh->stop();
    }
    mRkAiqCoreEvtsTh->triger_stop();
    mRkAiqCoreEvtsTh->stop();


    mRkAiqCoreMsgTh->triger_stop();
    mRkAiqCoreMsgTh->stop();
    mRkAiqCoreGroupManager->stop();
    if (mThumbnailsService.ptr()) {
        mThumbnailsService->Stop();
    }

    mAiqStatsCachedList.clear();
    mAiqStatsOutMap.clear();
    mAlogsComSharedParams.conf_type = RK_AIQ_ALGO_CONFTYPE_INIT;
    mState = RK_AIQ_CORE_STATE_STOPED;
    firstStatsReceived = false;
    mLastAnalyzedId = 0;
    mIspStatsCond.broadcast ();
    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::prepare(const rk_aiq_exposure_sensor_descriptor* sensor_des,
                   int mode)
{
    ENTER_ANALYZER_FUNCTION();
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    // check state
    if ((mState == RK_AIQ_CORE_STATE_STARTED) ||
            (mState == RK_AIQ_CORE_STATE_INVALID) ||
            (mState == RK_AIQ_CORE_STATE_RUNNING)) {
        LOGW_ANALYZER("in state %d\n", mState);
        return XCAM_RETURN_NO_ERROR;
    }

    bool res_changed = (mAlogsComSharedParams.snsDes.isp_acq_width != 0) &&
                       (sensor_des->isp_acq_width != mAlogsComSharedParams.snsDes.isp_acq_width ||
                        sensor_des->isp_acq_height != mAlogsComSharedParams.snsDes.isp_acq_height);
    if (res_changed) {
        mAlogsComSharedParams.conf_type |= RK_AIQ_ALGO_CONFTYPE_CHANGERES;
        LOGD_ANALYZER("resolution changed !");
    }

    if ((mState == RK_AIQ_CORE_STATE_STOPED) ||
            (mState == RK_AIQ_CORE_STATE_PREPARED)) {
        mAlogsComSharedParams.conf_type |= RK_AIQ_ALGO_CONFTYPE_KEEPSTATUS;
        LOGD_ANALYZER("prepare from stopped, should keep algo status !");
    }

    mAlogsComSharedParams.snsDes = *sensor_des;
    mAlogsComSharedParams.working_mode = mode;
    mAlogsComSharedParams.spWidth = mSpWidth;
    mAlogsComSharedParams.spHeight = mSpHeight;
    mAlogsComSharedParams.spAlignedWidth = mSpAlignedWidth;
    mAlogsComSharedParams.spAlignedHeight = mSpAlignedHeight;
    CalibDbV2_ColorAsGrey_t *colorAsGrey =
        (CalibDbV2_ColorAsGrey_t*)CALIBDBV2_GET_MODULE_PTR((void*)(mAlogsComSharedParams.calibv2), colorAsGrey);

    CalibDbV2_Thumbnails_t* thumbnails_config_db =
        (CalibDbV2_Thumbnails_t*)CALIBDBV2_GET_MODULE_PTR((void*)(mAlogsComSharedParams.calibv2), thumbnails);
    if (thumbnails_config_db) {
        CalibDbV2_Thumbnails_Param_t* thumbnails_config = &thumbnails_config_db->param;
        if (thumbnails_config->thumbnail_configs_len > 0) {
            mThumbnailsService = new ThumbnailsService();
            if (mThumbnailsService.ptr()) {
                auto ret = mThumbnailsService->Prepare(thumbnails_config);
                if (ret == XCAM_RETURN_NO_ERROR) {
                    auto cb = std::bind(&RkAiqCore::onThumbnailsResult, this, std::placeholders::_1);
                    mThumbnailsService->SetResultCallback(cb);
                } else {
                    mThumbnailsService.release();
                }
            }
        }
    }

    if ((mAlogsComSharedParams.snsDes.sensor_pixelformat == V4L2_PIX_FMT_GREY) ||
            (mAlogsComSharedParams.snsDes.sensor_pixelformat == V4L2_PIX_FMT_Y10) ||
            (mAlogsComSharedParams.snsDes.sensor_pixelformat == V4L2_PIX_FMT_Y12)) {
        mAlogsComSharedParams.is_bw_sensor = true;
        mGrayMode = RK_AIQ_GRAY_MODE_ON;
        mAlogsComSharedParams.gray_mode = true;
    } else {
        mAlogsComSharedParams.is_bw_sensor = false;
        if (colorAsGrey->param.enable) {
            mAlogsComSharedParams.gray_mode = true;
            mGrayMode = RK_AIQ_GRAY_MODE_ON;
        }
    }

    for (auto algoHdl : mCurIspAlgoHandleList) {
        if (algoHdl.ptr() && algoHdl->getEnable()) {
            /* update user initial params */ \
            ret = algoHdl->updateConfig(true);
            RKAIQCORE_CHECK_BYPASS(ret, "algoHdl %d update initial user params failed", algoHdl->getAlgoType());
            algoHdl->setReConfig(mState == RK_AIQ_CORE_STATE_STOPED);
            ret = algoHdl->prepare();
            RKAIQCORE_CHECK_BYPASS(ret, "algoHdl %d prepare failed", algoHdl->getAlgoType());
        }
    }

    for (auto algoHdl : mCurIsppAlgoHandleList) {
        if (algoHdl.ptr() && algoHdl->getEnable()) {
            /* update user initial params */ \
            ret = algoHdl->updateConfig(true);
            RKAIQCORE_CHECK_BYPASS(ret, "algoHdl %d update initial user params failed", algoHdl->getAlgoType());
            algoHdl->setReConfig(mState == RK_AIQ_CORE_STATE_STOPED);
            ret = algoHdl->prepare();
            RKAIQCORE_CHECK_BYPASS(ret, "algoHdl %d prepare failed", algoHdl->getAlgoType());
        }
    }

    mAlogsComSharedParams.init = true;
    analyzeInternal(RK_AIQ_CORE_ANALYZE_ALL);
    mAlogsComSharedParams.init = false;

#if 0
    if (mAiqCurParams->data()->mIspMeasParams.ptr()) {
        mAiqCurParams->data()->mIspMeasParams->data()->frame_id = 0;
    }

    if (mAiqCurParams->data()->mIspOtherParams.ptr()) {
        mAiqCurParams->data()->mIspOtherParams->data()->frame_id = 0;
    }

    if (mAiqCurParams->data()->mIsppMeasParams.ptr()) {
        mAiqCurParams->data()->mIsppMeasParams->data()->frame_id = 0;
    }

    if (mAiqCurParams->data()->mIsppOtherParams.ptr()) {
        mAiqCurParams->data()->mIsppOtherParams->data()->frame_id = 0;
    }
#endif

    mState = RK_AIQ_CORE_STATE_PREPARED;

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

SmartPtr<RkAiqFullParamsProxy>
RkAiqCore::analyzeInternal(enum rk_aiq_core_analyze_type_e type)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (mAlogsComSharedParams.init) {
        // run algos without stats to generate
        // initial params
        CalibDb_Aec_ParaV2_t* calibv2_ae_calib =
            (CalibDb_Aec_ParaV2_t*)(CALIBDBV2_GET_MODULE_PTR((void*)(mAlogsComSharedParams.calibv2), ae_calib));

        auto mapIter = mAlogsGroupSharedParamsMap.begin();
        while (mapIter != mAlogsGroupSharedParamsMap.end()) {
            RkAiqAlgosGroupShared_t* &shared = mapIter->second;
            shared->reset();
            if (!shared->ispStats) {
                SmartPtr<RkAiqIspStatsIntProxy> ispStats = NULL;
                if (mAiqIspStatsIntPool->has_free_items()) {
                    ispStats = mAiqIspStatsIntPool->get_item();
                }
                shared->ispStats = ispStats->data().ptr();
            }
            shared->frameId = 0;
            shared->ispStats->aec_stats_valid = false;
            shared->ispStats->awb_stats_valid = false;
            shared->ispStats->awb_cfg_effect_valid = false;
            shared->ispStats->af_stats_valid = false;
            shared->ispStats->atmo_stats_valid = false;
            shared->aecStatsBuf = nullptr;

            shared->curExp.LinearExp.exp_real_params.analog_gain = \
                    calibv2_ae_calib->LinearAeCtrl.InitExp.InitGainValue;
            shared->curExp.LinearExp.exp_real_params.integration_time = \
                    calibv2_ae_calib->LinearAeCtrl.InitExp.InitTimeValue;
            for (int32_t i = 0; i < 3; i++) {
                shared->curExp.HdrExp[i].exp_real_params.analog_gain = \
                        calibv2_ae_calib->HdrAeCtrl.InitExp.InitGainValue[i];
                shared->curExp.HdrExp[i].exp_real_params.integration_time = \
                        calibv2_ae_calib->HdrAeCtrl.InitExp.InitTimeValue[i];
            }

            mapIter++;
        }
    }

    SmartPtr<RkAiqFullParamsProxy> aiqParamProxy = NULL;
    if (mAiqParamsPool->has_free_items())
        aiqParamProxy = mAiqParamsPool->get_item();

    if (!aiqParamProxy.ptr()) {
        LOGE_ANALYZER("no free aiq params buffer!");
        return NULL;
    }

    RkAiqFullParams* aiqParams = aiqParamProxy->data().ptr();
    aiqParams->reset();

    ret = getAiqParamsBuffer(aiqParams, type);
    if (ret != XCAM_RETURN_NO_ERROR)
        return NULL;

#if 0
    // for test
    int fd = open("/tmp/cpsl", O_RDWR);
    if (fd != -1) {
        char c;
        read(fd, &c, 1);
        int enable = atoi(&c);

        rk_aiq_cpsl_cfg_t cfg;

        cfg.mode = (RKAiqOPMode_t)enable;
        cfg.lght_src = RK_AIQ_CPSLS_LED;
        if (cfg.mode == RK_AIQ_OP_MODE_AUTO) {
            cfg.u.a.sensitivity = 100;
            cfg.u.a.sw_interval = 60;
            cfg.gray_on = false;
            LOGI_ANALYZER("mode sensitivity %f, interval time %d s\n",
                          cfg.u.a.sensitivity, cfg.u.a.sw_interval);
        } else {
            cfg.gray_on = true;
            cfg.u.m.on = true;
            cfg.u.m.strength_ir = 100;
            cfg.u.m.strength_led = 100;
            LOGI_ANALYZER("on %d, strength_led %f, strength_ir %f\n",
                          cfg.u.m.on, cfg.u.m.strength_led, cfg.u.m.strength_ir);
        }
        close(fd);
        setCpsLtCfg(cfg);
    }
#endif
    ret = preProcess(type);
    RKAIQCORE_CHECK_RET_NULL(ret, "preprocess failed");
    if (type == RK_AIQ_CORE_ANALYZE_OTHER) {
        genCpslResult(aiqParams);
    }

    ret = processing(type);
    RKAIQCORE_CHECK_RET_NULL(ret, "processing failed");

    ret = postProcess(type);
    RKAIQCORE_CHECK_RET_NULL(ret, "post process failed");

    ret = genIspParamsResult(aiqParams, type);

    EXIT_ANALYZER_FUNCTION();

    return aiqParamProxy;
}

XCamReturn
RkAiqCore::getAiqParamsBuffer(RkAiqFullParams* aiqParams, enum rk_aiq_core_analyze_type_e type)
{
#define NEW_PARAMS_BUFFER(lc, BC) \
    if (mAiqIsp##lc##ParamsPool->has_free_items()) { \
        aiqParams->m##lc##Params = mAiqIsp##lc##ParamsPool->get_item(); \
        aiqParams->m##lc##Params->data()->frame_id = -1; \
    } else { \
        LOGE_ANALYZER("no free %s buffer!", #BC); \
        return XCAM_RETURN_ERROR_MEM; \
    } \

    std::vector<SmartPtr<RkAiqHandle>>& algo_list =
        mRkAiqCoreGroupManager->getGroupAlgoList(type);

    for (auto& algoHdl : algo_list) {
        switch (algoHdl->getAlgoType()) {
        case RK_AIQ_ALGO_TYPE_AE:
            if (mAiqExpParamsPool->has_free_items()) {
                aiqParams->mExposureParams = mAiqExpParamsPool->get_item();
            } else {
                LOGE_ANALYZER("no free exposure params buffer!");
                return XCAM_RETURN_ERROR_MEM;
            }

            if (mAiqIrisParamsPool->has_free_items()) {
                aiqParams->mIrisParams = mAiqIrisParamsPool->get_item();
            } else {
                LOGE_ANALYZER("no free iris params buffer!");
                return XCAM_RETURN_ERROR_MEM;
            }

            NEW_PARAMS_BUFFER(Aec, aec);
            NEW_PARAMS_BUFFER(Hist, hist);
            break;
        case RK_AIQ_ALGO_TYPE_AWB:
            NEW_PARAMS_BUFFER(Awb, awb);
            NEW_PARAMS_BUFFER(AwbGain, awb_gain);
            break;
        case RK_AIQ_ALGO_TYPE_AF:
            if (mAiqFocusParamsPool->has_free_items()) {
                aiqParams->mFocusParams = mAiqFocusParamsPool->get_item();
            } else {
                LOGE_ANALYZER("no free focus params buffer!");
                return XCAM_RETURN_ERROR_MEM;
            }
            NEW_PARAMS_BUFFER(Af, af);
            break;
        case RK_AIQ_ALGO_TYPE_ABLC:
            NEW_PARAMS_BUFFER(Blc, blc);
            break;
        case RK_AIQ_ALGO_TYPE_ADPCC:
            NEW_PARAMS_BUFFER(Dpcc, dpcc);
            break;
#if 0
        case RK_AIQ_ALGO_TYPE_AHDR:
            NEW_PARAMS_BUFFER(Hdr, hdr);
            break;
#else
        case RK_AIQ_ALGO_TYPE_AMERGE:
            NEW_PARAMS_BUFFER(Merge, merge);
            break;
        case RK_AIQ_ALGO_TYPE_ATMO:
            NEW_PARAMS_BUFFER(Tmo, tmo);
            break;
#endif
        case RK_AIQ_ALGO_TYPE_ALSC:
            NEW_PARAMS_BUFFER(Lsc, lsc);
            break;
        case RK_AIQ_ALGO_TYPE_AGIC:
            NEW_PARAMS_BUFFER(Gic, gic);
            break;
        case RK_AIQ_ALGO_TYPE_ADEBAYER:
            NEW_PARAMS_BUFFER(Debayer, debayer);
            break;
        case RK_AIQ_ALGO_TYPE_ACCM:
            NEW_PARAMS_BUFFER(Ccm, ccm);
            break;
        case RK_AIQ_ALGO_TYPE_AGAMMA:
            NEW_PARAMS_BUFFER(Agamma, agamma);
            break;
        case RK_AIQ_ALGO_TYPE_AWDR:
            NEW_PARAMS_BUFFER(Wdr, wdr);
            break;
        case RK_AIQ_ALGO_TYPE_ADHAZ:
            NEW_PARAMS_BUFFER(Dehaze, dehaze);
            break;
        case RK_AIQ_ALGO_TYPE_A3DLUT:
            NEW_PARAMS_BUFFER(Lut3d, lut3d);
            break;
        case RK_AIQ_ALGO_TYPE_ALDCH:
            NEW_PARAMS_BUFFER(Ldch, ldch);
            break;
        case RK_AIQ_ALGO_TYPE_AR2Y:
            break;
        case RK_AIQ_ALGO_TYPE_ACP:
            NEW_PARAMS_BUFFER(Cp, cp);
            break;
        case RK_AIQ_ALGO_TYPE_AIE:
            NEW_PARAMS_BUFFER(Ie, ie);
            break;
        case RK_AIQ_ALGO_TYPE_ACGC:
            NEW_PARAMS_BUFFER(Cgc, cgc);
            break;
        case RK_AIQ_ALGO_TYPE_ASD:
            break;
        case RK_AIQ_ALGO_TYPE_ADRC:
            break;
        case RK_AIQ_ALGO_TYPE_ADEGAMMA:
            NEW_PARAMS_BUFFER(Adegamma, adegamma);
            break;
        case RK_AIQ_ALGO_TYPE_ARAWNR:
            NEW_PARAMS_BUFFER(Rawnr, rawnr);
            break;
        case RK_AIQ_ALGO_TYPE_AMFNR:
            NEW_PARAMS_BUFFER(Tnr, tnr);
            break;
        case RK_AIQ_ALGO_TYPE_AYNR:
            NEW_PARAMS_BUFFER(Ynr, ynr);
            break;
        case RK_AIQ_ALGO_TYPE_ACNR:
            NEW_PARAMS_BUFFER(Uvnr, uvnr);
            break;
        case RK_AIQ_ALGO_TYPE_ASHARP:
            NEW_PARAMS_BUFFER(Sharpen, sharpen);
            NEW_PARAMS_BUFFER(Edgeflt, edgeflt);
            break;
        case RK_AIQ_ALGO_TYPE_AORB:
            NEW_PARAMS_BUFFER(Orb, orb);
            break;
        case RK_AIQ_ALGO_TYPE_AFEC:
        case RK_AIQ_ALGO_TYPE_AEIS:
            NEW_PARAMS_BUFFER(Fec, fec);
            break;
        case RK_AIQ_ALGO_TYPE_ANR:
            NEW_PARAMS_BUFFER(Rawnr, rawnr);
            NEW_PARAMS_BUFFER(Tnr, tnr);
            NEW_PARAMS_BUFFER(Ynr, ynr);
            NEW_PARAMS_BUFFER(Uvnr, uvnr);
            NEW_PARAMS_BUFFER(Gain, gain);
            NEW_PARAMS_BUFFER(Motion, motion);
            break;
        case RK_AIQ_ALGO_TYPE_AMD:
            NEW_PARAMS_BUFFER(Md, md);
            break;
        default:
            break;
        }
    }

    return XCAM_RETURN_NO_ERROR;
}

void
RkAiqCore::setResultExpectedEffId(uint32_t& eff_id, enum RkAiqAlgoType_e type)
{
    int groupId = getGroupId(type);
    RkAiqAlgosGroupShared_t* shared = nullptr;

    if (groupId < 0) {
        LOGE_ANALYZER("get group of type %d failed !", type);
        return;
    }

    if (getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR) {
        LOGE_ANALYZER("no shared params for type %d !", type);
        return;
    }

    if (mAlogsComSharedParams.init) {
        // init params, set before streaming
        eff_id = 0;
    } else
        eff_id = shared->frameId;
}

XCamReturn
RkAiqCore::genIspParamsResult(RkAiqFullParams *aiqParams, enum rk_aiq_core_analyze_type_e type)
{
    SmartPtr<RkAiqFullParams> curParams = mAiqCurParams->data();
    for (auto algoHdl : mCurIspAlgoHandleList) {
        if (algoHdl.ptr() && algoHdl->getEnable() &&
            (mAlgoTypeToGrpMaskMap[algoHdl->getAlgoType()] & grpId2GrpMask(type))) {
            algoHdl->genIspResult(aiqParams, curParams.ptr());
        }
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::pushStats(SmartPtr<VideoBuffer> &buffer)
{
    ENTER_ANALYZER_FUNCTION();

    XCAM_ASSERT(buffer.ptr());
    mRkAiqCoreTh->push_stats(buffer);
    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::pushEvts(SmartPtr<ispHwEvt_t> &evts)
{
    ENTER_ANALYZER_FUNCTION();

    XCAM_ASSERT(evts.ptr());

    if (evts->evt_code == V4L2_EVENT_FRAME_SYNC)
        mRkAiqCoreEvtsTh->push_evts(evts);
    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

const RkAiqHandle*
RkAiqCore::getAiqAlgoHandle(const int algo_type)
{
    SmartPtr<RkAiqHandle>* handlePtr = getCurAlgoTypeHandle(algo_type);
    if (handlePtr == nullptr) {
        return NULL;
    }

    return (*handlePtr).ptr();
}

SmartPtr<RkAiqHandle>*
RkAiqCore::getCurAlgoTypeHandle(int algo_type)
{
    if (mCurAlgoHandleMaps.find(algo_type) != mCurAlgoHandleMaps.end())
        return &mCurAlgoHandleMaps.at(algo_type);

    LOGE("can't find algo handle %d", algo_type);
    return NULL;
}

std::map<int, SmartPtr<RkAiqHandle>>*
                                  RkAiqCore::getAlgoTypeHandleMap(int algo_type)
{
    if (mAlgoHandleMaps.find(algo_type) != mAlgoHandleMaps.end())
        return &mAlgoHandleMaps.at(algo_type);

    LOGE("can't find algo map %d", algo_type);
    return NULL;
}

void
RkAiqCore::addDefaultAlgos(const struct RkAiqAlgoDesCommExt* algoDes)
{
    map<int, SmartPtr<RkAiqHandle>> algoMap;
    for (int i = 0; i < RK_AIQ_ALGO_TYPE_MAX; i++) {
        mAlogsComSharedParams.ctxCfigs[i].calib =
            const_cast<CamCalibDbContext_t*>(mAlogsComSharedParams.calib);
        mAlogsComSharedParams.ctxCfigs[i].calibv2 =
            const_cast<CamCalibDbV2Context_t*>(mAlogsComSharedParams.calibv2);
        mAlogsComSharedParams.ctxCfigs[i].cfg_com.isp_hw_version = mIspHwVer;
    }

    for (size_t i = 0; algoDes[i].des != NULL; i++) {
        int algo_type = algoDes[i].des->type;
        // enable only the specified algorithm modules
        if (!(1 << algo_type & mCustomEnAlgosMask))
            continue;
        int32_t grpMask = 1ULL << algoDes[i].group;
        mAlogsComSharedParams.ctxCfigs[algo_type].calib =
            const_cast<CamCalibDbContext_t*>(mAlogsComSharedParams.calib);
        mAlogsComSharedParams.ctxCfigs[algo_type].calibv2 =
            const_cast<CamCalibDbV2Context_t*>(mAlogsComSharedParams.calibv2);
        mAlogsComSharedParams.ctxCfigs[algo_type].cfg_com.module_hw_version = algoDes[i].module_hw_ver;
        mAlgoTypeToGrpMaskMap[algo_type] = grpMask;
        bool isExist = false;
        for(auto it = mAlogsGroupList.begin(); it != mAlogsGroupList.end(); it++) {
            if (*it == algoDes[i].group)
                isExist = true;
        }
        if (!isExist) {
            mAlogsGroupList.push_back(algoDes[i].group);
            auto groupId = algoDes[i].group;
            mAlogsGroupSharedParamsMap[grpMask] = new RkAiqAlgosGroupShared_t;
            mAlogsGroupSharedParamsMap[grpMask]->reset();
            mAlogsGroupSharedParamsMap[grpMask]->groupId = algoDes[i].group;
            mAlogsGroupSharedParamsMap[grpMask]->frameId = 0;
            mAlogsGroupSharedParamsMap[grpMask]->ispStats = NULL;

        }
        algoMap[0] = newAlgoHandle(algoDes[i].des, algoDes[i].algo_ver);
        if (!algoMap[0].ptr()) {
            LOGE_ANALYZER("new algo_type %d handle failed", algo_type);
            continue;
        }
        algoMap[0]->setGroupId(grpMask);
        algoMap[0]->setGroupShared(mAlogsGroupSharedParamsMap[grpMask]);
        mAlgoHandleMaps[algo_type] = algoMap;
        mCurIspAlgoHandleList.push_back(algoMap[0]);
        mCurAlgoHandleMaps[algo_type] = algoMap[0];
        enableAlgo(algo_type, 0, true);
        algoMap.clear();
    }
}

SmartPtr<RkAiqHandle>
RkAiqCore::newAlgoHandle(RkAiqAlgoDesComm* algo, int version)
{
#define NEW_ALGO_HANDLE(lc, BC) \
    if (algo->type == RK_AIQ_ALGO_TYPE_##BC) { \
        if (version == 0) \
            return new RkAiq##lc##HandleInt(algo, this); \
    }\

    NEW_ALGO_HANDLE(Ae, AE);
    NEW_ALGO_HANDLE(Awb, AWB);
    NEW_ALGO_HANDLE(Af, AF);
    NEW_ALGO_HANDLE(Amerge, AMERGE);
    NEW_ALGO_HANDLE(Atmo, ATMO);
    NEW_ALGO_HANDLE(Anr, ANR);
    NEW_ALGO_HANDLE(Adhaz, ADHAZ);
    NEW_ALGO_HANDLE(Asd, ASD);
    NEW_ALGO_HANDLE(Acp, ACP);
    NEW_ALGO_HANDLE(Asharp, ASHARP);
    NEW_ALGO_HANDLE(A3dlut, A3DLUT);
    NEW_ALGO_HANDLE(Ablc, ABLC);
    NEW_ALGO_HANDLE(Accm, ACCM);
    NEW_ALGO_HANDLE(Acgc, ACGC);
    NEW_ALGO_HANDLE(Adebayer, ADEBAYER);
    NEW_ALGO_HANDLE(Adpcc, ADPCC);
    NEW_ALGO_HANDLE(Afec, AFEC);
    NEW_ALGO_HANDLE(Agamma, AGAMMA);
    NEW_ALGO_HANDLE(Agic, AGIC);
    NEW_ALGO_HANDLE(Aie, AIE);
    NEW_ALGO_HANDLE(Aldch, ALDCH);
    NEW_ALGO_HANDLE(Alsc, ALSC);
    NEW_ALGO_HANDLE(Aorb, AORB);
    NEW_ALGO_HANDLE(Ar2y, AR2Y);
    NEW_ALGO_HANDLE(Awdr, AWDR);
    NEW_ALGO_HANDLE(Arawnr, ARAWNR);
    NEW_ALGO_HANDLE(Amfnr, AMFNR);
    NEW_ALGO_HANDLE(Aynr, AYNR);
    NEW_ALGO_HANDLE(Acnr, ACNR);
    NEW_ALGO_HANDLE(Adrc, ADRC);
    NEW_ALGO_HANDLE(Adegamma, ADEGAMMA);
    NEW_ALGO_HANDLE(Aeis, AEIS);
    NEW_ALGO_HANDLE(Amd, AMD);
    NEW_ALGO_HANDLE(Again, AGAIN);
    NEW_ALGO_HANDLE(Acac, ACAC);

    return NULL;
}

XCamReturn
RkAiqCore::addAlgo(RkAiqAlgoDesComm& algo)
{
    ENTER_ANALYZER_FUNCTION();

    std::map<int, SmartPtr<RkAiqHandle>>* algo_map = getAlgoTypeHandleMap(algo.type);

    if (!algo_map) {
        LOGE_ANALYZER("do not support this algo type %d !", algo.type);
        return XCAM_RETURN_ERROR_FAILED;
    }
    // TODO, check if exist befor insert ?
    std::map<int, SmartPtr<RkAiqHandle>>::reverse_iterator rit = algo_map->rbegin();

    algo.id = rit->first + 1;

    int i = 0;
    const struct RkAiqAlgoDesCommExt* def_des = NULL;
    while (mAlgosDesArray[i].des != NULL) {
        if (mAlgosDesArray[i].des->type == algo.type) {
            def_des = &mAlgosDesArray[i];
            break;
        }
        i++;
    }

    // add to map
    SmartPtr<RkAiqHandle> new_hdl = newAlgoHandle(&algo, def_des->algo_ver);
    new_hdl->setEnable(false);
    (*algo_map)[algo.id] = new_hdl;

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

void
RkAiqCore::setReqAlgoResMask(int algoType, bool req)
{
    uint64_t tmp = 0;
    switch (algoType) {
    case RK_AIQ_ALGO_TYPE_AE:
        tmp |= (uint64_t)1 << RESULT_TYPE_EXPOSURE_PARAM;
        tmp |= (uint64_t)1 << RESULT_TYPE_AEC_PARAM;
        tmp |= (uint64_t)1 << RESULT_TYPE_HIST_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AWB:
        tmp |= (uint64_t)1 << RESULT_TYPE_AWB_PARAM;
        tmp |= (uint64_t)1 << RESULT_TYPE_AWBGAIN_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AF:
        tmp |= (uint64_t)1 << RESULT_TYPE_AF_PARAM;
        tmp |= (uint64_t)1 << RESULT_TYPE_FOCUS_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ADPCC:
        tmp |= (uint64_t)1 << RESULT_TYPE_DPCC_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AMERGE:
        tmp |= (uint64_t)1 << RESULT_TYPE_MERGE_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ATMO:
        tmp |= (uint64_t)1 << RESULT_TYPE_TMO_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ACCM:
        tmp |= (uint64_t)1 << RESULT_TYPE_CCM_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ALSC:
        tmp |= (uint64_t)1 << RESULT_TYPE_LSC_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ABLC:
        tmp |= (uint64_t)1 << RESULT_TYPE_BLC_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ARAWNR:
        tmp |= (uint64_t)1 << RESULT_TYPE_RAWNR_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AGIC:
        tmp |= (uint64_t)1 << RESULT_TYPE_GIC_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ADEBAYER:
        tmp |= (uint64_t)1 << RESULT_TYPE_DEBAYER_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ALDCH:
        tmp |= (uint64_t)1 << RESULT_TYPE_LDCH_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_A3DLUT:
        tmp |= (uint64_t)1 << RESULT_TYPE_LUT3D_PARAM ;
        break;
    case RK_AIQ_ALGO_TYPE_ADHAZ:
        tmp |= (uint64_t)1 << RESULT_TYPE_DEHAZE_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AGAMMA:
        tmp |= (uint64_t)1 << RESULT_TYPE_AGAMMA_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ADEGAMMA:
        tmp |= (uint64_t)1 << RESULT_TYPE_ADEGAMMA_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AWDR:
        tmp |= (uint64_t)1 << RESULT_TYPE_WDR_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AGAIN:
        tmp |= (uint64_t)1 << RESULT_TYPE_GAIN_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ACP:
        tmp |= (uint64_t)1 << RESULT_TYPE_CP_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AIE:
        tmp |= (uint64_t)1 << RESULT_TYPE_IE_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AMD:
        tmp |= (uint64_t)1 << RESULT_TYPE_MOTION_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AMFNR:
        tmp |= (uint64_t)1 << RESULT_TYPE_TNR_PARAM ;
        break;
    case RK_AIQ_ALGO_TYPE_AYNR:
        tmp |= (uint64_t)1 << RESULT_TYPE_YNR_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ACNR:
        tmp |= (uint64_t)1 << RESULT_TYPE_UVNR_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ASHARP:
        tmp |= (uint64_t)1 << RESULT_TYPE_SHARPEN_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_AFEC:
    case RK_AIQ_ALGO_TYPE_AEIS:
        tmp |= (uint64_t)1 << RESULT_TYPE_FEC_PARAM;
        break;
    case RK_AIQ_ALGO_TYPE_ADRC:
        tmp |= (uint64_t)1 << RESULT_TYPE_DRC_PARAM ;
        break;
    case RK_AIQ_ALGO_TYPE_ACAC:
        tmp |= (uint64_t)1 << RESULT_TYPE_CAC_PARAM ;
        break;
    default:
        break;
    }

    if (req) {
        mAllReqAlgoResMask |= tmp;
    } else {
        mAllReqAlgoResMask &= ~tmp;
    }
}

XCamReturn
RkAiqCore::enableAlgo(int algoType, int id, bool enable)
{
    ENTER_ANALYZER_FUNCTION();
    // get current algotype handle, get id
    SmartPtr<RkAiqHandle>* cur_algo_hdl = getCurAlgoTypeHandle(algoType);
    if (!cur_algo_hdl) {
        LOGE_ANALYZER("can't find current type %d algo", algoType);
        return XCAM_RETURN_ERROR_FAILED;
    }
    std::map<int, SmartPtr<RkAiqHandle>>* algo_map = getAlgoTypeHandleMap(algoType);
    NULL_RETURN_RET(algo_map, XCAM_RETURN_ERROR_FAILED);
    std::map<int, SmartPtr<RkAiqHandle>>::iterator it = algo_map->find(id);
    bool switch_algo = false;

    if (it == algo_map->end()) {
        LOGE_ANALYZER("can't find type id <%d, %d> algo", algoType, id);
        return XCAM_RETURN_ERROR_FAILED;
    }

    it->second->setEnable(enable);
    /* WARNING:
     * Be careful when use SmartPtr<RkAiqxxxHandle> = SmartPtr<RkAiqHandle>
     * if RkAiqxxxHandle is derived from multiple RkAiqHandle,
     * the ptr of RkAiqxxxHandle and RkAiqHandle IS NOT the same
     * (RkAiqHandle ptr = RkAiqxxxHandle ptr + offset), but seams like
     * SmartPtr do not deal with this correctly.
     */
    if (enable) {
        SmartLock locker (mApiMutex);
        while (mSafeEnableAlgo != true)
            mApiMutexCond.wait(mApiMutex);
        if ((*cur_algo_hdl).ptr() &&
                (*cur_algo_hdl).ptr() != it->second.ptr()) {
            (*cur_algo_hdl)->setEnable(false);
            switch_algo = true;
        }
        *cur_algo_hdl = it->second;
        for (auto& algo : mCurIspAlgoHandleList) {
            if (algo->getAlgoType() == algoType)
                algo = it->second;
        }
        for (auto& algo : mCurIsppAlgoHandleList) {
            if (algo->getAlgoType() == algoType)
                algo = it->second;
        }
        if (switch_algo && (mState >= RK_AIQ_CORE_STATE_PREPARED))
            (*cur_algo_hdl)->prepare();
        setReqAlgoResMask(algoType, true);
    } else {
        setReqAlgoResMask(algoType, false);
    }

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::rmAlgo(int algoType, int id)
{
    ENTER_ANALYZER_FUNCTION();

    // can't remove default algos
    if (id == 0)
        return XCAM_RETURN_NO_ERROR;

    SmartPtr<RkAiqHandle>* cur_algo_hdl = getCurAlgoTypeHandle(algoType);
    if (!cur_algo_hdl) {
        LOGE_ANALYZER("can't find current type %d algo", algoType);
        return XCAM_RETURN_ERROR_FAILED;
    }
    std::map<int, SmartPtr<RkAiqHandle>>* algo_map = getAlgoTypeHandleMap(algoType);
    NULL_RETURN_RET(algo_map, XCAM_RETURN_ERROR_FAILED);
    std::map<int, SmartPtr<RkAiqHandle>>::iterator it = algo_map->find(id);

    if (it == algo_map->end()) {
        LOGE_ANALYZER("can't find type id <%d, %d> algo", algoType, id);
        return XCAM_RETURN_ERROR_FAILED;
    }

    // if it's the current algo handle, clear it
    if ((*cur_algo_hdl).ptr() == it->second.ptr()) {
        (*cur_algo_hdl).release();
        for (auto& algo : mCurIspAlgoHandleList) {
            if (algo->getAlgoType() == algoType)
                algo.release();
        }
        for (auto& algo : mCurIsppAlgoHandleList) {
            if (algo->getAlgoType() == algoType)
                algo.release();
        }
    }

    algo_map->erase(it);

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

bool
RkAiqCore::getAxlibStatus(int algoType, int id)
{
    std::map<int, SmartPtr<RkAiqHandle>>* algo_map = getAlgoTypeHandleMap(algoType);
    NULL_RETURN_RET(algo_map, false);
    std::map<int, SmartPtr<RkAiqHandle>>::iterator it = algo_map->find(id);

    if (it == algo_map->end()) {
        LOGE_ANALYZER("can't find type id <%d, %d> algo", algoType, id);
        return false;
    }

    LOGD_ANALYZER("algo type id <%d,%d> status %s", algoType, id,
                  it->second->getEnable() ? "enable" : "disable");

    return it->second->getEnable();
}

const RkAiqAlgoContext*
RkAiqCore::getEnabledAxlibCtx(const int algo_type)
{
    if (algo_type <= RK_AIQ_ALGO_TYPE_NONE ||
            algo_type >= RK_AIQ_ALGO_TYPE_MAX)
        return NULL;

    SmartPtr<RkAiqHandle>* algo_handle = getCurAlgoTypeHandle(algo_type);

    if (algo_handle == nullptr) {
        return NULL;
    }

    if ((*algo_handle).ptr())
        return (*algo_handle)->getAlgoCtx();
    else
        return NULL;
}

void
RkAiqCore::copyIspStats(SmartPtr<RkAiqAecStatsProxy>& aecStat,
                        SmartPtr<RkAiqAwbStatsProxy>& awbStat,
                        SmartPtr<RkAiqAfStatsProxy>& afStat,
                        rk_aiq_isp_stats_t* to)
{
    if (aecStat.ptr()) {
        to->aec_stats = aecStat->data()->aec_stats;
        to->frame_id = aecStat->data()->frame_id;
    }
    to->awb_hw_ver = 0;
    if (awbStat.ptr())
        to->awb_stats_v200 = awbStat->data()->awb_stats;
    if (afStat.ptr())
        to->af_stats = afStat->data()->af_stats;
}

void
RkAiqCore::cacheIspStatsToList(SmartPtr<RkAiqAecStatsProxy>& aecStat,
                               SmartPtr<RkAiqAwbStatsProxy>& awbStat,
                               SmartPtr<RkAiqAfStatsProxy>& afStat)
{
    SmartLock locker (ispStatsListMutex);
    SmartPtr<RkAiqStatsProxy> stats = NULL;
    if (mAiqStatsPool->has_free_items()) {
        stats = mAiqStatsPool->get_item();
    } else {
        if(mAiqStatsCachedList.empty()) {
            LOGW_ANALYZER("no free or cached stats, user may hold all stats buf !");
            return ;
        }
        stats = mAiqStatsCachedList.front();
        mAiqStatsCachedList.pop_front();
    }

    copyIspStats(aecStat, awbStat, afStat, &stats->data()->result);

    mAiqStatsCachedList.push_back(stats);
    mIspStatsCond.broadcast ();
}

XCamReturn RkAiqCore::get3AStatsFromCachedList(rk_aiq_isp_stats_t **stats, int timeout_ms)
{
    SmartLock locker (ispStatsListMutex);
    int code = 0;
    while (mState != RK_AIQ_CORE_STATE_STOPED &&
            mAiqStatsCachedList.empty() &&
            code == 0) {
        if (timeout_ms < 0)
            code = mIspStatsCond.wait(ispStatsListMutex);
        else
            code = mIspStatsCond.timedwait(ispStatsListMutex, timeout_ms * 1000);
    }

    if (mState == RK_AIQ_CORE_STATE_STOPED) {
        *stats = NULL;
        return XCAM_RETURN_NO_ERROR;
    }

    if (mAiqStatsCachedList.empty()) {
        if (code == ETIMEDOUT) {
            *stats = NULL;
            return XCAM_RETURN_ERROR_TIMEOUT;
        } else {
            *stats = NULL;
            return XCAM_RETURN_ERROR_FAILED;
        }
    }
    SmartPtr<RkAiqStatsProxy> stats_proxy = mAiqStatsCachedList.front();
    mAiqStatsCachedList.pop_front();
    *stats = &stats_proxy->data()->result;
    mAiqStatsOutMap[*stats] = stats_proxy;
    stats_proxy.release();

    return XCAM_RETURN_NO_ERROR;
}

void RkAiqCore::release3AStatsRef(rk_aiq_isp_stats_t *stats)
{
    SmartLock locker (ispStatsListMutex);

    std::map<rk_aiq_isp_stats_t*, SmartPtr<RkAiqStatsProxy>>::iterator it;
    it = mAiqStatsOutMap.find(stats);
    if (it != mAiqStatsOutMap.end()) {
        mAiqStatsOutMap.erase(it);
    }
}

XCamReturn RkAiqCore::get3AStatsFromCachedList(rk_aiq_isp_stats_t &stats)
{
    SmartLock locker (ispStatsListMutex);
    if(!mAiqStatsCachedList.empty()) {
        SmartPtr<RkAiqStatsProxy> stats_proxy = mAiqStatsCachedList.front();
        mAiqStatsCachedList.pop_front();
        stats = stats_proxy->data()->result;
        stats_proxy.release();
        return XCAM_RETURN_NO_ERROR;
    } else {
        return XCAM_RETURN_ERROR_FAILED;
    }
}

XCamReturn
RkAiqCore::analyze(const SmartPtr<VideoBuffer> &buffer)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    {
        SmartLock locker (mApiMutex);
        mSafeEnableAlgo = false;
    }

    if (!firstStatsReceived) {
        firstStatsReceived = true;
        mState = RK_AIQ_CORE_STATE_RUNNING;
    }

    switch (buffer->_buf_type) {
    case ISP_POLL_3A_STATS:
    {
        SmartPtr<RkAiqAecStatsProxy> aecStat = NULL;
        SmartPtr<RkAiqAwbStatsProxy> awbStat = NULL;
        SmartPtr<RkAiqAfStatsProxy> afStat = NULL;
        handleIspStats(buffer);
        handleAecStats(buffer, aecStat);
        handleAwbStats(buffer, awbStat);
        handleAfStats(buffer, afStat);
        cacheIspStatsToList(aecStat, awbStat, afStat);
        handleAtmoStats(buffer);
        handleAdehazeStats(buffer);
    }
    break;
    case ISPP_POLL_TNR_STATS:
        break;
    case ISPP_POLL_NR_STATS:
        handleOrbStats(buffer);
        break;
    case ISP_POLL_SP:
    {
        SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_ISP_POLL_SP_OK,
                buffer->get_sequence(), buffer);
        post_message(msg);
        break;
    }
    case ISP_GAIN:
    {
        SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_ISP_GAIN_OK,
                buffer->get_sequence(), buffer);
        post_message(msg);
        break;
    }
    case ISPP_GAIN_KG:
    {
        SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_ISPP_GAIN_KG_OK,
                buffer->get_sequence(), buffer);
        post_message(msg);
        break;
    }
    case ISPP_GAIN_WR:
    {
        SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_ISPP_GAIN_WR_OK,
                buffer->get_sequence(), buffer);
        post_message(msg);
        break;
    }
    case ISP_NR_IMG:
    {
        SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_NR_IMG_OK,
                buffer->get_sequence(), buffer);
        post_message(msg);
        break;
    }
    case ISP_POLL_TX:
    {
        SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_ISP_POLL_TX_OK,
                buffer->get_sequence(), buffer);
        post_message(msg);
        break;
    }
defalut:
    LOGW_ANALYZER("don't know buffer type: 0x%x!", buffer->_buf_type);
    break;
    }

    return ret;
}

XCamReturn
RkAiqCore::events_analyze(const SmartPtr<ispHwEvt_t> &evts)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqExpParamsProxy> preExpParams = nullptr;
    SmartPtr<RkAiqExpParamsProxy> curExpParams = nullptr;
    SmartPtr<RkAiqExpParamsProxy> nxtExpParams = nullptr;

    const SmartPtr<Isp20Evt> isp20Evts =
        evts.dynamic_cast_ptr<Isp20Evt>();
    uint32_t sequence = isp20Evts->sequence;
    if (sequence == 0)
        return ret;

    uint32_t id = 0, maxId = 0;
    if (sequence > 0)
        id = mLastAnalyzedId + 1 > sequence ? mLastAnalyzedId + 1 : sequence;
    maxId = sequence + isp20Evts->expDelay - 1;

    LOGD_ANALYZER("camId:%d, sequence(%d), expDelay(%d), id(%d), maxId(%d)",
                  mAlogsComSharedParams.mCamPhyId,
                  isp20Evts->sequence, isp20Evts->expDelay,
                  id, maxId);

    while (id <= maxId) {
        if (isp20Evts->getExpInfoParams(preExpParams, id > 0 ? id - 1 : 0 ) < 0) {
            LOGE_ANALYZER("id(%d) get pre exp failed!", id);
            break;
        }
        if (isp20Evts->getExpInfoParams(curExpParams, id) < 0) {
            LOGE_ANALYZER("id(%d) get exp failed!", id);
            break;
        }
        if (isp20Evts->getExpInfoParams(nxtExpParams, id + 1) < 0) {
            LOGE_ANALYZER("id(%d) get exp failed!", id + 1);
            break;
        }

        SmartPtr<RkAiqSofInfoWrapperProxy> sofInfo = NULL;
        if (mAiqSofInfoWrapperPool->has_free_items()) {
            sofInfo = mAiqSofInfoWrapperPool->get_item();
        } else {
            LOGE_ANALYZER("no free item for sofInfo!");
            return XCAM_RETURN_BYPASS;
        }

        sofInfo->data()->sequence = id;
        sofInfo->data()->preExp = preExpParams;
        sofInfo->data()->curExp = curExpParams;
        sofInfo->data()->nxtExp = nxtExpParams;
        sofInfo->data()->sof = isp20Evts->getSofTimeStamp();


        sofInfo->setId(id);
        sofInfo->setType(RK_AIQ_SHARED_TYPE_SOF_INFO);

        SmartPtr<XCamMessage> msg = new RkAiqCoreExpMsg(XCAM_MESSAGE_SOF_INFO_OK,
                id, sofInfo);
        post_message(msg);

        mLastAnalyzedId = id;
        id++;

        LOGD_ANALYZER(">>> Framenum=%d, id=%d, Cur sgain=%f,stime=%f,mgain=%f,mtime=%f,lgain=%f,ltime=%f",
                      isp20Evts->sequence, id, curExpParams->data()->aecExpInfo.HdrExp[0].exp_real_params.analog_gain,
                      curExpParams->data()->aecExpInfo.HdrExp[0].exp_real_params.integration_time,
                      curExpParams->data()->aecExpInfo.HdrExp[1].exp_real_params.analog_gain,
                      curExpParams->data()->aecExpInfo.HdrExp[1].exp_real_params.integration_time,
                      curExpParams->data()->aecExpInfo.HdrExp[2].exp_real_params.analog_gain,
                      curExpParams->data()->aecExpInfo.HdrExp[2].exp_real_params.integration_time);
        LOGD_ANALYZER(">>> Framenum=%d, id=%d, nxt sgain=%f,stime=%f,mgain=%f,mtime=%f,lgain=%f,ltime=%f",
                      isp20Evts->sequence, id, nxtExpParams->data()->aecExpInfo.HdrExp[0].exp_real_params.analog_gain,
                      nxtExpParams->data()->aecExpInfo.HdrExp[0].exp_real_params.integration_time,
                      nxtExpParams->data()->aecExpInfo.HdrExp[1].exp_real_params.analog_gain,
                      nxtExpParams->data()->aecExpInfo.HdrExp[1].exp_real_params.integration_time,
                      nxtExpParams->data()->aecExpInfo.HdrExp[2].exp_real_params.analog_gain,
                      nxtExpParams->data()->aecExpInfo.HdrExp[2].exp_real_params.integration_time);

        LOGD_ANALYZER("analyze the id(%d), sequence(%d), mLastAnalyzedId(%d)",
                      id, sequence, mLastAnalyzedId);
    }

    return ret;
}

XCamReturn
RkAiqCore::preProcess(enum rk_aiq_core_analyze_type_e type)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    std::vector<SmartPtr<RkAiqHandle>>& algo_list =
        mRkAiqCoreGroupManager->getGroupAlgoList(type);

    for (auto& algoHdl : algo_list) {
        if (algoHdl.ptr() && algoHdl->getEnable()) {
            ret = algoHdl->updateConfig(true);
            RKAIQCORE_CHECK_BYPASS(ret, "algoHdl %d updateConfig failed", algoHdl->getAlgoType());
            ret = algoHdl->preProcess();
            RKAIQCORE_CHECK_BYPASS(ret, "algoHdl %d processing failed", algoHdl->getAlgoType());
        }
    }

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::processing(enum rk_aiq_core_analyze_type_e type)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    std::vector<SmartPtr<RkAiqHandle>>& algo_list =
        mRkAiqCoreGroupManager->getGroupAlgoList(type);

    for (auto& algoHdl : algo_list) {
        if (algoHdl.ptr() && algoHdl->getEnable()) {
            ret = algoHdl->processing();
            RKAIQCORE_CHECK_BYPASS(ret, "algoHdl %d processing failed", algoHdl->getAlgoType());
        }
    }


    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::postProcess(enum rk_aiq_core_analyze_type_e type)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    std::vector<SmartPtr<RkAiqHandle>>& algo_list =
        mRkAiqCoreGroupManager->getGroupAlgoList(type);

    for (auto& algoHdl : algo_list) {
        if (algoHdl.ptr() && algoHdl->getEnable()) {
            ret = algoHdl->postProcess();
            RKAIQCORE_CHECK_BYPASS(ret, "algoHdl %d postProcess failed", algoHdl->getAlgoType());
        }
    }

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::setHwInfos(struct RkAiqHwInfo &hw_info)
{
    ENTER_ANALYZER_FUNCTION();
    mHwInfo = hw_info;
    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::setCpsLtCfg(rk_aiq_cpsl_cfg_t &cfg)
{
    ENTER_ANALYZER_FUNCTION();
    if (mState < RK_AIQ_CORE_STATE_INITED) {
        LOGE_ANALYZER("should call afer init");
        return XCAM_RETURN_ERROR_FAILED;
    }

    if (mCpslCap.modes_num == 0)
        return XCAM_RETURN_ERROR_PARAM;

    int i = 0;
    for (; i < mCpslCap.modes_num; i++) {
        if (mCpslCap.supported_modes[i] == cfg.mode)
            break;
    }

    if (i == mCpslCap.modes_num) {
        return XCAM_RETURN_ERROR_PARAM;
    }

    if (cfg.mode == RK_AIQ_OP_MODE_AUTO) {
        mAlogsComSharedParams.cpslCfg.u.a = cfg.u.a;
    } else if (cfg.mode == RK_AIQ_OP_MODE_MANUAL) {
        mAlogsComSharedParams.cpslCfg.u.m = cfg.u.m;
    } else {
        return XCAM_RETURN_ERROR_PARAM;
    }

    mAlogsComSharedParams.cpslCfg.mode = cfg.mode;

    for (i = 0; i < mCpslCap.lght_src_num; i++) {
        if (mCpslCap.supported_lght_src[i] == cfg.lght_src)
            break;
    }

    if (i == mCpslCap.lght_src_num) {
        return XCAM_RETURN_ERROR_PARAM;
    }

    mAlogsComSharedParams.cpslCfg = cfg;
    LOGD("set cpsl: mode %d", cfg.mode);
    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::getCpsLtInfo(rk_aiq_cpsl_info_t &info)
{
    ENTER_ANALYZER_FUNCTION();
    if (mState < RK_AIQ_CORE_STATE_INITED) {
        LOGE_ANALYZER("should call afer init");
        return XCAM_RETURN_ERROR_FAILED;
    }

    info.mode = mAlogsComSharedParams.cpslCfg.mode;
    if (info.mode == RK_AIQ_OP_MODE_MANUAL) {
        info.on = mAlogsComSharedParams.cpslCfg.u.m.on;
        info.strength_led = mAlogsComSharedParams.cpslCfg.u.m.strength_led;
        info.strength_ir = mAlogsComSharedParams.cpslCfg.u.m.strength_ir;
    } else {
        info.on = mCurCpslOn;
        info.gray = mAlogsComSharedParams.gray_mode;
    }

    info.lght_src = mAlogsComSharedParams.cpslCfg.lght_src;
    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::queryCpsLtCap(rk_aiq_cpsl_cap_t &cap)
{
    ENTER_ANALYZER_FUNCTION();
    if (mHwInfo.fl_supported || mHwInfo.irc_supported) {
        cap.supported_modes[0] = RK_AIQ_OP_MODE_AUTO;
        cap.supported_modes[1] = RK_AIQ_OP_MODE_MANUAL;
        cap.modes_num = 2;
    } else {
        cap.modes_num = 0;
    }

    cap.lght_src_num = 0;
    if (mHwInfo.fl_supported) {
        cap.supported_lght_src[0] = RK_AIQ_CPSLS_LED;
        cap.lght_src_num++;
    }

    if (mHwInfo.irc_supported) {
        cap.supported_lght_src[cap.lght_src_num] = RK_AIQ_CPSLS_IR;
        cap.lght_src_num++;
    }

    if (cap.lght_src_num > 1) {
        cap.supported_lght_src[cap.lght_src_num] = RK_AIQ_CPSLS_MIX;
        cap.lght_src_num++;
    }

    cap.strength_led.min = 0;
    cap.strength_led.max = 100;
    if (!mHwInfo.fl_strth_adj)
        cap.strength_led.step = 100;
    else
        cap.strength_led.step = 1;

    cap.strength_ir.min = 0;
    cap.strength_ir.max = 100;
    if (!mHwInfo.fl_ir_strth_adj)
        cap.strength_ir.step = 100;
    else
        cap.strength_ir.step = 1;

    cap.sensitivity.min = 0;
    cap.sensitivity.max = 100;
    cap.sensitivity.step = 1;

    LOGI("cpsl cap: light_src_num %d, led_step %f, ir_step %f",
         cap.lght_src_num, cap.strength_led.step, cap.strength_ir.step);

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::genCpslResult(RkAiqFullParams* params)
{
    rk_aiq_cpsl_cfg_t* cpsl_cfg = &mAlogsComSharedParams.cpslCfg;

    if (cpsl_cfg->mode == RK_AIQ_OP_MODE_INVALID)
        return XCAM_RETURN_NO_ERROR;

    if (mAiqCpslParamsPool->has_free_items()) {
        params->mCpslParams = mAiqCpslParamsPool->get_item();
    } else {
        LOGW_ANALYZER("no free cpsl params buffer!");
        return XCAM_RETURN_NO_ERROR;
    }

    RKAiqCpslInfoWrapper_t* cpsl_param = params->mCpslParams->data().ptr();
    //xcam_mem_clear(*cpsl_param);

    LOGD_ANALYZER("cpsl mode %d, light src %d", cpsl_cfg->mode, cpsl_cfg->lght_src);
    bool cpsl_on = false;
    bool need_update = false;

    if (cpsl_cfg->mode == RK_AIQ_OP_MODE_MANUAL) {
        if ((mCurCpslOn != cpsl_cfg->u.m.on) ||
                (fabs(mStrthLed - cpsl_cfg->u.m.strength_led) > EPSINON) ||
                (fabs(mStrthIr - cpsl_cfg->u.m.strength_ir) > EPSINON)) {
            need_update = true;
            cpsl_on = cpsl_cfg->u.m.on;
            cpsl_param->fl.power[0] = cpsl_cfg->u.m.strength_led / 100.0f;
            cpsl_param->fl_ir.power[0] = cpsl_cfg->u.m.strength_ir / 100.0f;
        }
    } else {
        RkAiqAlgosGroupShared_t* shared = nullptr;
        int groupId = getGroupId(RK_AIQ_ALGO_TYPE_ASD);
        if (groupId >= 0) {
            if (getGroupSharedParams(groupId, shared) != XCAM_RETURN_NO_ERROR)
                return XCAM_RETURN_BYPASS;
        } else
            return XCAM_RETURN_BYPASS;
        RkAiqAlgoPreResAsdInt* asd_pre_rk = (RkAiqAlgoPreResAsdInt*)shared->preResComb.asd_pre_res;
        if (asd_pre_rk) {
            asd_preprocess_result_t* asd_result = &asd_pre_rk->asd_result;
            if (mCurCpslOn != asd_result->cpsl_on) {
                need_update = true;
                cpsl_on = asd_result->cpsl_on;
            }
        }
        cpsl_param->fl.power[0] = 1.0f;
        cpsl_param->fl_ir.power[0] = 1.0f;
    }

    // need to init cpsl status, cause the cpsl driver state
    // may be not correct
    if (mState == RK_AIQ_CORE_STATE_INITED)
        need_update = true;

    if (need_update) {
        if (cpsl_cfg->lght_src & RK_AIQ_CPSLS_LED) {
            cpsl_param->update_fl = true;
            if (cpsl_on)
                cpsl_param->fl.flash_mode = RK_AIQ_FLASH_MODE_TORCH;
            else
                cpsl_param->fl.flash_mode = RK_AIQ_FLASH_MODE_OFF;
            if (cpsl_on ) {
                cpsl_param->fl.strobe = true;
                mAlogsComSharedParams.fill_light_on = true;
            } else {
                cpsl_param->fl.strobe = false;
                mAlogsComSharedParams.fill_light_on = false;
            }
            LOGD_ANALYZER("cpsl fl mode %d, strength %f, strobe %d",
                          cpsl_param->fl.flash_mode, cpsl_param->fl.power[0],
                          cpsl_param->fl.strobe);
        }

        if (cpsl_cfg->lght_src & RK_AIQ_CPSLS_IR) {
            cpsl_param->update_ir = true;
            if (cpsl_on) {
                cpsl_param->ir.irc_on = true;
                cpsl_param->fl_ir.flash_mode = RK_AIQ_FLASH_MODE_TORCH;
                cpsl_param->fl_ir.strobe = true;
                mAlogsComSharedParams.fill_light_on = true;
            } else {
                cpsl_param->ir.irc_on = false;
                cpsl_param->fl_ir.flash_mode = RK_AIQ_FLASH_MODE_OFF;
                cpsl_param->fl_ir.strobe = false;
                mAlogsComSharedParams.fill_light_on = false;
            }
            LOGD_ANALYZER("cpsl irc on %d, fl_ir: mode %d, strength %f, strobe %d",
                          cpsl_param->ir.irc_on, cpsl_param->fl_ir.flash_mode, cpsl_param->fl_ir.power[0],
                          cpsl_param->fl_ir.strobe);
        }

        if (mGrayMode == RK_AIQ_GRAY_MODE_CPSL) {
            if (mAlogsComSharedParams.fill_light_on && cpsl_cfg->gray_on) {
                mAlogsComSharedParams.gray_mode = true;
            } else
                mAlogsComSharedParams.gray_mode = false;

        } else {
            /* no mutex lock protection for gray_mode with setGrayMode,
             * so need set again here
             */
            if (mGrayMode == RK_AIQ_GRAY_MODE_OFF)
                mAlogsComSharedParams.gray_mode = false;
            else if (mGrayMode == RK_AIQ_GRAY_MODE_ON)
                mAlogsComSharedParams.gray_mode = true;
        }
        mCurCpslOn = cpsl_on;
        mStrthLed = cpsl_cfg->u.m.strength_led;
        mStrthIr = cpsl_cfg->u.m.strength_ir;
    } else {
        cpsl_param->update_ir = false;
        cpsl_param->update_fl = false;
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::setGrayMode(rk_aiq_gray_mode_t mode)
{
    LOGD_ANALYZER("%s: gray mode %d", __FUNCTION__, mode);

    if (mAlogsComSharedParams.is_bw_sensor) {
        LOGE_ANALYZER("%s: not support for black&white sensor", __FUNCTION__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    CalibDbV2_ColorAsGrey_t *colorAsGrey =
        (CalibDbV2_ColorAsGrey_t*)CALIBDBV2_GET_MODULE_PTR((void*)(mAlogsComSharedParams.calibv2), colorAsGrey);

    if (colorAsGrey->param.enable) {
        LOGE_ANALYZER("%s: not support,since color_as_grey is enabled in xml", __FUNCTION__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    mGrayMode = mode;
    if (mode == RK_AIQ_GRAY_MODE_OFF)
        mAlogsComSharedParams.gray_mode = false;
    else if (mode == RK_AIQ_GRAY_MODE_ON)
        mAlogsComSharedParams.gray_mode = true;
    else if (mode == RK_AIQ_GRAY_MODE_CPSL)
        ; // do nothing
    else
        LOGE_ANALYZER("%s: gray mode %d error", __FUNCTION__, mode);

    return XCAM_RETURN_NO_ERROR;
}

rk_aiq_gray_mode_t
RkAiqCore::getGrayMode()
{
    LOGD_ANALYZER("%s: gray mode %d", __FUNCTION__, mGrayMode);
    return mGrayMode;
}

void
RkAiqCore::setSensorFlip(bool mirror, bool flip)
{
    mAlogsComSharedParams.sns_mirror = mirror;
    mAlogsComSharedParams.sns_flip = flip;
}

XCamReturn
RkAiqCore::setCalib(const CamCalibDbContext_t* aiqCalib)
{
    ENTER_ANALYZER_FUNCTION();

    if (mState != RK_AIQ_CORE_STATE_STOPED) {
        LOGE_ANALYZER("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_ANALYZER;
    }

    /* TODO: xuhf WARNING */
    mAlogsComSharedParams.calib = aiqCalib;
    mAlogsComSharedParams.conf_type = RK_AIQ_ALGO_CONFTYPE_UPDATECALIB;

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::setCalib(const CamCalibDbV2Context_t* aiqCalib)
{
    ENTER_ANALYZER_FUNCTION();

    if (mState != RK_AIQ_CORE_STATE_STOPED) {
        LOGE_ANALYZER("wrong state %d\n", mState);
        return XCAM_RETURN_ERROR_ANALYZER;
    }

    /* TODO: xuhf WARNING */
    mAlogsComSharedParams.calibv2 = aiqCalib;
    mAlogsComSharedParams.conf_type = RK_AIQ_ALGO_CONFTYPE_UPDATECALIB;

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqCore::calibTuning(const CamCalibDbV2Context_t* aiqCalib,
                                  ModuleNameList& change_name_list)
{
    ENTER_ANALYZER_FUNCTION();

    if (!aiqCalib || !change_name_list) {
        LOGE_ANALYZER("invalied tuning param\n");
        return XCAM_RETURN_ERROR_PARAM;
    }

    // Fill new calib to the AlogsSharedParams
    /* TODO: xuhf WARNING */
    mAlogsComSharedParams.calibv2 = aiqCalib;
    mAlogsComSharedParams.conf_type = RK_AIQ_ALGO_CONFTYPE_UPDATECALIB;

    std::for_each(std::begin(*change_name_list), std::end(*change_name_list),
    [this](const std::string & name) {
        if (!name.compare(0, 4, "cpsl", 0, 4)) {
            initCpsl();
        } else if (!name.compare(0, 11, "colorAsGrey", 0, 11)) {
            setGrayMode(mGrayMode);
        }
    });

    AlgoList change_list = std::make_shared<std::list<RkAiqAlgoType_t>>();
    std::transform(
        change_name_list->begin(), change_name_list->end(), std::back_inserter(*change_list),
    [](const std::string name) {
        return RkAiqCalibDbV2::string2algostype(name.c_str());
    });

    change_list->sort();
    change_list->unique();

    // Call prepare of the Alog handle annd notify update param
    list<RkAiqAlgoType_t>::iterator it;
    for(it = change_list->begin(); it != change_list->end(); it++) {
        auto algo_handle = getCurAlgoTypeHandle(*it);
        if (algo_handle) {
            (*algo_handle)->updateConfig(true);
            (*algo_handle)->prepare();
        }
    }

    EXIT_ANALYZER_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn RkAiqCore::setMemsSensorIntf(const rk_aiq_mems_sensor_intf_t* intf) {
    if (mState != RK_AIQ_CORE_STATE_INITED) {
        LOGE_ANALYZER("set MEMS sensor intf in wrong aiq state %d !", mState);
        return XCAM_RETURN_ERROR_FAILED;
    }

    mMemsSensorIntf = intf;

    return XCAM_RETURN_NO_ERROR;
}

const rk_aiq_mems_sensor_intf_t* RkAiqCore::getMemsSensorIntf() {
    return mMemsSensorIntf;
}

void RkAiqCore::post_message (SmartPtr<XCamMessage> &msg)
{
    //mRkAiqCoreMsgTh->push_msg(msg);
    mRkAiqCoreGroupManager->handleMessage(msg);
#ifdef RKAIQ_ENABLE_CAMGROUP
    if (mCamGroupCoreManager)
        mCamGroupCoreManager->processAiqCoreMsgs(this, msg);
#endif
}

XCamReturn
RkAiqCore::handle_message (const SmartPtr<XCamMessage> &msg)
{
    //return mRkAiqCoreGroupManager->handleMessage(msg);
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::otherGroupAnalye(uint32_t id, const SmartPtr<RkAiqCoreExpMsg> &msg)
{
    ENTER_ANALYZER_FUNCTION();

    SmartPtr<RkAiqFullParamsProxy> fullParam;
    uint32_t sequence = msg->msg->data()->sequence;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_OTHER);
    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId = msg->msg->data()->sequence;
    shared->preExp = msg->msg->data()->preExp->data()->aecExpInfo;
    shared->curExp = msg->msg->data()->curExp->data()->aecExpInfo;

    LOGI_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_OTHER);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    EXIT_ANALYZER_FUNCTION();
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::aeGroupAnalyze(uint32_t id, XCamVideoBuffer* aecStatsBuf)
{
    uint32_t frameId = id;

    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_AE);
    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId = frameId;
    shared->aecStatsBuf = aecStatsBuf;

    LOGI_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_AE);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::awbGroupAnalyze(int32_t id,
                           XCamVideoBuffer* aePreRes,
                           XCamVideoBuffer* awbStatsBuf)
{
    uint32_t frameId = id;

    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_AWB);
    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId                 = frameId;
    shared->awbStatsBuf             = awbStatsBuf;
    shared->res_comb.ae_pre_res     = aePreRes;

    LOGI_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_AWB);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::measGroupAnalyze(uint32_t id, const SmartPtr<RkAiqCoreIspStatsMsg> &msg, XCamVideoBuffer* aePreRes)
{
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_MEAS);
    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId                 = id;
    shared->ispStats                = msg->msg->data().ptr();
    shared->res_comb.ae_pre_res     = aePreRes;

    LOGI_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_MEAS);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::amdGroupAnalyze(uint32_t id, const SmartPtr<RkAiqCoreExpMsg> &expMsg,
                           XCamVideoBuffer* sp, XCamVideoBuffer* ispGain)
{
    uint32_t frameId = sp->frame_id;
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_AMD);
    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId = frameId;
    shared->sp = sp;
    shared->ispGain = ispGain;
    shared->curExp = expMsg->msg->data()->curExp->data()->aecExpInfo;

    LOGD_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_AMD);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::lscGroupAnalyze(uint32_t id, const SmartPtr<RkAiqCoreExpMsg> &expMsg,
                           XCamVideoBuffer* awbProcRes, XCamVideoBuffer* tx)
{
    uint32_t frameId = expMsg->frame_id;
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_LSC);
    RkAiqAlgosGroupShared_t *shared     = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId                     = frameId;
    shared->tx                          = tx;
    shared->res_comb.awb_proc_res       = awbProcRes;
    shared->curExp                      = expMsg->msg->data()->curExp->data()->aecExpInfo;

    LOGD_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_LSC);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    tx->unref(tx);
    awbProcRes->unref(awbProcRes);

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::thumbnailsGroupAnalyze(rkaiq_image_source_t &thumbnailsSrc)
{
    uint32_t frameId = thumbnailsSrc.frame_id;

    if (mThumbnailsService.ptr())
        mThumbnailsService->OnFrameEvent(thumbnailsSrc);

    thumbnailsSrc.image_source->unref(thumbnailsSrc.image_source);

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::mfnrGroupAnalyze(uint32_t id, const SmartPtr<RkAiqCoreExpMsg> &expMsg,
                            XCamVideoBuffer* ispGain, XCamVideoBuffer* kgGain,
                            rk_aiq_amd_params_t &amdParams)
{
    uint32_t frameId = expMsg->frame_id;
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_AMFNR);
    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId = frameId;
    shared->ispGain = ispGain;
    shared->kgGain = kgGain;
    // shared->amdResParams = amdParams;
    shared->curExp = expMsg->msg->data()->curExp->data()->aecExpInfo;

    LOGD_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_AMFNR);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::ynrGroupAnalyze(uint32_t id, const SmartPtr<RkAiqCoreExpMsg> &expMsg,
                           XCamVideoBuffer* ispGain, XCamVideoBuffer* wrGain,
                           rk_aiq_amd_params_t &amdParams)
{
    uint32_t frameId = expMsg->frame_id;
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_AYNR);
    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId = frameId;
    shared->ispGain = ispGain;
    shared->wrGain = wrGain;
    // shared->amdResParams = amdParams;
    shared->curExp = expMsg->msg->data()->curExp->data()->aecExpInfo;

    LOGD_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_AYNR);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::grp0Analyze(grp0AnalyzerInParams_t &inParams)
{
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_GRP0);
    RkAiqAlgosGroupShared_t *shared     = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId                     = inParams.id;
    shared->aecStatsBuf                 = inParams.aecStatsBuf;
    shared->awbStatsBuf                 = inParams.awbStatsBuf;
    shared->afStatsBuf                  = inParams.afStatsBuf;
    shared->res_comb.ae_pre_res         = inParams.aePreRes;
    shared->res_comb.ae_proc_res        = inParams.aeProcRes;
    shared->preExp                      = inParams.sofInfoMsg->msg->data()->preExp->data()->aecExpInfo;
    shared->curExp                      = inParams.sofInfoMsg->msg->data()->curExp->data()->aecExpInfo;
    shared->nxtExp                      = inParams.sofInfoMsg->msg->data()->nxtExp->data()->aecExpInfo;

    LOGI_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_GRP0);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::grp1Analyze(grp1AnalyzerInParams_t &inParams)
{
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_GRP1);
    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId                 = inParams.id;
    shared->aecStatsBuf             = inParams.aecStatsBuf;
    shared->awbStatsBuf             = inParams.awbStatsBuf;
    shared->afStatsBuf              = inParams.afStatsBuf;
    shared->res_comb.ae_pre_res     = inParams.aePreRes;
    shared->res_comb.awb_proc_res   = inParams.awbProcRes;
    shared->curExp                  = inParams.sofInfoMsg->msg->data()->curExp->data()->aecExpInfo;

    LOGI_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_GRP1);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::afAnalyze(afAnalyzerInParams_t &inParams)
{
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    uint64_t grpMask = grpId2GrpMask(RK_AIQ_CORE_ANALYZE_AF);
    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[grpMask];
    shared->frameId                 = inParams.id;
    shared->aecStatsBuf             = inParams.aecStatsBuf;
    shared->afStatsBuf              = inParams.afStatsBuf;
    shared->res_comb.ae_pre_res     = inParams.aePreRes;
    shared->res_comb.ae_proc_res    = inParams.aeProcRes;
    shared->curExp                  = inParams.expInfo->msg->data()->curExp->data()->aecExpInfo;

    LOGI_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_AF);
    if (fullParam.ptr()) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        if (mCamGroupCoreManager)
            mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
        else if (mCb)
#else
        if (mCb)
#endif
            mCb->rkAiqCalcDone(fullParam);
    }

    return XCAM_RETURN_NO_ERROR;
}


XCamReturn RkAiqCore::eisGroupAnalyze(uint32_t id, const SmartPtr<RkAiqCoreExpMsg>& expMsg,
                                      XCamVideoBuffer* orbStats, XCamVideoBuffer* nrImg) {
    uint32_t frameId = orbStats->frame_id;
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    RkAiqAlgosGroupShared_t* shared = mAlogsGroupSharedParamsMap[RK_AIQ_CORE_ANALYZE_EIS];
    shared->frameId                 = frameId;
    shared->orbStats                = orbStats;
    shared->nrImg                   = nrImg;
    shared->sof                     = expMsg->msg->data()->sof;
    shared->curExp                  = expMsg->msg->data()->curExp->data()->aecExpInfo;

    LOGD_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_EIS);
    if (fullParam.ptr()) {
        if (fullParam->data()->mFecParams.ptr()) {
            rk_aiq_isp_fec_params_v20_t* fec_params = fullParam->data()->mFecParams->data().ptr();
            if (fec_params->update_mask != 0) {
#ifdef RKAIQ_ENABLE_CAMGROUP
                if (mCamGroupCoreManager)
                    mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
                else if (mCb)
#else
                if (mCb)
#endif
                    mCb->rkAiqCalcDone(fullParam);
            }
        }
    }

    if (orbStats != nullptr)
        orbStats->unref(orbStats);

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::orbGroupAnalyze(uint32_t id, XCamVideoBuffer* orbStats)
{
    uint32_t frameId = orbStats->frame_id;
    SmartPtr<RkAiqFullParamsProxy> fullParam;

    RkAiqAlgosGroupShared_t *shared = mAlogsGroupSharedParamsMap[RK_AIQ_CORE_ANALYZE_ORB];
    shared->frameId = frameId;
    shared->orbStats = orbStats;

    LOGD_ANALYZER("%s, start analyzing id(%d)", __FUNCTION__, shared->frameId);

    fullParam = analyzeInternal(RK_AIQ_CORE_ANALYZE_ORB);
#ifdef RKAIQ_ENABLE_CAMGROUP
    if (mCamGroupCoreManager)
        mCamGroupCoreManager->RelayAiqCoreResults(this, fullParam);
    else if (mCb)
#else
    if (mCb)
#endif
        mCb->rkAiqCalcDone(fullParam);

    if (orbStats != nullptr)
        orbStats->unref(orbStats);

    return XCAM_RETURN_NO_ERROR;
}

void RkAiqCore::newAiqParamsPool()
{
    for (auto algoHdl : mCurIspAlgoHandleList) {
        if (algoHdl.ptr() && algoHdl->getEnable()) {
            switch (algoHdl->getAlgoType()) {
            case RK_AIQ_ALGO_TYPE_AE:
                mAiqExpParamsPool           = new RkAiqExpParamsPool("RkAiqExpParams", MAX_AEC_EFFECT_FNUM * 4);
                mAiqIrisParamsPool          = new RkAiqIrisParamsPool("RkAiqIrisParams", 4);
                mAiqIspAecParamsPool        = new RkAiqIspAecParamsPool("RkAiqIspAecParams", RkAiqCore::DEFAULT_POOL_SIZE);
                mAiqIspHistParamsPool       = new RkAiqIspHistParamsPool("RkAiqIspHistParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AWB:
                mAiqIspAwbParamsPool        = new RkAiqIspAwbParamsPool("RkAiqIspAwbParams", RkAiqCore::DEFAULT_POOL_SIZE);
                mAiqIspAwbGainParamsPool    = new RkAiqIspAwbGainParamsPool("RkAiqIspAwbGainParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AF:
                mAiqFocusParamsPool         = new RkAiqFocusParamsPool("RkAiqFocusParams", 4);
                mAiqIspAfParamsPool         = new RkAiqIspAfParamsPool("RkAiqIspAfParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADPCC:
                mAiqIspDpccParamsPool       = new RkAiqIspDpccParamsPool("RkAiqIspDpccParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AMERGE:
                mAiqIspMergeParamsPool      = new RkAiqIspMergeParamsPool("RkAiqIspMergeParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ATMO:
                mAiqIspTmoParamsPool        = new RkAiqIspTmoParamsPool("RkAiqIspTmoParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ACCM:
                mAiqIspCcmParamsPool        = new RkAiqIspCcmParamsPool("RkAiqIspCcmParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ALSC:
                mAiqIspLscParamsPool        = new RkAiqIspLscParamsPool("RkAiqIspLscParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ABLC:
                mAiqIspBlcParamsPool        = new RkAiqIspBlcParamsPool("RkAiqIspBlcParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ARAWNR:
                mAiqIspRawnrParamsPool      = new RkAiqIspRawnrParamsPool("RkAiqIspRawnrParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AGIC:
                mAiqIspGicParamsPool        = new RkAiqIspGicParamsPool("RkAiqIspGicParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADEBAYER:
                mAiqIspDebayerParamsPool    = new RkAiqIspDebayerParamsPool("RkAiqIspDebayerParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ALDCH:
                mAiqIspLdchParamsPool       = new RkAiqIspLdchParamsPool("RkAiqIspLdchParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_A3DLUT:
                mAiqIspLut3dParamsPool      = new RkAiqIspLut3dParamsPool("RkAiqIspLut3dParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADHAZ:
                mAiqIspDehazeParamsPool     = new RkAiqIspDehazeParamsPool("RkAiqIspDehazeParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AGAMMA:
                mAiqIspAgammaParamsPool     = new RkAiqIspAgammaParamsPool("RkAiqIspAgammaParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADEGAMMA:
                mAiqIspAdegammaParamsPool   = new RkAiqIspAdegammaParamsPool("RkAiqIspAdegammaParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AWDR:
                mAiqIspWdrParamsPool        = new RkAiqIspWdrParamsPool("RkAiqIspWdrParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AR2Y:
                mAiqIspCsmParamsPool        = new RkAiqIspCsmParamsPool("RkAiqIspCsmParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ACGC:
                mAiqIspCgcParamsPool        = new RkAiqIspCgcParamsPool("RkAiqIspCgcParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AGAIN:
                mAiqIspGainParamsPool       = new RkAiqIspGainParamsPool("RkAiqIspGainParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ACP:
                mAiqIspCpParamsPool         = new RkAiqIspCpParamsPool("RkAiqIspCpParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AIE:
                mAiqIspIeParamsPool         = new RkAiqIspIeParamsPool("RkAiqIspIeParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AMD:
                mAiqIspMdParamsPool         = new RkAiqIspMdParamsPool("RkAiqIspMdParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AMFNR:
                mAiqIspTnrParamsPool        = new RkAiqIspTnrParamsPool("RkAiqIspTnrParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AYNR:
                mAiqIspYnrParamsPool        = new RkAiqIspYnrParamsPool("RkAiqIspYnrParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ACNR:
                mAiqIspUvnrParamsPool       = new RkAiqIspUvnrParamsPool("RkAiqIspUvnrParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ASHARP:
                mAiqIspSharpenParamsPool    = new RkAiqIspSharpenParamsPool("RkAiqIspSharpenParams", RkAiqCore::DEFAULT_POOL_SIZE);
                mAiqIspEdgefltParamsPool    = new RkAiqIspEdgefltParamsPool("RkAiqIspEdgefltParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AORB:
                mAiqIspOrbParamsPool        = new RkAiqIspOrbParamsPool("RkAiqIspOrbParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AFEC:
            case RK_AIQ_ALGO_TYPE_AEIS:
                mAiqIspFecParamsPool        = new RkAiqIspFecParamsPool("RkAiqIspFecParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            default:
                break;
            }
        }
    }
}

void RkAiqCore::onThumbnailsResult(const rkaiq_thumbnails_t& thumbnail) {
    LOGV_ANALYZER("Callback thumbnail : id:%d, type:%d, 1/%dx1/%d, %dx%d", thumbnail.frame_id,
                  thumbnail.config.stream_type, thumbnail.config.width_intfactor,
                  thumbnail.config.height_intfactor, thumbnail.buffer->info.width,
                  thumbnail.buffer->info.height);
#if 0
    thumbnail.buffer->ref(thumbnail.buffer);
    if (thumbnail.frame_id == 1) {
        char* ptr = reinterpret_cast<char*>(thumbnail.buffer->map(thumbnail.buffer));
        size_t size = thumbnail.buffer->info.size;
        std::string path = "/data/thumbnails_";
        path.append(std::to_string(thumbnail.frame_id));
        path.append("_");
        path.append(std::to_string(thumbnail.buffer->info.width));
        path.append("x");
        path.append(std::to_string(thumbnail.buffer->info.height));
        path.append(".yuv");
        std::ofstream ofs(path, std::ios::binary);
        ofs.write(ptr, size);
        thumbnail.buffer->unmap(thumbnail.buffer);
    }
    thumbnail.buffer->unref(thumbnail.buffer);
#endif
}

int32_t
RkAiqCore::getGroupId(RkAiqAlgoType_t type)
{
    auto mapIter = mAlgoTypeToGrpMaskMap.find(type);
    if (mapIter != mAlgoTypeToGrpMaskMap.end()) {
        return mapIter->second;
    } else {
        LOGW_ANALYZER("don't find the group id of module(0x%x)", type);
        return XCAM_RETURN_ERROR_FAILED;
    }
}

XCamReturn
RkAiqCore::getGroupSharedParams(int32_t groupId, RkAiqAlgosGroupShared_t* &shared)
{
    auto mapIter = mAlogsGroupSharedParamsMap.find(groupId);
    if (mapIter != mAlogsGroupSharedParamsMap.end()) {
        shared = mapIter->second;
    } else {
        LOGW_ANALYZER("don't find the group shared params of group(0x%x)", groupId);
        return XCAM_RETURN_ERROR_FAILED;
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::handleIspStats(const SmartPtr<VideoBuffer> &buffer)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqIspStatsIntProxy> ispStatsInt = NULL;

    if (mAiqIspStatsIntPool->has_free_items()) {
        ispStatsInt = mAiqIspStatsIntPool->get_item();
    } else {
        LOGE_ANALYZER("no free ispStatsInt!");
        return XCAM_RETURN_BYPASS;
    }

    ret = mTranslator->translateIspStats(buffer, ispStatsInt);
    if (ret) {
        LOGE_ANALYZER("translate isp stats failed!");
        return XCAM_RETURN_BYPASS;
    }

    uint32_t id = buffer->get_sequence();
    SmartPtr<XCamMessage> msg = new RkAiqCoreIspStatsMsg(XCAM_MESSAGE_ISP_STATS_OK,
            id, ispStatsInt);
    post_message(msg);

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::handleAecStats(const SmartPtr<VideoBuffer> &buffer, SmartPtr<RkAiqAecStatsProxy>& aecStat_ret)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqAecStatsProxy> aecStats = NULL;

    if (mAiqAecStatsPool->has_free_items()) {
        aecStats = mAiqAecStatsPool->get_item();
    } else {
        LOGE_ANALYZER("no free aecStats buffer!");
        return XCAM_RETURN_BYPASS;
    }
    ret = mTranslator->translateAecStats(buffer, aecStats);
    if (ret < 0) {
        LOGE_ANALYZER("translate aec stats failed!");
        return XCAM_RETURN_BYPASS;
    }

    aecStat_ret = aecStats;

    uint32_t id = buffer->get_sequence();
    SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_AEC_STATS_OK,
            id, aecStats);
    post_message(msg);

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::handleAwbStats(const SmartPtr<VideoBuffer> &buffer, SmartPtr<RkAiqAwbStatsProxy>& awbStat_ret)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqAwbStatsProxy> awbStats = NULL;

    if (mAiqAwbStatsPool->has_free_items()) {
        awbStats = mAiqAwbStatsPool->get_item();
    } else {
        LOGE_ANALYZER("no free awbStats buffer!");
        return XCAM_RETURN_BYPASS;
    }
    ret = mTranslator->translateAwbStats(buffer, awbStats);
    if (ret < 0) {
        LOGE_ANALYZER("translate awb stats failed!");
        return XCAM_RETURN_BYPASS;
    }

    awbStat_ret = awbStats;

    uint32_t id = buffer->get_sequence();
    SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_AWB_STATS_OK,
            id, awbStats);
    post_message(msg);

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::handleAfStats(const SmartPtr<VideoBuffer> &buffer, SmartPtr<RkAiqAfStatsProxy>& afStat_ret)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqAfStatsProxy> afStats = NULL;

    if (mAiqAfStatsPool->has_free_items()) {
        afStats = mAiqAfStatsPool->get_item();
    } else {
        LOGE_ANALYZER("no free afStats buffer!");
        return XCAM_RETURN_BYPASS;
    }
    ret = mTranslator->translateAfStats(buffer, afStats);
    if (ret < 0) {
        LOGE_ANALYZER("translate af stats failed!");
        return XCAM_RETURN_BYPASS;
    }

    afStat_ret = afStats;

    uint32_t id = buffer->get_sequence();
    SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_AF_STATS_OK,
            id, afStats);
    post_message(msg);

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::handleAtmoStats(const SmartPtr<VideoBuffer> &buffer)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqAtmoStatsProxy> atmoStats = NULL;

    if (mAiqAtmoStatsPool->has_free_items()) {
        atmoStats = mAiqAtmoStatsPool->get_item();
    } else {
        LOGE_ANALYZER("no free atmoStats buffer!");
        return XCAM_RETURN_BYPASS;
    }
    ret = mTranslator->translateAtmoStats(buffer, atmoStats);
    if (ret < 0) {
        LOGE_ANALYZER("translate tmo stats failed!");
        return XCAM_RETURN_BYPASS;
    }

    uint32_t id = buffer->get_sequence();
    SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_ATMO_STATS_OK,
            id, atmoStats);
    post_message(msg);

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::handleAdehazeStats(const SmartPtr<VideoBuffer> &buffer)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqAdehazeStatsProxy> adehazeStats = NULL;

    if (mAiqAdehazeStatsPool->has_free_items()) {
        adehazeStats = mAiqAdehazeStatsPool->get_item();
    } else {
        LOGE_ANALYZER("no free adehazeStats buffer!");
        return XCAM_RETURN_BYPASS;
    }
    ret = mTranslator->translateAdehazeStats(buffer, adehazeStats);
    if (ret < 0) {
        LOGE_ANALYZER("translate dehaze stats failed!");
        return XCAM_RETURN_BYPASS;
    }

    uint32_t id = buffer->get_sequence();
    SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_ADEHAZE_STATS_OK,
            id, adehazeStats);
    post_message(msg);

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::handleOrbStats(const SmartPtr<VideoBuffer> &buffer)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqOrbStatsProxy> orbStats = NULL;
    if (mAiqOrbStatsIntPool->has_free_items()) {
        orbStats = mAiqOrbStatsIntPool->get_item();
    } else {
        LOGE_ANALYZER("no free orbStats!");
        return XCAM_RETURN_BYPASS;
    }

    ret = mTranslator->translateOrbStats(buffer, orbStats);
    if (ret)
        return XCAM_RETURN_BYPASS;

    uint32_t id = buffer->get_sequence();
    orbStats->setId(id);
    orbStats->setType(RK_AIQ_SHARED_TYPE_ORB_STATS);
    SmartPtr<XCamMessage> msg = new RkAiqCoreVdBufMsg(XCAM_MESSAGE_ORB_STATS_OK,
            id, orbStats);
    post_message(msg);

    return XCAM_RETURN_NO_ERROR;
}



XCamReturn RkAiqCore::set_sp_resolution(int &width, int &height, int &aligned_w, int &aligned_h)
{
    mSpWidth = width;
    mSpHeight = height;
    mSpAlignedWidth = aligned_w;
    mSpAlignedHeight = aligned_h;
    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCore::newAiqGroupAnayzer()
{
    mRkAiqCoreGroupManager = new RkAiqAnalyzeGroupManager(this);
    mRkAiqCoreGroupManager->parseAlgoGroup(mAlgosDesArray);
    return XCAM_RETURN_NO_ERROR;
}

} //namespace RkCam
