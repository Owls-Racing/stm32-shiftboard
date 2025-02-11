#include "shifting.h"
#include "gpio.h"
#include "can.h"

static uint8_t shiftLock = 0;
static uint32_t tcButtonHoldTime = 0;
static uint8_t currentGear = 1;


static const uint16_t solenoidPulseTimes[7] = {0, 50, 55, 60, 65, 70, 75}; //shiz in ms

void shifting_init(void) {
    currentGear = can_get_gear();
}

void shifting_handle(void) {
    uint32_t currentTime = HAL_GetTick();
    uint8_t upButton = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
    uint8_t downButton = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);

    if (upButton && downButton) {
        return;  
    }

    if (upButton && !shiftLock && currentGear < 6) {
        shiftLock = 1;
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
        HAL_Delay(solenoidPulseTimes[currentGear]);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
        currentGear++;  // Increment gear
        can_send_shift_event(1);  // Log upshift
    }

  
    else if (downButton && !shiftLock && currentGear > 1) {
        shiftLock = 1;
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
        HAL_Delay(solenoidPulseTimes[currentGear]);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
        currentGear--; 
        can_send_shift_event(0); 
    }


    if (!upButton && !downButton) {
        shiftLock = 0;
    }

 
    if (currentGear == 1 && upButton && downButton) {
        tcButtonHoldTime += 10;  
        if (tcButtonHoldTime >= NEUTRAL_HOLD_TIME) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
            HAL_Delay(50); 
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
            tcButtonHoldTime = 0; 
        }
    } else {
        tcButtonHoldTime = 0; 
    }
}
