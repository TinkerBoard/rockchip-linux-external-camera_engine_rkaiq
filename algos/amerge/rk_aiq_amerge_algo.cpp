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

/******************************************************************************
 * AmergeConfig()
 *set default Config data
 *****************************************************************************/
void AmergeConfig
(
    AmergeContext_t*           pAmergeCtx
) {
    LOG1_ATMO( "%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAmergeCtx != NULL);

    //config default PrevData data
    pAmergeCtx->PrevData.CtrlData.EnvLv = 0;
    pAmergeCtx->PrevData.CtrlData.MoveCoef = 0;
    pAmergeCtx->PrevData.CtrlData.ApiMode = MERGE_OPMODE_API_OFF;
    pAmergeCtx->PrevData.HandleData.MergeMode = 1;
    pAmergeCtx->PrevData.HandleData.OECurve_smooth = 80;
    pAmergeCtx->PrevData.HandleData.OECurve_offset = 210;
    pAmergeCtx->PrevData.HandleData.MDCurveLM_smooth = 80;
    pAmergeCtx->PrevData.HandleData.MDCurveLM_offset = 38;
    pAmergeCtx->PrevData.HandleData.MDCurveMS_smooth = 80;
    pAmergeCtx->PrevData.HandleData.MDCurveMS_offset = 38;

    //set default ctrl info
    pAmergeCtx->mergeAttr.CtlInfo.Envlv = 1.0;
    pAmergeCtx->mergeAttr.CtlInfo.MoveCoef = 0.0;

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}
void AmergeGetAeResult
(
    AmergeContext_t*           pAmergeCtx,
    AecPreResult_t  AecHdrPreResult
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    //get Ae Pre Result
    pAmergeCtx->AeResult.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[AecHdrPreResult.NormalIndex];
    pAmergeCtx->AeResult.M2S_Ratio = AecHdrPreResult.M2S_ExpRatio;
    pAmergeCtx->AeResult.M2S_Ratio = pAmergeCtx->AeResult.M2S_Ratio < 1 ? 1 : pAmergeCtx->AeResult.M2S_Ratio;
    pAmergeCtx->AeResult.L2M_Ratio = AecHdrPreResult.L2M_ExpRatio;
    pAmergeCtx->AeResult.L2M_Ratio = pAmergeCtx->AeResult.L2M_Ratio < 1 ? 1 : pAmergeCtx->AeResult.L2M_Ratio;

    //transfer AeResult data into AhdrHandle
    switch (pAmergeCtx->FrameNumber)
    {
    case 1:
        pAmergeCtx->CurrData.CtrlData.LExpo = AecHdrPreResult.LinearExp.exp_real_params.analog_gain * AecHdrPreResult.LinearExp.exp_real_params.integration_time;
        pAmergeCtx->CurrData.CtrlData.L2S_Ratio = 1;
        pAmergeCtx->CurrData.CtrlData.L2M_Ratio = 1;
        pAmergeCtx->CurrData.CtrlData.L2L_Ratio = 1;
        pAmergeCtx->AeResult.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[0];
        break;
    case 2:
        pAmergeCtx->CurrData.CtrlData.L2S_Ratio = pAmergeCtx->AeResult.M2S_Ratio;
        pAmergeCtx->CurrData.CtrlData.L2M_Ratio = 1;
        pAmergeCtx->CurrData.CtrlData.L2L_Ratio = 1;
        pAmergeCtx->CurrData.CtrlData.LExpo = AecHdrPreResult.HdrExp[1].exp_real_params.analog_gain * AecHdrPreResult.HdrExp[1].exp_real_params.integration_time;
        pAmergeCtx->AeResult.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[1];
        break;
    case 3:
        pAmergeCtx->CurrData.CtrlData.L2S_Ratio = pAmergeCtx->AeResult.L2M_Ratio * pAmergeCtx->AeResult.M2S_Ratio;
        pAmergeCtx->CurrData.CtrlData.L2M_Ratio = pAmergeCtx->AeResult.L2M_Ratio;
        pAmergeCtx->CurrData.CtrlData.L2L_Ratio = 1;
        pAmergeCtx->CurrData.CtrlData.LExpo = AecHdrPreResult.HdrExp[2].exp_real_params.analog_gain * AecHdrPreResult.HdrExp[2].exp_real_params.integration_time;
        pAmergeCtx->AeResult.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[2];
        break;
    default:
        LOGE_AMERGE("%s:  Wrong frame number in HDR mode!!!\n", __FUNCTION__);
        break;
    }

    //Normalize the current envLv for AEC
    float maxEnvLuma = 65 / 10;
    float minEnvLuma = 0;
    pAmergeCtx->CurrData.CtrlData.EnvLv = (pAmergeCtx->AeResult.GlobalEnvLv  - minEnvLuma) / (maxEnvLuma - minEnvLuma);
    pAmergeCtx->CurrData.CtrlData.EnvLv = LIMIT_VALUE(pAmergeCtx->CurrData.CtrlData.EnvLv, ENVLVMAX, ENVLVMIN);

    LOGV_AMERGE("%s:  Current CtrlData.L2S_Ratio:%f CtrlData.L2M_Ratio:%f CtrlData.L2L_Ratio:%f\n", __FUNCTION__, pAmergeCtx->CurrData.CtrlData.L2S_Ratio,
                pAmergeCtx->CurrData.CtrlData.L2M_Ratio, pAmergeCtx->CurrData.CtrlData.L2L_Ratio);

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

void GetCurrMergeData
(
    AmergeContext_t*           pAmergeCtx
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    //get Current merge OECurve
    pAmergeCtx->CurrData.HandleData.OECurve_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.EnvLv,
            pAmergeCtx->Config.EnvLv, pAmergeCtx->Config.OECurve_smooth, pAmergeCtx->Config.MaxEnvLvKnots);
    pAmergeCtx->CurrData.HandleData.OECurve_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.EnvLv,
            pAmergeCtx->Config.EnvLv, pAmergeCtx->Config.OECurve_offset, pAmergeCtx->Config.MaxEnvLvKnots);

    //get Current merge MDCurve
    pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
            pAmergeCtx->Config.MoveCoef, pAmergeCtx->Config.MDCurveLM_smooth, pAmergeCtx->Config.MaxMoveCoefKnots);
    pAmergeCtx->CurrData.HandleData.MDCurveLM_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
            pAmergeCtx->Config.MoveCoef, pAmergeCtx->Config.MDCurveLM_offset, pAmergeCtx->Config.MaxMoveCoefKnots);
    pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
            pAmergeCtx->Config.MoveCoef, pAmergeCtx->Config.MDCurveMS_smooth, pAmergeCtx->Config.MaxMoveCoefKnots);
    pAmergeCtx->CurrData.HandleData.MDCurveMS_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
            pAmergeCtx->Config.MoveCoef, pAmergeCtx->Config.MDCurveMS_offset, pAmergeCtx->Config.MaxMoveCoefKnots);

    pAmergeCtx->CurrData.CtrlData.MergeOEDamp = pAmergeCtx->Config.OECurve_damp;
    pAmergeCtx->CurrData.CtrlData.MergeMDDampLM = pAmergeCtx->Config.MDCurveLM_damp;
    pAmergeCtx->CurrData.CtrlData.MergeMDDampMS = pAmergeCtx->Config.MDCurveMS_damp;

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

