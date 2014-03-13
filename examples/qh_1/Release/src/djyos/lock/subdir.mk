################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/djysdk/djysrc/djyos/lock/lock.c 

OBJS += \
./src/djyos/lock/lock.o 

C_DEPS += \
./src/djyos/lock/lock.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/lock/lock.o: C:/djysdk/djysrc/djyos/lock/lock.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -Os -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


