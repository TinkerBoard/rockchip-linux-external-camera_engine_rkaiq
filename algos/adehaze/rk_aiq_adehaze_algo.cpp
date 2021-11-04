/*
 * rk_aiq_adehaze_algo.c
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
#include <string.h>
#include "rk_aiq_algo_types_int.h"
#include "rk_aiq_adehaze_algo.h"
#include "xcam_log.h"

#define LIMIT_VALUE(value,max_value,min_value)      (value > max_value? max_value : value < min_value ? min_value : value)

float  LinearInterp(const float *pX, const float *pY, float posx, int XSize)
{
    int index;
    float yOut = 0;

    if (posx >= pX[XSize - 1])
    {
        yOut = pY[XSize - 1];
    }
    else if (posx <= pX[0])
    {
        yOut = pY[0];
    }
    else
    {
        index = 0;
        while((posx >= pX[index]) && (index < XSize))
        {
            index++;
        }
        index -= 1;
        yOut = ((pY[index + 1] - pY[index]) / (pX[index + 1] - pX[index]) * (posx - pX[index]))
               + pY[index];
    }

    return yOut;
}

int LinearInterpEnable(const float *pX, const unsigned char *pY, float posx, int XSize)
{
    int index;
    float out;
    float yOut = 0;
    if (posx >= pX[XSize - 1])
    {
        out = (float)pY[XSize - 1];
    }
    else if (posx <= pX[0])
    {
        out = pY[0];
    }
    else
    {
        index = 0;
        while((posx >= pX[index]) && (index < XSize))
        {
            index++;
        }
        index -= 1;
        out = ((pY[index + 1] - pY[index]) / (pX[index + 1] - pX[index]) * (posx - pX[index]))
              + pY[index];
    }
    yOut = out > 0.5 ? 1 : 0;

    return yOut;

}

void EnableSetting(CalibDbV2_dehaze_V20_t* pAdehazeCtx, RkAiqAdehazeProcResult_t* ProcRes)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    ProcRes->ProcResV20.enable = true;

    bool dehaze_enable = false;
    bool enhance_enable = false;

    if(pAdehazeCtx->DehazeTuningPara.Enable) {
        if(pAdehazeCtx->DehazeTuningPara.dehaze_setting.en && pAdehazeCtx->DehazeTuningPara.enhance_setting.en)
        {
            ProcRes->ProcResV20.dc_en = 1;
            ProcRes->ProcResV20.enhance_en = 1;
        }
        else if(pAdehazeCtx->DehazeTuningPara.dehaze_setting.en && !pAdehazeCtx->DehazeTuningPara.enhance_setting.en)
        {
            ProcRes->ProcResV20.dc_en = 1;
            ProcRes->ProcResV20.enhance_en = 0;
        }
        else if(!pAdehazeCtx->DehazeTuningPara.dehaze_setting.en && pAdehazeCtx->DehazeTuningPara.enhance_setting.en)
        {
            ProcRes->ProcResV20.dc_en = 1;
            ProcRes->ProcResV20.enhance_en = 1;
        }
        else
        {
            ProcRes->ProcResV20.dc_en = 0;
            ProcRes->ProcResV20.enhance_en = 0;
        }

        if(pAdehazeCtx->DehazeTuningPara.hist_setting.en)
            ProcRes->ProcResV20.hist_en = 0x1;
        else
            ProcRes->ProcResV20.hist_en = 0;
    }
    else {
        ProcRes->ProcResV20.dc_en = 0;
        ProcRes->ProcResV20.enhance_en = 0;
        ProcRes->ProcResV20.hist_en = 0;
    }

    dehaze_enable = (ProcRes->ProcResV20.dc_en & 0x1) && (!(ProcRes->ProcResV20.enhance_en & 0x1));
    enhance_enable = (ProcRes->ProcResV20.dc_en & 0x1) && (ProcRes->ProcResV20.enhance_en & 0x1);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__, ProcRes->ProcResV20.enable,
                 dehaze_enable, enhance_enable, ProcRes->ProcResV20.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void EnableSettingV21(CalibDbDehazeV21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    ProcRes->ProcResV21.enable = pCalibV21->Enable;

    bool dehaze_enable = false;
    bool enhance_enable = false;
    if(pCalibV21->Enable) {
        if(pCalibV21->dehaze_setting.en && pCalibV21->enhance_setting.en)
        {
            ProcRes->ProcResV21.dc_en = 1;
            ProcRes->ProcResV21.enhance_en = 1;
        }
        else if(pCalibV21->dehaze_setting.en && !pCalibV21->enhance_setting.en)
        {
            ProcRes->ProcResV21.dc_en = 1;
            ProcRes->ProcResV21.enhance_en = 0;
        }
        else if(!pCalibV21->dehaze_setting.en && pCalibV21->enhance_setting.en)
        {
            ProcRes->ProcResV21.dc_en = 1;
            ProcRes->ProcResV21.enhance_en = 1;
        }
        else
        {
            ProcRes->ProcResV21.dc_en = 0;
            ProcRes->ProcResV21.enhance_en = 0;
        }

        if(pCalibV21->hist_setting.en)
            ProcRes->ProcResV21.hist_en = 0x1;
        else
            ProcRes->ProcResV21.hist_en = 0;
    }
    else {
        ProcRes->ProcResV21.dc_en = 0;
        ProcRes->ProcResV21.enhance_en = 0;
        ProcRes->ProcResV21.hist_en = 0;
    }
    dehaze_enable = (ProcRes->ProcResV21.dc_en & 0x1) && (!(ProcRes->ProcResV21.enhance_en & 0x1));
    enhance_enable = (ProcRes->ProcResV21.dc_en & 0x1) && (ProcRes->ProcResV21.enhance_en & 0x1);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 ProcRes->ProcResV21.enable, dehaze_enable, enhance_enable, ProcRes->ProcResV21.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void EnableSettingV30(CalibDbDehazeV21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    ProcRes->ProcResV30.enable = pCalibV21->Enable;

    bool dehaze_enable = false;
    bool enhance_enable = false;
    if(pCalibV21->Enable) {
        if(pCalibV21->dehaze_setting.en && pCalibV21->enhance_setting.en)
        {
            ProcRes->ProcResV30.dc_en = 1;
            ProcRes->ProcResV30.enhance_en = 1;
        }
        else if(pCalibV21->dehaze_setting.en && !pCalibV21->enhance_setting.en)
        {
            ProcRes->ProcResV30.dc_en = 1;
            ProcRes->ProcResV30.enhance_en = 0;
        }
        else if(!pCalibV21->dehaze_setting.en && pCalibV21->enhance_setting.en)
        {
            ProcRes->ProcResV30.dc_en = 1;
            ProcRes->ProcResV30.enhance_en = 1;
        }
        else
        {
            ProcRes->ProcResV30.dc_en = 0;
            ProcRes->ProcResV30.enhance_en = 0;
        }

        if(pCalibV21->hist_setting.en)
            ProcRes->ProcResV30.hist_en = 0x1;
        else
            ProcRes->ProcResV30.hist_en = 0;
    }
    else {
        ProcRes->ProcResV30.dc_en = 0;
        ProcRes->ProcResV30.enhance_en = 0;
        ProcRes->ProcResV30.hist_en = 0;
    }
    dehaze_enable = (ProcRes->ProcResV30.dc_en & 0x1) && (!(ProcRes->ProcResV30.enhance_en & 0x1));
    enhance_enable = (ProcRes->ProcResV30.dc_en & 0x1) && (ProcRes->ProcResV30.enhance_en & 0x1);

    LOGD_ADEHAZE(" %s: Dehaze module en:%d Dehaze en:%d, Enhance en:%d, Hist en:%d\n", __func__,
                 ProcRes->ProcResV30.enable, dehaze_enable, enhance_enable, ProcRes->ProcResV30.hist_en);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeParams(CalibDbV2_dehaze_V20_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int iso_len = pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO_len;
    // dehaze_self_adp[7]
    float dc_min_th = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dc_min_th, variate, iso_len);
    float dc_max_th = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dc_max_th, variate, iso_len);
    float yhist_th = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.yhist_th, variate,  iso_len);
    float yblk_th = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.yblk_th, variate, iso_len);
    float dark_th = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dark_th, variate, iso_len);
    float bright_min = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.bright_min, variate, iso_len);
    float bright_max = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.bright_max, variate, iso_len);

    // dehaze_range_adj[6]
    float wt_max = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.wt_max, variate, iso_len);
    float air_max = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.air_max, variate, iso_len);
    float air_min = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.air_min, variate, iso_len);
    float tmax_base = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.tmax_base, variate, iso_len);
    float tmax_off = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.tmax_off, variate, iso_len);
    float tmax_max = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.tmax_max, variate, iso_len);

    // dehaze_iir_control[5]
    float stab_fnum = pCalib->DehazeTuningPara.dehaze_setting.stab_fnum;
    float sigma = pCalib->DehazeTuningPara.dehaze_setting.sigma;
    float wt_sigma = pCalib->DehazeTuningPara.dehaze_setting.wt_sigma;
    float air_sigma = pCalib->DehazeTuningPara.dehaze_setting.air_sigma;
    float tmax_sigma = pCalib->DehazeTuningPara.dehaze_setting.tmax_sigma;

    float cfg_wt = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.cfg_wt, variate, iso_len);
    float cfg_air = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.cfg_air, variate, iso_len);
    float cfg_tmax = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.cfg_tmax, variate, iso_len);

    // dehaze_bi_pAdehazeCtx[4]
    float dc_thed = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dc_thed, variate, iso_len);
    float dc_weitcur = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.dc_weitcur, variate, iso_len);
    float air_thed = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.air_thed, variate, iso_len);
    float air_weitcur = LinearInterp(pCalib->DehazeTuningPara.dehaze_setting.DehazeData.ISO, pCalib->DehazeTuningPara.dehaze_setting.DehazeData.air_weitcur, variate, iso_len);

    // dehaze_dc_bf_h[25]
    float dc_bf_h[25] = {12.0000, 17.0000, 19.0000, 17.0000, 12.0000,
                         17.0000, 25.0000, 28.0000, 25.0000, 17.0000,
                         19.0000, 28.0000, 32.0000, 28.0000, 19.0000,
                         17.0000, 25.0000, 28.0000, 25.0000, 17.0000,
                         12.0000, 17.0000, 19.0000, 17.0000, 12.0000
                        };

    // dehaze_air_bf_h[9],dehaze_gaus_h[9]
    float air_bf_h[9] = {25.0000, 28.0000, 25.0000,
                         28.0000, 32.0000, 28.0000,
                         25.0000, 28.0000, 25.0000
                        };
    float gaus_h[9] = {2.0000, 4.0000, 2.0000,
                       4.0000, 8.0000, 4.0000,
                       2.0000, 4.0000, 2.0000
                      };

    LOGD_ADEHAZE("%s dc_min_th:%f dc_max_th:%f yhist_th:%f yblk_th:%f dark_th:%f bright_min:%f bright_max:%f\n", __func__, dc_min_th, dc_max_th, yhist_th, yblk_th, dark_th, bright_min, bright_max);
    LOGD_ADEHAZE("%s wt_max:%f air_max:%f air_min:%f tmax_base:%f tmax_off:%f tmax_max:%f\n", __func__, wt_max, air_max, air_min, tmax_base, tmax_off, tmax_max);
    LOGD_ADEHAZE("%s stab_fnum:%f sigma:%f wt_sigma:%f air_sigma:%f tmax_sigma:%f\n", __func__, stab_fnum, sigma, wt_sigma, air_sigma, tmax_sigma);
    LOGD_ADEHAZE("%s  cfg_wt:%f cfg_air:%f cfg_tmax:%f\n", __func__, cfg_wt, cfg_air, cfg_tmax);
    LOGD_ADEHAZE("%s dc_thed:%f dc_weitcur:%f air_thed:%f air_weitcur:%f\n", __func__, dc_thed, dc_weitcur, air_thed, air_weitcur);

    int rawWidth = 1920;
    int rawHeight = 1080;
    ProcRes->ProcResV20.dc_min_th    = int(dc_min_th); //0~255, (8bit) dc_min_th
    ProcRes->ProcResV20.dc_max_th    = int(dc_max_th);  //0~255, (8bit) dc_max_th
    ProcRes->ProcResV20.yhist_th    = int(yhist_th);  //0~255, (8bit) yhist_th
    ProcRes->ProcResV20.yblk_th    = int(yblk_th * ((rawWidth + 15) / 16) * ((rawHeight + 15) / 16)); //default:28,(9bit) yblk_th
    ProcRes->ProcResV20.dark_th    = int(dark_th);  //0~255, (8bit) dark_th
    ProcRes->ProcResV20.bright_min   = int(bright_min);  //0~255, (8bit) bright_min
    ProcRes->ProcResV20.bright_max   = int(bright_max);  //0~255, (8bit) bright_max


    ProcRes->ProcResV20.wt_max   = int(wt_max * 256); //0~255, (9bit) wt_max
    ProcRes->ProcResV20.air_min   = int(air_min);  //0~255, (8bit) air_min
    ProcRes->ProcResV20.air_max   = int(air_max);  //0~256, (8bit) air_max
    ProcRes->ProcResV20.tmax_base   = int(tmax_base);  //0~255, (8bit) tmax_base
    ProcRes->ProcResV20.tmax_off   = int(tmax_off * 1024); //0~1024,(10bit) tmax_off
    ProcRes->ProcResV20.tmax_max   = int(tmax_max * 1024); //0~1024,(10bit) tmax_max

    ProcRes->ProcResV20.stab_fnum = int(stab_fnum);  //1~31,  (5bit) stab_fnum
    ProcRes->ProcResV20.iir_sigma = int(sigma);  //0~255, (8bit) sigma
    ProcRes->ProcResV20.iir_wt_sigma = int(wt_sigma * 8 + 0.5); //       (11bit),8bit+3bit, wt_sigma
    ProcRes->ProcResV20.iir_air_sigma = int(air_sigma);  //       (8bit) air_sigma
    ProcRes->ProcResV20.iir_tmax_sigma = int(tmax_sigma * 1024 + 0.5);  //       (11bit) tmax_sigma

    ProcRes->ProcResV20.cfg_wt = int(cfg_wt * 256); //0~256, (9bit) cfg_wt
    ProcRes->ProcResV20.cfg_air = int(cfg_air);  //0~255, (8bit) cfg_air
    ProcRes->ProcResV20.cfg_tmax = int(cfg_tmax * 1024); //0~1024,(11bit) cfg_tmax

    ProcRes->ProcResV20.dc_thed      = int(dc_thed);  //0~255, (8bit) dc_thed
    ProcRes->ProcResV20.dc_weitcur       = int(dc_weitcur * 256 + 0.5); //0~256, (9bit) dc_weitcur
    ProcRes->ProcResV20.air_thed     = int(air_thed);  //0~255, (8bit) air_thed
    ProcRes->ProcResV20.air_weitcur      = int(air_weitcur * 256 + 0.5);  //0~256, (9bit) air_weitcur

    ProcRes->ProcResV20.gaus_h0    = int(gaus_h[4]);//h0~h2  浠庡ぇ鍒板皬
    ProcRes->ProcResV20.gaus_h1    = int(gaus_h[1]);
    ProcRes->ProcResV20.gaus_h2    = int(gaus_h[0]);
    ProcRes->ProcResV20.sw_dhaz_dc_bf_h0   = int(dc_bf_h[12]);//h0~h5  浠庡ぇ鍒板皬
    ProcRes->ProcResV20.sw_dhaz_dc_bf_h1   = int(dc_bf_h[7]);
    ProcRes->ProcResV20.sw_dhaz_dc_bf_h2   = int(dc_bf_h[6]);
    ProcRes->ProcResV20.sw_dhaz_dc_bf_h3   = int(dc_bf_h[2]);
    ProcRes->ProcResV20.sw_dhaz_dc_bf_h4   = int(dc_bf_h[1]);
    ProcRes->ProcResV20.sw_dhaz_dc_bf_h5   = int(dc_bf_h[0]);
    ProcRes->ProcResV20.air_bf_h0  = int(air_bf_h[4]);//h0~h2  浠庡ぇ鍒板皬
    ProcRes->ProcResV20.air_bf_h1  = int(air_bf_h[1]);
    ProcRes->ProcResV20.air_bf_h2  = int(air_bf_h[0]);

    if(ProcRes->ProcResV20.dc_en && !(ProcRes->ProcResV20.enhance_en)) {
        LOGD_ADEHAZE("%s dc_min_th:%d dc_max_th:%d yhist_th:%d yblk_th:%d dark_th:%d bright_min:%d bright_max:%d\n", __func__, ProcRes->ProcResV20.dc_min_th,
                     ProcRes->ProcResV20.dc_max_th, ProcRes->ProcResV20.yhist_th, ProcRes->ProcResV20.yblk_th, ProcRes->ProcResV20.dark_th,
                     ProcRes->ProcResV20.bright_min, ProcRes->ProcResV20.bright_max);
        LOGD_ADEHAZE("%s wt_max:%d air_max:%d air_min:%d tmax_base:%d tmax_off:%d tmax_max:%d\n", __func__, ProcRes->ProcResV20.wt_max,
                     ProcRes->ProcResV20.air_max, ProcRes->ProcResV20.air_min, ProcRes->ProcResV20.tmax_base,
                     ProcRes->ProcResV20.tmax_off, ProcRes->ProcResV20.tmax_max);
        LOGD_ADEHAZE("%s stab_fnum:%d sigma:%d wt_sigma:%d air_sigma:%d tmax_sigma:%d\n", __func__, ProcRes->ProcResV20.stab_fnum,
                     ProcRes->ProcResV20.iir_sigma, ProcRes->ProcResV20.iir_wt_sigma, ProcRes->ProcResV20.iir_air_sigma,
                     ProcRes->ProcResV20.iir_tmax_sigma);
        LOGD_ADEHAZE("%s  cfg_wt:%d cfg_air:%d cfg_tmax:%d\n", __func__, ProcRes->ProcResV20.cfg_wt, ProcRes->ProcResV20.cfg_air, ProcRes->ProcResV20.cfg_tmax);
        LOGD_ADEHAZE("%s dc_thed:%d dc_weitcur:%d air_thed:%d air_weitcur:%d\n", __func__, ProcRes->ProcResV20.dc_thed,
                     ProcRes->ProcResV20.dc_weitcur, ProcRes->ProcResV20.air_thed, ProcRes->ProcResV20.air_weitcur);
    }


    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeParamsV21(CalibDbDehazeV21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int EnvLv_len = pCalibV21->dehaze_setting.DehazeData.EnvLv_len;
    bool air_lc_en = pCalibV21->dehaze_setting.air_lc_en;

    // dehaze_self_adp[7]
    float dc_min_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.dc_min_th, variate, EnvLv_len);
    float dc_max_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.dc_max_th, variate, EnvLv_len);
    float yhist_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.yhist_th, variate,  EnvLv_len);
    float yblk_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.yblk_th, variate, EnvLv_len);
    float dark_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.dark_th, variate, EnvLv_len);
    float bright_min = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.bright_min, variate, EnvLv_len);
    float bright_max = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.bright_max, variate, EnvLv_len);

    // dehaze_range_adj[6]
    float wt_max = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.wt_max, variate, EnvLv_len);
    float air_max = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.air_max, variate, EnvLv_len);
    float air_min = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.air_min, variate, EnvLv_len);
    float tmax_base = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.tmax_base, variate, EnvLv_len);
    float tmax_off = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.tmax_off, variate, EnvLv_len);
    float tmax_max = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.tmax_max, variate, EnvLv_len);

    // dehaze_iir_control[5]
    float stab_fnum = pCalibV21->dehaze_setting.stab_fnum;
    float sigma = pCalibV21->dehaze_setting.sigma;
    float wt_sigma = pCalibV21->dehaze_setting.wt_sigma;
    float air_sigma = pCalibV21->dehaze_setting.air_sigma;
    float tmax_sigma = pCalibV21->dehaze_setting.tmax_sigma;
    float pre_wet = pCalibV21->dehaze_setting.pre_wet;

    float cfg_wt = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.cfg_wt, variate, EnvLv_len);
    float cfg_air = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.cfg_air, variate, EnvLv_len);
    float cfg_tmax = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.cfg_tmax, variate, EnvLv_len);

    float range_sigma = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.range_sigma, variate, EnvLv_len);
    float space_sigma_cur = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.space_sigma_cur, variate, EnvLv_len);
    float space_sigma_pre = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.space_sigma_pre, variate, EnvLv_len);

    // dehaze_bi_pAdehazeCtx[4]
    float bf_weight = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.bf_weight, variate, EnvLv_len);
    float dc_weitcur = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.dc_weitcur, variate, EnvLv_len);

    // dehaze_air_bf_h[9],dehaze_gaus_h[9]
    float gaus_h[9] = {2.0000, 4.0000, 2.0000,
                       4.0000, 8.0000, 4.0000,
                       2.0000, 4.0000, 2.0000
                      };

    int rawWidth = 1920;
    int rawHeight = 1080;
    ProcRes->ProcResV21.air_lc_en    = air_lc_en ? 1 : 0; // air_lc_en
    ProcRes->ProcResV21.dc_min_th    = int(dc_min_th); //0~255, (8bit) dc_min_th
    ProcRes->ProcResV21.dc_max_th    = int(dc_max_th);  //0~255, (8bit) dc_max_th
    ProcRes->ProcResV21.yhist_th    = int(yhist_th);  //0~255, (8bit) yhist_th
    ProcRes->ProcResV21.yblk_th    = int(yblk_th * ((rawWidth + 15) / 16) * ((rawHeight + 15) / 16)); //default:28,(9bit) yblk_th
    ProcRes->ProcResV21.dark_th    = int(dark_th);  //0~255, (8bit) dark_th
    ProcRes->ProcResV21.bright_min   = int(bright_min);  //0~255, (8bit) bright_min
    ProcRes->ProcResV21.bright_max   = int(bright_max);  //0~255, (8bit) bright_max
    ProcRes->ProcResV21.wt_max   = int(wt_max * 256); //0~255, (8bit) wt_max
    ProcRes->ProcResV21.air_min   = int(air_min);  //0~255, (8bit) air_min
    ProcRes->ProcResV21.air_max   = int(air_max);  //0~256, (8bit) air_max
    ProcRes->ProcResV21.tmax_base   = int(tmax_base);  //0~255, (8bit) tmax_base
    ProcRes->ProcResV21.tmax_off   = int(tmax_off * 1024); //0~1024,(10bit) tmax_off
    ProcRes->ProcResV21.tmax_max   = int(tmax_max * 1024); //0~1024,(10bit) tmax_max
    ProcRes->ProcResV21.stab_fnum = int(stab_fnum);  //1~31,  (5bit) stab_fnum
    ProcRes->ProcResV21.iir_sigma = int(sigma);  //0~255, (8bit) sigma
    ProcRes->ProcResV21.iir_wt_sigma = int(wt_sigma * 8 + 0.5); //       (11bit),8bit+3bit, wt_sigma
    ProcRes->ProcResV21.iir_air_sigma = int(air_sigma);  //       (8bit) air_sigma
    ProcRes->ProcResV21.iir_tmax_sigma = int(tmax_sigma * 1024 + 0.5);  //       (11bit) tmax_sigma
    ProcRes->ProcResV21.iir_pre_wet = int(pre_wet * 128 + 0.5);  //       (7bit) iir_pre_wet
    ProcRes->ProcResV21.cfg_wt = int(cfg_wt * 256); //0~256, (9bit) cfg_wt
    ProcRes->ProcResV21.cfg_air = int(cfg_air);  //0~255, (8bit) cfg_air
    ProcRes->ProcResV21.cfg_tmax = int(cfg_tmax * 1024); //0~1024,(11bit) cfg_tmax
    ProcRes->ProcResV21.range_sima = int(range_sigma * 512); //0~512,(9bit) range_sima
    ProcRes->ProcResV21.space_sigma_cur = int(space_sigma_cur * 256); //0~256,(8bit) space_sigma_cur
    ProcRes->ProcResV21.space_sigma_pre = int(space_sigma_pre * 256); //0~256,(8bit) space_sigma_pre
    ProcRes->ProcResV21.bf_weight      = int(bf_weight * 512); //0~512, (9bit) dc_thed
    ProcRes->ProcResV21.dc_weitcur       = int(dc_weitcur * 256 + 0.5); //0~256, (9bit) dc_weitcur
    ProcRes->ProcResV21.gaus_h0    = int(gaus_h[4]);//h0~h2  浠庡ぇ鍒板皬
    ProcRes->ProcResV21.gaus_h1    = int(gaus_h[1]);
    ProcRes->ProcResV21.gaus_h2    = int(gaus_h[0]);

    if(ProcRes->ProcResV21.dc_en && !(ProcRes->ProcResV21.enhance_en)) {
        if(ProcRes->ProcResV21.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:0 EnvLv:%f cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__, variate, cfg_air, cfg_tmax, cfg_wt);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x0 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n", __func__, ProcRes->ProcResV21.cfg_air, ProcRes->ProcResV21.cfg_tmax,
                         ProcRes->ProcResV21.cfg_wt);
        }
        else if(ProcRes->ProcResV21.cfg_alpha == 0) {
            LOGD_ADEHAZE("%s cfg_alpha:0 EnvLv:%f air_max:%f air_min:%f tmax_base:%f wt_max:%f\n", __func__, variate, air_max, air_min, tmax_base, wt_max);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x0 air_max:0x%x air_min:0x%x tmax_base:0x%x wt_max:0x%x\n", __func__, ProcRes->ProcResV21.air_max, ProcRes->ProcResV21.air_min,
                         ProcRes->ProcResV21.tmax_base, ProcRes->ProcResV21.wt_max);
        }
    }


    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeParamsV30(CalibDbDehazeV21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int EnvLv_len = pCalibV21->dehaze_setting.DehazeData.EnvLv_len;
    bool air_lc_en = pCalibV21->dehaze_setting.air_lc_en;

    // dehaze_self_adp[7]
    float dc_min_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.dc_min_th, variate, EnvLv_len);
    float dc_max_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.dc_max_th, variate, EnvLv_len);
    float yhist_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.yhist_th, variate,  EnvLv_len);
    float yblk_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.yblk_th, variate, EnvLv_len);
    float dark_th = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.dark_th, variate, EnvLv_len);
    float bright_min = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.bright_min, variate, EnvLv_len);
    float bright_max = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.bright_max, variate, EnvLv_len);

    // dehaze_range_adj[6]
    float wt_max = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.wt_max, variate, EnvLv_len);
    float air_max = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.air_max, variate, EnvLv_len);
    float air_min = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.air_min, variate, EnvLv_len);
    float tmax_base = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.tmax_base, variate, EnvLv_len);
    float tmax_off = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.tmax_off, variate, EnvLv_len);
    float tmax_max = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.tmax_max, variate, EnvLv_len);

    // dehaze_iir_control[5]
    float stab_fnum = pCalibV21->dehaze_setting.stab_fnum;
    float sigma = pCalibV21->dehaze_setting.sigma;
    float wt_sigma = pCalibV21->dehaze_setting.wt_sigma;
    float air_sigma = pCalibV21->dehaze_setting.air_sigma;
    float tmax_sigma = pCalibV21->dehaze_setting.tmax_sigma;
    float pre_wet = pCalibV21->dehaze_setting.pre_wet;

    float cfg_wt = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.cfg_wt, variate, EnvLv_len);
    float cfg_air = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.cfg_air, variate, EnvLv_len);
    float cfg_tmax = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.cfg_tmax, variate, EnvLv_len);

    float range_sigma = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.range_sigma, variate, EnvLv_len);
    float space_sigma_cur = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.space_sigma_cur, variate, EnvLv_len);
    float space_sigma_pre = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.space_sigma_pre, variate, EnvLv_len);

    // dehaze_bi_pAdehazeCtx[4]
    float bf_weight = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.bf_weight, variate, EnvLv_len);
    float dc_weitcur = LinearInterp(pCalibV21->dehaze_setting.DehazeData.EnvLv, pCalibV21->dehaze_setting.DehazeData.dc_weitcur, variate, EnvLv_len);

    // dehaze_air_bf_h[9],dehaze_gaus_h[9]
    float gaus_h[9] = {2.0000, 4.0000, 2.0000,
                       4.0000, 8.0000, 4.0000,
                       2.0000, 4.0000, 2.0000
                      };

    int rawWidth = 1920;
    int rawHeight = 1080;
    ProcRes->ProcResV30.air_lc_en    = air_lc_en ? 1 : 0; // air_lc_en
    ProcRes->ProcResV30.dc_min_th    = int(dc_min_th); //0~255, (8bit) dc_min_th
    ProcRes->ProcResV30.dc_max_th    = int(dc_max_th);  //0~255, (8bit) dc_max_th
    ProcRes->ProcResV30.yhist_th    = int(yhist_th);  //0~255, (8bit) yhist_th
    ProcRes->ProcResV30.yblk_th    = int(yblk_th * ((rawWidth + 15) / 16) * ((rawHeight + 15) / 16)); //default:28,(9bit) yblk_th
    ProcRes->ProcResV30.dark_th    = int(dark_th);  //0~255, (8bit) dark_th
    ProcRes->ProcResV30.bright_min   = int(bright_min);  //0~255, (8bit) bright_min
    ProcRes->ProcResV30.bright_max   = int(bright_max);  //0~255, (8bit) bright_max
    ProcRes->ProcResV30.wt_max   = int(wt_max * 256); //0~255, (8bit) wt_max
    ProcRes->ProcResV30.air_min   = int(air_min);  //0~255, (8bit) air_min
    ProcRes->ProcResV30.air_max   = int(air_max);  //0~256, (8bit) air_max
    ProcRes->ProcResV30.tmax_base   = int(tmax_base);  //0~255, (8bit) tmax_base
    ProcRes->ProcResV30.tmax_off   = int(tmax_off * 1024); //0~1024,(10bit) tmax_off
    ProcRes->ProcResV30.tmax_max   = int(tmax_max * 1024); //0~1024,(10bit) tmax_max
    ProcRes->ProcResV30.stab_fnum = int(stab_fnum);  //1~31,  (5bit) stab_fnum
    ProcRes->ProcResV30.iir_sigma = int(sigma);  //0~255, (8bit) sigma
    ProcRes->ProcResV30.iir_wt_sigma = int(wt_sigma * 8 + 0.5); //       (11bit),8bit+3bit, wt_sigma
    ProcRes->ProcResV30.iir_air_sigma = int(air_sigma);  //       (8bit) air_sigma
    ProcRes->ProcResV30.iir_tmax_sigma = int(tmax_sigma * 1024 + 0.5);  //       (11bit) tmax_sigma
    ProcRes->ProcResV30.iir_pre_wet = int(pre_wet * 128 + 0.5);  //       (7bit) iir_pre_wet
    ProcRes->ProcResV30.cfg_wt = int(cfg_wt * 256); //0~256, (9bit) cfg_wt
    ProcRes->ProcResV30.cfg_air = int(cfg_air);  //0~255, (8bit) cfg_air
    ProcRes->ProcResV30.cfg_tmax = int(cfg_tmax * 1024); //0~1024,(11bit) cfg_tmax
    ProcRes->ProcResV30.range_sima = int(range_sigma * 512); //0~512,(9bit) range_sima
    ProcRes->ProcResV30.space_sigma_cur = int(space_sigma_cur * 256); //0~256,(8bit) space_sigma_cur
    ProcRes->ProcResV30.space_sigma_pre = int(space_sigma_pre * 256); //0~256,(8bit) space_sigma_pre
    ProcRes->ProcResV30.bf_weight      = int(bf_weight * 512); //0~512, (9bit) dc_thed
    ProcRes->ProcResV30.dc_weitcur       = int(dc_weitcur * 256 + 0.5); //0~256, (9bit) dc_weitcur
    ProcRes->ProcResV30.gaus_h0    = int(gaus_h[4]);//h0~h2  浠庡ぇ鍒板皬
    ProcRes->ProcResV30.gaus_h1    = int(gaus_h[1]);
    ProcRes->ProcResV30.gaus_h2    = int(gaus_h[0]);

    if(ProcRes->ProcResV30.dc_en && !(ProcRes->ProcResV30.enhance_en)) {
        if(ProcRes->ProcResV30.cfg_alpha == 255) {
            LOGD_ADEHAZE("%s cfg_alpha:1 EnvLv:%f cfg_air:%f cfg_tmax:%f cfg_wt:%f\n", __func__, variate, cfg_air, cfg_tmax, cfg_wt);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x255 cfg_air:0x%x cfg_tmax:0x%x cfg_wt:0x%x\n", __func__,
                         ProcRes->ProcResV30.cfg_air, ProcRes->ProcResV30.cfg_tmax, ProcRes->ProcResV30.cfg_wt);
        }
        else if(ProcRes->ProcResV30.cfg_alpha == 0) {

            LOGD_ADEHAZE("%s cfg_alpha:0 EnvLv:%f air_max:%f air_min:%f tmax_base:%f wt_max:%f\n", __func__, variate, air_max, air_min, tmax_base, wt_max);
            LOGD_ADEHAZE("%s cfg_alpha_reg:0x0 air_max:0x%x air_min:0x%x tmax_base:0x%x wt_max:0x%x\n", __func__, ProcRes->ProcResV30.air_max, ProcRes->ProcResV30.air_min,
                         ProcRes->ProcResV30.tmax_base, ProcRes->ProcResV30.wt_max);
        }
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetEnhanceParams(CalibDbV2_dehaze_V20_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int iso_len = pCalib->DehazeTuningPara.enhance_setting.EnhanceData.ISO_len;
    float enhance_value = LinearInterp(pCalib->DehazeTuningPara.enhance_setting.EnhanceData.ISO, pCalib->DehazeTuningPara.enhance_setting.EnhanceData.enhance_value, variate, iso_len);
    ProcRes->ProcResV20.enhance_value = int(enhance_value * 1024 + 0.5); //       (14bit),4bit + 10bit, enhance_value

    if(ProcRes->ProcResV20.dc_en && ProcRes->ProcResV20.enhance_en)
        LOGD_ADEHAZE("%s enhance_value:%f enhance_value:0x%x\n", __func__, enhance_value, ProcRes->ProcResV20.enhance_value);

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetEnhanceParamsV21(CalibDbDehazeV21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int EnvLv_len = pCalibV21->enhance_setting.EnhanceData.EnvLv_len;
    float enhance_value = LinearInterp(pCalibV21->enhance_setting.EnhanceData.EnvLv, pCalibV21->enhance_setting.EnhanceData.enhance_value, variate, EnvLv_len);
    float enhance_chroma = LinearInterp(pCalibV21->enhance_setting.EnhanceData.EnvLv, pCalibV21->enhance_setting.EnhanceData.enhance_chroma, variate, EnvLv_len);

    ProcRes->ProcResV21.enhance_value = int(enhance_value * 1024 + 0.5); //       (14bit),4bit + 10bit, enhance_value
    ProcRes->ProcResV21.enhance_chroma = int(enhance_chroma * 1024 + 0.5); //       (14bit),4bit + 10bit, enhance_value

    for(int i = 0; i < 17; i++)
        ProcRes->ProcResV21.enh_curve[i] = (int)(pCalibV21->enhance_setting.enhance_curve[i]);

    if(ProcRes->ProcResV21.dc_en && ProcRes->ProcResV21.enhance_en) {
        LOGD_ADEHAZE("%s EnvLv:%f enhance_value:%f enhance_chroma:%f\n", __func__,
                     variate, enhance_value, enhance_chroma);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     ProcRes->ProcResV21.enhance_value, ProcRes->ProcResV21.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetEnhanceParamsV30(CalibDbDehazeV21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int EnvLv_len = pCalibV21->enhance_setting.EnhanceData.EnvLv_len;
    float enhance_value = LinearInterp(pCalibV21->enhance_setting.EnhanceData.EnvLv, pCalibV21->enhance_setting.EnhanceData.enhance_value, variate, EnvLv_len);
    float enhance_chroma = LinearInterp(pCalibV21->enhance_setting.EnhanceData.EnvLv, pCalibV21->enhance_setting.EnhanceData.enhance_chroma, variate, EnvLv_len);

    ProcRes->ProcResV30.enhance_value = int(enhance_value * 1024 + 0.5); //       (14bit),4bit + 10bit, enhance_value
    ProcRes->ProcResV30.enhance_chroma = int(enhance_chroma * 1024 + 0.5); //       (14bit),4bit + 10bit, enhance_value

    for(int i = 0; i < 17; i++)
        ProcRes->ProcResV30.enh_curve[i] = (int)(pCalibV21->enhance_setting.enhance_curve[i]);

    if(ProcRes->ProcResV30.dc_en && ProcRes->ProcResV30.enhance_en) {
        LOGD_ADEHAZE("%s EnvLv:%f enhance_value:%f enhance_chroma:%f\n", __func__,
                     variate, enhance_value, enhance_chroma);
        LOGD_ADEHAZE("%s enhance_value_reg:0x%x enhance_chroma_reg:0x%x\n", __func__,
                     ProcRes->ProcResV30.enhance_value, ProcRes->ProcResV30.enhance_chroma);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}


void GetHistParams(CalibDbV2_dehaze_V20_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int iso_len = pCalib->DehazeTuningPara.hist_setting.HistData.ISO_len;
    bool hist_channel = pCalib->DehazeTuningPara.hist_setting.hist_channel;
    bool hist_para_en = pCalib->DehazeTuningPara.hist_setting.hist_para_en;
    float hist_gratio = LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO, pCalib->DehazeTuningPara.hist_setting.HistData.hist_gratio, variate, iso_len);
    float hist_th_off = LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO, pCalib->DehazeTuningPara.hist_setting.HistData.hist_th_off, variate, iso_len);
    float hist_k = LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO, pCalib->DehazeTuningPara.hist_setting.HistData.hist_k, variate, iso_len);
    float hist_min = LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO, pCalib->DehazeTuningPara.hist_setting.HistData.hist_min, variate, iso_len);
    float hist_scale = LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO, pCalib->DehazeTuningPara.hist_setting.HistData.hist_scale, variate, iso_len);
    float cfg_gratio = LinearInterp(pCalib->DehazeTuningPara.hist_setting.HistData.ISO, pCalib->DehazeTuningPara.hist_setting.HistData.cfg_gratio, variate, iso_len);

    // dehaze_hist_t0[6],dehaze_hist_t1[6],dehaze_hist_t2[6]
    float hist_conv_t0[6] = {1.0000, 2.0000, 1.0000, -1.0000, -2.0000, -1.0000};
    float hist_conv_t1[6] = {1.0000, 0.0000, -1.0000, 2.0000, 0.0000, -2.0000};
    float hist_conv_t2[6] = {1.0000, -2.0000, 1.0000, 2.0000, -4.0000, 2.0000};

    ProcRes->ProcResV20.hist_chn = hist_channel ? 1 : 0; //  hist_para_en
    ProcRes->ProcResV20.hpara_en = hist_para_en ? 1 : 0; //  hist_para_en
    ProcRes->ProcResV20.hist_gratio   = int(hist_gratio * 8); //       (8bit) hist_gratio
    ProcRes->ProcResV20.hist_th_off   = int(hist_th_off);  //       (8bit) hist_th_off
    ProcRes->ProcResV20.hist_k   = int(hist_k * 4 + 0.5); //0~7    (5bit),3bit+2bit, hist_k
    ProcRes->ProcResV20.hist_min   = int(hist_min * 256); //       (9bit) hist_min
    ProcRes->ProcResV20.cfg_gratio = int(cfg_gratio * 256); //       (13bit),5bit+8bit, cfg_gratio
    ProcRes->ProcResV20.hist_scale       = int(hist_scale *  256 + 0.5 );  //       (13bit),5bit + 8bit, sw_hist_scale

    for (int i = 0; i < 6; i++)
    {
        ProcRes->ProcResV20.conv_t0[i]     = int(hist_conv_t0[i]);
        ProcRes->ProcResV20.conv_t1[i]     = int(hist_conv_t1[i]);
        ProcRes->ProcResV20.conv_t2[i]     = int(hist_conv_t2[i]);
    }

    if(ProcRes->ProcResV20.hist_en) {
        LOGD_ADEHAZE("%s hist_channel:%d hist_prar_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f hist_min:%f hist_scale:%f cfg_gratio:%f\n", __func__,
                     ProcRes->ProcResV20.hist_chn, ProcRes->ProcResV20.hpara_en, hist_gratio, hist_th_off, hist_k, hist_min, hist_scale, cfg_gratio);
        LOGD_ADEHAZE("%s hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x hist_min_reg:0x%x hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n", __func__,
                     ProcRes->ProcResV20.hist_gratio, ProcRes->ProcResV20.hist_th_off, ProcRes->ProcResV20.hist_k,
                     ProcRes->ProcResV20.hist_min, ProcRes->ProcResV20.hist_scale, ProcRes->ProcResV20.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);

}

void GetHistParamsV21(CalibDbDehazeV21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int EnvLv_len = pCalibV21->hist_setting.HistData.EnvLv_len;
    bool hist_para_en = pCalibV21->hist_setting.hist_para_en;
    float hist_gratio = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_gratio, variate, EnvLv_len);
    float hist_th_off = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_th_off, variate, EnvLv_len);
    float hist_k = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_k, variate, EnvLv_len);
    float hist_min = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_min, variate, EnvLv_len);
    float hist_scale = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_scale, variate, EnvLv_len);
    float cfg_gratio = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.cfg_gratio, variate, EnvLv_len);

    // dehaze_hist_t0[6],dehaze_hist_t1[6],dehaze_hist_t2[6]
    float hist_conv_t0[6] = {1.0000, 2.0000, 1.0000, -1.0000, -2.0000, -1.0000};
    float hist_conv_t1[6] = {1.0000, 0.0000, -1.0000, 2.0000, 0.0000, -2.0000};
    float hist_conv_t2[6] = {1.0000, -2.0000, 1.0000, 2.0000, -4.0000, 2.0000};

    ProcRes->ProcResV21.hpara_en = hist_para_en ? 1 : 0; //  hist_para_en
    //clip hpara_en
    ProcRes->ProcResV21.hpara_en = ProcRes->ProcResV21.dc_en ? ProcRes->ProcResV21.hpara_en : 1; //  dc en 关闭，hpara必需开

    ProcRes->ProcResV21.hist_gratio   = int(hist_gratio * 8); //       (8bit) hist_gratio
    ProcRes->ProcResV21.hist_th_off   = int(hist_th_off);  //       (8bit) hist_th_off
    ProcRes->ProcResV21.hist_k   = int(hist_k * 4 + 0.5); //0~7    (5bit),3bit+2bit, hist_k
    ProcRes->ProcResV21.hist_min   = int(hist_min * 256); //       (9bit) hist_min
    ProcRes->ProcResV21.cfg_gratio = int(cfg_gratio * 256); //       (13bit),5bit+8bit, cfg_gratio
    ProcRes->ProcResV21.hist_scale       = int(hist_scale *  256 + 0.5 );  //       (13bit),5bit + 8bit, sw_hist_scale

    if(ProcRes->ProcResV21.hist_en) {
        LOGD_ADEHAZE("%s cfg_alpha:%f EnvLv:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f hist_min:%f hist_scale:%f cfg_gratio:%f\n", __func__,
                     ProcRes->ProcResV21.cfg_alpha / 255.0, variate, ProcRes->ProcResV21.hpara_en, hist_gratio, hist_th_off, hist_k, hist_min, hist_scale, cfg_gratio);
        LOGD_ADEHAZE("%s cfg_alpha_reg:0x%x hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x hist_min_reg:0x%x hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n", __func__,
                     ProcRes->ProcResV21.cfg_alpha, ProcRes->ProcResV21.hist_gratio, ProcRes->ProcResV21.hist_th_off, ProcRes->ProcResV21.hist_k,
                     ProcRes->ProcResV21.hist_min, ProcRes->ProcResV21.hist_scale, ProcRes->ProcResV21.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);

}

void GetHistParamsV30(CalibDbDehazeV21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    int EnvLv_len = pCalibV21->hist_setting.HistData.EnvLv_len;
    bool hist_para_en = pCalibV21->hist_setting.hist_para_en;
    float hist_gratio = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_gratio, variate, EnvLv_len);
    float hist_th_off = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_th_off, variate, EnvLv_len);
    float hist_k = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_k, variate, EnvLv_len);
    float hist_min = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_min, variate, EnvLv_len);
    float hist_scale = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.hist_scale, variate, EnvLv_len);
    float cfg_gratio = LinearInterp(pCalibV21->hist_setting.HistData.EnvLv, pCalibV21->hist_setting.HistData.cfg_gratio, variate, EnvLv_len);

    // dehaze_hist_t0[6],dehaze_hist_t1[6],dehaze_hist_t2[6]
    float hist_conv_t0[6] = {1.0000, 2.0000, 1.0000, -1.0000, -2.0000, -1.0000};
    float hist_conv_t1[6] = {1.0000, 0.0000, -1.0000, 2.0000, 0.0000, -2.0000};
    float hist_conv_t2[6] = {1.0000, -2.0000, 1.0000, 2.0000, -4.0000, 2.0000};

    ProcRes->ProcResV30.hpara_en = hist_para_en ? 1 : 0; //  hist_para_en
    //clip hpara_en
    ProcRes->ProcResV30.hpara_en = ProcRes->ProcResV30.dc_en ? ProcRes->ProcResV30.hpara_en : 1; //  dc en 关闭，hpara必需开

    ProcRes->ProcResV30.hist_gratio   = int(hist_gratio * 8); //       (8bit) hist_gratio
    ProcRes->ProcResV30.hist_th_off   = int(hist_th_off);  //       (8bit) hist_th_off
    ProcRes->ProcResV30.hist_k   = int(hist_k * 4 + 0.5); //0~7    (5bit),3bit+2bit, hist_k
    ProcRes->ProcResV30.hist_min   = int(hist_min * 256); //       (9bit) hist_min
    ProcRes->ProcResV30.cfg_gratio = int(cfg_gratio * 256); //       (13bit),5bit+8bit, cfg_gratio
    ProcRes->ProcResV30.hist_scale       = int(hist_scale *  256 + 0.5 );  //       (13bit),5bit + 8bit, sw_hist_scale

    if(ProcRes->ProcResV30.hist_en) {
        LOGD_ADEHAZE("%s cfg_alpha:%f EnvLv:%f hist_para_en:%d hist_gratio:%f hist_th_off:%f hist_k:%f hist_min:%f hist_scale:%f cfg_gratio:%f\n", __func__,
                     ProcRes->ProcResV30.cfg_alpha / 255.0, variate, ProcRes->ProcResV30.hpara_en, hist_gratio, hist_th_off, hist_k, hist_min, hist_scale, cfg_gratio);
        LOGD_ADEHAZE("%s cfg_alpha_reg:0x%x hist_gratio_reg:0x%x hist_th_off_reg:0x%x hist_k_reg:0x%x hist_min_reg:0x%x hist_scale_reg:0x%x cfg_gratio_reg:0x%x\n", __func__,
                     ProcRes->ProcResV30.cfg_alpha, ProcRes->ProcResV30.hist_gratio, ProcRes->ProcResV30.hist_th_off, ProcRes->ProcResV30.hist_k,
                     ProcRes->ProcResV30.hist_min, ProcRes->ProcResV30.hist_scale, ProcRes->ProcResV30.cfg_gratio);
    }

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void GetDehazeHistDuoISPSetting(CalibDbV2_dehaze_V30_Gain_Table_t* pCalibV30, RkAiqAdehazeProcResult_t* ProcRes, rkisp_adehaze_stats_t* pStats, bool DuoCamera, int FrameID)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    //dehaze gain table setting
    for(int i = 0; i < ISP3X_DHAZ_SIGMA_IDX_NUM; i++)
        ProcRes->ProcResV30.sigma_idx[i] = pCalibV30->sigma_idx[i];
    for(int i = 0; i < ISP3X_DHAZ_SIGMA_LUT_NUM; i++)
        ProcRes->ProcResV30.sigma_lut[i] = pCalibV30->sigma_lut[i];

    //round_en
    ProcRes->ProcResV30.round_en = 1;

    //deahze duo setting
    if(DuoCamera) {
        ProcRes->ProcResV30.soft_wr_en = 1;
#if 1
        for(int i = 0; i < 64; i++) {
            ProcRes->ProcResV30.hist_wr[i] = 16 * (i + 1);
            ProcRes->ProcResV30.hist_wr[i] = ProcRes->ProcResV30.hist_wr[i] > 1023 ? 1023 : ProcRes->ProcResV30.hist_wr[i];
        }

#else
        ProcRes->ProcResV30.adp_air_wr = pStats->dehaze_stats_v30.dhaz_adp_air_base;
        ProcRes->ProcResV30.adp_gratio_wr = pStats->dehaze_stats_v30.dhaz_adp_gratio;
        ProcRes->ProcResV30.adp_tmax_wr = pStats->dehaze_stats_v30.dhaz_adp_tmax;
        ProcRes->ProcResV30.adp_wt_wr = pStats->dehaze_stats_v30.dhaz_adp_wt;

        static int hist_wr[64];
        if(!FrameID)
            for(int i = 0; i < 64; i++) {
                hist_wr[i] = 16 * (i + 1);
                hist_wr[i] = hist_wr[i] > 1023 ? 1023 : hist_wr[i];
                ProcRes->ProcResV30.hist_wr[i] = hist_wr[i];
            }
        else {
            int num = MIN(FrameID + 1, ProcRes->ProcResV30.stab_fnum);
            int tmp = 0;
            for(int i = 0; i < 64; i++) {
                tmp = (hist_wr[i] * (num - 1) + pStats->dehaze_stats_v30.h_rgb_iir[i]) / num;
                ProcRes->ProcResV30.hist_wr[i] = tmp;
                hist_wr[i] = tmp;
            }
        }

        LOGD_ADEHAZE("%s adp_air_wr:0x%x adp_gratio_wr:0x%x adp_tmax_wr:0x%x adp_wt_wr:0x%x\n", __func__, ProcRes->ProcResV30.adp_air_wr, ProcRes->ProcResV30.adp_gratio_wr,
                     ProcRes->ProcResV30.adp_tmax_wr, ProcRes->ProcResV30.adp_wt_wr);

        LOGV_ADEHAZE("%s hist_wr:0x%x", __func__, ProcRes->ProcResV30.hist_wr[0]);
        for(int i = 1; i < 63; i++)
            LOGV_ADEHAZE(" 0x%x", ProcRes->ProcResV30.hist_wr[i]);
        LOGV_ADEHAZE(" 0x%x\n", ProcRes->ProcResV30.hist_wr[63]);
#endif
        LOGD_ADEHAZE("%s DuoCamera:%d soft_wr_en:%d\n", __func__, DuoCamera, ProcRes->ProcResV30.soft_wr_en);
    }
    else
        ProcRes->ProcResV30.soft_wr_en = 0;

    LOG1_ADEHAZE("EIXT: %s \n", __func__);
}

void AdehazeApiToolProcess(CalibDbV2_dehaze_V20_t* pStool, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE("%s: Adehaze in api TOOL !!! \n", __func__);

    //cfg setting
    ProcRes->ProcResV20.cfg_alpha = (int)LIMIT_VALUE((pStool->DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
    LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, ProcRes->ProcResV20.cfg_alpha);

    //fuction enable
    EnableSetting(pStool, ProcRes);

    //dehaze setting
    GetDehazeParams(pStool, ProcRes, variate);

    //enhance setting
    GetEnhanceParams(pStool, ProcRes, variate);

    //hist setting
    GetHistParams(pStool, ProcRes, variate);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);

}

void AdehazeEnhanceApiBypassProcess(CalibDbV2_dehaze_V20_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE(" %s: Adehaze Api off!!!\n", __func__);

    //cfg setting
    ProcRes->ProcResV20.cfg_alpha = (int)LIMIT_VALUE((pCalib->DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
    //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, ProcRes->ProcResV20.cfg_alpha);

    //enable setting
    EnableSetting(pCalib, ProcRes);

    //dehaze setting
    GetDehazeParams(pCalib, ProcRes, variate);

    //enhance setting
    GetEnhanceParams(pCalib, ProcRes, variate);

    //hist setting
    GetHistParams(pCalib, ProcRes, variate);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);

}

void AdehazeEnhanceApiBypassV21Process(CalibDbV2_dehaze_V21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE(" %s: Adehaze Api off!!!\n", __func__);

    //cfg setting
    ProcRes->ProcResV20.cfg_alpha = (int)LIMIT_VALUE((pCalibV21->DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
    //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, ProcRes->ProcResV20.cfg_alpha);

    //enable setting
    EnableSettingV21(&pCalibV21->DehazeTuningPara, ProcRes);

    //dehaze setting
    GetDehazeParamsV21(&pCalibV21->DehazeTuningPara, ProcRes, variate);

    //enhance setting
    GetEnhanceParamsV21(&pCalibV21->DehazeTuningPara, ProcRes, variate);

    //hist setting
    GetHistParamsV21(&pCalibV21->DehazeTuningPara, ProcRes, variate);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);

}

void AdehazeEnhanceApiBypassV30Process(CalibDbDehazeV21_t* pCalibV21, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE(" %s: Adehaze Api off!!!\n", __func__);

    //cfg setting
    ProcRes->ProcResV30.cfg_alpha = (int)LIMIT_VALUE((pCalibV21->cfg_alpha * 256.0), 255, 0);
    //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, ProcRes->ProcResV30.cfg_alpha);

    //enable setting
    EnableSettingV30(pCalibV21, ProcRes);

    //dehaze setting
    GetDehazeParamsV30(pCalibV21, ProcRes, variate);

    //enhance setting
    GetEnhanceParamsV30(pCalibV21, ProcRes, variate);

    //hist setting
    GetHistParamsV30(pCalibV21, ProcRes, variate);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);

}

void AdehazeEnhanceApiOffProcess(CalibDbV2_dehaze_V20_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE(" %s: Adehaze Api off!!!\n", __func__);

    //enable setting
    ProcRes->ProcResV20.enable = true;
    if(pCalib->DehazeTuningPara.enhance_setting.en) {
        ProcRes->ProcResV20.dc_en = true;
        ProcRes->ProcResV20.enhance_en = true;
    }
    else {
        ProcRes->ProcResV20.dc_en = false;
        ProcRes->ProcResV20.enhance_en = false;
    }

    //cfg setting
    ProcRes->ProcResV20.cfg_alpha = (int)LIMIT_VALUE((pCalib->DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
    //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, ProcRes->ProcResV20.cfg_alpha);

    //dehaze setting
    GetDehazeParams(pCalib, ProcRes, variate);

    //enhance setting
    GetEnhanceParams(pCalib, ProcRes, variate);

    //hist setting
    GetHistParams(pCalib, ProcRes, variate);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);

}

void AdehazeEnhanceApiOffProcessV21(CalibDbDehazeV21_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    LOGD_ADEHAZE(" %s: Adehaze Api off!!!\n", __func__);

    //enable setting
    ProcRes->ProcResV21.enable = true;
    if(pCalib->enhance_setting.en) {
        ProcRes->ProcResV21.dc_en = true;
        ProcRes->ProcResV21.enhance_en = true;
    }
    else {
        ProcRes->ProcResV21.dc_en = false;
        ProcRes->ProcResV21.enhance_en = false;
    }

    //hist en
    ProcRes->ProcResV21.hist_en = pCalib->hist_setting.en ? 1 : 0;
    LOGD_ADEHAZE(" Dehaze module en:%d, Dehaze en:%d, Enhance en:%d, Hist en:%d\n",
                 ProcRes->ProcResV21.dc_en || ProcRes->ProcResV21.enhance_en || ProcRes->ProcResV21.hist_en, 0, pCalib->enhance_setting.en, ProcRes->ProcResV21.hist_en );

    //cfg setting
    ProcRes->ProcResV21.cfg_alpha = (int)LIMIT_VALUE((pCalib->cfg_alpha * 256.0), 255, 0);
    //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, ProcRes->ProcResV21.cfg_alpha);

    //dehaze setting
    GetDehazeParamsV21(pCalib, ProcRes, variate);

    //enhance setting
    GetEnhanceParamsV21(pCalib, ProcRes, variate);

    //hist setting
    GetHistParamsV21(pCalib, ProcRes, variate);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);

}

void AdehazeEnhanceApiOffProcessV30(CalibDbDehazeV21_t* pCalib, RkAiqAdehazeProcResult_t* ProcRes, float variate)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    //enable setting
    ProcRes->ProcResV30.enable = true;
    if(pCalib->enhance_setting.en) {
        ProcRes->ProcResV30.dc_en = true;
        ProcRes->ProcResV30.enhance_en = true;
    }
    else {
        ProcRes->ProcResV30.dc_en = false;
        ProcRes->ProcResV30.enhance_en = false;
    }

    //hist en
    ProcRes->ProcResV30.hist_en = pCalib->hist_setting.en ? 1 : 0;
    LOGD_ADEHAZE(" %s: Adehaze Api off!!!\n", __func__);
    LOGD_ADEHAZE(" Dehaze module en:%d, Dehaze en:%d, Enhance en:%d, Hist en:%d\n",
                 ProcRes->ProcResV30.dc_en || ProcRes->ProcResV30.enhance_en || ProcRes->ProcResV30.hist_en, 0, pCalib->enhance_setting.en, ProcRes->ProcResV30.hist_en );
    //cfg setting
    ProcRes->ProcResV30.cfg_alpha = (int)LIMIT_VALUE((pCalib->cfg_alpha * 256.0), 255, 0);
    //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, ProcRes->ProcResV30.cfg_alpha);

    //dehaze setting
    GetDehazeParamsV30(pCalib, ProcRes, variate);

    //enhance setting
    GetEnhanceParamsV30(pCalib, ProcRes, variate);

    //hist setting
    GetHistParamsV30(pCalib, ProcRes, variate);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);

}

XCamReturn AdehazeProcessV21(AdehazeHandle_t* pAdehazeCtx, float variate)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode == DEHAZE_API_BYPASS)
        AdehazeEnhanceApiBypassV21Process(&pAdehazeCtx->Calib.Dehaze_v21, &pAdehazeCtx->ProcRes, variate);
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode > DEHAZE_API_BYPASS && pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode < DEHAZE_API_OFF) {
        pAdehazeCtx->ProcRes.ProcResV21.enable = true;
        pAdehazeCtx->ProcRes.ProcResV21.dc_en = 0x1;
        pAdehazeCtx->ProcRes.ProcResV21.enhance_en = 0x0;
        //LOGD_ADEHAZE(" Dehaze fuction en:%d, Dehaze en:%d, Enhance en:%d,", 1, 1, 0 );

        if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode == DEHAZE_API_AUTO )
            pAdehazeCtx->ProcRes.ProcResV21.cfg_alpha = (int)LIMIT_VALUE((pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode == DEHAZE_API_MANUAL)
            pAdehazeCtx->ProcRes.ProcResV21.cfg_alpha = 255;
        //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV21.cfg_alpha);

        //hist en setting
        if(pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara.hist_setting.en)
            pAdehazeCtx->ProcRes.ProcResV21.hist_en = 0x1;
        else
            pAdehazeCtx->ProcRes.ProcResV21.hist_en = 0;

        LOGD_ADEHAZE(" Dehaze module en:%d, Dehaze en:%d, Enhance en:%d, Hist en:%d\n", 1, 1, 0, pAdehazeCtx->ProcRes.ProcResV21.hist_en );

        GetDehazeParamsV21(&pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode == DEHAZE_API_MANUAL)
        {
            float level = (float)(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.stManual.strength);
            float level_default = 5;
            float level_diff = (float)(level - level_default);

            //sw_dhaz_cfg_wt
            float sw_dhaz_cfg_wt = (float)pAdehazeCtx->ProcRes.ProcResV21.cfg_wt;
            sw_dhaz_cfg_wt += level_diff * 0.05;
            sw_dhaz_cfg_wt = LIMIT_VALUE(sw_dhaz_cfg_wt, 0.99, 0.01);
            pAdehazeCtx->ProcRes.ProcResV21.cfg_wt = (int)sw_dhaz_cfg_wt;

            //sw_dhaz_cfg_air
            float sw_dhaz_cfg_air = (float)pAdehazeCtx->ProcRes.ProcResV21.cfg_air;
            sw_dhaz_cfg_air += level_diff * 5;
            sw_dhaz_cfg_air = LIMIT_VALUE(sw_dhaz_cfg_air, 255, 0.01);
            pAdehazeCtx->ProcRes.ProcResV21.cfg_air = (int)sw_dhaz_cfg_air;

            //sw_dhaz_cfg_tmax
            float sw_dhaz_cfg_tmax = (float)pAdehazeCtx->ProcRes.ProcResV21.cfg_tmax;
            sw_dhaz_cfg_tmax += level_diff * 0.05;
            sw_dhaz_cfg_tmax = LIMIT_VALUE(sw_dhaz_cfg_tmax, 0.99, 0.01);
            pAdehazeCtx->ProcRes.ProcResV21.cfg_tmax = (int)sw_dhaz_cfg_tmax;

            LOGD_ADEHAZE(" %s: Adehaze munual level:%f level_diff:%f\n", __func__, level, level_diff);
            LOGD_ADEHAZE(" %s: After manual api sw_dhaz_cfg_wt:%f sw_dhaz_cfg_air:%f sw_dhaz_cfg_tmax:%f\n", __func__, sw_dhaz_cfg_wt,
                         sw_dhaz_cfg_air, sw_dhaz_cfg_tmax);
        }
        //hist setting
        GetHistParamsV21(&pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

    }
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode == DEHAZE_API_OFF)
        AdehazeEnhanceApiOffProcessV21(&pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode == DEHAZE_API_TOOL)
        AdehazeEnhanceApiBypassV21Process(&pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.stTool, &pAdehazeCtx->ProcRes, variate);
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode == DEHAZE_API_ENHANCE_MANUAL) {
        pAdehazeCtx->ProcRes.ProcResV21.enable = true;
        pAdehazeCtx->ProcRes.ProcResV21.dc_en = 0x1;
        pAdehazeCtx->ProcRes.ProcResV21.enhance_en = 0x1;

        //cfg setting
        pAdehazeCtx->ProcRes.ProcResV21.cfg_alpha = (int)LIMIT_VALUE((pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
        //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV21.cfg_alpha);

        //hist en
        pAdehazeCtx->ProcRes.ProcResV21.hist_en = pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.hist_setting.en ? 1 : 0;
        LOGD_ADEHAZE(" Dehaze module en:%d, Dehaze en:%d, Enhance en:%d, Hist en:%d\n", 1, 0, 1, pAdehazeCtx->ProcRes.ProcResV21.hist_en );

        //dehaze setting
        GetDehazeParamsV21(&pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        //enhance setting
        GetEnhanceParamsV21(&pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        float level = (float)(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.stEnhanceManual.level);
        level -= 50;
        float step = (float)(pAdehazeCtx->ProcRes.ProcResV21.enhance_value - 1024);
        step = LIMIT_VALUE(step, 30.9, 0);
        step /= 50;
        pAdehazeCtx->ProcRes.ProcResV21.enhance_value =  pAdehazeCtx->ProcRes.ProcResV21.enhance_value + (int)(step * level);

        LOGD_ADEHAZE("%s After enhance api enhance_value:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV21.enhance_value);

        //hist setting
        GetHistParamsV21(&pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

    }
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode == DEHAZE_API_ENHANCE_AUTO) {
        pAdehazeCtx->ProcRes.ProcResV21.enable = true;
        pAdehazeCtx->ProcRes.ProcResV21.dc_en = 0x1;
        pAdehazeCtx->ProcRes.ProcResV21.enhance_en = 0x1;

        //cfg setting
        pAdehazeCtx->ProcRes.ProcResV21.cfg_alpha = (int)LIMIT_VALUE((pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
        //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV21.cfg_alpha);

        //hist en
        pAdehazeCtx->ProcRes.ProcResV21.hist_en = pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.hist_setting.en ? 1 : 0;
        LOGD_ADEHAZE(" Dehaze module en:%d, Dehaze en:%d, Enhance en:%d, Hist en:%d\n", 1, 0, 1, pAdehazeCtx->ProcRes.ProcResV21.hist_en );

        //dehaze setting
        GetDehazeParamsV21(&pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        //enhance setting
        GetEnhanceParamsV21(&pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        //hist setting
        GetHistParamsV21(&pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);
    }
    else
        LOGE_ADEHAZE("%s:Wrong Adehaze API mode!!! \n", __func__);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}

XCamReturn AdehazeProcessV30(AdehazeHandle_t* pAdehazeCtx, float variate)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode == DEHAZE_API_BYPASS) {
        AdehazeEnhanceApiBypassV30Process(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);
        //gain table &Duo cam setting
        GetDehazeHistDuoISPSetting(&pAdehazeCtx->Calib.Dehaze_v30.DehazeCalibPara, &pAdehazeCtx->ProcRes,
                                   &pAdehazeCtx->stats, pAdehazeCtx->is_multi_isp_mode, pAdehazeCtx->FrameID);
    }
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode > DEHAZE_API_BYPASS && pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode < DEHAZE_API_OFF) {
        pAdehazeCtx->ProcRes.ProcResV30.enable = true;
        pAdehazeCtx->ProcRes.ProcResV30.dc_en = 0x1;
        pAdehazeCtx->ProcRes.ProcResV30.enhance_en = 0x0;
        //LOGD_ADEHAZE(" Dehaze fuction en:%d, Dehaze en:%d, Enhance en:%d,", 1, 1, 0 );

        if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode == DEHAZE_API_AUTO )
            pAdehazeCtx->ProcRes.ProcResV30.cfg_alpha = (int)LIMIT_VALUE((pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode == DEHAZE_API_MANUAL)
            pAdehazeCtx->ProcRes.ProcResV30.cfg_alpha = 255;
        //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV30.cfg_alpha);

        //hist en setting
        if(pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.hist_setting.en)
            pAdehazeCtx->ProcRes.ProcResV30.hist_en = 0x1;
        else
            pAdehazeCtx->ProcRes.ProcResV30.hist_en = 0;

        LOGD_ADEHAZE(" Dehaze module en:%d, Dehaze en:%d, Enhance en:%d, Hist en:%d\n", 1, 1, 0, pAdehazeCtx->ProcRes.ProcResV30.hist_en );

        GetDehazeParamsV30(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode == DEHAZE_API_MANUAL)
        {
            float level = (float)(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.stManual.strength);
            float level_default = 5;
            float level_diff = (float)(level - level_default);

            //sw_dhaz_cfg_wt
            float sw_dhaz_cfg_wt = (float)pAdehazeCtx->ProcRes.ProcResV30.cfg_wt;
            sw_dhaz_cfg_wt += level_diff * 0.05;
            sw_dhaz_cfg_wt = LIMIT_VALUE(sw_dhaz_cfg_wt, 0.99, 0.01);
            pAdehazeCtx->ProcRes.ProcResV30.cfg_wt = (int)sw_dhaz_cfg_wt;

            //sw_dhaz_cfg_air
            float sw_dhaz_cfg_air = (float)pAdehazeCtx->ProcRes.ProcResV30.cfg_air;
            sw_dhaz_cfg_air += level_diff * 5;
            sw_dhaz_cfg_air = LIMIT_VALUE(sw_dhaz_cfg_air, 255, 0.01);
            pAdehazeCtx->ProcRes.ProcResV30.cfg_air = (int)sw_dhaz_cfg_air;

            //sw_dhaz_cfg_tmax
            float sw_dhaz_cfg_tmax = (float)pAdehazeCtx->ProcRes.ProcResV30.cfg_tmax;
            sw_dhaz_cfg_tmax += level_diff * 0.05;
            sw_dhaz_cfg_tmax = LIMIT_VALUE(sw_dhaz_cfg_tmax, 0.99, 0.01);
            pAdehazeCtx->ProcRes.ProcResV30.cfg_tmax = (int)sw_dhaz_cfg_tmax;

            LOGD_ADEHAZE(" %s: Adehaze munual level:%f level_diff:%f\n", __func__, level, level_diff);
            LOGD_ADEHAZE(" %s: After manual api sw_dhaz_cfg_wt:%f sw_dhaz_cfg_air:%f sw_dhaz_cfg_tmax:%f\n", __func__, sw_dhaz_cfg_wt,
                         sw_dhaz_cfg_air, sw_dhaz_cfg_tmax);
        }

        //hist setting
        GetHistParamsV30(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        //gain table &Duo cam setting
        GetDehazeHistDuoISPSetting(&pAdehazeCtx->Calib.Dehaze_v30.DehazeCalibPara, &pAdehazeCtx->ProcRes,
                                   &pAdehazeCtx->stats, pAdehazeCtx->is_multi_isp_mode, pAdehazeCtx->FrameID);

    }
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode == DEHAZE_API_OFF) {
        AdehazeEnhanceApiOffProcessV30(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);
        //gain table &Duo cam setting
        GetDehazeHistDuoISPSetting(&pAdehazeCtx->Calib.Dehaze_v30.DehazeCalibPara, &pAdehazeCtx->ProcRes,
                                   &pAdehazeCtx->stats, pAdehazeCtx->is_multi_isp_mode, pAdehazeCtx->FrameID);
    }
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode == DEHAZE_API_TOOL)
        LOGE_ADEHAZE("%s:ISP30 DO NOT support Tool mode!!! \n", __func__);
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode == DEHAZE_API_ENHANCE_MANUAL) {
        pAdehazeCtx->ProcRes.ProcResV30.enable = true;
        pAdehazeCtx->ProcRes.ProcResV30.dc_en = 0x1;
        pAdehazeCtx->ProcRes.ProcResV30.enhance_en = 0x1;

        //cfg setting
        pAdehazeCtx->ProcRes.ProcResV30.cfg_alpha = (int)LIMIT_VALUE((pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
        //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV30.cfg_alpha);

        //hist en
        pAdehazeCtx->ProcRes.ProcResV30.hist_en = pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.hist_setting.en ? 1 : 0;
        LOGD_ADEHAZE(" Dehaze module en:%d, Dehaze en:%d, Enhance en:%d, Hist en:%d\n", 1, 0, 1, pAdehazeCtx->ProcRes.ProcResV30.hist_en );

        //hist setting
        GetHistParamsV30(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        //dehaze setting
        GetDehazeParamsV30(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        //enhance setting
        GetEnhanceParamsV30(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        float level = (float)(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.stEnhanceManual.level);
        level -= 50;
        float step = (float)(pAdehazeCtx->ProcRes.ProcResV30.enhance_value - 1024);
        step = LIMIT_VALUE(step, 30.9, 0);
        step /= 50;
        pAdehazeCtx->ProcRes.ProcResV30.enhance_value =  pAdehazeCtx->ProcRes.ProcResV30.enhance_value + (int)(step * level);

        LOGD_ADEHAZE("%s After enhance api enhance_value:0x%x\n", __func__, pAdehazeCtx->ProcRes.ProcResV30.enhance_value);

        //gain table &Duo cam setting
        GetDehazeHistDuoISPSetting(&pAdehazeCtx->Calib.Dehaze_v30.DehazeCalibPara, &pAdehazeCtx->ProcRes,
                                   &pAdehazeCtx->stats, pAdehazeCtx->is_multi_isp_mode, pAdehazeCtx->FrameID);

    }
    else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode == DEHAZE_API_ENHANCE_AUTO) {
        pAdehazeCtx->ProcRes.ProcResV30.enable = true;
        pAdehazeCtx->ProcRes.ProcResV30.dc_en = 0x1;
        pAdehazeCtx->ProcRes.ProcResV30.enhance_en = 0x1;

        //cfg setting
        pAdehazeCtx->ProcRes.ProcResV30.cfg_alpha = (int)LIMIT_VALUE((pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
        //LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV30.cfg_alpha);

        //hist en
        pAdehazeCtx->ProcRes.ProcResV30.hist_en = pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.hist_setting.en ? 1 : 0;

        LOGD_ADEHAZE(" Dehaze module en:%d, Dehaze en:%d, Enhance en:%d, Hist en:%d\n", 1, 0, 1, pAdehazeCtx->ProcRes.ProcResV30.hist_en );

        //hist setting
        GetHistParamsV30(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        //dehaze setting
        GetDehazeParamsV30(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        //enhance setting
        GetEnhanceParamsV30(&pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara, &pAdehazeCtx->ProcRes, variate);

        //gain table &Duo cam setting
        GetDehazeHistDuoISPSetting(&pAdehazeCtx->Calib.Dehaze_v30.DehazeCalibPara, &pAdehazeCtx->ProcRes,
                                   &pAdehazeCtx->stats, pAdehazeCtx->is_multi_isp_mode, pAdehazeCtx->FrameID);
    }
    else
        LOGE_ADEHAZE("%s:Wrong Adehaze API mode!!! \n", __func__);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}

void AdehazeGetStats
(
    AdehazeHandle_t*           pAdehazeCtx,
    rkisp_adehaze_stats_t*         ROData
) {
    LOG1_ADEHAZE( "%s:enter!\n", __FUNCTION__);
    LOGV_ADEHAZE("%s: Adehaze RO data from register:\n", __FUNCTION__);

    if(pAdehazeCtx->HWversion == ADEHAZE_ISP20) {
        pAdehazeCtx->stats.dehaze_stats_v20.dhaz_adp_air_base = ROData->dehaze_stats_v20.dhaz_adp_air_base;
        pAdehazeCtx->stats.dehaze_stats_v20.dhaz_adp_wt = ROData->dehaze_stats_v20.dhaz_adp_wt;
        pAdehazeCtx->stats.dehaze_stats_v20.dhaz_adp_gratio = ROData->dehaze_stats_v20.dhaz_adp_gratio;
        pAdehazeCtx->stats.dehaze_stats_v20.dhaz_adp_tmax = ROData->dehaze_stats_v20.dhaz_adp_tmax;
        for(int i = 0; i < 64; i++) {
            pAdehazeCtx->stats.dehaze_stats_v20.h_b_iir[i] = ROData->dehaze_stats_v20.h_b_iir[i];
            pAdehazeCtx->stats.dehaze_stats_v20.h_g_iir[i] = ROData->dehaze_stats_v20.h_g_iir[i];
            pAdehazeCtx->stats.dehaze_stats_v20.h_r_iir[i] = ROData->dehaze_stats_v20.h_r_iir[i];
        }

        LOGV_ADEHAZE("%s:  dhaz_adp_air_base:%d dhaz_adp_wt:%d dhaz_adp_gratio:%d dhaz_adp_tmax:%d\n", __FUNCTION__,
                     pAdehazeCtx->stats.dehaze_stats_v20.dhaz_adp_air_base, pAdehazeCtx->stats.dehaze_stats_v20.dhaz_adp_wt,
                     pAdehazeCtx->stats.dehaze_stats_v20.dhaz_adp_gratio, pAdehazeCtx->stats.dehaze_stats_v20.dhaz_adp_tmax);
        for(int i = 0; i < 64; i++) {
            LOGV_ADEHAZE("%s:  h_b_iir[%d]:%d:\n", __FUNCTION__, i, pAdehazeCtx->stats.dehaze_stats_v20.h_b_iir[i]);
            LOGV_ADEHAZE("%s:  h_g_iir[%d]:%d:\n", __FUNCTION__, i, pAdehazeCtx->stats.dehaze_stats_v20.h_g_iir[i]);
            LOGV_ADEHAZE("%s:  h_r_iir[%d]:%d:\n", __FUNCTION__, i, pAdehazeCtx->stats.dehaze_stats_v20.h_r_iir[i]);
        }
    }
    else if(pAdehazeCtx->HWversion == ADEHAZE_ISP21) {
        pAdehazeCtx->stats.dehaze_stats_v21.dhaz_adp_air_base = ROData->dehaze_stats_v21.dhaz_adp_air_base;
        pAdehazeCtx->stats.dehaze_stats_v21.dhaz_adp_wt = ROData->dehaze_stats_v21.dhaz_adp_wt;
        pAdehazeCtx->stats.dehaze_stats_v21.dhaz_adp_gratio = ROData->dehaze_stats_v21.dhaz_adp_gratio;
        pAdehazeCtx->stats.dehaze_stats_v21.dhaz_adp_tmax = ROData->dehaze_stats_v21.dhaz_adp_tmax;
        for(int i = 0; i < 64; i++)
            pAdehazeCtx->stats.dehaze_stats_v21.h_rgb_iir[i] = ROData->dehaze_stats_v21.h_rgb_iir[i];

        LOGV_ADEHAZE("%s:  dhaz_adp_air_base:%d dhaz_adp_wt:%d dhaz_adp_gratio:%d dhaz_adp_tmax:%d\n", __FUNCTION__,
                     pAdehazeCtx->stats.dehaze_stats_v21.dhaz_adp_air_base, pAdehazeCtx->stats.dehaze_stats_v21.dhaz_adp_wt,
                     pAdehazeCtx->stats.dehaze_stats_v21.dhaz_adp_gratio, pAdehazeCtx->stats.dehaze_stats_v21.dhaz_adp_tmax);
        for(int i = 0; i < 64; i++)
            LOGV_ADEHAZE("%s:  h_rgb_iir[%d]:%d:\n", __FUNCTION__, i, pAdehazeCtx->stats.dehaze_stats_v21.h_rgb_iir[i]);
    }
    else if(pAdehazeCtx->HWversion == ADEHAZE_ISP30) {
        pAdehazeCtx->stats.dehaze_stats_v30.dhaz_adp_air_base = ROData->dehaze_stats_v30.dhaz_adp_air_base;
        pAdehazeCtx->stats.dehaze_stats_v30.dhaz_adp_wt = ROData->dehaze_stats_v30.dhaz_adp_wt;
        pAdehazeCtx->stats.dehaze_stats_v30.dhaz_adp_gratio = ROData->dehaze_stats_v30.dhaz_adp_gratio;
        pAdehazeCtx->stats.dehaze_stats_v30.dhaz_adp_tmax = ROData->dehaze_stats_v30.dhaz_adp_tmax;
        pAdehazeCtx->stats.dehaze_stats_v30.dhaz_pic_sumh_left = ROData->dehaze_stats_v30.dhaz_pic_sumh_left;
        pAdehazeCtx->stats.dehaze_stats_v30.dhaz_pic_sumh_right = ROData->dehaze_stats_v30.dhaz_pic_sumh_right;
        for(int i = 0; i < 64; i++)
            pAdehazeCtx->stats.dehaze_stats_v30.h_rgb_iir[i] = ROData->dehaze_stats_v30.h_rgb_iir[i];

        LOGV_ADEHAZE("%s:  dhaz_adp_air_base:%d dhaz_adp_wt:%d dhaz_adp_gratio:%d dhaz_adp_tmax:%d dhaz_pic_sumh_left:%d dhaz_pic_sumh_right:%d\n", __FUNCTION__,
                     pAdehazeCtx->stats.dehaze_stats_v30.dhaz_adp_air_base, pAdehazeCtx->stats.dehaze_stats_v30.dhaz_adp_wt,
                     pAdehazeCtx->stats.dehaze_stats_v30.dhaz_adp_gratio, pAdehazeCtx->stats.dehaze_stats_v30.dhaz_adp_tmax,
                     pAdehazeCtx->stats.dehaze_stats_v30.dhaz_pic_sumh_left, pAdehazeCtx->stats.dehaze_stats_v30.dhaz_pic_sumh_right);
        for(int i = 0; i < 64; i++)
            LOGV_ADEHAZE("%s:  h_rgb_iir[%d]:%d:\n", __FUNCTION__, i, pAdehazeCtx->stats.dehaze_stats_v30.h_rgb_iir[i]);
    }

    //get other stats from stats
    for(int i = 0; i < 225; i++)
    {
        pAdehazeCtx->stats.other_stats.short_luma[i] = ROData->other_stats.short_luma[i];
        pAdehazeCtx->stats.other_stats.long_luma[i] = ROData->other_stats.long_luma[i];
        pAdehazeCtx->stats.other_stats.tmo_luma[i] = ROData->other_stats.tmo_luma[i];
    }

    if(pAdehazeCtx->FrameNumber == 3)
    {
        for(int i = 0; i < 25; i++)
            pAdehazeCtx->stats.other_stats.middle_luma[i] = ROData->other_stats.middle_luma[i];
    }

    LOG1_ADEHAZE( "%s:exit!\n", __FUNCTION__);
}

void AdehazeGetCurrDataGroup
(
    AdehazeHandle_t*           pAdehazeCtx,
    RKAiqAecExpInfo_t*         pAeEffExpo,
    XCamVideoBuffer*           pAePreRes
) {
    LOG1_ADEHAZE( "%s:enter!\n", __FUNCTION__);

    if(pAdehazeCtx->HWversion == ADEHAZE_ISP20) {
        int iso = 50;
        AdehazeExpInfo_t stExpInfo;
        memset(&stExpInfo, 0x00, sizeof(AdehazeExpInfo_t));

        stExpInfo.hdr_mode = 0;
        for(int i = 0; i < 3; i++) {
            stExpInfo.arIso[i] = 50;
            stExpInfo.arAGain[i] = 1.0;
            stExpInfo.arDGain[i] = 1.0;
            stExpInfo.arTime[i] = 0.01;
        }

        if(pAdehazeCtx->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
            stExpInfo.hdr_mode = 0;
        } else if(RK_AIQ_HDR_GET_WORKING_MODE(pAdehazeCtx->working_mode) == RK_AIQ_WORKING_MODE_ISP_HDR2) {
            stExpInfo.hdr_mode = 1;
        } else if(RK_AIQ_HDR_GET_WORKING_MODE(pAdehazeCtx->working_mode) == RK_AIQ_WORKING_MODE_ISP_HDR3) {
            stExpInfo.hdr_mode = 2;
        }

        if(pAeEffExpo != NULL) {
            if(pAdehazeCtx->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
                stExpInfo.arAGain[0] = pAeEffExpo->LinearExp.exp_real_params.analog_gain;
                stExpInfo.arDGain[0] = pAeEffExpo->LinearExp.exp_real_params.digital_gain;
                stExpInfo.arTime[0] = pAeEffExpo->LinearExp.exp_real_params.integration_time;
                stExpInfo.arIso[0] = stExpInfo.arAGain[0] * stExpInfo.arDGain[0] * 50;
            } else {
                for(int i = 0; i < 3; i++) {
                    stExpInfo.arAGain[i] = pAeEffExpo->HdrExp[i].exp_real_params.analog_gain;
                    stExpInfo.arDGain[i] = pAeEffExpo->HdrExp[i].exp_real_params.digital_gain;
                    stExpInfo.arTime[i] = pAeEffExpo->HdrExp[i].exp_real_params.integration_time;
                    stExpInfo.arIso[i] = stExpInfo.arAGain[i] * stExpInfo.arDGain[i] * 50;

                    LOGD_ADEHAZE("index:%d again:%f dgain:%f time:%f iso:%d hdr_mode:%d\n",
                                 i,
                                 stExpInfo.arAGain[i],
                                 stExpInfo.arDGain[i],
                                 stExpInfo.arTime[i],
                                 stExpInfo.arIso[i],
                                 stExpInfo.hdr_mode);
                }
            }
        } else {
            LOGE_ADEHAZE("%s:%d pAEPreRes is NULL, so use default instead \n", __FUNCTION__, __LINE__);
        }

        iso = stExpInfo.arIso[stExpInfo.hdr_mode];
        pAdehazeCtx->CurrData.V20.ISO = (float)iso;
    }
    else if(pAdehazeCtx->HWversion == ADEHAZE_ISP21) {
        RkAiqAlgoPreResAeInt* pAEPreRes = NULL;
        if (pAePreRes) {
            pAEPreRes = (RkAiqAlgoPreResAeInt*)pAePreRes->map(pAePreRes);
            AdehazeGetEnvLv(pAdehazeCtx, pAEPreRes);
        }
        else {
            pAdehazeCtx->CurrData.V21.EnvLv = 0.0;
            LOGW_ADEHAZE( "%s:PreResBuf is NULL!\n", __FUNCTION__);
        }
    }
    else if(pAdehazeCtx->HWversion == ADEHAZE_ISP30) {
        RkAiqAlgoPreResAeInt* pAEPreRes = NULL;
        if (pAePreRes) {
            pAEPreRes = (RkAiqAlgoPreResAeInt*)pAePreRes->map(pAePreRes);
            AdehazeGetEnvLv(pAdehazeCtx, pAEPreRes);
        }
        else {
            pAdehazeCtx->CurrData.V30.EnvLv = 0.0;
            LOGE_ADEHAZE( "%s:PreResBuf is NULL!\n", __FUNCTION__);
        }
    }

    LOG1_ADEHAZE( "%s:exit!\n", __FUNCTION__);
}

void AdehazeGetCurrData
(
    AdehazeHandle_t*           pAdehazeCtx,
    RkAiqAlgoProcAdhazInt*         procPara
) {
    LOG1_ADEHAZE( "%s:enter!\n", __FUNCTION__);

    if(pAdehazeCtx->HWversion == ADEHAZE_ISP20) {
        int iso = 50;
        AdehazeExpInfo_t stExpInfo;
        memset(&stExpInfo, 0x00, sizeof(AdehazeExpInfo_t));

        stExpInfo.hdr_mode = 0;
        for(int i = 0; i < 3; i++) {
            stExpInfo.arIso[i] = 50;
            stExpInfo.arAGain[i] = 1.0;
            stExpInfo.arDGain[i] = 1.0;
            stExpInfo.arTime[i] = 0.01;
        }

        if(pAdehazeCtx->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
            stExpInfo.hdr_mode = 0;
        } else if(RK_AIQ_HDR_GET_WORKING_MODE(pAdehazeCtx->working_mode) == RK_AIQ_WORKING_MODE_ISP_HDR2) {
            stExpInfo.hdr_mode = 1;
        } else if(RK_AIQ_HDR_GET_WORKING_MODE(pAdehazeCtx->working_mode) == RK_AIQ_WORKING_MODE_ISP_HDR3) {
            stExpInfo.hdr_mode = 2;
        }

        RkAiqAlgoPreResAeInt* pAEPreRes =
            (RkAiqAlgoPreResAeInt*)(procPara->rk_com.u.proc.pre_res_comb->ae_pre_res);

        if(pAEPreRes != NULL) {
            if(pAdehazeCtx->working_mode == RK_AIQ_WORKING_MODE_NORMAL) {
                stExpInfo.arAGain[0] = pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.analog_gain;
                stExpInfo.arDGain[0] = pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.digital_gain;
                stExpInfo.arTime[0] = pAEPreRes->ae_pre_res_rk.LinearExp.exp_real_params.integration_time;
                stExpInfo.arIso[0] = stExpInfo.arAGain[0] * stExpInfo.arDGain[0] * 50;
            } else {
                for(int i = 0; i < 3; i++) {
                    stExpInfo.arAGain[i] = pAEPreRes->ae_pre_res_rk.HdrExp[i].exp_real_params.analog_gain;
                    stExpInfo.arDGain[i] = pAEPreRes->ae_pre_res_rk.HdrExp[i].exp_real_params.digital_gain;
                    stExpInfo.arTime[i] = pAEPreRes->ae_pre_res_rk.HdrExp[i].exp_real_params.integration_time;
                    stExpInfo.arIso[i] = stExpInfo.arAGain[i] * stExpInfo.arDGain[i] * 50;

                    LOGD_ADEHAZE("index:%d again:%f dgain:%f time:%f iso:%d hdr_mode:%d\n",
                                 i,
                                 stExpInfo.arAGain[i],
                                 stExpInfo.arDGain[i],
                                 stExpInfo.arTime[i],
                                 stExpInfo.arIso[i],
                                 stExpInfo.hdr_mode);
                }
            }
        } else {
            LOGE_ADEHAZE("%s:%d pAEPreRes is NULL, so use default instead \n", __FUNCTION__, __LINE__);
        }

        iso = stExpInfo.arIso[stExpInfo.hdr_mode];
        pAdehazeCtx->CurrData.V20.ISO = (float)iso;
    }
    else if(pAdehazeCtx->HWversion == ADEHAZE_ISP21) {
        XCamVideoBuffer* xCamAePreRes = procPara->rk_com.u.proc.res_comb->ae_pre_res;
        RkAiqAlgoPreResAeInt* pAEPreRes = NULL;
        if (xCamAePreRes) {
            pAEPreRes = (RkAiqAlgoPreResAeInt*)xCamAePreRes->map(xCamAePreRes);
            AdehazeGetEnvLv(pAdehazeCtx, pAEPreRes);
        }
        else {
            pAdehazeCtx->CurrData.V21.EnvLv = 0.0;
            LOGW_ADEHAZE( "%s:PreResBuf is NULL!\n", __FUNCTION__);
        }
    }
    else if(pAdehazeCtx->HWversion == ADEHAZE_ISP30) {
        XCamVideoBuffer* xCamAePreRes = procPara->rk_com.u.proc.res_comb->ae_pre_res;
        RkAiqAlgoPreResAeInt* pAEPreRes = NULL;
        if (xCamAePreRes) {
            pAEPreRes = (RkAiqAlgoPreResAeInt*)xCamAePreRes->map(xCamAePreRes);
            AdehazeGetEnvLv(pAdehazeCtx, pAEPreRes);
        }
        else {
            pAdehazeCtx->CurrData.V30.EnvLv = 0.0;
            LOGE_ADEHAZE( "%s:PreResBuf is NULL!\n", __FUNCTION__);
        }
    }

    LOG1_ADEHAZE( "%s:exit!\n", __FUNCTION__);
}

void AdehazeGetEnvLv
(
    AdehazeHandle_t*           pAdehazeCtx,
    RkAiqAlgoPreResAeInt*         pAePreRes
) {
    LOG1_ADEHAZE( "%s:enter!\n", __FUNCTION__);

    if(pAePreRes == NULL) {
        LOGE_ADEHAZE( "%s:Ae Pre Res is NULL!\n", __FUNCTION__);
        pAdehazeCtx->CurrData.V21.EnvLv = 0.0;
        return;
    }

    pAdehazeCtx->CurrData.V21.EnvLv = pAePreRes->ae_pre_res_rk.GlobalEnvLv[pAePreRes->ae_pre_res_rk.NormalIndex];

    //Normalize the current envLv for AEC
    float maxEnvLuma = 65 / 10;
    float minEnvLuma = 0;
    pAdehazeCtx->CurrData.V21.EnvLv = (pAdehazeCtx->CurrData.V21.EnvLv  - minEnvLuma) / (maxEnvLuma - minEnvLuma);
    pAdehazeCtx->CurrData.V21.EnvLv = LIMIT_VALUE(pAdehazeCtx->CurrData.V21.EnvLv, ENVLVMAX, ENVLVMIN);

    LOG1_ADEHAZE( "%s:exit!\n", __FUNCTION__);
}

XCamReturn AdehazeInit(AdehazeHandle_t** pAdehazeCtx, CamCalibDbV2Context_t* pCalib)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t *handle = (AdehazeHandle_t*)malloc(sizeof(AdehazeHandle_t));
    if (NULL == handle)
        return XCAM_RETURN_ERROR_MEM;
    memset(handle, 0, sizeof(AdehazeHandle_t));

    if(CHECK_ISP_HW_V20())
        handle->HWversion = ADEHAZE_ISP20;
    else if(CHECK_ISP_HW_V21())
        handle->HWversion = ADEHAZE_ISP21;
    else if(CHECK_ISP_HW_V30())
        handle->HWversion = ADEHAZE_ISP30;

    if(handle->HWversion == ADEHAZE_ISP20) {
        //isp20
        CalibDbV2_dehaze_V20_t* calibv2_adehaze_calib_V20 =
            (CalibDbV2_dehaze_V20_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, adehaze_calib_v20));
        memcpy(&handle->Calib.Dehaze_v20, calibv2_adehaze_calib_V20, sizeof(CalibDbV2_dehaze_V20_t));
        memcpy(&handle->AdehazeAtrr.AdehazeAtrrV20.stTool, calibv2_adehaze_calib_V20, sizeof(CalibDbV2_dehaze_V20_t));
        handle->AdehazeAtrr.AdehazeAtrrV20.mode = DEHAZE_API_BYPASS;
        handle->PreData.V20.ISO = 50.0;
        handle->PreData.V20.ApiMode = DEHAZE_API_BYPASS;
    } else if(handle->HWversion == ADEHAZE_ISP21) {
        //isp21
        CalibDbV2_dehaze_V21_t* calibv2_adehaze_calib_V21 =
            (CalibDbV2_dehaze_V21_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, adehaze_calib_v21));
        memcpy(&handle->Calib.Dehaze_v21, calibv2_adehaze_calib_V21, sizeof(CalibDbV2_dehaze_V21_t));
        memcpy(&handle->AdehazeAtrr.AdehazeAtrrV21.stTool, calibv2_adehaze_calib_V21, sizeof(CalibDbV2_dehaze_V21_t));
        handle->AdehazeAtrr.AdehazeAtrrV21.mode = DEHAZE_API_BYPASS;
        handle->PreData.V21.EnvLv = 0.0;
        handle->PreData.V21.ApiMode = DEHAZE_API_BYPASS;
    } else if(handle->HWversion == ADEHAZE_ISP30) {
        //isp30
        CalibDbV2_dehaze_V30_t* calibv2_adehaze_calib_V30 =
            (CalibDbV2_dehaze_V30_t*)(CALIBDBV2_GET_MODULE_PTR(pCalib, adehaze_calib_v30));
        memcpy(&handle->Calib.Dehaze_v30, calibv2_adehaze_calib_V30, sizeof(CalibDbV2_dehaze_V30_t));
        handle->AdehazeAtrr.AdehazeAtrrV30.mode = DEHAZE_API_BYPASS;
        handle->PreData.V30.EnvLv = 0.0;
        handle->PreData.V30.ApiMode = DEHAZE_API_BYPASS;
    }

    *pAdehazeCtx = handle;
    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return(ret);
}

XCamReturn AdehazeRelease(AdehazeHandle_t* pAdehazeCtx)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (pAdehazeCtx)
        free(pAdehazeCtx);
    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return(ret);
}

XCamReturn AdehazeProcess(AdehazeHandle_t* pAdehazeCtx, AdehazeVersion_t version)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    LOG1_ADEHAZE("ENTER: %s \n", __func__);

    float variate = 0.0;

    if(version == ADEHAZE_ISP20) {
        variate = pAdehazeCtx->CurrData.V20.ISO;
        //big mode
        pAdehazeCtx->ProcRes.ProcResV20.big_en = pAdehazeCtx->width > DEHAZEBIGMODE ? 1 : 0;
        pAdehazeCtx->ProcRes.ProcResV20.nobig_en = (int)(1 - pAdehazeCtx->ProcRes.ProcResV20.big_en);

        if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode == DEHAZE_API_BYPASS)
            AdehazeEnhanceApiBypassProcess(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode > DEHAZE_API_BYPASS && pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode < DEHAZE_API_OFF) {
            pAdehazeCtx->ProcRes.ProcResV20.enable = true;
            pAdehazeCtx->ProcRes.ProcResV20.dc_en = 0x1;
            pAdehazeCtx->ProcRes.ProcResV20.enhance_en = 0x0;
            LOGD_ADEHAZE(" Dehaze fuction en:%d, Dehaze en:%d, Enhance en:%d,", 1, 1, 0 );

            if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode == DEHAZE_API_AUTO )
                pAdehazeCtx->ProcRes.ProcResV20.cfg_alpha = (int)LIMIT_VALUE((pAdehazeCtx->Calib.Dehaze_v20.DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
            else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode == DEHAZE_API_MANUAL)
                pAdehazeCtx->ProcRes.ProcResV20.cfg_alpha = 255;
            LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV20.cfg_alpha);

            //hist en setting
            if(pAdehazeCtx->Calib.Dehaze_v20.DehazeTuningPara.hist_setting.en)
                pAdehazeCtx->ProcRes.ProcResV20.hist_en = 0x1;
            else
                pAdehazeCtx->ProcRes.ProcResV20.hist_en = 0;

            LOGD_ADEHAZE(" Hist en:%d\n", pAdehazeCtx->ProcRes.ProcResV20.hist_en );

            GetDehazeParams(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);

            if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode == DEHAZE_API_MANUAL)
            {
                float level = (float)(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.stManual.strength);
                float level_default = 5;
                float level_diff = (float)(level - level_default);

                //sw_dhaz_cfg_wt
                float sw_dhaz_cfg_wt = (float)pAdehazeCtx->ProcRes.ProcResV20.cfg_wt;
                sw_dhaz_cfg_wt += level_diff * 0.05;
                sw_dhaz_cfg_wt = LIMIT_VALUE(sw_dhaz_cfg_wt, 0.99, 0.01);
                pAdehazeCtx->ProcRes.ProcResV20.cfg_wt = (int)sw_dhaz_cfg_wt;

                //sw_dhaz_cfg_air
                float sw_dhaz_cfg_air = (float)pAdehazeCtx->ProcRes.ProcResV20.cfg_air;
                sw_dhaz_cfg_air += level_diff * 5;
                sw_dhaz_cfg_air = LIMIT_VALUE(sw_dhaz_cfg_air, 255, 0.01);
                pAdehazeCtx->ProcRes.ProcResV20.cfg_air = (int)sw_dhaz_cfg_air;

                //sw_dhaz_cfg_tmax
                float sw_dhaz_cfg_tmax = (float)pAdehazeCtx->ProcRes.ProcResV20.cfg_tmax;
                sw_dhaz_cfg_tmax += level_diff * 0.05;
                sw_dhaz_cfg_tmax = LIMIT_VALUE(sw_dhaz_cfg_tmax, 0.99, 0.01);
                pAdehazeCtx->ProcRes.ProcResV20.cfg_tmax = (int)sw_dhaz_cfg_tmax;

                LOGD_ADEHAZE(" %s: Adehaze munual level:%f level_diff:%f\n", __func__, level, level_diff);
                LOGD_ADEHAZE(" %s: After manual api sw_dhaz_cfg_wt:%f sw_dhaz_cfg_air:%f sw_dhaz_cfg_tmax:%f\n", __func__, sw_dhaz_cfg_wt,
                             sw_dhaz_cfg_air, sw_dhaz_cfg_tmax);
            }
            //hist setting
            GetHistParams(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);

        }
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode == DEHAZE_API_OFF)
            AdehazeEnhanceApiOffProcess(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode == DEHAZE_API_TOOL)
            AdehazeApiToolProcess(&pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.stTool, &pAdehazeCtx->ProcRes, variate);
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode == DEHAZE_API_ENHANCE_MANUAL) {
            pAdehazeCtx->ProcRes.ProcResV20.enable = true;
            pAdehazeCtx->ProcRes.ProcResV20.dc_en = 0x1;
            pAdehazeCtx->ProcRes.ProcResV20.enhance_en = 0x1;

            //cfg setting
            pAdehazeCtx->ProcRes.ProcResV20.cfg_alpha = (int)LIMIT_VALUE((pAdehazeCtx->Calib.Dehaze_v20.DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
            LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV20.cfg_alpha);

            //dehaze setting
            GetDehazeParams(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);

            //enhance setting
            GetEnhanceParams(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);

            float level = (float)(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.stEnhanceManual.level);
            level -= 50;
            float step = (float)(pAdehazeCtx->ProcRes.ProcResV20.enhance_value - 1024);
            step = LIMIT_VALUE(step, 30.9, 0);
            step /= 50;
            pAdehazeCtx->ProcRes.ProcResV20.enhance_value =  pAdehazeCtx->ProcRes.ProcResV20.enhance_value + (int)(step * level);

            LOGD_ADEHAZE("%s After enhance api enhance_value:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV20.enhance_value);

            //hist setting
            GetHistParams(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);

        }
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode == DEHAZE_API_ENHANCE_AUTO) {
            pAdehazeCtx->ProcRes.ProcResV20.enable = true;
            pAdehazeCtx->ProcRes.ProcResV20.dc_en = 0x1;
            pAdehazeCtx->ProcRes.ProcResV20.enhance_en = 0x1;

            //cfg setting
            pAdehazeCtx->ProcRes.ProcResV20.cfg_alpha = (int)LIMIT_VALUE((pAdehazeCtx->Calib.Dehaze_v20.DehazeTuningPara.cfg_alpha * 256.0), 255, 0);
            LOGD_ADEHAZE("%s Config Alpha:%d\n", __func__, pAdehazeCtx->ProcRes.ProcResV20.cfg_alpha);

            //dehaze setting
            GetDehazeParams(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);

            //enhance setting
            GetEnhanceParams(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);

            //hist en
            pAdehazeCtx->ProcRes.ProcResV20.hist_en = pAdehazeCtx->Calib.Dehaze_v20.DehazeTuningPara.hist_setting.en ? 1 : 0;
            //hist setting
            GetHistParams(&pAdehazeCtx->Calib.Dehaze_v20, &pAdehazeCtx->ProcRes, variate);
        }
        else
            LOGE_ADEHAZE("%s:Wrong Adehaze API mode!!! \n", __func__);

    }
    else if(version == ADEHAZE_ISP21) {
        variate = pAdehazeCtx->CurrData.V21.EnvLv;
        AdehazeProcessV21(pAdehazeCtx, variate);
    }
    else if(version == ADEHAZE_ISP30) {
        variate = pAdehazeCtx->CurrData.V30.EnvLv;
        AdehazeProcessV30(pAdehazeCtx, variate);
    }
    else
        LOGE_ADEHAZE(" %s:Wrong hardware version!! \n", __func__);

    //store pre data
    if(version == ADEHAZE_ISP20)
        pAdehazeCtx->PreData.V20.ISO = pAdehazeCtx->CurrData.V20.ISO;
    else if(version == ADEHAZE_ISP21)
        pAdehazeCtx->PreData.V21.EnvLv = pAdehazeCtx->CurrData.V21.EnvLv;
    else if(version == ADEHAZE_ISP30)
        pAdehazeCtx->PreData.V30.EnvLv = pAdehazeCtx->CurrData.V30.EnvLv;

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}

bool AdehazeByPassProcessing(AdehazeHandle_t* pAdehazeCtx)
{
    LOG1_ADEHAZE("ENTER: %s \n", __func__);
    bool ret = false;
    float diff = 0.0;

    if(pAdehazeCtx->FrameID <= 2)
        pAdehazeCtx->byPassProc = false;
    else if(pAdehazeCtx->HWversion == ADEHAZE_ISP20) {
        if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode > DEHAZE_API_BYPASS)
            pAdehazeCtx->byPassProc = false;
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV20.mode != pAdehazeCtx->PreData.V20.ApiMode)
            pAdehazeCtx->byPassProc = false;
        else {
            diff = (pAdehazeCtx->PreData.V20.ISO - pAdehazeCtx->CurrData.V20.ISO) / pAdehazeCtx->PreData.V20.ISO;
            if(diff > pAdehazeCtx->Calib.Dehaze_v20.DehazeTuningPara.ByPassThr || diff < (0 - pAdehazeCtx->Calib.Dehaze_v20.DehazeTuningPara.ByPassThr))
                pAdehazeCtx->byPassProc = false;
            else
                pAdehazeCtx->byPassProc = true;
        }
    }
    else if(pAdehazeCtx->HWversion == ADEHAZE_ISP21) {
        if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode > DEHAZE_API_BYPASS)
            pAdehazeCtx->byPassProc = false;
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV21.mode != pAdehazeCtx->PreData.V21.ApiMode)
            pAdehazeCtx->byPassProc = false;
        else {
            diff = pAdehazeCtx->PreData.V21.EnvLv - pAdehazeCtx->CurrData.V21.EnvLv;
            if(pAdehazeCtx->PreData.V21.EnvLv == 0.0) {
                diff = pAdehazeCtx->CurrData.V21.EnvLv;
                if(diff == 0.0)
                    pAdehazeCtx->byPassProc = true;
                else
                    pAdehazeCtx->byPassProc = false;
            }
            else {
                diff /= pAdehazeCtx->PreData.V21.EnvLv;
                if(diff >= pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara.ByPassThr || diff <= (0 - pAdehazeCtx->Calib.Dehaze_v21.DehazeTuningPara.ByPassThr))
                    pAdehazeCtx->byPassProc = false;
                else
                    pAdehazeCtx->byPassProc = true;

            }
        }

    }
    else if(pAdehazeCtx->HWversion == ADEHAZE_ISP30) {
        if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode > DEHAZE_API_BYPASS)
            pAdehazeCtx->byPassProc = false;
        else if(pAdehazeCtx->AdehazeAtrr.AdehazeAtrrV30.mode != pAdehazeCtx->PreData.V30.ApiMode)
            pAdehazeCtx->byPassProc = false;
        else {
            diff = pAdehazeCtx->PreData.V30.EnvLv - pAdehazeCtx->CurrData.V30.EnvLv;
            if(pAdehazeCtx->PreData.V30.EnvLv == 0.0) {
                diff = pAdehazeCtx->CurrData.V30.EnvLv;
                if(diff == 0.0)
                    pAdehazeCtx->byPassProc = true;
                else
                    pAdehazeCtx->byPassProc = false;
            }
            else {
                diff /= pAdehazeCtx->PreData.V30.EnvLv;
                if(diff >= pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.ByPassThr || diff <= (0 - pAdehazeCtx->Calib.Dehaze_v30.DehazeTuningPara.ByPassThr))
                    pAdehazeCtx->byPassProc = false;
                else
                    pAdehazeCtx->byPassProc = true;

            }
        }

    }
    else
        LOGE_ADEHAZE(" %s:Wrong hardware version!! \n", __func__);

    ret = pAdehazeCtx->byPassProc;

    LOGD_ADEHAZE("%s:FrameCnt:%d byPassProc:%d \n", __func__, pAdehazeCtx->FrameNumber, ret);

    LOG1_ADEHAZE("EXIT: %s \n", __func__);
    return ret;
}

