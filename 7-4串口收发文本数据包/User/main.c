#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "LED.h"
#include <string.h>


int main(void)
{
	OLED_Init();
	LED_Init();
	Serial_Init();
	
	OLED_ShowString(1,1,"TxPacket:");
	OLED_ShowString(1,1,"RxPacket:");
	
	
	while (1)
	{
		if(Serial_RxFlag == 1)
		{
			OLED_ShowString(4,1,"               ");
			OLED_ShowString(4,1,Serial_RxPacket);
			
			if(strcmp(Serial_RxPacket,"LED_ON") == 0)
			{
				LED1_ON();
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2,1,"               ");
				OLED_ShowString(2,1,"LED_ON_OK");
			}
			else if(strcmp(Serial_RxPacket,"LED_OFF") == 0)
			{
				LED1_OFF();
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2,1,"               ");
				OLED_ShowString(2,1,"LED_OFF_OK");
			}
			else
			{
				Serial_SendString("ERROR_CMD\r\n");
				OLED_ShowString(2,1,"               ");
				OLED_ShowString(2,1,"ERROR_CMD");
			}
			
			Serial_RxFlag = 0;
		}
	}
}
