#include "usart.h"

Queue<char> usart3_rec_list(SEND_BUF_SIZE);
u8 send_buff3[SEND_BUF_SIZE];

// UART function
// UART3 TxD GPIOB10   RxD GPIOB11
void UsartClass::usart3Init(u32 baudRate)
{
	// GPIO_InitTypeDef GPIO_InitStructure;
	// USART_InitTypeDef USART_InitStructure;

	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_Init(GPIOB, &GPIO_InitStructure);

	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	// GPIO_Init(GPIOB, &GPIO_InitStructure);

	// USART_InitStructure.USART_BaudRate = baudRate;
	// USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// USART_InitStructure.USART_Parity = USART_Parity_No;
	// USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	// USART_Init(USART3, &USART_InitStructure);
	// USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

	// USART_Cmd(USART3, ENABLE);

	// NVIC_InitTypeDef NVIC_InitStructure;
	// /* Enable the USART3 Interrupt */

	// NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init(&NVIC_InitStructure);

	// // Enable DMA1 Channel3 Interrupt
	// NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init(&NVIC_InitStructure);
	NVIC_InitTypeDef NVIC_InitStruct;	//����һ�������жϵĽṹ��
	USART_InitTypeDef USART_InitSturct; //���崮��1�ĳ�ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;	//���崮�ڶ�Ӧ�ܽŵĽṹ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //�򿪴��ڹܽ�ʱ��
	// USART3_Tx_Pin Configure
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;		  //�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; //��������ٶ�50MHz
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;  //���츴�����
	GPIO_Init(GPIOB, &GPIO_InitStruct);			  //����ʼ���õĽṹ��װ��Ĵ���

	// USART3_Rx_Pin Configure
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // GPIOģʽ��������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;			   //��������
	GPIO_Init(GPIOB, &GPIO_InitStruct);				   //����ʼ���õĽṹ��װ��Ĵ���

	// USART3 Configure
	USART_InitSturct.USART_BaudRate = baudRate;				 //������19200
	USART_InitSturct.USART_WordLength = USART_WordLength_8b; //���ݿ��8λ
	USART_InitSturct.USART_StopBits = USART_StopBits_1;		 //һ��ֹͣλ
	USART_InitSturct.USART_Parity = USART_Parity_No;		 //����żУ��
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //ʹ�ܷ��������
	USART_Init(USART3, &USART_InitSturct);						 //����ʼ���õĽṹ��װ��Ĵ���
	// USART1_INT Configure
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //ʹ�ܽ����ж�
												   //	USART_ITConfig(USART3 , USART_IT_TXE , ENABLE);
	USART_Cmd(USART3, ENABLE);					   //�򿪴���
	USART_ClearFlag(USART3, USART_FLAG_TC);		   //�����һ�����ݷ���ʧ�ܵ�����

	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //�򿪸��ж�
	NVIC_Init(&NVIC_InitStruct);
}

bool UsartClass::addUsartSendMsg(USART_TypeDef *USARTx, char *msg, int len)
{
	if (USARTx == USART3)
		return usart3_send_list.enQueue(msg, len);
	else
		return false;
}

void UsartClass::sendUsartSendList(USART_TypeDef *USARTx)
{
	if (USARTx == USART3)
	{
		char _ch;
		u16 j = 0; //�ϰ��Ӳ�����dma1ͬʱʹ��
		while (usart3_send_list.deQueue(&_ch))
		{
			send_buff3[j] = _ch;
			j++;
		};
		USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
		dma.Enable(j);
	}
}

bool UsartClass::deUsartRecMsgList(USART_TypeDef *USARTx, char *msg)
{
	if (USARTx == USART3)
		return usart3_rec_list.deQueue(msg);
	else
		return false;
}

bool UsartClass::deUsartRecMsgList(USART_TypeDef *USARTx, char *msg, int len)
{
	if (USARTx == USART3)
		return usart3_rec_list.deQueue(msg, len);
	else
		return false;
}
