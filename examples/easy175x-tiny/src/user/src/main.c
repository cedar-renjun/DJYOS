#include "os_inc.h"
#include "gpio_api.h"
#include "uart_tiny.h"
#include "cpu_peri.h"
void run_module_init(void);

void flash_led(void)
{
    u32 out = 0;
    gpio_power_on(0);
    gpio_cfg_pin_func(2,0,cn_p2_0_gpio);
    gpio_cfg_pin_func(2,1,cn_p2_1_gpio);
    gpio_cfg_pin_func(2,2,cn_p2_2_gpio);
    gpio_cfg_pin_func(2,3,cn_p2_3_gpio);
    gpio_setto_out(2,0x0f);                 //����0~3λΪ�����
    while(1)
    {
        out++;
        if(out == 4)
            out = 0;
        gpio_setto_low(2,1<<out);
        gpio_setto_high(2,0xf & ~(1<<out));

        djy_event_delay(500*mS);
    }
}

//��Ӧ����Ϊmain�ģ�������������Ĭ�����������������ڵ㣬����
void djy_main(void)
{
    uint16_t evtt_flash_led;
    u32 parameter;
    u16 i;
    u16 buf[512];
    run_module_init();

    evtt_flash_led = djy_evtt_regist(enum_correlative,cn_prio_RRS,0,0,
                                        1,flash_led,10,NULL);
    parameter = 1;
    djy_event_pop(evtt_flash_led,NULL,0,&parameter,
                    sizeof(parameter),false,0);

    uart_set_baud(1,6000000);
//    uart0_send("djyos welcome,�����߲���ϵͳ\n\r",30);
#if 1
    while(1)
    {
//        uart1_read((char*)buf,512,cn_timeout_forever);
        for(i = 0; i<256;i++)
        {
            if(buf[i] != i)
            {
                break;
            }
        }
//        if(i == 256)
//        	uart0_send("ok\n\r",4);
//        else
//            uart0_send("err\n\r",5);
//        uart1_send("end",3);
    }
#endif
#if 1
    while(1)
    {
        for(i = 0; i<256;i++)
        {
            buf[i] = i;
        }
        uart1_send((char*)buf,512);
//        uart1_read((u8*)buf,3,cn_timeout_forever);
    }

#endif
}    
