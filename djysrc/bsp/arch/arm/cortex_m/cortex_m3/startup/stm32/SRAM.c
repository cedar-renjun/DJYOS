#include "os_inc.h"
#include "cpu_peri.h"
#include "gpio_api.h"
#include "stm32f10x.h"
#include "SRAM.h"


void SRAM_GPIO_Init(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE );
    
    gpio_power_on(cn_gpio_d);
    gpio_power_on(cn_gpio_e);
    gpio_power_on(cn_gpio_f);
    gpio_power_on(cn_gpio_g);
    
    gpio_cfg_pin_func(cn_gpio_d, 14, cn_gpio_mode_peri_out_pp_50Mhz);   //d0
    gpio_cfg_pin_func(cn_gpio_d, 15, cn_gpio_mode_peri_out_pp_50Mhz);   //d1
    gpio_cfg_pin_func(cn_gpio_d, 0, cn_gpio_mode_peri_out_pp_50Mhz);    //d2
    gpio_cfg_pin_func(cn_gpio_d, 1, cn_gpio_mode_peri_out_pp_50Mhz);    //d3
    gpio_cfg_pin_func(cn_gpio_e, 7, cn_gpio_mode_peri_out_pp_50Mhz);    //d4
    gpio_cfg_pin_func(cn_gpio_e, 8, cn_gpio_mode_peri_out_pp_50Mhz);    //d5
    gpio_cfg_pin_func(cn_gpio_e, 9, cn_gpio_mode_peri_out_pp_50Mhz);    //d6
    gpio_cfg_pin_func(cn_gpio_e, 10, cn_gpio_mode_peri_out_pp_50Mhz);   //d7
    gpio_cfg_pin_func(cn_gpio_e, 11, cn_gpio_mode_peri_out_pp_50Mhz);   //d8
    gpio_cfg_pin_func(cn_gpio_e, 12, cn_gpio_mode_peri_out_pp_50Mhz);   //d9
    gpio_cfg_pin_func(cn_gpio_e, 13, cn_gpio_mode_peri_out_pp_50Mhz);   //d10
    gpio_cfg_pin_func(cn_gpio_e, 14, cn_gpio_mode_peri_out_pp_50Mhz);   //d11
    gpio_cfg_pin_func(cn_gpio_e, 15, cn_gpio_mode_peri_out_pp_50Mhz);   //d12
    gpio_cfg_pin_func(cn_gpio_d, 8, cn_gpio_mode_peri_out_pp_50Mhz);    //d13
    gpio_cfg_pin_func(cn_gpio_d, 9, cn_gpio_mode_peri_out_pp_50Mhz);    //d14
    gpio_cfg_pin_func(cn_gpio_d, 10, cn_gpio_mode_peri_out_pp_50Mhz);   //d15

    gpio_cfg_pin_func(cn_gpio_f, 0, cn_gpio_mode_peri_out_pp_50Mhz);    //a0
    gpio_cfg_pin_func(cn_gpio_f, 1, cn_gpio_mode_peri_out_pp_50Mhz);    //a1
    gpio_cfg_pin_func(cn_gpio_f, 2, cn_gpio_mode_peri_out_pp_50Mhz);    //a2
    gpio_cfg_pin_func(cn_gpio_f, 3, cn_gpio_mode_peri_out_pp_50Mhz);    //a3
    gpio_cfg_pin_func(cn_gpio_f, 4, cn_gpio_mode_peri_out_pp_50Mhz);    //a4
    gpio_cfg_pin_func(cn_gpio_f, 5, cn_gpio_mode_peri_out_pp_50Mhz);    //a5
    gpio_cfg_pin_func(cn_gpio_f, 12, cn_gpio_mode_peri_out_pp_50Mhz);   //a6
    gpio_cfg_pin_func(cn_gpio_f, 13, cn_gpio_mode_peri_out_pp_50Mhz);   //a7
    gpio_cfg_pin_func(cn_gpio_f, 14, cn_gpio_mode_peri_out_pp_50Mhz);   //a8
    gpio_cfg_pin_func(cn_gpio_f, 15, cn_gpio_mode_peri_out_pp_50Mhz);   //a9
    gpio_cfg_pin_func(cn_gpio_g, 0, cn_gpio_mode_peri_out_pp_50Mhz);    //a10
    gpio_cfg_pin_func(cn_gpio_g, 1, cn_gpio_mode_peri_out_pp_50Mhz);    //a11
    gpio_cfg_pin_func(cn_gpio_g, 2, cn_gpio_mode_peri_out_pp_50Mhz);    //a12
    gpio_cfg_pin_func(cn_gpio_g, 3, cn_gpio_mode_peri_out_pp_50Mhz);    //a13
    gpio_cfg_pin_func(cn_gpio_g, 4, cn_gpio_mode_peri_out_pp_50Mhz);    //a14
    gpio_cfg_pin_func(cn_gpio_g, 5, cn_gpio_mode_peri_out_pp_50Mhz);    //a15
    gpio_cfg_pin_func(cn_gpio_d, 11, cn_gpio_mode_peri_out_pp_50Mhz);   //a16
    gpio_cfg_pin_func(cn_gpio_d, 12, cn_gpio_mode_peri_out_pp_50Mhz);   //a17
    gpio_cfg_pin_func(cn_gpio_d, 13, cn_gpio_mode_peri_out_pp_50Mhz);   //a18
    gpio_cfg_pin_func(cn_gpio_e, 3, cn_gpio_mode_peri_out_pp_50Mhz);    //a19
    gpio_cfg_pin_func(cn_gpio_e, 4, cn_gpio_mode_peri_out_pp_50Mhz);    //a20
    gpio_cfg_pin_func(cn_gpio_e, 5, cn_gpio_mode_peri_out_pp_50Mhz);    //a21
    
    gpio_cfg_pin_func(cn_gpio_d, 5, cn_gpio_mode_peri_out_pp_50Mhz);    //we
    gpio_cfg_pin_func(cn_gpio_d, 4, cn_gpio_mode_peri_out_pp_50Mhz);    //re
    gpio_cfg_pin_func(cn_gpio_d, 7, cn_gpio_mode_peri_out_pp_50Mhz);    //cs1 for sram
    gpio_cfg_pin_func(cn_gpio_g, 9, cn_gpio_mode_peri_out_pp_50Mhz);    //cs2 for nand
    gpio_cfg_pin_func(cn_gpio_g, 10, cn_gpio_mode_peri_out_pp_50Mhz);   //cs3 for lcd
    gpio_cfg_pin_func(cn_gpio_g, 12, cn_gpio_mode_peri_out_pp_50Mhz);   //cs4 for dm9000a
    

    gpio_cfg_pin_func(cn_gpio_e, 0, cn_gpio_mode_peri_out_pp_50Mhz);    //lb
    gpio_cfg_pin_func(cn_gpio_e, 1, cn_gpio_mode_peri_out_pp_50Mhz);    //ub

}

