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

enum XiaoControlModeEnum
{
    InfraredRemoteControl,  // 红外遥控模式
    BluetoothRemoteControl, // 蓝牙遥控模式
    PathTracingControl,     // 红外黑线循迹

};

struct ControlMsgStruct
{
public:
    bool Reset; // 软件重启
	float leftSpeed,rightSpeed;
    XiaoControlModeEnum ControlMode;
};

struct RobotMsgStruct
{
    float WorldTime; // 全局时间(ms)
    float StartTime; // 开始某类运动的某个周期的WorldTime时刻(ms)
    float Runtime;   // 开始某类运动的某个周期后的当前运行时间
};

class MasterParam
{
public:
    ControlMsgStruct ControlMsg;
    RobotMsgStruct RobotMsg;

private:
    DataProcess data_process;
};
extern MasterParam Master;

#endif
