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

#ifndef _RK_AIQ_TYPE_ABAYERTNRV2_ALGO_INT_H_
#define _RK_AIQ_TYPE_ABAYERTNRV2_ALGO_INT_H_

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "rk_aiq_comm.h"
#include "RkAiqCalibDbTypes.h"
#include "abayertnr2/rk_aiq_types_abayertnr_algo_v2.h"
#include "bayertnr_head_v2.h"

//RKAIQ_BEGIN_DECLARE

#define ABAYERTNRV2_RECALCULATE_DELTA_ISO (10)

typedef enum Abayertnr_result_V2_e {
    ABAYERTNRV2_RET_SUCCESS             = 0,   // this has to be 0, if clauses rely on it
    ABAYERTNRV2_RET_FAILURE             = 1,   // process failure
    ABAYERTNRV2_RET_INVALID_PARM        = 2,   // invalid parameter
    ABAYERTNRV2_RET_WRONG_CONFIG        = 3,   // feature not supported
    ABAYERTNRV2_RET_BUSY                = 4,   // there's already something going on...
    ABAYERTNRV2_RET_CANCELED            = 5,   // operation canceled
    ABAYERTNRV2_RET_OUTOFMEM            = 6,   // out of memory
    ABAYERTNRV2_RET_OUTOFRANGE          = 7,   // parameter/value out of range
    ABAYERTNRV2_RET_NULL_POINTER        = 8,   // the/one/all parameter(s) is a(are) NULL pointer(s)
    ABAYERTNRV2_RET_DIVISION_BY_ZERO    = 9,   // a divisor equals ZERO
    ABAYERTNRV2_RET_NO_INPUTIMAGE       = 10   // no input image
} Abayertnr_result_V2_t;

typedef enum Abayertnr_State_V2_e {
    ABAYERTNRV2_STATE_INVALID           = 0,                   /**< initialization value */
    ABAYERTNRV2_STATE_INITIALIZED       = 1,                   /**< instance is created, but not initialized */
    ABAYERTNRV2_STATE_STOPPED           = 2,                   /**< instance is confiured (ready to start) or stopped */
    ABAYERTNRV2_STATE_RUNNING           = 3,                   /**< instance is running (processes frames) */
    ABAYERTNRV2_STATE_LOCKED            = 4,                   /**< instance is locked (for taking snapshots) */
    ABAYERTNRV2_STATE_MAX                                      /**< max */
} Abayertnr_State_V2_t;

typedef enum Abayertnr_OPMode_V2_e {
    ABAYERTNRV2_OP_MODE_INVALID           = 0,                   /**< initialization value */
    ABAYERTNRV2_OP_MODE_AUTO              = 1,                   /**< instance is created, but not initialized */
    ABAYERTNRV2_OP_MODE_MANUAL            = 2,                   /**< instance is confiured (ready to start) or stopped */
    ABAYERTNRV2_OP_MODE_MAX                                      /**< max */
} Abayertnr_OPMode_V2_t;

typedef enum Abayertnr_ParamMode_V2_e {
    ABAYERTNRV2_PARAM_MODE_INVALID           = 0,
    ABAYERTNRV2_PARAM_MODE_NORMAL          = 1,                   /**< initialization value */
    ABAYERTNRV2_PARAM_MODE_HDR              = 2,                   /**< instance is created, but not initialized */
    ABAYERTNRV2_PARAM_MODE_GRAY            = 3,                   /**< instance is confiured (ready to start) or stopped */
    ABAYERTNRV2_PARAM_MODE_MAX                                      /**< max */
} Abayertnr_ParamMode_V2_t;

typedef struct Abayertnr_ExpInfo_V2_s {
    int hdr_mode;
    float arTime[3];
    float arAGain[3];
    float arDGain[3];
    int   arIso[3];
    int   snr_mode;
} Abayertnr_ExpInfo_V2_t;



typedef struct RK_Bayertnr_Params_V2_s
{
    int bayertnrv2_tnr_enable;

    float iso[RK_BAYERNR_V2_MAX_ISO_NUM];

    float bayertnrv2_lo_filter_strength_r[RK_BAYERNR_V2_MAX_ISO_NUM];
    float bayertnrv2_hi_filter_strength_r[RK_BAYERNR_V2_MAX_ISO_NUM];
    float bayertnrv2_filter_soft_threshold_ratio_r[RK_BAYERNR_V2_MAX_ISO_NUM];
    int   bayertnrv2_thumbds_r[RK_BAYERNR_V2_MAX_ISO_NUM];
    int   bayertnrv2_lo_ena_r[RK_BAYERNR_V2_MAX_ISO_NUM];
    int   bayertnrv2_hi_ena_r[RK_BAYERNR_V2_MAX_ISO_NUM];
    int   bayertnrv2_lumapoint_r[16];
    int   bayertnrv2_sigma_r[RK_BAYERNR_V2_MAX_ISO_NUM][16];
    int   bayertnrv2_lumapoint2_r[16];
    int   bayertnrv2_lo_sigma_r[RK_BAYERNR_V2_MAX_ISO_NUM][16];
    int   bayertnrv2_hi_sigma_r[RK_BAYERNR_V2_MAX_ISO_NUM][16];
    int   bayertnrv2_blc_offset;

} RK_Bayertnr_Params_V2_t;


