/*
 * RkAiqCoreV21.cpp
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
#include "RkAiqHandleIntV21.h"
#include "RkAiqCoreV21.h"
#include "v4l2_buffer_proxy.h"
#include "acp/rk_aiq_algo_acp_itf.h"
#include "ae/rk_aiq_algo_ae_itf.h"
#include "awb/rk_aiq_algo_awb_itf.h"
#include "af/rk_aiq_algo_af_itf.h"
#include "anr/rk_aiq_algo_anr_itf.h"
#include "asd/rk_aiq_algo_asd_itf.h"
#include "amerge/rk_aiq_algo_amerge_itf.h"
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
#include "asharp3/rk_aiq_asharp_algo_itf_v3.h"
#include "aynr2/rk_aiq_aynr_algo_itf_v2.h"
#include "acnr/rk_aiq_acnr_algo_itf_v1.h"
#include "arawnr2/rk_aiq_abayernr_algo_itf_v2.h"



#ifdef RK_SIMULATOR_HW
#include "simulator/isp20_hw_simulator.h"
#else
#include "isp20/Isp20StatsBuffer.h"
#include "common/rkisp2-config.h"
#include "common/rkisp21-config.h"
#endif
#include <fcntl.h>
#include <unistd.h>
#include "RkAiqResourceTranslatorV21.h"
#include "RkAiqAnalyzeGroupManager.h"

namespace RkCam {
/*
 * isp/ispp pipeline algos ordered array, and the analyzer
 * will run these algos one by one.
 */

/*
 * isp gets the stats from frame n-1,
 * and the new parameters take effect on frame n+1
 */
#define ISP_PARAMS_EFFECT_DELAY_CNT 2

