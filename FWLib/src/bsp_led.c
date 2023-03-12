#include "bsp_led.h"


//LED 的 GPIO 初始化函数
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; // 定义 GPIO 结构体
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE); // 打开GPIOC 时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // 输出
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // 推挽
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15; // LED1对应的IO口
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // 上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3; // 50MHz输出速度
	GPIO_Init(GPIOC,&GPIO_InitStruct); // 初始化 GPIO
	GPIO_SetBits(GPIOC,GPIO_Pin_14|GPIO_Pin_15); // 设置LED1初始状态为灯灭 
}

