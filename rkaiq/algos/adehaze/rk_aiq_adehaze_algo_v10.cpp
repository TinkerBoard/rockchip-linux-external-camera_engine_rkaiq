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
#include "rk_aiq_adehaze_algo_v10.h"

#include <string.h>

#include "xcam_log.h"

float LinearInterp(const float* pX, const float* pY, float posx, int XSize) {
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

int LinearInterpEnable(const float* pX, const unsigned char* pY, float posx, int XSize) {
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
    yOut = out > 0.5 ? 1 : 0;

    return yOut;
}

void EnableSetting(CalibDbV2_dehaze_v10_t* pAdehazeCtx, RkAiqAdehazeProcResult_t* ProcRes) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    ProcRes->ProcResV10.enable = true;

    bool dehaze_enable  = false;
    bool enhance_enable = false;

    if (pAdehazeCtx->DehazeTuningPara.Enable) {
        if (pAdehazeCtx->DehazeTuningPara.dehaze_setting.en &&
            pAdehazeCtx->DehazeTuningPara.enhance_setting.en) {
            ProcRes->ProcResV10.dc_en      = FUNCTION_ENABLE;
            ProcRes->ProcResV10.enhance_en = FUNCTION_ENABLE;
        } else if (pAdehazeCtx->DehazeTuningPara.dehaze_setting.en &&
                   !pAdehazeCtx->DehazeTuningPara.enhance_setting.en) {
            ProcRes->ProcResV10.dc_en      = FUNCTION_ENABLE;
            ProcRes->ProcResV10.enhance_en = FUNCTION_DISABLE;
        } else if (!pAdehazeCtx->DehazeTuningPara.dehaze_setting.en &&
                   pAdehazeCtx->DehazeTuningPara.enhance_setting.en) {
            ProcRes->ProcResV10.dc_en      = FUNCTION_ENABLE;
            ProcRes->ProcResV10.enhance_en = FUNCTION_ENABLE;
        } else {
            ProcRes->ProcResV10.dc_en      = FUNCTION_DISABLE;
            ProcRes->ProcResV10.enhance_en = FUNCTION_DISABLE;
        }

        if (pAdehazeCtx->DehazeTuningPara.hist_setting.en)
            ProcRes->ProcResV10.hist_en = FUNCTION_ENABLE;
        else
            ProcRes->ProcResV10.hist_en = FUNCTION_DISABLE;
    } else {
        ProcRes->ProcResV10.dc_en      = FUNCTION_DISABLE;
        ProcRes->ProcResV10.enhance_en = FUNCTION_DISABLE;
        ProcRes->ProcResV10.hist_en    = FUNCTION_DISABLE;
    }

    dehaze_enable = (ProcRes->ProcResV10.dc_en & FUNCTION_ENABLE) &&
                    (!(ProcRes->ProcResV10.enhance_en & FUNCTION_ENABLE));
    enhance_enable = (ProcRes->ProcResV10.dc_en & FUNCTION_ENABLE) &&
                     (ProcRes->ProcResV10.enhance_en & FUNCTION_ENABLE);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 ProcRes->ProcResV10.enable, dehaze_enable, enhance_enable,
                 ProcRes->ProcResV10.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeParams(CalibDbV2_dehaze_v10_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes,
                     float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int iso_len = pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO_len;
    // dehaze_self_adp[7]
    float dc_min_th  = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                   pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dc_min_th,
                                   CtrlValue, iso_len);
    float dc_max_th  = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                   pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dc_max_th,
                                   CtrlValue, iso_len);
    float yhist_th   = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                  pCalib->DehazeTuningPara.dehaze_setting.DehazeData.yhist_th,
                                  CtrlValue, iso_len);
    float yblk_th    = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                 pCalib->DehazeTuningPara.dehaze_setting.DehazeData.yblk_th,
                                 CtrlValue, iso_len);
    float dark_th    = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                 pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dark_th,
                                 CtrlValue, iso_len);
    float bright_min = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                    pCalib->DehazeTuningPara.dehaze_setting.DehazeData.bright_min,
                                    CtrlValue, iso_len);
    float bright_max = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                    pCalib->DehazeTuningPara.dehaze_setting.DehazeData.bright_max,
                                    CtrlValue, iso_len);

    // dehaze_range_adj[6]
    float wt_max =
        LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                     pCalib->DehazeTuningPara.dehaze_setting.DehazeData.wt_max, CtrlValue, iso_len);
    float air_max   = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                 pCalib->DehazeTuningPara.dehaze_setting.DehazeData.air_max,
                                 CtrlValue, iso_len);
    float air_min   = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                 pCalib->DehazeTuningPara.dehaze_setting.DehazeData.air_min,
                                 CtrlValue, iso_len);
    float tmax_base = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                   pCalib->DehazeTuningPara.dehaze_setting.DehazeData.tmax_base,
                                   CtrlValue, iso_len);
    float tmax_off  = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                  pCalib->DehazeTuningPara.dehaze_setting.DehazeData.tmax_off,
                                  CtrlValue, iso_len);
    float tmax_max  = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                  pCalib->DehazeTuningPara.dehaze_setting.DehazeData.tmax_max,
                                  CtrlValue, iso_len);

    // dehaze_iir_control[5]
    float stab_fnum  = pCalib->DehazeTuningPara.dehaze_setting.stab_fnum;
    float sigma      = pCalib->DehazeTuningPara.dehaze_setting.sigma;
    float wt_sigma   = pCalib->DehazeTuningPara.dehaze_setting.wt_sigma;
    float air_sigma  = pCalib->DehazeTuningPara.dehaze_setting.air_sigma;
    float tmax_sigma = pCalib->DehazeTuningPara.dehaze_setting.tmax_sigma;

    float cfg_wt =
        LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                     pCalib->DehazeTuningPara.dehaze_setting.DehazeData.cfg_wt, CtrlValue, iso_len);
    float cfg_air  = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                 pCalib->DehazeTuningPara.dehaze_setting.DehazeData.cfg_air,
                                 CtrlValue, iso_len);
    float cfg_tmax = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                  pCalib->DehazeTuningPara.dehaze_setting.DehazeData.cfg_tmax,
                                  CtrlValue, iso_len);

    // dehaze_bi_pAdehazeCtx[4]
    float dc_thed     = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                 pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dc_thed,
                                 CtrlValue, iso_len);
    float dc_weitcur  = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                    pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dc_weitcur,
                                    CtrlValue, iso_len);
    float air_thed    = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                  pCalib->DehazeTuningPara.dehaze_setting.DehazeData.air_thed,
                                  CtrlValue, iso_len);
    float air_weitcur = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO,
                                     pCalib->DehazeTuningPara.dehaze_setting.DehazeData.air_weitcur,
                                     CtrlValue, iso_len);

    // dehaze_dc_bf_h[25]
    float dc_bf_h[25] = {12.0000, 17.0000, 19.0000, 17.0000, 12.0000, 17.0000, 25.0000,
                         28.0000, 25.0000, 17.0000, 19.0000, 28.0000, 32.0000, 28.0000,
                         19.0000, 17.0000, 25.0000, 28.0000, 25.0000, 17.0000, 12.0000,
                         17.0000, 19.0000, 17.0000, 12.0000};

    // dehaze_air_bf_h[9],dehaze_gaus_h[9]
    float air_bf_h[9] = {25.0000, 28.0000, 25.0000, 28.0000, 32.0000,
                         28.0000, 25.0000, 28.0000, 25.0000};
    float gaus_h[9]   = {2.0000, 4.0000, 2.0000, 4.0000, 8.0000, 4.0000, 2.0000, 4.0000, 2.0000};

    LOGD_ADEHAZE(
        "%s dc_min_th:%f dc_max_th:%f yhist_th:%f yblk_th:%f dark_th:%f bright_min:%f "
        "bright_max:%f\n",
        __func__, dc_min_th, dc_max_th, yhist_th, yblk_th, dark_th, bright_min, bright_max);
    LOGD_ADEHAZE("%s wt_max:%f air_max:%f air_min:%f tmax_base:%f tmax_off:%f tmax_max:%f\n",
                 __func__, wt_max, air_max, air_min, tmax_base, tmax_off, tmax_max);
    LOGD_ADEHAZE("%s stab_fnum:%f sigma:%f wt_sigma:%f air_sigma:%f tmax_sigma:%f\n", __func__,
                 stab_fnum, sigma, wt_sigma, air_sigma, tmax_sigma);
    LOGD_ADEHAZE("%s  cfg_wt:%f cfg_air:%f cfg_tmax:%f\n", __func__, cfg_wt, cfg_air, cfg_tmax);
    LOGD_ADEHAZE("%s dc_thed:%f dc_weitcur:%f air_thed:%f air_weitcur:%f\n", __func__, dc_thed,
                 dc_weitcur, air_thed, air_weitcur);

    int rawWidth                   = 1920;
    int rawHeight                  = 1080;
    ProcRes->ProcResV10.dc_min_th  = int(dc_min_th);  // 0~255, (8bit) dc_min_th
    ProcRes->ProcResV10.dc_max_th  = int(dc_max_th);  // 0~255, (8bit) dc_max_th
    ProcRes->ProcResV10.yhist_th   = int(yhist_th);   // 0~255, (8bit) yhist_th
    ProcRes->ProcResV10.yblk_th    = int(yblk_th * ((rawWidth + 15) / 16) *
                                      ((rawHeight + 15) / 16));  // default:28,(9bit) yblk_th
    ProcRes->ProcResV10.dark_th    = int(dark_th);                  // 0~255, (8bit) dark_th
    ProcRes->ProcResV10.bright_min = int(bright_min);               // 0~255, (8bit) bright_min
    ProcRes->ProcResV10.bright_max = int(bright_max);               // 0~255, (8bit) bright_max

    ProcRes->ProcResV10.wt_max    = int(wt_max * 256);     // 0~255, (9bit) wt_max
    ProcRes->ProcResV10.air_min   = int(air_min);          // 0~255, (8bit) air_min
    ProcRes->ProcResV10.air_max   = int(air_max);          // 0~256, (8bit) air_max
    ProcRes->ProcResV10.tmax_base = int(tmax_base);        // 0~255, (8bit) tmax_base
    ProcRes->ProcResV10.tmax_off  = int(tmax_off * 1024);  // 0~1024,(10bit) tmax_off
    ProcRes->ProcResV10.tmax_max  = int(tmax_max * 1024);  // 0~1024,(10bit) tmax_max

    ProcRes->ProcResV10.stab_fnum = int(stab_fnum);  // 1~31,  (5bit) stab_fnum
    ProcRes->ProcResV10.iir_sigma = int(sigma);      // 0~255, (8bit) sigma
    ProcRes->ProcResV10.iir_wt_sigma =
        int(wt_sigma * 8 + 0.5);                          //       (11bit),8bit+3bit, wt_sigma
    ProcRes->ProcResV10.iir_air_sigma  = int(air_sigma);  //       (8bit) air_sigma
    ProcRes->ProcResV10.iir_tmax_sigma = int(tmax_sigma * 1024 + 0.5);  //       (11bit) tmax_sigma

    ProcRes->ProcResV10.cfg_wt   = int(cfg_wt * 256);     // 0~256, (9bit) cfg_wt
    ProcRes->ProcResV10.cfg_air  = int(cfg_air);          // 0~255, (8bit) cfg_air
    ProcRes->ProcResV10.cfg_tmax = int(cfg_tmax * 1024);  // 0~1024,(11bit) cfg_tmax

    ProcRes->ProcResV10.dc_thed     = int(dc_thed);                  // 0~255, (8bit) dc_thed
    ProcRes->ProcResV10.dc_weitcur  = int(dc_weitcur * 256 + 0.5);   // 0~256, (9bit) dc_weitcur
    ProcRes->ProcResV10.air_thed    = int(air_thed);                 // 0~255, (8bit) air_thed
    ProcRes->ProcResV10.air_weitcur = int(air_weitcur * 256 + 0.5);  // 0~256, (9bit) air_weitcur

    ProcRes->ProcResV10.gaus_h0          = int(gaus_h[4]);  // h0~h2  从大到小
    ProcRes->ProcResV10.gaus_h1          = int(gaus_h[1]);
    ProcRes->ProcResV10.gaus_h2          = int(gaus_h[0]);
    ProcRes->ProcResV10.sw_dhaz_dc_bf_h0 = int(dc_bf_h[12]);  // h0~h5  从大到小
    ProcRes->ProcResV10.sw_dhaz_dc_bf_h1 = int(dc_bf_h[7]);
    ProcRes->ProcResV10.sw_dhaz_dc_bf_h2 = int(dc_bf_h[6]);
    ProcRes->ProcResV10.sw_dhaz_dc_bf_h3 = int(dc_bf_h[2]);
    ProcRes->ProcResV10.sw_dhaz_dc_bf_h4 = int(dc_bf_h[1]);
    ProcRes->ProcResV10.sw_dhaz_dc_bf_h5 = int(dc_bf_h[0]);
    ProcRes->ProcResV10.air_bf_h0        = int(air_bf_h[4]);  // h0~h2  从大到小
    ProcRes->ProcResV10.air_bf_h1        = int(air_bf_h[1]);
    ProcRes->ProcResV10.air_bf_h2        = int(air_bf_h[0]);

    if (ProcRes->ProcResV10.dc_en && !(ProcRes->ProcResV10.enhance_en)) {
        LOGD_ADEHAZE(
            "%s dc_min_th:%d dc_max_th:%d yhist_th:%d yblk_th:%d dark_th:%d bright_min:%d "
            "bright_max:%d\n",
            __func__, ProcRes->ProcResV10.dc_min_th, ProcRes->ProcResV10.dc_max_th,
            ProcRes->ProcResV10.yhist_th, ProcRes->ProcResV10.yblk_th, ProcRes->ProcResV10.dark_th,
            ProcRes->ProcResV10.bright_min, ProcRes->ProcResV10.bright_max);
        LOGD_ADEHAZE("%s wt_max:%d air_max:%d air_min:%d tmax_base:%d tmax_off:%d tmax_max:%d\n",
                     __func__, ProcRes->ProcResV10.wt_max, ProcRes->ProcResV10.air_max,
                     ProcRes->ProcResV10.air_min, ProcRes->ProcResV10.tmax_base,
                     ProcRes->ProcResV10.tmax_off, ProcRes->ProcResV10.tmax_max);
        LOGD_ADEHAZE("%s stab_fnum:%d sigma:%d wt_sigma:%d air_sigma:%d tmax_sigma:%d\n", __func__,
                     ProcRes->ProcResV10.stab_fnum, ProcRes->ProcResV10.iir_sigma,
                     ProcRes->ProcResV10.iir_wt_sigma, ProcRes->ProcResV10.iir_air_sigma,
                     ProcRes->ProcResV10.iir_tmax_sigma);
        LOGD_ADEHAZE("%s  cfg_wt:%d cfg_air:%d cfg_tmax:%d\n", __func__, ProcRes->ProcResV10.cfg_wt,
                     ProcRes->ProcResV10.cfg_air, ProcRes->ProcResV10.cfg_tmax);
        LOGD_ADEHAZE("%s dc_thed:%d dc_weitcur:%d air_thed:%d air_weitcur:%d\n", __func__,
                     ProcRes->ProcResV10.dc_thed, ProcRes->ProcResV10.dc_weitcur,
                     ProcRes->ProcResV10.air_thed, ProcRes->ProcResV10.air_weitcur);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetEnhanceParams(CalibDbV2_dehaze_v10_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes,
                      float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int iso_len         = pCalib->DehazeTuningPara.enhance_setting.EnhanceData.ISO_len;
    float enhance_value = LinearInterp(
        pCalib->DehazeTuningPara.enhance_setting.EnhanceData.ISO,
        pCalib->DehazeTuningPara.enhance_setting.EnhanceData.enhance_value, CtrlValue, iso_len);
    ProcRes->ProcResV10.enhance_value =
        int(enhance_value * 1024 + 0.5);  //       (14bit),4bit + 10bit, enhance_value

    if (ProcRes->ProcResV10.dc_en && ProcRes->ProcResV10.enhance_en)
        LOGD_ADEHAZE("%s enhance_value:%f enhance_value:0x%x\n", __func__, enhance_value,
                     ProcRes->ProcResV10.enhance_value);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetHistParams(CalibDbV2_dehaze_v10_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes,
                   float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int iso_len       = pCalib->DehazeTuningPara.hist_setting.HistData.ISO_len;
    bool hist_channel = pCalib->DehazeTuningPara.hist_setting.hist_channel;
    bool hist_para_en = pCalib->DehazeTuningPara.hist_setting.hist_para_en;
    float hist_gratio = LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO,
                                     pCalib->DehazeTuningPara.hist_setting.HistData.hist_gratio,
                                     CtrlValue, iso_len);
    float hist_th_off = LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO,
                                     pCalib->DehazeTuningPara.hist_setting.HistData.hist_th_off,
                                     CtrlValue, iso_len);
    float hist_k =
        LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO,
                     pCalib->DehazeTuningPara.hist_setting.HistData.hist_k, CtrlValue, iso_len);
    float hist_min =
        LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO,
                     pCalib->DehazeTuningPara.hist_setting.HistData.hist_min, CtrlValue, iso_len);
    float hist_scale =
        LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO,
                     pCalib->DehazeTuningPara.hist_setting.HistData.hist_scale, CtrlValue, iso_len);
    float cfg_gratio =
        LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO,
                     pCalib->DehazeTuningPara.hist_setting.HistData.cfg_gratio, CtrlValue, iso_len);

    // dehaze_hist_t0[6],dehaze_hist_t1[6],dehaze_hist_t2[6]
    float hist_conv_t0[ISP2X_DHAZ_CONV_COEFF_NUM] = {1.0000,  2.0000,  1.0000,
                                                     -1.0000, -2.0000, -1.0000};
    float hist_conv_t1[ISP2X_DHAZ_CONV_COEFF_NUM] = {1.0000, 0.0000, -1.0000,
                                                     2.0000, 0.0000, -2.0000};
    float hist_conv_t2[ISP2X_DHAZ_CONV_COEFF_NUM] = {1.0000, -2.0000, 1.0000,
                                                     2.0000, -4.0000, 2.0000};

    ProcRes->ProcResV10.hist_chn    = hist_channel ? 1 : 0;   //  hist_para_en
    ProcRes->ProcResV10.hpara_en    = hist_para_en ? 1 : 0;   //  hist_para_en
    ProcRes->ProcResV10.hist_gratio = int(hist_gratio * 8);   //       (8bit) hist_gratio
    ProcRes->ProcResV10.hist_th_off = int(hist_th_off);       //       (8bit) hist_th_off
    ProcRes->ProcResV10.hist_k      = int(hist_k * 4 + 0.5);  // 0~7    (5bit),3bit+2bit, hist_k
    ProcRes->ProcResV10.hist_min    = int(hist_min * 256);    //       (9bit) hist_min
    ProcRes->ProcResV10.cfg_gratio  = int(cfg_gratio * 256);  //       (13bit),5bit+8bit, cfg_gratio
    ProcRes->ProcResV10.hist_scale =
        int(hist_scale * 256 + 0.5);  //       (13bit),5bit + 8bit, sw_hist_scale

    for (int i = 0; i < ISP2X_DHAZ_CONV_COEFF_NUM; i++) {
        ProcRes->ProcResV10.conv_t0[i] = int(hist_conv_t0[i]);
        ProcRes->ProcResV10.conv_t1[i] = int(hist_conv_t1[i]);
        ProcRes->ProcResV10.conv_t2[i] = int(hist_conv_t2[i]);
    }

    if (ProcRes->ProcResV10.hist_en) {
        LOGD_ADEHAZE(
            "%s hist_channel:%d hist_prar_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f "
            "hist_min:%f hist_scale:%f cfg_gratio:%f\n",
            __func__, ProcRes->ProcResV10.hist_chn, ProcRes->ProcResV10.hpara_en, hist_gratio,
            hist_th_off, hist_k, hist_min, hist_scale, cfg_gratio);
        LOGD_ADEHAZE(
            "%s hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x hist_min_reg:0x%x "
            "hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n",
            __func__, ProcRes->ProcResV10.hist_gratio, ProcRes->ProcResV10.hist_th_off,
            ProcRes->ProcResV10.hist_k, ProcRes->ProcResV10.hist_min,
            ProcRes->ProcResV10.hist_scale, ProcRes->ProcResV10.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void AdehazeApiToolProcess(CalibDbV2_dehaze_v10_t* pStool, RkAiqAdehazeProcResult_t* ProcRes,
                           float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE("%s: Adehaze in api TOOL !!! \n", __func__);

    // cfg setting
    ProcRes->ProcResV10.cfg_alpha =
        (int)LIMIT_VALUE((pStool->DehazeTuningPara.cfg_alpha * 256.0), BIT_8_MAX, BIT_MIN);
    LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, ProcRes->ProcResV10.cfg_alpha);

    // fuction enable
    EnableSetting(pStool, ProcRes);

    // dehaze setting
    GetDehazeParams(pStool, ProcRes, CtrlValue);

    // enhance setting
    GetEnhanceParams(pStool, ProcRes, CtrlValue);

    // hist setting
    GetHistParams(pStool, ProcRes, CtrlValue);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
}

void AdehazeEnhanceApiBypassProcess(CalibDbV2_dehaze_v10_t* pCalib,
                                    RkAiqAdehazeProcResult_t* ProcRes, float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE(" %s: Adehaze Api off!!!\n", __func__);

    // cfg setting
    ProcRes->ProcResV10.cfg_alpha =
        (int)LIMIT_VALUE((pCalib->DehazeTuningPara.cfg_alpha * 256.0), BIT_8_MAX, BIT_MIN);
    // LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, ProcRes->ProcResV10.cfg_alpha);

    // enable setting
    EnableSetting(pCalib, ProcRes);

    // dehaze setting
    GetDehazeParams(pCalib, ProcRes, CtrlValue);

    // enhance setting
    GetEnhanceParams(pCalib, ProcRes, CtrlValue);

    // hist setting
    GetHistParams(pCalib, ProcRes, CtrlValue);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
}

void AdehazeEnhanceApiOffProcess(CalibDbV2_dehaze_v10_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes,
                                 float CtrlValue) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE(" %s: Adehaze Api off!!!\n", __func__);

    // enable setting
    ProcRes->ProcResV10.enable = true;
    if (pCalib->DehazeTuningPara.enhance_setting.en) {
        ProcRes->ProcResV10.dc_en      = true;
        ProcRes->ProcResV10.enhance_en = true;
    } else {
        ProcRes->ProcResV10.dc_en      = false;
        ProcRes->ProcResV10.enhance_en = false;
    }

    // cfg setting
    ProcRes->ProcResV10.cfg_alpha =
        (int)LIMIT_VALUE((pCalib->DehazeTuningPara.cfg_alpha * 256.0), BIT_8_MAX, BIT_MIN);

    // dehaze setting
    GetDehazeParams(pCalib, ProcRes, CtrlValue);

    // enhance setting
    GetEnhanceParams(pCalib, ProcRes, CtrlValue);

    // hist setting
    GetHistParams(pCalib, ProcRes, CtrlValue);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
}

