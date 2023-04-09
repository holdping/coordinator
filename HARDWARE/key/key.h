#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define KEY3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define KEY4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define set 1
#define up 2
#define down 3
#define enter 4
void KEY_init(void);  //IO≥ı ºªØ         
u8 KEY_Scan(u8);
#endif