#ifndef __TESTLED_H
#define __TESTLED_H

#include "stm32f10x.h"
#define TestLED_Pin GPIO_Pin_1  // 测试用LED引脚 PA1

extern uint8_t LED_State;

void TestLED_Init(void);
void TestLED_TurnOn(void);
void TestLED_TurnOff(void);

#endif