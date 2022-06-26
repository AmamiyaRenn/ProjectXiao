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
#include "IRCtrl.h"
#include "JoyStick.h"

class XiaoClass
{
public:
    XiaoClass(ChassisClass *Chassis, IRCtrlClass *IRCtrl, JoyStickControlClass *JoyStickControl) : Chassis(Chassis), IRCtrl(IRCtrl), JoyStickControl(JoyStickControl){};
    void updateState() { Chassis->updateAllMotor(); }
    void Run(s8 leftSpeed, s8 rightSpeed) { Chassis->setAllMotorSpeed(leftSpeed, rightSpeed); }
    void JoyStickFunction();

private:
    ChassisClass *Chassis;
    IRCtrlClass *IRCtrl;
    JoyStickControlClass *JoyStickControl;
};

#endif
