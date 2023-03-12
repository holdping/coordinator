#include "bsp_systick.h"

uint32_t boot_time_ms; // 系统运行时间
uint16_t time_uint_ms; // 定时器产生一次中断时间

// 初始化滴答定时器并配置定时器是1ms中断
// time_ms : 0~349ms   349 = 0xFFFFFF / (48m / 1000)
void SYSTICK_Init(uint16_t time_ms)
{
	time_uint_ms = time_ms;
	
	// 初始化系统定时器及中断 并打开定时器
	SysTick_Config(SystemCoreClock / 1000 * time_ms);
	/**
	 * 1s计数 SystemCoreClock
	 * 1ms计数 SystemCoreClock / 1000
	 * 1us计数 SystemCoreClock / 1000000
	 */	
}

// 滴答定时器中断处理函数
void SysTick_Handler(void)
{
	boot_time_ms += time_uint_ms;
}

// 获取当前时间毫秒数
uint32_t SYSTICK_GetTime_Ms(void)
{
	return boot_time_ms;
}

// 获取当前时间微秒数
uint32_t SYSTICK_GetTime_Us(void)
{
	return boot_time_ms * 1000 + SysTick->VAL / (SystemCoreClock / 1000000);
}

// 延时函数 us
void SYSTICK_DelayUs(uint32_t n)
{
	uint32_t ticks;
	uint32_t told;
	uint32_t tnow;
	uint32_t tcnt = 0;
	uint32_t reload;
	reload = SysTick->LOAD;	// 获取重装载值
	ticks = n * (SystemCoreClock / 1000000); // 需要递减的装载值数
	told = SysTick->VAL; // 刚进入时计数器值
	while(1)
	{
		tnow = SysTick->VAL; // 当前计数器的值
		if(tnow != told)
		{
			if(tnow < told)
			{
				tcnt += told - tnow;
			}
			else
			{
				tcnt += reload - tnow + told;
			}
			told = tnow;
			if(tcnt >= ticks)
			{
				break;
			}
		}
	}
}

// 延时函数 ms
void SYSTICK_DelayMs(uint32_t n)
{
	SYSTICK_DelayUs(n * 1000);
}

