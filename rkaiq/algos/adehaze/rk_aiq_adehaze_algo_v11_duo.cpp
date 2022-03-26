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

void EnableSettingV11duo(CalibDbDehazeV11_t* pCalibV21, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.enable = pCalibV21->Enable;

    bool dehaze_enable  = false;
    bool enhance_enable = false;
    if (pCalibV21->Enable) {
        if (pCalibV21->dehaze_setting.en && pCalibV21->enhance_setting.en) {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_ENABLE;
        } else if (pCalibV21->dehaze_setting.en && !pCalibV21->enhance_setting.en) {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_DISABLE;
        } else if (!pCalibV21->dehaze_setting.en && pCalibV21->enhance_setting.en) {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_ENABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_ENABLE;
        } else {
            pProcRes->ProcResV11duo.dc_en      = FUNCTION_DISABLE;
            pProcRes->ProcResV11duo.enhance_en = FUNCTION_DISABLE;
        }

        if (pCalibV21->hist_setting.en)
            pProcRes->ProcResV11duo.hist_en = FUNCTION_ENABLE;
        else
            pProcRes->ProcResV11duo.hist_en = FUNCTION_DISABLE;
    } else {
        pProcRes->ProcResV11duo.dc_en      = FUNCTION_DISABLE;
        pProcRes->ProcResV11duo.enhance_en = FUNCTION_DISABLE;
        pProcRes->ProcResV11duo.hist_en    = FUNCTION_DISABLE;
    }
    dehaze_enable = (pProcRes->ProcResV11duo.dc_en & FUNCTION_ENABLE) &&
                    (!(pProcRes->ProcResV11duo.enhance_en & FUNCTION_ENABLE));
    enhance_enable = (pProcRes->ProcResV11duo.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV11duo.enhance_en & FUNCTION_ENABLE);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV11duo.enable, dehaze_enable, enhance_enable,
                 pProcRes->ProcResV11duo.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuEnableSettingV11duo(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    pProcRes->ProcResV11duo.enable = pStManu->Enable;

    bool dehaze_enable  = false;
    bool enhance_enable = false;
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
    dehaze_enable = (pProcRes->ProcResV11duo.dc_en & FUNCTION_ENABLE) &&
                    (!(pProcRes->ProcResV11duo.enhance_en & FUNCTION_ENABLE));
    enhance_enable = (pProcRes->ProcResV11duo.dc_en & FUNCTION_ENABLE) &&
                     (pProcRes->ProcResV11duo.enhance_en & FUNCTION_ENABLE);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 pProcRes->ProcResV11duo.enable, dehaze_enable, enhance_enable,
                 pProcRes->ProcResV11duo.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetDehazeParamsV11duo(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
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

    int rawWidth                       = 1920;
    int rawHeight                      = 1080;
    pProcRes->ProcResV11duo.air_lc_en  = air_lc_en ? 1 : 0;  // air_lc_en
    pProcRes->ProcResV11duo.dc_min_th  = int(dc_min_th);     // 0~255, (8bit) dc_min_th
    pProcRes->ProcResV11duo.dc_max_th  = int(dc_max_th);     // 0~255, (8bit) dc_max_th
    pProcRes->ProcResV11duo.yhist_th   = int(yhist_th);      // 0~255, (8bit) yhist_th
    pProcRes->ProcResV11duo.yblk_th    = int(yblk_th * ((rawWidth + 15) / 16) *
                                          ((rawHeight + 15) / 16));  // default:28,(9bit) yblk_th
    pProcRes->ProcResV11duo.dark_th    = int(dark_th);                  // 0~255, (8bit) dark_th
    pProcRes->ProcResV11duo.bright_min = int(bright_min);               // 0~255, (8bit) bright_min
    pProcRes->ProcResV11duo.bright_max = int(bright_max);               // 0~255, (8bit) bright_max
    pProcRes->ProcResV11duo.wt_max     = int(wt_max * 256);             // 0~255, (8bit) wt_max
    pProcRes->ProcResV11duo.air_min    = int(air_min);                  // 0~255, (8bit) air_min
    pProcRes->ProcResV11duo.air_max    = int(air_max);                  // 0~256, (8bit) air_max
    pProcRes->ProcResV11duo.tmax_base  = int(tmax_base);                // 0~255, (8bit) tmax_base
    pProcRes->ProcResV11duo.tmax_off   = int(tmax_off * 1024);          // 0~1024,(10bit) tmax_off
    pProcRes->ProcResV11duo.tmax_max   = int(tmax_max * 1024);          // 0~1024,(10bit) tmax_max
    pProcRes->ProcResV11duo.stab_fnum  = int(stab_fnum);                // 1~31,  (5bit) stab_fnum
    pProcRes->ProcResV11duo.iir_sigma  = int(sigma);                    // 0~255, (8bit) sigma
    pProcRes->ProcResV11duo.iir_wt_sigma =
        int(wt_sigma * 8 + 0.5);                             //       (11bit),8bit+3bit, wt_sigma
    pProcRes->ProcResV11duo.iir_air_sigma = int(air_sigma);  //       (8bit) air_sigma
    pProcRes->ProcResV11duo.iir_tmax_sigma =
        int(tmax_sigma * 1024 + 0.5);                               //       (11bit) tmax_sigma
    pProcRes->ProcResV11duo.iir_pre_wet = int(pre_wet * 15 + 0.5);  //       (4bit) iir_pre_wet
    pProcRes->ProcResV11duo.cfg_wt      = int(cfg_wt * 256);        // 0~256, (9bit) cfg_wt
    pProcRes->ProcResV11duo.cfg_air     = int(cfg_air);             // 0~255, (8bit) cfg_air
    pProcRes->ProcResV11duo.cfg_tmax    = int(cfg_tmax * 1024);     // 0~1024,(11bit) cfg_tmax
    pProcRes->ProcResV11duo.range_sima  = int(range_sigma * 512);   // 0~512,(9bit) range_sima
    pProcRes->ProcResV11duo.space_sigma_cur =
        int(space_sigma_cur * 256);  // 0~256,(8bit) space_sigma_cur
    pProcRes->ProcResV11duo.space_sigma_pre =
        int(space_sigma_pre * 256);                             // 0~256,(8bit) space_sigma_pre
    pProcRes->ProcResV11duo.bf_weight  = int(bf_weight * 256);  // 0~512, (8bit) dc_thed
    pProcRes->ProcResV11duo.dc_weitcur = int(dc_weitcur * 256 + 0.5);  // 0~256, (9bit) dc_weitcur
    pProcRes->ProcResV11duo.gaus_h0    = DEHAZE_GAUS_H4;               // h0~h2  浠庡ぇ鍒板皬
    pProcRes->ProcResV11duo.gaus_h1    = DEHAZE_GAUS_H1;
    pProcRes->ProcResV11duo.gaus_h2    = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV11duo.dc_en && !(pProcRes->ProcResV11duo.enhance_en)) {
        if (pProcRes->ProcResV11duo.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:255 cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__, cfg_air,
                         cfg_tmax, cfg_wt);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x0 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n", __func__,
                         pProcRes->ProcResV11duo.cfg_air, pProcRes->ProcResV11duo.cfg_tmax,
                         pProcRes->ProcResV11duo.cfg_wt);
        } else if (pProcRes->ProcResV11duo.cfg_alpha == 0) {
            LOGD_ADEHAZE("%s cfg_alpha:0 air_max:%f air_min:%f tmax_base:%f wt_max:%f\n", __func__,
                         air_max, air_min, tmax_base, wt_max);
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

    float enhance_value  = pStManu->enhance_setting.EnhanceData.enhance_value;
    float enhance_chroma = pStManu->enhance_setting.EnhanceData.enhance_chroma;

    pProcRes->ProcResV11duo.enhance_value =
        int(enhance_value * 1024 + 0.5);  //       (14bit),4bit + 10bit, enhance_value
    pProcRes->ProcResV11duo.enhance_chroma =
        int(enhance_chroma * 1024 + 0.5);  //       (14bit),4bit + 10bit, enhance_value

    for (int i = 0; i < DHAZ_V11_ENHANCE_CRUVE_NUM; i++)
        pProcRes->ProcResV11duo.enh_curve[i] = (int)(pStManu->enhance_setting.enhance_curve[i]);

    if (pProcRes->ProcResV11duo.dc_en && pProcRes->ProcResV11duo.enhance_en) {
        LOGD_ADEHAZE("%s enhance_value:%f enhance_chroma:%f\n", __func__, enhance_value,
                     enhance_chroma);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV11duo.enhance_value, pProcRes->ProcResV11duo.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void stManuGetHistParamsV11duo(mDehazeAttrV11_t* pStManu, RkAiqAdehazeProcResult_t* pProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    bool hist_para_en = pStManu->hist_setting.hist_para_en;
    float hist_gratio = pStManu->hist_setting.HistData.hist_gratio;
    float hist_th_off = pStManu->hist_setting.HistData.hist_th_off;
    float hist_k      = pStManu->hist_setting.HistData.hist_k;
    float hist_min    = pStManu->hist_setting.HistData.hist_min;
    float hist_scale  = pStManu->hist_setting.HistData.hist_scale;
    float cfg_gratio  = pStManu->hist_setting.HistData.cfg_gratio;

    pProcRes->ProcResV11duo.hpara_en =
        hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;  //  hist_para_en
    // clip hpara_en
    pProcRes->ProcResV11duo.hpara_en = pProcRes->ProcResV11duo.dc_en
                                           ? pProcRes->ProcResV11duo.hpara_en
                                           : FUNCTION_ENABLE;  //  dc en 关闭，hpara必需开

    pProcRes->ProcResV11duo.hist_gratio = int(hist_gratio * 8);   //       (8bit) hist_gratio
    pProcRes->ProcResV11duo.hist_th_off = int(hist_th_off);       //       (8bit) hist_th_off
    pProcRes->ProcResV11duo.hist_k      = int(hist_k * 4 + 0.5);  // 0~7    (5bit),3bit+2bit, hist_k
    pProcRes->ProcResV11duo.hist_min    = int(hist_min * 256);    //       (9bit) hist_min
    pProcRes->ProcResV11duo.cfg_gratio =
        int(cfg_gratio * 256);  //       (13bit),5bit+8bit, cfg_gratio
    pProcRes->ProcResV11duo.hist_scale =
        int(hist_scale * 256 + 0.5);  //       (13bit),5bit + 8bit, sw_hist_scale

    if (pProcRes->ProcResV11duo.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f hist_min:%f "
            "hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV11duo.cfg_alpha / 255.0, pProcRes->ProcResV11duo.hpara_en,
            hist_gratio, hist_th_off, hist_k, hist_min, hist_scale, cfg_gratio);
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

void GetDehazeParamsV11duo(CalibDbDehazeV11_t* pCalibV21, RkAiqAdehazeProcResult_t* pProcRes,
                           float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int CtrlData_len = pCalibV21->dehaze_setting.DehazeData.CtrlData_len;
    bool air_lc_en = pCalibV21->dehaze_setting.air_lc_en;

    // dehaze_self_adp[7]
    float dc_min_th =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.dc_min_th, CtrlValue, CtrlData_len);
    float dc_max_th =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.dc_max_th, CtrlValue, CtrlData_len);
    float yhist_th =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.yhist_th, CtrlValue, CtrlData_len);
    float yblk_th =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.yblk_th, CtrlValue, CtrlData_len);
    float dark_th =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.dark_th, CtrlValue, CtrlData_len);
    float bright_min = LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                                          pCalibV21->dehaze_setting.DehazeData.bright_min,
                                          CtrlValue, CtrlData_len);
    float bright_max = LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                                          pCalibV21->dehaze_setting.DehazeData.bright_max,
                                          CtrlValue, CtrlData_len);

    // dehaze_range_adj[6]
    float wt_max =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.wt_max, CtrlValue, CtrlData_len);
    float air_max =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.air_max, CtrlValue, CtrlData_len);
    float air_min =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.air_min, CtrlValue, CtrlData_len);
    float tmax_base =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.tmax_base, CtrlValue, CtrlData_len);
    float tmax_off =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.tmax_off, CtrlValue, CtrlData_len);
    float tmax_max =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.tmax_max, CtrlValue, CtrlData_len);

    // dehaze_iir_control[5]
    float stab_fnum  = pCalibV21->dehaze_setting.stab_fnum;
    float sigma      = pCalibV21->dehaze_setting.sigma;
    float wt_sigma   = pCalibV21->dehaze_setting.wt_sigma;
    float air_sigma  = pCalibV21->dehaze_setting.air_sigma;
    float tmax_sigma = pCalibV21->dehaze_setting.tmax_sigma;
    float pre_wet    = pCalibV21->dehaze_setting.pre_wet;

    float cfg_wt =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.cfg_wt, CtrlValue, CtrlData_len);
    float cfg_air =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.cfg_air, CtrlValue, CtrlData_len);
    float cfg_tmax =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.cfg_tmax, CtrlValue, CtrlData_len);

    float range_sigma     = LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                                           pCalibV21->dehaze_setting.DehazeData.range_sigma,
                                           CtrlValue, CtrlData_len);
    float space_sigma_cur = LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                                               pCalibV21->dehaze_setting.DehazeData.space_sigma_cur,
                                               CtrlValue, CtrlData_len);
    float space_sigma_pre = LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                                               pCalibV21->dehaze_setting.DehazeData.space_sigma_pre,
                                               CtrlValue, CtrlData_len);

    // dehaze_bi_pAdehazeCtx[4]
    float bf_weight =
        LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                           pCalibV21->dehaze_setting.DehazeData.bf_weight, CtrlValue, CtrlData_len);
    float dc_weitcur = LinearInterpV11Duo(pCalibV21->dehaze_setting.DehazeData.CtrlData,
                                          pCalibV21->dehaze_setting.DehazeData.dc_weitcur,
                                          CtrlValue, CtrlData_len);

    int rawWidth                       = 1920;
    int rawHeight                      = 1080;
    pProcRes->ProcResV11duo.air_lc_en  = air_lc_en ? 1 : 0;  // air_lc_en
    pProcRes->ProcResV11duo.dc_min_th  = int(dc_min_th);     // 0~255, (8bit) dc_min_th
    pProcRes->ProcResV11duo.dc_max_th  = int(dc_max_th);     // 0~255, (8bit) dc_max_th
    pProcRes->ProcResV11duo.yhist_th   = int(yhist_th);      // 0~255, (8bit) yhist_th
    pProcRes->ProcResV11duo.yblk_th    = int(yblk_th * ((rawWidth + 15) / 16) *
                                          ((rawHeight + 15) / 16));  // default:28,(9bit) yblk_th
    pProcRes->ProcResV11duo.dark_th    = int(dark_th);                  // 0~255, (8bit) dark_th
    pProcRes->ProcResV11duo.bright_min = int(bright_min);               // 0~255, (8bit) bright_min
    pProcRes->ProcResV11duo.bright_max = int(bright_max);               // 0~255, (8bit) bright_max
    pProcRes->ProcResV11duo.wt_max     = int(wt_max * 256);             // 0~255, (8bit) wt_max
    pProcRes->ProcResV11duo.air_min    = int(air_min);                  // 0~255, (8bit) air_min
    pProcRes->ProcResV11duo.air_max    = int(air_max);                  // 0~256, (8bit) air_max
    pProcRes->ProcResV11duo.tmax_base  = int(tmax_base);                // 0~255, (8bit) tmax_base
    pProcRes->ProcResV11duo.tmax_off   = int(tmax_off * 1024);          // 0~1024,(10bit) tmax_off
    pProcRes->ProcResV11duo.tmax_max   = int(tmax_max * 1024);          // 0~1024,(10bit) tmax_max
    pProcRes->ProcResV11duo.stab_fnum  = int(stab_fnum);                // 1~31,  (5bit) stab_fnum
    pProcRes->ProcResV11duo.iir_sigma  = int(sigma);                    // 0~255, (8bit) sigma
    pProcRes->ProcResV11duo.iir_wt_sigma =
        int(wt_sigma * 8 + 0.5);                             //       (11bit),8bit+3bit, wt_sigma
    pProcRes->ProcResV11duo.iir_air_sigma = int(air_sigma);  //       (8bit) air_sigma
    pProcRes->ProcResV11duo.iir_tmax_sigma =
        int(tmax_sigma * 1024 + 0.5);                               //       (11bit) tmax_sigma
    pProcRes->ProcResV11duo.iir_pre_wet = int(pre_wet * 15 + 0.5);  //       (4bit) iir_pre_wet
    pProcRes->ProcResV11duo.cfg_wt      = int(cfg_wt * 256);        // 0~256, (9bit) cfg_wt
    pProcRes->ProcResV11duo.cfg_air     = int(cfg_air);             // 0~255, (8bit) cfg_air
    pProcRes->ProcResV11duo.cfg_tmax    = int(cfg_tmax * 1024);     // 0~1024,(11bit) cfg_tmax
    pProcRes->ProcResV11duo.range_sima  = int(range_sigma * 512);   // 0~512,(9bit) range_sima
    pProcRes->ProcResV11duo.space_sigma_cur =
        int(space_sigma_cur * 256);  // 0~256,(8bit) space_sigma_cur
    pProcRes->ProcResV11duo.space_sigma_pre =
        int(space_sigma_pre * 256);                             // 0~256,(8bit) space_sigma_pre
    pProcRes->ProcResV11duo.bf_weight  = int(bf_weight * 256);  // 0~512, (8bit) dc_thed
    pProcRes->ProcResV11duo.dc_weitcur = int(dc_weitcur * 256 + 0.5);  // 0~256, (9bit) dc_weitcur
    pProcRes->ProcResV11duo.gaus_h0    = DEHAZE_GAUS_H4;               // h0~h2  浠庡ぇ鍒板皬
    pProcRes->ProcResV11duo.gaus_h1    = DEHAZE_GAUS_H1;
    pProcRes->ProcResV11duo.gaus_h2    = DEHAZE_GAUS_H0;

    if (pProcRes->ProcResV11duo.dc_en && !(pProcRes->ProcResV11duo.enhance_en)) {
        if (pProcRes->ProcResV11duo.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:1 CtrlValue:%f cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__,
                         CtrlValue, cfg_air, cfg_tmax, cfg_wt);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x255 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n",
                         __func__, pProcRes->ProcResV11duo.cfg_air,
                         pProcRes->ProcResV11duo.cfg_tmax, pProcRes->ProcResV11duo.cfg_wt);
        } else if (pProcRes->ProcResV11duo.cfg_alpha == 0) {
            LOGD_ADEHAZE(
                "%s cfg_alpha:0 CtrlValue:%f air_max:%f air_min:%f tmax_base:%f wt_max:%f\n",
                __func__, CtrlValue, air_max, air_min, tmax_base, wt_max);
            LOGD_ADEHAZE(
                "%s cfg_alpha_reg:0x0 air_max:0x%x air_min:0x%x tmax_base:0x%x wt_max:0x%x\n",
                __func__, pProcRes->ProcResV11duo.air_max, pProcRes->ProcResV11duo.air_min,
                pProcRes->ProcResV11duo.tmax_base, pProcRes->ProcResV11duo.wt_max);
        }
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetEnhanceParamsV11duo(CalibDbDehazeV11_t* pCalibV21, RkAiqAdehazeProcResult_t* pProcRes,
                            float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int CtrlData_len     = pCalibV21->enhance_setting.EnhanceData.CtrlData_len;
    float enhance_value  = LinearInterpV11Duo(pCalibV21->enhance_setting.EnhanceData.CtrlData,
                                             pCalibV21->enhance_setting.EnhanceData.enhance_value,
                                             CtrlValue, CtrlData_len);
    float enhance_chroma = LinearInterpV11Duo(pCalibV21->enhance_setting.EnhanceData.CtrlData,
                                              pCalibV21->enhance_setting.EnhanceData.enhance_chroma,
                                              CtrlValue, CtrlData_len);

    pProcRes->ProcResV11duo.enhance_value =
        int(enhance_value * 1024 + 0.5);  //       (14bit),4bit + 10bit, enhance_value
    pProcRes->ProcResV11duo.enhance_chroma =
        int(enhance_chroma * 1024 + 0.5);  //       (14bit),4bit + 10bit, enhance_value

    for (int i = 0; i < DHAZ_V11_ENHANCE_CRUVE_NUM; i++)
        pProcRes->ProcResV11duo.enh_curve[i] = (int)(pCalibV21->enhance_setting.enhance_curve[i]);

    if (pProcRes->ProcResV11duo.dc_en && pProcRes->ProcResV11duo.enhance_en) {
        LOGD_ADEHAZE("%s CtrlValue:%f enhance_value:%f enhance_chroma:%f\n", __func__, CtrlValue,
                     enhance_value, enhance_chroma);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     pProcRes->ProcResV11duo.enhance_value, pProcRes->ProcResV11duo.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetHistParamsV11duo(CalibDbDehazeV11_t* pCalibV21, RkAiqAdehazeProcResult_t* pProcRes,
                         float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int CtrlData_len  = pCalibV21->hist_setting.HistData.CtrlData_len;
    bool hist_para_en = pCalibV21->hist_setting.hist_para_en;
    float hist_gratio =
        LinearInterpV11Duo(pCalibV21->hist_setting.HistData.CtrlData,
                           pCalibV21->hist_setting.HistData.hist_gratio, CtrlValue, CtrlData_len);
    float hist_th_off =
        LinearInterpV11Duo(pCalibV21->hist_setting.HistData.CtrlData,
                           pCalibV21->hist_setting.HistData.hist_th_off, CtrlValue, CtrlData_len);
    float hist_k =
        LinearInterpV11Duo(pCalibV21->hist_setting.HistData.CtrlData,
                           pCalibV21->hist_setting.HistData.hist_k, CtrlValue, CtrlData_len);
    float hist_min =
        LinearInterpV11Duo(pCalibV21->hist_setting.HistData.CtrlData,
                           pCalibV21->hist_setting.HistData.hist_min, CtrlValue, CtrlData_len);
    float hist_scale =
        LinearInterpV11Duo(pCalibV21->hist_setting.HistData.CtrlData,
                           pCalibV21->hist_setting.HistData.hist_scale, CtrlValue, CtrlData_len);
    float cfg_gratio =
        LinearInterpV11Duo(pCalibV21->hist_setting.HistData.CtrlData,
                           pCalibV21->hist_setting.HistData.cfg_gratio, CtrlValue, CtrlData_len);

    pProcRes->ProcResV11duo.hpara_en =
        hist_para_en ? FUNCTION_ENABLE : FUNCTION_DISABLE;  //  hist_para_en
    // clip hpara_en
    pProcRes->ProcResV11duo.hpara_en = pProcRes->ProcResV11duo.dc_en
                                           ? pProcRes->ProcResV11duo.hpara_en
                                           : FUNCTION_ENABLE;  //  dc en 关闭，hpara必需开

    pProcRes->ProcResV11duo.hist_gratio = int(hist_gratio * 8);   //       (8bit) hist_gratio
    pProcRes->ProcResV11duo.hist_th_off = int(hist_th_off);       //       (8bit) hist_th_off
    pProcRes->ProcResV11duo.hist_k      = int(hist_k * 4 + 0.5);  // 0~7    (5bit),3bit+2bit, hist_k
    pProcRes->ProcResV11duo.hist_min    = int(hist_min * 256);    //       (9bit) hist_min
    pProcRes->ProcResV11duo.cfg_gratio =
        int(cfg_gratio * 256);  //       (13bit),5bit+8bit, cfg_gratio
    pProcRes->ProcResV11duo.hist_scale =
        int(hist_scale * 256 + 0.5);  //       (13bit),5bit + 8bit, sw_hist_scale

    if (pProcRes->ProcResV11duo.hist_en) {
        LOGD_ADEHAZE(
            "%s cfg_alpha:%f CtrlValue:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f "
            "hist_min:%f hist_scale:%f cfg_gratio:%f\n",
            __func__, pProcRes->ProcResV11duo.cfg_alpha / 255.0, CtrlValue,
            pProcRes->ProcResV11duo.hpara_en, hist_gratio, hist_th_off, hist_k, hist_min,
            hist_scale, cfg_gratio);
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
            float ISO_lo    = 50.0;
            float ISO_hi    = 50.0;
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

        pAdehazeCtx->CurrDataV11duo.EnvLv =
            pAEPreRes->ae_pre_res_rk.GlobalEnvLv[pAEPreRes->ae_pre_res_rk.NormalIndex];

        // Normalize the current envLv for AEC
        pAdehazeCtx->CurrDataV11duo.EnvLv =
            (pAdehazeCtx->CurrDataV11duo.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
        pAdehazeCtx->CurrDataV11duo.EnvLv =
            LIMIT_VALUE(pAdehazeCtx->CurrDataV11duo.EnvLv, ENVLVMAX, ENVLVMIN);

        // get iso
        if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
            pAdehazeCtx->CurrDataV11duo.ISO =
                pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.analog_gain *
                pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.digital_gain * 50.0;
        else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
            pAdehazeCtx->CurrDataV11duo.ISO =
                pAEPreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.analog_gain *
                pAEPreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.digital_gain * 50.0;
    } else {
        pAdehazeCtx->CurrDataV11duo.EnvLv = ENVLVMIN;
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

        pAdehazeCtx->CurrDataV11duo.EnvLv =
            pAEPreRes->ae_pre_res_rk.GlobalEnvLv[pAEPreRes->ae_pre_res_rk.NormalIndex];
        // Normalize the current envLv for AEC
        pAdehazeCtx->CurrDataV11duo.EnvLv =
            (pAdehazeCtx->CurrDataV11duo.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
        pAdehazeCtx->CurrDataV11duo.EnvLv =
            LIMIT_VALUE(pAdehazeCtx->CurrDataV11duo.EnvLv, ENVLVMAX, ENVLVMIN);

        // get iso
        if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
            pAdehazeCtx->CurrDataV11duo.ISO =
                pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.analog_gain *
                pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.digital_gain * 50.0;
        else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
            pAdehazeCtx->CurrDataV11duo.ISO =
                pAEPreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.analog_gain *
                pAEPreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.digital_gain * 50.0;
    } else {
        pAdehazeCtx->CurrDataV11duo.EnvLv = ENVLVMIN;
        pAdehazeCtx->CurrDataV11duo.ISO   = ISOMIN;
        LOGE_ADEHAZE("%s:PreResBuf is NULL!\n", __FUNCTION__);
    }

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
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
                              &pAdehazeCtx->ProcRes, CtrlValue);

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
        stManuGetDehazeParamsV11duo(&pAdehazeCtx->AdehazeAtrrV11duo.stManual,
                                    &pAdehazeCtx->ProcRes);

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
