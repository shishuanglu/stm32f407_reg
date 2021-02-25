#include "extiBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"

unsigned char temp=0;

void EXTI_Config (void)
{
  EXTI_InitTypeDef EXTI_InitStructrue;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
    
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
  
  EXTI_InitStructrue.EXTI_Line = EXTI_Line0;
  EXTI_InitStructrue.EXTI_LineCmd = ENABLE;
  EXTI_InitStructrue.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructrue.EXTI_Trigger = EXTI_Trigger_Falling;
  
  EXTI_Init(&EXTI_InitStructrue);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //数值越低优先级越高
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //数值越低优先级越高
  
  NVIC_Init(&NVIC_InitStructure);
  
  
}


void EXTI0_IRQHandler(void)
{
  
  if (SET == EXTI_GetITStatus(EXTI_Line0)) {
    
    EXTI_ClearITPendingBit(EXTI_Line0);
    
   temp++; 
  }
  
  
  
}