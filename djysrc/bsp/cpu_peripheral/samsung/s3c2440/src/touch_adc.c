/*
 * adc.c
 *
 *  Created on: 2012-9-6
 *      Author: 逍遥派掌门人
 *      ADC组件
 */

#include <string.h>
#include "os_inc.h"
#include "cpu_peri.h"

#define LOOP 1

extern struct int_reg volatile * const pg_int_reg;
volatile struct adc_port_cb adc_port;

void  ClearPending(u32 bit)
{
  pg_int_reg->SRCPND = bit;
  pg_int_reg->INTPND = bit;
}

//----ADC硬件初始化-------------------------------------------------------
//功能: ADC硬件初始化
//参数：无
//返回：无
//-----------------------------------------------------------------------
void adc_init_hard(void)
{
        // 硬件端口设置
        pg_gpio_reg->GPGCON |= 0xff000000;
        pg_gpio_reg->GPGUP  &= 0x0f;

        // ADC 启动，中断的延时
        pg_adc_reg->ADCDLY = 50000;

        // Enable Prescaler,Prescaler,AIN7/5 fix,Normal,Disable read start,No operation
        pg_adc_reg->ADCCON=(1<<14)|(ADCPRS<<6)|(0<<3)|(0<<2)|(0<<1)|(0);

        // Down,YM:GND,YP:AIN5,XM:Hi-z,XP:AIN7,XP pullup En,Normal,Waiting for interrupt mode
        pg_adc_reg->ADCTSC=(0<<8)|(1<<7)|(1<<6)|(0<<5)|(1<<4)|(0<<3)|(0<<2)|(3);

}


// ADC中断引用的函数
u32 adc_isr(ufast_t uart_int_line)
{
        u8 i;
        u32 PtX[5], PtY[5];

  adc_port.touch_over=0;    // 没有触摸

  pg_int_reg->INTSUBMSK |= (BIT_SUB_ADC_S|BIT_SUB_TC);

     if(pg_adc_reg->ADCDAT0 & 0x8000)
     {//抬起
         adc_port.isdown = 0;
         pg_adc_reg->ADCTSC &= 0xff;  // Set stylus down interrupt
         adc_port.location_x = -1;
         adc_port.location_y = -1; //抬起触笔时，X,Y要置成不大于0的数
     }
     else //按下
     {
         adc_port.isdown = 1;

         pg_adc_reg->ADCTSC =(0<<8)|(0<<7)|(0<<6)|(1<<5)|(1<<4)|(1<<3)|(0<<2)|(1);

         for(i=0;i<LOOP;i++);            //delay to set up the next channel
         for(i=0;i<5;i++)                           //5 times
         {
             pg_adc_reg->ADCCON |= 0x1;               // Start X-position conversion
             while(pg_adc_reg->ADCCON & 0x1);       // Check if Enable_start is low
             while(!(0x8000 & pg_adc_reg->ADCCON));   // Check ECFLG
             PtX[i]=(0x3ff & pg_adc_reg->ADCDAT0);
         }

         adc_port.location_x=(PtX[0]+PtX[1]+PtX[2]+PtX[3]+PtX[4])/5;//多次采样取平均值

         pg_adc_reg->ADCTSC =(0<<8)|(0<<7)|(1<<6)|(1<<5)|(0<<4)|(1<<3)|(0<<2)|(2);

         for(i=0;i<LOOP;i++);            //delay to set up the next channel

         for(i=0;i<5;i++)                           //5 times
         {
             pg_adc_reg->ADCCON |=0x1;               // Start Y-position conversion
             while(pg_adc_reg->ADCCON & 0x1);       // Check if Enable_start is low
             while(!(0x8000 & pg_adc_reg->ADCCON));   // Check ECFLG
             PtY[i]=(0x3ff & pg_adc_reg->ADCDAT1);
         }
         adc_port.location_y =(PtY[0]+PtY[1]+PtY[2]+PtY[3]+PtY[4])/5;// 多次采样取平均值

         pg_adc_reg->ADCTSC = (1<<8)|(1<<7)|(1<<6)|(0<<5)|(1<<4)|(0<<3)|(0<<2)|(3);


        }


     if( pg_int_reg->SUBSRCPND & (BIT_SUB_TC))    //check if ADC is finished with interrupt bit
              {
                  adc_port.touch_over = 1;
              }


  //    djy_printf("adc x: %d , y: %d  , over: %d",adc_port.location_x,adc_port.location_y,adc_port.touch_over);

     pg_int_reg->SUBSRCPND |= BIT_SUB_TC;
     pg_int_reg->INTSUBMSK &= ~(BIT_SUB_TC);         // Unmask sub interrupt (TC)
     ClearPending(BIT_ADC);

  return 1;
}

//----读取触摸点坐标-----------------------------------------------------------
//功能: 读取采集到的ADC值
//参数: 无
//返回: 转换的触摸点坐标
// 逍遥派掌门人
//-----------------------------------------------------------------------------
ufast_t read_touch_adc(struct single_touch_msg *touch_data)
{
     if (adc_port.touch_over==1)
     {
        //touch_data->x = TOUCH_WIDTH * (TOUCH_DEFAULT_RB - adc_port.location_x) / (TOUCH_DEFAULT_RB - TOUCH_DEFAULT_LB);
       // touch_data->y = TOUCH_HEIGHT * (adc_port.location_y - TOUCH_DEFAULT_TB) / (TOUCH_DEFAULT_BB - TOUCH_DEFAULT_TB);

       touch_data->x = TOUCH_WIDTH * (adc_port.location_y - TOUCH_DEFAULT_LB) / (TOUCH_DEFAULT_RB - TOUCH_DEFAULT_LB);

        touch_data->y = TOUCH_HEIGHT * (adc_port.location_x - TOUCH_DEFAULT_TB) / (TOUCH_DEFAULT_BB - TOUCH_DEFAULT_TB);


        touch_data->z=0;

    //    djy_printf("\n\rtouch : %4d   %4d ",touch_data->x,touch_data->y);
     }
        return 1;
}

//----初始化触摸屏模块---------------------------------------------------------
//功能: 
//参数: display_name,本触摸屏对应的显示器名(资源名)
//返回: 无
//-----------------------------------------------------------------------------
ptu32_t module_init_touch_adc(ptu32_t para)
{
    static struct single_touch_private touch_adc;
    adc_init_hard();                          // 硬件初始化

    if (pg_int_reg->SRCPND & BIT_ADC)
        {pg_int_reg->SRCPND    |= BIT_ADC;}

    if (pg_int_reg->INTPND & BIT_ADC)
        {pg_int_reg->INTPND    |= BIT_ADC;}

    if (pg_int_reg->SUBSRCPND & BIT_SUB_TC)
        {pg_int_reg->SUBSRCPND |= BIT_SUB_TC;}

    if (pg_int_reg->SUBSRCPND & BIT_SUB_ADC_S)
        {pg_int_reg->SUBSRCPND |= BIT_SUB_ADC_S;}

    pg_int_reg->INTSUBMSK &=~(BIT_SUB_TC);

    // pg_int_reg->PRIORITY=1;                 // 设置ADC中断的优先级

    int_isr_connect(cn_int_line_adc,adc_isr);  // 挂接ADC中断

    int_setto_asyn_signal(cn_int_line_adc);
    int_echo_line(cn_int_line_adc);
    int_restore_asyn_line(cn_int_line_adc);

    //      int_setto_real(cn_int_line_adc);          //cn_int_line_adc中断被设为实时中断
    touch_adc.read_touch = read_touch_adc;
    touch_install_device("touch_adc",&touch_adc);
    return 1;
}

