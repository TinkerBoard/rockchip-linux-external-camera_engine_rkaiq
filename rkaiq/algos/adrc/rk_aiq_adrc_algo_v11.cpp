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
 * @file rk_aiq_adrc_algo_v11.cpp
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
 * DrcGetCurrParaV11()
 *****************************************************************************/
float DrcGetCurrParaV11(float inPara, float* inMatrixX, float* inMatrixY, int Max_Knots) {
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
 * DrcGetCurrParaV11()
 *****************************************************************************/
int DrcGetCurrParaV11Int(float inPara, float* inMatrixX, int* inMatrixY, int Max_Knots) {
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
 * CalibrateDrcGainYV11()
 *****************************************************************************/
void CalibrateDrcGainYV11(DrcProcRes_t* para, float DraGain, float alpha) {
    LOG1_ATMO("%s:Enter!\n", __FUNCTION__);

    float tmp      = 0;
    float luma[17] = {0,    256,  512,  768,  1024, 1280, 1536, 1792, 2048,
                      2304, 2560, 2816, 3072, 3328, 3584, 3840, 4096};
    float gainTable[17];

    for (int i = 0; i < 17; ++i) {
        tmp                     = luma[i];
        tmp                     = 1 - alpha * pow((1 - tmp / 4096), 2);
        gainTable[i]            = 1024 * pow(DraGain, tmp);
        para->Drc_v11.gain_y[i] = (int)(gainTable[i]);
    }

    LOG1_ATMO("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * ConfigV11()
 *set default Config data
 *****************************************************************************/
void ConfigV11(AdrcContext_t* pAdrcCtx) {
    LOGI_ATMO("%s:enter!\n", __FUNCTION__);

    // initial checks
    DCT_ASSERT(pAdrcCtx != NULL);

    // config default PrevData data
    pAdrcCtx->PrevData.frameCnt                           = 0;
    pAdrcCtx->PrevData.EnvLv                              = 0;
    pAdrcCtx->PrevData.MotionCoef                         = 0;
    pAdrcCtx->PrevData.ApiMode                            = DRC_OPMODE_AUTO;
    pAdrcCtx->PrevData.HandleData.Drc_v11.DrcGain         = 4.0;
    pAdrcCtx->PrevData.HandleData.Drc_v11.Alpha           = 0.2;
    pAdrcCtx->PrevData.HandleData.Drc_v11.Clip            = 16.0;
    pAdrcCtx->PrevData.HandleData.Drc_v11.Strength        = 0.01;
    pAdrcCtx->PrevData.HandleData.Drc_v11.LocalWeit       = 1.00;
    pAdrcCtx->PrevData.HandleData.Drc_v11.LocalAutoEnable = 1;
    pAdrcCtx->PrevData.HandleData.Drc_v11.LocalAutoWeit   = 0.037477;
    pAdrcCtx->PrevData.HandleData.Drc_v11.GlobalContrast  = 0;
    pAdrcCtx->PrevData.HandleData.Drc_v11.LoLitContrast   = 0;

    // set default value for api
    pAdrcCtx->drcAttrV11.stManual.Enable                                 = true;
    pAdrcCtx->drcAttrV11.stManual.DrcGain.Alpha                          = 0.1;
    pAdrcCtx->drcAttrV11.stManual.DrcGain.DrcGain                        = 1;
    pAdrcCtx->drcAttrV11.stManual.DrcGain.Clip                           = 1;
    pAdrcCtx->drcAttrV11.stManual.HiLight.Strength                       = 0.0;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.LocalWeit       = 1;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.LocalAutoEnable = 1;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.LocalAutoWeit   = 0.5;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.GlobalContrast  = 0.0;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.LoLitContrast   = 0.0;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.curPixWeit                = 0.376471;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.preFrameWeit              = 0.8;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.Range_force_sgm           = 0.0;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.Range_sgm_cur             = 0.2;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.Range_sgm_pre             = 0.2;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.Space_sgm_cur             = 4068;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.Space_sgm_pre             = 3068;
    pAdrcCtx->drcAttrV11.stManual.LocalSetting.Space_sgm_pre             = 3068;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Mode                   = COMPRESS_AUTO;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[0]        = 0;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[1]        = 558;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[2]        = 1087;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[3]        = 1588;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[4]        = 2063;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[5]        = 2515;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[6]        = 2944;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[7]        = 3353;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[8]        = 3744;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[9]        = 4473;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[10]       = 5139;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[11]       = 5751;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[12]       = 6316;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[13]       = 6838;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[14]       = 7322;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[15]       = 7772;
    pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[16]       = 8192;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[0]                             = 0;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[1]                             = 2;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[2]                             = 20;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[3]                             = 76;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[4]                             = 193;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[5]                             = 381;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[6]                             = 631;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[7]                             = 772;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[8]                             = 919;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[9]                             = 1066;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[10]                            = 1211;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[11]                            = 1479;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[12]                            = 1700;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[13]                            = 1863;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[14]                            = 1968;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[15]                            = 2024;
    pAdrcCtx->drcAttrV11.stManual.Scale_y[16]                            = 2048;
    pAdrcCtx->drcAttrV11.stManual.Edge_Weit                              = 0.02;
    pAdrcCtx->drcAttrV11.stManual.OutPutLongFrame                        = false;
    pAdrcCtx->drcAttrV11.stManual.IIR_frame                              = 2;

    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}

void AdrcGetEnvLvV11(AdrcContext_t* pAdrcCtx, AecPreResult_t AecHdrPreResult) {
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

    if (pAdrcCtx->FrameNumber == HDR_2X_NUM || pAdrcCtx->FrameNumber == HDR_3X_NUM)
        pAdrcCtx->CurrData.Enable = true;
    else if (pAdrcCtx->FrameNumber == LINEAR_NUM) {
        if (pAdrcCtx->drcAttrV11.opMode == DRC_OPMODE_AUTO)
            pAdrcCtx->CurrData.Enable = pAdrcCtx->CalibDBV11.DrcTuningPara.Enable;
        else if (pAdrcCtx->drcAttrV11.opMode == DRC_OPMODE_MANU)
            pAdrcCtx->CurrData.Enable = pAdrcCtx->drcAttrV11.stManual.Enable;
        else {
            LOGE_ATMO("%s: Drc api in WRONG MODE!!!, drc by pass!!!\n", __FUNCTION__);
            pAdrcCtx->CurrData.Enable = false;
        }
    }

    return pAdrcCtx->CurrData.Enable;
    LOG1_ATMO("%s:exit!\n", __FUNCTION__);
}
/******************************************************************************
 * AdrcDampingV11()
 *****************************************************************************/
void AdrcDampingV11(CurrData_t* pCurrData, AdrcPrevData_t* pPreData, drc_OpMode_t opMode,
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
            pCurrData->HandleData.Drc_v11.DrcGain =
                Drc_damp * pCurrData->HandleData.Drc_v11.DrcGain +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v11.DrcGain;
            pCurrData->HandleData.Drc_v11.Alpha =
                Drc_damp * pCurrData->HandleData.Drc_v11.Alpha +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v11.Alpha;
            pCurrData->HandleData.Drc_v11.Clip = Drc_damp * pCurrData->HandleData.Drc_v11.Clip +
                                                 (1 - Drc_damp) * pPreData->HandleData.Drc_v11.Clip;
            pCurrData->HandleData.Drc_v11.Strength =
                Drc_damp * pCurrData->HandleData.Drc_v11.Strength +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v11.Strength;
            pCurrData->HandleData.Drc_v11.LocalWeit =
                Drc_damp * pCurrData->HandleData.Drc_v11.LocalWeit +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v11.LocalWeit;
            pCurrData->HandleData.Drc_v11.LocalAutoWeit =
                Drc_damp * pCurrData->HandleData.Drc_v11.LocalAutoWeit +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v11.LocalAutoWeit;
            pCurrData->HandleData.Drc_v11.GlobalContrast =
                Drc_damp * pCurrData->HandleData.Drc_v11.GlobalContrast +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v11.GlobalContrast;
            pCurrData->HandleData.Drc_v11.LoLitContrast =
                Drc_damp * pCurrData->HandleData.Drc_v11.LoLitContrast +
                (1 - Drc_damp) * pPreData->HandleData.Drc_v11.LoLitContrast;
        }
    }

    LOGD_ATMO("%s: Current damp DrcGain:%f Alpha:%f Clip:%f Strength:%f CompressMode:%d\n",
              __FUNCTION__, pCurrData->HandleData.Drc_v11.DrcGain,
              pCurrData->HandleData.Drc_v11.Alpha, pCurrData->HandleData.Drc_v11.Clip,
              pCurrData->HandleData.Drc_v11.Strength, pCurrData->HandleData.Drc_v11.Mode);
    LOGD_ATMO(
        "%s: Current damp LocalWeit:%f LocalAutoEnable:%d LocalAutoWeit:%f GlobalContrast:%f "
        "LoLitContrast:%f\n",
        __FUNCTION__, pCurrData->HandleData.Drc_v11.LocalWeit,
        pCurrData->HandleData.Drc_v11.LocalAutoEnable, pCurrData->HandleData.Drc_v11.LocalAutoWeit,
        pCurrData->HandleData.Drc_v11.GlobalContrast, pCurrData->HandleData.Drc_v11.LoLitContrast);

    LOG1_ATMO("%s:Eixt!\n", __FUNCTION__);
}

/******************************************************************************
 * AdrcGetTuningProcResV11()
 *****************************************************************************/
void AdrcGetTuningProcResV11(RkAiqAdrcProcResult_t* pAdrcProcRes, CurrData_t* pCurrData,
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
    pAdrcProcRes->isHdrGlobalTmo = pCurrData->HandleData.Drc_v11.LocalWeit == 0 ? true : false;

    // compress mode
    pAdrcProcRes->CompressMode = pCurrData->HandleData.Drc_v11.Mode;

    // DrcProcRes
    pAdrcProcRes->DrcProcRes.Drc_v11.bypass_en   = FUNCTION_DISABLE;
    pAdrcProcRes->DrcProcRes.Drc_v11.offset_pow2 = SW_DRC_OFFSET_POW2_FIX;
    pAdrcProcRes->DrcProcRes.Drc_v11.position =
        (int)(SHIFT8BIT(pCurrData->HandleData.Drc_v11.Clip) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.hpdetail_ratio =
        (int)(SHIFT12BIT(pCurrData->HandleData.Drc_v11.LoLitContrast) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.lpdetail_ratio =
        (int)(SHIFT12BIT(pCurrData->HandleData.Drc_v11.GlobalContrast) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.weicur_pix =
        (int)(SHIFT8BIT(pCurrData->Others.curPixWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.weipre_frame =
        (int)(SHIFT8BIT(pCurrData->Others.preFrameWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.weipre_frame =
        LIMIT_VALUE(pAdrcProcRes->DrcProcRes.Drc_v11.weipre_frame, INT8BITMAX, 0);
    pAdrcProcRes->DrcProcRes.Drc_v11.bilat_wt_off =
        SW_DRC_BILAT_WT_OFF_FIX;  // LIMIT_VALUE(pCurrData->HandleData.Drc_v11.MotionStr *
                                  // INT8BITMAX, INT8BITMAX, 0);
    pAdrcProcRes->DrcProcRes.Drc_v11.force_sgm_inv0 =
        (int)(SHIFT13BIT(pCurrData->Others.Range_force_sgm) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.edge_scl = (int)(SHIFT8BIT(pCurrData->Others.Edge_Weit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.motion_scl     = SW_DRC_MOTION_SCL_FIX;
    pAdrcProcRes->DrcProcRes.Drc_v11.space_sgm_inv1 = (int)(pCurrData->Others.Space_sgm_cur);
    pAdrcProcRes->DrcProcRes.Drc_v11.space_sgm_inv0 = (int)(pCurrData->Others.Space_sgm_pre);
    pAdrcProcRes->DrcProcRes.Drc_v11.range_sgm_inv1 =
        (int)(SHIFT13BIT(pCurrData->Others.Range_sgm_cur) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.range_sgm_inv0 =
        (int)(SHIFT13BIT(pCurrData->Others.Range_sgm_pre) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.weig_maxl =
        (int)(SHIFT4BIT(pCurrData->HandleData.Drc_v11.Strength) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.adrc_gain = pCurrData->HandleData.Drc_v11.DrcGain;
    pAdrcProcRes->DrcProcRes.Drc_v11.weig_bilat =
        (int)(SHIFT4BIT(pCurrData->HandleData.Drc_v11.LocalWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.enable_soft_thd =
        pCurrData->HandleData.Drc_v11.LocalAutoEnable;
    pAdrcProcRes->DrcProcRes.Drc_v11.bilat_soft_thd =
        (int)(SHIFT14BIT(pCurrData->HandleData.Drc_v11.LocalAutoWeit) + 0.5);
    pAdrcProcRes->DrcProcRes.Drc_v11.bilat_soft_thd =
        LIMIT_VALUE(pAdrcProcRes->DrcProcRes.Drc_v11.bilat_soft_thd, INT14BITMAX, 0);
    for (int i = 0; i < ADRC_Y_NUM; ++i) {
        pAdrcProcRes->DrcProcRes.Drc_v11.scale_y[i] = (int)(pCurrData->Others.Scale_y[i]);
        pAdrcProcRes->DrcProcRes.Drc_v11.compres_y[i] =
            pCurrData->HandleData.Drc_v11.Manual_curve[i];
    }

    // get sw_drc_gain_y
    CalibrateDrcGainYV11(&pAdrcProcRes->DrcProcRes, pAdrcProcRes->DrcProcRes.Drc_v11.adrc_gain,
                         pCurrData->HandleData.Drc_v11.Alpha);

    pAdrcProcRes->DrcProcRes.Drc_v11.wr_cycle = FUNCTION_DISABLE;
    float iir_frame = (float)(MIN(FrameCnt + 1, pCurrData->Others.IIR_frame));
    pAdrcProcRes->DrcProcRes.Drc_v11.iir_weight =
        (int)(SHIFT6BIT((iir_frame - 1) / iir_frame) + 0.5);

    // sw_drc_delta_scalein FIX
    pAdrcProcRes->DrcProcRes.Drc_v11.delta_scalein = DELTA_SCALEIN_FIX;

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
    if (pAdrcCtx->drcAttrV11.opMode == DRC_OPMODE_AUTO) {
        // store enable
        pAdrcCtx->CurrData.Enable = pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.Enable;

        // get Drc gain
        for (int i = 0; i < pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.EnvLv_len; i++) {
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.EnvLv[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.EnvLv[i],
                            ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.DrcGain[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.DrcGain[i],
                            DRCGAINMAX, DRCGAINMIN);
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.Alpha[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.Alpha[i],
                            ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.Clip[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.Clip[i], CLIPMAX, CLIPMIN);
        }
        pAdrcCtx->CurrData.HandleData.Drc_v11.DrcGain = DrcGetCurrParaV11(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.DrcGain,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v11.Alpha = DrcGetCurrParaV11(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.Alpha,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v11.Clip = DrcGetCurrParaV11(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.Clip,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.DrcGain.EnvLv_len);

        // get hi lit
        for (int i = 0; i < pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.HiLight.EnvLv_len; i++) {
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.HiLight.EnvLv[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.HiLight.EnvLv[i],
                            ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.HiLight.Strength[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.HiLight.Strength[i],
                            ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        }
        pAdrcCtx->CurrData.HandleData.Drc_v11.Strength = DrcGetCurrParaV11(
            pAdrcCtx->CurrData.EnvLv, pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.HiLight.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.HiLight.Strength,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.HiLight.EnvLv_len);

        // get local
        for (int i = 0;
             i < pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len; i++) {
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv[i],
                ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalWeit[i] =
                LIMIT_VALUE(
                    pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalWeit[i],
                    ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData
                .GlobalContrast[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.GlobalContrast[i],
                ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData
                .LoLitContrast[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.LoLitContrast[i],
                ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData
                .LocalAutoEnable[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalAutoEnable[i],
                ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData
                .LocalAutoWeit[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalAutoWeit[i],
                ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        }
        pAdrcCtx->CurrData.HandleData.Drc_v11.LocalWeit = DrcGetCurrParaV11(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalWeit,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v11.GlobalContrast = DrcGetCurrParaV11(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.GlobalContrast,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v11.LoLitContrast = DrcGetCurrParaV11(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.LoLitContrast,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v11.LocalAutoEnable = DrcGetCurrParaV11Int(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalAutoEnable,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);
        pAdrcCtx->CurrData.HandleData.Drc_v11.LocalAutoWeit = DrcGetCurrParaV11(
            pAdrcCtx->CurrData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.LocalAutoWeit,
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.LocalData.EnvLv_len);

        // compress
        pAdrcCtx->CurrData.HandleData.Drc_v11.Mode =
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.CompressSetting.Mode;
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.HandleData.Drc_v11.Manual_curve[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.CompressSetting.Manual_curve[i],
                MANUALCURVEMAX, MANUALCURVEMIN);

        // update others
        pAdrcCtx->CurrData.Others.OutPutLongFrame =
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.OutPutLongFrame;
        pAdrcCtx->CurrData.Others.curPixWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.curPixWeit,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.preFrameWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.preFrameWeit,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.Range_force_sgm =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.Range_force_sgm,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.Range_sgm_cur =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.Range_sgm_cur,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.Range_sgm_pre =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.Range_sgm_pre,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.Space_sgm_cur =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.Space_sgm_cur,
                        SPACESGMMAX, SPACESGMMIN);
        pAdrcCtx->CurrData.Others.Space_sgm_pre =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.LocalSetting.Space_sgm_pre,
                        SPACESGMMAX, SPACESGMMIN);
        // scale y
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.Others.Scale_y[i] = LIMIT_VALUE(
                pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.Scale_y[i], SCALEYMAX, SCALEYMIN);
        pAdrcCtx->CurrData.Others.ByPassThr =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.ByPassThr, ADRCNORMALIZEMAX,
                        ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.Edge_Weit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.Edge_Weit, ADRCNORMALIZEMAX,
                        ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.IIR_frame = LIMIT_VALUE(
            pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.IIR_frame, IIRFRAMEMAX, IIRFRAMEMIN);
        pAdrcCtx->CurrData.Others.Tolerance =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.Tolerance, ADRCNORMALIZEMAX,
                        ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.damp = LIMIT_VALUE(pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.damp,
                                                     ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
    } else if (pAdrcCtx->drcAttrV11.opMode == DRC_OPMODE_MANU) {
        // update drc gain
        pAdrcCtx->CurrData.HandleData.Drc_v11.DrcGain =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.DrcGain.DrcGain, DRCGAINMAX, DRCGAINMIN);
        pAdrcCtx->CurrData.HandleData.Drc_v11.Alpha = LIMIT_VALUE(
            pAdrcCtx->drcAttrV11.stManual.DrcGain.Alpha, ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.HandleData.Drc_v11.Clip =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.DrcGain.Clip, CLIPMAX, CLIPMIN);

        // update hight light
        pAdrcCtx->CurrData.HandleData.Drc_v11.Strength = LIMIT_VALUE(
            pAdrcCtx->drcAttrV11.stManual.HiLight.Strength, ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);

        // update local
        pAdrcCtx->CurrData.HandleData.Drc_v11.LocalWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.LocalWeit,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.HandleData.Drc_v11.LocalAutoEnable =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.LocalAutoEnable,
                        ADRCNORMALIZEINTMAX, ADRCNORMALIZEINTMIN);
        pAdrcCtx->CurrData.HandleData.Drc_v11.LocalAutoWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.LocalAutoWeit,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.HandleData.Drc_v11.GlobalContrast =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.GlobalContrast,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.HandleData.Drc_v11.LoLitContrast =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.LocalData.LoLitContrast,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);

        // compress
        pAdrcCtx->CurrData.HandleData.Drc_v11.Mode =
            pAdrcCtx->drcAttrV11.stManual.CompressSetting.Mode;
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.HandleData.Drc_v11.Manual_curve[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.CompressSetting.Manual_curve[i],
                            MANUALCURVEMAX, MANUALCURVEMIN);

        // others
        pAdrcCtx->CurrData.Others.OutPutLongFrame = pAdrcCtx->drcAttrV11.stManual.OutPutLongFrame;
        pAdrcCtx->CurrData.Others.curPixWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.curPixWeit, ADRCNORMALIZEMAX,
                        ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.preFrameWeit =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.preFrameWeit, ADRCNORMALIZEMAX,
                        ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.Range_force_sgm =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.Range_force_sgm,
                        ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.Range_sgm_cur =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.Range_sgm_cur, ADRCNORMALIZEMAX,
                        ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.Range_sgm_pre =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.LocalSetting.Range_sgm_pre, ADRCNORMALIZEMAX,
                        ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.Space_sgm_cur = LIMIT_VALUE(
            pAdrcCtx->drcAttrV11.stManual.LocalSetting.Space_sgm_cur, SPACESGMMAX, SPACESGMMIN);
        pAdrcCtx->CurrData.Others.Space_sgm_pre = LIMIT_VALUE(
            pAdrcCtx->drcAttrV11.stManual.LocalSetting.Space_sgm_pre, SPACESGMMAX, SPACESGMMIN);
        for (int i = 0; i < ADRC_Y_NUM; i++)
            pAdrcCtx->CurrData.Others.Scale_y[i] =
                LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.Scale_y[i], SCALEYMAX, SCALEYMIN);
        pAdrcCtx->CurrData.Others.ByPassThr = ADRCNORMALIZEMIN;
        pAdrcCtx->CurrData.Others.Edge_Weit = LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.Edge_Weit,
                                                          ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);
        pAdrcCtx->CurrData.Others.IIR_frame =
            LIMIT_VALUE(pAdrcCtx->drcAttrV11.stManual.IIR_frame, IIRFRAMEMAX, IIRFRAMEMIN);
        pAdrcCtx->CurrData.Others.Tolerance = ADRCNORMALIZEMIN;
        pAdrcCtx->CurrData.Others.damp      = ADRCNORMALIZEMIN;
    }

    // clip drc gain
    if (pAdrcCtx->AeResult.Next.L2S_Ratio * pAdrcCtx->CurrData.HandleData.Drc_v11.DrcGain >
        MAX_AE_DRC_GAIN) {
        LOGE_ATMO("%s:  AERatio*DrcGain > 256!!!\n", __FUNCTION__);
        pAdrcCtx->CurrData.HandleData.Drc_v11.DrcGain =
            MAX(MAX_AE_DRC_GAIN / pAdrcCtx->AeResult.Next.L2S_Ratio, GAINMIN);
    }

    LOGD_ATMO(
        "%s: Current Enable:%d DrcGain:%f Alpha:%f Clip:%f Strength:%f CompressMode:%d\n",
        __FUNCTION__, pAdrcCtx->CurrData.Enable, pAdrcCtx->CurrData.HandleData.Drc_v11.DrcGain,
        pAdrcCtx->CurrData.HandleData.Drc_v11.Alpha, pAdrcCtx->CurrData.HandleData.Drc_v11.Clip,
        pAdrcCtx->CurrData.HandleData.Drc_v11.Strength, pAdrcCtx->CurrData.HandleData.Drc_v11.Mode);
    LOGD_ATMO(
        "%s: Current LocalWeit:%f LocalAutoEnable:%d LocalAutoWeit:%f GlobalContrast:%f "
        "LoLitContrast:%f\n",
        __FUNCTION__, pAdrcCtx->CurrData.HandleData.Drc_v11.LocalWeit,
        pAdrcCtx->CurrData.HandleData.Drc_v11.LocalAutoEnable,
        pAdrcCtx->CurrData.HandleData.Drc_v11.LocalAutoWeit,
        pAdrcCtx->CurrData.HandleData.Drc_v11.GlobalContrast,
        pAdrcCtx->CurrData.HandleData.Drc_v11.LoLitContrast);

    // transfer data to api
    // info
    pAdrcCtx->drcAttrV11.Info.EnvLv = pAdrcCtx->CurrData.EnvLv;

    // damp
    AdrcDampingV11(&pAdrcCtx->CurrData, &pAdrcCtx->PrevData, pAdrcCtx->drcAttrV11.opMode,
                   pAdrcCtx->frameCnt);

    // get io data
    AdrcGetTuningProcResV11(&pAdrcCtx->AdrcProcRes, &pAdrcCtx->CurrData,
                            pAdrcCtx->AeResult.LongFrmMode, pAdrcCtx->FrameNumber,
                            pAdrcCtx->frameCnt);

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
    float adrc_gain      = pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.adrc_gain;
    float log_ratio2     = log(pAdrcCtx->AeResult.Next.L2S_Ratio * adrc_gain) / log(2.0f) + 12;
    float offsetbits_int = (float)(pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.offset_pow2);
    float offsetbits     = offsetbits_int * pow(2, MFHDR_LOG_Q_BITS);
    float hdrbits        = log_ratio2 * pow(2, MFHDR_LOG_Q_BITS);
    float hdrvalidbits   = hdrbits - offsetbits;
    float compres_scl    = (12 * pow(2, MFHDR_LOG_Q_BITS * 2)) / hdrvalidbits;
    pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_scl = (int)(compres_scl);

    // get sw_drc_min_ogain
    if (pAdrcCtx->CurrData.Others.OutPutLongFrame)
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.min_ogain = 1 << 15;
    else {
        float sw_drc_min_ogain = 1 / (pAdrcCtx->AeResult.Next.L2S_Ratio * adrc_gain);
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.min_ogain =
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
            pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[i] = (int)(curveTable[i]);
        }
    }

    LOGV_ATMO("%s: nextRatioLS:%f sw_drc_position:%d sw_drc_compres_scl:%d sw_drc_offset_pow2:%d\n",
              __FUNCTION__, pAdrcCtx->AeResult.Next.L2S_Ratio,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.position,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_scl,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.offset_pow2);
    LOGV_ATMO("%s: sw_drc_lpdetail_ratio:%d sw_drc_hpdetail_ratio:%d sw_drc_delta_scalein:%d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.lpdetail_ratio,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.hpdetail_ratio,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.delta_scalein);
    LOGV_ATMO("%s: sw_drc_bilat_wt_off:%d sw_drc_weipre_frame:%d sw_drc_weicur_pix:%d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.bilat_wt_off,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.weipre_frame,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.weicur_pix);
    LOGV_ATMO("%s: sw_drc_edge_scl:%d sw_drc_motion_scl:%d sw_drc_force_sgm_inv0:%d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.edge_scl,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.motion_scl,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.force_sgm_inv0);
    LOGV_ATMO("%s: sw_drc_space_sgm_inv0:%d sw_drc_space_sgm_inv1:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.space_sgm_inv0,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.space_sgm_inv1);
    LOGV_ATMO("%s: sw_drc_range_sgm_inv0:%d sw_drc_range_sgm_inv1:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.range_sgm_inv0,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.range_sgm_inv1);
    LOGV_ATMO(
        "%s: sw_drc_weig_bilat:%d sw_drc_weig_maxl:%d sw_drc_bilat_soft_thd:%d "
        "sw_drc_enable_soft_thd:%d\n",
        __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.weig_bilat,
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.weig_maxl,
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.bilat_soft_thd,
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.enable_soft_thd);
    LOGV_ATMO("%s: sw_drc_min_ogain:%d sw_drc_iir_weight:%d\n", __FUNCTION__,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.min_ogain,
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.iir_weight);
    LOGV_ATMO("%s: sw_drc_gain_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[0],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[1],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[2],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[3],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[4],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[5],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[6],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[7],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[8],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[9],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[10],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[11],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[12],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[13],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[14],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[15],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.gain_y[16]);
    LOGV_ATMO("%s: sw_drc_scale_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
              __FUNCTION__, pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[0],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[1],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[2],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[3],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[4],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[5],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[6],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[7],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[8],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[9],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[10],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[11],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[12],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[13],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[14],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[15],
              pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.scale_y[16]);
    LOGV_ATMO(
        "%s: CompressMode:%d sw_drc_compres_y: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
        "%d\n",
        __FUNCTION__, pAdrcCtx->AdrcProcRes.CompressMode,
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[0],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[1],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[2],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[3],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[4],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[5],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[6],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[7],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[8],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[9],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[10],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[11],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[12],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[13],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[14],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[15],
        pAdrcCtx->AdrcProcRes.DrcProcRes.Drc_v11.compres_y[16]);

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

    float ByPassThr = pAdrcCtx->drcAttrV11.stAuto.DrcTuningPara.ByPassThr;

    if (pAdrcCtx->frameCnt <= 2)  // start frame
        bypass = false;
    else if (pAdrcCtx->drcAttrV11.opMode == DRC_OPMODE_MANU)  // api
        bypass = false;
    else if (pAdrcCtx->drcAttrV11.opMode != pAdrcCtx->PrevData.ApiMode)  // api change
        bypass = false;
    else {  // EnvLv change
        // get current EnvLv from AecPreRes
        AdrcGetEnvLvV11(pAdrcCtx, AecHdrPreResult);

        // motion coef
        pAdrcCtx->CurrData.MotionCoef = MOVE_COEF_DEFAULT;

        // transfer ae data to CurrHandle
        pAdrcCtx->CurrData.EnvLv =
            LIMIT_VALUE(pAdrcCtx->CurrData.EnvLv, ADRCNORMALIZEMAX, ADRCNORMALIZEMIN);

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
              pAdrcCtx->AeResult.LongFrmMode, pAdrcCtx->drcAttrV11.opMode, pAdrcCtx->CurrData.EnvLv,
              bypass);

    LOG1_ATMO("%s: CtrlEnvLv:%f PrevEnvLv:%f diff:%f ByPassThr:%f opMode:%d bypass:%d!\n",
              __FUNCTION__, pAdrcCtx->CurrData.EnvLv, pAdrcCtx->PrevData.EnvLv, diff, ByPassThr,
              pAdrcCtx->drcAttrV11.opMode, bypass);

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

    CalibDbV2_drc_V11_t* calibv2_adrc_calib =
        (CalibDbV2_drc_V11_t*)(CALIBDBV2_GET_MODULE_PTR(pCalibDb, adrc_calib));

    pAdrcCtx->drcAttrV11.opMode = DRC_OPMODE_AUTO;
    ConfigV11(pAdrcCtx);  // set default para
    memcpy(&pAdrcCtx->CalibDBV11, calibv2_adrc_calib, sizeof(CalibDbV2_drc_V11_t));  // load iq
                                                                                     // paras
    memcpy(&pAdrcCtx->drcAttrV11.stAuto, calibv2_adrc_calib,
           sizeof(CalibDbV2_drc_V11_t));  // set stAuto

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
