/******************************************************************************
 *
 * Copyright 2019, Fuzhou Rockchip Electronics Co.Ltd. All rights reserved.
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of:
 * Fuzhou Rockchip Electronics Co.Ltd .
 *
 *
 *****************************************************************************/
/**
 * @file rk_aiq_amerge_algo.cpp
 *
 * @brief
 *   ADD_DESCRIPTION_HERE
 *
 *****************************************************************************/
#include "math.h"
#include "rk_aiq_types_amerge_algo_int.h"
#include "rk_aiq_types_amerge_algo_prvt.h"
#include "xcam_log.h"

/******************************************************************************
 * AmergeStart()
 *****************************************************************************/
XCamReturn AmergeStart
(
    AmergeContext_t* pAmergeCtx
) {

    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    // initial checks
    if (pAmergeCtx == NULL) {
        return (XCAM_RETURN_ERROR_MEM);
    }

    if ((AMERGE_STATE_RUNNING == pAmergeCtx->state)
            || (AMERGE_STATE_LOCKED == pAmergeCtx->state)) {
        return (XCAM_RETURN_ERROR_FAILED);
    }

    pAmergeCtx->state = AMERGE_STATE_RUNNING;

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
    return (XCAM_RETURN_NO_ERROR);
}
/******************************************************************************
 * AmergeStop()
 *****************************************************************************/
XCamReturn AmergeStop
(
    AmergeContext_t* pAmergeCtx
) {

    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    // initial checks
    if (pAmergeCtx == NULL) {
        return (XCAM_RETURN_ERROR_MEM);
    }

    // before stopping, unlock the AHDR if locked
    if (AMERGE_STATE_LOCKED == pAmergeCtx->state) {
        return (XCAM_RETURN_ERROR_FAILED);
    }

    pAmergeCtx->state = AMERGE_STATE_STOPPED;

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);

    return (XCAM_RETURN_NO_ERROR);
}

/******************************************************************************
 * GetCurrPara()
 *****************************************************************************/
float GetCurrPara
(
    float           inPara,
    float*         inMatrixX,
    float*         inMatrixY,
    int Max_Knots
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);
    float x1 = 0.0f;
    float x2 = 0.0f;
    float value1 = 0.0f;
    float value2 = 0.0f;
    float outPara = 0.0f;

    if(inPara < inMatrixX[0])
        outPara = inMatrixY[0];
    else if (inPara >= inMatrixX[Max_Knots - 1])
        outPara = inMatrixY[Max_Knots - 1];
    else
        for(int i = 0; i < Max_Knots - 1; i++)
        {
            if(inPara >= inMatrixX[i] && inPara < inMatrixX[i + 1])
            {
                x1 = inMatrixX[i];
                x2 = inMatrixX[i + 1];
                value1 = inMatrixY[i];
                value2 = inMatrixY[i + 1];
                outPara = value1 + (inPara - x1) * (value1 - value2) / (x1 - x2);
                break;
            }
            else
                continue;
        }

    return outPara;
    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

