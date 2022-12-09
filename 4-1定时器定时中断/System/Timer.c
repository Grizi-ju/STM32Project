#include "stm32f10x.h"

//extern uint16_t Num;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   //RCC内部时钟
	
	TIM_InternalClockConfig(TIM2);   //配置内部时钟
	
	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructor;		//时基单元
	Tim_TimeBaseInitStructor.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_TimeBaseInitStructor.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_TimeBaseInitStructor.TIM_Period = 10000 - 1;
	Tim_TimeBaseInitStructor.TIM_Prescaler = 7200 -1;
	Tim_TimeBaseInitStructor.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&Tim_TimeBaseInitStructor); 
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);   //清除中断标志位，从0开始

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);             //使能中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   	 //NVIC配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);       //开启定时器
}


//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
//	{
//		Num ++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//			
//}
