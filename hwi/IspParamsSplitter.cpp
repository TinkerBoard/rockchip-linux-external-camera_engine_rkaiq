/*
 * IspParamsSplitter.h - Split ISP params to Left/Right ISP params
 *
 *  Copyright (c) 2021 Rockchip Electronics Co., Ltd
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
 * Author: Cody Xie <cody.xie@rock-chips.com>
 */
#include "IspParamsSplitter.h"

#include <utility>

#include "common/rk_isp20_hw.h"
#include "common/rkisp2-config.h"
#include "common/rkisp3-config.h"

#include "algos/ae/rk_aiq_types_ae_hw.h"

using namespace RkCam;

//#define DEBUG

#define MAX(a,b) (((a)>(b))?(a):(b))

namespace {
// Internal implementation to split submodule configs eg:
//  * SplitIsp2xAeLittle
//  * SplitIsp2xAeBig0
//  * SplitIsp3xAeBig0
// Then a module can be an aggregation of submodules
// for example:
// SplitAecParams
//   -> SplitIsp2xAeLittle
//   -> SplitIsp3xAeBig0

/*********************************************/
/*            Aec hwi splitter               */
/*********************************************/

void SplitAecWeight(
    u8* ori_weight,
    u8* left_weight,
    u8* right_weight,
    WinSplitMode mode,
    u8 wnd_num
) {
    switch (mode) {
    case LEFT_AND_RIGHT_MODE:
        for (int i = 0; i < wnd_num; i++) {
            for (int j = 0; j < wnd_num; j++) {
                left_weight[i * wnd_num + j] = ori_weight[i * wnd_num + j / 2];
                right_weight[i * wnd_num + j] = ori_weight[i * wnd_num + j / 2 + j % 2 + wnd_num / 2];
            }
        }
        break;
    case LEFT_MODE:
    case RIGHT_MODE:
        memcpy(left_weight, ori_weight, wnd_num * wnd_num * sizeof(u8));
        memcpy(right_weight, ori_weight, wnd_num * wnd_num * sizeof(u8));
    default:
        break;
    }
}

void SplitAecSubWin(
    u8* subwin_en,
    struct isp2x_window* ori_win,
    struct isp2x_window* left_win,
    struct isp2x_window* right_win,
    IspParamsSplitter::Rectangle left_isp_rect_,
    IspParamsSplitter::Rectangle right_isp_rect_,
    WinSplitMode* mode
) {

    for (int i = 0; i < ISP2X_RAWAEBIG_SUBWIN_NUM; i++) {
        if (subwin_en[i] == 1) { //only when subwin is enabled, should split hwi params
            if (ori_win[i].h_offs + ori_win[i].h_size <= left_isp_rect_.w) {
#ifdef DEBUG
                printf("win locate in left isp\n");
#endif
                mode[i] = LEFT_MODE;

                left_win[i].h_offs = ori_win[i].h_offs;
                left_win[i].h_size = ori_win[i].h_size;
                left_win[i].v_offs = ori_win[i].v_offs;
                left_win[i].v_size = ori_win[i].v_size;

                right_win[i].h_offs = 0;
                right_win[i].h_size = ori_win[i].h_size;
                right_win[i].v_offs = ori_win[i].v_offs;
                right_win[i].v_size = ori_win[i].v_size;
            }
            else if (ori_win[i].h_offs >= right_isp_rect_.x) {
#ifdef DEBUG
                printf("win locate in right isp\n");
#endif
                mode[i] = RIGHT_MODE;

                //win only locate in right isp, actually stats of left isp would not be used
                left_win[i].h_offs = 0;
                left_win[i].h_size = ori_win[i].h_size;
                left_win[i].v_offs = ori_win[i].v_offs;
                left_win[i].v_size = ori_win[i].v_size;

                right_win[i].h_offs = ori_win[i].h_offs - right_isp_rect_.x;
                right_win[i].h_size = ori_win[i].h_size;
                right_win[i].v_offs = ori_win[i].v_offs;
                right_win[i].v_size = ori_win[i].v_size;

            }
            else {
#ifdef DEBUG
                printf(" win locate at left&right isp\n");
#endif
                mode[i] = LEFT_AND_RIGHT_MODE;

                left_win[i].h_offs = ori_win[i].h_offs;
                left_win[i].h_size = MAX(0, left_isp_rect_.w - left_win[i].h_offs);
                left_win[i].v_offs = ori_win[i].v_offs;
                left_win[i].v_size = ori_win[i].v_size;


                right_win[i].h_offs = left_win[i].h_offs + left_win[i].h_size - right_isp_rect_.x;
                right_win[i].h_size = MAX(0, ori_win[i].h_size - left_win[i].h_size);
                right_win[i].v_offs = ori_win[i].v_offs;
                right_win[i].v_size = ori_win[i].v_size;
            }
        }
    }
};

void SplitAecCalcBlockSize(
    struct isp2x_window* left_win,
    struct isp2x_window* right_win,
    u8 wnd_num,
    IspParamsSplitter::Rectangle right_isp_rect_,
    u16* block_h
) {

    bool loop_en = true;

    while (loop_en && *block_h > 0) {

        left_win->h_size = *block_h * wnd_num;
        right_win->h_offs = (left_win->h_size + left_win->h_offs > right_isp_rect_.x) ?
                            left_win->h_size + left_win->h_offs - right_isp_rect_.x : 0;

        if (u32(right_win->h_offs + *block_h * wnd_num) > right_isp_rect_.w - 1) {

            (*block_h)--;

        }
        else {
            loop_en = false;

            //if (*block_h % 2)
            //(*block_h)--;

            left_win->h_size = *block_h * wnd_num;
            right_win->h_offs = (left_win->h_size + left_win->h_offs > right_isp_rect_.x) ?
                                left_win->h_size + left_win->h_offs - right_isp_rect_.x : 0;
            right_win->h_offs = right_win->h_offs & 0xfffe;
            right_win->h_size = *block_h * wnd_num;
        }
    }
}

void SplitAecWin(
    isp2x_window* ori_win,
    isp2x_window* left_win,
    isp2x_window* right_win,
    u8 wnd_num,
    IspParamsSplitter::Rectangle left_isp_rect_,
    IspParamsSplitter::Rectangle right_isp_rect_,
    WinSplitMode* mode
) {

    //win only locate in left isp, actually stats of right isp would not be used
    if (ori_win->h_offs + ori_win->h_size <= left_isp_rect_.w) {

#ifdef DEBUG
        printf("win locate in left isp\n");
#endif
        *mode = LEFT_MODE;

        left_win->h_offs = ori_win->h_offs;
        left_win->h_size = ori_win->h_size;
        left_win->v_offs = ori_win->v_offs;
        left_win->v_size = ori_win->v_size;

        right_win->h_offs = 0;
        right_win->h_size = ori_win->h_size;
        right_win->v_offs = ori_win->v_offs;
        right_win->v_size = ori_win->v_size;
    }
    else if (ori_win->h_offs >= right_isp_rect_.x) {

#ifdef DEBUG
        printf("win locate in right isp\n");
#endif
        *mode = RIGHT_MODE;

        //win only locate in right isp, actually stats of left isp would not be used
        left_win->h_offs = 0;
        left_win->h_size = ori_win->h_size;
        left_win->v_offs = ori_win->v_offs;
        left_win->v_size = ori_win->v_size;

        right_win->h_offs = ori_win->h_offs - right_isp_rect_.x;
        right_win->h_size = ori_win->h_size;
        right_win->v_offs = ori_win->v_offs;
        right_win->v_size = ori_win->v_size;

    }
    else {
        if ((ori_win->h_offs + ori_win->h_size / 2) <= left_isp_rect_.w
                && right_isp_rect_.x <= (ori_win->h_offs + ori_win->h_size / 2)) {
#ifdef DEBUG
            printf(" win locate at left&right isp,and center line locate in overlapping zone!\n");
#endif
            *mode = LEFT_AND_RIGHT_MODE;

            //win center locate at overlap zone
            left_win->h_offs = ori_win->h_offs;
            left_win->v_offs = ori_win->v_offs;
            left_win->v_size = ori_win->v_size;

            right_win->v_offs = ori_win->v_offs;
            right_win->v_size = ori_win->v_size;

            u16 block_h = ori_win->h_size / (2 * wnd_num);
            SplitAecCalcBlockSize(left_win, right_win, wnd_num, right_isp_rect_, &block_h);
        }
        else {
#ifdef DEBUG
            printf(" win locate at left&right isp,but center line not locate in overlapping zone!\n");
#endif
            if ((ori_win->h_offs + ori_win->h_size / 2) < right_isp_rect_.x) {

                left_win->h_offs = ori_win->h_offs;
                left_win->v_offs = ori_win->v_offs;
                left_win->v_size = ori_win->v_size;

                right_win->v_offs = ori_win->v_offs;
                right_win->v_size = ori_win->v_size;

                u16 h_size_tmp1 = left_isp_rect_.w - ori_win->h_offs;
                u16 h_size_tmp2 = (right_isp_rect_.x - ori_win->h_offs) * 2;

                if (abs(ori_win->h_size - h_size_tmp1) < abs(ori_win->h_size - h_size_tmp2)) {
#ifdef DEBUG
                    printf("correct glb.h_size %d to %d\n", ori_win->h_size, h_size_tmp1);
#endif
                    *mode = LEFT_MODE;

                    ori_win->h_size = h_size_tmp1;

                    left_win->h_size = ori_win->h_size;
                    //actually stats of right isp would not be used
                    right_win->h_offs = 0;
                    right_win->h_size = ori_win->h_size;
                }
                else {
#ifdef DEBUG
                    printf("correct glb.h_size %d to %d\n", ori_win->h_size, h_size_tmp2);
#endif
                    *mode = LEFT_AND_RIGHT_MODE;

                    ori_win->h_size = h_size_tmp2;

                    u16 block_h = ori_win->h_size / (2 * wnd_num);
                    SplitAecCalcBlockSize(left_win, right_win, wnd_num, right_isp_rect_, &block_h);
                }
            }
            else {
                left_win->v_offs = ori_win->v_offs;
                left_win->v_size = ori_win->v_size;

                right_win->v_offs = ori_win->v_offs;
                right_win->v_size = ori_win->v_size;

                u16 h_size_tmp1 = ori_win->h_offs + ori_win->h_size - right_isp_rect_.x;
                u16 h_size_tmp2 = (ori_win->h_offs + ori_win->h_size - left_isp_rect_.w) * 2;

                if (abs(ori_win->h_size - h_size_tmp1) < abs(ori_win->h_size - h_size_tmp2)) {

#ifdef DEBUG
                    printf("correct glb.h_off %d to %d\n", ori_win->h_offs, right_isp_rect_.x);
                    printf("correct glb.h_size %d to %d\n", ori_win->h_size, h_size_tmp1);
#endif

                    *mode = RIGHT_MODE;

                    ori_win->h_size = h_size_tmp1;
                    ori_win->h_offs = right_isp_rect_.x;

                    right_win->h_offs = 0;
                    right_win->h_size = ori_win->h_size;

                    //actually stats of left isp would not be used
                    left_win->h_offs = 0;
                    left_win->h_size = ori_win->h_size;
                }
                else {
#ifdef DEBUG
                    printf("correct glb.h_off %d to %d\n", ori_win->h_offs,
                           ori_win->h_offs + ori_win->h_size - (ori_win->h_offs + ori_win->h_size - left_isp_rect_.w) * 2);
                    printf("correct glb.h_size %d to %d\n", ori_win->h_size, h_size_tmp2);
#endif
                    *mode = LEFT_AND_RIGHT_MODE;

                    ori_win->h_offs = ori_win->h_offs + ori_win->h_size - (ori_win->h_offs + ori_win->h_size - left_isp_rect_.w) * 2;
                    ori_win->h_size = h_size_tmp2;
                    left_win->h_offs = ori_win->h_offs;

                    u16 block_h = ori_win->h_size / (2 * wnd_num);
                    SplitAecCalcBlockSize(left_win, right_win, wnd_num, right_isp_rect_, &block_h);
                }
            }
        }
    }
}

/*********************************************/
/*      other module hwi splitter            */
/*********************************************/

void SplitAwbCalcBlockSize(
    struct isp2x_window* left_win,
    struct isp2x_window* right_win,
    u8 ds_awb,
    u8 wnd_num,
    IspParamsSplitter::Rectangle right_isp_rect_,
    u16* block_h
) {

    bool loop_en = true;
    int i = 0;

    while (loop_en && *block_h > 0) {

        left_win->h_size = (*block_h  * wnd_num) << ds_awb;
        
        right_win->h_offs = (left_win->h_size + left_win->h_offs > right_isp_rect_.x) ?
                            left_win->h_size + left_win->h_offs - right_isp_rect_.x : 0;
		
        if (u32(right_win->h_offs + left_win->h_size) > right_isp_rect_.w ) {	
            (*block_h)--;
        }
        else {
            loop_en = false;

            //if (*block_h % 2)
            //    (*block_h)--;

            left_win->h_size = (*block_h  * wnd_num) << ds_awb;
            right_win->h_offs = (left_win->h_size + left_win->h_offs > right_isp_rect_.x) ?
                                left_win->h_size + left_win->h_offs - right_isp_rect_.x : 0;
            right_win->h_offs = right_win->h_offs & 0xfffe;
            right_win->h_size =  (*block_h  * wnd_num) << ds_awb;
        }
    }
}

void SplitAwbWin(
    isp2x_window* ori_win,
    isp2x_window* left_win,
    isp2x_window* right_win,
    u8 ds_awb,
    u8 wnd_num,
    IspParamsSplitter::Rectangle left_isp_rect_,
    IspParamsSplitter::Rectangle right_isp_rect_,
    WinSplitMode* mode
) {

    u16 win_ds_hsize = ori_win->h_size >> ds_awb;
    u16 ori_win_hsize_clip = win_ds_hsize << ds_awb;

    //win only locate in left isp, actually stats of right isp would not be used
    if (ori_win->h_offs + ori_win_hsize_clip <= left_isp_rect_.w) {

#ifdef DEBUG
        printf("win locate in left isp\n");
#endif
        *mode = LEFT_MODE;

        left_win->h_offs = ori_win->h_offs;
        left_win->h_size = ori_win_hsize_clip;
        left_win->v_offs = ori_win->v_offs;
        left_win->v_size = ori_win->v_size;

        right_win->h_offs = 0;
        right_win->h_size = ori_win_hsize_clip;
        right_win->v_offs = ori_win->v_offs;
        right_win->v_size = ori_win->v_size;
    }
    else if (ori_win->h_offs >= right_isp_rect_.x) {

#ifdef DEBUG
        printf("win locate in right isp\n");
#endif
        *mode = RIGHT_MODE;

        //win only locate in right isp, actually stats of left isp would not be used
        left_win->h_offs = 0;
        left_win->h_size = ori_win->h_size;
        left_win->v_offs = ori_win->v_offs;
        left_win->v_size = ori_win->v_size;

        right_win->h_offs = ori_win->h_offs - right_isp_rect_.x;
        right_win->h_size = ori_win->h_size;
        right_win->v_offs = ori_win->v_offs;
        right_win->v_size = ori_win->v_size;

    }
    else {

        if ((ori_win->h_offs + ori_win->h_size / 2) <= left_isp_rect_.w
                && right_isp_rect_.x <= (ori_win->h_offs + ori_win->h_size / 2)) {
#ifdef DEBUG
            printf(" win locate at left&right isp,and center line locate in overlapping zone!\n");
#endif
            *mode = LEFT_AND_RIGHT_MODE;

            //win center locate at overlap zone
            left_win->h_offs = ori_win->h_offs;
            left_win->v_offs = ori_win->v_offs;
            left_win->v_size = ori_win->v_size;

            right_win->v_offs = ori_win->v_offs;
            right_win->v_size = ori_win->v_size;
            // u16 block_h = ori_win->h_size / (2 * wnd_num);

            u16 block_h = win_ds_hsize / (2 * wnd_num);

            left_win->h_size = (block_h  * wnd_num) << ds_awb;
        
            right_win->h_offs = (left_win->h_size + left_win->h_offs > right_isp_rect_.x) ?
                            left_win->h_size + left_win->h_offs - right_isp_rect_.x : 0;
            right_win->h_offs = right_win->h_offs & 0xfffe;
            right_win->h_size = (win_ds_hsize - block_h * wnd_num) << ds_awb ;
        }
        else {
#ifdef DEBUG
            printf(" win locate at left&right isp,but center line not locate in overlapping zone!\n");
#endif
            if ((ori_win->h_offs + ori_win->h_size / 2) < right_isp_rect_.x) {

                left_win->h_offs = ori_win->h_offs;
                left_win->v_offs = ori_win->v_offs;
                left_win->v_size = ori_win->v_size;

                right_win->v_offs = ori_win->v_offs;
                right_win->v_size = ori_win->v_size;

                u16 h_size_tmp1 = left_isp_rect_.w - ori_win->h_offs;
                u16 h_size_tmp2 = (right_isp_rect_.x - ori_win->h_offs) * 2;

                if (abs(ori_win_hsize_clip - h_size_tmp1) < abs(ori_win_hsize_clip - h_size_tmp2)) {
#ifdef DEBUG
                    printf("correct glb.h_size %d to %d\n", ori_win->h_size, h_size_tmp1);
#endif
                    *mode = LEFT_MODE;

                    ori_win->h_size = h_size_tmp1;

                    left_win->h_size = ori_win->h_size;
                    //actually stats of right isp would not be used
                    right_win->h_offs = 0;
                    right_win->h_size = ori_win->h_size;
                }
                else {
                    printf("correct glb.h_size %d to %d\n", ori_win->h_size, h_size_tmp2);
                    *mode = LEFT_AND_RIGHT_MODE;

                    ori_win->h_size = h_size_tmp2;
                    win_ds_hsize = ori_win->h_size >> ds_awb;

                    u16 block_h = win_ds_hsize / (2 * wnd_num);

                    SplitAwbCalcBlockSize(left_win, right_win, ds_awb, wnd_num, right_isp_rect_, &block_h);  
                }
            }
            else {
                left_win->v_offs = ori_win->v_offs;
                left_win->v_size = ori_win->v_size;

                right_win->v_offs = ori_win->v_offs;
                right_win->v_size = ori_win->v_size;

                u16 h_size_tmp1 = ori_win->h_offs + ori_win->h_size - right_isp_rect_.x;
                u16 h_size_tmp2 = (ori_win->h_offs + ori_win->h_size - left_isp_rect_.w) * 2;

                if (abs(ori_win_hsize_clip - h_size_tmp1) < abs(ori_win_hsize_clip - h_size_tmp2)) {

#ifdef DEBUG
                    printf("correct glb.h_off %d to %d\n", ori_win->h_offs, right_isp_rect_.x);
                    printf("correct glb.h_size %d to %d\n", ori_win->h_size, h_size_tmp1);
#endif

                    *mode = RIGHT_MODE;

                    ori_win->h_size = h_size_tmp1;
                    ori_win->h_offs = right_isp_rect_.x;

                    right_win->h_offs = 0;
                    right_win->h_size = ori_win->h_size;

                    //actually stats of left isp would not be used
                    left_win->h_offs = 0;
                    left_win->h_size = ori_win->h_size;
                }
                else {
#ifdef DEBUG
                    printf("correct glb.h_off %d to %d\n", ori_win->h_offs,
                           ori_win->h_offs + ori_win->h_size - (ori_win->h_offs + ori_win->h_size - left_isp_rect_.w) * 2);
                    printf("correct glb.h_size %d to %d\n", ori_win->h_size, h_size_tmp2);
#endif
                    *mode = LEFT_AND_RIGHT_MODE;

                    ori_win->h_offs = ori_win->h_offs + ori_win->h_size - (ori_win->h_offs + ori_win->h_size - left_isp_rect_.w) * 2;
                    ori_win->h_size = h_size_tmp2;
                    left_win->h_offs = ori_win->h_offs;

                    win_ds_hsize = ori_win->h_size >> ds_awb;

                    u16 block_h = win_ds_hsize / (2 * wnd_num);
					
                    SplitAwbCalcBlockSize(left_win, right_win, ds_awb, wnd_num, right_isp_rect_, &block_h);
                }
            }
        }
    }
}

void SplitAwbMultiWin(
    struct isp2x_window* ori_win,
    struct isp2x_window* left_win,
    struct isp2x_window* right_win,
    IspParamsSplitter::Rectangle left_isp_rect_,
    IspParamsSplitter::Rectangle right_isp_rect_,
    WinSplitMode* mode
) {
    if (ori_win->h_offs + ori_win->h_size <= left_isp_rect_.w) {
#ifdef DEBUG
        printf("win locate in left isp\n");
#endif
        *mode = LEFT_MODE;

        left_win->h_offs = ori_win->h_offs;
        left_win->h_size = ori_win->h_size;
        left_win->v_offs = ori_win->v_offs;
        left_win->v_size = ori_win->v_size;

        right_win->h_offs = 0;
        right_win->h_size = 0;
        right_win->v_offs = 0;
        right_win->v_size = 0;
    }
    else if (ori_win->h_offs >= right_isp_rect_.x) {
#ifdef DEBUG
        printf("win locate in right isp\n");
#endif
        *mode = RIGHT_MODE;

        //win only locate in right isp, actually stats of left isp would not be used
        left_win->h_offs = 0;
        left_win->h_size = 0;
        left_win->v_offs = 0;
        left_win->v_size = 0;

        right_win->h_offs = ori_win->h_offs - right_isp_rect_.x;
        right_win->h_size = ori_win->h_size;
        right_win->v_offs = ori_win->v_offs;
        right_win->v_size = ori_win->v_size;

    }
    else {
#ifdef DEBUG
        printf(" win locate at left&right isp\n");
#endif
        *mode = LEFT_AND_RIGHT_MODE;

        left_win->h_offs = ori_win->h_offs;
        left_win->h_size = MAX(0, left_isp_rect_.w - left_win->h_offs);
        left_win->v_offs = ori_win->v_offs;
        left_win->v_size = ori_win->v_size;


        right_win->h_offs = left_win->h_offs + left_win->h_size - right_isp_rect_.x;
        right_win->h_size = MAX(0, ori_win->h_size - left_win->h_size);
        right_win->v_offs = ori_win->v_offs;
        right_win->v_size = ori_win->v_size;
    }
}

};