void AmergeGetEnvLv
(
    AmergeContext_t*           pAmergeCtx,
    AecPreResult_t  AecHdrPreResult
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    //get Ae Pre Result
    pAmergeCtx->AeResult.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[AecHdrPreResult.NormalIndex];

    //transfer AeResult data into AhdrHandle
    switch (pAmergeCtx->FrameNumber)
    {
    case LINEAR_NUM:
        pAmergeCtx->AeResult.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[0];
        break;
    case HDR_2X_NUM:
        pAmergeCtx->AeResult.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[1];
        break;
    case HDR_3X_NUM:
        pAmergeCtx->AeResult.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[1];
        break;
    default:
        LOGE_AMERGE("%s:  Wrong frame number in HDR mode!!!\n", __FUNCTION__);
        break;
    }

    //Normalize the current envLv for AEC
    pAmergeCtx->CurrData.CtrlData.EnvLv = (pAmergeCtx->AeResult.GlobalEnvLv  - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
    pAmergeCtx->CurrData.CtrlData.EnvLv = LIMIT_VALUE(pAmergeCtx->CurrData.CtrlData.EnvLv, ENVLVMAX, ENVLVMIN);

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

void AmergeGetSensorInfo
(
    AmergeContext_t*     pAmergeCtx,
    AecProcResult_t  AecHdrProcResult
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    pAmergeCtx->SensorInfo.LongFrmMode = AecHdrProcResult.LongFrmMode && (pAmergeCtx->FrameNumber != LINEAR_NUM);

    for(int i = 0; i < 3; i++)
    {
        pAmergeCtx->SensorInfo.HdrMinGain[i] = AecHdrProcResult.HdrMinGain[i];
        pAmergeCtx->SensorInfo.HdrMaxGain[i] = AecHdrProcResult.HdrMaxGain[i];
        pAmergeCtx->SensorInfo.HdrMinIntegrationTime[i] = AecHdrProcResult.HdrMinIntegrationTime[i];
        pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[i] = AecHdrProcResult.HdrMaxIntegrationTime[i];
    }

    if(pAmergeCtx->FrameNumber == HDR_2X_NUM) {
        pAmergeCtx->SensorInfo.MaxExpoL = pAmergeCtx->SensorInfo.HdrMaxGain[1] * pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[1];
        pAmergeCtx->SensorInfo.MinExpoL = pAmergeCtx->SensorInfo.HdrMinGain[1] * pAmergeCtx->SensorInfo.HdrMinIntegrationTime[1];
        pAmergeCtx->SensorInfo.MaxExpoM = 0;
        pAmergeCtx->SensorInfo.MinExpoM = 0;
    }
    else if(pAmergeCtx->FrameNumber == HDR_3X_NUM)
    {
        pAmergeCtx->SensorInfo.MaxExpoL = pAmergeCtx->SensorInfo.HdrMaxGain[2] * pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[2];
        pAmergeCtx->SensorInfo.MinExpoL = pAmergeCtx->SensorInfo.HdrMinGain[2] * pAmergeCtx->SensorInfo.HdrMinIntegrationTime[2];
        pAmergeCtx->SensorInfo.MaxExpoM = pAmergeCtx->SensorInfo.HdrMaxGain[1] * pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[1];
        pAmergeCtx->SensorInfo.MinExpoM = pAmergeCtx->SensorInfo.HdrMinGain[1] * pAmergeCtx->SensorInfo.HdrMinIntegrationTime[1];
    }

    pAmergeCtx->SensorInfo.MaxExpoS = pAmergeCtx->SensorInfo.HdrMaxGain[0] * pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[0];
    pAmergeCtx->SensorInfo.MinExpoS = pAmergeCtx->SensorInfo.HdrMinGain[0] * pAmergeCtx->SensorInfo.HdrMinIntegrationTime[0];

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeIQUpdate()
 *
 *****************************************************************************/
void AmergeIQUpdate(AmergeContext_t*     pAmergeCtx)
{
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    if(pAmergeCtx->ConfigV2.BaseFrm == BASEFRAME_LONG) {
        //get Current merge OECurve
        pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->ConfigV2.LongFrmEnvLv, pAmergeCtx->ConfigV2.LongFrmOECurve_smooth, pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots);
        pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->ConfigV2.LongFrmEnvLv, pAmergeCtx->ConfigV2.LongFrmOECurve_offset, pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots);

        //get Current merge MDCurve
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->ConfigV2.LongFrmMoveCoef, pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth, pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots);
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->ConfigV2.LongFrmMoveCoef, pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset, pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots);
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->ConfigV2.LongFrmMoveCoef, pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth, pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots);
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->ConfigV2.LongFrmMoveCoef, pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset, pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots);

        pAmergeCtx->CurrData.CtrlData.MergeOEDamp = pAmergeCtx->ConfigV2.LongFrmOECurve_damp;
        pAmergeCtx->CurrData.CtrlData.MergeMDDampLM = pAmergeCtx->ConfigV2.LongFrmMDCurveLM_damp;
        pAmergeCtx->CurrData.CtrlData.MergeMDDampMS = pAmergeCtx->ConfigV2.LongFrmMDCurveMS_damp;
    }
    else if(pAmergeCtx->ConfigV2.BaseFrm == BASEFRAME_SHORT) {
        //get Current merge OECurve
        pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->ConfigV2.ShortFrmEnvLv, pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth, pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots);
        pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->ConfigV2.ShortFrmEnvLv, pAmergeCtx->ConfigV2.ShortFrmOECurve_offset, pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots);

        //get Current merge MDCurve
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_Coef = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->ConfigV2.ShortFrmMoveCoef, pAmergeCtx->ConfigV2.ShortFrmMDCurve_Coef, pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots);
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_ms_thd0 = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->ConfigV2.ShortFrmMoveCoef, pAmergeCtx->ConfigV2.ShortFrmMDCurve_ms_thd0, pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots);
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_lm_thd0 = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->ConfigV2.ShortFrmMoveCoef, pAmergeCtx->ConfigV2.ShortFrmMDCurve_lm_thd0, pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots);

        pAmergeCtx->CurrData.CtrlData.MergeOEDamp = pAmergeCtx->ConfigV2.ShortFrmOECurve_damp;
        pAmergeCtx->CurrData.CtrlData.MergeMDDampLM = pAmergeCtx->ConfigV2.ShortFrmMDCurve_damp;
        pAmergeCtx->CurrData.CtrlData.MergeMDDampMS = pAmergeCtx->ConfigV2.ShortFrmMDCurve_damp;
    }

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergePrepareJsonUpdateConfigV2()
 *transfer html parameter into handle
 ***************************************************************************/
void AmergePrepareJsonUpdateConfigV2
(
    AmergeContext_t*           pAmergeCtx
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAmergeCtx != NULL);

    pAmergeCtx->ConfigV2.BaseFrm = pAmergeCtx->CalibDBV2.MergeTuningPara.BaseFrm;
    pAmergeCtx->ConfigV2.ByPassThr = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ByPassThr, DAMPMAX, DAMPMIN);

    //long frm mode para
    pAmergeCtx->ConfigV2.LongFrmOECurve_damp = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.OECurve_damp, DAMPMAX, DAMPMIN);
    pAmergeCtx->ConfigV2.LongFrmMDCurveLM_damp = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.MDCurveLM_damp, DAMPMAX, DAMPMIN);
    pAmergeCtx->ConfigV2.LongFrmMDCurveMS_damp = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.MDCurveMS_damp, DAMPMAX, DAMPMIN);
    for (int i = 0; i < pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots; i++ ) {
        pAmergeCtx->ConfigV2.LongFrmEnvLv[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.OECurve.EnvLv[i], ENVLVMAX, ENVLVMIN);
        pAmergeCtx->ConfigV2.LongFrmOECurve_smooth[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.OECurve.Smooth[i], IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.LongFrmOECurve_offset[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.OECurve.Offset[i], OECURVEOFFSETMAX, OECURVEOFFSETMIN);
    }
    for (int i = 0; i < pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots; i++ ) {
        pAmergeCtx->ConfigV2.LongFrmMoveCoef[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef[i], MOVECOEFMAX, MOVECOEFMIN);
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.MDCurve.LM_smooth[i], IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.MDCurve.LM_offset[i], IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.MDCurve.MS_smooth[i], IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.MDCurve.MS_offset[i], IQPARAMAX, IQPARAMIN);
    }
    //short frm mode para
    pAmergeCtx->ConfigV2.ShortFrmOECurve_damp = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.OECurve_damp, DAMPMAX, DAMPMIN);
    pAmergeCtx->ConfigV2.ShortFrmMDCurve_damp = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.MDCurve_damp, DAMPMAX, DAMPMIN);
    for (int i = 0; i < pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots; i++ ) {
        pAmergeCtx->ConfigV2.ShortFrmEnvLv[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.OECurve.EnvLv[i], ENVLVMAX, ENVLVMIN);
        pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.OECurve.Smooth[i], IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.ShortFrmOECurve_offset[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.OECurve.Offset[i], OECURVEOFFSETMAX, OECURVEOFFSETMIN);
    }
    for (int i = 0; i < pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots; i++ ) {
        pAmergeCtx->ConfigV2.ShortFrmMoveCoef[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef[i], MOVECOEFMAX, MOVECOEFMIN);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_Coef[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.MDCurve.Coef[i], IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_ms_thd0[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.MDCurve.ms_thd0[i], IQ_TH0_PARAMAX, IQ_TH0_PARAMIN);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_lm_thd0[i] = LIMIT_VALUE(pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.MDCurve.lm_thd0[i], IQ_TH0_PARAMAX, IQ_TH0_PARAMIN);
    }

    //turn the IQ paras into algo paras
    for(int i = 0; i < pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots; i++) {
        pAmergeCtx->ConfigV2.LongFrmOECurve_smooth[i] *= OECURVESMOOTHMAX;
        pAmergeCtx->ConfigV2.LongFrmOECurve_smooth[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmOECurve_smooth[i], OECURVESMOOTHMAX, OECURVESMOOTHMIN) ;
    }
    for(int i = 0; i < pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots; i++)
    {
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth[i] *= MDCURVESMOOTHMAX;
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth[i], MDCURVESMOOTHMAX, MDCURVESMOOTHMIN) ;
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset[i] *= MDCURVEOFFSETMAX;
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset[i], MDCURVEOFFSETMAX, MDCURVEOFFSETMIN) ;

        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth[i] *= MDCURVESMOOTHMAX;
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth[i], MDCURVESMOOTHMAX, MDCURVESMOOTHMIN) ;
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset[i] *= MDCURVEOFFSETMAX;
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset[i], MDCURVEOFFSETMAX, MDCURVEOFFSETMIN) ;
    }
    for(int i = 0; i < pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots; i++) {
        pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth[i] *= OECURVESMOOTHMAX;
        pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth[i], OECURVESMOOTHMAX, OECURVESMOOTHMIN) ;
    }

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * MergePrepareJsonMallocAndUpdateConfig()
 ***************************************************************************/
