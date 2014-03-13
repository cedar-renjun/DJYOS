//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//��Ȩ���� (C), 2004-2009,   ������.
//����ģ��:����
//����:  ������.
//�汾��V1.0.0
//�ļ�����: �ṩ�����豸������
//����˵��:
//�޶���ʷ:
//2. ...
//1. ����: 2009-01-04
//   ����:  ������.
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#if cfg_keyboard == 1

#define cn_break_code       0xf0    //���̶���

struct keyboard_private
{
    u32 (*read_keyboard)(void);
    u32 key_bak;
    u32 key_now;
    u32 vtime_limit;        //����ʱ�䣬ms����0�򲻷���,������ϵͳִ�У���������
                            //���ÿ��ǣ�ֻҪ����ϵͳ����ʱ��Ϳ����ˡ�
    u32 vtime_count;        //����������
};

//��������
ptu32_t module_init_keyboard(ptu32_t para);
s32 key_install_device(char *keyboard_name,struct keyboard_private *keyboard_pr);
#endif   //for #if cfg_keyboard == 1

#ifdef __cplusplus
}
#endif

#endif // __KEYBOARD_H__

