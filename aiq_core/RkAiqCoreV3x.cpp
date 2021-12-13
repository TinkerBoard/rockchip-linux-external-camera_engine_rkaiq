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
    { &g_RkIspAlgoDescAldch.common, RK_AIQ_CORE_ANALYZE_OTHER, 0, 0, otherGrpCondsV3x },
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
                mAiqIspMergeParamsPool   = new RkAiqIspMergeParamsPool("RkAiqIspMergeParams", RkAiqCore::DEFAULT_POOL_SIZE);
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
                mAiqIspLscParamsPool     = new RkAiqIspLscParamsPool("RkAiqIspLscParams", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ABLC:
                mAiqIspBlcV21ParamsPool     = new RkAiqIspBlcParamsPoolV21("RkAiqIspBlcParamsV21", RkAiqCore::DEFAULT_POOL_SIZE);
                break;
            case RK_AIQ_ALGO_TYPE_ARAWNR:
                mAiqIspBaynrV3xParamsPool      = new RkAiqIspBaynrParamsPoolV3x("RkAiqIspRawnrParams", RkAiqCore::DEFAULT_POOL_SIZE);
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
                mAiqIspAgammaParamsPool  = new RkAiqIspAgammaParamsPool("RkAiqIspAgammaParams", RkAiqCore::DEFAULT_POOL_SIZE);
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
                mAiqIspDrcParamsPool        = new RkAiqIspDrcParamsPool("RkAiqIspDrcParams", RkAiqCore::DEFAULT_POOL_SIZE);
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

SmartPtr<RkAiqHandle>
RkAiqCoreV3x::newAlgoHandle(RkAiqAlgoDesComm* algo, int version)
{
#define NEW_ALGO_HANDLE_WITH_V(lc, BC, v) \
    do {\
        if (algo->type == RK_AIQ_ALGO_TYPE_##BC) \
            return new RkAiq##lc##V##v##HandleInt(algo, this); \
    } while(0)\

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
        return NULL;
    } else {
        return RkAiqCoreV21::newAlgoHandle(algo, version);
    }
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

} //namespace RkCam
