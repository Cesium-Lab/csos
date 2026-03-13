#ifndef __GPIO_H__
#define __GPIO_H__
/*
Section 8 p. 125-140
Reference:
    https://www.st.com/resource/en/reference_manual/rm0360-stm32f030x4x6x8xc-and-stm32f070x6xb-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
*/


#include "stm32f042-pins.h"

#define gpio_panic(msg...) panic(msg)

enum {
    GPIO_MAX_PIN = 16
};

// ****************************************************************************************************
//                  Setup
// ****************************************************************************************************

// Configure GPIO <pin> as an output pin.
int gpio_set_output(uint32_t port, uint32_t pin);

// Configure GPIO <pin> as an input pin.
int gpio_set_input(uint32_t port, uint32_t pin);

// ****************************************************************************************************
//                  IO
// ****************************************************************************************************

// Set GPIO <pin> on.
int gpio_set_on(uint32_t port, uint32_t pin);

// Set GPIO<pin> off.
int gpio_set_off(uint32_t port, uint32_t pin);

// Set GPIO <pin> to <v>.
int gpio_write(uint32_t port, uint32_t pin, uint32_t v);

// Read the current value of GPIO <pin>.
// Returns either 0 or 1.
int gpio_read(uint32_t port, uint32_t pin);

// ****************************************************************************************************
//                  GPIO Pullup/Down routines
// ****************************************************************************************************

/**
 * Activate the pullup register on GPIO <pin>.
 *
 * GPIO <pin> must be an input pin.
 */
int gpio_set_pullup(uint32_t port, uint32_t pin);

/**
 * Activate the pulldown register on GPIO <pin>.
 *
 * GPIO <pin> must be an input pin.
 */
int gpio_set_pulldown(uint32_t port, uint32_t pin);

/**
 * Deactivate both the pullup and pulldown registers on GPIO <pin>.
 *
 * GPIO <pin> must be an input pin.
 */
int gpio_pud_off(uint32_t port, uint32_t pin);


#endif