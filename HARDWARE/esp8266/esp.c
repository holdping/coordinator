#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "esp.h"
#include "usart3.h"
#include "bsp_adc.h"


extern u16 co2_value;
extern u8 soil_value;
extern u16 light_value;
extern u8 DHT11_Temp,DHT11_Hum;
 u8 LED_state=0;
 u8 fans_state=0;
 u8 hot_state=0;
 u8 cold_state=0;
 u8 steam_state=0;
extern char RECS[600];
extern char RECS1[600];
const char* WIFI ="mali.apply";
const char* WIFIASSWORD="999999999";
const char* ClintID="e455919db9594116a2da839ed1aa346d";
const char* username="9ihdhvwqdvqnhnq1";
const char* passwd="H0oBbZwHmj";
const char* Url="gz-3-mqtt.iot-api.com";
const char* pubtopic="attributes";
const char* subtopic="attributes/push";
const char* s_soil_value="soil_value";
const char* s_light_value="light_value";
const char* s_temp_value="temp_value";
const char* s_hum_value="hum_value";
const char* s_co2_value="co2_value";
const char* s_led="LED_state";
const char* s_cold="cold_state";
const char* s_hot="hot_state";
const char* s_fans="fans_state";
const char* s_steam="steam_state";
char* ret;
int esp_Init(void)
{
	memset(RECS,0,sizeof(RECS));
	u3_printf("AT+RST\r\n");  //重启
	delay_ms(500);
	
//	memset(RECS,0,sizeof(RECS));
//	u3_printf("ATE0\r\n");    //关闭回显
//	delay_ms(10);
//	if(strcmp(RECS,"OK"))
//		return 1;
	
	u3_printf("AT+CWMODE=1\r\n"); //Station模式
	delay_ms(1000);
	if(strcmp(RECS,"OK")!=0)
		return 0;
	
	memset(RECS,0,sizeof(RECS));
	u3_printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
	delay_ms(1000);
	if(strcmp(RECS,"OK")!=0)
		return 2;
	
	memset(RECS,0,sizeof(RECS));
	u3_printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
	delay_ms(1000);
	if(strcmp(RECS,"OK")!=0)
		return 3;
	
	memset(RECS,0,sizeof(RECS));
	u3_printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
	delay_ms(1000);
	if(strcmp(RECS,"OK"))
		return 4;
	
	u3_printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
	delay_ms(1000);
	if(strcmp(RECS,"OK")!=0)
		return 5;
	memset(RECS,0,sizeof(RECS));
	return 1;
}
//功能：esp发送消息
//参数：无
//返回值：0：发送成功；1：发送失败
char Esp_PUB(void)
{
	memset(RECS,0,sizeof(RECS));
	u3_printf("AT+MQTTPUB=0,\"%s\",\"\\{\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\}\",0,0\r\n",
	pubtopic,s_soil_value,soil_value,s_light_value,light_value,s_co2_value,co2_value,s_temp_value,DHT11_Temp,s_hum_value,DHT11_Hum);
	//while(RECS[0]);//等待ESP返回数据
	delay_ms(200);//延时等待数据接收完成 
	if(strcmp(RECS,"ERROR")==0)
		return 1;
	return 0;
}
char esp_pub_state(void)
{
		memset(RECS,0,sizeof(RECS));
	u3_printf("AT+MQTTPUB=0,\"%s\",\"\\{\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\}\",0,0\r\n",
	pubtopic,s_led,LED_state,s_hot,hot_state,s_cold,cold_state,s_fans,fans_state,s_steam,steam_state);
	//while(RECS[0]);//等待ESP返回数据
	delay_ms(200);//延时等待数据接收完成 
	if(strcmp(RECS,"ERROR")==0)
		return 1;
	return 0;
}
//void CommandAnalyse(void)
//{

