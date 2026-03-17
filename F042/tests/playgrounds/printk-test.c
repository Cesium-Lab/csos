#include <stdint.h>

#include "hal/stm32f042-pins.h"
#include "stm32.h"
#include "libc/print.h"

uart_t* uart = &UART2;

void clock_init_48mhz(void) {
    // RM0091 p.94 - Enable HSI48
    #define RCC_CR2         (RCC_BASE + 0x34)
    #define RCC_CR2_HSI48ON (1 << 16)
    #define RCC_CR2_HSI48RDY (1 << 17)
    
    uint32_t val;
    
    // Turn on HSI48
    val = GET32(RCC_CR2);
    val |= RCC_CR2_HSI48ON;
    PUT32(RCC_CR2, val);
    
    // Wait for ready
    while (!(GET32(RCC_CR2) & RCC_CR2_HSI48RDY)) {
        ;
    }
    
    // Switch system clock to HSI48 (SW = 0b11)
    val = GET32(RCC_CFGR);
    val &= ~(0x3 << 0);  // Clear SW[1:0]
    val |= (0x3 << 0);   // Set SW = 11 (HSI48)
    PUT32(RCC_CFGR, val);
    
    // Wait for switch complete (SWS = 0b11)
    while ((GET32(RCC_CFGR) & (0x3 << 2)) != (0x3 << 2)) {
        ;
    }
}

int main(void) {
    clock_init_48mhz();

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

    printk("UART_CR1_OFFSET    0x00: %0x\n\r", GET32(uart->base_reg + UART_CR1_OFFSET));
    printk("UART_CR2_OFFSET    0x04: %0x\n\r", GET32(uart->base_reg + UART_CR2_OFFSET));
    printk("UART_CR3_OFFSET    0x08: %0x\n\r", GET32(uart->base_reg + UART_CR3_OFFSET));
    printk("UART_BRR_OFFSET    0x0C: %0x\n\r", GET32(uart->base_reg + UART_BRR_OFFSET));
    printk("UART_GTPR_OFFSET   0x10: %0x\n\r", GET32(uart->base_reg + UART_GTPR_OFFSET));
    printk("UART_RTOR_OFFSET   0x14: %0x\n\r", GET32(uart->base_reg + UART_RTOR_OFFSET));
    printk("UART_RQR_OFFSET    0x18: %0x\n\r", GET32(uart->base_reg + UART_RQR_OFFSET));
    printk("UART_ISR_OFFSET    0x1C: %0x\n\r", GET32(uart->base_reg + UART_ISR_OFFSET));
    printk("UART_ICR_OFFSET    0x20: %0x\n\r", GET32(uart->base_reg + UART_ICR_OFFSET));
    printk("UART_RDR_OFFSET    0x24: %0x\n\r", GET32(uart->base_reg + UART_RDR_OFFSET));
    printk("UART_TDR_OFFSET    0x28: %0x\n\r", GET32(uart->base_reg + UART_TDR_OFFSET));


    printk("Crazy num: %d %u %b %c \n\r", -500, -1, 254, 'c');
    printk("Crazy num: %d %d %u %b %c \n\r", -1, -500, -1, 0b10101011110100011010, 'c');
    printk("also a cstring: %s\n\r\n\r\n\r", "oh wow");

    while (1)
        ;
}