/*
 * Copyright (c) 2022 Rockchip Eletronics Co., Ltd.
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
#include "RkAiqResourceTranslatorV32.h"

#include "common/rkisp32-config.h"
#include "isp20/Isp20Evts.h"
#include "isp20/Isp20StatsBuffer.h"

//#define AE_STATS_DEBUG

namespace RkCam {

RkAiqResourceTranslatorV32::RkAiqResourceTranslatorV32() {}

XCamReturn RkAiqResourceTranslatorV32::translateAecStats(const SmartPtr<VideoBuffer>& from,
        SmartPtr<RkAiqAecStatsProxy>& to) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    const SmartPtr<Isp20StatsBuffer> buf = from.dynamic_cast_ptr<Isp20StatsBuffer>();
    struct rkisp32_isp_stat_buffer* stats;
    SmartPtr<RkAiqAecStats> statsInt = to->data();

    stats = (struct rkisp32_isp_stat_buffer*)(buf->get_v4l2_userptr());
    if (stats == NULL) {
        LOGE("fail to get stats ,ignore\n");
        return XCAM_RETURN_BYPASS;
    }
    LOGI_ANALYZER("camId: %d, stats: frame_id: %d,  meas_type; 0x%x", mCamPhyId, stats->frame_id,
                  stats->meas_type);

    SmartPtr<RkAiqIrisParamsProxy> irisParams = buf->get_iris_params();
    SmartPtr<RkAiqExpParamsProxy> expParams   = nullptr;
    rkisp_effect_params_v20 ispParams;
    memset(&ispParams, 0, sizeof(ispParams));
    if (buf->getEffectiveExpParams(stats->frame_id, expParams) < 0) LOGE("fail to get expParams");
    if (buf->getEffectiveIspParams(stats->frame_id, ispParams) < 0) {
        LOGE("fail to get ispParams ,ignore\n");
        return XCAM_RETURN_BYPASS;
    }

    // ae stats v3.2
    statsInt->frame_id = stats->frame_id;

    /*rawae stats*/
    struct isp32_isp_meas_cfg* isp_params = &ispParams.isp_params_v32.meas;
    uint8_t AeSwapMode, AeSelMode, AfUseAeBig;
    AeSwapMode             = isp_params->rawae0.rawae_sel;
    AeSelMode              = isp_params->rawae3.rawae_sel;
    AfUseAeBig             = isp_params->rawaf.ae_mode;
    unsigned int meas_type = 0;

    // ae_stats = (ae_ori_stats_u12/10 - ob_offset_u9 - bls1_val_u12) * awb1_gain_u16 * range_ratio
    struct isp32_bls_cfg* bls_cfg = &ispParams.isp_params_v32.others.bls_cfg;
    struct isp32_awb_gain_cfg* awb_gain_cfg = &ispParams.isp_params_v32.others.awb_gain_cfg;
    struct isp2x_bls_fixed_val bls1_val;  // bls1_val = blc1_ori_val * awb * range_ratio
    u16 isp_ob_offset_rb, isp_ob_offset_g, isp_ob_predgain;
    float awb1_gain_r, awb1_gain_gr, awb1_gain_gb, awb1_gain_b;
    u16 MAX_10BITS     = (1 << 10) - 1;
    u16 MAX_12BITS     = (1 << 12) - 1;
    u32 MAX_29BITS     = (1 << 29) - 1;
    u32 MAX_32BITS     = 0xffffffff;
    u32 pixel_num      = 0;
    u8  rawhist_mode   = 0;
    u8  index0, index1, index2 = 0;

    isp_ob_offset_rb = MAX(bls_cfg->isp_ob_offset >> 2, 0);
    isp_ob_offset_g =  MAX(bls_cfg->isp_ob_offset, 0);
    isp_ob_predgain =  MAX(bls_cfg->isp_ob_predgain >> 8, 1);

    if (bls_cfg->bls1_en) {
        bls1_val.r  = (bls_cfg->bls1_val.r / isp_ob_predgain) >> 2;
        bls1_val.gr = bls_cfg->bls1_val.gr / isp_ob_predgain;
        bls1_val.gb = bls_cfg->bls1_val.gb / isp_ob_predgain;
        bls1_val.b  = (bls_cfg->bls1_val.b / isp_ob_predgain) >> 2;
    } else {
        bls1_val.r  = 0;
        bls1_val.gr = 0;
        bls1_val.gb = 0;
        bls1_val.b  = 0;
    }
    //awb1_gain have adapted to the range of bls1_lvl
    awb1_gain_r  = MAX((float)awb_gain_cfg->awb1_gain_r / 256, 1);
    awb1_gain_gr = MAX((float)awb_gain_cfg->awb1_gain_gr / 256, 1);
    awb1_gain_gb = MAX((float)awb_gain_cfg->awb1_gain_gb / 256, 1);
    awb1_gain_b  = MAX((float)awb_gain_cfg->awb1_gain_b / 256, 1);
