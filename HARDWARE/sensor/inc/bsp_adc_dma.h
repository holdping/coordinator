#ifndef _BSP_ADC_DMA_H_
#define _BSP_ADC_DMA_H_

#include "stm32f0xx.h"

extern __IO uint16_t ADC_Value;

void ADC_DMA_Init(void);
void DMA1_Calculation(void);

#endif

