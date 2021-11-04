#include "abayertnr2/rk_aiq_uapi_abayertnr_int_v2.h"
#include "abayertnr2/rk_aiq_types_abayertnr_algo_prvt_v2.h"
#include "RkAiqCalibApi.h"
//#include "bayertnr_xml2json_v2.h"



#if 1

#define ABAYERTNR_LUMA_TF_STRENGTH_MAX_PERCENT (100.0)
#define ABAYERTNR_LUMA_SF_STRENGTH_MAX_PERCENT (100.0)


XCamReturn
rk_aiq_uapi_abayertnrV2_SetAttrib(RkAiqAlgoContext *ctx,
                                  rk_aiq_bayertnr_attrib_v2_t *attr,
                                  bool need_sync)
{

    Abayertnr_Context_V2_t* pCtx = (Abayertnr_Context_V2_t*)ctx;

    pCtx->eMode = attr->eMode;
    pCtx->stAuto = attr->stAuto;
    pCtx->stManual = attr->stManual;
    pCtx->isReCalculate |= 1;

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
rk_aiq_uapi_abayertnrV2_GetAttrib(const RkAiqAlgoContext *ctx,
                                  rk_aiq_bayertnr_attrib_v2_t *attr)
{

    Abayertnr_Context_V2_t* pCtx = (Abayertnr_Context_V2_t*)ctx;

    attr->eMode = pCtx->eMode;
    memcpy(&attr->stAuto, &pCtx->stAuto, sizeof(attr->stAuto));
    memcpy(&attr->stManual, &pCtx->stManual, sizeof(attr->stManual));

    return XCAM_RETURN_NO_ERROR;
}


XCamReturn
rk_aiq_uapi_abayertnrV2_SetStrength(const RkAiqAlgoContext *ctx,
                                    float fPercent)
{
    Abayertnr_Context_V2_t* pCtx = (Abayertnr_Context_V2_t*)ctx;

    float fStrength = 1.0;
    float fMax = ABAYERTNR_LUMA_TF_STRENGTH_MAX_PERCENT;

    if(fPercent <= 0.5) {
        fStrength =  fPercent / 0.5;
    } else {
        fStrength = (fPercent - 0.5) * (fMax - 1) * 2 + 1;
    }

    pCtx->fStrength = fStrength;
    pCtx->isReCalculate |= 1;

    return XCAM_RETURN_NO_ERROR;
}




XCamReturn
rk_aiq_uapi_abayertnrV2_GetStrength(const RkAiqAlgoContext *ctx,
                                    float *pPercent)
{
    Abayertnr_Context_V2_t* pCtx = (Abayertnr_Context_V2_t*)ctx;

    float fStrength = 1.0;
    float fMax = ABAYERTNR_LUMA_TF_STRENGTH_MAX_PERCENT;

    fStrength = pCtx->fStrength;

    if(fStrength <= 1) {
        *pPercent = fStrength * 0.5;
    } else {
        *pPercent = (fStrength - 1) / ((fMax - 1) * 2) + 0.5;
    }

    return XCAM_RETURN_NO_ERROR;
}


#endif

