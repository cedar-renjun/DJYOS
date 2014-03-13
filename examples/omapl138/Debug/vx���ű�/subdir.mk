################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vx·ûºÅ±í/WrSymTbl(1).c 

OBJS += \
./vx·ûºÅ±í/WrSymTbl(1).o 

C_DEPS += \
./vx·ûºÅ±í/WrSymTbl(1).d 


# Each subdirectory must supply rules for building sources it contributes
vx·ûºÅ±í/WrSymTbl(1).o: ../vx·ûºÅ±í/WrSymTbl(1).c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:/djysdk/djysrc/examples/omapl138/src/user/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyip\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\/djysrc/djyos/djyos/djyfs/include" -I"D:\djysdk\/djysrc/djyos/djyos/gui/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"vx·ûºÅ±í/WrSymTbl(1).d" -MT"vx·ûºÅ±í/WrSymTbl(1).d" -mcpu=cortex-m4 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


