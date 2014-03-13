################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/user/src/subdir.mk
-include src/user/critical/subdir.mk
-include src/user/config/subdir.mk
-include src/loader/si/subdir.mk
-include src/djyos/wdt/subdir.mk
-include src/djyos/stdin/touch/subdir.mk
-include src/djyos/stdin/keypad/subdir.mk
-include src/djyos/stdin/char_term/subdir.mk
-include src/djyos/stdin/subdir.mk
-include src/djyos/shell/subdir.mk
-include src/djyos/rsc/subdir.mk
-include src/djyos/pipe/subdir.mk
-include src/djyos/msg/subdir.mk
-include src/djyos/memory/subdir.mk
-include src/djyos/lock/subdir.mk
-include src/djyos/int/subdir.mk
-include src/djyos/gui/window/subdir.mk
-include src/djyos/gui/lib/subdir.mk
-include src/djyos/gui/gk_draw/subdir.mk
-include src/djyos/gui/font/subdir.mk
-include src/djyos/gui/encoding/subdir.mk
-include src/djyos/gui/display/subdir.mk
-include src/djyos/driver/subdir.mk
-include src/djyos/djyfs/flashfile/subdir.mk
-include src/djyos/djyfs/subdir.mk
-include src/djyos/core/subdir.mk
-include src/djyos/clock/subdir.mk
-include src/djyos/buffer/subdir.mk
-include src/bsp/vendor_lib/CMSIS/CoreSupport/subdir.mk
-include src/bsp/cpu_peripheral/src/subdir.mk
-include src/bsp/arch/startup/subdir.mk
-include src/bsp/arch/core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
easy175x.hex \

SECONDARY_LIST += \
easy175x.lst \

SECONDARY_SIZE += \
easy175x.siz \


# All Target
all: easy175x.elf secondary-outputs

# Tool invocations
easy175x.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"..\config\debug.lds" -nostartfiles -Wl,-Map,easy175x.map -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o "easy175x.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

easy175x.hex: easy175x.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex easy175x.elf  "easy175x.hex"
	@echo 'Finished building: $@'
	@echo ' '

easy175x.lst: easy175x.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S easy175x.elf > "easy175x.lst"
	@echo 'Finished building: $@'
	@echo ' '

easy175x.siz: easy175x.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley easy175x.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) easy175x.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
