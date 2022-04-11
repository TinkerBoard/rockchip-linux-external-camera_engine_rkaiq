
#ifndef _RKAIQ_BAYERTNR_V23_H_
#define _RKAIQ_BAYERTNR_V23_H_

#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "base/xcam_log.h"
#include "rk_aiq_comm.h"
#include "RkAiqCalibDbTypes.h"
#include "RkAiqCalibApi.h"
#include "abayertnrV23/rk_aiq_types_abayertnr_algo_prvt_v23.h"

XCAM_BEGIN_DECLARE


Abayertnr_result_V23_t bayertnr_select_params_by_ISO_V23(RK_Bayertnr_Params_V23_t *pParams, RK_Bayertnr_Params_V23_Select_t *pSelect, Abayertnr_ExpInfo_V23_t *pExpInfo);

Abayertnr_result_V23_t bayertnr_fix_transfer_V23(RK_Bayertnr_Params_V23_Select_t* pSelect, RK_Bayertnr_Fix_V23_t *pFix, rk_aiq_bayertnr_strength_v23_t* pStrength, Abayertnr_ExpInfo_V23_t *pExpInfo);

Abayertnr_result_V23_t bayertnr_fix_printf_V23(RK_Bayertnr_Fix_V23_t * pFix);

Abayertnr_result_V23_t bayertnr_get_setting_by_name_json_V23(CalibDbV2_BayerTnrV23_t* pCalibdb, char *name, int *calib_idx, int *tuning_idx);

Abayertnr_result_V23_t bayertnr_init_params_json_V23(RK_Bayertnr_Params_V23_t *pParams, CalibDbV2_BayerTnrV23_t* pCalibdb, int calib_idx, int tuning_idx);

Abayertnr_result_V23_t bayertnr_config_setting_param_json_V23(RK_Bayertnr_Params_V23_t *pParams, CalibDbV2_BayerTnrV23_t* pCalibdbV23, char* param_mode, char * snr_name);


XCAM_END_DECLARE


#endif  // BAYERNR_READ_PARM_H_