void AmergeGetSensorInfo
(
    AmergeContext_t*     pAmergeCtx,
    AecProcResult_t  AecHdrProcResult
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    pAmergeCtx->SensorInfo.LongFrmMode = AecHdrProcResult.LongFrmMode && (pAmergeCtx->FrameNumber != 1);

    for(int i = 0; i < 3; i++)
    {
        pAmergeCtx->SensorInfo.HdrMinGain[i] = AecHdrProcResult.HdrMinGain[i];
        pAmergeCtx->SensorInfo.HdrMaxGain[i] = AecHdrProcResult.HdrMaxGain[i];
        pAmergeCtx->SensorInfo.HdrMinIntegrationTime[i] = AecHdrProcResult.HdrMinIntegrationTime[i];
        pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[i] = AecHdrProcResult.HdrMaxIntegrationTime[i];
    }

    if(pAmergeCtx->FrameNumber == 2)
    {
        pAmergeCtx->SensorInfo.MaxExpoL = pAmergeCtx->SensorInfo.HdrMaxGain[1] * pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[1];
        pAmergeCtx->SensorInfo.MinExpoL = pAmergeCtx->SensorInfo.HdrMinGain[1] * pAmergeCtx->SensorInfo.HdrMinIntegrationTime[1];
        pAmergeCtx->SensorInfo.MaxExpoM = 0;
        pAmergeCtx->SensorInfo.MinExpoM = 0;

    }
    else if(pAmergeCtx->FrameNumber == 3)
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

    //get Current merge OECurve
    pAmergeCtx->CurrData.HandleData.OECurve_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.EnvLv,
            pAmergeCtx->Config.EnvLv, pAmergeCtx->Config.OECurve_smooth, pAmergeCtx->Config.MaxEnvLvKnots);
    pAmergeCtx->CurrData.HandleData.OECurve_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.EnvLv,
            pAmergeCtx->Config.EnvLv, pAmergeCtx->Config.OECurve_offset, pAmergeCtx->Config.MaxEnvLvKnots);

    //get Current merge MDCurve
    pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
            pAmergeCtx->Config.MoveCoef, pAmergeCtx->Config.MDCurveLM_smooth, pAmergeCtx->Config.MaxMoveCoefKnots);
    pAmergeCtx->CurrData.HandleData.MDCurveLM_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
            pAmergeCtx->Config.MoveCoef, pAmergeCtx->Config.MDCurveLM_offset, pAmergeCtx->Config.MaxMoveCoefKnots);
    pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
            pAmergeCtx->Config.MoveCoef, pAmergeCtx->Config.MDCurveMS_smooth, pAmergeCtx->Config.MaxMoveCoefKnots);
    pAmergeCtx->CurrData.HandleData.MDCurveMS_offset = GetCurrPara(pAmergeCtx->CurrData.CtrlData.MoveCoef,
            pAmergeCtx->Config.MoveCoef, pAmergeCtx->Config.MDCurveMS_offset, pAmergeCtx->Config.MaxMoveCoefKnots);

    pAmergeCtx->CurrData.CtrlData.MergeOEDamp = pAmergeCtx->Config.OECurve_damp;
    pAmergeCtx->CurrData.CtrlData.MergeMDDampLM = pAmergeCtx->Config.MDCurveLM_damp;
    pAmergeCtx->CurrData.CtrlData.MergeMDDampMS = pAmergeCtx->Config.MDCurveMS_damp;

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeTranferData2Api()
 *
 *****************************************************************************/
