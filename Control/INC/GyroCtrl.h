/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-29 19:39:38
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _GYROCTRL_H
#define _GYROCTRL_H

#include "MyMath.h"

class GyroCtrlClass
{
public:
    GyroCtrlClass(float *roll, float *pitch) : roll(roll), pitch(pitch){};
    void setThreshold(float rollThreshold, float pitchThreshold)
    {
        this->rollThreshold = rollThreshold;
        this->pitchThreshold = pitchThreshold;
    }
    float getRoll() const { return *roll; }
    float getPitch() const { return *pitch; }
    float getRollThreshold() const { return rollThreshold; }
    float getPitchThreshold() const { return pitchThreshold; }

private:
    float *roll, *pitch;                 // Euler Angle
    float rollThreshold, pitchThreshold; // 死区
};

#endif
