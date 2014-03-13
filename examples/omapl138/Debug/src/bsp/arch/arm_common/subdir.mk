################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/cache.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/exception.c \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/mmu.c 

S_UPPER_SRCS += \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/cpus.S \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/exceptions.S \
C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/mmucache.S 

OBJS += \
./src/bsp/arch/arm_common/cache.o \
./src/bsp/arch/arm_common/cpus.o \
./src/bsp/arch/arm_common/exception.o \
./src/bsp/arch/arm_common/exceptions.o \
./src/bsp/arch/arm_common/mmu.o \
./src/bsp/arch/arm_common/mmucache.o 

C_DEPS += \
./src/bsp/arch/arm_common/cache.d \
./src/bsp/arch/arm_common/exception.d \
./src/bsp/arch/arm_common/mmu.d 

S_UPPER_DEPS += \
./src/bsp/arch/arm_common/cpus.d \
./src/bsp/arch/arm_common/exceptions.d \
./src/bsp/arch/arm_common/mmucache.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/arch/arm_common/cache.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/cache.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/cpus.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/cpus.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/exception.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/exception.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/exceptions.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/exceptions.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/mmu.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/mmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/mmucache.o: C:/eclipseCppIndigo/djysrc/djyos/bsp/arch/arm/arm7_11/common/mmucache.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/arm9/omapl138_arm/include -ID:/djysdk/djysrc/examples/omapl138/src/user/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/std_inc -ID:/djysdk/djysrc/djyos/bsp/arch/arm/arm7_11/include -ID:/djysdk/djysrc/djyos/djyos/djyip/include -ID:/djysdk/djysrc/djyos/djyos/include -ID:/djysdk/djysrc/djyos/djyos/djyfs/include -ID:/djysdk/djysrc/djyos/djyos/gui/include -ID:/djysdk/djysrc/djyos/bsp/cpu_peripheral/omapl138/include -ID:/djysdk/djysrc/djyos/bsp/board_peripheral/omapl138/include -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


