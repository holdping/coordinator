#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
 
	    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11;				 //LED0-->PC.13 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 GPIO_SetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11);						 //���̵�������ȫ������

}
