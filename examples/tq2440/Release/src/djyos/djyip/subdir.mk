################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/arp.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/enet.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/enet_cmd.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/ethernet.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/icmp.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/ip.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/ipopts.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/ping.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/socket.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/socketopts.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/tcp.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/tcpopts.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/udp.c 

OBJS += \
./src/djyos/djyip/arp.o \
./src/djyos/djyip/enet.o \
./src/djyos/djyip/enet_cmd.o \
./src/djyos/djyip/ethernet.o \
./src/djyos/djyip/icmp.o \
./src/djyos/djyip/ip.o \
./src/djyos/djyip/ipopts.o \
./src/djyos/djyip/ping.o \
./src/djyos/djyip/socket.o \
./src/djyos/djyip/socketopts.o \
./src/djyos/djyip/tcp.o \
./src/djyos/djyip/tcpopts.o \
./src/djyos/djyip/udp.o 

C_DEPS += \
./src/djyos/djyip/arp.d \
./src/djyos/djyip/enet.d \
./src/djyos/djyip/enet_cmd.d \
./src/djyos/djyip/ethernet.d \
./src/djyos/djyip/icmp.d \
./src/djyos/djyip/ip.d \
./src/djyos/djyip/ipopts.d \
./src/djyos/djyip/ping.d \
./src/djyos/djyip/socket.d \
./src/djyos/djyip/socketopts.d \
./src/djyos/djyip/tcp.d \
./src/djyos/djyip/tcpopts.d \
./src/djyos/djyip/udp.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/djyip/arp.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/arp.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/enet.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/enet.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/enet_cmd.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/enet_cmd.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/ethernet.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/ethernet.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/icmp.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/icmp.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/ip.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/ip.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/ipopts.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/ipopts.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/ping.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/ping.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/socket.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/socket.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/socketopts.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/socketopts.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/tcp.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/tcp.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/tcpopts.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/tcpopts.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyip/udp.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyip/udp.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/tq2440/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