void AdehazeGetStats(AdehazeHandle_t* pAdehazeCtx, rkisp_adehaze_stats_t* ROData) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);
    LOGV_ADEHAZE("%s: Adehaze RO data from register:\n", __FUNCTION__);

    pAdehazeCtx->stats.dehaze_stats_v10.dhaz_adp_air_base =
        ROData->dehaze_stats_v10.dhaz_adp_air_base;
    pAdehazeCtx->stats.dehaze_stats_v10.dhaz_adp_wt     = ROData->dehaze_stats_v10.dhaz_adp_wt;
    pAdehazeCtx->stats.dehaze_stats_v10.dhaz_adp_gratio = ROData->dehaze_stats_v10.dhaz_adp_gratio;
    pAdehazeCtx->stats.dehaze_stats_v10.dhaz_adp_tmax   = ROData->dehaze_stats_v10.dhaz_adp_tmax;
    for (int i = 0; i < ISP2X_DHAZ_HIST_IIR_NUM; i++) {
        pAdehazeCtx->stats.dehaze_stats_v10.h_b_iir[i] = ROData->dehaze_stats_v10.h_b_iir[i];
        pAdehazeCtx->stats.dehaze_stats_v10.h_g_iir[i] = ROData->dehaze_stats_v10.h_g_iir[i];
        pAdehazeCtx->stats.dehaze_stats_v10.h_r_iir[i] = ROData->dehaze_stats_v10.h_r_iir[i];
    }

    LOGV_ADEHAZE("%s:  dhaz_adp_air_base:%d dhaz_adp_wt:%d dhaz_adp_gratio:%d dhaz_adp_tmax:%d\n",
                 __FUNCTION__, pAdehazeCtx->stats.dehaze_stats_v10.dhaz_adp_air_base,
                 pAdehazeCtx->stats.dehaze_stats_v10.dhaz_adp_wt,
                 pAdehazeCtx->stats.dehaze_stats_v10.dhaz_adp_gratio,
                 pAdehazeCtx->stats.dehaze_stats_v10.dhaz_adp_tmax);
    for (int i = 0; i < ISP2X_DHAZ_HIST_IIR_NUM; i++) {
        LOGV_ADEHAZE("%s:  h_b_iir[%d]:%d:\n", __FUNCTION__, i,
                     pAdehazeCtx->stats.dehaze_stats_v10.h_b_iir[i]);
        LOGV_ADEHAZE("%s:  h_g_iir[%d]:%d:\n", __FUNCTION__, i,
                     pAdehazeCtx->stats.dehaze_stats_v10.h_g_iir[i]);
        LOGV_ADEHAZE("%s:  h_r_iir[%d]:%d:\n", __FUNCTION__, i,
                     pAdehazeCtx->stats.dehaze_stats_v10.h_r_iir[i]);
    }

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
        pAdehazeCtx->CurrData.V21.EnvLv = 0.0;
        return;
    }

    pAdehazeCtx->CurrData.V21.EnvLv =
        pAePreRes->ae_pre_res_rk.GlobalEnvLv[pAePreRes->ae_pre_res_rk.NormalIndex];

    // Normalize the current envLv for AEC
    pAdehazeCtx->CurrData.V21.EnvLv =
        (pAdehazeCtx->CurrData.V21.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
    pAdehazeCtx->CurrData.V21.EnvLv =
        LIMIT_VALUE(pAdehazeCtx->CurrData.V21.EnvLv, ENVLVMAX, ENVLVMIN);

    // get iso
    if (pAdehazeCtx->FrameNumber == LINEAR_NUM)
        pAdehazeCtx->CurrData.V30.ISO =
            pAePreRes->ae_pre_res_rk.LinearExp.exp_real_params.analog_gain *
            pAePreRes->ae_pre_res_rk.LinearExp.exp_real_params.digital_gain * 50.0;
    else if (pAdehazeCtx->FrameNumber == HDR_2X_NUM || pAdehazeCtx->FrameNumber == HDR_3X_NUM)
        pAdehazeCtx->CurrData.V30.ISO =
            pAePreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.analog_gain *
            pAePreRes->ae_pre_res_rk.HdrExp[1].exp_real_params.digital_gain * 50.0;

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
}

