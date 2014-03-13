//----------------------------------------------------
//Copyright (C), 2004-2009,  lst.
//��Ȩ���� (C), 2004-2009,   lst.
//����ģ��:����
//���ߣ�lst
//�汾��V1.0.0
//�ļ�����: ɨ��Ӳ��������������ֻ��ֱ�Ӹ���������ǰֵ�����������
//����˵��:
//�޶���ʷ:
//2. ����: 2009-05-29
//   ����: lst
//   �°汾��: V1.1.0
//   �޸�˵��: ����key_hard_init����
//1. ����: 2009-03-10
//   ����: lst
//   �°汾��: V1.0.0
//   �޸�˵��: ԭʼ�汾
//------------------------------------------------------
#include "os_inc.h"
#include "cpu_peri.h"
#include "gpio_api.h"

bool_t key_hard_init(void);
u32 keyboard_scan(void);
//----��ʼ������ģ��-----------------------------------------------------------
//����: ��ʼ��һ����windows�ļ��̺Ͱ�ťģ��ļ��̣��ü��̹�8������
//����: ��
//����: ��
//-----------------------------------------------------------------------------
ptu32_t module_init_keyboard_hard(ptu32_t para)
{
    static struct keyboard_private windows_keyboard;
    key_hard_init();
    windows_keyboard.read_keyboard = keyboard_scan;
    key_install_device("keyboard driver",&windows_keyboard);
    windows_keyboard.vtime_limit = para;
    windows_keyboard.vtime_count = 100;
    windows_keyboard.key_bak = 0;
    windows_keyboard.key_now = 0;
    return 1;
}


//----��ʼ������Ӳ��-----------------------------------------------------------
//����: ���⣬��ʼ�������ɨ�����
//����: ��
//����: ��
//----------------------------------------------------------------------------
bool_t key_hard_init(void)
{
    gpio_power_on(cn_gpio_c);
    gpio_cfg_pin_func(cn_gpio_c,10,cn_gpio_mode_in_pullup);
    gpio_cfg_pin_func(cn_gpio_c,11,cn_gpio_mode_in_pullup);
    gpio_cfg_pin_func(cn_gpio_c,12,cn_gpio_mode_in_pullup);
    gpio_cfg_pin_func(cn_gpio_c,13,cn_gpio_mode_in_pullup);
    return true;
}

//----����Ӳ��ɨ��------------------------------------------------------------
//����: ��4����,�ɶ��븴�ϼ������2��������,key0=gpf0,
//      key1=gpf2,key2=gpg3,key3=gpg11
//����: key,��ֵ����ָ��,�ɴ��2������ֵ
//����: �����ļ��ĸ���0,1,2
//----------------------------------------------------------------------------
u32 keyboard_scan(void)
{
    u32 readed;
    uint8_t i = 0;
    u32 reg;
    
    readed = 0;
    reg = gpio_get_data(cn_gpio_c);
    if( ! (reg & 0x0400))
    {
        readed |= (u32)(4<<(i<<3));
        i++;
    }
    if( ! (reg & 0x0800))
    {
        readed |= (u32)(3<<(i<<3));
        i++;
    }
    if( ! (reg & 0x1000))
    {
        readed |= (u32)(2<<(i<<3));
        i++;
    }
    if( ! (reg & 0x2000))
    {
        readed |= (u32)(1<<(i<<3));
        i++;
    }
    return(readed);
}