void MergePrepareJsonMallocAndUpdateConfig
(
    AmergeContext_t*        pAmergeCtx
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAmergeCtx != NULL);

    int New_Long_OECurve_EnvLv_len = pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.OECurve.EnvLv_len;
    int New_Long_MDCurve_MoveCoef_len = pAmergeCtx->CalibDBV2.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef_len;
    int New_Short_OECurve_EnvLv_len = pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.OECurve.EnvLv_len;
    int New_Short_MDCurve_MoveCoef_len = pAmergeCtx->CalibDBV2.MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef_len;

    //long frm mode
    LOG1_AMERGE( "%s: Pre MaxEnvLvKnots:%d Cur MaxEnvLvKnots:%d\n", __FUNCTION__,
                 pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots, New_Long_OECurve_EnvLv_len);
    LOG1_AMERGE( "%s: Pre MaxMoveCoefKnots:%d Cur MaxMoveCoefKnots:%d\n", __FUNCTION__,
                 pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots, New_Long_MDCurve_MoveCoef_len);

    if(pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots != New_Long_OECurve_EnvLv_len) {
        free(pAmergeCtx->ConfigV2.LongFrmEnvLv);
        free(pAmergeCtx->ConfigV2.LongFrmOECurve_smooth);
        free(pAmergeCtx->ConfigV2.LongFrmOECurve_offset);
        pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots = New_Long_OECurve_EnvLv_len;
        pAmergeCtx->ConfigV2.LongFrmEnvLv = (float*)malloc(sizeof(float) * (New_Long_OECurve_EnvLv_len));
        pAmergeCtx->ConfigV2.LongFrmOECurve_smooth = (float*)malloc(sizeof(float) * (New_Long_OECurve_EnvLv_len));
        pAmergeCtx->ConfigV2.LongFrmOECurve_offset = (float*)malloc(sizeof(float) * (New_Long_OECurve_EnvLv_len));
    }
    if(pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots != New_Long_MDCurve_MoveCoef_len) {
        free(pAmergeCtx->ConfigV2.LongFrmMoveCoef);
        free(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth);
        free(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset);
        free(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth);
        free(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset);
        pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots = New_Long_MDCurve_MoveCoef_len;
        pAmergeCtx->ConfigV2.LongFrmMoveCoef = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
    }

    //short frm mode
    LOG1_AMERGE( "%s: Pre MaxEnvLvKnots:%d Cur MaxEnvLvKnots:%d\n", __FUNCTION__,
                 pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots, New_Short_OECurve_EnvLv_len);
    LOG1_AMERGE( "%s: Pre MaxMoveCoefKnots:%d Cur MaxMoveCoefKnots:%d\n", __FUNCTION__,
                 pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots, New_Short_MDCurve_MoveCoef_len);

    if(pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots != New_Short_OECurve_EnvLv_len) {
        free(pAmergeCtx->ConfigV2.ShortFrmEnvLv);
        free(pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth);
        free(pAmergeCtx->ConfigV2.ShortFrmOECurve_offset);
        pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots = New_Short_OECurve_EnvLv_len;
        pAmergeCtx->ConfigV2.ShortFrmEnvLv = (float*)malloc(sizeof(float) * New_Short_OECurve_EnvLv_len);
        pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth = (float*)malloc(sizeof(float) * New_Short_OECurve_EnvLv_len);
        pAmergeCtx->ConfigV2.ShortFrmOECurve_offset = (float*)malloc(sizeof(float) * New_Short_OECurve_EnvLv_len);
    }
    if(pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots != New_Short_MDCurve_MoveCoef_len) {
        free(pAmergeCtx->ConfigV2.ShortFrmMoveCoef);
        free(pAmergeCtx->ConfigV2.ShortFrmMDCurve_Coef);
        free(pAmergeCtx->ConfigV2.ShortFrmMDCurve_ms_thd0);
        free(pAmergeCtx->ConfigV2.ShortFrmMDCurve_lm_thd0);
        pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots = New_Short_MDCurve_MoveCoef_len;
        pAmergeCtx->ConfigV2.ShortFrmMoveCoef = (float*)malloc(sizeof(float) * New_Short_MDCurve_MoveCoef_len);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_Coef = (float*)malloc(sizeof(float) * New_Short_MDCurve_MoveCoef_len);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_ms_thd0 = (float*)malloc(sizeof(float) * New_Short_MDCurve_MoveCoef_len);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_lm_thd0 = (float*)malloc(sizeof(float) * New_Short_MDCurve_MoveCoef_len);
    }

    AmergePrepareJsonUpdateConfigV2(pAmergeCtx);

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeProcApiUpdateConfigV2()
 *transfer api parameter into handle
 ***************************************************************************/
