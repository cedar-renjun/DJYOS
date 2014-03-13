################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/cache.c \
C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/exception.c \
C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/mmu.c 

S_UPPER_SRCS += \
C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/cpus.S \
C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/exceptions.S \
C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/mmucache.S 

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
src/bsp/arch/arm_common/cache.o: C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/cache.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/tq2440/src/user/include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\tq2440\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\djyos\djyip\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\/djysrc/djyos/djyfs/include" -I"C:\djysdk\/djysrc/djyos/gui/include" -O0 -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/cpus.o: C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/cpus.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -I"C:\djysdk\/djysrc/bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/exception.o: C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/exception.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/tq2440/src/user/include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\tq2440\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\djyos\djyip\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\/djysrc/djyos/djyfs/include" -I"C:\djysdk\/djysrc/djyos/gui/include" -O0 -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/exceptions.o: C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/exceptions.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -I"C:\djysdk\/djysrc/bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/mmu.o: C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/mmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"C:/djysdk/djyos_workspace/examples/tq2440/src/user/include" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\std_inc" -I"C:\djysdk\\djysrc\bsp\cpu_peripheral\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\bsp\board_peripheral\tq2440\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\include" -I"C:\djysdk\\djysrc\bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -I"C:\djysdk\\djysrc\djyos\djyip\include" -I"C:\djysdk\\djysrc\djyos\include" -I"C:\djysdk\/djysrc/djyos/djyfs/include" -I"C:\djysdk\/djysrc/djyos/gui/include" -O0 -fdata-sections -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/bsp/arch/arm_common/mmucache.o: C:/djysdk/djysrc/bsp/arch/arm/arm7_11/common/mmucache.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Ddebug -I"C:\djysdk\/djysrc/bsp\arch\arm\arm7_11\arm9\samsung\s3c2440\include" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm920t -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


