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

uint8_t transfermode;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void sendbyte(uint8_t data);
void udelay(volatile unsigned int delay);

void sendInstruction(uint8_t data);
void sendData(uint8_t data, int count);
uint8_t readByte();

int main(void)
{
	uint8_t receivedData;

	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	HAL_SuspendTick();

	STB(HIGH);
	DIO(HIGH);
	CLK(HIGH);
	CDELAY;

/**********************************/
	STB(LOW); //Command 1
	CDELAY;
	sendInstruction(0x8F); //Lights up

	CDELAY;
	STB(HIGH);
	CDELAY;

/**********************************/
/***************************************/
	STB(LOW);
	CDELAY;
	sendInstruction(0x40); //Command, write to chip, chip autoincrements

	CDELAY;
	STB(HIGH);
	CDELAY;
/***************************************/
	//Sending Adress mode setting comand
	STB(LOW);
	CDELAY;
	sendInstruction(0xC0);//Send start adress

	CDELAY;
	//STB(HIGH); //Keep strobe low
	CDELAY;
/***********************************/
	STB(LOW);
	CDELAY;
	// Sendinging (data,count)
	sendData(0xFF, 2);
	sendData(0xFF, 14);

	CDELAY;
	STB(HIGH);
	CDELAY;
/**********************************/

	while (1)
	{


		udelay(50000);
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

	for(i=0x1;i!=0;i<<=1)
	{
		DIO(data & i);
		CLK(LOW);
		CDELAY;
		CLK(HIGH);
		CDELAY;
	}
}
uint8_t readByte()
{
	int i;

	uint8_t received = 0;
	uint32_t input;


	for(i = 0;i < 8; i++)
	{
		CLK(LOW);
		CDELAY;
		CLK(HIGH);
		input = rDIO;
		if(input == 1){
			received = received | (0x01 << i); //setting the bit at position i
		}
		CDELAY;
	}
	return received;
}

void sendInstruction(uint8_t data)
{
	sendbyte(data);
}
void sendData(uint8_t data, int count)
{
	int i;
	for(i = 0; i < count; i++)
			sendbyte(data);
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
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
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

	/*Configure GPIO pin : PC0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : PC1 */
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
	GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
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