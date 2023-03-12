#include "bsp_adc_dma.h" 

__IO uint16_t ADC_Value = 0;

// ADC接受DMA初始化配置函数
void ADC_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMA1_Channel1); // 复位
	DMA_StructInit(&DMA_InitStruct);	
	DMA_InitStruct.DMA_BufferSize = 1; // 整体的数据个数
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC; // 指定外设为发送源
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable; // 关闭两个存储区互相访问
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&ADC_Value; // 存储区基地址
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // 存储区每次接收两个字节
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable; // 存储区地址自增
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular; // 开启循环模式
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR; // 外设地址
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 外设每次传输两个字节
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 外设地址不自增
	DMA_InitStruct.DMA_Priority = DMA_Priority_High; // 设置通道转换优先级
	DMA_Init(DMA1_Channel1, &DMA_InitStruct); // 初始化
	
	ADC_DMACmd(ADC1,ENABLE); // 使能ADC的DMA循环转换模式
	
	DMA_Cmd(DMA1_Channel1, ENABLE); //DMA 使能	
	ADC_DMACmd(ADC1, ENABLE); // ADC DMA 使能	
	ADC_GetConversionValue(ADC1); // 开始 ADC1 转换
}
