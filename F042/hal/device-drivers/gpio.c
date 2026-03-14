#include "stm32.h"
#include "gpio.h"

#include "stm32f042-pins.h"
/*
Section 8 p. 125-140
Reference:
    https://www.st.com/resource/en/reference_manual/rm0360-stm32f030x4x6x8xc-and-stm32f070x6xb-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
*/

#define PULLDOWN_WAITTIME 150 // cycles

int pin_valid(uint32_t port, uint32_t pin) {
    
    // Handles ports A and B
    if (port <= GPIO_PORTB)
        if (pin <= PB15) // Could also use PA15
            return 1;

    // Handles port F
    if (port == GPIO_PORTF)
        if (pin <= PF1)
            return 1;
    
    return -1;
}

// ****************************************************************************************************
//                  Setup
// ****************************************************************************************************

// int gpio_init(uint32_t port) {
//     switch (port) {
//         case GPIO_PORTA:
//             clock_enable(port)
//             return 1;
//     }


//     if (port <= GPIO_PORTB || port == GPIO_PORTF)
//         clock_enable(port)
// }

int gpio_set_mode(uint32_t port, uint32_t pin, uint32_t mode) {
    // RM p. 158
    if (pin_valid(port, pin) < 0) return -1;
    if (mode & ~0b11) return -1; // Must be only in the lowest 2 bits
        

    // Each port is spaced out by 0x400
    uint32_t addr = (uint32_t)GPIOA_MODER + (GPIO_PORT_STRIDE * port);
    uint32_t mask_n = 0b11 << (pin*2);
    uint32_t value = GET32(addr);

    value &= ~mask_n;
    value |= mode << (pin*2);

    PUT32(addr, value);

    return 1;
}

int gpio_set_output(uint32_t port, uint32_t pin) {
    return gpio_set_mode(port, pin, GPIO_PIN_MODE_OUTPUT);
}
int gpio_set_input(uint32_t port, uint32_t pin) {
    return gpio_set_mode(port, pin, GPIO_PIN_MODE_INPUT);
}
int gpio_set_analog(uint32_t port, uint32_t pin) {
    return gpio_set_mode(port, pin, GPIO_PIN_MODE_ANALOG);
}

int gpio_set_alt(uint32_t port, uint32_t pin, uint32_t alt_function) {
    // RM p. 162
    if (pin_valid(port, pin) < 0) return -1;
    if (alt_function > 0b0111) return -1;

    // Pin validity already handled above
    gpio_set_mode(port, pin, GPIO_PIN_MODE_ALT);

    uint32_t afr_off = (pin < 8) ? 0x20 : 0x24; // AFRL or AFRH offset from GPIOx base
    uint32_t addr = GPIOA_BASE + GPIO_PORT_STRIDE * port + afr_off;

    uint32_t mask_n = 0b1111 << ( (pin % 8) * 4);
    uint32_t value = GET32(addr);

    value &= ~mask_n;
    value |= alt_function << ( (pin % 8) * 4);

    PUT32(addr, value);

    return 1;
}

// ****************************************************************************************************
//                  IO
// ****************************************************************************************************

int gpio_write(uint32_t port, uint32_t pin, uint32_t v) {
    // RM p. 161
    if(pin_valid(port, pin) < 0) return -1;

    uint32_t addr = (uint32_t)GPIOA_BSRR + (0x400 * port);

    // Shifted to higher 16 bits if turning OFF
    uint32_t val = 1 << (pin + (!v)*16);
    PUT32(addr, val);

    return 1;
}

int gpio_write_on(uint32_t port, uint32_t pin) {
    // RM p. 161
    return gpio_write(port, pin, 1);
}

int gpio_write_off(uint32_t port, uint32_t pin) {
    // RM p. 161
    return gpio_write(port, pin, 0);
}

int gpio_read(uint32_t port, uint32_t pin) {
    // RM p. 161
    if(pin_valid(port, pin < 0)) return -1;

    uint32_t addr = (uint32_t)GPIOA_IDR + (0x400 * port);

    // Shifted to higher 16 bits if turning OFF
    uint32_t value = GET32(addr);
    return (value >> pin) & 0b1;
}

// ****************************************************************************************************
//              Pullup/pulldown TODO
// ****************************************************************************************************

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