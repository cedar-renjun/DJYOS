################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/loader/si/loader.c \
D:/djysdk/djysrc/djyos/loader/si/pre_loader.c 

OBJS += \
./src/loader/si/loader.o \
./src/loader/si/pre_loader.o 

C_DEPS += \
./src/loader/si/loader.d \
./src/loader/si/pre_loader.d 


# Each subdirectory must supply rules for building sources it contributes
src/loader/si/loader.o: D:/djysdk/djysrc/djyos/loader/si/loader.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/loader/si/pre_loader.o: D:/djysdk/djysrc/djyos/loader/si/pre_loader.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

