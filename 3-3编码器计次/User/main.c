#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

int8_t Num;

int main(void)
{
	OLED_Init();
	Encoder_Init();
	
	OLED_ShowString(1,1,"Num:");
	
	while (1)
	{
		Num += Encoder_Get();
		OLED_ShowSignedNum(1,5,Num,5);
	}
}
