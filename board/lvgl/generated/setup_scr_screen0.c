/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

/* 用于旋转图片的动画回调 */
static void rotate_img_cb(void *obj, int32_t angle)
{
    lv_img_set_angle((lv_obj_t *)obj, angle);
}

void setup_scr_screen0(lv_ui *ui)
{
    //Write codes screen0
    ui->screen0 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen0, 480, 360);
    lv_obj_set_scrollbar_mode(ui->screen0, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen0, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen0_cont1
    ui->screen0_cont1 = lv_obj_create(ui->screen0);
    lv_obj_set_pos(ui->screen0_cont1, 0, 0);
    lv_obj_set_size(ui->screen0_cont1, 480, 360);
    lv_obj_set_scrollbar_mode(ui->screen0_cont1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen0_cont1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen0_cont1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen0_cont1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen0_cont1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen0_cont1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen0_cont1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen0_cont1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen0_cont1, lv_color_hex(0xfbfbfb), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen0_cont1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen0_cont1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen0_cont1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen0_cont1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen0_cont1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen0_cont1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen0_img1
    ui->screen0_img1 = lv_img_create(ui->screen0_cont1);
    lv_obj_add_flag(ui->screen0_img1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen0_img1, &_logo_alpha_132x26);
    lv_img_set_pivot(ui->screen0_img1, 50,50);
    lv_img_set_angle(ui->screen0_img1, 0);
    lv_obj_set_pos(ui->screen0_img1, 1, 3);
    lv_obj_set_size(ui->screen0_img1, 132, 26);

    //Write style for screen0_img1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen0_img1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen0_img1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen0_img1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen0_img1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen0_img2
    ui->screen0_img2 = lv_img_create(ui->screen0_cont1);
    lv_obj_add_flag(ui->screen0_img2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen0_img2, &_camera_alpha_130x124);
    lv_img_set_pivot(ui->screen0_img2, 50,50);
    lv_img_set_angle(ui->screen0_img2, 0);
    lv_obj_set_pos(ui->screen0_img2, 175, 98);
    lv_obj_set_size(ui->screen0_img2, 130, 124);
	
    //Write style for screen0_img2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen0_img2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen0_img2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen0_img2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen0_img2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen0.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen0);

    //Init events for screen.
    events_init_screen0(ui);
	
	
	    // 添加 img2 旋转动画
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, ui->screen0_img2);                      // 设置动画目标为 img2
    lv_anim_set_exec_cb(&a, rotate_img_cb);                    // 绑定执行回调
    lv_anim_set_time(&a, 2000);                                // 每圈用时：2000 毫秒
    lv_anim_set_values(&a, 0, 3600);                            // 旋转 0.1°单位的 0 ~ 360° (即3600)
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);     // 无限循环
    lv_anim_start(&a);                                         // 启动动画

}


