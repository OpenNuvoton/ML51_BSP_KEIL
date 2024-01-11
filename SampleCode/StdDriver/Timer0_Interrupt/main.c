/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ml51.h"

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Timer0 interrupt Service Routine                                                       */
/************************************************************************************************************/
void Timer0_ISR (void) interrupt 1        // Vector @  0x0B
{
    PUSH_SFRS;
      SFRS = 0;
/* following setting for reload Timer 0 counter */
      TH0 = TH0TMP;
      TL0 = TL0TMP;
/* following clear flag for next interrupt */
      clr_TCON_TF0;
      GPIO_LED ^= 1;
   POP_SFRS;
}

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void)
{

    GPIO_LED_QUASI_MODE;

    Timer0_AutoReload_Interrupt_Initial(24,32000);
    ENABLE_GLOBAL_INTERRUPT;

    while(1);
}

