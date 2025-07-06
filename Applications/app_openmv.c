#include <rtthread.h>
#include <rtdevice.h>
#include "ra/board/ra8d1_ek/board_sdram.h"
#include "app_openmv.h"

/* ���������� MicroPython/OpenMV ���� ������������������������������������������������������ */
#include <py/compile.h>
#include <py/runtime.h>
#include <py/repl.h>
#include <py/gc.h>
#include <py/mperrno.h>
#include <py/stackctrl.h>
#include <py/frozenmod.h>
#include <py/mphal.h>
#include <lib/utils/pyexec.h>
#include <lib/mp-readline/readline.h>
#include <framebuffer.h>
#include <fb_alloc.h>
#include <ff_wrapper.h>
#include <usbdbg.h>

#include <tinyusb_debug.h>
#include <tusb.h>
#include <led.h>
#include <mpy_main.h>
#include <fmath.h>
#ifdef RT_USING_FAL
#include "fal.h"
#endif
/* ���������������������������������������������������������������������������������������������������������������� */

#define MP_TASK_STACK_SIZE   (64 * 1024)          /* 64 KB �߳�ջ */

static void *stack_top = RT_NULL;
/* GC �ѷŵ��ⲿ SDRAM��4 byte ���뼴�ɣ�*/
static char  OMV_ATTR_SECTION(OMV_ATTR_ALIGNED(gc_heap[OMV_HEAP_SIZE], 4), ".sdram");
extern int mount_init(void);
extern void fmath_init(void);
extern int tusb_board_init(void);
static bool exec_boot_script(const char *path, bool interruptible);

void *__signgam_addr(void)
{
    return NULL;
}

void flash_error(int n)
{
    led_state(LED_RED, 0);
    led_state(LED_GREEN, 0);
    led_state(LED_BLUE, 0);
    for (int i = 0; i < n; i++)
    {
        led_state(LED_RED, 0);
        rt_thread_mdelay(100);
        led_state(LED_RED, 1);
        rt_thread_mdelay(100);
    }
    led_state(LED_RED, 0);
}

void NORETURN __fatal_error(const char *msg)
{
    rt_thread_mdelay(100);
    led_state(1, 1);
    led_state(2, 1);
    led_state(3, 1);
    led_state(4, 1);
    mp_hal_stdout_tx_strn("\nFATAL ERROR:\n", 14);
    mp_hal_stdout_tx_strn(msg, strlen(msg));
    for (uint i = 0;;)
    {
        led_toggle(((i++) & 3) + 1);
        rt_thread_mdelay(100);
        if (i >= 16)
        {
            /* to conserve power */
            __WFI();
        }
    }
}

/* �������������� ���ߺ��� �������������������������������������������������������������� */
static bool exec_boot_script(const char *path, bool interruptible)
{
    nlr_buf_t nlr;
    bool interrupted = false;

    if (nlr_push(&nlr) == 0)
    {
        if (interruptible)
        {
            usbdbg_set_irq_enabled(true);
            usbdbg_set_script_running(true);
        }

        pyexec_file_if_exists(path);
        nlr_pop();
    }
    else
    {
        interrupted = true;
    }

    usbdbg_set_irq_enabled(false);
    usbdbg_set_script_running(false);

    if (interrupted)
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);

    return interrupted;
}

