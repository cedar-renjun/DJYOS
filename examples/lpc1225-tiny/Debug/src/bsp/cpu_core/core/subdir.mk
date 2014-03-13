################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpu.c \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exception.c \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/int_hard.c 

S_UPPER_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpus.S \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exceptions.S 

OBJS += \
./src/bsp/cpu_core/core/cpu.o \
./src/bsp/cpu_core/core/cpus.o \
./src/bsp/cpu_core/core/exception.o \
./src/bsp/cpu_core/core/exceptions.o \
./src/bsp/cpu_core/core/int_hard.o 

C_DEPS += \
./src/bsp/cpu_core/core/cpu.d \
./src/bsp/cpu_core/core/exception.d \
./src/bsp/cpu_core/core/int_hard.d 

S_UPPER_DEPS += \
./src/bsp/cpu_core/core/cpus.d \
./src/bsp/cpu_core/core/exceptions.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/cpu_core/core/cpu.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:/djyos_workspace/qh_0524/src/user/include" -I"D:/djyos_workspace/qh_0524/src/user/config" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/stm32" -I"D:\djysdk\\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyfs\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_core/core/cpus.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpus.S
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC Assembler'
	arm-none-eabi-gcc -Ddebug -I"D:/djyos_workspace/qh_0524/src/bsp/arch/cpu/include" -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_core/core/exception.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exception.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:/djyos_workspace/qh_0524/src/user/include" -I"D:/djyos_workspace/qh_0524/src/user/config" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/stm32" -I"D:\djysdk\\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyfs\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_core/core/exceptions.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exceptions.S
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC Assembler'
	arm-none-eabi-gcc -Ddebug -I"D:/djyos_workspace/qh_0524/src/bsp/arch/cpu/include" -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_core/core/int_hard.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/int_hard.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:/djyos_workspace/qh_0524/src/user/include" -I"D:/djyos_workspace/qh_0524/src/user/config" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/stm32" -I"D:\djysdk\\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyfs\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


