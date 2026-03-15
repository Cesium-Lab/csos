#include "stm32.h"
#include "stm32f042-pins.h"


void clock_set(uint32_t reg, uint32_t clock, uint32_t state) {
    uint32_t value;

    value = GET32(reg);

    if (state)
        value |= clock;
    else
        value &= ~clock;

    PUT32(reg, value);
}