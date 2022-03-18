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

#if RKAIQ_HAVE_MERGE_V10
int rk_aiq_user_api2_amerge_V10_SetAttrib2(const rk_aiq_sys_ctx_t* sys_ctx,
                                           uapiMergeCurrCtlData_t* ctldata) {
    mergeAttrV10_t setdata;

    memset(&setdata, 0, sizeof(mergeAttrV10_t));
    rk_aiq_user_api2_amerge_v10_GetAttrib(sys_ctx, &setdata);
    memcpy(&setdata.CtlInfo, ctldata, sizeof(uapiMergeCurrCtlData_t));

    return rk_aiq_user_api2_amerge_v10_SetAttrib(sys_ctx, &setdata);
}

int rk_aiq_user_api2_amerge_V10_GetAttrib2(const rk_aiq_sys_ctx_t* sys_ctx,
                                           uapiMergeCurrCtlData_t* ctldata) {
    mergeAttrV10_t setdata;

    memset(&setdata, 0, sizeof(mergeAttrV10_t));
    rk_aiq_user_api2_amerge_v10_GetAttrib(sys_ctx, &setdata);
    memcpy(ctldata, &setdata.CtlInfo, sizeof(uapiMergeCurrCtlData_t));

    return 0;
}
#endif
#if RKAIQ_HAVE_MERGE_V11
int rk_aiq_user_api2_amerge_V11_SetAttrib2(const rk_aiq_sys_ctx_t* sys_ctx,
                                           uapiMergeCurrCtlData_t* ctldata) {
    mergeAttrV11_t setdata;

    memset(&setdata, 0, sizeof(mergeAttrV11_t));
    rk_aiq_user_api2_amerge_v11_GetAttrib(sys_ctx, &setdata);
    memcpy(&setdata.CtlInfo, ctldata, sizeof(uapiMergeCurrCtlData_t));

    return rk_aiq_user_api2_amerge_v11_SetAttrib(sys_ctx, &setdata);
}

int rk_aiq_user_api2_amerge_V11_GetAttrib2(const rk_aiq_sys_ctx_t* sys_ctx,
                                           uapiMergeCurrCtlData_t* ctldata) {
    mergeAttrV11_t setdata;

    memset(&setdata, 0, sizeof(mergeAttrV11_t));
    rk_aiq_user_api2_amerge_v11_GetAttrib(sys_ctx, &setdata);
    memcpy(ctldata, &setdata.CtlInfo, sizeof(uapiMergeCurrCtlData_t));

    return 0;
}
#endif
#if RKAIQ_HAVE_MERGE_V12
int rk_aiq_user_api2_amerge_V12_SetAttrib2(const rk_aiq_sys_ctx_t* sys_ctx,
                                           uapiMergeCurrCtlData_t* ctldata) {
    mergeAttrV12_t setdata;

    memset(&setdata, 0, sizeof(mergeAttrV12_t));
    rk_aiq_user_api2_amerge_v12_GetAttrib(sys_ctx, &setdata);
    memcpy(&setdata.CtlInfo, ctldata, sizeof(uapiMergeCurrCtlData_t));

    return rk_aiq_user_api2_amerge_v12_SetAttrib(sys_ctx, &setdata);
}

int rk_aiq_user_api2_amerge_V12_GetAttrib2(const rk_aiq_sys_ctx_t* sys_ctx,
                                           uapiMergeCurrCtlData_t* ctldata) {
    mergeAttrV12_t setdata;

    memset(&setdata, 0, sizeof(mergeAttrV12_t));
    rk_aiq_user_api2_amerge_v12_GetAttrib(sys_ctx, &setdata);
    memcpy(ctldata, &setdata.CtlInfo, sizeof(uapiMergeCurrCtlData_t));

    return 0;
}
#endif

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
