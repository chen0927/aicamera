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
#include "app_camera.h"
//extern uint16_t canvas_buf[];
extern framebuffer_t *framebuffer;  
void setup_scr_screen1(lv_ui *ui)
{
    //Write codes screen1
    ui->screen1 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen1, 480, 360);
    lv_obj_set_scrollbar_mode(ui->screen1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen1_cont
    ui->screen1_cont = lv_obj_create(ui->screen1);
    lv_obj_set_pos(ui->screen1_cont, 0, 0);
    lv_obj_set_size(ui->screen1_cont, 480, 360);
    lv_obj_set_scrollbar_mode(ui->screen1_cont, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen1_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen1_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen1_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen1_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen1_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen1_btn1
    ui->screen1_btn1 = lv_btn_create(ui->screen1_cont);
    ui->screen1_btn1_label = lv_label_create(ui->screen1_btn1);
    lv_label_set_text(ui->screen1_btn1_label, "拍照");
    lv_label_set_long_mode(ui->screen1_btn1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen1_btn1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen1_btn1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen1_btn1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen1_btn1, 13, 311);
    lv_obj_set_size(ui->screen1_btn1, 79, 33);

    //Write style for screen1_btn1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen1_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen1_btn1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen1_btn1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen1_btn1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen1_btn1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen1_btn1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen1_btn1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen1_btn1, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen1_btn1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen1_btn1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen1_btn2
    ui->screen1_btn2 = lv_btn_create(ui->screen1_cont);
    ui->screen1_btn2_label = lv_label_create(ui->screen1_btn2);
    lv_label_set_text(ui->screen1_btn2_label, "识别");
    lv_label_set_long_mode(ui->screen1_btn2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen1_btn2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen1_btn2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen1_btn2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen1_btn2, 134, 310);
    lv_obj_set_size(ui->screen1_btn2, 79, 33);

    //Write style for screen1_btn2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen1_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen1_btn2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen1_btn2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen1_btn2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen1_btn2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen1_btn2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen1_btn2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen1_btn2, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen1_btn2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen1_btn2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen1_btn4
    ui->screen1_btn4 = lv_btn_create(ui->screen1_cont);
    ui->screen1_btn4_label = lv_label_create(ui->screen1_btn4);
    lv_label_set_text(ui->screen1_btn4_label, "恢复");
    lv_label_set_long_mode(ui->screen1_btn4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen1_btn4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen1_btn4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen1_btn4_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen1_btn4, 377, 310);
    lv_obj_set_size(ui->screen1_btn4, 79, 33);

    //Write style for screen1_btn4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen1_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen1_btn4, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen1_btn4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen1_btn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen1_btn4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen1_btn4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen1_btn4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen1_btn4, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen1_btn4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen1_btn4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen1_btn3
    ui->screen1_btn3 = lv_btn_create(ui->screen1_cont);
    ui->screen1_btn3_label = lv_label_create(ui->screen1_btn3);
    lv_label_set_text(ui->screen1_btn3_label, "保存");
    lv_label_set_long_mode(ui->screen1_btn3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen1_btn3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen1_btn3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen1_btn3_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen1_btn3, 257, 311);
    lv_obj_set_size(ui->screen1_btn3, 79, 33);

    //Write style for screen1_btn3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen1_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen1_btn3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen1_btn3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen1_btn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen1_btn3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen1_btn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen1_btn3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen1_btn3, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen1_btn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen1_btn3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen1_btn5
    ui->screen1_btn5 = lv_btn_create(ui->screen1_cont);
    ui->screen1_btn5_label = lv_label_create(ui->screen1_btn5);
    lv_label_set_text(ui->screen1_btn5_label, "上一页");
    lv_label_set_long_mode(ui->screen1_btn5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen1_btn5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen1_btn5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen1_btn5_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen1_btn5, 396, 3);
    lv_obj_set_size(ui->screen1_btn5, 79, 33);

    //Write style for screen1_btn5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen1_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen1_btn5, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen1_btn5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen1_btn5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen1_btn5, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen1_btn5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen1_btn5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen1_btn5, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen1_btn5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen1_btn5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



  
    ui->screen1_canvas = lv_canvas_create(ui->screen1);
    lv_canvas_set_buffer(ui->screen1_canvas,
                         framebuffer->data+32,               
                         CAM_W,
                         CAM_H,
                         LV_IMG_CF_TRUE_COLOR);         
    lv_obj_set_pos(ui->screen1_canvas, 51, 40);
    lv_obj_set_size(ui->screen1_canvas, CAM_W, CAM_H);
    lv_obj_set_scrollbar_mode(ui->screen1_canvas, LV_SCROLLBAR_MODE_OFF);
	

    //Update current screen layout.
    lv_obj_update_layout(ui->screen1);

    //Init events for screen.
    events_init_screen1(ui);
	
	
	
	

}
