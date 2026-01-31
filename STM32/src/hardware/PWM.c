#include "PWM.h"

// 摄像头舵机PWM初始化
void CAM_Servo_PWM_Init(void)
{
    // 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = CAM_SERVO_PWM_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CAM_SERVO_PWM_GPIO, &GPIO_InitStructure);

    // 时基单元初始化
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(CAM_SERVO_PWM_TIM, &TIM_TimeBaseStructure);

    // 输出比较初始化
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);  // 结构体初始化，赋予默认值
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // 初始占空比0
    TIM_OC3Init(CAM_SERVO_PWM_TIM, &TIM_OCInitStructure);

    TIM_Cmd(CAM_SERVO_PWM_TIM, ENABLE);
}

void CAM_Servo_PWM_SetCompare3(uint16_t campare)
{
    TIM_SetCompare3(CAM_SERVO_PWM_TIM, campare);
}

// 方向舵机PWM初始化
void Steering_Servo_PWM_Init(void)
{
    // 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = STEERING_SERVO_PWM_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(STEERING_SERVO_PWM_GPIO, &GPIO_InitStructure);

    // 时基单元初始化
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(STEERING_SERVO_PWM_TIM, &TIM_TimeBaseStructure);

    // 输出比较初始化
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);  // 结构体初始化，赋予默认值
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // 初始占空比0
    TIM_OC4Init(STEERING_SERVO_PWM_TIM, &TIM_OCInitStructure);

    TIM_Cmd(STEERING_SERVO_PWM_TIM, ENABLE);
}

void Steering_Servo_PWM_SetCompare4(uint16_t campare)
{
    TIM_SetCompare4(STEERING_SERVO_PWM_TIM, campare);
}