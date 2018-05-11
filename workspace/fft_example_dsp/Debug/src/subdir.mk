################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/arm_cfft_f32.c \
../src/arm_cmplx_mag_f32.c \
../src/arm_common_tables.c \
../src/arm_const_structs.c \
../src/arm_fft_bin_data.c \
../src/arm_fft_bin_example_f32.c \
../src/arm_max_f32.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/arm_cfft_f32.o \
./src/arm_cmplx_mag_f32.o \
./src/arm_common_tables.o \
./src/arm_const_structs.o \
./src/arm_fft_bin_data.o \
./src/arm_fft_bin_example_f32.o \
./src/arm_max_f32.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/arm_cfft_f32.d \
./src/arm_cmplx_mag_f32.d \
./src/arm_common_tables.d \
./src/arm_const_structs.d \
./src/arm_fft_bin_data.d \
./src/arm_fft_bin_example_f32.d \
./src/arm_max_f32.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F4DISCOVERY -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DARM_MATH_CM4 -I"/home/lazarc/workspace/fft_example_dsp/Utilities" -I"/home/lazarc/workspace/fft_example_dsp/StdPeriph_Driver/inc" -I"/home/lazarc/workspace/fft_example_dsp/inc" -I"/home/lazarc/workspace/fft_example_dsp/CMSIS/device" -I"/home/lazarc/workspace/fft_example_dsp/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


