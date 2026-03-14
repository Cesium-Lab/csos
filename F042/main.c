#include <stdint.h>

#include "hal/stm32f042-pins.h"
#include "stm32.h"

void delay(int count) {
    while(count--) { __asm("nop"); }
}

// Write 1 to state for on, 0 for off
// void clock_enable(uint32_t reg, uint32_t clock, uint32_t state) {
//     uint32_t value;

//     value = GET32(reg);

//     if (state)
//         value |= clock;
//     else
//         value &= ~clock;

//     PUT32(reg, value);
// }

int main(void) {
    // 1) Enable GPIOB clock
    // uint32_t reg = GET32(RCC_AHBENR);
    // reg |= RCC_AHB_B_EN;
    // PUT32(RCC_AHBENR, reg);

    clock_enable(RCC_AHBENR, RCC_AHB_B_EN, 1);

    // gpio_set_output(GPIO_PORTB, 3);
    if (gpio_set_output(GPIO_PORTB, 3) < 0)    
        return 0;

    while(1) {
        gpio_write_off(GPIO_PORTB, PB3);
        delay(500000);
        gpio_write_on(GPIO_PORTB, PB3);
        delay(200000);
    }
}