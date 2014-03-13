################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/djyos/core/djyos.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/core/endian.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/core/sys_init.c 

OBJS += \
./src/djyos/core/djyos.o \
./src/djyos/core/endian.o \
./src/djyos/core/sys_init.o 

C_DEPS += \
./src/djyos/core/djyos.d \
./src/djyos/core/endian.d \
./src/djyos/core/sys_init.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/core/djyos.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/core/djyos.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/core/endian.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/core/endian.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/core/sys_init.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/core/sys_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


