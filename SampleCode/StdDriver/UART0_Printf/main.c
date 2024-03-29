/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: ML51 use UART0 as printf function output demo                                            */
/************************************************************************************************************/
#include "ml51.h"


void main (void) 
{

/* 
   For UART0 P3.1 as TXD output setting   
   include uart.c in Library Folder for UART0 
*/
    Enable_UART0_VCOM_printf();
    printf("\n Hello world!");
    while(1);

}