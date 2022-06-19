/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2020-03-16 07:55:06
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "string.h"
#include "led.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void usart_init(u32 bound);

#ifdef __cplusplus
}
#endif

#endif
