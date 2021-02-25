#include "dmaBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dma.h"

DMA_InitTypeDef DMA_InitStructure;

uint8_t SendBuff[8] = {1,2,3,4,5,6,7,8};
uint8_t ReceiveBuff[8];// = {8,7,6,5,4,3,2,1};
/**
  * @brief  USART1 TX DMA 配置，内存到内存
  * @param  无
  * @retval 无
  */
void DMA_Mem2Mem_Config(void)
{
#if 0
  /*开启DMA时钟*/
  RCC->AHB1ENR |= RCC_AHB1Periph_DMA2;
  

  /*源地址*/
  DMA2_Stream1->PAR = (uint32_t)SendBuff;
  /*目标地址*/
  DMA2_Stream1->M0AR = (uint32_t)ReceiveBuff;
  
  /*传输方向*/
  DMA2_Stream1->CR = DMA_Channel_0 | DMA_DIR_MemoryToMemory | DMA_PeripheralInc_Enable | DMA_MemoryInc_Enable | DMA_PeripheralDataSize_Byte
                    | DMA_MemoryDataSize_Byte | DMA_Mode_Normal | DMA_MemoryBurst_Single | DMA_PeripheralBurst_Single;
  
  
  /*传输大小*/
  DMA2_Stream1->NDTR = 8;
  
  
   DMA2_Stream1->CR |= 1;
  
   
   
#else
   
   
   
   
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
   
   DMA_DeInit(DMA2_Stream1);
   while(DMA_GetCmdStatus(DMA2_Stream1)!=DISABLE){}
   
   
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ReceiveBuff;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SendBuff; 
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;
  DMA_InitStructure.DMA_BufferSize = 8;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    
  DMA_Init(DMA2_Stream1, &DMA_InitStructure);
  
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;        //中断源：[9:5]，位于<stm32f10x.h>中
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级：1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //子优先级：1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能中断通道
  NVIC_Init(&NVIC_InitStructure);
  
  DMA_ITConfig(DMA2_Stream1,DMA_IT_TC,ENABLE);
    
    //DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_FEIF0);
   // DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIFx);
    
  DMA_Cmd (DMA2_Stream1,DISABLE);
  while(DMA_GetCmdStatus(DMA2_Stream1)!=DISABLE){}
  DMA_SetCurrDataCounter(DMA2_Stream1,8);
  DMA_Cmd (DMA2_Stream1,ENABLE);
    
    
    //传输完成先清除传输完成和半传输完成中断位
    //NDTR寄存器写长度
    //使能传输EN
    //STM32F4的DMA1不能实现存储到存储的传输
  
  
  DMA_DeInit(DMA2_Stream7);
   while(DMA_GetCmdStatus(DMA2_Stream7)!=DISABLE){}
   
   
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)SendBuff;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)  &USART1->DR; 
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = 8;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    
  DMA_Init(DMA2_Stream7, &DMA_InitStructure);
  
   
  USART_ITConfig(USART1, USART_IT_TC, ENABLE);// 使能串口发送完成中断
  USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);// 使能DMA串口发送和接受请求
  
  DMA_Cmd (DMA2_Stream7,DISABLE);
  while(DMA_GetCmdStatus(DMA2_Stream7)!=DISABLE){}
  DMA_SetCurrDataCounter(DMA2_Stream7,8);
  DMA_Cmd (DMA2_Stream7,ENABLE);
#endif
}

uint8_t cnt=0;
void DMA2_Stream1_IRQHandler(void)
{
  cnt++;
  DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIF1);
  
}