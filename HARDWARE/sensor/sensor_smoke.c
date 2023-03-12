#include "sensor_smoke.h"
#include "bsp_adc.h" 
#include "bsp_systick.h"
#include "bsp_adc_dma.h" 
#include <math.h>

#define CAL_PPM 20  // 校准环境中PPM值
#define RL			5		// RL阻值
static float R0; // 元件在洁净空气中的阻值

 // 传感器初始化
void MQ2_Init(void)
{
	ADC_Pin_Init();
	ADC_DMA_Init();
}
/****************************************
 * 1.651428	          200               *
 * 1.437143	          300               *
 * 1.257143	          400               *
 * 1.137143	          500               *
 * 1				          600               *
 * 0.928704	          700               *
 * 0.871296	          800               *
 * 0.816667	          900               *
 * 0.785714	          1000              *
 * 0.574393	          2000              *
 * 0.466047	          3000              *
 * 0.415581	          4000              *
 * 0.370478	          5000              *
 * 0.337031	          6000              *
 * 0.305119	          7000              *
 * 0.288169	          8000              *
 * 0.272727	          9000              *
 * 0.254795	          10000             *
 *                                      *
 * ppm = 613.9f * pow(RS/RL, -2.074f)   *
 ***************************************/

 // 传感器校准函数
void MQ2_PPM_Calibration(float RS)
{
	R0 = RS / pow(CAL_PPM / 613.9f, 1 / -2.074f);
}
 
 // MQ2传感器数据处理
float MQ2_GetPPM(void)
{
	float Vrl = 3.3f * ADC_GetConversionValue(ADC1) / 4095.f;
	float RS = (3.3f - Vrl) / Vrl * RL; 
	if(boot_time_ms < 3000) // 获取系统执行时间，3s前进行校准
	{
		MQ2_PPM_Calibration(RS);
	}
	float ppm = 613.9f * pow(RS/R0, -2.074f);
	return  ppm;
}
/*void mq2_smog(void){
	    u16 ad=0;
	ad = (ADC_Trans(ADC_Channel_8,20) * 99 )/ 4096.0;

}
       */