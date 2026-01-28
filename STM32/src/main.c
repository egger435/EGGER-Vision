#include "stm32f10x.h"
#include "sys/sys.h"

void Setup(void)
{
    Sys_Init();
    
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
