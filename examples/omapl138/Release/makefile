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
-include src/bsp/board_peripheral/lcd/subdir.mk
-include src/bsp/board_peripheral/keyboard/subdir.mk
-include src/bsp/board_peripheral/fpga/subdir.mk
-include src/bsp/arch/omapl138/startup/subdir.mk
-include src/bsp/arch/omapl138/core/subdir.mk
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
omapl138.hex \

SECONDARY_LIST += \
omapl138.lst \

SECONDARY_SIZE += \
omapl138.siz \


# All Target
all: omapl138.elf secondary-outputs

# Tool invocations
omapl138.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"..\config\Release.lds" -nostartfiles -Wl,-Map,omapl138.map -mcpu=arm920t -g3 -gdwarf-2 -o "omapl138.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

omapl138.hex: omapl138.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary omapl138.elf  "omapl138.hex"
	@echo 'Finished building: $@'
	@echo ' '

omapl138.lst: omapl138.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S omapl138.elf > "omapl138.lst"
	@echo 'Finished building: $@'
	@echo ' '

omapl138.siz: omapl138.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley omapl138.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) omapl138.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
