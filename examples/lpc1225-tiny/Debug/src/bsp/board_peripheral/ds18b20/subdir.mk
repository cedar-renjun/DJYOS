################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/bsp/board_peripheral/qh_1/ds18b20/DS18B20.c 

OBJS += \
./src/bsp/board_peripheral/ds18b20/DS18B20.o 

C_DEPS += \
./src/bsp/board_peripheral/ds18b20/DS18B20.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/board_peripheral/ds18b20/DS18B20.o: D:/djysdk/djysrc/djyos/bsp/board_peripheral/qh_1/ds18b20/DS18B20.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:/djyos_workspace/easy175x/src/user/include" -I"D:/djyos_workspace/easy175x/src/user/config" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyfs\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\lpc175x\include" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


