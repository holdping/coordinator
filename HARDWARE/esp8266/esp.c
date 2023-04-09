#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delay.h"
#include "esp.h"
#include "usart3.h"
#include "bsp_adc.h"

extern u8 Connect_flag;
extern u16 co2_value;
extern u8 soil_value;
extern u16 light_value;
extern u8 DHT11_Temp,DHT11_Hum;
extern  u8 systemmode;
u8 Err=1;
 u8 LED_state=0;
 u8 fans_state=0;
 u8 hot_state=0;
 u8 cold_state=0;
 u8 steam_state=0;
 u8 temp_min=25;
 u8 temp_max=30;
 extern char check[200];
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
const char* s_temp_min="temp_min";
const char* s_temp_max="temp_max";
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
//	memset(RECS,0,sizeof(RECS));
//	u1_printf("AT+RST\r\n");  //重启
//	delay_ms(1000);
	
//	memset(RECS,0,sizeof(RECS));
//	u3_printf("ATE0\r\n");    //关闭回显
//	delay_ms(10);
//	if(strcmp(RECS,"OK"))
//		return 1;
	u1_printf("AT+MQTTCLEAN=0"); //连接服务器
	delay_ms(1000);
	u1_printf("AT+CWMODE=1\r\n"); //Station模式
	delay_ms(1000);
//	if(strstr(check,"OK")==NULL)
//		return 1;
	
	memset(RECS,0,sizeof(RECS));
		memset(check,0,sizeof(check));
	u1_printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
	delay_ms(1000);
//	if(strstr(check,"OK")==NULL)
//		return 2;
	
	memset(RECS,0,sizeof(RECS));
		memset(check,0,sizeof(check));
	u1_printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
	delay_ms(1000);
	delay_ms(1000);
//	if(strstr(check,"OK")==NULL)
//		return 3;
	
	memset(RECS,0,sizeof(RECS));
		memset(check,0,sizeof(check));
	u1_printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
	delay_ms(1000);
	delay_ms(1000);
//	if(strstr(check,"OK")==NULL)
//		return 4;
	
	 	memset(RECS,0,sizeof(RECS));
		memset(check,0,sizeof(check));
	u1_printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
	delay_ms(1000);
	delay_ms(1000);
//	if(strstr(check,"OK")==NULL)
//		return 5;
	memset(RECS,0,sizeof(RECS));
		memset(check,0,sizeof(check));
	return 0;
}
//功能：esp发送消息
//参数：无
//返回值：0：发送成功；1：发送失败
char Esp_PUB(void)
{
	memset(RECS,0,sizeof(RECS));
	u1_printf("AT+MQTTPUB=0,\"%s\",\"\\{\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\}\",0,0\r\n",
	pubtopic,s_soil_value,soil_value,s_light_value,light_value,s_co2_value,co2_value,s_temp_value,DHT11_Temp,s_hum_value,DHT11_Hum,s_temp_min,temp_min,s_temp_max,temp_max);
	//while(RECS[0]);//等待ESP返回数据
	delay_ms(200);//延时等待数据接收完成 
	if(strcmp(RECS,"ERROR")==0)
		return 1;
	return 0;
}
char esp_pub_state(void)
{
		memset(RECS,0,sizeof(RECS));
	u1_printf("AT+MQTTPUB=0,\"%s\",\"\\{\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"%s\\\"\:%d\\,\\\"systemmode\\\"\:%d\}\",0,0\r\n",
	pubtopic,s_led,LED_state,s_hot,hot_state,s_cold,cold_state,s_fans,fans_state,s_steam,steam_state,systemmode);
	//while(RECS[0]);//等待ESP返回数据
	delay_ms(200);//延时等待数据接收完成 
	if(strcmp(RECS,"ERROR")==0)
		return 1;
	return 0;
}
void CommandAnalyse(void)
{

	if(strncmp(RECS,"+MQTTSUBRECV:",13)==0)
	{
		if(strstr(RECS,s_led))
		LED_state=analyse_str(RECS,"\"LED_state\":");
		if(strstr(RECS,s_hot))
    hot_state=analyse_str(RECS,"\"hot_state\":");
		if(strstr(RECS,s_cold))
		cold_state=analyse_str(RECS,"\"cold_state\":");
		if(strstr(RECS,s_fans))
			fans_state=analyse_str(RECS,"\"fans_state\":");
		if(strstr(RECS,s_steam))
		steam_state=analyse_str(RECS,"\"steam_state\":");
		if(strstr(RECS,"systemmode"))
		systemmode=analyse_str(RECS,"\"systemmode\":");	
		 if(strstr(RECS,"temp_min"))
		temp_min=analyse_str(RECS,"\"temp_min\":");	
		 if(strstr(RECS,"temp_max"))
		temp_max=analyse_str(RECS,"\"temp_max\":");
		
		
	}
}

 void esp8266(void){
//	 	u3_printf("AT+RST\r\n");  //重启
//	delay_ms(2000);

	u1_printf("AT+CWMODE=1\r\n"); //Station模式
	delay_ms(1000);


	

	u1_printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
	delay_ms(1000);
	 delay_ms(1000);

	u1_printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
	delay_ms(1000);
	 delay_ms(1000);


	u1_printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
	delay_ms(1000);
	 delay_ms(1000);

	u1_printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
	delay_ms(1000);
	delay_ms(1000);
 
 }