template <>
XCamReturn IspParamsSplitter::SplitRawAeLiteParams<struct isp2x_rawaelite_meas_cfg>(
    struct isp2x_rawaelite_meas_cfg* ori, struct isp2x_rawaelite_meas_cfg* left,
    struct isp2x_rawaelite_meas_cfg* right) {

    u8 wnd_num = 0;
    if (ori->wnd_num == 0)
        wnd_num = 1;
    else
        wnd_num = 5;

    WinSplitMode mode = LEFT_AND_RIGHT_MODE;
    WinSplitMode sub_mode[4] = {LEFT_AND_RIGHT_MODE};

    SplitAecWin(&ori->win, &left->win, &right->win, wnd_num, left_isp_rect_, right_isp_rect_, &mode);

#ifdef DEBUG
    printf("AeLite left=%d-%d-%d-%d, right=%d-%d-%d-%d\n", left->win.h_offs, left->win.v_offs,
           left->win.h_size, left->win.v_size, right->win.h_offs, right->win.v_offs,
           right->win.h_size, right->win.v_size);
#endif

    return XCAM_RETURN_NO_ERROR;
}

template <>
XCamReturn IspParamsSplitter::SplitRawAeBigParams<struct isp2x_rawaebig_meas_cfg>(
    struct isp2x_rawaebig_meas_cfg* ori, struct isp2x_rawaebig_meas_cfg* left,
    struct isp2x_rawaebig_meas_cfg* right) {

    u8 wnd_num = 0;

    if (ori->wnd_num == 0)
        wnd_num = 1;
    else if (ori->wnd_num == 1)
        wnd_num = 5;
    else
        wnd_num = 15;

    WinSplitMode mode = LEFT_AND_RIGHT_MODE;
    WinSplitMode sub_mode[4] = {LEFT_AND_RIGHT_MODE};

    SplitAecWin(&ori->win, &left->win, &right->win, wnd_num, left_isp_rect_, right_isp_rect_, &mode);
    SplitAecSubWin(ori->subwin_en, ori->subwin, left->subwin, right->subwin, left_isp_rect_, right_isp_rect_, sub_mode);

    for (int i = 0; i < ISP2X_RAWAEBIG_SUBWIN_NUM; i++) {
        if (ori->subwin_en[i]) {
            switch (sub_mode[i]) {
            case LEFT_AND_RIGHT_MODE:
                left->subwin_en[i] = true;
                right->subwin_en[i] = true;
                break;
            case LEFT_MODE:
                left->subwin_en[i] = true;
                right->subwin_en[i] = false;
                break;
            case RIGHT_MODE:
                left->subwin_en[i] = false;
                right->subwin_en[i] = true;
                break;

            }
        }
    }

#ifdef DEBUG
    printf("AeBig left=%d-%d-%d-%d, right=%d-%d-%d-%d\n", left->win.h_offs, left->win.v_offs,
           left->win.h_size, left->win.v_size, right->win.h_offs, right->win.v_offs,
           right->win.h_size, right->win.v_size);
#endif

    return XCAM_RETURN_NO_ERROR;

}


