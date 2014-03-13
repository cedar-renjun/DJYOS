################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpu.c \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exception.c \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/int_hard.c 

S_UPPER_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpus.S \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exceptions.S \
D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/ints.S 

OBJS += \
./src/bsp/arch/core/cpu.o \
./src/bsp/arch/core/cpus.o \
./src/bsp/arch/core/exception.o \
./src/bsp/arch/core/exceptions.o \
./src/bsp/arch/core/int_hard.o \
./src/bsp/arch/core/ints.o 

C_DEPS += \
./src/bsp/arch/core/cpu.d \
./src/bsp/arch/core/exception.d \
./src/bsp/arch/core/int_hard.d 

S_UPPER_DEPS += \
./src/bsp/arch/core/cpus.d \
./src/bsp/arch/core/exceptions.d \
./src/bsp/arch/core/ints.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/core/cpu.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/cpus.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/cpus.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/exception.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exception.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/exceptions.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/exceptions.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/int_hard.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/int_hard.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/core/ints.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/cortex_m/cortex_m3/core/ints.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


