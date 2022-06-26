/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2020-03-16 07:55:03
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _LED_H
#define _LED_H

#include "sys.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define LED2_ON GPIOE->BRR = GPIO_Pin_12
#define LED2_OFF GPIOE->BSRR = GPIO_Pin_12

    void LED_Init(void);
    void GPIOCLKInit(void);

#ifdef __cplusplus
}
#endif

#endif
