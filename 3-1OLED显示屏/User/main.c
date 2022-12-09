#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"


int main(void)
{
	OLED_Init();
	
	//OLED_ShowChar(1,1,'A');
	//OLED_ShowString(1,1,"HelloTT!");
	//OLED_ShowNum(2,1,5201314,7);
	//OLED_ShowString(3,1,"Love u always!");
	//OLED_ShowSignedNum(2,9,-33,2);
	//OLED_ShowHexNum(3,1,0xAA55,4);
	//OLED_ShowBinNum(4,1,0xAA55,16);
	
	OLED_ShowString(1,4,"** **");
	OLED_ShowString(2,3,"*******");
	OLED_ShowString(3,4,"*****");
	OLED_ShowString(4,6,"*");
	
	while (1)
	{
		
	}
}
