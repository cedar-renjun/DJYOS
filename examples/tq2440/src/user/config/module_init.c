#include "os_inc.h"
#include "cpu_peri.h"
#include "font_songti_16x16.h"
#include "key_hard.h"

void djy_main(void);

void __djy_main(void)
{
    djy_main();
}

//----组件初始化2-----------------------------------------------------------
//功能：可选组件初始化函数共有3个:
//      1、sys_module_init，在sys_init.c中，参见该函数注释
//      2、prj_module_init，在这里初始化的模块，需要调用跟具体工程相关的代码，例
//        如键盘模块，除了调用module_init_keyboard函数外，还要调用跟硬件相关的
//        module_init_keyboard_hard函数。
//      前两步初始化时，块相联分配方式还没有初始化，驱动中如果用到动态分配，使用
//      的是准静态分配，关于准静态分配的说明，参见mems.c文件。
//      3、run_module_init，参见该函数注释。
//参数：无
//返回：无
//-----------------------------------------------------------------------------
void prj_module_init(void)
{
    djy_handle_t char_term_lhdl;
    uint16_t evtt_main;

#if (cfg_gui_kernel == 1)
    static struct gkwin_rsc desktop;
    struct display_rsc *lcd_2440;
#endif


#if (cfg_time_module == 1)
    module_init_datatime(0);
#if(cfg_time_src == cfg_time_src_rtc)
    module_init_rtc(0);
#endif
#endif


#if (cfg_wdt == 1)
    module_init_wdt(0);
#endif

#if ((cfg_djyfs == 1) && (cfg_run_mode != cn_mode_tiny))
    module_init_djyfs(0);
#if (cfg_djyfs_flash == 1)
    module_init_DFFSD(0);
    module_init_fs_nandflash(0);
#endif
#endif


#if (cfg_djyip == 1)
    module_init_djyip(0);
#endif

#if (cfg_keyboard == 1)
    module_init_keyboard(0);
    module_init_keyboard_hard(0);
#endif

//初始化gui kernel模块
#if ((cfg_gui_kernel == 1) && (cfg_run_mode != cn_mode_tiny))
    module_init_gk(0);
    lcd_2440 = (struct display_rsc*)module_init_lcd((ptu32_t)"lcd_2440");

    gk_api_create_desktop(lcd_2440,&desktop,0,0,
                        cn_color_red+cn_color_green,cn_winbuf_buf);

    //以下初始化字符集驱动程序
#if (cfg_charset_gb2312 == 1)       //初始化gb2312字符集
extern ptu32_t module_init_encode_gb2312(ptu32_t para);
    module_init_encode_gb2312(0);
#endif

#if (cfg_charset_ascii == 1)       //初始化ascii字符集
    module_init_encode_ascii(0);
#endif

#if (cfg_charset_utf8 == 1)       //初始化utf8字符集
    module_init_encode_utf8(0);
#endif

//以下初始化字体驱动程序
#if (cfg_gb2312_8x16_1616 == 1)     //初始化gb2312点阵字库
extern ptu32_t module_init_font_gb2312_1616(ptu32_t para);
    module_init_font_gb2312_1616((ptu32_t)cs_gb2312_song_16);
#endif

#if (cfg_ascii_8x16 == 1)           //初始化8*16 ascii点阵字库
    module_init_font_ascii_8x16(0);
#endif

#if (cfg_ascii_8x8 == 1)           //初始化8*8 ascii点阵字库
extern ptu32_t module_init_font_ascii_8x8(ptu32_t para);
    module_init_font_ascii_8x8(0);
#endif
extern ptu32_t module_init_nls(ptu32_t para);
    module_init_nls(0);
#endif		//for #if (cfg_gui_kernel == 1)


#if(cfg_uart0_used == 1)
    module_init_uart0(0);
#endif
#if(cfg_uart1_used == 1)
    module_init_uart1(0);
#endif
#if(cfg_uart2_used == 1)
    module_init_uart2(0);
#endif

#if (cfg_shell == 1)
    module_init_shell(0);
    char_term_lhdl = dev_open_left(cfg_stdin_device,0);
    if(char_term_lhdl != NULL)
    {
        dev_ctrl_left(char_term_lhdl,cn_uart_start,0,0);
        //设置串口波特率为57600，
        dev_ctrl_left(char_term_lhdl,cn_uart_set_baud,57600,0);
        module_init_char_term((ptu32_t)char_term_lhdl);
        dev_ctrl_left(char_term_lhdl,cn_uart_connect_recv_evtt,
                            djy_get_evtt_id("term_scan"),0);
    }
#endif

    evtt_main = djy_evtt_regist(enum_correlative,cn_prio_RRS,0,0,2,
                                    __djy_main,cfg_main_stack,"main function");
    //事件的两个参数暂设为0，如果用shell启动，可用来采集shell命令行参数
    djy_event_pop(evtt_main,NULL,0,NULL,0,0,0);
    return ;
}


