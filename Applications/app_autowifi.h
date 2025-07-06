#ifndef __WIFI_AUTO_CONNECT_H__
#define __WIFI_AUTO_CONNECT_H__
#include <stdbool.h>
void wifi_auto_connect_init(void);

extern volatile bool wifi_connected;
#endif /* __WIFI_AUTO_CONNECT_H__ */
