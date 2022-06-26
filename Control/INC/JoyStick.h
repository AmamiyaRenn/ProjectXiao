/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-26 19:05:06
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#include "MyMath.h"

// 摇杆类
class JoyStickControlClass
{
public:
    void linkJoyStickPos(Vector2f *JoyStickPos) { this->JoyStickPos = JoyStickPos; }
    // 计算转角和推摇杆量
    void update()
    {
        magnitude = JoyStickPos->norm();
        angle = RadToDeg(acos(JoyStickPos->y));
    }
    float getAngle() const { return angle; }
    float getMagnitude() const { return magnitude; }

private:
    Vector2f *JoyStickPos; // JoyStick的位置
    float angle;           // JoyStickPos计算出的平面角(deg)
    float magnitude;       // 推摇杆量，摇杆推到底就是1
};

#endif