#ifdef AE_STATS_DEBUG
    LOGE("bls1[%d-%d-%d-%d]", bls1_val.r, bls1_val.gr, bls1_val.gb, bls1_val.b);
    LOGE("isp_ob_offset_rb, isp_ob_offset_g, isp_ob_predgain [%d-%d-%d]",
            isp_ob_offset_rb, isp_ob_offset_g, isp_ob_predgain);
    LOGE("awb1_gain[%f-%f-%f-%f]", awb1_gain_r, awb1_gain_gr, awb1_gain_gb, awb1_gain_b);
#endif
    switch (AeSwapMode) {
    case AEC_RAWSWAP_MODE_S_LITE:
        meas_type = ((stats->meas_type >> 7) & (0x01)) & ((stats->meas_type >> 11) & (0x01));
        index0       = 0;
        index1       = 1;
        index2       = 2;
        rawhist_mode = isp_params->rawhist0.mode;
        break;
    case AEC_RAWSWAP_MODE_M_LITE:
        meas_type = ((stats->meas_type >> 8) & (0x01)) & ((stats->meas_type >> 12) & (0x01));
        index0       = 1;
        index1       = 0;
        index2       = 2;
        rawhist_mode = isp_params->rawhist1.mode;
        break;
    /*
    case AEC_RAWSWAP_MODE_L_LITE:
        meas_type = ((stats->meas_type >> 9) & (0x01)) & ((stats->meas_type >> 13) & (0x01));
        index0       = 2;
        index1       = 1;
        index2       = 0;
        rawhist_mode = isp_params->rawhist2.mode;
        break;
    */
    default:
        LOGE("wrong AeSwapMode=%d\n", AeSwapMode);
        return XCAM_RETURN_ERROR_PARAM;
        break;
    }

    statsInt->aec_stats_valid = (meas_type & 0x01) ? true : false;

    for (int i = 0; i < ISP3X_RAWAEBIG_MEAN_NUM; i++) {
        if (i < ISP3X_RAWAELITE_MEAN_NUM) {
            statsInt->aec_stats.ae_data.chn[index0].rawae_lite.channelr_xy[i] = (u16)MIN(
                (stats->params.rawae0.data[i].channelr_xy - isp_ob_offset_rb - bls1_val.r) * awb1_gain_r, MAX_10BITS);
            statsInt->aec_stats.ae_data.chn[index0].rawae_lite.channelg_xy[i] = (u16)MIN(
                (stats->params.rawae0.data[i].channelg_xy - isp_ob_offset_g - bls1_val.gr) * awb1_gain_gr, MAX_12BITS);
            statsInt->aec_stats.ae_data.chn[index0].rawae_lite.channelb_xy[i] = (u16)MIN(
                (stats->params.rawae0.data[i].channelb_xy - isp_ob_offset_rb - bls1_val.b) * awb1_gain_b, MAX_10BITS);
        }
        statsInt->aec_stats.ae_data.chn[index1].rawae_big.channelr_xy[i] = (u16)MIN(
            (stats->params.rawae1_0.data[i].channelr_xy - isp_ob_offset_rb - bls1_val.r) * awb1_gain_r, MAX_10BITS);
        statsInt->aec_stats.ae_data.chn[index1].rawae_big.channelg_xy[i] = (u16)MIN(
            (stats->params.rawae1_0.data[i].channelg_xy - isp_ob_offset_g - bls1_val.gr) * awb1_gain_gr, MAX_12BITS);
        statsInt->aec_stats.ae_data.chn[index1].rawae_big.channelb_xy[i] = (u16)MIN(
            (stats->params.rawae1_0.data[i].channelb_xy - isp_ob_offset_rb - bls1_val.b) * awb1_gain_b, MAX_10BITS);
        statsInt->aec_stats.ae_data.chn[index2].rawae_big.channelr_xy[i] = (u16)MIN(
            (stats->params.rawae2_0.data[i].channelr_xy - isp_ob_offset_rb - bls1_val.r) * awb1_gain_r, MAX_10BITS);
        statsInt->aec_stats.ae_data.chn[index2].rawae_big.channelg_xy[i] = (u16)MIN(
            (stats->params.rawae2_0.data[i].channelg_xy - isp_ob_offset_g - bls1_val.gr) * awb1_gain_gr, MAX_12BITS);
        statsInt->aec_stats.ae_data.chn[index2].rawae_big.channelb_xy[i] = (u16)MIN(
            (stats->params.rawae2_0.data[i].channelb_xy - isp_ob_offset_rb - bls1_val.b) * awb1_gain_b, MAX_10BITS);

        if (i < ISP3X_RAWAEBIG_SUBWIN_NUM) {
            pixel_num = isp_params->rawae1.subwin[i].h_size * isp_params->rawae1.subwin[i].v_size;
            statsInt->aec_stats.ae_data.chn[index1].rawae_big.wndx_sumr[i] = (u32)MIN(
                (stats->params.rawae1_1.sumr[i] - (pixel_num >> 2) * (isp_ob_offset_rb + bls1_val.r)) * awb1_gain_r, MAX_29BITS);
            statsInt->aec_stats.ae_data.chn[index1].rawae_big.wndx_sumg[i] = (u32)MIN(
                (stats->params.rawae1_1.sumg[i] - (pixel_num >> 1) * (isp_ob_offset_g + bls1_val.gr)) * awb1_gain_gr, MAX_32BITS);
            statsInt->aec_stats.ae_data.chn[index1].rawae_big.wndx_sumb[i] = (u32)MIN(
                (stats->params.rawae1_1.sumb[i] - (pixel_num >> 2) * (isp_ob_offset_rb + bls1_val.b)) * awb1_gain_b, MAX_29BITS);

            pixel_num = isp_params->rawae2.subwin[i].h_size * isp_params->rawae2.subwin[i].v_size;
            statsInt->aec_stats.ae_data.chn[index2].rawae_big.wndx_sumr[i] = (u32)MIN(
                (stats->params.rawae2_1.sumr[i] - (pixel_num >> 2) * (isp_ob_offset_rb + bls1_val.r)) * awb1_gain_r, MAX_29BITS);
            statsInt->aec_stats.ae_data.chn[index2].rawae_big.wndx_sumg[i] = (u32)MIN(
                (stats->params.rawae2_1.sumg[i] - (pixel_num >> 1) * (isp_ob_offset_g + bls1_val.gr)) * awb1_gain_gr, MAX_32BITS);
            statsInt->aec_stats.ae_data.chn[index2].rawae_big.wndx_sumb[i] = (u32)MIN(
                (stats->params.rawae2_1.sumb[i] - (pixel_num >> 2) * (isp_ob_offset_rb + bls1_val.b)) * awb1_gain_b, MAX_29BITS);
        }
    }

    if (bls_cfg->bls1_en) {
        memset(statsInt->aec_stats.ae_data.chn[index0].rawhist_lite.bins, 0,
               ISP3X_HIST_BIN_N_MAX * sizeof(u32));
        memset(statsInt->aec_stats.ae_data.chn[index1].rawhist_big.bins, 0,
               ISP3X_HIST_BIN_N_MAX * sizeof(u32));
        memset(statsInt->aec_stats.ae_data.chn[index2].rawhist_big.bins, 0,
               ISP3X_HIST_BIN_N_MAX * sizeof(u32));
        for (int i = 0; i < ISP3X_HIST_BIN_N_MAX; i++) {
            int tmp;
            switch (rawhist_mode) {
                case 2:
                    tmp = (i - (isp_ob_offset_rb >> 2) - (bls1_val.r >> 2) > 0)
                          ? (i - (isp_ob_offset_rb >> 2) - (bls1_val.r >> 2)) * awb1_gain_r + 0.5
                          : 0;
                    break;
                case 3:
                    tmp = (i - (isp_ob_offset_g >> 4) - (bls1_val.gr >> 4) > 0)
                          ? (i - (isp_ob_offset_g >> 4) - (bls1_val.gr >> 4)) * awb1_gain_gr + 0.5
                          : 0;
                    break;
                case 4:
                    tmp = (i - (isp_ob_offset_rb >> 2) - (bls1_val.b >> 2) > 0)
                          ? (i - (isp_ob_offset_rb >> 2) - (bls1_val.b >> 2)) * awb1_gain_b + 0.5
                          : 0;
                    break;
                case 5:
                default:
                    //TODO: need to adapt for isp3.2 awb1_gain
                    s16 hist_bls1 = (s16)((bls1_val.gr >> 4) * 0.587 + (bls1_val.r >> 2) * 0.299 +
                                            (bls1_val.b >> 2) * 0.144 + 0.5);
                    s16 hist_offset = (s16)((isp_ob_offset_g >> 4) * 0.587 + (isp_ob_offset_rb >> 2) * 0.299 +
                                            (isp_ob_offset_rb >> 2) * 0.144 + 0.5);
                    float awb1_gain = 1 / (0.299 / awb1_gain_r + 0.587 / awb1_gain_gr + 0.144 / awb1_gain_b);
                    tmp = (i - hist_bls1 - hist_offset > 0) ? (i - hist_bls1 - hist_offset) * awb1_gain + 0.5 : 0;
                    break;
            }
            if (tmp > ISP3X_HIST_BIN_N_MAX - 1) tmp = ISP3X_HIST_BIN_N_MAX - 1;
            statsInt->aec_stats.ae_data.chn[index0].rawhist_lite.bins[tmp] +=
                stats->params.rawhist0.hist_bin[i];
            statsInt->aec_stats.ae_data.chn[index1].rawhist_big.bins[tmp] +=
                stats->params.rawhist1.hist_bin[i];
            statsInt->aec_stats.ae_data.chn[index2].rawhist_big.bins[tmp] +=
                stats->params.rawhist2.hist_bin[i];
        }
    } else {
        memcpy(statsInt->aec_stats.ae_data.chn[index0].rawhist_lite.bins,
               stats->params.rawhist0.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
        memcpy(statsInt->aec_stats.ae_data.chn[index1].rawhist_big.bins,
               stats->params.rawhist1.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
        memcpy(statsInt->aec_stats.ae_data.chn[index2].rawhist_big.bins,
               stats->params.rawhist2.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
    }

    statsInt->af_prior = (AfUseAeBig == 0) ? false : true;

    if (!AfUseAeBig) {
        switch (AeSelMode) {
        case AEC_RAWSEL_MODE_CHN_0:
        case AEC_RAWSEL_MODE_CHN_1:
        case AEC_RAWSEL_MODE_CHN_2:
            for (int i = 0; i < ISP3X_RAWAEBIG_MEAN_NUM; i++) {
                statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.channelr_xy[i] = (u16)MIN(
                    (stats->params.rawae3_0.data[i].channelr_xy - isp_ob_offset_rb - bls1_val.r) * awb1_gain_r, MAX_10BITS);
                statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.channelg_xy[i] = (u16)MIN(
                    (stats->params.rawae3_0.data[i].channelg_xy - isp_ob_offset_g - bls1_val.gr) * awb1_gain_gr, MAX_12BITS);
                statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.channelb_xy[i] = (u16)MIN(
                    (stats->params.rawae3_0.data[i].channelb_xy - isp_ob_offset_rb - bls1_val.b) * awb1_gain_b, MAX_10BITS);

                if (i < ISP3X_RAWAEBIG_SUBWIN_NUM) {
                    pixel_num = isp_params->rawae3.subwin[i].h_size * isp_params->rawae3.subwin[i].v_size;
                    statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.wndx_sumr[i] = (u32)MIN(
                        (stats->params.rawae3_1.sumr[i] - (pixel_num >> 2) * (isp_ob_offset_rb + bls1_val.r)) * awb1_gain_r, MAX_29BITS);
                    statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.wndx_sumg[i] = (u32)MIN(
                        (stats->params.rawae3_1.sumg[i] - (pixel_num >> 1) * (isp_ob_offset_g + bls1_val.gr)) * awb1_gain_gr, MAX_32BITS);
                    statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.wndx_sumb[i] = (u32)MIN(
                        (stats->params.rawae3_1.sumb[i] - (pixel_num >> 2) * (isp_ob_offset_rb + bls1_val.b)) * awb1_gain_b, MAX_29BITS);
                }
            }

            if (bls_cfg->bls1_en) {
                memset(statsInt->aec_stats.ae_data.chn[AeSelMode].rawhist_big.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                for (int i = 0; i < ISP3X_HIST_BIN_N_MAX; i++) {
                    int tmp;
                    switch (isp_params->rawhist3.mode) {
                    case 2:
                        tmp = (i - (isp_ob_offset_rb >> 2) - (bls1_val.r >> 2) > 0)
                              ? (i - (isp_ob_offset_rb >> 2) - (bls1_val.r >> 2)) * awb1_gain_r + 0.5
                              : 0;
                        break;
                    case 3:
                        tmp = (i - (isp_ob_offset_g >> 4) - (bls1_val.gr >> 4) > 0)
                              ? (i - (isp_ob_offset_g >> 4) - (bls1_val.gr >> 4)) * awb1_gain_gr + 0.5
                              : 0;
                        break;
                    case 4:
                        tmp = (i - (isp_ob_offset_rb >> 2) - (bls1_val.b >> 2) > 0)
                              ? (i - (isp_ob_offset_rb >> 2) - (bls1_val.b >> 2)) * awb1_gain_b + 0.5
                              : 0;
                        break;
                    case 5:
                    default:
                        //TODO: need to adapt for isp3.2 awb1_gain
                        s16 hist_bls1 = (s16)((bls1_val.gr >> 4) * 0.587 + (bls1_val.r >> 2) * 0.299 +
                                                (bls1_val.b >> 2) * 0.144 + 0.5);
                        s16 hist_offset = (s16)((isp_ob_offset_g >> 4) * 0.587 + (isp_ob_offset_rb >> 2) * 0.299 +
                                                (isp_ob_offset_rb >> 2) * 0.144 + 0.5);
                        float awb1_gain = 1 / (0.299 / awb1_gain_r + 0.587 / awb1_gain_gr + 0.144 / awb1_gain_b);
                        tmp = (i - hist_bls1 - hist_offset > 0) ? (i - hist_bls1 - hist_offset) * awb1_gain + 0.5 : 0;
                        break;
                    }
                    if (tmp > ISP3X_HIST_BIN_N_MAX - 1) tmp = ISP3X_HIST_BIN_N_MAX - 1;
                    statsInt->aec_stats.ae_data.chn[AeSelMode].rawhist_big.bins[tmp] +=
                        stats->params.rawhist3.hist_bin[i];
                }
            } else {
                memcpy(statsInt->aec_stats.ae_data.chn[AeSelMode].rawhist_big.bins,
                       stats->params.rawhist3.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
            }
            break;
        case AEC_RAWSEL_MODE_TMO:
            for (int i = 0; i < ISP3X_RAWAEBIG_MEAN_NUM; i++) {
                statsInt->aec_stats.ae_data.extra.rawae_big.channelr_xy[i] =
                    stats->params.rawae3_0.data[i].channelr_xy;
                statsInt->aec_stats.ae_data.extra.rawae_big.channelg_xy[i] =
                    stats->params.rawae3_0.data[i].channelg_xy;
                statsInt->aec_stats.ae_data.extra.rawae_big.channelb_xy[i] =
                    stats->params.rawae3_0.data[i].channelb_xy;

                if (i < ISP3X_RAWAEBIG_SUBWIN_NUM) {
                    statsInt->aec_stats.ae_data.extra.rawae_big.wndx_sumr[i] =
                        stats->params.rawae3_1.sumr[i];
                    statsInt->aec_stats.ae_data.extra.rawae_big.wndx_sumg[i] =
                        stats->params.rawae3_1.sumg[i];
                    statsInt->aec_stats.ae_data.extra.rawae_big.wndx_sumb[i] =
                        stats->params.rawae3_1.sumb[i];
                }
            }
            memcpy(statsInt->aec_stats.ae_data.extra.rawhist_big.bins,
                   stats->params.rawhist3.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
            break;

        default:
            LOGE("wrong AeSelMode=%d\n", AeSelMode);
            return XCAM_RETURN_ERROR_PARAM;
        }
    }

#ifdef AE_STATS_DEBUG
    if (AeSwapMode != 0) {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                printf("chn0[%d,%d]:r 0x%x, g 0x%x, b 0x%x\n", i, j,
                       statsInt->aec_stats.ae_data.chn[0].rawae_big.channelr_xy[i * 15 + j],
                       statsInt->aec_stats.ae_data.chn[0].rawae_big.channelg_xy[i * 15 + j],
                       statsInt->aec_stats.ae_data.chn[0].rawae_big.channelb_xy[i * 15 + j]);
            }
        }
        printf("====================sub-win-result======================\n");

        for (int i = 0; i < 4; i++)
            printf("chn0_subwin[%d]:sumr 0x%08llx, sumg 0x%08llx, sumb 0x%08llx\n", i,
                   statsInt->aec_stats.ae_data.chn[0].rawae_big.wndx_sumr[i],
                   statsInt->aec_stats.ae_data.chn[0].rawae_big.wndx_sumg[i],
                   statsInt->aec_stats.ae_data.chn[0].rawae_big.wndx_sumb[i]);

        printf("====================hist_result========================\n");

        for (int i = 0; i < 256; i++)
            printf("bin[%d]= 0x%08x\n", i, statsInt->aec_stats.ae_data.chn[0].rawhist_big.bins[i]);

    } else {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                printf("chn0[%d,%d]:r 0x%x, g 0x%x, b 0x%x\n", i, j,
                       statsInt->aec_stats.ae_data.chn[0].rawae_lite.channelr_xy[i * 5 + j],
                       statsInt->aec_stats.ae_data.chn[0].rawae_lite.channelg_xy[i * 5 + j],
                       statsInt->aec_stats.ae_data.chn[0].rawae_lite.channelb_xy[i * 5 + j]);
            }
        }
        printf("====================hist_result========================\n");
        for (int i = 0; i < 256; i++)
            printf("bin[%d]= 0x%08x\n", i, statsInt->aec_stats.ae_data.chn[0].rawhist_lite.bins[i]);
    }

#endif

    /*
     *         unsigned long chn0_mean = 0, chn1_mean = 0;
     *         for(int i = 0; i < ISP3X_RAWAEBIG_MEAN_NUM; i++) {
     *             chn0_mean += stats->params.rawae1.data[i].channelg_xy;
     *             chn1_mean += stats->params.rawae3.data[i].channelg_xy;
     *         }
     *
     *
     *         printf("frame[%d]: chn[0-1]_g_mean_xy: %ld-%ld\n",
     *                 stats->frame_id, chn0_mean/ISP3X_RAWAEBIG_MEAN_NUM,
     *                 chn1_mean/ISP3X_RAWAEBIG_MEAN_NUM);
     */

    // expsoure params
    if (expParams.ptr()) {
        statsInt->aec_stats.ae_exp = expParams->data()->aecExpInfo;
        /*printf("frame[%d],gain=%d,time=%d\n", stats->frame_id,
               expParams->data()->aecExpInfo.LinearExp.exp_sensor_params.analog_gain_code_global,
               expParams->data()->aecExpInfo.LinearExp.exp_sensor_params.coarse_integration_time);*/

        /*
         * printf("%s: L: [0x%x-0x%x], M: [0x%x-0x%x], S: [0x%x-0x%x]\n",
         *        __func__,
         *        expParams->data()->aecExpInfo.HdrExp[2].exp_sensor_params.coarse_integration_time,
         *        expParams->data()->aecExpInfo.HdrExp[2].exp_sensor_params.analog_gain_code_global,
         *        expParams->data()->aecExpInfo.HdrExp[1].exp_sensor_params.coarse_integration_time,
         *        expParams->data()->aecExpInfo.HdrExp[1].exp_sensor_params.analog_gain_code_global,
         *        expParams->data()->aecExpInfo.HdrExp[0].exp_sensor_params.coarse_integration_time,
         *        expParams->data()->aecExpInfo.HdrExp[0].exp_sensor_params.analog_gain_code_global);
         */
    }

    // iris params
    if (irisParams.ptr()) {
        float sof_time   = (float)irisParams->data()->sofTime / 1000000000.0f;
        float start_time = (float)irisParams->data()->PIris.StartTim.tv_sec +
                           (float)irisParams->data()->PIris.StartTim.tv_usec / 1000000.0f;
        float end_time = (float)irisParams->data()->PIris.EndTim.tv_sec +
                         (float)irisParams->data()->PIris.EndTim.tv_usec / 1000000.0f;
        float frm_intval = 1 / (statsInt->aec_stats.ae_exp.pixel_clock_freq_mhz * 1000000.0f /
                                (float)statsInt->aec_stats.ae_exp.line_length_pixels /
                                (float)statsInt->aec_stats.ae_exp.frame_length_lines);

        /*printf("%s: step=%d,last-step=%d,start-tim=%f,end-tim=%f,sof_tim=%f\n",
            __func__,
            statsInt->aec_stats.ae_exp.Iris.PIris.step,
            irisParams->data()->PIris.laststep,start_time,end_time,sof_time);
        */

        if (sof_time < end_time + frm_intval)
            statsInt->aec_stats.ae_exp.Iris.PIris.step = irisParams->data()->PIris.laststep;
        else
            statsInt->aec_stats.ae_exp.Iris.PIris.step = irisParams->data()->PIris.step;
    }

    to->set_sequence(stats->frame_id);

    return ret;
}

XCamReturn RkAiqResourceTranslatorV32::translateAwbStats(const SmartPtr<VideoBuffer>& from,
        SmartPtr<RkAiqAwbStatsProxy>& to) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    const SmartPtr<Isp20StatsBuffer> buf =
        from.dynamic_cast_ptr<Isp20StatsBuffer>();
    struct rkisp32_isp_stat_buffer *stats;
    SmartPtr<RkAiqAwbStats> statsInt = to->data();


    stats = (struct rkisp32_isp_stat_buffer*)(buf->get_v4l2_userptr());
    if(stats == NULL) {
        LOGE("fail to get stats ,ignore\n");
        return XCAM_RETURN_BYPASS;
    }
    LOGI_ANALYZER("awb stats: camId:%d, frame_id: %d,  meas_type; 0x%x",
                  mCamPhyId, stats->frame_id, stats->meas_type);

    statsInt->awb_stats_valid = stats->meas_type >> 5 & 1;
    if (!statsInt->awb_stats_valid) {
        LOGE_ANALYZER("AWB stats invalid, ignore");
        return XCAM_RETURN_BYPASS;
    }

    rkisp_effect_params_v20 ispParams;
    memset(&ispParams, 0, sizeof(ispParams));
    if (buf->getEffectiveIspParams(stats->frame_id, ispParams) < 0) {
        LOGE("fail to get ispParams ,ignore\n");
        return XCAM_RETURN_BYPASS;
    }
    statsInt->awb_stats_v32.awb_cfg_effect_v32.blkMeasureMode = ispParams.awb_cfg_v32.blkMeasureMode;
    statsInt->awb_stats_v32.awb_cfg_effect_v32.lightNum = ispParams.awb_cfg_v32.lightNum;
    statsInt->awb_stats_v32.awb_cfg_effect_v32.groupIllIndxCurrent = ispParams.awb_cfg_v32.groupIllIndxCurrent;
    memcpy(statsInt->awb_stats_v32.awb_cfg_effect_v32.IllIndxSetCurrent, ispParams.awb_cfg_v32.IllIndxSetCurrent,
        sizeof(statsInt->awb_stats_v32.awb_cfg_effect_v32.IllIndxSetCurrent));
    memcpy(statsInt->awb_stats_v32.awb_cfg_effect_v32.timeSign, ispParams.awb_cfg_v32.timeSign,
        sizeof(statsInt->awb_stats_v32.awb_cfg_effect_v32.timeSign));
    statsInt->awb_cfg_effect_valid = true;
    rk_aiq_isp_blc_t *bls_cfg = &ispParams.blc_cfg.v0;
    statsInt->blc_cfg_effect = ispParams.blc_cfg.v0;
    statsInt->frame_id = stats->frame_id;
    for(int i = 0; i < statsInt->awb_stats_v32.awb_cfg_effect_v32.lightNum; i++) {
        statsInt->awb_stats_v32.light[i].xYType[RK_AIQ_AWB_XY_TYPE_NORMAL_V201].RgainValue =
            stats->params.rawawb.sum[i].rgain_nor;
        statsInt->awb_stats_v32.light[i].xYType[RK_AIQ_AWB_XY_TYPE_NORMAL_V201].BgainValue =
            stats->params.rawawb.sum[i].bgain_nor;
        statsInt->awb_stats_v32.light[i].xYType[RK_AIQ_AWB_XY_TYPE_NORMAL_V201].WpNo =
            stats->params.rawawb.sum[i].wp_num_nor;
        statsInt->awb_stats_v32.light[i].xYType[RK_AIQ_AWB_XY_TYPE_BIG_V201].RgainValue =
            stats->params.rawawb.sum[i].rgain_big;
        statsInt->awb_stats_v32.light[i].xYType[RK_AIQ_AWB_XY_TYPE_BIG_V201].BgainValue =
            stats->params.rawawb.sum[i].bgain_big;
        statsInt->awb_stats_v32.light[i].xYType[RK_AIQ_AWB_XY_TYPE_BIG_V201].WpNo =
            stats->params.rawawb.sum[i].wp_num_big;
    }

    for(int i = 0; i < RK_AIQ_AWB_GRID_NUM_TOTAL; i++) {
        statsInt->awb_stats_v32.blockResult[i].Rvalue = stats->params.rawawb.ramdata[i].r;
        statsInt->awb_stats_v32.blockResult[i].Gvalue = stats->params.rawawb.ramdata[i].g;
        statsInt->awb_stats_v32.blockResult[i].Bvalue = stats->params.rawawb.ramdata[i].b;
        statsInt->awb_stats_v32.blockResult[i].WpNo = stats->params.rawawb.ramdata[i].wp;
    }

    for(int i = 0; i < RK_AIQ_AWB_WP_HIST_BIN_NUM; i++) {
        statsInt->awb_stats_v32.WpNoHist[i] = stats->params.rawawb.yhist_bin[i];
        // move the shift code here to make WpNoHist merged by several cameras easily
        if( stats->params.rawawb.yhist_bin[i]  & 0x8000 ) {
            statsInt->awb_stats_v32.WpNoHist[i] = stats->params.rawawb.yhist_bin[i] & 0x7FFF;
            statsInt->awb_stats_v32.WpNoHist[i] *=    (1 << 3);
        }
    }

    for(int i = 0; i < statsInt->awb_stats_v32.awb_cfg_effect_v32.lightNum; i++) {
        statsInt->awb_stats_v32.WpNo2[i] =  stats->params.rawawb.sum[i].wp_num2;
    }
    for(int i = 0; i < RK_AIQ_AWB_STAT_WP_RANGE_NUM_V201; i++) {
        statsInt->awb_stats_v32.excWpRangeResult[i].RgainValue = stats->params.rawawb.sum_exc[i].rgain_exc;
        statsInt->awb_stats_v32.excWpRangeResult[i].BgainValue = stats->params.rawawb.sum_exc[i].bgain_exc;
        statsInt->awb_stats_v32.excWpRangeResult[i].WpNo =    stats->params.rawawb.sum_exc[i].wp_num_exc;

    }

    to->set_sequence(stats->frame_id);

    return ret;
}



