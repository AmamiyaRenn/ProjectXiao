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
#include "GyroCtrl.h"

class XiaoClass
{
public:
    XiaoClass(ChassisClass *Chassis, GyroCtrlClass *GyroCtrl) : Chassis(Chassis), GyroCtrl(GyroCtrl){};
    void updateState() { Chassis->updateAllMotor(); }
    void Run(s8 leftSpeed, s8 rightSpeed) { Chassis->setAllMotorSpeed(leftSpeed, rightSpeed); }
    void GyroCtrlFunction();

private:
    ChassisClass *Chassis;
    GyroCtrlClass *GyroCtrl;
};

#endif
