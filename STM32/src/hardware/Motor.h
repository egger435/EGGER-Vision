#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"
#include "PWM.h"

#define MOTOR_GPIO GPIOB               // 电机控制端口 GPIOB

#define FRONT_LEFT_PIN_1 GPIO_Pin_0    // 左前电机控制引脚1 PB0
#define FRONT_LEFT_PIN_2 GPIO_Pin_1    // 左前电机控制引脚2 PB1
#define FRONT_RIGHT_PIN_1 GPIO_Pin_10  // 右前电机控制引脚1 PB10
#define FRONT_RIGHT_PIN_2 GPIO_Pin_11  // 右前电机控制引脚2 PB11 

#define RERR_LEFT_PIN_1 GPIO_Pin_6     // 左后电机控制引脚1 PB6
#define REAR_LEFT_PIN_2 GPIO_Pin_5     // 左后电机控制引脚2 PB5
#define REAR_RIGHT_PIN_1 GPIO_Pin_4    // 右后电机控制引脚1 PB4
#define REAR_RIGHT_PIN_2 GPIO_Pin_3    // 右后电机控制引脚2 PB3


#endif