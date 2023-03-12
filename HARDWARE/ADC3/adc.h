#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
 
#define Channel_Num  3			//ת��ͨ������Ŀ
#define Sample_Num  10			//ÿ��ͨ��ת���Ĵ���
 
extern vu16 ADC_ConvertedValue[Sample_Num][Channel_Num];
 
void ADC1_Config(void);
uint16_t get_adc_value(uint16_t Channel);
 
 
#endif 