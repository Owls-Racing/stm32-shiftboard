#ifndef MAIN_H
#define MAIN_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
#include "gpio.h"
#include "lora.h"
#include "can.h"
#include "multiplexer.h"
#include "shifting.h"

void system_clock_config(void);
void error_handler(void);

#endif
