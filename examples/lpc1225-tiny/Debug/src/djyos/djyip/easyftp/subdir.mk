################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/djysdk/djysrc/djyos/djyos/djyip/easyftp/easyftp.c 

OBJS += \
./src/djyos/djyip/easyftp/easyftp.o 

C_DEPS += \
./src/djyos/djyip/easyftp/easyftp.d 


# Each subdirectory must supply rules for building sources it contributes
src/djyos/djyip/easyftp/easyftp.o: D:/djysdk/djysrc/djyos/djyos/djyip/easyftp/easyftp.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Ddebug -I"D:/djysdk/djysrc/examples/lpc1225-tiny/src/user/include" -I"D:/djysdk/djysrc/examples/lpc1225-tiny/src/user/config" -I"D:\djysdk\\djysrc\djyos\djyos\include" -I"D:\djysdk\\djysrc\djyos\djyos\gui\include" -I"D:\djysdk\\djysrc\djyos\djyos\djyfs\include" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\std_inc" -I"D:\djysdk\\djysrc\djyos\bsp\arch\arm\cortex_m\cortex_m0\include" -I"D:\djysdk\\djysrc\djyos\bsp\vendor_lib/CMSIS/CM0/CoreSupport" -I"D:\djysdk\\djysrc\djyos\bsp\cpu_peripheral\lpc12xx\include" -O0 -Wall -std=c99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m0 -mthumb -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