void SRAM_FSMCConfig(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p;

    /*-- FSMC Configuration ------------------------------------------------------*/
    /*----------------------- SRAM Bank 1 ----------------------------------------*/
      /* FSMC_Bank1_NORSRAM1 configuration */

    p.FSMC_AddressSetupTime = 1;
    p.FSMC_AddressHoldTime = 0;
    p.FSMC_DataSetupTime = 2;
    p.FSMC_BusTurnAroundDuration = 0;
    p.FSMC_CLKDivision = 0;
    p.FSMC_DataLatency = 1;
    p.FSMC_AccessMode = FSMC_AccessMode_A;
    
    /* Color LCD configuration ------------------------------------
       LCD configured as follow:
          - Data/Address MUX = Disable
          - Memory Type = SRAM
          - Data Width = 16bit
          - Write Operation = Enable
          - Extended Mode = Enable
          - Asynchronous Wait = Disable */
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_PSRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    /* BANK1 (of NOR/SRAM Bank) is enabled */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

void LCD_FSMCConfig(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
     FSMC_NORSRAMTimingInitTypeDef  p;
    /*-- FSMC Configuration ------------------------------------------------------*/
    /*----------------------- SRAM Bank 3 ----------------------------------------*/
      /* FSMC_Bank1_NORSRAM3 configuration */
      p.FSMC_AddressSetupTime = 1;
      p.FSMC_AddressHoldTime = 0;
      p.FSMC_DataSetupTime = 2;
      p.FSMC_BusTurnAroundDuration = 0;
      p.FSMC_CLKDivision = 0;
      p.FSMC_DataLatency = 0;
      p.FSMC_AccessMode = FSMC_AccessMode_A;
      /* Color LCD configuration ------------------------------------
         LCD configured as follow:
            - Data/Address MUX = Disable
            - Memory Type = SRAM
            - Data Width = 16bit
            - Write Operation = Enable
            - Extended Mode = Enable
            - Asynchronous Wait = Disable */
      FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
      FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
      FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
      FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
      FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
      FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
      FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
      FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
      FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
      FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
      FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
      FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
      FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
      FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
      FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
      FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
      /* BANK 3 (of NOR/SRAM Bank) is enabled */
      FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);
}

