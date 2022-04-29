/*
 * Copyright (c) 2019-2022 Rockchip Eletronics Co., Ltd.
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
#ifndef RK_AIQ_CORE_CONFIG_V32_H
#define RK_AIQ_CORE_CONFIG_V32_H

#include "a3dlut/rk_aiq_algo_a3dlut_itf.h"
#include "abayer2dnr2/rk_aiq_abayer2dnr_algo_itf_v2.h"
#include "abayer2dnrV23/rk_aiq_abayer2dnr_algo_itf_v23.h"
#include "abayertnr2/rk_aiq_abayertnr_algo_itf_v2.h"
#include "abayertnrV23/rk_aiq_abayertnr_algo_itf_v23.h"
#include "ablc/rk_aiq_algo_ablc_itf.h"
#include "ablcV32/rk_aiq_ablc_algo_itf_v32.h"
#include "acac/rk_aiq_algo_acac_itf.h"
#include "accm/rk_aiq_algo_accm_itf.h"
#include "acgc/rk_aiq_algo_acgc_itf.h"
#include "acnr2/rk_aiq_acnr_algo_itf_v2.h"
#include "acnrV30/rk_aiq_acnr_algo_itf_v30.h"
#include "acp/rk_aiq_algo_acp_itf.h"
#include "acsm/rk_aiq_algo_acsm_itf.h"
#include "adebayer/rk_aiq_algo_adebayer_itf.h"
#include "adegamma/rk_aiq_algo_adegamma_itf.h"
#include "adehaze/rk_aiq_algo_adehaze_itf.h"
#include "adpcc/rk_aiq_algo_adpcc_itf.h"
#include "adrc/rk_aiq_algo_adrc_itf.h"
#include "ae/rk_aiq_algo_ae_itf.h"
#include "af/rk_aiq_algo_af_itf.h"
#include "afec/rk_aiq_algo_afec_itf.h"
#include "again2/rk_aiq_again_algo_itf_v2.h"
#include "agamma/rk_aiq_algo_agamma_itf.h"
#include "agic/rk_aiq_algo_agic_itf.h"
#include "aie/rk_aiq_algo_aie_itf.h"
#include "aldch/rk_aiq_algo_aldch_itf.h"
#include "alsc/rk_aiq_algo_alsc_itf.h"
#include "amerge/rk_aiq_algo_amerge_itf.h"
#include "asd/rk_aiq_algo_asd_itf.h"
#include "asharp4/rk_aiq_asharp_algo_itf_v4.h"
#include "asharpV33/rk_aiq_asharp_algo_itf_v33.h"
#include "awb/rk_aiq_algo_awb_itf.h"
#include "awdr/rk_aiq_algo_awdr_itf.h"
#include "aynr3/rk_aiq_aynr_algo_itf_v3.h"
#include "aynrV22/rk_aiq_aynr_algo_itf_v22.h"

namespace RkCam {

/*
 * isp gets the stats from frame n-1,
 * and the new parameters take effect on frame n+1
 */
#define ISP_PARAMS_EFFECT_DELAY_CNT 2

static RkAiqGrpCondition_t aeGrpCondV3x[] = {
    [0] = {XCAM_MESSAGE_AEC_STATS_OK, ISP_PARAMS_EFFECT_DELAY_CNT},
};
static RkAiqGrpConditions_t aeGrpCondsV3x = {grp_conds_array_info(aeGrpCondV3x)};

static RkAiqGrpCondition_t awbGrpCond[] = {
    [0] = {XCAM_MESSAGE_SOF_INFO_OK, 0},
    [1] = {XCAM_MESSAGE_AE_PRE_RES_OK, 0},
    [2] = {XCAM_MESSAGE_AWB_STATS_OK, ISP_PARAMS_EFFECT_DELAY_CNT},
    [3] = {XCAM_MESSAGE_BLC_V32_PROC_RES_OK, 0},
};
static RkAiqGrpConditions_t awbGrpConds = {grp_conds_array_info(awbGrpCond)};

static RkAiqGrpCondition_t afGrpCondV3x[] = {
    [0] = {XCAM_MESSAGE_AF_STATS_OK, ISP_PARAMS_EFFECT_DELAY_CNT},
#if RKAIQ_HAVE_PDAF
    [1] = {XCAM_MESSAGE_PDAF_STATS_OK, ISP_PARAMS_EFFECT_DELAY_CNT},
#endif
};
static RkAiqGrpConditions_t afGrpCondsV3x = {grp_conds_array_info(afGrpCondV3x)};

