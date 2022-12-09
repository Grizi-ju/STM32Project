#include "stm32f10x.h"

uint16_t CountSensor_count;

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //开启AFIO时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;			//GPIO引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);  //AFIO外部中断引脚配置
	
	EXTI_InitTypeDef EXTI_InitStructure;			//外部中断配置  14线路  下降沿触发
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;    
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //NVIC配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//外部中断信号从GPIO到AFIO,到EXTI,再到NVIC,最终通向CPU
	
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_count ++;
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		CountSensor_count ++;
		EXTI_ClearFlag(EXTI_Line14);
	}
}
