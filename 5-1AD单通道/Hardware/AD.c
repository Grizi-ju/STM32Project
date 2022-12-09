#include "stm32f10x.h"

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);			//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;							//配置GPIO
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);	//选择输入通道
	
	ADC_InitTypeDef ADC_InitStructure;								//初始化ADC 单次转换、非扫描模式
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);				//ADC上电
	
	ADC_ResetCalibration(ADC1);			//复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);

}

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

