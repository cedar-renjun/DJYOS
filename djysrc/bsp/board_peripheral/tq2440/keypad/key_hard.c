//----------------------------------------------------
//Copyright (C), 2004-2009,  lst.
//版权所有 (C), 2004-2009,   lst.
//所属模块:键盘
//作者：lst
//版本：V1.0.0
//文件描述: 扫描硬件读按键函数，只需直接给出按键当前值，无须防抖。
//其他说明:
//修订历史:
//2. 日期: 2009-05-29
//   作者: lst
//   新版本号: V1.1.0
//   修改说明: 增加key_hard_init函数
//1. 日期: 2009-03-10
//   作者: lst
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#include "os_inc.h"
#include "cpu_peri.h"

bool_t key_hard_init(void);
u32 keyboard_scan(void);
//----初始化键盘模块-----------------------------------------------------------
//功能: 初始化一个由windows的键盘和按钮模拟的键盘，该键盘供8个键。
//参数: 无
//返回: 无
//-----------------------------------------------------------------------------
ptu32_t module_init_keyboard_hard(ptu32_t para)
{
    static struct keyboard_private windows_keyboard;
    key_hard_init();
    windows_keyboard.read_keyboard = keyboard_scan;
    key_install_device("keyboard driver",&windows_keyboard);
    windows_keyboard.vtime_limit = para;
    windows_keyboard.vtime_count = 100;
    windows_keyboard.key_bak = 0;
    windows_keyboard.key_now = 0;
    return 1;
}


//----初始化键盘硬件-----------------------------------------------------------
//功能: 如题，初始化后才能扫描键盘
//参数: 无
//返回: 无
//----------------------------------------------------------------------------
bool_t key_hard_init(void)
{
    pg_gpio_reg->GPFCON &= 0xfffffcc0;
    return true;
}


//----键盘硬件扫描------------------------------------------------------------
//功能: 读取键盘按键状态，每个按键用8bit表示，32位返回值可以存放4个按键。扫描到
//      的第一个按键放在最低8位，第四个按键放在最高8位。扫描到4个按键后，不再继
//      续，若同时按下超过4个按键，只记录4个。
//参数: key,键值数组指针,可存放2个单键值
//返回: 读到的键的个数0,1,2
//----------------------------------------------------------------------------
u32 keyboard_scan(void)
{
    u32 readed;
    uint8_t i = 0;

    readed = 0;
    if( ! (pg_gpio_reg->GPFDAT & 1))
    {
        readed |= (u32)(1<<(i<<3));
        i++;
    }
    if( ! (pg_gpio_reg->GPFDAT & 0x2))
    {
        readed |= (u32)(2<<(i<<3));
        i++;
    }
    if( ! (pg_gpio_reg->GPFDAT & 0x4))
    {
        readed |= (u32)(3<<(i<<3));
        i++;
    }
    if( ! (pg_gpio_reg->GPFDAT & 0x10))
    {
        readed |= (u32)(4<<(i<<3));
        i++;
    }
    return(readed);
}

