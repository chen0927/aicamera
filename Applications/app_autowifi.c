#include <rtthread.h>
#include <rtdevice.h>
#include <wlan_mgnt.h>  // RT-Thread WLAN 管理接口
#include <wlan_cfg.h>   // 包含 WLAN 自动连接相关配置接口
#include "app_autowifi.h"
#define WIFI_SSID     "ISO-407-24"      // <<< 修改为你的 WiFi 名称
#define WIFI_PASSWORD "jsj407407.."  // <<< 修改为你的 WiFi 密码

#define WIFI_CONNECT_INTERVAL  5000   // 每5秒尝试连接一次（ms）
volatile bool wifi_connected = RT_FALSE;

static void auto_wifi_connect_thread(void *parameter)
{
	struct rt_wlan_info info;
	
    while (1)
    {
		
        if (!rt_wlan_is_ready())
        {
           if (wifi_connected == RT_TRUE)
           {
                rt_kprintf("[WiFi] Disconnected. Trying to reconnect to %s...\n", WIFI_SSID);
                wifi_connected = RT_FALSE;
           }

            rt_wlan_connect(WIFI_SSID, WIFI_PASSWORD);			
        }
        else
        {
			if (wifi_connected == RT_FALSE)
            {
               if (rt_wlan_get_info(&info) == RT_EOK)
                {
                    rt_kprintf("[WiFi] Connected to: %s (RSSI: %d)\n", info.ssid.val, info.rssi);
                    wifi_connected = RT_TRUE;
                }
                else
                {
                    rt_kprintf("[WiFi] Connection ready, but failed to get info.\n");
                }
            }
			
        }

        rt_thread_mdelay(WIFI_CONNECT_INTERVAL);
    }
}

void wifi_auto_connect_init(void)
{
    rt_thread_t tid = rt_thread_create("wifi_auto",
                                       auto_wifi_connect_thread,
                                       RT_NULL,
                                       1024,   
                                       12,     
                                       20);   
    if (tid)
    {
        rt_thread_startup(tid);
        rt_kprintf("[WiFi] Auto-connect thread started.\n");
    }
    else
    {
        rt_kprintf("[WiFi] Failed to start auto-connect thread!\n");
    }
}