void AmergeProcApiUpdateConfigV2
(
    AmergeContext_t*           pAmergeCtx
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAmergeCtx != NULL);

    pAmergeCtx->ConfigV2.BaseFrm = pAmergeCtx->mergeAttr.attrV30.stManual.BaseFrm;
    pAmergeCtx->ConfigV2.ByPassThr = DAMPMIN;

    //long frm mode para
    pAmergeCtx->ConfigV2.LongFrmOECurve_damp = DAMPMIN;
    pAmergeCtx->ConfigV2.LongFrmMDCurveLM_damp = DAMPMIN;
    pAmergeCtx->ConfigV2.LongFrmMDCurveMS_damp = DAMPMIN;
    for (int i = 0; i < pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots; i++ ) {
        pAmergeCtx->ConfigV2.LongFrmEnvLv[i] = ENVLVMIN;
        pAmergeCtx->ConfigV2.LongFrmOECurve_smooth[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.OECurve.Smooth, IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.LongFrmOECurve_offset[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.OECurve.Offset, OECURVEOFFSETMAX, OECURVEOFFSETMIN);
    }
    for (int i = 0; i < pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots; i++ ) {
        pAmergeCtx->ConfigV2.LongFrmMoveCoef[i] = MOVECOEFMIN;
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.MDCurve.LM_smooth, IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.MDCurve.LM_offset, IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.MDCurve.MS_smooth, IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.MDCurve.MS_offset, IQPARAMAX, IQPARAMIN);
    }
    //short frm mode para
    pAmergeCtx->ConfigV2.ShortFrmOECurve_damp = DAMPMIN;
    pAmergeCtx->ConfigV2.ShortFrmMDCurve_damp = DAMPMIN;
    for (int i = 0; i < pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots; i++ ) {
        pAmergeCtx->ConfigV2.ShortFrmEnvLv[i] = ENVLVMIN;
        pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.OECurve.Smooth, IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.ShortFrmOECurve_offset[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.OECurve.Offset, OECURVEOFFSETMAX, OECURVEOFFSETMIN);
    }
    for (int i = 0; i < pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots; i++ ) {
        pAmergeCtx->ConfigV2.ShortFrmMoveCoef[i] = MOVECOEFMIN;
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_Coef[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.MDCurve.Coef, IQPARAMAX, IQPARAMIN);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_ms_thd0[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.MDCurve.ms_thd0, IQ_TH0_PARAMAX, IQ_TH0_PARAMIN);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_lm_thd0[i] = LIMIT_VALUE(pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.MDCurve.lm_thd0, IQ_TH0_PARAMAX, IQ_TH0_PARAMIN);
    }

    //turn the IQ paras into algo paras
    for(int i = 0; i < pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots; i++) {
        pAmergeCtx->ConfigV2.LongFrmOECurve_smooth[i] *= OECURVESMOOTHMAX;
        pAmergeCtx->ConfigV2.LongFrmOECurve_smooth[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmOECurve_smooth[i], OECURVESMOOTHMAX, OECURVESMOOTHMIN) ;
    }
    for(int i = 0; i < pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots; i++)
    {
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth[i] *= MDCURVESMOOTHMAX;
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth[i], MDCURVESMOOTHMAX, MDCURVESMOOTHMIN) ;
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset[i] *= MDCURVEOFFSETMAX;
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset[i], MDCURVEOFFSETMAX, MDCURVEOFFSETMIN) ;

        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth[i] *= MDCURVESMOOTHMAX;
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth[i], MDCURVESMOOTHMAX, MDCURVESMOOTHMIN) ;
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset[i] *= MDCURVEOFFSETMAX;
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset[i], MDCURVEOFFSETMAX, MDCURVEOFFSETMIN) ;
    }
    for(int i = 0; i < pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots; i++) {
        pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth[i] *= OECURVESMOOTHMAX;
        pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth[i] = LIMIT_VALUE(pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth[i], OECURVESMOOTHMAX, OECURVESMOOTHMIN) ;
    }

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * MergeProcApiMallocAndUpdateConfig()
 ***************************************************************************/
