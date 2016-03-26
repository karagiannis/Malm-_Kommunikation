/**
  ******************************************************************************
  * @file    USART/Synchronous/platform_config.h 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    24-April-2012
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
#if !defined (USE_STM32100B_EVAL) && !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL) &&  !defined (USE_STM32100E_EVAL)
 //#define USE_STM32100B_EVAL
 //#define USE_STM3210B_EVAL
 //#define USE_STM32100E_EVAL 
 #define USE_STM3210E_EVAL 
#endif

/* Define the STM32F10x hardware depending on the used evaluation board */
#if defined(USE_STM3210B_EVAL) || defined (USE_STM32100B_EVAL)

  #define USARTy                   USART1
  #define USARTy_GPIO              GPIOA
  #define USARTy_CLK               RCC_APB2Periph_USART1
  #define USARTy_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USARTy_RxPin             GPIO_Pin_10
  #define USARTy_TxPin             GPIO_Pin_9
  #define USARTy_ClkPin            GPIO_Pin_8
  
  #define SPIy                     SPI1
  #define SPIy_GPIO                GPIOA
  #define SPIy_CLK                 RCC_APB2Periph_SPI1
  #define SPIy_GPIO_CLK            RCC_APB2Periph_GPIOA
  #define SPIy_SCKPin              GPIO_Pin_5
  #define SPIy_MISOPin             GPIO_Pin_6
  #define SPIy_MOSIPin             GPIO_Pin_7

#elif defined USE_STM3210E_EVAL || defined USE_STM32100E_EVAL

  #define USARTy                   USART1
  #define USARTy_GPIO              GPIOA
  #define USARTy_CLK               RCC_APB2Periph_USART1
  #define USARTy_GPIO_CLK          RCC_APB2Periph_GPIOA
  #define USARTy_RxPin             GPIO_Pin_10
  #define USARTy_TxPin             GPIO_Pin_9
  #define USARTy_ClkPin            GPIO_Pin_8
  
  #define SPIy                     SPI1
  #define SPIy_GPIO                GPIOA
  #define SPIy_CLK                 RCC_APB2Periph_SPI1
  #define SPIy_GPIO_CLK            RCC_APB2Periph_GPIOA
  #define SPIy_SCKPin              GPIO_Pin_5
  #define SPIy_MISOPin             GPIO_Pin_6
  #define SPIy_MOSIPin             GPIO_Pin_7

#endif /* USE_STM3210B_EVAL */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
