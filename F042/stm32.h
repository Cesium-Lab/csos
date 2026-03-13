#ifndef __STM32_H__
#define __STM32_H__

#include <stdint.h>

#include "gpio.h"

// ****************************************************************************************************
//                  Lowest level (defined in startup.s)
// ****************************************************************************************************

void PUT32(uint32_t addr, uint32_t v);
void put32(volatile void *addr, uint32_t v);

// *(uint32_t *)addr
uint32_t GET32(uint32_t addr);
uint32_t get32(const volatile void *addr);

// check port fn

#endif