XCamReturn AdehazeGetCurrDataGroup(AdehazeHandle_t* pAdehazeCtx, RKAiqAecExpInfo_t* pAeEffExpo,
                                   XCamVideoBuffer* pAePreRes) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    int iso = 50;
    AdehazeExpInfo_t stExpInfo;
    memset(&stExpInfo, 0x00, sizeof(AdehazeExpInfo_t));

    stExpInfo.hdr_mode = 0;
    for (int i = 0; i < 3; i++) {
        stExpInfo.arIso[i]   = 50;
        stExpInfo.arAGain[i] = 1.0;
        stExpInfo.arDGain[i] = 1.0;
        stExpInfo.arTime[i]  = 0.01;
    }

    if (pAdehazeCtx->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
        stExpInfo.hdr_mode = 0;
    } else if (RK_AIQ_HDR_GET_WORKING_MODE(pAdehazeCtx->working_mode) ==
               RK_AIQ_WORKING_MODE_ISP_HDR2) {
        stExpInfo.hdr_mode = 1;
    } else if (RK_AIQ_HDR_GET_WORKING_MODE(pAdehazeCtx->working_mode) ==
               RK_AIQ_WORKING_MODE_ISP_HDR3) {
        stExpInfo.hdr_mode = 2;
    }

    if (pAeEffExpo != NULL) {
        if (pAdehazeCtx->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
            stExpInfo.arAGain[0] = pAeEffExpo->LinearExp.exp_real_params.analog_gain;
            stExpInfo.arDGain[0] = pAeEffExpo->LinearExp.exp_real_params.digital_gain;
            stExpInfo.arTime[0]  = pAeEffExpo->LinearExp.exp_real_params.integration_time;
            stExpInfo.arIso[0]   = stExpInfo.arAGain[0] * stExpInfo.arDGain[0] * 50;
        } else {
            for (int i = 0; i < 3; i++) {
                stExpInfo.arAGain[i] = pAeEffExpo->HdrExp[i].exp_real_params.analog_gain;
                stExpInfo.arDGain[i] = pAeEffExpo->HdrExp[i].exp_real_params.digital_gain;
                stExpInfo.arTime[i]  = pAeEffExpo->HdrExp[i].exp_real_params.integration_time;
                stExpInfo.arIso[i]   = stExpInfo.arAGain[i] * stExpInfo.arDGain[i] * 50;

                LOGD_ADEHAZE("index:%d again:%f dgain:%f time:%f iso:%d hdr_mode:%d\n", i,
                             stExpInfo.arAGain[i], stExpInfo.arDGain[i], stExpInfo.arTime[i],
                             stExpInfo.arIso[i], stExpInfo.hdr_mode);
            }
        }
    } else {
        ret = XCAM_RETURN_ERROR_PARAM;
    }

    iso                          = stExpInfo.arIso[stExpInfo.hdr_mode];
    pAdehazeCtx->CurrDataV10.ISO = (float)iso;

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
    return ret;
}

