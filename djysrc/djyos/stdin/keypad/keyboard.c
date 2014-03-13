//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//��Ȩ���� (C), 2004-2009,   ������.
//����ģ��:����
//����:  ������.
//�汾��V1.1.0
//�ļ�����: �ṩ�����豸�����ܵĹ������֣���ֲ��Ҫ�޸ĵļ�key_xxx.c�ļ�
//����˵��:
//�޶���ʷ:
//3. ����:20120324
//   ����:  ������.
//   �°汾�ţ�v1.1.0
//   �޸�˵��:
//      1.�����µ�stdinģ��Ҫ����д
//      2.����key_read������key_read_direct����
//2. ����:20090131
//   ����:  ������.
//   �°汾�ţ�v1.1.0
//   �޸�˵��:
//      1.��Ӳ����صĺ���key_scan_hard�Ƶ�key_xxx.c��.
//      2.����key_read������key_read_direct����
//1. ����: 2009-01-04
//   ����:  ������.
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------
#include "os_inc.h"

#if cfg_keyboard == 1

void key_scan(void);
//----��ʼ������ģ��----------------------------------------------------------
//����: ��ʼ������ģ�飬����:��װ���̱�׼�����豸���ǼǼ���ɨ���¼�
//      ���ͣ�pop����ɨ���¼�������ɨ��(ʵ��ɨ�蹤��Ҫ�ȶ��߳�������ſ�ʼ)
//����: ��
//����: 0=ʧ�ܣ�1=�ɹ�
//----------------------------------------------------------------------------
ptu32_t module_init_keyboard(ptu32_t para)
{
    s16 evtt_key;
    if(!rsc_search_tree("stdin input device"))      //��׼�����豸δ��ʼ��
        return 0;
    evtt_key = djy_evtt_regist(enum_correlative,cn_prio_RRS,0,0,1,
                                    key_scan,512,"keyboard");
    if(evtt_key == cn_invalid_evtt_id)
    {
        stdin_uninstall_device("key board");
        return 0;
    }
    if(djy_event_pop(evtt_key,NULL,0,NULL,0,0,0) 
                        == (uint16_t)cn_invalid_event_id)
    {
        djy_evtt_unregist(evtt_key);
        return 0;
    }
    return 1;
}

//----��װ����-----------------------------------------------------------------
//����: ��Ӳ������������ã�������ʼ�����������豸���ɰ�װ��������豸
//����: 
//����: 
//-----------------------------------------------------------------------------
s32 key_install_device(char *keyboard_name,struct keyboard_private *keyboard_pr)
{
    if(!stdin_install_device(keyboard_name, enum_stdin_keyboard, keyboard_pr))
        return -1;
    else
        return 0;
}

//----����ɨ������-------------------------------------------------------------
//����: �����Եص���Ӳ��ɨ����򣬻�ȡ�û��û���Ϣ���ϳɱ�׼�����룬�͵���׼
//      �����豸�С�ɨ���������ֲ�ͬ�����ͣ�ͨ��(make code)�Ͷ���(break code)��
//      ��һ���������»������סʱ,�Ͳ���һ��ͨ��;����һ�������ͷ�ʱ,�Ͳ���һ��
//      ���롣ÿ�������������ֽ���ɣ�ͨ��Ϊ0+���룬����Ϊ0xF0+���롣����ֵ����
//      windows��������룬��A��,ͨ��Ϊ0x00,0x41,����Ϊ0xF0��0x41��
//����: ��
//����: ��
//----------------------------------------------------------------------------
void key_scan(void)
{
    struct stdin_device_rsc *touch_rsc,*stdin_rsc;
    struct keyboard_private *keyboard_pr;
    struct keyboard_msg key_msg;
    u32 keyvalue;

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
            if(touch_rsc->input_type != enum_stdin_keyboard)
                continue;
            keyboard_pr = (struct keyboard_private*)touch_rsc->stdin_private;
            keyvalue = keyboard_pr->read_keyboard();
			if(keyvalue != keyboard_pr->key_now)
            {
                keyboard_pr->key_now = keyvalue;
                keyboard_pr->vtime_count = 0;
            }
            else
            {
                if(keyboard_pr->vtime_count < keyboard_pr->vtime_limit)
                    keyboard_pr->vtime_count += 10;
            }

            if((keyboard_pr->key_bak != keyboard_pr->key_now)
                && (keyboard_pr->vtime_count >= keyboard_pr->vtime_limit))
            {
                u32 loop;
                u8 key,key_byte[4];
                //��ע: �˴����ʹ��union������������ֲ�Ե����⡣
                key_byte[0] = keyboard_pr->key_bak & 0xff;
                key_byte[1] = (keyboard_pr->key_bak >> 8) & 0xff;
                key_byte[2] = (keyboard_pr->key_bak >> 16) & 0xff;
                key_byte[3] = (keyboard_pr->key_bak >> 24) & 0xff;
                for(loop = 0; loop < 4; loop++)
                {
                    key = (keyboard_pr->key_now >> (loop<<3)) & 0xff;
                    if(key == 0)
                        continue;
                    //�鿴�ǲ����°��µİ���
                    if((key_byte[0] != key)
                        && (key_byte[1] != key)
                        && (key_byte[2] != key)
                        && (key_byte[3] != key) )
                    {
                        
                        key_msg.time = djy_get_time_tick();
                        key_msg.key_value[1] = 0;
                        key_msg.key_value[0] = key;
                        stdin_input_msg(touch_rsc->device_id,
                                            (u8*)&key_msg,sizeof(key_msg));
                    }
                }

                //��ע: �˴����ʹ��union������������ֲ�Ե����⡣
                key_byte[0] = keyboard_pr->key_now & 0xff;
                key_byte[1] = (keyboard_pr->key_now >> 8) & 0xff;
                key_byte[2] = (keyboard_pr->key_now >> 16) & 0xff;
                key_byte[3] = (keyboard_pr->key_now >> 24) & 0xff;
                for(loop = 0; loop < 4; loop++)
                {
                    key = (u8)(keyboard_pr->key_bak >> (loop<<3)) & 0xff;
                    if(key == 0)
                        continue;
                    //�鿴��û�а����ͷ�
                    if((key_byte[0] != key)
                        && (key_byte[1] != key)
                        && (key_byte[2] != key)
                        && (key_byte[3] != key) )
                    {
                        
                        key_msg.time = djy_get_time_tick();
                        key_msg.key_value[1] = cn_break_code;
                        key_msg.key_value[0] = key;
                        stdin_input_msg(touch_rsc->device_id,
                                            (u8*)&key_msg,sizeof(key_msg));
                    }
                }
                keyboard_pr->key_bak = keyboard_pr->key_now;
            }
        }
        djy_event_delay(10*mS);
    }
}

#endif   //for #if cfg_keyboard == 1

