################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/arch/core/cpu.c \
../src/bsp/arch/core/exception.c \
../src/bsp/arch/core/int_hard.c 

S_UPPER_SRCS += \
../src/bsp/arch/core/cpus.S \
../src/bsp/arch/core/exceptions.S \
../src/bsp/arch/core/ints.S 

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
src/bsp/arch/core/%.o: ../src/bsp/arch/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/tq2440/src/bsp/arch/include" -I"D:/djyos_workspace/tq2440/src/user/include" -I"D:/djyos_workspace/tq2440/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/tq2440/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/tq2440/src/bsp/cpu_peripheral/include_api" -Os -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/%.o: ../src/bsp/arch/core/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC Assembler'
	arm-none-eabi-gcc -I"D:/djyos_workspace/tq2440/src/bsp/arch/include" -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


