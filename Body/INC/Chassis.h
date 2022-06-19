/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 11:20:03
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _CHAISSIS_H
#define _CHAISSIS_H

#include "Macro.h"

#define SPEED_PERIOD 50 // 一个周期的时间(ms)
#define SPEED_DUTY 40   // 周期内的默认驱动时间(ms)

class ChassisClass
{
public:
    void MotorHardwareInit();
    void updateAllMotor();
    // 设置电机速度，范围为[0,50]
    void setAllMotorSpeed(s8 leftSpeed, s8 rightSpeed) { this->leftSpeed = leftSpeed, this->rightSpeed = rightSpeed; }

private:
    s8 leftSpeed, rightSpeed; // 左/右速度
    s8 SpeedDutyCount;        // 占空比计数器, 50次一周期
};

#endif
