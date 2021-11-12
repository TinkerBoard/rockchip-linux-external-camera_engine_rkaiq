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

#ifndef _RK_AIQ_TYPE_ABAYER2DNR_ALGO_INT_V2_H_
#define _RK_AIQ_TYPE_ABAYER2DNR_ALGO_INT_V2_H_

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "rk_aiq_comm.h"
#include "RkAiqCalibDbTypes.h"
#include "abayer2dnr2/rk_aiq_types_abayer2dnr_algo_v2.h"
#include "bayer2dnr_head_v2.h"

//RKAIQ_BEGIN_DECLARE

#define RK_BAYER2DNR_V2_MAX_ISO_NUM  CALIBDB_MAX_ISO_LEVEL
#define ABAYER2DNRV2_RECALCULATE_DELTA_ISO (10)

typedef enum Abayer2dnr_result_V2_e {
    ABAYER2DNR_RET_SUCCESS             = 0,   // this has to be 0, if clauses rely on it
    ABAYER2DNR_RET_FAILURE             = 1,   // process failure
    ABAYER2DNR_RET_INVALID_PARM        = 2,   // invalid parameter
    ABAYER2DNR_RET_WRONG_CONFIG        = 3,   // feature not supported
    ABAYER2DNR_RET_BUSY                = 4,   // there's already something going on...
    ABAYER2DNR_RET_CANCELED            = 5,   // operation canceled
    ABAYER2DNR_RET_OUTOFMEM            = 6,   // out of memory
    ABAYER2DNR_RET_OUTOFRANGE          = 7,   // parameter/value out of range
    ABAYER2DNR_RET_NULL_POINTER        = 8,   // the/one/all parameter(s) is a(are) NULL pointer(s)
    ABAYER2DNR_RET_DIVISION_BY_ZERO    = 9,   // a divisor equals ZERO
    ABAYER2DNR_RET_NO_INPUTIMAGE       = 10   // no input image
} Abayer2dnr_result_V2_t;

typedef enum Abayer2dnr_State_V2_e {
    ABAYER2DNR_STATE_INVALID           = 0,                   /**< initialization value */
    ABAYER2DNR_STATE_INITIALIZED       = 1,                   /**< instance is created, but not initialized */
    ABAYER2DNR_STATE_STOPPED           = 2,                   /**< instance is confiured (ready to start) or stopped */
    ABAYER2DNR_STATE_RUNNING           = 3,                   /**< instance is running (processes frames) */
    ABAYER2DNR_STATE_LOCKED            = 4,                   /**< instance is locked (for taking snapshots) */
    ABAYER2DNR_STATE_MAX                                      /**< max */
} Abayer2dnr_State_V2_t;

typedef enum Abayer2dnr_OPMode_V2_e {
    ABAYER2DNR_OP_MODE_INVALID           = 0,                   /**< initialization value */
    ABAYER2DNR_OP_MODE_AUTO              = 1,                   /**< instance is created, but not initialized */
    ABAYER2DNR_OP_MODE_MANUAL            = 2,                   /**< instance is confiured (ready to start) or stopped */
    ABAYER2DNR_OP_MODE_MAX                                      /**< max */
} Abayer2dnr_OPMode_V2_t;

typedef enum Abayer2dnr_ParamMode_V2_e {
    ABAYER2DNR_PARAM_MODE_INVALID           = 0,
    ABAYER2DNR_PARAM_MODE_NORMAL          = 1,                   /**< initialization value */
    ABAYER2DNR_PARAM_MODE_HDR              = 2,                   /**< instance is created, but not initialized */
    ABAYER2DNR_PARAM_MODE_GRAY            = 3,                   /**< instance is confiured (ready to start) or stopped */
    ABAYER2DNR_PARAM_MODE_MAX                                      /**< max */
} Abayer2dnr_ParamMode_V2_t;

typedef struct Abayer2dnr_ExpInfo_V2_s {
    int hdr_mode;
    float arTime[3];
    float arAGain[3];
    float arDGain[3];
    int   arIso[3];
    int   snr_mode;
} Abayer2dnr_ExpInfo_V2_t;



