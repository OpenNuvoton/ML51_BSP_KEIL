/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: ML51 TIMER 2 Capture function demo
//***********************************************************************************************************

#include "ML51.h"
/**
 * @brief       Timer2  interrupt subroutine
 */
void Capture_ISR(void) interrupt 12      // Vector @  0x63
{
    _push_(SFRS);

    clr_CAPCON0_CAPF0;
    clr_CAPCON0_CAPF2;
    DISABLE_TIMER2_CAP0;

    _pop_(SFRS);
}


void main (void) 
{
/* Setting Multi function pin setting for GPIO toggle */ 
    MFP_P33_IC0;
    P33_INPUT_MODE;                          //Define P33 as IC0 input pin.
    ENABLE_P33_PULLUP;                       //Since check falling edge enalbe internal pull high function.
    TIMER2_Capture(IC0,CaptureRising,2);
    MFP_P31_IC2;
    P31_INPUT_MODE;                          //Define P33 as IC0 input pin.
    ENABLE_P31_PULLUP;                       //Since check falling edge enalbe internal pull high function.
    TIMER2_Capture(IC2,CaptureEither,7);;

    while(1);
}



