################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/startup/initcpuc.c 

S_UPPER_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/startup/initcpu.S 

OBJS += \
./src/bsp/arch/omapl138_arm/startup/initcpu.o \
./src/bsp/arch/omapl138_arm/startup/initcpuc.o 

C_DEPS += \
./src/bsp/arch/omapl138_arm/startup/initcpuc.d 

S_UPPER_DEPS += \
./src/bsp/arch/omapl138_arm/startup/initcpu.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/omapl138_arm/startup/initcpu.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/startup/initcpu.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/omapl138_arm/startup/initcpuc.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/startup/initcpuc.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:/djysdk/djysrc/examples/omapl138/src/user/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyip\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\/djysrc/djyos/djyos/djyfs/include" -I"D:\djysdk\/djysrc/djyos/djyos/gui/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -Os -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


