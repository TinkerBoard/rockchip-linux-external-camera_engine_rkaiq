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
    rkisp_effect_params_v20 ispParams         = {0};
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

    struct isp32_bls_cfg* bls_cfg = &ispParams.isp_params_v32.others.bls_cfg;
    struct isp2x_bls_fixed_val bls1_val;  // bls1_val = blc1_ori_val * awb * range_ratio
    float bls_ratio[3] = {1, 1, 1};
    u32 pixel_num      = 0;

    if (bls_cfg->bls1_en) {
        bls1_val.r  = bls_cfg->bls1_val.r >> 2;
        bls1_val.gr = bls_cfg->bls1_val.gr;
        bls1_val.gb = bls_cfg->bls1_val.gb;
        bls1_val.b  = bls_cfg->bls1_val.b >> 2;

        bls_ratio[0] = (float)((1 << 12) - 1) / ((1 << 12) - 1 - bls_cfg->bls1_val.r);
        bls_ratio[1] = (float)((1 << 12) - 1) / ((1 << 12) - 1 - bls_cfg->bls1_val.gr);
        bls_ratio[2] = (float)((1 << 12) - 1) / ((1 << 12) - 1 - bls_cfg->bls1_val.b);

    } else {
        bls1_val.r  = 0;
        bls1_val.gr = 0;
        bls1_val.gb = 0;
        bls1_val.b  = 0;
    }

#ifdef AE_STATS_DEBUG
    LOGE("bls1[%d-%d-%d-%d]", bls1_val.r, bls1_val.gr, bls1_val.gb, bls1_val.b);
    LOGE("bls_ratio[%f-%f-%f]", bls_ratio[0], bls_ratio[1], bls_ratio[2]);
