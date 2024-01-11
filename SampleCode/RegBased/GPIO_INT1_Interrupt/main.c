/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 INT1 initial 
//***********************************************************************************************************
#include "ml51.h"
/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function

bit  int1flag=0;
/* External pin interrupt INT0 subroutine */
void INT1_ISR (void) interrupt 2          // Vector @  0x13
{
    PUSH_SFRS;
    clr_TCON_IE1;                        //clr int flag wait next falling edge
    int1flag=1;
    POP_SFRS;
}

void main (void) 
{
#ifdef  print_function
    Enable_UART0_VCOM_printf();
    printf ("\n P24 INT1 external interrupt initial!!");
#endif

/* INT1 initial */
    MFP_P24_INT1;
    P24_QUASI_MODE;                      //setting INT0 pin P2.4 as Quasi mode with internal pull high  
    P24 = 1;
    INT1_LOW_LEVEL_TRIG;                 //setting trig condition level or edge
    ENABLE_INT1_INTERRUPT;               //INT1_Enable;
    ENABLE_GLOBAL_INTERRUPT;             //Global interrupt enable
    while(!int1flag);

#ifdef  print_function
    PUSH_SFRS;
    SFRS = 0;
    printf ("\n INT1 interrupt !!");
    POP_SFRS;
#endif

    while(1);
}



