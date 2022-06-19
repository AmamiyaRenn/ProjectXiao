/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-09 21:21:03
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _DELAY_H
#define _DELAY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"

    void delay_ms(unsigned int t);
    void delay_us(unsigned int t);

#ifdef __cplusplus
}
#endif

#endif