/* �������������� OpenMV / MicroPython �߳����� ���������������������� */
static void omv_thread(void *parameter)
{
    (void)parameter;
    int stack_dummy;
    stack_top = (void *)&stack_dummy;

#ifdef __DCACHE_PRESENT
    SCB_CleanDCache();           /* �������� Cache�����������ʼ���ȿ� */
#endif

    tusb_board_init();           /* TinyUSB (CDC) Ӳ����ʼ�� */

#ifdef RT_USING_FAL
    fal_init();
#endif

#ifdef BSP_USING_FS                    /* �ȴ� SD �����أ���ʹ�ã� */
    extern struct rt_semaphore sem_mnt_lock;
    rt_sem_take(&sem_mnt_lock, 400);
    struct dfs_fdtable *fd_table_bak = NULL;
#endif

    fmath_init();                /* OpenMV ������ٱ� */

#if MICROPY_PY_THREAD
    mp_thread_init(rt_thread_self()->stack_addr,
                   MP_TASK_STACK_SIZE / sizeof(uintptr_t));
#endif

    bool first_soft_reset = true;
soft_reset:
#ifdef BSP_USING_FS
    mp_sys_resource_bak(&fd_table_bak);  /* ���� fd ��(���� GC) */
#endif

    /* �ʵ���ʾ���� MicroPython ��ʼ���׶� */
    led_state(LED_RED,   1);
    led_state(LED_GREEN, 1);
    led_state(LED_BLUE,  1);

    /* ��ʼ�� framebuffer��OpenMV IDE �ã�*/
   // fb_alloc_init0();
    //framebuffer_init0();

    /* ���� MP ��ջ�� GC */
    mp_stack_set_top(stack_top);
    mp_stack_set_limit(MP_TASK_STACK_SIZE - 1024);
    gc_init(&gc_heap[0], &gc_heap[MP_ARRAY_SIZE(gc_heap)]);

    /* MicroPython ��ʼ�� */
    mp_init();
    readline_init0();
    usb_cdc_init();
    usbdbg_init();

    /* �صƣ���������ָʾ */
    led_state(LED_RED,   0);
    led_state(LED_GREEN, 0);
    led_state(LED_BLUE,  0);

    /* ����ִ�� boot.py / main.py��������ڣ� */
    bool interrupted = exec_boot_script("boot.py", false);
    if (first_soft_reset && !interrupted)
    {
        exec_boot_script("main.py", true);
        goto soft_reset_exit;
    }

    /* ���� REPL����ȴ� IDE �·��ű� */
    while (!usbdbg_script_ready())
    {
        nlr_buf_t nlr;
        if (nlr_push(&nlr) == 0)
        {
            usbdbg_set_irq_enabled(true);

            if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL)
            {
                if (pyexec_raw_repl() != 0) break;
            }
            else
            {
                if (pyexec_friendly_repl() != 0) break;
            }
            nlr_pop();
        }
    }

    /* IDE ���ͽű�ִ�� */
    if (usbdbg_script_ready())
    {
        nlr_buf_t nlr;
        if (nlr_push(&nlr) == 0)
        {
            usbdbg_set_irq_enabled(true);
            pyexec_str(usbdbg_get_script());
            usbdbg_set_irq_enabled(false);
            nlr_pop();
        }
        else
        {
            mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
        }

        /* �ȴ� IDE ������� */
        if (usbdbg_is_busy() && nlr_push(&nlr) == 0)
        {
            usbdbg_set_irq_enabled(true);
            usbdbg_wait_for_command(1000);
            usbdbg_set_irq_enabled(false);
            nlr_pop();
        }
    }

soft_reset_exit:
    mp_printf(&mp_plat_print, "MPY: soft reboot\n");
    gc_sweep_all();
    mp_deinit();

#if MICROPY_PY_THREAD
    mp_thread_deinit();
#endif
#ifdef RT_USING_DFS
    mp_sys_resource_gc(fd_table_bak);
#endif

    first_soft_reset = false;
    goto soft_reset;             /* ��λ���ص� REPL */
}

/* �������������� �ⲿ���ýӿ� ���������������������������������������������������������� */
int app_openmv_init(void)
{
    rt_thread_t tid = rt_thread_create("omv",
                                       omv_thread,
                                       RT_NULL,
                                       MP_TASK_STACK_SIZE / sizeof(uint32_t),
                                       22,          /* ���� camera/LVGL ��ʵʱ�߳� */
                                       20);
    if (tid)
    {
        rt_thread_startup(tid);
        return 0;
    }
    return -1;
}