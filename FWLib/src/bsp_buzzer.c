#include "bsp_buzzer.h"
#include "bsp_systick.h"
#include "bsp_led.h"
//蜂鸣器的初始化函数
void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; // 定义 GPIO 结构体
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE); // 打开GPIOC口时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // 输出
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // 推挽
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13; // 蜂鸣器对应 IO 口
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // 上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3; // 50MHZ输出速度
	GPIO_Init(GPIOC, &GPIO_InitStruct); // 初始化 GPIO
	GPIO_SetBits(GPIOC, GPIO_Pin_13 ); // 设置蜂鸣器初始状态为关 
}	
	
void Buzzer_Bi(void)
{
	BUZZER_ON; // 蜂鸣器关
	SYSTICK_DelayMs(100); //延时 100ms
	BUZZER_OFF; // 蜂鸣器开
	SYSTICK_DelayMs(100); //延时 100ms
}
