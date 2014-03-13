################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/arch/cpu/startup/initcpuc.c 

S_UPPER_SRCS += \
../src/bsp/arch/cpu/startup/initcpu.S 

OBJS += \
./src/bsp/arch/cpu/startup/initcpu.o \
./src/bsp/arch/cpu/startup/initcpuc.o 

C_DEPS += \
./src/bsp/arch/cpu/startup/initcpuc.d 

S_UPPER_DEPS += \
./src/bsp/arch/cpu/startup/initcpu.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/cpu/startup/%.o: ../src/bsp/arch/cpu/startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC Assembler'
	arm-none-eabi-gcc -Drelease -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/cpu/startup/%.o: ../src/bsp/arch/cpu/startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


