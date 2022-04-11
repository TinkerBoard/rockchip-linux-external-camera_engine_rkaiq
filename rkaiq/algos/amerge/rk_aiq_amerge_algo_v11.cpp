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
 * @file rk_aiq_amerge_algo_v11.cpp
 *
 * @brief
 *   ADD_DESCRIPTION_HERE
 *
 *****************************************************************************/
//#include "math.h"
#include "rk_aiq_types_amerge_algo_int.h"
#include "rk_aiq_types_amerge_algo_prvt.h"
#include "xcam_log.h"
#include "mathlib.h"

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
 * GetCurrParaV11()
 *****************************************************************************/
float GetCurrParaV11(float inPara, float* inMatrixX, float* inMatrixY, int Max_Knots) {
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
/******************************************************************************
 * AmergeGetEnvLvV11()
 *****************************************************************************/
void AmergeGetEnvLvV11(AmergeContext_t* pAmergeCtx, AecPreResult_t AecHdrPreResult) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    // transfer AeResult data into AhdrHandle
    switch (pAmergeCtx->FrameNumber) {
        case LINEAR_NUM:
            pAmergeCtx->CurrData.CtrlData.EnvLv = AecHdrPreResult.GlobalEnvLv[0];
            break;
        case HDR_2X_NUM:
            pAmergeCtx->CurrData.CtrlData.EnvLv = AecHdrPreResult.GlobalEnvLv[1];
            break;
        case HDR_3X_NUM:
            pAmergeCtx->CurrData.CtrlData.EnvLv = AecHdrPreResult.GlobalEnvLv[1];
            break;
        default:
            LOGE_AMERGE("%s:  Wrong frame number in HDR mode!!!\n", __FUNCTION__);
            break;
    }

    // Normalize the current envLv for AEC
    pAmergeCtx->CurrData.CtrlData.EnvLv =
        (pAmergeCtx->CurrData.CtrlData.EnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
    pAmergeCtx->CurrData.CtrlData.EnvLv =
        LIMIT_VALUE(pAmergeCtx->CurrData.CtrlData.EnvLv, ENVLVMAX, ENVLVMIN);

    LOG1_AMERGE("%s:exit!\n", __FUNCTION__);
}
/******************************************************************************
 * CalibrateOECurveV11()
 *****************************************************************************/
void CalibrateOECurveV11(float smooth, float offset, unsigned short* OECurve) {
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    int step    = 32;
    float curve = 0.0f;
    float k     = 511.0f;

    for (int i = 0; i < HDRMGE_V11_OE_CURVE_NUM; ++i) {
        curve      = 1 + exp(-smooth * OECURVESMOOTHMAX * (k / 1023.0f - offset / 256.0f));
        curve      = 1024.0f / curve;
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
    float curve = 0.0f;
    float k     = 0.0f;

    for (int i = 0; i < HDRMGE_V11_MD_CURVE_NUM; ++i) {
        curve      = 1 + exp(-smooth * MDCURVESMOOTHMAX *
                        (k / 1023.0f - offset * MDCURVEOFFSETMAX / 256.0f));
        curve      = 1024.0f / curve;
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

    for (int i = 0; i < HDRMGE_V11_MD_CURVE_NUM; ++i) {
        curve        = 0.01 + pow(i * step, 2.0f);
        curve        = 1024.0 * pow(i * step, 2.0f) / curve;
        MDCurveLM[i] = round(curve);
        MDCurveLM[i] = MIN(MDCurveLM[i], 1023);
        MDCurveMS[i] = MDCurveLM[i];
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}
/******************************************************************************
 * AmergeGetTuningProcResV11()
 *****************************************************************************/
void AmergeGetTuningProcResV11(AmergeContext_t* pAmergeCtx) {
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_mode =
        pAmergeCtx->CurrData.HandleData.Merge_v11.MergeMode;
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_s_base =
        pAmergeCtx->CurrData.HandleData.Merge_v11.BaseFrm;
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_dif_0p9 = SW_HDRMGE_LM_DIF_0P9_FIX;
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_dif_0p8 = SW_HDRMGE_MS_DIF_0P8_FIX;
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_dif_0p15 =
        (int)(pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_offset * MDCURVEOFFSETMAX);
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_dif_0p15 =
        (int)(pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_offset * MDCURVEOFFSETMAX);

    CalibrateOECurveV11(pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_smooth,
                        pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_offset,
                        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y);
    if (pAmergeCtx->CurrData.HandleData.Merge_v11.BaseFrm == BASEFRAME_LONG) {
        CalibrateMDCurveLongFrmMode(pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_smooth,
                                    pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_offset,
                                    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y);
        CalibrateMDCurveLongFrmMode(pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_smooth,
                                    pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_offset,
                                    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y);
    } else if (pAmergeCtx->CurrData.HandleData.Merge_v11.BaseFrm == BASEFRAME_SHORT)
        CalibrateMDCurveShortFrmMode(pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_smooth,
                                     pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_offset,
                                     pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y,
                                     pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y);

    if (pAmergeCtx->SensorInfo.LongFrmMode) {
        for (int i = 0; i < HDRMGE_V11_OE_CURVE_NUM; i++)
            pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[i] = HDR_LONG_FRMAE_MODE_OECURVE;
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * MergeDampingV11()
 *****************************************************************************/
void MergeDampingV11(AmergeContext_t* pAmergeCtx) {
    LOG1_AMERGE("%s:Enter!\n", __FUNCTION__);

    float OEDamp         = pAmergeCtx->CurrData.CtrlData.MergeOEDamp;
    float MDDampLM       = pAmergeCtx->CurrData.CtrlData.MergeMDDampLM;
    float MDDampMS       = pAmergeCtx->CurrData.CtrlData.MergeMDDampMS;
    bool ifHDRModeChange = false;

    ifHDRModeChange = pAmergeCtx->CurrData.HandleData.Merge_v11.MergeMode ==
                              pAmergeCtx->PrevData.HandleData.Merge_v11.MergeMode
                          ? false
                          : true;

    // get finnal current data
    if (pAmergeCtx->mergeAttrV11.opMode == MERGE_OPMODE_AUTO && pAmergeCtx->frameCnt != 0 &&
        !ifHDRModeChange) {
        pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_smooth =
            OEDamp * pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_smooth +
            (1 - OEDamp) * pAmergeCtx->PrevData.HandleData.Merge_v11.OECurve_smooth;
        pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_offset =
            OEDamp * pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_offset +
            (1 - OEDamp) * pAmergeCtx->PrevData.HandleData.Merge_v11.OECurve_offset;
        pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_smooth =
            MDDampLM * pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_smooth +
            (1 - MDDampLM) * pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurveLM_smooth;
        pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_offset =
            MDDampLM * pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_offset +
            (1 - MDDampLM) * pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurveLM_offset;
        pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_smooth =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_smooth +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurveMS_smooth;
        pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_offset =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_offset +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurveMS_offset;

        pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_Coef =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_Coef +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurve_Coef;
        pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_ms_thd0 =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_ms_thd0 +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurve_ms_thd0;
        pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_lm_thd0 =
            MDDampMS * pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_lm_thd0 +
            (1 - MDDampMS) * pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurve_lm_thd0;
    }

    LOGD_AMERGE("%s: Current BaseFrm:%d OECurve_smooth:%f OECurve_offset:%f \n", __FUNCTION__,
                pAmergeCtx->CurrData.HandleData.Merge_v11.BaseFrm,
                pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_smooth,
                pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_offset);
    if (pAmergeCtx->CurrData.HandleData.Merge_v11.BaseFrm == BASEFRAME_LONG)
        LOGD_AMERGE(
            "%s: Current MDCurveMS_smooth:%f MDCurveMS_offset:%f MDCurveLM_smooth:%f "
            "MDCurveLM_offset:%f \n",
            __FUNCTION__, pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_smooth,
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_offset,
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_smooth,
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_offset);
    else if (pAmergeCtx->CurrData.HandleData.Merge_v11.BaseFrm == BASEFRAME_SHORT) {
        LOGD_AMERGE("%s: Current MDCurve_Coef:%f MDCurve_ms_thd0:%f MDCurve_lm_thd0:%f\n",
                    __FUNCTION__, pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_Coef,
                    pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_ms_thd0,
                    pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_lm_thd0);
    }

    LOG1_AMERGE("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * AmergeTuningProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
void AmergeTuningProcessing(AmergeContext_t* pAmergeCtx) {
    LOG1_AMERGE("%s:enter!\n", __FUNCTION__);

    if (pAmergeCtx->mergeAttrV11.opMode == MERGE_OPMODE_AUTO) {
        pAmergeCtx->CurrData.HandleData.Merge_v11.BaseFrm =
            pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.BaseFrm;
        if (pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.BaseFrm == BASEFRAME_LONG) {
            // get Current merge OECurve
            pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_smooth = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.OECurve.EnvLv,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.OECurve.Smooth,
                MERGE_ENVLV_STEP_MAX);
            pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_offset = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.OECurve.EnvLv,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.OECurve.Offset,
                MERGE_ENVLV_STEP_MAX);

            // get Current merge MDCurve
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_smooth = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.LM_smooth,
                MERGE_ENVLV_STEP_MAX);
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_offset = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.LM_offset,
                MERGE_ENVLV_STEP_MAX);
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_smooth = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MS_smooth,
                MERGE_ENVLV_STEP_MAX);
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_offset = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurve.MS_offset,
                MERGE_ENVLV_STEP_MAX);

            pAmergeCtx->CurrData.CtrlData.MergeOEDamp =
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.OECurve_damp;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampLM =
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurveLM_damp;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampMS =
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.LongFrmModeData.MDCurveMS_damp;
        } else if (pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.BaseFrm == BASEFRAME_SHORT) {
            // get Current merge OECurve
            pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_smooth = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.EnvLv,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.Smooth,
                MERGE_ENVLV_STEP_MAX);
            pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_offset = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.EnvLv,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.EnvLv,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.OECurve.Offset,
                MERGE_ENVLV_STEP_MAX);

            // get Current merge MDCurve
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_Coef = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.Coef,
                MERGE_ENVLV_STEP_MAX);
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_ms_thd0 = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.ms_thd0,
                MERGE_ENVLV_STEP_MAX);
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_lm_thd0 = GetCurrParaV11(
                pAmergeCtx->CurrData.CtrlData.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.MoveCoef,
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve.lm_thd0,
                MERGE_ENVLV_STEP_MAX);

            pAmergeCtx->CurrData.CtrlData.MergeOEDamp =
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.OECurve_damp;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampLM =
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve_damp;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampMS =
                pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ShortFrmModeData.MDCurve_damp;
        }
    } else if (pAmergeCtx->mergeAttrV11.opMode == MERGE_OPMODE_MANUAL) {
        pAmergeCtx->CurrData.HandleData.Merge_v11.BaseFrm =
            pAmergeCtx->mergeAttrV11.stManual.BaseFrm;
        if (pAmergeCtx->mergeAttrV11.stManual.BaseFrm == BASEFRAME_LONG) {
            // get Current merge OECurve
            pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_smooth =
                pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.OECurve.Smooth;
            pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_offset =
                pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.OECurve.Offset;

            // get Current merge MDCurve
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_smooth =
                pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.MDCurve.LM_smooth;
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveLM_offset =
                pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.MDCurve.LM_offset;
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_smooth =
                pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.MDCurve.MS_smooth;
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurveMS_offset =
                pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.MDCurve.MS_offset;

            pAmergeCtx->CurrData.CtrlData.MergeOEDamp   = 1;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampLM = 1;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampMS = 1;
        } else if (pAmergeCtx->mergeAttrV11.stManual.BaseFrm == BASEFRAME_SHORT) {
            // get Current merge OECurve
            pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_smooth =
                pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.OECurve.Smooth;
            pAmergeCtx->CurrData.HandleData.Merge_v11.OECurve_offset =
                pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.OECurve.Offset;

            // get Current merge MDCurve
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_Coef =
                pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.MDCurve.Coef;
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_ms_thd0 =
                pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.MDCurve.ms_thd0;
            pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_lm_thd0 =
                pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.MDCurve.lm_thd0;

            pAmergeCtx->CurrData.CtrlData.MergeOEDamp   = 1;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampLM = 1;
            pAmergeCtx->CurrData.CtrlData.MergeMDDampMS = 1;
        }
    }

    // transfer data to api
    // transfer control data to api
    pAmergeCtx->mergeAttrV11.Info.Envlv    = pAmergeCtx->CurrData.CtrlData.EnvLv;
    pAmergeCtx->mergeAttrV11.Info.MoveCoef = pAmergeCtx->CurrData.CtrlData.MoveCoef;

    // merge damp
    MergeDampingV11(pAmergeCtx);

    // get current IO data
    AmergeGetTuningProcResV11(pAmergeCtx);

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
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain0 = (int)(64 * pExpoData->nextRatioLS);
    if (pExpoData->nextRatioLS == 1)
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain0_inv =
            (int)(4096 * (1 / pExpoData->nextRatioLS) - 1);
    else
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain0_inv =
            (int)(4096 * (1 / pExpoData->nextRatioLS));

    // get sw_hdrmge_gain1
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain1 = (int)(64 * pExpoData->nextRatioLM);
    if (pExpoData->nextRatioLM == 1)
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain1_inv =
            (int)(4096 * (1 / pExpoData->nextRatioLM) - 1);
    else
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain1_inv =
            (int)(4096 * (1 / pExpoData->nextRatioLM));

    // get sw_hdrmge_gain2
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain2 = SW_HDRMGE_GAIN_FIX;

    // isp30 add
    float Coef = pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_Coef / SHORT_MODE_COEF_MAX;
    float sw_hdrmge_ms_thd0 = pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_ms_thd0;
    float sw_hdrmge_lm_thd0 = pAmergeCtx->CurrData.HandleData.Merge_v11.MDCurve_lm_thd0;
    float sw_hdrmge_ms_thd1 = 1024 * pow(100 * Coef * pExpoData->nextSGain, 0.5f);
    float sw_hdrmge_lm_thd1 = 1024 * pow(100 * Coef * pExpoData->nextMGain, 0.5f);
    float sw_hdrmge_ms_scl  = (sw_hdrmge_ms_thd1 == sw_hdrmge_ms_thd0)
                                 ? 0
                                 : (1 / (sw_hdrmge_ms_thd1 - sw_hdrmge_ms_thd0));
    float sw_hdrmge_lm_scl = (sw_hdrmge_lm_thd1 == sw_hdrmge_lm_thd0)
                                 ? 0
                                 : (1 / (sw_hdrmge_lm_thd1 - sw_hdrmge_lm_thd0));
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_thd0 = (int)(1024 * sw_hdrmge_ms_thd0);
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_thd1 = (int)(1024 * sw_hdrmge_ms_thd1);
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_scl  = (int)(64 * sw_hdrmge_ms_scl);
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_thd0 = (int)(1024 * sw_hdrmge_lm_thd0);
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_thd1 = (int)(1024 * sw_hdrmge_lm_thd1);
    pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_scl  = (int)(64 * sw_hdrmge_lm_scl);

    LOGV_AMERGE(
        "%s: sw_hdrmge_mode:%d sw_hdrmge_ms_dif_0p8:%d sw_hdrmge_lm_dif_0p9:%d "
        "sw_hdrmge_ms_dif_0p15:%d sw_hdrmge_lm_dif_0p15:%d\n",
        __FUNCTION__, pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_mode,
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_dif_0p8,
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_dif_0p9,
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_dif_0p15,
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_dif_0p15);
    LOGV_AMERGE(
        "%s: nextRatioLS:%f sw_hdrmge_gain0:%d sw_hdrmge_gain0_inv:%d nextRatioLM:%f "
        "sw_hdrmge_gain1:%d sw_hdrmge_gain1_inv:%d sw_hdrmge_gain2:%d\n",
        __FUNCTION__, pExpoData->nextRatioLS, pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain0,
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain0_inv, pExpoData->nextRatioLM,
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain1,
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain1_inv,
        pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_gain2);
    LOGV_AMERGE("%s: sw_hdrmge_ms_thd0:%d sw_hdrmge_ms_thd1:%d sw_hdrmge_ms_scl:%d\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_thd0,
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_thd1,
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_ms_scl);
    LOGV_AMERGE("%s: sw_hdrmge_lm_thd0:%d sw_hdrmge_lm_thd1:%d sw_hdrmge_lm_scl:%d\n", __FUNCTION__,
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_thd0,
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_thd1,
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_lm_scl);
    LOGV_AMERGE("%s: sw_hdrmge_e_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                __FUNCTION__, pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[0],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[1],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[2],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[3],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[4],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[5],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[6],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[7],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[8],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[9],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[10],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[11],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[12],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[13],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[14],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[15],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_e_y[16]);
    LOGV_AMERGE("%s: sw_hdrmge_l0_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                __FUNCTION__, pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[0],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[1],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[2],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[3],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[4],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[5],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[6],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[7],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[8],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[9],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[10],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[11],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[12],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[13],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[14],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[15],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l0_y[16]);
    LOGV_AMERGE("%s: sw_hdrmge_l1_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                __FUNCTION__, pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[0],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[1],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[2],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[3],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[4],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[5],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[6],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[7],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[8],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[9],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[10],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[11],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[12],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[13],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[14],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[15],
                pAmergeCtx->ProcRes.Merge_v11.sw_hdrmge_l1_y[16]);

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
    ApiMode                = pAmergeCtx->mergeAttrV11.opMode;

    if (pAmergeCtx->frameCnt <= 2)  // start frame
        bypass = false;
    else if (ApiMode == MERGE_OPMODE_MANUAL)  // api
        bypass = false;
    else if (ApiMode != pAmergeCtx->PrevData.CtrlData.ApiMode)  // api change
        bypass = false;
    else {  // EvnLv change
        // get Current hdr mode
        float ByPassThr = pAmergeCtx->mergeAttrV11.stAuto.MergeTuningPara.ByPassThr;
        pAmergeCtx->CurrData.HandleData.Merge_v11.MergeMode = pAmergeCtx->FrameNumber - 1;
        LOG1_AMERGE("%s:  Current MergeMode: %d \n", __FUNCTION__,
                    pAmergeCtx->CurrData.HandleData.Merge_v11.MergeMode);

        // get envlv from AecPreRes
        AmergeGetEnvLvV11(pAmergeCtx, AecHdrPreResult);
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

    CalibDbV2_merge_V11_t* calibv2_amerge_calib =
        (CalibDbV2_merge_V11_t*)(CALIBDBV2_GET_MODULE_PTR(pCalibV2, amerge_calib));
    memcpy(&pAmergeCtx->mergeAttrV11.stAuto, calibv2_amerge_calib,
           sizeof(CalibDbV2_merge_V11_t));  // load iq paras

    // set default para
    // config default PrevData data
    pAmergeCtx->PrevData.CtrlData.EnvLv                        = 0;
    pAmergeCtx->PrevData.CtrlData.MoveCoef                     = 0;
    pAmergeCtx->PrevData.CtrlData.ApiMode                      = MERGE_OPMODE_AUTO;
    pAmergeCtx->PrevData.HandleData.Merge_v11.MergeMode        = 1;
    pAmergeCtx->PrevData.HandleData.Merge_v11.OECurve_smooth   = 0.4;
    pAmergeCtx->PrevData.HandleData.Merge_v11.OECurve_offset   = 210;
    pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurveLM_smooth = 0.4;
    pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurveLM_offset = 0.38;
    pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurveMS_smooth = 0.4;
    pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurveMS_offset = 0.38;
    pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurve_Coef     = 0.05;
    pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurve_ms_thd0  = 0;
    pAmergeCtx->PrevData.HandleData.Merge_v11.MDCurve_lm_thd0  = 0;

    // set default ctrl info
    pAmergeCtx->mergeAttrV11.opMode           = MERGE_OPMODE_AUTO;
    pAmergeCtx->mergeAttrV11.Info.Envlv       = 1.0;
    pAmergeCtx->mergeAttrV11.Info.MoveCoef    = 0.0;

    pAmergeCtx->mergeAttrV11.stManual.BaseFrm                           = BASEFRAME_LONG;
    pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.OECurve.Smooth    = 0.4;
    pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.OECurve.Offset    = 210;
    pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.MDCurve.LM_smooth = 0.4;
    pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.MDCurve.LM_offset = 0.38;
    pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.MDCurve.MS_smooth = 0.4;
    pAmergeCtx->mergeAttrV11.stManual.LongFrmModeData.MDCurve.MS_offset = 0.38;

    pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.OECurve.Smooth  = 0.4;
    pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.OECurve.Offset  = 210;
    pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.MDCurve.Coef    = 0.05;
    pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.MDCurve.ms_thd0 = 0.00;
    pAmergeCtx->mergeAttrV11.stManual.ShortFrmModeData.MDCurve.lm_thd0 = 0.00;

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
