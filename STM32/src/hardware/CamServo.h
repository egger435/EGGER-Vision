#ifndef __CAMSERVO_H
#define __CAMSERVO_H

// 摄像头舵机角度定义
#define CAM_SERVO_MID_ANGLE   90.0f  
#define CAM_SERVO_LEFT_ANGLE 135.0f
#define CAM_SERVO_RIGHT_ANGLE 45.0f 

void Cam_Servo_Init(void);

void Cam_Servo_RotateLeft(void);
void Cam_Servo_RotateRight(void);
void Cam_Servo_ResetPos(void);

#endif