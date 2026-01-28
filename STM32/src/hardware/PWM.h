#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"

#define CAM_SERVO_PWM_TIM  TIM2        // 摄像头舵机PWM定时器 TIM2
#define CAM_SERVO_PWM_GPIO GPIOA       // 摄像头舵机PWM输出端口 GPIOA
#define CAM_SERVO_PWM_PIN  GPIO_Pin_2  // 摄像头舵机PWM输出引脚 PA2 TIM2_CH3

void CAM_Servo_PWM_Init(void);
void CAM_Servo_PWN_SetCompare3(uint16_t campare);

#endif