################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/djyfs/flashfile/ddr.c \
D:/djysdk/djysrc/djyos/djyfs/flashfile/ecc256.c \
D:/djysdk/djysrc/djyos/djyfs/flashfile/fdt.c \
D:/djysdk/djysrc/djyos/djyfs/flashfile/flashfile.c \
D:/djysdk/djysrc/djyos/djyfs/flashfile/mdr.c 

OBJS += \
./src/djyos/djyfs/flashfile/ddr.o \
./src/djyos/djyfs/flashfile/ecc256.o \
./src/djyos/djyfs/flashfile/fdt.o \
./src/djyos/djyfs/flashfile/flashfile.o \
./src/djyos/djyfs/flashfile/mdr.o 

C_DEPS += \
./src/djyos/djyfs/flashfile/ddr.d \
./src/djyos/djyfs/flashfile/ecc256.d \
./src/djyos/djyfs/flashfile/fdt.d \
./src/djyos/djyfs/flashfile/flashfile.d \
./src/djyos/djyfs/flashfile/mdr.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/djyfs/flashfile/ddr.o: D:/djysdk/djysrc/djyos/djyfs/flashfile/ddr.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyfs/flashfile/ecc256.o: D:/djysdk/djysrc/djyos/djyfs/flashfile/ecc256.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyfs/flashfile/fdt.o: D:/djysdk/djysrc/djyos/djyfs/flashfile/fdt.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyfs/flashfile/flashfile.o: D:/djysdk/djysrc/djyos/djyfs/flashfile/flashfile.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyfs/flashfile/mdr.o: D:/djysdk/djysrc/djyos/djyfs/flashfile/mdr.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/include" -I"E:/djysdk/djyos_workspace/examples/easy175x-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\include" -I"D:\djysdk\\djysrc\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyfs\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"D:\djysdk\\djysrc\bsp\arch\arm\cortex_m\cortex_m3\include" -I"D:\djysdk\\djysrc\bsp\cpu_peripheral\lpc175x\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


