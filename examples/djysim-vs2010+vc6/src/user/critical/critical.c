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
	cn_int_line_timer_event,
    cn_int_line_switch_context,
    cn_int_line_cmd,
};

const ufast_t ufg_int_used_num = sizeof(tg_int_used)/sizeof(ufast_t);
//�����ж��߿������ݽṹ
struct int_line tg_int_table[sizeof(tg_int_used)/sizeof(ufast_t)];

void critical(void)
{
}
struct int_line *djy_get_int_table()
{
    return tg_int_table;

}
ufast_t djy_get_int_sued_num()
{
    return ufg_int_used_num;
}


