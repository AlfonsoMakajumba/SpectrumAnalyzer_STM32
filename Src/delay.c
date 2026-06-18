#include "Inc/stm32f446xx.h"
#include <stdint.h>
#include "config.h"

volatile uint32_t msElapsed = 0;

void SysTick_init(void)
{
    SysTick -> LOAD = (CPU_CLOCK / 1000) - 1;
    SysTick -> VAL = 0;
    SysTick -> CTRL = (1 << 0) | (1 << 1) | (1 << 2);
}

void SysTick_Handler(void)
{
    msElapsed++;
}

void delay_ms(uint32_t ms)
{
    uint32_t time = msElapsed;
    while((msElapsed - time) < ms);
}
