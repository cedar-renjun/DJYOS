################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/djysdk/djysrc/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/cpu.c \
C:/djysdk/djysrc/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/int_hard.c 

S_UPPER_SRCS += \
C:/djysdk/djysrc/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/ints.S 

OBJS += \
./src/bsp/arch/s3c2440/core/cpu.o \
./src/bsp/arch/s3c2440/core/int_hard.o \
./src/bsp/arch/s3c2440/core/ints.o 

C_DEPS += \
./src/bsp/arch/s3c2440/core/cpu.d \
./src/bsp/arch/s3c2440/core/int_hard.d 

S_UPPER_DEPS += \
./src/bsp/arch/s3c2440/core/ints.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/s3c2440/core/cpu.o: C:/djysdk/djysrc/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/djysdk/djyos_workspace/examples/tq2440/src/user/include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\tq2440\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\djyos\djyip\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\/djysrc/djyos/djyfs/include" -I"C:\djysdk\/djysrc/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/s3c2440/core/int_hard.o: C:/djysdk/djysrc/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/int_hard.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Drelease -I"C:/djysdk/djyos_workspace/examples/tq2440/src/user/include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\tq2440\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\djyos\djyip\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\/djysrc/djyos/djyfs/include" -I"C:\djysdk\/djysrc/djyos/gui/include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/s3c2440/core/ints.o: C:/djysdk/djysrc/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/ints.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Drelease -I"C:\djysdk\/djysrc/bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:/djysdk/djyos_workspace/examples/tq2440/src/bsp/arch/include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


