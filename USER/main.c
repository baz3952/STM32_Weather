#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "esp8266.h"
#include "beep.h"
#include "malloc.h"
#include "weather.h"


int main(void)
{ 
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	BEEP_Init();
	Usart1_Init(115200);
	Usart3_Init(115200);
	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	ESP8266_Init();
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
	
//	BEEP = 1;
//	delay_ms(250);
//	BEEP = 0;//���ӳɹ�

	Get_Oneday_Weather();
	while(1)
	{
		
	}
}

 



