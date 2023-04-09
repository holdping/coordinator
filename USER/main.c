#include "stm32f10x.h"
#include "delay.h"
#include "string.h"
#include "Timer.h"
#include <stdio.h>
#include "esp.h"
#include "usart3.h"
#include "oled.h"
#include "sys.h"
#include "co2.h"
#include "iwdg.h"
void sned_data(void);
u8 Connect_flag = 0;
extern u8 Err;
	extern int min_1;
 u16 co2_value=0;
 u8 soil_value=0;
 u16 light_value=0;
 u8 systemmode=0;
	extern char RECS[600];
	extern char RECS1[600];
	extern char USART1_RX_BUF[USART1_MAX_RECV_LEN];
u8 DHT11_Temp=0;
u8 DHT11_Hum=0;
u8 buff[30];//参数显示缓存数组
extern u8 temp_min;
extern u8 temp_max;
extern u8 send_state;
extern	u8 LED_state;
extern	u8 fans_state;
extern	u8 hot_state;
extern	u8 cold_state;
extern	u8 steam_state;
extern u8 USART3_RX_FLAG;
extern u8 USART1_RX_FLAG;
void show_data(void);
int main(void)
	
{  
	   Timer_Init();
     OLED_Init();				//OLED???
	OLED_Clear();				//OLED??
	OLED_ShowCHinese(0,0,0);   //温
	OLED_ShowCHinese(16,0,2);  //度
	OLED_ShowCHinese(64,0,1);  //湿
	OLED_ShowCHinese(80,0,2);  //度
 

	OLED_ShowCHinese(0,2,5);    //光
	OLED_ShowCHinese(16,2,6);   //照
	OLED_ShowCHinese(64,2,4);   //土
	OLED_ShowCHinese(80,2,12);  //壤
	

	
	OLED_ShowCHinese(0,4,17);   //二
	OLED_ShowCHinese(16,4,18);  //氧
	OLED_ShowCHinese(32,4,19);  //化
	OLED_ShowCHinese(48,4,20);  //碳
    IWDG_Init(5,625);

		usart1_init(115200);
			 u1_printf("复位");
		usart3_init(115200);
//	 esp8266();
				Err=esp_Init();   
		if(Err==0)
		{
			OLED_ShowCHinese(32,6,34);
			OLED_ShowCHinese(48,6,35);
			OLED_ShowCHinese(64,6,36);
			OLED_ShowCHinese(80,6,37);
		}
 u8 flag=0;


	while(1)
	{ 
//      	Analys_zig();
			if((Err==0)||(Connect_flag==1)){  
			OLED_ShowCHinese(32,6,34);
			OLED_ShowCHinese(48,6,35);
			OLED_ShowCHinese(64,6,36);
			OLED_ShowCHinese(80,6,37);
				sned_data();
													}
			else
			{
			  Err=esp_Init();
			}
		
		//	u1_printf("system:%d,temp_min:%d\r\n",systemmode,temp_min);
			delay_ms(1);

		show_data();


	}
}

void show_data(void)
{
			sprintf((char*)buff,":%4d",light_value);
					OLED_ShowString(32,2,buff,16);            //显示光照值
	
//	        u1_printf("光照:%2d\r\n",light_value); 
					sprintf((char*)buff,":%2d%%",soil_value);
					OLED_ShowString(96,2,buff,16);           //显示土壤值
	
//					u1_printf("土壤湿度:%2d\r\n",soil_value); 
					sprintf((char*)buff,":%4dp",co2_value);
					OLED_ShowString(64,4,buff,16);//显示MQ135数据
	
//					u1_printf("MQ135:%4dp\r\n",co2_value); 
					sprintf((char*)buff,":%2dC",DHT11_Temp);                                          
					OLED_ShowString(32,0,buff,16);	          //显示温度值
	
					sprintf((char*)buff,":%2d%%",DHT11_Hum);
					OLED_ShowString(96,0,buff,16);            //显示湿度值
//					u1_printf("温度:%2dC 湿度:%2d%%\r\n ",DHT11_Temp,DHT11_Hum);
}

void sned_data(void)
{
	
	if(USART1_RX_FLAG==0)
	{
		u3_printf("%s\r\n",RECS);
		memset(RECS,0,sizeof(RECS));
		 USART1_RX_FLAG=1;
	}
		delay_ms(1) ;

		if(min_1)
		{
		  Esp_PUB();
			delay_ms(1000);
//			esp_pub_state();
			min_1=0;
		}
		
		if(send_state==3)
		{
			esp_pub_state();
			send_state=0;
		}
}