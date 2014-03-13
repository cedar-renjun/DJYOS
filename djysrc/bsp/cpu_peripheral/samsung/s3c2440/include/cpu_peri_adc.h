/*
 * cpu_peri_adc.h
 *
 *  Created on: 2012-9-6
 *      Author: 逍遥派掌门人
 *      ADC组件的头文件
 */

#ifndef CPU_PERI_ADC_H_
#define CPU_PERI_ADC_H_

#ifdef __cplusplus
extern "C"
{
#endif


#include "os_inc.h"


// ADCCON寄存器
#define PRESCALE_DIS   (0 << 14)
#define PRESCALE_EN    (1 << 14)
#define PRSCVL(x)      ((x) << 6)
#define ADC_INPUT(x)   ((x) << 3)
#define ADC_START      (1 << 0)
#define ADC_ENDCVT     (1 << 15)

// ADCTSC寄存器
#define UD_SEN         (1 << 8)
#define DOWN_INT       (UD_SEN*0)
#define UP_INT         (UD_SEN*1)
#define YM_SEN         (1 << 7)
#define YM_HIZ         (YM_SEN*0)
#define YM_GND         (YM_SEN*1)
#define YP_SEN         (1 << 6)
#define YP_EXTVLT      (YP_SEN*0)
#define YP_AIN         (YP_SEN*1)
#define XM_SEN         (1 << 5)
#define XM_HIZ         (XM_SEN*0)
#define XM_GND         (XM_SEN*1)
#define XP_SEN         (1 << 4)
#define XP_EXTVLT      (XP_SEN*0)
#define XP_AIN         (XP_SEN*1)
#define XP_PULL_UP     (1 << 3)
#define XP_PULL_UP_EN  (XP_PULL_UP*0)
#define XP_PULL_UP_DIS (XP_PULL_UP*1)
#define AUTO_PST       (1 << 2)
#define CONVERT_MAN    (AUTO_PST*0)
#define CONVERT_AUTO   (AUTO_PST*1)
#define XP_PST(x)      (x << 0)

#define NOP_MODE 0
#define X_AXIS_MODE 1
#define Y_AXIS_MODE 2
#define WAIT_INT_MODE 3


#define ADCPRS 39

#define BIT_ADC        (0x1<<31)
#define BIT_SUB_ADC_S  (0x1<<10)
#define BIT_SUB_TC     (0x1<<9)

struct adc_reg
{
        u32 ADCCON;   //0x58000000
        u32 ADCTSC;   //0x58000004
        u32 ADCDLY;   //0x58000008
        u32 ADCDAT0;  //0x5800000c
        u32 ADCDAT1;  //0x58000010
};


//ADC状态控制结构
struct adc_port_cb
{
   u32 location_x;    // X 坐标值
   u32 location_y;    // Y 坐标值
   u8  isdown;        // 抬起，还是按下，按下为1
   u8  touch_over;    // 是否触摸完成
};

ptu32_t module_init_adc(ptu32_t para);

void  ClearPending(u32 bit);

#ifdef __cplusplus
}
#endif

#endif /* CPU_PERI_ADC_H_ */
