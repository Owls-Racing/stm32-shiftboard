#ifndef LORA_H
#define LORA_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"

void lora_init(void);
void lora_handle(void);
void lora_transmit_data(uint8_t gear, uint16_t rpm, uint16_t speed, uint8_t ath);

#endif
