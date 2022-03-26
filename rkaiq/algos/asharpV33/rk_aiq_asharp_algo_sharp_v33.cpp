/*
 * rk_aiq_asharp_algo_sharp_v33.cpp
 *
 *  Copyright (c) 2022 Rockchip Corporation
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

#include "rk_aiq_asharp_algo_sharp_v33.h"

RKAIQ_BEGIN_DECLARE

Asharp_result_V33_t sharp_select_params_by_ISO_V33(RK_SHARP_Params_V33_t* pParams,
        RK_SHARP_Params_V33_Select_t* pSelect,
        Asharp_ExpInfo_V33_t* pExpInfo) {
    Asharp_result_V33_t res = ASHARP_V33_RET_SUCCESS;

    int i;
    int iso     = 50;
    int iso_div = 50;
    float ratio = 0.0f;
    int iso_low = iso, iso_high = iso;
    int gain_high = 0, gain_low = 0;
    int max_iso_step = RK_SHARP_V33_MAX_ISO_NUM;
    int sum_coeff, offset;

    LOGI_ASHARP("%s(%d): enter\n", __FUNCTION__, __LINE__);

    if (pParams == NULL) {
        LOGE_ASHARP("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ASHARP_V33_RET_NULL_POINTER;
    }

    if (pSelect == NULL) {
        LOGE_ASHARP("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ASHARP_V33_RET_NULL_POINTER;
    }

    if (pExpInfo == NULL) {
        LOGE_ASHARP("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ASHARP_V33_RET_NULL_POINTER;
    }

    iso = pExpInfo->arIso[pExpInfo->hdr_mode];

#ifndef RK_SIMULATOR_HW
    for (i = 0; i < max_iso_step - 1; i++) {
        if (iso >= pParams->iso[i] && iso <= pParams->iso[i + 1]) {
            iso_low   = pParams->iso[i];
            iso_high  = pParams->iso[i + 1];
            gain_low  = i;
            gain_high = i + 1;
            ratio     = (float)(iso - iso_low) / (iso_high - iso_low);
            break;
        }
    }

    if (iso < pParams->iso[0]) {
        iso_low   = pParams->iso[0];
        iso_high  = pParams->iso[1];
        gain_low  = 0;
        gain_high = 1;
        ratio     = 0;
    }

    if (iso > pParams->iso[max_iso_step - 1]) {
        iso_low   = pParams->iso[max_iso_step - 2];
        iso_high  = pParams->iso[max_iso_step - 1];
        gain_low  = max_iso_step - 2;
        gain_high = max_iso_step - 1;
        ratio     = 1;
    }
#else
    for (i = max_iso_step - 1; i >= 0; i--) {
        if (iso < iso_div * (2 << i)) {
            iso_low  = iso_div * (2 << (i)) / 2;
            iso_high = iso_div * (2 << i);
        }
    }

    ratio = (float)(iso - iso_low) / (iso_high - iso_low);
    if (iso_low == iso) {
        iso_high = iso;
        ratio    = 0;
    }
    if (iso_high == iso) {
        iso_low = iso;
        ratio   = 1;
    }
    gain_high = (int)(log((float)iso_high / 50) / log((float)2));
    gain_low  = (int)(log((float)iso_low / 50) / log((float)2));

    gain_low  = MIN(MAX(gain_low, 0), max_iso_step - 1);
    gain_high = MIN(MAX(gain_high, 0), max_iso_step - 1);
#endif

    LOGD_ASHARP("%s:%d iso:%d gainlow:%d gian_high:%d\n", __FUNCTION__, __LINE__, iso, gain_high,
                gain_high);

    pSelect->enable = pParams->enable;

    pSelect->center_mode    = pParams->center_mode;
    pSelect->kernel_sigma_enable = pParams->kernel_sigma_enable;

    for (int i = 0; i < RK_SHARP_V33_LUMA_POINT_NUM; i++) {
        pSelect->sharpParamsSelectISO.luma_point[i] =
            pParams->sharpParamsISO[gain_low].luma_point[i];
        pSelect->sharpParamsSelectISO.luma_sigma[i] =
            INTERP_V4(pParams->sharpParamsISO[gain_low].luma_sigma[i],
                      pParams->sharpParamsISO[gain_high].luma_sigma[i], ratio);
        pSelect->sharpParamsSelectISO.lum_clip_h[i] =
            (int16_t)ROUND_F(INTERP_V4(pParams->sharpParamsISO[gain_low].lum_clip_h[i],
                                       pParams->sharpParamsISO[gain_high].lum_clip_h[i], ratio));
    }

    if (iso - iso_low <= iso_high - iso) {
        pSelect->sharpParamsSelectISO.global_clip_pos =
            pParams->sharpParamsISO[gain_low].global_clip_pos;
        pSelect->sharpParamsSelectISO.GaussianFilter_radius =
            pParams->sharpParamsISO[gain_low].GaussianFilter_radius;
    } else {
        pSelect->sharpParamsSelectISO.global_clip_pos =
            pParams->sharpParamsISO[gain_high].global_clip_pos;
        pSelect->sharpParamsSelectISO.GaussianFilter_radius =
            pParams->sharpParamsISO[gain_high].GaussianFilter_radius;
    }
    pSelect->sharpParamsSelectISO.prefilter_sigma =
        INTERP_V4(pParams->sharpParamsISO[gain_low].prefilter_sigma,
                  pParams->sharpParamsISO[gain_high].prefilter_sigma, ratio);
    pSelect->sharpParamsSelectISO.hfBilateralFilter_sigma =
        INTERP_V4(pParams->sharpParamsISO[gain_low].hfBilateralFilter_sigma,
                  pParams->sharpParamsISO[gain_high].hfBilateralFilter_sigma, ratio);
    pSelect->sharpParamsSelectISO.GaussianFilter_sigma =
        INTERP_V4(pParams->sharpParamsISO[gain_low].GaussianFilter_sigma,
                  pParams->sharpParamsISO[gain_high].GaussianFilter_sigma, ratio);
    pSelect->sharpParamsSelectISO.pbf_gain =
        INTERP_V4(pParams->sharpParamsISO[gain_low].pbf_gain,
                  pParams->sharpParamsISO[gain_high].pbf_gain, ratio);
    pSelect->sharpParamsSelectISO.pbf_add =
        INTERP_V4(pParams->sharpParamsISO[gain_low].pbf_add,
                  pParams->sharpParamsISO[gain_high].pbf_add, ratio);
    pSelect->sharpParamsSelectISO.pbf_ratio =
        INTERP_V4(pParams->sharpParamsISO[gain_low].pbf_ratio,
                  pParams->sharpParamsISO[gain_high].pbf_ratio, ratio);

    pSelect->sharpParamsSelectISO.gaus_ratio =
        INTERP_V4(pParams->sharpParamsISO[gain_low].gaus_ratio,
                  pParams->sharpParamsISO[gain_high].gaus_ratio, ratio);
    pSelect->sharpParamsSelectISO.sharp_ratio =
        INTERP_V4(pParams->sharpParamsISO[gain_low].sharp_ratio,
                  pParams->sharpParamsISO[gain_high].sharp_ratio, ratio);

    pSelect->sharpParamsSelectISO.bf_gain =
        INTERP_V4(pParams->sharpParamsISO[gain_low].bf_gain,
                  pParams->sharpParamsISO[gain_high].bf_gain, ratio);
    pSelect->sharpParamsSelectISO.bf_add = INTERP_V4(
            pParams->sharpParamsISO[gain_low].bf_add, pParams->sharpParamsISO[gain_high].bf_add, ratio);
    pSelect->sharpParamsSelectISO.bf_ratio =
        INTERP_V4(pParams->sharpParamsISO[gain_low].bf_ratio,
                  pParams->sharpParamsISO[gain_high].bf_ratio, ratio);

    for (int i = 0; i < RK_SHARP_V33_PBF_DIAM * RK_SHARP_V33_PBF_DIAM; i++) {
        pSelect->sharpParamsSelectISO.kernel_pre_bila_filter[i] =
            INTERP_V4(pParams->sharpParamsISO[gain_low].kernel_pre_bila_filter[i],
                      pParams->sharpParamsISO[gain_high].kernel_pre_bila_filter[i], ratio);
    }

    for (int i = 0; i < RK_SHARP_V33_RF_DIAM * RK_SHARP_V33_RF_DIAM; i++) {
        pSelect->sharpParamsSelectISO.kernel_range_filter[i] =
            INTERP_V4(pParams->sharpParamsISO[gain_low].kernel_range_filter[i],
                      pParams->sharpParamsISO[gain_high].kernel_range_filter[i], ratio);
    }

    for (int i = 0; i < RK_SHARP_V33_BF_DIAM * RK_SHARP_V33_BF_DIAM; i++) {
        pSelect->sharpParamsSelectISO.kernel_bila_filter[i] =
            INTERP_V4(pParams->sharpParamsISO[gain_low].kernel_bila_filter[i],
                      pParams->sharpParamsISO[gain_high].kernel_bila_filter[i], ratio);
    }

    pSelect->sharpParamsSelectISO.global_gain =
        INTERP_V4(pParams->sharpParamsISO[gain_low].global_gain,
                  pParams->sharpParamsISO[gain_high].global_gain, ratio);
    pSelect->sharpParamsSelectISO.global_gain_alpha =
        INTERP_V4(pParams->sharpParamsISO[gain_low].global_gain_alpha,
                  pParams->sharpParamsISO[gain_high].global_gain_alpha, ratio);
    pSelect->sharpParamsSelectISO.local_gainscale =
        INTERP_V4(pParams->sharpParamsISO[gain_low].local_gainscale,
                  pParams->sharpParamsISO[gain_high].local_gainscale, ratio);

    for (int i = 0; i < RK_SHARP_V33_SHARP_ADJ_GAIN_TABLE_LEN; i++) {
        pSelect->sharpParamsSelectISO.gain_adj_sharp_strength[i] =
            INTERP_V4(pParams->sharpParamsISO[gain_low].gain_adj_sharp_strength[i],
                      pParams->sharpParamsISO[gain_high].gain_adj_sharp_strength[i], ratio);
    }
    pSelect->sharpParamsSelectISO.exgain_bypass =
        INTERP_V4(pParams->sharpParamsISO[gain_low].exgain_bypass,
                  pParams->sharpParamsISO[gain_high].exgain_bypass, ratio);

    for (int i = 0; i < RK_SHARP_V33_STRENGTH_TABLE_LEN; i++) {
        pSelect->sharpParamsSelectISO.dis_adj_sharp_strength[i] =
            INTERP_V4(pParams->sharpParamsISO[gain_low].dis_adj_sharp_strength[i],
                      pParams->sharpParamsISO[gain_high].dis_adj_sharp_strength[i], ratio);
    }

    pSelect->sharpParamsSelectISO.noiseclip_strength =
        INTERP_V4(pParams->sharpParamsISO[gain_low].noiseclip_strength,
                  pParams->sharpParamsISO[gain_high].noiseclip_strength, ratio);
    pSelect->sharpParamsSelectISO.enhance_bit =
        INTERP_V4(pParams->sharpParamsISO[gain_low].enhance_bit,
                  pParams->sharpParamsISO[gain_high].enhance_bit, ratio);
    pSelect->sharpParamsSelectISO.noiseclip_mode =
        INTERP_V4(pParams->sharpParamsISO[gain_low].noiseclip_mode,
                  pParams->sharpParamsISO[gain_high].noiseclip_mode, ratio);
    pSelect->sharpParamsSelectISO.noise_sigma_clip =
        INTERP_V4(pParams->sharpParamsISO[gain_low].noise_sigma_clip,
                  pParams->sharpParamsISO[gain_high].noise_sigma_clip, ratio);

    LOGI_ASHARP("%s(%d): exit\n", __FUNCTION__, __LINE__);
    return res;
}

Asharp_result_V33_t sharp_fix_transfer_V33(RK_SHARP_Params_V33_Select_t* pSelect,
        RK_SHARP_Fix_V33_t* pFix, float fPercent,
        Asharp_ExpInfo_V33_t *pExpInfo) {
    int sum_coeff, offset;
    int pbf_sigma_shift     = 0;
    int bf_sigma_shift      = 0;
    Asharp_result_V33_t res = ASHARP_V33_RET_SUCCESS;
    int tmp                 = 0;

    LOGI_ASHARP("%s(%d): enter\n", __FUNCTION__, __LINE__);

    if (pSelect == NULL) {
        LOGE_ASHARP("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ASHARP_V33_RET_NULL_POINTER;
    }

    if (pFix == NULL) {
        LOGE_ASHARP("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ASHARP_V33_RET_NULL_POINTER;
    }

    if (fPercent <= 0.0) {
        fPercent = 0.000001;
    }

    if(pExpInfo == NULL) {
        LOGE_ASHARP("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ASHARP_V33_RET_NULL_POINTER;
    }

    LOGD_ASHARP("%s:%d strength:%f raw:width:%d height:%d\n",
                __FUNCTION__, __LINE__,
                fPercent, pExpInfo->rawHeight, pExpInfo->rawWidth);

    int rows = pExpInfo->rawHeight; //raw height
    int cols = pExpInfo->rawWidth; //raw  width

    // SHARP_SHARP_EN (0x0000)
    pFix->sharp_exgain_bypass = pSelect->sharpParamsSelectISO.exgain_bypass;
    pFix->sharp_center_mode = 0;
    pFix->sharp_bypass        = !pSelect->enable;
    pFix->sharp_en            = pSelect->enable;

    // CENTER
    pFix->sharp_center_mode   = pSelect->center_mode;
    tmp = cols / 2;
    pFix->sharp_center_wid = CLIP(tmp, 0, 8191);
    tmp = rows / 2;
    pFix->sharp_center_het = CLIP(tmp, 0, 8191);

    // SHARP_SHARP_RATIO  (0x0004)
    tmp                     = (int)ROUND_F(pSelect->sharpParamsSelectISO.pbf_ratio / fPercent *
                                           (1 << RK_SHARP_V33_BF_RATIO_FIX_BITS));
    pFix->sharp_pbf_ratio   = CLIP(tmp, 0, 255);
    tmp                     = (int)ROUND_F(pSelect->sharpParamsSelectISO.gaus_ratio / fPercent *
                                           (1 << RK_SHARP_V33_GAUS_RATIO_FIX_BITS));
    pFix->sharp_gaus_ratio  = CLIP(tmp, 0, 255);
    tmp                     = (int)ROUND_F(pSelect->sharpParamsSelectISO.sharp_ratio * fPercent *
                                           (1 << RK_SHARP_V33_SHARP_RATIO_FIX_BITS));
    pFix->sharp_sharp_ratio = CLIP(tmp, 0, 127);
    tmp                     = (int)ROUND_F(pSelect->sharpParamsSelectISO.bf_ratio / fPercent *
                                           (1 << RK_SHARP_V33_BF_RATIO_FIX_BITS));
    pFix->sharp_bf_ratio    = CLIP(tmp, 0, 255);

    // SHARP_SHARP_LUMA_DX (0x0008)
    for (int i = 0; i < RK_SHARP_V33_LUMA_POINT_NUM - 1; i++) {
        tmp                    = (int16_t)LOG2(pSelect->sharpParamsSelectISO.luma_point[i + 1] -
                                               pSelect->sharpParamsSelectISO.luma_point[i]);
        pFix->sharp_luma_dx[i] = CLIP(tmp, 0, 15);
    }

    // SHARP_SHARP_PBF_SIGMA_INV_0 (0x000c - 0x0014)
    // pre bf sigma inv
    int sigma_deci_bits = 9;
    int sigma_inte_bits = 1;
    int max_val         = 0;
    int min_val         = 65536;
    int shf_bits        = 0;
    short sigma_bits[3];
    for (int i = 0; i < RK_SHARP_V33_LUMA_POINT_NUM; i++) {
        int cur_sigma = FLOOR(
                            (pSelect->sharpParamsSelectISO.luma_sigma[i] * pSelect->sharpParamsSelectISO.pbf_gain +
                             pSelect->sharpParamsSelectISO.pbf_add) /
                            fPercent);
        if (max_val < cur_sigma) max_val = cur_sigma;
        if (min_val > cur_sigma) min_val = cur_sigma;
    }
    sigma_bits[0]   = FLOOR(log((float)min_val) / log((float)2));
    sigma_bits[1]   = MAX(sigma_inte_bits - sigma_bits[0], 0);
    sigma_bits[2]   = sigma_deci_bits + sigma_bits[0];
    pbf_sigma_shift = sigma_bits[2] - 5;
    for (int i = 0; i < RK_SHARP_V33_LUMA_POINT_NUM; i++) {
        tmp = (int16_t)ROUND_F(
                  (float)1 /
                  (pSelect->sharpParamsSelectISO.luma_sigma[i] * pSelect->sharpParamsSelectISO.pbf_gain +
                   pSelect->sharpParamsSelectISO.pbf_add) *
                  fPercent * (1 << sigma_bits[2]));
        pFix->sharp_pbf_sigma_inv[i] = CLIP(tmp, 0, 4095);
    }

    // SHARP_SHARP_BF_SIGMA_INV_0 (0x0018 -  0x0020)
    // bf sigma inv
    sigma_deci_bits = 9;
    sigma_inte_bits = 1;
    max_val         = 0;
    min_val         = 65536;
    shf_bits        = 0;
    for (int i = 0; i < RK_SHARP_V33_LUMA_POINT_NUM; i++) {
        int cur_sigma = FLOOR(
                            (pSelect->sharpParamsSelectISO.luma_sigma[i] * pSelect->sharpParamsSelectISO.bf_gain +
                             pSelect->sharpParamsSelectISO.bf_add) /
                            fPercent);
        if (max_val < cur_sigma) max_val = cur_sigma;
        if (min_val > cur_sigma) min_val = cur_sigma;
    }
    sigma_bits[0]  = FLOOR(log((float)min_val) / log((float)2));
    sigma_bits[1]  = MAX(sigma_inte_bits - sigma_bits[0], 0);
    sigma_bits[2]  = sigma_deci_bits + sigma_bits[0];
    bf_sigma_shift = sigma_bits[2] - 5;
    for (int i = 0; i < RK_SHARP_V33_LUMA_POINT_NUM; i++) {
        tmp = (int16_t)ROUND_F(
                  (float)1 /
                  (pSelect->sharpParamsSelectISO.luma_sigma[i] * pSelect->sharpParamsSelectISO.bf_gain +
                   pSelect->sharpParamsSelectISO.bf_add) *
                  fPercent * (1 << sigma_bits[2]));
        pFix->sharp_bf_sigma_inv[i] = CLIP(tmp, 0, 4095);
    }

    // SHARP_SHARP_SIGMA_SHIFT (0x00024)
    pFix->sharp_pbf_sigma_shift = CLIP(pbf_sigma_shift, 0, 15);
    pFix->sharp_bf_sigma_shift  = CLIP(bf_sigma_shift, 0, 15);

    if (pSelect->sharpParamsSelectISO.global_clip_pos == 1) {
        pSelect->sharpParamsSelectISO.dis_adj_sharp_strength[RK_SHARP_V33_STRENGTH_TABLE_LEN - 1] =
            64;
        for (int i = 0; i < RK_SHARP_V33_LUMA_POINT_NUM; i++) {
            pSelect->sharpParamsSelectISO.lum_clip_h[i] =
                MAX(pSelect->sharpParamsSelectISO.lum_clip_h[i], 256);
        }
    } else if (pSelect->sharpParamsSelectISO.global_clip_pos == 2) {
        pSelect->sharpParamsSelectISO.dis_adj_sharp_strength[RK_SHARP_V33_STRENGTH_TABLE_LEN - 1] =
            128;
        for (int i = 0; i < RK_SHARP_V33_LUMA_POINT_NUM; i++) {
            pSelect->sharpParamsSelectISO.lum_clip_h[i] =
                MAX(pSelect->sharpParamsSelectISO.lum_clip_h[i], 512);
        }
    } else {
        pSelect->sharpParamsSelectISO.dis_adj_sharp_strength[RK_SHARP_V33_STRENGTH_TABLE_LEN - 1] =
            0;
    }
    // SHARP_SHARP_CLIP_HF_0 (0x0034 -  0x003c)
    for (int i = 0; i < RK_SHARP_V33_LUMA_POINT_NUM; i++) {
        tmp                    = (int)(pSelect->sharpParamsSelectISO.lum_clip_h[i] * fPercent);
        pFix->sharp_clip_hf[i] = CLIP(tmp, 0, 1023);
    }

    // SHARP_SHARP_PBF_COEF (0x00040)
    // filter coeff
    // bf coeff
    // rk_sharp_V33_pbfCoeff : [4], [1], [0]
    float pre_bila_filter[3];
    if (pSelect->kernel_sigma_enable) {
        float dis_table_3x3[3] = {0.0, 1.0, 2.0};
        double e               = 2.71828182845905;
        float sigma            = pSelect->sharpParamsSelectISO.prefilter_sigma;
        float sum_gauss_coeff  = 0.0;
        for (int i = 0; i < 3; i++) {
            float tmp          = pow(e, -dis_table_3x3[i] / 2.0 / sigma / sigma);
            pre_bila_filter[i] = tmp;
        }
        sum_gauss_coeff = pre_bila_filter[0] + 4 * pre_bila_filter[1] + 4 * pre_bila_filter[2];
        for (int i = 0; i < 3; i++) {
            pre_bila_filter[i] = pre_bila_filter[i] / sum_gauss_coeff;
            LOGD_ASHARP("kernel_sigma_enable:%d pre_bila_filter[%d]:%f\n",
                        pSelect->kernel_sigma_enable, i, pre_bila_filter[i]);
        }
    } else {
        for (int i = 0; i < 3; i++) {
            pre_bila_filter[i] = pSelect->sharpParamsSelectISO.kernel_pre_bila_filter[i];
            LOGD_ASHARP("kernel_sigma_enable:%d pre_bila_filter[%d]:%f\n",
                        pSelect->kernel_sigma_enable, i, pre_bila_filter[i]);
        }
    }
    tmp = (int)ROUND_F(pre_bila_filter[0] * (1 << RK_SHARP_V33_PBFCOEFF_FIX_BITS));
    pFix->sharp_pbf_coef[0] = CLIP(tmp, 0, 127);
    tmp = (int)ROUND_F(pre_bila_filter[1] * (1 << RK_SHARP_V33_PBFCOEFF_FIX_BITS));
    pFix->sharp_pbf_coef[1] = CLIP(tmp, 0, 127);
    tmp = (int)ROUND_F(pre_bila_filter[2] * (1 << RK_SHARP_V33_PBFCOEFF_FIX_BITS));
    pFix->sharp_pbf_coef[2] = CLIP(tmp, 0, 127);

    sum_coeff = pFix->sharp_pbf_coef[0] + 4 * pFix->sharp_pbf_coef[1] + 4 * pFix->sharp_pbf_coef[2];
    offset    = (1 << RK_SHARP_V33_PBFCOEFF_FIX_BITS) - sum_coeff;
    tmp       = (int)(pFix->sharp_pbf_coef[0] + offset);
    pFix->sharp_pbf_coef[0] = CLIP(tmp, 0, 127);

    // SHARP_SHARP_GAUS_COEF (0x00048)
    // rk_sharp_V33_rfCoeff :  [4], [1], [0]
    float bila_filter[3];
    if (pSelect->kernel_sigma_enable) {
        float dis_table_3x3[3] = {0.0, 1.0, 2.0};
        double e               = 2.71828182845905;
        float sigma            = pSelect->sharpParamsSelectISO.hfBilateralFilter_sigma;
        float sum_gauss_coeff  = 0.0;
        for (int i = 0; i < 3; i++) {
            float tmp      = pow(e, -dis_table_3x3[i] / 2.0 / sigma / sigma);
            bila_filter[i] = tmp;
        }
        sum_gauss_coeff = bila_filter[0] + 4 * bila_filter[1] + 4 * bila_filter[2];
        for (int i = 0; i < 3; i++) {
            bila_filter[i] = bila_filter[i] / sum_gauss_coeff;
            LOGD_ASHARP("kernel_sigma_enable:%d bila_filter[%d]:%f\n", pSelect->kernel_sigma_enable,
                        i, bila_filter[i]);
        }
    } else {
        for (int i = 0; i < 3; i++) {
            bila_filter[i] = pSelect->sharpParamsSelectISO.kernel_bila_filter[i];
            LOGD_ASHARP("kernel_sigma_enable:%d bila_filter[%d]:%f\n", pSelect->kernel_sigma_enable,
                        i, bila_filter[i]);
        }
    }
    tmp                    = (int)ROUND_F(bila_filter[0] * (1 << RK_SHARP_V33_RFCOEFF_FIX_BITS));
    pFix->sharp_bf_coef[0] = CLIP(tmp, 0, 127);
    tmp                    = (int)ROUND_F(bila_filter[1] * (1 << RK_SHARP_V33_RFCOEFF_FIX_BITS));
    pFix->sharp_bf_coef[1] = CLIP(tmp, 0, 127);
    tmp                    = (int)ROUND_F(bila_filter[2] * (1 << RK_SHARP_V33_RFCOEFF_FIX_BITS));
    pFix->sharp_bf_coef[2] = CLIP(tmp, 0, 127);

    sum_coeff = pFix->sharp_bf_coef[0] + 4 * pFix->sharp_bf_coef[1] + 4 * pFix->sharp_bf_coef[2];
    offset    = (1 << RK_SHARP_V33_PBFCOEFF_FIX_BITS) - sum_coeff;
    tmp       = (int)(pFix->sharp_bf_coef[0] + offset);
    pFix->sharp_bf_coef[0] = CLIP(tmp, 0, 127);

    // SHARP_SHARP_BF_COEF (0x00044)
    // bf coeff
    // rk_sharp_V33_rfCoeff : [4], [1], [0]
    float range_filter[6];
    LOGD_ASHARP("GaussianFilter_sigma = %f ,GaussianFilter_radius %f \n",
                pSelect->sharpParamsSelectISO.GaussianFilter_sigma,
                pSelect->sharpParamsSelectISO.GaussianFilter_radius);
    if (pSelect->kernel_sigma_enable) {
        float gauss_dis_table_5x5[6] = {0.0, 1.0, 2.0, 4.0, 5.0, 8.0};
        float gauss_dis_table_3x3[6] = {0.0, 1.0, 2.0, 1000, 1000, 1000};
        double e                     = 2.71828182845905;
        float sigma                  = pSelect->sharpParamsSelectISO.GaussianFilter_sigma;
        float sum_gauss_coeff        = 0.0;
        if (pSelect->sharpParamsSelectISO.GaussianFilter_radius == 2) {
            for (int i = 0; i < 6; i++) {
                float tmp       = pow(e, -gauss_dis_table_5x5[i] / 2.0 / sigma / sigma);
                range_filter[i] = tmp;
            }
        } else {
            for (int i = 0; i < 6; i++) {
                float tmp       = pow(e, -gauss_dis_table_3x3[i] / 2.0 / sigma / sigma);
                range_filter[i] = tmp;
            }
        }

        sum_gauss_coeff = range_filter[0] + 4 * range_filter[1] + 4 * range_filter[2] +
                          4 * range_filter[3] + 8 * range_filter[4] + 4 * range_filter[5];
        for (int i = 0; i < 6; i++) {
            range_filter[i] = range_filter[i] / sum_gauss_coeff;
            LOGD_ASHARP("kernel_sigma_enable:%d range_filter[%d]:%f\n",
                        pSelect->kernel_sigma_enable, i, range_filter[i]);
        }
    } else {
        for (int i = 0; i < 6; i++) {
            range_filter[i] = pSelect->sharpParamsSelectISO.kernel_range_filter[i];
            LOGD_ASHARP("kernel_sigma_enable:%d range_filter[%d]:%f\n",
                        pSelect->kernel_sigma_enable, i, range_filter[i]);
        }
    }
    tmp = (int)ROUND_F(range_filter[0] * (1 << RK_SHARP_V33_HBFCOEFF_FIX_BITS));
    pFix->sharp_gaus_coef[0] = CLIP(tmp, 0, 127);
    tmp = (int)ROUND_F(range_filter[1] * (1 << RK_SHARP_V33_HBFCOEFF_FIX_BITS));
    pFix->sharp_gaus_coef[1] = CLIP(tmp, 0, 127);
    tmp = (int)ROUND_F(range_filter[2] * (1 << RK_SHARP_V33_HBFCOEFF_FIX_BITS));
    pFix->sharp_gaus_coef[2] = CLIP(tmp, 0, 127);
    tmp = (int)ROUND_F(range_filter[3] * (1 << RK_SHARP_V33_HBFCOEFF_FIX_BITS));
    pFix->sharp_gaus_coef[3] = CLIP(tmp, 0, 127);
    tmp = (int)ROUND_F(range_filter[4] * (1 << RK_SHARP_V33_HBFCOEFF_FIX_BITS));
    pFix->sharp_gaus_coef[4] = CLIP(tmp, 0, 127);
    tmp = (int)ROUND_F(range_filter[5] * (1 << RK_SHARP_V33_HBFCOEFF_FIX_BITS));
    pFix->sharp_gaus_coef[5] = CLIP(tmp, 0, 127);

    sum_coeff = pFix->sharp_gaus_coef[0] + 4 * pFix->sharp_gaus_coef[1] +
                4 * pFix->sharp_gaus_coef[2] + 4 * pFix->sharp_gaus_coef[3] +
                8 * pFix->sharp_gaus_coef[4] + 4 * pFix->sharp_gaus_coef[5];
    offset                   = (1 << RK_SHARP_V33_RFCOEFF_FIX_BITS) - sum_coeff;
    tmp                      = (int)(pFix->sharp_gaus_coef[0] + offset);
    pFix->sharp_gaus_coef[0] = CLIP(tmp, 0, 127);

    // gain
    tmp = pSelect->sharpParamsSelectISO.global_gain * (1 << RK_SHARP_V33_GLOBAL_GAIN_FIX_BITS);
    pFix->sharp_global_gain = CLIP(tmp, 0, 1023);
    tmp                     = pSelect->sharpParamsSelectISO.global_gain_alpha *
                              (1 << RK_SHARP_V33_GLOBAL_GAIN_ALPHA_FIX_BITS);
    pFix->sharp_global_gain_alpha = CLIP(tmp, 0, 15);
    tmp                           = pSelect->sharpParamsSelectISO.local_gainscale *
                                    (1 << RK_SHARP_V33_LOCAL_GAIN_SACLE_FIX_BITS);
    pFix->sharp_local_gainscale = CLIP(tmp, 0, 255);

    // gain adjust strength
    for (int i = 0; i < RK_SHARP_V33_SHARP_ADJ_GAIN_TABLE_LEN; i++) {
        tmp                     = ROUND_F(pSelect->sharpParamsSelectISO.gain_adj_sharp_strength[i] *
                                          (1 << RK_SHARP_V33_ADJ_GAIN_FIX_BITS));
        pFix->sharp_gain_adj[i] = CLIP(tmp, 0, 32767);
    }

    // gain dis strength
    for (int i = 0; i < RK_SHARP_V33_STRENGTH_TABLE_LEN; i++) {
        tmp                     = ROUND_F(pSelect->sharpParamsSelectISO.dis_adj_sharp_strength[i] *
                                          (1 << RK_SHARP_V33_STRENGTH_TABLE_FIX_BITS));
        pFix->sharp_strength[i] = CLIP(tmp, 0, 255);
    }

    // texture: sharp enhence strength
    tmp                        = ROUND_F(pSelect->sharpParamsSelectISO.noiseclip_strength *
                                         (1 << RK_SHARP_V33_ADJ_GAIN_FIX_BITS));
    pFix->sharp_noise_strength = CLIP(tmp, 0, 16383);
    tmp                        = ROUND_F(pSelect->sharpParamsSelectISO.enhance_bit);
    pFix->sharp_enhance_bit    = CLIP(tmp, 0, 15);
    tmp                        = ROUND_F(pSelect->sharpParamsSelectISO.noise_sigma_clip);
    pFix->sharp_noise_sigma    = CLIP(tmp, 0, 1023);

#if 1
    sharp_fix_printf_V33(pFix);
#endif

    LOGI_ASHARP("%s(%d): exit\n", __FUNCTION__, __LINE__);
    return res;
}

Asharp_result_V33_t sharp_fix_printf_V33(RK_SHARP_Fix_V33_t* pFix) {
    int i                   = 0;
    Asharp_result_V33_t res = ASHARP_V33_RET_SUCCESS;

    LOGD_ASHARP("%s:(%d) enter \n", __FUNCTION__, __LINE__);

    if (pFix == NULL) {
        LOGE_ASHARP("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ASHARP_V33_RET_NULL_POINTER;
    }

    // SHARP_SHARP_EN (0X0000)
    LOGD_ASHARP("(0x0000) sahrp_center_mode:0x%x sharp_bypass:0x%x sharp_en:0x%x \n",
                pFix->sharp_center_mode, pFix->sharp_bypass, pFix->sharp_en);

    // SHARP_SHARP_RATIO (0x0004)
    LOGD_ASHARP(
        "(0x0004) sharp_sharp_ratio:0x%x sharp_bf_ratio:0x%x sharp_gaus_ratio:0x%x "
        "sharp_pbf_ratio:0x%x \n",
        pFix->sharp_sharp_ratio, pFix->sharp_bf_ratio, pFix->sharp_gaus_ratio,
        pFix->sharp_pbf_ratio);

    // SHARP_SHARP_LUMA_DX (0x0008)
    for (int i = 0; i < 7; i++) {
        LOGD_ASHARP("(0x0008) sharp_luma_dx[%d]:0x%x \n", i, pFix->sharp_luma_dx[i]);
    }

    // SHARP_SHARP_PBF_SIGMA_INV_0 (0x000c - 0x0014)
    for (int i = 0; i < 8; i++) {
        LOGD_ASHARP("(0x000c - 0x0014) sharp_pbf_sigma_inv[%d]:0x%x \n", i,
                    pFix->sharp_pbf_sigma_inv[i]);
    }

    // SHARP_SHARP_BF_SIGMA_INV_0 (0x0018 -  0x0020)
    for (int i = 0; i < 8; i++) {
        LOGD_ASHARP("(0x0018 - 0x0020) sharp_bf_sigma_inv[%d]:0x%x \n", i,
                    pFix->sharp_bf_sigma_inv[i]);
    }

    // SHARP_SHARP_SIGMA_SHIFT (0x00024)
    LOGD_ASHARP("(0x00024) sharp_bf_sigma_shift:0x%x sharp_pbf_sigma_shift:0x%x \n",
                pFix->sharp_bf_sigma_shift, pFix->sharp_pbf_sigma_shift);

    // SHARP_SHARP_CLIP_HF_0 (0x0034 -  0x003c)
    for (int i = 0; i < 8; i++) {
        LOGD_ASHARP("(0x0034 - 0x003c) sharp_clip_hf[%d]:0x%x \n", i, pFix->sharp_clip_hf[i]);
    }

    // SHARP_SHARP_PBF_COEF (0x00040)
    for (int i = 0; i < 3; i++) {
        LOGD_ASHARP("(0x00040) sharp_pbf_coef[%d]:0x%x \n", i, pFix->sharp_pbf_coef[i]);
    }

    // SHARP_SHARP_BF_COEF (0x00044)
    for (int i = 0; i < 3; i++) {
        LOGD_ASHARP("(0x00044) sharp_bf_coef[%d]:0x%x \n", i, pFix->sharp_bf_coef[i]);
    }

    // SHARP_SHARP_GAUS_COEF (0x00048)
    for (int i = 0; i < 6; i++) {
        LOGD_ASHARP("(0x00048) sharp_gaus_coef[%d]:0x%x \n", i, pFix->sharp_gaus_coef[i]);
    }

    // SHARP_GAIN (0x0050)
    LOGD_ASHARP(
        "(0x0050) sharp_global_gain:0x%x sharp_global_gain_alpha:0x%x sharp_local_gaincale:0x%x \n",
        pFix->sharp_global_gain, pFix->sharp_global_gain_alpha, pFix->sharp_local_gainscale);

    // SHARP_GAIN_ADJUST (0x54)
    for (int i = 0; i < 14; i++) {
        LOGD_ASHARP("(0x00048) sharp_gain_adj[%d]:0x%x \n", i, pFix->sharp_gain_adj[i]);
    }

    // SHARP_CENTER (0x70)
    LOGD_ASHARP("(0x0070) sharp_center_wid:0x%x shrap_center_het:%x \n", pFix->sharp_center_wid,
                pFix->sharp_center_het);

    // SHARP_GAIN_DIS_STRENGTH (0x74)
    for (int i = 0; i < 22; i++) {
        LOGD_ASHARP("(0x00048) sharp_strength[%d]:0x%x \n", i, pFix->sharp_strength[i]);
    }

    // SHARP_TEXTURE (0x8c)
    LOGD_ASHARP("(0x0070) sharp_noise_sigma:0x%x sharp_enhance_bit:%x sharp_noise_strength:%x \n",
                pFix->sharp_noise_sigma, pFix->sharp_enhance_bit, pFix->sharp_noise_strength);

    return res;
}

Asharp_result_V33_t sharp_get_setting_by_name_json_V33(CalibDbV2_SharpV33_t* pCalibdbV2, char* name,
        int* tuning_idx) {
    int i                   = 0;
    Asharp_result_V33_t res = ASHARP_V33_RET_SUCCESS;

    LOGI_ASHARP("%s:%d snr_name:%s  snr_idx:%d i:%d \n", __FUNCTION__, __LINE__, name, *tuning_idx,
                i);
    return res;
}

Asharp_result_V33_t sharp_init_params_json_V33(RK_SHARP_Params_V33_t* pSharpParams,
        CalibDbV2_SharpV33_t* pCalibdbV2, int tuning_idx) {
    Asharp_result_V33_t res = ASHARP_V33_RET_SUCCESS;
    int i                   = 0;
    int j                   = 0;
    short isoCurveSectValue;
    short isoCurveSectValue1;
    float ave1, ave2, ave3, ave4;
    int bit_calib = 12;
    int bit_proc;
    int bit_shift;
    CalibDbV2_SharpV33_TuningPara_Setting_ISO_t* pTuningISO;

    LOGI_ASHARP("%s(%d): enter\n", __FUNCTION__, __LINE__);

    if (pSharpParams == NULL || pCalibdbV2 == NULL) {
        LOGE_ASHARP("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return ASHARP_V33_RET_NULL_POINTER;
    }

    pSharpParams->enable              = pCalibdbV2->TuningPara.enable;
    pSharpParams->kernel_sigma_enable = pCalibdbV2->TuningPara.kernel_sigma_enable;
    pSharpParams->center_mode         = pCalibdbV2->TuningPara.Center_Mode;

    for (i = 0; i < pCalibdbV2->TuningPara.Setting[tuning_idx].Tuning_ISO_len &&
            i < RK_SHARP_V33_MAX_ISO_NUM;
            i++) {
        pTuningISO           = &pCalibdbV2->TuningPara.Setting[tuning_idx].Tuning_ISO[i];
        pSharpParams->iso[i] = pTuningISO->iso;

        for (j = 0; j < RK_SHARP_V33_LUMA_POINT_NUM; j++) {
            pSharpParams->sharpParamsISO[i].luma_point[j] = pTuningISO->luma_para.luma_point[j];
            pSharpParams->sharpParamsISO[i].luma_sigma[j] = pTuningISO->luma_para.luma_sigma[j];
            pSharpParams->sharpParamsISO[i].lum_clip_h[j] = pTuningISO->luma_para.hf_clip[j];
        }

        pSharpParams->sharpParamsISO[i].pbf_gain        = pTuningISO->pbf_gain;
        pSharpParams->sharpParamsISO[i].pbf_add         = pTuningISO->pbf_add;
        pSharpParams->sharpParamsISO[i].pbf_ratio       = pTuningISO->pbf_ratio;
        pSharpParams->sharpParamsISO[i].gaus_ratio      = pTuningISO->gaus_ratio;
        pSharpParams->sharpParamsISO[i].sharp_ratio     = pTuningISO->sharp_ratio;
        pSharpParams->sharpParamsISO[i].bf_gain         = pTuningISO->bf_gain;
        pSharpParams->sharpParamsISO[i].bf_add          = pTuningISO->bf_add;
        pSharpParams->sharpParamsISO[i].bf_ratio        = pTuningISO->bf_ratio;
        pSharpParams->sharpParamsISO[i].global_clip_pos = pTuningISO->global_hf_clip_pos;

        for (j = 0; j < 3; j++) {
            pSharpParams->sharpParamsISO[i].kernel_pre_bila_filter[j] =
                pTuningISO->kernel_para.prefilter_coeff[j];
            pSharpParams->sharpParamsISO[i].kernel_bila_filter[j] =
                pTuningISO->kernel_para.hfBilateralFilter_coeff[j];
            LOGD_ASHARP("kernel_pbf: index[%d][%d] = %f\n", i, j,
                        pSharpParams->sharpParamsISO[i].kernel_pre_bila_filter[j]);
            LOGD_ASHARP("kernel_bf: index[%d][%d] = %f\n", i, j,
                        pSharpParams->sharpParamsISO[i].kernel_bila_filter[j]);
        }

        for (j = 0; j < 6; j++) {
            pSharpParams->sharpParamsISO[i].kernel_range_filter[j] =
                pTuningISO->kernel_para.GaussianFilter_coeff[j];
            LOGD_ASHARP("kernel: index[%d][%d] = %f\n", i, j,
                        pSharpParams->sharpParamsISO[i].kernel_range_filter[j]);
        }

        pSharpParams->sharpParamsISO[i].global_gain       = pTuningISO->global_gain;
        pSharpParams->sharpParamsISO[i].global_gain_alpha = pTuningISO->global_gain_alpha;
        pSharpParams->sharpParamsISO[i].local_gainscale   = pTuningISO->local_gainscale;

        for (int j = 0; j < 14; j++) {
            pSharpParams->sharpParamsISO[i].gain_adj_sharp_strength[j] =
                pTuningISO->gain_adj_sharp_strength[j];
        }

        pSharpParams->sharpParamsISO[i].exgain_bypass = pTuningISO->exgain_bypass;

        for (int j = 0; j < 22; j++) {
            pSharpParams->sharpParamsISO[i].dis_adj_sharp_strength[j] =
                pTuningISO->dis_adj_sharp_strength[j];
        }

        pSharpParams->sharpParamsISO[i].noiseclip_strength = pTuningISO->noiseclip_strength;
        pSharpParams->sharpParamsISO[i].enhance_bit        = pTuningISO->enhance_bit;
        pSharpParams->sharpParamsISO[i].noiseclip_mode     = pTuningISO->noiseclip_mode;
        pSharpParams->sharpParamsISO[i].noise_sigma_clip   = pTuningISO->noise_sigma_clip;

        pSharpParams->sharpParamsISO[i].prefilter_sigma = pTuningISO->kernel_sigma.prefilter_sigma;
        pSharpParams->sharpParamsISO[i].hfBilateralFilter_sigma =
            pTuningISO->kernel_sigma.hfBilateralFilter_sigma;
        pSharpParams->sharpParamsISO[i].GaussianFilter_sigma =
            pTuningISO->kernel_sigma.GaussianFilter_sigma;
        pSharpParams->sharpParamsISO[i].GaussianFilter_radius =
            pTuningISO->kernel_sigma.GaussianFilter_radius;
    }

    LOGI_ASHARP("%s(%d): exit\n", __FUNCTION__, __LINE__);
    return res;
}

Asharp_result_V33_t sharp_config_setting_param_json_V33(RK_SHARP_Params_V33_t* pParams,
        CalibDbV2_SharpV33_t* pCalibdbV2,
        char* param_mode, char* snr_name) {
    Asharp_result_V33_t res = ASHARP_V33_RET_SUCCESS;
    int tuning_idx          = 0;

    LOGI_ASHARP("%s(%d): enter\n", __FUNCTION__, __LINE__);

    if (pParams == NULL || pCalibdbV2 == NULL || param_mode == NULL || snr_name == NULL) {
        LOGE_ASHARP("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        pParams->enable = false;
        return ASHARP_V33_RET_NULL_POINTER;
    }

    res             = sharp_init_params_json_V33(pParams, pCalibdbV2, tuning_idx);
    pParams->enable = pCalibdbV2->TuningPara.enable;

    LOGI_ASHARP("%s(%d): exit\n", __FUNCTION__, __LINE__);

    return res;
}

RKAIQ_END_DECLARE
