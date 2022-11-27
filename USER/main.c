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
	delay_init(168);		  //初始化延时函数
	LED_Init();		  	//初始化与LED连接的硬件接口
	BEEP_Init();
	Usart1_Init(115200);
	Usart3_Init(115200);
	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	ESP8266_Init();
	
	my_mem_init(SRAMIN);		//初始化内部内存池
	my_mem_init(SRAMEX);		//初始化外部内存池
	
//	BEEP = 1;
//	delay_ms(250);
//	BEEP = 0;//链接成功

	Get_Oneday_Weather();
	while(1)
	{
		
	}
}

 



