//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//版权所有 (C), 2004-2009,   罗侍田.
//所属模块:标准输入--触摸屏模块
//作者:  罗侍田.
//版本：V1.1.0
//文件描述: 触摸屏设备驱动程序
//其他说明:
//修订历史:
//1. 日期: 2009-01-04
//   作者:  罗侍田.
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------

#include "os_inc.h"

#if (cfg_single_touch == 1)

#include "Touch.h"
#include "string.h"

//----触摸屏扫描任务-----------------------------------------------------------
//功能: 周期性地调用硬件扫描程序，获取用户用户触摸信息，并把获得的信息输入到标准
//      输入缓冲区(调用函数stdin_input_msg)，注意，抬起触摸笔后，还要发送一条触
//      摸笔离开的信息
//参数: my_event，键盘服务事件类型。
//返回: 无
//----------------------------------------------------------------------------
void touch_scan(void)
{
    struct stdin_device_rsc *touch_rsc,*stdin_rsc;
    struct single_touch_private *touch_pr;
    struct single_touch_msg touch_temp = {0,0,0,0};

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
            if(touch_rsc->input_type != enum_stdin_single_touch)
                continue;
            touch_pr = (struct single_touch_private*)touch_rsc->stdin_private;
            if(touch_pr->read_touch(&touch_temp) != 0)
            {
                if((touch_temp.x != touch_pr->touch_loc.x)
                    ||(touch_temp.y != touch_pr->touch_loc.y)
                    ||(touch_temp.z != touch_pr->touch_loc.z))
                {
                    touch_temp.time = djy_get_time_tick();
                    stdin_input_msg(touch_rsc->device_id,(u8*)&touch_temp,
                                                        sizeof(touch_temp));
                    touch_pr->touch_loc = touch_temp;
                    touch_pr->status = true;
                }
            }
            else
            {
                if(touch_pr->status == true)
                {
                    touch_pr->touch_loc.time = djy_get_time_tick();
                    touch_pr->touch_loc.z = 0;
                    stdin_input_msg(touch_rsc->device_id,
                                    (u8*)&touch_pr->touch_loc,
                                    sizeof(touch_pr->touch_loc));
                    touch_pr->status = false;
                }
            }
        }
        djy_event_delay(10*mS);
    }
}

s32 touch_install_device(char *touch_name,struct single_touch_private *touch_pr)
{
    if(!stdin_install_device(touch_name, enum_stdin_single_touch, touch_pr))
        return -1;
    touch_pr->status = false;
    return 0;
}
//----初始化触摸屏模块---------------------------------------------------------
//功能: 初始化触摸屏模块，包括:安装触摸屏标准输入设备；登记触摸屏扫描事件
//      类型；pop触摸屏扫描事件以启动扫描(实际扫描工作要等多线程启动后才开始)
//参数: 无
//返回: 0=失败，1=成功
//----------------------------------------------------------------------------
ptu32_t module_init_touch(ptu32_t para)
{
    s16 touch_scan_evtt;
    if(!rsc_search_tree("stdin input device"))      //标准输入设备未初始化
        return 0;
    touch_scan_evtt = djy_evtt_regist(enum_correlative,cn_prio_real,0,0,1,
                            touch_scan,1024,"touch");
    if(touch_scan_evtt == cn_invalid_evtt_id)
    {
        return 0;
    }
    if(djy_event_pop(touch_scan_evtt, NULL,0,NULL,0,0,0)
                        == (uint16_t)cn_invalid_event_id)
    {
        djy_evtt_unregist(touch_scan_evtt);
        return 0;
    }
    return 1;
}

#endif  //for #if (cfg_single_touch == 1)