static RkAiqGrpCondition_t otherGrpCondV21[] = {
    [0] = {XCAM_MESSAGE_SOF_INFO_OK, 0},
};
static RkAiqGrpConditions_t otherGrpCondsV21 = {grp_conds_array_info(otherGrpCondV21)};

static RkAiqGrpCondition_t grp0Cond[] = {
    [0] = {XCAM_MESSAGE_SOF_INFO_OK, 0},
    [1] = {XCAM_MESSAGE_AE_PRE_RES_OK, 0},
    [2] = {XCAM_MESSAGE_AE_PROC_RES_OK, 0},
    [3] = {XCAM_MESSAGE_AEC_STATS_OK, ISP_PARAMS_EFFECT_DELAY_CNT},
    [4] = {XCAM_MESSAGE_BLC_V32_PROC_RES_OK, 0},
};
static RkAiqGrpConditions_t grp0Conds = {grp_conds_array_info(grp0Cond)};

static RkAiqGrpCondition_t grp1Cond[] = {
    [0] = {XCAM_MESSAGE_SOF_INFO_OK, 0},
    [1] = {XCAM_MESSAGE_AWB_PROC_RES_OK, 0},
};
static RkAiqGrpConditions_t grp1Conds = {grp_conds_array_info(grp1Cond)};

static RkAiqGrpCondition_t otherGrpCondV3x[] = {
    [0] = {XCAM_MESSAGE_SOF_INFO_OK, 0},
};
static RkAiqGrpConditions_t otherGrpCondsV3x = {grp_conds_array_info(otherGrpCondV3x)};

