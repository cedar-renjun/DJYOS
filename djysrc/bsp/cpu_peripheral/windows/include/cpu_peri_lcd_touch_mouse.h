#ifndef __CPU_PERI_LCD_TOUCH_H__
#define __CPU_PERI_LCD_TOUCH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "os_inc.h"
#include "arch.h"
#define cn_lcd_xsize        320
#define cn_lcd_ysize        240
#define cn_lcd_line_size    (cn_lcd_xsize*2)

#define cn_lcd_pf       cn_sys_pf_r5g6b5

void __lcd_envid_of(int );
void __lcd_power_enable(int ,int );
void __lcd_hard_init(void);
bool_t __lcd_set_pixel_screen(s32 x,s32 y,u32 color,u32 rop2_code);
ptu32_t module_init_lcd(ptu32_t para);
ptu32_t module_init_touch_windows(ptu32_t para);

#ifdef __cplusplus
}
#endif

#endif   //__CPU_PERI_LCD_TOUCH_H__

