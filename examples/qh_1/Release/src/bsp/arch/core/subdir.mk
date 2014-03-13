################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/cpu.c \
C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/exception.c \
C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/int_hard.c 

S_UPPER_SRCS += \
C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/cpus.S \
C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/exceptions.S \
C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/ints.S 

OBJS += \
./src/bsp/arch/core/cpu.o \
./src/bsp/arch/core/cpus.o \
./src/bsp/arch/core/exception.o \
./src/bsp/arch/core/exceptions.o \
./src/bsp/arch/core/int_hard.o \
./src/bsp/arch/core/ints.o 

C_DEPS += \
./src/bsp/arch/core/cpu.d \
./src/bsp/arch/core/exception.d \
./src/bsp/arch/core/int_hard.d 

S_UPPER_DEPS += \
./src/bsp/arch/core/cpus.d \
./src/bsp/arch/core/exceptions.d \
./src/bsp/arch/core/ints.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/core/cpu.o: C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -Os -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/cpus.o: C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/cpus.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Drelease -I"C:/djysdk/djyos_workspace/examples/qh_1/src/bsp/arch/cpu/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/exception.o: C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/exception.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -Os -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/exceptions.o: C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/exceptions.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Drelease -I"C:/djysdk/djyos_workspace/examples/qh_1/src/bsp/arch/cpu/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/int_hard.o: C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/int_hard.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/include" -I"C:/djysdk/djyos_workspace/examples/qh_1/src/user/config" -I"C:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\stm32\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\qh_1\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\\djysrc\djyos\gui\include" -I"C:\djysdk\\djysrc\djyos\djyfs\include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32" -I"C:\djysdk\\djysrc\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -I"C:\djysdk\\djysrc\djyos\djyip\include" -Os -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/ints.o: C:/djysdk/djysrc/bsp/arch/arm/cortex_m/cortex_m3/core/ints.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Drelease -I"C:/djysdk/djyos_workspace/examples/qh_1/src/bsp/arch/cpu/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


