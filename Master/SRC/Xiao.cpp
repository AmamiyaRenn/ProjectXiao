/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 11:02:40
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#include "Xiao.h"

float speedTemp;

void XiaoClass::GyroCtrlFunction()
{
    if (abs(GyroCtrl->getPitch()) > GyroCtrl->getPitchThreshold())
    {
        speedTemp = (GyroCtrl->getPitch() - sign(GyroCtrl->getPitch()) * GyroCtrl->getPitchThreshold()) * 200.f;
        speedTemp = abs(speedTemp) > SPEED_PERIOD ? sign(speedTemp) * SPEED_PERIOD : speedTemp;
        if (abs(GyroCtrl->getRoll()) > GyroCtrl->getRollThreshold())
        {
            if (sign(GyroCtrl->getRoll()) == 1)
            {
                float leftSpeed = speedTemp - (GyroCtrl->getRoll() - sign(GyroCtrl->getRoll()) * GyroCtrl->getRollThreshold()) * 200.f;
                leftSpeed = abs(leftSpeed) > SPEED_PERIOD ? sign(leftSpeed) * SPEED_PERIOD : leftSpeed;
                Run(int(leftSpeed), int(speedTemp));
                return;
            }
            else
            {
                float rightSpeed = speedTemp + (GyroCtrl->getRoll() - sign(GyroCtrl->getRoll()) * GyroCtrl->getRollThreshold()) * 200.f;
                rightSpeed = abs(rightSpeed) > SPEED_PERIOD ? sign(rightSpeed) * SPEED_PERIOD : rightSpeed;
                Run(int(speedTemp), int(rightSpeed));
                return;
            }
        }
        Run(int(speedTemp), int(speedTemp));
        return;
    }
    Run(0, 0);
}