void NandFlash_FSMCConfig(void)
{
  FSMC_NANDInitTypeDef FSMC_NANDInitStructure;
  FSMC_NAND_PCCARDTimingInitTypeDef  p;

  /*-- FSMC Configuration ------------------------------------------------------*/
  p.FSMC_SetupTime = 0x0;
  p.FSMC_WaitSetupTime = 0x3;
  p.FSMC_HoldSetupTime = 0x9;
  p.FSMC_HiZSetupTime = 0x0;

  FSMC_NANDInitStructure.FSMC_Bank = FSMC_Bank3_NAND;
  FSMC_NANDInitStructure.FSMC_Waitfeature = FSMC_Waitfeature_Enable;
  FSMC_NANDInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
  FSMC_NANDInitStructure.FSMC_ECC = FSMC_ECC_Enable;
  FSMC_NANDInitStructure.FSMC_ECCPageSize = FSMC_ECCPageSize_512Bytes;
  FSMC_NANDInitStructure.FSMC_TCLRSetupTime = 0x00;
  FSMC_NANDInitStructure.FSMC_TARSetupTime = 0x00;
  FSMC_NANDInitStructure.FSMC_CommonSpaceTimingStruct = &p;
  FSMC_NANDInitStructure.FSMC_AttributeSpaceTimingStruct = &p;

  FSMC_NANDInit(&FSMC_NANDInitStructure);

  /*!< FSMC NAND Bank Cmd Test */
  FSMC_NANDCmd(FSMC_Bank3_NAND, ENABLE);
}

void Dm9000a_FSMCConfig()
{
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef p;

	// DM9000A使用的地址（BANK1，BANK1有4个片选，DM9000A使用第4条片选）
	// 时序设置
	p.FSMC_AddressSetupTime = 1;
	p.FSMC_AddressHoldTime = 1;
	p.FSMC_DataSetupTime = 2;
	p.FSMC_BusTurnAroundDuration = 1;
	p.FSMC_CLKDivision = 1;
	p.FSMC_DataLatency = 1;
	p.FSMC_AccessMode = FSMC_AccessMode_A;
	// 工作模式
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_PSRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
	// 使能DM9000A的FSMC访问
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}

void SRAM_Init(void)
{
	SRAM_GPIO_Init();
    SRAM_FSMCConfig();
    LCD_FSMCConfig();
    NandFlash_FSMCConfig();
    Dm9000a_FSMCConfig();
}

