#ifndef _SENSOR_SMOKE_H_
#define _SENSOR_SMOKE_H_

#include "stm32f10x.h"
	
void   MQ2_Init(void);
float MQ2_GetPPM(void);
void mq2_smog(void);
#endif