typedef struct RK_Bayer2dnr_Params_V2_s
{
    // bayernr version
    int bayernrv2_2dnr_enable;

    // v2 parse
    float iso[RK_BAYER2DNR_V2_MAX_ISO_NUM];
    float bayernrv2_edge_filter_lumapoint_r[8];
    float bayernrv2_edge_filter_wgt_r[RK_BAYER2DNR_V2_MAX_ISO_NUM][8];
    float bayernrv2_filter_strength_r[RK_BAYER2DNR_V2_MAX_ISO_NUM];
    int   bayernrv2_filter_lumapoint_r[16];
    int   bayernrv2_filter_sigma_r[RK_BAYER2DNR_V2_MAX_ISO_NUM][16];
    float bayernrv2_filter_edgesofts_r[RK_BAYER2DNR_V2_MAX_ISO_NUM];
    float bayernrv2_filter_soft_threshold_ratio_r[RK_BAYER2DNR_V2_MAX_ISO_NUM];
    float bayernrv2_filter_out_wgt_r[RK_BAYER2DNR_V2_MAX_ISO_NUM];
    int   bayernrv2_gauss_guide_r[RK_BAYER2DNR_V2_MAX_ISO_NUM];

} RK_Bayer2dnr_Params_V2_t;

typedef struct RK_Bayer2dnr_Params_V2_Select_s
{
    // v2 version register // edge filter params
    int bayernrv2_2dnr_enable;

    float bayernrv2_filter_strength;
    float bayernrv2_filter_soft_threshold_ratio;
    float bayernrv2_filter_out_wgt;
    float bayernrv2_filter_edgesofts;

    int bayernrv2_edge_filter_en;
    int bayernrv2_edge_filter_lumapoint[8];
    int bayernrv2_edge_filter_wgt[8];
    int bayernrv2_gauss_guide;
    int bayernrv2_filter_lumapoint[16];
    int bayernrv2_filter_sigma[16];
    int bayernrv2_bil_gauss_weight[16];
    int bayernrv2_gray_mode;
    int bayernrv2_dgains[3];
    int bayernrv2_thld_diff;
    int bayernrv2_pix_diff;

} RK_Bayer2dnr_Params_V2_Select_t;


typedef struct Abayer2dnr_Manual_Attr_V2_s
{
    int bayernr2DEn;
    int bayernr3DEn;
    RK_Bayer2dnr_Params_V2_Select_t st2DSelect;

} Abayer2dnr_Manual_Attr_V2_t;

typedef struct Abayer2dnr_Auto_Attr_V2_s
{
    //all ISO params and select param
    int bayernr2DEn;

    RK_Bayer2dnr_Params_V2_t st2DParams;
    RK_Bayer2dnr_Params_V2_Select_t st2DSelect;

} Abayer2dnr_Auto_Attr_V2_t;

typedef struct Abayer2dnr_ProcResult_V2_s {
    int bayernr2DEn;

    //for sw simultaion
    RK_Bayer2dnr_Params_V2_Select_t st2DSelect;

    //for hw register
    RK_Bayer2dnr_Fix_V2_t st2DFix;

    bool isNeedUpdate;

} Abayer2dnr_ProcResult_V2_t;


typedef struct Abayer2dnr_Config_V2_s {
    Abayer2dnr_State_V2_t eState;
    Abayer2dnr_OPMode_V2_t eMode;
} Abayer2dnr_Config_V2_t;


typedef struct rk_aiq_bayer2dnr_attrib_v2_s {
    Abayer2dnr_OPMode_V2_t eMode;
    Abayer2dnr_Auto_Attr_V2_t stAuto;
    Abayer2dnr_Manual_Attr_V2_t stManual;
} rk_aiq_bayer2dnr_attrib_v2_t;


typedef struct rk_aiq_bayer2dnr_IQPara_V2_s {
    struct list_head listHead_mode;
} rk_aiq_bayer2dnr_IQPara_V2_t;


typedef struct rk_aiq_bayer2dnr_JsonPara_V2_s {
    CalibDbV2_Bayer2dnr_V2_t bayer2dnr_v2;
} rk_aiq_bayer2dnr_JsonPara_V2_t;


//RKAIQ_END_DECLARE

#endif

