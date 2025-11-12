#ifndef __CMDCTRL_H
#define __CMDCTRL_H

typedef void (*CmdHandler)(char *args);  // 函数指针, 处理指令

// 指令表结构体
typedef struct 
{
    char *cmd_name;
    CmdHandler handler;
} CmdEntry;

void Cmd_Ctrl(char *cmd);

#endif