//----------------------------------------------------
//Copyright (C), 2004-2009,  lst.
//��Ȩ���� (C), 2004-2009,   lst.
//����ģ��:��ȫ����
//���ߣ�lst
//�汾��V1.0.0
//�ļ�����:��ȫ�����Ǳ����ڿ����󾡿��ܿ��ִ�еĲ��ִ���
//����˵��:
//�޶���ʷ:
//2. ...
//1. ����: 2009-01-04
//   ����: lst
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
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
//�����ж��߿������ݽṹ
struct int_line tg_int_table[sizeof(tg_int_used)/sizeof(ufast_t)];

void critical(void)
{
    gpio_init();        //������ִ��,��ΪӲ���ĳ�ʼ״̬���ܹغ���ȫ
}
struct int_line *djy_get_int_table()
{
    return tg_int_table;

}
ufast_t djy_get_int_sued_num()
{
    return ufg_int_used_num;
}


