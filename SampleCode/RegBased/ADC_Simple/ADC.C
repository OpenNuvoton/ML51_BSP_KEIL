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
//  File Function: ML51 ADC trig by sfr start bit demo
//***********************************************************************************************************
#include "ML51.h"


/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function 

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
unsigned int xdata ADCdataAIN;

void main (void) 
{

#ifdef print_function
  /* UART0 initial setting
  ** include uart.c in Library for UART initial setting
  **UART0 define P3.1 TXD multi function setting
  **/
    MFP_P31_UART0_TXD;
    P31_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
#endif

    ENABLE_ADC_CH4;
    ADCCON1|=0x30;                     /* clock divider */
    ADCCON2|=0x0E;                     /* AQT time */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;                  // ADC start trig signal
    while(!(ADCCON0&SET_BIT7));
    ADCdataAIN = (ADCRH<<4)|ADCRL;

#ifdef print_function
  /*printf must in SFR page 0 */
      _push_(SFRS);
      SFRS = 0;
      printf ("\n ADC result = 0x%X",ADCdataAIN);
      _pop_(SFRS);
#endif

    while(1);
}