XCamReturn AdehazeGetCurrData(AdehazeHandle_t* pAdehazeCtx, RkAiqAlgoProcAdhaz* pProcPara) {
    LOG1_ADEHAZE("%s:enter!\n", __FUNCTION__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    int iso = 50;
    AdehazeExpInfo_t stExpInfo;
    memset(&stExpInfo, 0x00, sizeof(AdehazeExpInfo_t));

    stExpInfo.hdr_mode = 0;
    for (int i = 0; i < 3; i++) {
        stExpInfo.arIso[i]   = 50;
        stExpInfo.arAGain[i] = 1.0;
        stExpInfo.arDGain[i] = 1.0;
        stExpInfo.arTime[i]  = 0.01;
    }

    if (pAdehazeCtx->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
        stExpInfo.hdr_mode = 0;
    } else if (RK_AIQ_HDR_GET_WORKING_MODE(pAdehazeCtx->working_mode) ==
               RK_AIQ_WORKING_MODE_ISP_HDR2) {
        stExpInfo.hdr_mode = 1;
    } else if (RK_AIQ_HDR_GET_WORKING_MODE(pAdehazeCtx->working_mode) ==
               RK_AIQ_WORKING_MODE_ISP_HDR3) {
        stExpInfo.hdr_mode = 2;
    }

    XCamVideoBuffer* xCamAePreRes = pProcPara->com.u.proc.res_comb->ae_pre_res;
    RkAiqAlgoPreResAe* pAEPreRes  = NULL;
    if (xCamAePreRes) {
        pAEPreRes = (RkAiqAlgoPreResAe*)xCamAePreRes->map(xCamAePreRes);
        if (pAdehazeCtx->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
            stExpInfo.arAGain[0] = pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.analog_gain;
            stExpInfo.arDGain[0] = pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.digital_gain;
            stExpInfo.arTime[0] =
                pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.integration_time;
            stExpInfo.arIso[0] = stExpInfo.arAGain[0] * stExpInfo.arDGain[0] * 50;
        } else {
            for (int i = 0; i < 3; i++) {
                stExpInfo.arAGain[i] =
                    pAEPreRes->ae_pre_res_rk.HdrExp[i].exp_real_params.analog_gain;
                stExpInfo.arDGain[i] =
                    pAEPreRes->ae_pre_res_rk.HdrExp[i].exp_real_params.digital_gain;
                stExpInfo.arTime[i] =
                    pAEPreRes->ae_pre_res_rk.HdrExp[i].exp_real_params.integration_time;
                stExpInfo.arIso[i] = stExpInfo.arAGain[i] * stExpInfo.arDGain[i] * 50;

                LOGD_ADEHAZE("index:%d again:%f dgain:%f time:%f iso:%d hdr_mode:%d\n", i,
                             stExpInfo.arAGain[i], stExpInfo.arDGain[i], stExpInfo.arTime[i],
                             stExpInfo.arIso[i], stExpInfo.hdr_mode);
            }
        }
    } else {
        ret = XCAM_RETURN_ERROR_PARAM;
    }

    iso                          = stExpInfo.arIso[stExpInfo.hdr_mode];
    pAdehazeCtx->CurrDataV10.ISO = (float)iso;

    LOG1_ADEHAZE("%s:exit!\n", __FUNCTION__);
    return ret;
}

XCamReturn AdehazeInit(AdehazeHandle_t** pAdehazeCtx, CamCalibDbV2Context_t* pCalib) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret          = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t* handle = (AdehazeHandle_t*)calloc(1, sizeof(AdehazeHandle_t));

    // isp20
    CalibDbV2_dehaze_v10_t* calibv2_adehaze_calib_V10 =
        (CalibDbV2_dehaze_v10_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, adehaze_calib));
    memcpy(&handle->CalibV10, calibv2_adehaze_calib_V10, sizeof(CalibDbV2_dehaze_v10_t));

    handle->PreDataV10.ISO     = 50.0;
    handle->PreDataV10.ApiMode = DEHAZE_API_AUTO;

    // set api default
    handle->AdehazeAtrrV10.mode                                               = DEHAZE_API_AUTO;
    handle->AdehazeAtrrV10.stManual.Enable                                    = true;
    handle->AdehazeAtrrV10.stManual.cfg_alpha                                 = 1.0;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.en                         = false;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.air_lc_en                  = true;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.stab_fnum                  = 8;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.sigma                      = 6;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.wt_sigma                   = 8;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.air_sigma                  = 120;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.tmax_sigma                 = 0.01;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.pre_wet                    = 0.01;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.dc_min_th       = 64;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.dc_max_th       = 192;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.yhist_th        = 249;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.yblk_th         = 0.002;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.dark_th         = 250;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.bright_min      = 180;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.bright_max      = 240;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.wt_max          = 0.9;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.air_min         = 200;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.air_max         = 250;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.tmax_base       = 125;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.tmax_off        = 0.1;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.tmax_max        = 0.8;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.cfg_wt          = 0.8;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.cfg_air         = 210;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.cfg_tmax        = 0.2;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.dc_weitcur      = 1;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.bf_weight       = 0.5;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.range_sigma     = 0.14;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.space_sigma_pre = 0.14;
    handle->AdehazeAtrrV10.stManual.dehaze_setting.DehazeData.space_sigma_cur = 0.14;

    handle->AdehazeAtrrV10.stManual.enhance_setting.en                         = true;
    handle->AdehazeAtrrV10.stManual.enhance_setting.EnhanceData.enhance_value  = 1.0;
    handle->AdehazeAtrrV10.stManual.enhance_setting.EnhanceData.enhance_chroma = 1.0;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[0]           = 0;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[1]           = 64;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[2]           = 128;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[3]           = 192;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[4]           = 256;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[5]           = 320;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[6]           = 384;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[7]           = 448;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[8]           = 512;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[9]           = 576;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[10]          = 640;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[11]          = 704;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[12]          = 768;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[13]          = 832;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[14]          = 896;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[15]          = 960;
    handle->AdehazeAtrrV10.stManual.enhance_setting.enhance_curve[16]          = 1023;

    handle->AdehazeAtrrV10.stManual.hist_setting.en                   = false;
    handle->AdehazeAtrrV10.stManual.hist_setting.hist_para_en         = true;
    handle->AdehazeAtrrV10.stManual.hist_setting.HistData.hist_gratio = 2;
    handle->AdehazeAtrrV10.stManual.hist_setting.HistData.hist_th_off = 64;
    handle->AdehazeAtrrV10.stManual.hist_setting.HistData.hist_k      = 2;
    handle->AdehazeAtrrV10.stManual.hist_setting.HistData.hist_min    = 0.015;
    handle->AdehazeAtrrV10.stManual.hist_setting.HistData.hist_scale  = 0.09;
    handle->AdehazeAtrrV10.stManual.hist_setting.HistData.cfg_gratio  = 2;

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

    float CtrlValue = 0.0;

    // todo

    // store pre data
    pAdehazeCtx->PreDataV10.ISO = pAdehazeCtx->CurrDataV10.ISO;
    pAdehazeCtx->PreDataV10.ApiMode = pAdehazeCtx->CurrDataV10.ApiMode;

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}

