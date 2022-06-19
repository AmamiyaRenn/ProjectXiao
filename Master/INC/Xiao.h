/***
 * @Description: 智能车——晓
 * @Author: Amamiya
 * @Date: 2022-06-19 11:02:48
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _XIAO_H
#define _XIAO_H

#include "MasterParam.h"
#include "Chassis.h"

class XiaoClass
{
public:
    void Init() { Chassis.MotorHardwareInit(); }
    void updateState() { Chassis.updateAllMotor(); }
    void Run(s8 leftSpeed, s8 rightSpeed) { Chassis.setAllMotorSpeed(leftSpeed, rightSpeed); }
    XiaoControlModeEnum getControlMode() const { return ControlMode; }

private:
    ChassisClass Chassis;
    XiaoControlModeEnum ControlMode;
};

extern XiaoClass *Xiao;

#endif
