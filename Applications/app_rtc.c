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

    // ���豸
    if (rt_device_open(rtc_dev, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("[RTC] Failed to open rtc device!\n");
        return -1;
    }

    // ����һ�� RTC ʱ�䣨ʵ��������Զ�ȡ NTP �򴮿�ͬ����
    // ?? ʵ��ʹ��ʱ�˲���ֻ��ִ��һ�μ��ɣ��������籣���� VBAT ��ر�֤
    set_date(2025, 6, 21);     // ��-��-��
    set_time(21, 00, 0);       // ʱ-��-��

    time_t now = time(NULL);
    rt_kprintf("[RTC] ��ǰʱ�䣺%s\n", ctime(&now));

    return 0;
}
INIT_APP_EXPORT(rtc_app_init);  // ϵͳ�Զ�ִ��
