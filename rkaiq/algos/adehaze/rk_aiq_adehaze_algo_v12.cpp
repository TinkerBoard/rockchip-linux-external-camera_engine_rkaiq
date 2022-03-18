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
#include "rk_aiq_adehaze_algo_v12.h"
#include <string.h>
#include "xcam_log.h"

int DehazeLinearInterpV12(const float* pX, const float* pY, float posx, int BitInt, int BitFloat,
                          int XSize) {
    int index;
    float yOut     = 0.0;
    int yOutInt    = 0;
    int yOutIntMax = (int)(pow(2, (BitFloat + BitInt)) - 1);
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

    yOutInt = LIMIT_VALUE((int)(yOut * pow(2, BitFloat)), yOutIntMax, yOutIntMin);

    return yOutInt;
}

float LinearInterpV12(const float* pX, const float* pY, float posx, int XSize) {
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

void EnableSettingV12(CalibDbDehazeV12_t* pCalibV12, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV12.enable = pCalibV12->Enable;

    bool dehaze_enable  = false;
    bool enhance_enable = false;
    if (pCalibV12->Enable) {
        if (pCalibV12->dehaze_setting.en && pCalibV12->enhance_setting.en) {
            pProcRes->ProcResV12.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV12.enhance_en = FUNCTION_ENABLE;
        } else if (pCalibV12->dehaze_setting.en && !pCalibV12->enhance_setting.en) {
            pProcRes->ProcResV12.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV12.enhance_en = FUNCTION_DISABLE;
        } else if (!pCalibV12->dehaze_setting.en && pCalibV12->enhance_setting.en) {
            pProcRes->ProcResV12.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV12.enhance_en = FUNCTION_ENABLE;
        } else {
            pProcRes->ProcResV12.dc_en      = FUNCTION_DISABLE;
            pProcRes->ProcResV12.enhance_en = FUNCTION_DISABLE;
        }

        if (pCalibV12->hist_setting.en)
            pProcRes->ProcResV12.hist_en = FUNCTION_ENABLE;
        else
            pProcRes->ProcResV12.hist_en = FUNCTION_DISABLE;
    } else {
        pProcRes->ProcResV12.dc_en      = FUNCTION_DISABLE;
        pProcRes->ProcResV12.enhance_en = FUNCTION_DISABLE;
        pProcRes->ProcResV12.hist_en    = FUNCTION_DISABLE;
    }
    dehaze_enable = (pProcRes->ProcResV12.dc_en & FUNCTION_ENABLE) &&
                    (!(pProcRes->ProcResV12.enhance_en & FUNCTION_ENABLE));
    enhance_enable = (pProcRes->ProcResV12.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV12.enhance_en & FUNCTION_ENABLE);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV12.enable, dehaze_enable, enhance_enable,
                 pProcRes->ProcResV12.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

int ClipValueV12(float posx, int BitInt, int BitFloat) {
    int yOutInt    = 0;
    int yOutIntMax = (int)(pow(2, (BitFloat + BitInt)) - 1);
    int yOutIntMin = 0;

    yOutInt = LIMIT_VALUE((int)(posx * pow(2, BitFloat)), yOutIntMax, yOutIntMin);

    return yOutInt;
}

void stManuEnableSettingV12(mDehazeAttrV12_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV12.enable = pStManu->Enable;

    bool dehaze_enable  = false;
    bool enhance_enable = false;
    if (pStManu->Enable) {
        if (pStManu->dehaze_setting.en && pStManu->enhance_setting.en) {
            pProcRes->ProcResV12.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV12.enhance_en = FUNCTION_ENABLE;
        } else if (pStManu->dehaze_setting.en && !pStManu->enhance_setting.en) {
            pProcRes->ProcResV12.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV12.enhance_en = FUNCTION_DISABLE;
        } else if (!pStManu->dehaze_setting.en && pStManu->enhance_setting.en) {
            pProcRes->ProcResV12.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV12.enhance_en = FUNCTION_ENABLE;
        } else {
            pProcRes->ProcResV12.dc_en      = FUNCTION_DISABLE;
            pProcRes->ProcResV12.enhance_en = FUNCTION_DISABLE;
        }

        if (pStManu->hist_setting.en)
            pProcRes->ProcResV12.hist_en = FUNCTION_ENABLE;
        else
            pProcRes->ProcResV12.hist_en = FUNCTION_DISABLE;
    } else {
        pProcRes->ProcResV12.dc_en      = FUNCTION_DISABLE;
        pProcRes->ProcResV12.enhance_en = FUNCTION_DISABLE;
        pProcRes->ProcResV12.hist_en    = FUNCTION_DISABLE;
    }
    dehaze_enable = (pProcRes->ProcResV12.dc_en & FUNCTION_ENABLE) &&
                    (!(pProcRes->ProcResV12.enhance_en & FUNCTION_ENABLE));
    enhance_enable = (pProcRes->ProcResV12.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV12.enhance_en & FUNCTION_ENABLE);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV12.enable, dehaze_enable, enhance_enable,
                 pProcRes->ProcResV12.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetDehazeParamsV12(mDehazeAttrV12_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes,
                              int rawWidth, int rawHeight) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV12.air_lc_en =
        pStManu->dehaze_setting.air_lc_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    pProcRes->ProcResV12.dc_min_th =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.dc_min_th, 8, 0);
    pProcRes->ProcResV12.dc_max_th =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.dc_max_th, 8, 0);
    pProcRes->ProcResV12.yhist_th = ClipValueV12(pStManu->dehaze_setting.DehazeData.yhist_th, 8, 0);
    pProcRes->ProcResV12.yblk_th  = int(pStManu->dehaze_setting.DehazeData.yblk_th *
                                       ((rawWidth + 15) / 16) * ((rawHeight + 15) / 16));
    pProcRes->ProcResV12.dark_th  = ClipValueV12(pStManu->dehaze_setting.DehazeData.dark_th, 8, 0);
    pProcRes->ProcResV12.bright_min =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.bright_min, 8, 0);
    pProcRes->ProcResV12.bright_max =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.bright_max, 8, 0);
    pProcRes->ProcResV12.wt_max  = ClipValueV12(pStManu->dehaze_setting.DehazeData.wt_max, 0, 8);
    pProcRes->ProcResV12.air_min = ClipValueV12(pStManu->dehaze_setting.DehazeData.air_min, 8, 0);
    pProcRes->ProcResV12.air_max = ClipValueV12(pStManu->dehaze_setting.DehazeData.air_max, 8, 0);
    pProcRes->ProcResV12.tmax_base =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.tmax_base, 8, 0);
    pProcRes->ProcResV12.tmax_off =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.tmax_off, 0, 10);
    pProcRes->ProcResV12.tmax_max =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.tmax_max, 0, 10);
    pProcRes->ProcResV12.cfg_wt  = ClipValueV12(pStManu->dehaze_setting.DehazeData.cfg_wt, 0, 8);
    pProcRes->ProcResV12.cfg_air = ClipValueV12(pStManu->dehaze_setting.DehazeData.cfg_air, 8, 0);
    pProcRes->ProcResV12.cfg_tmax =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.cfg_tmax, 0, 10);
    pProcRes->ProcResV12.range_sima =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.range_sigma, 0, 9);
    pProcRes->ProcResV12.space_sigma_cur =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.space_sigma_cur, 0, 8);
    pProcRes->ProcResV12.space_sigma_pre =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.space_sigma_pre, 0, 8);
    pProcRes->ProcResV12.bf_weight =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.bf_weight, 0, 8);
    pProcRes->ProcResV12.dc_weitcur =
        ClipValueV12(pStManu->dehaze_setting.DehazeData.dc_weitcur, 0, 8);
    pProcRes->ProcResV12.stab_fnum      = ClipValueV12(pStManu->dehaze_setting.stab_fnum, 5, 0);
    pProcRes->ProcResV12.iir_sigma      = ClipValueV12(pStManu->dehaze_setting.sigma, 8, 0);
    pProcRes->ProcResV12.iir_wt_sigma   = ClipValueV12(pStManu->dehaze_setting.wt_sigma 8, 3);
    pProcRes->ProcResV12.iir_air_sigma  = ClipValueV12(pStManu->dehaze_setting.air_sigma, 8, 0);
    pProcRes->ProcResV12.iir_tmax_sigma = ClipValueV12(pStManu->dehaze_setting.tmax_sigma, 0, 10);
    pProcRes->ProcResV12.iir_pre_wet    = ClipValueV12(pStManu->dehaze_setting.pre_wet, 0, 4);
    pProcRes->ProcResV12.gaus_h0        = DEHAZE_GAUS_H4;
    pProcRes->ProcResV12.gaus_h1        = DEHAZE_GAUS_H1;
    pProcRes->ProcResV12.gaus_h2        = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV12.dc_en && !(pProcRes->ProcResV12.enhance_en)) {
        if (pProcRes->ProcResV12.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:1 cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__,
                         pProcRes->ProcResV12.cfg_air / 1.0, pProcRes->ProcResV12.cfg_tmax / 1023.0,
                         pProcRes->ProcResV12.cfg_wt / 255.0);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x255 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n",
                         __func__, pProcRes->ProcResV12.cfg_air, pProcRes->ProcResV12.cfg_tmax,
                         pProcRes->ProcResV12.cfg_wt);
        } else if (pProcRes->ProcResV12.cfg_alpha == 0) {
            LOGD_ADEHAZE("%s cfg_alpha:0 air_max:%f air_min:%f tmax_base:%f wt_max:%f\n", __func__,
                         pProcRes->ProcResV12.air_max / 1.0, pProcRes->ProcResV12.air_min / 1.0,
                         pProcRes->ProcResV12.tmax_base / 1.0, pProcRes->ProcResV12.wt_max / 255.0);
            LOGD_ADEHAZE(
                "%s cfg_alpha_reg:0x0 air_max:0x%x air_min:0x%x tmax_base:0x%x wt_max:0x%x\n",
                __func__, pProcRes->ProcResV12.air_max, pProcRes->ProcResV12.air_min,
                pProcRes->ProcResV12.tmax_base, pProcRes->ProcResV12.wt_max);
        }
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetEnhanceParamsV12(mDehazeAttrV12_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV12.enhance_value =
        ClipValueV12(pStManu->enhance_setting.EnhanceData.enhance_value, 4, 10);
    pProcRes->ProcResV12.enhance_chroma =
        ClipValueV12(pStManu->enhance_setting.EnhanceData.enhance_chroma, 4, 10);

    for (int i = 0; i < DHAZ_V12_ENHANCE_CRUVE_NUM; i++)
        pProcRes->ProcResV12.enh_curve[i] = (int)(pStManu->enhance_setting.enhance_curve[i]);

    // dehaze v12 add
    pProcRes->ProcResV12.color_deviate_en = pStManu->enhance_setting.color_deviate_en;
    pProcRes->ProcResV12.enh_luma_en      = pStManu->enhance_setting.enh_luma_en;
    for (int i = 0; i < DHAZ_V12_ENH_LUMA_NUM; i++)
        pProcRes->ProcResV12.enh_luma[i] = (int)(pStManu->enhance_setting.enh_luma[i]);

    if (pProcRes->ProcResV12.dc_en && pProcRes->ProcResV12.enhance_en) {
        LOGD_ADEHAZE("%s color_deviate_en:%d enh_luma_en:%d\n", __func__,
                     pProcRes->ProcResV12.color_deviate_en, pProcRes->ProcResV12.enh_luma_en);
        LOGD_ADEHAZE("%s enhance_value:%f enhance_chroma:%f\n", __func__,
                     pStManu->enhance_setting.EnhanceData.enhance_value / 1024.0,
                     pStManu->enhance_setting.EnhanceData.enhance_chroma / 1024.0);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV12.enhance_value, pProcRes->ProcResV12.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetHistParamsV12(mDehazeAttrV12_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV12.hpara_en =
        pStManu->hist_setting.hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    // clip hpara_en
    pProcRes->ProcResV12.hpara_en =
        pProcRes->ProcResV12.dc_en ? pProcRes->ProcResV12.hpara_en : FUNCTION_ENABLE;

    pProcRes->ProcResV12.hist_gratio = ClipValueV12(pStManu->hist_setting.hist_gratio, 0, 8);
    pProcRes->ProcResV12.hist_th_off = ClipValueV12(pStManu->hist_setting.hist_th_off, 8, 0);
    pProcRes->ProcResV12.hist_k      = ClipValueV12(pStManu->hist_setting.hist_k, 3, 2);
    pProcRes->ProcResV12.hist_min    = ClipValueV12(pStManu->hist_setting.hist_min, 1, 8);
    pProcRes->ProcResV12.cfg_gratio  = ClipValueV12(pStManu->hist_setting.cfg_gratio, 5, 8);
    pProcRes->ProcResV12.hist_scale  = ClipValueV12(pStManu->hist_setting.hist_scale, 5, 8);

    if (pProcRes->ProcResV12.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f "
            "hist_min:%f hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV12.cfg_alpha / 255.0, pProcRes->ProcResV12.hpara_en,
            pProcRes->ProcResV12.hist_gratio / 255.0, pProcRes->ProcResV12.hist_th_off / 1.0,
            pProcRes->ProcResV12.hist_k / 4.0, pProcRes->ProcResV12.hist_min / 256.0,
            pProcRes->ProcResV12.hist_scale / 256.0, pProcRes->ProcResV12.cfg_gratio / 256.0);
        LOGD_ADEHAZE(
            "%s cfg_alpha_reg:0x%x hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x "
            "hist_min_reg:0x%x hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n",
            __func__, pProcRes->ProcResV12.cfg_alpha, pProcRes->ProcResV12.hist_gratio,
            pProcRes->ProcResV12.hist_th_off, pProcRes->ProcResV12.hist_k,
            pProcRes->ProcResV12.hist_min, pProcRes->ProcResV12.hist_scale,
            pProcRes->ProcResV12.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeParamsV12(CalibDbDehazeV12_t* pCalibV12, RkAiqAdehazeProcResult_t* pProcRes,
                        int rawWidth, int rawHeight, float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV12.air_lc_en =
        pCalibV12->dehaze_setting.air_lc_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    pProcRes->ProcResV12.dc_min_th = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.dc_min_th,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.dc_max_th = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.dc_max_th,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.yhist_th = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.yhist_th,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.yblk_th =
        LinearInterpV12(pCalibV12->dehaze_setting.DehazeData.EnvLv,
                        pCalibV12->dehaze_setting.DehazeData.yblk_th, CtrlValue,
                        pCalibV12->dehaze_setting.DehazeData.EnvLv_len) *
        ((rawWidth + 15) / 16) * ((rawHeight + 15) / 16);
    pProcRes->ProcResV12.dark_th = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.dark_th,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.bright_min = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.bright_min,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.bright_max = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.bright_max,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.wt_max = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.wt_max,
        CtrlValue, 0, 8, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.air_min = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.air_min,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.air_max = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.air_max,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.tmax_base = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.tmax_base,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.tmax_off = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.tmax_off,
        CtrlValue, 0, 10, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.tmax_max = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.tmax_max,
        CtrlValue, 0, 10, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.cfg_wt = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.cfg_wt,
        CtrlValue, 0, 8, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.cfg_air = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.cfg_air,
        CtrlValue, 8, 0, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.cfg_tmax = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.cfg_tmax,
        CtrlValue, 0, 10, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.range_sima =
        DehazeLinearInterpV12(pCalibV12->dehaze_setting.DehazeData.EnvLv,
                              pCalibV12->dehaze_setting.DehazeData.range_sigma, CtrlValue, 0, 9,
                              pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.space_sigma_cur =
        DehazeLinearInterpV12(pCalibV12->dehaze_setting.DehazeData.EnvLv,
                              pCalibV12->dehaze_setting.DehazeData.space_sigma_cur, CtrlValue, 0, 8,
                              pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.space_sigma_pre =
        DehazeLinearInterpV12(pCalibV12->dehaze_setting.DehazeData.EnvLv,
                              pCalibV12->dehaze_setting.DehazeData.space_sigma_pre, CtrlValue, 0, 8,
                              pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.bf_weight = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.bf_weight,
        CtrlValue, 0, 8, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.dc_weitcur = DehazeLinearInterpV12(
        pCalibV12->dehaze_setting.DehazeData.EnvLv, pCalibV12->dehaze_setting.DehazeData.dc_weitcur,
        CtrlValue, 0, 8, pCalibV12->dehaze_setting.DehazeData.EnvLv_len);
    pProcRes->ProcResV12.stab_fnum      = ClipValueV12(pCalibV12->dehaze_setting.stab_fnum, 5, 0);
    pProcRes->ProcResV12.iir_sigma      = ClipValueV12(pCalibV12->dehaze_setting.sigma, 8, 0);
    pProcRes->ProcResV12.iir_wt_sigma   = ClipValueV12(pCalibV12->dehaze_setting.wt_sigma 8, 3);
    pProcRes->ProcResV12.iir_air_sigma  = ClipValueV12(pCalibV12->dehaze_setting.air_sigma, 8, 0);
    pProcRes->ProcResV12.iir_tmax_sigma = ClipValueV12(pCalibV12->dehaze_setting.tmax_sigma, 0, 10);
    pProcRes->ProcResV12.iir_pre_wet    = ClipValueV12(pCalibV12->dehaze_setting.pre_wet, 0, 4);
    pProcRes->ProcResV12.gaus_h0        = DEHAZE_GAUS_H4;
    pProcRes->ProcResV12.gaus_h1        = DEHAZE_GAUS_H1;
    pProcRes->ProcResV12.gaus_h2        = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV12.dc_en && !(pProcRes->ProcResV12.enhance_en)) {
        if (pProcRes->ProcResV12.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:1 EnvLv:%f cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__,
                         CtrlValue, pProcRes->ProcResV12.cfg_air / 1.0,
                         pProcRes->ProcResV12.cfg_tmax / 1023.0,
                         pProcRes->ProcResV12.cfg_wt / 255.0);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x255 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n",
                         __func__, pProcRes->ProcResV12.cfg_air, pProcRes->ProcResV12.cfg_tmax,
                         pProcRes->ProcResV12.cfg_wt);
        } else if (pProcRes->ProcResV12.cfg_alpha == 0) {
            LOGD_ADEHAZE("%s cfg_alpha:0 EnvLv:%f air_max:%f air_min:%f tmax_base:%f wt_max:%f\n",
                         __func__, CtrlValue, pProcRes->ProcResV12.air_max / 1.0,
                         pProcRes->ProcResV12.air_min / 1.0, pProcRes->ProcResV12.tmax_base / 1.0,
                         pProcRes->ProcResV12.wt_max / 255.0);
            LOGD_ADEHAZE(
                "%s cfg_alpha_reg:0x0 air_max:0x%x air_min:0x%x tmax_base:0x%x wt_max:0x%x\n",
                __func__, pProcRes->ProcResV12.air_max, pProcRes->ProcResV12.air_min,
                pProcRes->ProcResV12.tmax_base, pProcRes->ProcResV12.wt_max);
        }
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetEnhanceParamsV12(CalibDbDehazeV12_t* pCalibV12, RkAiqAdehazeProcResult_t* pProcRes,
                         float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV12.enhance_value =
        DehazeLinearInterpV12(pCalibV12->enhance_setting.EnhanceData.EnvLv,
                              pCalibV12->enhance_setting.EnhanceData.enhance_value, CtrlValue, 4,
                              10, pCalibV12->enhance_setting.EnhanceData.EnvLv_len);
    pProcRes->ProcResV12.enhance_chroma =
        DehazeLinearInterpV12(pCalibV12->enhance_setting.EnhanceData.EnvLv,
                              pCalibV12->enhance_setting.EnhanceData.enhance_chroma, CtrlValue, 4,
                              10, pCalibV12->enhance_setting.EnhanceData.EnvLv_len);

    for (int i = 0; i < DHAZ_V12_ENHANCE_CRUVE_NUM; i++)
        pProcRes->ProcResV12.enh_curve[i] = (int)(pCalibV12->enhance_setting.enhance_curve[i]);

    // dehaze v12 add
    pProcRes->ProcResV12.color_deviate_en =
        pCalibV12->enhance_setting.color_deviate_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    pProcRes->ProcResV12.enh_luma_en =
        pCalibV12->enhance_setting.enh_luma_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    for (int i = 0; i < DHAZ_V12_ENH_LUMA_NUM; i++)
        pProcRes->ProcResV12.enh_luma[i] = (int)(pCalibV12->enhance_setting.enh_luma[i]);

    if (pProcRes->ProcResV12.dc_en && pProcRes->ProcResV12.enhance_en) {
        LOGD_ADEHAZE("%s color_deviate_en:%d enh_luma_en:%d\n", __func__,
                     pProcRes->ProcResV12.color_deviate_en, pProcRes->ProcResV12.enh_luma_en);
        LOGD_ADEHAZE("%s EnvLv:%f enhance_value:%f enhance_chroma:%f\n", __func__, CtrlValue,
                     pProcRes->ProcResV12.enhance_value / 1024.0,
                     pProcRes->ProcResV12.enhance_chroma / 1024.0);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV12.enhance_value, pProcRes->ProcResV12.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetHistParamsV12(CalibDbDehazeV12_t* pCalibV12, RkAiqAdehazeProcResult_t* pProcRes,
                      float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV12.hpara_en =
        pCalibV12->hist_setting.hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;
    // clip hpara_en
    pProcRes->ProcResV12.hpara_en = pProcRes->ProcResV12.dc_en
                                        ? pProcRes->ProcResV12.hpara_en
                                        : FUNCTION_ENABLE;  //  dc en �رգ�hpara���迪

    pProcRes->ProcResV12.hist_gratio = DehazeLinearInterpV12(
        pCalibV12->hist_setting.HistData.EnvLv, pCalibV12->hist_setting.HistData.hist_gratio,
        CtrlValue, 0, 8, pCalibV12->hist_setting.HistData.EnvLv_len);
    pProcRes->ProcResV12.hist_th_off = DehazeLinearInterpV12(
        pCalibV12->hist_setting.HistData.EnvLv, pCalibV12->hist_setting.HistData.hist_th_off,
        CtrlValue, 8, 0, pCalibV12->hist_setting.HistData.EnvLv_len);
    pProcRes->ProcResV12.hist_k = DehazeLinearInterpV12(
        pCalibV12->hist_setting.HistData.EnvLv, pCalibV12->hist_setting.HistData.hist_k, CtrlValue,
        3, 2, pCalibV12->hist_setting.HistData.EnvLv_len);
    pProcRes->ProcResV12.hist_min = DehazeLinearInterpV12(
        pCalibV12->hist_setting.HistData.EnvLv, pCalibV12->hist_setting.HistData.hist_min,
        CtrlValue, 1, 8, pCalibV12->hist_setting.HistData.EnvLv_len);
    pProcRes->ProcResV12.cfg_gratio = DehazeLinearInterpV12(
        pCalibV12->hist_setting.HistData.EnvLv, pCalibV12->hist_setting.HistData.cfg_gratio,
        CtrlValue, 5, 8, pCalibV12->hist_setting.HistData.EnvLv_len);
    pProcRes->ProcResV12.hist_scale = DehazeLinearInterpV12(
        pCalibV12->hist_setting.HistData.EnvLv, pCalibV12->hist_setting.HistData.hist_scale,
        CtrlValue, 5, 8, pCalibV12->hist_setting.HistData.EnvLv_len);

    if (pProcRes->ProcResV12.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f EnvLv:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f "
            "hist_min:%f hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV12.cfg_alpha / 255.0, CtrlValue,
            pProcRes->ProcResV12.hpara_en, pProcRes->ProcResV12.hist_gratio / 255.0,
            pProcRes->ProcResV12.hist_th_off / 1.0, pProcRes->ProcResV12.hist_k / 4.0,
            pProcRes->ProcResV12.hist_min / 256.0, pProcRes->ProcResV12.hist_scale / 256.0,
            pProcRes->ProcResV12.cfg_gratio / 256.0);
        LOGD_ADEHAZE(
            "%s cfg_alpha_reg:0x%x hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x "
            "hist_min_reg:0x%x hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n",
            __func__, pProcRes->ProcResV12.cfg_alpha, pProcRes->ProcResV12.hist_gratio,
            pProcRes->ProcResV12.hist_th_off, pProcRes->ProcResV12.hist_k,
            pProcRes->ProcResV12.hist_min, pProcRes->ProcResV12.hist_scale,
            pProcRes->ProcResV12.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeHistDuoISPSettingV12(RkAiqAdehazeProcResult_t* pProcRes,
                                   rkisp_adehaze_stats_t* pStats, bool DuoCamera, int FrameID) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    // round_en
    pProcRes->ProcResV12.round_en = FUNCTION_ENABLE;

    // deahze duo setting
    if (DuoCamera) {
        pProcRes->ProcResV12.soft_wr_en = FUNCTION_ENABLE;
        // support default value for kernel calc
        for (int i = 0; i < DHAZ_V12_HIST_WR_NUM; i++) {
            pProcRes->ProcResV12.hist_wr[i] = 16 * (i + 1);
            pProcRes->ProcResV12.hist_wr[i] =
                pProcRes->ProcResV12.hist_wr[i] > 1023 ? 1023 : pProcRes->ProcResV12.hist_wr[i];
        }
        LOGD_ADEHAZE("%s DuoCamera:%d soft_wr_en:%d\n", __func__, DuoCamera,
                     pProcRes->ProcResV12.soft_wr_en);
    } else
        pProcRes->ProcResV12.soft_wr_en = FUNCTION_DISABLE;

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

XCamReturn GetDehazeLocalGainSettingV12(RkAiqAdehazeProcResult_t* pProcRes,
                                        CalibDbV2_YnrV3_CalibPara_t* pYnrCalib, float ISO,
                                        YnrSnrMode_t SnrMode) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    if (pYnrCalib->Setting_len >= 1 && SnrMode <= pYnrCalib->Setting_len) {
        if (pYnrCalib->Setting[SnrMode].Calib_ISO_len >= 1) {
            // get iso knots and ratio
            float ISO_lo    = ISOMIN;
            float ISO_hi    = ISOMIN;
            float ratio     = 1.0;
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
            float* noiseSigma_lo = (float*)calloc(DHAZ_V12_SIGMA_LUT_NUM, sizeof(float));
            if (NULL == noiseSigma_lo) return XCAM_RETURN_ERROR_MEM;
            float* noiseSigma_hi = (float*)calloc(DHAZ_V12_SIGMA_LUT_NUM, sizeof(float));
            if (NULL == noiseSigma_hi) return XCAM_RETURN_ERROR_MEM;
            float* noiseSigma = (float*)calloc(DHAZ_V12_SIGMA_LUT_NUM, sizeof(float));
            if (NULL == noiseSigma) return XCAM_RETURN_ERROR_MEM;
            for (int i = 0; i < DHAZ_V12_SIGMA_LUT_NUM; i++) {
                float ave1, ave2, ave3, ave4;
                if (i == (DHAZ_V12_SIGMA_LUT_NUM - 1))
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
            for (int i = 0; i < DHAZ_V12_SIGMA_IDX_NUM; i++)
                pProcRes->ProcResV12.sigma_idx[i] = (i + 1) * YNR_CURVE_STEP;

            // get sigma_lut
            int tmp = 0;
            for (int i = 0; i < DHAZ_V12_SIGMA_LUT_NUM; i++) {
                tmp                               = LIMIT_VALUE(noiseSigma[i], BIT_10_MAX, BIT_MIN);
                pProcRes->ProcResV12.sigma_lut[i] = tmp;
            }

            free(noiseSigma);
            free(noiseSigma_lo);
            free(noiseSigma_hi);

#if 0
            LOGE_ADEHAZE("%s(%d) ISO:%f SnrMode:%d ISO_lo:%f ISO_hi:%f\n", __func__, __LINE__, ISO, SnrMode, ISO_lo, ISO_hi);
            LOGE_ADEHAZE("%s(%d) dehaze local gain IDX(0~5): 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n", __func__, __LINE__, ppProcRes->ProcResV12.sigma_idx[0], ppProcRes->ProcResV12.sigma_idx[1],
                         ppProcRes->ProcResV12.sigma_idx[2], ppProcRes->ProcResV12.sigma_idx[3], ppProcRes->ProcResV12.sigma_idx[4], ppProcRes->ProcResV12.sigma_idx[5]);
            LOGE_ADEHAZE("%s(%d) dehaze local gain LUT(0~5): 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n", __func__, __LINE__, ppProcRes->ProcResV12.sigma_lut[0], ppProcRes->ProcResV12.sigma_lut[1],
                         ppProcRes->ProcResV12.sigma_lut[2], ppProcRes->ProcResV12.sigma_lut[3], ppProcRes->ProcResV12.sigma_lut[4], ppProcRes->ProcResV12.sigma_lut[5]);
#endif
        } else
            LOGE_ADEHAZE("%s(%d) Ynr calib setting ISO length is under 1!!!\n", __func__, __LINE__);
    } else
        LOGE_ADEHAZE("%s(%d) Ynr calib setting length is under 1!!!\n", __func__, __LINE__);

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
    for (int i = 0; i < DHAZ_V12_HIST_WR_NUM; i++)
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
    for (int i = 0; i < DHAZ_V12_HIST_WR_NUM; i++)
        LOGV_ADEHAZE("%s:  h_rgb_iir[%d]:%d:\n", __FUNCTION__, i,
                     pAdehazeCtx->stats.dehaze_stats_v11_duo.h_rgb_iir[i]);

    // get other stats from stats
    for (int i = 0; i < 225; i++) {
        pAdehazeCtx->stats.other_stats.short_luma[i] = ROData->other_stats.short_luma[i];
        pAdehazeCtx->stats.other_stats.long_luma[i]  = ROData->other_stats.long_luma[i];
        pAdehazeCtx->stats.other_stats.tmo_luma[i]   = ROData->other_stats.tmo_luma[i];
    }

    if (pAdehazeCtx->FrameNumber == HDR_3X_NUM) {
        for (int i = 0; i < 25; i++)
            pAdehazeCtx->stats.other_stats.middle_luma[i] = ROData->other_stats.middle_luma[i];
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

void AdehazeGetCurrDataGroup(AdehazeHandle_t* pAdehazeCtx, RKAiqAecExpInfo_t* pAeEffExpo,
                             XCamVideoBuffer* pAePreRes) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);

    RkAiqAlgoPreResAe* pAEPreRes = NULL;
    if (pAePreRes) {
        pAEPreRes = (RkAiqAlgoPreResAe*)pAePreRes->map(pAePreRes);

        pAdehazeCtx->CurrDataV12.EnvLv =
            pAEPreRes->ae_pre_res_rk.GlobalEnvLv[pAEPreRes->ae_pre_res_rk.NormalIndex];

        // Normalize the current envLv for AEC
        pAdehazeCtx->CurrDataV12.EnvLv =
            (pAdehazeCtx->CurrDataV12.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
        pAdehazeCtx->CurrDataV12.EnvLv =
            LIMIT_VALUE(pAdehazeCtx->CurrDataV12.EnvLv, ENVLVMAX, ENVLVMIN);

        // get iso
        if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
            pAdehazeCtx->CurrDataV12.ISO =
                pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.analog_gain *
                pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.digital_gain * 50.0;
        else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
            pAdehazeCtx->CurrDataV12.ISO =
                pAEPreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.analog_gain *
                pAEPreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.digital_gain * 50.0;
    } else {
        pAdehazeCtx->CurrDataV12.EnvLv = ENVLVMIN;
        LOGE_ADEHAZE("%s:PreResBuf is NULL!\n", __FUNCTION__);
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

void AdehazeGetCurrData(AdehazeHandle_t* pAdehazeCtx, RkAiqAlgoProcAdhaz* pProcPara) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);

    XCamVideoBuffer* xCamAePreRes = pProcPara->com.u.proc.res_comb->ae_pre_res;
    RkAiqAlgoPreResAe* pAEPreRes  = NULL;
    if (xCamAePreRes) {
        pAEPreRes = (RkAiqAlgoPreResAe*)xCamAePreRes->map(xCamAePreRes);

        pAdehazeCtx->CurrDataV12.EnvLv =
            pAEPreRes->ae_pre_res_rk.GlobalEnvLv[pAEPreRes->ae_pre_res_rk.NormalIndex];
        // Normalize the current envLv for AEC
        pAdehazeCtx->CurrDataV12.EnvLv =
            (pAdehazeCtx->CurrDataV12.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
        pAdehazeCtx->CurrDataV12.EnvLv =
            LIMIT_VALUE(pAdehazeCtx->CurrDataV12.EnvLv, ENVLVMAX, ENVLVMIN);

        // get iso
        if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
            pAdehazeCtx->CurrDataV12.ISO =
                pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.analog_gain *
                pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.digital_gain * 50.0;
        else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
            pAdehazeCtx->CurrDataV12.ISO =
                pAEPreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.analog_gain *
                pAEPreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.digital_gain * 50.0;
    } else {
        pAdehazeCtx->CurrDataV12.EnvLv = ENVLVMIN;
        pAdehazeCtx->CurrDataV12.ISO   = ISOMIN;
        LOGE_ADEHAZE("%s:PreResBuf is NULL!\n", __FUNCTION__);
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

XCamReturn AdehazeInit(AdehazeHandle_t** pAdehazeCtx, CamCalibDbV2Context_t* pCalib) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret          = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t* handle = (AdehazeHandle_t*)calloc(1, sizeof(AdehazeHandle_t));

    CalibDbV2_dehaze_V12_t* calibv2_adehaze_calib_V12 =
        (CalibDbV2_dehaze_V12_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, adehaze_calib));
    memcpy(&handle->CalibV12.DehazeTuningPara, &calibv2_adehaze_calib_V12->DehazeTuningPara,
           sizeof(CalibDbDehazeV12_t));  // load iq
    memcpy(&handle->AdehazeAtrrV12.stAuto, calibv2_adehaze_calib_V12,
           sizeof(CalibDbV2_dehaze_V12_t));  // set defsult stAuto

    // set when ynr is done
    /*
    //dehaze local gain
    CalibDbV2_YnrV3_t*  calibv2_Ynr =
        (CalibDbV2_YnrV3_t *)(CALIBDBV2_GET_MODULE_PTR(pCalib, ynr_v3));
    memcpy(&handle->CalibV12.YnrCalibPara, &calibv2_Ynr->CalibPara,
    sizeof(CalibDbV2_YnrV3_CalibPara_t));
*/
    handle->PreDataV12.EnvLv   = ENVLVMIN;
    handle->PreDataV12.ApiMode = DEHAZE_API_AUTO;

    // set api default
    handle->AdehazeAtrrV12.mode                                               = DEHAZE_API_AUTO;
    handle->AdehazeAtrrV12.stManual.Enable                                    = true;
    handle->AdehazeAtrrV12.stManual.cfg_alpha                                 = 1.0;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.en                         = false;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.air_lc_en                  = true;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.stab_fnum                  = 8;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.sigma                      = 6;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.wt_sigma                   = 8;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.air_sigma                  = 120;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.tmax_sigma                 = 0.01;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.pre_wet                    = 0.01;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.dc_min_th       = 64;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.dc_max_th       = 192;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.yhist_th        = 249;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.yblk_th         = 0.002;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.dark_th         = 250;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.bright_min      = 180;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.bright_max      = 240;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.wt_max          = 0.9;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.air_min         = 200;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.air_max         = 250;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.tmax_base       = 125;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.tmax_off        = 0.1;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.tmax_max        = 0.8;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.cfg_wt          = 0.8;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.cfg_air         = 210;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.cfg_tmax        = 0.2;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.dc_weitcur      = 1;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.bf_weight       = 0.5;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.range_sigma     = 0.14;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.space_sigma_pre = 0.14;
    handle->AdehazeAtrrV12.stManual.dehaze_setting.DehazeData.space_sigma_cur = 0.14;

    handle->AdehazeAtrrV12.stManual.enhance_setting.en                         = true;
    handle->AdehazeAtrrV12.stManual.enhance_setting.color_deviate_en           = false;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma_en                = false;
    handle->AdehazeAtrrV12.stManual.enhance_setting.EnhanceData.enhance_value  = 1.0;
    handle->AdehazeAtrrV12.stManual.enhance_setting.EnhanceData.enhance_chroma = 1.0;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[0]           = 0;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[1]           = 64;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[2]           = 128;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[3]           = 192;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[4]           = 256;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[5]           = 320;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[6]           = 384;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[7]           = 448;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[8]           = 512;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[9]           = 576;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[10]          = 640;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[11]          = 704;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[12]          = 768;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[13]          = 832;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[14]          = 896;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[15]          = 960;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enhance_curve[16]          = 1023;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[0]                = 0;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[1]                = 64;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[2]                = 128;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[3]                = 192;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[4]                = 256;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[5]                = 320;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[6]                = 384;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[7]                = 448;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[8]                = 512;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[9]                = 576;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[10]               = 640;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[11]               = 704;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[12]               = 768;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[13]               = 832;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[14]               = 896;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[15]               = 960;
    handle->AdehazeAtrrV12.stManual.enhance_setting.enh_luma[16]               = 1023;

    handle->AdehazeAtrrV12.stManual.hist_setting.en                   = false;
    handle->AdehazeAtrrV12.stManual.hist_setting.hist_para_en         = true;
    handle->AdehazeAtrrV12.stManual.hist_setting.HistData.hist_gratio = 2;
    handle->AdehazeAtrrV12.stManual.hist_setting.HistData.hist_th_off = 64;
    handle->AdehazeAtrrV12.stManual.hist_setting.HistData.hist_k      = 2;
    handle->AdehazeAtrrV12.stManual.hist_setting.HistData.hist_min    = 0.015;
    handle->AdehazeAtrrV12.stManual.hist_setting.HistData.hist_scale  = 0.09;
    handle->AdehazeAtrrV12.stManual.hist_setting.HistData.cfg_gratio  = 2;

    handle->AdehazeAtrrV12.Info.ISO                 = ISOMIN;
    handle->AdehazeAtrrV12.Info.EnvLv               = ENVLVMIN;
    handle->AdehazeAtrrV12.Info.MDehazeStrth        = DEHAZE_API_MANUAL_DEFAULT_LEVEL;
    handle->AdehazeAtrrV12.Info.MEnhanceStrth       = DEHAZE_API_ENHANCE_MANUAL_DEFAULT_LEVEL;
    handle->AdehazeAtrrV12.Info.MEnhanceChromeStrth = DEHAZE_API_ENHANCE_MANUAL_DEFAULT_LEVEL;

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

    if (pAdehazeCtx->AdehazeAtrrV12.mode == DEHAZE_API_AUTO) {
        LOGD_ADEHAZE(" %s: Adehaze Api stAuto!!!\n", __func__);
        float CtrlValue = pAdehazeCtx->CurrDataV12.EnvLv;
        // cfg setting
        pAdehazeCtx->ProcRes.ProcResV12.cfg_alpha =
            LIMIT_VALUE(SHIFT8BIT(pAdehazeCtx->AdehazeAtrrV12.stAuto.DehazeTuningPara.cfg_alpha),
                        BIT_8_MAX, BIT_MIN);

        // enable setting
        EnableSettingV12(&pAdehazeCtx->AdehazeAtrrV12.stAuto.DehazeTuningPara,
                         &pAdehazeCtx->ProcRes);

        // dehaze setting
        GetDehazeParamsV12(&pAdehazeCtx->AdehazeAtrrV12.stAuto.DehazeTuningPara,
                           &pAdehazeCtx->ProcRes, pAdehazeCtx->width, pAdehazeCtx->height,
                           CtrlValue);

        // enhance setting
        GetEnhanceParamsV12(&pAdehazeCtx->AdehazeAtrrV12.stAuto.DehazeTuningPara,
                            &pAdehazeCtx->ProcRes, CtrlValue);

        // hist setting
        GetHistParamsV12(&pAdehazeCtx->AdehazeAtrrV12.stAuto.DehazeTuningPara,
                         &pAdehazeCtx->ProcRes, CtrlValue);
    } else if (pAdehazeCtx->AdehazeAtrrV12.mode == DEHAZE_API_MANUAL) {
        LOGD_ADEHAZE(" %s: Adehaze Api stManual!!!\n", __func__);
        // cfg setting
        pAdehazeCtx->ProcRes.ProcResV12.cfg_alpha = LIMIT_VALUE(
            SHIFT8BIT(pAdehazeCtx->AdehazeAtrrV12.stManual.cfg_alpha), BIT_8_MAX, BIT_MIN);

        // enable setting
        stManuEnableSettingV12(&pAdehazeCtx->AdehazeAtrrV12.stManual, &pAdehazeCtx->ProcRes);

        // dehaze setting
        stManuGetDehazeParamsV12(&pAdehazeCtx->AdehazeAtrrV12.stManual, &pAdehazeCtx->ProcRes,
                                 pAdehazeCtx->width, pAdehazeCtx->height);

        // enhance setting
        stManuGetEnhanceParamsV12(&pAdehazeCtx->AdehazeAtrrV12.stManual, &pAdehazeCtx->ProcRes);

        // hist setting
        stManuGetHistParamsV12(&pAdehazeCtx->AdehazeAtrrV12.stManual, &pAdehazeCtx->ProcRes);
    } else
        LOGE_ADEHAZE("%s:Wrong Adehaze API mode!!! \n", __func__);

    // get Duo cam setting
    GetDehazeHistDuoISPSettingV12(&pAdehazeCtx->ProcRes, &pAdehazeCtx->stats,
                                  pAdehazeCtx->is_multi_isp_mode, pAdehazeCtx->FrameID);

    // set when ynr is done
    // get local gain setting
    // ret = GetDehazeLocalGainSettingV12(&pAdehazeCtx->ProcRes,
    // &pAdehazeCtx->CalibV12.YnrCalibPara, pAdehazeCtx->CurrDataV12.ISO,
    // pAdehazeCtx->CurrDataV12.SnrMode);

    // store pre data
    pAdehazeCtx->PreDataV12.EnvLv = pAdehazeCtx->CurrDataV12.EnvLv;
    pAdehazeCtx->PreDataV12.ISO     = pAdehazeCtx->CurrDataV12.ISO;
    pAdehazeCtx->PreDataV12.ApiMode = pAdehazeCtx->CurrDataV12.ApiMode;

    // store api info
    pAdehazeCtx->AdehazeAtrrV12.Info.ISO   = pAdehazeCtx->CurrDataV12.ISO;
    pAdehazeCtx->AdehazeAtrrV12.Info.EnvLv = pAdehazeCtx->CurrDataV12.EnvLv;

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}

bool AdehazeByPassProcessing(AdehazeHandle_t* pAdehazeCtx) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    bool ret   = false;
    float diff = 0.0;

    if (pAdehazeCtx->FrameID <= 2) pAdehazeCtx->byPassProc = false;
    if (pAdehazeCtx->AdehazeAtrrV12.mode > DEHAZE_API_AUTO)
        pAdehazeCtx->byPassProc = false;
    else if (pAdehazeCtx->AdehazeAtrrV12.mode != pAdehazeCtx->PreDataV12.ApiMode)
        pAdehazeCtx->byPassProc = false;
    else {
        diff = pAdehazeCtx->PreDataV12.EnvLv - pAdehazeCtx->CurrDataV12.EnvLv;
        if (pAdehazeCtx->PreDataV12.EnvLv == ENVLVMIN) {
            diff = pAdehazeCtx->CurrDataV12.EnvLv;
            if (diff == 0.0)
                pAdehazeCtx->byPassProc = true;
            else
                pAdehazeCtx->byPassProc = false;
        } else {
            diff /= pAdehazeCtx->PreDataV12.EnvLv;
            if (diff >= pAdehazeCtx->CalibV12.DehazeTuningPara.ByPassThr ||
                diff <= (0 - pAdehazeCtx->CalibV12.DehazeTuningPara.ByPassThr))
                pAdehazeCtx->byPassProc = false;
            else
                pAdehazeCtx->byPassProc = true;
        }
    }

    ret = pAdehazeCtx->byPassProc;

    LOGD_ADEHAZE("%s:FrameID:%d byPassProc:%d ISO:%f\n", __func__, pAdehazeCtx->FrameID, ret,
                 pAdehazeCtx->CurrDataV12.ISO);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}