/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************
//  File Function: ML51 UART0 receive and transmit loop test
/***********************************************************************************************************/
#include "ml51.h"

//#define  UART0_TX_only
#define  UART0_RXTX_loop
/************************************************************************************************************/
/*  Main function                                                                                           */
/************************************************************************************************************/
 void main(void)
{

    MFP_P31_UART0_TXD;
    P31_QUASI_MODE;
    MFP_P30_UART0_RXD;
    P30_INPUT_MODE;
    UART_Open(24000000,UART0_Timer3,115200);

    ENABLE_UART0_INTERRUPT;                                   /* Enable UART0 interrupt */
    ENABLE_GLOBAL_INTERRUPT;                                  /* Global interrupt enable */

#if defined UART0_TX_only
    DISABLE_UART0_INTERRUPT;
    while (1)
    {
      UART_Send_Data(UART0,0x55);
      Timer0_Delay(24000000,500,1000);
    }

#elif defined UART0_RXTX_loop
/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart0_receive_flag)
    {
      uart0_receive_flag = 0;
	  DISABLE_UART0_INTERRUPT;
      UART_Send_Data(UART0,uart0_receive_data);
      ENABLE_UART0_INTERRUPT;
    }
  }
#endif 
}