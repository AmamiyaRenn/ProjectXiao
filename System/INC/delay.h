/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-09 21:21:03
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _DELAY_H
#define _DELAY_H

#include "sys.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f10x.h"

    void delay_init(void);
    void delay_ms(u16 nms);
    void delay_us(u32 nus);

#ifdef __cplusplus
}
#endif

#endif
