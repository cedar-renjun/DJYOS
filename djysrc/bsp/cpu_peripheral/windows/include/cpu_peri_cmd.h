//----------------------------------------------------
//Copyright (C), 2004-2011,  罗侍田.
//版权所有 (C), 2004-2011,   罗侍田.
//所属模块:时钟模块
//作者:  罗侍田
//版本：V1.0.0
//文件描述: 命令行输入输出
//其他说明:
//修订历史:
// 1. 日期: 2012-10-09
//   作者:  罗侍田
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#ifndef __CPU_PERI_CMD_H__
#define __CPU_PERI_CMD_H__
                   
#ifdef __cplusplus
extern "C" {
#endif
#include "windows.h"

#define     cn_cmd_connect_recv_evtt    0
#define     cn_cmd_disconnect_recv_evtt 1

u32 cmd_int(ufast_t uart_int_line);
u32 WINAPI win32_scanf_pro( LPVOID lpParameter );
ptu32_t module_init_cmd(ptu32_t para);
ptu32_t cmd_hard_write(struct  pan_device *cmd_dev,ptu32_t buf,
                            ptu32_t res2,ptu32_t len);
ptu32_t cmd_app_write(struct  pan_device *cmd_dev,ptu32_t src_buf,
                            ptu32_t res,ptu32_t len);
ptu32_t cmd_app_read(struct  pan_device *uart_dev,ptu32_t res,
                                        ptu32_t dst_buf,ptu32_t len);
ptu32_t cmd_ctrl(struct pan_device *uart_dev,u32 cmd,
                   u32 data1,u32 data2);
                   
#ifdef __cplusplus
}
#endif
                   
#endif /*__CPU_PERI_CMD_H__*/

