#include "stm32f10x.h"
#include "./Module/TestLED.h"
#include "./Module/Serial.h"
#include "./Module/CmdCtrl.h"

void LED_Ctrl(char *cmd);

void Setup(void)
{
    TestLED_Init();
    Serial_Init(); 

    TestLED_TurnOff();    
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
