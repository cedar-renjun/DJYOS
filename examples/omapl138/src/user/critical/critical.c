//----------------------------------------------------
//Copyright (C), 2004-2009,  luoshitian.
//版权所有 (C), 2004-2009,   罗侍田.
//所属模块:安全钩子
//作者:  罗侍田.
//版本：V1.0.0
//文件描述:安全钩子是必须在开机后尽可能快地执行的部分代码
//其他说明:
//修订历史:
//2. ...
//1. 日期: 2009-01-04
//   作者:  罗侍田.
//   新版本号: V1.0.0
//   修改说明: 原始版本
//------------------------------------------------------
#include "os_inc.h"
#include "gpio_api.h"
#include "cpu_peri.h"

#define vx_load_address 0x60100000
#define dsp_load_address 0x60300000

const ufast_t tg_int_used[] =
{
    cn_int_line_commtx          ,
    cn_int_line_commrx          ,
    cn_int_line_nint            ,
    cn_int_line_pru_ev0         ,
    cn_int_line_pru_ev1         ,
    cn_int_line_pru_ev2         ,
    cn_int_line_pru_ev3         ,
    cn_int_line_pru_ev4         ,
    cn_int_line_pru_ev5         ,
    cn_int_line_pru_ev6         ,
    cn_int_line_pru_ev7         ,
    cn_int_line_edma3_0_cc0     ,
    cn_int_line_edma3_0_cc0_err ,
    cn_int_line_edma3_0_tc0_err ,
    cn_int_line_emifa           ,
    cn_int_line_iic0            ,
    cn_int_line_mmcsd0_int0     ,
    cn_int_line_mmcsd0_int1     ,
    cn_int_line_psc0_allint     ,
    cn_int_line_rtc_irqs10      ,
    cn_int_line_spi0            ,
    cn_int_line_t64p0_tint12    ,
    cn_int_line_t64p0_tint34    ,
    cn_int_line_t64p1_tint12    ,
    cn_int_line_t64p1_tint34    ,
    cn_int_line_uart0           ,
    cn_int_line_reserved1       ,
    cn_int_line_proterr         ,
    cn_int_line_sfg_chip0       ,
    cn_int_line_sfg_chip1       ,
    cn_int_line_sfg_chip2       ,
    cn_int_line_sfg_chip3       ,
    cn_int_line_edma3_0_tc1_err ,
    cn_int_line_emac_c0rxthresh ,
    cn_int_line_emac_c0rx       , 
    cn_int_line_emac_c0tx       ,
    cn_int_line_emac_c0misc     ,
    cn_int_line_emac_c1rxthresh ,
    cn_int_line_emac_c1rx       ,
    cn_int_line_emac_c1tx       ,
    cn_int_line_c1misc          ,
    cn_int_line_memerr          ,
    cn_int_line_gpiob0          ,
    cn_int_line_gpiob1          ,
    cn_int_line_gpiob2          ,
    cn_int_line_gpiob3          ,
    cn_int_line_gpiob4          ,
    cn_int_line_gpiob5          ,
    cn_int_line_gpiob6          ,
    cn_int_line_gpiob7          ,
    cn_int_line_gpiob8          ,
    cn_int_line_iic1            ,
    cn_int_line_lcdc            ,
    cn_int_line_uart1           ,
    cn_int_line_mcasp           ,
    cn_int_line_psc1_allint     ,
    cn_int_line_spi1            ,
    cn_int_line_uhpi_arm        ,
    cn_int_line_usb0            ,
    cn_int_line_usb1_hc         ,
    cn_int_line_usb1_r_wakeup   ,
    cn_int_line_uart2           ,
    cn_int_line_reserved2       ,
    cn_int_line_ehrpwm0         ,
    cn_int_line_ehrpwm0tz       ,
    cn_int_line_ehrpwm1         ,
    cn_int_line_ehrpwm1tz       ,
    cn_int_line_sata            ,
    cn_int_line_t64p2_all       ,
    cn_int_line_ecap0           ,
    cn_int_line_ecap1           ,
    cn_int_line_ecap2           ,
    cn_int_line_mmcad1_int0     ,
    cn_int_line_mmcsd1_int1     ,
    cn_int_line_t64p0_cmp0      ,
    cn_int_line_t64p0_cmp1      ,
    cn_int_line_t64p0_cmp2      ,
    cn_int_line_t64p0_cmp3      ,
    cn_int_line_t64p0_cmp4      ,
    cn_int_line_t64p0_cmp5      ,
    cn_int_line_t64p0_cmp6      ,
    cn_int_line_t64p0_cmp7      ,
    cn_int_line_t64p1_cmp0      ,
    cn_int_line_t64p1_cmp1      ,
    cn_int_line_t64p1_cmp2      ,
    cn_int_line_t64p1_cmp3      ,
    cn_int_line_t64p1_cmp4      ,
    cn_int_line_t64p1_cmp5      ,
    cn_int_line_t64p1_cmp6      ,
    cn_int_line_t64p1_cmp7      ,
    cn_int_line_armclkstopreq   ,
    cn_int_line_upp_all         ,
    cn_int_line_vpif_all        ,
    cn_int_line_edma3_1_cc0     ,
    cn_int_line_edma3_1_cc0_err ,
    cn_int_line_edma3_1_tc0_err ,
    cn_int_line_t64p3_all       ,
    cn_int_line_mcbsp0_r        ,
    cn_int_line_mcbsp0_x        ,
    cn_int_line_mcbsp1_r        ,
    cn_int_line_mcbsp1_x        
};

const ufast_t ufg_int_used_num = sizeof(tg_int_used)/sizeof(ufast_t);
//定义中断线控制数据结构
struct int_line tg_int_table[sizeof(tg_int_used)/sizeof(ufast_t)];

void __asm_hot_restart(void );

void start_dsp(void)
{
    volatile u32 i;
    void (*start_address)(void);
    start_address = Dcore_LoadAisCode((u8*)dsp_load_address,NULL);
    if(start_address != NULL)
        Dcore_WakeupDspRun(start_address);
    else 
    {
        start_address  = Dcore_LoadTiBinCode((u8*)dsp_load_address,NULL);
        if(start_address != NULL)
            Dcore_WakeupDspRun(start_address);
        else
            Dcore_WakeupDspReset();
    }
}

//----配置全部IO扣--------------------------------------------------------------
//功能：除必须的外，全部配置成初始态，各功能口由相应的功能模块自行定义。
//参数：无
//返回：无
//------------------------------------------------------------------------------
void gpio_init(void)
{
    gpio_power_on(0);       //port0.10 = D10 port0.11 = D11
    gpio_power_on(7);       //port7.1 = D2
    gpio_power_on(2);       //boot mode,0=诊断，1=运行

    gpio_cfg_pin_func(0,10,cn_p0_10_gpio0_10);
    gpio_cfg_pin_func(7,1,cn_p7_1_gpio7_1);
    gpio_cfg_pin_func(2,0,cn_p2_0_gpio2_0);
    
    gpio_setto_out(0,0x400);
    gpio_setto_out(7,0x02);
    gpio_setto_in(2,0x01);
    
    gpio_setto_high(0,0x400);
    gpio_setto_high(7,0x2);
}

void critical(void)
{
    u32 i;
    *(u32*)0xc037fff8 = (u32)__asm_hot_restart;
    gpio_init();        //建议早执行,因为硬件的初始状态可能关乎安全
    if(Cpucfg_TestLPSC(cn_PSC0_DSP) == PlscPowerOff)
    	start_dsp();
    
}

