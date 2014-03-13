################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/misc.c \
C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c \
C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c \
C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c \
C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c \
C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c \
C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c \
C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c \
C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/system_stm32f10x.c 

OBJS += \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/misc.o \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.o \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.o \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.o \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.o \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.o \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.o \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.o \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/system_stm32f10x.o 

C_DEPS += \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/misc.d \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.d \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.d \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.d \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.d \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.d \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.d \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.d \
./src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/misc.o: C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/misc.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.o: C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.o: C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.o: C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.o: C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.o: C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.o: C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.o: C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/system_stm32f10x.o: C:/djysdk/djysrc/bsp/vendor_lib/stm32/STM32F10x_StdPeriph_Driver/src/system_stm32f10x.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


