/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 GPIO toggle demo code
//***********************************************************************************************************
#include "ML51.H"


//----------------------------------------------------------------------------------------------//
void main (void)
{
/* As defaut all multi function define as GPIO */ 
    GPIO_SetMode(Port1,SET_BIT0 | SET_BIT5| SET_BIT7, GPIO_MODE_QUASI);
    GPIO_SetMode(Port4,SET_BIT6 | SET_BIT1, GPIO_MODE_PUSHPULL);
    GPIO_SetMode(Port6,SET_BIT0 | SET_BIT1, GPIO_MODE_PUSHPULL);
  while(1)
  {
    P1 = ~P1;
    P4 = ~P4;
    SFRS=0; set_P5_3;          /* or P5 |= SET_BIT3;  for none bit-addressable port */
    SFRS=2; P6 |= SET_BIT0;    /* or set_P6_0; for none bit-addressable port */
    if (!(P6&SET_BIT1))        /* if P6.1 == 0 , for none bit-addressable port */
    {
      _nop_();
    }
    Timer2_Delay(24000000,4,2,1000);

    SFRS=0; clr_P5_3;          /* or P5 &= CLR_BIT3;  for none bit-addressable port */
    SFRS=2; P6 &= CLR_BIT0;    /* or clr_P6_0;   for none bit-addressable port */
    if (P6&SET_BIT1)           /* if P6.1 == 1  for none bit-addressable port*/
    {
      _nop_();
    }
    Timer2_Delay(24000000,4,2,1000);
  }
}



