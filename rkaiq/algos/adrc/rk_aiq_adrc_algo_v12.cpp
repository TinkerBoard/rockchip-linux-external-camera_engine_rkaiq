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
 * @file rk_aiq_adrc_algo_v12.cpp
 *
 * @brief
 *   ADD_DESCRIPTION_HERE
 *
 *****************************************************************************/
#include "math.h"
//#include "rk_aiq_types_adrc_algo_int.h"
#include "rk_aiq_types_adrc_algo_prvt.h"
#include "xcam_log.h"

/******************************************************************************
 * AdrcStart()
 *****************************************************************************/
XCamReturn AdrcStart(AdrcContext_t* pAdrcCtx) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // initial checks
    if (pAdrcCtx == NULL) {
        return (XCAM_RETURN_ERROR_MEM);
    }

    if ((ADRC_STATE_RUNNING == pAdrcCtx->state) || (ADRC_STATE_LOCKED == pAdrcCtx->state)) {
        return (XCAM_RETURN_ERROR_PARAM);
    }

    pAdrcCtx->state = ADRC_STATE_RUNNING;

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
    return (XCAM_RETURN_NO_ERROR);
}

/******************************************************************************
 * DrcGetCurrParaV12()
 *****************************************************************************/
float DrcGetCurrParaV12(float inPara, float* inMatrixX, float* inMatrixY, int Max_Knots) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);
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
    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * DrcGetCurrParaV12Int()
 *****************************************************************************/
int DrcGetCurrParaV12Int(float inPara, float* inMatrixX, int* inMatrixY, int Max_Knots) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);
    float x1     = 0.0f;
    float x2     = 0.0f;
    float value1 = 0.0f;
    float value2 = 0.0f;
    int outPara  = 0;

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
                outPara = (int)(value1 + (inPara - x1) * (value1 - value2) / (x1 - x2));
                break;
            } else
                continue;
        }

    return outPara;
    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AdrcStop()
 *****************************************************************************/
XCamReturn AdrcStop(AdrcContext_t* pAdrcCtx) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // initial checks
    if (pAdrcCtx == NULL) {
        return (XCAM_RETURN_ERROR_MEM);
    }

    // before stopping, unlock the AHDR if locked
    if (ADRC_STATE_LOCKED == pAdrcCtx->state) {
        return (XCAM_RETURN_ERROR_PARAM);
    }

    pAdrcCtx->state = ADRC_STATE_STOPPED;

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);

    return (XCAM_RETURN_NO_ERROR);
}

/******************************************************************************
 * CalibrateDrcGainYV12()
 *****************************************************************************/
