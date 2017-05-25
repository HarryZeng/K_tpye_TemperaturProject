/**
  ******************************************************************************
  * @file    TEMPERATURE.c 
  * @author  ZKRT
  * @version V1.0
  * @date    11-May-2017
  * @brief   K type thermocouple
	*					 + (1) init
	*                       
  ******************************************************************************
  * @attention
  *
  * ...
  *
	PACKAGE:
	Byte0: 0x5A package head
	Byte1: 0x5A package head
	Byte2: 0X45 type of package(0x45:temperature value)
	Byte3: 0x04 length
	Byte4: 0x00~0xFF 	MSB1
	Byte5: 0x00~0xFF 	LSB1       
	Byte6: 0x00~0xFF 	MSB2
	Byte7: 0x00~0xFF 	LSB2
	Byte8: 0x00~0xFF 	CHECK
	Byte9: 0x01~0x15 	ID ,default is 0x14
	
	Calculate:
	temperature = MSB <<8 | LSB8
	
	Example:
		5A- 5A- 45- 04- 0C- 78- 0D- 19- A7- 14 
		
		TO =  0X0C78->3192/100 = 31.92 ¡æ
		TA =  0X0D19->3353/100 = 33.53 ¡æ
		
	COMMAND:
		*****
		
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
//#include "radar.h"
#include "Temperature.h"
#include "adc.h"
#include "led.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  parse infra-red data
  * @param  
  * @note   
  * @retval succeed 1£¬failed 0
  */

uint8_t __data[10];
	
void SendPackage(uint8_t *package);
extern float ADCvalue;

void TemperatureInit(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
  
  /* USART1 Pins configuration ************************************************/
  /* Connect pin to Periph */
  /* Configure pins as AF pushpull */
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
  GPIO_InitStructure.GPIO_Pin = RS485_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(RS485_PORT, &GPIO_InitStructure); 
	
	RS485_R;
}


float ADCget(void)
{
	
  u16 adcx;
	float Temp;
	float CaliValue;
	
	CaliValue=1.3;
	
	adcx=Get_Adc_Average(ADC_Channel_1,10);
	
//	Temp1=(float)adcx*(3.3/(4096));
//	Temp=((Temp1-0.6)/0.0025)+CaliValue;
//	Temp = Temp*100;
	
	Temp = ((((float)adcx*(3.3/(4096))-0.6)/0.0025) + CaliValue)*100;
	
	return 	Temp;
}
	


void packet_data(void)
{
		uint8_t sum;
		uint8_t i=0,k=0;
	
		__data[i++]= 0x5a;							/*package head*/
		__data[i++]= 0x5a;
		__data[i++]= 0x45;							/*data type*/
		__data[i++]= 0x04;							/*length*/
		__data[i++]= (int)ADCvalue>>8;	/*TO*/
		__data[i++]= (int)ADCvalue%100;
		__data[i++]= 0x00;							/*TA*/
		__data[i++]= 0x00;
		
		for(sum=0,k=0;k<(__data[3]+4);k++)//_/*accumulation*/
			sum+=__data[k];
	
		__data[i++]= sum;
		__data[i++]= SensorNo;				/*ID*/
		
		for(k=0;k<sizeof(__data)+1;k++)
		{
			RS485_T;
			LED0=!LED0;
			USART_SendData(USART1,__data[k]);
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
			RS485_R;
		}
		
}

int16_t counter=0;

void getSensorNo(uint8_t *__BUF)
{
		uint8_t sumCheck;
		uint8_t i;
		uint8_t ID;
	
		for(sumCheck=0,i=0;i<sizeof(__BUF)-1;i++)//atmosphereBuf[3]=4
			sumCheck+=__BUF[i];

		if(sumCheck == __BUF[i])
		{
			ID = __BUF[2];
			if(ID == SensorNo)
			{
					packet_data();
					counter++;
			}
		}
}

/**
*@
*/
