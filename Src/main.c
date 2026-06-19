#include "config.h"
#include <stdint.h>
#include "Inc/stm32f4xx.h"

#include "delay.h"
#include "uart.h"

int main(void)
{
    RCC -> AHB1ENR |= (1 << 0); //enables clock for GPIOA, RM0390 p. 142/1321
    GPIOA -> MODER &= ~(0b11 << 10); //clears bit 10 and 11 in MODER register, RM0390 p. 185/1321
    GPIOA -> MODER |= (0b01 << 10); //sets bit 10 and 11 to 01 accordingly, RM0390 p. 185/1321

    SysTick_init();

    uart_init(115200);

	while(1)
    {
        GPIOA -> ODR ^= (1 << 5); //sets PA5 to high if its low and to low if its high, RM0390 p. 187/1321
        ser_print("Led changed");
        delay_ms(1000);
    }
}

