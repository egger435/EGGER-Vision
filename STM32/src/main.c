#include "stm32f10x.h"
#include "./Module/Serial.h"

void LED_Init(void);

void Setup()
{
    LED_Init();
    Serial_Init();

    GPIO_SetBits(GPIOA, GPIO_Pin_1);    
}

void Loop()
{
    // 接收串口数据..
    // TODO
}

// LED初始化, GPIOA1引脚
void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main()
{
    Setup();

    while (1)
    {
        Loop();
    }
}
