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
	extern int min_1;
 u16 co2_value=0;
 u8 soil_value=0;
 u16 light_value=0;
	extern char RECS[600];
	extern char RECS1[600];
	extern char USART1_RX_BUF[USART1_MAX_RECV_LEN];
u8 DHT11_Temp=0;
u8 DHT11_Hum=0;
extern	u8 LED_state;
extern	u8 fans_state;
extern	u8 hot_state;
extern	u8 cold_state;
extern	u8 steam_state;
extern u8 USART3_RX_FLAG;
extern u16 show_co2(void);
int main(void)
	
{  

	static char erro;
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
    IWDG_Init(5,624);

		usart1_init(115200);
		usart3_init(115200);
	 erro=esp_Init();

	while(1)
	{ 
 
	if(USART3_RX_FLAG==1)
	{
		u1_printf("%s",RECS);
		USART3_RX_FLAG=0;
	}
 	Analys_zig();
		delay_ms(1) ;
		if(min_1)
		{
		  Esp_PUB();
			delay_ms(500);
			esp_pub_state();
			min_1=0;
		}

	}
}

//u16 show_co2(void)
//{
//		co2_value=(u8)USART1_RX_BUF[1]*256+(u8)USART1_RX_BUF[2];
//		return  co2_value;
//	
//}