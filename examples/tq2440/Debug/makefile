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
-include src/bsp/cpu_peripheral/src/subdir.mk
-include src/bsp/board_peripheral/nandflash/subdir.mk
-include src/bsp/board_peripheral/lcd/subdir.mk
-include src/bsp/board_peripheral/keypad/subdir.mk
-include src/bsp/arch/s3c2440/startup/subdir.mk
-include src/bsp/arch/s3c2440/core/subdir.mk
-include src/bsp/arch/arm_common/subdir.mk
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
tq2440.hex \

SECONDARY_LIST += \
tq2440.lst \

SECONDARY_SIZE += \
tq2440.siz \


# All Target
all: tq2440.elf secondary-outputs

# Tool invocations
tq2440.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"..\config\Debug.lds" -nostartfiles -Xlinker --gc-sections -Wl,-Map,tq2440.map -mcpu=arm920t -g3 -gdwarf-2 -o "tq2440.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

tq2440.hex: tq2440.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex tq2440.elf  "tq2440.hex"
	@echo 'Finished building: $@'
	@echo ' '

tq2440.lst: tq2440.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S tq2440.elf > "tq2440.lst"
	@echo 'Finished building: $@'
	@echo ' '

tq2440.siz: tq2440.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley tq2440.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) tq2440.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
