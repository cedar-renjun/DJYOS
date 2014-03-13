#include "os_inc.h"
#include "gpio_api.h"
#include "uart_tiny.h"
#include "cpu_peri.h"
void run_module_init(void);

void djy_main(void)
{
    run_module_init();

}    
