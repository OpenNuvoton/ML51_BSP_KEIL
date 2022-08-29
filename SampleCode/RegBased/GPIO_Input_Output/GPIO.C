/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 GPIO toggle demo code
//***********************************************************************************************************
#include "ML51.h"

unsigned char temp _at_ 0x08;
unsigned char idata itemp _at_ 0x90;
unsigned char xdata xtemp _at_ 0x80;

//----------------------------------------------------------------------------------------------//
void main (void)
{
/* As defaut all multi function define as GPIO */ 
  ALL_GPIO_QUASI_MODE;
  P51_INPUT_MODE;
  P60_PUSHPULL_MODE;

  while(1)
  {
    P1 = ~P1;
    P4 = ~P4;
    SFRS=0; set_P5_3;
    SFRS=2; P6 |= SET_BIT0;    /* or set_P6_0; */
    Timer2_Delay(24000000,4,2,1000);
    SFRS=0; clr_P5_3;
    SFRS=2; P6 &= ~SET_BIT0;   /* or clr_P6_0; */
    Timer2_Delay(24000000,4,2,1000);
  }
}



