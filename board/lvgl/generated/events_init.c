/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "app_camera.h"
#include "app_sd.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void screen0_img2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen1, guider_ui.screen1_del, &guider_ui.screen0_del, setup_scr_screen1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen0 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen0_img2, screen0_img2_event_handler, LV_EVENT_ALL, ui);
}
//ÅÄÕÕ°´Å¥
static void screen1_btn1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		rt_mutex_take(&lvgl_mutex,RT_WAITING_FOREVER);
		preview_flag = false;
		rt_mutex_release(&lvgl_mutex);
		rt_kprintf("[UI] Camera state set to FROZEN\n");
        break;
    }
    default:
        break;
    }
}

static void screen1_btn2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen2, guider_ui.screen2_del, &guider_ui.screen1_del, setup_scr_screen2, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}
//»Ö¸´°´Å¥
static void screen1_btn4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		rt_mutex_take(&lvgl_mutex,RT_WAITING_FOREVER);
		preview_flag = true;
		rt_mutex_release(&lvgl_mutex);
        rt_kprintf("[UI] Camera state set to PREVIEWING\n");
        break;
    }
    default:
        break;
    }
}
//±£´æ°´Å¥
static void screen1_btn3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
		rt_mutex_take(&lvgl_mutex,RT_WAITING_FOREVER);
		save_flag = true;
		rt_mutex_release(&lvgl_mutex);
        break;
    }
    default:
        break;
    }
}

static void screen1_btn5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen0, guider_ui.screen0_del, &guider_ui.screen1_del, setup_scr_screen0, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen1_btn1, screen1_btn1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen1_btn2, screen1_btn2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen1_btn4, screen1_btn4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen1_btn3, screen1_btn3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen1_btn5, screen1_btn5_event_handler, LV_EVENT_ALL, ui);
}

static void screen2_label1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen2, guider_ui.screen2_del, &guider_ui.screen2_del, setup_scr_screen2, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen2_btn1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen1, guider_ui.screen1_del, &guider_ui.screen2_del, setup_scr_screen1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen2 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen2_label1, screen2_label1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen2_btn1, screen2_btn1_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{
//	events_init_screen0(ui);
//	events_init_screen1(ui);
//	events_init_screen2(ui);
}
