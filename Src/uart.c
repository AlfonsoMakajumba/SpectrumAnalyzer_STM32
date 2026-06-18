#include "config.h"
#include "Inc/stm32f4xx.h"
#include "stdint.h"

//PA2 and PA3 are wired to ST-LINK UART2, PA2 - TX, PA3 - RX, as stated in DS10693 p. (47 & 48) / 197

void uart_init(uint32_t baud)
{
    RCC -> AHB1ENR |= (1 << 0); //clock turn on for GPIOA
    RCC -> APB1ENR |= (1 << 17); //clock turn on for USART2

    GPIOA -> MODER &= ~(0b11 << 4); //clear bit 4 and 5 
    GPIOA -> MODER |= (0b10 << 4); //config PA2 as alternate function

    //struggled to find any info bout this, but DS10693 p. 58/197 came in clutch
    //alternate function for PA2 is UART2_TX(we need that), and its AF7 - so that means 
    //that we have to write 0b0111 = 0d7, into AFRL - as stated in RM0390 p. 189/1321 section 7.4.9
    //why AFRL? cause it corresponds to PA2, AFRL is for ports from 0 to 7, while AFRH is for port 8 to 15
    //some fucker in ST thought that a great idea would be to call AFRL AFR[0] and AFRH AFR[1](this took me so long to find),

    GPIOA -> AFR[0] &= ~(0b1111 << 8)   ; //clear 4 bits for AF7 in AFRL
    GPIOA -> AFR[0] |= (0b0111 << 8); //set 0d7 = 0b0111 to make PA2 into alternate function

    //now we gotta set the baudrate which is weird af
    //theres this equation Baud = f_ck / ( 8 * (2 - OVER8) * USARTDIV )
    //and since OVER8 is in our case 0(we sample the same bit 16 times to make sure - fewer errors, two times slower)
    //we are left with Baud = f_ck / (16 * USARTDIV), which translates to
    //USARTDIV = f_ck / (16 * Baud), and since we have manttis and a fraction represented with 4 bits, 
    //we have to multiply the result by 16(every bit in fraction is 1/2, so its 1/2 multiplied to the power of 4
    //which leaves us with 1/16, so it gets cancelled via multiplication by 16)
    //so the final formula is USARTDIV = f_ck / Baud 
    //apply only to cases with OVER8 == 8

    USART2 -> BRR = CPU_CLOCK / baud; //calculation for baud rate, well rather after how many cycles we have to read
    USART2 -> CR1 |= (1 << 13) | (1 << 3); // 13 is enabling uart and 3 enabling transmitter
}

void ser_write(char c)
{
    while(!(USART2 -> SR & (1 << 7))); // 7th bit is set to 1 DR is empty
    USART2 -> DR = c; //we put c into TDR(Transmit Data Register), again its stupid - DR is a shared namespace for TDR and RDR
    //only difference is that TDR is when we transmit from the DR and RDR is when we read from it XD
}

void ser_print(char *str) //pointer is more lightweight than a whole string - cause it can be a hella long string
{
    while(*str)
    {
        ser_write(*str++);
    }
}