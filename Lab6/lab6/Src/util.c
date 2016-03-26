/*
 * util.c
 *
 *  Created on: Mar 26, 2016
 *      Author: Lasse
 */
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#ifndef STB
#define STB(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, x)			//A3
#endif

#ifndef CLK
#define CLK(x)		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, x)			//A4
#endif

#ifndef DIO
#define DIO(x)		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, x)			//A5
#endif

#ifndef rDIO
#define rDIO		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)				//A5
#endif

#define LD2(x)		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, x); 	//LD2

#ifndef HIGH
#define HIGH		GPIO_PIN_SET
#endif

#ifndef LOW
#define LOW			GPIO_PIN_RESET
#endif

#ifndef CDELAY
#define CDELAY		udelay(1);
#endif

#define DATA		0x40
#define TESTMODE	0x08
#define FIXED		0x04
#define READ		0x02

#define DISPLAY		0x80	//+ intensity
#define	ON			0x08

#define ADDRESS		0xc0	//+ address


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
void sendInstructionRead(void)
{
	STB(LOW);
	CDELAY;
	sendbyte(0x42);
	CDELAY;

	//CDELAY;
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




void clearSegmentsAndLEDs(void){
	sendInstruction(0x8F); //Lights up
	sendInstruction(0x40); //Command, write to chip, chip autoincrements
	sendStartAdress(0xC0);//Send start adress

		// Sendinging (data,count)
	sendMultipleData(0x00, 16);

}

void writeHexValueToSegmentAtAdress(uint8_t value, uint8_t adress)
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
		 highNibble = highNibble >> 4 ;
		 highNibble = decodeHexToSevenSegment(highNibble);


		 sendInstruction(DATA|FIXED);    //Command, write to chip, chip no autoincrements
		 sendStartAdress(adress+2);
		 sendMultipleData(lowNibble, 1); // One byte


		 sendInstruction(DATA|FIXED); //No auto increment
		 sendStartAdress(adress);
		 sendMultipleData(highNibble, 1);


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

