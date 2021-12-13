/*
 * RkAiqCoreV3x.h
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

#ifndef _RK_AIQ_CORE_V3x_H_
#define _RK_AIQ_CORE_V3x_H_

#include "RkAiqCoreV21.h"

using namespace XCam;
namespace RkCam {

class RkAiqCoreV3x
    : public RkAiqCoreV21 {
public:
    RkAiqCoreV3x();
    virtual ~RkAiqCoreV3x();
protected:
    virtual XCamReturn prepare(const rk_aiq_exposure_sensor_descriptor* sensor_des, int mode);
    SmartPtr<RkAiqHandle> newAlgoHandle(RkAiqAlgoDesComm* algo, int hw_ver);
    void copyIspStats(SmartPtr<RkAiqAecStatsProxy>& aecStat,
                      SmartPtr<RkAiqAwbStatsProxy>& awbStat,
                      SmartPtr<RkAiqAfStatsProxy>& afStat,
                      rk_aiq_isp_stats_t* to);
    void newAiqParamsPool();
    XCamReturn getAiqParamsBuffer(RkAiqFullParams* aiqParams, enum rk_aiq_core_analyze_type_e type);

protected:
    // TODO: change full params to list
    // V3x differential modules
    SmartPtr<RkAiqIspAwbParamsPoolV3x>         mAiqIspAwbV3xParamsPool;
    SmartPtr<RkAiqIspAfParamsPoolV3x>          mAiqIspAfV3xParamsPool;
    SmartPtr<RkAiqIspCacParamsPoolV3x>         mAiqIspCacV3xParamsPool;
    SmartPtr<RkAiqIspGainParamsPoolV3x>        mAiqIspGainV3xParamsPool;
    SmartPtr<RkAiqIspBaynrParamsPoolV3x>       mAiqIspBaynrV3xParamsPool;
    SmartPtr<RkAiqIspBa3dParamsPoolV3x>        mAiqIspBa3dV3xParamsPool;
    SmartPtr<RkAiqIspYnrParamsPoolV3x>         mAiqIspYnrV3xParamsPool;
    SmartPtr<RkAiqIspCnrParamsPoolV3x>         mAiqIspCnrV3xParamsPool;
    SmartPtr<RkAiqIspSharpenParamsPoolV3x>     mAiqIspSharpenV3xParamsPool;
    SmartPtr<RkAiqIspTnrParamsPoolV3x>         mAiqIspTnrV3xParamsPool;
private:
};

};

#endif //_RK_AIQ_CORE_V21_H_
