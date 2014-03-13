################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/djyos/easyIP/Ethernet.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/Http.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/Stack.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/Timer.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/app.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/arp.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/icmp.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/ip.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/tagexpand.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/tcp.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/udp.c \
D:/djysdk/djysrc/djyos/djyos/easyIP/web_server.c 

OBJS += \
./src/djyos/easyIP/Ethernet.o \
./src/djyos/easyIP/Http.o \
./src/djyos/easyIP/Stack.o \
./src/djyos/easyIP/Timer.o \
./src/djyos/easyIP/app.o \
./src/djyos/easyIP/arp.o \
./src/djyos/easyIP/icmp.o \
./src/djyos/easyIP/ip.o \
./src/djyos/easyIP/tagexpand.o \
./src/djyos/easyIP/tcp.o \
./src/djyos/easyIP/udp.o \
./src/djyos/easyIP/web_server.o 

C_DEPS += \
./src/djyos/easyIP/Ethernet.d \
./src/djyos/easyIP/Http.d \
./src/djyos/easyIP/Stack.d \
./src/djyos/easyIP/Timer.d \
./src/djyos/easyIP/app.d \
./src/djyos/easyIP/arp.d \
./src/djyos/easyIP/icmp.d \
./src/djyos/easyIP/ip.d \
./src/djyos/easyIP/tagexpand.d \
./src/djyos/easyIP/tcp.d \
./src/djyos/easyIP/udp.d \
./src/djyos/easyIP/web_server.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/easyIP/Ethernet.o: D:/djysdk/djysrc/djyos/djyos/easyIP/Ethernet.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/Http.o: D:/djysdk/djysrc/djyos/djyos/easyIP/Http.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/Stack.o: D:/djysdk/djysrc/djyos/djyos/easyIP/Stack.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/Timer.o: D:/djysdk/djysrc/djyos/djyos/easyIP/Timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/app.o: D:/djysdk/djysrc/djyos/djyos/easyIP/app.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/arp.o: D:/djysdk/djysrc/djyos/djyos/easyIP/arp.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/icmp.o: D:/djysdk/djysrc/djyos/djyos/easyIP/icmp.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/ip.o: D:/djysdk/djysrc/djyos/djyos/easyIP/ip.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/tagexpand.o: D:/djysdk/djysrc/djyos/djyos/easyIP/tagexpand.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/tcp.o: D:/djysdk/djysrc/djyos/djyos/easyIP/tcp.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/udp.o: D:/djysdk/djysrc/djyos/djyos/easyIP/udp.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/easyIP/web_server.o: D:/djysdk/djysrc/djyos/djyos/easyIP/web_server.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"D:\djysdk\djysrc\djyos\djyos\include" -I"D:\djysdk\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\djysrc\djyos\djyos\djyfs\include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/include" -I"D:/djyos_workspace/omap_l138/src/bsp/arch/cpu/include" -I"D:/djyos_workspace/omap_l138/src/user/include" -I"D:/djyos_workspace/omap_l138/src/bsp/board_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include" -I"D:/djyos_workspace/omap_l138/src/bsp/cpu_peripheral/include_api" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


