#ifndef LV_CONF_H
#define LV_CONF_H
#include <rtconfig.h>
#define LV_USE_SYSMON           1
#define LV_USE_PERF_MONITOR     1
#define LV_COLOR_DEPTH          16
#define LV_HOR_RES_MAX          480
#define LV_VER_RES_MAX          360
#define LV_COLOR_16_SWAP        0
#ifdef BSP_USING_LVGL_DAVE2D
    #define LV_USE_DRAW_DAVE2D      1
#endif
/*turn-on helium acceleration when Arm-2D and the Helium-powered device are detected */
#ifdef BSP_USING_LVGL_ARM2D
    #if defined(__ARM_FEATURE_MVE) && __ARM_FEATURE_MVE
        #define LV_USE_DRAW_SW_ASM  LV_DRAW_SW_ASM_HELIUM
        #define LV_USE_DRAW_ARM2D       1
        #define LV_USE_DRAW_ARM2D_SYNC  1
    #endif
#endif
#ifdef BSP_USING_LVGL_WIDGETS_DEMO
    #define LV_USE_DEMO_WIDGETS 1
    #define LV_DEMO_WIDGETS_SLIDESHOW   0
#endif  /* BSP_USING_LVGL_WIDGETS_DEMO */
/*Benchmark your system*/
#ifdef BSP_USING_LVGL_BENCHMARK_DEMO
    #define LV_USE_DEMO_BENCHMARK 1
    /*Use RGB565A8 images with 16 bit color depth instead of ARGB8565*/
    #define LV_DEMO_BENCHMARK_RGB565A8  1
    #define LV_FONT_MONTSERRAT_14       1
    #define LV_FONT_MONTSERRAT_24       1
#endif  /* BSP_USING_LVGL_BENCHMARK_DEMO */
/*Stress test for LVGL*/
#ifdef BSP_USING_LVGL_STRESS_DEMO
    #define LV_USE_DEMO_STRESS 1
#endif  /* BSP_USING_LVGL_STRESS_DEMO */
/*Render test for LVGL*/
#ifdef BSP_USING_LVGL_RENDER_DEMO
    #define LV_USE_DEMO_RENDER 1
#endif  /* BSP_USING_LVGL_RENDER_DEMO */
/*Music player demo*/
#ifdef BSP_USING_LVGL_MUSIC_DEMO
    #define LV_USE_DEMO_MUSIC 1
    #define LV_DEMO_MUSIC_SQUARE    1
    #define LV_DEMO_MUSIC_LANDSCAPE 0
    #define LV_DEMO_MUSIC_ROUND     0
    #define LV_DEMO_MUSIC_LARGE     0
    #define LV_DEMO_MUSIC_AUTO_PLAY 0
    #define LV_FONT_MONTSERRAT_12   1
    #define LV_FONT_MONTSERRAT_16   1
#endif  /* BSP_USING_LVGL_MUSIC_DEMO */
#ifdef _LV_LOG_LEVEL_TRACE
    /*Enable/disable LV_LOG_TRACE in modules that produces a huge number of logs*/
    #define LV_LOG_TRACE_MEM        1
    #define LV_LOG_TRACE_TIMER      1
    #define LV_LOG_TRACE_INDEV      1
    #define LV_LOG_TRACE_DISP_REFR  1
    #define LV_LOG_TRACE_EVENT      1
    #define LV_LOG_TRACE_OBJ_CREATE 1
    #define LV_LOG_TRACE_LAYOUT     1
    #define LV_LOG_TRACE_ANIM       1
#else
    #define LV_USE_LOG 0
    #define LV_LOG_PRINTF 0
