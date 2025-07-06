#ifndef __APP_SD_H__
#define __APP_SD_H__


#include <rtthread.h>
#include <rtdevice.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>


#include "app_camera.h"


#define STORAGE_THREAD_STACK_SIZE  4096
#define STORAGE_THREAD_PRIORITY    22
#define STORAGE_THREAD_TIMESLICE   10


extern volatile bool save_flag;

void sd_init(void);



#endif




