#include "bsp_usart.h" 
#include <stdio.h>

#define EN_USART1_INTERRUPT  1

// 标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
} ; 
FILE __stdout;       
// 重定义printf函数 
int fputc(int ch, FILE *f)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);	// 等待发送完成
	USART_SendData(USART1, (uint8_t) ch);  
	return ch;
}

//串口 1初始化函数
void USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;  // 定义 IO 初始化的结构体变量
	USART_InitTypeDef USART_InitStruct; // 定义串口初始化的结构体变量
#if EN_USART1_INTERRUPT
	NVIC_InitTypeDef NVIC_InitStructure; // 定义中断的结构体变量
#endif
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE); // 使能对应 GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); // 使能串口 1时钟
	
	//串口 1对应引脚复用映射
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // 复用功能
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // 推挽复用输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //相对于引脚
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // 上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3; // 速度50MHz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_0); // GPIOB6 复用为 USART1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_0); // GPIOB7 复用为 USART1
	
	USART_DeInit(USART1);
	//串口1端口配置
	USART_InitStruct.USART_BaudRate = 115200; // 波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 收发模式
	USART_InitStruct.USART_Parity = USART_Parity_No; // 无奇偶校验位
	USART_InitStruct.USART_StopBits = USART_StopBits_1; // 一个停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 字长为 8位数据
	USART_Init(USART1, &USART_InitStruct);
	
	USART_Cmd(USART1, ENABLE); // 使能串口
	
//	USART_ClearFlag(USART1, USART_FLAG_TC); // 清除发送完成标志位
	
#if EN_USART1_INTERRUPT
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); // 使能串口为接受中断
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; // 串口中断通道
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0; // 抢占优先级 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  // IRQ 通道使能
	NVIC_Init(&NVIC_InitStructure); // 初始化串口中断

#endif
}

// 轮询方式串口数据处理
void USART1_DataProcess(void)
{
	uint8_t usart1_data;
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET)
	{
		usart1_data = USART_ReceiveData(USART1);
		USART_SendData(USART1,usart1_data);		
	}
}

#if EN_USART1_INTERRUPT
uint8_t usart1_data;
//串口中断服务函数
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)) // 检测串口中断是否发生
	{
		usart1_data = USART_ReceiveData(USART1);
		USART_SendData(USART1,usart1_data);
	}
}
#endif

