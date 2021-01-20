/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/29/2020
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: ML51 Pin interrupt demo
//***********************************************************************************************************
#include "ML51.h"

/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function 
/******************************************************************************
Pin interrupt subroutine.
******************************************************************************/
void PinInterrupt_ISR (void) interrupt 7
{
    _push_(SFRS);
  
    SFRS = 0;
    switch(PIF)
    {
      case 1: printf("\n PIT0 interrupt!"); break;
      case 2: printf("\n PIT1 interrupt!"); break;
      case 3: printf("\n PIT2 interrupt!"); break;
      default: break;
    }
    PIF = 0; 
  
    _pop_(SFRS);
}
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
#ifdef print_function
  /* UART0 initial setting
  ** include uart.c in Library for UART initial setting
  **UART0 define P3.1 TXD multi function setting
  **/
  Enable_UART0_VCOM_printf();
#endif

//----------------------------------------------------
//  P1.3 set as highlevel trig pin interrupt function
//  otherwise, MCU into idle mode.
//----------------------------------------------------

    MFP_P17_GPIO;
    P17_INPUT_MODE;
    ENABLE_P17_PULLUP;

    MFP_P25_GPIO;
    P25_INPUT_MODE;
    ENABLE_P25_PULLUP;
    
    MFP_P35_GPIO;
    P35_INPUT_MODE;

    SFRS = 0;
    PIF = 0;
    ENABLE_PIT0_P17_LOWLEVEL;
    ENABLE_PIT1_P25_FALLINGEDGE;
    ENABLE_PIT2_P35_BOTHEDGE;
    ENABLE_PIN_INTERRUPT;                   // Enable pin interrupt
    ENABLE_GLOBAL_INTERRUPT;                // global enable bit
    while(1);


}