int connect_try(void)
{
	memset(RECS,0,sizeof(RECS));
	u1_printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
	delay_ms(1000);
	if(strcmp(RECS,"OK")!=0)
		return 3;
	
	memset(RECS,0,sizeof(RECS));
	u1_printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
	delay_ms(500);
 	memset(RECS,0,sizeof(RECS));
	
	u1_printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
	delay_ms(500);
	if(strcmp(RECS,"OK")!=0)
			return 1;
	memset(RECS,0,sizeof(RECS));
	


}

void Analys_zig(void)
{
 	//分析传感器数据
	    	if(strncmp(RECS1,"v:",2)==0)
	{
			uint8_t j=0;
		while(RECS1[j++] != '\0')             
		{
			if(strncmp((RECS1+j),s_soil_value,sizeof(*s_soil_value))==0)
			{
				while(RECS1[j++] != ':');
				if(RECS1[j+1]!=',')
					 soil_value=(RECS1[j]-'0')*10+(RECS1[j+1]-'0');
				if(RECS1[j+1]==',')
					 soil_value=(RECS1[j]-'0');
				j+=2;
			}
	
				if(strncmp((RECS1+j),s_temp_value,sizeof(*s_temp_value))==0)
			{
				while(RECS1[j++] != ':');       
					 DHT11_Temp=(RECS1[j]-'0')*10+(RECS1[j+1]-'0');
				j+=2;
			}
			
					if(strncmp((RECS1+j),s_hum_value,sizeof(*s_hum_value))==0)
			{	
				while(RECS1[j++] != ':');       
					 DHT11_Hum=(RECS1[j]-'0')*10+(RECS1[j+1]-'0');
				j+=2;
			}
			
			if(strncmp((RECS1+j),s_co2_value,sizeof(*s_co2_value))==0)
			{
				while(RECS1[j++] != ':');
					co2_value=(RECS1[j]-'0')*1000+(RECS1[j+1]-'0')*100+(RECS1[j+2]-'0')*10+(RECS1[j+3]-'0');
				j+=4;
			}
			
			if(strncmp((RECS1+j),s_light_value,sizeof(*s_light_value))==0)
			{
				while(RECS1[j++] != ':');
					light_value=(RECS1[j]-'0')*1000+(RECS1[j+1]-'0')*100+(RECS1[j+2]-'0')*10+(RECS1[j+3]-'0');
				j+=4;
			}
			
		}
	
	}
}
void analys_state(void)
{
		  //分析执行单元状态

    	if(strncmp(RECS1,"s:",2)==0)
	{
			uint8_t i=0;
		while(RECS1[i++] != '\0')             
		{
			if(strncmp((RECS1+i),s_led,sizeof(*s_led))==0)
			{
				while(RECS1[i++] != ':');       
					if(RECS1[i]=='1')
						LED_state=1;
					else LED_state=0;
				i++;
			}
	
				if(strncmp((RECS1+i),s_hot,sizeof(*s_hot))==0)
			{
			
				while(RECS1[i++] != ':');       
					if(RECS1[i]=='1')
						hot_state=1;
					else hot_state=0;
				i++;
			}
			
					if(strncmp((RECS1+i),s_cold,sizeof(*s_cold))==0)
			{	
				while(RECS1[i++] != ':');       
					if(RECS1[i]=='1')
						cold_state=1;
					else cold_state=0;
				i++;
			}
			
					if(strncmp((RECS1+i),s_fans,sizeof(*s_fans))==0)
			{	
				while(RECS1[i++] != ':');       
					if(RECS1[i]=='1')
						fans_state=1;
					else fans_state=0;
				i++;
			}
			
			
					if(strncmp((RECS1+i),s_steam,sizeof(*s_steam))==0)
			{	
				while(RECS1[i++] != ':');       
					if(RECS1[i]=='1')
						steam_state=1;
					else steam_state=0;
				i++;
			}
			
			
			
		}
		
//	memset(RECS1,0,sizeof(RECS));
	}
  
}

