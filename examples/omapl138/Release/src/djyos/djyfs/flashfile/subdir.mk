################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/ddr.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/ecc256.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/fdt.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/flashfile.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/mdr.c 

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
src/djyos/djyfs/flashfile/ddr.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/ddr.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyfs/flashfile/ecc256.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/ecc256.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyfs/flashfile/fdt.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/fdt.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyfs/flashfile/flashfile.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/flashfile.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/djyfs/flashfile/mdr.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/djyfs/flashfile/mdr.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/eclipseCppIndigo/djysrc/examples/omapl138/src/user/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\djyip\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\djyos\include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/djyfs/include" -I"C:\eclipseCppIndigo\/djysrc/djyos/djyos/gui/include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\cpu_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\board_peripheral\omapl138\include" -I"C:\eclipseCppIndigo\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\omapl138_arm\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


