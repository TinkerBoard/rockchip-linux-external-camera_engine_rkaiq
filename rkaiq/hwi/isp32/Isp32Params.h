/*
 * Copyright (c) 2021-2022 Rockchip Eletronics Co., Ltd.
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
#ifndef _CAM_HW_ISP32_PARAMS_H_
#define _CAM_HW_ISP32_PARAMS_H_

#include "isp3x/Isp3xParams.h"
#include "rk_aiq_pool.h"
#include "rkisp32-config.h"

namespace RkCam {

class Isp32Params : virtual public Isp3xParams {
 public:
    explicit Isp32Params() : Isp3xParams(){};
    virtual ~Isp32Params(){};

 protected:
    virtual bool convert3aResultsToIspCfg(SmartPtr<cam3aResult>& result, void* isp_cfg_p);
#if 0
    void fixedAwbOveflowToIsp32Params(void* isp_cfg_p, bool is_dual_isp);
#endif

 private:
    XCAM_DEAD_COPY(Isp32Params);
#if 0
    void convertAiqAwbToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                    const rk_aiq_isp_awb_meas_cfg_v32_t& awb_meas,
                                    bool awb_cfg_udpate);
    void convertAiqRawnrToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                      rk_aiq_isp_baynr_v32_t& rawnr);
    void convertAiqTnrToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                    rk_aiq_isp_tnr_v32_t& tnr);
    void convertAiqUvnrToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                     rk_aiq_isp_cnr_v32_t& uvnr);
    void convertAiqYnrToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                    rk_aiq_isp_ynr_v32_t& ynr);
    void convertAiqSharpenToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                        rk_aiq_isp_sharp_v32_t& sharp);
    void convertAiqDrcToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                    rk_aiq_isp_drc_v32_t& adrc_data);
    void convertAiqAfToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                   const rk_aiq_isp_af_meas_v32_t& af_data, bool af_cfg_udpate);
    void convertAiqMergeToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                      const rk_aiq_isp_merge_v32_t& amerge_data);
    void convertAiqAgammaToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                       const rk_aiq_isp_goc_v32_t& gamma_out_cfg);
#if RKAIQ_HAVE_CAC_V10
    void convertAiqCacToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                    struct isp32_isp_params_cfg& isp_cfg_right,
                                    const rk_aiq_isp_cac_v32_t& cac_cfg);
#endif
    void convertAiqAdehazeToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                        const rk_aiq_isp_dehaze_v32_t& dhaze);
    void convertAiqGainToIsp32Params(struct isp32_isp_params_cfg& isp_cfg,
                                     rk_aiq_isp_gain_v32_t& gain);
#endif
};

};  // namespace RkCam
#endif