typedef struct RK_Bayertnr_Params_V2_Select_s
{
    int bayertnrv2_tnr_enable;
    int bayertnrv2_logt_en;
    int bayertnrv2_logit_en;

    float bayertnrv2_lo_filter_strength;
    float bayertnrv2_hi_filter_strength;
    float bayertnrv2_filter_soft_threshold_ratio;
    int bayertnrv2_tnr_sigratio;
    int bayertnrv2_tnr_lo_clipwgt;
    int bayertnrv2_tnr_hi_clipwgt;
    int bayertnrv2_tnr_strength;
    int bayertnrv2_tnr_softwgt;
    int bayertnrv2_tnr_global_pk_en;        // 1 use local pk, 0 use global pk
    int bayertnrv2_tnr_global_pksq;
    int bayertnrv2_tnr_luma_point[16];
    int bayertnrv2_tnr_sigma[16];
    int bayertnrv2_tnr_sw_pkds;
    int bayertnrv2_tnr_sw_sigunit;
    int bayertnrv2_tnr_sw_thumbds;
    int bayertnrv2_tnr_sw_lo_ena;
    int bayertnrv2_tnr_sw_lo_med_en;
    int bayertnrv2_tnr_sw_lo_gsbay_en;
    int bayertnrv2_tnr_sw_lo_gslum_en;
    int bayertnrv2_tnr_sw_hi_ena;
    int bayertnrv2_tnr_sw_hi_med_en;
    int bayertnrv2_tnr_sw_hi_gslum_en;
    int bayertnrv2_tnr_sw_hi_gscur_en;
    int bayertnrv2_tnr_sw_hi_gsiir_en;
    int bayertnrv2_tnr_sw_lo_kcoef;
    int bayertnrv2_tnr_sw_hi_kcoef;
    int bayertnrv2_tnr_sw_hi_wgtback;
    int bayertnrv2_tnr_sw_hi_filt_bef_abs;
    int bayertnrv2_tnr_sw_hi_filt_use_bay;
    int bayertnrv2_tnr_sw_wgt_lum[16];
    int bayertnrv2_tnr_sw_lo_sig[16];
    int bayertnrv2_tnr_sw_hi_sig[16];
} RK_Bayertnr_Params_V2_Select_t;


typedef struct Abayertnr_Manual_Attr_V2_s
{
    int bayernr3DEn;
    RK_Bayertnr_Params_V2_Select_t st3DSelect;

} Abayertnr_Manual_Attr_V2_t;

typedef struct Abayertnr_Auto_Attr_V2_s
{
    //all ISO params and select param
    int bayernr3DEn;

    RK_Bayertnr_Params_V2_t st3DParams;
    RK_Bayertnr_Params_V2_Select_t st3DSelect;

} Abayertnr_Auto_Attr_V2_t;

typedef struct Abayertnr_ProcResult_V2_s {
    int bayernr2DEn;
    int bayernr3DEn;

    //for sw simultaion
    RK_Bayertnr_Params_V2_Select_t st3DSelect;

    //for hw register
    RK_Bayertnr_Fix_V2_t st3DFix;

    bool isNeedUpdate;

} Abayertnr_ProcResult_V2_t;


typedef struct Abayertnr_Config_V2_s {
    Abayertnr_State_V2_t eState;
    Abayertnr_OPMode_V2_t eMode;
} Abayertnr_Config_V2_t;


typedef struct rk_aiq_bayertnr_attrib_v2_s {
    Abayertnr_OPMode_V2_t eMode;
    Abayertnr_Auto_Attr_V2_t stAuto;
    Abayertnr_Manual_Attr_V2_t stManual;
} rk_aiq_bayertnr_attrib_v2_t;


typedef struct rk_aiq_bayertnr_IQPara_V2_s {
    struct list_head listHead_mode;
} rk_aiq_bayertnr_IQPara_V2_t;


typedef struct rk_aiq_bayertnr_JsonPara_V2_s {
    CalibDbV2_BayerTnr_V2_t bayernr_v2;
} rk_aiq_bayertnr_JsonPara_V2_t;


//RKAIQ_END_DECLARE

#endif

