#include "captureBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"


/*定时器2，通道1，输出引脚PA0*/
void CAPTURE_Config (void)
{
  /*APB1 = 84MHZ*/
  /*Tout()=(TIM_Period+1)(TIM_Prescaler+1)/Tclk*/
  TIM_TimeBaseInitTypeDef TIM2_TimeBaseInitStructure;
  TIM_ICInitTypeDef TIM2_ICInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
  
  
  TIM2_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM2_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  /*1MS*/
  TIM2_TimeBaseInitStructure.TIM_Period = 999;       //0-0XFFFF
  TIM2_TimeBaseInitStructure.TIM_Prescaler = 83;       //0-0XFFFF
  //TIM1_TimeBaseInitStructure.TIM_RepetitionCounter
  TIM_TimeBaseInit(TIM2, &TIM2_TimeBaseInitStructure);
  
  TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM2_ICInitStructure.TIM_ICFilter = 0x00;
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//映射到TI1
  TIM_ICInit(TIM2, &TIM2_ICInitStructure);

  TIM_ITConfig(TIM2, TIM_IT_CC1|TIM_IT_Update, ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //数值越低优先级越高
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //数值越低优先级越高
  NVIC_Init(&NVIC_InitStructure);

  
  TIM_Cmd(TIM2, ENABLE);
  
  //TIM_OC1PolarityConfig();    //设置捕获沿
  
}

#if 1
void TIM2_IRQHandler(void)
{
  static u8 res;
  static u16 cnt=0;
  
  if (SET == TIM_GetITStatus(TIM2,TIM_IT_CC1))
  {
    //GPIO_ToggleBits(GPIOG, GPIO_Pin_15);


    res++;
    TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
  }
  
  if (SET == TIM_GetITStatus(TIM2,TIM_IT_Update))
  {
    //GPIO_ToggleBits(GPIOG, GPIO_Pin_15);
    cnt++;
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
  }
    
}
#endif
