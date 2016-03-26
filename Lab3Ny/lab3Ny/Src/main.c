/*============================================================================
Name:          main.c
Author:        Lasse Karagiannis
Compile with:  Atolic Studio Version: 5.4.0 Build id: 20151109-1237
Date:          2016-03-07
Description:   Lab3 The program lights up all segments and LEDs,
 	 	 	 	on the TM1638 button read and segment display evalutaion
 	 	 	   card, from Titanmec.
======================================================================================*/




#include "stm32f4xx_hal.h"

#define STB(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, x)			//A3
#define CLK(x)		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, x)			//A4
#define DIO(x)		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, x)			//A5
#define rDIO		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)				//A5
#define LD2(x)		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, x); 	//LD2
#define HIGH		GPIO_PIN_SET
#define LOW			GPIO_PIN_RESET
#define CDELAY		udelay(1);

#define DATA		0x40
#define TESTMODE	0x08
#define FIXED		0x04
#define READ		0x02

#define DISPLAY		0x80	//+ intensity
#define	ON			0x08

#define ADDRESS		0xc0	//+ address


void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void sendbyte(uint8_t data);
void udelay(volatile unsigned int delay);

void sendInstruction(uint8_t data);
void sendInstructionRead();
void sendStartAdress(uint8_t data);
void sendMultipleData(uint8_t data, int count);
void clearSegmentsAndLEDs(void);
void writeIntValueToSegments(uint32_t value);
void LightUpAllLEDs(void);
uint8_t decodeHexToSevenSegment(uint8_t digit);
void LigtUpEveryThing(void);


int main(void)
{

	uint32_t uReceivedData;

	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	HAL_SuspendTick();

	STB(HIGH);
	DIO(HIGH);
	CLK(HIGH);
	CDELAY;

	clearSegmentsAndLEDs();

	//writeIntValueToSegments(0xFFFFFFFF);
	//LightUpAllLEDs();
	LigtUpEveryThing();

//Att g�ra l�sa in och j�mf�ra med k�nd str�ng och anv�nda segmenten och leddarna f�r
	//felutskrifter
/**********************************/


	while (1)
	{


		udelay(5000);
	}

}
void LigtUpEveryThing(void){
	sendInstruction(0x8F); //Lights up
	sendInstruction(0x40); //Command, write to chip, chip autoincrements
	sendStartAdress(0xC0);
	sendMultipleData(0xFF,16);

}

void clearSegmentsAndLEDs(void)
{
	sendInstruction(0x8F); //Lights up
	sendInstruction(0x40); //Command, write to chip, chip autoincrements
	sendStartAdress(0xC0);//Send start adress

		// Sendinging (data,count)
	sendMultipleData(0x00, 16);

}
void LightUpAllLEDs(void)
{
	int i;
	uint8_t  adress = 0xC1;
	sendInstruction(0x8F); //Lights up
	sendInstruction(0x40); //Command, write to chip, chip autoincrements
	sendStartAdress(adress);//Send start adress
	for(i = 0; i < 8; i++)
	{
		sendInstruction(DATA|FIXED);    //Command, write to chip, chip no autoincrements
		sendStartAdress(adress +2*i);
		sendMultipleData(0xFF, 1); // One byte
	}

}

void writeIntValueToSegments(uint32_t value)
{
	uint8_t adress = 0xC0;
	uint8_t extractedNibblesInByteFormat[8];
	uint32_t mask = 0x0F;
	uint32_t extractedNibbleAs32bit;
	uint8_t nibble;
	uint8_t i;
	for(i = 0; i < 8; i++){
		extractedNibbleAs32bit = mask & value;
		extractedNibbleAs32bit = extractedNibbleAs32bit >> 4*i;
		nibble = (uint8_t)extractedNibbleAs32bit;
		nibble = decodeHexToSevenSegment(nibble);
		extractedNibblesInByteFormat[i] = nibble;
		mask = mask << 4;
	}
	for(i = 0; i < 8; i++){
		sendInstruction(DATA|FIXED);    //Command, write to chip, chip no autoincrements
		sendStartAdress(adress +2*i);
		sendMultipleData(extractedNibblesInByteFormat[7-i], 1); // One byte
		}


}


void udelay(volatile unsigned int delay)
{
	delay*=11.206;
	for (;delay!=0;delay--);
}

void sendbyte(uint8_t data)
{
	uint8_t i;
  //i = i << 1
	for(i=0x1;i!=0;i<<=1)
	{
		DIO(data & i);
		CLK(LOW);
		CDELAY;
		CLK(HIGH);
		CDELAY;
	}
}




void sendValueToSegments(uint8_t value)
{

	//Decoding low nibble to segment display
	 uint8_t lowMask = 0x0F;
	 uint8_t lowNibble;
	 lowNibble= value & lowMask;
	 lowNibble = decodeHexToSevenSegment(lowNibble);

	//Decoding high nibble to segment display
	 uint8_t highMask = 0xF0;
	 uint8_t highNibble;
	 highNibble= value & highMask;
	 highNibble = decodeHexToSevenSegment(highNibble);



	//Starting sending real data to the 2 right most segment displays
	//Command, write to chip, chip no autoincrements
	sendInstruction(DATA|FIXED);

	//Send start adress
	sendStartAdress(0xCC);
	highNibble = 4 >> highNibble;
	sendMultipleData(highNibble, 1);

	//Command, write to chip, chip no autoincrements
	sendInstruction(DATA|FIXED);
	sendStartAdress(0xCE);//Send start adress
	sendMultipleData(lowNibble, 1);


}
uint8_t decodeHexToSevenSegment(uint8_t digit){

	switch(digit){

	case 0: return 0x3F;
	case 1: return 0x06;
	case 2: return 0x5B;
	case 3: return 0x4F;
	case 4: return 0x66;
	case 5: return 0x6D;
	case 6: return 0x7D;
	case 7: return 0x07;
	case 8: return 0x7F;
	case 9: return 0x6F;
	case 0x0A: return 0xB7;
	case 0x0B: return 0xFF;
	case 0x0C: return 0x39;
	case 0x0D: return 0xDE;
	case 0x0E: return 0x79;
	case 0x0F: return 0x71;
	default: return 0x00;


	}
}

void sendInstruction(uint8_t data)
{
	STB(LOW);
	CDELAY;
	sendbyte(data);
	CDELAY;
	STB(HIGH);
	CDELAY;
}


void sendStartAdress(uint8_t data)
{
	STB(LOW);
	CDELAY;
	sendbyte(data);
	CDELAY;
}

void sendMultipleData(uint8_t data, int count)
{
	int i;
	for(i = 0; i < count; i++)
			sendbyte(data);

	CDELAY;
	STB(HIGH);
	CDELAY;
}



/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* USART1 init function */
void MX_USART1_UART_Init(void)
{

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PA2   ------> USART2_TX
     PA3   ------> USART2_RX
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOC_CLK_ENABLE();
  __GPIOH_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 USART_RX_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_2|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/