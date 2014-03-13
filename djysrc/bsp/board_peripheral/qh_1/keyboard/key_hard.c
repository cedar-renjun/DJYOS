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
#include "gpio_api.h"

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
    gpio_power_on(cn_gpio_c);
    gpio_cfg_pin_func(cn_gpio_c,10,cn_gpio_mode_in_pullup);
    gpio_cfg_pin_func(cn_gpio_c,11,cn_gpio_mode_in_pullup);
    gpio_cfg_pin_func(cn_gpio_c,12,cn_gpio_mode_in_pullup);
    gpio_cfg_pin_func(cn_gpio_c,13,cn_gpio_mode_in_pullup);
    return true;
}

//----键盘硬件扫描------------------------------------------------------------
//功能: 共4个键,可读入复合键，最多2个键复合,key0=gpf0,
//      key1=gpf2,key2=gpg3,key3=gpg11
//参数: key,键值数组指针,可存放2个单键值
//返回: 读到的键的个数0,1,2
//----------------------------------------------------------------------------
u32 keyboard_scan(void)
{
    u32 readed;
    uint8_t i = 0;
    u32 reg;
    
    readed = 0;
    reg = gpio_get_data(cn_gpio_c);
    if( ! (reg & 0x0400))
    {
        readed |= (u32)(4<<(i<<3));
        i++;
    }
    if( ! (reg & 0x0800))
    {
        readed |= (u32)(3<<(i<<3));
        i++;
    }
    if( ! (reg & 0x1000))
    {
        readed |= (u32)(2<<(i<<3));
        i++;
    }
    if( ! (reg & 0x2000))
    {
        readed |= (u32)(1<<(i<<3));
        i++;
    }
    return(readed);
}

