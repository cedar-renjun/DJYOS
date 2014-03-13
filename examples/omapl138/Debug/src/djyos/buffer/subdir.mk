################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/djyos/buffer/abc.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/buffer/line.c \
C:/eclipseCppIndigo/djysrc/djyos/djyos/buffer/ring.c 

OBJS += \
./src/djyos/buffer/abc.o \
./src/djyos/buffer/line.o \
./src/djyos/buffer/ring.o 

C_DEPS += \
./src/djyos/buffer/abc.d \
./src/djyos/buffer/line.d \
./src/djyos/buffer/ring.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/buffer/abc.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/buffer/abc.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/buffer/line.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/buffer/line.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/djyos/buffer/ring.o: C:/eclipseCppIndigo/djysrc/djyos/djyos/buffer/ring.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


