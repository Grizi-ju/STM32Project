#include "stm32f10x.h"   // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   //RCC内部时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //引脚输出
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);         
	
	TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStructor;		//时基单元
	Tim_TimeBaseInitStructor.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_TimeBaseInitStructor.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_TimeBaseInitStructor.TIM_Period = 20000 - 1;     	//ARR
	Tim_TimeBaseInitStructor.TIM_Prescaler = 72 -1;		//PSC
	Tim_TimeBaseInitStructor.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&Tim_TimeBaseInitStructor); 
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;          		//CCR
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);    			//通道2
	
	TIM_Cmd(TIM2,ENABLE);       //开启定时器

}

void PWM_SetCompare2(uint16_t compare)
{
	TIM_SetCompare2(TIM2,compare);
}