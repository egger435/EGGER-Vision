#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"

#define CAM_SERVO_PWM_TIM  TIM2        // 摄像头舵机PWM定时器 TIM2
#define CAM_SERVO_PWM_GPIO GPIOA       // 摄像头舵机PWM输出端口 GPIOA
#define CAM_SERVO_PWM_PIN  GPIO_Pin_2  // 摄像头舵机PWM输出引脚 PA2 TIM2_CH3

#define STEERING_SERVO_PWM_TIM  TIM2        // 方向舵机PWM定时器 TIM2
#define STEERING_SERVO_PWM_GPIO GPIOA       // 方向舵机PWM输出端口 GPIOA
#define STEERING_SERVO_PWM_PIN  GPIO_Pin_3  // 方向舵机PWM输出引脚 PA3 TIM2_CH4

// 摄像头舵机PWM
void CAM_Servo_PWM_Init(void);
void CAM_Servo_PWM_SetCompare3(uint16_t campare);

// 方向舵机PWM
void Steering_Servo_PWM_Init(void);
void Steering_Servo_PWM_SetCompare4(uint16_t campare);

#endif