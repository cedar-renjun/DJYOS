################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/djysdk/djysrc/djyos/core/djyos.c \
C:/djysdk/djysrc/djyos/core/endian.c \
C:/djysdk/djysrc/djyos/core/sys_init.c 

OBJS += \
./src/djyos/core/djyos.o \
./src/djyos/core/endian.o \
./src/djyos/core/sys_init.o 

C_DEPS += \
./src/djyos/core/djyos.d \
./src/djyos/core/endian.d \
./src/djyos/core/sys_init.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/core/djyos.o: C:/djysdk/djysrc/djyos/core/djyos.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/djysdk/djyos_workspace/examples/tq2440/src/user/include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\tq2440\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\djyos\djyip\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\/djysrc/djyos/djyfs/include" -I"C:\djysdk\/djysrc/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/core/endian.o: C:/djysdk/djysrc/djyos/core/endian.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/djysdk/djyos_workspace/examples/tq2440/src/user/include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\tq2440\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\djyos\djyip\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\/djysrc/djyos/djyfs/include" -I"C:\djysdk\/djysrc/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/core/sys_init.o: C:/djysdk/djysrc/djyos/core/sys_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/djysdk/djyos_workspace/examples/tq2440/src/user/include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\tq2440\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\djyos\djyip\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\/djysrc/djyos/djyfs/include" -I"C:\djysdk\/djysrc/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


