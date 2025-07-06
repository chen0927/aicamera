#ifndef __APP_CAMERA_H__
#define __APP_CAMERA_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <sensor.h>
#include <framebuffer.h>
#include <fb_alloc.h>
#include <imlib.h>
#include <drv_lcd.h>
#include "gui_guider.h"
#include "ra/board/ra8d1_ek/board_sdram.h"  

#define CAM_W        		320
#define CAM_H        		240
#define FRAME_SIZE   		(CAM_W *CAM_H *2)

#define CAM_THREAD_STACK 	4096
#define CAM_THREAD_PRIORITY 15
#define CAM_THREAD_SLICE    10

extern volatile bool preview_flag;//预览标志位
extern volatile bool detect_flag;//识别标志位
extern struct rt_mutex lvgl_mutex; 




int app_camera_init(void);


#endif



 