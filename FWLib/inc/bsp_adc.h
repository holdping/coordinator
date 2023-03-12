#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_

#include "stm32f10x.h"
#define soil_pin GPIO_Pin_3
#define LI_pin GPIO_Pin_0
#define MQ135_pin GPIO_Pin_2

void ADC_Pin_Init(void);

u16 ADC_Trans(u8 ch,u8 times);


#endif


