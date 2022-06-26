/*
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-26 10:07:02
 * TechChangeTheWorld
 * WHUROBOCON_Alright_Reserved
 */
#include "Beep.h"

void Beep_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    BEEP_OFF();
}

/**
 * @brief: 开场蜂鸣器特效
 */
void Beep_Start(void)
{
    BEEP_ON();
    delay_ms(30);
    BEEP_OFF();
    delay_ms(40);
    BEEP_ON();
    delay_ms(50);
    BEEP_OFF();
    delay_ms(60);
    BEEP_ON();
    delay_ms(70);
    BEEP_OFF();
    delay_ms(50);
}

u16 beep_on_num;
/**
 * @brief: 供外部调用的beep函数
 */
void Beep_Task(void)
{
    u16 num_temp = beep_on_num;
    if (0 == num_temp)
    {
        OSTimeDly(2000);
    }
    else
    {
        u32 i;
        for (i = 0; i < num_temp; i++)
        {
            // if (BEEP_OFF_flag == false)
            // {
            //     BEEP_ON();
            //     delay_ms(100);
            //     BEEP_OFF();
            //     delay_ms(100);
            //     beep_on_num--;
            // }
            // else
            // {
            //     beep_on_num = 0;
            //     break;
            // }
        }
        delay_ms(200);
    }
}
