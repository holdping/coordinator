#include "key.h"
#include "sys.h"
#include "delay.h" 
//按键初始化函数
void KEY_Init(void) //IO 初始化
{
GPIO_InitTypeDef GPIO_InitStructure;
157
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|
RCC_APB2Periph_GPIOE,ENABLE); //使能 PORTA时钟
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//GPIOA 4-6
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 设置成输入，下拉 
GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIOA.0
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下;1， KEY1 按下;2， KEY2 按下;3， KEY3 按下 ;4， KEY4 按下 WK_UP
//注意此函数有响应优先级,KEY1>KEY2>KEY3>KEY4!!
u8 KEY_Scan(u8 mode)
{
static u8 key_up=1; //按键按松开标志
if(mode)key_up=1;  //支持连按 
if(KEY1&&(KEY2==0||KEY3==0||KEY4==0))
{
delay_ms(10); //去抖动
KEY1=0;
if(KEY0==0)return set;
else if(KEY1==0)return up;
else if(KEY2==0)return down;
else if(KEY3==1)return enter;
}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==0)key_up=1; 
return 0; // 无按键按下
}