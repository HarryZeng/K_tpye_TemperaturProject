#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "adc.h"
#include "Temperature.h"

/************************************************
 ALIENTEK 战舰STM32F103开发板实验17
 ADC 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


 
 int main(void)
 {	 

	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化		 	
 	Adc_Init();		  		//ADC初始化
  LED0=0;
	
  //printf("Initial is ok");	 
	while(1)
	{
		//packet_data();
		LED0=!LED0;
		delay_ms(5);
		if(USART_RX_STA)
		{
			getSensorNo(USART_RX_BUF);
			USART_RX_STA = 0;
		}
		
	}
 }


