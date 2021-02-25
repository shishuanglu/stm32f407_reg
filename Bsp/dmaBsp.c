#include "dmaBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dma.h"

DMA_InitTypeDef DMA_InitStructure;

uint8_t SendBuff[8] = {1,2,3,4,5,6,7,8};
uint8_t ReceiveBuff[8];// = {8,7,6,5,4,3,2,1};
/**
  * @brief  USART1 TX DMA ���ã��ڴ浽�ڴ�
  * @param  ��
  * @retval ��
  */
void DMA_Mem2Mem_Config(void)
{
#if 0
  /*����DMAʱ��*/
  RCC->AHB1ENR |= RCC_AHB1Periph_DMA2;
  

  /*Դ��ַ*/
  DMA2_Stream1->PAR = (uint32_t)SendBuff;
  /*Ŀ���ַ*/
  DMA2_Stream1->M0AR = (uint32_t)ReceiveBuff;
  
  /*���䷽��*/
  DMA2_Stream1->CR = DMA_Channel_0 | DMA_DIR_MemoryToMemory | DMA_PeripheralInc_Enable | DMA_MemoryInc_Enable | DMA_PeripheralDataSize_Byte
                    | DMA_MemoryDataSize_Byte | DMA_Mode_Normal | DMA_MemoryBurst_Single | DMA_PeripheralBurst_Single;
  
  
  /*�����С*/
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
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;        //�ж�Դ��[9:5]��λ��<stm32f10x.h>��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ���1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //�����ȼ���1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);
  
  DMA_ITConfig(DMA2_Stream1,DMA_IT_TC,ENABLE);
    
    //DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_FEIF0);
   // DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIFx);
    
  DMA_Cmd (DMA2_Stream1,DISABLE);
  while(DMA_GetCmdStatus(DMA2_Stream1)!=DISABLE){}
  DMA_SetCurrDataCounter(DMA2_Stream1,8);
  DMA_Cmd (DMA2_Stream1,ENABLE);
    
    
    //������������������ɺͰ봫������ж�λ
    //NDTR�Ĵ���д����
    //ʹ�ܴ���EN
    //STM32F4��DMA1����ʵ�ִ洢���洢�Ĵ���
  
  
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
  
   
  USART_ITConfig(USART1, USART_IT_TC, ENABLE);// ʹ�ܴ��ڷ�������ж�
  USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);// ʹ��DMA���ڷ��ͺͽ�������
  
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