template <>
XCamReturn IspParamsSplitter::SplitRawHistLiteParams<struct isp2x_rawhistlite_cfg>(
    struct isp2x_rawhistlite_cfg* ori, struct isp2x_rawhistlite_cfg* left,
    struct isp2x_rawhistlite_cfg* right) {

    u8 wnd_num = 0;
    wnd_num = 5;

    WinSplitMode mode = LEFT_AND_RIGHT_MODE;

    SplitAecWin(&ori->win, &left->win, &right->win, wnd_num, left_isp_rect_, right_isp_rect_, &mode);
    SplitAecWeight(ori->weight, left->weight, right->weight, mode, wnd_num);

#ifdef DEBUG
    printf("HistLite left=%d-%d-%d-%d, right=%d-%d-%d-%d\n", left->win.h_offs, left->win.v_offs,
           left->win.h_size, left->win.v_size, right->win.h_offs, right->win.v_offs,
           right->win.h_size, right->win.v_size);

    for (int i = 0; i < wnd_num; i++) {
        for (int j = 0; j < wnd_num; j++)
            printf("%d ", left->weight[i * wnd_num + j]);
        printf("\n");
    }
    for (int i = 0; i < wnd_num; i++) {
        for (int j = 0; j < wnd_num; j++)
            printf("%d ", right->weight[i * wnd_num + j]);
        printf("\n");
    }
#endif

    return XCAM_RETURN_NO_ERROR;

}