//----组件初始化3-----------------------------------------------------------
//功能：可选组件初始化函数共有3个:
//      1、sys_module_init，在sys_init.c中，参见该函数注释
//      2、prj_module_init，参见该函数注释。
//      3、run_module_init，本函数在djy_main函数开始处调用，需要操作系统的事件
//          调度开始后，或者需要块相联内存分配初始化后才能初始化的模块。
//参数：无
//返回：无
//-----------------------------------------------------------------------------
void run_module_init(void)
{
    djyfs_user_set_work_path();
#if ((cfg_gui_kernel == 1) && (cfg_single_touch == 1))
    module_init_touch(0);
    module_init_touch_adc(0);
#endif
}
/*
int app_init(void)
{
//    djyfs_file *zk_gb2312;
    static struct gkwin_rsc desktop;
    struct display_rsc *lcd_2440;
    djy_handle_t char_term_lhdl;
    uint16_t evtt_main;
    
    lcd_2440 = (struct display_rsc*)module_init_lcd((ptu32_t)"lcd_2440");
    
    gk_api_create_desktop(lcd_2440,&desktop,0,0,
                            cn_color_red+cn_color_green,cn_winbuf_buf);
#if (cfg_single_touch == 1)
#endif

#if (cfg_gui_kernel == 1)
    //以下初始化字符集驱动程序
#if (cfg_charset_gb2312 == 1)       //初始化gb2312字符集
extern ptu32_t module_init_encode_gb2312(ptu32_t para);
    module_init_encode_gb2312(0);
#endif

#if (cfg_charset_ascii == 1)       //初始化ascii字符集
    module_init_encode_ascii(0);
#endif

#if (cfg_charset_utf8 == 1)       //初始化utf8字符集
    module_init_encode_utf8(0);
#endif

//以下初始化字体驱动程序
#if (cfg_gb2312_8x16_1616 == 1)     //初始化gb2312点阵字库
extern ptu32_t module_init_font_gb2312_1616(ptu32_t para);
	module_init_font_gb2312_1616((ptu32_t)cs_gb2312_song_16);
#endif

#if (cfg_ascii_8x16 == 1)           //初始化8*16 ascii点阵字库
	module_init_font_ascii_8x16(0);
#endif

#if (cfg_ascii_8x8 == 1)           //初始化8*8 ascii点阵字库
extern ptu32_t module_init_font_ascii_8x8(ptu32_t para);
	module_init_font_ascii_8x8(0);
#endif
extern ptu32_t module_init_nls(ptu32_t para);
	module_init_nls(0);

#endif		//for #if (cfg_gui_kernel == 1)

#if((cfg_time_module == 1) && (cfg_time_src == cfg_time_src_rtc))
    module_init_rtc(0);
#endif

#if(cfg_uart0_used == 1)
    module_init_uart0(0);
#endif
#if(cfg_uart1_used == 1)
    module_init_uart1(0);
#endif
#if(cfg_uart2_used == 1)
    module_init_uart2(0);
#endif

#if (cfg_shell == 1)
    module_init_shell(0);
    char_term_lhdl = dev_open_left(cfg_stdin_device,0);
    if(char_term_lhdl != NULL)
    {
        dev_ctrl_left(char_term_lhdl,cn_uart_start,0,0);
        //设置串口波特率为57600，
        dev_ctrl_left(char_term_lhdl,cn_uart_set_baud,57600,0);
        module_init_char_term((ptu32_t)char_term_lhdl);
        dev_ctrl_left(char_term_lhdl,cn_uart_connect_recv_evtt,
                            djy_get_evtt_id("term_scan"),0);
    }
#endif

    evtt_main = djy_evtt_regist(enum_correlative,cn_prio_RRS,0,0,2,
                                    __djy_main,cfg_main_stack,"main function");
    //事件的两个参数暂设为0，如果用shell启动，可用来采集shell命令行参数
    djy_event_pop(evtt_main,NULL,0,NULL,0,0,0);
    return 1;
}
*/

