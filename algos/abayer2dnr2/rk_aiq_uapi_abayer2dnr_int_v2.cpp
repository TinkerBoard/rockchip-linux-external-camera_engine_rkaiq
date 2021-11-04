#include "abayer2dnr2/rk_aiq_uapi_abayer2dnr_int_v2.h"
#include "abayer2dnr2/rk_aiq_types_abayer2dnr_algo_prvt_v2.h"
#include "RkAiqCalibApi.h"
//#include "bayer2dnr_xml2json_v2.h"



#if 1

#define RAWNR_LUMA_TF_STRENGTH_MAX_PERCENT (100.0)
#define RAWNR_LUMA_SF_STRENGTH_MAX_PERCENT (100.0)


XCamReturn
rk_aiq_uapi_abayer2dnrV2_SetAttrib(RkAiqAlgoContext *ctx,
                                   rk_aiq_bayer2dnr_attrib_v2_t *attr,
                                   bool need_sync)
{

    Abayer2dnr_Context_V2_t* pCtx = (Abayer2dnr_Context_V2_t*)ctx;

    pCtx->eMode = attr->eMode;
    pCtx->stAuto = attr->stAuto;
    pCtx->stManual = attr->stManual;
    pCtx->isReCalculate |= 1;

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
rk_aiq_uapi_abayer2dnrV2_GetAttrib(const RkAiqAlgoContext *ctx,
                                   rk_aiq_bayer2dnr_attrib_v2_t *attr)
{

    Abayer2dnr_Context_V2_t* pCtx = (Abayer2dnr_Context_V2_t*)ctx;

    attr->eMode = pCtx->eMode;
    memcpy(&attr->stAuto, &pCtx->stAuto, sizeof(attr->stAuto));
    memcpy(&attr->stManual, &pCtx->stManual, sizeof(attr->stManual));

    return XCAM_RETURN_NO_ERROR;
}


XCamReturn
rk_aiq_uapi_abayer2dnrV2_SetStrength(const RkAiqAlgoContext *ctx,
                                     float fPercent)
{
    Abayer2dnr_Context_V2_t* pCtx = (Abayer2dnr_Context_V2_t*)ctx;

    float fStrength = 1.0f;
    float fMax = RAWNR_LUMA_SF_STRENGTH_MAX_PERCENT;


    if(fPercent <= 0.5) {
        fStrength =  fPercent / 0.5;
    } else {
        fStrength = (fPercent - 0.5) * (fMax - 1) * 2 + 1;
    }

    pCtx->fRawnr_SF_Strength = fStrength;
    pCtx->isReCalculate |= 1;

    return XCAM_RETURN_NO_ERROR;
}




XCamReturn
rk_aiq_uapi_abayer2dnrV2_GetStrength(const RkAiqAlgoContext *ctx,
                                     float *pPercent)
{
    Abayer2dnr_Context_V2_t* pCtx = (Abayer2dnr_Context_V2_t*)ctx;

    float fStrength = 1.0f;
    float fMax = RAWNR_LUMA_SF_STRENGTH_MAX_PERCENT;


    fStrength = pCtx->fRawnr_SF_Strength;

    if(fStrength <= 1) {
        *pPercent = fStrength * 0.5;
    } else {
        *pPercent = (fStrength - 1) / ((fMax - 1) * 2) + 0.5;
    }

    return XCAM_RETURN_NO_ERROR;
}



#endif

