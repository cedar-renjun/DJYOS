//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//��Ȩ���� (C), 2004-2009,   ������.
//����ģ��:��׼����--��������ģ��
//����:  ������.
//�汾��V1.1.0
//�ļ�����: ��������
//����˵��:
//�޶���ʷ:
//1. ����: 2009-01-04
//   ����:  ������.
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------

#if (cfg_keyboard== 1)

#ifndef __KEY_HARD_H__
#define __KEY_HARD_H__

#ifdef __cplusplus
extern "C" {
#endif

//�������壬�ο�����windows���������
#define CN_KeyValueUp       38
#define CN_KeyValueDown     40
#define CN_KeyValueLeft     37
#define CN_KeyValueRight    39
#define CN_KeyValueEnter    13
#define CN_KeyValueRetrun   27
#define CN_KeyValueF1       112
#define CN_KeyValueF2       113


ptu32_t module_init_keyboard_hard(ptu32_t para);

#ifdef __cplusplus
}
#endif

#endif /* __KEY_HARD_H__ */

#endif  //for #if (cfg_single_touch == 1)

