################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/loader/si/loader.c \
C:/eclipseCppIndigo/djysrc/djyos/loader/si/pre_loader.c 

OBJS += \
./src/loader/si/loader.o \
./src/loader/si/pre_loader.o 

C_DEPS += \
./src/loader/si/loader.d \
./src/loader/si/pre_loader.d 


# Each subdirectory must supply rules for building sources it contributes
src/loader/si/loader.o: C:/eclipseCppIndigo/djysrc/djyos/loader/si/loader.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/loader/si/pre_loader.o: C:/eclipseCppIndigo/djysrc/djyos/loader/si/pre_loader.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