template <>
XCamReturn IspParamsSplitter::SplitRawHistBigParams<struct isp2x_rawhistbig_cfg>(
    struct isp2x_rawhistbig_cfg* ori, struct isp2x_rawhistbig_cfg* left,
    struct isp2x_rawhistbig_cfg* right) {

    u8 wnd_num = 0;

    if (ori->wnd_num <= 1)
        wnd_num = 5;
    else
        wnd_num = 15;


    WinSplitMode mode = LEFT_AND_RIGHT_MODE;

    SplitAecWin(&ori->win, &left->win, &right->win, wnd_num, left_isp_rect_, right_isp_rect_, &mode);
    SplitAecWeight(ori->weight, left->weight, right->weight, mode, wnd_num);

#ifdef DEBUG
    printf("HistBig left=%d-%d-%d-%d, right=%d-%d-%d-%d\n", left->win.h_offs, left->win.v_offs,
           left->win.h_size, left->win.v_size, right->win.h_offs, right->win.v_offs,
           right->win.h_size, right->win.v_size);

    for (int i = 0; i < wnd_num; i++) {
        for (int j = 0; j < wnd_num; j++)
            printf("%d ", left->weight[i * wnd_num + j]);
        printf("\n");
    }
    for (int i = 0; i < wnd_num; i++) {
        for (int j = 0; j < wnd_num; j++)
            printf("%d ", right->weight[i * wnd_num + j]);
        printf("\n");
    }

#endif

    return XCAM_RETURN_NO_ERROR;

}


