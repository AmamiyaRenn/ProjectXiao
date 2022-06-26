/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-26 10:07:09
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _BEEP_H
#define _BEEP_H

#include "includes.h"
#include "delay.h"
#include "led.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define BEEP_OFF() GPIOE->BRR = GPIO_Pin_14
#define BEEP_ON() GPIOE->BSRR = GPIO_Pin_14

#define Beep_Show(x) beep_on_num += (x)
#define Beep_Clear() beep_on_num = 0

    void Beep_Configuration(void);
    void Beep_Start(void);
    void Beep_Task(void);

#ifdef __cplusplus
}
#endif

#endif
