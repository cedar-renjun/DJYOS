################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/cpu.c \
D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/int_hard.c 

S_UPPER_SRCS += \
D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/ints.S 

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
src/bsp/arch/s3c2440/core/cpu.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:/djysdk/djysrc/examples/tq2440/src/user/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyip\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\/djysrc/djyos/djyos/djyfs/include" -I"D:\djysdk\/djysrc/djyos/djyos/gui/include" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/s3c2440/core/int_hard.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/int_hard.c
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:/djysdk/djysrc/examples/tq2440/src/user/include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\samsung\s3c2440\include" -I"D:\djysdk\\djysrc\djyos\bsp\board_peripheral\tq2440\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\include" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyip\include" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\/djysrc/djyos/djyos/djyfs/include" -I"D:\djysdk\/djysrc/djyos/djyos/gui/include" -O0 -ffunction-sections -fdata-sections -std=c99 -c -Wa,-adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/s3c2440/core/ints.o: D:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/samsung/s3c2440/core/ints.S
	@echo 'Building file: $<'
	@echo 'Invoking: Sourcery GCC Assembler'
	arm-none-eabi-gcc -Ddebug -I"D:\djysdk\/djysrc/djyos/bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -c -adhlns="$@.lst" -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g2 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


