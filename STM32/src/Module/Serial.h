#ifndef __SERIAL_H
#define __SERIAL_H

#include <stm32f10x.h>

extern char Serial_RxString[100];

void Serial_Init(void);
uint8_t Serial_GetRxFlag(void);

#endif