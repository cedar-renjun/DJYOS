################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/ascii.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/encoding.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/gb2312.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/loc_string.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/nls.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/utf8.c 

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
src/djyos/gui/encoding/ascii.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/ascii.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/encoding.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/encoding.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/gb2312.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/gb2312.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/loc_string.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/loc_string.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/nls.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/nls.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/encoding/utf8.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/encoding/utf8.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/lpc1225-tiny/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