#endif
//#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
//#define LV_ASSERT_HANDLER while(1);   /*Halt by default*/
#ifdef _LV_USE_ASSERT_NULL
#define LV_USE_ASSERT_NULL 1
#endif
#ifdef _LV_USE_ASSERT_MALLOC
#define LV_USE_ASSERT_MALLOC 1
#endif
#ifdef _LV_USE_ASSERT_STYLE
#define LV_USE_ASSERT_STYLE 1
#endif
#ifdef _LV_USE_ASSERT_MEM_INTEGRITY
#define LV_USE_ASSERT_MEM_INTEGRITY 1
#endif
#ifdef _LV_USE_ASSERT_OBJ
#define LV_USE_ASSERT_OBJ 1
#endif
//"Widget usage"
#ifndef _LV_USE_ARC
#define LV_USE_ARC                       1
#endif
#ifndef _LV_USE_BAR
#define LV_USE_BAR                       1
#endif
#ifndef _LV_USE_BTN
#define LV_USE_BTN                       1
#endif
#ifndef _LV_USE_BTNMATRIX
#define LV_USE_BTNMATRIX                 1
#endif
#ifndef _LV_USE_CANVAS
#define LV_USE_CANVAS                    1
#endif
#ifndef _LV_USE_CHECKBOX
#define LV_USE_CHECKBOX                  1
#endif
#ifndef _LV_USE_DROPDOWN
#define LV_USE_DROPDOWN                  1
#endif
#ifndef _LV_USE_IMG
#define LV_USE_IMG                       1
#endif
#ifndef _LV_USE_LABEL
#define LV_USE_LABEL                     1
#endif
#ifndef _LV_LABEL_TEXT_SELECTION
#define LV_LABEL_TEXT_SELECTION          1
#endif
#ifndef _LV_LABEL_LONG_TXT_HINT
#define LV_LABEL_LONG_TXT_HINT           1
#endif
#ifndef _LV_USE_LINE
#define LV_USE_LINE                      1
#endif
#ifndef _LV_USE_ROLLER
#define LV_USE_ROLLER                    1
#endif
#ifdef _LV_ROLLER_INF_PAGES
#define LV_ROLLER_INF_PAGES              _LV_ROLLER_INF_PAGES
#endif
#ifndef _LV_USE_SLIDER
#define LV_USE_SLIDER                    1
#endif
#ifndef _LV_USE_SWITCH
#define LV_USE_SWITCH                    1
#endif
#ifndef _LV_USE_TEXTAREA
#define LV_USE_TEXTAREA                  1
#endif
#ifdef _LV_TEXTAREA_DEF_PWD_SHOW_TIME
#define LV_TEXTAREA_DEF_PWD_SHOW_TIME    _LV_TEXTAREA_DEF_PWD_SHOW_TIME
#endif
#ifndef _LV_USE_TABLE
#define LV_USE_TABLE                     1
#endif
//"Extra Widgets"
#ifndef _LV_USE_ANIMIMG
#define LV_USE_ANIMIMG                     1
#endif
#ifndef _LV_USE_CALENDAR
#define LV_USE_CALENDAR                    1
#endif
#ifndef _LV_CALENDAR_WEEK_STARTS_MONDA
#define LV_CALENDAR_WEEK_STARTS_MONDA      1
#endif
#ifndef _LV_USE_CALENDAR_HEADER_ARROW
#define LV_USE_CALENDAR_HEADER_ARROW       1
#endif
#ifndef _LV_USE_CALENDAR_HEADER_DROPDO
#define LV_USE_CALENDAR_HEADER_DROPDO      1
#endif
#ifndef _LV_USE_CHART
#define LV_USE_CHART                       1
#endif
#ifndef _LV_USE_COLORWHEEL
#define LV_USE_COLORWHEEL                  1
#endif
#ifndef _LV_USE_IMGBTN
#define LV_USE_IMGBTN                      1
#endif
#ifndef _LV_USE_KEYBOARD
#define LV_USE_KEYBOARD                    1
#endif
#ifndef _LV_USE_LED
#define LV_USE_LED                         1
#endif
#ifndef _LV_USE_LIST
#define LV_USE_LIST                        1
#endif
#ifndef _LV_USE_MENU
#define LV_USE_MENU                        1
#endif
#ifndef _LV_USE_METER
#define LV_USE_METER                       1
#endif
#ifndef _LV_USE_MSGBOX
#define LV_USE_MSGBOX                      1
#endif
#ifndef _LV_USE_SPINBOX
#define LV_USE_SPINBOX                     1
#endif
#ifndef _LV_USE_SPINNER
#define LV_USE_SPINNER                     1
#endif
#ifndef _LV_USE_TABVIEW
#define LV_USE_TABVIEW                     1
#endif
#ifndef _LV_USE_TILEVIEW
#define LV_USE_TILEVIEW                    1
#endif
#ifndef _LV_USE_WIN
#define LV_USE_WIN                         1
#endif
#ifndef _LV_USE_SPAN
#define LV_USE_SPAN                        1
#endif
#ifdef _LV_SPAN_SNIPPET_STACK_SIZE
#define LV_SPAN_SNIPPET_STACK_SIZE   _LV_SPAN_SNIPPET_STACK_SIZE
#endif
//"Layouts"
#ifndef _LV_USE_FLEX
#define LV_USE_FLEX                       1
#endif
#ifndef _LV_USE_GRID
#define LV_USE_GRID                       1
#endif
#ifndef _LV_USE_THEME_DEFAULT
#define LV_USE_THEME_DEFAULT              1
#endif
#ifndef _LV_THEME_DEFAULT_DARK
#define LV_THEME_DEFAULT_DARK             1
#endif
#ifndef _LV_THEME_DEFAULT_GROW
#define LV_THEME_DEFAULT_GROW             1
#endif
#ifdef _LV_THEME_DEFAULT_TRANSITION_TIME
#define LV_THEME_DEFAULT_TRANSITION_TIME        _LV_THEME_DEFAULT_TRANSITION_TIME
#endif
#ifndef _LV_USE_THEME_BASIC
#define LV_USE_THEME_BASIC                1
#endif
//"Enable built-in fonts"
#define LV_FONT_MONTSERRAT_8                   1
#define LV_FONT_MONTSERRAT_10                  1
#define LV_FONT_MONTSERRAT_10                  1
#define LV_FONT_MONTSERRAT_14                  1
#define LV_FONT_MONTSERRAT_16                  1
#define LV_FONT_MONTSERRAT_18                  1
#define LV_FONT_MONTSERRAT_20                  1
#define LV_FONT_MONTSERRAT_22                  1
#define LV_FONT_MONTSERRAT_24                  1
#define LV_FONT_MONTSERRAT_26                  1
#define LV_FONT_MONTSERRAT_28                  1
#define LV_FONT_MONTSERRAT_30                  1
#define LV_FONT_MONTSERRAT_32                  1
#define LV_FONT_MONTSERRAT_34                  1
#define LV_FONT_MONTSERRAT_36                  1
#define LV_FONT_MONTSERRAT_38                  0
#define LV_FONT_MONTSERRAT_40                  0
#define LV_FONT_MONTSERRAT_42                  0
#define LV_FONT_MONTSERRAT_44                  0
#define LV_FONT_MONTSERRAT_48                  0
#define LV_FONT_MONTSERRAT_12_SUBPX            0
#define LV_FONT_MONTSERRAT_28_COMPRESSED       0
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW       0
#define LV_FONT_SIMSUN_16_CJK                  0
#define LV_FONT_UNSCII_8                       0
#define LV_FONT_UNSCII_16                      0
#ifdef _LV_FONT_MONTSERRAT_8
#undef LV_FONT_MONTSERRAT_8
#define LV_FONT_MONTSERRAT_8                   1
#endif
#ifdef _LV_FONT_MONTSERRAT_10
#undef LV_FONT_MONTSERRAT_10
#define LV_FONT_MONTSERRAT_10                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_12
#undef LV_FONT_MONTSERRAT_12
#define LV_FONT_MONTSERRAT_12                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_14
#undef LV_FONT_MONTSERRAT_14
#define LV_FONT_MONTSERRAT_14                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_16
#undef LV_FONT_MONTSERRAT_16
#define LV_FONT_MONTSERRAT_16                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_18
#undef LV_FONT_MONTSERRAT_18
#define LV_FONT_MONTSERRAT_18                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_20
#undef LV_FONT_MONTSERRAT_20
#define LV_FONT_MONTSERRAT_20                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_22
#undef LV_FONT_MONTSERRAT_22
#define LV_FONT_MONTSERRAT_22                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_24
#undef LV_FONT_MONTSERRAT_24
#define LV_FONT_MONTSERRAT_24                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_26
#undef LV_FONT_MONTSERRAT_26
#define LV_FONT_MONTSERRAT_26                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_28
#undef LV_FONT_MONTSERRAT_28
#define LV_FONT_MONTSERRAT_28                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_30
#undef LV_FONT_MONTSERRAT_30
#define LV_FONT_MONTSERRAT_30                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_32
#undef LV_FONT_MONTSERRAT_32
#define LV_FONT_MONTSERRAT_32                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_34
#undef LV_FONT_MONTSERRAT_34
#define LV_FONT_MONTSERRAT_34                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_36
#undef LV_FONT_MONTSERRAT_36
#define LV_FONT_MONTSERRAT_36                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_38
#undef LV_FONT_MONTSERRAT_38
#define LV_FONT_MONTSERRAT_38                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_40
#undef LV_FONT_MONTSERRAT_40
#define LV_FONT_MONTSERRAT_40                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_42
#undef LV_FONT_MONTSERRAT_42
#define LV_FONT_MONTSERRAT_42                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_44
#undef LV_FONT_MONTSERRAT_44
#define LV_FONT_MONTSERRAT_44                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_46
#undef LV_FONT_MONTSERRAT_46
#define LV_FONT_MONTSERRAT_46                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_48
#undef LV_FONT_MONTSERRAT_48
#define LV_FONT_MONTSERRAT_48                  1
#endif
#ifdef _LV_FONT_MONTSERRAT_12_SUBPX
#undef LV_FONT_MONTSERRAT_12_SUBPX
#define LV_FONT_MONTSERRAT_12_SUBPX            1
#endif
#ifdef _LV_FONT_MONTSERRAT_28_COMPRESSED
#undef LV_FONT_MONTSERRAT_28_COMPRESSED
#define LV_FONT_MONTSERRAT_28_COMPRESSED       1
#endif
#ifdef _LV_FONT_DEJAVU_16_PERSIAN_HEBREW
#undef LV_FONT_DEJAVU_16_PERSIAN_HEBREW
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW       1
#endif
#ifdef _LV_FONT_SIMSUN_16_CJK
#undef LV_FONT_SIMSUN_16_CJK
#define LV_FONT_SIMSUN_16_CJK                  1
#endif
#ifdef _LV_FONT_UNSCII_8
#undef LV_FONT_UNSCII_8
#define LV_FONT_UNSCII_8                       1
#endif
#ifdef _LV_FONT_UNSCII_16
#undef LV_FONT_UNSCII_16
#define LV_FONT_UNSCII_16                      1
#endif
#ifdef _LV_FONT_CUSTOM
#define LV_FONT_CUSTOM                         1
#endif
#ifdef _LV_FONT_CUSTOM_DECLARE
#define LV_FONT_CUSTOM_DECLARE _LV_FONT_CUSTOM_DECLARE
#endif
/*------------------
 * DEFAULT FONT
 *-----------------*/