void MergeProcApiMallocAndUpdateConfig
(
    AmergeContext_t* pAmergeCtx
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAmergeCtx->ConfigV2 != NULL);

    int New_Long_OECurve_EnvLv_len = 1;
    int New_Long_MDCurve_MoveCoef_len = 1;
    int New_Short_OECurve_EnvLv_len = 1;
    int New_Short_MDCurve_MoveCoef_len = 1;

    //long frm mode
    LOG1_AMERGE( "%s: Pre MaxEnvLvKnots:%d Cur MaxEnvLvKnots:%d\n", __FUNCTION__,
                 pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots, New_Long_OECurve_EnvLv_len);
    LOG1_AMERGE( "%s: Pre MaxMoveCoefKnots:%d Cur MaxMoveCoefKnots:%d\n", __FUNCTION__,
                 pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots, New_Long_MDCurve_MoveCoef_len);

    if(pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots != New_Long_OECurve_EnvLv_len) {
        free(pAmergeCtx->ConfigV2.LongFrmEnvLv);
        free(pAmergeCtx->ConfigV2.LongFrmOECurve_smooth);
        free(pAmergeCtx->ConfigV2.LongFrmOECurve_offset);
        pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots = New_Long_OECurve_EnvLv_len;
        pAmergeCtx->ConfigV2.LongFrmEnvLv = (float*)malloc(sizeof(float) * (New_Long_OECurve_EnvLv_len));
        pAmergeCtx->ConfigV2.LongFrmOECurve_smooth = (float*)malloc(sizeof(float) * (New_Long_OECurve_EnvLv_len));
        pAmergeCtx->ConfigV2.LongFrmOECurve_offset = (float*)malloc(sizeof(float) * (New_Long_OECurve_EnvLv_len));
    }
    if(pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots != New_Long_MDCurve_MoveCoef_len) {
        free(pAmergeCtx->ConfigV2.LongFrmMoveCoef);
        free(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth);
        free(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset);
        free(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth);
        free(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset);
        pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots = New_Long_MDCurve_MoveCoef_len;
        pAmergeCtx->ConfigV2.LongFrmMoveCoef = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
        pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
        pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset = (float*)malloc(sizeof(float) * (New_Long_MDCurve_MoveCoef_len));
    }

    //short frm mode
    LOG1_AMERGE( "%s: Pre MaxEnvLvKnots:%d Cur MaxEnvLvKnots:%d\n", __FUNCTION__,
                 pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots, New_Short_OECurve_EnvLv_len);
    LOG1_AMERGE( "%s: Pre MaxMoveCoefKnots:%d Cur MaxMoveCoefKnots:%d\n", __FUNCTION__,
                 pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots, New_Short_MDCurve_MoveCoef_len);

    if(pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots != New_Short_OECurve_EnvLv_len) {
        free(pAmergeCtx->ConfigV2.ShortFrmEnvLv);
        free(pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth);
        free(pAmergeCtx->ConfigV2.ShortFrmOECurve_offset);
        pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots = New_Short_OECurve_EnvLv_len;
        pAmergeCtx->ConfigV2.ShortFrmEnvLv = (float*)malloc(sizeof(float) * New_Short_OECurve_EnvLv_len);
        pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth = (float*)malloc(sizeof(float) * New_Short_OECurve_EnvLv_len);
        pAmergeCtx->ConfigV2.ShortFrmOECurve_offset = (float*)malloc(sizeof(float) * New_Short_OECurve_EnvLv_len);
    }
    if(pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots != New_Short_MDCurve_MoveCoef_len) {
        free(pAmergeCtx->ConfigV2.ShortFrmMoveCoef);
        free(pAmergeCtx->ConfigV2.ShortFrmMDCurve_Coef);
        free(pAmergeCtx->ConfigV2.ShortFrmMDCurve_ms_thd0);
        free(pAmergeCtx->ConfigV2.ShortFrmMDCurve_lm_thd0);
        pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots = New_Short_MDCurve_MoveCoef_len;
        pAmergeCtx->ConfigV2.ShortFrmMoveCoef = (float*)malloc(sizeof(float) * New_Short_MDCurve_MoveCoef_len);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_Coef = (float*)malloc(sizeof(float) * New_Short_MDCurve_MoveCoef_len);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_ms_thd0 = (float*)malloc(sizeof(float) * New_Short_MDCurve_MoveCoef_len);
        pAmergeCtx->ConfigV2.ShortFrmMDCurve_lm_thd0 = (float*)malloc(sizeof(float) * New_Short_MDCurve_MoveCoef_len);
    }

    AmergeProcApiUpdateConfigV2(pAmergeCtx);

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
* CalibrateOECurve()
*****************************************************************************/
void CalibrateOECurve
(
    float smooth, float offset, unsigned short *OECurve
)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    int step = 32 ;
    float curve = 0.0;
    float k = 511;

    for(int i = 0; i < ISP20_HDRMGE_OE_CURVE_NUM; ++i)
    {
        curve = 1 + exp(-smooth * (k / 1023 - offset / 256));
        curve = 1024 / curve ;
        OECurve[i] = round(curve) ;
        OECurve[i] = MIN(OECurve[i], 1023);
        k += step ;
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}
/******************************************************************************
* CalibrateMDCurveLongFrmMode()
*****************************************************************************/
void CalibrateMDCurveLongFrmMode
(
    float smooth, float offset, unsigned short *MDCurve
)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    int step = 16;
    float curve = 0.0;
    float k = 0;

    for (int i = 0; i < ISP20_HDRMGE_MD_CURVE_NUM; ++i)
    {
        curve = 1 + exp(-smooth * (k / 1023 - offset / 256));
        curve = 1024 / curve ;
        MDCurve[i] = round(curve) ;
        MDCurve[i] = MIN(MDCurve[i], 1023);
        k += step ;
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}
/******************************************************************************
* CalibrateMDCurveShortFrmMode()
*****************************************************************************/
void CalibrateMDCurveShortFrmMode
(
    float smooth, float offset, unsigned short *MDCurveLM, unsigned short *MDCurveMS
)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    float step = 1.0 / 16.0;
    float curve = 0.0;

    for (int i = 0; i < ISP3X_HDRMGE_MD_CURVE_NUM; ++i)
    {
        curve = 0.01 + pow(i * step, 2.0f);
        curve =  1024.0 * pow(i * step, 2.0f) / curve ;
        MDCurveLM[i] = round(curve) ;
        MDCurveLM[i] = MIN(MDCurveLM[i], 1023);
        MDCurveMS[i] = MDCurveLM[i];
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}
/******************************************************************************
 * AmergeGetTuningProcResV30()
 *****************************************************************************/
