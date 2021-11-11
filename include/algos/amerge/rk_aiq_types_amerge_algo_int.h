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
#ifndef __RK_AIQ_TYPES_AMERGE_ALGO_INT_H__
#define __RK_AIQ_TYPES_AMERGE_ALGO_INT_H__

#include "RkAiqCalibDbTypes.h"
#include "amerge_head.h"

typedef struct mgeCtrlData_S
{
    float stCoef;
    float stCoefMax;
    float stCoefMin;
    float stSmthMax;
    float stSmthMin;
    float stOfstMax;
    float stOfstMin;
} mgeCtrlData_t;

typedef struct amgeAttr_s
{
    mgeCtrlData_t stMDCurveLM;
    mgeCtrlData_t stMDCurveMS;
    mgeCtrlData_t stOECurve;
} amgeAttr_t;

typedef struct mmgeAttr_s
{
    float OECurve_smooth;
    float OECurve_offset;
    float MDCurveLM_smooth;
    float MDCurveLM_offset;
    float MDCurveMS_smooth;
    float MDCurveMS_offset;
    float dampOE;
    float dampMDLM;
    float dampMDMS;
} mmgeAttr_t;

typedef struct amergeAttr_s
{
    bool      bUpdateMge;
    amgeAttr_t stMgeAuto;
} amergeAttr_t;

typedef struct mmergeAttr_s
{
    bool      bUpdateMge;
    mmgeAttr_t stMgeManual;
} mmergeAttr_t;

typedef enum merge_OpMode_s {
    MERGE_OPMODE_API_OFF = 0, // run IQ ahdr
    MERGE_OPMODE_AUTO = 1, //run api auto ahdr
    MERGE_OPMODE_MANU = 2, //run api manual ahdr
    MERGE_OPMODE_TOOL = 3, // for tool
} merge_OpMode_t;

typedef struct MergeCurrCtlData_s
{
    float Envlv;
    float MoveCoef;
} MergeCurrCtlData_t;

typedef struct MergeCurrRegData_s
{
    float OECurve_smooth;
    float OECurve_offset;
    float MDCurveLM_smooth;
    float MDCurveLM_offset;
    float MDCurveMS_smooth;
    float MDCurveMS_offset;
} MergeCurrRegData_t;

typedef struct mergeAttr_s
{
    merge_OpMode_t    opMode;
    amergeAttr_t    stAuto;
    mmergeAttr_t stManual;
    MergeCurrCtlData_t CtlInfo;
    MergeCurrRegData_t RegInfo;
    CalibDbV2_merge_t stTool;
} mergeAttr_t;

typedef struct MgeProcRes_s
{
    unsigned char  sw_hdrmge_mode;
    unsigned short sw_hdrmge_gain0_inv;
    unsigned short sw_hdrmge_gain0;
    unsigned short sw_hdrmge_gain1_inv;
    unsigned short sw_hdrmge_gain1;
    unsigned char  sw_hdrmge_gain2;
    unsigned char  sw_hdrmge_ms_dif_0p8;
    unsigned char  sw_hdrmge_lm_dif_0p9;
    unsigned char  sw_hdrmge_ms_dif_0p15;
    unsigned char  sw_hdrmge_lm_dif_0p15;
    unsigned short sw_hdrmge_l0_y[17];
    unsigned short sw_hdrmge_l1_y[17];
    unsigned short sw_hdrmge_e_y[17];
} MgeProcRes_t;

typedef struct MgeProcResV2_s
{
    unsigned char  sw_hdrmge_s_base;
    unsigned char  sw_hdrmge_mode;
    unsigned short sw_hdrmge_gain0_inv;
    unsigned short sw_hdrmge_gain0;
    unsigned short sw_hdrmge_gain1_inv;
    unsigned short sw_hdrmge_gain1;
    unsigned char  sw_hdrmge_gain2;
    unsigned char  sw_hdrmge_ms_dif_0p8;
    unsigned char  sw_hdrmge_lm_dif_0p9;
    unsigned char  sw_hdrmge_ms_dif_0p15;
    unsigned char  sw_hdrmge_lm_dif_0p15;
    unsigned short sw_hdrmge_l0_y[17];
    unsigned short sw_hdrmge_l1_y[17];
    unsigned short sw_hdrmge_e_y[17];
    unsigned short sw_hdrmge_ms_thd1;
    unsigned short sw_hdrmge_ms_thd0;
    unsigned short sw_hdrmge_ms_scl;
    unsigned short sw_hdrmge_lm_thd1;
    unsigned short sw_hdrmge_lm_thd0;
    unsigned short sw_hdrmge_lm_scl;
} MgeProcResV2_t;

typedef struct RkAiqAmergeProcResult_s
{
    union {
        MgeProcRes_t Merge_v20;
        MgeProcResV2_t Merge_v30;
    };
    bool update;;
    bool LongFrameMode;
} RkAiqAmergeProcResult_t;


#endif
