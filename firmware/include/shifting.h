#ifndef SHIFTING_H
#define SHIFTING_H

#include "stm32f1xx_hal.h"

#define NEUTRAL_HOLD_TIME 3000  // 3 seconds hold time for neutral shift

void shifting_init(void);
void shifting_handle(void);

#endif
