/*
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

#include "sample_comm.h"

static void sample_adebayer_usage()
{
    printf("Usage : \n");
    printf("\t 0) ADEBAYER:         enable/disable in sync.\n");
    printf("\t 1) ADEBAYER:         set enhance strength of 250 in sync.\n");
    printf("\t 2) ADEBAYER:         set enhance strength of 0 in sync.\n");
    printf("\t 3) ADEBAYER:         set high freq thresh of 250 in sync.\n");
    printf("\t 4) ADEBAYER:         set high freq thresh of 0 in sync.\n");
    printf("\t 5) ADEBAYER:         set low freq thresh of 250 in sync.\n");
    printf("\t 6) ADEBAYER:         set low freq thresh of 0 in sync.\n");
    printf("\n");

    printf("\t h) ADEBAYER: help.\n");
    printf("\t q/Q) ADEBAYER:       return to main sample screen.\n");
    printf("\n");
    printf("\t please press the key: \n\n");

    return;
}

void sample_print_adebayer_info(const void *arg)
{
    printf ("enter ADEBAYER test!\n");
}

XCamReturn sample_adebayer_en(const rk_aiq_sys_ctx_t* ctx, bool en)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (ctx == NULL) {
        ret = XCAM_RETURN_ERROR_PARAM;
        RKAIQ_SAMPLE_CHECK_RET(ret, "param error!");
    }

    adebayer_attrib_t attr;
    ret = rk_aiq_user_api2_adebayer_GetAttrib(ctx, &attr);
    RKAIQ_SAMPLE_CHECK_RET(ret, "get debayer attrib failed!");
    attr.enable = en;
    rk_aiq_user_api2_adebayer_SetAttrib(ctx, attr);

    ret = rk_aiq_user_api2_adebayer_GetAttrib(ctx, &attr);
    RKAIQ_SAMPLE_CHECK_RET(ret, "get ldch attrib failed!");

    printf ("sync_mode: %d, done: %d\n", attr.sync.sync_mode, attr.sync.done);

    return ret;
}

XCamReturn sample_adebayer_setEnhanceStrength(const rk_aiq_sys_ctx_t* ctx, unsigned char *strength)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (ctx == NULL) {
        ret = XCAM_RETURN_ERROR_PARAM;
        RKAIQ_SAMPLE_CHECK_RET(ret, "param error!");
    }

    adebayer_attrib_t attr;
    ret = rk_aiq_user_api2_adebayer_GetAttrib(ctx, &attr);
    RKAIQ_SAMPLE_CHECK_RET(ret, "get debayer attrib failed!");
    memcpy(attr.enhance_strength, strength, sizeof(attr.enhance_strength));
    rk_aiq_user_api2_adebayer_SetAttrib(ctx, attr);

    ret = rk_aiq_user_api2_adebayer_GetAttrib(ctx, &attr);
    RKAIQ_SAMPLE_CHECK_RET(ret, "get ldch attrib failed!");

    printf ("sync_mode: %d, done: %d\n", attr.sync.sync_mode, attr.sync.done);

    return ret;
}

XCamReturn sample_adebayer_setLowFreqThresh(const rk_aiq_sys_ctx_t* ctx, __u8 thresh)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (ctx == NULL) {
        ret = XCAM_RETURN_ERROR_PARAM;
        RKAIQ_SAMPLE_CHECK_RET(ret, "param error!");
    }

    adebayer_attrib_t attr;
    ret = rk_aiq_user_api2_adebayer_GetAttrib(ctx, &attr);
    RKAIQ_SAMPLE_CHECK_RET(ret, "get debayer attrib failed!");
    attr.low_freq_thresh = thresh;
    rk_aiq_user_api2_adebayer_SetAttrib(ctx, attr);

    ret = rk_aiq_user_api2_adebayer_GetAttrib(ctx, &attr);
    RKAIQ_SAMPLE_CHECK_RET(ret, "get ldch attrib failed!");

    printf ("sync_mode: %d, done: %d\n", attr.sync.sync_mode, attr.sync.done);

    return ret;
}

XCamReturn sample_adebayer_setHighFreqThresh(const rk_aiq_sys_ctx_t* ctx, __u8 thresh)
{
    XCamReturn ret = XCAM_RETURN_NO_ERROR;
    if (ctx == NULL) {
        ret = XCAM_RETURN_ERROR_PARAM;
        RKAIQ_SAMPLE_CHECK_RET(ret, "param error!");
    }

    adebayer_attrib_t attr;
    ret = rk_aiq_user_api2_adebayer_GetAttrib(ctx, &attr);
    RKAIQ_SAMPLE_CHECK_RET(ret, "get debayer attrib failed!");
    attr.high_freq_thresh = thresh;
    rk_aiq_user_api2_adebayer_SetAttrib(ctx, attr);

    return ret;
}

XCamReturn sample_adebayer_module (const void *arg)
{
    int key = -1;
    CLEAR();

    const demo_context_t *demo_ctx = (demo_context_t *)arg;
    const rk_aiq_sys_ctx_t* ctx;
    if (demo_ctx->camGroup) {
        ctx = (rk_aiq_sys_ctx_t*)(demo_ctx->camgroup_ctx);
    } else {
        ctx = (rk_aiq_sys_ctx_t*)(demo_ctx->aiq_ctx);
    }

    if (ctx == nullptr) {
        ERR ("%s, ctx is nullptr\n", __FUNCTION__);
        return XCAM_RETURN_ERROR_PARAM;
    }

    sample_adebayer_usage ();
    do {

        key = getchar ();
        while (key == '\n' || key == '\r')
            key = getchar ();
        printf ("\n");

        switch (key)
        {
        case 'h':
            CLEAR();
            sample_adebayer_usage ();
            break;
        case '0': {
            static bool on = false;
            on = !on;
            sample_adebayer_en(ctx, on);
            printf("%s adebayer\n\n", on ? "enable" : "disable");
            break;
        }
        case '1': {
            unsigned char enhance_strength[9] = {250,250,250,250,250,250,250,250,250};
            sample_adebayer_setEnhanceStrength(ctx, enhance_strength);
            printf("test the enhance_strength of 255 in sync mode...\n");
            break;
        }
        case '2': {
            unsigned char enhance_strength[9] = {0,0,0,0,0,0,0,0,0};
            sample_adebayer_setEnhanceStrength(ctx, enhance_strength);
            printf("test the enhance_strength of 0 in sync mode...\n");
            break;
        }
        case '3':
            sample_adebayer_setHighFreqThresh(ctx, 250);
            printf("test the high freq thresh of 250 in sync mode...\n");
            break;
        case '4':
            sample_adebayer_setHighFreqThresh(ctx, 0);
            printf("test the high freq thresh of 0 in sync mode...\n");
            break;
        case '5':
            sample_adebayer_setLowFreqThresh(ctx, 250);
            printf("test the low freq thresh of 250 in sync mode...\n");
            break;
        case '6':
            sample_adebayer_setLowFreqThresh(ctx, 0);
            printf("test the low freq thresh of 0 in sync mode...\n");
            break;
        default:
            break;
        }
    } while (key != 'q' && key != 'Q');

    return XCAM_RETURN_NO_ERROR;
}
