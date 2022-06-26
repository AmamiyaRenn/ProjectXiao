/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 11:02:40
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#include "Xiao.h"

void XiaoClass::JoyStickFunction()
{
    JoyStickControl->update();
    float angle = JoyStickControl->getAngle();
    float SpeedTemp = JoyStickControl->getMagnitude() * SPEED_PERIOD;
    if (angle >= 0.f && angle < 180.f)
        Run(int((180.f - angle) / 180.f * SpeedTemp),
            int(SpeedTemp));
    else if (angle >= 180.f)
        Run(int((180.f - angle) / 180.f * SpeedTemp),
            -int(SpeedTemp));
    else if (angle >= -180.f && angle < 0.f)
        Run(int(SpeedTemp),
            int((180.f + angle) / 180.f * SpeedTemp));
    else
        Run(-int(SpeedTemp),
            int((180.f + angle) / 180.f * SpeedTemp));
}