#ifdef _LV_FONT_DEFAULT_MONTSERRAT_8
#  define LV_FONT_DEFAULT &lv_font_montserrat_8
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_10)
#  define LV_FONT_DEFAULT &lv_font_montserrat_10
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_12)
#  define LV_FONT_DEFAULT &lv_font_montserrat_12
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_14)
#  define LV_FONT_DEFAULT &lv_font_montserrat_14
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_16)
#  define LV_FONT_DEFAULT &lv_font_montserrat_16
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_18)
#  define LV_FONT_DEFAULT &lv_font_montserrat_18
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_20)
#  define LV_FONT_DEFAULT &lv_font_montserrat_20
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_22)
#  define LV_FONT_DEFAULT &lv_font_montserrat_22
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_24)
#  define LV_FONT_DEFAULT &lv_font_montserrat_24
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_26)
#  define LV_FONT_DEFAULT &lv_font_montserrat_26
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_28)
#  define LV_FONT_DEFAULT &lv_font_montserrat_28
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_30)
#  define LV_FONT_DEFAULT &lv_font_montserrat_30
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_32)
#  define LV_FONT_DEFAULT &lv_font_montserrat_32
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_34)
#  define LV_FONT_DEFAULT &lv_font_montserrat_34
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_36)
#  define LV_FONT_DEFAULT &lv_font_montserrat_36
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_38)
#  define LV_FONT_DEFAULT &lv_font_montserrat_38
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_40)
#  define LV_FONT_DEFAULT &lv_font_montserrat_40
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_42)
#  define LV_FONT_DEFAULT &lv_font_montserrat_42
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_44)
#  define LV_FONT_DEFAULT &lv_font_montserrat_44
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_46)
#  define LV_FONT_DEFAULT &lv_font_montserrat_46
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_48)
#  define LV_FONT_DEFAULT &lv_font_montserrat_48
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_12_SUBPX)
#  define LV_FONT_DEFAULT &lv_font_montserrat_12_subpx
#elif defined(_LV_FONT_DEFAULT_MONTSERRAT_28_COMPRESSED)
#  define LV_FONT_DEFAULT &lv_font_montserrat_28_compressed
#elif defined(_LV_FONT_DEFAULT_DEJAVU_16_PERSIAN_HEBREW)
#  define LV_FONT_DEFAULT &lv_font_dejavu_16_persian_hebrew
#elif defined(_LV_FONT_DEFAULT_SIMSUN_16_CJK)
#  define LV_FONT_DEFAULT &lv_font_simsun_16_cjk
#elif defined(_LV_FONT_DEFAULT_UNSCII_8)
#  define LV_FONT_DEFAULT &lv_font_unscii_8
#elif defined(_LV_FONT_DEFAULT_UNSCII_16)
#  define LV_FONT_DEFAULT &lv_font_unscii_16
#endif
#ifdef _LV_TXT_ENC_UTF8
#  define LV_TXT_ENC LV_TXT_ENC_UTF8
#elif defined(_LV_TXT_ENC_ASCII)
#  define LV_TXT_ENC LV_TXT_ENC_ASCII
#endif
#endif
