/*
 *rk_aiq_types_alsc_algo_int.h
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

#ifndef _RK_AIQ_TYPE_ACNR_ALGO_INT_V2_H_
#define _RK_AIQ_TYPE_ACNR_ALGO_INT_V2_H_

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "rk_aiq_comm.h"
#include "RkAiqCalibDbTypes.h"
#include "acnr2/rk_aiq_types_acnr_algo_v2.h"
#include "RkAiqCalibDbTypesV2.h"
#include "RkAiqCalibDbV2Helper.h"
#include "cnr_head_v2.h"


//RKAIQ_BEGIN_DECLARE
#define RK_CNR_V2_MAX_ISO_NUM (CALIBDB_MAX_ISO_LEVEL)

#define ACNRV2_RECALCULATE_DELTA_ISO       (10)
// fix bit
#define     RK_CNR_V2_sgmGain               4
#define     RK_CNR_V2_sgmRatio              4
#define     RK_CNR_V2_log2e                 6
#define     RK_CNR_V2_gainRatio             7

#define     RK_CNR_V2_ratio                 0
#define     RK_CNR_V2_offset                4

#define     RK_CNR_V2_uvgain_local          4
#define     RK_CNR_V2_kernels               7

#define     RK_CNR_V2_medRatio              4
#define     RK_CNR_V2_sigmaR                0
#define     RK_CNR_V2_sigmaD                0
#define     RK_CNR_V2_uvgain                4

//exp(-x)
#define     RK_CNR_V2_exp2_lut_num          15
#define     RK_CNR_V2_exp2_lut_x            7
#define     RK_CNR_V2_exp2_lut_y            7

#define     RK_CNR_V2_bfRatio               RK_CNR_V2_exp2_lut_y

#define     RK_CNR_V2_SIGMA_FIX_BIT         8

#define     RKCNR_V2_SGM_ADJ_TABLE_LEN      13

#define     RKCNR_V2_SIGMA_FIX_BIT          8
#define     RKCNR_V2_LOCAL_GAIN_FIX_BITS    4
#define     RKCNR_V2_G_GAIN_FIX_BITS        4
#define     RKCNR_V2_G_GAIN_ALPHA_FIX_BITS  3
#define     RKCNR_V2_GAIN_ISO_FIX_BITS      7

typedef enum AcnrV2_result_e {
    ACNRV2_RET_SUCCESS             = 0,   // this has to be 0, if clauses rely on it
    ACNRV2_RET_FAILURE             = 1,   // process failure
    ACNRV2_RET_INVALID_PARM        = 2,   // invalid parameter
    ACNRV2_RET_WRONG_CONFIG        = 3,   // feature not supported
    ACNRV2_RET_BUSY                = 4,   // there's already something going on...
    ACNRV2_RET_CANCELED            = 5,   // operation canceled
    ACNRV2_RET_OUTOFMEM            = 6,   // out of memory
    ACNRV2_RET_OUTOFRANGE          = 7,   // parameter/value out of range
    ACNRV2_RET_NULL_POINTER        = 8,   // the/one/all parameter(s) is a(are) NULL pointer(s)
    ACNRV2_RET_DIVISION_BY_ZERO    = 9,   // a divisor equals ZERO
    ACNRV2_RET_NO_INPUTIMAGE       = 10   // no input image
} AcnrV2_result_t;

typedef enum AcnrV2_State_e {
    ACNRV2_STATE_INVALID           = 0,                   /**< initialization value */
    ACNRV2_STATE_INITIALIZED       = 1,                   /**< instance is created, but not initialized */
    ACNRV2_STATE_STOPPED           = 2,                   /**< instance is confiured (ready to start) or stopped */
    ACNRV2_STATE_RUNNING           = 3,                   /**< instance is running (processes frames) */
    ACNRV2_STATE_LOCKED            = 4,                   /**< instance is locked (for taking snapshots) */
    ACNRV2_STATE_MAX                                      /**< max */
} AcnrV2_State_t;

typedef enum AcnrV2_OPMode_e {
    ACNRV2_OP_MODE_INVALID           = 0,                   /**< initialization value */
    ACNRV2_OP_MODE_AUTO              = 1,                   /**< instance is created, but not initialized */
    ACNRV2_OP_MODE_MANUAL            = 2,                   /**< instance is confiured (ready to start) or stopped */
    ACNRV2_OP_MODE_MAX                                      /**< max */
} AcnrV2_OPMode_t;

typedef enum AcnrV2_ParamMode_e {
    ACNRV2_PARAM_MODE_INVALID           = 0,
    ACNRV2_PARAM_MODE_NORMAL          = 1,                   /**< initialization value */
    ACNRV2_PARAM_MODE_HDR              = 2,                   /**< instance is created, but not initialized */
    ACNRV2_PARAM_MODE_GRAY            = 3,                   /**< instance is confiured (ready to start) or stopped */
    ACNRV2_PARAM_MODE_MAX                                      /**< max */
} AcnrV2_ParamMode_t;

