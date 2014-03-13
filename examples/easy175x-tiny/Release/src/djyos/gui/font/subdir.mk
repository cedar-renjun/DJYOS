################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/djyos/gui/font/ascii8x16.c \
D:/djysdk/djysrc/djyos/djyos/gui/font/ascii8x8.c \
D:/djysdk/djysrc/djyos/djyos/gui/font/font.c \
D:/djysdk/djysrc/djyos/djyos/gui/font/gb2312_16.c \
D:/djysdk/djysrc/djyos/djyos/gui/font/textshow.c 

OBJS += \
./src/djyos/gui/font/ascii8x16.o \
./src/djyos/gui/font/ascii8x8.o \
./src/djyos/gui/font/font.o \
./src/djyos/gui/font/gb2312_16.o \
./src/djyos/gui/font/textshow.o 

C_DEPS += \
./src/djyos/gui/font/ascii8x16.d \
./src/djyos/gui/font/ascii8x8.d \
./src/djyos/gui/font/font.d \
./src/djyos/gui/font/gb2312_16.d \
./src/djyos/gui/font/textshow.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/gui/font/ascii8x16.o: D:/djysdk/djysrc/djyos/djyos/gui/font/ascii8x16.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/font/ascii8x8.o: D:/djysdk/djysrc/djyos/djyos/gui/font/ascii8x8.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/font/font.o: D:/djysdk/djysrc/djyos/djyos/gui/font/font.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/font/gb2312_16.o: D:/djysdk/djysrc/djyos/djyos/gui/font/gb2312_16.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/font/textshow.o: D:/djysdk/djysrc/djyos/djyos/gui/font/textshow.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/arch/cpu/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/board_peripheral/include_api" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include" -I"D:/djysdk/djysrc/examples/easy175x-tiny/src/bsp/cpu_peripheral/include_api" -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


