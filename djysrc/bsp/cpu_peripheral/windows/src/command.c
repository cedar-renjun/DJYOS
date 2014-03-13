//----------------------------------------------------
//Copyright (C), 2004-2011,  ������.
//��Ȩ���� (C), 2004-2011,   ������.
//����ģ��:windowsģ���ַ�����ģ��
//����:  ������
//�汾��V1.0.0
//�ļ�����: ��ȡwindows�����������룬��Ϊdjyos���ַ���������豸����djyos�����
//          �ն˵��ַ������windows��cmd����
//����˵��:
//�޶���ʷ:
// 1. ����: 2012-10-09
//   ����:  ������
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------
#include "os_inc.h"
#include "cpu_peri.h"
#include "windows.h"
#include "stdio.h"
 
#define cmd_buf_len  1024

HANDLE win32_scanf;

char cmd_ptcl_recv_buf[cmd_buf_len];
static djy_handle_t pg_cmd_rhdl;
struct ring_buf recv_ring_buf;           //���ν��ջ�����.
char scanf_buf[cmd_buf_len-2];

struct semaphore_LCB *pg_recv_buf_semp;     //���ջ�������

u16 u16g_evtt_right_write;      //�豸���ֱ�д�󵯳����¼�����

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

//----��ʼ���������豸---------------------------------------------------------
//����: ����
//����: ��
//����: ������
//-----------------------------------------------------------------------------
ptu32_t module_init_cmd(ptu32_t para)
{
    struct semaphore_LCB *left_semp,*right_semp;
    struct  pan_device   *cmd_dev;
    
    pg_recv_buf_semp = semp_create(1,0,"cmd rx buf");
    if(pg_recv_buf_semp == NULL)
        goto exit_from_right_buf_semp;
    //�ֱ𴴽����ֺ����ַ����ַ��豸���ź�������һ������Ϊ1��ʾ�����Ƕ�ռ����
    //�ģ��ڶ�������1��ʾ��ʼ״̬��һյ�źŵƵ�����������Ӧ�ó���ʹ�ã�������Ӳ
    //����������ʹ�á�
    left_semp = semp_create(1,1,"cmd device left");
    if(left_semp == NULL)
        goto exit_from_left_semp;
    right_semp = semp_create(1,1,"cmd device right");
    if(right_semp == NULL)
        goto exit_from_right_semp;

    ring_init(  &recv_ring_buf,
                cmd_ptcl_recv_buf,
                cmd_buf_len);

    //���½���windows �ն������豸
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
    pg_cmd_rhdl = dev_open_right("windows_cmd",0);      //�����־��
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

//----�ַ������豸����д����---------------------------------------------------
//����: ������д��uart�豸,��uart�豸���ӵĴ���ģ�����.
//      1.������д�봮��serial_DCB_t�Ļ��η��ͻ�������.
//      2.���д���豸������δ�ﵽ����ˮƽ��������ռ�����
//      3.�ﵽ����ˮƽ�󣬰��趨�ķ�ʽ�����ݴ��ݸ��ϲ��豸
//����: uart_dev,���������豸������ָ��.
//      buf������Դָ�롣
//      len��������(bytes)
//����: ʵ��д�뻷�λ��������ַ���
//-----------------------------------------------------------------------------
ptu32_t cmd_hard_write(struct  pan_device *cmd_dev,ptu32_t buf,
                            ptu32_t res2,ptu32_t len)
{
    u16 recv_bytes;

    //copy����Ӳ����������Э�黺����
    recv_bytes = ring_write(&recv_ring_buf, (u8*)buf,len);
    djy_event_pop(u16g_evtt_right_write,NULL,0,NULL,0,0,0);

    return (ptu32_t)recv_bytes;
}

//----uart�豸����д����-------------------------------------------------------
//����: ������д��uart�豸,һ����uart��ʹ���ߵ���.
//      1.������д�봮��serial_DCB_t�Ļ��η��ͻ�������.
//      2.�������Ӳ������,�������д��Ӳ�����ͻ�����,����������,���򲻲���
//����: uart_dev,���������豸������ָ��.
//      src_buf,����Դָ��
//      len,Ҫ���͵����г���
//����: ʵ��д�뻷�λ��������ַ���
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


//----�����豸���ֶ�����------------------------------------------------------
//����: ���ֶ������ϲ��豸,��ȡ���ڽ��ջ��λ�����������
//����: uart_dev,���������豸������ָ��.
//      dst_buf,��������
//      len,���볤��,
//����: ʵ�ʶ�������
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

//----�����豸���ƺ���---------------------------------------------------------
//����: �����豸�Ŀ��ƺ���
//����: uart_handle,�������Ĵ����豸ָ��.
//      cmd,��������
//      data,������cmd����
//����: ������.
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

