################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/ascii8x16.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/ascii8x8.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/font.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/gb2312_16.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/textshow.c 

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
src/djyos/gui/font/ascii8x16.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/ascii8x16.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/font/ascii8x8.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/ascii8x8.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/font/font.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/font.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/font/gb2312_16.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/gb2312_16.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/gui/font/textshow.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/gui/font/textshow.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