void AmergeGetTuningProcResV30
(
    AmergeContext_t* pAmergeCtx
)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_mode = pAmergeCtx->CurrData.HandleData.Merge_v30.MergeMode;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_s_base = pAmergeCtx->ConfigV2.BaseFrm;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_dif_0p9 = SW_HDRMGE_LM_DIF_0P9_FIX;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_dif_0p8 = SW_HDRMGE_MS_DIF_0P8_FIX;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_dif_0p15 = (int)pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_offset;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_dif_0p15 = (int)pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_offset;


    CalibrateOECurve(pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_smooth,
                     pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_offset, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y);
    if(pAmergeCtx->ConfigV2.BaseFrm == BASEFRAME_LONG) {
        CalibrateMDCurveLongFrmMode(pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_smooth,
                                    pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_offset, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y);
        CalibrateMDCurveLongFrmMode(pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_smooth,
                                    pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_offset, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y);
    }
    else if(pAmergeCtx->ConfigV2.BaseFrm == BASEFRAME_SHORT)
        CalibrateMDCurveShortFrmMode(pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_smooth, pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_offset,
                                     pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y);

    if(pAmergeCtx->SensorInfo.LongFrmMode) {
        for(int i = 0; i < ISP3X_HDRMGE_OE_CURVE_NUM; i++)
            pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[i] = HDR_LONG_FRMAE_MODE_OECURVE;
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * MergeDamping()
 *****************************************************************************/
void MergeDamping
(
    AmergeContext_t* pAmergeCtx
)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    float OEDamp = pAmergeCtx->CurrData.CtrlData.MergeOEDamp;
    float MDDampLM = pAmergeCtx->CurrData.CtrlData.MergeMDDampLM;
    float MDDampMS = pAmergeCtx->CurrData.CtrlData.MergeMDDampMS;
    bool ifHDRModeChange = false;

    ifHDRModeChange = pAmergeCtx->CurrData.HandleData.Merge_v30.MergeMode == pAmergeCtx->PrevData.HandleData.Merge_v30.MergeMode ? false : true;

    //get finnal current data
    if (pAmergeCtx->mergeAttr.attrV30.opMode == MERGE_OPMODE_API_OFF && pAmergeCtx->frameCnt != 0 && !ifHDRModeChange)
    {
        pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_smooth = OEDamp * pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_smooth
                + (1 - OEDamp) * pAmergeCtx->PrevData.HandleData.Merge_v30.OECurve_smooth;
        pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_offset = OEDamp * pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_offset
                + (1 - OEDamp) * pAmergeCtx->PrevData.HandleData.Merge_v30.OECurve_offset;
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_smooth = MDDampLM * pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_smooth
                + (1 - MDDampLM) * pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurveLM_smooth;
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_offset = MDDampLM * pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_offset
                + (1 - MDDampLM) * pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurveLM_offset;
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_smooth = MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_smooth
                + (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurveMS_smooth;
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_offset = MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_offset
                + (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurveMS_offset;

        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_Coef = MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_Coef
                + (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurve_Coef;
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_ms_thd0 = MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_ms_thd0
                + (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurve_ms_thd0;
        pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_lm_thd0 = MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_lm_thd0
                + (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurve_lm_thd0;
    }

    LOGD_AMERGE("%s: Current BaseFrm:%d OECurve_smooth:%f OECurve_offset:%f \n", __FUNCTION__, pAmergeCtx->ConfigV2.BaseFrm,
                pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_smooth, pAmergeCtx->CurrData.HandleData.Merge_v30.OECurve_offset);
    if(pAmergeCtx->ConfigV2.BaseFrm == BASEFRAME_LONG)
        LOGD_AMERGE("%s: Current MDCurveMS_smooth:%f MDCurveMS_offset:%f MDCurveLM_smooth:%f MDCurveLM_offset:%f \n", __FUNCTION__,
                    pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_smooth, pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveMS_offset,
                    pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_smooth, pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurveLM_offset);
    else if(pAmergeCtx->ConfigV2.BaseFrm == BASEFRAME_SHORT)
        LOGD_AMERGE("%s: Current MDCurve_Coef:%f MDCurve_ms_thd0:%f MDCurve_lm_thd0:%f\n", __FUNCTION__,
                    pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_Coef, pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_ms_thd0,
                    pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_lm_thd0);

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeTuningProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
void AmergeTuningProcessing
(
    AmergeContext_t*     pAmergeCtx
)
{
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    AmergeIQUpdate(pAmergeCtx);

    //transfer data to api
    //transfer control data to api
    pAmergeCtx->mergeAttr.attrV30.CtlInfo.Envlv = pAmergeCtx->CurrData.CtrlData.EnvLv;
    pAmergeCtx->mergeAttr.attrV30.CtlInfo.MoveCoef = pAmergeCtx->CurrData.CtrlData.MoveCoef;

    //merge damp
    MergeDamping(pAmergeCtx);

    //get current IO data
    AmergeGetTuningProcResV30(pAmergeCtx);

    // store current handle data to pre data for next loop
    pAmergeCtx->PrevData.CtrlData.EnvLv = pAmergeCtx->CurrData.CtrlData.EnvLv;
    pAmergeCtx->PrevData.CtrlData.MoveCoef = pAmergeCtx->CurrData.CtrlData.MoveCoef;
    memcpy(&pAmergeCtx->PrevData.HandleData, &pAmergeCtx->CurrData.HandleData, sizeof(MergeHandleData_s));

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeExpoProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
void AmergeExpoProcessing
(
    AmergeContext_t*     pAmergeCtx,
    MergeExpoData_t*      pExpoData
)
{
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    //get sw_hdrmge_gain0
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0 = (int)(64 * pExpoData->nextRatioLS);
    if(pExpoData->nextRatioLS == 1)
        pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0_inv = (int)(4096 * (1 / pExpoData->nextRatioLS) - 1);
    else
        pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0_inv = (int)(4096 * (1 / pExpoData->nextRatioLS));

    //get sw_hdrmge_gain1
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1 = (int)(64 * pExpoData->nextRatioLM);
    if(pExpoData->nextRatioLM == 1)
        pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1_inv = (int)(4096 * (1 / pExpoData->nextRatioLM) - 1);
    else
        pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1_inv = (int)(4096 * (1 / pExpoData->nextRatioLM));

    //get sw_hdrmge_gain2
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain2 = SW_HDRMGE_GAIN_FIX;

    //isp30 add
    float Coef = pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_Coef / SHORT_MODE_COEF_MAX;
    float sw_hdrmge_ms_thd0 = pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_ms_thd0;
    float sw_hdrmge_lm_thd0 = pAmergeCtx->CurrData.HandleData.Merge_v30.MDCurve_lm_thd0;
    float sw_hdrmge_ms_thd1 = 1024 * pow(100 * Coef * pExpoData->nextSGain, 0.5f);
    float sw_hdrmge_lm_thd1 = 1024 * pow(100 * Coef * pExpoData->nextMGain, 0.5f);
    float sw_hdrmge_ms_scl = (sw_hdrmge_ms_thd1 == sw_hdrmge_ms_thd0) ? 0 : (1 / (sw_hdrmge_ms_thd1 - sw_hdrmge_ms_thd0));
    float sw_hdrmge_lm_scl = (sw_hdrmge_lm_thd1 == sw_hdrmge_lm_thd0) ? 0 : (1 / (sw_hdrmge_lm_thd1 - sw_hdrmge_lm_thd0));
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_thd0 = (int)(1024 * sw_hdrmge_ms_thd0);
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_thd1 = (int)(1024 * sw_hdrmge_ms_thd1);
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_scl = (int)(64 * sw_hdrmge_ms_scl);
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_thd0 = (int)(1024 * sw_hdrmge_lm_thd0);
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_thd1 = (int)(1024 * sw_hdrmge_lm_thd1);
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_scl = (int)(64 * sw_hdrmge_lm_scl);

    LOGV_AMERGE("%s: sw_hdrmge_mode:%d sw_hdrmge_ms_dif_0p8:%d sw_hdrmge_lm_dif_0p9:%d sw_hdrmge_ms_dif_0p15:%d sw_hdrmge_lm_dif_0p15:%d\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_mode, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_dif_0p8,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_dif_0p9, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_dif_0p15,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_dif_0p15);
    LOGV_AMERGE( "%s: nextRatioLS:%f sw_hdrmge_gain0:%d sw_hdrmge_gain0_inv:%d nextRatioLM:%f sw_hdrmge_gain1:%d sw_hdrmge_gain1_inv:%d sw_hdrmge_gain2:%d\n", __FUNCTION__,
                 pExpoData->nextRatioLS, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0_inv, pExpoData->nextRatioLM,
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1_inv, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain2);
    LOGV_AMERGE( "%s: sw_hdrmge_ms_thd0:%d sw_hdrmge_ms_thd1:%d sw_hdrmge_ms_scl:%d\n", __FUNCTION__,
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_thd0, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_thd1, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_scl);
    LOGV_AMERGE( "%s: sw_hdrmge_lm_thd0:%d sw_hdrmge_lm_thd1:%d sw_hdrmge_lm_scl:%d\n", __FUNCTION__,
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_thd0, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_thd1, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_scl);
    LOGV_AMERGE("%s: sw_hdrmge_e_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[0], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[1],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[2], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[3],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[4], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[5],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[6], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[7],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[8], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[9],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[10], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[11],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[12], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[13],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[14], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[15],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[16]);
    LOGV_AMERGE("%s: sw_hdrmge_l0_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[0], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[1],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[2], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[3],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[4], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[5],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[6], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[7],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[8], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[9],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[10], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[11],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[12], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[13],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[14], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[15],
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[16]);
    LOGV_AMERGE( "%s: sw_hdrmge_l1_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", __FUNCTION__,
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[0], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[1],
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[2], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[3],
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[4], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[5],
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[6], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[7],
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[8], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[9],
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[10], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[11],
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[12], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[13],
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[14], pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[15],
                 pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[16]);

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeByPassProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
bool AmergeByPassProcessing
(
    AmergeContext_t*     pAmergeCtx,
    AecPreResult_t  AecHdrPreResult
)
{
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    bool bypass = false;
    float diff = 0.0;

    merge_OpModeV21_t ApiMode = MERGE_OPMODE_API_OFF;
    ApiMode = pAmergeCtx->mergeAttr.attrV30.opMode;

    if(pAmergeCtx->frameCnt <= 2) //start frame
        bypass = false;
    else if(ApiMode > MERGE_OPMODE_API_OFF)//api
        bypass = false;
    else if(ApiMode != pAmergeCtx->PrevData.CtrlData.ApiMode)//api change
        bypass = false;
    else { //EvnLv change
        //get Current hdr mode
        float ByPassThr = 0.0;
        pAmergeCtx->CurrData.HandleData.Merge_v30.MergeMode = pAmergeCtx->FrameNumber - 1;
        LOG1_AMERGE("%s:  Current MergeMode: %d \n", __FUNCTION__, pAmergeCtx->CurrData.HandleData.Merge_v30.MergeMode);
        ByPassThr = pAmergeCtx->ConfigV2.ByPassThr;

        //get envlv from AecPreRes
        AmergeGetEnvLv(pAmergeCtx, AecHdrPreResult);
        pAmergeCtx->CurrData.CtrlData.EnvLv = LIMIT_VALUE(pAmergeCtx->CurrData.CtrlData.EnvLv, ENVLVMAX, ENVLVMIN);

        pAmergeCtx->CurrData.CtrlData.MoveCoef = MOVE_COEF_DEFAULT;
        pAmergeCtx->CurrData.CtrlData.MoveCoef = LIMIT_VALUE(pAmergeCtx->CurrData.CtrlData.MoveCoef, MOVECOEFMAX, MOVECOEFMIN);

        //use Envlv for now
        diff = pAmergeCtx->PrevData.CtrlData.EnvLv - pAmergeCtx->CurrData.CtrlData.EnvLv;
        if(pAmergeCtx->PrevData.CtrlData.EnvLv == 0.0) {
            diff = pAmergeCtx->CurrData.CtrlData.EnvLv;
            if(diff == 0.0)
                bypass = true;
            else
                bypass = false;
        }
        else {
            diff /= pAmergeCtx->PrevData.CtrlData.EnvLv;
            if(diff >= ByPassThr || diff <= (0 - ByPassThr))
                bypass = false;
            else
                bypass = true;
        }
    }

    LOGD_AMERGE( "%s: FrameID:%d HDRFrameNum:%d LongFrmMode:%d MergeApiMode:%d EnvLv:%f MoveCoef:%f bypass:%d\n", __FUNCTION__, pAmergeCtx->frameCnt, pAmergeCtx->FrameNumber,
                 pAmergeCtx->SensorInfo.LongFrmMode, ApiMode, pAmergeCtx->CurrData.CtrlData.EnvLv, pAmergeCtx->CurrData.CtrlData.MoveCoef, bypass);

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
    return bypass;
}

/******************************************************************************
 * AmergeInit()
 *****************************************************************************/
XCamReturn AmergeInit
(
    AmergeContext_t **ppAmergeCtx,
    CamCalibDbV2Context_t* pCalibV2
) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    XCamReturn result = XCAM_RETURN_NO_ERROR;

    AmergeContext_t * pAmergeCtx;
    pAmergeCtx = (AmergeContext_t *)malloc(sizeof(AmergeContext_t));
    if(pAmergeCtx == NULL) {
        LOGE_ATMO("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_MEM;
    }

    memset(pAmergeCtx, 0x00, sizeof(AmergeContext_t));
    *ppAmergeCtx = pAmergeCtx;
    pAmergeCtx->state = AMERGE_STATE_INITIALIZED;

    CalibDbV2_merge_V2_t* calibv2_amerge_calib =
        (CalibDbV2_merge_V2_t*)(CALIBDBV2_GET_MODULE_PTR(pCalibV2, amerge_calib));

    memcpy(&pAmergeCtx->CalibDBV2, calibv2_amerge_calib, sizeof(CalibDbV2_merge_V2_t));//load iq paras

    //malloc long frm mode
    pAmergeCtx->ConfigV2.LongFrmMaxEnvLvKnots = calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.OECurve.EnvLv_len;
    pAmergeCtx->ConfigV2.LongFrmMaxMoveCoefKnots = calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef_len;
    pAmergeCtx->ConfigV2.LongFrmEnvLv = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.OECurve.EnvLv_len));
    pAmergeCtx->ConfigV2.LongFrmOECurve_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.OECurve.EnvLv_len));
    pAmergeCtx->ConfigV2.LongFrmOECurve_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.OECurve.EnvLv_len));
    pAmergeCtx->ConfigV2.LongFrmMoveCoef = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef_len));
    pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef_len));
    pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef_len));
    pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef_len));
    pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef_len));

    //malloc short frm mode
    pAmergeCtx->ConfigV2.ShortFrmMaxEnvLvKnots = calibv2_amerge_calib->MergeTuningPara.ShortFrmModeData.OECurve.EnvLv_len;
    pAmergeCtx->ConfigV2.ShortFrmMaxMoveCoefKnots = calibv2_amerge_calib->MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef_len;
    pAmergeCtx->ConfigV2.ShortFrmEnvLv = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.ShortFrmModeData.OECurve.EnvLv_len));
    pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.ShortFrmModeData.OECurve.EnvLv_len));
    pAmergeCtx->ConfigV2.ShortFrmOECurve_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.ShortFrmModeData.OECurve.EnvLv_len));
    pAmergeCtx->ConfigV2.ShortFrmMoveCoef = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef_len));
    pAmergeCtx->ConfigV2.ShortFrmMDCurve_Coef = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef_len));
    pAmergeCtx->ConfigV2.ShortFrmMDCurve_ms_thd0 = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef_len));
    pAmergeCtx->ConfigV2.ShortFrmMDCurve_lm_thd0 = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef_len));

    //set default para
    //config default PrevData data
    pAmergeCtx->PrevData.CtrlData.EnvLv = 0;
    pAmergeCtx->PrevData.CtrlData.MoveCoef = 0;
    pAmergeCtx->PrevData.CtrlData.ApiMode = MERGE_OPMODE_API_OFF;
    pAmergeCtx->PrevData.HandleData.Merge_v30.MergeMode = 1;
    pAmergeCtx->PrevData.HandleData.Merge_v30.OECurve_smooth = 80;
    pAmergeCtx->PrevData.HandleData.Merge_v30.OECurve_offset = 210;
    pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurveLM_smooth = 80;
    pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurveLM_offset = 38;
    pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurveMS_smooth = 80;
    pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurveMS_offset = 38;
    pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurve_Coef = 0.05;
    pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurve_ms_thd0 = 0;
    pAmergeCtx->PrevData.HandleData.Merge_v30.MDCurve_lm_thd0 = 0;

    //set default ctrl info
    pAmergeCtx->mergeAttr.attrV30.opMode = MERGE_OPMODE_API_OFF;
    pAmergeCtx->mergeAttr.attrV30.CtlInfo.Envlv = 1.0;
    pAmergeCtx->mergeAttr.attrV30.CtlInfo.MoveCoef = 0.0;

    pAmergeCtx->mergeAttr.attrV30.stManual.BaseFrm = BASEFRAME_LONG;
    pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.OECurve.Smooth = 0.4;
    pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.OECurve.Offset = 210;
    pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.MDCurve.LM_smooth = 0.4;
    pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.MDCurve.LM_offset = 38;
    pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.MDCurve.MS_smooth = 0.4;
    pAmergeCtx->mergeAttr.attrV30.stManual.LongFrmModeData.MDCurve.MS_offset = 38;

    pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.OECurve.Smooth = 0.4;
    pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.OECurve.Offset = 210;
    pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.MDCurve.Coef = 0.05;
    pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.MDCurve.ms_thd0 = 0.00;
    pAmergeCtx->mergeAttr.attrV30.stManual.ShortFrmModeData.MDCurve.lm_thd0 = 0.00;

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
    return (result);
}
/******************************************************************************
 * AmergeRelease()
 *****************************************************************************/
