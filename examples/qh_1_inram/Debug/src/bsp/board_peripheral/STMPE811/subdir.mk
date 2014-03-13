################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/bsp/board_peripheral/qh_1/STMPE811/I2C_STM32.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/board_peripheral/qh_1/STMPE811/TS_I2C.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/board_peripheral/qh_1/STMPE811/stmpe811.c 

OBJS += \
./src/bsp/board_peripheral/STMPE811/I2C_STM32.o \
./src/bsp/board_peripheral/STMPE811/TS_I2C.o \
./src/bsp/board_peripheral/STMPE811/stmpe811.o 

C_DEPS += \
./src/bsp/board_peripheral/STMPE811/I2C_STM32.d \
./src/bsp/board_peripheral/STMPE811/TS_I2C.d \
./src/bsp/board_peripheral/STMPE811/stmpe811.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/board_peripheral/STMPE811/I2C_STM32.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/board_peripheral/qh_1/STMPE811/I2C_STM32.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/board_peripheral/STMPE811/TS_I2C.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/board_peripheral/qh_1/STMPE811/TS_I2C.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/board_peripheral/STMPE811/stmpe811.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/board_peripheral/qh_1/STMPE811/stmpe811.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/include" -I"C:/eclipseCppIndigo/djysrc/examples/qh_1_inram/src/user/config" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m3\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\stm32\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\qh_1\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\gui\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyfs\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM3/CoreSupport" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\vendor_lib/stm32/STM32F10x_StdPeriph_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

