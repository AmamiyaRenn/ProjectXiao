#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x_tim.h"
#include "pid.h"
#include "delay.h"
#include "stm32f10x_can.h"
#include "led.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void TIM2_Init();
    void TIM3_Init();

#ifdef __cplusplus
}
#endif

#endif
