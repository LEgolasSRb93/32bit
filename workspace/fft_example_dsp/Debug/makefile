################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include Utilities/subdir.mk
-include StdPeriph_Driver/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: fft_example_dsp.elf

# Tool invocations
fft_example_dsp.elf: $(OBJS) $(USER_OBJS) /home/lazarc/workspace/fft_example_dsp/LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -specs=nosys.specs -specs=rdimon.specs -lc -lrdimon -T"/home/lazarc/workspace/fft_example_dsp/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "fft_example_dsp.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "fft_example_dsp.elf" "fft_example_dsp.bin"
	arm-none-eabi-size "fft_example_dsp.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
