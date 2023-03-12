#include "sys.h"
void NVIC_Configuration2(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

}

void SysTick_Init(int n)
{
/* SystemFrequency /1000 1ms ????
* SystemFrequency / 100000 10us ????
* SystemFrequency / 1000000 1us ????
*/
if (SysTick_Config(SystemCoreClock/1000000*n)) {
/* Capture error */
	  while(1)
			;
	}
}
