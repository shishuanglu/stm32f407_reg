#include "iwdgBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_iwdg.h"



void IWDG_Config (void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//取消寄存器写保护
    IWDG_SetPrescaler(IWDG_Prescaler_32);//设置独立看门狗分频系数，M4使用LSI,32kHz，32分频最小为1ms
    IWDG_SetReload(100);//设置看门狗重装载值100ms
    IWDG_Enable();//使能看门狗
    
    IWDG_ReloadCounter();//应用程序喂狗
  
}


