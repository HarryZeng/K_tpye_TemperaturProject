#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "adc.h"
#include "Temperature.h"

/************************************************
 ALIENTEK ս��STM32F103������ʵ��17
 ADC ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 float ADCvalue;

#define DBGMCU_CR    (*((volatile unsigned long *)0xE0042004)) 
 
 int main(void)
 {	 
	 /*�����ͷ�PB3��PB4,ʹ����Ϊ��ͨIO��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//��PA,PB,����ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�л���SWJ����,�ͷ�PA15,PB4
	DBGMCU_CR &= 0xFFFFFFDF;		//��ֹ�첽����,�ͷ�PB3
	 /**/
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��		 	
 	Adc_Init();		  		//ADC��ʼ��
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


