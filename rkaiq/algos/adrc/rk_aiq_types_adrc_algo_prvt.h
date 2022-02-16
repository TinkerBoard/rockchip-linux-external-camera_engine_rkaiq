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
#ifndef __RK_AIQ_TYPES_ADRC_ALGO_PRVT_H__
#define __RK_AIQ_TYPES_ADRC_ALGO_PRVT_H__

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "RkAiqCalibDbV2Helper.h"
#include "ae/rk_aiq_types_ae_algo_int.h"
#include "af/rk_aiq_types_af_algo_int.h"
#include "amerge/rk_aiq_types_amerge_algo_prvt.h"
#include "rk_aiq_algo_types.h"
#include "rk_aiq_types_adrc_algo_int.h"
#include "rk_aiq_types_adrc_hw.h"
#include "rk_aiq_types_adrc_stat_v200.h"
#include "xcam_log.h"

#define GAINMIN                 (1)
#define DRCGAINMAX     (8)
#define DRCGAINMIN              (GAINMIN)
#define CLIPMAX     (64.0)
#define CLIPMIN     (0.0)
#define MINOGAINMAX     (2.0)
#define MINOGAINMIN     (0.0)
#define ADRCNORMALIZEMAX     (1.0)
#define ADRCNORMALIZEMIN     (0.0)
#define ADRCNORMALIZEINTMAX     (1)
#define ADRCNORMALIZEINTMIN     (0)
#define SPACESGMMAX     (4095)
#define SPACESGMMIN     (0)
#define SCALEYMAX     (2048)
#define SCALEYMIN     (0)
#define MANUALCURVEMAX     (8192)
#define MANUALCURVEMIN     (0)
#define IIRFRAMEMAX     (1000)
#define IIRFRAMEMIN     (0)
#define INTMIN                  (0)
#define INT8BITMAX     (255)
#define INT14BITMAX     (16383)
#define INT16BITMAX             (65535)
#define SW_DRC_OFFSET_POW2_FIX (8)
#define SW_DRC_MOTION_SCL_FIX (0)
#define SW_DRC_BILAT_WT_OFF_FIX (255)
#define MAX_AE_DRC_GAIN (256)
#define OB_OFFSET_MAX           (511)
#define OB_OFFSET_MIN           (0)
#define OB_MAX_MAX              (1048575)
#define OB_MAX_MIN              (0)
#define OB_PREDGAIN_MAX         (255.9)
#define OB_PREDGAIN_MIN         (GAINMIN)
#define GAS_T_MAX               (4)
#define GAS_T_MIN               (0)
#define GAS_L_MAX               (64)
#define GAS_L_MIN               (0)

#define ISP_RAW_BIT (12)
#define MFHDR_LOG_Q_BITS (11)
#define DSTBITS (ISP_RAW_BIT << MFHDR_LOG_Q_BITS)
#define OFFSETBITS_INT (SW_DRC_OFFSET_POW2_FIX)
#define OFFSETBITS (OFFSETBITS_INT << MFHDR_LOG_Q_BITS)
#define VALIDBITS (DSTBITS - OFFSETBITS)
#define DELTA_SCALEIN_FIX ((256 << MFHDR_LOG_Q_BITS) / VALIDBITS)


typedef enum AdrcState_e {
    ADRC_STATE_INVALID       = 0,
    ADRC_STATE_INITIALIZED   = 1,
    ADRC_STATE_STOPPED       = 2,
    ADRC_STATE_RUNNING       = 3,
    ADRC_STATE_LOCKED        = 4,
    ADRC_STATE_MAX
} AdrcState_t;

typedef struct AdrcGainConfig_s {
    int len;
    float*            EnvLv;
    float*            DrcGain;
    float*            Alpha;
    float*            Clip;
} AdrcGainConfig_t;

typedef struct HighLightConfig_s {
    int len;
    float*            EnvLv;
    float*            Strength;
} HighLightConfig_t;

typedef struct LocalDataConfigV10_s {
    int len;
    float*            EnvLv;
    float*            LocalWeit;
    float*            GlobalContrast;
    float*            LoLitContrast;
} LocalDataConfigV10_t;

typedef struct LocalDataConfigV11_s {
    int len;
    float*            EnvLv;
    float*            LocalWeit;
    int*            LocalAutoEnable;
    float*            LocalAutoWeit;
    float*            GlobalContrast;
    float*            LoLitContrast;
} LocalDataConfigV11_t;

