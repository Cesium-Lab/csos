#include "print-utils.h"
#include "stm32.h"
#include "uart.h"

uart_t* _stdout;

void set_stdout(uart_t* uart) {
    if (!uart) return;
    _stdout = uart;
}

void emit_num(char c, uint32_t base, uint8_t upper_hex) {
    char buf[33]; // 33 = 32 + 1(bc uint32_t in base 2)
    char* p = buf;

    

    switch(base) {
    case 2:
        do {
            *p++ = "01"[c % 2];
        } while(c /= 2);
        break;
    case 10:
        do {
            *p++ = "0123456789"[c % 10];
        } while(c /= 10);
        break;
    case 16: // Take care of upper hex
        if (upper_hex)
            do {    
                *p++ = "0123456789ABCDEF"[c % 16];
            } while(c /= 16);
        else 
            do {    
                *p++ = "0123456789abcdef"[c % 16];
            } while(c /= 16);
            
        break;
    default: 
        // panic("invalid base=%d\n", base);
        return;
    }

    // buffered in reverse, so emit backwards
    while(p > buf) {
        p--;
        uart_put8(_stdout, *p);
    }
}