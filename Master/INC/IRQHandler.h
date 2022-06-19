/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 17:16:44
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _IRQHANDLER_H
#define _IRQHANDLER_H

#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"
#include "string.h"
#include "led.h"
#include "Xiao.h"
#include "IRCtrl.h"
#include "dma.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void USART1_IRQHandler();
    void EXTI15_10_IRQHandler();
    void TIM2_IRQHandler();

#ifdef __cplusplus
}
#endif

#endif