//	if(strncmp(RECS,"+MQTTSUBRECV:",13)==0)
//	{
//			uint8_t i=0;
//		while(RECS[i++] != '\0')             
//		{
//			if(strncmp((RECS+i),s_led,sizeof(*s_led))==0)
//			{
//				while(RECS[i++] != ':');       
//				if(RECS[i]=='1') 
//					 LED0=0;
//				else 
//	      LED0=1;
//				 	
//				memset(RECS,0,sizeof(RECS));
//			}
//	
//				if(strncmp((RECS+i),s_hot,sizeof(*s_hot))==0)
//			{
//				while(RECS[i++] != ':');
//				if(RECS[i]=='1') 
//					 HOT=0;
//				else 
//	      HOT=1;
//			memset(RECS,0,sizeof(RECS));
//			}
//					if(strncmp((RECS+i),s_cold,sizeof(*s_cold))==0)
//			{
//				while(RECS[i++] != ':');
//				if(RECS[i]=='1') 
//					 COLD=0;
//				else 
//	      COLD=1;
//			memset(RECS,0,sizeof(RECS));
//			}
//								if(strncmp((RECS+i),s_fans,sizeof(*s_fans))==0)
//			{
//				while(RECS[i++] != ':');
//				if(RECS[i]=='1') 
//					 FANS=0;
//				else 
//	      FANS=1;
//			memset(RECS,0,sizeof(RECS));
//			}
//											if(strncmp((RECS+i),s_steam,sizeof(*s_steam))==0)
//			{
//				while(RECS[i++] != ':');
//				if(RECS[i]=='1') 
//					 jsq=0;
//				else 
//	      jsq=1;
//			memset(RECS,0,sizeof(RECS));
//			}
////	
////	
////	
//		}
//		
//		
//		
//	}
//}

 void esp8266(void){
//	 	u3_printf("AT+RST\r\n");  //重启
//	delay_ms(2000);

	u3_printf("AT+CWMODE=3\r\n"); //Station模式
	delay_ms(500);


	

	u3_printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
	delay_ms(500);

	u3_printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
	delay_ms(500);


	u3_printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
	delay_ms(500);

	u3_printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
	delay_ms(500);
 
 }

void connect_try(void)
{
esp_Init();
}

void Analys_zig(void)
{
		  //分析执行单元状态

    	if(strncmp(RECS1,"s:",2)==0)
	{
			uint8_t i=0;
		while(RECS1[i++] != '\0')             
		{
			if(strncmp((RECS1+i),s_led,sizeof(*s_led))==0)
			{
					while(RECS1[i++] != '=');       
					if(RECS1[i]=='1')
						LED_state=1;
					else LED_state=0;
				i++;
			}
	
				if(strncmp((RECS1+i),s_hot,sizeof(*s_hot))==0)
			{
			
					while(RECS1[i++] != '=');       
					if(RECS1[i]=='1')
						hot_state=1;
					else LED_state=0;
				i++;
			}
			
					if(strncmp((RECS1+i),s_cold,sizeof(*s_cold))==0)
			{	
				while(RECS1[i++] != '=');       
					if(RECS1[i]=='1')
						cold_state=1;
					else cold_state=0;
				i++;
			}
			
					if(strncmp((RECS1+i),s_fans,sizeof(*s_fans))==0)
			{	
				while(RECS1[i++] != '=');       
					if(RECS1[i]=='1')
						fans_state=1;
					else fans_state=0;
				i++;
			}
			
			
					if(strncmp((RECS1+i),s_steam,sizeof(*s_steam))==0)
			{	
				while(RECS1[i++] != '=');       
					if(RECS1[i]=='1')
						steam_state=1;
					else steam_state=0;
				i++;
			}
			
		memset(RECS1,0,sizeof(RECS1));
		}
	}
   	//分析传感器数据
	    	if(strncmp(RECS1,"v:",2)==0)
	{
			uint8_t j=0;
		while(RECS1[j++] != '\0')             
		{
			delay_ms(1);
			if(strncmp((RECS1+j),s_soil_value,sizeof(*s_soil_value))==0)
			{
				while(RECS1[j++] != ':');
				if(RECS1[j+1]!=',')
					 soil_value=(RECS1[j]-'0')*10+(RECS1[j+1]-'0');
				if(RECS1[j+1]==',')
					 soil_value=(RECS1[j]-'0');
				delay_ms(1);
				j+=2;
			}
	
				if(strncmp((RECS1+j),s_temp_value,sizeof(*s_temp_value))==0)
			{
				while(RECS1[j++] != ':');       
					 DHT11_Temp=(RECS1[j]-'0')*10+(RECS1[j+1]-'0');
				delay_ms(1);
				j+=2;
			}
			
					if(strncmp((RECS1+j),s_hum_value,sizeof(*s_hum_value))==0)
			{	
				while(RECS1[j++] != ':');       
					 DHT11_Hum=(RECS1[j]-'0')*10+(RECS1[j+1]-'0');
				delay_ms(1);
				j+=2;
			}
			
			if(strncmp((RECS1+j),s_co2_value,sizeof(*s_co2_value))==0)
			{
				while(RECS1[j++] != ':');
				delay_ms(1);
					co2_value=(RECS1[j]-'0')*1000+(RECS1[j+1]-'0')*100+(RECS1[j+2]-'0')*10+(RECS1[j+3]-'0');
				j+=4;
			}
			
			if(strncmp((RECS1+j),s_light_value,sizeof(*s_light_value))==0)
			{
				while(RECS1[j++] != ':');
				delay_ms(1);
					light_value=(RECS1[j]-'0')*1000+(RECS1[j+1]-'0')*100+(RECS1[j+2]-'0')*10+(RECS1[j+3]-'0');
				j+=4;
			}
			
		}
	
	}
}



