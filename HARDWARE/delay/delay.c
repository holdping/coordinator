#include "delay.h"
#include "iwdg.h"

#define 		AHB_freq			72000000UL
#define 		APB1_freq			36000000UL
#define 		APB2_freq			72000000UL
void delay_ms(u16 ms)
{
	ms = 1864 <= ms ? 1864 : ms;
	SysTick->LOAD = ms * (AHB_freq / 8000);
	SysTick->VAL = 0;
	SysTick->CTRL = 0x01;
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	SysTick->CTRL &= ~(0x01<<SysTick_CTRL_ENABLE_Pos);
	IWDG_Feed();                                      
}
//延时nus
//nus为要延时的us数.		    								   
/**
	* @name		delay_us
  * @brief  ??????
	* @param  us	?????   0 ~ 2^24
	* @return void
	* @Sample delay_us(2)
  */
void delay_us(u32 us)
{
	us = (1<<25) <= us ? (1<<25) - 1 : us;
	//LOAD(????)= t(????,??:?) x T(??,??:Hz)
	SysTick->LOAD = us * (AHB_freq / 8000000);
	SysTick->VAL = 0;
	SysTick->CTRL = 0x01;
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	SysTick->CTRL &= ~(0x01<<SysTick_CTRL_ENABLE_Pos);
}


































