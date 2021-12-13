/*
 * rkisp_aiq_core.h
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

#ifndef _RK_AIQ_HANDLE_H_
#define _RK_AIQ_HANDLE_H_

#include "rk_aiq_algo_types.h"
#include "rk_aiq_types.h"
#include "xcam_mutex.h"
#include "rk_aiq_pool.h"

namespace RkCam {

class RkAiqCore;
struct RkAiqAlgosGroupShared_s;

class RkAiqHandle {
 public:
    explicit RkAiqHandle(RkAiqAlgoDesComm* des, RkAiqCore* aiqCore);
    virtual ~RkAiqHandle();
    void setEnable(bool enable) { mEnable = enable; };
    void setReConfig(bool reconfig) { mReConfig = reconfig; };
    bool getEnable() { return mEnable; };
    virtual XCamReturn prepare();
    virtual XCamReturn preProcess();
    virtual XCamReturn processing();
    virtual XCamReturn postProcess();
    virtual XCamReturn genIspResult(RkAiqFullParams* params, RkAiqFullParams* cur_params) { return XCAM_RETURN_NO_ERROR; };
    RkAiqAlgoContext* getAlgoCtx() { return mAlgoCtx; }
    int getAlgoId() { return mDes->id; }
    int getAlgoType() { return mDes->type; }
    void setGroupId(int32_t gId) {
        mGroupId = gId;
    }
    int32_t getGroupId() {
       return mGroupId;
    }
    void setGroupShared(void* grp_shared) {
        mAlogsGroupSharedParams = grp_shared;
    }
    void* getGroupShared() {
       return mAlogsGroupSharedParams;
    }
    virtual XCamReturn updateConfig(bool needSync) { return XCAM_RETURN_NO_ERROR; };

 protected:
    virtual void init() = 0;
    virtual void deInit();
    void waitSignal();
    void sendSignal();
    enum {
        RKAIQ_CONFIG_COM_PREPARE,
        RKAIQ_CONFIG_COM_PRE,
        RKAIQ_CONFIG_COM_PROC,
        RKAIQ_CONFIG_COM_POST,
    };
    virtual XCamReturn configInparamsCom(RkAiqAlgoCom* com, int type);
    RkAiqAlgoCom* mConfig;
    RkAiqAlgoCom* mPreInParam;
    RkAiqAlgoResCom* mPreOutParam;
    RkAiqAlgoCom* mProcInParam;
    RkAiqAlgoResCom* mProcOutParam;
    RkAiqAlgoCom* mPostInParam;
    RkAiqAlgoResCom* mPostOutParam;
    RkAiqAlgoDesComm* mDes;
    RkAiqAlgoContext* mAlgoCtx;
    RkAiqCore* mAiqCore;
    bool mEnable;
    bool mReConfig;
    uint32_t mGroupId;
    void* mAlogsGroupSharedParams;
    XCam::Mutex mCfgMutex;
    bool updateAtt;
    XCam::Cond mUpdateCond;
};

};  // namespace RkCam

#endif
