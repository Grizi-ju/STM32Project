#include "stm32f10x.h"   // Device header

void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   	//RCC内部时钟     TIM3  PA6
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  	//引脚输出
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);         
	
	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructor;				//时基单元
	Tim_TimeBaseInitStructor.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_TimeBaseInitStructor.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_TimeBaseInitStructor.TIM_Period = 65536 - 1;     			//ARR
	Tim_TimeBaseInitStructor.TIM_Prescaler = 72 -1;					//PSC
	Tim_TimeBaseInitStructor.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&Tim_TimeBaseInitStructor); 
	
	TIM_ICInitTypeDef TIM_ICInitStructure;							//输入
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1); 					//触发源选择
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);					//从模式Reset
	
	TIM_Cmd(TIM3,ENABLE);       //开启定时器
}

uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM3) + 1);
}
