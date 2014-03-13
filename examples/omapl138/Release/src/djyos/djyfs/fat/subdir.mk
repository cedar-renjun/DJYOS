################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/djyos/djyfs/fat/djyFAT32.c 

OBJS += \
./src/djyos/djyfs/fat/djyFAT32.o 

C_DEPS += \
./src/djyos/djyfs/fat/djyFAT32.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/djyfs/fat/djyFAT32.o: D:/djysdk/djysrc/djyos/djyos/djyfs/fat/djyFAT32.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -I"D:/djysdk/djysrc/examples/omap_l138/src/user/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyip\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\/djysrc/djyos/djyos/djyfs/include" -I"D:\djysdk\/djysrc/djyos/djyos/gui/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -Os -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