int analyse_str(char *str,char *substr)
{

	
	    char *pos=strstr(str,substr);
		if(pos != NULL)
		{
	
		pos += strlen(substr);
		if(*pos !='\0')
		{
         if((*(pos+1)>='0')&&(*(pos+1)<='9'))
				 return (((*pos)-'0')*10+(*(pos+1)-'0'));
					else 
					return (*pos)-'0';	
		} 
	}
}

//int connet_first(void)
//{
//			TIM_Cmd(TIM2,DISABLE);  	
//			memset(check,0,sizeof(check)); 
//				Err=wifi_sendcmd(Err);	
//			if(Err){   			     //Èç¹ûWiFiÁ¬½ÓÔÆ·þÎñÆ÷º¯Êý·µ»Ø0£¬±íÊ¾ÕýÈ·£¬½øÈëif
//				Connect_flag = 1;                            //Connect_flagÖÃ1£¬±íÊ¾Á¬½Ó³É¹¦	                       
//				memset(check,0,sizeof(check));      //Çå¿ÕWiFi½ÓÊÕ»º³åÇø 
//			TIM_Cmd(TIM2,ENABLE);   
//			}else u1_printf("连接错误代码：%d\r\n",Err);
//			return Err;


//}
//void retryconn(void)
//{

//	   switch(Err)
//		 {
//			 case 1:
//					u1_printf("AT+CWMODE=1\r\n"); //Station模式
//			 delay_ms(100);
//			 	if(strstr(check,"OK")!=NULL)
//					Err=2;
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));				
//				  break;
//			 case 2:
//			 		u1_printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
//			 delay_ms(100);
//			 	if(strstr(check,"OK")!=NULL)
//				Err=3;
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));		
//				  break;
//			 case 3:
//				  u1_printf("AT+MQTTCONN?\r\n");
//				delay_ms(100);
//			  if(strstr(check,"gz-3-mqtt.iot-api.com")!=NULL)
//				Err=4;
//				else 
//				u1_printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//				 break;
//			 case 4:
//				  u1_printf("AT+MQTTCONN?\r\n");
//			 delay_ms(100);
//			  if((strstr(check,"gz-3-mqtt.iot-api.com")!=NULL))
//				Err=5;
//				else  u1_printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//				 break;
//			 case 5:
//				   u1_printf("AT+MQTTCONN?\r\n");
//			   if(strstr(check,"gz-3-mqtt.iot-api.com"))
//				Err=0;
//				 else	 u1_printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//				 break;

//		 }
//	 
//}
// int wifi_sendcmd(int cmd)
// {
//      	   switch(cmd)
//		 {
//			 case WIFIMODE:
//					u1_printf("AT+CWMODE=1\r\n"); //Station模式
//			 delay_ms(100);
//			 	if(strstr(check,"OK")==NULL)
//				return 1;
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));	
//				return 2;				
//				  break;
//			 case JOINAP:
//			 		u1_printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI,WIFIASSWORD); //连接热点
//			 delay_ms(100);
//			 	if(strstr(check,"OK")==NULL)
//				return 2;
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//				 return 3;				
//				  break;
//			 case MQTTINIT:
//				  u1_printf("AT+MQTTCONN?\r\n");
//				delay_ms(100);
//			  if(strstr(check,"gz-3-mqtt.iot-api.com")!=NULL)
//         {
//					u1_printf("mqtt connected \r\n");
//					memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS)); 
//				 }
//				else 
//				u1_printf("AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"\r\n",ClintID,username,passwd);//用户信息配置
//				if(strstr(check,"OK")==NULL)
//						{
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//						return 3;
//					}
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//				return 4;
//				 break;
//			 case MQTTCONN:
//				  u1_printf("AT+MQTTCONN?\r\n");
//			 delay_ms(100);
//			  if((strstr(check,"gz-3-mqtt.iot-api.com")!=NULL))
//				{
//					u1_printf("mqttconnected \r\n");
//					memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS)); }
//				else  u1_printf("AT+MQTTCONN=0,\"%s\",1883,1\r\n",Url); //连接服务器
//					if(strstr(check,"OK")==NULL)
//					{
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//						return 4;
//					}
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//					return 5;
//				 break;
//			 case MQTTSUB:
//				   u1_printf("AT+MQTTCONN?\r\n");
//			   if(strstr(check,"gz-3-mqtt.iot-api.com"))
//						{
//					u1_printf("mqttsub \r\n");
//					memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS)); }
//				 else	 u1_printf("AT+MQTTSUB=0,\"%s\",1\r\n",subtopic); //订阅消息
//				if(strstr(check,"OK")==NULL)
//					{
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//						return 5;
//					}
//				memset(check,0,sizeof(check));
//				memset(RECS,0,sizeof(RECS));
//					return 0;
//				 break;

//		 }
// }
