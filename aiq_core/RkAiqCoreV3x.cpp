/*
 * RkAiqCoreV3x.cpp
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
#include "RkAiqHandleIntV3x.h"
#include "RkAiqCoreV3x.h"
#include "acac/rk_aiq_algo_acac_itf.h"
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
#include "isp20/Isp20StatsBuffer.h"
#include "common/rkisp2-config.h"
#include "common/rkisp21-config.h"
#include "common/rkisp3-config.h"
#include <fcntl.h>
#include <unistd.h>
#include "RkAiqResourceTranslatorV3x.h"
#include "RkAiqAnalyzeGroupManager.h"


#include "asharp4/rk_aiq_asharp_algo_itf_v4.h"
#include "aynr3/rk_aiq_aynr_algo_itf_v3.h"
#include "acnr2/rk_aiq_acnr_algo_itf_v2.h"
#include "abayer2dnr2/rk_aiq_abayer2dnr_algo_itf_v2.h"
#include "abayertnr2/rk_aiq_abayertnr_algo_itf_v2.h"
#include "again2/rk_aiq_again_algo_itf_v2.h"


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

static RkAiqGrpCondition_t aeGrpCondV3x[]       = {
    [0] = { XCAM_MESSAGE_AEC_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t aeGrpCondsV3x       = { grp_conds_array_info(aeGrpCondV3x) };

static RkAiqGrpCondition_t awbGrpCond[]         = {
    [0] = { XCAM_MESSAGE_AE_PRE_RES_OK,     0 },
    [1] = { XCAM_MESSAGE_AWB_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t  awbGrpConds        = { grp_conds_array_info(awbGrpCond) };

static RkAiqGrpCondition_t afGrpCondV3x[]     = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
    [1] = { XCAM_MESSAGE_AE_PRE_RES_OK,     0 },
    [2] = { XCAM_MESSAGE_AE_PROC_RES_OK,    0 },
    [3] = { XCAM_MESSAGE_AF_STATS_OK,       ISP_PARAMS_EFFECT_DELAY_CNT },
    [4] = { XCAM_MESSAGE_AEC_STATS_OK,      ISP_PARAMS_EFFECT_DELAY_CNT },
};
static RkAiqGrpConditions_t  afGrpCondsV3x    = { grp_conds_array_info(afGrpCondV3x) };

static RkAiqGrpCondition_t otherGrpCondV3x[]    = {
    [0] = { XCAM_MESSAGE_SOF_INFO_OK,       0 },
};
static RkAiqGrpConditions_t  otherGrpCondsV3x   = { grp_conds_array_info(otherGrpCondV3x) };

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

static struct RkAiqAlgoDesCommExt g_default_3a_des_v3x[] = {
    { &g_RkIspAlgoDescAe.common, RK_AIQ_CORE_ANALYZE_AE, 0, 2, aeGrpCondsV3x },
    { &g_RkIspAlgoDescAwb.common, RK_AIQ_CORE_ANALYZE_AWB, 1, 1, awbGrpConds },
    { &g_RkIspAlgoDescAdebayer.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescAgamma.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescAdegamma.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescAmerge.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescAcac.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescAdhaz.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 1, grp0Conds },
    { &g_RkIspAlgoDescAbayer2dnrV2.common, RK_AIQ_CORE_ANALYZE_GRP0, 2, 2, grp0Conds },
    { &g_RkIspAlgoDescAbayertnrV2.common, RK_AIQ_CORE_ANALYZE_GRP0, 2, 2, grp0Conds },
    { &g_RkIspAlgoDescAynrV3.common, RK_AIQ_CORE_ANALYZE_GRP0, 3, 3, grp0Conds },
    { &g_RkIspAlgoDescAcnrV2.common, RK_AIQ_CORE_ANALYZE_GRP0, 2, 2, grp0Conds },
    { &g_RkIspAlgoDescAsharpV4.common, RK_AIQ_CORE_ANALYZE_GRP0, 4, 4, grp0Conds },
    { &g_RkIspAlgoDescAdrc.common, RK_AIQ_CORE_ANALYZE_GRP0, 0, 0, grp0Conds },
    { &g_RkIspAlgoDescA3dlut.common, RK_AIQ_CORE_ANALYZE_GRP1, 0, 0, grp1Conds },
    { &g_RkIspAlgoDescAlsc.common, RK_AIQ_CORE_ANALYZE_GRP1, 0, 0, grp1Conds },
    { &g_RkIspAlgoDescAccm.common, RK_AIQ_CORE_ANALYZE_GRP1, 0, 0, grp1Conds },
    { &g_RkIspAlgoDescAcp.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x },
    { &g_RkIspAlgoDescAie.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x },
    { &g_RkIspAlgoDescAdpcc.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x},
    //{ &g_RkIspAlgoDescAldch.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x },
    { &g_RkIspAlgoDescAcgc.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x },
    { &g_RkIspAlgoDescAr2y.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x },
    { &g_RkIspAlgoDescAf.common, RK_AIQ_CORE_ANALYZE_AF, 0, 1, afGrpCondsV3x },
    { &g_RkIspAlgoDescAblc.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x },
    { &g_RkIspAlgoDescAgic.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 1, otherGrpCondsV3x },
    { &g_RkIspAlgoDescAwdr.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x },
    { &g_RkIspAlgoDescAsd.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x },
    { &g_RkIspAlgoDescAgainV2.common, RK_AIQ_CORE_ANALYZE_GRP0, 2, 2, grp0Conds },
    { NULL, RK_AIQ_CORE_ANALYZE_ALL, 0, 0 },
};

RkAiqCoreV3x::RkAiqCoreV3x()
    : RkAiqCoreV21()
{
    ENTER_ANALYZER_FUNCTION();

    mHasPp = false;
    mIspHwVer = 3;
    mAlgosDesArray = g_default_3a_des_v3x;

    mTranslator = new  RkAiqResourceTranslatorV3x();

    EXIT_ANALYZER_FUNCTION();
}

RkAiqCoreV3x::~RkAiqCoreV3x()
{
    ENTER_ANALYZER_FUNCTION();

    EXIT_ANALYZER_FUNCTION();
}

XCamReturn
RkAiqCoreV3x::prepare(const rk_aiq_exposure_sensor_descriptor* sensor_des,
                      int mode)
{
    if (mHwInfo.is_multi_isp_mode) {
        XCAM_ASSERT((sensor_des->isp_acq_width % 32 == 0));// &&
        //(sensor_des->isp_acq_height % 16 == 0));
        uint32_t extended_pixel = mHwInfo.multi_isp_extended_pixel;
        RkAiqResourceTranslatorV3x* translator = static_cast<RkAiqResourceTranslatorV3x*>(mTranslator.ptr());
        translator->SetMultiIspMode(true)
        .SetPicInfo({0, 0, sensor_des->isp_acq_width, sensor_des->isp_acq_height})
        .SetLeftIspRect(
        {0, 0, sensor_des->isp_acq_width / 2 + extended_pixel, sensor_des->isp_acq_height})
        .SetRightIspRect({sensor_des->isp_acq_width / 2 - extended_pixel, 0,
                          sensor_des->isp_acq_width / 2 + extended_pixel,
                          sensor_des->isp_acq_height});
        RkAiqResourceTranslatorV3x::Rectangle f = translator->GetPicInfo();
        RkAiqResourceTranslatorV3x::Rectangle l = translator->GetLeftIspRect();
        RkAiqResourceTranslatorV3x::Rectangle r = translator->GetLeftIspRect();
        LOGD_ANALYZER(
            "Set Multi-ISP mode Translator info :"
            " F: { %u, %u, %u, %u }"
            " L: { %u, %u, %u, %u }"
            " R: { %u, %u, %u, %u }",
            f.x, f.y, f.w, f.h, l.x, l.y, l.w, l.h, r.x, r.y, r.w, r.h);
        mAlogsComSharedParams.is_multi_isp_mode = mHwInfo.is_multi_isp_mode;
        mAlogsComSharedParams.multi_isp_extended_pixels = extended_pixel;
    } else {
        static_cast<RkAiqResourceTranslatorV3x*>(mTranslator.ptr())->SetMultiIspMode(false);
    }

    return RkAiqCore::prepare(sensor_des, mode);
}

void
RkAiqCoreV3x::newAiqParamsPool()
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
                mAiqIspAwbV3xParamsPool     = new RkAiqIspAwbParamsPoolV3x("RkAiqIspAwbV3xParams", RkAiqCore::DEFAULT_POOL_SIZE);
                mAiqIspAwbGainParamsPool = new RkAiqIspAwbGainParamsPool("RkAiqIspAwbGainParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AF:
                mAiqFocusParamsPool         = new RkAiqFocusParamsPool("RkAiqFocusParams", RkAiqCore::DEFAULT_POOL_SIZE);
                mAiqIspAfV3xParamsPool      = new RkAiqIspAfParamsPoolV3x("RkAiqIspAfParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADPCC:
                mAiqIspDpccParamsPool       = new RkAiqIspDpccParamsPool("RkAiqIspDpccParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AMERGE:
                mAiqIspMergeV3xParamsPool   = new RkAiqIspMergeParamsPoolV3x("RkAiqIspMergeParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADHAZ:
                mAiqIspDehazeV3xParamsPool  = new RkAiqIspDehazeParamsPoolV3x("RkAiqIspDehazeV3xParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_A3DLUT:
                mAiqIspLut3dParamsPool      = new RkAiqIspLut3dParamsPool("RkAiqIspLut3dParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ACCM:
                mAiqIspCcmParamsPool        = new RkAiqIspCcmParamsPool("RkAiqIspCcmParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ALSC:
                mAiqIspLscParamsPool     = new RkAiqIspLscParamsPool("RkAiqIspLscParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ABLC:
                mAiqIspBlcV21ParamsPool     = new RkAiqIspBlcParamsPoolV21("RkAiqIspBlcParamsV21", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ARAWNR:
                mAiqIspBaynrV3xParamsPool      = new RkAiqIspBaynrParamsPoolV3x("RkAiqIspRawnrParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AGIC:
                mAiqIspGicV21ParamsPool     = new RkAiqIspGicParamsPoolV21("RkAiqIspGicParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADEBAYER:
                mAiqIspDebayerParamsPool    = new RkAiqIspDebayerParamsPool("RkAiqIspDebayerParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ALDCH:
                mAiqIspLdchParamsPool       = new RkAiqIspLdchParamsPool("RkAiqIspLdchParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AGAMMA:
                mAiqIspAgammaV3xParamsPool  = new RkAiqIspAgammaParamsPoolV3x("RkAiqIspAgammaParams", RkAiqCore::DEFAULT_POOL_SIZE);
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
                mAiqIspYnrV3xParamsPool     = new RkAiqIspYnrParamsPoolV3x("RkAiqIspYnrV3xParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ACNR:
                mAiqIspCnrV3xParamsPool     = new RkAiqIspCnrParamsPoolV3x("RkAiqIspCnrV3xParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ASHARP:
                mAiqIspSharpenV3xParamsPool   = new RkAiqIspSharpenParamsPoolV3x("RkAiqIspSharpenV3xParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ADRC:
                mAiqIspDrcV3xParamsPool     = new RkAiqIspDrcParamsPoolV3x("RkAiqIspDrcV3xParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ACAC:
                mAiqIspCacV3xParamsPool     = new RkAiqIspCacParamsPoolV3x("RkAiqIspCacV3xParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AMFNR:
                mAiqIspTnrV3xParamsPool     = new RkAiqIspTnrParamsPoolV3x("RkAiqIspTnrV3xParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_AGAIN:
                mAiqIspGainV3xParamsPool     = new RkAiqIspGainParamsPoolV3x("RkAiqIspGainV3xParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            default:
                break;
            }
        }
    }
}

XCamReturn
RkAiqCoreV3x::getAiqParamsBuffer(RkAiqFullParams* aiqParams, enum rk_aiq_core_analyze_type_e type)
{
#define NEW_PARAMS_BUFFER(lc, BC) \
    if (mAiqIsp##lc##ParamsPool->has_free_items()) { \
        aiqParams->m##lc##Params = mAiqIsp##lc##ParamsPool->get_item(); \
    } else { \
        LOGE_ANALYZER("no free %s buffer!", #BC); \
        return XCAM_RETURN_ERROR_MEM; \
    } \

#define NEW_PARAMS_BUFFER_WITH_V(lc, BC, v) \
    if (mAiqIsp##lc##V##v##ParamsPool->has_free_items()) { \
        aiqParams->m##lc##V##v##Params = mAiqIsp##lc##V##v##ParamsPool->get_item(); \
    } else { \
        LOGE_ANALYZER("no free %s buffer!", #BC); \
        return XCAM_RETURN_ERROR_MEM; \
    } \

    std::list<int>& algo_list =
        mRkAiqCoreGroupManager->getGroupAlgoList(type);

    for (auto algo_type : algo_list) {
        SmartPtr<RkAiqHandle>* algoHdl = getCurAlgoTypeHandle(algo_type);
        if (!(algoHdl && (*algoHdl)->getEnable()))
            continue;

        switch (algo_type) {
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
            NEW_PARAMS_BUFFER_WITH_V(Awb, awb, 3x);
            NEW_PARAMS_BUFFER(AwbGain, awb_gain);
            break;
        case RK_AIQ_ALGO_TYPE_AF:
            if (mAiqFocusParamsPool->has_free_items()) {
                aiqParams->mFocusParams = mAiqFocusParamsPool->get_item();
            } else {
                LOGE_ANALYZER("no free focus params buffer!");
                return XCAM_RETURN_ERROR_MEM;
            }
            NEW_PARAMS_BUFFER_WITH_V(Af, af, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_ABLC:
            NEW_PARAMS_BUFFER_WITH_V(Blc, blc, 21);
            break;
        case RK_AIQ_ALGO_TYPE_ADPCC:
            NEW_PARAMS_BUFFER(Dpcc, dpcc);
            break;
        case RK_AIQ_ALGO_TYPE_AMERGE:
            NEW_PARAMS_BUFFER_WITH_V(Merge, merge, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_ALSC:
            NEW_PARAMS_BUFFER(Lsc, lsc);
            break;
        case RK_AIQ_ALGO_TYPE_AGIC:
            NEW_PARAMS_BUFFER_WITH_V(Gic, gic, 21);
            break;
        case RK_AIQ_ALGO_TYPE_ADEBAYER:
            NEW_PARAMS_BUFFER(Debayer, debayer);
            break;
        case RK_AIQ_ALGO_TYPE_ACCM:
            NEW_PARAMS_BUFFER(Ccm, ccm);
            break;
        case RK_AIQ_ALGO_TYPE_AGAMMA:
            NEW_PARAMS_BUFFER_WITH_V(Agamma, agamma, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_ADEGAMMA:
            NEW_PARAMS_BUFFER(Adegamma, adegamma);
            break;
        case RK_AIQ_ALGO_TYPE_AWDR:
            NEW_PARAMS_BUFFER(Wdr, wdr);
            break;
        case RK_AIQ_ALGO_TYPE_ADHAZ:
            NEW_PARAMS_BUFFER_WITH_V(Dehaze, dehaze, 3x);
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
            NEW_PARAMS_BUFFER_WITH_V(Drc, drc, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_ARAWNR:
            NEW_PARAMS_BUFFER_WITH_V(Baynr, baynr, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_AMFNR:
            NEW_PARAMS_BUFFER_WITH_V(Tnr, tnr, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_AYNR:
            NEW_PARAMS_BUFFER_WITH_V(Ynr, ynr, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_ACNR:
            NEW_PARAMS_BUFFER_WITH_V(Cnr, cnr, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_ASHARP:
            NEW_PARAMS_BUFFER_WITH_V(Sharpen, sharpen, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_ACAC:
            NEW_PARAMS_BUFFER_WITH_V(Cac, cac, 3x);
            break;
        case RK_AIQ_ALGO_TYPE_AGAIN:
            NEW_PARAMS_BUFFER_WITH_V(Gain, Gain, 3x);
            break;
        default:
            break;
        }
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
RkAiqCoreV3x::genIspParamsResult(RkAiqFullParams *aiqParams, enum rk_aiq_core_analyze_type_e type)
{
    SmartPtr<RkAiqFullParams> curParams = mAiqCurParams->data();
    for (auto algoHdl : mCurIspAlgoHandleList) {
        if (algoHdl.ptr() && algoHdl->getEnable() &&
                (mAlgoTypeToGrpMaskMap[algoHdl->getAlgoType()] & grpId2GrpMask(type))) {
            switch (algoHdl->getAlgoType()) {
            case RK_AIQ_ALGO_TYPE_AE:
                genIspAeResult(aiqParams);
                curParams->mExposureParams = aiqParams->mExposureParams;
                curParams->mAecParams      = aiqParams->mAecParams;
                curParams->mHistParams     = aiqParams->mHistParams;
                break;
            case RK_AIQ_ALGO_TYPE_AWB:
                genIspAwbResult(aiqParams);
                curParams->mAwbV3xParams  = aiqParams->mAwbV3xParams;
                curParams->mAwbGainParams = aiqParams->mAwbGainParams;
                break;
            case RK_AIQ_ALGO_TYPE_AF:
                genIspAfResult(aiqParams);
                curParams->mAfV3xParams    = aiqParams->mAfV3xParams;
                curParams->mFocusParams = aiqParams->mFocusParams;
                break;
            case RK_AIQ_ALGO_TYPE_ABLC:
                genIspAblcResult(aiqParams);
                curParams->mBlcV21Params = aiqParams->mBlcV21Params;
                break;
            case RK_AIQ_ALGO_TYPE_ADPCC:
                genIspAdpccResult(aiqParams);
                curParams->mDpccParams = aiqParams->mDpccParams;
                break;
            case RK_AIQ_ALGO_TYPE_AMERGE:
                genIspAmergeResult(aiqParams);
                curParams->mMergeV3xParams = aiqParams->mMergeV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_ALSC:
                genIspAlscResult(aiqParams);
                curParams->mLscParams = aiqParams->mLscParams;
                break;
            case RK_AIQ_ALGO_TYPE_AGIC:
                genIspAgicResult(aiqParams);
                curParams->mGicV21Params = aiqParams->mGicV21Params;
                break;
            case RK_AIQ_ALGO_TYPE_ADEBAYER:
                genIspAdebayerResult(aiqParams);
                curParams->mDebayerParams = aiqParams->mDebayerParams;
                break;
            case RK_AIQ_ALGO_TYPE_ACCM:
                genIspAccmResult(aiqParams);
                curParams->mCcmParams = aiqParams->mCcmParams;
                break;
            case RK_AIQ_ALGO_TYPE_AGAMMA:
                genIspAgammaResult(aiqParams);
                curParams->mAgammaV3xParams = aiqParams->mAgammaV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_ADEGAMMA:
                genIspAdegammaResult(aiqParams);
                curParams->mAdegammaParams = aiqParams->mAdegammaParams;
                break;
            case RK_AIQ_ALGO_TYPE_AWDR:
                genIspAwdrResult(aiqParams);
                curParams->mWdrParams = aiqParams->mWdrParams;
                break;
            case RK_AIQ_ALGO_TYPE_ADHAZ:
                genIspAdhazResult(aiqParams);
                curParams->mDehazeV3xParams = aiqParams->mDehazeV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_A3DLUT:
                genIspA3dlutResult(aiqParams);
                curParams->mLut3dParams = aiqParams->mLut3dParams;
                break;
            case RK_AIQ_ALGO_TYPE_ALDCH:
                genIspAldchResult(aiqParams);
                curParams->mLdchParams = aiqParams->mLdchParams;
                break;
            case RK_AIQ_ALGO_TYPE_AR2Y:
                genIspAr2yResult(aiqParams);
                break;
            case RK_AIQ_ALGO_TYPE_ACP:
                genIspAcpResult(aiqParams);
                curParams->mCpParams = aiqParams->mCpParams;
                break;
            case RK_AIQ_ALGO_TYPE_AIE:
                genIspAieResult(aiqParams);
                curParams->mIeParams = aiqParams->mIeParams;
                break;
            case RK_AIQ_ALGO_TYPE_ACGC:
                genIspAcgcResult(aiqParams);
                curParams->mCgcParams = aiqParams->mCgcParams;
                break;
            case RK_AIQ_ALGO_TYPE_ASD:
                break;
            case RK_AIQ_ALGO_TYPE_ADRC:
                genIspAdrcResult(aiqParams);
                curParams->mDrcV3xParams = aiqParams->mDrcV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_ARAWNR:
                genIspArawnrResult(aiqParams);
                curParams->mBaynrV3xParams = aiqParams->mBaynrV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_ACNR:
                genIspAcnrResult(aiqParams);
                curParams->mCnrV3xParams = aiqParams->mCnrV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_AYNR:
                genIspAynrResult(aiqParams);
                curParams->mYnrV3xParams = aiqParams->mYnrV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_ASHARP:
                genIspAsharpResult(aiqParams);
                curParams->mSharpenV3xParams = aiqParams->mSharpenV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_ACAC:
                genIspAcacResult(aiqParams);
                curParams->mCacV3xParams = aiqParams->mCacV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_AMFNR:
                genIspAtnrResult(aiqParams);
                curParams->mTnrV3xParams = aiqParams->mTnrV3xParams;
                break;
            case RK_AIQ_ALGO_TYPE_AGAIN:
                genIspAgainResult(aiqParams);
                curParams->mGainV3xParams = aiqParams->mGainV3xParams;
                break;
            default:
                break;
            }
        }
    }

    return XCAM_RETURN_NO_ERROR;
}
SmartPtr<RkAiqHandle>
RkAiqCoreV3x::newAlgoHandle(RkAiqAlgoDesComm* algo, bool generic, int version)
{
#define NEW_ALGO_HANDLE_WITH_V(lc, BC, v) \
    do {\
        if (algo->type == RK_AIQ_ALGO_TYPE_##BC) { \
            if (generic) { \
                return new RkAiq##lc##V##v##Handle(algo, this); \
            } else { \
                return new RkAiq##lc##V##v##HandleInt(algo, this); \
            }\
        }\
    } while(0)\

    // TODO: ISP3x specific handlers
    typedef RkAiqAsharpHandle RkAiqAsharpV4Handle;
    typedef RkAiqAynrHandle RkAiqAynrV3Handle;
    typedef RkAiqAcnrHandle RkAiqAcnrV2Handle;
    typedef RkAiqArawnrHandle RkAiqAbayer2dnrV2Handle;
    typedef RkAiqAmfnrHandle RkAiqAbayertnrV2Handle;
    typedef RkAiqAgainHandle RkAiqAgainV2Handle;

    if(algo->type == RK_AIQ_ALGO_TYPE_ARAWNR
            || algo->type == RK_AIQ_ALGO_TYPE_AMFNR
            || algo->type == RK_AIQ_ALGO_TYPE_AYNR
            || algo->type == RK_AIQ_ALGO_TYPE_ACNR
            || algo->type == RK_AIQ_ALGO_TYPE_ASHARP
            || algo->type == RK_AIQ_ALGO_TYPE_AGAIN) {
        NEW_ALGO_HANDLE_WITH_V(Asharp, ASHARP, 4);
        NEW_ALGO_HANDLE_WITH_V(Aynr, AYNR, 3);
        NEW_ALGO_HANDLE_WITH_V(Acnr, ACNR, 2);
        NEW_ALGO_HANDLE_WITH_V(Abayer2dnr, ARAWNR, 2);
        NEW_ALGO_HANDLE_WITH_V(Abayertnr, AMFNR, 2);
        NEW_ALGO_HANDLE_WITH_V(Again, AGAIN, 2);
    }

    return RkAiqCoreV21::newAlgoHandle(algo, generic, version);

}

void
RkAiqCoreV3x::copyIspStats(SmartPtr<RkAiqAecStatsProxy>& aecStat,
                           SmartPtr<RkAiqAwbStatsProxy>& awbStat,
                           SmartPtr<RkAiqAfStatsProxy>& afStat,
                           rk_aiq_isp_stats_t* to)
{
    if (aecStat.ptr()) {
        to->aec_stats = aecStat->data()->aec_stats;
        to->frame_id = aecStat->data()->frame_id;
    }
    to->awb_hw_ver = 3;
    if (awbStat.ptr())
        to->awb_stats_v3x = awbStat->data()->awb_stats_v3x;
    to->af_hw_ver = 3;
    if (afStat.ptr())
        to->af_stats_v3x = afStat->data()->af_stats_v3x;
}

XCamReturn
RkAiqCoreV3x::genIspArawnrResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_ARAWNR);
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResArawnr* arawnr_com =
        shared->procResComb.arawnr_proc_res;

    if (!arawnr_com) {
        LOGD_ANALYZER("no arawnr result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen asharp common result

    int algo_id = (*handle)->getAlgoId();

    // gen rk asharp result
    if (algo_id == 0) {
        RkAiqAlgoProcResAbayer2dnrV2Int* arawnr_rk = (RkAiqAlgoProcResAbayer2dnrV2Int*)arawnr_com;

        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);

        rk_aiq_isp_baynr_params_v3x_t* rawnr_param = params->mBaynrV3xParams->data().ptr();
        setResultExpectedEffId(rawnr_param->frame_id, RK_AIQ_ALGO_TYPE_ARAWNR);
        memcpy(&rawnr_param->result,
               &arawnr_rk->stArawnrProcResult.st2DFix,
               sizeof(RK_Bayer2dnr_Fix_V2_t));
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAynrResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_AYNR);
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAynr* aynr_com =
        shared->procResComb.aynr_proc_res;

    if (!aynr_com) {
        LOGD_ANALYZER("no aynr result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen asharp common result

    int algo_id = (*handle)->getAlgoId();

    // gen rk asharp result
    if (algo_id == 0) {
        RkAiqAlgoProcResAynrV3Int* aynr_rk = (RkAiqAlgoProcResAynrV3Int*)aynr_com;

        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);

        rk_aiq_isp_ynr_params_v3x_t* ynr_param = params->mYnrV3xParams->data().ptr();
        setResultExpectedEffId(ynr_param->frame_id, RK_AIQ_ALGO_TYPE_AYNR);

        memcpy(&ynr_param->result,
               &aynr_rk->stAynrProcResult.stFix,
               sizeof(RK_YNR_Fix_V3_t));
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAcnrResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_ACNR);
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAcnr* acnr_com =
        shared->procResComb.acnr_proc_res;

    if (!acnr_com) {
        LOGD_ANALYZER("no aynr result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen asharp common result

    int algo_id = (*handle)->getAlgoId();

    // gen rk asharp result
    if (algo_id == 0) {
        RkAiqAlgoProcResAcnrV2Int* acnr_rk = (RkAiqAlgoProcResAcnrV2Int*)acnr_com;

        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);
        rk_aiq_isp_cnr_params_v3x_t* cnr_param = params->mCnrV3xParams->data().ptr();
        setResultExpectedEffId(cnr_param->frame_id, RK_AIQ_ALGO_TYPE_ACNR);

        memcpy(&cnr_param->result,
               &acnr_rk->stAcnrProcResult.stFix,
               sizeof(RK_CNR_Fix_V2_t));
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAdrcResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_ADRC);
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAdrc* adrc_com =
        shared->procResComb.adrc_proc_res;

    if (!adrc_com) {
        LOGD_ANALYZER("no adrc result");
        return XCAM_RETURN_NO_ERROR;
    }

    int algo_id = (*handle)->getAlgoId();

    // gen rk adrc result
    if (algo_id == 0) {
        RkAiqAlgoProcResAdrcInt* adrc_rk = (RkAiqAlgoProcResAdrcInt*)adrc_com;

        rk_aiq_isp_drc_params_v3x_t* drc_param = params->mDrcV3xParams->data().ptr();
        setResultExpectedEffId(drc_param->frame_id, RK_AIQ_ALGO_TYPE_ADRC);

        drc_param->result.DrcProcRes.Drc_v21.bypass_en     = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.bypass_en;
        drc_param->result.DrcProcRes.Drc_v21.offset_pow2     = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.offset_pow2;
        drc_param->result.DrcProcRes.Drc_v21.compres_scl  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.compres_scl;
        drc_param->result.DrcProcRes.Drc_v21.position  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.position;
        drc_param->result.DrcProcRes.Drc_v21.delta_scalein        = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.delta_scalein;
        drc_param->result.DrcProcRes.Drc_v21.hpdetail_ratio      = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.hpdetail_ratio;
        drc_param->result.DrcProcRes.Drc_v21.lpdetail_ratio     = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.lpdetail_ratio;
        drc_param->result.DrcProcRes.Drc_v21.weicur_pix      = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.weicur_pix;
        drc_param->result.DrcProcRes.Drc_v21.weipre_frame  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.weipre_frame;
        drc_param->result.DrcProcRes.Drc_v21.bilat_wt_off  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.bilat_wt_off;
        drc_param->result.DrcProcRes.Drc_v21.force_sgm_inv0   = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.force_sgm_inv0;
        drc_param->result.DrcProcRes.Drc_v21.motion_scl     = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.motion_scl;
        drc_param->result.DrcProcRes.Drc_v21.edge_scl   = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.edge_scl;
        drc_param->result.DrcProcRes.Drc_v21.space_sgm_inv1    = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.space_sgm_inv1;
        drc_param->result.DrcProcRes.Drc_v21.space_sgm_inv0     = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.space_sgm_inv0;
        drc_param->result.DrcProcRes.Drc_v21.range_sgm_inv1     = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.range_sgm_inv1;
        drc_param->result.DrcProcRes.Drc_v21.range_sgm_inv0 = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.range_sgm_inv0;
        drc_param->result.DrcProcRes.Drc_v21.weig_maxl    = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.weig_maxl;
        drc_param->result.DrcProcRes.Drc_v21.weig_bilat  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.weig_bilat;
        drc_param->result.DrcProcRes.Drc_v21.enable_soft_thd  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.enable_soft_thd;
        drc_param->result.DrcProcRes.Drc_v21.bilat_soft_thd  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.bilat_soft_thd;
        drc_param->result.DrcProcRes.Drc_v21.iir_weight  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.iir_weight;
        drc_param->result.DrcProcRes.Drc_v21.min_ogain  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.min_ogain;
        drc_param->result.DrcProcRes.Drc_v21.adrc_gain  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.adrc_gain;
        drc_param->result.DrcProcRes.Drc_v21.wr_cycle  = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.wr_cycle;
        for(int i = 0; i < 17; i++) {
            drc_param->result.DrcProcRes.Drc_v21.gain_y[i]    = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.gain_y[i];
            drc_param->result.DrcProcRes.Drc_v21.compres_y[i]    = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.compres_y[i];
            drc_param->result.DrcProcRes.Drc_v21.scale_y[i]    = adrc_rk->AdrcProcRes.DrcProcRes.Drc_v21.scale_y[i];
        }

        drc_param->result.CompressMode =
            adrc_rk->AdrcProcRes.CompressMode;

        drc_param->result.update =
            adrc_rk->AdrcProcRes.update;

        drc_param->result.LongFrameMode =
            adrc_rk->AdrcProcRes.LongFrameMode;

        drc_param->result.isHdrGlobalTmo =
            adrc_rk->AdrcProcRes.isHdrGlobalTmo;

        drc_param->result.bTmoEn =
            adrc_rk->AdrcProcRes.bTmoEn;

        drc_param->result.isLinearTmo =
            adrc_rk->AdrcProcRes.isLinearTmo;
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAgammaResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_AGAMMA);
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAgamma* agamma_com =
        shared->procResComb.agamma_proc_res;

    if (!agamma_com) {
        LOGD_ANALYZER("no agamma result");
        return XCAM_RETURN_NO_ERROR;
    }

    int algo_id = (*handle)->getAlgoId();

    // gen rk adrc result
    if (algo_id == 0) {
        RkAiqAlgoProcResAgammaInt* agamma_rk = (RkAiqAlgoProcResAgammaInt*)agamma_com;

        rk_aiq_isp_agamma_params_v3x_t* gamma_param = params->mAgammaV3xParams->data().ptr();
        setResultExpectedEffId(gamma_param->frame_id, RK_AIQ_ALGO_TYPE_AGAMMA);

        gamma_param->result.Gamma_v30.gamma_en     = agamma_rk->GammaProcRes.Gamma_v30.gamma_en;
        gamma_param->result.Gamma_v30.equ_segm     = agamma_rk->GammaProcRes.Gamma_v30.equ_segm;
        gamma_param->result.Gamma_v30.EnableDot49     = agamma_rk->GammaProcRes.Gamma_v30.EnableDot49;
        gamma_param->result.Gamma_v30.offset     = agamma_rk->GammaProcRes.Gamma_v30.offset;

        for(int i = 0; i < 49; i++)
            gamma_param->result.Gamma_v30.gamma_y[i]     = agamma_rk->GammaProcRes.Gamma_v30.gamma_y[i];

    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAwbResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_AWB);
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAwb* awb_com =
        shared->procResComb.awb_proc_res;

    if (!awb_com) {
        LOGD_ANALYZER("no awb result");
        return XCAM_RETURN_NO_ERROR;
    }
    // TODO: gen awb common result
    //RkAiqCore::genIspAwbResult(params);
    RkAiqAlgoProcResAwb* awb_rk = (RkAiqAlgoProcResAwb*)awb_com;

    rk_aiq_isp_awb_params_v3x_t *awb_param = params->mAwbV3xParams->data().ptr();
    rk_aiq_isp_awb_gain_params_v20_t *awb_gain_param = params->mAwbGainParams->data().ptr();
    setResultExpectedEffId(awb_param->frame_id, RK_AIQ_ALGO_TYPE_AWB);
    setResultExpectedEffId(awb_gain_param->frame_id, RK_AIQ_ALGO_TYPE_AWB);

    awb_gain_param->update_mask = awb_rk->awb_gain_update;
    awb_gain_param->result = awb_rk->awb_gain_algo;

    awb_param->update_mask = awb_rk->awb_cfg_update;
    awb_param->result = awb_rk->awb_hw1_para;

    int algo_id = (*handle)->getAlgoId();

    // gen rk awb result
    if (algo_id == 0) {
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAgicResult(RkAiqFullParams* params)
{
    return RkAiqCoreV21::genIspAgicResult(params);
}

XCamReturn
RkAiqCoreV3x::genIspAdhazResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_ADHAZ);
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAdhaz* adhaz_com =
        shared->procResComb.adhaz_proc_res;

    if (!adhaz_com) {
        LOGD_ANALYZER("no adehaze result");
        return XCAM_RETURN_NO_ERROR;
    }
    // TODO: gen adrc common result
    //RkAiqCore::genIspAdrcResult(params);
    RkAiqAlgoProcResAdhaz* adhaz_rk = (RkAiqAlgoProcResAdhaz*)adhaz_com;
    int algo_id = (*handle)->getAlgoId();

    // gen rk adrc result
    if (algo_id == 0) {
        RkAiqAlgoProcResAdhazInt* adhaz_rk = (RkAiqAlgoProcResAdhazInt*)adhaz_com;
        rk_aiq_isp_dehaze_params_v3x_t* dehaze_param = params->mDehazeV3xParams->data().ptr();
        setResultExpectedEffId(dehaze_param->frame_id, RK_AIQ_ALGO_TYPE_ADHAZ);

        dehaze_param->result.ProcResV30.enable     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.enable;
        dehaze_param->result.ProcResV30.update     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.update;
        dehaze_param->result.ProcResV30.round_en     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.round_en;
        dehaze_param->result.ProcResV30.soft_wr_en     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.soft_wr_en;
        dehaze_param->result.ProcResV30.enhance_en     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.enhance_en;
        dehaze_param->result.ProcResV30.air_lc_en  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.air_lc_en;
        dehaze_param->result.ProcResV30.hpara_en   = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.hpara_en;
        dehaze_param->result.ProcResV30.hist_en    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.hist_en;
        dehaze_param->result.ProcResV30.dc_en  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.dc_en;
        dehaze_param->result.ProcResV30.yblk_th    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.yblk_th;
        dehaze_param->result.ProcResV30.yhist_th   = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.yhist_th;
        dehaze_param->result.ProcResV30.dc_max_th  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.dc_max_th;
        dehaze_param->result.ProcResV30.dc_min_th  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.dc_min_th;
        dehaze_param->result.ProcResV30.wt_max     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.wt_max;
        dehaze_param->result.ProcResV30.bright_max     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.bright_max;
        dehaze_param->result.ProcResV30.bright_min     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.bright_min;
        dehaze_param->result.ProcResV30.tmax_base  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.tmax_base;
        dehaze_param->result.ProcResV30.dark_th    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.dark_th;
        dehaze_param->result.ProcResV30.air_max    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.air_max;
        dehaze_param->result.ProcResV30.air_min    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.air_min;
        dehaze_param->result.ProcResV30.tmax_max   = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.tmax_max;
        dehaze_param->result.ProcResV30.tmax_off   = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.tmax_off;
        dehaze_param->result.ProcResV30.hist_k     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.hist_k;
        dehaze_param->result.ProcResV30.hist_th_off    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.hist_th_off;
        dehaze_param->result.ProcResV30.hist_min   = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.hist_min;
        dehaze_param->result.ProcResV30.hist_gratio    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.hist_gratio;
        dehaze_param->result.ProcResV30.hist_scale     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.hist_scale;
        dehaze_param->result.ProcResV30.enhance_value  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.enhance_value;
        dehaze_param->result.ProcResV30.enhance_chroma     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.enhance_chroma;
        dehaze_param->result.ProcResV30.iir_wt_sigma   = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.iir_wt_sigma;
        dehaze_param->result.ProcResV30.iir_sigma  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.iir_sigma;
        dehaze_param->result.ProcResV30.stab_fnum  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.stab_fnum;
        dehaze_param->result.ProcResV30.iir_tmax_sigma     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.iir_tmax_sigma;
        dehaze_param->result.ProcResV30.iir_air_sigma  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.iir_air_sigma;
        dehaze_param->result.ProcResV30.iir_pre_wet    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.iir_pre_wet;
        dehaze_param->result.ProcResV30.cfg_wt     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.cfg_wt;
        dehaze_param->result.ProcResV30.cfg_air    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.cfg_air;
        dehaze_param->result.ProcResV30.cfg_alpha  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.cfg_alpha;
        dehaze_param->result.ProcResV30.cfg_gratio     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.cfg_gratio;
        dehaze_param->result.ProcResV30.cfg_tmax   = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.cfg_tmax;
        dehaze_param->result.ProcResV30.range_sima     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.range_sima;
        dehaze_param->result.ProcResV30.space_sigma_cur    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.space_sigma_cur;
        dehaze_param->result.ProcResV30.space_sigma_pre    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.space_sigma_pre;
        dehaze_param->result.ProcResV30.dc_weitcur     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.dc_weitcur;
        dehaze_param->result.ProcResV30.bf_weight  = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.bf_weight;
        dehaze_param->result.ProcResV30.gaus_h0    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.gaus_h0;
        dehaze_param->result.ProcResV30.gaus_h1    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.gaus_h1;
        dehaze_param->result.ProcResV30.gaus_h2    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.gaus_h2;
        dehaze_param->result.ProcResV30.adp_wt_wr    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.adp_wt_wr;
        dehaze_param->result.ProcResV30.adp_air_wr    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.adp_air_wr;
        dehaze_param->result.ProcResV30.adp_tmax_wr    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.adp_tmax_wr;
        dehaze_param->result.ProcResV30.adp_gratio_wr    = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.adp_gratio_wr;

        for(int i = 0; i < 15; i++)
            dehaze_param->result.ProcResV30.sigma_idx[i]     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.sigma_idx[i];

        for(int i = 0; i < 17; i++) {
            dehaze_param->result.ProcResV30.enh_curve[i]     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.enh_curve[i];
            dehaze_param->result.ProcResV30.sigma_lut[i]     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.sigma_lut[i];
        }

        for(int i = 0; i < 64; i++)
            dehaze_param->result.ProcResV30.hist_wr[i]     = adhaz_rk->adhaz_proc_res_com.AdehzeProcRes.ProcResV30.hist_wr[i];

    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAsharpResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_ASHARP);
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAsharp* asharp_com =
        shared->procResComb.asharp_proc_res;

    if (!asharp_com) {
        LOGD_ANALYZER("no asharp result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen asharp common result

    int algo_id = (*handle)->getAlgoId();

    // gen rk asharp result
    if (algo_id == 0) {
        RkAiqAlgoProcResAsharpV4Int* asharp_rk = (RkAiqAlgoProcResAsharpV4Int*)asharp_com;

        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);

        rk_aiq_isp_sharpen_params_v3x_t* sharp_param = params->mSharpenV3xParams->data().ptr();
        setResultExpectedEffId(sharp_param->frame_id, RK_AIQ_ALGO_TYPE_ASHARP);

        memcpy(&sharp_param->result,
               &asharp_rk->stAsharpProcResult.stFix,
               sizeof(RK_SHARP_Fix_V4_t));
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAmergeResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_AMERGE);
    if (handle == nullptr) {
        return XCAM_RETURN_BYPASS;
    }
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAmerge* amerge_com =
        shared->procResComb.amerge_proc_res;

    rk_aiq_isp_merge_params_v3x_t* merge_param = params->mMergeV3xParams->data().ptr();

    if (!amerge_com) {
        LOGD_ANALYZER("no amerge result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen ahdr common result

    int algo_id = (*handle)->getAlgoId();

    // gen rk ahdr result
    if (algo_id == 0) {
        RkAiqAlgoProcResAmergeInt* amerge_rk = (RkAiqAlgoProcResAmergeInt*)amerge_com;

        setResultExpectedEffId(merge_param->frame_id, RK_AIQ_ALGO_TYPE_AMERGE);

        merge_param->result.Merge_v30.sw_hdrmge_mode =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_mode;
        merge_param->result.Merge_v30.sw_hdrmge_lm_dif_0p9 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_lm_dif_0p9;
        merge_param->result.Merge_v30.sw_hdrmge_ms_dif_0p8 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_ms_dif_0p8;
        merge_param->result.Merge_v30.sw_hdrmge_lm_dif_0p15 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_lm_dif_0p15;
        merge_param->result.Merge_v30.sw_hdrmge_ms_dif_0p15 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_ms_dif_0p15;
        merge_param->result.Merge_v30.sw_hdrmge_gain0 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_gain0;
        merge_param->result.Merge_v30.sw_hdrmge_gain0_inv =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_gain0_inv;
        merge_param->result.Merge_v30.sw_hdrmge_gain1 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_gain1;
        merge_param->result.Merge_v30.sw_hdrmge_gain1_inv =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_gain1_inv;
        merge_param->result.Merge_v30.sw_hdrmge_gain2 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_gain2;
        for(int i = 0; i < 17; i++)
        {
            merge_param->result.Merge_v30.sw_hdrmge_e_y[i] =
                amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_e_y[i];
            merge_param->result.Merge_v30.sw_hdrmge_l1_y[i] =
                amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_l1_y[i];
            merge_param->result.Merge_v30.sw_hdrmge_l0_y[i] =
                amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_l0_y[i];
        }

        merge_param->result.LongFrameMode =
            amerge_rk->AmergeProcRes.LongFrameMode;
        merge_param->result.update =
            amerge_rk->AmergeProcRes.update;

        //isp30 add
        merge_param->result.Merge_v30.sw_hdrmge_s_base =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_s_base;
        merge_param->result.Merge_v30.sw_hdrmge_ms_thd0 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_ms_thd0;
        merge_param->result.Merge_v30.sw_hdrmge_ms_thd1 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_ms_thd1;
        merge_param->result.Merge_v30.sw_hdrmge_ms_scl =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_ms_scl;
        merge_param->result.Merge_v30.sw_hdrmge_lm_thd0 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_lm_thd0;
        merge_param->result.Merge_v30.sw_hdrmge_lm_thd1 =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_lm_thd1;
        merge_param->result.Merge_v30.sw_hdrmge_lm_scl =
            amerge_rk->AmergeProcRes.Merge_v30.sw_hdrmge_lm_scl;

    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}


XCamReturn
RkAiqCoreV3x::genIspAgainResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_AGAIN);
    if (handle == nullptr) {
        return XCAM_RETURN_BYPASS;
    }
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAgain* again_com =
        shared->procResComb.again_proc_res;

    if (!again_com) {
        LOGD_ANALYZER("no asharp result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen asharp common result

    int algo_id = (*handle)->getAlgoId();

    // gen rk asharp result
    if (algo_id == 0) {
        RkAiqAlgoProcResAgainV2Int* again_rk = (RkAiqAlgoProcResAgainV2Int*)again_com;

        if (params->mGainV3xParams.ptr()) {
            rk_aiq_isp_gain_params_v3x_t* gain_param = params->mGainV3xParams->data().ptr();
            setResultExpectedEffId(gain_param ->frame_id, RK_AIQ_ALGO_TYPE_AGAIN);
            LOGD_ANR("oyyf: %s:%d output gain  param start\n", __FUNCTION__, __LINE__);

            memcpy(&gain_param->result,
                   &again_rk->stAgainProcResult.stFix,
                   sizeof(RK_GAIN_Fix_V2_t));
            LOGD_ANR("oyyf: %s:%d output gain param end \n", __FUNCTION__, __LINE__);
        }


    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAfResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_AF);
    if (handle == nullptr) {
        return XCAM_RETURN_BYPASS;
    }
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAf* af_com =
        shared->procResComb.af_proc_res;

    rk_aiq_isp_af_params_v3x_t* af_param = params->mAfV3xParams->data().ptr();

    SmartPtr<rk_aiq_focus_params_wrapper_t> focus_param =
        params->mFocusParams->data();
    rk_aiq_focus_params_t* p_focus_param = &focus_param->result;

#if 0
    isp_param->af_cfg_update = false;
#else
    // af_param->af_cfg_update = false;
#endif
    p_focus_param->lens_pos_valid = false;
    p_focus_param->zoom_pos_valid = false;
    if (!af_com) {
        LOGD_ANALYZER("no af result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen af common result

    int algo_id = (*handle)->getAlgoId();

    // gen rk af result
    if (algo_id == 0) {
        RkAiqAlgoProcResAfInt* af_rk = (RkAiqAlgoProcResAfInt*)af_com;

#if 0
        isp_param->af_meas = af_rk->af_proc_res_com.af_isp_param;
        isp_param->af_cfg_update = af_rk->af_proc_res_com.af_cfg_update;
#else
        setResultExpectedEffId(af_param->frame_id, RK_AIQ_ALGO_TYPE_AF);
        af_param->result = af_rk->af_proc_res_com.af_isp_param_v3x;
        // isp_param->af_cfg_update = af_rk->af_proc_res_com.af_cfg_update;
#endif

        p_focus_param->zoomfocus_modifypos = af_rk->af_proc_res_com.af_focus_param.zoomfocus_modifypos;
        p_focus_param->focus_correction = af_rk->af_proc_res_com.af_focus_param.focus_correction;
        p_focus_param->zoom_correction = af_rk->af_proc_res_com.af_focus_param.zoom_correction;
        p_focus_param->lens_pos_valid = af_rk->af_proc_res_com.af_focus_param.lens_pos_valid;
        p_focus_param->zoom_pos_valid = af_rk->af_proc_res_com.af_focus_param.zoom_pos_valid;
        p_focus_param->send_zoom_reback = af_rk->af_proc_res_com.af_focus_param.send_zoom_reback;
        p_focus_param->send_focus_reback = af_rk->af_proc_res_com.af_focus_param.send_focus_reback;
        p_focus_param->end_zoom_chg = af_rk->af_proc_res_com.af_focus_param.end_zoom_chg;
        p_focus_param->focus_noreback = af_rk->af_proc_res_com.af_focus_param.focus_noreback;
        p_focus_param->use_manual = af_rk->af_proc_res_com.af_focus_param.use_manual;
        p_focus_param->auto_focpos = af_rk->af_proc_res_com.af_focus_param.auto_focpos;
        p_focus_param->auto_zoompos = af_rk->af_proc_res_com.af_focus_param.auto_zoompos;
        p_focus_param->manual_focpos = af_rk->af_proc_res_com.af_focus_param.manual_focpos;
        p_focus_param->manual_zoompos = af_rk->af_proc_res_com.af_focus_param.manual_zoompos;
        p_focus_param->next_pos_num = af_rk->af_proc_res_com.af_focus_param.next_pos_num;
        for (int i = 0; i < af_rk->af_proc_res_com.af_focus_param.next_pos_num; i++) {
            p_focus_param->next_lens_pos[i] = af_rk->af_proc_res_com.af_focus_param.next_lens_pos[i];
            p_focus_param->next_zoom_pos[i] = af_rk->af_proc_res_com.af_focus_param.next_zoom_pos[i];
        }

        p_focus_param->vcm_start_ma = af_rk->af_proc_res_com.af_focus_param.vcm_start_ma;
        p_focus_param->vcm_end_ma = af_rk->af_proc_res_com.af_focus_param.vcm_end_ma;
        p_focus_param->vcm_config_valid = af_rk->af_proc_res_com.af_focus_param.vcm_config_valid;

        {
            SmartPtr<RkAiqHandle>* ae_handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_AE);
            int algo_id = (*ae_handle)->getAlgoId();

            if (ae_handle) {
                if ((algo_id == 0) && (af_rk->af_proc_res_com.lockae_en)) {
                    RkAiqAeHandleInt *ae_algo = dynamic_cast<RkAiqAeHandleInt*>(ae_handle->ptr());
                    Uapi_ExpSwAttr_t expSwAttr;

                    ae_algo->getExpSwAttr(&expSwAttr);
                    if (expSwAttr.enable != !af_rk->af_proc_res_com.lockae) {
                        expSwAttr.enable = !af_rk->af_proc_res_com.lockae;
                        ae_algo->setExpSwAttr(expSwAttr);
                    }
                }
            }
        }
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

XCamReturn
RkAiqCoreV3x::genIspAcacResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_ACAC);
    if (handle == nullptr) {
        return XCAM_RETURN_BYPASS;
    }
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAcac* cac_com =
        shared->procResComb.acac_proc_res;

    rk_aiq_isp_cac_params_v3x_t* cac_param = params->mCacV3xParams->data().ptr();

    int algo_id = (*handle)->getAlgoId();
    if (algo_id == 0) {
        RkAiqAlgoProcResAcacInt* cac_rk = (RkAiqAlgoProcResAcacInt*)cac_com;
        setResultExpectedEffId(cac_param->frame_id, RK_AIQ_ALGO_TYPE_ACAC);
        memcpy(&cac_param->result.cfg[0], &cac_rk->config[0], sizeof(cac_rk->config[0]));
        memcpy(&cac_param->result.cfg[1], &cac_rk->config[1], sizeof(cac_rk->config[1]));
    }

    EXIT_ANALYZER_FUNCTION();
    return ret;
}


XCamReturn
RkAiqCoreV3x::genIspAtnrResult(RkAiqFullParams* params)
{
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    SmartPtr<RkAiqHandle>* handle = getCurAlgoTypeHandle(RK_AIQ_ALGO_TYPE_AMFNR);
    RkAiqCore::RkAiqAlgosGroupShared_t* shared =
        (RkAiqCore::RkAiqAlgosGroupShared_t*)((*handle)->getGroupShared());
    RkAiqAlgoProcResAmfnr* atnr_com =
        shared->procResComb.amfnr_proc_res;

    if (!atnr_com) {
        LOGD_ANALYZER("no abayertnr result");
        return XCAM_RETURN_NO_ERROR;
    }

    // TODO: gen asharp common result

    int algo_id = (*handle)->getAlgoId();

    // gen rk asharp result
    if (algo_id == 0) {
        RkAiqAlgoProcResAbayertnrV2Int* atnr_rk = (RkAiqAlgoProcResAbayertnrV2Int*)atnr_com;

        LOGD_ANR("oyyf: %s:%d output isp param start\n", __FUNCTION__, __LINE__);

        rk_aiq_isp_tnr_params_v3x_t* tnr_param = params->mTnrV3xParams->data().ptr();
        setResultExpectedEffId(tnr_param->frame_id, RK_AIQ_ALGO_TYPE_AMFNR);
        memcpy(&tnr_param->result,
               &atnr_rk->stAbayertnrProcResult.st3DFix,
               sizeof(RK_Bayertnr_Fix_V2_t));
        LOGD_ANR("oyyf: %s:%d output isp param end \n", __FUNCTION__, __LINE__);
    }

    EXIT_ANALYZER_FUNCTION();

    return ret;
}

} //namespace RkCam
