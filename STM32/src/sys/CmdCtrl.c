#include "CmdCtrl.h"
#include "string.h"
#include "stdlib.h"

CarGear cur_gear = GEAR_NEUTRAL;  // 默认空档

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

// 改变LED状态
void Cmd_Change_LED_State(char *args)
{
    TestLED_Toggle();
}

// 控制摄像头左转
void Cmd_Rotate_Camera_Left(char *args)
{
    Cam_Servo_RotateLeft();
}

// 控制摄像头右转
void Cmd_Rotate_Camera_Right(char *args)
{
    Cam_Servo_RotateRight();
}

// 控制摄像头向后转
void Cmd_Rotate_Camera_Behind(char *args)
{
    // TODO: 控制摄像头舵机向后转
}

// 控制摄像头归位
void Cmd_Rotate_Camera_in_Place(char *args)
{
    Cam_Servo_ResetPos();
}

// 设置方向舵机角度
void Cmd_Steering_Servo_Angle(char *args)
{
    // 获取目标角度值
    int targetAngle = atoi(args);
    Steering_Servo_SetAngle(targetAngle);
}

// 切换档位 TODO 档位状态待完成
void Cmd_Shift_Gear(char *args)
{
    char gear = args[0];
    switch(gear)
    {
        case 'N': cur_gear = GEAR_NEUTRAL; break;
        case 'D': cur_gear = GEAR_DRIVE;   break;
        case 'S': cur_gear = GEAR_SPEED;   break;
        case 'R': 
            cur_gear = GEAR_REVERSE;
            reverse_gear_LED_State = 0;
            LED_Timer = 0;
            break;
        default: cur_gear = GEAR_NEUTRAL; break;
    }
}

void Cmd_Motor_Speed(char *args)
{
    // TODO: 设置电机速度
}

