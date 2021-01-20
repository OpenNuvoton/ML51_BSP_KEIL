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
      case 0x01: printf("\n PIT0 interrupt!"); break;
      case 0x02: printf("\n PIT1 interrupt!"); break;
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
    MFP_P65_GPIO;

    GPIO_SetMode(Port1,BIT7,GPIO_MODE_INPUT);
    GPIO_SetMode(Port2,BIT5,GPIO_MODE_INPUT);
    GPIO_Pull_Enable(Port1,BIT7,PULLUP);
    GPIO_Pull_Enable(Port6,BIT5,PULLDOWN);
    GPIO_EnableInt(PIT0,BOTH,EDGE,Port1,7);
    GPIO_EnableInt(PIT1,HIGH,LEVEL,Port6,5);

    ENABLE_GLOBAL_INTERRUPT;                // global enable bit
    while(1);


}


