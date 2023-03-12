#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#include "stm32f10x.h"

#define LED_ON    GPIO_ResetBits(GPIOC,GPIO_Pin_14); // 将GPIOC口的第14号引脚输出为低电平（灯亮）
#define LED_OFF   GPIO_SetBits(GPIOC,GPIO_Pin_14); // 将GPIOC口的第 14号引脚输出为高电平（灯灭）
	
void LED_Init(void);

#endif


