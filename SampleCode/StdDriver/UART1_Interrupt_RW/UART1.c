/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Apr/29/2020                                                                                   */
/***********************************************************************************************************/

/************************************************************************************************************/
/*  File Function: ML51 UART1 with interrupt demo                                                           */
/************************************************************************************************************/
#include "ML51.h"


//#define  UART1_TX_only
#define  UART1_RXTX_loop

/****************************************************************************************************************
 * FUNCTION_PURPOSE: Main function 
 !!! if UART1 pin also occupied by debug pin, 
 please remove Nu-link or not in debug mode to test UART1 function.
 External UART1 connect also disturb debug download
 ***************************************************************************************************************/
void main (void)
{
    MFP_P23_UART1_TXD;
    P23_QUASI_MODE;
    MFP_P22_UART1_RXD;
    P22_INPUT_MODE;

    UART_Open(24000000,UART1_Timer3,115200);
    ENABLE_UART1_INTERRUPT;                 //For interrupt enable , interrupt subroutine is in uart.c file
    ENABLE_GLOBAL_INTERRUPT;                //Enable global interrupt

#if defined UART1_TX_only
    while(1)
    {
        UART_Send_Data(UART1,0x55);
        _delay_();
    }

#elif defined UART1_RXTX_loop
    while(1)
    {
      if (uart1_receive_flag)
      {   
          uart1_receive_flag = 0;
          UART_Send_Data(UART1,uart1_receive_data);
      }
    }
#endif
    while(1);
}
  