template <>
XCamReturn IspParamsSplitter::SplitAecParams<struct isp3x_isp_params_cfg>(
    struct isp3x_isp_params_cfg* ori,
    struct isp3x_isp_params_cfg* left,
    struct isp3x_isp_params_cfg* right) {

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    //RAWAE

    ret = SplitRawAeLiteParams(&ori->meas.rawae0, &left->meas.rawae0, &right->meas.rawae0);
    ret = SplitRawAeBigParams(&ori->meas.rawae1, &left->meas.rawae1, &right->meas.rawae1);
    ret = SplitRawAeBigParams(&ori->meas.rawae2, &left->meas.rawae2, &right->meas.rawae2);
    ret = SplitRawAeBigParams(&ori->meas.rawae3, &left->meas.rawae3, &right->meas.rawae3);

    //RAWHIST

    ret = SplitRawHistLiteParams(&ori->meas.rawhist0, &left->meas.rawhist0, &right->meas.rawhist0);
    ret = SplitRawHistBigParams(&ori->meas.rawhist1, &left->meas.rawhist1, &right->meas.rawhist1);
    ret = SplitRawHistBigParams(&ori->meas.rawhist2, &left->meas.rawhist2, &right->meas.rawhist2);
    ret = SplitRawHistBigParams(&ori->meas.rawhist3, &left->meas.rawhist3, &right->meas.rawhist3);


    return XCAM_RETURN_NO_ERROR;
}

// split Awb param

