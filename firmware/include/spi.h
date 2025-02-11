#ifndef SPI_H
#define SPI_H

#include "stm32f1xx_hal.h"

extern SPI_HandleTypeDef hspi1;  // Global SPI handle

void spi_init(void);

#endif
