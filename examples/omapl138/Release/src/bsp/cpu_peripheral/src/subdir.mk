################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/nude_io.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_cpucfg.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_dcore.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_gpio.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_peri.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_spi.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_timer.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_uart.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/wdt_hard.c 

OBJS += \
./src/bsp/cpu_peripheral/src/nude_io.o \
./src/bsp/cpu_peripheral/src/omapl138_cpucfg.o \
./src/bsp/cpu_peripheral/src/omapl138_dcore.o \
./src/bsp/cpu_peripheral/src/omapl138_gpio.o \
./src/bsp/cpu_peripheral/src/omapl138_peri.o \
./src/bsp/cpu_peripheral/src/omapl138_spi.o \
./src/bsp/cpu_peripheral/src/omapl138_timer.o \
./src/bsp/cpu_peripheral/src/omapl138_uart.o \
./src/bsp/cpu_peripheral/src/wdt_hard.o 

C_DEPS += \
./src/bsp/cpu_peripheral/src/nude_io.d \
./src/bsp/cpu_peripheral/src/omapl138_cpucfg.d \
./src/bsp/cpu_peripheral/src/omapl138_dcore.d \
./src/bsp/cpu_peripheral/src/omapl138_gpio.d \
./src/bsp/cpu_peripheral/src/omapl138_peri.d \
./src/bsp/cpu_peripheral/src/omapl138_spi.d \
./src/bsp/cpu_peripheral/src/omapl138_timer.d \
./src/bsp/cpu_peripheral/src/omapl138_uart.d \
./src/bsp/cpu_peripheral/src/wdt_hard.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/cpu_peripheral/src/nude_io.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/nude_io.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/omapl138_cpucfg.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_cpucfg.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/omapl138_dcore.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_dcore.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/omapl138_gpio.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/omapl138_peri.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_peri.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/omapl138_spi.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/omapl138_timer.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/omapl138_uart.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/omapl138_uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/wdt_hard.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/omapl138/src/wdt_hard.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


