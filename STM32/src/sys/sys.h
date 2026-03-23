#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x.h"
#include "CmdCtrl.h"
#include "Delay.h"
#include "../hardware/Serial.h"
#include "../hardware/TestLED.h"
#include "../hardware/CamServo.h"
#include "../hardware/SteeringServo.h"
#include "../hardware/Motor.h"

void Sys_Init(void);

#endif