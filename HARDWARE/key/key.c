#include "key.h"
#include "sys.h"
#include "delay.h" 
//������ʼ������
void KEY_Init(void) //IO ��ʼ��
{
GPIO_InitTypeDef GPIO_InitStructure;
157
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|
RCC_APB2Periph_GPIOE,ENABLE); //ʹ�� PORTAʱ��
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//GPIOA 4-6
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ���ó����룬���� 
GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� GPIOA.0
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������;1�� KEY1 ����;2�� KEY2 ����;3�� KEY3 ���� ;4�� KEY4 ���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY1>KEY2>KEY3>KEY4!!
u8 KEY_Scan(u8 mode)
{
static u8 key_up=1; //�������ɿ���־
if(mode)key_up=1;  //֧������ 
if(KEY1&&(KEY2==0||KEY3==0||KEY4==0))
{
delay_ms(10); //ȥ����
KEY1=0;
if(KEY0==0)return set;
else if(KEY1==0)return up;
else if(KEY2==0)return down;
else if(KEY3==1)return enter;
}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==0)key_up=1; 
return 0; // �ް�������
}