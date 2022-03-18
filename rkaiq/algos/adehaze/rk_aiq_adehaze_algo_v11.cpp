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

    bool dehaze_enable  = false;
    bool enhance_enable = false;
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
    dehaze_enable = (pProcRes->ProcResV11.dc_en & FUNCTION_ENABLE) &&
                    (!(pProcRes->ProcResV11.enhance_en & FUNCTION_ENABLE));
    enhance_enable = (pProcRes->ProcResV11.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV11.enhance_en & FUNCTION_ENABLE);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV11.enable, dehaze_enable, enhance_enable,
                 pProcRes->ProcResV11.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuEnableSettingV11(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11.enable = pStManu->Enable;

    bool dehaze_enable  = false;
    bool enhance_enable = false;
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
    dehaze_enable = (pProcRes->ProcResV11.dc_en & FUNCTION_ENABLE) &&
                    (!(pProcRes->ProcResV11.enhance_en & FUNCTION_ENABLE));
    enhance_enable = (pProcRes->ProcResV11.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV11.enhance_en & FUNCTION_ENABLE);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV11.enable, dehaze_enable, enhance_enable,
                 pProcRes->ProcResV11.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetDehazeParamsV11(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    bool air_lc_en = pStManu->dehaze_setting.air_lc_en;

    // dehaze_self_adp[7]
    float dc_min_th  = pStManu->dehaze_setting.DehazeData.dc_min_th;
    float dc_max_th  = pStManu->dehaze_setting.DehazeData.dc_max_th;
    float yhist_th   = pStManu->dehaze_setting.DehazeData.yhist_th;
    float yblk_th    = pStManu->dehaze_setting.DehazeData.yblk_th;
    float dark_th    = pStManu->dehaze_setting.DehazeData.dark_th;
    float bright_min = pStManu->dehaze_setting.DehazeData.bright_min;
    float bright_max = pStManu->dehaze_setting.DehazeData.bright_max;

    // dehaze_range_adj[6]
    float wt_max    = pStManu->dehaze_setting.DehazeData.wt_max;
    float air_max   = pStManu->dehaze_setting.DehazeData.air_max;
    float air_min   = pStManu->dehaze_setting.DehazeData.air_min;
    float tmax_base = pStManu->dehaze_setting.DehazeData.tmax_base;
    float tmax_off  = pStManu->dehaze_setting.DehazeData.tmax_off;
    float tmax_max  = pStManu->dehaze_setting.DehazeData.tmax_max;

    // dehaze_iir_control[5]
    float stab_fnum  = pStManu->dehaze_setting.stab_fnum;
    float sigma      = pStManu->dehaze_setting.sigma;
    float wt_sigma   = pStManu->dehaze_setting.wt_sigma;
    float air_sigma  = pStManu->dehaze_setting.air_sigma;
    float tmax_sigma = pStManu->dehaze_setting.tmax_sigma;
    float pre_wet    = pStManu->dehaze_setting.pre_wet;

    float cfg_wt   = pStManu->dehaze_setting.DehazeData.cfg_wt;
    float cfg_air  = pStManu->dehaze_setting.DehazeData.cfg_air;
    float cfg_tmax = pStManu->dehaze_setting.DehazeData.cfg_tmax;

    float range_sigma     = pStManu->dehaze_setting.DehazeData.range_sigma;
    float space_sigma_cur = pStManu->dehaze_setting.DehazeData.space_sigma_cur;
    float space_sigma_pre = pStManu->dehaze_setting.DehazeData.space_sigma_pre;

    // dehaze_bi_pAdehazeCtx[4]
    float bf_weight  = pStManu->dehaze_setting.DehazeData.bf_weight;
    float dc_weitcur = pStManu->dehaze_setting.DehazeData.dc_weitcur;

    int rawWidth                    = 1920;
    int rawHeight                   = 1080;
    pProcRes->ProcResV11.air_lc_en  = air_lc_en ? 1 : 0;  // air_lc_en
    pProcRes->ProcResV11.dc_min_th  = int(dc_min_th);     // 0~255, (8bit) dc_min_th
    pProcRes->ProcResV11.dc_max_th  = int(dc_max_th);     // 0~255, (8bit) dc_max_th
    pProcRes->ProcResV11.yhist_th   = int(yhist_th);      // 0~255, (8bit) yhist_th
    pProcRes->ProcResV11.yblk_th    = int(yblk_th * ((rawWidth + 15) / 16) *
                                       ((rawHeight + 15) / 16));  // default:28,(9bit) yblk_th
    pProcRes->ProcResV11.dark_th    = int(dark_th);                  // 0~255, (8bit) dark_th
    pProcRes->ProcResV11.bright_min = int(bright_min);               // 0~255, (8bit) bright_min
    pProcRes->ProcResV11.bright_max = int(bright_max);               // 0~255, (8bit) bright_max
    pProcRes->ProcResV11.wt_max     = int(wt_max * 256);             // 0~255, (8bit) wt_max
    pProcRes->ProcResV11.air_min    = int(air_min);                  // 0~255, (8bit) air_min
    pProcRes->ProcResV11.air_max    = int(air_max);                  // 0~256, (8bit) air_max
    pProcRes->ProcResV11.tmax_base  = int(tmax_base);                // 0~255, (8bit) tmax_base
    pProcRes->ProcResV11.tmax_off   = int(tmax_off * 1024);          // 0~1024,(10bit) tmax_off
    pProcRes->ProcResV11.tmax_max   = int(tmax_max * 1024);          // 0~1024,(10bit) tmax_max
    pProcRes->ProcResV11.stab_fnum  = int(stab_fnum);                // 1~31,  (5bit) stab_fnum
    pProcRes->ProcResV11.iir_sigma  = int(sigma);                    // 0~255, (8bit) sigma
    pProcRes->ProcResV11.iir_wt_sigma =
        int(wt_sigma * 8 + 0.5);                           //       (11bit),8bit+3bit, wt_sigma
    pProcRes->ProcResV11.iir_air_sigma  = int(air_sigma);  //       (8bit) air_sigma
    pProcRes->ProcResV11.iir_tmax_sigma = int(tmax_sigma * 1024 + 0.5);  //       (11bit) tmax_sigma
    pProcRes->ProcResV11.iir_pre_wet    = int(pre_wet * 15 + 0.5);       //       (4bit) iir_pre_wet
    pProcRes->ProcResV11.cfg_wt         = int(cfg_wt * 256);             // 0~256, (9bit) cfg_wt
    pProcRes->ProcResV11.cfg_air        = int(cfg_air);                  // 0~255, (8bit) cfg_air
    pProcRes->ProcResV11.cfg_tmax       = int(cfg_tmax * 1024);          // 0~1024,(11bit) cfg_tmax
    pProcRes->ProcResV11.range_sima     = int(range_sigma * 512);        // 0~512,(9bit) range_sima
    pProcRes->ProcResV11.space_sigma_cur =
        int(space_sigma_cur * 256);  // 0~256,(8bit) space_sigma_cur
    pProcRes->ProcResV11.space_sigma_pre =
        int(space_sigma_pre * 256);                                 // 0~256,(8bit) space_sigma_pre
    pProcRes->ProcResV11.bf_weight  = int(bf_weight * 256);         // 0~512, (8bit) dc_thed
    pProcRes->ProcResV11.dc_weitcur = int(dc_weitcur * 256 + 0.5);  // 0~256, (9bit) dc_weitcur
    pProcRes->ProcResV11.gaus_h0    = DEHAZE_GAUS_H4;               // h0~h2  从大到小
    pProcRes->ProcResV11.gaus_h1    = DEHAZE_GAUS_H1;
    pProcRes->ProcResV11.gaus_h2    = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV11.dc_en && !(pProcRes->ProcResV11.enhance_en)) {
        if (pProcRes->ProcResV11.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:255 cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__, cfg_air,
                         cfg_tmax, cfg_wt);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x0 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n", __func__,
                         pProcRes->ProcResV11.cfg_air, pProcRes->ProcResV11.cfg_tmax,
                         pProcRes->ProcResV11.cfg_wt);
        } else if (pProcRes->ProcResV11.cfg_alpha == 0) {
            LOGD_ADEHAZE("%s cfg_alpha:0 air_max:%f air_min:%f tmax_base:%f wt_max:%f\n", __func__,
                         air_max, air_min, tmax_base, wt_max);
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

    float enhance_value  = pStManu->enhance_setting.EnhanceData.enhance_value;
    float enhance_chroma = pStManu->enhance_setting.EnhanceData.enhance_chroma;

    pProcRes->ProcResV11.enhance_value =
        int(enhance_value * 1024 + 0.5);  //       (14bit),4bit + 10bit, enhance_value
    pProcRes->ProcResV11.enhance_chroma =
        int(enhance_chroma * 1024 + 0.5);  //       (14bit),4bit + 10bit, enhance_value

    for (int i = 0; i < ISP21_DHAZ_ENH_CURVE_NUM; i++)
        pProcRes->ProcResV11.enh_curve[i] = (int)(pStManu->enhance_setting.enhance_curve[i]);

    if (pProcRes->ProcResV11.dc_en && pProcRes->ProcResV11.enhance_en) {
        LOGD_ADEHAZE("%s enhance_value:%f enhance_chroma:%f\n", __func__, enhance_value,
                     enhance_chroma);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV11.enhance_value, pProcRes->ProcResV11.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetHistParamsV11(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    bool hist_para_en = pStManu->hist_setting.hist_para_en;
    float hist_gratio = pStManu->hist_setting.HistData.hist_gratio;
    float hist_th_off = pStManu->hist_setting.HistData.hist_th_off;
    float hist_k      = pStManu->hist_setting.HistData.hist_k;
    float hist_min    = pStManu->hist_setting.HistData.hist_min;
    float hist_scale  = pStManu->hist_setting.HistData.hist_scale;
    float cfg_gratio  = pStManu->hist_setting.HistData.cfg_gratio;

    pProcRes->ProcResV11.hpara_en =
        hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;  //  hist_para_en
    // clip hpara_en
    pProcRes->ProcResV11.hpara_en = pProcRes->ProcResV11.dc_en
                                        ? pProcRes->ProcResV11.hpara_en
                                        : FUNCTION_ENABLE;  //  dc en 关闭，hpara必需开

    pProcRes->ProcResV11.hist_gratio = int(hist_gratio * 8);   //       (8bit) hist_gratio
    pProcRes->ProcResV11.hist_th_off = int(hist_th_off);       //       (8bit) hist_th_off
    pProcRes->ProcResV11.hist_k      = int(hist_k * 4 + 0.5);  // 0~7    (5bit),3bit+2bit, hist_k
    pProcRes->ProcResV11.hist_min    = int(hist_min * 256);    //       (9bit) hist_min
    pProcRes->ProcResV11.cfg_gratio = int(cfg_gratio * 256);  //       (13bit),5bit+8bit, cfg_gratio
    pProcRes->ProcResV11.hist_scale =
        int(hist_scale * 256 + 0.5);  //       (13bit),5bit + 8bit, sw_hist_scale

    if (pProcRes->ProcResV11.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f hist_min:%f "
            "hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV11.cfg_alpha / 255.0, pProcRes->ProcResV11.hpara_en,
            hist_gratio, hist_th_off, hist_k, hist_min, hist_scale, cfg_gratio);
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
                        float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int EnvLv_len  = pCalibV11->dehaze_setting.DehazeData.EnvLv_len;
    bool air_lc_en = pCalibV11->dehaze_setting.air_lc_en;

    // dehaze_self_adp[7]
    float dc_min_th =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.dc_min_th, CtrlValue, EnvLv_len);
    float dc_max_th =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.dc_max_th, CtrlValue, EnvLv_len);
    float yhist_th =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.yhist_th, CtrlValue, EnvLv_len);
    float yblk_th =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.yblk_th, CtrlValue, EnvLv_len);
    float dark_th =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.dark_th, CtrlValue, EnvLv_len);
    float bright_min =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.bright_min, CtrlValue, EnvLv_len);
    float bright_max =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.bright_max, CtrlValue, EnvLv_len);

    // dehaze_range_adj[6]
    float wt_max =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.wt_max, CtrlValue, EnvLv_len);
    float air_max =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.air_max, CtrlValue, EnvLv_len);
    float air_min =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.air_min, CtrlValue, EnvLv_len);
    float tmax_base =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.tmax_base, CtrlValue, EnvLv_len);
    float tmax_off =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.tmax_off, CtrlValue, EnvLv_len);
    float tmax_max =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.tmax_max, CtrlValue, EnvLv_len);

    // dehaze_iir_control[5]
    float stab_fnum  = pCalibV11->dehaze_setting.stab_fnum;
    float sigma      = pCalibV11->dehaze_setting.sigma;
    float wt_sigma   = pCalibV11->dehaze_setting.wt_sigma;
    float air_sigma  = pCalibV11->dehaze_setting.air_sigma;
    float tmax_sigma = pCalibV11->dehaze_setting.tmax_sigma;
    float pre_wet    = pCalibV11->dehaze_setting.pre_wet;

    float cfg_wt =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.cfg_wt, CtrlValue, EnvLv_len);
    float cfg_air =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.cfg_air, CtrlValue, EnvLv_len);
    float cfg_tmax =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.cfg_tmax, CtrlValue, EnvLv_len);

    float range_sigma =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.range_sigma, CtrlValue, EnvLv_len);
    float space_sigma_cur =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.space_sigma_cur, CtrlValue, EnvLv_len);
    float space_sigma_pre =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.space_sigma_pre, CtrlValue, EnvLv_len);

    // dehaze_bi_pAdehazeCtx[4]
    float bf_weight =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.bf_weight, CtrlValue, EnvLv_len);
    float dc_weitcur =
        LinearInterpV11(pCalibV11->dehaze_setting.DehazeData.EnvLv,
                        pCalibV11->dehaze_setting.DehazeData.dc_weitcur, CtrlValue, EnvLv_len);

    int rawWidth                    = 1920;
    int rawHeight                   = 1080;
    pProcRes->ProcResV11.air_lc_en  = air_lc_en ? 1 : 0;  // air_lc_en
    pProcRes->ProcResV11.dc_min_th  = int(dc_min_th);     // 0~255, (8bit) dc_min_th
    pProcRes->ProcResV11.dc_max_th  = int(dc_max_th);     // 0~255, (8bit) dc_max_th
    pProcRes->ProcResV11.yhist_th   = int(yhist_th);      // 0~255, (8bit) yhist_th
    pProcRes->ProcResV11.yblk_th    = int(yblk_th * ((rawWidth + 15) / 16) *
                                       ((rawHeight + 15) / 16));  // default:28,(9bit) yblk_th
    pProcRes->ProcResV11.dark_th    = int(dark_th);                  // 0~255, (8bit) dark_th
    pProcRes->ProcResV11.bright_min = int(bright_min);               // 0~255, (8bit) bright_min
    pProcRes->ProcResV11.bright_max = int(bright_max);               // 0~255, (8bit) bright_max
    pProcRes->ProcResV11.wt_max     = int(wt_max * 256);             // 0~255, (8bit) wt_max
    pProcRes->ProcResV11.air_min    = int(air_min);                  // 0~255, (8bit) air_min
    pProcRes->ProcResV11.air_max    = int(air_max);                  // 0~256, (8bit) air_max
    pProcRes->ProcResV11.tmax_base  = int(tmax_base);                // 0~255, (8bit) tmax_base
    pProcRes->ProcResV11.tmax_off   = int(tmax_off * 1024);          // 0~1024,(10bit) tmax_off
    pProcRes->ProcResV11.tmax_max   = int(tmax_max * 1024);          // 0~1024,(10bit) tmax_max
    pProcRes->ProcResV11.stab_fnum  = int(stab_fnum);                // 1~31,  (5bit) stab_fnum
    pProcRes->ProcResV11.iir_sigma  = int(sigma);                    // 0~255, (8bit) sigma
    pProcRes->ProcResV11.iir_wt_sigma =
        int(wt_sigma * 8 + 0.5);                           //       (11bit),8bit+3bit, wt_sigma
    pProcRes->ProcResV11.iir_air_sigma  = int(air_sigma);  //       (8bit) air_sigma
    pProcRes->ProcResV11.iir_tmax_sigma = int(tmax_sigma * 1024 + 0.5);  //       (11bit) tmax_sigma
    pProcRes->ProcResV11.iir_pre_wet    = int(pre_wet * 15 + 0.5);       //       (4bit) iir_pre_wet
    pProcRes->ProcResV11.cfg_wt         = int(cfg_wt * 256);             // 0~256, (9bit) cfg_wt
    pProcRes->ProcResV11.cfg_air        = int(cfg_air);                  // 0~255, (8bit) cfg_air
    pProcRes->ProcResV11.cfg_tmax       = int(cfg_tmax * 1024);          // 0~1024,(11bit) cfg_tmax
    pProcRes->ProcResV11.range_sima     = int(range_sigma * 512);        // 0~512,(9bit) range_sima
    pProcRes->ProcResV11.space_sigma_cur =
        int(space_sigma_cur * 256);  // 0~256,(8bit) space_sigma_cur
    pProcRes->ProcResV11.space_sigma_pre =
        int(space_sigma_pre * 256);                                 // 0~256,(8bit) space_sigma_pre
    pProcRes->ProcResV11.bf_weight  = int(bf_weight * 256);         // 0~512, (8bit) dc_thed
    pProcRes->ProcResV11.dc_weitcur = int(dc_weitcur * 256 + 0.5);  // 0~256, (9bit) dc_weitcur
    pProcRes->ProcResV11.gaus_h0    = DEHAZE_GAUS_H4;               // h0~h2  从大到小
    pProcRes->ProcResV11.gaus_h1    = DEHAZE_GAUS_H1;
    pProcRes->ProcResV11.gaus_h2    = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV11.dc_en && !(pProcRes->ProcResV11.enhance_en)) {
        if (pProcRes->ProcResV11.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:255 EnvLv:%f cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__,
                         CtrlValue, cfg_air, cfg_tmax, cfg_wt);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x0 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n", __func__,
                         pProcRes->ProcResV11.cfg_air, pProcRes->ProcResV11.cfg_tmax,
                         pProcRes->ProcResV11.cfg_wt);
        } else if (pProcRes->ProcResV11.cfg_alpha == 0) {
            LOGD_ADEHAZE("%s cfg_alpha:0 EnvLv:%f air_max:%f air_min:%f tmax_base:%f wt_max:%f\n",
                         __func__, CtrlValue, air_max, air_min, tmax_base, wt_max);
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

    int EnvLv_len = pCalibV11->enhance_setting.EnhanceData.EnvLv_len;
    float enhance_value =
        LinearInterpV11(pCalibV11->enhance_setting.EnhanceData.EnvLv,
                        pCalibV11->enhance_setting.EnhanceData.enhance_value, CtrlValue, EnvLv_len);
    float enhance_chroma = LinearInterpV11(pCalibV11->enhance_setting.EnhanceData.EnvLv,
                                           pCalibV11->enhance_setting.EnhanceData.enhance_chroma,
                                           CtrlValue, EnvLv_len);

    pProcRes->ProcResV11.enhance_value =
        int(enhance_value * 1024 + 0.5);  //       (14bit),4bit + 10bit, enhance_value
    pProcRes->ProcResV11.enhance_chroma =
        int(enhance_chroma * 1024 + 0.5);  //       (14bit),4bit + 10bit, enhance_value

    for (int i = 0; i < ISP21_DHAZ_ENH_CURVE_NUM; i++)
        pProcRes->ProcResV11.enh_curve[i] = (int)(pCalibV11->enhance_setting.enhance_curve[i]);

    if (pProcRes->ProcResV11.dc_en && pProcRes->ProcResV11.enhance_en) {
        LOGD_ADEHAZE("%s EnvLv:%f enhance_value:%f enhance_chroma:%f\n", __func__, CtrlValue,
                     enhance_value, enhance_chroma);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV11.enhance_value, pProcRes->ProcResV11.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetHistParamsV11(CalibDbDehazeV11_t* pCalibV11, RkAiqAdehazeProcResult_t* pProcRes,
                      float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int EnvLv_len     = pCalibV11->hist_setting.HistData.EnvLv_len;
    bool hist_para_en = pCalibV11->hist_setting.hist_para_en;
    float hist_gratio =
        LinearInterpV11(pCalibV11->hist_setting.HistData.EnvLv,
                        pCalibV11->hist_setting.HistData.hist_gratio, CtrlValue, EnvLv_len);
    float hist_th_off =
        LinearInterpV11(pCalibV11->hist_setting.HistData.EnvLv,
                        pCalibV11->hist_setting.HistData.hist_th_off, CtrlValue, EnvLv_len);
    float hist_k = LinearInterpV11(pCalibV11->hist_setting.HistData.EnvLv,
                                   pCalibV11->hist_setting.HistData.hist_k, CtrlValue, EnvLv_len);
    float hist_min =
        LinearInterpV11(pCalibV11->hist_setting.HistData.EnvLv,
                        pCalibV11->hist_setting.HistData.hist_min, CtrlValue, EnvLv_len);
    float hist_scale =
        LinearInterpV11(pCalibV11->hist_setting.HistData.EnvLv,
                        pCalibV11->hist_setting.HistData.hist_scale, CtrlValue, EnvLv_len);
    float cfg_gratio =
        LinearInterpV11(pCalibV11->hist_setting.HistData.EnvLv,
                        pCalibV11->hist_setting.HistData.cfg_gratio, CtrlValue, EnvLv_len);

    pProcRes->ProcResV11.hpara_en =
        hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;  //  hist_para_en
    // clip hpara_en
    pProcRes->ProcResV11.hpara_en = pProcRes->ProcResV11.dc_en
                                        ? pProcRes->ProcResV11.hpara_en
                                        : FUNCTION_ENABLE;  //  dc en 关闭，hpara必需开

    pProcRes->ProcResV11.hist_gratio = int(hist_gratio * 8);   //       (8bit) hist_gratio
    pProcRes->ProcResV11.hist_th_off = int(hist_th_off);       //       (8bit) hist_th_off
    pProcRes->ProcResV11.hist_k      = int(hist_k * 4 + 0.5);  // 0~7    (5bit),3bit+2bit, hist_k
    pProcRes->ProcResV11.hist_min    = int(hist_min * 256);    //       (9bit) hist_min
    pProcRes->ProcResV11.cfg_gratio = int(cfg_gratio * 256);  //       (13bit),5bit+8bit, cfg_gratio
    pProcRes->ProcResV11.hist_scale =
        int(hist_scale * 256 + 0.5);  //       (13bit),5bit + 8bit, sw_hist_scale

    if (pProcRes->ProcResV11.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f EnvLv:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f "
            "hist_min:%f hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV11.cfg_alpha / 255.0, CtrlValue,
            pProcRes->ProcResV11.hpara_en, hist_gratio, hist_th_off, hist_k, hist_min, hist_scale,
            cfg_gratio);
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
    LOGD_ADEHAZE(" %s: Adehaze Api stManual!!!\n", __func__);

    // cfg setting
    pProcRes->ProcResV11.cfg_alpha = LIMIT_VALUE(SHIFT8BIT(pStManu->cfg_alpha), BIT_8_MAX, BIT_MIN);

    // enable setting
    stManuEnableSettingV11(pStManu, pProcRes);

    // dehaze setting
    stManuGetDehazeParamsV11(pStManu, pProcRes);

    // enhance setting
    stManuGetEnhanceParamsV11(pStManu, pProcRes);

    // hist setting
    stManuGetHistParamsV11(pStManu, pProcRes);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
}

void AdehazeAtuoProcessV11(CalibDbV2_dehaze_V11_t* pCalibV11, RkAiqAdehazeProcResult_t* pProcRes,
                           float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE(" %s: Adehaze stAuto!!!\n", __func__);

    // cfg setting
    pProcRes->ProcResV11.cfg_alpha =
        LIMIT_VALUE(SHIFT8BIT(pCalibV11->DehazeTuningPara.cfg_alpha), BIT_8_MAX, BIT_MIN);

    // enable setting
    EnableSettingV11(&pCalibV11->DehazeTuningPara, pProcRes);

    // dehaze setting
    GetDehazeParamsV11(&pCalibV11->DehazeTuningPara, pProcRes, CtrlValue);

    // enhance setting
    GetEnhanceParamsV11(&pCalibV11->DehazeTuningPara, pProcRes, CtrlValue);

    // hist setting
    GetHistParamsV11(&pCalibV11->DehazeTuningPara, pProcRes, CtrlValue);

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

void AdehazeGetEnvLvISO(AdehazeHandle_t* pAdehazeCtx, RkAiqAlgoPreResAe* pAePreRes) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);

    if (pAePreRes == NULL) {
        LOGE_ADEHAZE("%s:Ae Pre Res is NULL!\n", __FUNCTION__);
        pAdehazeCtx->CurrDataV11.EnvLv = 0.0;
        return;
    }

    pAdehazeCtx->CurrDataV11.EnvLv =
        pAePreRes->ae_pre_res_rk.GlobalEnvLv[pAePreRes->ae_pre_res_rk.NormalIndex];

    // Normalize the current envLv for AEC
    pAdehazeCtx->CurrDataV11.EnvLv =
        (pAdehazeCtx->CurrDataV11.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
    pAdehazeCtx->CurrDataV11.EnvLv =
        LIMIT_VALUE(pAdehazeCtx->CurrDataV11.EnvLv, ENVLVMAX, ENVLVMIN);

    // get iso
    if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
        pAdehazeCtx->CurrDataV11.ISO =
            pAePreRes->ae_pre_res_rk.LinearExp.exp_real_params.analog_gain *
            pAePreRes->ae_pre_res_rk.LinearExp.exp_real_params.digital_gain * 50.0;
    else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
        pAdehazeCtx->CurrDataV11.ISO =
            pAePreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.analog_gain *
            pAePreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.digital_gain * 50.0;

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

void AdehazeGetCurrDataGroup(AdehazeHandle_t* pAdehazeCtx, RKAiqAecExpInfo_t* pAeEffExpo,
                             XCamVideoBuffer* pAePreRes) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);

    RkAiqAlgoPreResAe* pAEPreRes = NULL;
    if (pAePreRes) {
        pAEPreRes = (RkAiqAlgoPreResAe*)pAePreRes->map(pAePreRes);
        AdehazeGetEnvLvISO(pAdehazeCtx, pAEPreRes);
    } else {
        pAdehazeCtx->CurrDataV11.EnvLv = 0.0;
        LOGW_ADEHAZE("%s:PreResBuf is NULL!\n", __FUNCTION__);
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

void AdehazeGetCurrData(AdehazeHandle_t* pAdehazeCtx, RkAiqAlgoProcAdhaz* pProcPara) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);

    XCamVideoBuffer* xCamAePreRes = pProcPara->com.u.proc.res_comb->ae_pre_res;
    RkAiqAlgoPreResAe* pAEPreRes  = NULL;
    if (xCamAePreRes) {
        pAEPreRes = (RkAiqAlgoPreResAe*)xCamAePreRes->map(xCamAePreRes);
        AdehazeGetEnvLvISO(pAdehazeCtx, pAEPreRes);
    } else {
        pAdehazeCtx->CurrDataV11.EnvLv = 0.0;
        pAdehazeCtx->CurrDataV11.ISO   = 50.0;
        LOGW_ADEHAZE("%s:PreResBuf is NULL!\n", __FUNCTION__);
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

XCamReturn AdehazeInit(AdehazeHandle_t** pAdehazeCtx, CamCalibDbV2Context_t* pCalib) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret          = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t* handle = (AdehazeHandle_t*)calloc(1, sizeof(AdehazeHandle_t));

    CalibDbV2_dehaze_V11_t* calibv2_adehaze_calib_V21 =
        (CalibDbV2_dehaze_V11_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, adehaze_calib));
    memcpy(&handle->AdehazeAtrrV11.stAuto, calibv2_adehaze_calib_V21,
           sizeof(CalibDbV2_dehaze_V11_t));  // set default stauto

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

    float CtrlValue = pAdehazeCtx->CurrDataV11.EnvLv;

    if (pAdehazeCtx->AdehazeAtrrV11.mode == DEHAZE_API_AUTO)
        AdehazeAtuoProcessV11(&pAdehazeCtx->AdehazeAtrrV11.stAuto, &pAdehazeCtx->ProcRes,
                              CtrlValue);
    else if (pAdehazeCtx->AdehazeAtrrV11.mode == DEHAZE_API_MANUAL)
        AdehazeManuProcessV11(&pAdehazeCtx->ProcRes, &pAdehazeCtx->AdehazeAtrrV11.stManual);
    else
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

    if (pAdehazeCtx->FrameID <= 2) pAdehazeCtx->byPassProc = false;
    if (pAdehazeCtx->AdehazeAtrrV11.mode > DEHAZE_API_AUTO)
        pAdehazeCtx->byPassProc = false;
    else if (pAdehazeCtx->AdehazeAtrrV11.mode != pAdehazeCtx->PreDataV11.ApiMode)
        pAdehazeCtx->byPassProc = false;
    else {
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
    }

    ret = pAdehazeCtx->byPassProc;

    LOGD_ADEHAZE("%s:FrameID:%d byPassProc:%d ISO:%f\n", __func__, pAdehazeCtx->FrameID, ret,
                 pAdehazeCtx->CurrDataV11.ISO);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}
