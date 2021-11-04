/*
 * rk_aiq_user_api2_camgroup.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef RK_AIQ_USER_API2_CAMGROUP_H
#define RK_AIQ_USER_API2_CAMGROUP_H

#include "rk_aiq.h"
#include "rk_aiq_algo_des.h"
#include "rk_aiq_user_api_sysctl.h"

/*****************************************
 * Useage examples
 * 
 * 1) create single cam ctxs
 * sns_ctx1 = rk_aiq_uapi2_sysctl_init (ent_name_sns1,...);
 * sns_ctx2 = rk_aiq_uapi2_sysctl_init (ent_name_sns2,...);
 * sns_ctx3 = rk_aiq_uapi2_sysctl_init (ent_name_sns3,...);
 *
 * 2) create cam group ctx, and add single cam's ctx to group
 * camgroup_ctx = rk_aiq_uapi2_camgroup_create(cfg);
 * // will control the life cycle of sns_ctx till unbind
 * rk_aiq_uapi2_camgroup_bind(camgroup_ctx, sns_ctx_array, 3);
 *
 * 3) prepare camgroup, will prepare each single cam internal
 * rk_aiq_uapi2_camgroup_prepare(camgroup_ctx)
 *
 * 4) start camgroup, will prepare each single cam internal
 * rk_aiq_uapi2_camgroup_start(camgroup_ctx)
 *
 *   running single AIQ and group cams algo
 *
 * 5) stop camgroup, will stop each single cam internal
 * rk_aiq_uapi2_camgroup_stop(camgroup_ctx)
 * 5.1) may unbind, the unbinded cam's life cycle will not controlled by cam group 
 *  rk_aiq_uapi2_camgroup_unbind 
 * 6) destroy camgroup, will deinit each single cam
 * rk_aiq_uapi2_camgroup_destroy(camgroup_ctx)
 * 6.1) may call unbinded cam's deinit 

 ****************************************/

RKAIQ_BEGIN_DECLARE

typedef struct rk_aiq_camgroup_ctx_s rk_aiq_camgroup_ctx_t;

typedef struct rk_aiq_camgroup_instance_cfg_s {
    const char* sns_ent_nm_array[RK_AIQ_CAM_GROUP_MAX_CAMS];
    int sns_num;
    const char* config_file_dir;
} rk_aiq_camgroup_instance_cfg_t;

rk_aiq_camgroup_ctx_t*
rk_aiq_uapi2_camgroup_create(rk_aiq_camgroup_instance_cfg_t* cfg);

rk_aiq_sys_ctx_t*
rk_aiq_uapi2_camgroup_getAiqCtxBySnsNm(rk_aiq_camgroup_ctx_t* camgroup_ctx, const char* sns_entity_name);

XCamReturn
rk_aiq_uapi2_camgroup_bind(rk_aiq_camgroup_ctx_t* camgroup_ctx, rk_aiq_sys_ctx_t** ctx, int num);

XCamReturn
rk_aiq_uapi2_camgroup_unbind(rk_aiq_camgroup_ctx_t* camgroup_ctx, rk_aiq_sys_ctx_t** ctx, int num);

XCamReturn
rk_aiq_uapi2_camgroup_prepare(rk_aiq_camgroup_ctx_t* camgroup_ctx, rk_aiq_working_mode_t mode);

XCamReturn
rk_aiq_uapi2_camgroup_start(rk_aiq_camgroup_ctx_t* camgroup_ctx);

XCamReturn
rk_aiq_uapi2_camgroup_stop(rk_aiq_camgroup_ctx_t* camgroup_ctx);

XCamReturn
rk_aiq_uapi2_camgroup_destroy(rk_aiq_camgroup_ctx_t* camgroup_ctx);

RKAIQ_END_DECLARE

#endif
