#include "sys.h"

// 系统模块初始化
void Sys_Init(void)
{
    Serial_Init();
    TestLED_Init();
    Cam_Servo_Init();
    Steering_Servo_Init();
}