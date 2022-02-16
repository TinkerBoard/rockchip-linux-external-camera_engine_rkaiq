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
 * @file rk_aiq_amerge_algo_v12.cpp
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
XCamReturn AmergeStart(AmergeContext_t* pAmergeCtx) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    // initial checks
    if (pAmergeCtx == NULL) {
        return (XCAM_RETURN_ERROR_MEM);
    }

    if ((AMERGE_STATE_RUNNING == pAmergeCtx->state) || (AMERGE_STATE_LOCKED == pAmergeCtx->state)) {
        return (XCAM_RETURN_ERROR_FAILED);
    }

    pAmergeCtx->state = AMERGE_STATE_RUNNING;

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);
    return (XCAM_RETURN_NO_ERROR);
}
/******************************************************************************
 * AmergeStop()
 *****************************************************************************/
XCamReturn AmergeStop(AmergeContext_t* pAmergeCtx) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    // initial checks
    if (pAmergeCtx == NULL) {
        return (XCAM_RETURN_ERROR_MEM);
    }

    // before stopping, unlock the AHDR if locked
    if (AMERGE_STATE_LOCKED == pAmergeCtx->state) {
        return (XCAM_RETURN_ERROR_FAILED);
    }

    pAmergeCtx->state = AMERGE_STATE_STOPPED;

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);

    return (XCAM_RETURN_NO_ERROR);
}

/******************************************************************************
 * GetCurrPara()
 *****************************************************************************/
float GetCurrPara(float inPara, float* inMatrixX, float* inMatrixY, int Max_Knots) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);
    float x1      = 0.0f;
    float x2      = 0.0f;
    float value1  = 0.0f;
    float value2  = 0.0f;
    float outPara = 0.0f;

    if (inPara < inMatrixX[0])
        outPara = inMatrixY[0];
    else if (inPara >= inMatrixX[Max_Knots - 1])
        outPara = inMatrixY[Max_Knots - 1];
    else
        for (int i = 0; i < Max_Knots - 1; i++) {
            if (inPara >= inMatrixX[i] && inPara < inMatrixX[i + 1]) {
                x1      = inMatrixX[i];
                x2      = inMatrixX[i + 1];
                value1  = inMatrixY[i];
                value2  = inMatrixY[i + 1];
                outPara = value1 + (inPara - x1) * (value1 - value2) / (x1 - x2);
                break;
            } else
                continue;
        }

    return outPara;
    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);
}

void AmergeGetEnvLv(AmergeContext_t* pAmergeCtx, AecPreResult_t AecHdrPreResult) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    // get Ae Pre Result
    pAmergeCtx->AeResult.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[AecHdrPreResult.NormalIndex];

    // transfer AeResult data into AhdrHandle
    switch (pAmergeCtx->FrameNumber) {
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

    // Normalize the current envLv for AEC
    pAmergeCtx->CurrData.CtrlData.EnvLv =
        (pAmergeCtx->AeResult.GlobalEnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
    pAmergeCtx->CurrData.CtrlData.EnvLv =
        LIMIT_VALUE(pAmergeCtx->CurrData.CtrlData.EnvLv, ENVLVMAX, ENVLVMIN);

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);
}

void AmergeGetSensorInfo(AmergeContext_t* pAmergeCtx, AecProcResult_t AecHdrProcResult) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    pAmergeCtx->SensorInfo.LongFrmMode =
        AecHdrProcResult.LongFrmMode && (pAmergeCtx->FrameNumber != LINEAR_NUM);

    for (int i = 0; i < 3; i++) {
        pAmergeCtx->SensorInfo.HdrMinGain[i]            = AecHdrProcResult.HdrMinGain[i];
        pAmergeCtx->SensorInfo.HdrMaxGain[i]            = AecHdrProcResult.HdrMaxGain[i];
        pAmergeCtx->SensorInfo.HdrMinIntegrationTime[i] = AecHdrProcResult.HdrMinIntegrationTime[i];
        pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[i] = AecHdrProcResult.HdrMaxIntegrationTime[i];
    }

    if (pAmergeCtx->FrameNumber == HDR_2X_NUM) {
        pAmergeCtx->SensorInfo.MaxExpoL =
            pAmergeCtx->SensorInfo.HdrMaxGain[1] * pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[1];
        pAmergeCtx->SensorInfo.MinExpoL =
            pAmergeCtx->SensorInfo.HdrMinGain[1] * pAmergeCtx->SensorInfo.HdrMinIntegrationTime[1];
        pAmergeCtx->SensorInfo.MaxExpoM = 0;
        pAmergeCtx->SensorInfo.MinExpoM = 0;
    } else if (pAmergeCtx->FrameNumber == HDR_3X_NUM) {
        pAmergeCtx->SensorInfo.MaxExpoL =
            pAmergeCtx->SensorInfo.HdrMaxGain[2] * pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[2];
        pAmergeCtx->SensorInfo.MinExpoL =
            pAmergeCtx->SensorInfo.HdrMinGain[2] * pAmergeCtx->SensorInfo.HdrMinIntegrationTime[2];
        pAmergeCtx->SensorInfo.MaxExpoM =
            pAmergeCtx->SensorInfo.HdrMaxGain[1] * pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[1];
        pAmergeCtx->SensorInfo.MinExpoM =
            pAmergeCtx->SensorInfo.HdrMinGain[1] * pAmergeCtx->SensorInfo.HdrMinIntegrationTime[1];
    }

    pAmergeCtx->SensorInfo.MaxExpoS =
        pAmergeCtx->SensorInfo.HdrMaxGain[0] * pAmergeCtx->SensorInfo.HdrMaxIntegrationTime[0];
    pAmergeCtx->SensorInfo.MinExpoS =
        pAmergeCtx->SensorInfo.HdrMinGain[0] * pAmergeCtx->SensorInfo.HdrMinIntegrationTime[0];

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * CalibrateOECurve()
 *****************************************************************************/
