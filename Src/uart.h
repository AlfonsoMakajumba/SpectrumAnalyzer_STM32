#include "stdint.h"

void uart_init(uint32_t baud);
void ser_write(char c);
void ser_print(char *str);