#include "timBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"



void TIM_Config (void)
{
  /*APB2 = 168MHZ*/
  /*Tout()=(TIM_Period+1)(TIM_Prescaler+1)/Tclk*/
  TIM_TimeBaseInitTypeDef TIM1_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
 
  /*1ms 进入一次*/
  TIM1_TimeBaseInitStructure.TIM_Period = 999;       //0-0XFFFF
  TIM1_TimeBaseInitStructure.TIM_Prescaler = 167;       //0-0XFFFF
  TIM1_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM1_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  //TIM1_TimeBaseInitStructure.TIM_RepetitionCounter
  TIM_TimeBaseInit(TIM1, &TIM1_TimeBaseInitStructure);
  
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //数值越低优先级越高
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //数值越低优先级越高
  NVIC_Init(&NVIC_InitStructure);
  
  TIM_Cmd(TIM1, ENABLE);
  
}


void TIM1_UP_TIM10_IRQHandler(void)
{
  static u8 res;
    
  static u16 cnt=0;
  
  if (SET == TIM_GetITStatus(TIM1,TIM_IT_Update))
  {
    

    //TIM_SetCompare1(TIM3, cnt);
    if(cnt>=999) {
      GPIO_ToggleBits(GPIOG, GPIO_Pin_15);

      cnt=0;
    } else {
      cnt++;
    }
    res++;
    TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
  }
    
}