void CalibrateDrcGainYV12(DrcProcRes_t* para, float DraGain, bool obEnable, float predgain,
                          float alpha) {
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);

    float tmp      = 0;
    float luma[17] = {0,    256,  512,  768,  1024, 1280, 1536, 1792, 2048,
                      2304, 2560, 2816, 3072, 3328, 3584, 3840, 4096};
    float gainTable[17];

    for (int i = 0; i < 17; ++i) {
        tmp = luma[i];
        tmp = -alpha * pow((1 - tmp / 4096), 2);
        if (obEnable)
            gainTable[i] = 1024 * DraGain * pow(DraGain * predgain, tmp);
        else
            gainTable[i] = 1024 * DraGain * pow(DraGain * 1, tmp);
        para->Drc_v12.gain_y[i] = (int)(gainTable[i]);
    }

    LOG1_ATMO("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * SetDefaultValueV12()
 *set default Config data
 *****************************************************************************/
void SetDefaultValueV12(AdrcContext_t* pAdrcCtx) {
    LOGI_ATMO("%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAdrcCtx != NULL);

    // config default PrevData data
    pAdrcCtx->PrevData.frameCnt                           = 0;
    pAdrcCtx->PrevData.EnvLv                              = 0;
    pAdrcCtx->PrevData.MotionCoef                         = 0;
    pAdrcCtx->PrevData.ApiMode                            = DRC_OPMODE_AUTO;
    pAdrcCtx->PrevData.HandleData.Drc_v12.DrcGain         = 4.0;
    pAdrcCtx->PrevData.HandleData.Drc_v12.Alpha           = 0.2;
    pAdrcCtx->PrevData.HandleData.Drc_v12.Clip            = 16.0;
    pAdrcCtx->PrevData.HandleData.Drc_v12.Strength        = 0.01;
    pAdrcCtx->PrevData.HandleData.Drc_v12.LocalWeit       = 1.00;
    pAdrcCtx->PrevData.HandleData.Drc_v12.LocalAutoEnable = 1;
    pAdrcCtx->PrevData.HandleData.Drc_v12.LocalAutoWeit   = 0.037477;
    pAdrcCtx->PrevData.HandleData.Drc_v12.GlobalContrast  = 0;
    pAdrcCtx->PrevData.HandleData.Drc_v12.LoLitContrast   = 0;

    // set default value for api
    pAdrcCtx->drcAttrV12.stManual.Enable                                 = true;
    pAdrcCtx->drcAttrV12.stManual.DrcGain.Alpha                          = 0.1;
    pAdrcCtx->drcAttrV12.stManual.DrcGain.DrcGain                        = 1;
    pAdrcCtx->drcAttrV12.stManual.DrcGain.Clip                           = 1;
    pAdrcCtx->drcAttrV12.stManual.HiLight.HiLightData.Strength           = 0.0;
    pAdrcCtx->drcAttrV12.stManual.HiLight.HiLightData.gas_t              = 0.0;
    pAdrcCtx->drcAttrV12.stManual.HiLight.gas_l0                         = 24;
    pAdrcCtx->drcAttrV12.stManual.HiLight.gas_l1                         = 10;
    pAdrcCtx->drcAttrV12.stManual.HiLight.gas_l2                         = 10;
    pAdrcCtx->drcAttrV12.stManual.HiLight.gas_l3                         = 5;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.LocalWeit       = 1;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.LocalAutoEnable = 1;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.LocalAutoWeit   = 0.5;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.GlobalContrast  = 0.0;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.LoLitContrast   = 0.0;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.MotionData.MotionStr      = 0.0;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.curPixWeit                = 0.376471;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.preFrameWeit              = 0.8;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.Range_force_sgm           = 0.0;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.Range_sgm_cur             = 0.2;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.Range_sgm_pre             = 0.2;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.Space_sgm_cur             = 4068;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.Space_sgm_pre             = 3068;
    pAdrcCtx->drcAttrV12.stManual.LocalSetting.Space_sgm_pre             = 3068;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Mode                   = COMPRESS_AUTO;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[0]        = 0;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[1]        = 558;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[2]        = 1087;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[3]        = 1588;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[4]        = 2063;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[5]        = 2515;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[6]        = 2944;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[7]        = 3353;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[8]        = 3744;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[9]        = 4473;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[10]       = 5139;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[11]       = 5751;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[12]       = 6316;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[13]       = 6838;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[14]       = 7322;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[15]       = 7772;
    pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[16]       = 8192;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[0]                             = 0;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[1]                             = 2;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[2]                             = 20;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[3]                             = 76;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[4]                             = 193;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[5]                             = 381;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[6]                             = 631;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[7]                             = 772;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[8]                             = 919;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[9]                             = 1066;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[10]                            = 1211;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[11]                            = 1479;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[12]                            = 1700;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[13]                            = 1863;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[14]                            = 1968;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[15]                            = 2024;
    pAdrcCtx->drcAttrV12.stManual.Scale_y[16]                            = 2048;
    pAdrcCtx->drcAttrV12.stManual.Edge_Weit                              = 0.02;
    pAdrcCtx->drcAttrV12.stManual.OutPutLongFrame                        = false;
    pAdrcCtx->drcAttrV12.stManual.IIR_frame                              = 2;

    pAdrcCtx->drcAttrV12.Info.ValidParams.Enable                                 = true;
    pAdrcCtx->drcAttrV12.Info.ValidParams.DrcGain.Alpha                          = 0.1;
    pAdrcCtx->drcAttrV12.Info.ValidParams.DrcGain.DrcGain                        = 1;
    pAdrcCtx->drcAttrV12.Info.ValidParams.DrcGain.Clip                           = 1;
    pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.HiLightData.Strength           = 0.0;
    pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.HiLightData.gas_t              = 0.0;
    pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.gas_l0                         = 24;
    pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.gas_l1                         = 10;
    pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.gas_l2                         = 10;
    pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.gas_l3                         = 5;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.LocalWeit       = 1;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.LocalAutoEnable = 1;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.LocalAutoWeit   = 0.5;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.GlobalContrast  = 0.0;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.LoLitContrast   = 0.0;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.MotionData.MotionStr      = 0.0;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.curPixWeit                = 0.376471;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.preFrameWeit              = 0.8;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Range_force_sgm           = 0.0;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Range_sgm_cur             = 0.2;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Range_sgm_pre             = 0.2;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Space_sgm_cur             = 4068;
    pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Space_sgm_pre             = 3068;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Mode                   = COMPRESS_AUTO;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[0]        = 0;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[1]        = 558;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[2]        = 1087;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[3]        = 1588;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[4]        = 2063;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[5]        = 2515;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[6]        = 2944;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[7]        = 3353;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[8]        = 3744;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[9]        = 4473;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[10]       = 5139;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[11]       = 5751;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[12]       = 6316;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[13]       = 6838;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[14]       = 7322;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[15]       = 7772;
    pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[16]       = 8192;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[0]                             = 0;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[1]                             = 2;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[2]                             = 20;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[3]                             = 76;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[4]                             = 193;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[5]                             = 381;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[6]                             = 631;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[7]                             = 772;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[8]                             = 919;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[9]                             = 1066;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[10]                            = 1211;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[11]                            = 1479;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[12]                            = 1700;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[13]                            = 1863;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[14]                            = 1968;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[15]                            = 2024;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[16]                            = 2048;
    pAdrcCtx->drcAttrV12.Info.ValidParams.Edge_Weit                              = 0.02;
    pAdrcCtx->drcAttrV12.Info.ValidParams.OutPutLongFrame                        = false;
    pAdrcCtx->drcAttrV12.Info.ValidParams.IIR_frame                              = 2;

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

void AdrcGetEnvLvV12(AdrcContext_t* pAdrcCtx, AecPreResult_t AecHdrPreResult) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // transfer AeResult data into AhdrHandle
    switch (pAdrcCtx->FrameNumber) {
        case LINEAR_NUM:
            pAdrcCtx->AeResult.Curr.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[0];
            break;
        case HDR_2X_NUM:
            pAdrcCtx->AeResult.Curr.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[1];
            break;
        case HDR_3X_NUM:
            if (CHECK_ISP_HW_V30()) {
                pAdrcCtx->AeResult.Curr.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[1];
            }
            break;
        default:
            LOGE_ATMO("%s:  Wrong frame number in HDR mode!!!\n", __FUNCTION__);
            break;
    }

    // Normalize the current envLv for AEC
    pAdrcCtx->CurrData.EnvLv =
        (pAdrcCtx->AeResult.Curr.GlobalEnvLv - MIN_ENV_LV) / (MAX_ENV_LV - MIN_ENV_LV);
    pAdrcCtx->CurrData.EnvLv = LIMIT_VALUE(pAdrcCtx->CurrData.EnvLv, ENVLVMAX, ENVLVMIN);

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * DrcEnableSetting()
 *
 *****************************************************************************/
bool DrcEnableSetting(AdrcContext_t* pAdrcCtx) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    if (pAdrcCtx->FrameNumber == HDR_2X_NUM || pAdrcCtx->FrameNumber == HDR_3X_NUM)
        pAdrcCtx->CurrData.Enable = true;
    else if (pAdrcCtx->FrameNumber == LINEAR_NUM) {
        if (pAdrcCtx->ablcV32_proc_res.blc_ob_enable)
            pAdrcCtx->CurrData.Enable = true;
        else {
            if (pAdrcCtx->drcAttrV12.opMode == DRC_OPMODE_AUTO) {
                pAdrcCtx->CurrData.Enable = pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.Enable;
            } else if (pAdrcCtx->drcAttrV12.opMode == DRC_OPMODE_MANUAL) {
                pAdrcCtx->CurrData.Enable = pAdrcCtx->drcAttrV12.stManual.Enable;
            } else {
                LOGE_ATMO("%s: Drc api in WRONG MODE!!!, drc by pass!!!\n", __FUNCTION__);
                pAdrcCtx->CurrData.Enable = false;
            }
        }
    }

    return pAdrcCtx->CurrData.Enable;
    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}
/******************************************************************************
 * AdrcDampingV12()
 *****************************************************************************/
void AdrcDampingV12(CurrData_t* pCurrData, AdrcPrevData_t* pPreData, drc_OpMode_t opMode,
                    int FrameCnt) {
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    float Drc_damp = pCurrData->Others.damp;
    bool enDamp;
    bool ifHDRModeChange = pCurrData->frameCnt == pPreData->frameCnt ? false : true;

    if (opMode == DRC_OPMODE_AUTO && FrameCnt != 0 && !ifHDRModeChange) {
        float diff = 0.0;

        diff = ABS(pCurrData->EnvLv - pPreData->EnvLv);
        diff = diff / pPreData->EnvLv;
        if (diff < pCurrData->Others.Tolerance)
            enDamp = false;
        else
            enDamp = true;

        // get finnal cfg data by damp
        if (enDamp) {
            pCurrData->HandleData.Drc_v12.DrcGain =
                Drc_damp * pCurrData->HandleData.Drc_v12.DrcGain +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v12.DrcGain;
            pCurrData->HandleData.Drc_v12.Alpha =
                Drc_damp * pCurrData->HandleData.Drc_v12.Alpha +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v12.Alpha;
            pCurrData->HandleData.Drc_v12.Clip = Drc_damp * pCurrData->HandleData.Drc_v12.Clip +
                                                 (1 - Drc_damp) * pPreData->HandleData.Drc_v12.Clip;
            pCurrData->HandleData.Drc_v12.Strength =
                Drc_damp * pCurrData->HandleData.Drc_v12.Strength +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v12.Strength;
            pCurrData->HandleData.Drc_v12.LocalWeit =
                Drc_damp * pCurrData->HandleData.Drc_v12.LocalWeit +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v12.LocalWeit;
            pCurrData->HandleData.Drc_v12.LocalAutoWeit =
                Drc_damp * pCurrData->HandleData.Drc_v12.LocalAutoWeit +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v12.LocalAutoWeit;
            pCurrData->HandleData.Drc_v12.GlobalContrast =
                Drc_damp * pCurrData->HandleData.Drc_v12.GlobalContrast +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v12.GlobalContrast;
            pCurrData->HandleData.Drc_v12.LoLitContrast =
                Drc_damp * pCurrData->HandleData.Drc_v12.LoLitContrast +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v12.LoLitContrast;
            // drc v12
            pCurrData->HandleData.Drc_v12.gas_t =
                Drc_damp * pCurrData->HandleData.Drc_v12.gas_t +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v12.gas_t;
            pCurrData->HandleData.Drc_v12.MotionStr =
                Drc_damp * pCurrData->HandleData.Drc_v12.MotionStr +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v12.MotionStr;
        }
    }

    LOGD_ATMO("%s: Current damp DrcGain:%f Alpha:%f Clip:%f CompressMode:%d\n", __FUNCTION__,
              pCurrData->HandleData.Drc_v12.DrcGain, pCurrData->HandleData.Drc_v12.Alpha,
              pCurrData->HandleData.Drc_v12.Clip, pCurrData->HandleData.Drc_v12.Mode);
    LOGD_ATMO("%s: Current damp HiLight Strength:%f gas_t:%f\n", __FUNCTION__,
              pCurrData->HandleData.Drc_v12.Strength, pCurrData->HandleData.Drc_v12.gas_t);
    LOGD_ATMO(
        "%s: Current damp LocalWeit:%f LocalAutoEnable:%d LocalAutoWeit:%f GlobalContrast:%f "
        "LoLitContrast:%f MotionStr:%f\n",
        __FUNCTION__, pCurrData->HandleData.Drc_v12.LocalWeit,
        pCurrData->HandleData.Drc_v12.LocalAutoEnable, pCurrData->HandleData.Drc_v12.LocalAutoWeit,
        pCurrData->HandleData.Drc_v12.GlobalContrast, pCurrData->HandleData.Drc_v12.LoLitContrast,
        pCurrData->HandleData.Drc_v12.MotionStr);

    LOG1_ATMO("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * AdrcGetTuningProcResV12()
 *****************************************************************************/
void AdrcGetTuningProcResV12(RkAiqAdrcProcResult_t* pAdrcProcRes, CurrData_t* pCurrData,
                             AblcProc_V32_t* pAblcData, bool LongFrmMode, int FrameNumber,
                             int FrameCnt) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // enable
    if (FrameNumber == HDR_2X_NUM || FrameNumber == HDR_3X_NUM) {
        pAdrcProcRes->bTmoEn      = true;
        pAdrcProcRes->isLinearTmo = false;
    } else if (FrameNumber == LINEAR_NUM) {
        pAdrcProcRes->bTmoEn      = pCurrData->Enable;
        pAdrcProcRes->isLinearTmo = pAdrcProcRes->bTmoEn;
    }

    // drc v12 add
    pAdrcProcRes->DrcProcRes.Drc_v12.gas_t =
        (int)(SHIFT11BIT(pCurrData->HandleData.Drc_v12.gas_t) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.gas_l0 = pCurrData->HandleData.Drc_v12.gas_l0;
    pAdrcProcRes->DrcProcRes.Drc_v12.gas_l1 = pCurrData->HandleData.Drc_v12.gas_l1;
    pAdrcProcRes->DrcProcRes.Drc_v12.gas_l2 = pCurrData->HandleData.Drc_v12.gas_l2;
    pAdrcProcRes->DrcProcRes.Drc_v12.gas_l3 = pCurrData->HandleData.Drc_v12.gas_l3;

    // Long Frame mode
    pAdrcProcRes->LongFrameMode = LongFrmMode;

    // Global tmo
    pAdrcProcRes->isHdrGlobalTmo = pCurrData->HandleData.Drc_v12.LocalWeit == 0 ? true : false;

    // compress mode
    pAdrcProcRes->CompressMode = pCurrData->HandleData.Drc_v12.Mode;

    // DrcProcRes
    pAdrcProcRes->DrcProcRes.Drc_v12.bypass_en   = FUNCTION_DISABLE;
    pAdrcProcRes->DrcProcRes.Drc_v12.offset_pow2 = SW_DRC_OFFSET_POW2_FIX;
    pAdrcProcRes->DrcProcRes.Drc_v12.position =
        (int)(SHIFT8BIT(pCurrData->HandleData.Drc_v12.Clip) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.hpdetail_ratio =
        (int)(SHIFT12BIT(pCurrData->HandleData.Drc_v12.LoLitContrast) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.lpdetail_ratio =
        (int)(SHIFT12BIT(pCurrData->HandleData.Drc_v12.GlobalContrast) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.weicur_pix =
        (int)(SHIFT8BIT(pCurrData->Others.curPixWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.weipre_frame =
        (int)(SHIFT8BIT(pCurrData->Others.preFrameWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.weipre_frame =
        LIMIT_VALUE(pAdrcProcRes->DrcProcRes.Drc_v12.weipre_frame, INT8BITMAX, INTMIN);
    pAdrcProcRes->DrcProcRes.Drc_v12.bilat_wt_off =
        LIMIT_VALUE(pCurrData->HandleData.Drc_v12.MotionStr * INT8BITMAX, INT8BITMAX, INTMIN);
    pAdrcProcRes->DrcProcRes.Drc_v12.force_sgm_inv0 =
        (int)(SHIFT13BIT(pCurrData->Others.Range_force_sgm) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.edge_scl = (int)(SHIFT8BIT(pCurrData->Others.Edge_Weit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.motion_scl     = SW_DRC_MOTION_SCL_FIX;
    pAdrcProcRes->DrcProcRes.Drc_v12.space_sgm_inv1 = (int)(pCurrData->Others.Space_sgm_cur);
    pAdrcProcRes->DrcProcRes.Drc_v12.space_sgm_inv0 = (int)(pCurrData->Others.Space_sgm_pre);
    pAdrcProcRes->DrcProcRes.Drc_v12.range_sgm_inv1 =
        (int)(SHIFT13BIT(pCurrData->Others.Range_sgm_cur) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.range_sgm_inv0 =
        (int)(SHIFT13BIT(pCurrData->Others.Range_sgm_pre) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.weig_maxl =
        (int)(SHIFT4BIT(pCurrData->HandleData.Drc_v12.Strength) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.weig_bilat =
        (int)(SHIFT4BIT(pCurrData->HandleData.Drc_v12.LocalWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.enable_soft_thd =
        pCurrData->HandleData.Drc_v12.LocalAutoEnable;
    pAdrcProcRes->DrcProcRes.Drc_v12.bilat_soft_thd =
        (int)(SHIFT14BIT(pCurrData->HandleData.Drc_v12.LocalAutoWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v12.bilat_soft_thd =
        LIMIT_VALUE(pAdrcProcRes->DrcProcRes.Drc_v12.bilat_soft_thd, INT14BITMAX, INTMIN);
    for (int i = 0; i < ADRC_Y_NUM; ++i) {
        pAdrcProcRes->DrcProcRes.Drc_v12.scale_y[i] = (int)(pCurrData->Others.Scale_y[i]);
        pAdrcProcRes->DrcProcRes.Drc_v12.compres_y[i] =
            pCurrData->HandleData.Drc_v12.Manual_curve[i];
    }

    // get sw_drc_gain_y
    CalibrateDrcGainYV12(&pAdrcProcRes->DrcProcRes, pCurrData->HandleData.Drc_v12.DrcGain,
                         pAblcData->blc_ob_enable, pAblcData->isp_ob_predgain,
                         pCurrData->HandleData.Drc_v12.Alpha);

    float iir_frame = (float)(MIN(FrameCnt + 1, pCurrData->Others.IIR_frame));
    pAdrcProcRes->DrcProcRes.Drc_v12.iir_weight =
        (int)(SHIFT6BIT((iir_frame - 1) / iir_frame) + 0.5);

    // sw_drc_delta_scalein FIX
    pAdrcProcRes->DrcProcRes.Drc_v12.delta_scalein = DELTA_SCALEIN_FIX;

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

void AdrcParams2ApiV12(AdrcContext_t* pAdrcCtx) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // ctrl info
    pAdrcCtx->drcAttrV12.Info.CtrlInfo.ISO   = pAdrcCtx->AeResult.Curr.ISO;
    pAdrcCtx->drcAttrV12.Info.CtrlInfo.EnvLv = pAdrcCtx->CurrData.EnvLv;

    // paras
    if (pAdrcCtx->drcAttrV12.opMode == DRC_OPMODE_MANUAL)
        memcpy(&pAdrcCtx->drcAttrV12.Info.ValidParams, &pAdrcCtx->drcAttrV12.stManual,
               sizeof(mdrcAttr_V12_t));
    else if (pAdrcCtx->drcAttrV12.opMode == DRC_OPMODE_AUTO) {
        pAdrcCtx->drcAttrV12.Info.ValidParams.Enable = pAdrcCtx->CurrData.Enable;
        pAdrcCtx->drcAttrV12.Info.ValidParams.DrcGain.Alpha =
            pAdrcCtx->CurrData.HandleData.Drc_v12.Alpha;
        pAdrcCtx->drcAttrV12.Info.ValidParams.DrcGain.DrcGain =
            pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain;
        pAdrcCtx->drcAttrV12.Info.ValidParams.DrcGain.Clip =
            pAdrcCtx->CurrData.HandleData.Drc_v12.Clip;
        pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.HiLightData.Strength =
            pAdrcCtx->CurrData.HandleData.Drc_v12.Strength;
        pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.HiLightData.gas_t =
            pAdrcCtx->CurrData.HandleData.Drc_v12.gas_t;
        pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.gas_l0 =
            pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l0;
        pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.gas_l1 =
            pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l1;
        pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.gas_l2 =
            pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l2;
        pAdrcCtx->drcAttrV12.Info.ValidParams.HiLight.gas_l3 =
            pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l3;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.LocalWeit =
            pAdrcCtx->CurrData.HandleData.Drc_v12.LocalWeit;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.LocalAutoEnable =
            pAdrcCtx->CurrData.HandleData.Drc_v12.LocalAutoEnable;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.LocalAutoWeit =
            pAdrcCtx->CurrData.HandleData.Drc_v12.LocalAutoWeit;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.GlobalContrast =
            pAdrcCtx->CurrData.HandleData.Drc_v12.GlobalContrast;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.LocalData.LoLitContrast =
            pAdrcCtx->CurrData.HandleData.Drc_v12.LoLitContrast;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.MotionData.MotionStr =
            pAdrcCtx->CurrData.HandleData.Drc_v12.MotionStr;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.curPixWeit =
            pAdrcCtx->CurrData.Others.curPixWeit;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.preFrameWeit =
            pAdrcCtx->CurrData.Others.preFrameWeit;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Range_force_sgm =
            pAdrcCtx->CurrData.Others.Range_force_sgm;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Range_sgm_cur =
            pAdrcCtx->CurrData.Others.Range_sgm_cur;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Range_sgm_pre =
            pAdrcCtx->CurrData.Others.Range_sgm_pre;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Space_sgm_cur =
            pAdrcCtx->CurrData.Others.Space_sgm_cur;
        pAdrcCtx->drcAttrV12.Info.ValidParams.LocalSetting.Space_sgm_pre =
            pAdrcCtx->CurrData.Others.Space_sgm_pre;
        pAdrcCtx->drcAttrV12.Info.ValidParams.Edge_Weit = pAdrcCtx->CurrData.Others.Edge_Weit;
        pAdrcCtx->drcAttrV12.Info.ValidParams.OutPutLongFrame =
            pAdrcCtx->CurrData.Others.OutPutLongFrame;
        pAdrcCtx->drcAttrV12.Info.ValidParams.IIR_frame = pAdrcCtx->CurrData.Others.IIR_frame;
        pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Mode =
            pAdrcCtx->CurrData.HandleData.Drc_v12.Mode;
        for (int i = 0; i < ADRC_Y_NUM; i++) {
            pAdrcCtx->drcAttrV12.Info.ValidParams.CompressSetting.Manual_curve[i] =
                pAdrcCtx->CurrData.HandleData.Drc_v12.Manual_curve[i];
            pAdrcCtx->drcAttrV12.Info.ValidParams.Scale_y[i] = pAdrcCtx->CurrData.Others.Scale_y[i];
        }
    }

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AdrcTuningParaProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
void AdrcTuningParaProcessing(AdrcContext_t* pAdrcCtx) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);
    pAdrcCtx->CurrData.frameCnt = pAdrcCtx->frameCnt;

    // para setting
    if (pAdrcCtx->drcAttrV12.opMode == DRC_OPMODE_AUTO) {
        // get Drc gain
        for (int i = 0; i < pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.EnvLv_len; i++) {
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.EnvLv[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.EnvLv[i],
                            NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.DrcGain[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.DrcGain[i],
                            DRCGAINMAX, DRCGAINMIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.Alpha[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.Alpha[i],
                            NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.Clip[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.Clip[i], CLIPMAX, CLIPMIN);
        }
        pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.DrcGain,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v12.Alpha = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.Alpha,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v12.Clip = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.Clip,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.DrcGain.EnvLv_len);

        // get hi lit
        for (int i = 0; i < pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.EnvLv_len;
             i++) {
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.EnvLv[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.EnvLv[i],
                            NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.Strength[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.Strength[i],
                NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.gas_t[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.gas_t[i],
                            GAS_T_MAX, GAS_T_MIN);
        }
        pAdrcCtx->CurrData.HandleData.Drc_v12.Strength = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.Strength,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_t = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.gas_t,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.HiLightData.EnvLv_len);

        // get local
        for (int i = 0;
             i < pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len; i++) {
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv[i],
                NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalWeit[i] =
                LIMIT_VALUE(
                    pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalWeit[i],
                    NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData
                .GlobalContrast[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.GlobalContrast[i],
                NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData
                .LoLitContrast[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.LoLitContrast[i],
                NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData
                .LocalAutoEnable[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalAutoEnable[i],
                NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData
                .LocalAutoWeit[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalAutoWeit[i],
                NORMALIZE_MAX, NORMALIZE_MIN);
        }
        for (int i = 0;
             i < pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.MotionData.MotionCoef_len;
             i++) {
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.MotionData.MotionCoef[i] =
                LIMIT_VALUE(
                    pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.MotionData.MotionCoef[i],
                    NORMALIZE_MAX, NORMALIZE_MIN);
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.MotionData.MotionStr[i] =
                LIMIT_VALUE(
                    pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.MotionData.MotionStr[i],
                    NORMALIZE_MAX, NORMALIZE_MIN);
        }
        pAdrcCtx->CurrData.HandleData.Drc_v12.LocalWeit = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalWeit,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v12.GlobalContrast = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.GlobalContrast,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v12.LoLitContrast = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.LoLitContrast,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v12.LocalAutoEnable = DrcGetCurrParaV12Int(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalAutoEnable,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v12.LocalAutoWeit = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalAutoWeit,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v12.LocalAutoWeit = DrcGetCurrParaV12(
            pAdrcCtx->CurrData.MotionCoef,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.MotionData.MotionCoef,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.MotionData.MotionStr,
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.MotionData.MotionCoef_len);

        // compress
        pAdrcCtx->CurrData.HandleData.Drc_v12.Mode =
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.CompressSetting.Mode;
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.HandleData.Drc_v12.Manual_curve[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.CompressSetting.Manual_curve[i],
                MANUALCURVEMAX, MANUALCURVEMIN);

        // update others
        pAdrcCtx->CurrData.Others.OutPutLongFrame =
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.OutPutLongFrame;
        pAdrcCtx->CurrData.Others.curPixWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.curPixWeit,
                        NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.preFrameWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.preFrameWeit,
                        NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.Range_force_sgm =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.Range_force_sgm,
                        NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.Range_sgm_cur =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.Range_sgm_cur,
                        NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.Range_sgm_pre =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.Range_sgm_pre,
                        NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.Space_sgm_cur =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.Space_sgm_cur,
                        SPACESGMMAX, SPACESGMMIN);
        pAdrcCtx->CurrData.Others.Space_sgm_pre =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.LocalSetting.Space_sgm_pre,
                        SPACESGMMAX, SPACESGMMIN);
        // scale y
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.Others.Scale_y[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.Scale_y[i], SCALEYMAX, SCALEYMIN);
        pAdrcCtx->CurrData.Others.ByPassThr = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.ByPassThr, NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.Edge_Weit = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.Edge_Weit, NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.IIR_frame = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.IIR_frame, IIRFRAMEMAX, IIRFRAMEMIN);
        pAdrcCtx->CurrData.Others.Tolerance = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.Tolerance, NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.damp = LIMIT_VALUE(pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.damp,
                                                     NORMALIZE_MAX, NORMALIZE_MIN);

        // drc v12 add
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l0 = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.gas_l0, GAS_L_MAX, GAS_L_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l1 = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.gas_l1, GAS_L_MAX, GAS_L_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l2 = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.gas_l2, GAS_L_MAX, GAS_L_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l3 = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.HiLight.gas_l3, GAS_L_MAX, GAS_L_MIN);
    } else if (pAdrcCtx->drcAttrV12.opMode == DRC_OPMODE_MANUAL) {
        // update drc gain
        pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.DrcGain.DrcGain, DRCGAINMAX, DRCGAINMIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.Alpha =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.DrcGain.Alpha, NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.Clip =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.DrcGain.Clip, CLIPMAX, CLIPMIN);

        // update hight light
        pAdrcCtx->CurrData.HandleData.Drc_v12.Strength =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.HiLight.HiLightData.Strength, NORMALIZE_MAX,
                        NORMALIZE_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_t = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stManual.HiLight.HiLightData.gas_t, GAS_T_MAX, GAS_T_MIN);

        // update local
        pAdrcCtx->CurrData.HandleData.Drc_v12.LocalWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.LocalWeit,
                        NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.LocalAutoEnable =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.LocalAutoEnable,
                        ADRCNORMALIZEINTMAX, ADRCNORMALIZEINTMIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.LocalAutoWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.LocalAutoWeit,
                        NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.GlobalContrast =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.GlobalContrast,
                        NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.LoLitContrast =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.LocalSetting.LocalData.LoLitContrast,
                        NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.LoLitContrast =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.LocalSetting.MotionData.MotionStr,
                        NORMALIZE_MAX, NORMALIZE_MIN);

        // compress
        pAdrcCtx->CurrData.HandleData.Drc_v12.Mode =
            pAdrcCtx->drcAttrV12.stManual.CompressSetting.Mode;
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.HandleData.Drc_v12.Manual_curve[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.CompressSetting.Manual_curve[i],
                            MANUALCURVEMAX, MANUALCURVEMIN);

        // others
        pAdrcCtx->CurrData.Others.OutPutLongFrame = pAdrcCtx->drcAttrV12.stManual.OutPutLongFrame;
        pAdrcCtx->CurrData.Others.curPixWeit      = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stManual.LocalSetting.curPixWeit, NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.preFrameWeit = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stManual.LocalSetting.preFrameWeit, NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.Range_force_sgm =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.LocalSetting.Range_force_sgm, NORMALIZE_MAX,
                        NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.Range_sgm_cur = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stManual.LocalSetting.Range_sgm_cur, NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.Range_sgm_pre = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stManual.LocalSetting.Range_sgm_pre, NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.Space_sgm_cur = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stManual.LocalSetting.Space_sgm_cur, SPACESGMMAX, SPACESGMMIN);
        pAdrcCtx->CurrData.Others.Space_sgm_pre = LIMIT_VALUE(
            pAdrcCtx->drcAttrV12.stManual.LocalSetting.Space_sgm_pre, SPACESGMMAX, SPACESGMMIN);
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.Others.Scale_y[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.Scale_y[i], SCALEYMAX, SCALEYMIN);
        pAdrcCtx->CurrData.Others.ByPassThr = NORMALIZE_MIN;
        pAdrcCtx->CurrData.Others.Edge_Weit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.Edge_Weit, NORMALIZE_MAX, NORMALIZE_MIN);
        pAdrcCtx->CurrData.Others.IIR_frame =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.IIR_frame, IIRFRAMEMAX, IIRFRAMEMIN);
        pAdrcCtx->CurrData.Others.Tolerance = NORMALIZE_MIN;
        pAdrcCtx->CurrData.Others.damp      = NORMALIZE_MIN;

        // drc v12 add
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l0 =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.HiLight.gas_l0, GAS_L_MAX, GAS_L_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l1 =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.HiLight.gas_l1, GAS_L_MAX, GAS_L_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l2 =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.HiLight.gas_l2, GAS_L_MAX, GAS_L_MIN);
        pAdrcCtx->CurrData.HandleData.Drc_v12.gas_l3 =
            LIMIT_VALUE(pAdrcCtx->drcAttrV12.stManual.HiLight.gas_l3, GAS_L_MAX, GAS_L_MIN);
    }

    // clip drc gain
    if (pAdrcCtx->FrameNumber == HDR_2X_NUM || pAdrcCtx->FrameNumber == HDR_3X_NUM) {
        if (pAdrcCtx->AeResult.Next.L2S_Ratio * pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain >
            MAX_AE_DRC_GAIN) {
            LOGE_ATMO("%s:  AERatio*DrcGain > 256!!!\n", __FUNCTION__);
            pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain =
                MAX(MAX_AE_DRC_GAIN / pAdrcCtx->AeResult.Next.L2S_Ratio, GAINMIN);
        }
    } else if (pAdrcCtx->FrameNumber == LINEAR_NUM) {
        if (pAdrcCtx->ablcV32_proc_res.isp_ob_predgain *
                pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain >
            MAX_AE_DRC_GAIN) {
            LOGE_ATMO("%s:  predgain*DrcGain > 256!!!\n", __FUNCTION__);
            if (pAdrcCtx->ablcV32_proc_res.isp_ob_predgain > MAX_AE_DRC_GAIN)
                LOGE_ATMO("%s:  predgain > 256!!!\n", __FUNCTION__);
            else
                pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain =
                    MAX(MAX_AE_DRC_GAIN / pAdrcCtx->ablcV32_proc_res.isp_ob_predgain, GAINMIN);
        }
    }

    LOGD_ATMO(
        "%s: Current DrcGain:%f Alpha:%f Clip:%f CompressMode:%d\n", __FUNCTION__,
        pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain, pAdrcCtx->CurrData.HandleData.Drc_v12.Alpha,
        pAdrcCtx->CurrData.HandleData.Drc_v12.Clip, pAdrcCtx->CurrData.HandleData.Drc_v12.Mode);
    LOGD_ATMO("%s: Current HiLight Strength:%f gas_t:%f\n", __FUNCTION__,
              pAdrcCtx->CurrData.HandleData.Drc_v12.Strength,
              pAdrcCtx->CurrData.HandleData.Drc_v12.gas_t);
    LOGD_ATMO(
        "%s: Current LocalWeit:%f LocalAutoEnable:%d LocalAutoWeit:%f GlobalContrast:%f "
        "LoLitContrast:%f MotionStr:%f\n",
        __FUNCTION__, pAdrcCtx->CurrData.HandleData.Drc_v12.LocalWeit,
        pAdrcCtx->CurrData.HandleData.Drc_v12.LocalAutoEnable,
        pAdrcCtx->CurrData.HandleData.Drc_v12.LocalAutoWeit,
        pAdrcCtx->CurrData.HandleData.Drc_v12.GlobalContrast,
        pAdrcCtx->CurrData.HandleData.Drc_v12.LoLitContrast,
        pAdrcCtx->CurrData.HandleData.Drc_v12.MotionStr);

    // damp
    AdrcDampingV12(&pAdrcCtx->CurrData, &pAdrcCtx->PrevData, pAdrcCtx->drcAttrV12.opMode,
                   pAdrcCtx->frameCnt);

    // get io data
    AdrcGetTuningProcResV12(&pAdrcCtx->AdrcProcRes, &pAdrcCtx->CurrData,
                            &pAdrcCtx->ablcV32_proc_res, pAdrcCtx->AeResult.LongFrmMode,
                            pAdrcCtx->FrameNumber, pAdrcCtx->frameCnt);

    // store curr data 2 api
    AdrcParams2ApiV12(pAdrcCtx);

    // store current handle data to pre data for next loop
    pAdrcCtx->PrevData.EnvLv      = pAdrcCtx->CurrData.EnvLv;
    pAdrcCtx->PrevData.ISO        = pAdrcCtx->CurrData.ISO;
    pAdrcCtx->PrevData.MotionCoef = pAdrcCtx->CurrData.MotionCoef;
    if (0 != memcmp(&pAdrcCtx->PrevData.HandleData, &pAdrcCtx->CurrData.HandleData,
                    sizeof(DrcHandleData_t)))
        memcpy(&pAdrcCtx->PrevData.HandleData, &pAdrcCtx->CurrData.HandleData,
               sizeof(DrcHandleData_t));

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AdrcExpoParaProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
void AdrcExpoParaProcessing(AdrcContext_t* pAdrcCtx) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // get sw_drc_compres_scl
    float adrc_gain = 1.0;
    if (pAdrcCtx->ablcV32_proc_res.blc_ob_enable)
        adrc_gain = pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain *
                    pAdrcCtx->ablcV32_proc_res.isp_ob_predgain;
    else
        adrc_gain = pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain;
    float log_ratio2     = log(pAdrcCtx->AeResult.Next.L2S_Ratio * adrc_gain) / log(2.0f) + 12;
    float offsetbits_int = (float)(pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.offset_pow2);
    float offsetbits     = offsetbits_int * pow(2, MFHDR_LOG_Q_BITS);
    float hdrbits        = log_ratio2 * pow(2, MFHDR_LOG_Q_BITS);
    float hdrvalidbits   = hdrbits - offsetbits;
    float compres_scl    = (12 * pow(2, MFHDR_LOG_Q_BITS * 2)) / hdrvalidbits;
    pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_scl = (int)(compres_scl);

    // get sw_drc_min_ogain
    if (pAdrcCtx->CurrData.Others.OutPutLongFrame)
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.min_ogain = 1 << 15;
    else {
        float sw_drc_min_ogain = 1 / (pAdrcCtx->AeResult.Next.L2S_Ratio * adrc_gain);
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.min_ogain =
            (int)(sw_drc_min_ogain * pow(2, 15) + 0.5);
    }

    // get sw_drc_compres_y
    float curveparam, curveparam2, curveparam3, tmp;
    if (pAdrcCtx->AdrcProcRes.CompressMode == COMPRESS_AUTO) {
        float luma2[17] = {0,     1024,  2048,  3072,  4096,  5120,  6144,  7168, 8192,
                           10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576};
        float curveTable[17];
        float dstbits   = ISP_RAW_BIT * pow(2, MFHDR_LOG_Q_BITS);
        float validbits = dstbits - offsetbits;
        for (int i = 0; i < ISP21_DRC_Y_NUM; ++i) {
            curveparam    = (float)(validbits - 0) / (hdrvalidbits - validbits + pow(2, -6));
            curveparam2   = validbits * (1 + curveparam);
            curveparam3   = hdrvalidbits * curveparam;
            tmp           = luma2[i] * hdrvalidbits / 24576;
            curveTable[i] = (tmp * curveparam2 / (tmp + curveparam3));
            pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[i] = (int)(curveTable[i]);
        }
    }

    LOGV_ATMO("%s: nextRatioLS:%f sw_drc_position:%d sw_drc_compres_scl:%d sw_drc_offset_pow2:%d\n",
              __FUNCTION__, pAdrcCtx->AeResult.Next.L2S_Ratio,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.position,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_scl,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.offset_pow2);
    LOGV_ATMO("%s: blc_ob_enable:%d OB_predgain:%f DrcGain:%f TotalDgain:%f\n", __FUNCTION__,
              pAdrcCtx->ablcV32_proc_res.blc_ob_enable, pAdrcCtx->ablcV32_proc_res.isp_ob_predgain,
              pAdrcCtx->CurrData.HandleData.Drc_v12.DrcGain, adrc_gain);
    LOGV_ATMO("%s: sw_drc_lpdetail_ratio:%d sw_drc_hpdetail_ratio:%d sw_drc_delta_scalein:%d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.lpdetail_ratio,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.hpdetail_ratio,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.delta_scalein);
    LOGV_ATMO("%s: sw_drc_bilat_wt_off:%d sw_drc_weipre_frame:%d sw_drc_weicur_pix:%d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.bilat_wt_off,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.weipre_frame,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.weicur_pix);
    LOGV_ATMO("%s: sw_drc_edge_scl:%d sw_drc_motion_scl:%d sw_drc_force_sgm_inv0:%d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.edge_scl,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.motion_scl,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.force_sgm_inv0);
    LOGV_ATMO("%s: sw_drc_space_sgm_inv0:%d sw_drc_space_sgm_inv1:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.space_sgm_inv0,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.space_sgm_inv1);
    LOGV_ATMO("%s: sw_drc_range_sgm_inv0:%d sw_drc_range_sgm_inv1:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.range_sgm_inv0,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.range_sgm_inv1);
    LOGV_ATMO(
        "%s: sw_drc_weig_bilat:%d sw_drc_weig_maxl:%d sw_drc_bilat_soft_thd:%d "
        "sw_drc_enable_soft_thd:%d\n",
        __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.weig_bilat,
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.weig_maxl,
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.bilat_soft_thd,
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.enable_soft_thd);
    LOGV_ATMO("%s: sw_drc_min_ogain:%d sw_drc_iir_weight:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.min_ogain,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.iir_weight);
    LOGV_ATMO("%s: sw_drc_gain_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[0],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[1],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[2],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[3],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[4],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[5],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[6],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[7],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[8],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[9],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[10],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[11],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[12],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[13],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[14],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[15],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.gain_y[16]);
    LOGV_ATMO("%s: sw_drc_scale_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[0],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[1],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[2],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[3],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[4],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[5],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[6],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[7],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[8],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[9],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[10],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[11],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[12],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[13],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[14],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[15],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.scale_y[16]);
    LOGV_ATMO(
        "%s: CompressMode:%d sw_drc_compres_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
        "%d\n",
        __FUNCTION__, pAdrcCtx->AdrcProcRes.CompressMode,
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[0],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[1],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[2],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[3],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[4],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[5],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[6],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[7],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[8],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[9],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[10],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[11],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[12],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[13],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[14],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[15],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v12.compres_y[16]);

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AdrcByPassProcessing()
 *get handle para by config and current variate
 *****************************************************************************/
bool AdrcByPassProcessing(AdrcContext_t* pAdrcCtx, AecPreResult_t AecHdrPreResult) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    bool bypass = false;
    float diff  = 0.0;

    float ByPassThr = pAdrcCtx->drcAttrV12.stAuto.DrcTuningPara.ByPassThr;

    if (pAdrcCtx->frameCnt <= 2)  // start frame
        bypass = false;
    else if (pAdrcCtx->drcAttrV12.opMode == DRC_OPMODE_MANUAL)  // api
        bypass = false;
    else if (pAdrcCtx->drcAttrV12.opMode != pAdrcCtx->PrevData.ApiMode)  // api change
        bypass = false;
    else {  // EnvLv change
        // get current EnvLv from AecPreRes
        AdrcGetEnvLvV12(pAdrcCtx, AecHdrPreResult);

        // motion coef
        pAdrcCtx->CurrData.MotionCoef = MOVE_COEF_DEFAULT;

        // transfer ae data to CurrHandle
        pAdrcCtx->CurrData.EnvLv =
            LIMIT_VALUE(pAdrcCtx->CurrData.EnvLv, NORMALIZE_MAX, NORMALIZE_MIN);

        pAdrcCtx->CurrData.ISO = pAdrcCtx->AeResult.Next.ISO;
        pAdrcCtx->CurrData.ISO = LIMIT_VALUE(pAdrcCtx->CurrData.ISO, ISOMAX, ISOMIN);

        // use Envlv for now
        diff = pAdrcCtx->PrevData.EnvLv - pAdrcCtx->CurrData.EnvLv;
        if (pAdrcCtx->PrevData.EnvLv == 0.0) {
            diff = pAdrcCtx->CurrData.EnvLv;
            if (diff == 0.0)
                bypass = true;
            else
                bypass = false;
        } else {
            diff /= pAdrcCtx->PrevData.EnvLv;
            if (diff >= ByPassThr || diff <= (0 - ByPassThr))
                bypass = false;
            else
                bypass = true;
        }
    }

    LOGD_ATMO(
        "%s: FrameID:%d HDRFrameNum:%d LongFrmMode:%d DRCApiMode:%d EnvLv:%f ISO:%f bypass:%d\n",
        __FUNCTION__, pAdrcCtx->frameCnt, pAdrcCtx->FrameNumber, pAdrcCtx->AeResult.LongFrmMode,
        pAdrcCtx->drcAttrV12.opMode, pAdrcCtx->CurrData.EnvLv, pAdrcCtx->CurrData.ISO, bypass);

    LOG1_ATMO("%s: CtrlEnvLv:%f PrevEnvLv:%f diff:%f ByPassThr:%f opMode:%d bypass:%d!\n",
              __FUNCTION__, pAdrcCtx->CurrData.EnvLv, pAdrcCtx->PrevData.EnvLv, diff, ByPassThr,
              pAdrcCtx->drcAttrV12.opMode, bypass);

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
    return bypass;
}

/******************************************************************************
 * AdrcInit()
 *****************************************************************************/
XCamReturn AdrcInit(AdrcContext_t** ppAdrcCtx, CamCalibDbV2Context_t* pCalibDb) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    AdrcContext_t* pAdrcCtx;
    pAdrcCtx = (AdrcContext_t*)malloc(sizeof(AdrcContext_t));
    if (pAdrcCtx == NULL) {
        LOGE_ATMO("%s(%d): invalid inputparams\n", __FUNCTION__, __LINE__);
        return XCAM_RETURN_ERROR_MEM;
    }

    memset(pAdrcCtx, 0x00, sizeof(AdrcContext_t));
    *ppAdrcCtx      = pAdrcCtx;
    pAdrcCtx->state = ADRC_STATE_INITIALIZED;

    CalibDbV2_drc_V12_t* calibv2_adrc_calib =
        (CalibDbV2_drc_V12_t*)(CALIBDBV2_GET_MODULE_PTR(pCalibDb, adrc_calib));

    pAdrcCtx->drcAttrV12.opMode = DRC_OPMODE_AUTO;
    SetDefaultValueV12(pAdrcCtx);  // set default para
    memcpy(&pAdrcCtx->CalibDBV12, calibv2_adrc_calib, sizeof(CalibDbV2_drc_V12_t));  // load iq
                                                                                     // paras
    memcpy(&pAdrcCtx->drcAttrV12.stAuto, calibv2_adrc_calib,
           sizeof(CalibDbV2_drc_V12_t));  // set stAuto

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);

    return (XCAM_RETURN_NO_ERROR);
}
/******************************************************************************
 * AhdrRelease()
 *****************************************************************************/
XCamReturn AdrcRelease(AdrcContext_t* pAdrcCtx) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);
    XCamReturn result = XCAM_RETURN_NO_ERROR;

    // initial checks
    if (NULL == pAdrcCtx) {
        return (XCAM_RETURN_ERROR_PARAM);
    }

    result = AdrcStop(pAdrcCtx);
    if (result != XCAM_RETURN_NO_ERROR) {
        LOGE_ATMO("%s: AHDRStop() failed!\n", __FUNCTION__);
        return (result);
    }

    // check state
    if ((ADRC_STATE_RUNNING == pAdrcCtx->state) || (ADRC_STATE_LOCKED == pAdrcCtx->state)) {
        return (XCAM_RETURN_ERROR_MEM);
    }

    free(pAdrcCtx);
    pAdrcCtx = NULL;

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);

    return (XCAM_RETURN_NO_ERROR);
}
