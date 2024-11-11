/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ML51.H"

bit bodflag=0;
void BOD_ISR (void) interrupt 8           // Vector @  0x43
{
    _push_(SFRS);
 
    clr_BODCON0_BOF;
    bodflag=1;


    _pop_(SFRS);
}

//----------------------------------------------------------------------------------------------//
void main (void)
{
/* As defaut all multi function define as GPIO */ 
  P32_QUASI_MODE;

  BOD_Open(Enable, VBOD_2_4, BOD_NO_RESET);
//  BOD_LowPower(LPBOD_Mode_3);
  BOD_Interrupt(Enable);
  ENABLE_GLOBAL_INTERRUPT;
  while(1)
  {
     Timer0_Delay(24000000,200,1000);
    if (bodflag)
    {
        P32 ^= 1;
    }
  }
}



