/*
 * util.h
 *
 *  Created on: Mar 26, 2016
 *      Author: Lasse
 */

#ifndef UTIL_H_
#define UTIL_H_

#define CDELAY		udelay(1);
#define HIGH		GPIO_PIN_SET
#define LOW			GPIO_PIN_RESET
#define CLK(x)		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, x)
#define STB(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, x)			//A3
#define DIO(x)		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, x)			//A5
#define rDIO		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)

void udelay(volatile unsigned int delay);
void sendbyte(uint8_t data);
void udelay(volatile unsigned int delay);

void sendInstruction(uint8_t data);
void sendInstructionRead();
void sendStartAdress(uint8_t data);
void sendMultipleData(uint8_t data, int count);
uint8_t decodeHexToSevenSegment(uint8_t digit);
void clearSegmentsAndLEDs(void);
void writeHexValueToSegmentAtAdress(uint8_t value, uint8_t position);
void writeIntValueToSegments(uint32_t value);


#endif /* UTIL_H_ */
