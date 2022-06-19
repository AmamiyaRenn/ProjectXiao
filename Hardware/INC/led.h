#ifndef _LED_H
#define _LED_H

#include "sys.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define LED2_ON GPIOE->BRR = GPIO_Pin_2
#define LED3_ON GPIOE->BRR = GPIO_Pin_3
#define LED2_OFF GPIOE->BSRR = GPIO_Pin_2
#define LED3_OFF GPIOE->BSRR = GPIO_Pin_3
#define Cylinder_OPEN GPIOB->BSRR = GPIO_Pin_0
#define Cylinder_CLOSE GPIOB->BRR = GPIO_Pin_0
#define Cylinder_TOGGLE GPIOB->ODR ^= GPIO_Pin_0

    void LED_Init(void);
    void GPIOCLKInit(void);

#ifdef __cplusplus
}
#endif

#endif
