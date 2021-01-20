/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Apr/29/2020                                                                                   */
/***********************************************************************************************************/

/************************************************************************************************************/
/*  File Function: ML51 Wakeup timer demo code with interrupt                                               */
/************************************************************************************************************/

#include "ML51.h"


void WakeUp_Timer_ISR (void)   interrupt 17     //ISR for self wake-up timer
{
    unsigned char i; 
    _push_(SFRS);

    clr_WKCON_WKTR;
    for (i=0;i<10;i++)
    {
      P35 = ~P35;
      _delay_();
      _delay_();
    }
    clr_WKCON_WKTF;                                   //clear interrupt flag
    set_WKCON_WKTR;

    _pop_(SFRS);
}


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
   
    P35_PUSHPULL_MODE;

//-----------------------------------------------------
//  WKT initial   
//-----------------------------------------------------  
    SFRS = 0;
    WKCON = 0x02;                     //timer base 10k, Pre-scale = 1/16
    SFRS = 2;
    RWKH = 0xFC;
    SFRS = 0;
    RWKL = 0X00;                      //  if prescale is 0x00, never set RWK = 0xff
    ENABLE_WKT_INTERRUPT;             // enable WKT interrupt
    ENABLE_GLOBAL_INTERRUPT;
    set_WKCON_WKTR;                   // Wake-up timer run 

    while(1)
    {
      P35 = ~P35 ;
      _delay_();
    }
}

