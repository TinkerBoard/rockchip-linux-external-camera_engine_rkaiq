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
#include "rk_aiq_adehaze_algo_v11.h"

#include <string.h>

#include "xcam_log.h"
#include "rkisp21-config.h"
#include "mathlib.h"

float LinearInterpV11(const float* pX, const float* pY, float posx, int XSize) {
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

int DehazeLinearInterpV11(const float* pX, const float* pY, float posx, int BitInt, int BitFlaot,
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

int LinearInterpEnableV11(const float* pX, const unsigned char* pY, float posx, int XSize) {
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

void EnableSettingV11(CalibDbDehazeV11_t* pCalibV11, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11.enable = pCalibV11->Enable;

    if (pCalibV11->Enable) {
        if (pCalibV11->dehaze_setting.en && pCalibV11->enhance_setting.en) {
            pProcRes->ProcResV11.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11.enhance_en = FUNCTION_ENABLE;
        } else if (pCalibV11->dehaze_setting.en && !pCalibV11->enhance_setting.en) {
            pProcRes->ProcResV11.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11.enhance_en = FUNCTION_DISABLE;
        } else if (!pCalibV11->dehaze_setting.en && pCalibV11->enhance_setting.en) {
            pProcRes->ProcResV11.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11.enhance_en = FUNCTION_ENABLE;
        } else {
            pProcRes->ProcResV11.dc_en      = FUNCTION_DISABLE;
            pProcRes->ProcResV11.enhance_en = FUNCTION_DISABLE;
        }

        if (pCalibV11->hist_setting.en)
            pProcRes->ProcResV11.hist_en = FUNCTION_ENABLE;
        else
            pProcRes->ProcResV11.hist_en = FUNCTION_DISABLE;
    } else {
        pProcRes->ProcResV11.dc_en      = FUNCTION_DISABLE;
        pProcRes->ProcResV11.enhance_en = FUNCTION_DISABLE;
        pProcRes->ProcResV11.hist_en    = FUNCTION_DISABLE;
    }

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV11.enable,
                 (pProcRes->ProcResV11.dc_en & FUNCTION_ENABLE) &&
                     (!(pProcRes->ProcResV11.enhance_en & FUNCTION_ENABLE)),
                 (pProcRes->ProcResV11.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV11.enhance_en & FUNCTION_ENABLE),
                 pProcRes->ProcResV11.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuEnableSettingV11(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11.enable = pStManu->Enable;

    if (pStManu->Enable) {
        if (pStManu->dehaze_setting.en && pStManu->enhance_setting.en) {
            pProcRes->ProcResV11.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11.enhance_en = FUNCTION_ENABLE;
        } else if (pStManu->dehaze_setting.en && !pStManu->enhance_setting.en) {
            pProcRes->ProcResV11.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11.enhance_en = FUNCTION_DISABLE;
        } else if (!pStManu->dehaze_setting.en && pStManu->enhance_setting.en) {
            pProcRes->ProcResV11.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11.enhance_en = FUNCTION_ENABLE;
        } else {
            pProcRes->ProcResV11.dc_en      = FUNCTION_DISABLE;
            pProcRes->ProcResV11.enhance_en = FUNCTION_DISABLE;
        }

        if (pStManu->hist_setting.en)
            pProcRes->ProcResV11.hist_en = FUNCTION_ENABLE;
        else
            pProcRes->ProcResV11.hist_en = FUNCTION_DISABLE;
    } else {
        pProcRes->ProcResV11.dc_en      = FUNCTION_DISABLE;
        pProcRes->ProcResV11.enhance_en = FUNCTION_DISABLE;
        pProcRes->ProcResV11.hist_en    = FUNCTION_DISABLE;
    }

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV11.enable,
                 (pProcRes->ProcResV11.dc_en & FUNCTION_ENABLE) &&
                     (!(pProcRes->ProcResV11.enhance_en & FUNCTION_ENABLE)),
                 (pProcRes->ProcResV11.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV11.enhance_en & FUNCTION_ENABLE),
                 pProcRes->ProcResV11.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

int ClipValueV11(float posx, int BitInt, int BitFloat) {
    int yOutInt    = 0;
    int yOutIntMax = (int)(pow(2, (BitFloat + BitInt)) - 1);
    int yOutIntMin = 0;

    yOutInt = LIMIT_VALUE((int)(posx * pow(2, BitFloat)), yOutIntMax, yOutIntMin);

    return yOutInt;
}

void stManuGetDehazeParamsV11(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes,
                              int rawWidth, int rawHeight) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11.air_lc_en =
        pStManu->dehaze_setting.air_lc_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    pProcRes->ProcResV11.dc_min_th =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.dc_min_th, 8, 0);
    pProcRes->ProcResV11.dc_max_th =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.dc_max_th, 8, 0);
    pProcRes->ProcResV11.yhist_th = ClipValueV11(pStManu->dehaze_setting.DehazeData.yhist_th, 8, 0);
    pProcRes->ProcResV11.yblk_th  = int(pStManu->dehaze_setting.DehazeData.yblk_th *
                                       ((rawWidth + 15) / 16) * ((rawHeight + 15) / 16));
    pProcRes->ProcResV11.dark_th  = ClipValueV11(pStManu->dehaze_setting.DehazeData.dark_th, 8, 0);
    pProcRes->ProcResV11.bright_min =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.bright_min, 8, 0);
    pProcRes->ProcResV11.bright_max =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.bright_max, 8, 0);
    pProcRes->ProcResV11.wt_max  = ClipValueV11(pStManu->dehaze_setting.DehazeData.wt_max, 0, 8);
    pProcRes->ProcResV11.air_min = ClipValueV11(pStManu->dehaze_setting.DehazeData.air_min, 8, 0);
    pProcRes->ProcResV11.air_max = ClipValueV11(pStManu->dehaze_setting.DehazeData.air_max, 8, 0);
    pProcRes->ProcResV11.tmax_base =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.tmax_base, 8, 0);
    pProcRes->ProcResV11.tmax_off =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.tmax_off, 0, 10);
    pProcRes->ProcResV11.tmax_max =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.tmax_max, 0, 10);
    pProcRes->ProcResV11.cfg_wt  = ClipValueV11(pStManu->dehaze_setting.DehazeData.cfg_wt, 0, 8);
    pProcRes->ProcResV11.cfg_air = ClipValueV11(pStManu->dehaze_setting.DehazeData.cfg_air, 8, 0);
    pProcRes->ProcResV11.cfg_tmax =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.cfg_tmax, 0, 10);
    pProcRes->ProcResV11.range_sima =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.range_sigma, 0, 9);
    pProcRes->ProcResV11.space_sigma_cur =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.space_sigma_cur, 0, 8);
    pProcRes->ProcResV11.space_sigma_pre =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.space_sigma_pre, 0, 8);
    pProcRes->ProcResV11.bf_weight =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.bf_weight, 0, 8);
    pProcRes->ProcResV11.dc_weitcur =
        ClipValueV11(pStManu->dehaze_setting.DehazeData.dc_weitcur, 0, 8);
    pProcRes->ProcResV11.stab_fnum      = ClipValueV11(pStManu->dehaze_setting.stab_fnum, 5, 0);
    pProcRes->ProcResV11.iir_sigma      = ClipValueV11(pStManu->dehaze_setting.sigma, 8, 0);
    pProcRes->ProcResV11.iir_wt_sigma   = ClipValueV11(pStManu->dehaze_setting.wt_sigma, 8, 3);
    pProcRes->ProcResV11.iir_air_sigma  = ClipValueV11(pStManu->dehaze_setting.air_sigma, 8, 0);
    pProcRes->ProcResV11.iir_tmax_sigma = ClipValueV11(pStManu->dehaze_setting.tmax_sigma, 0, 10);
    pProcRes->ProcResV11.iir_pre_wet    = ClipValueV11(pStManu->dehaze_setting.pre_wet, 0, 4);
    pProcRes->ProcResV11.gaus_h0        = DEHAZE_GAUS_H4;
    pProcRes->ProcResV11.gaus_h1        = DEHAZE_GAUS_H1;
    pProcRes->ProcResV11.gaus_h2        = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV11.dc_en && !(pProcRes->ProcResV11.enhance_en)) {
        if (pProcRes->ProcResV11.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:1 cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__,
                         pProcRes->ProcResV11.cfg_air / 1.0f,
                         pProcRes->ProcResV11.cfg_tmax / 1023.0f,
                         pProcRes->ProcResV11.cfg_wt / 255.0f);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x255 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n",
                         __func__, pProcRes->ProcResV11.cfg_air, pProcRes->ProcResV11.cfg_tmax,
                         pProcRes->ProcResV11.cfg_wt);
        } else if (pProcRes->ProcResV11.cfg_alpha == 0) {
            LOGD_ADEHAZE("%s cfg_alpha:0 air_max:%f air_min:%f tmax_base:%f wt_max:%f\n", __func__,
                         pProcRes->ProcResV11.air_max / 1.0f, pProcRes->ProcResV11.air_min / 1.0f,
                         pProcRes->ProcResV11.tmax_base / 1.0f,
                         pProcRes->ProcResV11.wt_max / 255.0f);
            LOGD_ADEHAZE(
                "%s cfg_alpha_reg:0x0 air_max:0x%x air_min:0x%x tmax_base:0x%x wt_max:0x%x\n",
                __func__, pProcRes->ProcResV11.air_max, pProcRes->ProcResV11.air_min,
                pProcRes->ProcResV11.tmax_base, pProcRes->ProcResV11.wt_max);
        }
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetEnhanceParamsV11(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11.enhance_value =
        ClipValueV11(pStManu->enhance_setting.EnhanceData.enhance_value, 4, 10);
    pProcRes->ProcResV11.enhance_chroma =
        ClipValueV11(pStManu->enhance_setting.EnhanceData.enhance_chroma, 4, 10);

    for (int i = 0; i < DHAZ_V11_ENHANCE_CRUVE_NUM; i++)
        pProcRes->ProcResV11.enh_curve[i] = (int)(pStManu->enhance_setting.enhance_curve[i]);

    if (pProcRes->ProcResV11.dc_en && pProcRes->ProcResV11.enhance_en) {
        LOGD_ADEHAZE("%s enhance_value:%f enhance_chroma:%f\n", __func__,
                     pStManu->enhance_setting.EnhanceData.enhance_value / 1024.0f,
                     pStManu->enhance_setting.EnhanceData.enhance_chroma / 1024.0f);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV11.enhance_value, pProcRes->ProcResV11.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetHistParamsV11(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11.hpara_en =
        pStManu->hist_setting.hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    // clip hpara_en
    pProcRes->ProcResV11.hpara_en =
        pProcRes->ProcResV11.dc_en ? pProcRes->ProcResV11.hpara_en : FUNCTION_ENABLE;

    pProcRes->ProcResV11.hist_gratio =
        ClipValueV11(pStManu->hist_setting.HistData.hist_gratio, 0, 8);
    pProcRes->ProcResV11.hist_th_off =
        ClipValueV11(pStManu->hist_setting.HistData.hist_th_off, 8, 0);
    pProcRes->ProcResV11.hist_k     = ClipValueV11(pStManu->hist_setting.HistData.hist_k, 3, 2);
    pProcRes->ProcResV11.hist_min   = ClipValueV11(pStManu->hist_setting.HistData.hist_min, 1, 8);
    pProcRes->ProcResV11.cfg_gratio = ClipValueV11(pStManu->hist_setting.HistData.cfg_gratio, 5, 8);
    pProcRes->ProcResV11.hist_scale = ClipValueV11(pStManu->hist_setting.HistData.hist_scale, 5, 8);

    if (pProcRes->ProcResV11.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f "
            "hist_min:%f hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV11.cfg_alpha / 255.0f, pProcRes->ProcResV11.hpara_en,
            pProcRes->ProcResV11.hist_gratio / 255.0f, pProcRes->ProcResV11.hist_th_off / 1.0f,
            pProcRes->ProcResV11.hist_k / 4.0f, pProcRes->ProcResV11.hist_min / 256.0f,
            pProcRes->ProcResV11.hist_scale / 256.0f, pProcRes->ProcResV11.cfg_gratio / 256.0f);
        LOGD_ADEHAZE(
            "%s cfg_alpha_reg:0x%x hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x "
            "hist_min_reg:0x%x hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n",
            __func__, pProcRes->ProcResV11.cfg_alpha, pProcRes->ProcResV11.hist_gratio,
            pProcRes->ProcResV11.hist_th_off, pProcRes->ProcResV11.hist_k,
            pProcRes->ProcResV11.hist_min, pProcRes->ProcResV11.hist_scale,
            pProcRes->ProcResV11.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeParamsV11(CalibDbDehazeV11_t* pCalibV11, RkAiqAdehazeProcResult_t* pProcRes,
                        int rawWidth, int rawHeight, float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11.air_lc_en =
        pCalibV11->dehaze_setting.air_lc_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    pProcRes->ProcResV11.dc_min_th = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.dc_min_th, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.dc_max_th = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.dc_max_th, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.yhist_th = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.yhist_th, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.yblk_th = LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.CtrlData,
                                                   pCalibV11->dehaze_setting.DehazeData.yblk_th,
                                                   CtrlValue, DHAZ_CTRL_DATA_STEP_MAX) *
                                   ((rawWidth + 15) / 16) * ((rawHeight + 15) / 16);
    pProcRes->ProcResV11.dark_th = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData, pCalibV11->dehaze_setting.DehazeData.dark_th,
        CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.bright_min = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.bright_min, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.bright_max = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.bright_max, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.wt_max = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData, pCalibV11->dehaze_setting.DehazeData.wt_max,
        CtrlValue, 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.air_min = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData, pCalibV11->dehaze_setting.DehazeData.air_min,
        CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.air_max = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData, pCalibV11->dehaze_setting.DehazeData.air_max,
        CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.tmax_base = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.tmax_base, CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.tmax_off = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.tmax_off, CtrlValue, 0, 10, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.tmax_max = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.tmax_max, CtrlValue, 0, 10, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.cfg_wt = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData, pCalibV11->dehaze_setting.DehazeData.cfg_wt,
        CtrlValue, 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.cfg_air = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData, pCalibV11->dehaze_setting.DehazeData.cfg_air,
        CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.cfg_tmax = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.cfg_tmax, CtrlValue, 0, 10, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.range_sima = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.range_sigma, CtrlValue, 0, 9, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.space_sigma_cur =
        DehazeLinearInterpV11(pCalibV11->dehaze_setting.DehazeData.CtrlData,
                              pCalibV11->dehaze_setting.DehazeData.space_sigma_cur, CtrlValue, 0, 8,
                              DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.space_sigma_pre =
        DehazeLinearInterpV11(pCalibV11->dehaze_setting.DehazeData.CtrlData,
                              pCalibV11->dehaze_setting.DehazeData.space_sigma_pre, CtrlValue, 0, 8,
                              DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.bf_weight = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.bf_weight, CtrlValue, 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.dc_weitcur = DehazeLinearInterpV11(
        pCalibV11->dehaze_setting.DehazeData.CtrlData,
        pCalibV11->dehaze_setting.DehazeData.dc_weitcur, CtrlValue, 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.stab_fnum      = ClipValueV11(pCalibV11->dehaze_setting.stab_fnum, 5, 0);
    pProcRes->ProcResV11.iir_sigma      = ClipValueV11(pCalibV11->dehaze_setting.sigma, 8, 0);
    pProcRes->ProcResV11.iir_wt_sigma   = ClipValueV11(pCalibV11->dehaze_setting.wt_sigma, 8, 3);
    pProcRes->ProcResV11.iir_air_sigma  = ClipValueV11(pCalibV11->dehaze_setting.air_sigma, 8, 0);
    pProcRes->ProcResV11.iir_tmax_sigma = ClipValueV11(pCalibV11->dehaze_setting.tmax_sigma, 0, 10);
    pProcRes->ProcResV11.iir_pre_wet    = ClipValueV11(pCalibV11->dehaze_setting.pre_wet, 0, 4);
    pProcRes->ProcResV11.gaus_h0        = DEHAZE_GAUS_H4;
    pProcRes->ProcResV11.gaus_h1        = DEHAZE_GAUS_H1;
    pProcRes->ProcResV11.gaus_h2        = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV11.dc_en && !(pProcRes->ProcResV11.enhance_en)) {
        if (pProcRes->ProcResV11.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:1 CtrlValue:%f cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__,
                         CtrlValue, pProcRes->ProcResV11.cfg_air / 1.0f,
                         pProcRes->ProcResV11.cfg_tmax / 1023.0f,
                         pProcRes->ProcResV11.cfg_wt / 255.0f);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x255 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n",
                         __func__, pProcRes->ProcResV11.cfg_air, pProcRes->ProcResV11.cfg_tmax,
                         pProcRes->ProcResV11.cfg_wt);
        } else if (pProcRes->ProcResV11.cfg_alpha == 0) {
            LOGD_ADEHAZE(
                "%s cfg_alpha:0 CtrlValue:%f air_max:%f air_min:%f tmax_base:%f wt_max:%f\n",
                __func__, CtrlValue, pProcRes->ProcResV11.air_max / 1.0f,
                pProcRes->ProcResV11.air_min / 1.0f, pProcRes->ProcResV11.tmax_base / 1.0f,
                pProcRes->ProcResV11.wt_max / 255.0f);
            LOGD_ADEHAZE(
                "%s cfg_alpha_reg:0x0 air_max:0x%x air_min:0x%x tmax_base:0x%x wt_max:0x%x\n",
                __func__, pProcRes->ProcResV11.air_max, pProcRes->ProcResV11.air_min,
                pProcRes->ProcResV11.tmax_base, pProcRes->ProcResV11.wt_max);
        }
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetEnhanceParamsV11(CalibDbDehazeV11_t* pCalibV11, RkAiqAdehazeProcResult_t* pProcRes,
                         float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11.enhance_value =
        DehazeLinearInterpV11(pCalibV11->enhance_setting.EnhanceData.CtrlData,
                              pCalibV11->enhance_setting.EnhanceData.enhance_value, CtrlValue, 4,
                              10, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.enhance_chroma =
        DehazeLinearInterpV11(pCalibV11->enhance_setting.EnhanceData.CtrlData,
                              pCalibV11->enhance_setting.EnhanceData.enhance_chroma, CtrlValue, 4,
                              10, DHAZ_CTRL_DATA_STEP_MAX);

    for (int i = 0; i < DHAZ_V11_ENHANCE_CRUVE_NUM; i++)
        pProcRes->ProcResV11.enh_curve[i] = (int)(pCalibV11->enhance_setting.enhance_curve[i]);

    if (pProcRes->ProcResV11.dc_en && pProcRes->ProcResV11.enhance_en) {
        LOGD_ADEHAZE("%s CtrlValue:%f enhance_value:%f enhance_chroma:%f\n", __func__, CtrlValue,
                     pProcRes->ProcResV11.enhance_value / 1024.0f,
                     pProcRes->ProcResV11.enhance_chroma / 1024.0f);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV11.enhance_value, pProcRes->ProcResV11.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetHistParamsV11(CalibDbDehazeV11_t* pCalibV11, RkAiqAdehazeProcResult_t* pProcRes,
                      float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11.hpara_en =
        pCalibV11->hist_setting.hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    // clip hpara_en
    pProcRes->ProcResV11.hpara_en = pProcRes->ProcResV11.dc_en
                                        ? pProcRes->ProcResV11.hpara_en
                                        : FUNCTION_ENABLE;  //  dc en 关闭，hpara必需开

    pProcRes->ProcResV11.hist_gratio = DehazeLinearInterpV11(
        pCalibV11->hist_setting.HistData.CtrlData, pCalibV11->hist_setting.HistData.hist_gratio,
        CtrlValue, 0, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.hist_th_off = DehazeLinearInterpV11(
        pCalibV11->hist_setting.HistData.CtrlData, pCalibV11->hist_setting.HistData.hist_th_off,
        CtrlValue, 8, 0, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.hist_k   = DehazeLinearInterpV11(pCalibV11->hist_setting.HistData.CtrlData,
                                                        pCalibV11->hist_setting.HistData.hist_k,
                                                        CtrlValue, 3, 2, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.hist_min = DehazeLinearInterpV11(pCalibV11->hist_setting.HistData.CtrlData,
                                                          pCalibV11->hist_setting.HistData.hist_min,
                                                          CtrlValue, 1, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.cfg_gratio = DehazeLinearInterpV11(
        pCalibV11->hist_setting.HistData.CtrlData, pCalibV11->hist_setting.HistData.cfg_gratio,
        CtrlValue, 5, 8, DHAZ_CTRL_DATA_STEP_MAX);
    pProcRes->ProcResV11.hist_scale = DehazeLinearInterpV11(
        pCalibV11->hist_setting.HistData.CtrlData, pCalibV11->hist_setting.HistData.hist_scale,
        CtrlValue, 5, 8, DHAZ_CTRL_DATA_STEP_MAX);

    if (pProcRes->ProcResV11.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f CtrlValue:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f "
            "hist_min:%f hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV11.cfg_alpha / 255.0f, CtrlValue,
            pProcRes->ProcResV11.hpara_en, pProcRes->ProcResV11.hist_gratio / 255.0f,
            pProcRes->ProcResV11.hist_th_off / 1.0f, pProcRes->ProcResV11.hist_k / 4.0f,
            pProcRes->ProcResV11.hist_min / 256.0f, pProcRes->ProcResV11.hist_scale / 256.0f,
            pProcRes->ProcResV11.cfg_gratio / 256.0f);
        LOGD_ADEHAZE(
            "%s cfg_alpha_reg:0x%x hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x "
            "hist_min_reg:0x%x hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n",
            __func__, pProcRes->ProcResV11.cfg_alpha, pProcRes->ProcResV11.hist_gratio,
            pProcRes->ProcResV11.hist_th_off, pProcRes->ProcResV11.hist_k,
            pProcRes->ProcResV11.hist_min, pProcRes->ProcResV11.hist_scale,
            pProcRes->ProcResV11.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void AdehazeManuProcessV11(RkAiqAdehazeProcResult_t* pProcRes, mDehazeAttrV11_t* pStManu) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
}

void AdehazeGetStats(AdehazeHandle_t* pAdehazeCtx, rkisp_adehaze_stats_t* ROData) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);
    LOGV_ADEHAZE("%s: Adehaze RO data from register:\n", __FUNCTION__);

    pAdehazeCtx->stats.dehaze_stats_v11.dhaz_adp_air_base =
        ROData->dehaze_stats_v11.dhaz_adp_air_base;
    pAdehazeCtx->stats.dehaze_stats_v11.dhaz_adp_wt     = ROData->dehaze_stats_v11.dhaz_adp_wt;
    pAdehazeCtx->stats.dehaze_stats_v11.dhaz_adp_gratio = ROData->dehaze_stats_v11.dhaz_adp_gratio;
    pAdehazeCtx->stats.dehaze_stats_v11.dhaz_adp_tmax   = ROData->dehaze_stats_v11.dhaz_adp_tmax;
    for (int i = 0; i < ISP21_DHAZ_HIST_IIR_NUM; i++)
        pAdehazeCtx->stats.dehaze_stats_v11.h_rgb_iir[i] = ROData->dehaze_stats_v11.h_rgb_iir[i];

    LOGV_ADEHAZE("%s:  dhaz_adp_air_base:%d dhaz_adp_wt:%d dhaz_adp_gratio:%d dhaz_adp_tmax:%d\n",
                 __FUNCTION__, pAdehazeCtx->stats.dehaze_stats_v11.dhaz_adp_air_base,
                 pAdehazeCtx->stats.dehaze_stats_v11.dhaz_adp_wt,
                 pAdehazeCtx->stats.dehaze_stats_v11.dhaz_adp_gratio,
                 pAdehazeCtx->stats.dehaze_stats_v11.dhaz_adp_tmax);
    for (int i = 0; i < ISP21_DHAZ_HIST_IIR_NUM; i++)
        LOGV_ADEHAZE("%s:  h_rgb_iir[%d]:%d:\n", __FUNCTION__, i,
                     pAdehazeCtx->stats.dehaze_stats_v11.h_rgb_iir[i]);

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

void AdehazeGetEnvLvISO(AdehazeHandle_t* pAdehazeCtx, RkAiqAlgoPreResAe* pAePreRes) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);

    if (pAePreRes == NULL) {
        LOGE_ADEHAZE("%s:Ae Pre Res is NULL!\n", __FUNCTION__);
        pAdehazeCtx->CurrDataV11.EnvLv = ENVLVMIN;
        return;
    }

    switch (pAdehazeCtx->FrameNumber) {
        case LINEAR_NUM:
            pAdehazeCtx->CurrDataV11.EnvLv = pAePreRes->ae_pre_res_rk.GlobalEnvLv[0];
            break;
        case HDR_2X_NUM:
            pAdehazeCtx->CurrDataV11.EnvLv = pAePreRes->ae_pre_res_rk.GlobalEnvLv[1];
            break;
        case HDR_3X_NUM:
            pAdehazeCtx->CurrDataV11.EnvLv = pAePreRes->ae_pre_res_rk.GlobalEnvLv[1];
            break;
        default:
            LOGE_ADEHAZE("%s:  Wrong frame number in HDR mode!!!\n", __FUNCTION__);
            break;
    }

    // Normalize the current envLv for AEC
    pAdehazeCtx->CurrDataV11.EnvLv =
        (pAdehazeCtx->CurrDataV11.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
    pAdehazeCtx->CurrDataV11.EnvLv =
        LIMIT_VALUE(pAdehazeCtx->CurrDataV11.EnvLv, ENVLVMAX, ENVLVMIN);

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

XCamReturn AdehazeGetCurrDataGroup(AdehazeHandle_t* pAdehazeCtx, RKAiqAecExpInfo_t* pAeEffExpo,
                                   XCamVideoBuffer* pAePreRes) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);
    XCamReturn ret               = XCAM_RETURN_NO_ERROR;

    // get EnvLv
    if (pAePreRes) {
        RkAiqAlgoPreResAe* pAEPreRes = (RkAiqAlgoPreResAe*)pAePreRes->map(pAePreRes);
        AdehazeGetEnvLvISO(pAdehazeCtx, pAEPreRes);
    } else {
        pAdehazeCtx->CurrDataV11.EnvLv = ENVLVMIN;
        ret                            = XCAM_RETURN_ERROR_PARAM;
    }

    // get iso
    if (pAeEffExpo) {
        if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
            pAdehazeCtx->CurrDataV11.ISO = pAeEffExpo->LinearExp.exp_real_params.analog_gain *
                                           pAeEffExpo->LinearExp.exp_real_params.digital_gain *
                                           50.0f;
        else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
            pAdehazeCtx->CurrDataV11.ISO = pAeEffExpo->HdrExp[1].exp_real_params.analog_gain *
                                           pAeEffExpo->HdrExp[1].exp_real_params.digital_gain *
                                           50.0f;
    } else {
        pAdehazeCtx->CurrDataV11.ISO   = ISOMIN;
        ret                            = XCAM_RETURN_ERROR_PARAM;
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
    return ret;
}

XCamReturn AdehazeGetCurrData(AdehazeHandle_t* pAdehazeCtx, RkAiqAlgoProcAdhaz* pProcPara) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);
    XCamReturn ret                = XCAM_RETURN_NO_ERROR;

    // get EvnLv
    XCamVideoBuffer* xCamAePreRes = pProcPara->com.u.proc.res_comb->ae_pre_res;
    if (xCamAePreRes) {
        RkAiqAlgoPreResAe* pAEPreRes = (RkAiqAlgoPreResAe*)xCamAePreRes->map(xCamAePreRes);
        AdehazeGetEnvLvISO(pAdehazeCtx, pAEPreRes);
    } else {
        pAdehazeCtx->CurrDataV11.EnvLv = ENVLVMIN;
        ret                            = XCAM_RETURN_ERROR_PARAM;
    }

    // get ISO
    if (pProcPara->com.u.proc.nxtExp) {
        if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
            pAdehazeCtx->CurrDataV11.ISO =
                pProcPara->com.u.proc.nxtExp->LinearExp.exp_real_params.analog_gain *
                pProcPara->com.u.proc.nxtExp->LinearExp.exp_real_params.digital_gain * 50.0f;
        else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
            pAdehazeCtx->CurrDataV11.ISO =
                pProcPara->com.u.proc.nxtExp->HdrExp[1].exp_real_params.analog_gain *
                pProcPara->com.u.proc.nxtExp->HdrExp[1].exp_real_params.digital_gain * 50.0f;
    } else {
        pAdehazeCtx->CurrDataV11.ISO = ISOMIN;
        ret                          = XCAM_RETURN_ERROR_PARAM;
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
    return ret;
}

XCamReturn AdehazeInit(AdehazeHandle_t** pAdehazeCtx, CamCalibDbV2Context_t* pCalib) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret          = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t* handle = (AdehazeHandle_t*)calloc(1, sizeof(AdehazeHandle_t));

    CalibDbV2_dehaze_v11_t* calibv2_adehaze_calib_V21 =
        (CalibDbV2_dehaze_v11_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, adehaze_calib));
    memcpy(&handle->AdehazeAtrrV11.stAuto, calibv2_adehaze_calib_V21,
           sizeof(CalibDbV2_dehaze_v11_t));  // set default stauto

    handle->PreDataV11.EnvLv   = ENVLVMIN;
    handle->PreDataV11.ApiMode = DEHAZE_API_AUTO;

    // set api default
    handle->AdehazeAtrrV11.mode                                               = DEHAZE_API_AUTO;
    handle->AdehazeAtrrV11.stManual.Enable                                    = true;
    handle->AdehazeAtrrV11.stManual.cfg_alpha                                 = 1.0;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.en                         = false;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.air_lc_en                  = true;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.stab_fnum                  = 8;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.sigma                      = 6;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.wt_sigma                   = 8;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.air_sigma                  = 120;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.tmax_sigma                 = 0.01;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.pre_wet                    = 0.01;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.dc_min_th       = 64;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.dc_max_th       = 192;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.yhist_th        = 249;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.yblk_th         = 0.002;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.dark_th         = 250;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.bright_min      = 180;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.bright_max      = 240;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.wt_max          = 0.9;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.air_min         = 200;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.air_max         = 250;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.tmax_base       = 125;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.tmax_off        = 0.1;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.tmax_max        = 0.8;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.cfg_wt          = 0.8;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.cfg_air         = 210;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.cfg_tmax        = 0.2;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.dc_weitcur      = 1;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.bf_weight       = 0.5;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.range_sigma     = 0.14;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.space_sigma_pre = 0.14;
    handle->AdehazeAtrrV11.stManual.dehaze_setting.DehazeData.space_sigma_cur = 0.14;

    handle->AdehazeAtrrV11.stManual.enhance_setting.en                         = true;
    handle->AdehazeAtrrV11.stManual.enhance_setting.EnhanceData.enhance_value  = 1.0;
    handle->AdehazeAtrrV11.stManual.enhance_setting.EnhanceData.enhance_chroma = 1.0;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[0]           = 0;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[1]           = 64;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[2]           = 128;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[3]           = 192;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[4]           = 256;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[5]           = 320;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[6]           = 384;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[7]           = 448;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[8]           = 512;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[9]           = 576;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[10]          = 640;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[11]          = 704;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[12]          = 768;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[13]          = 832;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[14]          = 896;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[15]          = 960;
    handle->AdehazeAtrrV11.stManual.enhance_setting.enhance_curve[16]          = 1023;

    handle->AdehazeAtrrV11.stManual.hist_setting.en                   = false;
    handle->AdehazeAtrrV11.stManual.hist_setting.hist_para_en         = true;
    handle->AdehazeAtrrV11.stManual.hist_setting.HistData.hist_gratio = 2;
    handle->AdehazeAtrrV11.stManual.hist_setting.HistData.hist_th_off = 64;
    handle->AdehazeAtrrV11.stManual.hist_setting.HistData.hist_k      = 2;
    handle->AdehazeAtrrV11.stManual.hist_setting.HistData.hist_min    = 0.015;
    handle->AdehazeAtrrV11.stManual.hist_setting.HistData.hist_scale  = 0.09;
    handle->AdehazeAtrrV11.stManual.hist_setting.HistData.cfg_gratio  = 2;

    handle->AdehazeAtrrV11.Info.ISO                 = ISOMIN;
    handle->AdehazeAtrrV11.Info.EnvLv               = ENVLVMIN;
    handle->AdehazeAtrrV11.Info.MDehazeStrth        = DEHAZE_API_MANUAL_DEFAULT_LEVEL;
    handle->AdehazeAtrrV11.Info.MEnhanceStrth       = DEHAZE_API_ENHANCE_MANUAL_DEFAULT_LEVEL;
    handle->AdehazeAtrrV11.Info.MEnhanceChromeStrth = DEHAZE_API_ENHANCE_MANUAL_DEFAULT_LEVEL;

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

    if (pAdehazeCtx->AdehazeAtrrV11.mode == DEHAZE_API_AUTO) {
        LOGD_ADEHAZE(" %s: Adehaze stAuto!!!\n", __func__);
        float CtrlValue = pAdehazeCtx->CurrDataV11.EnvLv;
        if (pAdehazeCtx->CurrDataV11.CtrlDataType == CTRLDATATYPE_ISO)
            CtrlValue = pAdehazeCtx->CurrDataV11.ISO;

        // cfg setting
        pAdehazeCtx->ProcRes.ProcResV11.cfg_alpha =
            LIMIT_VALUE(SHIFT8BIT(pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara.cfg_alpha),
                        BIT_8_MAX, BIT_MIN);

        // enable setting
        EnableSettingV11(&pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara,
                         &pAdehazeCtx->ProcRes);

        // dehaze setting
        GetDehazeParamsV11(&pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara,
                           &pAdehazeCtx->ProcRes, pAdehazeCtx->width, pAdehazeCtx->height,
                           CtrlValue);

        // enhance setting
        GetEnhanceParamsV11(&pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara,
                            &pAdehazeCtx->ProcRes, CtrlValue);

        // hist setting
        GetHistParamsV11(&pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara,
                         &pAdehazeCtx->ProcRes, CtrlValue);
    } else if (pAdehazeCtx->AdehazeAtrrV11.mode == DEHAZE_API_MANUAL) {
        LOGD_ADEHAZE(" %s: Adehaze Api stManual!!!\n", __func__);

        // cfg setting
        pAdehazeCtx->ProcRes.ProcResV11.cfg_alpha = LIMIT_VALUE(
            SHIFT8BIT(pAdehazeCtx->AdehazeAtrrV11.stManual.cfg_alpha), BIT_8_MAX, BIT_MIN);

        // enable setting
        stManuEnableSettingV11(&pAdehazeCtx->AdehazeAtrrV11.stManual, &pAdehazeCtx->ProcRes);

        // dehaze setting
        stManuGetDehazeParamsV11(&pAdehazeCtx->AdehazeAtrrV11.stManual, &pAdehazeCtx->ProcRes,
                                 pAdehazeCtx->width, pAdehazeCtx->height);

        // enhance setting
        stManuGetEnhanceParamsV11(&pAdehazeCtx->AdehazeAtrrV11.stManual, &pAdehazeCtx->ProcRes);

        // hist setting
        stManuGetHistParamsV11(&pAdehazeCtx->AdehazeAtrrV11.stManual, &pAdehazeCtx->ProcRes);
    } else
        LOGE_ADEHAZE("%s:Wrong Adehaze API mode!!! \n", __func__);

    // store pre data
    pAdehazeCtx->PreDataV11.EnvLv = pAdehazeCtx->CurrDataV11.EnvLv;
    pAdehazeCtx->PreDataV11.ISO     = pAdehazeCtx->CurrDataV11.ISO;
    pAdehazeCtx->PreDataV11.ApiMode = pAdehazeCtx->CurrDataV11.ApiMode;

    // store api info
    pAdehazeCtx->AdehazeAtrrV11.Info.ISO   = pAdehazeCtx->CurrDataV11.ISO;
    pAdehazeCtx->AdehazeAtrrV11.Info.EnvLv = pAdehazeCtx->CurrDataV11.EnvLv;

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}

bool AdehazeByPassProcessing(AdehazeHandle_t* pAdehazeCtx) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    bool ret   = false;
    float diff = 0.0;

    pAdehazeCtx->CurrDataV11.CtrlDataType =
        pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara.CtrlDataType;

    if (pAdehazeCtx->FrameID <= 2) pAdehazeCtx->byPassProc = false;
    if (pAdehazeCtx->AdehazeAtrrV11.mode > DEHAZE_API_AUTO)
        pAdehazeCtx->byPassProc = false;
    else if (pAdehazeCtx->AdehazeAtrrV11.mode != pAdehazeCtx->PreDataV11.ApiMode)
        pAdehazeCtx->byPassProc = false;
    else {
        if (pAdehazeCtx->CurrDataV11.CtrlDataType == CTRLDATATYPE_ENVLV) {
            diff = pAdehazeCtx->PreDataV11.EnvLv - pAdehazeCtx->CurrDataV11.EnvLv;
            if (pAdehazeCtx->PreDataV11.EnvLv == 0.0) {
                diff = pAdehazeCtx->CurrDataV11.EnvLv;
                if (diff == 0.0)
                    pAdehazeCtx->byPassProc = true;
                else
                    pAdehazeCtx->byPassProc = false;
            } else {
                diff /= pAdehazeCtx->PreDataV11.EnvLv;
                if (diff >= pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara.ByPassThr ||
                    diff <= (0 - pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara.ByPassThr))
                    pAdehazeCtx->byPassProc = false;
                else
                    pAdehazeCtx->byPassProc = true;
            }
        } else if (pAdehazeCtx->CurrDataV11.CtrlDataType == CTRLDATATYPE_ISO) {
            diff = pAdehazeCtx->PreDataV11.ISO - pAdehazeCtx->CurrDataV11.ISO;
            diff /= pAdehazeCtx->PreDataV11.ISO;
            if (diff >= pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara.ByPassThr ||
                diff <= (0 - pAdehazeCtx->AdehazeAtrrV11.stAuto.DehazeTuningPara.ByPassThr))
                pAdehazeCtx->byPassProc = false;
            else
                pAdehazeCtx->byPassProc = true;
        }
    }

    ret = pAdehazeCtx->byPassProc;

    LOGD_ADEHAZE("%s:FrameID:%d CtrlDataType:%d EnvLv:%f ISO:%f byPassProc:%d\n", __func__,
                 pAdehazeCtx->FrameID, pAdehazeCtx->CurrDataV11.CtrlDataType,
                 pAdehazeCtx->CurrDataV11.EnvLv, pAdehazeCtx->CurrDataV11.ISO, ret);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}
