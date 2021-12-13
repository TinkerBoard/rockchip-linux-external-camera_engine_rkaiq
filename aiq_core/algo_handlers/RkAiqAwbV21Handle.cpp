/*
 * Copyright (c) 2019-2021 Rockchip Eletronics Co., Ltd.
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
#include "RkAiqCore.h"
#include "RkAiqHandle.h"
#include "RkAiqHandleInt.h"
#include "RkAiqHandleIntV21.h"

namespace RkCam {

XCamReturn RkAiqAwbV21HandleInt::updateConfig(bool needSync) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (needSync) mCfgMutex.lock();
    // if something changed
    if (updateAtt) {
        mCurAtt   = mNewAtt;
        updateAtt = false;
        rk_aiq_uapi_awb_SetAttrib(mAlgoCtx, mCurAtt, false);
        sendSignal();
    }
    if (updateWbV21Attr) {
        mCurWbV21Attr   = mNewWbV21Attr;
        updateWbV21Attr = false;
        rk_aiq_uapiV2_awbV21_SetAttrib(mAlgoCtx, mCurWbV21Attr, false);
        sendSignal();
    }
    if (updateWbOpModeAttr) {
        mCurWbOpModeAttr   = mNewWbOpModeAttr;
        updateWbOpModeAttr = false;
        rk_aiq_uapiV2_awb_SetMwbMode(mAlgoCtx, mCurWbOpModeAttr, false);
        sendSignal();
    }
    if (updateWbMwbAttr) {
        mCurWbMwbAttr   = mNewWbMwbAttr;
        updateWbMwbAttr = false;
        rk_aiq_uapiV2_awb_SetMwbAttrib(mAlgoCtx, mCurWbMwbAttr, false);
        sendSignal();
    }
    if (updateWbAwbAttr) {
        mCurWbAwbAttr   = mNewWbAwbAttr;
        updateWbAwbAttr = false;
        rk_aiq_uapiV2_awbV20_SetAwbAttrib(mAlgoCtx, mCurWbAwbAttr, false);
        sendSignal();
    }
    if (updateWbAwbWbGainAdjustAttr) {
        mCurWbAwbWbGainAdjustAttr   = mNewWbAwbWbGainAdjustAttr;
        updateWbAwbWbGainAdjustAttr = false;
        rk_aiq_uapiV2_awb_SetAwbGainAdjust(mAlgoCtx, mCurWbAwbWbGainAdjustAttr, false);
        sendSignal();
    }
    if (updateWbAwbWbGainOffsetAttr) {
        mCurWbAwbWbGainOffsetAttr   = mNewWbAwbWbGainOffsetAttr;
        updateWbAwbWbGainOffsetAttr = false;
        rk_aiq_uapiV2_awb_SetAwbGainOffset(mAlgoCtx, mCurWbAwbWbGainOffsetAttr, false);
        sendSignal();
    }
    if (updateWbAwbMultiWindowAttr) {
        mCurWbAwbMultiWindowAttr   = mNewWbAwbMultiWindowAttr;
        updateWbAwbMultiWindowAttr = false;
        rk_aiq_uapiV2_awb_SetAwbMultiwindow(mAlgoCtx, mCurWbAwbMultiWindowAttr, false);
        sendSignal();
    }
    if (needSync) mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAwbV21HandleInt::setWbV21Attrib(rk_aiq_uapiV2_wbV21_attrib_t att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    mCfgMutex.lock();
    // TODO
    // check if there is different between att & mCurAtt
    // if something changed, set att to mNewAtt, and
    // the new params will be effective later when updateConfig
    // called by RkAiqCore

    // if something changed
    if (0 != memcmp(&mCurWbV21Attr, &att, sizeof(rk_aiq_uapiV2_wbV21_attrib_t))) {
        mNewWbV21Attr   = att;
        updateWbV21Attr = true;
        waitSignal();
    }

    mCfgMutex.unlock();

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

XCamReturn RkAiqAwbV21HandleInt::getWbV21Attrib(rk_aiq_uapiV2_wbV21_attrib_t* att) {
    ENTER_ANALYZER_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_uapiV2_awbV21_GetAttrib(mAlgoCtx, att);

    EXIT_ANALYZER_FUNCTION();
    return ret;
}

};  // namespace RkCam
