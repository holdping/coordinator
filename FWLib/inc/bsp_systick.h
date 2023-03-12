#ifndef _BSP_SYSTICK_H_
#define _BSP_SYSTICK_H_

#include "stm32f10x.h"

extern uint32_t boot_time_ms; // 系统运行时间
extern uint16_t time_uint_ms; // 定时器产生一次中断时间

void SYSTICK_Init(uint16_t time_ms);
uint32_t SYSTICK_GetTime_Ms(void);
uint32_t SYSTICK_GetTime_Us(void);
void SYSTICK_DelayUs(uint32_t n);
void SYSTICK_DelayMs(uint32_t n);

#endif