bool AdehazeByPassProcessing(AdehazeHandle_t* pAdehazeCtx) {
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    bool ret   = false;
    float diff = 0.0;

    if (pAdehazeCtx->FrameID <= 2) pAdehazeCtx->byPassProc = false;
    if (pAdehazeCtx->AdehazeAtrrV10.mode > DEHAZE_API_AUTO)
        pAdehazeCtx->byPassProc = false;
    else if (pAdehazeCtx->AdehazeAtrrV10.mode != pAdehazeCtx->PreDataV10.ApiMode)
        pAdehazeCtx->byPassProc = false;
    else {
        diff = (pAdehazeCtx->PreDataV10.ISO - pAdehazeCtx->CurrDataV10.ISO) /
               pAdehazeCtx->PreDataV10.ISO;
        if (diff > pAdehazeCtx->CalibV10.DehazeTuningPara.ByPassThr ||
            diff < (0 - pAdehazeCtx->CalibV10.DehazeTuningPara.ByPassThr))
            pAdehazeCtx->byPassProc = false;
        else
            pAdehazeCtx->byPassProc = true;
    }

    ret = pAdehazeCtx->byPassProc;

    LOGD_ADEHAZE("%s:FrameID:%d byPassProc:%d ISO:%f\n", __func__, pAdehazeCtx->FrameID, ret,
                 pAdehazeCtx->CurrData.V30.ISO);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}
