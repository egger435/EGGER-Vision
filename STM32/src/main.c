#include "stm32f10x.h"
#include "./Module/Serial.h"

uint8_t LED_State = 0;
void LED_Init(void);
void LED_Ctrl(char *cmd);

void Setup(void)
{
    LED_Init();
    Serial_Init();

    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    LED_State = 0;    
}

void Loop(void)
{
    if (Serial_GetRxFlag() == 1)
    {
        LED_Ctrl(Serial_RxString);
    }
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

// LED控制
void LED_Ctrl(char *cmd)
{
    if (cmd[0] == '0' && cmd[1] == '0')
    {
        if (LED_State == 1)
        {
            GPIO_ResetBits(GPIOA, GPIO_Pin_1);
            LED_State = !LED_State;
        }
    }
    else if (cmd[0] == '1' && cmd[1] == '1')
    {
        if (LED_State == 0)
        {
            GPIO_SetBits(GPIOA, GPIO_Pin_1);
            LED_State = !LED_State;
        }
    }
    else if (cmd[0] == 'L' && cmd[1] == 'C' && cmd[2] == 'S')
    {
        if (LED_State == 0)
        {
            GPIO_SetBits(GPIOA, GPIO_Pin_1);
            LED_State = !LED_State;
        }
        else
        {
            GPIO_ResetBits(GPIOA, GPIO_Pin_1);
            LED_State = !LED_State;
        }
    }
}

int main()
{
    Setup();

    while (1)
    {
        Loop();
    }
}
