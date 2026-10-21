################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/fsm_automatic.c \
../Core/Inc/input_processing.c \
../Core/Inc/input_reading.c \
../Core/Inc/led_display.c \
../Core/Inc/timer.c \
../Core/Inc/traffic_light.c 

OBJS += \
./Core/Inc/fsm_automatic.o \
./Core/Inc/input_processing.o \
./Core/Inc/input_reading.o \
./Core/Inc/led_display.o \
./Core/Inc/timer.o \
./Core/Inc/traffic_light.o 

C_DEPS += \
./Core/Inc/fsm_automatic.d \
./Core/Inc/input_processing.d \
./Core/Inc/input_reading.d \
./Core/Inc/led_display.d \
./Core/Inc/timer.d \
./Core/Inc/traffic_light.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o: ../Core/Inc/%.c Core/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