template <>
XCamReturn IspParamsSplitter::SplitAwbParams<struct isp3x_isp_params_cfg>(
    struct isp3x_isp_params_cfg* ori,
    struct isp3x_isp_params_cfg* left,
    struct isp3x_isp_params_cfg* right) {

    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    isp2x_window ori_win;
    isp2x_window left_win;
    isp2x_window right_win;
    WinSplitMode mode = LEFT_AND_RIGHT_MODE;
    u8 wnd_num = 15;

    ori_win.h_offs = ori->meas.rawawb.sw_rawawb_h_offs;
    ori_win.h_size = ori->meas.rawawb.sw_rawawb_h_size;
    ori_win.v_offs = ori->meas.rawawb.sw_rawawb_v_offs;
    ori_win.v_size = ori->meas.rawawb.sw_rawawb_v_size;

    memcpy(&left_win, &ori_win, sizeof(ori_win));
    memcpy(&right_win, &ori_win, sizeof(ori_win));

    // Awb measure window
    u8 awb_ds;
    if (ori->meas.rawawb.sw_rawawb_wind_size == 0)
        awb_ds = 2;
    else
        awb_ds = 3;
	u16 min_hsize = wnd_num << awb_ds;
		
    SplitAwbWin(&ori_win, &left_win, &right_win, awb_ds, wnd_num, left_isp_rect_, right_isp_rect_, &mode);
    if (ori_win.h_size < min_hsize) {
        ori->meas.rawawb.sw_rawawb_blk_measure_enable = 0;
        left->meas.rawawb.sw_rawawb_blk_measure_enable = 0;
        right->meas.rawawb.sw_rawawb_blk_measure_enable = 0;
    }
    else {
        if (mode == LEFT_AND_RIGHT_MODE) {
            if (left_win.h_size < min_hsize) 
                left->meas.rawawb.sw_rawawb_blk_measure_enable = 0;
            if (right_win.h_size < min_hsize) 
                right->meas.rawawb.sw_rawawb_blk_measure_enable = 0;
        }
    }

    // Awb blk_wei_w
    //SplitAwbWeight(&ori_win, &left_win, &right_win, ori->meas.rawawb.sw_rawawb_wp_blk_wei_w, left->meas.rawawb.sw_rawawb_wp_blk_wei_w, right->meas.rawawb.sw_rawawb_wp_blk_wei_w, mode, wnd_num);
    SplitAecWeight(ori->meas.rawawb.sw_rawawb_wp_blk_wei_w, left->meas.rawawb.sw_rawawb_wp_blk_wei_w, right->meas.rawawb.sw_rawawb_wp_blk_wei_w, mode, wnd_num);
    
    left->meas.rawawb.sw_rawawb_h_offs = left_win.h_offs;
    left->meas.rawawb.sw_rawawb_h_size = left_win.h_size;
    left->meas.rawawb.sw_rawawb_v_offs = left_win.v_offs;
    left->meas.rawawb.sw_rawawb_v_size = left_win.v_size;

    right->meas.rawawb.sw_rawawb_h_offs = right_win.h_offs;
    right->meas.rawawb.sw_rawawb_h_size = right_win.h_size;
    right->meas.rawawb.sw_rawawb_v_offs = right_win.v_offs;
    right->meas.rawawb.sw_rawawb_v_size = right_win.v_size;

#ifdef DEBUG
printf("Awb measure window  left=%d-%d-%d-%d, right=%d-%d-%d-%d\n", left_win.h_offs, left_win.v_offs,
       left_win.h_size, left_win.v_size, right_win.h_offs, right_win.v_offs,
       right_win.h_size, right_win.v_size);

printf("Awb block weight: \n LEFT = { \n");

for (int i = 0; i < wnd_num; i++) {
       for (int j = 0; j < wnd_num; j++)
           printf("%d ", left->meas.rawawb.sw_rawawb_wp_blk_wei_w[i * wnd_num + j]);
       printf("\n");
   }
   printf("} \n RIGHT = { \n");

   for (int i = 0; i < wnd_num; i++) {
       for (int j = 0; j < wnd_num; j++)
           printf("%d ", right->meas.rawawb.sw_rawawb_wp_blk_wei_w[i * wnd_num + j]);
       printf("\n");
   }
   printf("}  \n");

#endif

    // Awb Multi Window
    isp2x_window sub_ori_win;
    isp2x_window sub_left_win;
    isp2x_window sub_right_win;
    if (ori->meas.rawawb.sw_rawawb_multiwindow_en) {
        // Awb Multi window 0
        sub_ori_win.h_offs = ori->meas.rawawb.sw_rawawb_multiwindow0_h_offs;
        sub_ori_win.h_size = ori->meas.rawawb.sw_rawawb_multiwindow0_h_size;
        sub_ori_win.v_offs = ori->meas.rawawb.sw_rawawb_multiwindow0_v_offs;
        sub_ori_win.v_size = ori->meas.rawawb.sw_rawawb_multiwindow0_v_size;

        memcpy(&sub_left_win, &sub_ori_win, sizeof(sub_ori_win));
        memcpy(&sub_right_win, &sub_ori_win, sizeof(sub_ori_win));

        SplitAwbMultiWin(&sub_ori_win, &sub_left_win, &sub_right_win, left_isp_rect_, right_isp_rect_, &mode);
        left->meas.rawawb.sw_rawawb_multiwindow0_h_offs = sub_left_win.h_offs;
        left->meas.rawawb.sw_rawawb_multiwindow0_h_size = sub_left_win.h_size;
        left->meas.rawawb.sw_rawawb_multiwindow0_v_offs = sub_left_win.v_offs;
        left->meas.rawawb.sw_rawawb_multiwindow0_v_size = sub_left_win.v_size;

        right->meas.rawawb.sw_rawawb_multiwindow0_h_offs = sub_right_win.h_offs;
        right->meas.rawawb.sw_rawawb_multiwindow0_h_size = sub_right_win.h_size;
        right->meas.rawawb.sw_rawawb_multiwindow0_v_offs = sub_right_win.v_offs;
        right->meas.rawawb.sw_rawawb_multiwindow0_v_size = sub_right_win.v_size;

#ifdef DEBUG
    printf("Awb Multi window 0 left=%d-%d-%d-%d, right=%d-%d-%d-%d\n", sub_left_win.h_offs, sub_left_win.v_offs,
           sub_left_win.h_size, sub_left_win.v_size, sub_right_win.h_offs, sub_right_win.v_offs,
           sub_right_win.h_size, sub_right_win.v_size);

#endif

       // Awb Multi window 1
        sub_ori_win.h_offs = ori->meas.rawawb.sw_rawawb_multiwindow1_h_offs;
        sub_ori_win.h_size = ori->meas.rawawb.sw_rawawb_multiwindow1_h_size;
        sub_ori_win.v_offs = ori->meas.rawawb.sw_rawawb_multiwindow1_v_offs;
        sub_ori_win.v_size = ori->meas.rawawb.sw_rawawb_multiwindow1_v_size;

        memcpy(&sub_left_win, &sub_ori_win, sizeof(sub_ori_win));
        memcpy(&sub_right_win, &sub_ori_win, sizeof(sub_ori_win));

        SplitAwbMultiWin(&sub_ori_win, &sub_left_win, &sub_right_win, left_isp_rect_, right_isp_rect_, &mode);
        left->meas.rawawb.sw_rawawb_multiwindow1_h_offs = sub_left_win.h_offs;
        left->meas.rawawb.sw_rawawb_multiwindow1_h_size = sub_left_win.h_size;
        left->meas.rawawb.sw_rawawb_multiwindow1_v_offs = sub_left_win.v_offs;
        left->meas.rawawb.sw_rawawb_multiwindow1_v_size = sub_left_win.v_size;

        right->meas.rawawb.sw_rawawb_multiwindow1_h_offs = sub_right_win.h_offs;
        right->meas.rawawb.sw_rawawb_multiwindow1_h_size = sub_right_win.h_size;
        right->meas.rawawb.sw_rawawb_multiwindow1_v_offs = sub_right_win.v_offs;
        right->meas.rawawb.sw_rawawb_multiwindow1_v_size = sub_right_win.v_size;

#ifdef DEBUG
        printf("Awb Multi window 1 left=%d-%d-%d-%d, right=%d-%d-%d-%d\n", sub_left_win.h_offs, sub_left_win.v_offs,
           sub_left_win.h_size, sub_left_win.v_size, sub_right_win.h_offs, sub_right_win.v_offs,
           sub_right_win.h_size, sub_right_win.v_size);

#endif

        // Awb Multi window 2
        sub_ori_win.h_offs = ori->meas.rawawb.sw_rawawb_multiwindow2_h_offs;
        sub_ori_win.h_size = ori->meas.rawawb.sw_rawawb_multiwindow2_h_size;
        sub_ori_win.v_offs = ori->meas.rawawb.sw_rawawb_multiwindow2_v_offs;
        sub_ori_win.v_size = ori->meas.rawawb.sw_rawawb_multiwindow2_v_size;

        memcpy(&sub_left_win, &sub_ori_win, sizeof(sub_ori_win));
        memcpy(&sub_right_win, &sub_ori_win, sizeof(sub_ori_win));

        SplitAwbMultiWin(&sub_ori_win, &sub_left_win, &sub_right_win, left_isp_rect_, right_isp_rect_, &mode);
        left->meas.rawawb.sw_rawawb_multiwindow2_h_offs = sub_left_win.h_offs;
        left->meas.rawawb.sw_rawawb_multiwindow2_h_size = sub_left_win.h_size;
        left->meas.rawawb.sw_rawawb_multiwindow2_v_offs = sub_left_win.v_offs;
        left->meas.rawawb.sw_rawawb_multiwindow2_v_size = sub_left_win.v_size;

        right->meas.rawawb.sw_rawawb_multiwindow2_h_offs = sub_right_win.h_offs;
        right->meas.rawawb.sw_rawawb_multiwindow2_h_size = sub_right_win.h_size;
        right->meas.rawawb.sw_rawawb_multiwindow2_v_offs = sub_right_win.v_offs;
        right->meas.rawawb.sw_rawawb_multiwindow2_v_size = sub_right_win.v_size;

#ifdef DEBUG
        printf("Awb Multi window 2 left=%d-%d-%d-%d, right=%d-%d-%d-%d\n", sub_left_win.h_offs, sub_left_win.v_offs,
           sub_left_win.h_size, sub_left_win.v_size, sub_right_win.h_offs, sub_right_win.v_offs,
           sub_right_win.h_size, sub_right_win.v_size);

#endif

        // Awb Multi window 3
        sub_ori_win.h_offs = ori->meas.rawawb.sw_rawawb_multiwindow3_h_offs;
        sub_ori_win.h_size = ori->meas.rawawb.sw_rawawb_multiwindow3_h_size;
        sub_ori_win.v_offs = ori->meas.rawawb.sw_rawawb_multiwindow3_v_offs;
        sub_ori_win.v_size = ori->meas.rawawb.sw_rawawb_multiwindow3_v_size;

        memcpy(&sub_left_win, &sub_ori_win, sizeof(sub_ori_win));
        memcpy(&sub_right_win, &sub_ori_win, sizeof(sub_ori_win));

        SplitAwbMultiWin(&sub_ori_win, &sub_left_win, &sub_right_win, left_isp_rect_, right_isp_rect_, &mode);
        left->meas.rawawb.sw_rawawb_multiwindow3_h_offs = sub_left_win.h_offs;
        left->meas.rawawb.sw_rawawb_multiwindow3_h_size = sub_left_win.h_size;
        left->meas.rawawb.sw_rawawb_multiwindow3_v_offs = sub_left_win.v_offs;
        left->meas.rawawb.sw_rawawb_multiwindow3_v_size = sub_left_win.v_size;

        right->meas.rawawb.sw_rawawb_multiwindow3_h_offs = sub_right_win.h_offs;
        right->meas.rawawb.sw_rawawb_multiwindow3_h_size = sub_right_win.h_size;
        right->meas.rawawb.sw_rawawb_multiwindow3_v_offs = sub_right_win.v_offs;
        right->meas.rawawb.sw_rawawb_multiwindow3_v_size = sub_right_win.v_size;

#ifdef DEBUG
        printf("Awb Multi window 3 left=%d-%d-%d-%d, right=%d-%d-%d-%d\n", sub_left_win.h_offs, sub_left_win.v_offs,
           sub_left_win.h_size, sub_left_win.v_size, sub_right_win.h_offs, sub_right_win.v_offs,
           sub_right_win.h_size, sub_right_win.v_size);
#endif
    }

    return ret;

}

