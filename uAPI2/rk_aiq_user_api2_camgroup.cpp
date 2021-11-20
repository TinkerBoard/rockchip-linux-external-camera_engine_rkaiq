/*
 * rk_aiq_user_api2_camgroup.cpp
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

#include "rk_aiq_user_api2_sysctl.h"
#include "rk_aiq_user_api2_camgroup.h"
#include "RkAiqCamGroupManager.h"

using namespace RkCam;
using namespace XCam;

typedef struct rk_aiq_camgroup_ctx_s {
    rk_aiq_sys_ctx_t* cam_ctxs_array[RK_AIQ_CAM_GROUP_MAX_CAMS];
    int sns_ids_array[RK_AIQ_CAM_GROUP_MAX_CAMS];
    int cam_ctxs_num;
    SmartPtr<RkAiqCamGroupManager> cam_group_manager;
    SmartPtr<Mutex> _apiMutex;
    CamCalibDbCamgroup_t* _camgroup_calib;
} rk_aiq_camgroup_ctx_t;

#define RKAIQ_API_SMART_LOCK(ctx) \
    SmartLock lock (*ctx->_apiMutex.ptr());

static XCamReturn
_cam_group_bind(rk_aiq_camgroup_ctx_t* camgroup_ctx, rk_aiq_sys_ctx_t* aiq_ctx)
{
    ENTER_XCORE_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    // bind aiq to group
    ret = camgroup_ctx->cam_group_manager->bind(aiq_ctx->_rkAiqManager.ptr());
    if (ret) {
        LOGE("bind sensor %s aiq ctx %p failed !", aiq_ctx->_sensor_entity_name, aiq_ctx);
        return ret;
    }

    // bind group to aiq
    aiq_ctx->_camGroupManager = camgroup_ctx->cam_group_manager.ptr();
    aiq_ctx->_analyzer->setCamGroupManager(aiq_ctx->_camGroupManager);
    // set first one as main cam
    aiq_ctx->_rkAiqManager->setCamGroupManager(aiq_ctx->_camGroupManager,
                                               camgroup_ctx->cam_ctxs_num == 0 ? true : false);

    camgroup_ctx->cam_ctxs_num++;
    camgroup_ctx->cam_ctxs_array[aiq_ctx->_camPhyId] = aiq_ctx;

    LOGD("%s: bind sensor %s aiq ctx success !", aiq_ctx->_sensor_entity_name, aiq_ctx);

    EXIT_XCORE_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

static XCamReturn
_cam_group_unbind(rk_aiq_camgroup_ctx_t* camgroup_ctx, rk_aiq_sys_ctx_t* aiq_ctx)
{
    ENTER_XCORE_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    ret = camgroup_ctx->cam_group_manager->unbind(aiq_ctx->_camPhyId);
    if (ret) {
        LOGE("unbind sensor %s aiq ctx 0x%x failed !", aiq_ctx->_sensor_entity_name, aiq_ctx);
        return ret;
    }
    aiq_ctx->_camGroupManager = NULL;
    aiq_ctx->_analyzer->setCamGroupManager(NULL);
    aiq_ctx->_rkAiqManager->setCamGroupManager(NULL, false);
    camgroup_ctx->cam_ctxs_array[aiq_ctx->_camPhyId] = NULL;
    camgroup_ctx->cam_ctxs_num--;

    LOGD("%s: unbind sensor %s aiq ctx success !", aiq_ctx->_sensor_entity_name, aiq_ctx);

    EXIT_XCORE_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

rk_aiq_camgroup_ctx_t*
rk_aiq_uapi2_camgroup_create(rk_aiq_camgroup_instance_cfg_t* cfg)
{
    ENTER_XCORE_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    rk_aiq_camgroup_ctx_t* camgroup_ctx = NULL;
    rk_aiq_sys_ctx_t* aiq_ctx = NULL;
    char camgroup_jsfile[128] = {'\0'};

    camgroup_ctx = new rk_aiq_camgroup_ctx_t();

    if (!camgroup_ctx)
        goto error;

    camgroup_ctx->cam_group_manager = new RkAiqCamGroupManager();
    if (!camgroup_ctx->cam_group_manager.ptr())
        goto error;

    camgroup_ctx->_apiMutex = new Mutex();
    //RKAIQ_API_SMART_LOCK(camgroup_ctx);

    if (cfg->sns_num > RK_AIQ_CAM_GROUP_MAX_CAMS) {
        LOGE("nums %s is over the max cams %d !", cfg->sns_num, RK_AIQ_CAM_GROUP_MAX_CAMS);
        return NULL;
    }

    camgroup_ctx->cam_ctxs_num = 0;
    memset(camgroup_ctx->cam_ctxs_array, 0, sizeof(camgroup_ctx->cam_ctxs_array));

    for (int i = 0; i < cfg->sns_num; i++) {
        aiq_ctx = rk_aiq_uapi_sysctl_init(cfg->sns_ent_nm_array[i],
                                          cfg->config_file_dir, NULL, NULL);
        if (!aiq_ctx) {
           LOGE("init aiq ctx %d for %s failed !", i, cfg->sns_ent_nm_array[i]);
           goto error;
        }
        // notify single cam work as multiple mode
        rk_aiq_uapi_sysctl_setMulCamConc(aiq_ctx, true);

        ret = _cam_group_bind(camgroup_ctx, aiq_ctx);
        if (ret) {
            LOGE("%s: bind sensor %s aiq ctx 0x%x failed !",
                 __func__, aiq_ctx->_sensor_entity_name, aiq_ctx);
            goto error;
        }
    }

    sprintf(camgroup_jsfile, "%s/%s", cfg->config_file_dir, "camgroup.json");
    camgroup_ctx->_camgroup_calib = RkAiqCalibDbV2::createCalibDbCamgroup(camgroup_jsfile);
    ret = camgroup_ctx->cam_group_manager->setCamgroupCalib(camgroup_ctx->_camgroup_calib);
    if (ret) {
        LOGE("%s: set camgroup calib failed !", __func__);
        goto error;
    }
    ret = camgroup_ctx->cam_group_manager->init();
    if (ret) {
        LOGE("%s: init failed !", __func__);
        goto error;
    }

    LOGD("%s: create camgroup 0x%x success !", __func__, camgroup_ctx);

    EXIT_XCORE_FUNCTION();

    return camgroup_ctx;

error:
    LOGE("%s failed", __func__);
    if (camgroup_ctx)
        rk_aiq_uapi2_camgroup_destroy(camgroup_ctx);
    return NULL;
}

rk_aiq_sys_ctx_t*
rk_aiq_uapi2_camgroup_getAiqCtxBySnsNm(rk_aiq_camgroup_ctx_t* camgroup_ctx, const char* sns_entity_name)
{
    ENTER_XCORE_FUNCTION();

    RKAIQ_API_SMART_LOCK(camgroup_ctx);

    for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
        if (camgroup_ctx->cam_ctxs_array[i]) {
            if (strcmp(camgroup_ctx->cam_ctxs_array[i]->_sensor_entity_name, sns_entity_name) == 0) {
                LOGD("%s: get sensor %s aiq ctx 0x%x success !",
                     __func__, sns_entity_name, camgroup_ctx->cam_ctxs_array[i]);
                return camgroup_ctx->cam_ctxs_array[i];
            }
        }
    }

    LOGD("%s: get sensor %s aiq ctx failed !", __func__, sns_entity_name);

    EXIT_XCORE_FUNCTION();

    return NULL;

}

XCamReturn
rk_aiq_uapi2_camgroup_bind(rk_aiq_camgroup_ctx_t* camgroup_ctx, rk_aiq_sys_ctx_t** ctx, int num)
{
    ENTER_XCORE_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RKAIQ_API_SMART_LOCK(camgroup_ctx);

    if (camgroup_ctx->cam_ctxs_num + num > RK_AIQ_CAM_GROUP_MAX_CAMS) {
        LOGE("binded num %d + num %d > max %d !", camgroup_ctx->cam_ctxs_num, num, RK_AIQ_CAM_GROUP_MAX_CAMS);
        return XCAM_RETURN_ERROR_OUTOFRANGE;
    }

    for (int j = 0; j < num; j++) {
        // query bind status firstly
        bool need_bind = true;
        for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
            if (camgroup_ctx->cam_ctxs_array[i] == ctx[j]) {
                LOGI("already binded for ctx 0x%x", ctx[j]);
                need_bind = false;
                break;
            }
        }
        // find a empty slot
        if (need_bind) {
            for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
                if (camgroup_ctx->cam_ctxs_array[i] == NULL) {
                    ret = _cam_group_bind(camgroup_ctx, ctx[j]);
                    if (ret) {
                        LOGE("%s: bind sensor %s aiq ctx 0x%x failed !",
                             __func__, ctx[j]->_sensor_entity_name, ctx[j]);
                        break;
                    }
                }
            }
        }
    }

    LOGD("%s: bind sensor aiq ctxs success !", __func__);

    EXIT_XCORE_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
rk_aiq_uapi2_camgroup_unbind(rk_aiq_camgroup_ctx_t* camgroup_ctx, rk_aiq_sys_ctx_t** ctx, int num)
{
    ENTER_XCORE_FUNCTION();

    RKAIQ_API_SMART_LOCK(camgroup_ctx);

    for (int j = 0; j < num; j++) {
        for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
            if (camgroup_ctx->cam_ctxs_array[i] == ctx[j]) {
                if (_cam_group_unbind(camgroup_ctx, ctx[j])) {
                    LOGE("%s: unbind sensor %s aiq ctx 0x%x failed !",
                         __func__, ctx[j]->_sensor_entity_name, ctx[j]);
                    break;
                }
            }
        }
    }

    LOGD("%s: unbind sensor aiq ctxs success !", __func__);

    EXIT_XCORE_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
rk_aiq_uapi2_camgroup_prepare(rk_aiq_camgroup_ctx_t* camgroup_ctx, rk_aiq_working_mode_t mode)
{
    ENTER_XCORE_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RKAIQ_API_SMART_LOCK(camgroup_ctx);

    for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
        rk_aiq_sys_ctx_t* aiq_ctx = camgroup_ctx->cam_ctxs_array[i];
        if (aiq_ctx) {
            ret = rk_aiq_uapi_sysctl_prepare(aiq_ctx, 0, 0, mode);
            if (ret) {
                LOGE("%s: prepare failed for aiq ctx 0x%x !", __func__, aiq_ctx);
                continue;
            }
        }
    }

    ret = camgroup_ctx->cam_group_manager->prepare();
    if (ret) {
        LOGE("%s: prepare failed !", __func__);
        return ret;
    }

    LOGD("%s: prepare camgroup success !", __func__);

    EXIT_XCORE_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
rk_aiq_uapi2_camgroup_start(rk_aiq_camgroup_ctx_t* camgroup_ctx)
{
    ENTER_XCORE_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RKAIQ_API_SMART_LOCK(camgroup_ctx);

    ret = camgroup_ctx->cam_group_manager->start();
    if (ret) {
        LOGE("%s: start failed !", __func__);
        return ret;
    }

    for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
        rk_aiq_sys_ctx_t* aiq_ctx = camgroup_ctx->cam_ctxs_array[i];
        if (aiq_ctx) {
            ret = rk_aiq_uapi_sysctl_start(aiq_ctx);
            if (ret) {
                LOGE("%s: start failed for aiq ctx 0x%x !", __func__, aiq_ctx);
                continue;
            }
        }
    }

    LOGD("%s: start camgroup success !", __func__);

    EXIT_XCORE_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}

XCamReturn
rk_aiq_uapi2_camgroup_stop(rk_aiq_camgroup_ctx_t* camgroup_ctx)
{
    ENTER_XCORE_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    RKAIQ_API_SMART_LOCK(camgroup_ctx);

    ret = camgroup_ctx->cam_group_manager->stop();
    if (ret) {
        LOGE("%s: stop failed !", __func__);
        return ret;
    }

    for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
        rk_aiq_sys_ctx_t* aiq_ctx = camgroup_ctx->cam_ctxs_array[i];
        if (aiq_ctx) {
            ret = rk_aiq_uapi_sysctl_stop(aiq_ctx, false);
            if (ret) {
                LOGE("%s: stop failed for aiq ctx 0x%x !", __func__, aiq_ctx);
                continue;
            }
        }
    }

    LOGD("%s: stop camgroup success !", __func__);

    EXIT_XCORE_FUNCTION();

    return XCAM_RETURN_NO_ERROR;

}

XCamReturn
rk_aiq_uapi2_camgroup_destroy(rk_aiq_camgroup_ctx_t* camgroup_ctx)
{
    ENTER_XCORE_FUNCTION();

    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    {
        RKAIQ_API_SMART_LOCK(camgroup_ctx);
        for (int i = 0; i < RK_AIQ_CAM_GROUP_MAX_CAMS; i++) {
            rk_aiq_sys_ctx_t* aiq_ctx = camgroup_ctx->cam_ctxs_array[i];
            if (aiq_ctx) {
                ret = _cam_group_unbind(camgroup_ctx, aiq_ctx);
                if (ret) {
                    LOGE("%s: unbind sensor %s aiq ctx 0x%x failed !",
                         __func__, aiq_ctx->_sensor_entity_name, aiq_ctx);
                    continue;
                }
                rk_aiq_uapi_sysctl_deinit(aiq_ctx);
            }
        }

        if (camgroup_ctx->cam_ctxs_num > 0) {
            LOGE("impossible case, some aiq ctx may not deinit !");
        }
        ret = camgroup_ctx->cam_group_manager->deInit();
        if (ret) {
            LOGE("%s: deinit failed !", __func__);
            return ret;
        }
        camgroup_ctx->cam_group_manager.release();
    }
    if (camgroup_ctx->_camgroup_calib) {
        RkAiqCalibDbV2::CamCalibDbCamgroupFree(camgroup_ctx->_camgroup_calib);
    }
    camgroup_ctx->_apiMutex.release();
    delete camgroup_ctx;

    LOGD("%s: destroy camgroup success !", __func__);

    EXIT_XCORE_FUNCTION();

    return XCAM_RETURN_NO_ERROR;
}
