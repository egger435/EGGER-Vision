#ifndef __TESTLED_H
#define __TESTLED_H

#include "stm32f10x.h"

#define TestLED_GPIO GPIOA
#define TestLED_Pin GPIO_Pin_1  // 测试用LED引脚 PA1

extern uint8_t LED_State;
extern uint32_t LED_Timer;  // 由SysTick周期中断更新
extern uint8_t reverse_gear_LED_State;  // 倒档闪烁子状态

void TestLED_Init(void);
void TestLED_TurnOn(void);
void TestLED_TurnOff(void);
void TestLED_Toggle(void);
void LED_Flash_Control(void);

#endif