################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/arch/arm_all/cache.c \
../src/bsp/arch/arm_all/mmu.c 

OBJS += \
./src/bsp/arch/arm_all/cache.o \
./src/bsp/arch/arm_all/mmu.o 

C_DEPS += \
./src/bsp/arch/arm_all/cache.d \
./src/bsp/arch/arm_all/mmu.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/arm_all/%.o: ../src/bsp/arch/arm_all/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


