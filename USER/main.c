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


 float ADCvalue;

#define DBGMCU_CR    (*((volatile unsigned long *)0xE0042004)) 
 
 int main(void)
 {	 
	 /*用于释放PB3，PB4,使其作为普通IO口*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//打开PA,PB,辅助时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//切换到SWJ调试,释放PA15,PB4
	DBGMCU_CR &= 0xFFFFFFDF;		//禁止异步跟踪,释放PB3
	 /**/
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化		 	
 	Adc_Init();		  		//ADC初始化
  LED0=1;
	TemperatureInit();

	while(1)
	{

		ADCvalue = ADCget();
//			RS485_T;
//			USART_SendData(USART1,0x85);
//			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
//			RS485_R;
		//delay_ms(SensorTIME);
		//LED0=!LED0;
		//packet_data();
		if(finishFlah==1)
		{
			finishFlah = 0;
			getSensorNo(USART_RX_BUF);
		}
	}
 }


