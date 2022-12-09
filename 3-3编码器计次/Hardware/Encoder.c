#include "stm32f10x.h"

int16_t Encoder_count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //开启AFIO时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;			//GPIO引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);  //AFIO外部中断引脚配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	EXTI_InitTypeDef EXTI_InitStructure;			//外部中断配置  14线路  下降沿触发
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;    
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //NVIC配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	//外部中断信号从GPIO到AFIO,到EXTI,再到NVIC,最终通向CPU
	
}

int16_t Encoder_Get(void)
{
	int8_t Temp;
	Temp = Encoder_count;
	Encoder_count = 0;
	return Temp;
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
		{
			Encoder_count --;
		}
		EXTI_ClearFlag(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
		{
			Encoder_count ++;
		}
		EXTI_ClearFlag(EXTI_Line1);
	}
}
