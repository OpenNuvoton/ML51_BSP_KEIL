/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/29/2020
//***********************************************************************************************************

#include "ML51.h"

unsigned int rctemp[5],rtemp;
unsigned char data c,d;
/**
 * @brief       Trim LIRC into 1% sub
 * @param       none
 * @return      none
 * @details     whole trim time about 32ms.
 * @note        always use trim lirc when power is stable.
 */
 
 void Timer2_Initial_Start(void)
{
    SFRS = 0x00;
    clr_T2CON_CMRL2;                                  //Timer 2 as auto-reload mode
    set_T2MOD_LDEN;
    set_T2MOD_CMPCR;                                  //Timer 2 value is auto-cleared as 0000H when a compare match occurs.
    TL2 = 0;
    TH2 = 0;
    SFRS = 1;
    RCMP2L = 0;
    RCMP2H = 0;
    set_T2CON_TR2;                                
}

void WKT_Initial_Start(void)
{
    SFRS = 0;
    WKCON &= 0xDF;
    RWKH = 0xFF;
    RWKL = 0x19;
    set_WKCON_WKTR;
}

void WakeUp_Timer_ISR (void) interrupt 17     //ISR for self wake-up timer
{
    _push_(SFRS);
  
    clr_WKCON_WKTR;
    clr_WKCON_WKTF;                                   //clear interrupt flag   
    clr_T2CON_TR2;
    rctemp[c] = (TH2<<8)+TL2;
    c++;
    SFRS = 
    SFRS = 0;
    TL2 = 0;
    TH2 = 0;
    WKT_Initial_Start();
    set_T2CON_TR2;    

    _pop_(SFRS);
}

void Trim_LIRC(void) 
{
    set_EIE1_EWKT;                                   // Enable WKT interrupt
    ENABLE_GLOBAL_INTERRUPT;                        // Enable Globe interrupt
    WKT_Initial_Start();
    Timer2_Initial_Start();
    c=0;
    while (c!=5);
    clr_WKCON_WKTR;
    clr_WKCON_WKTF;                                  //clear interrupt flag   
    clr_T2CON_TR2;
    DISABLE_GLOBAL_INTERRUPT;
    for(c=0;c<4;c++)
    {
        rtemp=(rctemp[c+1]+rctemp[c])/2;
    }
    if (rtemp<15625)
    {
      d = (15625-rtemp)/300; 
      SFRS=1;  
      c=LIRCTRIM+d;
      TA=0xAA;
      TA=0x55;
      LIRCTRIM = c;
    }
}


void Trim_LIRC_32768(void) 
{      
      SFRS=0;
      if(PCON&SET_BIT4)
      {
        Trim_LIRC();
        SFRS=1;  
        c=LIRCTRIM+0x21;
        TA=0xAA;
        TA=0x55;
        LIRCTRIM = c;
        SFRS=0;
        PCON&=CLR_BIT4;
      }
}