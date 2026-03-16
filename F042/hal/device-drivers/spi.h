#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

#include "stm32f042-pins.h"

// interface that allows use of chip 1 + chip 0
typedef struct {
    uint32_t instance;
    uint32_t div;
    uint32_t cs_port;
    uint32_t cs_pin;
} spi_t;



// pass either of these for chip select.

#define SPI1_CS PA15
#define SPI2_CS1 PB12
#define SPI2_CS2 PB9


int spi_begin(spi_t* spi, uint32_t chip_select, uint32_t clock_divider);

// tx and rx must be the same size; easy to have dedicated rx or tx.
int spi_transfer(spi_t* spi, uint8_t* rx, const uint8_t* tx, uint32_t nbytes);

// Give initialized `spi_t` 
spi_t spi_t_get(uint32_t instance, uint32_t chip_select, uint32_t clock_divider);


#endif