template <>
XCamReturn IspParamsSplitter::SplitAfParams<struct isp3x_isp_params_cfg>(
    struct isp3x_isp_params_cfg* ori,
    struct isp3x_isp_params_cfg* left,
    struct isp3x_isp_params_cfg* right) {
    struct isp3x_rawaf_meas_cfg org_af = left->meas.rawaf;
    struct isp3x_rawaf_meas_cfg* l_af = &left->meas.rawaf;
    struct isp3x_rawaf_meas_cfg* r_af = &right->meas.rawaf;
    struct isp2x_rawaebig_meas_cfg org_ae3 = left->meas.rawae3;
    struct isp2x_rawaebig_meas_cfg* l_ae3 = &left->meas.rawae3;
    struct isp2x_rawaebig_meas_cfg* r_ae3 = &right->meas.rawae3;
    int32_t l_isp_st, l_isp_ed, r_isp_st, r_isp_ed;
    int32_t l_win_st, l_win_ed, r_win_st, r_win_ed;
    int32_t x_st, x_ed, l_blknum, r_blknum, ov_w, blk_w, r_skip_blknum;

    ov_w = left_isp_rect_.w + left_isp_rect_.x - right_isp_rect_.x;
    x_st = org_af.win[0].h_offs;
    x_ed = x_st + org_af.win[0].h_size;
    l_isp_st = left_isp_rect_.x;
    l_isp_ed = left_isp_rect_.x + left_isp_rect_.w;
    r_isp_st = right_isp_rect_.x;
    r_isp_ed = right_isp_rect_.x + right_isp_rect_.w;
    LOGD_AF("wina.x_st %d, wina.x_ed %d, l_isp_st %d, l_isp_ed %d, r_isp_st %d, r_isp_ed %d",
        x_st, x_ed, l_isp_st, l_isp_ed, r_isp_st, r_isp_ed);

    //// winA ////
    // af win in both side
    if ((x_st < r_isp_st) && (x_ed > l_isp_ed)) {
        // af win < one isp width
        if (org_af.win[0].h_size < left_isp_rect_.w) {
            blk_w = org_af.win[0].h_size / ISP2X_RAWAF_SUMDATA_ROW;
            l_blknum = (l_isp_ed - x_st + blk_w - 1) / blk_w;
            r_blknum = ISP2X_RAWAF_SUMDATA_ROW - l_blknum;
            l_win_ed = l_isp_ed - 2;
            l_win_st = l_win_ed - blk_w * ISP2X_RAWAF_SUMDATA_ROW;
            if (blk_w < ov_w) {
                r_skip_blknum = ov_w / blk_w;
                r_win_st = ov_w - r_skip_blknum * blk_w;
                r_win_ed = ov_w + (ISP2X_RAWAF_SUMDATA_ROW - r_skip_blknum) * blk_w;
            }
            else {
                r_skip_blknum = 0;
                r_win_st = 2;
                r_win_ed = r_win_st + ISP2X_RAWAF_SUMDATA_ROW * blk_w;
            }
        }
        // af win >= one isp width
        else {
            l_win_st = x_st;
            l_win_ed = l_isp_ed - 2;
            blk_w = (l_win_ed - l_win_st) / (ISP2X_RAWAF_SUMDATA_ROW + 1);
            l_win_st = l_win_ed - blk_w * ISP2X_RAWAF_SUMDATA_ROW;
            l_blknum = ((l_win_ed - l_win_st) * ISP2X_RAWAF_SUMDATA_ROW + org_af.win[0].h_size - 1) / org_af.win[0].h_size;
            r_blknum = ISP2X_RAWAF_SUMDATA_ROW - l_blknum;
            if (blk_w < ov_w) {
                r_skip_blknum = ov_w / blk_w;
                r_win_st = ov_w - r_skip_blknum * blk_w;
                r_win_ed = ov_w + (ISP2X_RAWAF_SUMDATA_ROW - r_skip_blknum) * blk_w;
            }
            else {
                r_skip_blknum = 0;
                r_win_st = 2;
                r_win_ed = r_win_st + ISP2X_RAWAF_SUMDATA_ROW * blk_w;
            }
        }
        LOGD_AF("wina: blk_w %d, ov_w %d, l_blknum %d, r_blknum %d, r_skip_blknum %d",
            blk_w, ov_w, l_blknum, r_blknum, r_skip_blknum);
    }
    // af win in right side
    else if ((x_st >= r_isp_st) && (x_ed > l_isp_ed)) {
        l_blknum = 0;
        r_blknum = ISP2X_RAWAF_SUMDATA_ROW;
        r_win_st = x_st - right_isp_rect_.x;
        r_win_ed = x_ed - right_isp_rect_.x;
        l_win_st = r_win_st;
        l_win_ed = r_win_ed;
    }
    // af win in left side
    else {
        l_blknum = ISP2X_RAWAF_SUMDATA_ROW;
        r_blknum = 0;
        l_win_st = x_st;
        l_win_ed = x_ed;
        r_win_st = l_win_st;
        r_win_ed = l_win_ed;
    }

    l_af->win[0].h_offs = l_win_st;
    l_af->win[0].h_size = l_win_ed - l_win_st;
    r_af->win[0].h_offs = r_win_st;
    r_af->win[0].h_size = r_win_ed - r_win_st;

    //// winB ////
    x_st = org_af.win[1].h_offs;
    x_ed = x_st + org_af.win[1].h_size;
    LOGD_AF("winb.x_st %d, winb.x_ed %d, l_isp_st %d, l_isp_ed %d, r_isp_st %d, r_isp_ed %d",
        x_st, x_ed, l_isp_st, l_isp_ed, r_isp_st, r_isp_ed);

    // af win in both side
    if ((x_st < r_isp_st) && (x_ed > l_isp_ed)) {
        l_win_st = x_st;
        l_win_ed = l_isp_ed - 2;
        r_win_st = ov_w - 2;
        r_win_ed = x_ed - right_isp_rect_.x;
    }
    // af win in right side
    else if ((x_st >= r_isp_st) && (x_ed > l_isp_ed)) {
        r_win_st = x_st - right_isp_rect_.x;
        r_win_ed = x_ed - right_isp_rect_.x;
        l_win_st = r_win_st;
        l_win_ed = r_win_ed;
    }
    // af win in left side
    else {
        l_win_st = x_st;
        l_win_ed = x_ed;
        r_win_st = l_win_st;
        r_win_ed = l_win_ed;
    }

    l_af->win[1].h_offs = l_win_st;
    l_af->win[1].h_size = l_win_ed - l_win_st;
    r_af->win[1].h_offs = r_win_st;
    r_af->win[1].h_size = r_win_ed - r_win_st;

    // rawae3 is used by af now!!!
    if (org_af.ae_mode) {
        l_ae3->win.h_offs = l_af->win[0].h_offs;
        l_ae3->win.v_offs = l_af->win[0].v_offs;
        l_ae3->win.h_size = l_af->win[0].h_size;
        l_ae3->win.v_size = l_af->win[0].v_size;
        r_ae3->win.h_offs = r_af->win[0].h_offs;
        r_ae3->win.v_offs = r_af->win[0].v_offs;
        r_ae3->win.h_size = r_af->win[0].h_size;
        r_ae3->win.v_size = r_af->win[0].v_size;
    }

    LOGD_AF("AfWinA left=%d-%d-%d-%d, right=%d-%d-%d-%d",
        l_af->win[0].h_offs, l_af->win[0].v_offs,
        l_af->win[0].h_size, l_af->win[0].v_size,
        r_af->win[0].h_offs, r_af->win[0].v_offs,
        r_af->win[0].h_size, r_af->win[0].v_size);

    LOGD_AF("AfWinB left=%d-%d-%d-%d, right=%d-%d-%d-%d",
        l_af->win[1].h_offs, l_af->win[1].v_offs,
        l_af->win[1].h_size, l_af->win[1].v_size,
        r_af->win[1].h_offs, r_af->win[1].v_offs,
        r_af->win[1].h_size, r_af->win[1].v_size);

    return XCAM_RETURN_NO_ERROR;
}

