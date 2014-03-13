################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/arch/common/cache.c \
../src/bsp/arch/common/mmu.c 

OBJS += \
./src/bsp/arch/common/cache.o \
./src/bsp/arch/common/mmu.o 

C_DEPS += \
./src/bsp/arch/common/cache.d \
./src/bsp/arch/common/mmu.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/common/%.o: ../src/bsp/arch/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/tq2440/src/bsp/arch/include" -I"D:/djyos_workspace/tq2440/src/user/include" -I"D:/djyos_workspace/tq2440/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/tq2440/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/tq2440/src/bsp/cpu_peripheral/include_api" -Os -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


