#include "os_inc.h"
#include "cpu_peri.h"
#include "font_songti_16x16.h"
#include "key_hard.h"

void djy_main(void);

void __djy_main(void)
{
    djy_main();
}

//----�����ʼ��2-----------------------------------------------------------
//���ܣ���ѡ�����ʼ����������3��:
//      1��sys_module_init����sys_init.c�У��μ��ú���ע��
//      2��prj_module_init���������ʼ����ģ�飬��Ҫ���ø����幤����صĴ��룬��
//        �����ģ�飬���˵���module_init_keyboard�����⣬��Ҫ���ø�Ӳ����ص�
//        module_init_keyboard_hard������
//      ǰ������ʼ��ʱ�����������䷽ʽ��û�г�ʼ��������������õ���̬���䣬ʹ��
//      ����׼��̬���䣬����׼��̬�����˵�����μ�mems.c�ļ���
//      3��run_module_init���μ��ú���ע�͡�
//��������
//���أ���
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

//��ʼ��gui kernelģ��
#if ((cfg_gui_kernel == 1) && (cfg_run_mode != cn_mode_tiny))
    module_init_gk(0);
    lcd_2440 = (struct display_rsc*)module_init_lcd((ptu32_t)"lcd_2440");

    gk_api_create_desktop(lcd_2440,&desktop,0,0,
                        cn_color_red+cn_color_green,cn_winbuf_buf);

    //���³�ʼ���ַ�����������
#if (cfg_charset_gb2312 == 1)       //��ʼ��gb2312�ַ���
extern ptu32_t module_init_encode_gb2312(ptu32_t para);
    module_init_encode_gb2312(0);
#endif

#if (cfg_charset_ascii == 1)       //��ʼ��ascii�ַ���
    module_init_encode_ascii(0);
#endif

#if (cfg_charset_utf8 == 1)       //��ʼ��utf8�ַ���
    module_init_encode_utf8(0);
#endif

//���³�ʼ��������������
#if (cfg_gb2312_8x16_1616 == 1)     //��ʼ��gb2312�����ֿ�
extern ptu32_t module_init_font_gb2312_1616(ptu32_t para);
    module_init_font_gb2312_1616((ptu32_t)cs_gb2312_song_16);
#endif

#if (cfg_ascii_8x16 == 1)           //��ʼ��8*16 ascii�����ֿ�
    module_init_font_ascii_8x16(0);
#endif

#if (cfg_ascii_8x8 == 1)           //��ʼ��8*8 ascii�����ֿ�
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
        //���ô��ڲ�����Ϊ57600��
        dev_ctrl_left(char_term_lhdl,cn_uart_set_baud,57600,0);
        module_init_char_term((ptu32_t)char_term_lhdl);
        dev_ctrl_left(char_term_lhdl,cn_uart_connect_recv_evtt,
                            djy_get_evtt_id("term_scan"),0);
    }
#endif

    evtt_main = djy_evtt_regist(enum_correlative,cn_prio_RRS,0,0,2,
                                    __djy_main,cfg_main_stack,"main function");
    //�¼���������������Ϊ0�������shell�������������ɼ�shell�����в���
    djy_event_pop(evtt_main,NULL,0,NULL,0,0,0);
    return ;
}


//----�����ʼ��3-----------------------------------------------------------
//���ܣ���ѡ�����ʼ����������3��:
//      1��sys_module_init����sys_init.c�У��μ��ú���ע��
//      2��prj_module_init���μ��ú���ע�͡�
//      3��run_module_init����������djy_main������ʼ�����ã���Ҫ����ϵͳ���¼�
//          ���ȿ�ʼ�󣬻�����Ҫ�������ڴ�����ʼ������ܳ�ʼ����ģ�顣
//��������
//���أ���
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
    //���³�ʼ���ַ�����������
#if (cfg_charset_gb2312 == 1)       //��ʼ��gb2312�ַ���
extern ptu32_t module_init_encode_gb2312(ptu32_t para);
    module_init_encode_gb2312(0);
#endif

#if (cfg_charset_ascii == 1)       //��ʼ��ascii�ַ���
    module_init_encode_ascii(0);
#endif

#if (cfg_charset_utf8 == 1)       //��ʼ��utf8�ַ���
    module_init_encode_utf8(0);
#endif

//���³�ʼ��������������
#if (cfg_gb2312_8x16_1616 == 1)     //��ʼ��gb2312�����ֿ�
extern ptu32_t module_init_font_gb2312_1616(ptu32_t para);
	module_init_font_gb2312_1616((ptu32_t)cs_gb2312_song_16);
#endif

#if (cfg_ascii_8x16 == 1)           //��ʼ��8*16 ascii�����ֿ�
	module_init_font_ascii_8x16(0);
#endif

#if (cfg_ascii_8x8 == 1)           //��ʼ��8*8 ascii�����ֿ�
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
        //���ô��ڲ�����Ϊ57600��
        dev_ctrl_left(char_term_lhdl,cn_uart_set_baud,57600,0);
        module_init_char_term((ptu32_t)char_term_lhdl);
        dev_ctrl_left(char_term_lhdl,cn_uart_connect_recv_evtt,
                            djy_get_evtt_id("term_scan"),0);
    }
#endif

    evtt_main = djy_evtt_regist(enum_correlative,cn_prio_RRS,0,0,2,
                                    __djy_main,cfg_main_stack,"main function");
    //�¼���������������Ϊ0�������shell�������������ɼ�shell�����в���
    djy_event_pop(evtt_main,NULL,0,NULL,0,0,0);
    return 1;
}
*/

