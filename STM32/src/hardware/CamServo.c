#include "PWM.h"
#include "CamServo.h"

// 摄像头舵机初始化
void Cam_Servo_Init(void)
{
    CAM_Servo_PWM_Init();
    Cam_Servo_ResetPos();
}

// 设置舵机角度
void Cam_Servo_SetAngle(float angle)
{
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;

    uint16_t pulse_width = (uint16_t)(500 + (angle / 180.0f) * 2000); // 计算脉宽
    CAM_Servo_PWM_SetCompare3(pulse_width);
}

// 摄像头舵机左转
void Cam_Servo_RotateLeft(void)
{
    Cam_Servo_SetAngle(CAM_SERVO_LEFT_ANGLE);
}

// 摄像头舵机右转
void Cam_Servo_RotateRight(void)
{
    Cam_Servo_SetAngle(CAM_SERVO_RIGHT_ANGLE);
}

// 摄像头舵机归位
void Cam_Servo_ResetPos(void)
{
    Cam_Servo_SetAngle(CAM_SERVO_MID_ANGLE);
}