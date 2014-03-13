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
	cn_int_line_timer_event,
    cn_int_line_switch_context,
    cn_int_line_cmd,
};

const ufast_t ufg_int_used_num = sizeof(tg_int_used)/sizeof(ufast_t);
//定义中断线控制数据结构
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


