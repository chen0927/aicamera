#include <rtthread.h>
#include <rtdevice.h>
#include "ra/board/ra8d1_ek/board_sdram.h"
#include "app_openmv.h"

/* ───── MicroPython/OpenMV 依赖 ─────────────────────────── */
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
/* ──────────────────────────────────────────────────────── */

#define MP_TASK_STACK_SIZE   (64 * 1024)          /* 64 KB 线程栈 */

static void *stack_top = RT_NULL;
/* GC 堆放到外部 SDRAM（4 byte 对齐即可）*/
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

/* ─────── 工具函数 ─────────────────────────────── */
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

/* ─────── OpenMV / MicroPython 线程主体 ─────────── */
static void omv_thread(void *parameter)
{
    (void)parameter;
    int stack_dummy;
    stack_top = (void *)&stack_dummy;

#ifdef __DCACHE_PRESENT
    SCB_CleanDCache();           /* 先清数据 Cache，避免后续初始化踩坑 */
#endif

    tusb_board_init();           /* TinyUSB (CDC) 硬件初始化 */

#ifdef RT_USING_FAL
    fal_init();
#endif

#ifdef BSP_USING_FS                    /* 等待 SD 卡挂载（若使用） */
    extern struct rt_semaphore sem_mnt_lock;
    rt_sem_take(&sem_mnt_lock, 400);
    struct dfs_fdtable *fd_table_bak = NULL;
#endif

    fmath_init();                /* OpenMV 浮点加速表 */

#if MICROPY_PY_THREAD
    mp_thread_init(rt_thread_self()->stack_addr,
                   MP_TASK_STACK_SIZE / sizeof(uintptr_t));
#endif

    bool first_soft_reset = true;
soft_reset:
#ifdef BSP_USING_FS
    mp_sys_resource_bak(&fd_table_bak);  /* 备份 fd 表(用于 GC) */
#endif

    /* 彩灯提示进入 MicroPython 初始化阶段 */
    led_state(LED_RED,   1);
    led_state(LED_GREEN, 1);
    led_state(LED_BLUE,  1);

    /* 初始化 framebuffer（OpenMV IDE 用）*/
   // fb_alloc_init0();
    //framebuffer_init0();

    /* 配置 MP 堆栈与 GC */
    mp_stack_set_top(stack_top);
    mp_stack_set_limit(MP_TASK_STACK_SIZE - 1024);
    gc_init(&gc_heap[0], &gc_heap[MP_ARRAY_SIZE(gc_heap)]);

    /* MicroPython 初始化 */
    mp_init();
    readline_init0();
    usb_cdc_init();
    usbdbg_init();

    /* 关灯，结束启动指示 */
    led_state(LED_RED,   0);
    led_state(LED_GREEN, 0);
    led_state(LED_BLUE,  0);

    /* 依次执行 boot.py / main.py（如果存在） */
    bool interrupted = exec_boot_script("boot.py", false);
    if (first_soft_reset && !interrupted)
    {
        exec_boot_script("main.py", true);
        goto soft_reset_exit;
    }

    /* 进入 REPL，或等待 IDE 下发脚本 */
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

    /* IDE 推送脚本执行 */
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

        /* 等待 IDE 命令完成 */
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
    goto soft_reset;             /* 软复位，回到 REPL */
}

/* ─────── 外部调用接口 ───────────────────────────── */
int app_openmv_init(void)
{
    rt_thread_t tid = rt_thread_create("omv",
                                       omv_thread,
                                       RT_NULL,
                                       MP_TASK_STACK_SIZE / sizeof(uint32_t),
                                       22,          /* 低于 camera/LVGL 等实时线程 */
                                       20);
    if (tid)
    {
        rt_thread_startup(tid);
        return 0;
    }
    return -1;
}