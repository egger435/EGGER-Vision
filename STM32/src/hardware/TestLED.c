#include "stm32f10x.h"
#include "TestLED.h"
#include "../sys/CmdCtrl.h"

uint8_t LED_State;
uint32_t LED_Timer = 0;  // 计时器 100ms加一
uint8_t reverse_gear_LED_State = 0;

// LED初始化
void TestLED_Init(void)
{
    RCC_APB2PeriphClockCmd(TestLED_GPIO, ENABLE);

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

// LED翻转状态
void TestLED_Toggle(void)
{
    LED_State ? TestLED_TurnOff() : TestLED_TurnOn();
}

// LED闪烁控制 指示小车状态
void LED_Flash_Control(void)
{
    switch(cur_gear)
    {
        case GEAR_NEUTRAL:  // 空档 常亮
            TestLED_TurnOn();
            break;
        case GEAR_DRIVE:    // 前进档 1s闪烁
            if (LED_Timer >= 4)
            {
                LED_Timer = 0;
                TestLED_Toggle();
            }
            break;
        case GEAR_SPEED:    // 速度档 0.5s闪烁
            if (LED_Timer >= 2)
            {
                LED_Timer = 0;
                TestLED_Toggle();
            }
            break;
        case GEAR_REVERSE:  // 倒档 2s两次连续闪烁
            switch(reverse_gear_LED_State)
            {
                case 0:
                    if (LED_Timer >= 1) { LED_Timer = 0; TestLED_TurnOn(); reverse_gear_LED_State = 1; }
                    break;
                case 1:
                    if (LED_Timer >= 1) { LED_Timer = 0; TestLED_TurnOff(); reverse_gear_LED_State = 2; }
                    break;
                case 2:
                    if (LED_Timer >= 1) { LED_Timer = 0; TestLED_TurnOn(); reverse_gear_LED_State = 3; }
                    break;
                case 3:
                    if (LED_Timer >= 1) { LED_Timer = 0; TestLED_TurnOff(); reverse_gear_LED_State = 4; }
                    break;
                case 4:
                    if (LED_Timer >= 5) { LED_Timer = 0; reverse_gear_LED_State = 0; }
                    break;
                default:
                    reverse_gear_LED_State = 0;
                    LED_Timer = 0;
                    break;
            }
            break;

        default:
            cur_gear = GEAR_NEUTRAL;
            break;
    }
}