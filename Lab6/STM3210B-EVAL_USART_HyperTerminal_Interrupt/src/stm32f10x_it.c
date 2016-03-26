/**
  ******************************************************************************
  * @file    USART/HyperTerminal_Interrupt/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    24-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

#ifdef USE_STM32100B_EVAL
 #include "stm32100b_eval.h"
#elif defined USE_STM3210B_EVAL
 #include "stm3210b_eval.h"
#elif defined USE_STM3210E_EVAL
 #include "stm3210e_eval.h" 
#elif defined USE_STM3210C_EVAL
 #include "stm3210c_eval.h"
#elif defined USE_STM32100E_EVAL
 #include "stm32100e_eval.h"
#endif

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_HyperTerminal_Interrupt
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifdef USE_STM3210C_EVAL
  #define USARTx_IRQHandler   USART2_IRQHandler
#else
  #define USARTx_IRQHandler   USART1_IRQHandler
#endif

#define TxBufferSize   (countof(TxBuffer) - 1)
#define RxBufferSize   0x20

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer[] = "\n\rUSART Hyperterminal Interrupts Example: USART-Hyperterminal\
 communication using Interrupt\n\r";
uint8_t RxBuffer[RxBufferSize];
uint8_t NbrOfDataToTransfer = TxBufferSize;
uint8_t NbrOfDataToRead = RxBufferSize;
uint8_t TxCounter = 0; 
uint16_t RxCounter = 0; 

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles USARTx global interrupt request.
  * @param  None
  * @retval None
  */
void USARTx_IRQHandler(void)
{
  if(USART_GetITStatus(EVAL_COM1, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    RxBuffer[RxCounter++] = (USART_ReceiveData(EVAL_COM1) & 0x7F);

    if(RxCounter == NbrOfDataToRead)
    {
      /* Disable the EVAL_COM1 Receive interrupt */
      USART_ITConfig(EVAL_COM1, USART_IT_RXNE, DISABLE);
    }
  }

  if(USART_GetITStatus(EVAL_COM1, USART_IT_TXE) != RESET)
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(EVAL_COM1, TxBuffer[TxCounter++]);

    if(TxCounter == NbrOfDataToTransfer)
    {
      /* Disable the EVAL_COM1 Transmit interrupt */
      USART_ITConfig(EVAL_COM1, USART_IT_TXE, DISABLE);
    }
  }
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
