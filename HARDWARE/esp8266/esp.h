#ifndef __esp_H
#define __esp_H
#define WIFIMODE 1
#define JOINAP 2
#define MQTTINIT 3
#define MQTTCONN 4
#define MQTTSUB 5
int esp_Init(void);
char Esp_PUB(void);
void CommandAnalyse(void);
 void esp8266(void);
 char esp_pub_state(void);
 void Analys_zig(void);
 void analys_state(void);
int connect_try(void);
int analyse_str(char *str,char *substr);
#endif
