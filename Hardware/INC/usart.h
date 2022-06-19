/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2020-03-16 07:55:06
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _USART_H
#define _USART_H

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "string.h"
#include "queue.h"
#include "dma.h"
#include "Macro.h"

class UsartClass
{
public:
    void usart3Init(u32 baudRate);

    bool addUsartSendMsg(USART_TypeDef *USARTx, char *msg, int len); // 添加消息到队列
    void sendUsartSendList(USART_TypeDef *USARTx);                   // 发送消息 清空队列

    bool deUsartRecMsgList(USART_TypeDef *USARTx, char *msg, int len); // 串口接收消息出队
    bool deUsartRecMsgList(USART_TypeDef *USARTx, char *msg);          // 串口接收消息出队 单个

private:
    DMA dma;
    Queue<char> usart3_send_list;  // 发送队列
    Queue<char> *usart3_rec_list_; // 接收队列的指针  只是为了方便查看
};

#endif
