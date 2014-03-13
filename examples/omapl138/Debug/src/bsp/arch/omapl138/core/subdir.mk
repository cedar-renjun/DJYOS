################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/cpu.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/int_hard.c 

S_UPPER_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/ints.S 

OBJS += \
./src/bsp/arch/omapl138/core/cpu.o \
./src/bsp/arch/omapl138/core/int_hard.o \
./src/bsp/arch/omapl138/core/ints.o 

C_DEPS += \
./src/bsp/arch/omapl138/core/cpu.d \
./src/bsp/arch/omapl138/core/int_hard.d 

S_UPPER_DEPS += \
./src/bsp/arch/omapl138/core/ints.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/omapl138/core/cpu.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/omapl138/core/int_hard.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/int_hard.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/omapl138/core/ints.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/core/ints.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