static RkAiqGrpCondition_t aeGrpCondV21[]       = {
    [0] = { XCAM_MESSAGE_AEC_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t aeGrpCondsV21       = { grp_conds_array_info(aeGrpCondV21) };

static RkAiqGrpCondition_t awbGrpCond[]         = {
    [0] = { XCAM_MESSAGE_AE_PRE_RES_OK,     0 },
    [1] = { XCAM_MESSAGE_AWB_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t  awbGrpConds        = { grp_conds_array_info(awbGrpCond) };

static RkAiqGrpCondition_t afGrpCondV21[]     = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
    [1] = { XCAM_MESSAGE_AE_PRE_RES_OK,     0 },
    [2] = { XCAM_MESSAGE_AE_PROC_RES_OK,    0 },
    [3] = { XCAM_MESSAGE_AF_STATS_OK,       ISP_PARAMS_EFFECT_DELAY_CNT },
    [4] = { XCAM_MESSAGE_AEC_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t  afGrpCondsV21    = { grp_conds_array_info(afGrpCondV21) };

static RkAiqGrpCondition_t otherGrpCondV21[]    = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
};
static RkAiqGrpConditions_t  otherGrpCondsV21   = { grp_conds_array_info(otherGrpCondV21) };

static RkAiqGrpCondition_t grp0Cond[]           = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
    [1] = { XCAM_MESSAGE_AE_PRE_RES_OK,     0 },
    [2] = { XCAM_MESSAGE_AE_PROC_RES_OK,    0 },
    [3] = { XCAM_MESSAGE_AEC_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
    [4] = { XCAM_MESSAGE_AWB_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t  grp0Conds          = { grp_conds_array_info(grp0Cond) };

static RkAiqGrpCondition_t grp1Cond[]           = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
    [1] = { XCAM_MESSAGE_AWB_PROC_RES_OK,   0 },
};
static RkAiqGrpConditions_t  grp1Conds          = { grp_conds_array_info(grp1Cond) };

static struct RkAiqAlgoDesCommExt g_default_3a_des_v21[] = {
    { &g_RkIspAlgoDescAe.common, RK_AIQ_CORE_ANALYZE_AE, 0, 1, aeGrpCondsV21 },
    { &g_RkIspAlgoDescAwb.common, RK_AIQ_CORE_ANALYZE_AWB, 1, 1, awbGrpConds },
    { &g_RkIspAlgoDescAdebayer.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescAgamma.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescAdegamma.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescAmerge.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescAdhaz.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 1, grp0Conds },
    { &g_RkIspAlgoDescArawnrV2.common, RK_AIQ_CORE_ANALYZE_GRP0, 2, 2, grp0Conds },
    { &g_RkIspAlgoDescAynrV2.common, RK_AIQ_CORE_ANALYZE_GRP0, 2, 2, grp0Conds },
    { &g_RkIspAlgoDescAcnrV1.common, RK_AIQ_CORE_ANALYZE_GRP0, 1, 1, grp0Conds },
    { &g_RkIspAlgoDescAsharpV3.common, RK_AIQ_CORE_ANALYZE_GRP0, 3, 3, grp0Conds },
    { &g_RkIspAlgoDescAdrc.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescA3dlut.common, RK_AIQ_CORE_ANALYZE_GRP1, 0, 0, grp1Conds },
    { &g_RkIspAlgoDescAlsc.common, RK_AIQ_CORE_ANALYZE_GRP1, 0, 0, grp1Conds },
    { &g_RkIspAlgoDescAccm.common, RK_AIQ_CORE_ANALYZE_GRP1, 0, 0, grp1Conds },
    { &g_RkIspAlgoDescAcp.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV21 },
    { &g_RkIspAlgoDescAie.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV21 },
    { &g_RkIspAlgoDescAdpcc.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV21},
    { &g_RkIspAlgoDescAldch.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV21 },
    { &g_RkIspAlgoDescAcgc.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV21 },
    { &g_RkIspAlgoDescAr2y.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV21 },
    { &g_RkIspAlgoDescAf.common, RK_AIQ_CORE_ANALYZE_AF, 0, 0, afGrpCondsV21 },
    { &g_RkIspAlgoDescAblc.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV21 },
    { &g_RkIspAlgoDescAgic.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 1, otherGrpCondsV21 },
    { &g_RkIspAlgoDescAwdr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV21 },
    { &g_RkIspAlgoDescAsd.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV21 },

    { NULL, RK_AIQ_CORE_ANALYZE_ALL, 0, 0 },
};

RkAiqCoreV21::RkAiqCoreV21()
    : RkAiqCore()
{
    ENTER_ANALYZER_FUNCTION();

    mHasPp = false;
    mIspHwVer = 1;
    mAlgosDesArray = g_default_3a_des_v21;

    mTranslator = new  RkAiqResourceTranslatorV21();

    EXIT_ANALYZER_FUNCTION();
}

RkAiqCoreV21::~RkAiqCoreV21()
{
    ENTER_ANALYZER_FUNCTION();

    EXIT_ANALYZER_FUNCTION();
}

void
RkAiqCoreV21::newAiqParamsPool()
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
                mAiqIspAwbV21ParamsPool     = new RkAiqIspAwbParamsPoolV21("RkAiqIspAwbV21Params", RkAiqCore::DEFAULT_POOL_SIZE);
                mAiqIspAwbGainParamsPool    = new RkAiqIspAwbGainParamsPool("RkAiqIspAwbGainParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AF:
                mAiqFocusParamsPool         = new RkAiqFocusParamsPool("RkAiqFocusParams", RkAiqCore::DEFAULT_POOL_SIZE);
                mAiqIspAfParamsPool         = new RkAiqIspAfParamsPool("RkAiqIspAfParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADPCC:
                mAiqIspDpccParamsPool       = new RkAiqIspDpccParamsPool("RkAiqIspDpccParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AMERGE:
                mAiqIspMergeParamsPool      = new RkAiqIspMergeParamsPool("RkAiqIspMergeParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADHAZ:
                mAiqIspDehazeParamsPool     = new RkAiqIspDehazeParamsPool("RkAiqIspDehazeParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_A3DLUT:
                mAiqIspLut3dParamsPool      = new RkAiqIspLut3dParamsPool("RkAiqIspLut3dParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ACCM:
                mAiqIspCcmParamsPool        = new RkAiqIspCcmParamsPool("RkAiqIspCcmParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ALSC:
                mAiqIspLscParamsPool        = new RkAiqIspLscParamsPool("RkAiqIspLscParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ABLC:
                mAiqIspBlcV21ParamsPool     = new RkAiqIspBlcParamsPoolV21("RkAiqIspBlcParamsV21", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ARAWNR:
                mAiqIspBaynrV21ParamsPool      = new RkAiqIspBaynrParamsPoolV21("RkAiqIspRawnrParams", RkAiqCore::DEFAULT_POOL_SIZE);
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
            case RK_AIQ_ALGO_TYPE_AGAMMA:
                mAiqIspAgammaParamsPool     = new RkAiqIspAgammaParamsPool("RkAiqIspAgammaParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADEGAMMA:
                mAiqIspAdegammaParamsPool     = new RkAiqIspAdegammaParamsPool("RkAiqIspAdegammaParams", RkAiqCore::DEFAULT_POOL_SIZE);
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
            case RK_AIQ_ALGO_TYPE_ACP:
                mAiqIspCpParamsPool         = new RkAiqIspCpParamsPool("RkAiqIspCpParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AIE:
                mAiqIspIeParamsPool         = new RkAiqIspIeParamsPool("RkAiqIspIeParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AYNR:
                mAiqIspYnrV21ParamsPool     = new RkAiqIspYnrParamsPoolV21("RkAiqIspYnrV21Params", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ACNR:
                mAiqIspCnrV21ParamsPool     = new RkAiqIspCnrParamsPoolV21("RkAiqIspCnrV21Params", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ASHARP:
                mAiqIspSharpenV21ParamsPool   = new RkAiqIspSharpenParamsPoolV21("RkAiqIspSharpenV21Params", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADRC:
                mAiqIspDrcParamsPool     = new RkAiqIspDrcParamsPool("RkAiqIspDrcParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            default:
                break;
            }
        }
    }
}

XCamReturn
RkAiqCoreV21::getAiqParamsBuffer(RkAiqFullParams* aiqParams, enum rk_aiq_core_analyze_type_e type)
{
#define NEW_PARAMS_BUFFER(lc, BC) \
    if (mAiqIsp##lc##ParamsPool->has_free_items()) { \
        aiqParams->m##lc##Params = mAiqIsp##lc##ParamsPool->get_item(); \
    } else { \
        LOGE_ANALYZER("no free %s buffer!", #BC); \
        return XCAM_RETURN_ERROR_MEM; \
    } \

#define NEW_PARAMS_BUFFER_V21(lc, BC) \
    if (mAiqIsp##lc##V21ParamsPool->has_free_items()) { \
        aiqParams->m##lc##V21Params = mAiqIsp##lc##V21ParamsPool->get_item(); \
    } else { \
        LOGE_ANALYZER("no free %s buffer!", #BC); \
        return XCAM_RETURN_ERROR_MEM; \
    } \

    std::vector<SmartPtr<RkAiqHandle>>& algo_list =
        mRkAiqCoreGroupManager->getGroupAlgoList(type);

    for (auto& algoHdl : algo_list) {
        if (!(algoHdl.ptr() && algoHdl->getEnable()))
            continue;

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
            NEW_PARAMS_BUFFER_V21(Awb, awb);
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
            NEW_PARAMS_BUFFER_V21(Blc, blc);
            break;
        case RK_AIQ_ALGO_TYPE_ADPCC:
            NEW_PARAMS_BUFFER(Dpcc, dpcc);
            break;
        case RK_AIQ_ALGO_TYPE_AMERGE:
            NEW_PARAMS_BUFFER(Merge, merge);
            break;
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
        case RK_AIQ_ALGO_TYPE_ADEGAMMA:
            NEW_PARAMS_BUFFER(Adegamma, adegamma);
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
            NEW_PARAMS_BUFFER(Drc, drc);
            break;
        case RK_AIQ_ALGO_TYPE_ARAWNR:
            NEW_PARAMS_BUFFER_V21(Baynr, baynr);
            break;
        case RK_AIQ_ALGO_TYPE_AMFNR:
            NEW_PARAMS_BUFFER(Tnr, tnr);
            break;
        case RK_AIQ_ALGO_TYPE_AYNR:
            NEW_PARAMS_BUFFER_V21(Ynr, ynr);
            break;
        case RK_AIQ_ALGO_TYPE_ACNR:
            NEW_PARAMS_BUFFER_V21(Cnr, cnr);
            break;
        case RK_AIQ_ALGO_TYPE_ASHARP:
            NEW_PARAMS_BUFFER_V21(Sharpen, sharpen);
            break;
        default:
            break;
        }
    }

    return XCAM_RETURN_NO_ERROR;
}

SmartPtr<RkAiqHandle>
RkAiqCoreV21::newAlgoHandle(RkAiqAlgoDesComm* algo, int version)
{
    if (version == 0)
        return RkAiqCore::newAlgoHandle(algo, 0);

#define NEW_ALGO_HANDLE_WITH_V(lc, BC, v) \
    do {\
        if (algo->type == RK_AIQ_ALGO_TYPE_##BC) \
                return new RkAiq##lc##V##v##HandleInt(algo, this); \
    } while(0)\

    /* NEW_ALGO_HANDLE_V2(Arawnr, ARAWNR); */
    /* NEW_ALGO_HANDLE_V2(Amfnr, AMFNR); */
    /* NEW_ALGO_HANDLE_V2(Aynr, AYNR); */
    /* NEW_ALGO_HANDLE_V2(Acnr, ACNR); */
    NEW_ALGO_HANDLE_WITH_V(Asharp, ASHARP, 3);
    NEW_ALGO_HANDLE_WITH_V(Aynr, AYNR, 2);
    NEW_ALGO_HANDLE_WITH_V(Acnr, ACNR, 1);
    NEW_ALGO_HANDLE_WITH_V(Arawnr, ARAWNR, 2);
    NEW_ALGO_HANDLE_WITH_V(Awb, AWB, 21);
    return NULL;
}

void
RkAiqCoreV21::copyIspStats(SmartPtr<RkAiqAecStatsProxy>& aecStat,
                           SmartPtr<RkAiqAwbStatsProxy>& awbStat,
                           SmartPtr<RkAiqAfStatsProxy>& afStat,
                           rk_aiq_isp_stats_t* to)
{
    if (aecStat.ptr()) {
        to->aec_stats = aecStat->data()->aec_stats;
        to->frame_id = aecStat->data()->frame_id;
    }
    to->awb_hw_ver = 1;
    if (awbStat.ptr())
        to->awb_stats_v21 = awbStat->data()->awb_stats_v201;
    if (afStat.ptr())
        to->af_stats = afStat->data()->af_stats;
}

} //namespace RkCam
