#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>

#define RTC_DEV_NAME "rtc"

static int rtc_app_init(void)
{
    rt_device_t rtc_dev = rt_device_find(RTC_DEV_NAME);
    if (!rtc_dev)
    {
        rt_kprintf("[RTC] Cannot find rtc device!\n");
        return -1;
    }

    // 打开设备
    if (rt_device_open(rtc_dev, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("[RTC] Failed to open rtc device!\n");
        return -1;
    }

    // 设置一次 RTC 时间（实际中你可以读取 NTP 或串口同步）
    // ?? 实际使用时此步骤只需执行一次即可，后续掉电保留由 VBAT 电池保证
    set_date(2025, 6, 21);     // 年-月-日
    set_time(21, 00, 0);       // 时-分-秒

    time_t now = time(NULL);
    rt_kprintf("[RTC] 当前时间：%s\n", ctime(&now));

    return 0;
}
INIT_APP_EXPORT(rtc_app_init);  // 系统自动执行
