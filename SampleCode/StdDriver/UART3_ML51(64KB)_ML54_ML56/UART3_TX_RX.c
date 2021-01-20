/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: ML51 UART receive and transmit toggle out demo code
//***********************************************************************************************************

#include "ML51.h"

/**
 * @brief       UART2 TXD output demo
 * @param       None
 * @return      None
 * @details     conned UART2 and UART0 to loop check.
 */

void main (void) 
{
    MFP_P12_UART3_TXD;
    P12_QUASI_MODE;
    MFP_P11_UART3_RXD;
    P11_INPUT_MODE;
    UART3_Open(24000000,115200);                 /* Open UART3 use timer1 as baudrate generate and baud rate = 115200*/

    ENABLE_SC1_RECEIVE_DATA_REACH_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart3rvflag)
    {
      uart3rvflag = 0;
      UART3_Send_Data(uart3rvbuffer);
    }
   }
 }