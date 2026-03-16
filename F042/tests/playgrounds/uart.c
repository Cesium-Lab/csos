#include <stdint.h>

#include "hal/stm32f042-pins.h"
#include "stm32.h"
#include "libc/print.h"

uart_t* uart = &UART2;

int main(void) {
    // 1) Enable GPIOB clock

    gpio_init(GPIO_PORTB);

    
    uart->instance = 2;
    uart->baud = 115200;

    print_begin(uart);

    // if (uart_init(uart) != STM32_SUCCESS) { // For clocks
    //     return 0;
    // }

    // uart_begin(uart);


    if (gpio_set_output(GPIO_PORTB, 3) < 0)    
        return 0;

    while(1) {

        // Wow it works yayy (never gonna do floats holy hell)
        printk("Crazy hex: %x %X %0x %0X \n\r", 0xE5, 0xE5, 0xE5, 0xE5);
        printk("Crazy num: %d %u %b %c \n\r", -500, -1, 254, 'c');
        printk("Crazy num: %d %d %u %b %c \n\r", -1, -500, -1, 0b10101011110100011010, 'c');
        printk("also a cstring: %s\n\r\n\r\n\r", "oh wow");

        delay(200000);
    }
}