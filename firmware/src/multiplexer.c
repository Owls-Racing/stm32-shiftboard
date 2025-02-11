#include "multiplexer.h"
#include "gpio.h"

static uint8_t current_channel = 0;

void multiplexer_init(void) {
    current_channel = 0;
    multiplexer_set_channel(current_channel);
}

void multiplexer_handle(void) {
    uint8_t upButton = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
    uint8_t downButton = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
    static uint8_t lastUpState = 0;
    static uint8_t lastDownState = 0;

    if (upButton && !lastUpState && current_channel < MULTIPLEXER_MAX) {
        current_channel++;
        multiplexer_set_channel(current_channel);
    }

    if (downButton && !lastDownState && current_channel > MULTIPLEXER_MIN) {
        current_channel--;
        multiplexer_set_channel(current_channel);
    }

    lastUpState = upButton;
    lastDownState = downButton;
}

void multiplexer_set_channel(uint8_t channel) {
    if (channel > MULTIPLEXER_MAX) {
        return;
    }

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (channel & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (channel & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (channel & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (channel & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

uint8_t multiplexer_get_current_channel(void) {
    return current_channel;
}