void AmergeTranferData2Api
(
    AmergeContext_t*     pAmergeCtx
)
{
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    //transfer control data to api
    pAmergeCtx->mergeAttr.CtlInfo.Envlv = pAmergeCtx->CurrData.CtrlData.EnvLv;
    pAmergeCtx->mergeAttr.CtlInfo.MoveCoef = pAmergeCtx->CurrData.CtrlData.MoveCoef;

    //transfer register data to api
    pAmergeCtx->mergeAttr.RegInfo.OECurve_smooth = pAmergeCtx->CurrData.HandleData.OECurve_smooth;
    pAmergeCtx->mergeAttr.RegInfo.OECurve_offset = pAmergeCtx->CurrData.HandleData.OECurve_offset;
    pAmergeCtx->mergeAttr.RegInfo.MDCurveLM_smooth = pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth;
    pAmergeCtx->mergeAttr.RegInfo.MDCurveLM_offset = pAmergeCtx->CurrData.HandleData.MDCurveLM_offset;
    pAmergeCtx->mergeAttr.RegInfo.MDCurveMS_smooth = pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth;
    pAmergeCtx->mergeAttr.RegInfo.MDCurveMS_offset = pAmergeCtx->CurrData.HandleData.MDCurveMS_offset;

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeApiAutoUpdate()
 *
 *****************************************************************************/
void AmergeApiAutoUpdate
(
    AmergeContext_t*     pAmergeCtx
)
{
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    if (pAmergeCtx->mergeAttr.stAuto.bUpdateMge == true)
    {
        //get oe cruve
        pAmergeCtx->CurrData.HandleData.OECurve_smooth =
            LIMIT_PARA(pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stCoef, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stSmthMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stSmthMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stCoefMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stCoefMin);
        pAmergeCtx->CurrData.HandleData.OECurve_offset =
            LIMIT_PARA(pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stCoef, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stOfstMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stOfstMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stCoefMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stCoefMin);

        //get md cruve ms
        pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth =
            LIMIT_PARA(pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stCoef, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stSmthMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stSmthMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stCoefMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stCoefMin);
        pAmergeCtx->CurrData.HandleData.MDCurveMS_offset =
            LIMIT_PARA(pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stCoef, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stOfstMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stOfstMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stCoefMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stCoefMin);

        //get md cruve lm
        pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth =
            LIMIT_PARA(pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stCoef, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stSmthMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stSmthMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stCoefMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stCoefMin);
        pAmergeCtx->CurrData.HandleData.MDCurveLM_offset =
            LIMIT_PARA(pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stCoef, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stOfstMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stOfstMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stCoefMax,
                       pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stCoefMin);

    }
    else
        GetCurrMergeData(pAmergeCtx);

    //paras after updating
    LOGD_AMERGE("%s: Data from api: bUpdateMge:%d OECurve stCoef:%f stCoefMin:%f stCoefMax:%f stOfstMin:%f stOfstMax:%f stSmthMin:%f stSmthMax:%f\n", __FUNCTION__, pAmergeCtx->mergeAttr.stAuto.bUpdateMge,
                pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stCoef, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stCoefMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stCoefMax,
                pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stOfstMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stOfstMax,
                pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stSmthMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stOECurve.stSmthMax);
    LOGD_AMERGE("%s: Data from api: MDCurveMS stCoef:%f stCoefMin:%f stCoefMax:%f stOfstMin:%f stOfstMax:%f stSmthMin:%f stSmthMax:%f\n", __FUNCTION__,
                pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stCoef, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stCoefMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stCoefMax,
                pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stOfstMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stOfstMax,
                pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stSmthMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveMS.stSmthMax);
    LOGD_AMERGE("%s: Data from api: MDCurveLM stCoef:%f stCoefMin:%f stCoefMax:%f stOfstMin:%f stOfstMax:%f stSmthMin:%f stSmthMax:%f\n", __FUNCTION__,
                pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stCoef, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stCoefMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stCoefMax,
                pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stOfstMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stOfstMax,
                pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stSmthMin, pAmergeCtx->mergeAttr.stAuto.stMgeAuto.stMDCurveLM.stSmthMax);

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeApiManualUpdate()
 *
 *****************************************************************************/
void AmergeApiManualUpdate
(
    AmergeContext_t*     pAmergeCtx
)
{
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    //update merge data in manual mode
    if (pAmergeCtx->mergeAttr.stManual.bUpdateMge == true)
    {
        pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth = pAmergeCtx->mergeAttr.stManual.stMgeManual.MDCurveMS_smooth * MDCURVESMOOTHMAX;
        pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth = LIMIT_VALUE(pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth,
                MDCURVESMOOTHMAX, MDCURVESMOOTHMIN);
        pAmergeCtx->CurrData.HandleData.MDCurveMS_offset = pAmergeCtx->mergeAttr.stManual.stMgeManual.MDCurveMS_offset * MDCURVEOFFSETMAX;
        pAmergeCtx->CurrData.HandleData.MDCurveMS_offset = LIMIT_VALUE(pAmergeCtx->CurrData.HandleData.MDCurveMS_offset,
                MDCURVEOFFSETMAX, MDCURVEOFFSETMIN);

        pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth = pAmergeCtx->mergeAttr.stManual.stMgeManual.MDCurveLM_smooth * MDCURVESMOOTHMAX;
        pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth = LIMIT_VALUE(pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth,
                MDCURVESMOOTHMAX, MDCURVESMOOTHMIN);
        pAmergeCtx->CurrData.HandleData.MDCurveLM_offset = pAmergeCtx->mergeAttr.stManual.stMgeManual.MDCurveLM_offset * MDCURVEOFFSETMAX;
        pAmergeCtx->CurrData.HandleData.MDCurveLM_offset = LIMIT_VALUE(pAmergeCtx->CurrData.HandleData.MDCurveLM_offset,
                MDCURVEOFFSETMAX, MDCURVEOFFSETMIN);

        pAmergeCtx->CurrData.HandleData.OECurve_smooth = pAmergeCtx->mergeAttr.stManual.stMgeManual.OECurve_smooth * OECURVESMOOTHMAX;
        pAmergeCtx->CurrData.HandleData.OECurve_smooth = LIMIT_VALUE(pAmergeCtx->CurrData.HandleData.OECurve_smooth,
                OECURVESMOOTHMAX, OECURVESMOOTHMIN);
        pAmergeCtx->CurrData.HandleData.OECurve_offset = pAmergeCtx->mergeAttr.stManual.stMgeManual.OECurve_offset;
        pAmergeCtx->CurrData.HandleData.OECurve_offset = LIMIT_VALUE(pAmergeCtx->CurrData.HandleData.OECurve_offset,
                OECURVEOFFSETMAX, OECURVEOFFSETMIN);

        pAmergeCtx->CurrData.CtrlData.MergeOEDamp = pAmergeCtx->mergeAttr.stManual.stMgeManual.dampOE;
        pAmergeCtx->CurrData.CtrlData.MergeMDDampLM = pAmergeCtx->mergeAttr.stManual.stMgeManual.dampMDLM;
        pAmergeCtx->CurrData.CtrlData.MergeMDDampMS = pAmergeCtx->mergeAttr.stManual.stMgeManual.dampMDMS;

    }
    else
        GetCurrMergeData(pAmergeCtx);

    //paras after updating
    LOGD_AMERGE("%s: Data from api: bUpdateMge:%d OECurve_smooth:%f OECurve_offset:%f MergeOEDamp:%f MergeMDDampLM:%f MergeMDDampMS:%f\n", __FUNCTION__, pAmergeCtx->mergeAttr.stManual.bUpdateMge,
                pAmergeCtx->mergeAttr.stManual.stMgeManual.OECurve_smooth, pAmergeCtx->mergeAttr.stManual.stMgeManual.OECurve_offset,
                pAmergeCtx->mergeAttr.stManual.stMgeManual.dampOE, pAmergeCtx->mergeAttr.stManual.stMgeManual.dampMDLM, pAmergeCtx->mergeAttr.stManual.stMgeManual.dampMDMS);
    LOGD_AMERGE("%s: Data from api: MDCurveMS_smooth:%f MDCurveMS_offset:%f MDCurveLM_smooth:%f MDCurveLM_offset:%f\n", __FUNCTION__,
                pAmergeCtx->mergeAttr.stManual.stMgeManual.MDCurveMS_smooth, pAmergeCtx->mergeAttr.stManual.stMgeManual.MDCurveMS_offset,
                pAmergeCtx->mergeAttr.stManual.stMgeManual.MDCurveLM_smooth, pAmergeCtx->mergeAttr.stManual.stMgeManual.MDCurveLM_offset);

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}
/******************************************************************************
 * MergeNewMalloc()
 ***************************************************************************/
void MergeNewMalloc
(
    AmergeConfig_t*           pAmergeConfig,
    AmergeCalib_t*         pCalibDb,
    AmergeVersion_t HWversion
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAmergeConfig != NULL);
    DCT_ASSERT(pCalibDb != NULL);

    if(HWversion == AMERGE_ISP20 || HWversion == AMERGE_ISP21) {
        LOG1_AMERGE( "%s: Pre MaxEnvLvKnots:%d Cur MaxEnvLvKnots:%d\n", __FUNCTION__, pAmergeConfig->MaxEnvLvKnots, pCalibDb->Merge_v20.MergeTuningPara.OECurve.EnvLv_len);
        LOG1_AMERGE( "%s: Pre MaxMoveCoefKnots:%d Cur MaxMoveCoefKnots:%d\n", __FUNCTION__, pAmergeConfig->MaxMoveCoefKnots, pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MoveCoef_len);

        if(pAmergeConfig->MaxEnvLvKnots != pCalibDb->Merge_v20.MergeTuningPara.OECurve.EnvLv_len) {
            free(pAmergeConfig->EnvLv);
            free(pAmergeConfig->OECurve_smooth);
            free(pAmergeConfig->OECurve_offset);
            pAmergeConfig->MaxEnvLvKnots = pCalibDb->Merge_v20.MergeTuningPara.OECurve.EnvLv_len;
            pAmergeConfig->EnvLv = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v20.MergeTuningPara.OECurve.EnvLv_len));
            pAmergeConfig->OECurve_smooth = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v20.MergeTuningPara.OECurve.EnvLv_len));
            pAmergeConfig->OECurve_offset = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v20.MergeTuningPara.OECurve.EnvLv_len));
        }
        if(pAmergeConfig->MaxMoveCoefKnots != pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MoveCoef_len) {
            free(pAmergeConfig->MoveCoef);
            free(pAmergeConfig->MDCurveLM_smooth);
            free(pAmergeConfig->MDCurveLM_offset);
            free(pAmergeConfig->MDCurveMS_smooth);
            free(pAmergeConfig->MDCurveMS_offset);
            pAmergeConfig->MaxMoveCoefKnots = pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MoveCoef_len;
            pAmergeConfig->MoveCoef = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MoveCoef_len));
            pAmergeConfig->MDCurveLM_smooth = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MoveCoef_len));
            pAmergeConfig->MDCurveLM_offset = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MoveCoef_len));
            pAmergeConfig->MDCurveMS_smooth = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MoveCoef_len));
            pAmergeConfig->MDCurveMS_offset = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MoveCoef_len));
        }
    }
    else if(HWversion == AMERGE_ISP30) {
        LOG1_AMERGE( "%s: Pre MaxEnvLvKnots:%d Cur MaxEnvLvKnots:%d\n", __FUNCTION__, pAmergeConfig->MaxEnvLvKnots, pCalibDb->Merge_v30.MergeTuningPara.OECurve.EnvLv_len);
        LOG1_AMERGE( "%s: Pre MaxMoveCoefKnots:%d Cur MaxMoveCoefKnots:%d\n", __FUNCTION__, pAmergeConfig->MaxMoveCoefKnots, pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MoveCoef_len);

        if(pAmergeConfig->MaxEnvLvKnots != pCalibDb->Merge_v30.MergeTuningPara.OECurve.EnvLv_len) {
            free(pAmergeConfig->EnvLv);
            free(pAmergeConfig->OECurve_smooth);
            free(pAmergeConfig->OECurve_offset);
            pAmergeConfig->MaxEnvLvKnots = pCalibDb->Merge_v30.MergeTuningPara.OECurve.EnvLv_len;
            pAmergeConfig->EnvLv = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v30.MergeTuningPara.OECurve.EnvLv_len));
            pAmergeConfig->OECurve_smooth = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v30.MergeTuningPara.OECurve.EnvLv_len));
            pAmergeConfig->OECurve_offset = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v30.MergeTuningPara.OECurve.EnvLv_len));
        }
        if(pAmergeConfig->MaxMoveCoefKnots != pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MoveCoef_len) {
            free(pAmergeConfig->MoveCoef);
            free(pAmergeConfig->MDCurveLM_smooth);
            free(pAmergeConfig->MDCurveLM_offset);
            free(pAmergeConfig->MDCurveMS_smooth);
            free(pAmergeConfig->MDCurveMS_offset);
            pAmergeConfig->MaxMoveCoefKnots = pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MoveCoef_len;
            pAmergeConfig->MoveCoef = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MoveCoef_len));
            pAmergeConfig->MDCurveLM_smooth = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MoveCoef_len));
            pAmergeConfig->MDCurveLM_offset = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MoveCoef_len));
            pAmergeConfig->MDCurveMS_smooth = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MoveCoef_len));
            pAmergeConfig->MDCurveMS_offset = (float*)malloc(sizeof(float) * (pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MoveCoef_len));
        }
    }

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeUpdateConfig()
 *transfer html parameter into handle
 ***************************************************************************/
