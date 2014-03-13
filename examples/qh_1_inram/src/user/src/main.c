#include "os_inc.h"
#include "gk_api.h"
#include "cpu_peri.h"
#include "gpio_api.h"
#include <string.h>


void led_flash(void)
{
    while(1)
    {
    	gpio_setto_low(cn_gpio_c, (1<<4)|(1<<6)|(1<<8));
    	gpio_setto_high(cn_gpio_c, (1<<9));
    	djy_event_delay(500*mS);

    	gpio_setto_low(cn_gpio_c, (1<<4)|(1<<6)|(1<<9));
    	gpio_setto_high(cn_gpio_c, (1<<8));
    	djy_event_delay(500*mS);

    	gpio_setto_low(cn_gpio_c, (1<<6)|(1<<9)|(1<<8));
    	gpio_setto_high(cn_gpio_c, (1<<4));
    	djy_event_delay(500*mS);

    	gpio_setto_low(cn_gpio_c, (1<<9)|(1<<4)|(1<<8));
    	gpio_setto_high(cn_gpio_c, (1<<6));
    	djy_event_delay(500*mS);
    }
}

void led_init(void)
{
	uint16_t evtt_led;

    gpio_power_on(cn_gpio_c);
    gpio_cfg_pin_func(cn_gpio_c, 6, cn_gpio_mode_gpio_out_pp_2Mhz);
    gpio_cfg_pin_func(cn_gpio_c, 4, cn_gpio_mode_gpio_out_pp_2Mhz);
    gpio_cfg_pin_func(cn_gpio_c, 8, cn_gpio_mode_gpio_out_pp_2Mhz);
    gpio_cfg_pin_func(cn_gpio_c, 9, cn_gpio_mode_gpio_out_pp_2Mhz);

	evtt_led = djy_evtt_regist(enum_correlative, cn_prio_RRS, 0, 1, 1, led_flash, 100, "hello led");
	if (evtt_led != cn_invalid_evtt_id)
	{
		djy_event_pop(evtt_led, NULL, 0, NULL, 0, 0, 0);
	}
}

void djy_main(void)
{
    led_init();
}
