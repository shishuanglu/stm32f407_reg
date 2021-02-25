#include "rccBsp.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rcc.h"

void HSI_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q)	
{
    __IO uint32_t HSIStartUpStatus = 0;

    // 把RCC外设初始化成复位状态
    RCC_DeInit();

    //使能HSI, HSI=16M
    RCC_HSICmd(ENABLE);

    // 等待 HSI 就绪
    HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY;

    // 只有 HSI就绪之后则继续往下执行
    if (HSIStartUpStatus == RCC_CR_HSIRDY)
    {
        // 调压器电压输出级别配置为1，以便在器件为最大频率
        // 工作时使性能和功耗实现平衡
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;
        PWR->CR |= PWR_CR_VOS;
        
        // HCLK = SYSCLK / 1    168M
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        
        // PCLK2 = HCLK / 2     84M
        RCC_PCLK2Config(RCC_HCLK_Div2);
        
        // PCLK1 = HCLK / 4     42M
        RCC_PCLK1Config(RCC_HCLK_Div4);
        
        // 如果要超频就得在这里下手啦
        // 设置PLL来源时钟，设置VCO分频因子m，设置VCO倍频因子n，
        //  设置系统时钟分频因子p，设置OTG FS,SDIO,RNG分频因子q
        //pllclk=(CLK*PLLN)/(PLLM*PLLP)=(16*336)/(16*2)
        RCC_PLLConfig(RCC_PLLSource_HSI, m, n, p, q);
        
        // 使能PLL
        RCC_PLLCmd(ENABLE);

        // 等待 PLL稳定
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }   

        /*-----------------------------------------------------*/
        //开启 OVER-RIDE模式，以能达到更高频率(F429才有该功能)
        //    PWR->CR |= PWR_CR_ODEN;
        //    while((PWR->CSR & PWR_CSR_ODRDY) == 0)
        //    {
        //    }
        //    PWR->CR |= PWR_CR_ODSWEN;
        //    while((PWR->CSR & PWR_CSR_ODSWRDY) == 0)
        //    {
        //    }      
        // 配置FLASH预取指,指令缓存,数据缓存和等待状态
        FLASH->ACR = FLASH_ACR_PRFTEN 
                    | FLASH_ACR_ICEN 
                    |FLASH_ACR_DCEN 
                    |FLASH_ACR_LATENCY_5WS;
        /*-----------------------------------------------------*/
            
            // 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        
        //RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

        // 读取时钟切换状态位，确保PLLCLK被选为系统时钟
        while (RCC_GetSYSCLKSource() != 0x08)
        {
        }
    }
    else
    { // HSI启动出错处理
        while (1){}
    }
}

void SYSCLK_Configuration(void)
{        
        u8 status;
        RCC_ClocksTypeDef RCC_Clocks;
        //ErrorStatus HSEStartUpStatus;
        /* RCC system reset */
        RCC_DeInit();
        /* Enable Internal High Speed oscillator */
        RCC_HSICmd(ENABLE);        
        /* Wait till HSI is ready */
        while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
  {
  }
        /* HCLK = SYSCLK */
  RCC_HCLKConfig(RCC_SYSCLK_Div1);
  /* PCLK2 = HCLK */
  RCC_PCLK2Config(RCC_HCLK_Div2);
  /* PCLK1 = HCLK/2 */
  RCC_PCLK1Config(RCC_HCLK_Div4);    
  /* SYSCLK = ((HSI / 16) * 336) / 2 = 168MHz */
        RCC_PLLConfig(RCC_PLLSource_HSI, 16, 336, 2, 4);
  /* Enable PLL */
  RCC_PLLCmd(ENABLE);
  /* Wait till PLL is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {}
  /* Select PLL as system clock source */
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  /* Wait till PLL is used as system clock source */
  while (RCC_GetSYSCLKSource() != 0x00)
  {}                
        RCC_GetClocksFreq(&RCC_Clocks);        
}

void RCC_Config (void)
{
    /*使用内部高速时钟时调用，16M*/
    HSI_SetSysClock(16, 336, 4, 7);
    //SYSCLK_Configuration ();
}