static struct RkAiqAlgoDesCommExt g_default_3a_des[] = {
// clang-format off

#if RKAIQ_HAVE_AE_V1
    { &g_RkIspAlgoDescAe.common,            RK_AIQ_CORE_ANALYZE_AE,     0, 3, 0,    aeGrpCondsV3x      },
#endif
#if RKAIQ_HAVE_BLC_V32
    { &g_RkIspAlgoDescAblcV32.common,          RK_AIQ_CORE_ANALYZE_OTHER,    32, 32, 32,    otherGrpCondsV3x        },
#endif
#if RKAIQ_HAVE_AWB_V32
    { &g_RkIspAlgoDescAwb.common,           RK_AIQ_CORE_ANALYZE_AWB,    1, 2, 32,   awbGrpConds        },
#endif

#if RKAIQ_HAVE_CAC_V11
    { &g_RkIspAlgoDescAcac.common,          RK_AIQ_CORE_ANALYZE_GRP0,   0, 0, 11,   grp0Conds          },
#endif

#if RKAIQ_HAVE_DEBAYER_V2
    { &g_RkIspAlgoDescAdebayer.common,      RK_AIQ_CORE_ANALYZE_OTHER,   0, 1, 0,    otherGrpCondsV3x          },
#endif

#if RKAIQ_HAVE_GAIN_V2
    { &g_RkIspAlgoDescAgainV2.common,       RK_AIQ_CORE_ANALYZE_GRP0,   2, 2, 2,    grp0Conds          },
#endif

#if RKAIQ_HAVE_GAMMA_V11
    { &g_RkIspAlgoDescAgamma.common,        RK_AIQ_CORE_ANALYZE_GRP0,   0, 0, 0,    grp0Conds          },
#endif
#if RKAIQ_HAVE_DEHAZE_V12
    { &g_RkIspAlgoDescAdhaz.common,         RK_AIQ_CORE_ANALYZE_GRP0,   0, 1, 0,    grp0Conds          },
#endif
#if RKAIQ_HAVE_DRC_V12
    { &g_RkIspAlgoDescAdrc.common,          RK_AIQ_CORE_ANALYZE_GRP0,   0, 0, 0,    grp0Conds          },
#endif
#if RKAIQ_HAVE_MERGE_V12
    { &g_RkIspAlgoDescAmerge.common,        RK_AIQ_CORE_ANALYZE_GRP0,   0, 0, 0,    grp0Conds          },
#endif
#if RKAIQ_HAVE_CCM_V2
    { &g_RkIspAlgoDescAccm.common,          RK_AIQ_CORE_ANALYZE_GRP1,   0, 0, 0,    grp1Conds          },
#endif
#if RKAIQ_HAVE_3DLUT_V1
    { &g_RkIspAlgoDescA3dlut.common,        RK_AIQ_CORE_ANALYZE_GRP1,   0, 0, 0,    grp1Conds          },
#endif
#if RKAIQ_HAVE_LSC_V3
    { &g_RkIspAlgoDescAlsc.common,          RK_AIQ_CORE_ANALYZE_GRP1,   0, 0, 0,    grp1Conds          },
#endif
#if RKAIQ_HAVE_DPCC_V1
    { &g_RkIspAlgoDescAdpcc.common,         RK_AIQ_CORE_ANALYZE_OTHER,  0, 0, 0,    otherGrpCondsV3x   },
#endif
#if 0
    { &g_RkIspAlgoDescAdegamma.common,      RK_AIQ_CORE_ANALYZE_GRP0,   0, 0, 0,    grp0Conds          },
#if RKAIQ_HAVE_CAC_V10
    { &g_RkIspAlgoDescAcac.common,          RK_AIQ_CORE_ANALYZE_GRP0,   0, 0, 0,    grp0Conds          },
#endif
#endif
#if RKAIQ_HAVE_ACP_V10
    { &g_RkIspAlgoDescAcp.common,           RK_AIQ_CORE_ANALYZE_OTHER,  0, 0, 0,    otherGrpCondsV3x   },
#endif
#if RKAIQ_HAVE_AIE_V10
    { &g_RkIspAlgoDescAie.common,           RK_AIQ_CORE_ANALYZE_OTHER,  0, 0, 0,    otherGrpCondsV3x   },
#endif
#if RKAIQ_HAVE_LDCH_V21
    { &g_RkIspAlgoDescAldch.common,         RK_AIQ_CORE_ANALYZE_OTHER,  0, 0, 0,    otherGrpCondsV3x   },
#endif
#if RKAIQ_HAVE_CGC_V1
    { &g_RkIspAlgoDescAcgc.common,          RK_AIQ_CORE_ANALYZE_OTHER,  0, 0, 0,    otherGrpCondsV3x   },
#endif
#if RKAIQ_HAVE_CSM_V1
    { &g_RkIspAlgoDescAcsm.common,          RK_AIQ_CORE_ANALYZE_OTHER,  0, 0, 0,    otherGrpCondsV3x   },
#endif
#if RKAIQ_HAVE_AF_V31
    { &g_RkIspAlgoDescAf.common,            RK_AIQ_CORE_ANALYZE_AF,     0, 2, 0,    afGrpCondsV3x      },
#endif
#if RKAIQ_HAVE_GIC_V2
    { &g_RkIspAlgoDescAgic.common,          RK_AIQ_CORE_ANALYZE_OTHER,  0, 1, 0,    otherGrpCondsV3x   },
#endif
    { &g_RkIspAlgoDescAsd.common,           RK_AIQ_CORE_ANALYZE_GRP0,   0, 0, 0,    grp0Conds          },
#if 0
    { &g_RkIspAlgoDescAwdr.common,          RK_AIQ_CORE_ANALYZE_OTHER,  0, 0, 0,    otherGrpCondsV3x   },
#endif

#if RKAIQ_HAVE_BAYERTNR_V23
    { &g_RkIspAlgoDescAbayertnrV23.common, RK_AIQ_CORE_ANALYZE_GRP0,    23, 23, 23, grp0Conds          },
#endif
#if RKAIQ_HAVE_BAYER2DNR_V23
    { &g_RkIspAlgoDescAbayer2dnrV23.common, RK_AIQ_CORE_ANALYZE_GRP0,   23, 23, 23, grp0Conds          },
#endif
#if RKAIQ_HAVE_YNR_V22
    { &g_RkIspAlgoDescAynrV22.common,       RK_AIQ_CORE_ANALYZE_GRP0,   22, 22, 22, grp0Conds          },
#endif
#if RKAIQ_HAVE_CNR_V30
    { &g_RkIspAlgoDescAcnrV30.common, RK_AIQ_CORE_ANALYZE_GRP0,    30, 30, 30, grp0Conds          },
#endif
#if RKAIQ_HAVE_SHARP_V33
    { &g_RkIspAlgoDescAsharpV33.common,       RK_AIQ_CORE_ANALYZE_GRP0,   33, 33, 33,    grp0Conds          },
#endif
    { NULL,                                 RK_AIQ_CORE_ANALYZE_ALL,    0, 0, 0,    {0, 0}             },
    // clang-format on

};

}  // namespace RkCam

#endif  // RK_AIQ_CORE_CONFIG_V32_H
