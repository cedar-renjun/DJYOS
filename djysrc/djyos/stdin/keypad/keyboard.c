//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//版权所有 (C), 2004-2009,   罗侍田.
//所属模块:键盘
//作者:  罗侍田.
//版本：V1.1.0
//文件描述: 提供键盘设备管理功能的公共部分，移植需要修改的见key_xxx.c文件
//其他说明:
//修订历史:
//3. 日期:20120324
//   作者:  罗侍田.
//   新版本号：v1.1.0
//   修改说明:
//      1.按照新的stdin模块要求重写
//      2.增加key_read函数和key_read_direct函数
//2. 日期:20090131
//   作者:  罗侍田.
//   新版本号：v1.1.0
//   修改说明:
//      1.把硬件相关的函数key_scan_hard移到key_xxx.c中.
//      2.增加key_read函数和key_read_direct函数
//1. 日期: 2009-01-04
//   作者:  罗侍田.
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#include "os_inc.h"

#if cfg_keyboard == 1

void key_scan(void);
//----初始化键盘模块----------------------------------------------------------
//功能: 初始化键盘模块，包括:安装键盘标准输入设备；登记键盘扫描事件
//      类型；pop键盘扫描事件以启动扫描(实际扫描工作要等多线程启动后才开始)
//参数: 无
//返回: 0=失败，1=成功
//----------------------------------------------------------------------------
ptu32_t module_init_keyboard(ptu32_t para)
{
    s16 evtt_key;
    if(!rsc_search_tree("stdin input device"))      //标准输入设备未初始化
        return 0;
    evtt_key = djy_evtt_regist(enum_correlative,cn_prio_RRS,0,0,1,
                                    key_scan,512,"keyboard");
    if(evtt_key == cn_invalid_evtt_id)
    {
        stdin_uninstall_device("key board");
        return 0;
    }
    if(djy_event_pop(evtt_key,NULL,0,NULL,0,0,0) 
                        == (uint16_t)cn_invalid_event_id)
    {
        djy_evtt_unregist(evtt_key);
        return 0;
    }
    return 1;
}

//----安装键盘-----------------------------------------------------------------
//功能: 由硬件驱动程序调用，用来初始化键盘输入设备，可安装多个输入设备
//参数: 
//返回: 
//-----------------------------------------------------------------------------
s32 key_install_device(char *keyboard_name,struct keyboard_private *keyboard_pr)
{
    if(!stdin_install_device(keyboard_name, enum_stdin_keyboard, keyboard_pr))
        return -1;
    else
        return 0;
}

//----键盘扫描任务-------------------------------------------------------------
//功能: 周期性地调用硬件扫描程序，获取用户敲击信息，合成标准键盘码，送到标准
//      输入设备中。扫描码有两种不同的类型：通码(make code)和断码(break code)。
//      当一个键被按下或持续按住时,就产生一个通码;而当一个键被释放时,就产生一个
//      断码。每个按键由两个字节组成，通码为0+键码，断码为0xF0+键码。键码值参照
//      windows的虚拟键码，如A键,通码为0x00,0x41,断码为0xF0，0x41。
//参数: 无
//返回: 无
//----------------------------------------------------------------------------
void key_scan(void)
{
    struct stdin_device_rsc *touch_rsc,*stdin_rsc;
    struct keyboard_private *keyboard_pr;
    struct keyboard_msg key_msg;
    u32 keyvalue;

    stdin_rsc = (struct stdin_device_rsc *)rsc_search_tree("stdin input device");
    while(1)
    {
        touch_rsc = stdin_rsc;
        while(1)
        {
            touch_rsc = (struct stdin_device_rsc*)
                            rsc_trave_scion(&stdin_rsc->stdin_device_node,
                                            &touch_rsc->stdin_device_node);
            if(touch_rsc == NULL)
                break;
            if(touch_rsc->input_type != enum_stdin_keyboard)
                continue;
            keyboard_pr = (struct keyboard_private*)touch_rsc->stdin_private;
            keyvalue = keyboard_pr->read_keyboard();
			if(keyvalue != keyboard_pr->key_now)
            {
                keyboard_pr->key_now = keyvalue;
                keyboard_pr->vtime_count = 0;
            }
            else
            {
                if(keyboard_pr->vtime_count < keyboard_pr->vtime_limit)
                    keyboard_pr->vtime_count += 10;
            }

            if((keyboard_pr->key_bak != keyboard_pr->key_now)
                && (keyboard_pr->vtime_count >= keyboard_pr->vtime_limit))
            {
                u32 loop;
                u8 key,key_byte[4];
                //特注: 此处如果使用union，将带来可移植性的问题。
                key_byte[0] = keyboard_pr->key_bak & 0xff;
                key_byte[1] = (keyboard_pr->key_bak >> 8) & 0xff;
                key_byte[2] = (keyboard_pr->key_bak >> 16) & 0xff;
                key_byte[3] = (keyboard_pr->key_bak >> 24) & 0xff;
                for(loop = 0; loop < 4; loop++)
                {
                    key = (keyboard_pr->key_now >> (loop<<3)) & 0xff;
                    if(key == 0)
                        continue;
                    //查看是不是新按下的按键
                    if((key_byte[0] != key)
                        && (key_byte[1] != key)
                        && (key_byte[2] != key)
                        && (key_byte[3] != key) )
                    {
                        
                        key_msg.time = djy_get_time_tick();
                        key_msg.key_value[1] = 0;
                        key_msg.key_value[0] = key;
                        stdin_input_msg(touch_rsc->device_id,
                                            (u8*)&key_msg,sizeof(key_msg));
                    }
                }

                //特注: 此处如果使用union，将带来可移植性的问题。
                key_byte[0] = keyboard_pr->key_now & 0xff;
                key_byte[1] = (keyboard_pr->key_now >> 8) & 0xff;
                key_byte[2] = (keyboard_pr->key_now >> 16) & 0xff;
                key_byte[3] = (keyboard_pr->key_now >> 24) & 0xff;
                for(loop = 0; loop < 4; loop++)
                {
                    key = (u8)(keyboard_pr->key_bak >> (loop<<3)) & 0xff;
                    if(key == 0)
                        continue;
                    //查看有没有按键释放
                    if((key_byte[0] != key)
                        && (key_byte[1] != key)
                        && (key_byte[2] != key)
                        && (key_byte[3] != key) )
                    {
                        
                        key_msg.time = djy_get_time_tick();
                        key_msg.key_value[1] = cn_break_code;
                        key_msg.key_value[0] = key;
                        stdin_input_msg(touch_rsc->device_id,
                                            (u8*)&key_msg,sizeof(key_msg));
                    }
                }
                keyboard_pr->key_bak = keyboard_pr->key_now;
            }
        }
        djy_event_delay(10*mS);
    }
}

#endif   //for #if cfg_keyboard == 1