void CalibrateOECurve(float smooth, float offset, unsigned short* OECurve) {
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    int step    = 32;
    float curve = 0.0;
    float k     = 511;

    for (int i = 0; i < HDRMGE_V12_OE_CURVE_NUM; ++i) {
        curve      = 1 + exp(-smooth * (k / 1023 - offset / 256));
        curve      = 1024 / curve;
        OECurve[i] = round(curve);
        OECurve[i] = MIN(OECurve[i], 1023);
        k += step;
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * CalibrateEachChnCurve()
 *****************************************************************************/
void CalibrateEachChnCurve(float smooth, float offset, unsigned short* OECurve) {
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    int step    = 64;
    float curve = 0.0;
    float k     = 0;

    for (int i = 0; i < HDRMGE_V12_OE_CURVE_NUM; ++i) {
        curve      = 1 + exp(-smooth * (k / 1023 - offset / 256));
        curve      = 1024 / curve;
        OECurve[i] = round(curve);
        OECurve[i] = MIN(OECurve[i], 1023);
        k += step;
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * CalibrateMDCurveLongFrmMode()
 *****************************************************************************/
void CalibrateMDCurveLongFrmMode(float smooth, float offset, unsigned short* MDCurve) {
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    int step    = 16;
    float curve = 0.0;
    float k     = 0;

    for (int i = 0; i < HDRMGE_V12_MD_CURVE_NUM; ++i) {
        curve      = 1 + exp(-smooth * (k / 1023 - offset / 256));
        curve      = 1024 / curve;
        MDCurve[i] = round(curve);
        MDCurve[i] = MIN(MDCurve[i], 1023);
        k += step;
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}
/******************************************************************************
 * CalibrateMDCurveShortFrmMode()
 *****************************************************************************/
void CalibrateMDCurveShortFrmMode(float smooth, float offset, unsigned short* MDCurveLM,
                                  unsigned short* MDCurveMS) {
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    float step  = 1.0 / 16.0;
    float curve = 0.0;

    for (int i = 0; i < HDRMGE_V12_MD_CURVE_NUM; ++i) {
        curve        = 0.01 + pow(i * step, 2.0f);
        curve        = 1024.0 * pow(i * step, 2.0f) / curve;
        MDCurveLM[i] = round(curve);
        MDCurveLM[i] = MIN(MDCurveLM[i], 1023);
        MDCurveMS[i] = MDCurveLM[i];
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}
/******************************************************************************
 * AmergeGetTuningProcResV12()
 *****************************************************************************/
void AmergeGetTuningProcResV12(AmergeContext_t* pAmergeCtx) {
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    pAmergeCtx->ProcRes.Merge_v12.mode   = pAmergeCtx->CurrData.HandleData.Merge_v12.MergeMode;
    pAmergeCtx->ProcRes.Merge_v12.s_base = pAmergeCtx->CurrData.HandleData.Merge_v12.BaseFrm;
    pAmergeCtx->ProcRes.Merge_v12.each_raw_en =
        pAmergeCtx->CurrData.HandleData.Merge_v12.EnableEachChn;
    pAmergeCtx->ProcRes.Merge_v12.lm_dif_0p9 = SW_HDRMGE_LM_DIF_0P9_FIX;
    pAmergeCtx->ProcRes.Merge_v12.ms_dif_0p8 = SW_HDRMGE_MS_DIF_0P8_FIX;
    pAmergeCtx->ProcRes.Merge_v12.lm_dif_0p15 =
        (int)pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_offset;
    pAmergeCtx->ProcRes.Merge_v12.ms_dif_0p15 =
        (int)pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_offset;

    CalibrateOECurve(pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_smooth,
                     pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_offset,
                     pAmergeCtx->ProcRes.Merge_v12.e_y);
    if (pAmergeCtx->CurrData.HandleData.Merge_v12.BaseFrm == BASEFRAME_LONG) {
        CalibrateMDCurveLongFrmMode(pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_smooth,
                                    pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_offset,
                                    pAmergeCtx->ProcRes.Merge_v12.l1_y);
        CalibrateMDCurveLongFrmMode(pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_smooth,
                                    pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_offset,
                                    pAmergeCtx->ProcRes.Merge_v12.l0_y);
    } else if (pAmergeCtx->CurrData.HandleData.Merge_v12.BaseFrm == BASEFRAME_SHORT)
        CalibrateMDCurveShortFrmMode(pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_smooth,
                                     pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_offset,
                                     pAmergeCtx->ProcRes.Merge_v12.l1_y,
                                     pAmergeCtx->ProcRes.Merge_v12.l0_y);

    // merge v12 add
    CalibrateEachChnCurve(pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_smooth,
                          pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_offset,
                          pAmergeCtx->ProcRes.Merge_v12.l_raw0);
    CalibrateEachChnCurve(pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_smooth,
                          pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_offset,
                          pAmergeCtx->ProcRes.Merge_v12.l_raw1);

    if (pAmergeCtx->SensorInfo.LongFrmMode) {
        for (int i = 0; i < HDRMGE_V12_OE_CURVE_NUM; i++)
            pAmergeCtx->ProcRes.Merge_v12.e_y[i] = HDR_LONG_FRMAE_MODE_OECURVE;
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * MergeDampingV12()
 *****************************************************************************/
void MergeDampingV12(AmergeContext_t* pAmergeCtx) {
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    float OEDamp         = pAmergeCtx->CurrData.CtrlData.MergeOEDamp;
    float MDDampLM       = pAmergeCtx->CurrData.CtrlData.MergeMDDampLM;
    float MDDampMS       = pAmergeCtx->CurrData.CtrlData.MergeMDDampMS;
    bool ifHDRModeChange = false;

    ifHDRModeChange = pAmergeCtx->CurrData.HandleData.Merge_v12.MergeMode ==
                              pAmergeCtx->PrevData.HandleData.Merge_v12.MergeMode
                          ? false
                          : true;

    // get finnal current data
    if (pAmergeCtx->mergeAttrV12.opMode == MERGE_OPMODE_AUTO && pAmergeCtx->frameCnt != 0 &&
        !ifHDRModeChange) {
        pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_smooth =
            OEDamp * pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_smooth +
            (1 - OEDamp) * pAmergeCtx->PrevData.HandleData.Merge_v12.OECurve_smooth;
        pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_offset =
            OEDamp * pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_offset +
            (1 - OEDamp) * pAmergeCtx->PrevData.HandleData.Merge_v12.OECurve_offset;
        pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_smooth =
            MDDampLM * pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_smooth +
            (1 - MDDampLM) * pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurveLM_smooth;
        pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_offset =
            MDDampLM * pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_offset +
            (1 - MDDampLM) * pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurveLM_offset;
        pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_smooth =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_smooth +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurveMS_smooth;
        pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_offset =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_offset +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurveMS_offset;

        pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_Coef =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_Coef +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurve_Coef;
        pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_ms_thd0 =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_ms_thd0 +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurve_ms_thd0;
        pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_lm_thd0 =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_lm_thd0 +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurve_lm_thd0;
    }

    LOGD_AMERGE("%s: Current BaseFrm:%d OECurve_smooth:%f OECurve_offset:%f \n", __FUNCTION__,
                pAmergeCtx->CurrData.HandleData.Merge_v12.BaseFrm,
                pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_smooth,
                pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_offset);
    if (pAmergeCtx->CurrData.HandleData.Merge_v12.BaseFrm == BASEFRAME_LONG) {
        LOGD_AMERGE(
            "%s: Current MDCurveMS_smooth:%f MDCurveMS_offset:%f MDCurveLM_smooth:%f "
            "MDCurveLM_offset:%f \n",
            __FUNCTION__, pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_smooth,
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_smooth,
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_offset,
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_smooth,
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_offset);
        LOGD_AMERGE("%s: Current EnableEachChn:%d EachChnCurve_smooth:%f EachChnCurve_offset:%f\n",
                    __FUNCTION__, pAmergeCtx->CurrData.HandleData.Merge_v12.EnableEachChn,
                    pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_smooth,
                    pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_offset);
    } else if (pAmergeCtx->CurrData.HandleData.Merge_v12.BaseFrm == BASEFRAME_SHORT) {
        LOGD_AMERGE("%s: Current MDCurve_Coef:%f MDCurve_ms_thd0:%f MDCurve_lm_thd0:%f\n",
                    __FUNCTION__, pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_Coef,
                    pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_ms_thd0,
                    pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_lm_thd0);
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeTuningProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
void AmergeTuningProcessing(AmergeContext_t* pAmergeCtx) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    if (pAmergeCtx->mergeAttrV12.opMode == MERGE_OPMODE_AUTO) {
        pAmergeCtx->CurrData.HandleData.Merge_v12.BaseFrm =
            pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.BaseFrm;
        if (pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.BaseFrm == BASEFRAME_LONG) {
            // get Current merge OECurve
            pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_smooth = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.OECurve.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.OECurve.Smooth,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.OECurve.EnvLv_len);
            pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_offset = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.OECurve.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.OECurve.Offset,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.OECurve.EnvLv_len);

            // get Current merge MDCurve
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_smooth = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.LM_smooth,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve
                    .MoveCoef_len);
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_offset = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.LM_offset,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve
                    .MoveCoef_len);
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_smooth = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MS_smooth,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve
                    .MoveCoef_len);
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_offset = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MS_offset,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurve
                    .MoveCoef_len);

            // get Current merge each channel
            pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_smooth = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.EachChnCurve.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.EachChnCurve.Smooth,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.EachChnCurve
                    .EnvLv_len);
            pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_offset = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.EachChnCurve.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.EachChnCurve.Offset,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.EachChnCurve
                    .EnvLv_len);

            pAmergeCtx->CurrData.HandleData.Merge_v12.EnableEachChn =
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.EnableEachChn;
            pAmergeCtx->CurrData.CtrlData.MergeOEDamp =
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.OECurve_damp;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampLM =
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurveLM_damp;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampMS =
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.LongFrmModeData.MDCurveMS_damp;
        } else if (pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.BaseFrm == BASEFRAME_SHORT) {
            // get Current merge OECurve
            pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_smooth = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.Smooth,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.EnvLv_len);
            pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_offset = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.EnvLv,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.Offset,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.EnvLv_len);

            // get Current merge MDCurve
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_Coef = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.Coef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve
                    .MoveCoef_len);
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_ms_thd0 = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.ms_thd0,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve
                    .MoveCoef_len);
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_lm_thd0 = GetCurrPara(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.lm_thd0,
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve
                    .MoveCoef_len);

            pAmergeCtx->CurrData.CtrlData.MergeOEDamp =
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.OECurve_damp;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampLM =
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve_damp;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampMS =
                pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve_damp;
        }
    } else if (pAmergeCtx->mergeAttrV12.opMode == MERGE_OPMODE_MANUAL) {
        pAmergeCtx->CurrData.HandleData.Merge_v12.BaseFrm =
            pAmergeCtx->mergeAttrV12.stManual.BaseFrm;
        if (pAmergeCtx->mergeAttrV12.stManual.BaseFrm == BASEFRAME_LONG) {
            // get Current merge OECurve
            pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_smooth =
                pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.OECurve.Smooth;
            pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_offset =
                pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.OECurve.Offset;

            // get Current merge MDCurve
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_smooth =
                pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.MDCurve.LM_smooth;
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveLM_offset =
                pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.MDCurve.LM_offset;
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_smooth =
                pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.MDCurve.MS_smooth;
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurveMS_offset =
                pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.MDCurve.MS_offset;

            // get Current merge each channel
            pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_smooth =
                pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.EachChnCurve.Smooth;
            pAmergeCtx->CurrData.HandleData.Merge_v12.EachChnCurve_offset =
                pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.EachChnCurve.Offset;

            pAmergeCtx->CurrData.HandleData.Merge_v12.EnableEachChn =
                pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.EnableEachChn;
            pAmergeCtx->CurrData.CtrlData.MergeOEDamp   = 1;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampLM = 1;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampMS = 1;
        } else if (pAmergeCtx->mergeAttrV12.stManual.BaseFrm == BASEFRAME_SHORT) {
            // get Current merge OECurve
            pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_smooth =
                pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.OECurve.Smooth;
            pAmergeCtx->CurrData.HandleData.Merge_v12.OECurve_offset =
                pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.OECurve.Offset;

            // get Current merge MDCurve
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_Coef =
                pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.MDCurve.Coef;
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_ms_thd0 =
                pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.MDCurve.ms_thd0;
            pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_lm_thd0 =
                pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.MDCurve.lm_thd0;

            pAmergeCtx->CurrData.CtrlData.MergeOEDamp   = 1;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampLM = 1;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampMS = 1;
        }
    }

    // transfer data to api
    // transfer control data to api
    pAmergeCtx->mergeAttrV12.CtlInfo.Envlv    = pAmergeCtx->CurrData.CtrlData.EnvLv;
    pAmergeCtx->mergeAttrV12.CtlInfo.MoveCoef = pAmergeCtx->CurrData.CtrlData.MoveCoef;

    // merge damp
    MergeDampingV12(pAmergeCtx);

    // get current IO data
    AmergeGetTuningProcResV12(pAmergeCtx);

    // store current handle data to pre data for next loop
    pAmergeCtx->PrevData.CtrlData.EnvLv    = pAmergeCtx->CurrData.CtrlData.EnvLv;
    pAmergeCtx->PrevData.CtrlData.MoveCoef = pAmergeCtx->CurrData.CtrlData.MoveCoef;
    memcpy(&pAmergeCtx->PrevData.HandleData, &pAmergeCtx->CurrData.HandleData,
           sizeof(MergeHandleData_s));

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeExpoProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
void AmergeExpoProcessing(AmergeContext_t* pAmergeCtx, MergeExpoData_t* pExpoData) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    // get sw_hdrmge_gain0
    pAmergeCtx->ProcRes.Merge_v12.gain0 = (int)(64 * pExpoData->nextRatioLS);
    if (pExpoData->nextRatioLS == 1)
        pAmergeCtx->ProcRes.Merge_v12.gain0_inv = (int)(4096 * (1 / pExpoData->nextRatioLS) - 1);
    else
        pAmergeCtx->ProcRes.Merge_v12.gain0_inv = (int)(4096 * (1 / pExpoData->nextRatioLS));

    // get sw_hdrmge_gain1
    pAmergeCtx->ProcRes.Merge_v12.gain1     = SW_HDRMGE_GAIN_FIX;
    pAmergeCtx->ProcRes.Merge_v12.gain1_inv = SW_HDRMGE_GAIN_INV_FIX;

    // get sw_hdrmge_gain2
    pAmergeCtx->ProcRes.Merge_v12.gain2 = SW_HDRMGE_GAIN_FIX;

    // merge v11 add
    float Coef = pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_Coef / SHORT_MODE_COEF_MAX;
    float sw_hdrmge_ms_thd0 = pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_ms_thd0;
    float sw_hdrmge_lm_thd0 = pAmergeCtx->CurrData.HandleData.Merge_v12.MDCurve_lm_thd0;
    float sw_hdrmge_ms_thd1 = 1024 * pow(100 * Coef * pExpoData->nextSGain, 0.5f);
    float sw_hdrmge_lm_thd1 = 1024 * pow(100 * Coef * pExpoData->nextMGain, 0.5f);
    float sw_hdrmge_ms_scl  = (sw_hdrmge_ms_thd1 == sw_hdrmge_ms_thd0)
                                 ? 0
                                 : (1 / (sw_hdrmge_ms_thd1 - sw_hdrmge_ms_thd0));
    float sw_hdrmge_lm_scl = (sw_hdrmge_lm_thd1 == sw_hdrmge_lm_thd0)
                                 ? 0
                                 : (1 / (sw_hdrmge_lm_thd1 - sw_hdrmge_lm_thd0));
    pAmergeCtx->ProcRes.Merge_v12.ms_thd0 = (int)(1024 * sw_hdrmge_ms_thd0);
    pAmergeCtx->ProcRes.Merge_v12.ms_thd1 = (int)(1024 * sw_hdrmge_ms_thd1);
    pAmergeCtx->ProcRes.Merge_v12.ms_scl  = (int)(64 * sw_hdrmge_ms_scl);
    pAmergeCtx->ProcRes.Merge_v12.lm_thd0 = (int)(1024 * sw_hdrmge_lm_thd0);
    pAmergeCtx->ProcRes.Merge_v12.lm_thd1 = (int)(1024 * sw_hdrmge_lm_thd1);
    pAmergeCtx->ProcRes.Merge_v12.lm_scl  = (int)(64 * sw_hdrmge_lm_scl);

    // merge v12 add
    pAmergeCtx->ProcRes.Merge_v12.each_raw_gain0 =
        (int)(64 * pExpoData->nextRatioLS);  // ratio between middle and short
    pAmergeCtx->ProcRes.Merge_v12.each_raw_gain1 =
        SW_HDRMGE_GAIN_FIX;  // ratio between middle and long

    LOGV_AMERGE(
        "%s: sw_hdrmge_mode:%d sw_hdrmge_ms_dif_0p8:%d sw_hdrmge_lm_dif_0p9:%d "
        "sw_hdrmge_ms_dif_0p15:%d sw_hdrmge_lm_dif_0p15:%d\n",
        __FUNCTION__, pAmergeCtx->ProcRes.Merge_v12.mode, pAmergeCtx->ProcRes.Merge_v12.ms_dif_0p8,
        pAmergeCtx->ProcRes.Merge_v12.lm_dif_0p9, pAmergeCtx->ProcRes.Merge_v12.ms_dif_0p15,
        pAmergeCtx->ProcRes.Merge_v12.lm_dif_0p15);
    LOGV_AMERGE(
        "%s: nextRatioLS:%f sw_hdrmge_gain0:%d sw_hdrmge_gain0_inv:%d nextRatioLM:%f "
        "sw_hdrmge_gain1:%d sw_hdrmge_gain1_inv:%d sw_hdrmge_gain2:%d\n",
        __FUNCTION__, pExpoData->nextRatioLS, pAmergeCtx->ProcRes.Merge_v12.gain0,
        pAmergeCtx->ProcRes.Merge_v12.gain0_inv, pExpoData->nextRatioLM,
        pAmergeCtx->ProcRes.Merge_v12.gain1, pAmergeCtx->ProcRes.Merge_v12.gain1_inv,
        pAmergeCtx->ProcRes.Merge_v12.gain2);
    LOGV_AMERGE("%s: each_raw_gain0:%d each_raw_gain1:%d\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v12.each_raw_gain0,
                pAmergeCtx->ProcRes.Merge_v12.each_raw_gain1);
    LOGV_AMERGE("%s: sw_hdrmge_ms_thd0:%d sw_hdrmge_ms_thd1:%d sw_hdrmge_ms_scl:%d\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v12.ms_thd0, pAmergeCtx->ProcRes.Merge_v12.ms_thd1,
                pAmergeCtx->ProcRes.Merge_v12.ms_scl);
    LOGV_AMERGE("%s: sw_hdrmge_lm_thd0:%d sw_hdrmge_lm_thd1:%d sw_hdrmge_lm_scl:%d\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v12.lm_thd0, pAmergeCtx->ProcRes.Merge_v12.lm_thd1,
                pAmergeCtx->ProcRes.Merge_v12.lm_scl);
    LOGV_AMERGE("%s: sw_hdrmge_e_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                __FUNCTION__, pAmergeCtx->ProcRes.Merge_v12.e_y[0],
                pAmergeCtx->ProcRes.Merge_v12.e_y[1], pAmergeCtx->ProcRes.Merge_v12.e_y[2],
                pAmergeCtx->ProcRes.Merge_v12.e_y[3], pAmergeCtx->ProcRes.Merge_v12.e_y[4],
                pAmergeCtx->ProcRes.Merge_v12.e_y[5], pAmergeCtx->ProcRes.Merge_v12.e_y[6],
                pAmergeCtx->ProcRes.Merge_v12.e_y[7], pAmergeCtx->ProcRes.Merge_v12.e_y[8],
                pAmergeCtx->ProcRes.Merge_v12.e_y[9], pAmergeCtx->ProcRes.Merge_v12.e_y[10],
                pAmergeCtx->ProcRes.Merge_v12.e_y[11], pAmergeCtx->ProcRes.Merge_v12.e_y[12],
                pAmergeCtx->ProcRes.Merge_v12.e_y[13], pAmergeCtx->ProcRes.Merge_v12.e_y[14],
                pAmergeCtx->ProcRes.Merge_v12.e_y[15], pAmergeCtx->ProcRes.Merge_v12.e_y[16]);
    LOGV_AMERGE("%s: sw_hdrmge_l0_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                __FUNCTION__, pAmergeCtx->ProcRes.Merge_v12.l0_y[0],
                pAmergeCtx->ProcRes.Merge_v12.l0_y[1], pAmergeCtx->ProcRes.Merge_v12.l0_y[2],
                pAmergeCtx->ProcRes.Merge_v12.l0_y[3], pAmergeCtx->ProcRes.Merge_v12.l0_y[4],
                pAmergeCtx->ProcRes.Merge_v12.l0_y[5], pAmergeCtx->ProcRes.Merge_v12.l0_y[6],
                pAmergeCtx->ProcRes.Merge_v12.l0_y[7], pAmergeCtx->ProcRes.Merge_v12.l0_y[8],
                pAmergeCtx->ProcRes.Merge_v12.l0_y[9], pAmergeCtx->ProcRes.Merge_v12.l0_y[10],
                pAmergeCtx->ProcRes.Merge_v12.l0_y[11], pAmergeCtx->ProcRes.Merge_v12.l0_y[12],
                pAmergeCtx->ProcRes.Merge_v12.l0_y[13], pAmergeCtx->ProcRes.Merge_v12.l0_y[14],
                pAmergeCtx->ProcRes.Merge_v12.l0_y[15], pAmergeCtx->ProcRes.Merge_v12.l0_y[16]);
    LOGV_AMERGE("%s: sw_hdrmge_l1_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                __FUNCTION__, pAmergeCtx->ProcRes.Merge_v12.l1_y[0],
                pAmergeCtx->ProcRes.Merge_v12.l1_y[1], pAmergeCtx->ProcRes.Merge_v12.l1_y[2],
                pAmergeCtx->ProcRes.Merge_v12.l1_y[3], pAmergeCtx->ProcRes.Merge_v12.l1_y[4],
                pAmergeCtx->ProcRes.Merge_v12.l1_y[5], pAmergeCtx->ProcRes.Merge_v12.l1_y[6],
                pAmergeCtx->ProcRes.Merge_v12.l1_y[7], pAmergeCtx->ProcRes.Merge_v12.l1_y[8],
                pAmergeCtx->ProcRes.Merge_v12.l1_y[9], pAmergeCtx->ProcRes.Merge_v12.l1_y[10],
                pAmergeCtx->ProcRes.Merge_v12.l1_y[11], pAmergeCtx->ProcRes.Merge_v12.l1_y[12],
                pAmergeCtx->ProcRes.Merge_v12.l1_y[13], pAmergeCtx->ProcRes.Merge_v12.l1_y[14],
                pAmergeCtx->ProcRes.Merge_v12.l1_y[15], pAmergeCtx->ProcRes.Merge_v12.l1_y[16]);

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeByPassProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
bool AmergeByPassProcessing(AmergeContext_t* pAmergeCtx, AecPreResult_t AecHdrPreResult) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    bool bypass = false;
    float diff  = 0.0;

    merge_OpMode_t ApiMode = MERGE_OPMODE_AUTO;
    ApiMode                = pAmergeCtx->mergeAttrV12.opMode;

    if (pAmergeCtx->frameCnt <= 2)  // start frame
        bypass = false;
    else if (ApiMode == MERGE_OPMODE_MANUAL)  // api
        bypass = false;
    else if (ApiMode != pAmergeCtx->PrevData.CtrlData.ApiMode)  // api change
        bypass = false;
    else {  // EvnLv change
        // get Current hdr mode
        float ByPassThr = pAmergeCtx->mergeAttrV12.stAuto.MergeTuningPara.ByPassThr;
        pAmergeCtx->CurrData.HandleData.Merge_v12.MergeMode = pAmergeCtx->FrameNumber - 1;
        LOG1_AMERGE("%s:  Current MergeMode: %d \n", __FUNCTION__,
                    pAmergeCtx->CurrData.HandleData.Merge_v12.MergeMode);

        // get envlv from AecPreRes
        AmergeGetEnvLv(pAmergeCtx, AecHdrPreResult);
        pAmergeCtx->CurrData.CtrlData.EnvLv =
            LIMIT_VALUE(pAmergeCtx->CurrData.CtrlData.EnvLv, ENVLVMAX, ENVLVMIN);

        pAmergeCtx->CurrData.CtrlData.MoveCoef = MOVE_COEF_DEFAULT;
        pAmergeCtx->CurrData.CtrlData.MoveCoef =
            LIMIT_VALUE(pAmergeCtx->CurrData.CtrlData.MoveCoef, MOVECOEFMAX, MOVECOEFMIN);

        // use Envlv for now
        diff = pAmergeCtx->PrevData.CtrlData.EnvLv - pAmergeCtx->CurrData.CtrlData.EnvLv;
        if (pAmergeCtx->PrevData.CtrlData.EnvLv == 0.0) {
            diff = pAmergeCtx->CurrData.CtrlData.EnvLv;
            if (diff == 0.0)
                bypass = true;
            else
                bypass = false;
        } else {
            diff /= pAmergeCtx->PrevData.CtrlData.EnvLv;
            if (diff >= ByPassThr || diff <= (0 - ByPassThr))
                bypass = false;
            else
                bypass = true;
        }
    }

    LOGD_AMERGE(
        "%s: FrameID:%d HDRFrameNum:%d LongFrmMode:%d MergeApiMode:%d EnvLv:%f MoveCoef:%f "
        "bypass:%d\n",
        __FUNCTION__, pAmergeCtx->frameCnt, pAmergeCtx->FrameNumber,
        pAmergeCtx->SensorInfo.LongFrmMode, ApiMode, pAmergeCtx->CurrData.CtrlData.EnvLv,
        pAmergeCtx->CurrData.CtrlData.MoveCoef, bypass);

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);
    return bypass;
}

