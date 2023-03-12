#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"
#include "sys.h"
#define LED_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define hot_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define cold_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define fans_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define steam_state  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)

#define LED0  PAout(4)  // led�� 
#define HOT   PAout(5)  // ����Ƭ
#define COLD  PAout(6)  // ����Ƭ
#define FANS  PAout(7) // ����
#define jsq   PAout(8)  // ��ʪ��
#define LED3  PAout(12)// PA12

void LED_Init(void);
#endif
