//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//��Ȩ���� (C), 2004-2009,   ������.
//����ģ��:��׼����--������ģ��
//����:  ������.
//�汾��V1.1.0
//�ļ�����: �������豸��������
//����˵��:
//�޶���ʷ:
//1. ����: 2009-01-04
//   ����:  ������.
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------
#if (cfg_single_touch == 1)

#ifndef TOUCH_H_
#define TOUCH_H_

#ifdef __cplusplus
extern "C" {
#endif

struct st_touch_adjust
{
    s32 ratio_x,ratio_y;        //����С������16λ��С��λ��
    s32 offset_x,offset_y;       //����С������16λ��С��λ��
};

struct single_touch_private
{
    ufast_t (*read_touch)(struct single_touch_msg *touch_data);
    struct single_touch_msg touch_loc;
    bool_t status;
};

s32 touch_install_device(char *touch_name,struct single_touch_private *touch_pr);

void touch_scan(void);
ptu32_t module_init_touch(ptu32_t para);

#ifdef __cplusplus
}
#endif

#endif /* TOUCH_H_ */


#endif  //for #if (cfg_single_touch == 1)

