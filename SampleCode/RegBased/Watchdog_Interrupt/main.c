/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: ML51 Watchdog timer interrupt function demo                                              */
/************************************************************************************************************/
#include "ml51.h"
 
/************************************************************************************************************
*    WDT interrupt sub-routine
************************************************************************************************************/
void WDT_ISR (void)   interrupt 10
{
  PUSH_SFRS;
    clr_WDCON_WDTF;
    set_WDCON_WDCLR;
    while((WDCON|~SET_BIT6)==0xFF);
    P32 = ~P32;
  POP_SFRS;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
/* Note
  WDT timer base is LIRC 10Khz
*/
    MFP_P32_GPIO;
    P32_QUASI_MODE;
//--------------------------------------------------------
//Warning:
//Pleaes always check CONFIG WDT disable first 
//only when WDT reset disable, WDT use as pure timer
//--------------------------------------------------------
    TA=0xAA;TA=0x55;WDCON=0x07;          //Setting WDT prescale 
    set_WDCON_WIDPD;                     //WDT run in POWER DOWM mode setting if needed
    ENABLE_WDT_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    set_WDCON_WDTR;                      //WDT run
    set_WDCON_WDCLR;                     //Clear WDT timer
    while((WDCON|~SET_BIT6)==0xFF);

    while (1)
    {
      set_PCON_PD;
    }

}
