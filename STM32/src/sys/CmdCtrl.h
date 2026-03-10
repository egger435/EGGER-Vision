#ifndef __CMDCTRL_H
#define __CMDCTRL_H

#include "sys.h"

typedef void (*CmdHandler)(char *args);  // 函数指针, 处理指令

// 指令表结构体
typedef struct 
{
    char *cmd_name;
    CmdHandler handler;
} CmdEntry;

// 档位枚举
typedef enum
{
    GEAR_REVERSE = -1,  // 倒挡
    GEAR_NEUTRAL =  0,  // 空挡
    GEAR_DRIVE   =  1,  // 前进挡
    GEAR_SPEED   =  2   // 速度档
} CarGear;

extern CarGear cur_gear;  // 小车当前档位

void Cmd_Ctrl(char *cmd);

#endif