#include "pwmBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"


/*定时器3，通道1，输出引脚PB4*/
void PWM_Config (void)
{
  /*
  APB1 = 84MHZ，参考手册上if APB_presc=1则定时器时钟*1，否则*2
  因此APB1定时器时钟 = 84MHZ*/
  /*Tout()=(TIM_Period+1)(TIM_Prescaler+1)/Tclk*/
  TIM_TimeBaseInitTypeDef TIM3_TimeBaseInitStructure;
  TIM_OCInitTypeDef TIM3_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);
  

  
  TIM3_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM3_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  /*1MS 进入一次*/
  TIM3_TimeBaseInitStructure.TIM_Period = 999;       //0-0XFFFF
  TIM3_TimeBaseInitStructure.TIM_Prescaler = 83;       //0-0XFFFF
  //TIM1_TimeBaseInitStructure.TIM_RepetitionCounter
  TIM_TimeBaseInit(TIM3, &TIM3_TimeBaseInitStructure);

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //数值越低优先级越高
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //数值越低优先级越高
  NVIC_Init(&NVIC_InitStructure);

  TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//TIM_OCPolarity_High;  //极性
  TIM3_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //输出模式
  TIM_OC1Init(TIM3, &TIM3_OCInitStructure);
  
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  
  TIM_Cmd(TIM3, ENABLE);
  
  TIM_SetCompare1(TIM3, 99);//设置比较值
  
}

#if 1
void TIM3_IRQHandler(void)
{
  static u8 res;
  static u16 cnt=0;
  
  if (SET == TIM_GetITStatus(TIM3,TIM_IT_Update))
  {
    GPIO_ToggleBits(GPIOG, GPIO_Pin_15);

    /*TIM_SetCompare1(TIM3, cnt);
    if(cnt>=999) {
      cnt=0;
    } else {
      cnt+=100;
    }*/
    res++;
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
  }
    
}
#endif