XCamReturn RkAiqResourceTranslatorV32::translateAfStats(const SmartPtr<VideoBuffer>& from,
        SmartPtr<RkAiqAfStatsProxy>& to) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    const SmartPtr<Isp20StatsBuffer> buf =
        from.dynamic_cast_ptr<Isp20StatsBuffer>();
    struct rkisp32_isp_stat_buffer *stats;
    SmartPtr<RkAiqAfStats> statsInt = to->data();

    stats = (struct rkisp32_isp_stat_buffer*)(buf->get_v4l2_userptr());
    if(stats == NULL) {
        LOGE("fail to get stats ,ignore\n");
        return XCAM_RETURN_BYPASS;
    }
    LOGI_ANALYZER("stats: frame_id: %d,  meas_type; 0x%x",
                  stats->frame_id, stats->meas_type);

    SmartPtr<RkAiqAfInfoProxy> afParams = buf->get_af_params();

    memset(&statsInt->af_stats_v3x, 0, sizeof(rk_aiq_isp_af_stats_v3x_t));
    statsInt->frame_id = stats->frame_id;

    //af
    {
        statsInt->af_stats_valid =
            (stats->meas_type >> 6) & (0x01) ? true : false;

        statsInt->af_stats_v3x.int_state = stats->params.rawaf.int_state;
        statsInt->af_stats_v3x.wndb_luma = stats->params.rawaf.afm_lum_b;
        statsInt->af_stats_v3x.wndb_sharpness = stats->params.rawaf.afm_sum_b;
        statsInt->af_stats_v3x.winb_highlit_cnt = stats->params.rawaf.highlit_cnt_winb;
        for (int i = 0; i < RKAIQ_RAWAF_SUMDATA_NUM; i++) {
            statsInt->af_stats_v3x.wnda_fv_v1[i] = stats->params.rawaf.ramdata[i].v1;
            statsInt->af_stats_v3x.wnda_fv_v2[i] = stats->params.rawaf.ramdata[i].v2;
            statsInt->af_stats_v3x.wnda_fv_h1[i] = stats->params.rawaf.ramdata[i].h1;
            statsInt->af_stats_v3x.wnda_fv_h2[i] = stats->params.rawaf.ramdata[i].h2;

            statsInt->af_stats_v3x.wnda_luma[i] = stats->params.rawae3_0.data[i].channelg_xy;
            statsInt->af_stats_v3x.wina_highlit_cnt[i] =
                ((stats->params.rawae3_0.data[i].channelr_xy & 0x3F) << 10) | stats->params.rawae3_0.data[i].channelb_xy;
        }

        if(afParams.ptr()) {
            statsInt->af_stats_v3x.focusCode = afParams->data()->focusCode;
            statsInt->af_stats_v3x.zoomCode = afParams->data()->zoomCode;
            statsInt->af_stats_v3x.focus_endtim = afParams->data()->focusEndTim;
            statsInt->af_stats_v3x.focus_starttim = afParams->data()->focusStartTim;
            statsInt->af_stats_v3x.zoom_endtim = afParams->data()->zoomEndTim;
            statsInt->af_stats_v3x.zoom_starttim = afParams->data()->zoomStartTim;
            statsInt->af_stats_v3x.sof_tim = afParams->data()->sofTime;
            statsInt->af_stats_v3x.focusCorrection = afParams->data()->focusCorrection;
            statsInt->af_stats_v3x.zoomCorrection = afParams->data()->zoomCorrection;
            statsInt->af_stats_v3x.angleZ = afParams->data()->angleZ;
        }
    }

    return ret;

}

