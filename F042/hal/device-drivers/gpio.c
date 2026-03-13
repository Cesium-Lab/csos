#include "stm32.h"
#include "gpio.h"

#include "stm32f042-pins.h"
/*
Section 8 p. 125-140
Reference:
    https://www.st.com/resource/en/reference_manual/rm0360-stm32f030x4x6x8xc-and-stm32f070x6xb-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
*/

#define PULLDOWN_WAITTIME 150 // cycles

int gpio_set_output(uint32_t port, uint32_t pin) {
    // p. 144

    // if(port > GPIO_PORTC)
    //     return 0;
    if(pin > GPIO_MAX_PIN)
        return 0;

    // Each port is spaced out by 0x400
     uint32_t addr = (uint32_t)GPIOA_MODER + (GPIO_PORT_STRIDE * port);
    //  uint32_t addr = (uint32_t)GPIOB_MODER;
     uint32_t mask_n = 0b11 << (pin*2);
     uint32_t value = GET32(addr);

    value &= ~mask_n;
    value |= 0b01 << (pin*2);

    PUT32(addr, value);

    return 1;
}

// // Set GPIO <pin> = on.
// int gpio_set_on(uint32_t port, uint32_t pin) {
//     if(port > GPIO_PORTC)
//         return 0;
//     if(pin > GPIO_MAX_PIN)
//         return 0;

//     volatile uint32_t addr = (uint32_t)GPIOA_MODER + (0x400 * port);
//     volatile uint32_t mask_n = 0b11 << pin;
//     volatile uint32_t value = get32(addr);

//     volatile uint32_t* gpio_addr = (uint32_t*) gpio_set0 + (pin / 32);
//     put32(gpio_addr, 1 << (pin % 32));

//     return 1;
// }

// // Set GPIO <pin> = off
// int gpio_set_off(uint32_t pin) {
//     if(port > GPIO_PORTC)
//         return 0;
//     if(pin > GPIO_MAX_PIN)
//         return 0;

//     // Implement this. 
//     // NOTE: 
//     //  - If you want to be slick, you can exploit the fact that 
//     //    SET0/SET1 are contiguous in memory.
//     volatile uint32_t addr = (uint32_t)GPIOA_MODER + (0x400 * port);
//     volatile uint32_t mask_n = 0b11 << pin;
//     volatile uint32_t value = get32(addr);

//     return 1;
// }

// // Set <pin> to <v> (v \in {0,1})
// int gpio_write(uint32_t pin, uint32_t v) {
//     if(v)
//         gpio_set_on(pin);
//     else
//         gpio_set_off(pin);
// }

// //
// // Part 2: implement gpio_set_input and gpio_read
// //

// // set <pin> = input.
// int gpio_set_input(uint32_t pin) {
//     if(pin > GPIO_MAX_PIN)
//         gpio_panic("illegal pin=%d\n", pin);

//     // Implement.
//     volatile uint32_t* gpio_addr = (uint32_t*) gpio_set0 + (pin / 10);
//     volatile uint32_t mask_n = 0b111 << (3 * (pin % 10));
//     volatile uint32_t value = get32(gpio_addr);

//     value &= ~mask_n;
//     // value |= 0b000 << (3 * (pin % 10)); don't need to set them for input

//     put32(gpio_addr, value);
// }

// // Return 1 if <pin> is on, 0 if not.
// int gpio_read(uint32_t pin) {
//     if(pin > GPIO_MAX_PIN)
//         gpio_panic("illegal pin=%d\n", pin);

//     volatile uint32_t* gpio_addr = (uint32_t*) gpio_lev0 + (pin / 32);
//     volatile uint32_t value = get32(gpio_addr);

//     return (value >> (pin % 32)) & 0b1;
// }


//
// Part 3: implement gpio_set_pullup and gpio_set_pulldown
//

// int gpio_set_pullup(uint32_t pin) {
//     if(pin > GPIO_MAX_PIN)
//         gpio_panic("illegal pin=%d\n", pin);

//     // Implement this.
    
//     // Write to GPPUD to enable control line and wait for the control line to set-up (?) 
//     put32((uint32_t*)gpio_pud, 0b10);
//     delay_cycles(PULLDOWN_WAITTIME);

//     // Write to GPPUDCLK0/1 to "Assert Clock on line (n)"
//     volatile uint32_t* pud_ck_addr = (uint32_t*) gpio_pudclk0 + (pin / 32);
//     put32(pud_ck_addr, 1 << (pin % 32));
//     delay_cycles(PULLDOWN_WAITTIME); // Iffy on whether we have to wait again (according to annotations on datasheet)

//     // Write back to GPPUD 
//     put32((uint32_t*)gpio_pud, 0);
//     put32(pud_ck_addr, 0);
// }


// int gpio_set_pulldown(uint32_t pin) {
//     if(pin > GPIO_MAX_PIN)
//         gpio_panic("illegal pin=%d\n", pin);

//     // Implement this.
    
//     put32((uint32_t*)gpio_pud, 0b01);
//     delay_cycles(PULLDOWN_WAITTIME);

//     volatile uint32_t* pud_ck_addr = (uint32_t*) gpio_pudclk0 + (pin / 32);
//     put32(pud_ck_addr, 1 << (pin % 32));
//     delay_cycles(PULLDOWN_WAITTIME); // Iffy on whether we have to wait again (according to annotations on datasheet)

//     put32((uint32_t*)gpio_pud, 0);
//     put32(pud_ck_addr, 0);
// }