typedef struct DrcOhters_s {
    bool OutPutLongFrame;
    float curPixWeit;
    float preFrameWeit;
    float Range_force_sgm;
    float Range_sgm_cur;
    float Range_sgm_pre;
    int Space_sgm_cur;
    int Space_sgm_pre;
    int Scale_y[ADRC_Y_NUM];
    float ByPassThr;
    float Edge_Weit;
    float Tolerance;
    int IIR_frame;
    float damp;
} DrcOhters_t;

typedef struct CompressConfig_s {
    CompressMode_t Mode;
    uint16_t       Manual_curve[ADRC_Y_NUM];
} CompressConfig_t;

typedef struct DrcHandleDataV10_s {
    float DrcGain;
    float Alpha;
    float Clip;
    float Strength;
    float LocalWeit;
    float GlobalContrast;
    float LoLitContrast;
    CompressMode_t Mode;
    uint16_t Manual_curve[ADRC_Y_NUM];
} DrcHandleDataV10_t;

typedef struct DrcHandleDataV11_s {
    float DrcGain;
    float Alpha;
    float Clip;
    float Strength;
    float LocalWeit;
    int LocalAutoEnable;
    float LocalAutoWeit;
    float GlobalContrast;
    float LoLitContrast;
    CompressMode_t Mode;
    uint16_t       Manual_curve[ADRC_Y_NUM];
} DrcHandleDataV11_t;

typedef struct DrcHandleDataV12_s {
    float DrcGain;
    float Alpha;
    float Clip;
    float Strength;
    float LocalWeit;
    int LocalAutoEnable;
    float LocalAutoWeit;
    float GlobalContrast;
    float LoLitContrast;
    CompressMode_t Mode;
    uint16_t       Manual_curve[ADRC_Y_NUM];
    // v12 add
    float gas_t;
    int gas_l0;
    int gas_l1;
    int gas_l2;
    int gas_l3;
    bool obEnable;
    int ob_offset;
    float predgain;
    float MotionStr;
} DrcHandleDataV12_t;

typedef struct DrcHandleData_s {
#if RKAIQ_HAVE_DRC_V10
    DrcHandleDataV10_t Drc_v10;
#endif
#if RKAIQ_HAVE_DRC_V11
    DrcHandleDataV11_t Drc_v11;
#endif
#if RKAIQ_HAVE_DRC_V12
    DrcHandleDataV12_t Drc_v12;
#endif
} DrcHandleData_t;

typedef struct AdrcPrevData_s {
    float EnvLv;
    float ISO;
    float MotionCoef;
    drc_OpMode_t ApiMode;
    int frameCnt;
    DrcHandleData_t HandleData;
} AdrcPrevData_t;

typedef struct AdrcAEData_s {
    float GlobalEnvLv;
    float L2M_Ratio;
    float M2S_Ratio;
    float L2S_Ratio;
    float ISO;
    float LExpo;
    float MExpo;
    float SExpo;
} AdrcAEData_t;

typedef struct CurrAeResult_s {
    bool LongFrmMode;
    AdrcAEData_t Curr;
    AdrcAEData_t Next;
} CurrAeResult_t;

typedef struct CurrData_s {
    bool Enable;
    float Ratio;
    float EnvLv;
    float MotionCoef;
    float ISO;
    float Damp;
    float LumaWeight[225];
    int frameCnt;
    DrcHandleData_t HandleData;
    DrcOhters_t Others;
} CurrData_t;

typedef struct AdrcContext_s {
#if RKAIQ_HAVE_DRC_V10
    drcAttrV10_t drcAttrV10;
    CalibDbV2_drc_V10_t CalibDBV10;
#endif
#if RKAIQ_HAVE_DRC_V11
    drcAttrV11_t drcAttrV11;
    CalibDbV2_drc_V11_t CalibDBV11;
#endif
#if RKAIQ_HAVE_DRC_V12
    drcAttrV12_t drcAttrV12;
    CalibDbV2_drc_V12_t CalibDBV12;
#endif
    AdrcState_t state;
    AdrcPrevData_t PrevData ;
    RkAiqAdrcProcResult_t AdrcProcRes;
    CurrAeResult_t AeResult;
    CurrData_t CurrData;
    rkisp_adrc_stats_t CurrStatsData;
    int frameCnt;
    FrameNumber_t FrameNumber;
} AdrcContext_t;

#endif
