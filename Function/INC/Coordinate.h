/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-05-16 10:23:29
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _COORDINATE_H
#define _COORDINATE_H

#include "stm32f1xx.h"
#include "MyMath.h"

// 世界坐标系下底盘坐标与角度
struct PositionStruct : Vector2f
{
    float angle; // 世界坐标系底盘角度（deg）
    PositionStruct() : angle(0) {}
    PositionStruct(const Vector2f &vec, float angle) : Vector2f(vec.x, vec.y), angle(angle) {}
    PositionStruct(float x, float y, float angle) : Vector2f(x, y), angle(angle) {}
    // 根据x,y计算angle（rad）
    void CalAngleRad() { angle = this->CalculateAngleRad(); }
};

// 底盘速度矢量
struct VelocityStruct : Vector2f
{
    VelocityStruct() : v(0), w(0) {}
    float v; // 速度大小
    float w; // 角速度大小（deg）
};

#endif
