/*
 * Copyright (c) 2019-2022 Rockchip Eletronics Co., Ltd.
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
#include "uAPI2/rk_aiq_user_api2_adrc.h"
#include "RkAiqCamGroupHandleInt.h"
#include "algo_handlers/RkAiqAdrcHandle.h"

RKAIQ_BEGIN_DECLARE

#ifdef RK_SIMULATOR_HW
#define CHECK_USER_API_ENABLE
#endif

#if RKAIQ_HAVE_DRC_V10
XCamReturn rk_aiq_user_api2_adrc_v10_SetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               const drcAttrV10_t* attr) {
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_ADRC);

    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        RkAiqCamGroupAdrcHandleInt* algo_handle =
            camgroupAlgoHandle<RkAiqCamGroupAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->setAttribV10(attr);
        } else {
            const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t*)sys_ctx;
            for (auto camCtx : camgroup_ctx->cam_ctxs_array) {
                if (!camCtx) continue;

                RkAiqAdrcHandleInt* singleCam_algo_handle =
                    algoHandle<RkAiqAdrcHandleInt>(camCtx, RK_AIQ_ALGO_TYPE_ADRC);
                if (singleCam_algo_handle) return singleCam_algo_handle->setAttribV10(attr);
            }
        }
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        RkAiqAdrcHandleInt* algo_handle =
            algoHandle<RkAiqAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->setAttribV10(attr);
        }
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn rk_aiq_user_api2_adrc_v10_GetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               drcAttrV10_t* attr) {
    RKAIQ_API_SMART_LOCK(sys_ctx);

    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        RkAiqCamGroupAdrcHandleInt* algo_handle =
            camgroupAlgoHandle<RkAiqCamGroupAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->getAttribV10(attr);
        } else {
            const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t*)sys_ctx;
            for (auto camCtx : camgroup_ctx->cam_ctxs_array) {
                if (!camCtx) continue;

                RkAiqAdrcHandleInt* singleCam_algo_handle =
                    algoHandle<RkAiqAdrcHandleInt>(camCtx, RK_AIQ_ALGO_TYPE_ADRC);
                if (singleCam_algo_handle) return singleCam_algo_handle->getAttribV10(attr);
            }
        }
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        RkAiqAdrcHandleInt* algo_handle =
            algoHandle<RkAiqAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->getAttribV10(attr);
        }
    }

    return XCAM_RETURN_NO_ERROR;
}
#else
XCamReturn rk_aiq_user_api2_adrc_v10_SetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               const drcAttrV10_t* attr) {
    return XCAM_RETURN_ERROR_UNKNOWN;
}

XCamReturn rk_aiq_user_api2_adrc_v10_GetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               drcAttrV10_t* attr) {
    return XCAM_RETURN_ERROR_UNKNOWN;
}
#endif

#if RKAIQ_HAVE_DRC_V11
XCamReturn rk_aiq_user_api2_adrc_v11_SetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               const drcAttrV11_t* attr) {
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_ADRC);

    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        RkAiqCamGroupAdrcHandleInt* algo_handle =
            camgroupAlgoHandle<RkAiqCamGroupAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->setAttribV11(attr);
        } else {
            const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t*)sys_ctx;
            for (auto camCtx : camgroup_ctx->cam_ctxs_array) {
                if (!camCtx) continue;

                RkAiqAdrcHandleInt* singleCam_algo_handle =
                    algoHandle<RkAiqAdrcHandleInt>(camCtx, RK_AIQ_ALGO_TYPE_ADRC);
                if (singleCam_algo_handle) return singleCam_algo_handle->setAttribV11(attr);
            }
        }
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        RkAiqAdrcHandleInt* algo_handle =
            algoHandle<RkAiqAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->setAttribV11(attr);
        }
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn rk_aiq_user_api2_adrc_v11_GetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               drcAttrV11_t* attr) {
    RKAIQ_API_SMART_LOCK(sys_ctx);

    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        RkAiqCamGroupAdrcHandleInt* algo_handle =
            camgroupAlgoHandle<RkAiqCamGroupAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->getAttribV11(attr);
        } else {
            const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t*)sys_ctx;
            for (auto camCtx : camgroup_ctx->cam_ctxs_array) {
                if (!camCtx) continue;

                RkAiqAdrcHandleInt* singleCam_algo_handle =
                    algoHandle<RkAiqAdrcHandleInt>(camCtx, RK_AIQ_ALGO_TYPE_ADRC);
                if (singleCam_algo_handle) return singleCam_algo_handle->getAttribV11(attr);
            }
        }
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        RkAiqAdrcHandleInt* algo_handle =
            algoHandle<RkAiqAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->getAttribV11(attr);
        }
    }

    return XCAM_RETURN_NO_ERROR;
}
#else
XCamReturn rk_aiq_user_api2_adrc_v11_SetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               const drcAttrV11_t* attr) {
    return XCAM_RETURN_ERROR_UNKNOWN;
}

XCamReturn rk_aiq_user_api2_adrc_v11_GetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               drcAttrV11_t* attr) {
    return XCAM_RETURN_ERROR_UNKNOWN;
}
#endif

#if RKAIQ_HAVE_DRC_V12
XCamReturn rk_aiq_user_api2_adrc_v12_SetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               const drcAttrV12_t* attr) {
    CHECK_USER_API_ENABLE2(sys_ctx);
    CHECK_USER_API_ENABLE(RK_AIQ_ALGO_TYPE_ADRC);

    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        RkAiqCamGroupAdrcHandleInt* algo_handle =
            camgroupAlgoHandle<RkAiqCamGroupAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->setAttribV12(attr);
        } else {
            const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t *)sys_ctx;
            for (auto camCtx : camgroup_ctx->cam_ctxs_array) {
                if (!camCtx)
                    continue;

                RkAiqAdrcHandleInt* singleCam_algo_handle =
                    algoHandle<RkAiqAdrcHandleInt>(camCtx, RK_AIQ_ALGO_TYPE_ADRC);
                if (singleCam_algo_handle) return singleCam_algo_handle->setAttribV12(attr);
            }
        }
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        RkAiqAdrcHandleInt* algo_handle =
            algoHandle<RkAiqAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->setAttribV12(attr);
        }
    }

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn rk_aiq_user_api2_adrc_v12_GetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               drcAttrV12_t* attr) {
    RKAIQ_API_SMART_LOCK(sys_ctx);

    if (sys_ctx->cam_type == RK_AIQ_CAM_TYPE_GROUP) {
#ifdef RKAIQ_ENABLE_CAMGROUP
        RkAiqCamGroupAdrcHandleInt* algo_handle =
            camgroupAlgoHandle<RkAiqCamGroupAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->getAttribV12(attr);
        } else {
            const rk_aiq_camgroup_ctx_t* camgroup_ctx = (rk_aiq_camgroup_ctx_t *)sys_ctx;
            for (auto camCtx : camgroup_ctx->cam_ctxs_array) {
                if (!camCtx)
                    continue;

                RkAiqAdrcHandleInt* singleCam_algo_handle =
                    algoHandle<RkAiqAdrcHandleInt>(camCtx, RK_AIQ_ALGO_TYPE_ADRC);
                if (singleCam_algo_handle) return singleCam_algo_handle->getAttribV12(attr);
            }
        }
#else
        return XCAM_RETURN_ERROR_FAILED;
#endif
    } else {
        RkAiqAdrcHandleInt* algo_handle =
            algoHandle<RkAiqAdrcHandleInt>(sys_ctx, RK_AIQ_ALGO_TYPE_ADRC);

        if (algo_handle) {
            return algo_handle->getAttribV12(attr);
        }
    }

    return XCAM_RETURN_NO_ERROR;
}
#else
XCamReturn rk_aiq_user_api2_adrc_v12_SetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               const drcAttrV12_t* attr) {
    return XCAM_RETURN_ERROR_UNKNOWN;
}

XCamReturn rk_aiq_user_api2_adrc_v12_GetAttrib(const rk_aiq_sys_ctx_t* sys_ctx,
                                               drcAttrV12_t* attr) {
    return XCAM_RETURN_ERROR_UNKNOWN;
}
#endif

RKAIQ_END_DECLARE
