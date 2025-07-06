#include "app_camera.h"


volatile bool preview_flag = true;//预览标志位
volatile bool detect_flag = false;//识别标志位

extern framebuffer_t *framebuffer;  
extern lv_ui guider_ui;
extern volatile bool lvgl_ready;
struct rt_mutex lvgl_mutex;


static void camera_thread_entry(void *parameter)
{
	
	while(!lvgl_ready)
	{
		rt_thread_mdelay(10);
	}
	
	#ifdef __DCACHE_PRESENT
		SCB_CleanDCache();
	#endif
	
	fb_alloc_init0();
	framebuffer_init0();
	imlib_init_all();
	
	sensor_init0();
	
	if(sensor_init()!=0)
	{
		rt_kprintf("[Camera]Sensor init failed!\n");
		return;
	}
	
	sensor_reset();
	sensor_set_pixformat(PIXFORMAT_RGB565);
	sensor_set_framesize(FRAMESIZE_QVGA);
	sensor_set_vflip(1);
	sensor_set_hmirror(1);
	
	
	rt_kprintf("[Camera] Initialization complete, start preview...\n");
	
	while(1)
	{
		if(preview_flag)
		{
			sensor_snapshot(&sensor, (uint8_t *)framebuffer->data, 0);		
			 #if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1)
				 SCB_InvalidateDCache_by_Addr((uint32_t *)framebuffer->data, FRAME_SIZE);
			 #endif
			  rt_mutex_take(&lvgl_mutex, RT_WAITING_FOREVER);
			  if (lv_obj_is_valid(guider_ui.screen1_canvas))
				  lv_obj_invalidate(guider_ui.screen1_canvas);
              rt_mutex_release(&lvgl_mutex);
			  
		}
		 rt_thread_mdelay(33);
	}
	
}

int app_camera_init(void)
{
	rt_mutex_init(&lvgl_mutex, "lvgl_mtx", RT_IPC_FLAG_FIFO);


    rt_thread_t tid;

    tid = rt_thread_create("camera",
                           camera_thread_entry,
                           RT_NULL,
                           CAM_THREAD_STACK,
                           CAM_THREAD_PRIORITY,
                           CAM_THREAD_SLICE);

    if (tid == RT_NULL)
    {
        rt_kprintf("[Camera] thread create failed!\n");
        return -RT_ERROR;
    }

    rt_thread_startup(tid);
    rt_kprintf("[Camera] thread startup OK.\n");
    return RT_EOK;
}





