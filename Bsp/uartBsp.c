#include "uartBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"


void UART_Config (void)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;

  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
  
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //数值越低优先级越高
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //数值越低优先级越高
  
  NVIC_Init(&NVIC_InitStructure);
  
//  USART_SendData(USART1,0x12);
}

void USART1_IRQHandler(void)
{
  u8 res;
  if (USART_GetFlagStatus(USART1, USART_IT_RXNE)) {
    USART_ClearFlag(USART1, USART_IT_RXNE);
    res = USART_ReceiveData(USART1);
    USART_SendData(USART1, res);
  }
  
}