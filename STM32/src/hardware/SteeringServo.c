#include "PWM.h"
#include "SteeringServo.h"

// 舵机复位
void Reset_Pos(void);

// 方向舵机初始化
void Steering_Servo_Init(void)
{
    Steering_Servo_PWM_Init();
    Reset_Pos();
}

// 设定方向舵机的角度
void Steering_Servo_SetAngle(int angle)
{
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;

    uint16_t pulse_width = (uint16_t)(500 + (angle / 180.0f) * 2000); // 计算脉宽
    Steering_Servo_PWM_SetCompare4(pulse_width);
}

void Reset_Pos(void)
{
    Steering_Servo_SetAngle(0);
}
