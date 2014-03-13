################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/arch/cpu/core/cpu.c \
../src/bsp/arch/cpu/core/int_hard.c 

S_UPPER_SRCS += \
../src/bsp/arch/cpu/core/exceptions.S \
../src/bsp/arch/cpu/core/ints.S 

OBJS += \
./src/bsp/arch/cpu/core/cpu.o \
./src/bsp/arch/cpu/core/exceptions.o \
./src/bsp/arch/cpu/core/int_hard.o \
./src/bsp/arch/cpu/core/ints.o 

C_DEPS += \
./src/bsp/arch/cpu/core/cpu.d \
./src/bsp/arch/cpu/core/int_hard.d 

S_UPPER_DEPS += \
./src/bsp/arch/cpu/core/exceptions.d \
./src/bsp/arch/cpu/core/ints.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/cpu/core/%.o: ../src/bsp/arch/cpu/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/cpu/core/%.o: ../src/bsp/arch/cpu/core/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC Assembler'
	arm-none-eabi-gcc -Ddebug -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -c -adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


