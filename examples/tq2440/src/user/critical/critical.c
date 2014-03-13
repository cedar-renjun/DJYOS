//----------------------------------------------------
//Copyright (C), 2004-2009,  lst.
//版权所有 (C), 2004-2009,   lst.
//所属模块:安全钩子
//作者：lst
//版本：V1.0.0
//文件描述:安全钩子是必须在开机后尽可能快地执行的部分代码
//其他说明:
//修订历史:
//2. ...
//1. 日期: 2009-01-04
//   作者: lst
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#include "os_inc.h"
#include "cpu_peri.h"
const ufast_t tg_int_used[] =
{
    cn_int_line_eint0,
    cn_int_line_eint1,
    cn_int_line_eint2,
    cn_int_line_eint3,
    cn_int_line_eint4_7,
    cn_int_line_eint8_23,
    cn_int_line_resv6,
    cn_int_line_bat_flt,
    cn_int_line_tick,
    cn_int_line_wdt,
    cn_int_line_timer0,
    cn_int_line_timer1,
    cn_int_line_timer2,
    cn_int_line_timer3,
    cn_int_line_timer4,
    cn_int_line_uart2,
    cn_int_line_lcd,
    cn_int_line_dma0,
    cn_int_line_dma1,
    cn_int_line_dma2,
    cn_int_line_dma3,
    cn_int_line_sdi,
    cn_int_line_spi0,
    cn_int_line_uart1,
    cn_int_line_resv24,
    cn_int_line_usbd,
    cn_int_line_usbh,
    cn_int_line_iic,
    cn_int_line_uart0,
    cn_int_line_spi1,
    cn_int_line_rtc,
    cn_int_line_adc,
};

const ufast_t ufg_int_used_num = sizeof(tg_int_used)/sizeof(ufast_t);
//定义中断线控制数据结构
struct int_line tg_int_table[sizeof(tg_int_used)/sizeof(ufast_t)];

void critical(void)
{
    gpio_init();        //建议早执行,因为硬件的初始状态可能关乎安全
}
struct int_line *djy_get_int_table()
{
    return tg_int_table;

}
ufast_t djy_get_int_sued_num()
{
    return ufg_int_used_num;
}


