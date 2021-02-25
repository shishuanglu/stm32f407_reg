//#include "stm32f4xx.h"
#include "rccBsp.h"
#include "dmaBsp.h"
#include "uartBsp.h"
#include "extiBsp.h"
#include "gpioBsp.h"
#include "iwdgBsp.h"
#include "timBsp.h"
#include "pwmBsp.h"
#include "captureBsp.h"
#include "canBsp.h"
#include "sdioBsp.h"
#include <stdio.h>


unsigned char b=0;
u8 canbuf[8] = {1,1,1,1,1,1,1,1};

u8 res = 0;

int main()
{
  

  /*
    有外部晶振系统时钟=(CLK*PLLN)/(PLLM*PLLP)=(CLK*336)/(25*2)
    没有外部晶振系统时钟 = 16MHZ
  */
  //时钟SYSCLK输出
  /*RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef SCK_InitStructure;
  SCK_InitStructure.GPIO_Pin = GPIO_Pin_9;
  SCK_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  SCK_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  SCK_InitStructure.GPIO_OType = GPIO_OType_PP; 
  SCK_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;   //下拉
  GPIO_Init(GPIOC,&SCK_InitStructure);
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_MCO);
  RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_4);*/

  /**/
  RCC_Config();
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  GPIO_Config ();
  
  //UART_Config ();
  
  //EXTI_Config ();
  
  //IWDG_Config ();
  
  //TIM_Config();
  
  PWM_Config();
  
  //CAPTURE_Config();
  //DMA_Mem2Mem_Config ();

  //CAN_Config();
   
  while(SD_Init())//检测不到SD卡
  {
    printf("SD card init error");
  }

  show_sdcard_info();	//打印SD卡相关信息

  while(1)
  {
    b++;
    //res = CAN1_Send_Msg(canbuf,8);
    //CAN1_Receive_Msg(canbuf);
    //IWDG_ReloadCounter();//应用程序喂狗
  }

}

