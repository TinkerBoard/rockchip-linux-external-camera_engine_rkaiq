#include "abayertnrV23/rk_aiq_uapi_abayertnr_int_v23.h"
#include "abayertnrV23/rk_aiq_types_abayertnr_algo_prvt_v23.h"
#include "RkAiqCalibApi.h"
//#include "bayertnr_xml2json_v23.h"



#if 1

#define ABAYERTNR_LUMA_TF_STRENGTH_MAX_PERCENT (100.0)
#define ABAYERTNR_LUMA_SF_STRENGTH_MAX_PERCENT (100.0)


XCamReturn
rk_aiq_uapi_abayertnrV23_SetAttrib(RkAiqAlgoContext *ctx,
                                   rk_aiq_bayertnr_attrib_v23_t *attr,
                                   bool need_sync)
{

    Abayertnr_Context_V23_t* pCtx = (Abayertnr_Context_V23_t*)ctx;

    pCtx->eMode = attr->eMode;
    if(pCtx->eMode == ABAYERTNRV23_OP_MODE_AUTO) {
        pCtx->stAuto = attr->stAuto;
    } else if(pCtx->eMode == ABAYERTNRV23_OP_MODE_MANUAL) {
        pCtx->stManual.st3DSelect = attr->stManual.st3DSelect;
    } else if(pCtx->eMode == ABAYERTNRV23_OP_MODE_REG_MANUAL) {
        pCtx->stManual.st3DFix = attr->stManual.st3DFix;
    }
    pCtx->isReCalculate |= 1;

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
rk_aiq_uapi_abayertnrV23_GetAttrib(const RkAiqAlgoContext *ctx,
                                   rk_aiq_bayertnr_attrib_v23_t *attr)
{

    Abayertnr_Context_V23_t* pCtx = (Abayertnr_Context_V23_t*)ctx;

    attr->eMode = pCtx->eMode;
    memcpy(&attr->stAuto, &pCtx->stAuto, sizeof(attr->stAuto));
    memcpy(&attr->stManual, &pCtx->stManual, sizeof(attr->stManual));

    return XCAM_RETURN_NO_ERROR;
}


XCamReturn
rk_aiq_uapi_abayertnrV23_SetStrength(const RkAiqAlgoContext *ctx,
                                     float fPercent)
{
    Abayertnr_Context_V23_t* pCtx = (Abayertnr_Context_V23_t*)ctx;

    float fStrength = 1.0;
    float fMax = ABAYERTNR_LUMA_TF_STRENGTH_MAX_PERCENT;

    if(fPercent <= 0.5) {
        fStrength =  fPercent / 0.5;
    } else {
        if(fPercent >= 0.999999)
            fPercent = 0.999999;
        fStrength = 0.5 / (1.0 - fPercent);
    }

    pCtx->fStrength = fStrength;
    pCtx->isReCalculate |= 1;

    return XCAM_RETURN_NO_ERROR;
}




XCamReturn
rk_aiq_uapi_abayertnrV23_GetStrength(const RkAiqAlgoContext *ctx,
                                     float *pPercent)
{
    Abayertnr_Context_V23_t* pCtx = (Abayertnr_Context_V23_t*)ctx;

    float fStrength = 1.0;
    float fMax = ABAYERTNR_LUMA_TF_STRENGTH_MAX_PERCENT;

    fStrength = pCtx->fStrength;

    if(fStrength <= 1) {
        *pPercent = fStrength * 0.5;
    } else {
        float tmp = 1.0;
        tmp = 1 - 0.5 / fStrength;
        if(abs(tmp - 0.999999) < 0.000001) {
            tmp = 1.0;
        }
        *pPercent = tmp;
    }

    return XCAM_RETURN_NO_ERROR;
}


#endif

