/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 11:22:47
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _RUN_CONTORL_H
#define _RUN_CONTORL_H

#include "Coordinate.h"
#include "MyMath.h"
#include "pid.h"
#include "stm32f4xx.h"

class RunControl
{
public:
protected:
    PositionStruct posStart, *posNow, posGoal; // 世界坐标系开始/当前/目标位置
};

#endif
