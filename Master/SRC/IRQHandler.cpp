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
void USART3_IRQHandler()
{
	char rec_data;
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		/* Read one byte from the receive data register */
		rec_data = USART_ReceiveData(USART3);
		Master.ReadMsg(rec_data);
	}
}

void EXTI15_10_IRQHandler()
{
	if (EXTI_GetITStatus(IRIN_EXITLINE) != RESET) // 红外中断
	{
		EXTI_ClearITPendingBit(IRIN_EXITLINE); // 清除中断标志
		IRCtrl.RecNewMsg();
	}
}

void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		Chassis.updateAllMotor(); // 把状态更新放在这里，更加准确
		Master.RobotMsg.WorldTime += 0.1f;
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
