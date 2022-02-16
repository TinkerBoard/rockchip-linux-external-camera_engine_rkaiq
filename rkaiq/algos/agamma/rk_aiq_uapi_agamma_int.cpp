#include "rk_aiq_uapi_agamma_int.h"
#include "agamma/rk_aiq_types_agamma_algo_prvt.h"

#if RKAIQ_HAVE_GAMMA_V10
XCamReturn rk_aiq_uapi_agamma_V10_SetAttrib(RkAiqAlgoContext* ctx,
                                            const rk_aiq_gamma_v10_attr_t attr, bool need_sync) {
    LOG1_AGAMMA("ENTER: %s \n", __func__);
    AgammaHandle_t *gamma_handle = (AgammaHandle_t *)ctx;
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    gamma_handle->agammaAttrV10.mode = attr.mode;
    if (attr.mode == RK_AIQ_GAMMA_MODE_MANUAL)
        memcpy(&gamma_handle->agammaAttrV10.stManual, &attr.stManual, sizeof(AgammaApiManualV10_t));
    if (attr.mode == RK_AIQ_GAMMA_MODE_AUTO)
        memcpy(&gamma_handle->agammaAttrV10.stAuto, &attr.stAuto, sizeof(CalibDbV2_gamma_V10_t));

    LOG1_AGAMMA("EXIT: %s \n", __func__);
    return ret;
}

XCamReturn rk_aiq_uapi_agamma_V10_GetAttrib(const RkAiqAlgoContext* ctx,
                                            rk_aiq_gamma_v10_attr_t* attr) {
    LOG1_AGAMMA("ENTER: %s \n", __func__);
    AgammaHandle_t* gamma_handle = (AgammaHandle_t*)ctx;

    attr->mode = gamma_handle->agammaAttrV10.mode;
    memcpy(&attr->stManual, &gamma_handle->agammaAttrV10.stManual, sizeof(AgammaApiManualV10_t));
    memcpy(&attr->stAuto, &gamma_handle->agammaAttrV10.stAuto, sizeof(CalibDbV2_gamma_V10_t));

    LOG1_AGAMMA("EXIT: %s \n", __func__);
    return XCAM_RETURN_NO_ERROR;
}
#endif

#if RKAIQ_HAVE_GAMMA_V11
XCamReturn rk_aiq_uapi_agamma_V11_SetAttrib(RkAiqAlgoContext* ctx,
                                            const rk_aiq_gamma_v11_attr_t attr, bool need_sync) {
    LOG1_AGAMMA("ENTER: %s \n", __func__);
    AgammaHandle_t* gamma_handle = (AgammaHandle_t*)ctx;
    XCamReturn ret               = XCAM_RETURN_NO_ERROR;

    gamma_handle->agammaAttrV11.mode = attr.mode;
    if (attr.mode == RK_AIQ_GAMMA_MODE_MANUAL)
        memcpy(&gamma_handle->agammaAttrV11.stManual, &attr.stManual, sizeof(AgammaApiManualV11_t));
    if (attr.mode == RK_AIQ_GAMMA_MODE_AUTO)
        memcpy(&gamma_handle->agammaAttrV11.stAuto, &attr.stAuto, sizeof(CalibDbV2_gamma_V11_t));

    LOG1_AGAMMA("EXIT: %s \n", __func__);
    return ret;
}

XCamReturn rk_aiq_uapi_agamma_V11_GetAttrib(const RkAiqAlgoContext* ctx,
                                            rk_aiq_gamma_v11_attr_t* attr) {
    LOG1_AGAMMA("ENTER: %s \n", __func__);
    AgammaHandle_t* gamma_handle = (AgammaHandle_t*)ctx;

    attr->mode = gamma_handle->agammaAttrV11.mode;
    memcpy(&attr->stManual, &gamma_handle->agammaAttrV11.stManual, sizeof(AgammaApiManualV11_t));
    memcpy(&attr->stAuto, &gamma_handle->agammaAttrV11.stAuto, sizeof(CalibDbV2_gamma_V11_t));

    LOG1_AGAMMA("EXIT: %s \n", __func__);
    return XCAM_RETURN_NO_ERROR;
}
#endif
