/*
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

#ifndef _CAM_HW_ISP_PARAMS_H_
#define _CAM_HW_ISP_PARAMS_H_

#include "rk_aiq_pool.h"
#include "rkisp2-config.h"
#include "rkispp-config.h"

namespace RkCam {

template <typename T, typename... Ts>
void convertAiqToIspParams(T& isp_cfg, const Ts&... params){};

template <typename T, typename U>
void convertAiqToIspParams(T& isp_cfg, const U& param);

template <typename T, typename U, typename V>
void convertAiqToIspParams(T& isp_cfg, const U& param, const V& param);

template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_aec_meas_t& aec_meas);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_hist_meas_t& hist_meas);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_awb_stat_cfg_v200_t& awb_meas);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_wb_gain_t& awb_gain,
                           const rk_aiq_isp_blc_t& blc);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_merge_t& amerge_data);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_tmo_t& atmo_data);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_dehaze_t& dhaze);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const AgammaProcRes_t& gamma_out_cfg);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const AdegammaProcRes_t& degamma_cfg);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_debayer_t& demosaic);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_lsc_cfg_t& lsc);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_blc_t& blc);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_dpcc_t& dpcc);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_ccm_cfg_t& ccm);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_lut3d_cfg_t& lut3d_cfg);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_acp_params_t& lut3d_cfg);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_ie_t& ie_cfg);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_rawnr_t& rawnr);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_tnr_t& tnr);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_uvnr_t& uvnr);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_ynr_t& ynr);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_sharpen_t& sharp,
                           const rk_aiq_isp_edgeflt_t& edgeflt);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_af_meas_t& af_data);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_gain_t& gain);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_ldch_t& ldch_cfg);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_fec_t& fec);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_gic_t& gic_cfg);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_orb_t& orb);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_dehaze_v21_t& dhaze);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_awb_stat_cfg_v201_t& awb_meas);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_baynr_v21_t& rawnr);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_bay3d_v21_t& tnr);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_cnr_v21_t& uvnr);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_ynr_v21_t& ynr);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_sharp_v21_t& sharp);
template <typename T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_drc_v21_t& adrc_data);

template <class T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_ccm_cfg_t& ccm);
template <class T>
void convertAiqToIspParams(T& isp_cfg, rk_aiq_isp_blc_v21_t& blc);
template <class T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_isp_gic_v21_t& gic_cfg);
template <class T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_wb_gain_t& awb_gain,
                           const rk_aiq_isp_blc_v21_t* blc);
template <class T>
void convertAiqToIspParams(T& isp_cfg, const rk_aiq_acsm_params_t& csm_cfg);

};  // namespace RkCam

#endif
