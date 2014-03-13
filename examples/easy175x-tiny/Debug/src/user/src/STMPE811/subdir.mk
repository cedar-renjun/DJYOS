################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/user/src/STMPE811/I2C_STM32.c \
../src/user/src/STMPE811/TS_I2C.c \
../src/user/src/STMPE811/Touch.c 

OBJS += \
./src/user/src/STMPE811/I2C_STM32.o \
./src/user/src/STMPE811/TS_I2C.o \
./src/user/src/STMPE811/Touch.o 

C_DEPS += \
./src/user/src/STMPE811/I2C_STM32.d \
./src/user/src/STMPE811/TS_I2C.d \
./src/user/src/STMPE811/Touch.d 


# Each subdirectory must supply rules for building sources it contributes
src/user/src/STMPE811/%.o: ../src/user/src/STMPE811/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djyos_workspace\qh_1\src\user\src\STMPE811" -I"D:\djyos_workspace\qh_1\src\bsp\Libraries" -I"D:\djyos_workspace\qh_1\src\bsp\Libraries\CMSIS\CM3\CoreSupport" -I"D:\djyos_workspace\qh_1\src\bsp\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x" -I"D:\djyos_workspace\qh_1\src\bsp\Libraries\STM32F10x_StdPeriph_Driver\inc" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/qh_1/src/bsp/arch/include" -I"D:/djyos_workspace/qh_1/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/qh_1/src/user/include" -I"D:/djyos_workspace/qh_1/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/qh_1/src/bsp/board_peripheral/include_api" -I"D:/djyos_workspace/qh_1/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/qh_1/src/bsp/cpu_peripheral/include_api" -O1 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


