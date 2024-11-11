/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ml51.h"
 
BIT   wdtintflag;

/************************************************************************************************************/
/* FUNCTION_PURPOSE: ADC interrupt Service Routine                                                          */
/************************************************************************************************************/
void WDT_ISR (void)   interrupt 10
{
PUSH_SFRS;
    CLEAR_WDT_INTERRUPT_FLAG;
  /* Config Enable WDT reset and not clear couter trig reset */
    GPIO_LED ^= 1;
    wdtintflag = 1;
POP_SFRS;
}

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void)
{
    unsigned char ct; 
/* UART0 settting for printf function */
    Enable_UART0_VCOM_printf();
    printf ("\n Test start ...");

    GPIO_LED_QUASI_MODE;
/*--------------------------------------------------------
*Warning:
*Pleaes always check CONFIG WDT disable first 
*only when WDT reset disable, WDT use as pure timer
--------------------------------------------------------*/
    WDT_Open(256);
	  WDT_Interrupt(ENABLE);
	  Global_Interrupt(ENABLE);

    for(ct=0;ct<4;ct++)
    {
      WDT_Clear();
      Timer0_Delay(24000000,300,1000);
      GPIO_LED ^= 1;
    }
    while (1)
    {
      if (wdtintflag);
      {
        printf (" \n\r WDT interrupt ! \n\r");
        wdtintflag = 0;
        set_PCON_PD;
      }
    }
}
