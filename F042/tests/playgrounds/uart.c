#include <stdint.h>

#include "hal/stm32f042-pins.h"
#include "stm32.h"
#include "libc/print-utils.h"

uart_t* uart = &UART2;

int main(void) {
    // 1) Enable GPIOB clock

    gpio_init(GPIO_PORTB);

    set_stdout(uart);
    
    uart->instance = 2;
    uart->baud = 115200;

    if (uart_init(uart) != STM32_SUCCESS) { // For clocks
        return 0;
    }

    uart_begin(uart);


    if (gpio_set_output(GPIO_PORTB, 3) < 0)    
        return 0;

    char c = 'H';
    const char* msg = "I am a c string\n\r";

    while(1) {

        emit_char(107, 16, 1);

        uart_put_cstr(uart, msg);

        delay(200000);
    }
}