#include "TestLED.h"
#include "CmdCtrl.h"
#include "string.h"

void Cmd_Change_LED_State(char *args);        // LCS, 改变LED灯状态

void Cmd_Rotate_Camera_Left(char *args);      // RCL, 左转摄像头
void Cmd_Rotate_Camera_Right(char *args);     // RCR, 右转摄像头
void Cmd_Rotate_Camera_Behind(char *args);    // RCB, 倒转摄像头
void Cmd_Rotate_Camera_in_Place(char *args);  // RCP, 摄像头归位

void Cmd_Steering_Servo_Angle(char *args);    // SSA, 设置方向舵机角度

void Cmd_Shift_Gear(char *args);              // SG, 切换挡位
void Cmd_Motor_Speed(char *args);             // MS, 设置电机速度

// 指令表
static const CmdEntry cmd_Table[] = 
{
    {"MS", Cmd_Motor_Speed},
    {"SSA", Cmd_Steering_Servo_Angle},
    {"SG", Cmd_Shift_Gear},
    {"RCL", Cmd_Rotate_Camera_Left},
    {"RCR", Cmd_Rotate_Camera_Right},
    {"RCB", Cmd_Rotate_Camera_Behind},
    {"RCP", Cmd_Rotate_Camera_in_Place},
    {"LCS", Cmd_Change_LED_State},
    {NULL, NULL}  // 表尾标记
};

// 提取指令, 输出指令的参数部分, out_cmd中为指令部分
static char* Cmd_ExtractCommand(char *cmd, char *out_cmd)
{
    char *colon = strchr(cmd, ':');
    int cmd_len = colon ? (colon - cmd) : strlen(cmd);

    strncpy(out_cmd, cmd, cmd_len);
    out_cmd[cmd_len] = '\0';
    return colon ? (colon + 1) : "";
}

// 根据cmd执行指令
void Cmd_Ctrl(char *cmd)
{
    if (cmd == NULL || strlen(cmd) == 0) return;

    // 提取指令参数信息
    char cmd_name[10];
    char *args = Cmd_ExtractCommand(cmd, cmd_name);

    // 查找指令表
    for (int i = 0; cmd_Table[i].cmd_name != NULL; i++)
    {
        if (strcmp(cmd_name, cmd_Table[i].cmd_name) == 0)
        {
            cmd_Table[i].handler(args);
            return;
        }
    }
}

void Cmd_Change_LED_State(char *args)
{
    if (LED_State == 1)
    {
        TestLED_TurnOff();
    }
    else
    {
        TestLED_TurnOn();
    }
}

void Cmd_Rotate_Camera_Left(char *args)
{
    // TODO: 控制摄像头舵机左转
}

void Cmd_Rotate_Camera_Right(char *args)
{
    // TODO: 控制摄像头舵机右转
}

void Cmd_Rotate_Camera_Behind(char *args)
{
    // TODO: 控制摄像头舵机向后转
}

void Cmd_Rotate_Camera_in_Place(char *args)
{
    // TODO: 控制摄像头舵机归位
}

void Cmd_Steering_Servo_Angle(char *args)
{
    // TODO: 设置方向舵机的角度
}

void Cmd_Shift_Gear(char *args)
{
    // TODO: 切换挡位
}

void Cmd_Motor_Speed(char *args)
{
    // TODO: 设置电机速度
}