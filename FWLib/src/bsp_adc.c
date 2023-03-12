#include "bsp_adc.h" 
#include "bsp_systick.h"

// ADC1初始化函数
void ADC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; // 定义 GPIO 初始化结构体变量
	ADC_InitTypeDef ADC_InitStruct; // 定义 ADC初始化结构体变量
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE); // 使能 GPIOA 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); // 使能 ADC1 时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN; // 模拟输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;	// ADC通道引脚
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // 上拉
	GPIO_Init(GPIOA, &GPIO_InitStruct); // 初始化
	
	ADC_DeInit(ADC1);  // 复位 ADC
	ADC_StructInit(&ADC_InitStruct); // 使用默认值填充 ADC_InitStruct成员
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; // 连续转换模式
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; // 数据对齐
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // 禁止触发检测，使用软件触发
	ADC_InitStruct.ADC_ScanDirection = ADC_ScanDirection_Upward; // 启动向上扫描模式 (from CHSEL0 to CHSEL17)
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b; // 12 位模式
	ADC_Init(ADC1,&ADC_InitStruct); // ADC 初始化
	
	ADC_ChannelConfig(ADC1,ADC_Channel_0,ADC_SampleTime_239_5Cycles); // 配置ADC注入通道0及周期采样时间
	
	ADC_GetCalibrationFactor(ADC1);  // 校准 ADC
	ADC_Cmd(ADC1,ENABLE); // ADC 使能 	
	ADC_StartOfConversion(ADC1); // 开始 ADC1 转换
}


