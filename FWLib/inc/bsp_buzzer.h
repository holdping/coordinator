#ifndef _BSP_BUZZER_H_
#define _BSP_BUZZER_H_

#include "stm32f10x.h"

#define BUZZER_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_13); // 将GPIOC口的第13号引脚输出为低电平
#define BUZZER_OFF GPIO_SetBits(GPIOC,GPIO_Pin_13); // 将GPIOC口的第13号引脚输出为高电平

void Buzzer_Init(void); // 蜂鸣器函数声明
void Buzzer_Bi(void);
#endif

