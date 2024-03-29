/**
  @page USART_HyperTerminal_HwFlowControl USART Hyperterminal Hardware Flow Control example
  
  @verbatim
  ******************** (C) COPYRIGHT 2012 STMicroelectronics *******************
  * @file    USART/HyperTerminal_HwFlowControl/readme.txt 
  * @author  MCD Application Team
  * @version V3.6.0
  * @date    24-April-2012
  * @brief   Description of the USART Hyperterminal Hardware Flow Control
  *          example.
  ******************************************************************************
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
   @endverbatim

@par Example Description 

This example provides a description of how to use the USART with hardware flow
control and communicate with the Hyperterminal.
First, the USART2 sends the TxBuffer to the hyperterminal and still waiting for
a string from the hyperterminal that you must enter which must end by '\r'
character (keypad ENTER button). The communication will end if received data exceed
255 without sending the '\r' character. Each byte received is retransmitted to the
Hyperterminal.
The string that you have entered is stored in the RxBuffer array. The receive
buffer have a RxBufferSize bytes as maximum.

The USART2 is configured as follow:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control enabled (RTS and CTS signals)
    - Receive and transmit enabled

@par Directory contents 

  - USART/HyperTerminal_HwFlowControl/platform_config.h    Evaluation board specific configuration file
  - USART/HyperTerminal_HwFlowControl/stm32f10x_conf.h     Library Configuration file
  - USART/HyperTerminal_HwFlowControl/stm32f10x_it.h       Interrupt handlers header file
  - USART/HyperTerminal_HwFlowControl/stm32f10x_it.c       Interrupt handlers
  - USART/HyperTerminal_HwFlowControl/main.c               Main program
  - USART/HyperTerminal_HwFlowControl/system_stm32f10x.c   STM32F10x system source file
  
@par Hardware and Software environment 

  - This example runs on STM32F10x Connectivity line, High-Density, High-Density 
    Value line,Medium-Density, XL-Density, Medium-Density Value line, Low-Density 
    and Low-Density Value line Devices.
  
  - This example has been tested with STMicroelectronics STM32100E-EVAL (High-Density 
    Value line), STM32100B-EVAL (Medium-Density Value line), STM3210E-EVAL 
    (High-Density and XL-Density) and STM3210B-EVAL (Medium-Density) evaluation 
    boards and can be easily tailored to any other supported device and development 
    board.
    This example can't be tested with STM3210C-EVAL (Connectivity Line) evaluation board.
    To select the STMicroelectronics evaluation board used to run the example, 
    uncomment the corresponding line in USART/HyperTerminal_HwFlowControl/platform_config.h file

  - STM32100E-EVAL Set-up 
    - Connect a null-modem female/female RS232 cable between CN10 and PC serial 
      port.
      @note Make sure the Jumper 5 (JP5) is not open.
      
  - STM32100B-EVAL Set-up 
    - Connect a null-modem female/female RS232 cable between CN9 and PC serial 
      port.
      @note In this case USART2 Tx, Rx, RTS and CTS pins are remapped by software
            on PD.05, PD.06, PD.04 and PD.03 respectively. 

  - STM3210E-EVAL Set-up 
    - Connect a null-modem female/female RS232 cable between CN8 and PC serial 
      port.
      @note Make sure the Jumper 4 (JP4) is in position 2<-->3.  

  - STM3210B-EVAL Set-up 
    - Connect a null-modem female/female RS232 cable between CN5 and PC serial 
      port.
      @note In this case USART2 Tx, Rx, RTS and CTS pins are remapped by software
            on PD.05, PD.06, PD.04 and PD.03 respectively. 

 
  - Hyperterminal configuration: 
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - BaudRate = 115200 baud
    - flow control: Hardware 
    
@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\STM32F10x_StdPeriph_Template
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 

@note
 - Low-density Value line devices are STM32F100xx microcontrollers where the 
   Flash memory density ranges between 16 and 32 Kbytes.
 - Low-density devices are STM32F101xx, STM32F102xx and STM32F103xx 
   microcontrollers where the Flash memory density ranges between 16 and 32 Kbytes.
 - Medium-density Value line devices are STM32F100xx microcontrollers where
   the Flash memory density ranges between 64 and 128 Kbytes.  
 - Medium-density devices are STM32F101xx, STM32F102xx and STM32F103xx 
   microcontrollers where the Flash memory density ranges between 64 and 128 Kbytes.
 - High-density Value line devices are STM32F100xx microcontrollers where
   the Flash memory density ranges between 256 and 512 Kbytes.
 - High-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 256 and 512 Kbytes.
 - XL-density devices are STM32F101xx and STM32F103xx microcontrollers where
   the Flash memory density ranges between 512 and 1024 Kbytes.
 - Connectivity line devices are STM32F105xx and STM32F107xx microcontrollers.
    
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
