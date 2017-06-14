/**
  ******************************************************************************
  * @file    TEMPERATURE.h 
  * @author  ZKRT
  * @version V1.0
  * @date    11-May-2017
  * @brief   
	*					 + (1) init
  ******************************************************************************
  * @attention
  *
  * ...
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H 
/* Includes ------------------------------------------------------------------*/
#include "sys.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

#define SensorNo    		T_M2   /*The number of sensor*/
#define SensorTIME			5	

#define RS485_PORT		GPIOB
#define RS485_PIN			GPIO_Pin_4
	
#define RS485_T   GPIO_SetBits(RS485_PORT,RS485_PIN)
#define RS485_R		GPIO_ResetBits(RS485_PORT,RS485_PIN)

	
typedef enum SENSOR_INDEX
{
	T_M1=0x01,				
	T_M2,
	T_M3,
	T_M4,

}SENSOR_ID;

typedef struct TEMPERATURE_DATA
{
	uint8_t 	type;  		/*Non-contact type or contact type*/
	uint8_t 	ID;				/*number of the sensor*/
	int16_t 	TOvalue;		/*TO value of temperature*/
	int16_t 	TAvalue;		/*TA value of temperature*/
	uint8_t 	freq;			/*frequence of sensor updata*/
}TemperatureSensor;

/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void packet_data(void);
void getSensorNo(uint8_t *__BUF);
float ADCget(void);
void TemperatureInit(void);
#endif /* __INFRARED_H */
/**
  * @}
  */ 

/**
  * @}
  */
	
/************************ (C) COPYRIGHT ZKRT *****END OF FILE****/

