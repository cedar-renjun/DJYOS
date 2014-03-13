//----------------------------------------------------
//Copyright (C), 2004-2009,  lst.
//版权所有 (C), 2004-2009,   lst.
//所属模块:中断模块
//作者：lst
//版本：V1.0.0
//文件描述: 定义中断号
//其他说明:
//修订历史:
//2. ...
//1. 日期: 2009--9-28
//   作者: lst
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#ifndef __int_line_h__
#define __int_line_h__

#ifdef __cplusplus
extern "C" {
#endif

#define cn_int_line_timer_event     (0)     //用于tick中断
#define cn_int_line_switch_context  (1)     //用于切换上下文
#define cn_int_line_cmd             (2)
#define cn_int_line_last            (2)

#define cn_int_msk_all_line   (0xffffffff)

#ifdef __cplusplus
}
#endif

#endif //__int_line_h__

