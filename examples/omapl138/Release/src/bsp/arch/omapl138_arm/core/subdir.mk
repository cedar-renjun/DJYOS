################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/cpu.c \
D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/int_hard.c 

S_UPPER_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/ints.S 

OBJS += \
./src/bsp/arch/omapl138_arm/core/cpu.o \
./src/bsp/arch/omapl138_arm/core/int_hard.o \
./src/bsp/arch/omapl138_arm/core/ints.o 

C_DEPS += \
./src/bsp/arch/omapl138_arm/core/cpu.d \
./src/bsp/arch/omapl138_arm/core/int_hard.d 

S_UPPER_DEPS += \
./src/bsp/arch/omapl138_arm/core/ints.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/omapl138_arm/core/cpu.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:/djysdk/djysrc/examples/omapl138/src/user/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyip\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\/djysrc/djyos/djyos/djyfs/include" -I"D:\djysdk\/djysrc/djyos/djyos/gui/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -Os -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/omapl138_arm/core/int_hard.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/int_hard.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:/djysdk/djysrc/examples/omapl138/src/user/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyip\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\/djysrc/djyos/djyos/djyfs/include" -I"D:\djysdk\/djysrc/djyos/djyos/gui/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -Os -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/omapl138_arm/core/ints.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/ints.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


