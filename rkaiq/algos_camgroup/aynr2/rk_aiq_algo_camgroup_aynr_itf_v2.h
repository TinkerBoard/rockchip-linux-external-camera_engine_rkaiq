/*
 * rk_aiq_algo_camgroup_aynr_itf.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
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


#ifndef _RK_AIQ_ALGO_CAMGROUP_AYNRV2_ITF_H_
#define _RK_AIQ_ALGO_CAMGROUP_AYNRV2_ITF_H_


#include "rk_aiq_algo_des.h"

#define RKISP_ALGO_CAMGROUP_AYNRV2_VERSION     "v0.0.1"
#define RKISP_ALGO_CAMGROUP_AYNRV2_VENDOR      "Rockchip"
#define RKISP_ALGO_CAMGROUP_AYNRV2_DESCRIPTION "Rockchip AynrV2 camgroup algo for ISP2.0"

XCAM_BEGIN_DECLARE

extern RkAiqAlgoDescription g_RkIspAlgoDescCamgroupAynrV2;

XCAM_END_DECLARE

#endif //_RK_AIQ_ALGO_AWB_ITF_H_
