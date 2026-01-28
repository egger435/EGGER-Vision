#include "stm32f10x.h"
#include "TestLED.h"

uint8_t LED_State;

// LED初始化
void TestLED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = TestLED_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TestLED_TurnOn();
}

// LED亮
void TestLED_TurnOn(void)
{
    GPIO_SetBits(GPIOA, TestLED_Pin);
    LED_State = 1;
}

// LED关闭
void TestLED_TurnOff(void)
{
    GPIO_ResetBits(GPIOA, TestLED_Pin);
    LED_State = 0;
}