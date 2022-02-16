#include "rk_aiq_uapi_amerge_int.h"
#include "rk_aiq_types_amerge_algo_prvt.h"

#if RKAIQ_HAVE_MERGE_V10
XCamReturn rk_aiq_uapi_amerge_V10_SetAttrib(RkAiqAlgoContext* ctx, mergeAttrV10_t attr,
                                            bool need_sync) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if(ctx == NULL) {
        LOGE_AMERGE("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }
    AmergeContext_t* pAmergeCtx = (AmergeContext_t*)ctx;

    pAmergeCtx->mergeAttrV10.opMode = attr.opMode;
    if (attr.opMode == MERGE_OPMODE_MANUAL)
        memcpy(&pAmergeCtx->mergeAttrV10.stAuto, &attr.stAuto, sizeof(CalibDbV2_merge_V10_t));
    else if (attr.opMode == MERGE_OPMODE_MANUAL)
        memcpy(&pAmergeCtx->mergeAttrV10.stManual, &attr.stManual, sizeof(mmergeAttrV10_t));

    return ret;
}

XCamReturn rk_aiq_uapi_amerge_V10_GetAttrib(RkAiqAlgoContext* ctx, mergeAttrV10_t* attr) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (ctx == NULL || attr == NULL) {
        LOGE_AMERGE("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    AmergeContext_t* pAmergeCtx = (AmergeContext_t*)ctx;

    attr->opMode = pAmergeCtx->mergeAttrV10.opMode;
    memcpy(&attr->stManual, &pAmergeCtx->mergeAttrV10.stManual, sizeof(mmergeAttrV10_t));
    memcpy(&attr->stAuto, &pAmergeCtx->mergeAttrV10.stAuto, sizeof(CalibDbV2_merge_V10_t));
    memcpy(&attr->CtlInfo, &pAmergeCtx->mergeAttrV10.CtlInfo, sizeof(MergeCurrCtlData_t));

    return ret;
}
#endif

#if RKAIQ_HAVE_MERGE_V11
XCamReturn rk_aiq_uapi_amerge_V11_SetAttrib(RkAiqAlgoContext* ctx, mergeAttrV11_t attr,
                                            bool need_sync) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (ctx == NULL) {
        LOGE_AMERGE("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }
    AmergeContext_t* pAmergeCtx = (AmergeContext_t*)ctx;

    pAmergeCtx->mergeAttrV11.opMode = attr.opMode;
    if (attr.opMode == MERGE_OPMODE_MANUAL)
        memcpy(&pAmergeCtx->mergeAttrV11.stAuto, &attr.stAuto, sizeof(CalibDbV2_merge_V11_t));
    else if (attr.opMode == MERGE_OPMODE_MANUAL)
        memcpy(&pAmergeCtx->mergeAttrV11.stManual, &attr.stManual, sizeof(mergeAttrV11_t));

    return ret;
}

XCamReturn rk_aiq_uapi_amerge_V11_GetAttrib(RkAiqAlgoContext* ctx, mergeAttrV11_t* attr) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if(ctx == NULL || attr == NULL) {
        LOGE_AMERGE("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    AmergeContext_t* pAmergeCtx = (AmergeContext_t*)ctx;

    attr->opMode = pAmergeCtx->mergeAttrV11.opMode;
    memcpy(&attr->stManual, &pAmergeCtx->mergeAttrV11.stManual, sizeof(mMergeAttrV11_t));
    memcpy(&attr->CtlInfo, &pAmergeCtx->mergeAttrV11.CtlInfo, sizeof(MergeCurrCtlData_t));

    return ret;
}
#endif

#if RKAIQ_HAVE_MERGE_V12
XCamReturn rk_aiq_uapi_amerge_V12_SetAttrib(RkAiqAlgoContext* ctx, mergeAttrV12_t attr,
                                            bool need_sync) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (ctx == NULL) {
        LOGE_AMERGE("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }
    AmergeContext_t* pAmergeCtx = (AmergeContext_t*)ctx;

    pAmergeCtx->mergeAttrV12.opMode = attr.opMode;
    if (attr.opMode == MERGE_OPMODE_MANUAL)
        memcpy(&pAmergeCtx->mergeAttrV12.stAuto, &attr.stAuto, sizeof(CalibDbV2_merge_V12_t));
    else if (attr.opMode == MERGE_OPMODE_MANUAL)
        memcpy(&pAmergeCtx->mergeAttrV12.stManual, &attr.stManual, sizeof(mergeAttrV12_t));

    return ret;
}

XCamReturn rk_aiq_uapi_amerge_V12_GetAttrib(RkAiqAlgoContext* ctx, mergeAttrV12_t* attr) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (ctx == NULL || attr == NULL) {
        LOGE_AMERGE("%s(%d): null pointer\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    AmergeContext_t* pAmergeCtx = (AmergeContext_t*)ctx;

    attr->opMode = pAmergeCtx->mergeAttrV12.opMode;
    memcpy(&attr->stManual, &pAmergeCtx->mergeAttrV12.stManual, sizeof(mMergeAttrV12_t));
    memcpy(&attr->CtlInfo, &pAmergeCtx->mergeAttrV12.CtlInfo, sizeof(MergeCurrCtlData_t));

    return ret;
}
#endif
