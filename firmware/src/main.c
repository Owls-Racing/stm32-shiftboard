#include "main.h"

void system_clock_config(void);

int main(void) {
    // Initialize HAL and system clock
    HAL_Init();
    system_clock_config();

    // Initialize peripherals
    gpio_init();
    can_init();
    lora_init();
    multiplexer_init();  // Ensure this is properly defined
    shifting_init();

    // Main loop
    while (1) {
        multiplexer_handle();  // Ensure this is properly defined
        shifting_handle();
        lora_handle();
        can_handle();
    }
}

// System clock configuration function
void system_clock_config(void) {
    RCC_OscInitTypeDef osc_init = {0};
    RCC_ClkInitTypeDef clk_init = {0};

    // Enable High-Speed External (HSE) oscillator
    osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    osc_init.HSEState = RCC_HSE_ON;
    osc_init.PLL.PLLState = RCC_PLL_ON;
    osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    osc_init.PLL.PLLMUL = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&osc_init) != HAL_OK) {
        error_handler();
    }

    // Configure clock sources
    clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                         RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
    clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&clk_init, FLASH_LATENCY_2) != HAL_OK) {
        error_handler();
    }
}

// Generic error handler
void error_handler(void) {
    while (1) {
        // Stay here if an error occurs
    }
}
