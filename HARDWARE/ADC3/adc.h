#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
 
#define Channel_Num  3			//转换通道的数目
#define Sample_Num  10			//每个通道转换的次数
 
extern vu16 ADC_ConvertedValue[Sample_Num][Channel_Num];
 
void ADC1_Config(void);
uint16_t get_adc_value(uint16_t Channel);
 
 
#endif 