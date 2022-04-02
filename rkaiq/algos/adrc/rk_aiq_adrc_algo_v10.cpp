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
 * @file rk_aiq_adrc_algo_v10.cpp
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
 * DrcGetCurrPara()
 *****************************************************************************/
float DrcGetCurrPara(float inPara, float* inMatrixX, float* inMatrixY, int Max_Knots) {
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
 * DrcGetCurrPara()
 *****************************************************************************/
int DrcGetCurrParaInt(float inPara, float* inMatrixX, int* inMatrixY, int Max_Knots) {
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
 * CalibrateDrcGainY()
 *****************************************************************************/
void CalibrateDrcGainY(DrcProcRes_t* para, float DraGain, float alpha) {
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);

    float tmp      = 0;
    float luma[17] = {0,    256,  512,  768,  1024, 1280, 1536, 1792, 2048,
                      2304, 2560, 2816, 3072, 3328, 3584, 3840, 4096};
    float gainTable[17];

    for (int i = 0; i < 17; ++i) {
        tmp                            = luma[i];
        tmp                            = 1 - alpha * pow((1 - tmp / 4096), 2);
        gainTable[i]                   = 1024 * pow(DraGain, tmp);
        para->Drc_v10.sw_drc_gain_y[i] = (int)(gainTable[i]);
    }

    LOG1_ATMO("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * SetDefaultValueV10()
 *set default Config data
 *****************************************************************************/
void SetDefaultValueV10(AdrcContext_t* pAdrcCtx) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAdrcCtx != NULL);

    // config default PrevData data
    pAdrcCtx->PrevData.frameCnt                          = 0;
    pAdrcCtx->PrevData.EnvLv                             = 0;
    pAdrcCtx->PrevData.ApiMode                           = DRC_OPMODE_AUTO;
    pAdrcCtx->PrevData.HandleData.Drc_v10.DrcGain        = 4.0;
    pAdrcCtx->PrevData.HandleData.Drc_v10.Alpha          = 0.2;
    pAdrcCtx->PrevData.HandleData.Drc_v10.Clip           = 16.0;
    pAdrcCtx->PrevData.HandleData.Drc_v10.Strength       = 0.01;
    pAdrcCtx->PrevData.HandleData.Drc_v10.LocalWeit      = 1.00;
    pAdrcCtx->PrevData.HandleData.Drc_v10.GlobalContrast = 0;
    pAdrcCtx->PrevData.HandleData.Drc_v10.LoLitContrast  = 0;

    // set default value for api
    pAdrcCtx->drcAttrV10.stManual.Enable                                      = true;
    pAdrcCtx->drcAttrV10.stManual.DrcGain.Alpha                               = 0.1;
    pAdrcCtx->drcAttrV10.stManual.DrcGain.DrcGain                             = 1;
    pAdrcCtx->drcAttrV10.stManual.DrcGain.Clip                                = 1;
    pAdrcCtx->drcAttrV10.stManual.HiLight.Strength                            = 0.0;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.LocalTMOData.LocalWeit      = 1;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.LocalTMOData.GlobalContrast = 0.0;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.LocalTMOData.LoLitContrast  = 0.0;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.curPixWeit                  = 0.376471;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.preFrameWeit                = 0.8;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Range_force_sgm             = 0.0;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Range_sgm_cur               = 0.2;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Range_sgm_pre               = 0.2;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Space_sgm_cur               = 4068;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Space_sgm_pre               = 3068;
    pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Space_sgm_pre               = 3068;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Mode                        = COMPRESS_AUTO;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[0]             = 0;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[1]             = 558;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[2]             = 1087;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[3]             = 1588;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[4]             = 2063;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[5]             = 2515;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[6]             = 2944;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[7]             = 3353;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[8]             = 3744;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[9]             = 4473;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[10]            = 5139;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[11]            = 5751;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[12]            = 6316;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[13]            = 6838;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[14]            = 7322;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[15]            = 7772;
    pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[16]            = 8192;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[0]                                  = 0;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[1]                                  = 2;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[2]                                  = 20;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[3]                                  = 76;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[4]                                  = 193;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[5]                                  = 381;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[6]                                  = 631;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[7]                                  = 772;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[8]                                  = 919;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[9]                                  = 1066;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[10]                                 = 1211;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[11]                                 = 1479;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[12]                                 = 1700;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[13]                                 = 1863;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[14]                                 = 1968;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[15]                                 = 2024;
    pAdrcCtx->drcAttrV10.stManual.Scale_y[16]                                 = 2048;
    pAdrcCtx->drcAttrV10.stManual.Edge_Weit                                   = 0.02;
    pAdrcCtx->drcAttrV10.stManual.OutPutLongFrame                             = false;
    pAdrcCtx->drcAttrV10.stManual.IIR_frame                                   = 2;

    pAdrcCtx->drcAttrV10.Info.ValidParams.Enable                                      = true;
    pAdrcCtx->drcAttrV10.Info.ValidParams.DrcGain.Alpha                               = 0.1;
    pAdrcCtx->drcAttrV10.Info.ValidParams.DrcGain.DrcGain                             = 1;
    pAdrcCtx->drcAttrV10.Info.ValidParams.DrcGain.Clip                                = 1;
    pAdrcCtx->drcAttrV10.Info.ValidParams.HiLight.Strength                            = 0.0;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.LocalTMOData.LocalWeit      = 1;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.LocalTMOData.GlobalContrast = 0.0;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.LocalTMOData.LoLitContrast  = 0.0;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.curPixWeit                  = 0.376471;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.preFrameWeit                = 0.8;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Range_force_sgm             = 0.0;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Range_sgm_cur               = 0.2;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Range_sgm_pre               = 0.2;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Space_sgm_cur               = 4068;
    pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Space_sgm_pre               = 3068;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Mode             = COMPRESS_AUTO;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[0]  = 0;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[1]  = 558;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[2]  = 1087;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[3]  = 1588;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[4]  = 2063;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[5]  = 2515;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[6]  = 2944;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[7]  = 3353;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[8]  = 3744;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[9]  = 4473;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[10] = 5139;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[11] = 5751;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[12] = 6316;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[13] = 6838;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[14] = 7322;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[15] = 7772;
    pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[16] = 8192;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[0]                       = 0;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[1]                       = 2;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[2]                       = 20;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[3]                       = 76;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[4]                       = 193;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[5]                       = 381;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[6]                       = 631;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[7]                       = 772;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[8]                       = 919;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[9]                       = 1066;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[10]                      = 1211;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[11]                      = 1479;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[12]                      = 1700;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[13]                      = 1863;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[14]                      = 1968;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[15]                      = 2024;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[16]                      = 2048;
    pAdrcCtx->drcAttrV10.Info.ValidParams.Edge_Weit                        = 0.02;
    pAdrcCtx->drcAttrV10.Info.ValidParams.OutPutLongFrame                  = false;
    pAdrcCtx->drcAttrV10.Info.ValidParams.IIR_frame                        = 2;

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

void AdrcGetEnvLvV10(AdrcContext_t* pAdrcCtx, AecPreResult_t AecHdrPreResult) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // transfer AeResult data into AhdrHandle
    switch (pAdrcCtx->FrameNumber) {
        case LINEAR_NUM:
            pAdrcCtx->AeResult.Curr.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[0];
            break;
        case HDR_2X_NUM:
            pAdrcCtx->AeResult.Curr.GlobalEnvLv = AecHdrPreResult.GlobalEnvLv[1];
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

    if (pAdrcCtx->FrameNumber == HDR_2X_NUM)
        pAdrcCtx->CurrData.Enable = true;
    else if (pAdrcCtx->FrameNumber == LINEAR_NUM) {
        if (pAdrcCtx->drcAttrV10.opMode == DRC_OPMODE_AUTO)
            pAdrcCtx->CurrData.Enable = pAdrcCtx->CalibDBV10.DrcTuningPara.Enable;
        else if (pAdrcCtx->drcAttrV10.opMode == DRC_OPMODE_MANUAL)
            pAdrcCtx->CurrData.Enable = pAdrcCtx->drcAttrV10.stManual.Enable;
        else {
            LOGE_ATMO("%s: Drc api in WRONG MODE!!!, drc by pass!!!\n", __FUNCTION__);
            pAdrcCtx->CurrData.Enable = false;
        }
    }

    return pAdrcCtx->CurrData.Enable;
    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

/******************************************************************************
 * AdrcDampingV10()
 *****************************************************************************/
void AdrcDampingV10(CurrData_t* pCurrData, AdrcPrevData_t* pPreData, drc_OpMode_t opMode,
                    int FrameCnt) {
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);
    float Drc_damp = pCurrData->Others.damp;
    bool enDamp;
    bool ifHDRModeChange = pCurrData->frameCnt == pPreData->frameCnt ? false : true;

    if (opMode != DRC_OPMODE_MANUAL && FrameCnt != 0 && !ifHDRModeChange) {
        float diff = 0.0;

        diff = ABS(pCurrData->EnvLv - pPreData->EnvLv);
        diff = diff / pPreData->EnvLv;
        if (diff < pCurrData->Others.Tolerance)
            enDamp = false;
        else
            enDamp = true;

        // get finnal cfg data by damp
        if (enDamp) {
            pCurrData->HandleData.Drc_v10.DrcGain =
                Drc_damp * pCurrData->HandleData.Drc_v10.DrcGain +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v10.DrcGain;
            pCurrData->HandleData.Drc_v10.Alpha =
                Drc_damp * pCurrData->HandleData.Drc_v10.Alpha +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v10.Alpha;
            pCurrData->HandleData.Drc_v10.Clip = Drc_damp * pCurrData->HandleData.Drc_v10.Clip +
                                                 (1 - Drc_damp) * pPreData->HandleData.Drc_v10.Clip;
            pCurrData->HandleData.Drc_v10.Strength =
                Drc_damp * pCurrData->HandleData.Drc_v10.Strength +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v10.Strength;
            pCurrData->HandleData.Drc_v10.LocalWeit =
                Drc_damp * pCurrData->HandleData.Drc_v10.LocalWeit +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v10.LocalWeit;
            pCurrData->HandleData.Drc_v10.GlobalContrast =
                Drc_damp * pCurrData->HandleData.Drc_v10.GlobalContrast +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v10.GlobalContrast;
            pCurrData->HandleData.Drc_v10.LoLitContrast =
                Drc_damp * pCurrData->HandleData.Drc_v10.LoLitContrast +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v10.LoLitContrast;
        }
    }

    LOGD_ATMO(
        "%s:%d: Current damp DrcGain:%f Alpha:%f Clip:%f Strength:%f LocalWeit:%f "
        "GlobalContrast:%f LoLitContrast:%f CompressMode:%d\n",
        __FUNCTION__, __LINE__, pCurrData->HandleData.Drc_v10.DrcGain,
        pCurrData->HandleData.Drc_v10.Alpha, pCurrData->HandleData.Drc_v10.Clip,
        pCurrData->HandleData.Drc_v10.Strength, pCurrData->HandleData.Drc_v10.LocalWeit,
        pCurrData->HandleData.Drc_v10.GlobalContrast, pCurrData->HandleData.Drc_v10.LoLitContrast,
        pCurrData->HandleData.Drc_v10.Mode);

    LOG1_ATMO("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * AdrcGetTuningProcResV10()
 *****************************************************************************/
void AdrcGetTuningProcResV10(RkAiqAdrcProcResult_t* pAdrcProcRes, CurrData_t* pCurrData,
                             bool LongFrmMode, int FrameNumber, int FrameCnt) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // enable
    if (FrameNumber == HDR_2X_NUM || FrameNumber == HDR_3X_NUM) {
        pAdrcProcRes->bTmoEn      = true;
        pAdrcProcRes->isLinearTmo = false;
    } else if (FrameNumber == LINEAR_NUM) {
        pAdrcProcRes->bTmoEn      = pCurrData->Enable;
        pAdrcProcRes->isLinearTmo = pAdrcProcRes->bTmoEn;
    }

    // Long Frame mode
    pAdrcProcRes->LongFrameMode = LongFrmMode;

    // Global tmo
    pAdrcProcRes->isHdrGlobalTmo = pCurrData->HandleData.Drc_v10.LocalWeit == 0 ? true : false;

    // compress mode
    pAdrcProcRes->CompressMode = pCurrData->HandleData.Drc_v10.Mode;

    // DrcProcRes
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_offset_pow2 = SW_DRC_OFFSET_POW2_FIX;
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_position =
        (int)(SHIFT8BIT(pCurrData->HandleData.Drc_v10.Clip) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_hpdetail_ratio =
        (int)(SHIFT12BIT(pCurrData->HandleData.Drc_v10.LoLitContrast) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_lpdetail_ratio =
        (int)(SHIFT12BIT(pCurrData->HandleData.Drc_v10.GlobalContrast) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_weicur_pix =
        (int)(SHIFT8BIT(pCurrData->Others.curPixWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_weipre_frame =
        (int)(SHIFT8BIT(pCurrData->Others.preFrameWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_weipre_frame =
        LIMIT_VALUE(pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_weipre_frame, 255, 0);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_force_sgm_inv0 =
        (int)(SHIFT13BIT(pCurrData->Others.Range_force_sgm) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_edge_scl =
        (int)(SHIFT8BIT(pCurrData->Others.Edge_Weit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_motion_scl     = SW_DRC_MOTION_SCL_FIX;
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_space_sgm_inv1 = (int)(pCurrData->Others.Space_sgm_cur);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_space_sgm_inv0 = (int)(pCurrData->Others.Space_sgm_pre);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_range_sgm_inv1 =
        (int)(SHIFT13BIT(pCurrData->Others.Range_sgm_cur) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_range_sgm_inv0 =
        (int)(SHIFT13BIT(pCurrData->Others.Range_sgm_pre) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_weig_maxl =
        (int)(SHIFT4BIT(pCurrData->HandleData.Drc_v10.Strength) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_adrc_gain = pCurrData->HandleData.Drc_v10.DrcGain;
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_weig_bilat =
        (int)(SHIFT4BIT(pCurrData->HandleData.Drc_v10.LocalWeit) + 0.5);
    for (int i = 0; i < ADRC_Y_NUM; ++i) {
        pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_scale_y[i] = (int)(pCurrData->Others.Scale_y[i]);
        pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_compres_y[i] =
            pCurrData->HandleData.Drc_v10.Manual_curve[i];
    }

    // get sw_drc_gain_y
    CalibrateDrcGainY(&pAdrcProcRes->DrcProcRes, pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_adrc_gain,
                      pCurrData->HandleData.Drc_v10.Alpha);

    float iir_frame = (float)(MIN(FrameCnt + 1, pCurrData->Others.IIR_frame));
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_iir_weight =
        (int)(SHIFT6BIT((iir_frame - 1) / iir_frame) + 0.5);

    // sw_drc_delta_scalein FIX
    pAdrcProcRes->DrcProcRes.Drc_v10.sw_drc_delta_scalein = DELTA_SCALEIN_FIX;

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

void AdrcParams2ApiV10(AdrcContext_t* pAdrcCtx) {
    LOG1_ATMO("%s:enter!\n", __FUNCTION__);

    // ctrl info
    pAdrcCtx->drcAttrV10.Info.CtrlInfo.ISO   = pAdrcCtx->AeResult.Curr.ISO;
    pAdrcCtx->drcAttrV10.Info.CtrlInfo.EnvLv = pAdrcCtx->CurrData.EnvLv;

    // paras
    if (pAdrcCtx->drcAttrV10.opMode == DRC_OPMODE_MANUAL)
        memcpy(&pAdrcCtx->drcAttrV10.Info.ValidParams, &pAdrcCtx->drcAttrV10.stManual,
               sizeof(mdrcAttr_V10_t));
    else if (pAdrcCtx->drcAttrV10.opMode == DRC_OPMODE_AUTO) {
        pAdrcCtx->drcAttrV10.Info.ValidParams.Enable = pAdrcCtx->CurrData.Enable;
        pAdrcCtx->drcAttrV10.Info.ValidParams.DrcGain.Alpha =
            pAdrcCtx->CurrData.HandleData.Drc_v10.Alpha;
        pAdrcCtx->drcAttrV10.Info.ValidParams.DrcGain.DrcGain =
            pAdrcCtx->CurrData.HandleData.Drc_v10.DrcGain;
        pAdrcCtx->drcAttrV10.Info.ValidParams.DrcGain.Clip =
            pAdrcCtx->CurrData.HandleData.Drc_v10.Clip;
        pAdrcCtx->drcAttrV10.Info.ValidParams.HiLight.Strength =
            pAdrcCtx->CurrData.HandleData.Drc_v10.Strength;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.LocalTMOData.LocalWeit =
            pAdrcCtx->CurrData.HandleData.Drc_v10.LocalWeit;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.LocalTMOData.GlobalContrast =
            pAdrcCtx->CurrData.HandleData.Drc_v10.GlobalContrast;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.LocalTMOData.LoLitContrast =
            pAdrcCtx->CurrData.HandleData.Drc_v10.LoLitContrast;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.curPixWeit =
            pAdrcCtx->CurrData.Others.curPixWeit;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.preFrameWeit =
            pAdrcCtx->CurrData.Others.preFrameWeit;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Range_force_sgm =
            pAdrcCtx->CurrData.Others.Range_force_sgm;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Range_sgm_cur =
            pAdrcCtx->CurrData.Others.Range_sgm_cur;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Range_sgm_pre =
            pAdrcCtx->CurrData.Others.Range_sgm_pre;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Space_sgm_cur =
            pAdrcCtx->CurrData.Others.Space_sgm_cur;
        pAdrcCtx->drcAttrV10.Info.ValidParams.LocalTMOSetting.Space_sgm_pre =
            pAdrcCtx->CurrData.Others.Space_sgm_pre;
        pAdrcCtx->drcAttrV10.Info.ValidParams.Edge_Weit = pAdrcCtx->CurrData.Others.Edge_Weit;
        pAdrcCtx->drcAttrV10.Info.ValidParams.OutPutLongFrame =
            pAdrcCtx->CurrData.Others.OutPutLongFrame;
        pAdrcCtx->drcAttrV10.Info.ValidParams.IIR_frame = pAdrcCtx->CurrData.Others.IIR_frame;
        pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Mode =
            pAdrcCtx->CurrData.HandleData.Drc_v10.Mode;
        for (int i = 0; i < ADRC_Y_NUM; i++) {
            pAdrcCtx->drcAttrV10.Info.ValidParams.CompressSetting.Manual_curve[i] =
                pAdrcCtx->CurrData.HandleData.Drc_v10.Manual_curve[i];
            pAdrcCtx->drcAttrV10.Info.ValidParams.Scale_y[i] = pAdrcCtx->CurrData.Others.Scale_y[i];
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
    if (pAdrcCtx->drcAttrV10.opMode == DRC_OPMODE_AUTO) {
        // store enable
        pAdrcCtx->CurrData.Enable = pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.Enable;

        // get Drc gain
        pAdrcCtx->CurrData.HandleData.Drc_v10.DrcGain = DrcGetCurrPara(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.DrcGain.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.DrcGain.DrcGain, ADRC_ENVLV_STEP_MAX);
        pAdrcCtx->CurrData.HandleData.Drc_v10.Alpha = DrcGetCurrPara(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.DrcGain.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.DrcGain.Alpha, ADRC_ENVLV_STEP_MAX);
        pAdrcCtx->CurrData.HandleData.Drc_v10.Clip = DrcGetCurrPara(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.DrcGain.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.DrcGain.Clip, ADRC_ENVLV_STEP_MAX);

        // get hi lit
        pAdrcCtx->CurrData.HandleData.Drc_v10.Strength = DrcGetCurrPara(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.HiLight.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.HiLight.Strength, ADRC_ENVLV_STEP_MAX);

        // get local
        pAdrcCtx->CurrData.HandleData.Drc_v10.LocalWeit = DrcGetCurrPara(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.LocalTMOData.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.LocalTMOData.LocalWeit,
            ADRC_ENVLV_STEP_MAX);
        pAdrcCtx->CurrData.HandleData.Drc_v10.GlobalContrast = DrcGetCurrPara(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.LocalTMOData.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.LocalTMOData.GlobalContrast,
            ADRC_ENVLV_STEP_MAX);
        pAdrcCtx->CurrData.HandleData.Drc_v10.LoLitContrast = DrcGetCurrPara(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.LocalTMOData.EnvLv,
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.LocalTMOData.LoLitContrast,
            ADRC_ENVLV_STEP_MAX);

        // compress
        pAdrcCtx->CurrData.HandleData.Drc_v10.Mode =
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.CompressSetting.Mode;
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.HandleData.Drc_v10.Manual_curve[i] =
                pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.CompressSetting.Manual_curve[i];

        // others
        pAdrcCtx->CurrData.Others.OutPutLongFrame =
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.OutPutLongFrame;
        pAdrcCtx->CurrData.Others.curPixWeit =
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.curPixWeit;
        pAdrcCtx->CurrData.Others.preFrameWeit =
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.preFrameWeit;
        pAdrcCtx->CurrData.Others.Range_force_sgm =
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.Range_force_sgm;
        pAdrcCtx->CurrData.Others.Range_sgm_cur =
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.Range_sgm_cur;
        pAdrcCtx->CurrData.Others.Range_sgm_pre =
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.Range_sgm_pre;
        pAdrcCtx->CurrData.Others.Space_sgm_cur =
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.Space_sgm_cur;
        pAdrcCtx->CurrData.Others.Space_sgm_pre =
            pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.LocalTMOSetting.Space_sgm_pre;
        pAdrcCtx->CurrData.Others.ByPassThr = pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.ByPassThr;
        pAdrcCtx->CurrData.Others.Edge_Weit = pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.Edge_Weit;
        pAdrcCtx->CurrData.Others.Tolerance = pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.Tolerance;
        pAdrcCtx->CurrData.Others.IIR_frame = pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.IIR_frame;
        pAdrcCtx->CurrData.Others.damp      = pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.damp;
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.Others.Scale_y[i] =
                pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.Scale_y[i];
    } else if (pAdrcCtx->drcAttrV10.opMode == DRC_OPMODE_MANUAL) {
        // store enable
        pAdrcCtx->CurrData.Enable = pAdrcCtx->drcAttrV10.stManual.Enable;

        // get Drc gain
        pAdrcCtx->CurrData.HandleData.Drc_v10.DrcGain =
            pAdrcCtx->drcAttrV10.stManual.DrcGain.DrcGain;
        pAdrcCtx->CurrData.HandleData.Drc_v10.Alpha = pAdrcCtx->drcAttrV10.stManual.DrcGain.Alpha;
        pAdrcCtx->CurrData.HandleData.Drc_v10.Clip  = pAdrcCtx->drcAttrV10.stManual.DrcGain.Clip;

        // get hi lit
        pAdrcCtx->CurrData.HandleData.Drc_v10.Strength =
            pAdrcCtx->drcAttrV10.stManual.HiLight.Strength;

        // get local
        pAdrcCtx->CurrData.HandleData.Drc_v10.LocalWeit =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.LocalTMOData.LocalWeit;
        pAdrcCtx->CurrData.HandleData.Drc_v10.GlobalContrast =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.LocalTMOData.GlobalContrast;
        pAdrcCtx->CurrData.HandleData.Drc_v10.LoLitContrast =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.LocalTMOData.LoLitContrast;

        // compress
        pAdrcCtx->CurrData.HandleData.Drc_v10.Mode =
            pAdrcCtx->drcAttrV10.stManual.CompressSetting.Mode;
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.HandleData.Drc_v10.Manual_curve[i] =
                pAdrcCtx->drcAttrV10.stManual.CompressSetting.Manual_curve[i];

        // others
        pAdrcCtx->CurrData.Others.OutPutLongFrame = pAdrcCtx->drcAttrV10.stManual.OutPutLongFrame;
        pAdrcCtx->CurrData.Others.curPixWeit =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.curPixWeit;
        pAdrcCtx->CurrData.Others.preFrameWeit =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.preFrameWeit;
        pAdrcCtx->CurrData.Others.Range_force_sgm =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Range_force_sgm;
        pAdrcCtx->CurrData.Others.Range_sgm_cur =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Range_sgm_cur;
        pAdrcCtx->CurrData.Others.Range_sgm_pre =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Range_sgm_pre;
        pAdrcCtx->CurrData.Others.Space_sgm_cur =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Space_sgm_cur;
        pAdrcCtx->CurrData.Others.Space_sgm_pre =
            pAdrcCtx->drcAttrV10.stManual.LocalTMOSetting.Space_sgm_pre;
        pAdrcCtx->CurrData.Others.ByPassThr = 0;
        pAdrcCtx->CurrData.Others.Edge_Weit = pAdrcCtx->drcAttrV10.stManual.Edge_Weit;
        pAdrcCtx->CurrData.Others.Tolerance = 0;
        pAdrcCtx->CurrData.Others.IIR_frame = pAdrcCtx->drcAttrV10.stManual.IIR_frame;
        pAdrcCtx->CurrData.Others.damp      = 1;
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.Others.Scale_y[i] = pAdrcCtx->drcAttrV10.stManual.Scale_y[i];
    }

    // clip drc gain
    if (pAdrcCtx->AeResult.Next.L2S_Ratio * pAdrcCtx->CurrData.HandleData.Drc_v10.DrcGain >
        MAX_AE_DRC_GAIN) {
        LOGE_ATMO("%s:  AERatio*DrcGain > 256!!!\n", __FUNCTION__);
        pAdrcCtx->CurrData.HandleData.Drc_v10.DrcGain =
            MAX(MAX_AE_DRC_GAIN / pAdrcCtx->AeResult.Next.L2S_Ratio, GAINMIN);
    }

    LOGD_ATMO(
        "%s:Current Enable:%d DrcGain:%f Alpha:%f Clip:%f Strength:%f LocalWeit:%f "
        "GlobalContrast:%f LoLitContrast:%f CompressMode:%d\n",
        __FUNCTION__, pAdrcCtx->CurrData.Enable, pAdrcCtx->CurrData.HandleData.Drc_v10.DrcGain,
        pAdrcCtx->CurrData.HandleData.Drc_v10.Alpha, pAdrcCtx->CurrData.HandleData.Drc_v10.Clip,
        pAdrcCtx->CurrData.HandleData.Drc_v10.Strength,
        pAdrcCtx->CurrData.HandleData.Drc_v10.LocalWeit,
        pAdrcCtx->CurrData.HandleData.Drc_v10.GlobalContrast,
        pAdrcCtx->CurrData.HandleData.Drc_v10.LoLitContrast,
        pAdrcCtx->CurrData.HandleData.Drc_v10.Mode);

    // damp
    AdrcDampingV10(&pAdrcCtx->CurrData, &pAdrcCtx->PrevData, pAdrcCtx->drcAttrV10.opMode,
                   pAdrcCtx->frameCnt);

    // get tuning proc res
    AdrcGetTuningProcResV10(&pAdrcCtx->AdrcProcRes, &pAdrcCtx->CurrData,
                            pAdrcCtx->AeResult.LongFrmMode, pAdrcCtx->FrameNumber,
                            pAdrcCtx->frameCnt);

    // store curr data 2 api
    AdrcParams2ApiV10(pAdrcCtx);

    // store current handle data to pre data for next loop
    pAdrcCtx->PrevData.EnvLv = pAdrcCtx->CurrData.EnvLv;
    pAdrcCtx->PrevData.ISO   = pAdrcCtx->CurrData.ISO;
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
    float adrc_gain      = pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_adrc_gain;
    float log_ratio2     = log(pAdrcCtx->AeResult.Next.L2S_Ratio * adrc_gain) / log(2.0f) + 12;
    float offsetbits_int = (float)(pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_offset_pow2);
    float offsetbits     = offsetbits_int * pow(2, MFHDR_LOG_Q_BITS);
    float hdrbits        = log_ratio2 * pow(2, MFHDR_LOG_Q_BITS);
    float hdrvalidbits   = hdrbits - offsetbits;
    float compres_scl    = (12 * pow(2, MFHDR_LOG_Q_BITS * 2)) / hdrvalidbits;
    pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_scl = (int)(compres_scl);

    // get sw_drc_min_ogain
    if (pAdrcCtx->CurrData.Others.OutPutLongFrame)
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_min_ogain = 1 << 15;
    else {
        float sw_drc_min_ogain = 1 / (pAdrcCtx->AeResult.Next.L2S_Ratio * adrc_gain);
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_min_ogain =
            (int)(sw_drc_min_ogain * pow(2, 15) + 0.5);
    }

    // get sw_drc_compres_y
    if (pAdrcCtx->AdrcProcRes.CompressMode == COMPRESS_AUTO) {
        float curveparam, curveparam2, curveparam3, tmp;
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
            pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[i] = (int)(curveTable[i]);
        }
    }

    LOGV_ATMO("%s: nextRatioLS:%f sw_drc_position:%d sw_drc_compres_scl:%d sw_drc_offset_pow2:%d\n",
              __FUNCTION__, pAdrcCtx->AeResult.Next.L2S_Ratio,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_position,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_scl,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_offset_pow2);
    LOGV_ATMO("%s: sw_drc_lpdetail_ratio:%d sw_drc_hpdetail_ratio:%d sw_drc_delta_scalein:%d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_lpdetail_ratio,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_hpdetail_ratio,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_delta_scalein);
    LOGV_ATMO("%s: sw_drc_weipre_frame:%d sw_drc_weicur_pix:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_weipre_frame,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_weicur_pix);
    LOGV_ATMO("%s: sw_drc_edge_scl:%d sw_drc_motion_scl:%d sw_drc_force_sgm_inv0:%d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_edge_scl,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_motion_scl,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_force_sgm_inv0);
    LOGV_ATMO("%s: sw_drc_space_sgm_inv0:%d sw_drc_space_sgm_inv1:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_space_sgm_inv0,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_space_sgm_inv1);
    LOGV_ATMO("%s: sw_drc_range_sgm_inv0:%d sw_drc_range_sgm_inv1:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_range_sgm_inv0,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_range_sgm_inv1);
    LOGV_ATMO("%s: sw_drc_weig_bilat:%d sw_drc_weig_maxl:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_weig_bilat,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_weig_maxl);
    LOGV_ATMO("%s: sw_drc_min_ogain:%d sw_drc_iir_weight:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_min_ogain,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_iir_weight);
    LOGV_ATMO("%s: sw_drc_gain_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[0],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[1],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[2],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[3],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[4],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[5],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[6],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[7],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[8],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[9],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[10],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[11],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[12],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[13],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[14],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[15],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_gain_y[16]);
    LOGV_ATMO("%s: sw_drc_scale_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[0],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[1],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[2],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[3],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[4],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[5],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[6],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[7],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[8],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[9],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[10],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[11],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[12],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[13],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[14],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[15],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_scale_y[16]);
    LOGV_ATMO(
        "%s: CompressMode:%d sw_drc_compres_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
        "%d\n",
        __FUNCTION__, pAdrcCtx->AdrcProcRes.CompressMode,
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[0],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[1],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[2],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[3],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[4],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[5],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[6],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[7],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[8],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[9],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[10],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[11],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[12],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[13],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[14],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[15],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v10.sw_drc_compres_y[16]);

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

    float ByPassThr = 0.0f;
    ByPassThr       = pAdrcCtx->drcAttrV10.stAuto.DrcTuningPara.ByPassThr;

    if (pAdrcCtx->frameCnt <= 2)  // start frame
        bypass = false;
    else if (pAdrcCtx->drcAttrV10.opMode == DRC_OPMODE_MANUAL)  // api
        bypass = false;
    else if (pAdrcCtx->drcAttrV10.opMode != pAdrcCtx->PrevData.ApiMode)  // api change
        bypass = false;
    else {  // EnvLv change
        // get current EnvLv from AecPreRes
        AdrcGetEnvLvV10(pAdrcCtx, AecHdrPreResult);

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

    LOGD_ATMO("%s: FrameID:%d HDRFrameNum:%d LongFrmMode:%d DRCApiMode:%d EnvLv:%f bypass:%d\n",
              __FUNCTION__, pAdrcCtx->frameCnt, pAdrcCtx->FrameNumber,
              pAdrcCtx->AeResult.LongFrmMode, pAdrcCtx->drcAttrV10.opMode, pAdrcCtx->CurrData.EnvLv,
              bypass);

    LOG1_ATMO("%s: CtrlEnvLv:%f PrevEnvLv:%f diff:%f ByPassThr:%f opMode:%d bypass:%d!\n",
              __FUNCTION__, pAdrcCtx->CurrData.EnvLv, pAdrcCtx->PrevData.EnvLv, diff, ByPassThr,
              pAdrcCtx->drcAttrV10.opMode, bypass);

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

    CalibDbV2_drc_V10_t* calibv2_adrc_calib =
        (CalibDbV2_drc_V10_t*)(CALIBDBV2_GET_MODULE_PTR(pCalibDb, adrc_calib));

    pAdrcCtx->drcAttrV10.opMode = DRC_OPMODE_AUTO;
    SetDefaultValueV10(pAdrcCtx);  // set default para
    memcpy(&pAdrcCtx->CalibDBV10, calibv2_adrc_calib, sizeof(CalibDbV2_drc_V10_t));  // load iq
                                                                                     // paras
    memcpy(&pAdrcCtx->drcAttrV10.stAuto, calibv2_adrc_calib,
           sizeof(CalibDbV2_drc_V10_t));  // load iq paras

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
