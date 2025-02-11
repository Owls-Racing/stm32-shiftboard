#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include "stm32f1xx_hal.h"

#define MULTIPLEXER_MIN 0
#define MULTIPLEXER_MAX 11

void multiplexer_init(void);
void multiplexer_handle(void);
void multiplexer_set_channel(uint8_t channel);
uint8_t multiplexer_get_current_channel(void);

#endif
