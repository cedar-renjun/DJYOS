//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//版权所有 (C), 2004-2009,   罗侍田.
//所属模块:键盘
//作者:  罗侍田.
//版本：V1.0.0
//文件描述: 提供键盘设备管理功能
//其他说明:
//修订历史:
//2. ...
//1. 日期: 2009-01-04
//   作者:  罗侍田.
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#if cfg_keyboard == 1

#define cn_break_code       0xf0    //键盘断码

struct keyboard_private
{
    u32 (*read_keyboard)(void);
    u32 key_bak;
    u32 key_now;
    u32 vtime_limit;        //防抖时间，ms数，0则不防抖,防抖由系统执行，驱动程序
                            //不用考虑，只要告诉系统防抖时间就可以了。
    u32 vtime_count;        //防抖计数器
};

//函数定义
ptu32_t module_init_keyboard(ptu32_t para);
s32 key_install_device(char *keyboard_name,struct keyboard_private *keyboard_pr);
#endif   //for #if cfg_keyboard == 1

#ifdef __cplusplus
}
#endif

#endif // __KEYBOARD_H__

