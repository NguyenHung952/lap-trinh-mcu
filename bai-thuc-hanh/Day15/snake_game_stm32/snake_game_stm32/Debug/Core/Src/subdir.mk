################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/button.c \
../Core/Src/button_adapter.c \
../Core/Src/buzzer.c \
../Core/Src/collision.c \
../Core/Src/food.c \
../Core/Src/food_renderer.c \
../Core/Src/framebuffer.c \
../Core/Src/game.c \
../Core/Src/grid.c \
../Core/Src/lcd.c \
../Core/Src/lcd_renderer.c \
../Core/Src/led.c \
../Core/Src/main.c \
../Core/Src/random.c \
../Core/Src/render.c \
../Core/Src/renderer_utils.c \
../Core/Src/snake.c \
../Core/Src/snake_ai.c \
../Core/Src/snake_renderer.c \
../Core/Src/stm32f2xx_hal_msp.c \
../Core/Src/stm32f2xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f2xx.c \
../Core/Src/timer.c \
../Core/Src/timer_adapter.c 

OBJS += \
./Core/Src/button.o \
./Core/Src/button_adapter.o \
./Core/Src/buzzer.o \
./Core/Src/collision.o \
./Core/Src/food.o \
./Core/Src/food_renderer.o \
./Core/Src/framebuffer.o \
./Core/Src/game.o \
./Core/Src/grid.o \
./Core/Src/lcd.o \
./Core/Src/lcd_renderer.o \
./Core/Src/led.o \
./Core/Src/main.o \
./Core/Src/random.o \
./Core/Src/render.o \
./Core/Src/renderer_utils.o \
./Core/Src/snake.o \
./Core/Src/snake_ai.o \
./Core/Src/snake_renderer.o \
./Core/Src/stm32f2xx_hal_msp.o \
./Core/Src/stm32f2xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f2xx.o \
./Core/Src/timer.o \
./Core/Src/timer_adapter.o 

C_DEPS += \
./Core/Src/button.d \
./Core/Src/button_adapter.d \
./Core/Src/buzzer.d \
./Core/Src/collision.d \
./Core/Src/food.d \
./Core/Src/food_renderer.d \
./Core/Src/framebuffer.d \
./Core/Src/game.d \
./Core/Src/grid.d \
./Core/Src/lcd.d \
./Core/Src/lcd_renderer.d \
./Core/Src/led.d \
./Core/Src/main.d \
./Core/Src/random.d \
./Core/Src/render.d \
./Core/Src/renderer_utils.d \
./Core/Src/snake.d \
./Core/Src/snake_ai.d \
./Core/Src/snake_renderer.d \
./Core/Src/stm32f2xx_hal_msp.d \
./Core/Src/stm32f2xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f2xx.d \
./Core/Src/timer.d \
./Core/Src/timer_adapter.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/button.cyclo ./Core/Src/button.d ./Core/Src/button.o ./Core/Src/button.su ./Core/Src/button_adapter.cyclo ./Core/Src/button_adapter.d ./Core/Src/button_adapter.o ./Core/Src/button_adapter.su ./Core/Src/buzzer.cyclo ./Core/Src/buzzer.d ./Core/Src/buzzer.o ./Core/Src/buzzer.su ./Core/Src/collision.cyclo ./Core/Src/collision.d ./Core/Src/collision.o ./Core/Src/collision.su ./Core/Src/food.cyclo ./Core/Src/food.d ./Core/Src/food.o ./Core/Src/food.su ./Core/Src/food_renderer.cyclo ./Core/Src/food_renderer.d ./Core/Src/food_renderer.o ./Core/Src/food_renderer.su ./Core/Src/framebuffer.cyclo ./Core/Src/framebuffer.d ./Core/Src/framebuffer.o ./Core/Src/framebuffer.su ./Core/Src/game.cyclo ./Core/Src/game.d ./Core/Src/game.o ./Core/Src/game.su ./Core/Src/grid.cyclo ./Core/Src/grid.d ./Core/Src/grid.o ./Core/Src/grid.su ./Core/Src/lcd.cyclo ./Core/Src/lcd.d ./Core/Src/lcd.o ./Core/Src/lcd.su ./Core/Src/lcd_renderer.cyclo ./Core/Src/lcd_renderer.d ./Core/Src/lcd_renderer.o ./Core/Src/lcd_renderer.su ./Core/Src/led.cyclo ./Core/Src/led.d ./Core/Src/led.o ./Core/Src/led.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/random.cyclo ./Core/Src/random.d ./Core/Src/random.o ./Core/Src/random.su ./Core/Src/render.cyclo ./Core/Src/render.d ./Core/Src/render.o ./Core/Src/render.su ./Core/Src/renderer_utils.cyclo ./Core/Src/renderer_utils.d ./Core/Src/renderer_utils.o ./Core/Src/renderer_utils.su ./Core/Src/snake.cyclo ./Core/Src/snake.d ./Core/Src/snake.o ./Core/Src/snake.su ./Core/Src/snake_ai.cyclo ./Core/Src/snake_ai.d ./Core/Src/snake_ai.o ./Core/Src/snake_ai.su ./Core/Src/snake_renderer.cyclo ./Core/Src/snake_renderer.d ./Core/Src/snake_renderer.o ./Core/Src/snake_renderer.su ./Core/Src/stm32f2xx_hal_msp.cyclo ./Core/Src/stm32f2xx_hal_msp.d ./Core/Src/stm32f2xx_hal_msp.o ./Core/Src/stm32f2xx_hal_msp.su ./Core/Src/stm32f2xx_it.cyclo ./Core/Src/stm32f2xx_it.d ./Core/Src/stm32f2xx_it.o ./Core/Src/stm32f2xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f2xx.cyclo ./Core/Src/system_stm32f2xx.d ./Core/Src/system_stm32f2xx.o ./Core/Src/system_stm32f2xx.su ./Core/Src/timer.cyclo ./Core/Src/timer.d ./Core/Src/timer.o ./Core/Src/timer.su ./Core/Src/timer_adapter.cyclo ./Core/Src/timer_adapter.d ./Core/Src/timer_adapter.o ./Core/Src/timer_adapter.su

.PHONY: clean-Core-2f-Src

