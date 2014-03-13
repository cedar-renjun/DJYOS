################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/lpc12xx/src/cpu_peri.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/lpc12xx/src/gpio.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/lpc12xx/src/sysctrl.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/lpc12xx/src/uart_tiny.c 

OBJS += \
./src/bsp/cpu_peripheral/src/cpu_peri.o \
./src/bsp/cpu_peripheral/src/gpio.o \
./src/bsp/cpu_peripheral/src/sysctrl.o \
./src/bsp/cpu_peripheral/src/uart_tiny.o 

C_DEPS += \
./src/bsp/cpu_peripheral/src/cpu_peri.d \
./src/bsp/cpu_peripheral/src/gpio.d \
./src/bsp/cpu_peripheral/src/sysctrl.d \
./src/bsp/cpu_peripheral/src/uart_tiny.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/cpu_peripheral/src/cpu_peri.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/lpc12xx/src/cpu_peri.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/gpio.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/lpc12xx/src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/sysctrl.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/lpc12xx/src/sysctrl.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/cpu_peripheral/src/uart_tiny.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/cpu_peripheral/lpc12xx/src/uart_tiny.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


