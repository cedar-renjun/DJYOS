################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/loader/si/loader.c \
D:/djysdk/djysrc/loader/si/pre_loader.c 

OBJS += \
./src/loader/si/loader.o \
./src/loader/si/pre_loader.o 

C_DEPS += \
./src/loader/si/loader.d \
./src/loader/si/pre_loader.d 


# Each subdirectory must supply rules for building sources it contributes
src/loader/si/loader.o: D:/djysdk/djysrc/loader/si/loader.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/loader/si/pre_loader.o: D:/djysdk/djysrc/loader/si/pre_loader.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


