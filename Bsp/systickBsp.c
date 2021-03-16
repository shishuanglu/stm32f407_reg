#include "systickBsp.h"
#include "core_cm4.h"


void SYSTICK_Config(void)
{


    /*
        ahb=168M
        SysTick_CTRL_CLKSOURCE=1时，clk=ahb/8
        SysTick_CTRL_CLKSOURCE=0时，clk=ahb
        设置为168时，SysTick_Handler中断周期为1us

    */
    SysTick_Config(168);
}
