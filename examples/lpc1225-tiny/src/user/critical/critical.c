//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//��Ȩ���� (C), 2004-2009,   ������.
//����ģ��:��ȫ����
//����:  ������.
//�汾��V1.0.0
//�ļ�����:��ȫ�����Ǳ����ڿ����󾡿��ܿ��ִ�еĲ��ִ���
//����˵��:
//�޶���ʷ:
//2. ...
//1. ����: 2009-01-04
//   ����:  ������.
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------
#include "os_inc.h"
#include "cpu_peri.h"
const ufast_t tg_int_used[] =
{
    cn_int_line_adc,
    cn_int_line_uart0,
    cn_int_line_uart1,
    cn_int_line_wdt,
    cn_int_line_rtc,
	cn_int_line_timer32_0,
	cn_int_line_wakeup0

};

const ufast_t ufg_int_used_num = sizeof(tg_int_used)/sizeof(ufast_t);
//�����ж��߿������ݽṹ
struct int_line tg_int_table[sizeof(tg_int_used)/sizeof(ufast_t)];
void critical(void)
{
 //   PublicPinmuxInit();        //������ִ��,��ΪӲ���ĳ�ʼ״̬���ܹغ���ȫ
}