typedef struct AcnrV2_ExpInfo_s {
    int hdr_mode;
    float arTime[3];
    float arAGain[3];
    float arDGain[3];
    int   arIso[3];
    int   snr_mode;
    int rawWidth;
    int rawHeight;
} AcnrV2_ExpInfo_t;

typedef struct RK_CNR_Params_V2_s
{
    int enable;
    float iso[RK_CNR_V2_MAX_ISO_NUM];
    int rkcnr_hq_bila_bypass[RK_CNR_V2_MAX_ISO_NUM];
    int rkcnr_lq_bila_bypass[RK_CNR_V2_MAX_ISO_NUM];

    // gain
    float rkcnr_global_gain[RK_CNR_V2_MAX_ISO_NUM];
    float rkcnr_global_gain_alpha[RK_CNR_V2_MAX_ISO_NUM];
    float rkcnr_gain_iso[RK_CNR_V2_MAX_ISO_NUM];

    // strength adj by gain
    int sgmRatio_gain[RK_CNR_V2_MAX_ISO_NUM][RKCNR_V2_SGM_ADJ_TABLE_LEN];

    //
    float ratio[RK_CNR_V2_MAX_ISO_NUM];
    float offset[RK_CNR_V2_MAX_ISO_NUM];

    // step1
    // median filter
    float medRatio1[RK_CNR_V2_MAX_ISO_NUM];

    // bilateral filter
    float sigmaR1[RK_CNR_V2_MAX_ISO_NUM];
    float uvgain1[RK_CNR_V2_MAX_ISO_NUM];
    float bfRatio1[RK_CNR_V2_MAX_ISO_NUM];
    int  hbf_wgt_clip[RK_CNR_V2_MAX_ISO_NUM];


    // step2
    // median filter
    float medRatio2[RK_CNR_V2_MAX_ISO_NUM];

    // bilateral filter
    float sigmaR2[RK_CNR_V2_MAX_ISO_NUM];
    float uvgain2[RK_CNR_V2_MAX_ISO_NUM];

    // step3
    // bilateral filter
    float sigmaR3[RK_CNR_V2_MAX_ISO_NUM];
    float uvgain3[RK_CNR_V2_MAX_ISO_NUM];
    float bfRatio3[RK_CNR_V2_MAX_ISO_NUM];

    // bilateral filter kernels
    float kernel_5x5_table[5];
} RK_CNR_Params_V2_t;

typedef struct RK_CNR_Params_V2_Select_s
{
    int enable;

    // bypass
    int rkcnr_hq_bila_bypass;
    int rkcnr_lq_bila_bypass;

    // gain

    // gain
    float rkcnr_global_gain;
    float rkcnr_global_gain_alpha;
    float rkcnr_gain_iso;

    // strength adj by gain
    int sgmRatio_gain[RKCNR_V2_SGM_ADJ_TABLE_LEN];

    //
    float ratio;
    float offset;

    // step1
    // median filter
    float medRatio1;

    // bilateral filter
    float sigmaR1;
    float uvgain1;
    float bfRatio1;
    int hbf_wgt_clip;

    // step2

    // median filter
    float medRatio2;

    // bilateral filter
    float sigmaR2;
    float uvgain2;

    // step3
    // bilateral filter
    float sigmaR3;
    float uvgain3;
    float bfRatio3;

    // bilateral filter kernels
    float kernel_5x5_table[5];

} RK_CNR_Params_V2_Select_t;


typedef struct Acnr_Manual_Attr_V2_s
{
    int cnrEn;
    RK_CNR_Params_V2_Select_t stSelect;

} Acnr_Manual_Attr_V2_t;

typedef struct Acnr_Auto_Attr_V2_s
{
    //all ISO params and select param
    int cnrEn;

    RK_CNR_Params_V2_t stParams;
    RK_CNR_Params_V2_Select_t stSelect;

} Acnr_Auto_Attr_V2_t;

typedef struct Acnr_ProcResult_V2_s {
    int cnrEn;

    //for sw simultaion
    RK_CNR_Params_V2_Select_t stSelect;

    //for hw register
    RK_CNR_Fix_V2_t stFix;

    bool isNeedUpdate;

} Acnr_ProcResult_V2_t;


typedef struct Acnr_Config_V2_s {
    AcnrV2_State_t eState;
    AcnrV2_OPMode_t eMode;
    int rawHeight;
    int rawWidth;
} Acnr_Config_V2_t;


typedef struct rk_aiq_cnr_attrib_v2_s {
    AcnrV2_OPMode_t eMode;
    Acnr_Auto_Attr_V2_t stAuto;
    Acnr_Manual_Attr_V2_t stManual;
} rk_aiq_cnr_attrib_v2_t;


typedef struct rk_aiq_cnr_IQPara_V2_s {
    struct list_head* listHead;
} rk_aiq_cnr_IQPara_V2_t;


//calibdb


//RKAIQ_END_DECLARE

#endif