#if RKAIQ_HAVE_DEHAZE_V12
XCamReturn RkAiqResourceTranslatorV32::translateAdehazeStats(const SmartPtr<VideoBuffer>& from,
        SmartPtr<RkAiqAdehazeStatsProxy>& to) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    const SmartPtr<Isp20StatsBuffer> buf = from.dynamic_cast_ptr<Isp20StatsBuffer>();
    struct rkisp32_isp_stat_buffer* stats;
    SmartPtr<RkAiqAdehazeStats> statsInt = to->data();

    stats = (struct rkisp32_isp_stat_buffer*)(buf->get_v4l2_userptr());
    if (stats == NULL) {
        LOGE("fail to get stats ,ignore\n");
        return XCAM_RETURN_BYPASS;
    }
    LOGI_ANALYZER("stats: frame_id: %d,  meas_type; 0x%x", stats->frame_id, stats->meas_type);

    // dehaze
    statsInt->adehaze_stats_valid = stats->meas_type >> 17 & 1;
    statsInt->adehaze_stats.dehaze_stats_v12.dhaz_adp_air_base =
        stats->params.dhaz.dhaz_adp_air_base;
    statsInt->adehaze_stats.dehaze_stats_v12.dhaz_adp_wt     = stats->params.dhaz.dhaz_adp_wt;
    statsInt->adehaze_stats.dehaze_stats_v12.dhaz_adp_gratio = stats->params.dhaz.dhaz_adp_gratio;
    statsInt->adehaze_stats.dehaze_stats_v12.dhaz_adp_wt     = stats->params.dhaz.dhaz_adp_wt;
    statsInt->adehaze_stats.dehaze_stats_v12.dhaz_pic_sumh   = stats->params.dhaz.dhaz_pic_sumh;
    for (int i = 0; i < ISP3X_DHAZ_HIST_IIR_NUM; i++)
        statsInt->adehaze_stats.dehaze_stats_v12.h_rgb_iir[i] = stats->params.dhaz.h_rgb_iir[i];

    return ret;
}
#endif

}  // namespace RkCam
