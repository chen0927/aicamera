/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-12-10     Rbb666        first version
 */
//#include <rtthread.h>
//#include <rtdevice.h>
#define DRV_DEBUG
#define LOG_TAG             "main"
#include <drv_log.h>
#include "app_ui.h"
#include "app_camera.h"
#include "app_openmv.h"
#include "app_autowifi.h"
#include "app_sd.h"
#include "zFTP.h"

void hal_entry(void)
{
	LOG_I("===================================");
    LOG_I("This is OpenMV4.1.0 demo");
    LOG_I("===================================");
	ui_init();
	sd_init();
	app_openmv_init();
	rt_thread_mdelay(500);
	app_camera_init();
	wifi_auto_connect_init();
	auto_upload_start();
}