/******************************************************************************
 * AmergeInit()
 *****************************************************************************/
XCamReturn AmergeInit(AmergeContext_t** ppAmergeCtx, CamCalibDbV2Context_t* pCalibV2) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    XCamReturn result = XCAM_RETURN_NO_ERROR;

    AmergeContext_t* pAmergeCtx;
    pAmergeCtx = (AmergeContext_t*)malloc(sizeof(AmergeContext_t));
    if (pAmergeCtx == NULL) {
        LOGE_ATMO("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_MEM;
    }

    memset(pAmergeCtx, 0x00, sizeof(AmergeContext_t));
    *ppAmergeCtx      = pAmergeCtx;
    pAmergeCtx->state = AMERGE_STATE_INITIALIZED;

    CalibDbV2_merge_V12_t* calibv2_amerge_calib =
        (CalibDbV2_merge_V12_t*)(CALIBDBV2_GET_MODULE_PTR(pCalibV2, amerge_calib));

    memcpy(&pAmergeCtx->CalibDBV12, calibv2_amerge_calib,
           sizeof(CalibDbV2_merge_V12_t));  // load iq paras
    memcpy(&pAmergeCtx->mergeAttrV12.stAuto, calibv2_amerge_calib,
           sizeof(CalibDbV2_merge_V12_t));  // set  default stAuto

    // set default para
    // config default PrevData data
    pAmergeCtx->PrevData.CtrlData.EnvLv                        = 0;
    pAmergeCtx->PrevData.CtrlData.MoveCoef                     = 0;
    pAmergeCtx->PrevData.CtrlData.ApiMode                      = MERGE_OPMODE_AUTO;
    pAmergeCtx->PrevData.HandleData.Merge_v12.MergeMode        = 1;
    pAmergeCtx->PrevData.HandleData.Merge_v12.OECurve_smooth   = 80;
    pAmergeCtx->PrevData.HandleData.Merge_v12.OECurve_offset   = 210;
    pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurveLM_smooth = 80;
    pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurveLM_offset = 38;
    pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurveMS_smooth = 80;
    pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurveMS_offset = 38;
    pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurve_Coef     = 0.05;
    pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurve_ms_thd0  = 0;
    pAmergeCtx->PrevData.HandleData.Merge_v12.MDCurve_lm_thd0  = 0;

    // set default ctrl info
    pAmergeCtx->mergeAttrV12.opMode           = MERGE_OPMODE_AUTO;
    pAmergeCtx->mergeAttrV12.CtlInfo.Envlv    = 1.0;
    pAmergeCtx->mergeAttrV12.CtlInfo.MoveCoef = 0.0;

    pAmergeCtx->mergeAttrV12.stManual.BaseFrm                           = BASEFRAME_LONG;
    pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.OECurve.Smooth    = 0.4;
    pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.OECurve.Offset    = 210;
    pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.MDCurve.LM_smooth = 0.4;
    pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.MDCurve.LM_offset = 38;
    pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.MDCurve.MS_smooth = 0.4;
    pAmergeCtx->mergeAttrV12.stManual.LongFrmModeData.MDCurve.MS_offset = 38;

    pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.OECurve.Smooth  = 0.4;
    pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.OECurve.Offset  = 210;
    pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.MDCurve.Coef    = 0.05;
    pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.MDCurve.ms_thd0 = 0.00;
    pAmergeCtx->mergeAttrV12.stManual.ShortFrmModeData.MDCurve.lm_thd0 = 0.00;

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);
    return (result);
}
/******************************************************************************
 * AmergeRelease()
 *****************************************************************************/
XCamReturn AmergeRelease(AmergeContext_t* pAmergeCtx) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    // initial checks
    if (NULL == pAmergeCtx) {
        return (XCAM_RETURN_ERROR_MEM);
    }

    result = AmergeStop(pAmergeCtx);
    if (result != XCAM_RETURN_NO_ERROR) {
        LOGE_AMERGE("%s: Amerge Stop() failed!\n", __FUNCTION__);
        return (result);
    }

    // check state
    if ((AMERGE_STATE_RUNNING == pAmergeCtx->state) || (AMERGE_STATE_LOCKED == pAmergeCtx->state)) {
        return (XCAM_RETURN_ERROR_FAILED);
    }
    free(pAmergeCtx);
    pAmergeCtx = NULL;

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);

    return (result);
}
