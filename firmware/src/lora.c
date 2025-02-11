#include "lora.h"
#include "stm32f1xx_hal_spi.h"
#include "can.h"

extern SPI_HandleTypeDef hspi1; // Make sure this is defined in your project

void lora_init(void) {
    // SPI initialization is assumed to be handled elsewhere
}

void lora_handle(void) {
    static uint32_t last_transmit_time = 0;
    uint32_t current_time = HAL_GetTick();

    if (current_time - last_transmit_time >= 100) {
        uint8_t gear = can_get_gear();
        uint16_t rpm = can_get_rpm();
        uint16_t speed = can_get_speed();
        uint8_t ath = can_get_ath();

        lora_transmit_data(gear, rpm, speed, ath);
        last_transmit_time = current_time;
    }
}

void lora_transmit_data(uint8_t gear, uint16_t rpm, uint16_t speed, uint8_t ath) {
    uint8_t buffer[6] = {gear, (rpm >> 8) & 0xFF, rpm & 0xFF, (speed >> 8) & 0xFF, speed & 0xFF, ath};
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, buffer, sizeof(buffer), HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}
