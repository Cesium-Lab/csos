#ifndef __PRINT_UTILS_H__
#define __PRINT_UTILS_H__

#include <stdint.h>
#include "uart.h"

void set_stdout(uart_t* uart);

int putk(const char* cstr);

void emit_num(char c, uint32_t base, uint8_t upper_hex);


#endif