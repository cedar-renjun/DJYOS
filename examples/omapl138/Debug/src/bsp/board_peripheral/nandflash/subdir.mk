################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/bsp/board_peripheral/tq2440/nandflash/k9f1208xxx.c 

OBJS += \
./src/bsp/board_peripheral/nandflash/k9f1208xxx.o 

C_DEPS += \
./src/bsp/board_peripheral/nandflash/k9f1208xxx.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/board_peripheral/nandflash/k9f1208xxx.o: D:/djysdk/djysrc/djyos/bsp/board_peripheral/tq2440/nandflash/k9f1208xxx.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:/djysdk/djysrc/examples/tq2440/src/user/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyip\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\/djysrc/djyos/djyos/djyfs/include" -I"D:\djysdk\/djysrc/djyos/djyos/gui/include" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


