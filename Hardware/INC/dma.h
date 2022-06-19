/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-09 10:39:15
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _DMA_H
#define _DMA_H

#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "Macro.h"

class DMA
{
public:
    void Config(u32 chx, u32 par, u32 mar);
    void Enable(u16 ndtr);
};

#endif
