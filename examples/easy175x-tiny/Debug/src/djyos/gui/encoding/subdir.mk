################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/gui/encoding/ascii.c \
D:/djysdk/djysrc/djyos/gui/encoding/encoding.c \
D:/djysdk/djysrc/djyos/gui/encoding/gb2312.c \
D:/djysdk/djysrc/djyos/gui/encoding/loc_string.c \
D:/djysdk/djysrc/djyos/gui/encoding/nls.c \
D:/djysdk/djysrc/djyos/gui/encoding/utf8.c 

OBJS += \
./src/djyos/gui/encoding/ascii.o \
./src/djyos/gui/encoding/encoding.o \
./src/djyos/gui/encoding/gb2312.o \
./src/djyos/gui/encoding/loc_string.o \
./src/djyos/gui/encoding/nls.o \
./src/djyos/gui/encoding/utf8.o 

C_DEPS += \
./src/djyos/gui/encoding/ascii.d \
./src/djyos/gui/encoding/encoding.d \
./src/djyos/gui/encoding/gb2312.d \
./src/djyos/gui/encoding/loc_string.d \
./src/djyos/gui/encoding/nls.d \
./src/djyos/gui/encoding/utf8.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/gui/encoding/ascii.o: D:/djysdk/djysrc/djyos/gui/encoding/ascii.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/encoding.o: D:/djysdk/djysrc/djyos/gui/encoding/encoding.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/gb2312.o: D:/djysdk/djysrc/djyos/gui/encoding/gb2312.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/loc_string.o: D:/djysdk/djysrc/djyos/gui/encoding/loc_string.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/nls.o: D:/djysdk/djysrc/djyos/gui/encoding/nls.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/utf8.o: D:/djysdk/djysrc/djyos/gui/encoding/utf8.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


