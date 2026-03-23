#include "Motor.h"

uint8_t Motor_State;  // 电机状态 1前进 0后退 2停止

// 电机初始化
void Motor_Init(void)
{
    Motor_PWM_Init();
    Motor_PWM_SetCompare2(0);

    // GPIO初始化
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  // 释放PB3 PB4
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_PIN_1 | FRONT_LEFT_PIN_2 | FRONT_RIGHT_PIN_1 | FRONT_RIGHT_PIN_2 |
                                  REAR_LEFT_PIN_1  | REAR_LEFT_PIN_2  | REAR_RIGHT_PIN_1  | REAR_RIGHT_PIN_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOTOR_GPIO, &GPIO_InitStructure);

    Motor_Set_Speed(0);

    Motor_Stop();
}

// 设置电机转速
void Motor_Set_Speed(uint8_t speed)
{
    if (speed > 100) speed = 100;
    Motor_PWM_SetCompare2(speed);
}

void Motor_Reverse(void)
{
    GPIO_SetBits(MOTOR_GPIO, FRONT_LEFT_PIN_1);
    GPIO_ResetBits(MOTOR_GPIO, FRONT_LEFT_PIN_2);

    GPIO_SetBits(MOTOR_GPIO, FRONT_RIGHT_PIN_1);
    GPIO_ResetBits(MOTOR_GPIO, FRONT_RIGHT_PIN_2);

    GPIO_SetBits(MOTOR_GPIO, REAR_LEFT_PIN_1);
    GPIO_ResetBits(MOTOR_GPIO, REAR_LEFT_PIN_2);

    GPIO_SetBits(MOTOR_GPIO, REAR_RIGHT_PIN_1);
    GPIO_ResetBits(MOTOR_GPIO, REAR_RIGHT_PIN_2);
    
    Motor_State = 0;
}

void Motor_Forward(void)
{
    GPIO_ResetBits(MOTOR_GPIO, FRONT_LEFT_PIN_1);
    GPIO_SetBits(MOTOR_GPIO, FRONT_LEFT_PIN_2);

    GPIO_ResetBits(MOTOR_GPIO, FRONT_RIGHT_PIN_1);
    GPIO_SetBits(MOTOR_GPIO, FRONT_RIGHT_PIN_2);

    GPIO_ResetBits(MOTOR_GPIO, REAR_LEFT_PIN_1);
    GPIO_SetBits(MOTOR_GPIO, REAR_LEFT_PIN_2);

    GPIO_ResetBits(MOTOR_GPIO, REAR_RIGHT_PIN_1);
    GPIO_SetBits(MOTOR_GPIO, REAR_RIGHT_PIN_2);

    Motor_State = 1;
}

void Motor_Stop(void)
{
    GPIO_SetBits(MOTOR_GPIO, FRONT_LEFT_PIN_1);
    GPIO_SetBits(MOTOR_GPIO, FRONT_LEFT_PIN_2);

    GPIO_SetBits(MOTOR_GPIO, FRONT_RIGHT_PIN_1);
    GPIO_SetBits(MOTOR_GPIO, FRONT_RIGHT_PIN_2);

    GPIO_SetBits(MOTOR_GPIO, REAR_LEFT_PIN_1);
    GPIO_SetBits(MOTOR_GPIO, REAR_LEFT_PIN_2);

    GPIO_SetBits(MOTOR_GPIO, REAR_RIGHT_PIN_1);
    GPIO_SetBits(MOTOR_GPIO, REAR_RIGHT_PIN_2);

    Motor_State = 2;
}