IspParamsSplitter& IspParamsSplitter::SetPicInfo(IspParamsSplitter::Rectangle&& pic_rect) {
    pic_rect_ = std::move(pic_rect);
    return *this;
}

IspParamsSplitter& IspParamsSplitter::SetPicInfo(IspParamsSplitter::Rectangle& pic_rect) {
    pic_rect_ = pic_rect;
    return *this;
}

IspParamsSplitter& IspParamsSplitter::SetLeftIspRect(IspParamsSplitter::Rectangle&& left_isp_rect) {
    left_isp_rect_ = std::move(left_isp_rect);
    return *this;
}

IspParamsSplitter& IspParamsSplitter::SetLeftIspRect(IspParamsSplitter::Rectangle& left_isp_rect) {
    left_isp_rect_ = left_isp_rect;
    return *this;
}

IspParamsSplitter& IspParamsSplitter::SetRightIspRect(
    IspParamsSplitter::Rectangle&& right_isp_rect) {
    right_isp_rect_ = std::move(right_isp_rect);
    return *this;
}

IspParamsSplitter& IspParamsSplitter::SetRightIspRect(
    IspParamsSplitter::Rectangle& right_isp_rect) {
    right_isp_rect_ = right_isp_rect;
    return *this;
}

const IspParamsSplitter::Rectangle& IspParamsSplitter::GetPicInfo() const {
    return pic_rect_;
}

const IspParamsSplitter::Rectangle& IspParamsSplitter::GetLeftIspRect() const {
    return left_isp_rect_;
}

const IspParamsSplitter::Rectangle& IspParamsSplitter::GetRightIspRect() const {
    return right_isp_rect_;
}

template <>
XCamReturn IspParamsSplitter::SplitIspParams<struct isp3x_isp_params_cfg>(
    struct isp3x_isp_params_cfg* orig_isp_params,
    struct isp3x_isp_params_cfg* isp_params) {
    XCamReturn ret = XCAM_RETURN_NO_ERROR;

    struct isp3x_isp_params_cfg* left_isp_params  = isp_params;
    struct isp3x_isp_params_cfg* right_isp_params = isp_params + 1;

    // Modules that use the same params for both left and right isp
    // will not need to implent split function
    memcpy(right_isp_params, left_isp_params, sizeof(struct isp3x_isp_params_cfg));

    ret = SplitAecParams(orig_isp_params, left_isp_params, right_isp_params);
    // Should return failure ?
    ret = SplitAwbParams(orig_isp_params, left_isp_params, right_isp_params);
    ret = SplitAfParams(orig_isp_params, left_isp_params, right_isp_params);

    LOGD_CAMHW("Split ISP Params: left %p right %p size %d",
               left_isp_params,
               right_isp_params,
               sizeof(*left_isp_params));

    return ret;
}
