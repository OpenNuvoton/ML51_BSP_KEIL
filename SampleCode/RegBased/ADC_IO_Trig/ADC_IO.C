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
//  File Function: ML51  ADC  trig by GPIO
//****************************************************t*******************************************************
#include "ML51.h"

/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function

unsigned char adc_flag;
unsigned int temp;
/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR (void) interrupt 11
{
    _push_(SFRS);
    adc_flag = 1; 
    clr_ADCCON0_ADCF;                               //clear ADC interrupt flag
    temp = (ADCRH<<4)|ADCRL;
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
  printf("\n ADC trig by GPIO intial...");
  printf("\n P5.5 pull low to start ADC");
#endif
/*---------------------------------------------------------------
  ADC port trig initial setting toggle P5.5 to start ADC 
----------------------------------------------------------------*/
    ENABLE_ADC_CH0;                              // Enable AIN0 P1.7 as ADC pin
    MFP_P55_STADC;
    P55_INPUT_MODE;
    ENABLE_P55_PULLUP;
    ADC_EXTTRIG_STADC_FALLINGEDGE;                      // P5.5 falling edge as adc start trig signal
/* Enable ADC interrupt */
    ENABLE_ADC_INTERRUPT;                                  // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;
/* Trig P04 falling edge to start adc, no need set ADCS bit*/
    while (!adc_flag);
    temp = (ADCRH<<4)|ADCRL;
    DISABLE_ADC;

#ifdef print_function
  /*printf base on UART0 must in SFR page 0 */
      _push_(SFRS);
      SFRS = 0;
      printf ("\n Value = 0x%X",temp);
      _pop_(SFRS);
#endif

    while(1);
}


