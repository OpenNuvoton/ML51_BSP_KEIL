/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 simple GPIO toggle out demo code
//***********************************************************************************************************

#include "ml51.h"


void main (void) 
{
    unsigned char ct;
    ALL_GPIO_QUASI_MODE;
/*
 For UART0 P3.1 as TXD output setting 
 * include uart.c in Common Setting for UART0 
*/
    MFP_P31_UART0_TXD;                              // UART0 TXD use P1.6
    P31_QUASI_MODE;                                 // set P1.6 as Quasi mode for UART0 trasnfer
    UART_Open(24000000,UART0_Timer1,115200);        // Open UART0 use timer1 as baudrate generate and baud rate = 115200
    ENABLE_UART0_PRINTF;

    for (ct=0;ct<5;ct++)
    {
      P0 = ~P0;
      P1 = ~P1;
      P2 = ~P2;
      P3 = ~P3;
      P4 = ~P4;
      P5 = ~P5;
      SFRS=2;
      P6 = ~P6;
      SFRS=0;
      Timer0_Delay(24000000,200,1000);
    }
    P31 = 1;
    printf("\n Hello world!");
    while(1);
}



