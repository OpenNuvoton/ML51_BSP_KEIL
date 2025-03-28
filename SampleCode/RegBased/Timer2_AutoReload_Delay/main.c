/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************/
/*  File Function: ML51 Timer 2 delay with interrupt demo                                                   */
/************************************************************************************************************/
#include "ml51.h"

/************************************************************************************************************
*    Timer2 interrupt subroutine
************************************************************************************************************/
void Timer2_ISR (void) interrupt 5
{
    PUSH_SFRS;
  
    clr_T2CON_TF2;                                //Must clear Timer2 Interrupt Flag by software.
    P31 = ~ P31;
  
    POP_SFRS;
}	
/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    P31_PUSHPULL_MODE;

    TIMER2_DIV_1;
    TIMER2_Auto_Reload_Delay_Mode;

    SFRS = 1;
    RCMP2H = 0xA2;                                 /* Each time reload value from RCMP2 must initial when use auto reload mode. */
    RCMP2L = 0x40;
    SFRS = 0;
    TH2 = 0xA2;                                    /* First tmie delay value setting */
    TL2 = 0x40;

    set_EIE0_ET2;                                   /*  Enable Timer2 interrupt */
    set_IE_EA;
    set_T2CON_TR2;                                 /* Timer2 run  */

    while(1);


}