XCamReturn AmergeRelease
(
    AmergeContext_t* pAmergeCtx
) {

    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    // initial checks
    if (NULL == pAmergeCtx) {
        return (XCAM_RETURN_ERROR_MEM);
    }

    result = AmergeStop(pAmergeCtx);
    if (result != XCAM_RETURN_NO_ERROR) {
        LOGE_AMERGE( "%s: Amerge Stop() failed!\n", __FUNCTION__);
        return (result);
    }

    // check state
    if ((AMERGE_STATE_RUNNING == pAmergeCtx->state)
            || (AMERGE_STATE_LOCKED == pAmergeCtx->state)) {
        return (XCAM_RETURN_ERROR_FAILED);
    }
    //free long frm mode
    free(pAmergeCtx->ConfigV2.LongFrmEnvLv );
    free(pAmergeCtx->ConfigV2.LongFrmOECurve_smooth );
    free(pAmergeCtx->ConfigV2.LongFrmOECurve_offset);
    free(pAmergeCtx->ConfigV2.LongFrmMoveCoef );
    free(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_smooth );
    free(pAmergeCtx->ConfigV2.LongFrmMDCurveLM_offset);
    free(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_smooth);
    free(pAmergeCtx->ConfigV2.LongFrmMDCurveMS_offset);
    //free short frm mode
    free(pAmergeCtx->ConfigV2.ShortFrmEnvLv);
    free(pAmergeCtx->ConfigV2.ShortFrmOECurve_smooth);
    free(pAmergeCtx->ConfigV2.ShortFrmOECurve_offset);
    free(pAmergeCtx->ConfigV2.ShortFrmMoveCoef);
    free(pAmergeCtx->ConfigV2.ShortFrmMDCurve_Coef);
    free(pAmergeCtx->ConfigV2.ShortFrmMDCurve_ms_thd0);
    free(pAmergeCtx->ConfigV2.ShortFrmMDCurve_lm_thd0);
    memset(pAmergeCtx, 0, sizeof(AmergeContext_s));
    free(pAmergeCtx);
    pAmergeCtx = NULL;

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);

    return (result);
}

