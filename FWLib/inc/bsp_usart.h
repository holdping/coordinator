#ifndef _BSP_USART_H_
#define _BSP_USART_H_

#include "stm32f10x.h"

void USART1_Init(void); // 串口1初始化函数声明
void USART1_DataProcess(void); // 轮询方式串口数据处理
 
 #include "stm32f10x.h"
 #include "stdio.h"
 
 #define DEBUG1 1
 #define DEBUG_USART_BAUDRATE 115200
 
 // 串口对应的DMA请求通道
 #define  USART_TX_DMA_CHANNEL     DMA1_Channel5
 // 外设寄存器地址
 #define  USART_DR_ADDRESS        (USART1_BASE+0x04)
 // 一次发送的数据量
 #define  RECEIVEBUFF_SIZE            5000
 
 #ifdef DEBUG1
 // 串口 1-USART1
 #define DEBUG_USARTx USART1
 #define DEBUG_USART_CLK RCC_APB2Periph_USART1
 #define DEBUG_USART_APBxClkCmd RCC_APB2PeriphClockCmd
 // USART GPIO 引脚宏定义
 #define DEBUG_USART_GPIO_CLK (RCC_APB2Periph_GPIOA)
 #define DEBUG_USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd
 #define DEBUG_USART_TX_GPIO_PORT GPIOA
 #define DEBUG_USART_TX_GPIO_PIN GPIO_Pin_9
 #define DEBUG_USART_RX_GPIO_PORT GPIOA
 #define DEBUG_USART_RX_GPIO_PIN GPIO_Pin_10
 #define DEBUG_USART_IRQ USART1_IRQn
 #define DEBUG_USART_IRQHandler USART1_IRQHandler
 
 #elif DEBUG2
 // 串口2
 #define DEBUG_USARTx USART2
 #define DEBUG_USART_CLK RCC_APB1Periph_USART2
 #define DEBUG_USART_APBxClkCmd RCC_APB1PeriphClockCmd
 // USART GPIO 引脚宏定义
 #define DEBUG_USART_GPIO_CLK (RCC_APB2Periph_GPIOA)
 #define DEBUG_USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd
 #define DEBUG_USART_TX_GPIO_PORT GPIOA
 #define DEBUG_USART_TX_GPIO_PIN GPIO_Pin_2
 #define DEBUG_USART_RX_GPIO_PORT GPIOA
 #define DEBUG_USART_RX_GPIO_PIN GPIO_Pin_3
 #define DEBUG_USART_IRQ USART2_IRQn
 #define DEBUG_USART_IRQHandler USART2_IRQHandler
 
 #elif DEBUG3
 // 串口3
 #define DEBUG_USARTx USART3
 #define DEBUG_USART_CLK RCC_APB1Periph_USART3
 #define DEBUG_USART_APBxClkCmd RCC_APB1PeriphClockCmd
 // USART GPIO 引脚宏定义
 #define DEBUG_USART_GPIO_CLK (RCC_APB2Periph_GPIOB)
 #define DEBUG_USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd
 #define DEBUG_USART_TX_GPIO_PORT GPIOB
 #define DEBUG_USART_TX_GPIO_PIN GPIO_Pin_10
 #define DEBUG_USART_RX_GPIO_PORT GPIOB
 #define DEBUG_USART_RX_GPIO_PIN GPIO_Pin_11
 #define DEBUG_USART_IRQ USART3_IRQn
 #define DEBUG_USART_IRQHandler USART3_IRQHandler
 
 #elif DEBUG4
 // 串口4
 #define DEBUG_USARTx USART4
 #define DEBUG_USART_CLK RCC_APB1Periph_USART4
 #define DEBUG_USART_APBxClkCmd RCC_APB1PeriphClockCmd
 // USART GPIO 引脚宏定义
 #define DEBUG_USART_GPIO_CLK (RCC_APB2Periph_GPIOC)
 #define DEBUG_USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd
 #define DEBUG_USART_TX_GPIO_PORT GPIOC
 #define DEBUG_USART_TX_GPIO_PIN GPIO_Pin_10
 #define DEBUG_USART_RX_GPIO_PORT GPIOC
 #define DEBUG_USART_RX_GPIO_PIN GPIO_Pin_11
 #define DEBUG_USART_IRQ USART4_IRQn
 #define DEBUG_USART_IRQHandler USART4_IRQHandler
 
 #elif DEBUG5
 // 串口5
 #define DEBUG_USARTx USART5
 #define DEBUG_USART_CLK RCC_APB1Periph_USART5
 #define DEBUG_USART_APBxClkCmd RCC_APB1PeriphClockCmd
 // USART GPIO 引脚宏定义
 #define DEBUG_USART_GPIO_CLK (RCC_APB2Periph_GPIOC)
 #define DEBUG_USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd
 #define DEBUG_USART_TX_GPIO_PORT GPIOC
 #define DEBUG_USART_TX_GPIO_PIN GPIO_Pin_12
 #define DEBUG_USART_RX_GPIO_PORT GPIOD
 #define DEBUG_USART_RX_GPIO_PIN GPIO_Pin_2
 #define DEBUG_USART_IRQ USART5_IRQn
 #define DEBUG_USART_IRQHandler USART5_IRQHandler
 // 打开串口GPIOD的时钟
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
 

 
 static void NVIC_Configuration(void);
 void DEBUG_Config(void);
 void Usart_SendByte(USART_TypeDef* pUSARTX, char data);
 void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
 int fputc(int ch, FILE *f);
 int fgetc(FILE *f);
 void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
 #endif

static void NVIC_Configuration(void);

void USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);


#endif /* __USART_H */



