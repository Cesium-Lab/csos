#include <stdint.h>

#include "hal/stm32f042-pins.h"
#include "stm32.h"

void delay(int count) {
    while(count--) { __asm("nop"); }
}

#define PB3          3

int main(void) {
    uint32_t reg;

    // 1) Enable GPIOB clock
    reg = GET32(RCC_AHBENR);
    reg |= RCC_AHBENR_IOPBEN;
    PUT32(RCC_AHBENR, reg);

    // 2) Configure PB0 as output (MODER0 = 01)
    reg = GET32(GPIOB_MODER);
    // reg &= ~(0x3 << (PB3 * 2));     // clear MODER0[1:0]
    // reg |=  (0x1 << (PB3 * 2));     // set to output
    // PUT32(GPIOB_MODER, reg);

    gpio_set_output(GPIO_PORTB, 3);


    while(1) {
        // try LED ON as PB3 LOW (active-low)
        PUT32(GPIOB_BSRR, (1u << (PB3 + 16))); // reset PB3 (drive low)
        delay(500000);

        PUT32(GPIOB_BSRR, (1u << PB3));        // set PB3 (drive high)
        delay(200000);
    }
}