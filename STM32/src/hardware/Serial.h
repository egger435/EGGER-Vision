#ifndef __SERIAL_H
#define __SERIAL_H

#include <stm32f10x.h>

#define USART1_TX_PIN GPIO_Pin_9   // USART1_TX
#define USART1_RX_PIN GPIO_Pin_10  // USART1_RX
#define USART1_PI_BAUDRATE 115200  // 与树莓派通信串口波特率
#define USART1_BLE_BAUDRATE 9600   // 蓝牙调试波特率

extern char Serial_RxString[100];

void Serial_Init(void);
void Serial_SendByte(uint8_t byte);
void Serial_SendString(char *str);
uint8_t Serial_GetRxFlag(void);

#endif