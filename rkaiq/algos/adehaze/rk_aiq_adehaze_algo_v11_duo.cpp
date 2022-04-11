/*
 * rk_aiq_adehaze_algo_v10.cpp
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
#include "rk_aiq_adehaze_algo_v11_duo.h"
#include <string.h>
#include "xcam_log.h"
#include "mathlib.h"

float LinearInterpV11Duo(const float* pX, const float* pY, float posx, int XSize) {
    int index;
    float yOut = 0;

    if (posx >= pX[XSize - 1]) {
        yOut = pY[XSize - 1];
    } else if (posx <= pX[0]) {
        yOut = pY[0];
    } else {
        index = 0;
        while ((posx >= pX[index]) && (index < XSize)) {
            index++;
        }
        index -= 1;
        yOut = ((pY[index + 1] - pY[index]) / (pX[index + 1] - pX[index]) * (posx - pX[index])) +
               pY[index];
    }

    return yOut;
}

int DehazeLinearInterpV11Duo(const float* pX, const float* pY, float posx, int BitInt, int BitFlaot,
                             int XSize) {
    int index;
    float yOut     = 0.0;
    int yOutInt    = 0;
    int yOutIntMax = (int)(pow(2, (BitFlaot + BitInt)) - 1);
    int yOutIntMin = 0;

    if (posx >= pX[XSize - 1]) {
        yOut = pY[XSize - 1];
    } else if (posx <= pX[0]) {
        yOut = pY[0];
    } else {
        index = 0;
        while ((posx >= pX[index]) && (index < XSize)) {
            index++;
        }
        index -= 1;
        yOut = ((pY[index + 1] - pY[index]) / (pX[index + 1] - pX[index]) * (posx - pX[index])) +
               pY[index];
    }

    yOutInt = LIMIT_VALUE((int)(yOut * pow(2, BitFlaot)), yOutIntMax, yOutIntMin);

    return yOutInt;
}

int LinearInterpEnableV11Duo(const float* pX, const unsigned char* pY, float posx, int XSize) {
    int index;
    float out;
    int yOut = 0;
    if (posx >= pX[XSize - 1]) {
        out = (float)pY[XSize - 1];
    } else if (posx <= pX[0]) {
        out = pY[0];
    } else {
        index = 0;
        while ((posx >= pX[index]) && (index < XSize)) {
            index++;
        }
        index -= 1;
        out = ((pY[index + 1] - pY[index]) / (pX[index + 1] - pX[index]) * (posx - pX[index])) +
              pY[index];
    }
    yOut = out > 0.5 ? FUNCTION_ENABLE : FUNCTION_DISABLE;

    return yOut;
}

void EnableSettingV11duo(CalibDbDehazeV11_t* pCalibV11Duo, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.enable = pCalibV11Duo->Enable;

    if (pCalibV11Duo->Enable) {
        if (pCalibV11Duo->dehaze_setting.en && pCalibV11Duo->enhance_setting.en) {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_ENABLE;
        } else if (pCalibV11Duo->dehaze_setting.en && !pCalibV11Duo->enhance_setting.en) {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_DISABLE;
        } else if (!pCalibV11Duo->dehaze_setting.en && pCalibV11Duo->enhance_setting.en) {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_ENABLE;
        } else {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_DISABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_DISABLE;
        }

        if (pCalibV11Duo->hist_setting.en)
            pProcRes->ProcResV11duo.hist_en = FUNCTION_ENABLE;
        else
            pProcRes->ProcResV11duo.hist_en = FUNCTION_DISABLE;
    } else {
        pProcRes->ProcResV11duo.dc_en      = FUNCTION_DISABLE;
        pProcRes->ProcResV11duo.enhance_en = FUNCTION_DISABLE;
        pProcRes->ProcResV11duo.hist_en    = FUNCTION_DISABLE;
    }

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV11duo.enable,
                 (pProcRes->ProcResV11duo.dc_en & FUNCTION_ENABLE) &&
                     (!(pProcRes->ProcResV11duo.enhance_en & FUNCTION_ENABLE)),
                 (pProcRes->ProcResV11duo.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV11duo.enhance_en & FUNCTION_ENABLE),
                 pProcRes->ProcResV11duo.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

int ClipValueV11Duo(float posx, int BitInt, int BitFloat) {
    int yOutInt    = 0;
    int yOutIntMax = (int)(pow(2, (BitFloat + BitInt)) - 1);
    int yOutIntMin = 0;

    yOutInt = LIMIT_VALUE((int)(posx * pow(2, BitFloat)), yOutIntMax, yOutIntMin);

    return yOutInt;
}

void stManuEnableSettingV11duo(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.enable = pStManu->Enable;

    if (pStManu->Enable) {
        if (pStManu->dehaze_setting.en && pStManu->enhance_setting.en) {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_ENABLE;
        } else if (pStManu->dehaze_setting.en && !pStManu->enhance_setting.en) {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_DISABLE;
        } else if (!pStManu->dehaze_setting.en && pStManu->enhance_setting.en) {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_ENABLE;
        } else {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_DISABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_DISABLE;
        }

        if (pStManu->hist_setting.en)
            pProcRes->ProcResV11duo.hist_en = FUNCTION_ENABLE;
        else
            pProcRes->ProcResV11duo.hist_en = FUNCTION_DISABLE;
    } else {
        pProcRes->ProcResV11duo.dc_en      = FUNCTION_DISABLE;
        pProcRes->ProcResV11duo.enhance_en = FUNCTION_DISABLE;
        pProcRes->ProcResV11duo.hist_en    = FUNCTION_DISABLE;
    }

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV11duo.enable,
                 (pProcRes->ProcResV11duo.dc_en & FUNCTION_ENABLE) &&
                     (!(pProcRes->ProcResV11duo.enhance_en & FUNCTION_ENABLE)),
                 (pProcRes->ProcResV11duo.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV11duo.enhance_en & FUNCTION_ENABLE),
                 pProcRes->ProcResV11duo.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetDehazeParamsV11duo(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes,
                                 int rawWidth, int rawHeight) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.air_lc_en =
        pStManu->dehaze_setting.air_lc_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    pProcRes->ProcResV11duo.dc_min_th =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.dc_min_th, 8, 0);
    pProcRes->ProcResV11duo.dc_max_th =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.dc_max_th, 8, 0);
    pProcRes->ProcResV11duo.yhist_th =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.yhist_th, 8, 0);
    pProcRes->ProcResV11duo.yblk_th = int(pStManu->dehaze_setting.DehazeData.yblk_th *
                                          ((rawWidth + 15) / 16) * ((rawHeight + 15) / 16));
    pProcRes->ProcResV11duo.dark_th =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.dark_th, 8, 0);
    pProcRes->ProcResV11duo.bright_min =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.bright_min, 8, 0);
    pProcRes->ProcResV11duo.bright_max =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.bright_max, 8, 0);
    pProcRes->ProcResV11duo.wt_max =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.wt_max, 0, 8);
    pProcRes->ProcResV11duo.air_min =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.air_min, 8, 0);
    pProcRes->ProcResV11duo.air_max =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.air_max, 8, 0);
    pProcRes->ProcResV11duo.tmax_base =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.tmax_base, 8, 0);
    pProcRes->ProcResV11duo.tmax_off =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.tmax_off, 0, 10);
    pProcRes->ProcResV11duo.tmax_max =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.tmax_max, 0, 10);
    pProcRes->ProcResV11duo.cfg_wt =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.cfg_wt, 0, 8);
    pProcRes->ProcResV11duo.cfg_air =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.cfg_air, 8, 0);
    pProcRes->ProcResV11duo.cfg_tmax =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.cfg_tmax, 0, 10);
    pProcRes->ProcResV11duo.range_sima =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.range_sigma, 0, 9);
    pProcRes->ProcResV11duo.space_sigma_cur =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.space_sigma_cur, 0, 8);
    pProcRes->ProcResV11duo.space_sigma_pre =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.space_sigma_pre, 0, 8);
    pProcRes->ProcResV11duo.bf_weight =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.bf_weight, 0, 8);
    pProcRes->ProcResV11duo.dc_weitcur =
        ClipValueV11Duo(pStManu->dehaze_setting.DehazeData.dc_weitcur, 0, 8);
    pProcRes->ProcResV11duo.stab_fnum    = ClipValueV11Duo(pStManu->dehaze_setting.stab_fnum, 5, 0);
    pProcRes->ProcResV11duo.iir_sigma    = ClipValueV11Duo(pStManu->dehaze_setting.sigma, 8, 0);
    pProcRes->ProcResV11duo.iir_wt_sigma = ClipValueV11Duo(pStManu->dehaze_setting.wt_sigma, 8, 3);
    pProcRes->ProcResV11duo.iir_air_sigma =
        ClipValueV11Duo(pStManu->dehaze_setting.air_sigma, 8, 0);
    pProcRes->ProcResV11duo.iir_tmax_sigma =
        ClipValueV11Duo(pStManu->dehaze_setting.tmax_sigma, 0, 10);
    pProcRes->ProcResV11duo.iir_pre_wet = ClipValueV11Duo(pStManu->dehaze_setting.pre_wet, 0, 4);
    pProcRes->ProcResV11duo.gaus_h0     = DEHAZE_GAUS_H4;
    pProcRes->ProcResV11duo.gaus_h1     = DEHAZE_GAUS_H1;
    pProcRes->ProcResV11duo.gaus_h2     = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV11duo.dc_en && !(pProcRes->ProcResV11duo.enhance_en)) {
        if (pProcRes->ProcResV11duo.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:1 cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__,
                         pProcRes->ProcResV11duo.cfg_air / 1.0f,
                         pProcRes->ProcResV11duo.cfg_tmax / 1023.0f,
                         pProcRes->ProcResV11duo.cfg_wt / 255.0f);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x255 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n",
                         __func__, pProcRes->ProcResV11duo.cfg_air,
                         pProcRes->ProcResV11duo.cfg_tmax, pProcRes->ProcResV11duo.cfg_wt);
        } else if (pProcRes->ProcResV11duo.cfg_alpha == 0) {
            LOGD_ADEHAZE(
                "%s cfg_alpha:0 air_max:%f air_min:%f tmax_base:%f wt_max:%f\n", __func__,
                pProcRes->ProcResV11duo.air_max / 1.0f, pProcRes->ProcResV11duo.air_min / 1.0f,
                pProcRes->ProcResV11duo.tmax_base / 1.0f, pProcRes->ProcResV11duo.wt_max / 255.0f);
            LOGD_ADEHAZE(
                "%s cfg_alpha_reg:0x0 air_max:0x%x air_min:0x%x tmax_base:0x%x wt_max:0x%x\n",
                __func__, pProcRes->ProcResV11duo.air_max, pProcRes->ProcResV11duo.air_min,
                pProcRes->ProcResV11duo.tmax_base, pProcRes->ProcResV11duo.wt_max);
        }
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetEnhanceParamsV11duo(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.enhance_value =
        ClipValueV11Duo(pStManu->enhance_setting.EnhanceData.enhance_value, 4, 10);
    pProcRes->ProcResV11duo.enhance_chroma =
        ClipValueV11Duo(pStManu->enhance_setting.EnhanceData.enhance_chroma, 4, 10);

    for (int i = 0; i < DHAZ_V11_ENHANCE_CRUVE_NUM; i++)
        pProcRes->ProcResV11duo.enh_curve[i] = (int)(pStManu->enhance_setting.enhance_curve[i]);

    if (pProcRes->ProcResV11duo.dc_en && pProcRes->ProcResV11duo.enhance_en) {
        LOGD_ADEHAZE("%s enhance_value:%f enhance_chroma:%f\n", __func__,
                     pStManu->enhance_setting.EnhanceData.enhance_value / 1024.0f,
                     pStManu->enhance_setting.EnhanceData.enhance_chroma / 1024.0f);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV11duo.enhance_value, pProcRes->ProcResV11duo.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetHistParamsV11duo(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.hpara_en =
        pStManu->hist_setting.hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    // clip hpara_en
    pProcRes->ProcResV11duo.hpara_en =
        pProcRes->ProcResV11duo.dc_en ? pProcRes->ProcResV11duo.hpara_en : FUNCTION_ENABLE;

    pProcRes->ProcResV11duo.hist_gratio =
        ClipValueV11Duo(pStManu->hist_setting.HistData.hist_gratio, 0, 8);
    pProcRes->ProcResV11duo.hist_th_off =
        ClipValueV11Duo(pStManu->hist_setting.HistData.hist_th_off, 8, 0);
    pProcRes->ProcResV11duo.hist_k = ClipValueV11Duo(pStManu->hist_setting.HistData.hist_k, 3, 2);
    pProcRes->ProcResV11duo.hist_min =
        ClipValueV11Duo(pStManu->hist_setting.HistData.hist_min, 1, 8);
    pProcRes->ProcResV11duo.cfg_gratio =
        ClipValueV11Duo(pStManu->hist_setting.HistData.cfg_gratio, 5, 8);
    pProcRes->ProcResV11duo.hist_scale =
        ClipValueV11Duo(pStManu->hist_setting.HistData.hist_scale, 5, 8);

    if (pProcRes->ProcResV11duo.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f "
            "hist_min:%f hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV11duo.cfg_alpha / 255.0f, pProcRes->ProcResV11duo.hpara_en,
            pProcRes->ProcResV11duo.hist_gratio / 255.0f,
            pProcRes->ProcResV11duo.hist_th_off / 1.0f, pProcRes->ProcResV11duo.hist_k / 4.0f,
            pProcRes->ProcResV11duo.hist_min / 256.0f, pProcRes->ProcResV11duo.hist_scale / 256.0f,
            pProcRes->ProcResV11duo.cfg_gratio / 256.0f);
        LOGD_ADEHAZE(
            "%s cfg_alpha_reg:0x%x hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x "
            "hist_min_reg:0x%x hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n",
            __func__, pProcRes->ProcResV11duo.cfg_alpha, pProcRes->ProcResV11duo.hist_gratio,
            pProcRes->ProcResV11duo.hist_th_off, pProcRes->ProcResV11duo.hist_k,
            pProcRes->ProcResV11duo.hist_min, pProcRes->ProcResV11duo.hist_scale,
            pProcRes->ProcResV11duo.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeParamsV11duo(CalibDbDehazeV11_t* pCalibV11Duo, RkAiqAdehazeProcResult_t* pProcRes,
                           int rawWidth, int rawHeight, float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.air_lc_en =
        pCalibV11Duo->dehaze_setting.air_lc_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    pProcRes->ProcResV11duo.dc_min_th =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.dc_min_th, CtrlValue, 8, 0,
                                 DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.dc_max_th =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.dc_max_th, CtrlValue, 8, 0,
                                 DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.yhist_th = DehazeLinearInterpV11Duo(
        pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
        pCalibV11Duo->dehaze_setting.DehazeData.yhist_th, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.yblk_th =
        LinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                           pCalibV11Duo->dehaze_setting.DehazeData.yblk_th, CtrlValue,
                           DHAZ_CTRL_DATA_STEP_MAX) *
        ((rawWidth + 15) / 16) * ((rawHeight + 15) / 16);
    pProcRes->ProcResV11duo.dark_th = DehazeLinearInterpV11Duo(
        pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
        pCalibV11Duo->dehaze_setting.DehazeData.dark_th, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.bright_min =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.bright_min, CtrlValue, 8,
                                 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.bright_max =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.bright_max, CtrlValue, 8,
                                 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.wt_max = DehazeLinearInterpV11Duo(
        pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
        pCalibV11Duo->dehaze_setting.DehazeData.wt_max, CtrlValue, 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.air_min = DehazeLinearInterpV11Duo(
        pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
        pCalibV11Duo->dehaze_setting.DehazeData.air_min, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.air_max = DehazeLinearInterpV11Duo(
        pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
        pCalibV11Duo->dehaze_setting.DehazeData.air_max, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.tmax_base =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.tmax_base, CtrlValue, 8, 0,
                                 DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.tmax_off =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.tmax_off, CtrlValue, 0, 10,
                                 DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.tmax_max =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.tmax_max, CtrlValue, 0, 10,
                                 DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.cfg_wt = DehazeLinearInterpV11Duo(
        pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
        pCalibV11Duo->dehaze_setting.DehazeData.cfg_wt, CtrlValue, 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.cfg_air = DehazeLinearInterpV11Duo(
        pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
        pCalibV11Duo->dehaze_setting.DehazeData.cfg_air, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.cfg_tmax =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.cfg_tmax, CtrlValue, 0, 10,
                                 DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.range_sima =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.range_sigma, CtrlValue, 0,
                                 9, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.space_sigma_cur =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.space_sigma_cur, CtrlValue,
                                 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.space_sigma_pre =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.space_sigma_pre, CtrlValue,
                                 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.bf_weight =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.bf_weight, CtrlValue, 0, 8,
                                 DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.dc_weitcur =
        DehazeLinearInterpV11Duo(pCalibV11Duo->dehaze_setting.DehazeData.CtrlData,
                                 pCalibV11Duo->dehaze_setting.DehazeData.dc_weitcur, CtrlValue, 0,
                                 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.stab_fnum =
        ClipValueV11Duo(pCalibV11Duo->dehaze_setting.stab_fnum, 5, 0);
    pProcRes->ProcResV11duo.iir_sigma = ClipValueV11Duo(pCalibV11Duo->dehaze_setting.sigma, 8, 0);
    pProcRes->ProcResV11duo.iir_wt_sigma =
        ClipValueV11Duo(pCalibV11Duo->dehaze_setting.wt_sigma, 8, 3);
    pProcRes->ProcResV11duo.iir_air_sigma =
        ClipValueV11Duo(pCalibV11Duo->dehaze_setting.air_sigma, 8, 0);
    pProcRes->ProcResV11duo.iir_tmax_sigma =
        ClipValueV11Duo(pCalibV11Duo->dehaze_setting.tmax_sigma, 0, 10);
    pProcRes->ProcResV11duo.iir_pre_wet =
        ClipValueV11Duo(pCalibV11Duo->dehaze_setting.pre_wet, 0, 4);
    pProcRes->ProcResV11duo.gaus_h0 = DEHAZE_GAUS_H4;
    pProcRes->ProcResV11duo.gaus_h1 = DEHAZE_GAUS_H1;
    pProcRes->ProcResV11duo.gaus_h2 = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV11duo.dc_en && !(pProcRes->ProcResV11duo.enhance_en)) {
        if (pProcRes->ProcResV11duo.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:1 CtrlValue:%f cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__,
                         CtrlValue, pProcRes->ProcResV11duo.cfg_air / 1.0f,
                         pProcRes->ProcResV11duo.cfg_tmax / 1023.0f,
                         pProcRes->ProcResV11duo.cfg_wt / 255.0f);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x255 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n",
                         __func__, pProcRes->ProcResV11duo.cfg_air,
                         pProcRes->ProcResV11duo.cfg_tmax, pProcRes->ProcResV11duo.cfg_wt);
        } else if (pProcRes->ProcResV11duo.cfg_alpha == 0) {
            LOGD_ADEHAZE(
                "%s cfg_alpha:0 CtrlValue:%f air_max:%f air_min:%f tmax_base:%f wt_max:%f\n",
                __func__, CtrlValue, pProcRes->ProcResV11duo.air_max / 1.0f,
                pProcRes->ProcResV11duo.air_min / 1.0f, pProcRes->ProcResV11duo.tmax_base / 1.0f,
                pProcRes->ProcResV11duo.wt_max / 255.0f);
            LOGD_ADEHAZE(
                "%s cfg_alpha_reg:0x0 air_max:0x%x air_min:0x%x tmax_base:0x%x wt_max:0x%x\n",
                __func__, pProcRes->ProcResV11duo.air_max, pProcRes->ProcResV11duo.air_min,
                pProcRes->ProcResV11duo.tmax_base, pProcRes->ProcResV11duo.wt_max);
        }
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetEnhanceParamsV11duo(CalibDbDehazeV11_t* pCalibV11Duo, RkAiqAdehazeProcResult_t* pProcRes,
                            float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.enhance_value =
        DehazeLinearInterpV11Duo(pCalibV11Duo->enhance_setting.EnhanceData.CtrlData,
                                 pCalibV11Duo->enhance_setting.EnhanceData.enhance_value, CtrlValue,
                                 4, 10, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.enhance_chroma =
        DehazeLinearInterpV11Duo(pCalibV11Duo->enhance_setting.EnhanceData.CtrlData,
                                 pCalibV11Duo->enhance_setting.EnhanceData.enhance_chroma,
                                 CtrlValue, 4, 10, DHAZ_CTRL_DATA_STEP_MAX);

    for (int i = 0; i < DHAZ_V11_ENHANCE_CRUVE_NUM; i++)
        pProcRes->ProcResV11duo.enh_curve[i] =
            (int)(pCalibV11Duo->enhance_setting.enhance_curve[i]);

    if (pProcRes->ProcResV11duo.dc_en && pProcRes->ProcResV11duo.enhance_en) {
        LOGD_ADEHAZE("%s CtrlValue:%f enhance_value:%f enhance_chroma:%f\n", __func__, CtrlValue,
                     pProcRes->ProcResV11duo.enhance_value / 1024.0f,
                     pProcRes->ProcResV11duo.enhance_chroma / 1024.0f);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV11duo.enhance_value, pProcRes->ProcResV11duo.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetHistParamsV11duo(CalibDbDehazeV11_t* pCalibV11Duo, RkAiqAdehazeProcResult_t* pProcRes,
                         float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.hpara_en =
        pCalibV11Duo->hist_setting.hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    // clip hpara_en
    pProcRes->ProcResV11duo.hpara_en = pProcRes->ProcResV11duo.dc_en
                                           ? pProcRes->ProcResV11duo.hpara_en
                                           : FUNCTION_ENABLE;  //  dc en 关闭，hpara必需开

    pProcRes->ProcResV11duo.hist_gratio = DehazeLinearInterpV11Duo(
        pCalibV11Duo->hist_setting.HistData.CtrlData,
        pCalibV11Duo->hist_setting.HistData.hist_gratio, CtrlValue, 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.hist_th_off = DehazeLinearInterpV11Duo(
        pCalibV11Duo->hist_setting.HistData.CtrlData,
        pCalibV11Duo->hist_setting.HistData.hist_th_off, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.hist_k = DehazeLinearInterpV11Duo(
        pCalibV11Duo->hist_setting.HistData.CtrlData, pCalibV11Duo->hist_setting.HistData.hist_k,
        CtrlValue, 3, 2, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.hist_min = DehazeLinearInterpV11Duo(
        pCalibV11Duo->hist_setting.HistData.CtrlData, pCalibV11Duo->hist_setting.HistData.hist_min,
        CtrlValue, 1, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.cfg_gratio = DehazeLinearInterpV11Duo(
        pCalibV11Duo->hist_setting.HistData.CtrlData,
        pCalibV11Duo->hist_setting.HistData.cfg_gratio, CtrlValue, 5, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11duo.hist_scale = DehazeLinearInterpV11Duo(
        pCalibV11Duo->hist_setting.HistData.CtrlData,
        pCalibV11Duo->hist_setting.HistData.hist_scale, CtrlValue, 5, 8, DHAZ_CTRL_DATA_STEP_MAX);

    if (pProcRes->ProcResV11duo.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f CtrlValue:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f "
            "hist_min:%f hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV11duo.cfg_alpha / 255.0f, CtrlValue,
            pProcRes->ProcResV11duo.hpara_en, pProcRes->ProcResV11duo.hist_gratio / 255.0f,
            pProcRes->ProcResV11duo.hist_th_off / 1.0f, pProcRes->ProcResV11duo.hist_k / 4.0f,
            pProcRes->ProcResV11duo.hist_min / 256.0f, pProcRes->ProcResV11duo.hist_scale / 256.0f,
            pProcRes->ProcResV11duo.cfg_gratio / 256.0f);
        LOGD_ADEHAZE(
            "%s cfg_alpha_reg:0x%x hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x "
            "hist_min_reg:0x%x hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n",
            __func__, pProcRes->ProcResV11duo.cfg_alpha, pProcRes->ProcResV11duo.hist_gratio,
            pProcRes->ProcResV11duo.hist_th_off, pProcRes->ProcResV11duo.hist_k,
            pProcRes->ProcResV11duo.hist_min, pProcRes->ProcResV11duo.hist_scale,
            pProcRes->ProcResV11duo.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeHistDuoISPSettingV11(RkAiqAdehazeProcResult_t* pProcRes,
                                   rkisp_adehaze_stats_t* pStats, bool DuoCamera, int FrameID) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    // round_en
    pProcRes->ProcResV11duo.round_en = FUNCTION_ENABLE;

    // deahze duo setting
    if (DuoCamera) {
        pProcRes->ProcResV11duo.soft_wr_en = FUNCTION_ENABLE;
#if 1
        // support default value for kernel calc
        for (int i = 0; i < DHAZ_V11_HIST_WR_NUM; i++) {
            pProcRes->ProcResV11duo.hist_wr[i] = 16 * (i + 1);
            pProcRes->ProcResV11duo.hist_wr[i] = pProcRes->ProcResV11duo.hist_wr[i] > 1023
                                                     ? 1023
                                                     : pProcRes->ProcResV11duo.hist_wr[i];
        }
#else
        pProcRes->ProcResV11duo.adp_air_wr    = pStats->dehaze_stats_v11_duo.dhaz_adp_air_base;
        pProcRes->ProcResV11duo.adp_gratio_wr = pStats->dehaze_stats_v11_duo.dhaz_adp_gratio;
        pProcRes->ProcResV11duo.adp_tmax_wr   = pStats->dehaze_stats_v11_duo.dhaz_adp_tmax;
        pProcRes->ProcResV11duo.adp_wt_wr     = pStats->dehaze_stats_v11_duo.dhaz_adp_wt;

        static int hist_wr[64];
        if (!FrameID)
            for (int i = 0; i < 64; i++) {
                hist_wr[i]                         = 16 * (i + 1);
                hist_wr[i]                         = hist_wr[i] > 1023 ? 1023 : hist_wr[i];
                pProcRes->ProcResV11duo.hist_wr[i] = hist_wr[i];
            }
        else {
            int num = MIN(FrameID + 1, pProcRes->ProcResV11duo.stab_fnum);
            int tmp = 0;
            for (int i = 0; i < 64; i++) {
                tmp = (hist_wr[i] * (num - 1) + pStats->dehaze_stats_v11_duo.h_rgb_iir[i]) / num;
                pProcRes->ProcResV11duo.hist_wr[i] = tmp;
                hist_wr[i]                         = tmp;
            }
        }

        LOGD_ADEHAZE("%s adp_air_wr:0x%x adp_gratio_wr:0x%x adp_tmax_wr:0x%x adp_wt_wr:0x%x\n",
                     __func__, pProcRes->ProcResV11duo.adp_air_wr,
                     pProcRes->ProcResV11duo.adp_gratio_wr, pProcRes->ProcResV11duo.adp_tmax_wr,
                     pProcRes->ProcResV11duo.adp_wt_wr);

        LOGV_ADEHAZE("%s hist_wr:0x%x", __func__, pProcRes->ProcResV11duo.hist_wr[0]);
        for (int i = 1; i < 63; i++) LOGV_ADEHAZE(" 0x%x", pProcRes->ProcResV11duo.hist_wr[i]);
        LOGV_ADEHAZE(" 0x%x\n", pProcRes->ProcResV11duo.hist_wr[63]);
#endif
        LOGD_ADEHAZE("%s DuoCamera:%d soft_wr_en:%d\n", __func__, DuoCamera,
                     pProcRes->ProcResV11duo.soft_wr_en);
    } else
        pProcRes->ProcResV11duo.soft_wr_en = FUNCTION_DISABLE;

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

XCamReturn GetDehazeLocalGainSettingV11(RkAiqAdehazeProcResult_t* pProcRes,
                                        CalibDbV2_YnrV3_CalibPara_t* pYnrCalib, float ISO,
                                        YnrSnrMode_t SnrMode) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (pYnrCalib->Setting_len >= 1 && SnrMode <= pYnrCalib->Setting_len) {
        if (pYnrCalib->Setting[SnrMode].Calib_ISO_len >= 1) {
            // get iso knots and ratio
            float ISO_lo    = 50.0f;
            float ISO_hi    = 50.0f;
            float ratio     = 1.0f;
            int ISO_knot_lo = 0;
            int ISO_knot_hi = 0;
            for (int i = 0; i < pYnrCalib->Setting[SnrMode].Calib_ISO_len - 1; i++) {
                if (ISO >= pYnrCalib->Setting[SnrMode].Calib_ISO[i].iso &&
                    ISO <= pYnrCalib->Setting[SnrMode].Calib_ISO[i + 1].iso) {
                    ISO_knot_lo = i;
                    ISO_knot_hi = i + 1;
                    ISO_lo      = pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_lo].iso;
                    ISO_hi      = pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_hi].iso;

                    if ((ISO_hi - ISO_lo) != 0)
                        ratio = (ISO - ISO_lo) / (ISO_hi - ISO_lo);
                    else
                        LOGE_ADEHAZE("Dehaze zero in %s(%d) \n", __func__, __LINE__);
                    break;
                } else
                    continue;
            }

            // get noiseSigma
            float* noiseSigma_lo = (float*)calloc(DHAZ_V11_SIGMA_LUT_NUM, sizeof(float));
            if (NULL == noiseSigma_lo) return XCAM_RETURN_ERROR_MEM;
            float* noiseSigma_hi = (float*)calloc(DHAZ_V11_SIGMA_LUT_NUM, sizeof(float));
            if (NULL == noiseSigma_hi) return XCAM_RETURN_ERROR_MEM;
            float* noiseSigma = (float*)calloc(DHAZ_V11_SIGMA_LUT_NUM, sizeof(float));
            if (NULL == noiseSigma) return XCAM_RETURN_ERROR_MEM;

            for (int i = 0; i < DHAZ_V11_SIGMA_LUT_NUM; i++) {
                float ave1, ave2, ave3, ave4;
                if (i == (DHAZ_V11_SIGMA_LUT_NUM - 1))
                    ave1 = (float)YNR_ISO_CURVE_SECT_VALUE1;
                else
                    ave1 = (float)(i * YNR_ISO_CURVE_SECT_VALUE);

                ave2 = ave1 * ave1;
                ave3 = ave2 * ave1;
                ave4 = ave3 * ave1;
                noiseSigma_lo[i] =
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_lo].sigma_curve[0] * ave4 +
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_lo].sigma_curve[1] * ave3 +
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_lo].sigma_curve[2] * ave2 +
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_lo].sigma_curve[3] * ave1 +
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_lo].sigma_curve[4];

                if (noiseSigma_lo[i] < 0) noiseSigma_lo[i] = 0;

                noiseSigma_hi[i] =
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_hi].sigma_curve[0] * ave4 +
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_hi].sigma_curve[1] * ave3 +
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_hi].sigma_curve[2] * ave2 +
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_hi].sigma_curve[3] * ave1 +
                    pYnrCalib->Setting[SnrMode].Calib_ISO[ISO_knot_hi].sigma_curve[4];

                if (noiseSigma_hi[i] < 0) noiseSigma_hi[i] = 0;

                noiseSigma[i] = ratio * (noiseSigma_hi[i] - noiseSigma_lo[i]) + noiseSigma_lo[i];
            }

            // get proc res
            // get sigma_idx
            for (int i = 0; i < DHAZ_V11_SIGMA_IDX_NUM; i++)
                pProcRes->ProcResV11duo.sigma_idx[i] = (i + 1) * YNR_CURVE_STEP;

            // get sigma_lut
            int tmp = 0;
            for (int i = 0; i < DHAZ_V11_SIGMA_LUT_NUM; i++) {
                tmp = LIMIT_VALUE(noiseSigma[i], BIT_10_MAX, BIT_MIN);
                pProcRes->ProcResV11duo.sigma_lut[i] = tmp;
            }

            free(noiseSigma);
            free(noiseSigma_lo);
            free(noiseSigma_hi);

#if 0
            LOGE_ADEHAZE("%s(%d) ISO:%f SnrMode:%d ISO_lo:%f ISO_hi:%f\n", __func__, __LINE__, ISO, SnrMode, ISO_lo, ISO_hi);
            LOGE_ADEHAZE("%s(%d) dehaze local gain IDX(0~5): 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n", __func__, __LINE__, ppProcRes->ProcResV11duo.sigma_idx[0], ppProcRes->ProcResV11duo.sigma_idx[1],
                         ppProcRes->ProcResV11duo.sigma_idx[2], ppProcRes->ProcResV11duo.sigma_idx[3], ppProcRes->ProcResV11duo.sigma_idx[4], ppProcRes->ProcResV11duo.sigma_idx[5]);
            LOGE_ADEHAZE("%s(%d) dehaze local gain LUT(0~5): 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n", __func__, __LINE__, ppProcRes->ProcResV11duo.sigma_lut[0], ppProcRes->ProcResV11duo.sigma_lut[1],
                         ppProcRes->ProcResV11duo.sigma_lut[2], ppProcRes->ProcResV11duo.sigma_lut[3], ppProcRes->ProcResV11duo.sigma_lut[4], ppProcRes->ProcResV11duo.sigma_lut[5]);
#endif
        } else
            LOGE_ADEHAZE("%s(%d) Ynr calib setting ISO length is under 1!!!\n", __func__, __LINE__);
    } else
        LOGE_ADEHAZE("%s(%d) Ynr calib setting length is under 1!!!\n", __func__, __LINE__);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return ret;
}

XCamReturn GetManuDehazeLocalGainSettingV11Duo(RkAiqAdehazeProcResult_t* pProcRes,
                                               mDehazeAttrV11_t* pstManu) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // get noiseSigma
    float* noiseSigma = (float*)calloc(DHAZ_V11_SIGMA_LUT_NUM, sizeof(float));
    if (NULL == noiseSigma) return XCAM_RETURN_ERROR_MEM;

    for (int i = 0; i < DHAZ_V11_SIGMA_LUT_NUM; i++) {
        float ave1, ave2, ave3, ave4;
        if (i == (DHAZ_V11_SIGMA_LUT_NUM - 1))
            ave1 = (float)YNR_ISO_CURVE_SECT_VALUE1;
        else
            ave1 = (float)(i * YNR_ISO_CURVE_SECT_VALUE);

        ave2 = ave1 * ave1;
        ave3 = ave2 * ave1;
        ave4 = ave3 * ave1;

        noiseSigma[i] = pstManu->sigma_curve[0] * ave4 + pstManu->sigma_curve[1] * ave3 +
                        pstManu->sigma_curve[2] * ave2 + pstManu->sigma_curve[3] * ave1 +
                        pstManu->sigma_curve[4];
    }

    // get proc res
    // get sigma_idx
    for (int i = 0; i < DHAZ_V11_SIGMA_IDX_NUM; i++)
        pProcRes->ProcResV11duo.sigma_idx[i] = (i + 1) * YNR_CURVE_STEP;

    // get sigma_lut
    int tmp = 0;
    for (int i = 0; i < DHAZ_V11_SIGMA_LUT_NUM; i++) {
        tmp                                  = LIMIT_VALUE(noiseSigma[i], BIT_10_MAX, BIT_MIN);
        pProcRes->ProcResV11duo.sigma_lut[i] = tmp;
    }

    free(noiseSigma);
#if 0
			LOGE_ADEHAZE("%s(%d) dehaze stManual sigma_curve(0~4): 0x%f 0x%f 0x%f 0x%f 0x%f\n", __func__, __LINE__, pstManu->sigma_curve[0], pstManu->sigma_curve[1],
                         pstManu->sigma_curve[2], pstManu->sigma_curve[3], pstManu->sigma_curve[4]);
            LOGE_ADEHAZE("%s(%d) dehaze local gain IDX(0~5): 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n", __func__, __LINE__, pProcRes->ProcResV11duo.sigma_idx[0], pProcRes->ProcResV11duo.sigma_idx[1],
                         pProcRes->ProcResV11duo.sigma_idx[2], pProcRes->ProcResV11duo.sigma_idx[3], pProcRes->ProcResV11duo.sigma_idx[4], pProcRes->ProcResV11duo.sigma_idx[5]);
            LOGE_ADEHAZE("%s(%d) dehaze local gain LUT(0~5): 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n", __func__, __LINE__, pProcRes->ProcResV11duo.sigma_lut[0], pProcRes->ProcResV11duo.sigma_lut[1],
                         pProcRes->ProcResV11duo.sigma_lut[2], pProcRes->ProcResV11duo.sigma_lut[3], pProcRes->ProcResV11duo.sigma_lut[4], pProcRes->ProcResV11duo.sigma_lut[5]);
#endif

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
    return ret;
}

void AdehazeGetStats(AdehazeHandle_t* pAdehazeCtx, rkisp_adehaze_stats_t* ROData) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);
    LOGV_ADEHAZE("%s: Adehaze RO data from register:\n", __FUNCTION__);

    pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_adp_air_base =
        ROData->dehaze_stats_v11_duo.dhaz_adp_air_base;
    pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_adp_wt = ROData->dehaze_stats_v11_duo.dhaz_adp_wt;
    pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_adp_gratio =
        ROData->dehaze_stats_v11_duo.dhaz_adp_gratio;
    pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_adp_tmax =
        ROData->dehaze_stats_v11_duo.dhaz_adp_tmax;
    pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_pic_sumh_left =
        ROData->dehaze_stats_v11_duo.dhaz_pic_sumh_left;
    pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_pic_sumh_right =
        ROData->dehaze_stats_v11_duo.dhaz_pic_sumh_right;
    for (int i = 0; i < DHAZ_V11_HIST_WR_NUM; i++)
        pAdehazeCtx->stats.dehaze_stats_v11_duo.h_rgb_iir[i] =
            ROData->dehaze_stats_v11_duo.h_rgb_iir[i];

    LOGV_ADEHAZE(
        "%s:  dhaz_adp_air_base:%d dhaz_adp_wt:%d dhaz_adp_gratio:%d dhaz_adp_tmax:%d "
        "dhaz_pic_sumh_left:%d dhaz_pic_sumh_right:%d\n",
        __FUNCTION__, pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_adp_air_base,
        pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_adp_wt,
        pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_adp_gratio,
        pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_adp_tmax,
        pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_pic_sumh_left,
        pAdehazeCtx->stats.dehaze_stats_v11_duo.dhaz_pic_sumh_right);
    for (int i = 0; i < DHAZ_V11_HIST_WR_NUM; i++)
        LOGV_ADEHAZE("%s:  h_rgb_iir[%d]:%d:\n", __FUNCTION__, i,
                     pAdehazeCtx->stats.dehaze_stats_v11_duo.h_rgb_iir[i]);

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

XCamReturn AdehazeGetCurrDataGroup(AdehazeHandle_t* pAdehazeCtx, RKAiqAecExpInfo_t* pAeEffExpo,
                                   XCamVideoBuffer* pAePreRes) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);
    XCamReturn ret               = XCAM_RETURN_NO_ERROR;

    // get EnvLv
    if (pAePreRes) {
        RkAiqAlgoPreResAe* pAEPreRes = (RkAiqAlgoPreResAe*)pAePreRes->map(pAePreRes);

        switch (pAdehazeCtx->FrameNumber) {
            case LINEAR_NUM:
                pAdehazeCtx->CurrDataV11duo.EnvLv = pAEPreRes->ae_pre_res_rk.GlobalEnvLv[0];
                break;
            case HDR_2X_NUM:
                pAdehazeCtx->CurrDataV11duo.EnvLv = pAEPreRes->ae_pre_res_rk.GlobalEnvLv[1];
                break;
            case HDR_3X_NUM:
                pAdehazeCtx->CurrDataV11duo.EnvLv = pAEPreRes->ae_pre_res_rk.GlobalEnvLv[1];
                break;
            default:
                LOGE_ADEHAZE("%s:  Wrong frame number in HDR mode!!!\n", __FUNCTION__);
                break;
        }

        // Normalize the current envLv for AEC
        pAdehazeCtx->CurrDataV11duo.EnvLv =
            (pAdehazeCtx->CurrDataV11duo.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
        pAdehazeCtx->CurrDataV11duo.EnvLv =
            LIMIT_VALUE(pAdehazeCtx->CurrDataV11duo.EnvLv, ENVLVMAX, ENVLVMIN);
    } else {
        pAdehazeCtx->CurrDataV11duo.EnvLv = ENVLVMIN;
        ret                               = XCAM_RETURN_ERROR_PARAM;
    }

    // get iso
    if (pAeEffExpo) {
        if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
            pAdehazeCtx->CurrDataV11duo.ISO = pAeEffExpo->LinearExp.exp_real_params.analog_gain *
                                              pAeEffExpo->LinearExp.exp_real_params.digital_gain *
                                              50.0f;
        else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
            pAdehazeCtx->CurrDataV11duo.ISO = pAeEffExpo->HdrExp[1].exp_real_params.analog_gain *
                                              pAeEffExpo->HdrExp[1].exp_real_params.digital_gain *
                                              50.0f;
    } else {
        pAdehazeCtx->CurrDataV11duo.ISO = ISOMIN;
        ret                             = XCAM_RETURN_ERROR_PARAM;
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
    return ret;
}

XCamReturn AdehazeGetCurrData(AdehazeHandle_t* pAdehazeCtx, RkAiqAlgoProcAdhaz* pProcPara) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);
    XCamReturn ret                = XCAM_RETURN_NO_ERROR;

    // get EnvLv
    XCamVideoBuffer* xCamAePreRes = pProcPara->com.u.proc.res_comb->ae_pre_res;
    if (xCamAePreRes) {
        RkAiqAlgoPreResAe* pAEPreRes = (RkAiqAlgoPreResAe*)xCamAePreRes->map(xCamAePreRes);

        switch (pAdehazeCtx->FrameNumber) {
            case LINEAR_NUM:
                pAdehazeCtx->CurrDataV11duo.EnvLv = pAEPreRes->ae_pre_res_rk.GlobalEnvLv[0];
                break;
            case HDR_2X_NUM:
                pAdehazeCtx->CurrDataV11duo.EnvLv = pAEPreRes->ae_pre_res_rk.GlobalEnvLv[1];
                break;
            case HDR_3X_NUM:
                pAdehazeCtx->CurrDataV11duo.EnvLv = pAEPreRes->ae_pre_res_rk.GlobalEnvLv[1];
                break;
            default:
                LOGE_ADEHAZE("%s:  Wrong frame number in HDR mode!!!\n", __FUNCTION__);
                break;
        }
        // Normalize the current envLv for AEC
        pAdehazeCtx->CurrDataV11duo.EnvLv =
            (pAdehazeCtx->CurrDataV11duo.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
        pAdehazeCtx->CurrDataV11duo.EnvLv =
            LIMIT_VALUE(pAdehazeCtx->CurrDataV11duo.EnvLv, ENVLVMAX, ENVLVMIN);
    } else {
        pAdehazeCtx->CurrDataV11duo.EnvLv = ENVLVMIN;
        ret                               = XCAM_RETURN_ERROR_PARAM;
    }

    // get ISO
    if (pProcPara->com.u.proc.nxtExp) {
        if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
            pAdehazeCtx->CurrDataV11duo.ISO =
                pProcPara->com.u.proc.nxtExp->LinearExp.exp_real_params.analog_gain *
                pProcPara->com.u.proc.nxtExp->LinearExp.exp_real_params.digital_gain * 50.0f;
        else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
            pAdehazeCtx->CurrDataV11duo.ISO =
                pProcPara->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain *
                pProcPara->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain * 50.0f;
    } else {
        pAdehazeCtx->CurrDataV11duo.ISO = ISOMIN;
        ret                             = XCAM_RETURN_ERROR_PARAM;
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
    return ret;
}

XCamReturn AdehazeInit(AdehazeHandle_t** pAdehazeCtx, CamCalibDbV2Context_t* pCalib) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret          = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t* handle = (AdehazeHandle_t*)calloc(1, sizeof(AdehazeHandle_t));

    CalibDbV2_dehaze_v11_t* calibv2_adehaze_calib_V11_duo =
        (CalibDbV2_dehaze_v11_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, adehaze_calib));
    memcpy(&handle->CalibV11duo.DehazeTuningPara, &calibv2_adehaze_calib_V11_duo->DehazeTuningPara,
           sizeof(CalibDbDehazeV11_t));  // load iq
    memcpy(&handle->AdehazeAtrrV11duo.stAuto, calibv2_adehaze_calib_V11_duo,
           sizeof(CalibDbV2_dehaze_v11_t));  // set defsult stAuto

    // dehaze local gain
    CalibDbV2_YnrV3_t* calibv2_Ynr = (CalibDbV2_YnrV3_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, ynr_v3));
    memcpy(&handle->CalibV11duo.YnrCalibPara, &calibv2_Ynr->CalibPara,
           sizeof(CalibDbV2_YnrV3_CalibPara_t));

    handle->PreDataV11duo.EnvLv   = 0.0;
    handle->PreDataV11duo.ApiMode = DEHAZE_API_AUTO;

    // set api default
    handle->AdehazeAtrrV11duo.mode                                               = DEHAZE_API_AUTO;
    handle->AdehazeAtrrV11duo.stManual.Enable                                    = true;
    handle->AdehazeAtrrV11duo.stManual.cfg_alpha                                 = 1.0;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.en                         = false;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.air_lc_en                  = true;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.stab_fnum                  = 8;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.sigma                      = 6;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.wt_sigma                   = 8;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.air_sigma                  = 120;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.tmax_sigma                 = 0.01;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.pre_wet                    = 0.01;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.dc_min_th       = 64;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.dc_max_th       = 192;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.yhist_th        = 249;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.yblk_th         = 0.002;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.dark_th         = 250;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.bright_min      = 180;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.bright_max      = 240;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.wt_max          = 0.9;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.air_min         = 200;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.air_max         = 250;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.tmax_base       = 125;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.tmax_off        = 0.1;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.tmax_max        = 0.8;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.cfg_wt          = 0.8;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.cfg_air         = 210;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.cfg_tmax        = 0.2;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.dc_weitcur      = 1;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.bf_weight       = 0.5;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.range_sigma     = 0.14;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.space_sigma_pre = 0.14;
    handle->AdehazeAtrrV11duo.stManual.dehaze_setting.DehazeData.space_sigma_cur = 0.14;

    handle->AdehazeAtrrV11duo.stManual.enhance_setting.en                         = true;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.EnhanceData.enhance_value  = 1.0;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.EnhanceData.enhance_chroma = 1.0;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[0]           = 0;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[1]           = 64;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[2]           = 128;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[3]           = 192;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[4]           = 256;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[5]           = 320;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[6]           = 384;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[7]           = 448;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[8]           = 512;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[9]           = 576;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[10]          = 640;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[11]          = 704;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[12]          = 768;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[13]          = 832;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[14]          = 896;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[15]          = 960;
    handle->AdehazeAtrrV11duo.stManual.enhance_setting.enhance_curve[16]          = 1023;

    handle->AdehazeAtrrV11duo.stManual.hist_setting.en                   = false;
    handle->AdehazeAtrrV11duo.stManual.hist_setting.hist_para_en         = true;
    handle->AdehazeAtrrV11duo.stManual.hist_setting.HistData.hist_gratio = 2;
    handle->AdehazeAtrrV11duo.stManual.hist_setting.HistData.hist_th_off = 64;
    handle->AdehazeAtrrV11duo.stManual.hist_setting.HistData.hist_k      = 2;
    handle->AdehazeAtrrV11duo.stManual.hist_setting.HistData.hist_min    = 0.015;
    handle->AdehazeAtrrV11duo.stManual.hist_setting.HistData.hist_scale  = 0.09;
    handle->AdehazeAtrrV11duo.stManual.hist_setting.HistData.cfg_gratio  = 2;

    handle->AdehazeAtrrV11duo.Info.ISO                 = ISOMIN;
    handle->AdehazeAtrrV11duo.Info.EnvLv               = ENVLVMIN;
    handle->AdehazeAtrrV11duo.Info.MDehazeStrth        = DEHAZE_API_MANUAL_DEFAULT_LEVEL;
    handle->AdehazeAtrrV11duo.Info.MEnhanceStrth       = DEHAZE_API_ENHANCE_MANUAL_DEFAULT_LEVEL;
    handle->AdehazeAtrrV11duo.Info.MEnhanceChromeStrth = DEHAZE_API_ENHANCE_MANUAL_DEFAULT_LEVEL;

    *pAdehazeCtx = handle;
    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return (ret);
}

XCamReturn AdehazeRelease(AdehazeHandle_t* pAdehazeCtx) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (pAdehazeCtx) free(pAdehazeCtx);
    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return (ret);
}

XCamReturn AdehazeProcess(AdehazeHandle_t* pAdehazeCtx) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    if (pAdehazeCtx->AdehazeAtrrV11duo.mode == DEHAZE_API_AUTO) {
        LOGD_ADEHAZE(" %s: Adehaze Api stAuto!!!\n", __func__);
        float CtrlValue = pAdehazeCtx->CurrDataV11duo.EnvLv;
        if (pAdehazeCtx->CurrDataV11duo.CtrlDataType == CTRLDATATYPE_ISO)
            CtrlValue = pAdehazeCtx->CurrDataV11duo.ISO;

        // cfg setting
        pAdehazeCtx->ProcRes.ProcResV11duo.cfg_alpha =
            LIMIT_VALUE(SHIFT8BIT(pAdehazeCtx->AdehazeAtrrV11duo.stAuto.DehazeTuningPara.cfg_alpha),
                        BIT_8_MAX, BIT_MIN);

        // enable setting
        EnableSettingV11duo(&pAdehazeCtx->AdehazeAtrrV11duo.stAuto.DehazeTuningPara,
                            &pAdehazeCtx->ProcRes);

        // dehaze setting
        GetDehazeParamsV11duo(&pAdehazeCtx->AdehazeAtrrV11duo.stAuto.DehazeTuningPara,
                              &pAdehazeCtx->ProcRes, pAdehazeCtx->width, pAdehazeCtx->height,
                              CtrlValue);

        // enhance setting
        GetEnhanceParamsV11duo(&pAdehazeCtx->AdehazeAtrrV11duo.stAuto.DehazeTuningPara,
                               &pAdehazeCtx->ProcRes, CtrlValue);

        // hist setting
        GetHistParamsV11duo(&pAdehazeCtx->AdehazeAtrrV11duo.stAuto.DehazeTuningPara,
                            &pAdehazeCtx->ProcRes, CtrlValue);

        // get local gain setting
        ret = GetDehazeLocalGainSettingV11(
            &pAdehazeCtx->ProcRes, &pAdehazeCtx->CalibV11duo.YnrCalibPara,
            pAdehazeCtx->CurrDataV11duo.ISO, pAdehazeCtx->CurrDataV11duo.SnrMode);
    } else if (pAdehazeCtx->AdehazeAtrrV11duo.mode == DEHAZE_API_MANUAL) {
        LOGD_ADEHAZE(" %s: Adehaze Api stManual!!!\n", __func__);

        // cfg setting
        pAdehazeCtx->ProcRes.ProcResV11duo.cfg_alpha = LIMIT_VALUE(
            SHIFT8BIT(pAdehazeCtx->AdehazeAtrrV11duo.stManual.cfg_alpha), BIT_8_MAX, BIT_MIN);

        // enable setting
        stManuEnableSettingV11duo(&pAdehazeCtx->AdehazeAtrrV11duo.stManual, &pAdehazeCtx->ProcRes);

        // dehaze setting
        stManuGetDehazeParamsV11duo(&pAdehazeCtx->AdehazeAtrrV11duo.stManual, &pAdehazeCtx->ProcRes,
                                    pAdehazeCtx->width, pAdehazeCtx->height);

        // enhance setting
        stManuGetEnhanceParamsV11duo(&pAdehazeCtx->AdehazeAtrrV11duo.stManual,
                                     &pAdehazeCtx->ProcRes);

        // hist setting
        stManuGetHistParamsV11duo(&pAdehazeCtx->AdehazeAtrrV11duo.stManual, &pAdehazeCtx->ProcRes);

        // get local gain setting
        ret = GetManuDehazeLocalGainSettingV11Duo(&pAdehazeCtx->ProcRes,
                                                  &pAdehazeCtx->AdehazeAtrrV11duo.stManual);
    } else
        LOGE_ADEHAZE("%s:Wrong Adehaze API mode!!! \n", __func__);

    // get Duo cam setting
    GetDehazeHistDuoISPSettingV11(&pAdehazeCtx->ProcRes, &pAdehazeCtx->stats,
                                  pAdehazeCtx->is_multi_isp_mode, pAdehazeCtx->FrameID);

    // store pre data
    pAdehazeCtx->PreDataV11duo.EnvLv = pAdehazeCtx->CurrDataV11duo.EnvLv;
    pAdehazeCtx->PreDataV11duo.ISO     = pAdehazeCtx->CurrDataV11duo.ISO;
    pAdehazeCtx->PreDataV11duo.ApiMode = pAdehazeCtx->CurrDataV11duo.ApiMode;

    // store api info
    pAdehazeCtx->AdehazeAtrrV11duo.Info.ISO   = pAdehazeCtx->CurrDataV11duo.ISO;
    pAdehazeCtx->AdehazeAtrrV11duo.Info.EnvLv = pAdehazeCtx->CurrDataV11duo.EnvLv;

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}

bool AdehazeByPassProcessing(AdehazeHandle_t* pAdehazeCtx) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    bool ret   = false;
    float diff = 0.0;

    pAdehazeCtx->CurrDataV11duo.CtrlDataType =
        pAdehazeCtx->AdehazeAtrrV11duo.stAuto.DehazeTuningPara.CtrlDataType;

    if (pAdehazeCtx->FrameID <= 2) pAdehazeCtx->byPassProc = false;
    if (pAdehazeCtx->AdehazeAtrrV11duo.mode > DEHAZE_API_AUTO)
        pAdehazeCtx->byPassProc = false;
    else if (pAdehazeCtx->AdehazeAtrrV11duo.mode != pAdehazeCtx->PreDataV11duo.ApiMode)
        pAdehazeCtx->byPassProc = false;
    else {
        if (pAdehazeCtx->CurrDataV11duo.CtrlDataType == CTRLDATATYPE_ENVLV) {
            diff = pAdehazeCtx->PreDataV11duo.EnvLv - pAdehazeCtx->CurrDataV11duo.EnvLv;
            if (pAdehazeCtx->PreDataV11duo.EnvLv == ENVLVMIN) {
                diff = pAdehazeCtx->CurrDataV11duo.EnvLv;
                if (diff == 0.0)
                    pAdehazeCtx->byPassProc = true;
                else
                    pAdehazeCtx->byPassProc = false;
            } else {
                diff /= pAdehazeCtx->PreDataV11duo.EnvLv;
                if (diff >= pAdehazeCtx->CalibV11duo.DehazeTuningPara.ByPassThr ||
                    diff <= (0 - pAdehazeCtx->CalibV11duo.DehazeTuningPara.ByPassThr))
                    pAdehazeCtx->byPassProc = false;
                else
                    pAdehazeCtx->byPassProc = true;
            }
        } else if (pAdehazeCtx->CurrDataV11duo.CtrlDataType == CTRLDATATYPE_ISO) {
            diff = pAdehazeCtx->PreDataV11duo.ISO - pAdehazeCtx->CurrDataV11duo.ISO;
            diff /= pAdehazeCtx->PreDataV11duo.ISO;
            if (diff >= pAdehazeCtx->CalibV11duo.DehazeTuningPara.ByPassThr ||
                diff <= (0 - pAdehazeCtx->CalibV11duo.DehazeTuningPara.ByPassThr))
                pAdehazeCtx->byPassProc = false;
            else
                pAdehazeCtx->byPassProc = true;
        }
    }

    ret = pAdehazeCtx->byPassProc;

    LOGD_ADEHAZE("%s:FrameID:%d CtrlDataType:%d EnvLv:%f ISO:%f byPassProc:%d\n", __func__,
                 pAdehazeCtx->FrameID, pAdehazeCtx->CurrDataV11duo.CtrlDataType,
                 pAdehazeCtx->CurrDataV11duo.EnvLv, pAdehazeCtx->CurrDataV11duo.ISO, ret);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}
