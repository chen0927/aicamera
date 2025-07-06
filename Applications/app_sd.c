#include "app_sd.h"


#define PHOTO_DIR     "/"
#define PHOTO_PREFIX  "photo"
#define PHOTO_EXT     ".bmp"
#define CAM_WIDTH     320
#define CAM_HEIGHT    240

#define BMP_HEADER_SIZE 68
volatile bool save_flag = false;

static inline void put_le16(uint8_t *p, uint16_t v)
{
    p[0] = v & 0xFF; p[1] = v >> 8;
}
static inline void put_le32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)(v);
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}


static void ensure_directory(const char *path)
{
    if (access(path, F_OK) != 0)  // ������
    {
        mkdir(path, 0x0777);  // ����Ŀ¼
    }
}

static int save_to_sdcard(uint16_t *buf, size_t len)
{
    time_t now = time(RT_NULL);
    struct tm *t = localtime(&now);
    if (!t)
    {
        rt_kprintf("[Storage] ��ȡϵͳʱ��ʧ��\n");
        return -1;
    }

    // ����Ŀ¼·����/photo/YYYYMM/DD
    char dir_month[32], dir_day[64], file_path[128];
    rt_snprintf(dir_month, sizeof(dir_month), "/photo/%04d%02d", t->tm_year + 1900, t->tm_mon + 1);
    rt_snprintf(dir_day, sizeof(dir_day), "%s/%02d", dir_month, t->tm_mday);  // /photo/202506/22

    ensure_directory("/photo");
    ensure_directory(dir_month);
    ensure_directory(dir_day);

    // �Զ������ļ�����001.bmp, 002.bmp, ...
    int idx = 1;
    while (1)
    {
        rt_snprintf(file_path, sizeof(file_path), "%s/%03d.bmp", dir_day, idx);
        if (access(file_path, F_OK) != 0)
            break;
        idx++;
    }

    // ���ļ�д��
    int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd < 0)
    {
        rt_kprintf("[Storage] ��ʧ��: %s\n", file_path);
        return -1;
    }

    // ���� BMP ͷ
    uint8_t hdr[BMP_HEADER_SIZE] __attribute__((aligned(4)));
    uint8_t *p = hdr;

    put_le16(p, 0x4D42);                     p += 2;
    put_le32(p, 14 + 40 + 12 + len);         p += 4;
    put_le16(p, 0);                          p += 2;
    put_le16(p, 0);                          p += 2;
    put_le32(p, 14 + 40 + 12);               p += 4;

    put_le32(p, 40);                         p += 4;
    put_le32(p, CAM_WIDTH);                 p += 4;
    put_le32(p, -CAM_HEIGHT);               p += 4;
    put_le16(p, 1);                          p += 2;
    put_le16(p, 16);                         p += 2;
    put_le32(p, 3);                          p += 4;
    put_le32(p, len);                        p += 4;
    put_le32(p, 0);                          p += 4;
    put_le32(p, 0);                          p += 4;
    put_le32(p, 0);                          p += 4;
    put_le32(p, 0);                          p += 4;

    put_le32(p, 0xF800);                     p += 4;
    put_le32(p, 0x07E0);                     p += 4;
    put_le32(p, 0x001F);                     p += 4;
    put_le16(p, 0);                          p += 2;

#if defined(__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1)
    SCB_InvalidateDCache_by_Addr((uint32_t *)buf, len);
#endif

    if (write(fd, hdr, sizeof(hdr)) != sizeof(hdr))
    {
        rt_kprintf("[Storage] дBMPͷʧ��\n");
        goto _err;
    }

    if (write(fd, buf, len) != len)
    {
        rt_kprintf("[Storage] д��ͼ��ʧ��\n");
        goto _err;
    }

    close(fd);
    rt_kprintf("[Storage] ����ɹ�: %s\n", file_path);
    return 0;

_err:
    close(fd);
    unlink(file_path);
    return -2;
}



static void storage_thread_entry(void *parameter)
{
	
    while (1)
    {
        if(save_flag == true && preview_flag==false)
		{
			rt_kprintf("[Storage] Saving image to SD card...\n");
            save_to_sdcard((uint16_t *)(framebuffer->data + 32), FRAME_SIZE);  // ֱ�ӱ��浱ǰ֡
            save_flag = false;  // �����־����ֹ�ظ�����
            
		}
    }
}



static int storage_init(void)
{
	
    rt_thread_t tid;

    tid = rt_thread_create("storage",
                           storage_thread_entry,
                           RT_NULL,
                           STORAGE_THREAD_STACK_SIZE,                  // ջ��С
                           STORAGE_THREAD_PRIORITY,  // ���ȼ�
                           STORAGE_THREAD_TIMESLICE);                   // ʱ��Ƭ

    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
        rt_kprintf("[storage] storage thread started.\n");
        return 0;
    }
    else
    {
        rt_kprintf("[storage] Failed to create storage thread.\n");
        return -1;
    }
}

extern int mount_init(void);
void sd_init(void)
{
	
	mount_init(); //����SD��
	storage_init();//�����洢�߳�
}