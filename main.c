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
#include "ff.h"
#include "systickBsp.h"
#include "ucos_ii.h"


unsigned char b=0;
u8 canbuf[8] = {1,1,1,1,1,1,1,1};

u8 res = 0;

u8 writeBuf[512] = {1,2,3,4,5,6,7,8};
u8 readBuf[512];

FATFS fs;
FIL fil;
UINT fnum; 


#define OS_TASK_TMR_PRIO                         3
 
/* task priority */ 
 
#define STARTUP_TASK_PRIO                           6 
 
/* task stack size */ 
 
#define STARTUP_TASK_STK_SIZE                   80
 
 
 
#define                  Task1_Stk_Size             64
 
#define                  Task1_Prio                   11
static OS_STK       Task1_stk[Task1_Stk_Size];
static OS_STK       Task2_stk[Task1_Stk_Size];
 
 
 
static void Task1(void *p_arg) 
 
{ 
 
         for (;;) 
 
         { 
 
 
                 OSTimeDly(500);   
 
         } 
 
}

static void Task2(void *p_arg) 
 
{ 
 
         for (;;) 
 
         { 
 
 
                 OSTimeDly(1000);   
 
         } 
 
}

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
#if RCC_CONFIG_ENABLE
  RCC_Config();
#endif

#if SYSTICK_CONFIG_ENABLE
  SYSTICK_Config();
#endif

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
#if GPIO_CONFIG_ENABLE 
  GPIO_Config ();
#endif
  
#if UART_CONFIG_ENABLE
  UART_Config ();
#endif
  
#if EXTI_CONFIG_ENABLE
  EXTI_Config ();
#endif
  
#if IWDG_CONFIG_ENABLE
  IWDG_Config ();
#endif
  
#if TIM_CONFIG_ENABLE
  TIM_Config();
#endif
  
#if PWM_CONFIG_ENABLE
  PWM_Config();
#endif
  
#if CAPTURE_CONFIG_ENABLE
  CAPTURE_Config();
#endif

#if DMA_CONFIG_ENABLE
  DMA_Mem2Mem_Config ();
#endif

#if CAN_CONFIG_ENABLE
  CAN_Config();
#endif
/*   
  while(SD_Init())//检测不到SD卡
  {
    printf("SD card init error");
  }

  show_sdcard_info();	//打印SD卡相关信息
  */

  //SD_WriteDisk(writeBuf,0,1);
  //SD_ReadDisk(readBuf,0,1);
  
  /*res = f_mount(&fs,"0:",1); 	
  //res=f_mkfs("0:",0,512);
  res = f_open(&fil,"abc.txt",FA_OPEN_ALWAYS | FA_WRITE);
  res=f_write(&fil,writeBuf,sizeof(writeBuf),&fnum);
  f_close(&fil);*/


  OSInit(); 

  OSTaskCreate(Task1, (void *)0, 

          &Task1_stk[Task1_Stk_Size-1], Task1_Prio);
  OSTaskCreate(Task2, (void *)0, 

          &Task2_stk[Task1_Stk_Size-1], 12);

  OSStart();
  while(1)
  {
    b++;
    //res = CAN1_Send_Msg(canbuf,8);
    //CAN1_Receive_Msg(canbuf);
    //IWDG_ReloadCounter();//应用程序喂狗
  }

}

