################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/loader/loader.c \
../src/loader/module_init.c \
../src/loader/pre_loader.c 

OBJS += \
./src/loader/loader.o \
./src/loader/module_init.o \
./src/loader/pre_loader.o 

C_DEPS += \
./src/loader/loader.d \
./src/loader/module_init.d \
./src/loader/pre_loader.d 


# Each subdirectory must supply rules for building sources it contributes
src/loader/%.o: ../src/loader/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/tq2440/src/bsp/arch/include" -I"D:/djyos_workspace/tq2440/src/user/include" -I"D:/djyos_workspace/tq2440/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/tq2440/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/tq2440/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


