################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/arch/startup/initcpuc.c 

S_UPPER_SRCS += \
../src/bsp/arch/startup/initcpu.S 

OBJS += \
./src/bsp/arch/startup/initcpu.o \
./src/bsp/arch/startup/initcpuc.o 

C_DEPS += \
./src/bsp/arch/startup/initcpuc.d 

S_UPPER_DEPS += \
./src/bsp/arch/startup/initcpu.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/startup/%.o: ../src/bsp/arch/startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC Assembler'
	arm-none-eabi-gcc -Ddebug -I"D:/djyos_workspace/tq2440/src/bsp/arch/include" -c -adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/startup/%.o: ../src/bsp/arch/startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/tq2440/src/bsp/arch/include" -I"D:/djyos_workspace/tq2440/src/user/include" -I"D:/djyos_workspace/tq2440/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/tq2440/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/tq2440/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


