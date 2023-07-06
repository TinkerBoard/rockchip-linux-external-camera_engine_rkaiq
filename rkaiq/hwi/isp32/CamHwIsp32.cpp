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
#include "CamHwIsp32.h"

#ifdef ANDROID_OS
#include <cutils/properties.h>
#endif

namespace RkCam {

CamHwIsp32::CamHwIsp32() : CamHwIsp3x() { mVicapIspPhyLinkSupported = true; }

CamHwIsp32::~CamHwIsp32() {}

XCamReturn CamHwIsp32::init(const char* sns_ent_name) {
    XCamReturn ret = CamHwIsp3x::init(sns_ent_name);
    return ret;
}

XCamReturn CamHwIsp32::stop() {
    XCamReturn ret = CamHwIsp3x::stop();
    return ret;
}

void
CamHwIsp32::updateEffParams(void* params, void* ori_params)
{
#if defined(ISP_HW_V32) || defined(ISP_HW_V32_LITE)
    struct isp32_isp_params_cfg* isp_params = (struct isp32_isp_params_cfg*)params;
    uint32_t effFrmId = isp_params->frame_id;

    SmartLock locker(_isp_params_cfg_mutex);

    if (getParamsForEffMap(effFrmId)) {
        if (mAwbParams) {
            RkAiqIspAwbParamsProxyV32* awbParams =
                dynamic_cast<RkAiqIspAwbParamsProxyV32*>(mAwbParams);
            _effecting_ispparam_map[effFrmId]->data()->result.awb_cfg_v32 = awbParams->data()->result;
        }
        _effecting_ispparam_map[effFrmId]->data()->result.meas = mLatestMeasCfg;
        _effecting_ispparam_map[effFrmId]->data()->result.bls_cfg = mLatestBlsCfg;
        _effecting_ispparam_map[effFrmId]->data()->result.awb_gain_cfg = mLatestWbGainCfg;
    }
#endif
}

bool
CamHwIsp32::processTb(void* params)
{
#if defined(ISP_HW_V32) || defined(ISP_HW_V32_LITE)
    struct isp32_isp_params_cfg* isp_params = (struct isp32_isp_params_cfg*)params;
    if (mTbInfo.is_pre_aiq) {
        if (isp_params->frame_id == 0 && _not_skip_first) {
            _not_skip_first = false;
            _first_awb_cfg = isp_params->meas.rawawb;
            LOGE_ANALYZER("<TB> Skip config id(%d)'s isp params", isp_params->frame_id);
            return true;
        } else if (!_not_skip_first) {
            _first_awb_cfg.pre_wbgain_inv_r = isp_params->meas.rawawb.pre_wbgain_inv_r;
            _first_awb_cfg.pre_wbgain_inv_g = isp_params->meas.rawawb.pre_wbgain_inv_g;
            _first_awb_cfg.pre_wbgain_inv_b = isp_params->meas.rawawb.pre_wbgain_inv_b;
            isp_params->meas.rawawb = _first_awb_cfg;
        }
        LOGE_ANALYZER("<TB> Config id(%u)'s isp params, ens 0x%llx ens_up 0x%llx, cfg_up 0x%llx", isp_params->frame_id,
                      isp_params->module_ens,
                      isp_params->module_en_update,
                      isp_params->module_cfg_update);
        return false;
    } else if (isp_params->frame_id == 0) {
        return true;
    } else {
        return false;
    }
#else
    return false;
#endif
}

}  // namespace RkCam
