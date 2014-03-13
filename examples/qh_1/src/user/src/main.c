#include "os_inc.h"
#include "gk_api.h"
#include "cpu_peri.h"
#include "gpio_api.h"
//#include <string.h>

void run_module_init(void);

#if (cfg_gui_kernel == 1)
// 在显示器主体上显示内容
void dis_wnd_body_text(struct gkwin_rsc *parent, s32 area)
{
	struct input_device_msg *input_msg;
    s32 touch_x=0, touch_y=0;

	switch (area)
	{
	case 1:
        input_msg = (struct input_device_msg *)djy_get_event_para(NULL);
        if(input_msg->input_type == enum_stdin_single_touch)
    	{
    		touch_x = input_msg->input_data.single_touch_msg.x;
    		touch_y = input_msg->input_data.single_touch_msg.y;
    		gk_api_draw_circle(parent, touch_x, touch_y, 10,
    				cn_color_white, cn_r2_copypen, cn_timeout_forever);
    	}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}

// 在显示器底端显示时间
void dis_wnd_bottom_text(struct gkwin_rsc *parent)
{
	static char text_time[]="2012年07月06日  23:59:59";
	static s64 last_nowtime = 0;
	struct st_rect rect;
	char text_buf[32];
	struct djy_tm dtm;
	s64 nowtime;

	rect.left = 15;
	rect.top = 5;
	rect.right = 24*8+15;
	rect.bottom = 16+5;

	// 更新时间
	nowtime = djy_time(&nowtime);
	if ((nowtime - last_nowtime) > 0)
	{
		dtm = localtime(nowtime);
		text_time[0] = '\0';
		// 年
		djy_itoa(dtm.tm_year, text_buf, 10);
		strcat(text_buf, (const char*)"年");
		strcat(text_time, text_buf);
		// 月
		if (dtm.tm_mon<10)
		{
			strcat(text_time, "0");
		}
		djy_itoa(dtm.tm_mon, text_buf, 10);
		strcat(text_buf, "月");
		strcat(text_time, text_buf);
		// 日
		if (dtm.tm_mday<10)
		{
			strcat(text_time, "0");
		}
		djy_itoa(dtm.tm_mday, text_buf, 10);
		strcat(text_buf, "日 ");
		strcat(text_time, text_buf);
		// 时
		if (dtm.tm_hour<10)
		{
			strcat(text_time, "0");
		}
		djy_itoa(dtm.tm_hour, text_buf, 10);
		strcat(text_buf, ":");
		strcat(text_time, text_buf);
		// 分
		if (dtm.tm_min<10)
		{
			strcat(text_time, "0");
		}
		djy_itoa(dtm.tm_min, text_buf, 10);
		strcat(text_buf, ":");
		strcat(text_time, text_buf);
		// 秒
		if (dtm.tm_sec<10)
		{
			strcat(text_time, "0");
		}
		djy_itoa(dtm.tm_sec, text_buf, 10);
		strcat(text_time, text_buf);

		gk_api_fill_part_win(parent, rect, cn_color_blue,0);
		gk_api_draw_text(parent, 0, 5, text_time, strnlen(text_time, 100), cn_timeout_forever);
	}
}
#endif

void led_flash(void)
{
    while(1)
    {
    	gpio_setto_low(cn_gpio_c, (1<<4)|(1<<6)|(1<<8));
    	gpio_setto_high(cn_gpio_c, (1<<9));
    	djy_event_delay(500*mS);

    	gpio_setto_low(cn_gpio_c, (1<<4)|(1<<6)|(1<<9));
    	gpio_setto_high(cn_gpio_c, (1<<8));
    	djy_event_delay(500*mS);

    	gpio_setto_low(cn_gpio_c, (1<<6)|(1<<9)|(1<<8));
    	gpio_setto_high(cn_gpio_c, (1<<4));
    	djy_event_delay(500*mS);

    	gpio_setto_low(cn_gpio_c, (1<<9)|(1<<4)|(1<<8));
    	gpio_setto_high(cn_gpio_c, (1<<6));
    	djy_event_delay(500*mS);
    }
}
void led_flash1(void)
{
    void *my_para;
    while(1)
    {
        my_para = djy_get_event_para(NULL);
        switch(*(u32*)my_para)
        {
            case 1:
            	gpio_setto_low(cn_gpio_c, (1<<4)|(1<<6)|(1<<8));
            	gpio_setto_high(cn_gpio_c, (1<<9));
                break;
            case 2:
            	gpio_setto_low(cn_gpio_c, (1<<4)|(1<<6)|(1<<9));
            	gpio_setto_high(cn_gpio_c, (1<<8));
               break;
            case 3:
            	gpio_setto_low(cn_gpio_c, (1<<6)|(1<<9)|(1<<8));
            	gpio_setto_high(cn_gpio_c, (1<<4));
                break;
            case 4:
            	gpio_setto_low(cn_gpio_c, (1<<9)|(1<<4)|(1<<8));
            	gpio_setto_high(cn_gpio_c, (1<<6));
                break;
            default:break;
        }
		djy_echo_para(0);
        //执行本句后，事件将被阻塞，由于被同步的事件类型就是本事件的事件类型，
        //所以同步条件就是：再次发生本类型事件。
        //参数 ‘1’表示只要发生一次事件就可以了
        //参数500表示如果一直不发生，500mS后结束等待
        //关于事件类型弹出同步，参见《都江堰操作系统与嵌入式系统设计》的第5.3节
        djy_wait_evtt_pop(djy_my_evtt_id(),1,0xfffffffe);
    }
}
uint16_t evtt_led;
uint16_t event_led;
void led_init(void)
{
    gpio_power_on(cn_gpio_c);
    gpio_cfg_pin_func(cn_gpio_c, 6, cn_gpio_mode_gpio_out_pp_2Mhz);
    gpio_cfg_pin_func(cn_gpio_c, 4, cn_gpio_mode_gpio_out_pp_2Mhz);
    gpio_cfg_pin_func(cn_gpio_c, 8, cn_gpio_mode_gpio_out_pp_2Mhz);
    gpio_cfg_pin_func(cn_gpio_c, 9, cn_gpio_mode_gpio_out_pp_2Mhz);

	evtt_led = djy_evtt_regist(enum_independence, cn_prio_RRS, 0, 1, 1, 
                                led_flash1, 100, "hello led");
	if (evtt_led != cn_invalid_evtt_id)
	{
		event_led = djy_event_pop(evtt_led, NULL, 0, NULL, 0, 0, 0);
	}
}

#if (cfg_gui_kernel == 1)
extern u8 pat_white[128];
extern u8 pat_black[128];
void djy_main(void)
{
    djyfs_file *fp;
	static char *banner_text = "---- DJYOS ----";
	static struct gkwin_rsc wnd_body, wnd_bodymsk, wnd_body_selector;
	static struct gkwin_rsc wnd_banner, wnd_bottom;
	static struct gkwin_rsc wnd_body_flip, wnd_body_main;
	s32 flip_x = 0, flip_y = 192, flip_inc = 2;
	s32 main_x = 240, main_y = 160, main_inc = -2;
    struct gkwin_rsc *desktop;
    struct input_device_msg *input_msg;
    struct st_rect_bitmap bitmap;
    u32 r=0;
    s32 touch_x=0, touch_y=0;
    u8 alpha = 0x80;
    
    run_module_init();
    led_init();

    desktop = gk_api_get_desktop("ili9325");

    // banner
    gk_api_create_gkwin(desktop, &wnd_banner, 0, 0, 240, 25,
    		cn_color_blue, cn_winbuf_buf, "banner", cn_r3_srccopy, 0);
    gk_api_draw_text(&wnd_banner, 60, 5,
    		banner_text, strnlen(banner_text, 100), 0);

    // body
    gk_api_create_gkwin(desktop, &wnd_body, 0, 30, 240, 290,
    		cn_color_red, cn_winbuf_buf, "body", cn_r3_srccopy, 0);
    gk_api_create_gkwin(&wnd_body, &wnd_body_selector, 0, 0, 240, 20,
    		cn_color_red+cn_color_green, cn_winbuf_buf, "body selector",
    		cn_r3_srccopy, 0);
    gk_api_lineto(&wnd_body_selector, 60, 0, 60, 20,
    		cn_color_black, cn_r2_copypen, 0);
    gk_api_lineto(&wnd_body_selector, 120, 0, 120, 20,
    		cn_color_black, cn_r2_copypen, 0);
    gk_api_lineto(&wnd_body_selector, 180, 0, 180, 20,
    		cn_color_black, cn_r2_copypen, 0);

    fp = djyfs_fopen("sys:\\logo.bmp","r+");
    if (fp)
    {
		bitmap.bm_bits = m_malloc(105600, 0);
		djyfs_fread(bitmap.bm_bits, 105600, 1, fp);
		bitmap.width = 220;
		bitmap.height = 240;
		bitmap.linebytes = 440;
		bitmap.pf_type = cn_sys_pf_r5g6b5;

		gk_api_draw_bitmap(&wnd_body, &bitmap, 10, 20, cn_timeout_forever);
		m_free(bitmap.bm_bits);
		djyfs_fclose(fp);
    }

    gk_api_create_gkwin(&wnd_body, &wnd_bodymsk, 0, 20, 240, 192,
    		cn_color_blue, cn_winbuf_buf, "body mask", cn_r3_srccopy, 0);
	gk_api_set_rop_code(&wnd_bodymsk, NULL, cn_rop_ext_en+cn_rop_alpha_en+alpha, 0);

    gk_api_create_gkwin(&wnd_body, &wnd_body_main, main_x, main_y, main_x+64, main_y+64,
    		cn_color_white, cn_winbuf_buf, "main", cn_r3_srccopy, 0);
    gk_api_create_gkwin(&wnd_body, &wnd_body_flip, flip_x, flip_y, flip_x+32, flip_y+32,
    		cn_color_red, cn_winbuf_buf, "flip", cn_r3_srccopy, 0);
    // 窗口贴图
    fp = djyfs_fopen("sys:\\tree.bmp","r+");
    if (fp)
    {
		bitmap.bm_bits = m_malloc(8192, 0);
		djyfs_fread(bitmap.bm_bits, 8192, 1, fp);
		bitmap.width = 64;
		bitmap.height = 64;
		bitmap.linebytes = 128;
		bitmap.pf_type = cn_sys_pf_r5g6b5;

		gk_api_draw_bitmap(&wnd_body_main, &bitmap, 0, 0, cn_timeout_forever);
		m_free(bitmap.bm_bits);
		djyfs_fclose(fp);
    }

    fp = djyfs_fopen("sys:\\pear.bmp","r+");
    if (fp)
    {
		bitmap.bm_bits = m_malloc(2048, 0);
		djyfs_fread(bitmap.bm_bits, 2048, 1, fp);
		bitmap.width = 32;
		bitmap.height = 32;
		bitmap.linebytes = 64;
		bitmap.pf_type = cn_sys_pf_r5g6b5;

		gk_api_draw_bitmap(&wnd_body_flip, &bitmap, 0, 0, cn_timeout_forever);
		gk_api_set_rop_code(&wnd_body_flip,NULL,cn_rop_transparentcolor+cn_rop_ext_en,0);
		gk_api_set_transparentcolor(&wnd_body_flip, cn_color_white);
		m_free(bitmap.bm_bits);
		djyfs_fclose(fp);
    }

	bitmap.bm_bits = pat_white;
	bitmap.width = 8;
	bitmap.height = 8;
	bitmap.linebytes = 16;
	bitmap.pf_type = cn_sys_pf_r5g6b5;
    gk_api_set_pat_buf(&wnd_body_main,&bitmap,cn_timeout_forever);

    // bottom
    gk_api_create_gkwin(desktop, &wnd_bottom, 0, 295, 240, 320,
    		cn_color_blue, cn_winbuf_buf, "bottom", cn_r3_srccopy, 0);

    gk_api_fill_win(desktop, cn_color_black, cn_timeout_forever);	// 背景涂黑

	stdin_set_focus_default(djy_my_evtt_id());
	r = 5;
    for ( ; ; )
    {
        input_msg = (struct input_device_msg *)djy_get_event_para(NULL);
        if(input_msg != NULL)
        {
            if(input_msg->input_type == enum_stdin_single_touch)
        	{
        		touch_x = input_msg->input_data.single_touch_msg.x;
        		touch_y = input_msg->input_data.single_touch_msg.y;

        		gk_api_set_rop_code(&wnd_bodymsk, NULL,
        				cn_rop_ext_en+cn_rop_alpha_en+alpha, 0);
        		alpha -= 0x20;
        		gk_api_fill_win(&wnd_bodymsk, (touch_y<<16) + (touch_y<<4), 0);
        	}else if(input_msg->input_type == enum_stdin_keyboard)//查看是否键盘
        	{
                //按键松开才确认，因此先判断是否断码
                if(input_msg->input_data.key_board.key_value[1] == cn_break_code)
                {
                    u32 parameter;
                    djy_printf("\n\rkey value: %d",input_msg->input_data.key_board.key_value[0]);
                    parameter = input_msg->input_data.key_board.key_value[0];
                    djy_event_pop(event_led, NULL, 0, &parameter, sizeof(u32), 0, 0);
                }
        	}
            djy_echo_para(0);
        }

		// 窗口移动
		flip_x += flip_inc;
		if (flip_x <= 0)
		{
			flip_inc = 2;
		}
		if (flip_x >= 240)
		{
			flip_inc = -2;
		}

		main_x += main_inc;
		if (main_x <= 0)
		{
			main_inc = 2;
		}
		if (main_x >= 240)
		{
			main_inc = -2;
		}

		gk_api_move_win(&wnd_body_main, main_x, main_y, 0);
		gk_api_move_win(&wnd_body_flip, flip_x, flip_y, cn_timeout_forever);

        dis_wnd_bottom_text(&wnd_bottom);

        djy_wait_evtt_pop(djy_my_evtt_id(),1,100*mS);
    }
}
#else
void djy_main(void)
{
    led_init();

    for ( ; ; )
    {
        djy_wait_evtt_pop(djy_my_evtt_id(), 1, 5000*mS);
    }

}
#endif

u8 pat_white[128] = 
{
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};

u8 pat_black[128] = 
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