void AmergeUpdateConfig
(
    AmergeContext_t*           pAmergeCtx,
    AmergeCalib_t*         pCalibDb
) {
    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAmergeCtx != NULL);
    DCT_ASSERT(pCalibDb != NULL);

    if(pAmergeCtx->HWversion == AMERGE_ISP20 || pAmergeCtx->HWversion == AMERGE_ISP21) {
        pAmergeCtx->Config.BaseFrm = BASEFRAME_LONG;
        pAmergeCtx->Config.ByPassThr = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.ByPassThr, DAMPMAX, DAMPMIN);
        pAmergeCtx->Config.OECurve_damp = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.OECurve_damp, DAMPMAX, DAMPMIN);
        pAmergeCtx->Config.MDCurveLM_damp = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.MDCurveLM_damp, DAMPMAX, DAMPMIN);
        pAmergeCtx->Config.MDCurveMS_damp = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.MDCurveMS_damp, DAMPMAX, DAMPMIN);
        for (int i = 0; i < pAmergeCtx->Config.MaxEnvLvKnots; i++ ) {
            pAmergeCtx->Config.EnvLv[i] = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.OECurve.EnvLv[i], ENVLVMAX, ENVLVMIN);
            pAmergeCtx->Config.OECurve_smooth[i] = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.OECurve.Smooth[i], IQPARAMAX, IQPARAMIN);
            pAmergeCtx->Config.OECurve_offset[i] = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.OECurve.Offset[i], OECURVEOFFSETMAX, OECURVEOFFSETMIN);
        }
        for (int i = 0; i < pAmergeCtx->Config.MaxMoveCoefKnots; i++ ) {
            pAmergeCtx->Config.MoveCoef[i] = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MoveCoef[i], MOVECOEFMAX, MOVECOEFMIN);
            pAmergeCtx->Config.MDCurveLM_smooth[i] = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.MDCurve.LM_smooth[i], IQPARAMAX, IQPARAMIN);
            pAmergeCtx->Config.MDCurveLM_offset[i] = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.MDCurve.LM_offset[i], IQPARAMAX, IQPARAMIN);
            pAmergeCtx->Config.MDCurveMS_smooth[i] = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MS_smooth[i], IQPARAMAX, IQPARAMIN);
            pAmergeCtx->Config.MDCurveMS_offset[i] = LIMIT_VALUE(pCalibDb->Merge_v20.MergeTuningPara.MDCurve.MS_offset[i], IQPARAMAX, IQPARAMIN);
        }
    }
    else if(pAmergeCtx->HWversion == AMERGE_ISP30) {
        pAmergeCtx->Config.BaseFrm = pCalibDb->Merge_v30.MergeTuningPara.BaseFrm;
        pAmergeCtx->Config.ByPassThr = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.ByPassThr, DAMPMAX, DAMPMIN);
        pAmergeCtx->Config.OECurve_damp = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.OECurve_damp, DAMPMAX, DAMPMIN);
        pAmergeCtx->Config.MDCurveLM_damp = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.MDCurveLM_damp, DAMPMAX, DAMPMIN);
        pAmergeCtx->Config.MDCurveMS_damp = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.MDCurveMS_damp, DAMPMAX, DAMPMIN);
        for (int i = 0; i < pAmergeCtx->Config.MaxEnvLvKnots; i++ ) {
            pAmergeCtx->Config.EnvLv[i] = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.OECurve.EnvLv[i], ENVLVMAX, ENVLVMIN);
            pAmergeCtx->Config.OECurve_smooth[i] = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.OECurve.Smooth[i], IQPARAMAX, IQPARAMIN);
            pAmergeCtx->Config.OECurve_offset[i] = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.OECurve.Offset[i], OECURVEOFFSETMAX, OECURVEOFFSETMIN);
        }
        for (int i = 0; i < pAmergeCtx->Config.MaxMoveCoefKnots; i++ ) {
            pAmergeCtx->Config.MoveCoef[i] = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MoveCoef[i], MOVECOEFMAX, MOVECOEFMIN);
            pAmergeCtx->Config.MDCurveLM_smooth[i] = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.MDCurve.LM_smooth[i], IQPARAMAX, IQPARAMIN);
            pAmergeCtx->Config.MDCurveLM_offset[i] = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.MDCurve.LM_offset[i], IQPARAMAX, IQPARAMIN);
            pAmergeCtx->Config.MDCurveMS_smooth[i] = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MS_smooth[i], IQPARAMAX, IQPARAMIN);
            pAmergeCtx->Config.MDCurveMS_offset[i] = LIMIT_VALUE(pCalibDb->Merge_v30.MergeTuningPara.MDCurve.MS_offset[i], IQPARAMAX, IQPARAMIN);
        }
    }

