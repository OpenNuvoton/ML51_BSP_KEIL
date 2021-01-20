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
//  File Function: ML51 simple GPIO toggle out demo code
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

    MFP_P25_UART2_TXD;
    P25_QUASI_MODE;                              /* Set UART2_TXD pin P3.0 as Quasi mode */
    MFP_P24_UART2_RXD;
    P24_INPUT_MODE;                              /* Set UART2_RXD pin P1.7 as Input mode */

    UART2_Open(24000000,9600);                 /* Open UART2 use timer1 as baudrate generate and baud rate = 115200*/
    ENABLE_SC0_RECEIVE_DATA_REACH_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;

/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart2rvflag)
    {
      uart2rvflag = 0;
      UART2_Send_Data(uart2rvbuffer);
    }
  }
}