#endif

    switch (AeSwapMode) {
        case AEC_RAWSWAP_MODE_S_LITE:
            meas_type = ((stats->meas_type >> 7) & (0x01)) & ((stats->meas_type >> 11) & (0x01));
            statsInt->aec_stats_valid = (meas_type & 0x01) ? true : false;

            for (int i = 0; i < ISP3X_RAWAEBIG_MEAN_NUM; i++) {
                if (i < ISP3X_RAWAELITE_MEAN_NUM) {
                    statsInt->aec_stats.ae_data.chn[0].rawae_lite.channelr_xy[i] = (u16)(
                        (stats->params.rawae0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[0].rawae_lite.channelg_xy[i] = (u16)(
                        (stats->params.rawae0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[0].rawae_lite.channelb_xy[i] = (u16)(
                        (stats->params.rawae0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);
                }
                statsInt->aec_stats.ae_data.chn[1].rawae_big.channelr_xy[i] =
                    (u16)((stats->params.rawae1_0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                statsInt->aec_stats.ae_data.chn[1].rawae_big.channelg_xy[i] =
                    (u16)((stats->params.rawae1_0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                statsInt->aec_stats.ae_data.chn[1].rawae_big.channelb_xy[i] =
                    (u16)((stats->params.rawae1_0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);
                statsInt->aec_stats.ae_data.chn[2].rawae_big.channelr_xy[i] =
                    (u16)((stats->params.rawae2_0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                statsInt->aec_stats.ae_data.chn[2].rawae_big.channelg_xy[i] =
                    (u16)((stats->params.rawae2_0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                statsInt->aec_stats.ae_data.chn[2].rawae_big.channelb_xy[i] =
                    (u16)((stats->params.rawae2_0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);

                if (i < ISP3X_RAWAEBIG_SUBWIN_NUM) {
                    pixel_num =
                        isp_params->rawae1.subwin[i].h_size * isp_params->rawae1.subwin[i].v_size;
                    statsInt->aec_stats.ae_data.chn[1].rawae_big.wndx_sumr[i] =
                        (u32)((stats->params.rawae1_1.sumr[i] - (pixel_num >> 2) * bls1_val.r) *
                              bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[1].rawae_big.wndx_sumg[i] =
                        (u32)((stats->params.rawae1_1.sumg[i] - (pixel_num >> 1) * bls1_val.gr) *
                              bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[1].rawae_big.wndx_sumb[i] =
                        (u32)((stats->params.rawae1_1.sumb[i] - (pixel_num >> 2) * bls1_val.b) *
                              bls_ratio[2]);
                    pixel_num =
                        isp_params->rawae2.subwin[i].h_size * isp_params->rawae2.subwin[i].v_size;
                    statsInt->aec_stats.ae_data.chn[2].rawae_big.wndx_sumr[i] =
                        (u32)((stats->params.rawae2_1.sumr[i] - (pixel_num >> 2) * bls1_val.r) *
                              bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[2].rawae_big.wndx_sumg[i] =
                        (u32)((stats->params.rawae2_1.sumg[i] - (pixel_num >> 1) * bls1_val.gr) *
                              bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[2].rawae_big.wndx_sumb[i] =
                        (u32)((stats->params.rawae2_1.sumb[i] - (pixel_num >> 2) * bls1_val.b) *
                              bls_ratio[2]);
                }
            }

            if (bls_cfg->bls1_en) {
                memset(statsInt->aec_stats.ae_data.chn[0].rawhist_lite.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memset(statsInt->aec_stats.ae_data.chn[1].rawhist_big.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memset(statsInt->aec_stats.ae_data.chn[2].rawhist_lite.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                for (int i = 0; i < ISP3X_HIST_BIN_N_MAX; i++) {
                    int tmp;
                    switch (isp_params->rawhist0.mode) {
                        case 2:
                            tmp = (i - (bls1_val.r >> 2) > 0)
                                      ? (i - (bls1_val.r >> 2)) * bls_ratio[0] + 0.5
                                      : 0;
                            break;
                        case 3:
                            tmp = (i - (bls1_val.gr >> 4) > 0)
                                      ? (i - (bls1_val.gr >> 4)) * bls_ratio[1] + 0.5
                                      : 0;
                            break;
                        case 4:
                            tmp = (i - (bls1_val.b >> 2) > 0)
                                      ? (i - (bls1_val.b >> 2)) * bls_ratio[2] + 0.5
                                      : 0;
                            break;
                        case 5:
                        default:
                            s16 hist_bls1 =
                                (s16)((bls1_val.gr >> 4) * 0.587 + (bls1_val.r >> 2) * 0.299 +
                                      (bls1_val.b >> 2) * 0.144 + 0.5);
                            float hist_bls_ratio =
                                (float)((1 << 8) - 1) / ((1 << 8) - 1 - hist_bls1);
                            tmp = (i - hist_bls1) ? (i - hist_bls1) * hist_bls_ratio + 0.5 : 0;
                            break;
                    }
                    if (tmp > ISP3X_HIST_BIN_N_MAX - 1) tmp = ISP3X_HIST_BIN_N_MAX - 1;
                    statsInt->aec_stats.ae_data.chn[0].rawhist_lite.bins[tmp] +=
                        stats->params.rawhist0.hist_bin[i];
                    statsInt->aec_stats.ae_data.chn[1].rawhist_big.bins[tmp] +=
                        stats->params.rawhist1.hist_bin[i];
                    statsInt->aec_stats.ae_data.chn[2].rawhist_big.bins[tmp] +=
                        stats->params.rawhist2.hist_bin[i];
                }
            } else {
                memcpy(statsInt->aec_stats.ae_data.chn[0].rawhist_lite.bins,
                       stats->params.rawhist0.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memcpy(statsInt->aec_stats.ae_data.chn[1].rawhist_big.bins,
                       stats->params.rawhist1.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memcpy(statsInt->aec_stats.ae_data.chn[2].rawhist_big.bins,
                       stats->params.rawhist2.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
            }

            break;

        case AEC_RAWSWAP_MODE_M_LITE:
            meas_type = ((stats->meas_type >> 8) & (0x01)) & ((stats->meas_type >> 12) & (0x01));
            statsInt->aec_stats_valid = (meas_type & 0x01) ? true : false;

            for (int i = 0; i < ISP3X_RAWAEBIG_MEAN_NUM; i++) {
                if (i < ISP3X_RAWAELITE_MEAN_NUM) {
                    statsInt->aec_stats.ae_data.chn[1].rawae_lite.channelr_xy[i] = (u16)(
                        (stats->params.rawae0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[1].rawae_lite.channelg_xy[i] = (u16)(
                        (stats->params.rawae0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[1].rawae_lite.channelb_xy[i] = (u16)(
                        (stats->params.rawae0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);
                }
                statsInt->aec_stats.ae_data.chn[0].rawae_big.channelr_xy[i] =
                    (u16)((stats->params.rawae1_0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                statsInt->aec_stats.ae_data.chn[0].rawae_big.channelg_xy[i] =
                    (u16)((stats->params.rawae1_0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                statsInt->aec_stats.ae_data.chn[0].rawae_big.channelb_xy[i] =
                    (u16)((stats->params.rawae1_0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);
                statsInt->aec_stats.ae_data.chn[2].rawae_big.channelr_xy[i] =
                    (u16)((stats->params.rawae2_0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                statsInt->aec_stats.ae_data.chn[2].rawae_big.channelg_xy[i] =
                    (u16)((stats->params.rawae2_0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                statsInt->aec_stats.ae_data.chn[2].rawae_big.channelb_xy[i] =
                    (u16)((stats->params.rawae2_0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);

                if (i < ISP3X_RAWAEBIG_SUBWIN_NUM) {
                    pixel_num =
                        isp_params->rawae1.subwin[i].h_size * isp_params->rawae1.subwin[i].v_size;
                    statsInt->aec_stats.ae_data.chn[0].rawae_big.wndx_sumr[i] =
                        (u32)((stats->params.rawae1_1.sumr[i] - (pixel_num >> 2) * bls1_val.r) *
                              bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[0].rawae_big.wndx_sumg[i] =
                        (u32)((stats->params.rawae1_1.sumg[i] - (pixel_num >> 1) * bls1_val.gr) *
                              bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[0].rawae_big.wndx_sumb[i] =
                        (u32)((stats->params.rawae1_1.sumb[i] - (pixel_num >> 2) * bls1_val.b) *
                              bls_ratio[2]);

                    pixel_num =
                        isp_params->rawae2.subwin[i].h_size * isp_params->rawae2.subwin[i].v_size;
                    statsInt->aec_stats.ae_data.chn[2].rawae_big.wndx_sumr[i] =
                        (u32)((stats->params.rawae2_1.sumr[i] - (pixel_num >> 2) * bls1_val.r) *
                              bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[2].rawae_big.wndx_sumg[i] =
                        (u32)((stats->params.rawae2_1.sumg[i] - (pixel_num >> 1) * bls1_val.gr) *
                              bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[2].rawae_big.wndx_sumb[i] =
                        (u32)((stats->params.rawae2_1.sumb[i] - (pixel_num >> 2) * bls1_val.b) *
                              bls_ratio[2]);
                }
            }

            if (bls_cfg->bls1_en) {
                memset(statsInt->aec_stats.ae_data.chn[0].rawhist_big.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memset(statsInt->aec_stats.ae_data.chn[1].rawhist_lite.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memset(statsInt->aec_stats.ae_data.chn[2].rawhist_big.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));

                for (int i = 0; i < ISP3X_HIST_BIN_N_MAX; i++) {
                    int tmp;
                    switch (isp_params->rawhist1.mode) {
                        case 2:
                            tmp = (i - (bls1_val.r >> 2) > 0)
                                      ? (i - (bls1_val.r >> 2)) * bls_ratio[0] + 0.5
                                      : 0;
                            break;
                        case 3:
                            tmp = (i - (bls1_val.gr >> 4) > 0)
                                      ? (i - (bls1_val.gr >> 4)) * bls_ratio[1] + 0.5
                                      : 0;
                            break;
                        case 4:
                            tmp = (i - (bls1_val.b >> 2) > 0)
                                      ? (i - (bls1_val.b >> 2)) * bls_ratio[2] + 0.5
                                      : 0;
                            break;
                        case 5:
                        default:
                            s16 hist_bls1 =
                                (s16)((bls1_val.gr >> 4) * 0.587 + (bls1_val.r >> 2) * 0.299 +
                                      (bls1_val.b >> 2) * 0.144 + 0.5);
                            float hist_bls_ratio =
                                (float)((1 << 8) - 1) / ((1 << 8) - 1 - hist_bls1);
                            tmp = (i - hist_bls1) ? (i - hist_bls1) * hist_bls_ratio + 0.5 : 0;
                            break;
                    }
                    if (tmp > ISP3X_HIST_BIN_N_MAX - 1) tmp = ISP3X_HIST_BIN_N_MAX - 1;
                    statsInt->aec_stats.ae_data.chn[0].rawhist_big.bins[tmp] +=
                        stats->params.rawhist1.hist_bin[i];
                    statsInt->aec_stats.ae_data.chn[1].rawhist_lite.bins[tmp] +=
                        stats->params.rawhist0.hist_bin[i];
                    statsInt->aec_stats.ae_data.chn[2].rawhist_big.bins[tmp] +=
                        stats->params.rawhist2.hist_bin[i];
                }
            } else {
                memcpy(statsInt->aec_stats.ae_data.chn[0].rawhist_big.bins,
                       stats->params.rawhist1.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memcpy(statsInt->aec_stats.ae_data.chn[1].rawhist_lite.bins,
                       stats->params.rawhist0.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memcpy(statsInt->aec_stats.ae_data.chn[2].rawhist_big.bins,
                       stats->params.rawhist2.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
            }

            break;

        case AEC_RAWSWAP_MODE_L_LITE:
            meas_type = ((stats->meas_type >> 9) & (0x01)) & ((stats->meas_type >> 13) & (0x01));
            statsInt->aec_stats_valid = (meas_type & 0x01) ? true : false;

            for (int i = 0; i < ISP3X_RAWAEBIG_MEAN_NUM; i++) {
                if (i < ISP3X_RAWAELITE_MEAN_NUM) {
                    statsInt->aec_stats.ae_data.chn[2].rawae_lite.channelr_xy[i] = (u16)(
                        (stats->params.rawae0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[2].rawae_lite.channelg_xy[i] = (u16)(
                        (stats->params.rawae0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[2].rawae_lite.channelb_xy[i] = (u16)(
                        (stats->params.rawae0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);
                }
                statsInt->aec_stats.ae_data.chn[0].rawae_big.channelr_xy[i] =
                    (u16)((stats->params.rawae2_0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                statsInt->aec_stats.ae_data.chn[0].rawae_big.channelg_xy[i] =
                    (u16)((stats->params.rawae2_0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                statsInt->aec_stats.ae_data.chn[0].rawae_big.channelb_xy[i] =
                    (u16)((stats->params.rawae2_0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);
                statsInt->aec_stats.ae_data.chn[1].rawae_big.channelr_xy[i] =
                    (u16)((stats->params.rawae1_0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                statsInt->aec_stats.ae_data.chn[1].rawae_big.channelg_xy[i] =
                    (u16)((stats->params.rawae1_0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                statsInt->aec_stats.ae_data.chn[1].rawae_big.channelb_xy[i] =
                    (u16)((stats->params.rawae1_0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);

                if (i < ISP3X_RAWAEBIG_SUBWIN_NUM) {
                    pixel_num =
                        isp_params->rawae2.subwin[i].h_size * isp_params->rawae2.subwin[i].v_size;
                    statsInt->aec_stats.ae_data.chn[0].rawae_big.wndx_sumr[i] =
                        (u32)((stats->params.rawae2_1.sumr[i] - (pixel_num >> 2) * bls1_val.r) *
                              bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[0].rawae_big.wndx_sumg[i] =
                        (u32)((stats->params.rawae2_1.sumg[i] - (pixel_num >> 1) * bls1_val.gr) *
                              bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[0].rawae_big.wndx_sumb[i] =
                        (u32)((stats->params.rawae2_1.sumb[i] - (pixel_num >> 2) * bls1_val.b) *
                              bls_ratio[2]);

                    pixel_num =
                        isp_params->rawae1.subwin[i].h_size * isp_params->rawae1.subwin[i].v_size;
                    statsInt->aec_stats.ae_data.chn[1].rawae_big.wndx_sumr[i] =
                        (u32)((stats->params.rawae1_1.sumr[i] - (pixel_num >> 2) * bls1_val.r) *
                              bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[1].rawae_big.wndx_sumg[i] =
                        (u32)((stats->params.rawae1_1.sumg[i] - (pixel_num >> 1) * bls1_val.gr) *
                              bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[1].rawae_big.wndx_sumb[i] =
                        (u32)((stats->params.rawae1_1.sumb[i] - (pixel_num >> 2) * bls1_val.b) *
                              bls_ratio[2]);
                }
            }

            if (bls_cfg->bls1_en) {
                memset(statsInt->aec_stats.ae_data.chn[0].rawhist_big.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memset(statsInt->aec_stats.ae_data.chn[1].rawhist_big.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memset(statsInt->aec_stats.ae_data.chn[2].rawhist_lite.bins, 0,
                       ISP3X_HIST_BIN_N_MAX * sizeof(u32));

                for (int i = 0; i < ISP3X_HIST_BIN_N_MAX; i++) {
                    int tmp;
                    switch (isp_params->rawhist2.mode) {
                        case 2:
                            tmp = (i - (bls1_val.r >> 2) > 0)
                                      ? (i - (bls1_val.r >> 2)) * bls_ratio[0] + 0.5
                                      : 0;
                            break;
                        case 3:
                            tmp = (i - (bls1_val.gr >> 4) > 0)
                                      ? (i - (bls1_val.gr >> 4)) * bls_ratio[1] + 0.5
                                      : 0;
                            break;
                        case 4:
                            tmp = (i - (bls1_val.b >> 2) > 0)
                                      ? (i - (bls1_val.b >> 2)) * bls_ratio[2] + 0.5
                                      : 0;
                            break;
                        case 5:
                        default:
                            s16 hist_bls1 =
                                (s16)((bls1_val.gr >> 4) * 0.587 + (bls1_val.r >> 2) * 0.299 +
                                      (bls1_val.b >> 2) * 0.144 + 0.5);
                            float hist_bls_ratio =
                                (float)((1 << 8) - 1) / ((1 << 8) - 1 - hist_bls1);
                            tmp = (i - hist_bls1) ? (i - hist_bls1) * hist_bls_ratio + 0.5 : 0;
                            break;
                    }
                    if (tmp > ISP3X_HIST_BIN_N_MAX - 1) tmp = ISP3X_HIST_BIN_N_MAX - 1;
                    statsInt->aec_stats.ae_data.chn[0].rawhist_big.bins[tmp] +=
                        stats->params.rawhist2.hist_bin[i];
                    statsInt->aec_stats.ae_data.chn[1].rawhist_big.bins[tmp] +=
                        stats->params.rawhist1.hist_bin[i];
                    statsInt->aec_stats.ae_data.chn[2].rawhist_lite.bins[tmp] +=
                        stats->params.rawhist0.hist_bin[i];
                }
            } else {
                memcpy(statsInt->aec_stats.ae_data.chn[0].rawhist_big.bins,
                       stats->params.rawhist2.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memcpy(statsInt->aec_stats.ae_data.chn[1].rawhist_big.bins,
                       stats->params.rawhist1.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                memcpy(statsInt->aec_stats.ae_data.chn[2].rawhist_lite.bins,
                       stats->params.rawhist0.hist_bin, ISP3X_HIST_BIN_N_MAX * sizeof(u32));
            }
            break;

        default:
            LOGE("wrong AeSwapMode=%d\n", AeSwapMode);
            return XCAM_RETURN_ERROR_PARAM;
            break;
    }

    statsInt->af_prior = (AfUseAeBig == 0) ? false : true;

    if (!AfUseAeBig) {
        switch (AeSelMode) {
            case AEC_RAWSEL_MODE_CHN_0:
            case AEC_RAWSEL_MODE_CHN_1:
            case AEC_RAWSEL_MODE_CHN_2:
                for (int i = 0; i < ISP3X_RAWAEBIG_MEAN_NUM; i++) {
                    statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.channelr_xy[i] = (u16)(
                        (stats->params.rawae3_0.data[i].channelr_xy - bls1_val.r) * bls_ratio[0]);
                    statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.channelg_xy[i] = (u16)(
                        (stats->params.rawae3_0.data[i].channelg_xy - bls1_val.gr) * bls_ratio[1]);
                    statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.channelb_xy[i] = (u16)(
                        (stats->params.rawae3_0.data[i].channelb_xy - bls1_val.b) * bls_ratio[2]);

                    if (i < ISP3X_RAWAEBIG_SUBWIN_NUM) {
                        pixel_num = isp_params->rawae3.subwin[i].h_size *
                                    isp_params->rawae3.subwin[i].v_size;
                        statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.wndx_sumr[i] =
                            (u32)((stats->params.rawae3_1.sumr[i] - (pixel_num >> 2) * bls1_val.r) *
                                  bls_ratio[0]);
                        statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.wndx_sumg[i] =
                            (u32)((stats->params.rawae3_1.sumg[i] - (pixel_num >> 1) * bls1_val.gr) *
                                  bls_ratio[1]);
                        statsInt->aec_stats.ae_data.chn[AeSelMode].rawae_big.wndx_sumb[i] =
                            (u32)((stats->params.rawae3_1.sumb[i] - (pixel_num >> 2) * bls1_val.b) *
                                  bls_ratio[2]);
                    }
                }

                if (bls_cfg->bls1_en) {
                    memset(statsInt->aec_stats.ae_data.chn[AeSelMode].rawhist_big.bins, 0,
                           ISP3X_HIST_BIN_N_MAX * sizeof(u32));
                    for (int i = 0; i < ISP3X_HIST_BIN_N_MAX; i++) {
                        int tmp;
                        switch (isp_params->rawhist3.mode) {
                            case 2:
                                tmp = (i - (bls1_val.r >> 2) > 0)
                                          ? (i - (bls1_val.r >> 2)) * bls_ratio[0] + 0.5
                                          : 0;
                                break;
                            case 3:
                                tmp = (i - (bls1_val.gr >> 4) > 0)
                                          ? (i - (bls1_val.gr >> 4)) * bls_ratio[1] + 0.5
                                          : 0;
                                break;
                            case 4:
                                tmp = (i - (bls1_val.b >> 2) > 0)
                                          ? (i - (bls1_val.b >> 2)) * bls_ratio[2] + 0.5
                                          : 0;
                                break;
                            case 5:
                            default:
                                s16 hist_bls1 =
                                    (s16)((bls1_val.gr >> 4) * 0.587 + (bls1_val.r >> 2) * 0.299 +
                                          (bls1_val.b >> 2) * 0.144 + 0.5);
                                float hist_bls_ratio =
                                    (float)((1 << 8) - 1) / ((1 << 8) - 1 - hist_bls1);
                                tmp = (i - hist_bls1) ? (i - hist_bls1) * hist_bls_ratio + 0.5 : 0;
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
            printf("chn0_subwin[%d]:sumr 0x%08lx, sumg 0x%08lx, sumb 0x%08lx\n", i,
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

    // rotate stats for group ae
    if (mIsGroupMode) {
        RkAiqAecHwStatsRes_t* temp = (RkAiqAecHwStatsRes_t*)calloc(1, sizeof(RkAiqAecHwStatsRes_t));
        if (mModuleRotation == 1 /*RK_PS_SrcOverlapPosition_90*/) {
            // 1) clockwise 90
            for (int i = 0; i < 3; i++) {
                // BIG
                uint8_t colnum = sqrt(ISP3X_RAWAEBIG_MEAN_NUM);
                for (int row = 0; row < colnum; row++) {
                    for (int col = 0; col < colnum; col++) {
                        temp->chn[i].rawae_big.channelr_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_big.channelr_xy[(colnum - 1 - col) * colnum + row];
                        temp->chn[i].rawae_big.channelg_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_big.channelg_xy[(colnum - 1 - col) * colnum + row];
                        temp->chn[i].rawae_big.channelb_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_big.channelb_xy[(colnum - 1 - col) * colnum + row];
                    }
                }
                // LITE
                colnum = sqrt(ISP3X_RAWAELITE_MEAN_NUM);
                for (int row = 0; row < colnum; row++) {
                    for (int col = 0; col < colnum; col++) {
                        temp->chn[i].rawae_lite.channelr_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_lite.channelr_xy[(colnum - 1 - col) * colnum + row];
                        temp->chn[i].rawae_lite.channelg_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_lite.channelg_xy[(colnum - 1 - col) * colnum + row];
                        temp->chn[i].rawae_lite.channelb_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_lite.channelb_xy[(colnum - 1 - col) * colnum + row];
                    }
                }
                memcpy(&statsInt->aec_stats.ae_data.chn[i].rawae_lite, &temp->chn[i].rawae_lite,
                       sizeof(rawaelite_stat_t));
                memcpy(&statsInt->aec_stats.ae_data.chn[i].rawae_big, &temp->chn[i].rawae_big,
                       sizeof(rawaebig_stat_t));
            }

            if (!AfUseAeBig) {
                uint8_t colnum = sqrt(ISP3X_RAWAEBIG_MEAN_NUM);
                for (int row = 0; row < colnum; row++) {
                    for (int col = 0; col < colnum; col++) {
                        temp->extra.rawae_big.channelr_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.extra.rawae_big
                                .channelr_xy[(colnum - 1 - col) * colnum + row];
                        temp->extra.rawae_big.channelg_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.extra.rawae_big
                                .channelg_xy[(colnum - 1 - col) * colnum + row];
                        temp->extra.rawae_big.channelb_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.extra.rawae_big
                                .channelb_xy[(colnum - 1 - col) * colnum + row];
                    }
                }
                memcpy(&statsInt->aec_stats.ae_data.extra.rawae_big, &temp->extra.rawae_big,
                       sizeof(rawaebig_stat_t));
            }
        } else if (mModuleRotation == 3 /*RK_PS_SrcOverlapPosition_270*/) {
            // 2) counter clockwise 90
            for (int i = 0; i < 3; i++) {
                // BIG
                uint8_t colnum = sqrt(ISP3X_RAWAEBIG_MEAN_NUM);
                for (int row = 0; row < colnum; row++) {
                    for (int col = 0; col < colnum; col++) {
                        temp->chn[i].rawae_big.channelr_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_big.channelr_xy[col * colnum + (colnum - 1 - row)];
                        temp->chn[i].rawae_big.channelg_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_big.channelg_xy[col * colnum + (colnum - 1 - row)];
                        temp->chn[i].rawae_big.channelb_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_big.channelb_xy[col * colnum + (colnum - 1 - row)];
                    }
                }
                // LITE
                colnum = sqrt(ISP3X_RAWAELITE_MEAN_NUM);
                for (int row = 0; row < colnum; row++) {
                    for (int col = 0; col < colnum; col++) {
                        temp->chn[i].rawae_lite.channelr_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_lite.channelr_xy[col * colnum + (colnum - 1 - row)];
                        temp->chn[i].rawae_lite.channelg_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_lite.channelg_xy[col * colnum + (colnum - 1 - row)];
                        temp->chn[i].rawae_lite.channelb_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.chn[i]
                                .rawae_lite.channelb_xy[col * colnum + (colnum - 1 - row)];
                    }
                }

                memcpy(&statsInt->aec_stats.ae_data.chn[i].rawae_lite, &temp->chn[i].rawae_lite,
                       sizeof(rawaelite_stat_t));
                memcpy(&statsInt->aec_stats.ae_data.chn[i].rawae_big, &temp->chn[i].rawae_big,
                       sizeof(rawaebig_stat_t));
            }

            if (!AfUseAeBig) {
                uint8_t colnum = sqrt(ISP3X_RAWAEBIG_MEAN_NUM);
                for (int row = 0; row < colnum; row++) {
                    for (int col = 0; col < colnum; col++) {
                        temp->extra.rawae_big.channelr_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.extra.rawae_big
                                .channelr_xy[col * colnum + (colnum - 1 - row)];
                        temp->extra.rawae_big.channelg_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.extra.rawae_big
                                .channelg_xy[col * colnum + (colnum - 1 - row)];
                        temp->extra.rawae_big.channelb_xy[row * colnum + col] =
                            statsInt->aec_stats.ae_data.extra.rawae_big
                                .channelb_xy[col * colnum + (colnum - 1 - row)];
                    }
                }
                memcpy(&statsInt->aec_stats.ae_data.extra.rawae_big, &temp->extra.rawae_big,
                       sizeof(rawaebig_stat_t));
            }
        } else {
            LOGW("not support mModuleRotation %d", mModuleRotation);
        }

        if (temp) free(temp);
    }

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

    return ret;
}

XCamReturn RkAiqResourceTranslatorV32::translateAfStats(const SmartPtr<VideoBuffer>& from,
                                                        SmartPtr<RkAiqAfStatsProxy>& to) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    return ret;
}

XCamReturn RkAiqResourceTranslatorV32::translateAdehazeStats(const SmartPtr<VideoBuffer>& from,
                                                             SmartPtr<RkAiqAdehazeStatsProxy>& to) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    return ret;
}

}  // namespace RkCam
