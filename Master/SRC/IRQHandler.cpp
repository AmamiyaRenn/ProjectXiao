/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 17:16:26
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#include "IRQHandler.h"

u16 USART_RX_STA = 0;
u8 USART_RX_BUF[32];
void USART1_IRQHandler()
{
	u8 temp;
	if (USART_GetITStatus(USART1, USART_IT_ORE) != RESET) // 过载重置接受数组
	{
		temp = USART_ReceiveData(USART1);
		USART_RX_STA = 0;
		memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF));
	}
	else if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		USART_ClearFlag(USART1, USART_IT_RXNE);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		temp = USART_ReceiveData(USART1);

		if (temp == '#')
		{
			u8 i;
			USART_RX_STA |= 0x40;
			for (i = 0; i < 32; i++)
				USART_RX_BUF[i] = 0x00;
		}
		else if ((USART_RX_STA & 0x40) != 0) // 接收已经开始
		{
			if ((USART_RX_STA & 0x80) == 0) // 接收未完成
			{
				if (temp != 0x0d)
				{
					USART_RX_BUF[USART_RX_STA & 0X3F] = temp;
					USART_RX_STA++;
					if ((USART_RX_STA & 0X3F) > 31)
						USART_RX_STA = 0; // 超出接收范围
				}
				else
					USART_RX_STA |= 0x80; // 接收完成了
			}
		}
		if ((USART_RX_STA & 0x80) != 0)
		{
			if (USART_RX_BUF[0] == 'O')
			{
				if (USART_RX_BUF[1] == 'N')
					LED2_ON;
				if (USART_RX_BUF[1] == 'F' && USART_RX_BUF[2] == 'F')
					LED2_OFF;
			}
			USART_RX_STA = 0;
		}
	}
}

void EXTI15_10_IRQHandler()
{
	if (EXTI_GetITStatus(IRIN_EXITLINE) != RESET) // 红外中断
	{
		EXTI_ClearITPendingBit(IRIN_EXITLINE); // 清除中断标志
		IRCtrl->RecNewMsg();
	}
}

void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		Xiao->updateState(); // 把状态更新放在这里，更加准确
	}
}

void DMA1_Channel3_IRQHandler(void)
{
	if (DMA_GetITStatus(DMA1_IT_TC3) == SET)
	{
		DMA_ClearFlag(DMA1_IT_TC3);
		DMA_ClearITPendingBit(DMA1_IT_TC3);
	}
}
