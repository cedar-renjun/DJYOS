################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vx���ű�/WrSymTbl(1).c 

OBJS += \
./vx���ű�/WrSymTbl(1).o 

C_DEPS += \
./vx���ű�/WrSymTbl(1).d 


# Each subdirectory must supply rules for building sources it contributes
vx���ű�/WrSymTbl(1).o: ../vx���ű�/WrSymTbl(1).c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/omap_l138/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/omap_l138/src/user/include" -I"D:/djysdk/djysrc/examples/omap_l138/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/omap_l138/src/bsp/cpu_peripheral/include_api" -Os -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"vx���ű�/WrSymTbl(1).d" -MT"vx���ű�/WrSymTbl(1).d" -mcpu=arm920t -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


