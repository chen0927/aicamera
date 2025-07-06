#include <lvgl.h>
#include <rtdevice.h>
#include "cst812t.h"
#define DBG_TAG "lv_port_indev"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include "hal_data.h"
#include <stdlib.h>   
#define DOUBLE_CLICK_INTERVAL_MS  350 

static rt_device_t touch_dev = RT_NULL;/*触摸设备句柄*/
static struct rt_touch_data read_data;/*保存每次读取的触摸点数据*/


/* 用于模拟触摸板模式下的鼠标指针全局位置以及上次触摸坐标*/
static int cursor_x = LV_HOR_RES_MAX /2;
static int cursor_y = LV_VER_RES_MAX /2;
static int16_t last_touch_x = 0;
static int16_t last_touch_y = 0;
static bool touch_active = false; /* 上一次是否触摸 */

lv_indev_t *indev_touchpad;
/* 触摸设备探测*/
static rt_err_t touch_probe()
{
    touch_dev = rt_device_find("cst8xx");
    if (touch_dev == RT_NULL)
    {
        LOG_E("can't find device cst8xx");
        return -RT_ERROR;
    }
	else
	{
		rt_kprintf("[OK] device found, ref_count=%d\n", touch_dev->ref_count);
	}
	if (touch_dev->open == RT_NULL)
	{
		rt_kprintf("[WARN] open callback is NULL!\n");
	}

    if (rt_device_open(touch_dev, RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        LOG_E("open device failed!");
        return -RT_ERROR;
    }
    return RT_EOK;
}
/* 读取触摸坐标函数*/
//static void touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
//{
//    if (rt_device_read(touch_dev, 0, &read_data, 1) == 1)
//    {
//        data->point.x  = read_data.x_coordinate;
//        data->point.y  = read_data.y_coordinate;
//        switch (read_data.event)
//        {
//        case TOUCH_EVENT_UP:
//            data->state = LV_INDEV_STATE_REL;
//            break;
//        case TOUCH_EVENT_DOWN:
//            data->state = LV_INDEV_STATE_PR;
//            break;
//        case TOUCH_EVENT_MOVE:
//            data->state = LV_INDEV_STATE_PR;
//            break;
//        default:
//            break;
//        }
//    }
//}
static void touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    static rt_tick_t last_click_tick = 0;
    static bool waiting_for_second_click = false;
    static bool finger_down = false;
    static int16_t last_touch_x = 0, last_touch_y = 0;

    if (rt_device_read(touch_dev, 0, &read_data, 1) != 1)
    {
        LOG_W("touch read fail");
        data->state = LV_INDEV_STATE_REL;
        return;
    }

    bool currently_pressed = (read_data.event == TOUCH_EVENT_DOWN || read_data.event == TOUCH_EVENT_MOVE);

    if (currently_pressed)
    {
        if (!finger_down && read_data.event == TOUCH_EVENT_DOWN)
        {
            rt_tick_t now = rt_tick_get();

            if (waiting_for_second_click && (now - last_click_tick <= rt_tick_from_millisecond(DOUBLE_CLICK_INTERVAL_MS)))
            {
                /* 这是一次有效双击事件 */
                data->state = LV_INDEV_STATE_PR;
                waiting_for_second_click = false; // 重置双击等待
            }
            else
            {
                /* 第一次点击: 等待第二次点击确认 */
                data->state = LV_INDEV_STATE_REL;
                waiting_for_second_click = true;
                last_click_tick = now;
            }

            /* 记录初始坐标 (不移动光标，避免跳跃) */
            last_touch_x = read_data.x_coordinate;
            last_touch_y = read_data.y_coordinate;

            finger_down = true;
        }
        else if (finger_down)
        {
            /* 计算相对位移更新光标位置 (鼠标移动效果) */
            int dx = read_data.x_coordinate - last_touch_x;
            int dy = read_data.y_coordinate - last_touch_y;

            cursor_x += dx;
            cursor_y += dy;

            /* 边界限制 */
            cursor_x = cursor_x < 0 ? 0 : (cursor_x >= LV_HOR_RES_MAX ? LV_HOR_RES_MAX - 1 : cursor_x);
            cursor_y = cursor_y < 0 ? 0 : (cursor_y >= LV_VER_RES_MAX ? LV_VER_RES_MAX - 1 : cursor_y);

            data->state = LV_INDEV_STATE_REL; /* 持续移动期间始终REL，不误触 */

            last_touch_x = read_data.x_coordinate;
            last_touch_y = read_data.y_coordinate;
        }
    }
    else
    {
        finger_down = false;
        data->state = LV_INDEV_STATE_REL;

        /* 超时后重置等待双击状态 */
        if (waiting_for_second_click && 
            rt_tick_get() - last_click_tick > rt_tick_from_millisecond(DOUBLE_CLICK_INTERVAL_MS))
        {
            waiting_for_second_click = false;
        }
    }

    /* 更新LVGL的坐标 */
    data->point.x = cursor_x;
    data->point.y = cursor_y;
}

#define RST_PIN   "p000"
#define INT_PIN   "p010"
#define TOUCH_DEVICE_NAME "sci3i"

/*注册CST812T驱动到系统 */
int rt_hw_cst812t_register(void)
{
    struct rt_touch_config cfg;
    rt_base_t int_pin = rt_pin_get(INT_PIN);
    rt_base_t rst_pin = rt_pin_get(RST_PIN);
    cfg.dev_name = TOUCH_DEVICE_NAME;
    cfg.irq_pin.pin = int_pin;
    cfg.irq_pin.mode = PIN_MODE_INPUT_PULLUP;
    cfg.user_data = &rst_pin;
    rt_hw_cst8xx_init("cst8xx", &cfg);
    cst8xx_probe();
    cst8xx_reset(20);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_cst812t_register);

/* LVGL输入设备初始化*/
void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;
    if (touch_probe() != RT_EOK)
    {
        rt_kprintf("probe cst812t failed.\n");
        return;
    }
    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
	
    indev_touchpad = lv_indev_drv_register(&indev_drv);
	
    LV_IMG_DECLARE(mouse_cursor_icon)
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /* Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);   /* Set the image source*/
    lv_indev_set_cursor(indev_touchpad, cursor_obj);    /* Connect the image  object to the driver*/
	

}
