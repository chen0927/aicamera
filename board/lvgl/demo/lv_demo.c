/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-17     Meco Man      First version
 * 2022-05-10     Meco Man      improve rt-thread initialization process
 */

#include "rtconfig.h"
#include "lv_demos.h"
#include <string.h>
#include "gui_guider.h"
#include "events_init.h"

lv_ui guider_ui;
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/


/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
volatile bool lvgl_ready = RT_FALSE;  // 全局变量

void lv_user_gui_init(void)
{
    /* display demo; you may replace with your LVGL application at here */
	setup_ui(&guider_ui);
	events_init(&guider_ui);
	
	lvgl_ready = RT_TRUE;    // 标记 LVGL 界面已初始化完成

}
