/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 Timer1 demo
//***********************************************************************************************************
#include "ml51.h"


/* if define TIMER1_FSYS_DIV12, timer = (0xFFFF-0x1000)*12/24MHz = 30.58ms */
/* if define TIMER1_FSYS, timer = (0xFFFF-0x1000)/24MHz = 2.54ms */
#define TH1_INIT        0x10 
#define TL1_INIT        0x00


/************************************************************************************************************
*    TIMER 0 interrupt subroutine
************************************************************************************************************/
void Timer1_ISR (void) interrupt 3  //interrupt address is 0x000B
{
    PUSH_SFRS;

    SFRS = 0;   
    TH1 = TH1_INIT;
    TL1 = TL1_INIT;
    TF0 = 0;
    P32 = ~P32;                     // GPIO1 toggle when interrupt
  
    POP_SFRS;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    MFP_P32_GPIO;
    P32_PUSHPULL_MODE;
  
    ENABLE_TIMER1_MODE1;
    TIMER1_FSYS_DIV12;

    TH1 = TH1_INIT;
    TL1 = TL1_INIT;
    
    ENABLE_TIMER1_INTERRUPT;                       //enable Timer1 interrupt
    ENABLE_GLOBAL_INTERRUPT;                       //enable interrupts
  
    set_TCON_TR1;                                  //Timer1 run
    while(1);
}

