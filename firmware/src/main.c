#include "stm32f1xx.h"

void delay(int count) {
    for (volatile int i = 0; i < count * 1000; i++);
}

int main(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;  // Enable GPIOC clock
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
    GPIOC->CRH |= GPIO_CRH_MODE13_1;  // Set PC13 as output

    while (1) {
        GPIOC->BSRR = GPIO_BSRR_BS13;  // LED ON
        delay(500);
        GPIOC->BSRR = GPIO_BSRR_BR13;  // LED OFF
        delay(500);
    }
}