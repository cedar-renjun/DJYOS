//----------------------------------------------------
//Copyright (C), 2004-2011,  ������.
//��Ȩ���� (C), 2004-2011,   ������.
//����ģ��:ʱ��ģ��
//����:  ������
//�汾��V1.0.0
//�ļ�����: �������������
//����˵��:
//�޶���ʷ:
// 1. ����: 2012-10-09
//   ����:  ������
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
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

