//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//版权所有 (C), 2004-2009,   罗侍田.
//所属模块:安全钩子
//作者:  罗侍田.
//版本：V1.0.0
//文件描述:安全钩子是必须在开机后尽可能快地执行的部分代码
//其他说明:
//修订历史:
//2. ...
//1. 日期: 2009-01-04
//   作者:  罗侍田.
//   新版本号: V1.0.0
//   修改说明: 原始版本
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
//定义中断线控制数据结构
struct int_line tg_int_table[sizeof(tg_int_used)/sizeof(ufast_t)];
void critical(void)
{
 //   PublicPinmuxInit();        //建议早执行,因为硬件的初始状态可能关乎安全
}

