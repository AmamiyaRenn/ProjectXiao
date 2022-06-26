/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-12 15:57:58
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _MASTER_PARAM_H
#define _MASTER_PARAM_H

#include "MyMath.h"
#include "usart.h"
#include "data_processing.h"

enum XiaoControlModeEnum : uint32_t
{
    BluetoothRemoteControl, // 蓝牙遥控模式
    PathTracingControl,     // 红外黑线循迹
    InfraredRemoteControl,  // 红外遥控模式
};

struct ControlMsgStruct
{
public:
    bool Begin;
    bool Reset; // 软件重启
    float leftSpeed, rightSpeed;
    XiaoControlModeEnum ControlMode;
    Vector2f JoyStickPos; // 摇杆位置
};

struct RobotMsgStruct
{
    float WorldTime; // 全局时间(ms)
    float leftSpeed, rightSpeed;
};

class MasterParam
{
public:
    void ReadMsg(u32 temp);
    void SendMsg();
    ControlMsgStruct ControlMsg;
    RobotMsgStruct RobotMsg;

private:
    UsartClass *usart;
    DataProcess data_process;
};
extern MasterParam Master;

#endif
