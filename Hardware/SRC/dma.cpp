#include "dma.h"

/**
 * @brief DMAx 的各通道配置(目前只针对了USART3)
 * 这里的传输形式是固定的,这点要根据不同的情况来修改
 * 从存储器->外设模式/8 位数据宽度/存储器增量模式
 * @param chx DMA 通道选择 DMA_channel DMA_Channel_0~DMA_Channel_7
 * @param par 外设地址
 * @param mar 存储器地址
 */
void DMA::Config(u32 chx, u32 par, u32 mar)
{
    DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA1_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = par;
    DMA_InitStructure.DMA_MemoryBaseAddr = mar;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;

    DMA_InitStructure.DMA_BufferSize = SEND_BUF_SIZE;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;

    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    DMA_Init(DMA1_Channel3, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Channel3, ENABLE);

    USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
}

/**
 * @brief 开启一次 DMA 传输
 * @param ndtr 数据传输量
 */
void DMA::Enable(u16 ndtr)
{
    DMA_Cmd(DMA1_Channel3, DISABLE);             // 关闭 DMA 传输
    DMA_SetCurrDataCounter(DMA1_Channel3, ndtr); // 数据传输量
    DMA_Cmd(DMA1_Channel3, ENABLE);              // 开启 DMA 传输
}
