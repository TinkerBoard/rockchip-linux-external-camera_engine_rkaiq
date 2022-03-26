#include "socket_server.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "rkaiq_tool_sysctl.cpp"

int setCpsLtCfg(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_uapi_sysctl_setCpsLtCfg(ctx, (rk_aiq_cpsl_cfg_t*) data);
}

int getCpsLtInfo(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_uapi_sysctl_getCpsLtInfo(ctx, (rk_aiq_cpsl_info_t *) data);
}

int queryCpsLtCap(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_uapi_sysctl_queryCpsLtCap(ctx, (rk_aiq_cpsl_cap_t *) data);
}

int setWorkingModeDyn(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_uapi_sysctl_swWorkingModeDyn(ctx, *(rk_aiq_working_mode_t*) data);
}

int getVersionInfo(rk_aiq_sys_ctx_t* ctx, char* data) {
    rk_aiq_uapi_get_version_info((rk_aiq_ver_info_t *)data);
    return 0;
}

#if RKAIQ_HAVE_MERGE_V10
int setMergeAttribV10(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_amerge_v10_SetAttrib(ctx, (mergeAttrV10_t*)data);
}

int getMergeAttribV10(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_amerge_v10_GetAttrib(ctx, (mergeAttrV10_t*)data);
}
#endif
#if RKAIQ_HAVE_MERGE_V11
int setMergeAttribV11(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_amerge_v11_SetAttrib(ctx, (mergeAttrV11_t*)data);
}

int getMergeAttribV11(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_amerge_v11_GetAttrib(ctx, (mergeAttrV11_t*)data);
}
#endif
#if RKAIQ_HAVE_MERGE_V12
int setMergeAttribV12(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_amerge_v12_SetAttrib(ctx, (mergeAttrV12_t*)data);
}

int getMergeAttribV12(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_amerge_v12_GetAttrib(ctx, (mergeAttrV12_t*)data);
}
#endif

int setTmoAttrib(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_atmo_SetAttrib(ctx, *(atmo_attrib_t*)data);
}

int getTmoAttrib(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_atmo_GetAttrib(ctx, (atmo_attrib_t*)data);
}

int setGammaAttrib(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api_agamma_SetAttrib(ctx, *(rk_aiq_gamma_attrib_t*)data);
}

int getGammaAttrib(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api_agamma_GetAttrib(ctx, (rk_aiq_gamma_attrib_t*)data);
}

int setDpccAttrib(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_adpcc_SetAttrib(ctx, (rk_aiq_dpcc_attrib_V20_t *)data);
}

int getDpccAttrib(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api2_adpcc_GetAttrib(ctx, (rk_aiq_dpcc_attrib_V20_t *)data);
}
/*
int setDehazeAttrib(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api_adehaze_setSwAttrib(ctx, *(adehaze_sw_t *)data);
}

int getDehazeAttrib(rk_aiq_sys_ctx_t* ctx, char* data) {
    return rk_aiq_user_api_adehaze_getSwAttrib(ctx, (adehaze_sw_t *)data);
}
*/
int setCcmAttrib(rk_aiq_sys_ctx_t* ctx, char* data)
{
#if RKAIQ_HAVE_CCM_V1
    return rk_aiq_user_api_accm_SetAttrib(ctx, (rk_aiq_ccm_attrib_t*) data);
#endif
#if RKAIQ_HAVE_CCM_V2
    return rk_aiq_user_api_accm_v2_SetAttrib(ctx, (rk_aiq_ccm_v2_attrib_t*) data);
#endif
}

int getCcmAttrib(rk_aiq_sys_ctx_t* ctx, char* data)
{
#if RKAIQ_HAVE_CCM_V1
    return rk_aiq_user_api_accm_GetAttrib(ctx, (rk_aiq_ccm_attrib_t *)data);
#endif
#if RKAIQ_HAVE_CCM_V2
    return rk_aiq_user_api_accm_v2_GetAttrib(ctx, (rk_aiq_ccm_v2_attrib_t *)data);
#endif
}

int queryCCMInfo(rk_aiq_sys_ctx_t* ctx, char* data)
{
    return rk_aiq_user_api_accm_QueryCcmInfo(ctx, (rk_aiq_ccm_querry_info_t *)data);
}
int setAwbAttrib(rk_aiq_sys_ctx_t* ctx, char* data)
{
    return rk_aiq_user_api_awb_SetAttrib(ctx, *(rk_aiq_wb_attrib_t*)data);
}

int getAwbAttrib(rk_aiq_sys_ctx_t* ctx, char* data)
{
    return rk_aiq_user_api_awb_GetAttrib(ctx, (rk_aiq_wb_attrib_t*)data);
}

int getAwbCCT(rk_aiq_sys_ctx_t* ctx, char* data)
{
    return rk_aiq_user_api_awb_GetCCT(ctx, (rk_aiq_wb_cct_t *)data);
}

int queryWBInfo(rk_aiq_sys_ctx_t* ctx, char* data)
{
    return rk_aiq_user_api_awb_QueryWBInfo(ctx, (rk_aiq_wb_querry_info_t*) data);
}

int setAcpAttrib(rk_aiq_sys_ctx_t* ctx, char* data)
{
    return  rk_aiq_user_api_acp_SetAttrib(ctx, *(acp_attrib_t*) data);
}

int getAcpAttrib(rk_aiq_sys_ctx_t* ctx, char* data)
{
    return rk_aiq_user_api_acp_GetAttrib(ctx, (acp_attrib_t *) data);
}

int enqueueRkRawFile(rk_aiq_sys_ctx_t* ctx, char* data)
{
    return rk_aiq_uapi_sysctl_enqueueRkRawFile(ctx, data);
}
