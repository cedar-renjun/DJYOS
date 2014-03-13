################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpu.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exception.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/int_hard.c 

S_UPPER_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpus.S \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exceptions.S \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/ints.S 

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
src/bsp/arch/core/cpu.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/cpus.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpus.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_tiny/src/bsp/arch/cpu/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/exception.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exception.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/exceptions.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exceptions.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_tiny/src/bsp/arch/cpu/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/int_hard.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/int_hard.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/ints.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/ints.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_tiny/src/bsp/arch/cpu/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


