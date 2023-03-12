 #include "adc.h"
 #include "delay.h"
 
uint16_t soil_value=0;
uint16_t light_value=0;
uint16_t co2_value=0;
//�ڴ��д洢ת�����������
vu16 ADC_ConvertedValue[Sample_Num][Channel_Num];
 
//DMA���ã�ADC1->CR --> ADC_ConvertedValue
void ADC_DMA_Config(void)
{
	 DMA_InitTypeDef DMA_InitStructure;
				   
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	 DMA_DeInit(DMA1_Channel1);												//��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	 DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;		//DMA����ADC����ַ
	 DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;		//DMA�ڴ����ַ
	 DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	 DMA_InitStructure.DMA_BufferSize = Sample_Num*Channel_Num;				//DMAͨ����DMA����Ĵ�С
	 DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//�����ַ����
	 DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				//�ڴ��ַ����
	 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//DMAͨ����DMA����Ĵ�С
	 DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			//DMAͨ����DMA����Ĵ�С
	 DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//������ѭ������ģʽ
	 DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMAͨ�� xӵ�и����ȼ�
	 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;			//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	 DMA_Init(DMA1_Channel1, &DMA_InitStructure);			//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
	 DMA_Cmd(DMA1_Channel1,ENABLE);
}
 
 
void ADC1_Config(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 ADC_InitTypeDef ADC_InitStructure;
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	   
	//Ĭ�Ͽ���     PC0 -- ͨ��10��PC1 -- ͨ��11��PC2 -- ͨ��12��PC3 -- ͨ��13
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;		
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			//ģ����������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 ADC_DMA_Config();
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	 RCC_ADCCLKConfig(RCC_PCLK2_Div6); 		//����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
	// ADC_DeInit(ADC1);
	 ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						//ADC1��ADC2�����ڶ���ģʽ
	 ADC_InitStructure.ADC_ScanConvMode = ENABLE;							//��ͨ��
	 ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						//����ת��
	 ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�������ת��
	 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//ת������Ҷ���
	 ADC_InitStructure.ADC_NbrOfChannel = Channel_Num;						//ͨ����Ŀ
	 ADC_Init(ADC1, &ADC_InitStructure); 
 
	   
	//ͨ����ת������ת��ʱ��
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_55Cycles5);
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_55Cycles5);
 
	   
	 ADC_DMACmd(ADC1, ENABLE);	   
	 ADC_Cmd(ADC1, ENABLE);
	 
	 ADC_ResetCalibration(ADC1);					//ʹ�ܸ�λУ׼
	 while(ADC_GetResetCalibrationStatus(ADC1));  	//�ȴ���λУ׼����
	 ADC_StartCalibration(ADC1);					//��ʼADУ׼
	 while(ADC_GetCalibrationStatus(ADC1));			//�ȴ�У׼����
	 
	 ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ADC�����ת����������
}
 
 
uint16_t get_adc_value(uint16_t Channel)
{
	uint8_t i;
	uint32_t sum = 0;
	for(i=0; i<Sample_Num; i++)
	{
		sum+=ADC_ConvertedValue[i][Channel];		//ȡƽ��ֵ
	}
	return (sum/Sample_Num);
}