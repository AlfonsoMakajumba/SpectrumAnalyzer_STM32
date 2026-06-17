//i promise i will do it properly one

#include <stdint.h>
#define SYS_CLOCK 16000000 //16MHz base, can be changed later when or if i add PLL

uint32_t cycles_ps = SYS_CLOCK / 8000; 

void delay_ms(volatile uint32_t ms)
{
    uint32_t count = ms * cycles_ps;
    while(count--)
    {
        __asm("nop"); //assembly inline for skipping a cycle of a CPU
    }
}