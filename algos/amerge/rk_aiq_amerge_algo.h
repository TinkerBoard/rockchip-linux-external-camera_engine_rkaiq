/******************************************************************************
 *
 * Copyright 2019, Fuzhou Rockchip Electronics Co.Ltd . All rights reserved.
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of:
 * Fuzhou Rockchip Electronics Co.Ltd .
 *
 *
 *****************************************************************************/
#ifndef __RK_AIQ_AMERGE_ALGO_H__
#define __RK_AIQ_AMERGE_ALGO_H__

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "ae/rk_aiq_types_ae_algo_int.h"
#include "rk_aiq_uapi_amerge_int.h"
#include "rk_aiq_types_amerge_algo_prvt.h"

XCamReturn AmergeStart(AmergeContext_t* pAmergeCtx);
XCamReturn AmergeStop(AmergeContext_t* pAmergeCtx);
void AmergeIQUpdate(AmergeContext_t* pAmergeCtx);
void AmergeGetSensorInfo( AmergeContext_t* pAmergeCtx, AecProcResult_t AecHdrProcResult);
void MergeNewMalloc(AmergeConfig_t* pAmergeConfig, AmergeCalib_t* pCalibDb, AmergeVersion_t HWversion);
void AmergeUpdateConfig(AmergeContext_t* pAmergeCtx, AmergeCalib_t* pCalibDb);
void AmergeProcessing(AmergeContext_t* pAmergeCtx);
bool AmergeByPassProcessing(AmergeContext_t* pAmergeCtx, AecPreResult_t AecHdrPreResult);
XCamReturn AmergeInit(AmergeContext_t **ppAmergeCtx, CamCalibDbV2Context_t* pCalibV2) ;
XCamReturn AmergeRelease(AmergeContext_t* pAmergeCtx) ;


#endif
