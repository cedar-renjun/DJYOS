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

#include "os_inc.h"

#if (cfg_single_touch == 1)

#include "Touch.h"
#include "string.h"

//----������ɨ������-----------------------------------------------------------
//����: �����Եص���Ӳ��ɨ����򣬻�ȡ�û��û�������Ϣ�����ѻ�õ���Ϣ���뵽��׼
//      ���뻺����(���ú���stdin_input_msg)��ע�⣬̧�����ʺ󣬻�Ҫ����һ����
//      �����뿪����Ϣ
//����: my_event�����̷����¼����͡�
//����: ��
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
//----��ʼ��������ģ��---------------------------------------------------------
//����: ��ʼ��������ģ�飬����:��װ��������׼�����豸���ǼǴ�����ɨ���¼�
//      ���ͣ�pop������ɨ���¼�������ɨ��(ʵ��ɨ�蹤��Ҫ�ȶ��߳�������ſ�ʼ)
//����: ��
//����: 0=ʧ�ܣ�1=�ɹ�
//----------------------------------------------------------------------------
ptu32_t module_init_touch(ptu32_t para)
{
    s16 touch_scan_evtt;
    if(!rsc_search_tree("stdin input device"))      //��׼�����豸δ��ʼ��
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