#if 0
    LOG1_AMERGE( "%s:EnvLv len:%d MoveCoef len:%d \n", __FUNCTION__, pAmergeCtx->Config.MaxEnvLvKnots, pAmergeCtx->Config.MaxMoveCoefKnots);
    for(int i = 0; i < pAmergeCtx->Config.MaxEnvLvKnots; i++)
        LOG1_AMERGE("%s: EnvLv[%d]:%f OEcurve_smooth[%d]:%f OEcurve_offset[%d]:%f OECurve_damp:%f\n", __FUNCTION__,
                    i, pAmergeCtx->Config.EnvLv[i],
                    i, pAmergeCtx->Config.OECurve_smooth[i], i, pAmergeCtx->Config.OECurve_offset[i], pAmergeCtx->Config.OECurve_damp);

    for(int i = 0; i < pAmergeCtx->Config.MaxMoveCoefKnots; i++)
        LOG1_AMERGE("%s: MoveCoef[%d]:%f MDCurveMS_smooth[%d]:%f MDCurveMS_offset[%d]:%f MDCurveMS_damp:%f\n", __FUNCTION__,
                    i, pAmergeCtx->Config.MoveCoef[i], i, pAmergeCtx->Config.MDCurveMS_smooth[i],
                    i, pAmergeCtx->Config.MDCurveMS_offset[i], pAmergeCtx->Config.MDCurveMS_damp);

    for(int i = 0; i < pAmergeCtx->Config.MaxMoveCoefKnots; i++)
        LOG1_AMERGE("%s: MoveCoef[%d]:%f MDCurveLM_smooth[%d]:%f MDCurveLM_offset[%d]:%f MDCurveLM_damp:%f\n", __FUNCTION__,
                    i, pAmergeCtx->Config.MoveCoef[i], i, pAmergeCtx->Config.MDCurveLM_smooth[i],
                    i, pAmergeCtx->Config.MDCurveLM_offset[i], pAmergeCtx->Config.MDCurveLM_damp);

#endif

    //turn the IQ paras into algo paras
    for(int i = 0; i < pAmergeCtx->Config.MaxEnvLvKnots; i++)
    {
        pAmergeCtx->Config.OECurve_smooth[i] = pAmergeCtx->Config.OECurve_smooth[i] * OECURVESMOOTHMAX;
        pAmergeCtx->Config.OECurve_smooth[i] = LIMIT_VALUE(pAmergeCtx->Config.OECurve_smooth[i], OECURVESMOOTHMAX, OECURVESMOOTHMIN) ;
    }

    for(int i = 0; i < pAmergeCtx->Config.MaxMoveCoefKnots; i++)
    {
        pAmergeCtx->Config.MDCurveLM_smooth[i] = pAmergeCtx->Config.MDCurveLM_smooth[i] * MDCURVESMOOTHMAX;
        pAmergeCtx->Config.MDCurveLM_smooth[i] = LIMIT_VALUE(pAmergeCtx->Config.MDCurveLM_smooth[i], MDCURVESMOOTHMAX, MDCURVESMOOTHMIN) ;
        pAmergeCtx->Config.MDCurveLM_offset[i] = pAmergeCtx->Config.MDCurveLM_offset[i] * MDCURVEOFFSETMAX;
        pAmergeCtx->Config.MDCurveLM_offset[i] = LIMIT_VALUE(pAmergeCtx->Config.MDCurveLM_offset[i], MDCURVEOFFSETMAX, MDCURVEOFFSETMIN) ;

        pAmergeCtx->Config.MDCurveMS_smooth[i] = pAmergeCtx->Config.MDCurveMS_smooth[i] * MDCURVESMOOTHMAX;
        pAmergeCtx->Config.MDCurveMS_smooth[i] = LIMIT_VALUE(pAmergeCtx->Config.MDCurveMS_smooth[i], MDCURVESMOOTHMAX, MDCURVESMOOTHMIN) ;
        pAmergeCtx->Config.MDCurveMS_offset[i] = pAmergeCtx->Config.MDCurveMS_offset[i] * MDCURVEOFFSETMAX;
        pAmergeCtx->Config.MDCurveMS_offset[i] = LIMIT_VALUE(pAmergeCtx->Config.MDCurveMS_offset[i], MDCURVEOFFSETMAX, MDCURVEOFFSETMIN) ;
    }

#if 0

    LOG1_AMERGE("%s:  Merge algo OECurve_smooth:%f %f %f %f %f %f:\n", __FUNCTION__, pAmergeCtx->Config.OECurve_smooth[0], pAmergeCtx->Config.OECurve_smooth[1], pAmergeCtx->Config.OECurve_smooth[2],
                pAmergeCtx->Config.OECurve_smooth[3], pAmergeCtx->Config.OECurve_smooth[4], pAmergeCtx->Config.OECurve_smooth[5]);
    LOG1_AMERGE("%s:  Merge algo MDCurveLM_smooth:%f %f %f %f %f %f:\n", __FUNCTION__, pAmergeCtx->Config.MDCurveLM_smooth[0], pAmergeCtx->Config.MDCurveLM_smooth[1], pAmergeCtx->Config.MDCurveLM_smooth[2],
                pAmergeCtx->Config.MDCurveLM_smooth[3], pAmergeCtx->Config.MDCurveLM_smooth[4], pAmergeCtx->Config.MDCurveLM_smooth[5]);
    LOG1_AMERGE("%s:  Merge algo MDCurveLM_offset:%f %f %f %f %f %f:\n", __FUNCTION__, pAmergeCtx->Config.MDCurveLM_offset[0], pAmergeCtx->Config.MDCurveLM_offset[1], pAmergeCtx->Config.MDCurveLM_offset[2],
                pAmergeCtx->Config.MDCurveLM_offset[3], pAmergeCtx->Config.MDCurveLM_offset[4], pAmergeCtx->Config.MDCurveLM_offset[5]);
    LOG1_AMERGE("%s:  Merge algo MDCurveMS_smooth:%f %f %f %f %f %f:\n", __FUNCTION__, pAmergeCtx->Config.MDCurveMS_smooth[0], pAmergeCtx->Config.MDCurveMS_smooth[1], pAmergeCtx->Config.MDCurveMS_smooth[2],
                pAmergeCtx->Config.MDCurveMS_smooth[3], pAmergeCtx->Config.MDCurveMS_smooth[4], pAmergeCtx->Config.MDCurveMS_smooth[5]);
    LOG1_AMERGE("%s:  Merge algo MDCurveMS_offset:%f %f %f %f %f %f:\n", __FUNCTION__, pAmergeCtx->Config.MDCurveMS_offset[0], pAmergeCtx->Config.MDCurveMS_offset[1], pAmergeCtx->Config.MDCurveMS_offset[2],
                pAmergeCtx->Config.MDCurveMS_offset[3], pAmergeCtx->Config.MDCurveMS_offset[4], pAmergeCtx->Config.MDCurveMS_offset[5]);

