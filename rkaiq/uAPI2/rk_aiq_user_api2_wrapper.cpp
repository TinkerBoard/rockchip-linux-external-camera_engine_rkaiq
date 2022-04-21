/*
 *  Copyright (c) 2021 Rockchip Corporation
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

#include "RkAiqCalibDbV2.h"
#include "RkAiqUapitypes.h"
#include "cJSON.h"
#include "cJSON_Utils.h"
#include "j2s.h"
#include "stdlib.h"
#include "string.h"
#include "uAPI2/rk_aiq_user_api2_wrapper.h"
#include "uAPI2/rk_aiq_user_api2_sysctl.h"
#include "rk_aiq_user_api_sysctl.h"
#include "uAPI2/rk_aiq_user_api2_ae.h"
#include "uAPI2/rk_aiq_user_api2_imgproc.h"
#include "uAPI/include/rk_aiq_user_api_sysctl.h"

int rk_aiq_uapi_sysctl_swWorkingModeDyn2(const rk_aiq_sys_ctx_t *ctx,
        work_mode_t *mode) {
    return rk_aiq_uapi_sysctl_swWorkingModeDyn(ctx, mode->mode);
}

int rk_aiq_uapi_sysctl_getWorkingModeDyn(const rk_aiq_sys_ctx_t *ctx,
        work_mode_t *mode) {
    return rk_aiq_uapi2_sysctl_getWorkingMode(ctx, &mode->mode);
}

int rk_aiq_uapi2_setWBMode2(rk_aiq_sys_ctx_t *ctx, uapi_wb_mode_t *mode) {
    return rk_aiq_uapi2_setWBMode(ctx, mode->mode);
}

int rk_aiq_uapi2_getWBMode2(rk_aiq_sys_ctx_t *ctx, uapi_wb_mode_t *mode) {
    return rk_aiq_uapi2_getWBMode(ctx, &mode->mode);
}

int rk_aiq_user_api2_set_scene(const rk_aiq_sys_ctx_t* sys_ctx, aiq_scene_t* scene)
{
    return rk_aiq_uapi_sysctl_switch_scene(sys_ctx, scene->main_scene, scene->sub_scene);
}

int rk_aiq_user_api2_get_scene(const rk_aiq_sys_ctx_t* sys_ctx, aiq_scene_t* scene)
{
    (void)sys_ctx;
    scene->main_scene = strdup("normal");
    scene->sub_scene = strdup("day");

    return 0;
}

int rk_aiq_uapi_get_ae_hwstats(const rk_aiq_sys_ctx_t* sys_ctx, uapi_ae_hwstats_t* ae_hwstats)
{
    rk_aiq_isp_stats_t isp_stats;
    rk_aiq_uapi_sysctl_get3AStats(sys_ctx, &isp_stats);

    memcpy(ae_hwstats, &isp_stats.aec_stats.ae_data, sizeof(uapi_ae_hwstats_t));

    return 0;
}

int rk_aiq_uapi_get_awb_stat(const rk_aiq_sys_ctx_t* sys_ctx, rk_tool_awb_stat_res2_v30_t* awb_stat)
{
    rk_aiq_isp_stats_t isp_stats;
    rk_aiq_uapi_sysctl_get3AStats(sys_ctx, &isp_stats);

    memcpy(awb_stat, &isp_stats.awb_stats_v3x, sizeof(rk_tool_awb_stat_res2_v30_t));

    return 0;
}
int rk_aiq_uapi_get_awbV21_stat(const rk_aiq_sys_ctx_t* sys_ctx, rk_tool_awb_stat_res2_v201_t* awb_stat)
{
    rk_aiq_isp_stats_t isp_stats;
    rk_aiq_uapi_sysctl_get3AStats(sys_ctx, &isp_stats);

    memcpy(awb_stat, &isp_stats.awb_stats_v21, sizeof(rk_aiq_awb_stat_res2_v201_t));

    return 0;
}
int rk_aiq_uapi_get_awbV32_stat(const rk_aiq_sys_ctx_t* sys_ctx, rk_tool_isp_awb_stats_v32_t* awb_stat)
{
    rk_aiq_isp_stats_t isp_stats;
    rk_aiq_uapi_sysctl_get3AStats(sys_ctx, &isp_stats);
    memcpy(awb_stat->light, isp_stats.awb_stats_v32.light, sizeof(awb_stat->light));
    memcpy(awb_stat->blockResult, isp_stats.awb_stats_v32.blockResult, sizeof(awb_stat->blockResult));
    memcpy(awb_stat->WpNo2, isp_stats.awb_stats_v32.WpNo2, sizeof(awb_stat->WpNo2));
    memcpy(awb_stat->WpNoHist, isp_stats.awb_stats_v32.WpNoHist, sizeof(awb_stat->WpNoHist));
    memcpy(awb_stat->excWpRangeResult, isp_stats.awb_stats_v32.excWpRangeResult, sizeof(awb_stat->excWpRangeResult));

   return 0;
}

#if RKAIQ_HAVE_MERGE_V10
XCamReturn rk_aiq_user_api2_amerge_v10_queryinfo(const rk_aiq_sys_ctx_t* sys_ctx,
                                                 uapiMergeCurrCtlData_t* merge_info) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mergeAttrV10_t merge_attr_v10;
    ret         = rk_aiq_user_api2_amerge_v10_GetAttrib(sys_ctx, &merge_attr_v10);
    *merge_info = merge_attr_v10.Info;

    return ret;
}

XCamReturn rk_aiq_set_amerge_v10_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             mMergeAttrV10_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mergeAttrV10_t merge_attr_v10;
    ret                     = rk_aiq_user_api2_amerge_v10_GetAttrib(sys_ctx, &merge_attr_v10);
    merge_attr_v10.stManual = *manual;
    ret                     = rk_aiq_user_api2_amerge_v10_SetAttrib(sys_ctx, &merge_attr_v10);

    return ret;
}

XCamReturn rk_aiq_get_amerge_v10_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             mMergeAttrV10_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mergeAttrV10_t merge_attr_v10;
    ret     = rk_aiq_user_api2_amerge_v10_GetAttrib(sys_ctx, &merge_attr_v10);
    *manual = merge_attr_v10.stManual;

    return ret;
}
#endif
#if RKAIQ_HAVE_MERGE_V11
XCamReturn rk_aiq_user_api2_amerge_v11_queryinfo(const rk_aiq_sys_ctx_t* sys_ctx,
                                                 uapiMergeCurrCtlData_t* merge_info) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mergeAttrV11_t merge_attr_v11;
    ret         = rk_aiq_user_api2_amerge_v11_GetAttrib(sys_ctx, &merge_attr_v11);
    *merge_info = merge_attr_v11.Info;

    return ret;
}

XCamReturn rk_aiq_set_amerge_v11_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             mMergeAttrV11_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mergeAttrV11_t merge_attr_v11;
    ret                     = rk_aiq_user_api2_amerge_v11_GetAttrib(sys_ctx, &merge_attr_v11);
    merge_attr_v11.stManual = *manual;
    ret                     = rk_aiq_user_api2_amerge_v11_SetAttrib(sys_ctx, &merge_attr_v11);

    return ret;
}

XCamReturn rk_aiq_get_amerge_v11_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             mMergeAttrV11_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mergeAttrV11_t merge_attr_v11;
    ret     = rk_aiq_user_api2_amerge_v11_GetAttrib(sys_ctx, &merge_attr_v11);
    *manual = merge_attr_v11.stManual;

    return ret;
}
#endif
#if RKAIQ_HAVE_MERGE_V12
XCamReturn rk_aiq_user_api2_amerge_v12_queryinfo(const rk_aiq_sys_ctx_t* sys_ctx,
                                                 uapiMergeCurrCtlData_t* merge_info) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mergeAttrV12_t merge_attr_v12;
    ret         = rk_aiq_user_api2_amerge_v12_GetAttrib(sys_ctx, &merge_attr_v12);
    *merge_info = merge_attr_v12.Info;

    return ret;
}

XCamReturn rk_aiq_set_amerge_v12_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             mMergeAttrV12_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mergeAttrV12_t merge_attr_v12;
    ret                     = rk_aiq_user_api2_amerge_v12_GetAttrib(sys_ctx, &merge_attr_v12);
    merge_attr_v12.stManual = *manual;
    ret                     = rk_aiq_user_api2_amerge_v12_SetAttrib(sys_ctx, &merge_attr_v12);

    return ret;
}

XCamReturn rk_aiq_get_amerge_v12_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             mMergeAttrV12_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    mergeAttrV12_t merge_attr_v12;
    ret     = rk_aiq_user_api2_amerge_v12_GetAttrib(sys_ctx, &merge_attr_v12);
    *manual = merge_attr_v12.stManual;

    return ret;
}
#endif

#if RKAIQ_HAVE_DRC_V10
XCamReturn rk_aiq_user_api2_adrc_v10_queryinfo(const rk_aiq_sys_ctx_t* sys_ctx,
                                               DrcInfoV10_t* drc_info) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    drcAttrV10_t drc_attr_v10;
    ret = rk_aiq_user_api2_adrc_v10_GetAttrib(sys_ctx, &drc_attr_v10);
    *drc_info = drc_attr_v10.Info;

    return ret;
}

XCamReturn rk_aiq_set_adrc_v10_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                           mdrcAttr_V10_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    drcAttrV10_t drc_attr_v10;
    ret = rk_aiq_user_api2_adrc_v10_GetAttrib(sys_ctx, &drc_attr_v10);
    drc_attr_v10.stManual = *manual;
    ret = rk_aiq_user_api2_adrc_v10_SetAttrib(sys_ctx, &drc_attr_v10);

    return ret;
}
XCamReturn rk_aiq_get_adrc_v10_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                           mdrcAttr_V10_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    drcAttrV10_t drc_attr_v10;
    ret = rk_aiq_user_api2_adrc_v10_GetAttrib(sys_ctx, &drc_attr_v10);
    *manual = drc_attr_v10.stManual;

    return ret;
}
#endif
#if RKAIQ_HAVE_DRC_V11
XCamReturn rk_aiq_user_api2_adrc_v11_queryinfo(const rk_aiq_sys_ctx_t* sys_ctx,
                                               DrcInfoV11_t* drc_info) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    drcAttrV11_t drc_attr_v11;
    ret = rk_aiq_user_api2_adrc_v11_GetAttrib(sys_ctx, &drc_attr_v11);
    *drc_info = drc_attr_v11.Info;

    return ret;
}

XCamReturn rk_aiq_set_adrc_v11_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                           mdrcAttr_V11_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    drcAttrV11_t drc_attr_v11;
    ret = rk_aiq_user_api2_adrc_v11_GetAttrib(sys_ctx, &drc_attr_v11);
    drc_attr_v11.stManual = *manual;
    ret = rk_aiq_user_api2_adrc_v11_SetAttrib(sys_ctx, &drc_attr_v11);

    return ret;
}
XCamReturn rk_aiq_get_adrc_v11_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                           mdrcAttr_V11_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    drcAttrV11_t drc_attr_v11;
    ret = rk_aiq_user_api2_adrc_v11_GetAttrib(sys_ctx, &drc_attr_v11);
    *manual = drc_attr_v11.stManual;

    return ret;
}
#endif
#if RKAIQ_HAVE_DRC_V12
XCamReturn rk_aiq_user_api2_adrc_v12_queryinfo(const rk_aiq_sys_ctx_t* sys_ctx,
                                               DrcInfoV12_t* drc_info) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    drcAttrV12_t drc_attr_v12;
    ret = rk_aiq_user_api2_adrc_v12_GetAttrib(sys_ctx, &drc_attr_v12);
    *drc_info = drc_attr_v12.Info;

    return ret;
}

XCamReturn rk_aiq_set_adrc_v12_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                           mdrcAttr_V12_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    drcAttrV12_t drc_attr_v12;
    ret = rk_aiq_user_api2_adrc_v12_GetAttrib(sys_ctx, &drc_attr_v12);
    drc_attr_v12.stManual = *manual;
    ret = rk_aiq_user_api2_adrc_v12_SetAttrib(sys_ctx, &drc_attr_v12);

    return ret;
}
XCamReturn rk_aiq_get_adrc_v12_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                           mdrcAttr_V12_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    drcAttrV12_t drc_attr_v12;
    ret = rk_aiq_user_api2_adrc_v12_GetAttrib(sys_ctx, &drc_attr_v12);
    *manual = drc_attr_v12.stManual;

    return ret;
}
#endif

#if RKAIQ_HAVE_GAMMA_V10
XCamReturn rk_aiq_set_agamma_v10_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             AgammaApiManualV10_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_gamma_v10_attr_t gamma_attr_v10;
    ret                     = rk_aiq_user_api2_agamma_v10_GetAttrib(sys_ctx, &gamma_attr_v10);
    gamma_attr_v10.stManual = *manual;
    ret                     = rk_aiq_user_api2_agamma_v10_SetAttrib(sys_ctx, &gamma_attr_v10);

    return ret;
}
XCamReturn rk_aiq_get_agamma_v10_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             AgammaApiManualV10_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_gamma_v10_attr_t gamma_attr_v10;
    ret     = rk_aiq_user_api2_agamma_v10_GetAttrib(sys_ctx, &gamma_attr_v10);
    *manual = gamma_attr_v10.stManual;

    return ret;
}
#endif
#if RKAIQ_HAVE_GAMMA_V11
XCamReturn rk_aiq_set_agamma_v11_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             AgammaApiManualV11_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_gamma_v11_attr_t gamma_attr_v11;
    ret                     = rk_aiq_user_api2_agamma_v11_GetAttrib(sys_ctx, &gamma_attr_v11);
    gamma_attr_v11.stManual = *manual;
    ret                     = rk_aiq_user_api2_agamma_v11_SetAttrib(sys_ctx, &gamma_attr_v11);

    return ret;
}
XCamReturn rk_aiq_get_agamma_v11_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                             AgammaApiManualV11_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_gamma_v11_attr_t gamma_attr_v11;
    ret     = rk_aiq_user_api2_agamma_v11_GetAttrib(sys_ctx, &gamma_attr_v11);
    *manual = gamma_attr_v11.stManual;

    return ret;
}
#endif

#if RKAIQ_HAVE_DEHAZE_V11
XCamReturn rk_aiq_user_api2_adehaze_v11_queryinfo(const rk_aiq_sys_ctx_t* sys_ctx,
                                                  mDehazeAttrInfoV11_t* dehaze_info) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    adehaze_sw_v11_t dehaze_attr_v11;
    ret          = rk_aiq_user_api2_adehaze_v11_getSwAttrib(sys_ctx, &dehaze_attr_v11);
    *dehaze_info = dehaze_attr_v11.Info;

    return ret;
}

XCamReturn rk_aiq_set_adehaze_v11_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                              mDehazeAttrV11_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    adehaze_sw_v11_t dehaze_attr_v11;
    ret                      = rk_aiq_user_api2_adehaze_v11_getSwAttrib(sys_ctx, &dehaze_attr_v11);
    dehaze_attr_v11.stManual = *manual;
    ret                      = rk_aiq_user_api2_adehaze_v11_setSwAttrib(sys_ctx, &dehaze_attr_v11);

    return ret;
}
XCamReturn rk_aiq_get_adehaze_v11_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                              mDehazeAttrV11_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    adehaze_sw_v11_t dehaze_attr_v11;
    ret     = rk_aiq_user_api2_adehaze_v11_getSwAttrib(sys_ctx, &dehaze_attr_v11);
    *manual = dehaze_attr_v11.stManual;

    return ret;
}
#endif
#if RKAIQ_HAVE_DEHAZE_V12
XCamReturn rk_aiq_user_api2_adehaze_v12_queryinfo(const rk_aiq_sys_ctx_t* sys_ctx,
                                                  mDehazeAttrInfoV11_t* dehaze_info) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    adehaze_sw_v12_t dehaze_attr_v12;
    ret          = rk_aiq_user_api2_adehaze_v12_getSwAttrib(sys_ctx, &dehaze_attr_v12);
    *dehaze_info = dehaze_attr_v12.Info;

    return ret;
}

XCamReturn rk_aiq_set_adehaze_v12_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                              mDehazeAttrV12_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    adehaze_sw_v12_t dehaze_attr_v12;
    ret                      = rk_aiq_user_api2_adehaze_v12_getSwAttrib(sys_ctx, &dehaze_attr_v12);
    dehaze_attr_v12.stManual = *manual;
    ret                      = rk_aiq_user_api2_adehaze_v12_setSwAttrib(sys_ctx, &dehaze_attr_v12);

    return ret;
}
XCamReturn rk_aiq_get_adehaze_v12_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                              mDehazeAttrV12_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    adehaze_sw_v12_t dehaze_attr_v12;
    ret     = rk_aiq_user_api2_adehaze_v12_getSwAttrib(sys_ctx, &dehaze_attr_v12);
    *manual = dehaze_attr_v12.stManual;

    return ret;
}
#endif

XCamReturn rk_aiq_set_accm_v1_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                              rk_aiq_ccm_mccm_attrib_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_ccm_attrib_t ccm_attr_v1;
    ret                      = rk_aiq_user_api2_accm_GetAttrib(sys_ctx, &ccm_attr_v1);
    ccm_attr_v1.stManual = *manual;
    ret                      = rk_aiq_user_api2_accm_SetAttrib(sys_ctx, &ccm_attr_v1);

    return ret;
}
XCamReturn rk_aiq_get_accm_v1_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                              rk_aiq_ccm_mccm_attrib_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_ccm_attrib_t ccm_attr_v1;
    ret     = rk_aiq_user_api2_accm_GetAttrib(sys_ctx, &ccm_attr_v1);
    *manual = ccm_attr_v1.stManual;

    return ret;
}

XCamReturn rk_aiq_set_accm_v2_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                              rk_aiq_ccm_mccm_attrib_v2_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_ccm_v2_attrib_t ccm_attr_v2;
    ret                      = rk_aiq_user_api2_accm_v2_GetAttrib(sys_ctx, &ccm_attr_v2);
    ccm_attr_v2.stManual = *manual;
    ret                      = rk_aiq_user_api2_accm_v2_SetAttrib(sys_ctx, &ccm_attr_v2);

    return ret;
}
XCamReturn rk_aiq_get_accm_v2_manual_attr(const rk_aiq_sys_ctx_t* sys_ctx,
                                              rk_aiq_ccm_mccm_attrib_v2_t* manual) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_ccm_v2_attrib_t ccm_attr_v2;
    ret     = rk_aiq_user_api2_accm_v2_GetAttrib(sys_ctx, &ccm_attr_v2);
    *manual = ccm_attr_v2.stManual;

    return ret;
}

