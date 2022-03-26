#include "rk_aiq_uapi_adehaze_int.h"
#include "rk_aiq_types_adehaze_algo_prvt.h"
#include "xcam_log.h"

#if RKAIQ_HAVE_DEHAZE_V10
XCamReturn rk_aiq_uapi_adehaze_v10_SetAttrib(RkAiqAlgoContext* ctx, adehaze_sw_v10_t* attr,
                                             bool need_sync) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t * AdehazeHandle = (AdehazeHandle_t *)ctx;

    // AdehazeHandle->AdehazeAtrrV10.mode = attr->mode;
    // if(attr->mode == DEHAZE_API_MANUAL)
    //    memcpy(&AdehazeHandle->AdehazeAtrrV10.stManual, &attr->stManual,
    //    sizeof(mDehazeAttrV11_t));
    // if(attr->mode == DEHAZE_API_AUTO)
    //    memcpy(&AdehazeHandle->AdehazeAtrrV10.stAuto, &attr->stAuto,
    //    sizeof(CalibDbV2_dehaze_v10_t));

    return ret;
}

XCamReturn rk_aiq_uapi_adehaze_v10_GetAttrib(RkAiqAlgoContext* ctx, adehaze_sw_v10_t* attr) {
    XCamReturn ret                 = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t* AdehazeHandle = (AdehazeHandle_t*)ctx;

    // attr->mode = AdehazeHandle->AdehazeAtrrV10.mode;
    // memcpy(&attr->stManual, &AdehazeHandle->AdehazeAtrrV10.stManual, sizeof(mDehazeAttrV11_t));
    // memcpy(&attr->stAuto, &AdehazeHandle->AdehazeAtrrV10.stAuto, sizeof(CalibDbV2_dehaze_v10_t));

    return ret;
}
#endif
#if RKAIQ_HAVE_DEHAZE_V11 || RKAIQ_HAVE_DEHAZE_V11_DUO
XCamReturn rk_aiq_uapi_adehaze_v11_SetAttrib(RkAiqAlgoContext* ctx, adehaze_sw_v11_t* attr,
                                             bool need_sync) {
    XCamReturn ret                 = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t* AdehazeHandle = (AdehazeHandle_t*)ctx;

#if RKAIQ_HAVE_DEHAZE_V11
    AdehazeHandle->AdehazeAtrrV11.mode = attr->mode;
    AdehazeHandle->AdehazeAtrrV11.Info = attr->Info;
    if (attr->mode == DEHAZE_API_MANUAL)
        memcpy(&AdehazeHandle->AdehazeAtrrV11.stManual, &attr->stManual, sizeof(mDehazeAttrV11_t));
    if (attr->mode == DEHAZE_API_AUTO)
        memcpy(&AdehazeHandle->AdehazeAtrrV11.stAuto, &attr->stAuto,
               sizeof(CalibDbV2_dehaze_v11_t));
#endif
#if RKAIQ_HAVE_DEHAZE_V11_DUO
    AdehazeHandle->AdehazeAtrrV11duo.mode = attr->mode;
    AdehazeHandle->AdehazeAtrrV11duo.Info = attr->Info;
    if (attr->mode == DEHAZE_API_MANUAL)
        memcpy(&AdehazeHandle->AdehazeAtrrV11duo.stManual, &attr->stManual,
               sizeof(mDehazeAttrV11_t));
    if (attr->mode == DEHAZE_API_AUTO)
        memcpy(&AdehazeHandle->AdehazeAtrrV11duo.stAuto, &attr->stAuto,
               sizeof(CalibDbV2_dehaze_v11_t));
#endif

    return ret;
}

XCamReturn rk_aiq_uapi_adehaze_v11_GetAttrib(RkAiqAlgoContext* ctx, adehaze_sw_v11_t* attr) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t * AdehazeHandle = (AdehazeHandle_t *)ctx;

#if RKAIQ_HAVE_DEHAZE_V11
    attr->mode = AdehazeHandle->AdehazeAtrrV11.mode;
    memcpy(&attr->stManual, &AdehazeHandle->AdehazeAtrrV11.stManual, sizeof(mDehazeAttrV11_t));
    memcpy(&attr->stAuto, &AdehazeHandle->AdehazeAtrrV11.stAuto, sizeof(CalibDbV2_dehaze_v11_t));
    memcpy(&attr->Info, &AdehazeHandle->AdehazeAtrrV11.Info, sizeof(mDehazeAttrInfoV11_t));
#endif
#if RKAIQ_HAVE_DEHAZE_V11_DUO
    attr->mode = AdehazeHandle->AdehazeAtrrV11duo.mode;
    memcpy(&attr->stManual, &AdehazeHandle->AdehazeAtrrV11duo.stManual, sizeof(mDehazeAttrV11_t));
    memcpy(&attr->stAuto, &AdehazeHandle->AdehazeAtrrV11duo.stAuto, sizeof(CalibDbV2_dehaze_v11_t));
    memcpy(&attr->Info, &AdehazeHandle->AdehazeAtrrV11duo.Info, sizeof(mDehazeAttrInfoV11_t));
#endif

    return ret;
}
#endif
#if RKAIQ_HAVE_DEHAZE_V12
XCamReturn rk_aiq_uapi_adehaze_v12_SetAttrib(RkAiqAlgoContext* ctx, adehaze_sw_v12_t* attr,
                                             bool need_sync) {
    XCamReturn ret                 = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t* AdehazeHandle = (AdehazeHandle_t*)ctx;

    AdehazeHandle->AdehazeAtrrV12.mode = attr->mode;
    AdehazeHandle->AdehazeAtrrV12.Info = attr->Info;
    if (attr->mode == DEHAZE_API_MANUAL)
        memcpy(&AdehazeHandle->AdehazeAtrrV12.stManual, &attr->stManual, sizeof(mDehazeAttrV12_t));
    if (attr->mode == DEHAZE_API_AUTO)
        memcpy(&AdehazeHandle->AdehazeAtrrV12.stAuto, &attr->stAuto,
               sizeof(CalibDbV2_dehaze_v12_t));

    return ret;
}

XCamReturn rk_aiq_uapi_adehaze_v12_GetAttrib(RkAiqAlgoContext* ctx, adehaze_sw_v12_t* attr) {
    XCamReturn ret                 = XCAM_RETURN_NO_ERROR;
    AdehazeHandle_t* AdehazeHandle = (AdehazeHandle_t*)ctx;

    attr->mode = AdehazeHandle->AdehazeAtrrV12.mode;
    memcpy(&attr->stManual, &AdehazeHandle->AdehazeAtrrV12.stManual, sizeof(mDehazeAttrV12_t));
    memcpy(&attr->stAuto, &AdehazeHandle->AdehazeAtrrV12.stAuto, sizeof(CalibDbV2_dehaze_v10_t));
    memcpy(&attr->Info, &AdehazeHandle->AdehazeAtrrV12.Info, sizeof(mDehazeAttrInfoV11_t));

    return ret;
}
#endif
