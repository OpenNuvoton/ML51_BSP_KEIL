/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 Read UID demo code
//***********************************************************************************************************
#include "ml51.h"

/* For printf code only. Disable this define to reduce code size. */
#define print_function 

/**********************************/
/* *only read one byte of UID    */
/*********************************/ 

void main(void)
{
  unsigned char READ;

#ifdef print_function  
/* Initial UART0 for printf */
    MFP_P31_UART0_TXD;
    P31_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
#endif  
 
  UID_Read();
#ifdef print_function
  /*printf must in SFR page 0 */
	PUSH_SFRS;
	SFRS = 0;		
  printf ("\n UID = ");
  for(READ=0;READ<12;READ++)
  {
    printf (" 0x%bx",UIDBuffer[READ]);
  }
  POP_SFRS;
#endif    
  while(1);


}