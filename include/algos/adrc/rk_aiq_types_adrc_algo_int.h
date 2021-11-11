/******************************************************************************
 *
 * Copyright 2019, Fuzhou Rockchip Electronics Co.Ltd . All rights reserved.
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of:
 * Fuzhou Rockchip Electronics Co.Ltd .
 *
 *
 *****************************************************************************/
#ifndef __RK_AIQ_TYPES_ADRC_ALGO_INT_H__
#define __RK_AIQ_TYPES_ADRC_ALGO_INT_H__

#include "RkAiqCalibDbTypes.h"
#include "adrc_head.h"
#include "rk_aiq_types_adrc_stat_v200.h"

#define AIQ_ISP3X_DRC_Y_NUM 17


typedef struct DrcProcResV20_s
{
    int sw_drc_offset_pow2;
    int sw_drc_compres_scl;
    int sw_drc_position;
    int sw_drc_delta_scalein;
    int sw_drc_hpdetail_ratio;
    int sw_drc_lpdetail_ratio;
    int sw_drc_weicur_pix;
    int sw_drc_weipre_frame;
    int sw_drc_force_sgm_inv0;
    int sw_drc_motion_scl;
    int sw_drc_edge_scl;
    int sw_drc_space_sgm_inv1;
    int sw_drc_space_sgm_inv0;
    int sw_drc_range_sgm_inv1;
    int sw_drc_range_sgm_inv0;
    int sw_drc_weig_maxl;
    int sw_drc_weig_bilat;
    int sw_drc_gain_y[ISP21_DRC_Y_NUM];
    int sw_drc_compres_y[ISP21_DRC_Y_NUM];
    int sw_drc_scale_y[ISP21_DRC_Y_NUM];
    float sw_drc_adrc_gain;
    int sw_drc_iir_weight;
    int sw_drc_min_ogain;

} DrcProcResV20_t;

typedef struct DrcProcResV21_s {
    int bypass_en;
    int offset_pow2;
    int compres_scl;
    int position;
    int delta_scalein;
    int hpdetail_ratio;
    int lpdetail_ratio;
    int weicur_pix;
    int weipre_frame;
    int bilat_wt_off;
    int force_sgm_inv0;
    int motion_scl;
    int edge_scl;
    int space_sgm_inv1;
    int space_sgm_inv0;
    int range_sgm_inv1;
    int range_sgm_inv0;
    int weig_maxl;
    int weig_bilat;
    int enable_soft_thd;
    int bilat_soft_thd;
    int gain_y[AIQ_ISP3X_DRC_Y_NUM];
    int compres_y[AIQ_ISP3X_DRC_Y_NUM];
    int scale_y[AIQ_ISP3X_DRC_Y_NUM];
    float adrc_gain;
    int wr_cycle;
    int iir_weight;
    int min_ogain;
} DrcProcResV21_t;

typedef struct DrcProcRes_s {
    union {
        DrcProcResV20_t Drc_v20;
        DrcProcResV21_t Drc_v21;
    };
} DrcProcRes_t;

typedef struct RkAiqAdrcProcResult_s
{
    DrcProcRes_t DrcProcRes;
    CompressMode_t CompressMode;
    bool update;
    bool LongFrameMode;
    bool isHdrGlobalTmo;
    bool bTmoEn;
    bool isLinearTmo;
} RkAiqAdrcProcResult_t;


#endif