#endif

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
    float curve = 0;
    float k = 511;

    for(int i = 0; i < 17; ++i)
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
* CalibrateMDCurve()
*****************************************************************************/
void CalibrateMDCurve
(
    float smooth, float offset, unsigned short *MDCurve
)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    int step = 16;
    float curve;
    float k = 0;

    for (int i = 0; i < 17; ++i)
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
 * GetCurrIOData()
 *****************************************************************************/
void MergeGetCurrIOData
(
    AmergeContext_t* pAmergeCtx
)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    int OECurve[17];

    pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_mode = pAmergeCtx->CurrData.HandleData.MergeMode;
    if(pAmergeCtx->HWversion == AMERGE_ISP21)
        pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_mode = LIMIT_VALUE(pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_mode, 1, 0);
    pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_lm_dif_0p9 = 230;
    pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_ms_dif_0p8 = 205;
    pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_lm_dif_0p15 = (int)pAmergeCtx->CurrData.HandleData.MDCurveLM_offset;
    pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_ms_dif_0p15 = (int)pAmergeCtx->CurrData.HandleData.MDCurveMS_offset;


    CalibrateOECurve(pAmergeCtx->CurrData.HandleData.OECurve_smooth,
                     pAmergeCtx->CurrData.HandleData.OECurve_offset, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_e_y) ;
    CalibrateMDCurve(pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth,
                     pAmergeCtx->CurrData.HandleData.MDCurveLM_offset, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_l1_y);
    CalibrateMDCurve(pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth,
                     pAmergeCtx->CurrData.HandleData.MDCurveMS_offset, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_l0_y);

    if(pAmergeCtx->SensorInfo.LongFrmMode == true) {
        for(int i = 0; i < 17; i++)
            pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_e_y[i] = 0;
    }

    //when gainX = 1, gainX_inv = 1/gainX -1
    pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain0 = (int)SHIFT6BIT(pAmergeCtx->CurrData.CtrlData.L2S_Ratio);
    if(pAmergeCtx->CurrData.CtrlData.L2S_Ratio == 1)
        pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain0_inv = (int)(SHIFT12BIT(1 / pAmergeCtx->CurrData.CtrlData.L2S_Ratio) - 1);
    else
        pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain0_inv = (int)SHIFT12BIT(1 / pAmergeCtx->CurrData.CtrlData.L2S_Ratio);

    pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain1 = (int)SHIFT6BIT(pAmergeCtx->CurrData.CtrlData.L2M_Ratio);
    if(pAmergeCtx->CurrData.CtrlData.L2M_Ratio == 1)
        pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain1_inv = (int)(SHIFT12BIT(1 / pAmergeCtx->CurrData.CtrlData.L2M_Ratio) - 1);
    else
        pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain1_inv = (int)SHIFT12BIT(1 / pAmergeCtx->CurrData.CtrlData.L2M_Ratio);

    pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain2 = (int)SHIFT6BIT(pAmergeCtx->CurrData.CtrlData.L2L_Ratio);

    LOGV_AMERGE("%s:  Merge set IOdata to register:\n", __FUNCTION__);
    LOGV_AMERGE("%s: sw_hdrmge_mode:%d sw_hdrmge_ms_dif_0p8:%d sw_hdrmge_lm_dif_0p9:%d sw_hdrmge_ms_dif_0p15:%d sw_hdrmge_lm_dif_0p15\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_mode, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_ms_dif_0p8,
                pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_lm_dif_0p9, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_ms_dif_0p15,
                pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_lm_dif_0p15);
    LOGV_AMERGE("%s:  sw_hdrmge_gain0:%d sw_hdrmge_gain0_inv:%d sw_hdrmge_gain1:%d sw_hdrmge_gain1_inv:%d sw_hdrmge_gain2:%d\n", __FUNCTION__, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain0,
                pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain0_inv, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain1,
                pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain1_inv, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_gain2);
    for(int i = 0; i < 17; i++)
        LOGV_AMERGE("%s:  sw_hdrmge_e_y[%d]:%d \n", __FUNCTION__, i, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_e_y[i]);
    for(int i = 0; i < 17; i++)
        LOGV_AMERGE("%s:  sw_hdrmge_l0_y[%d]:%d \n", __FUNCTION__, i, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_l0_y[i]);
    for(int i = 0; i < 17; i++)
        LOGV_AMERGE("%s:  sw_hdrmge_l1_y[%d]:%d \n", __FUNCTION__, i, pAmergeCtx->ProcRes.Merge_v20.sw_hdrmge_l1_y[i]);

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}
/******************************************************************************
 * GetCurrIOData()
 *****************************************************************************/
