//----------------------------------------------------
//Copyright (C), 2004-2011,  罗侍田.
//版权所有 (C), 2004-2011,   罗侍田.
//所属模块:windows模拟字符输入模块
//作者:  罗侍田
//版本：V1.0.0
//文件描述: 截取windows的命令行输入，作为djyos的字符输入输出设备；把djyos输出到
//          终端的字符输出到windows的cmd窗口
//其他说明:
//修订历史:
// 1. 日期: 2012-10-09
//   作者:  罗侍田
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#include "os_inc.h"
#include "cpu_peri.h"
#include "windows.h"
#include "stdio.h"
 
#define cmd_buf_len  1024

HANDLE win32_scanf;

char cmd_ptcl_recv_buf[cmd_buf_len];
static djy_handle_t pg_cmd_rhdl;
struct ring_buf recv_ring_buf;           //环形接收缓冲区.
char scanf_buf[cmd_buf_len-2];

struct semaphore_LCB *pg_recv_buf_semp;     //接收缓冲区锁

u16 u16g_evtt_right_write;      //设备右手被写后弹出的事件类型

u32 cmd_int(ufast_t uart_int_line)
{
    u32 len;
    len = strlen(scanf_buf);
//    scanf_buf[len] = '\r';
    dev_write_right(pg_cmd_rhdl,(ptu32_t)scanf_buf,0,len);
	return 0;
}

u32 WINAPI win32_scanf_pro( LPVOID lpParameter )
{
	u32 len = 0;
	char ch;
    while(1)
    {
        do
		{
		    scanf("%c",&ch);
			scanf_buf[len] = ch;
			len++;
		}while(ch == '\r');
		scanf_buf[len] = '\0';
		len = 0;
        int_tap_line(cn_int_line_cmd);
    }
}

//----初始化命令行设备---------------------------------------------------------
//功能: 如名
//参数: 无
//返回: 无意义
//-----------------------------------------------------------------------------
ptu32_t module_init_cmd(ptu32_t para)
{
    struct semaphore_LCB *left_semp,*right_semp;
    struct  pan_device   *cmd_dev;
    
    pg_recv_buf_semp = semp_create(1,0,"cmd rx buf");
    if(pg_recv_buf_semp == NULL)
        goto exit_from_right_buf_semp;
    //分别创建左手和右手访问字符设备的信号量，第一个参数为1表示串口是独占访问
    //的，第二个参数1表示初始状态有一盏信号灯点亮。左手由应用程序使用，右手由硬
    //件操作函数使用。
    left_semp = semp_create(1,1,"cmd device left");
    if(left_semp == NULL)
        goto exit_from_left_semp;
    right_semp = semp_create(1,1,"cmd device right");
    if(right_semp == NULL)
        goto exit_from_right_semp;

    ring_init(  &recv_ring_buf,
                cmd_ptcl_recv_buf,
                cmd_buf_len);

    //以下建立windows 终端输入设备
    cmd_dev = dev_add_device(dev_get_root_device(),"windows_cmd",
                               right_semp,left_semp,
                               (dev_write_func) cmd_hard_write,
                               (dev_read_func ) NULL_func,
                               (dev_ctrl_func ) cmd_ctrl,
                               (dev_write_func ) cmd_app_write,
                               (dev_read_func  ) cmd_app_read,
                               (dev_ctrl_func  ) cmd_ctrl,
                               (ptu32_t)0  
                               );
    if(cmd_dev == NULL)
        goto exit_from_add_device;
    pg_cmd_rhdl = dev_open_right("windows_cmd",0);      //打开右手句柄
    int_isr_connect(cn_int_line_cmd,cmd_int);
    int_setto_asyn_signal(cn_int_line_cmd);
    int_restore_asyn_line(cn_int_line_cmd);

    win32_scanf = CreateThread( NULL, 0, win32_scanf_pro, 0,
                                     0, NULL );
    SetThreadAffinityMask( win32_scanf, 1 );
    
    return 1;

exit_from_add_device:
    semp_delete(right_semp);
exit_from_right_semp:
    semp_delete(left_semp);
exit_from_left_semp:
    semp_delete(pg_recv_buf_semp);
exit_from_right_buf_semp:
    return 0;
}

//----字符输入设备右手写函数---------------------------------------------------
//功能: 从右手写入uart设备,由uart设备连接的串口模块调用.
//      1.把数据写入串口serial_DCB_t的环形发送缓冲区中.
//      2.如果写入设备的数据未达到触发水平，则继续收集数据
//      3.达到出发水平后，按设定的方式把数据传递给上层设备
//参数: uart_dev,被操作的设备的右手指针.
//      buf，数据源指针。
//      len，数据量(bytes)
//返回: 实际写入环形缓冲区的字符数
//-----------------------------------------------------------------------------
ptu32_t cmd_hard_write(struct  pan_device *cmd_dev,ptu32_t buf,
                            ptu32_t res2,ptu32_t len)
{
    u16 recv_bytes;

    //copy整个硬件缓冲区到协议缓冲区
    recv_bytes = ring_write(&recv_ring_buf, (u8*)buf,len);
    djy_event_pop(u16g_evtt_right_write,NULL,0,NULL,0,0,0);

    return (ptu32_t)recv_bytes;
}

//----uart设备左手写函数-------------------------------------------------------
//功能: 从左手写入uart设备,一般由uart的使用者调用.
//      1.把数据写入串口serial_DCB_t的环形发送缓冲区中.
//      2.如果串口硬件空闲,便把数据写入硬件发送缓冲区,并启动发送,否则不操作
//参数: uart_dev,被操作的设备的左手指针.
//      src_buf,数据源指针
//      len,要发送的序列长度
//返回: 实际写入环形缓冲区的字符数
//-----------------------------------------------------------------------------
ptu32_t cmd_app_write(struct  pan_device *cmd_dev,ptu32_t src_buf,
                            ptu32_t res,ptu32_t len)
{
    u32 sended;
    u8 *buf;

    if((len==0) || (src_buf == 0))
        return 0;
	buf = (u8*)src_buf;
    for(sended = 0; sended < len; sended++)
        putchar(buf[sended]);
    return sended;
}


//----串口设备左手读函数------------------------------------------------------
//功能: 左手读用于上层设备,读取串口接收环形缓冲区的数据
//参数: uart_dev,被操作的设备的左手指针.
//      dst_buf,读缓冲区
//      len,读入长度,
//返回: 实际读出长度
//----------------------------------------------------------------------------
ptu32_t cmd_app_read(struct  pan_device *uart_dev,ptu32_t res,
                                        ptu32_t dst_buf,ptu32_t len)
{
    u32 result;
    if(dst_buf == 0)
        return 0;
    result = ring_read(&recv_ring_buf,(u8*)dst_buf,len);
    return result;
}

//----串口设备控制函数---------------------------------------------------------
//功能: 串口设备的控制函数
//参数: uart_handle,被操作的串口设备指针.
//      cmd,操作类型
//      data,含义依cmd而定
//返回: 无意义.
//-----------------------------------------------------------------------------
ptu32_t cmd_ctrl(struct pan_device *uart_dev,u32 cmd,
                   u32 data1,u32 data2)
{


    switch(cmd)
    {
        case cn_cmd_connect_recv_evtt:
            u16g_evtt_right_write = (uint16_t)data1;
            break;
        case cn_cmd_disconnect_recv_evtt:
            u16g_evtt_right_write = cn_invalid_evtt_id;
            break;
        default: break;
    }
    return 0;
}

