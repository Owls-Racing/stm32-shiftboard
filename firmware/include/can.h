#ifndef CAN_H
#define CAN_H

#include "stm32f1xx_hal.h"

void can_init(void);
void can_handle(void);
uint8_t can_get_gear(void);
uint16_t can_get_rpm(void);
uint16_t can_get_speed(void);
uint8_t can_get_ath(void);
void can_send_shift_event(uint8_t upshift);
void can_receive_callback(uint8_t message_id, uint8_t* data, uint8_t length);
void error_handler(void);

#endif

