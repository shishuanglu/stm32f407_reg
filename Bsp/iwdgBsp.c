#include "iwdgBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_iwdg.h"



void IWDG_Config (void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//ȡ���Ĵ���д����
    IWDG_SetPrescaler(IWDG_Prescaler_32);//���ö������Ź���Ƶϵ����M4ʹ��LSI,32kHz��32��Ƶ��СΪ1ms
    IWDG_SetReload(100);//���ÿ��Ź���װ��ֵ100ms
    IWDG_Enable();//ʹ�ܿ��Ź�
    
    IWDG_ReloadCounter();//Ӧ�ó���ι��
  
}


