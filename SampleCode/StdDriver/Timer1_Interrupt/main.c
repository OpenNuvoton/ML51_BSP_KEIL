/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ml51.h"

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Timer3 interrupt Service Routine                                                          */
/************************************************************************************************************/
void Timer1_ISR (void) interrupt 3        // Vector @  0x1B
{
    PUSH_SFRS;
/* following setting for reload Timer 0 counter, this is must for next time*/
      TH1 = TH1TMP;
      TL1 = TL1TMP;
/* following clear flag is necessary for next time */
      clr_TCON_TF1;
      GPIO_LED ^= 1;
    POP_SFRS;
}
/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void)
{

    GPIO_LED_QUASI_MODE;

    Timer1_AutoReload_Interrupt_Initial(24,6400);
    ENABLE_GLOBAL_INTERRUPT;

    while(1);
}