void MergeGetCurrIODataV2
(
    AmergeContext_t* pAmergeCtx
)
{
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);
    int OECurve[17];

    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_mode = pAmergeCtx->CurrData.HandleData.MergeMode;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_dif_0p9 = 230;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_dif_0p8 = 205;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_dif_0p15 = (int)pAmergeCtx->CurrData.HandleData.MDCurveLM_offset;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_dif_0p15 = (int)pAmergeCtx->CurrData.HandleData.MDCurveMS_offset;


    CalibrateOECurve(pAmergeCtx->CurrData.HandleData.OECurve_smooth,
                     pAmergeCtx->CurrData.HandleData.OECurve_offset, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y) ;
    CalibrateMDCurve(pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth,
                     pAmergeCtx->CurrData.HandleData.MDCurveLM_offset, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y);
    CalibrateMDCurve(pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth,
                     pAmergeCtx->CurrData.HandleData.MDCurveMS_offset, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y);

    if(pAmergeCtx->SensorInfo.LongFrmMode == true) {
        for(int i = 0; i < 17; i++)
            pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[i] = 0;
    }

    //when gainX = 1, gainX_inv = 1/gainX -1
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0 = (int)SHIFT6BIT(pAmergeCtx->CurrData.CtrlData.L2S_Ratio);
    if(pAmergeCtx->CurrData.CtrlData.L2S_Ratio == 1)
        pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0_inv = (int)(SHIFT12BIT(1 / pAmergeCtx->CurrData.CtrlData.L2S_Ratio) - 1);
    else
        pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0_inv = (int)SHIFT12BIT(1 / pAmergeCtx->CurrData.CtrlData.L2S_Ratio);

    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1 = (int)SHIFT6BIT(pAmergeCtx->CurrData.CtrlData.L2M_Ratio);
    if(pAmergeCtx->CurrData.CtrlData.L2M_Ratio == 1)
        pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1_inv = (int)(SHIFT12BIT(1 / pAmergeCtx->CurrData.CtrlData.L2M_Ratio) - 1);
    else
        pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1_inv = (int)SHIFT12BIT(1 / pAmergeCtx->CurrData.CtrlData.L2M_Ratio);

    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain2 = (int)SHIFT6BIT(pAmergeCtx->CurrData.CtrlData.L2L_Ratio);

    //isp30 add
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_s_base = pAmergeCtx->Config.BaseFrm;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_thd0 = 0;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_thd1 = 0;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_scl = 0;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_thd0 = 0;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_thd1 = 0;
    pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_scl = 0;

    LOGV_AMERGE("%s: Merge set IOdata to register:\n", __FUNCTION__);
    LOGV_AMERGE("%s: sw_hdrmge_mode:%d sw_hdrmge_ms_dif_0p8:%d sw_hdrmge_lm_dif_0p9:%d sw_hdrmge_ms_dif_0p15:%d sw_hdrmge_lm_dif_0p15\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_mode, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_dif_0p8,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_dif_0p9, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_dif_0p15,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_dif_0p15);
    LOGV_AMERGE("%s:  sw_hdrmge_gain0:%d sw_hdrmge_gain0_inv:%d sw_hdrmge_gain1:%d sw_hdrmge_gain1_inv:%d sw_hdrmge_gain2:%d\n", __FUNCTION__, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain0_inv, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain1_inv, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_gain2);
    LOGV_AMERGE("%s: sw_hdrmge_s_base:%d sw_hdrmge_ms_thd0:%d sw_hdrmge_ms_thd1:%d sw_hdrmge_ms_scl:%d sw_hdrmge_lm_thd0:%d sw_hdrmge_lm_thd1:%d sw_hdrmge_lm_scl:%d\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_s_base, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_thd0,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_thd1, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_ms_scl,
                pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_thd0, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_thd1, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_lm_scl);

    for(int i = 0; i < 17; i++)
        LOGV_AMERGE("%s:  sw_hdrmge_e_y[%d]:%d \n", __FUNCTION__, i, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_e_y[i]);
    for(int i = 0; i < 17; i++)
        LOGV_AMERGE("%s:  sw_hdrmge_l0_y[%d]:%d \n", __FUNCTION__, i, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l0_y[i]);
    for(int i = 0; i < 17; i++)
        LOGV_AMERGE("%s:  sw_hdrmge_l1_y[%d]:%d \n", __FUNCTION__, i, pAmergeCtx->ProcRes.Merge_v30.sw_hdrmge_l1_y[i]);

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

    bool ifHDRModeChange = pAmergeCtx->CurrData.HandleData.MergeMode == pAmergeCtx->PrevData.HandleData.MergeMode ? false : true;

    //get finnal current data
    if (pAmergeCtx->mergeAttr.opMode != MERGE_OPMODE_AUTO && pAmergeCtx->frameCnt != 0 && !ifHDRModeChange)
    {
        pAmergeCtx->CurrData.HandleData.OECurve_smooth = OEDamp * pAmergeCtx->CurrData.HandleData.OECurve_smooth
                + (1 - OEDamp) * pAmergeCtx->PrevData.HandleData.OECurve_smooth;
        pAmergeCtx->CurrData.HandleData.OECurve_offset = OEDamp * pAmergeCtx->CurrData.HandleData.OECurve_offset
                + (1 - OEDamp) * pAmergeCtx->PrevData.HandleData.OECurve_offset;
        pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth = MDDampLM * pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth
                + (1 - MDDampLM) * pAmergeCtx->PrevData.HandleData.MDCurveLM_smooth;
        pAmergeCtx->CurrData.HandleData.MDCurveLM_offset = MDDampLM * pAmergeCtx->CurrData.HandleData.MDCurveLM_offset
                + (1 - MDDampLM) * pAmergeCtx->PrevData.HandleData.MDCurveLM_offset;
        pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth = MDDampMS * pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth
                + (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.MDCurveMS_smooth;
        pAmergeCtx->CurrData.HandleData.MDCurveMS_offset = MDDampMS * pAmergeCtx->CurrData.HandleData.MDCurveMS_offset
                + (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.MDCurveMS_offset;
    }

    if(pAmergeCtx->HWversion == AMERGE_ISP20 || pAmergeCtx->HWversion == AMERGE_ISP21)
        LOGD_AMERGE("%s:  Current OECurve_smooth:%f OECurve_offset:%f \n", __FUNCTION__, pAmergeCtx->CurrData.HandleData.OECurve_smooth,
                    pAmergeCtx->CurrData.HandleData.OECurve_offset);
    else if(pAmergeCtx->HWversion == AMERGE_ISP30)
        LOGD_AMERGE("%s:  Current BaseFrm:%d OECurve_smooth:%f OECurve_offset:%f \n", __FUNCTION__, pAmergeCtx->Config.BaseFrm,
                    pAmergeCtx->CurrData.HandleData.OECurve_smooth, pAmergeCtx->CurrData.HandleData.OECurve_offset);
    LOGD_AMERGE("%s:  Current MDCurveMS_smooth:%f MDCurveMS_offset:%f MDCurveLM_smooth:%f MDCurveLM_offset:%f \n", __FUNCTION__, pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth
                , pAmergeCtx->CurrData.HandleData.MDCurveMS_offset, pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth, pAmergeCtx->CurrData.HandleData.MDCurveLM_offset);

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeGetProcRes()
 *****************************************************************************/
void AmergeGetProcRes
(
    AmergeContext_t* pAmergeCtx
) {

    LOG1_AMERGE( "%s:enter!\n", __FUNCTION__);

    //merge damp
    MergeDamping(pAmergeCtx);

    //get current IO data
    if(pAmergeCtx->HWversion == AMERGE_ISP20 || pAmergeCtx->HWversion == AMERGE_ISP21)
        MergeGetCurrIOData(pAmergeCtx);
    else if(pAmergeCtx->HWversion == AMERGE_ISP30)
        MergeGetCurrIODataV2(pAmergeCtx);

    // store current handle data to pre data for next loop
    pAmergeCtx->PrevData.HandleData.MergeMode = pAmergeCtx->CurrData.HandleData.MergeMode;
    pAmergeCtx->PrevData.CtrlData.L2S_ratio = pAmergeCtx->CurrData.CtrlData.L2S_Ratio;
    pAmergeCtx->PrevData.CtrlData.LExpo = pAmergeCtx->CurrData.CtrlData.LExpo;
    pAmergeCtx->PrevData.CtrlData.EnvLv = pAmergeCtx->CurrData.CtrlData.EnvLv;
    pAmergeCtx->PrevData.CtrlData.MoveCoef = pAmergeCtx->CurrData.CtrlData.MoveCoef;
    memcpy(&pAmergeCtx->PrevData.HandleData, &pAmergeCtx->CurrData.HandleData, sizeof(MergeHandleData_s));

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
void AmergeProcessing
(
    AmergeContext_t*     pAmergeCtx
)
{
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    if(pAmergeCtx->mergeAttr.opMode == MERGE_OPMODE_API_OFF)
    {
        AmergeIQUpdate(pAmergeCtx);
    }
    else if(pAmergeCtx->mergeAttr.opMode == MERGE_OPMODE_AUTO)
    {
        AmergeApiAutoUpdate(pAmergeCtx);
    }
    else if(pAmergeCtx->mergeAttr.opMode == MERGE_OPMODE_MANU)
    {
        AmergeApiManualUpdate(pAmergeCtx);
    }
    else if(pAmergeCtx->mergeAttr.opMode == MERGE_OPMODE_TOOL)
    {
        AmergeIQUpdate(pAmergeCtx);
    }
    else
        LOGE_AMERGE("%s:  Amerge wrong mode!!!\n", __FUNCTION__);


    //log after updating
    LOG1_AMERGE("%s: Current Undamp OECurve_smooth:%f OECurve_offset:%f \n", __FUNCTION__,
                pAmergeCtx->CurrData.HandleData.OECurve_smooth, pAmergeCtx->CurrData.HandleData.OECurve_offset);
    LOG1_AMERGE("%s: Current Undamp MDCurveLM_smooth:%f MDCurveLM_offset:%f MDCurveMS_smooth:%f MDCurveMS_offset:%f\n", __FUNCTION__,
                pAmergeCtx->CurrData.HandleData.MDCurveLM_smooth, pAmergeCtx->CurrData.HandleData.MDCurveLM_offset,
                pAmergeCtx->CurrData.HandleData.MDCurveMS_smooth, pAmergeCtx->CurrData.HandleData.MDCurveMS_offset);

    //transfer data to api
    AmergeTranferData2Api(pAmergeCtx);

    //merge get proc res
    AmergeGetProcRes(pAmergeCtx);

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

    if(pAmergeCtx->frameCnt <= 2) //start frame
        bypass = false;
    else if(pAmergeCtx->mergeAttr.opMode > MERGE_OPMODE_API_OFF)//api
        bypass = false;
    if(pAmergeCtx->mergeAttr.opMode != pAmergeCtx->PrevData.CtrlData.ApiMode)//api change
        bypass = false;
    else { //EvnLv change
        //get Current hdr mode
        pAmergeCtx->CurrData.HandleData.MergeMode = pAmergeCtx->FrameNumber - 1;
        LOG1_AMERGE("%s:  Current MergeMode: %d \n", __FUNCTION__, pAmergeCtx->CurrData.HandleData.MergeMode);

        //get current ae data from AecPreRes
        AmergeGetAeResult(pAmergeCtx, AecHdrPreResult);

        //transfer ae data to CurrHandle
        pAmergeCtx->CurrData.CtrlData.EnvLv = LIMIT_VALUE(pAmergeCtx->CurrData.CtrlData.EnvLv, ENVLVMAX, ENVLVMIN);

        pAmergeCtx->CurrData.CtrlData.MoveCoef = 1;
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
            if(diff >= pAmergeCtx->Config.ByPassThr || diff <= (0 - pAmergeCtx->Config.ByPassThr))
                bypass = false;
            else
                bypass = true;
        }
    }

    LOGD_AMERGE( "%s: FrameID:%d HDRFrameNum:%d MergeApiMode:%d EnvLv:%f MoveCoef:%f bypass:%d\n", __FUNCTION__, pAmergeCtx->frameCnt, pAmergeCtx->FrameNumber, pAmergeCtx->mergeAttr.opMode,
                 pAmergeCtx->CurrData.CtrlData.EnvLv, pAmergeCtx->CurrData.CtrlData.MoveCoef, bypass);

    LOG1_AMERGE( "%s:CtrlEnvLv:%f PrevEnvLv:%f diff:%f ByPassThr:%f opMode:%d bypass:%d!\n", __FUNCTION__, pAmergeCtx->CurrData.CtrlData.EnvLv,
                 pAmergeCtx->PrevData.CtrlData.EnvLv, diff, pAmergeCtx->Config.ByPassThr, pAmergeCtx->mergeAttr.opMode, bypass);

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

    //get isp version
    if(CHECK_ISP_HW_V20())
        pAmergeCtx->HWversion = AMERGE_ISP20;
    else if(CHECK_ISP_HW_V21())
        pAmergeCtx->HWversion = AMERGE_ISP21;
    else if(CHECK_ISP_HW_V30())
        pAmergeCtx->HWversion = AMERGE_ISP30;


    if(pAmergeCtx->HWversion == AMERGE_ISP20 || pAmergeCtx->HWversion == AMERGE_ISP21) {
        CalibDbV2_merge_t* calibv2_amerge_calib =
            (CalibDbV2_merge_t*)(CALIBDBV2_GET_MODULE_PTR(pCalibV2, amerge_calib));

        memcpy(&pAmergeCtx->pCalibDB.Merge_v20, calibv2_amerge_calib, sizeof(CalibDbV2_merge_t));//load iq paras
        //memcpy(&pAmergeCtx->mergeAttr.stTool, calibv2_amerge_calib, sizeof(CalibDbV2_merge_t));//load iq paras to stTool

        //malloc
        pAmergeCtx->Config.MaxEnvLvKnots = calibv2_amerge_calib->MergeTuningPara.OECurve.EnvLv_len;
        pAmergeCtx->Config.EnvLv = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.OECurve.EnvLv_len));
        pAmergeCtx->Config.OECurve_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.OECurve.EnvLv_len));
        pAmergeCtx->Config.OECurve_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.OECurve.EnvLv_len));
        pAmergeCtx->Config.MaxMoveCoefKnots = calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len;
        pAmergeCtx->Config.MoveCoef = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));
        pAmergeCtx->Config.MDCurveLM_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));
        pAmergeCtx->Config.MDCurveLM_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));
        pAmergeCtx->Config.MDCurveMS_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));
        pAmergeCtx->Config.MDCurveMS_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));
    }
    else if(pAmergeCtx->HWversion == AMERGE_ISP30) {
        CalibDbV2_merge_V2_t* calibv2_amerge_calib =
            (CalibDbV2_merge_V2_t*)(CALIBDBV2_GET_MODULE_PTR(pCalibV2, amerge_calib));

        memcpy(&pAmergeCtx->pCalibDB.Merge_v30, calibv2_amerge_calib, sizeof(CalibDbV2_merge_V2_t));//load iq paras
        //memcpy(&pAmergeCtx->mergeAttr.stTool, calibv2_amerge_calib, sizeof(CalibDbV2_merge_t));//load iq paras to stTool

        //malloc
        pAmergeCtx->Config.MaxEnvLvKnots = calibv2_amerge_calib->MergeTuningPara.OECurve.EnvLv_len;
        pAmergeCtx->Config.EnvLv = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.OECurve.EnvLv_len));
        pAmergeCtx->Config.OECurve_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.OECurve.EnvLv_len));
        pAmergeCtx->Config.OECurve_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.OECurve.EnvLv_len));
        pAmergeCtx->Config.MaxMoveCoefKnots = calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len;
        pAmergeCtx->Config.MoveCoef = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));
        pAmergeCtx->Config.MDCurveLM_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));
        pAmergeCtx->Config.MDCurveLM_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));
        pAmergeCtx->Config.MDCurveMS_smooth = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));
        pAmergeCtx->Config.MDCurveMS_offset = (float*)malloc(sizeof(float) * (calibv2_amerge_calib->MergeTuningPara.MDCurve.MoveCoef_len));

    }
    pAmergeCtx->mergeAttr.opMode = MERGE_OPMODE_API_OFF;
    AmergeConfig(pAmergeCtx); //set default para

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

    free(pAmergeCtx->Config.EnvLv);
    free(pAmergeCtx->Config.OECurve_smooth);
    free(pAmergeCtx->Config.OECurve_offset);
    free(pAmergeCtx->Config.MoveCoef);
    free(pAmergeCtx->Config.MDCurveLM_smooth);
    free(pAmergeCtx->Config.MDCurveLM_offset);
    free(pAmergeCtx->Config.MDCurveMS_smooth);
    free(pAmergeCtx->Config.MDCurveMS_offset);
    memset(pAmergeCtx, 0, sizeof(AmergeContext_s));
    free(pAmergeCtx);
    pAmergeCtx = NULL;

    LOG1_AMERGE( "%s:exit!\n", __FUNCTION__);

    return (result);
}

