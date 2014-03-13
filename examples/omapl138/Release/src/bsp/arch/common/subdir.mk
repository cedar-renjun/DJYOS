################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/arch/common/cache.c \
../src/bsp/arch/common/exception.c \
../src/bsp/arch/common/mmu.c 

S_UPPER_SRCS += \
../src/bsp/arch/common/cpus.S \
../src/bsp/arch/common/exceptions.S \
../src/bsp/arch/common/mmucache.S 

OBJS += \
./src/bsp/arch/common/cache.o \
./src/bsp/arch/common/cpus.o \
./src/bsp/arch/common/exception.o \
./src/bsp/arch/common/exceptions.o \
./src/bsp/arch/common/mmu.o \
./src/bsp/arch/common/mmucache.o 

C_DEPS += \
./src/bsp/arch/common/cache.d \
./src/bsp/arch/common/exception.d \
./src/bsp/arch/common/mmu.d 

S_UPPER_DEPS += \
./src/bsp/arch/common/cpus.d \
./src/bsp/arch/common/exceptions.d \
./src/bsp/arch/common/mmucache.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/common/%.o: ../src/bsp/arch/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:/djysdk/djysrc/examples/omapl138/src/user/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyip\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\/djysrc/djyos/djyos/djyfs/include" -I"D:\djysdk\/djysrc/djyos/djyos/gui/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -Os -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/common/%.o: ../src/bsp/arch/common/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


