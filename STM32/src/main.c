#include "stm32f10x.h"
#include "./Module/Delay.h"
#include "./Module/TestLED.h"
#include "./Module/Serial.h"
#include "./Module/CmdCtrl.h"
#include "./Module/CamServo.h"

void Setup(void)
{
    TestLED_Init();
    Serial_Init();
    Cam_Servo_Init(); 
   
}

void Loop(void)
{
    if (Serial_GetRxFlag() == 1)
    {
        Cmd_Ctrl(Serial_RxString);
    }
}

int main()
{
    Setup();

    while (1)
    {
        Loop();
    }
}
