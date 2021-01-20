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
//  File Function: ML51 series ADC software trigger on shot demo code
//***********************************************************************************************************
#include "ML51.h"

/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function 

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main () 
{
  unsigned int ADCRESULT;

#ifdef print_function
  /* UART0 initial setting
  ** include uart.c in Library for UART initial setting
  **UART0 define P3.1 TXD multi function setting
  **/
  Enable_UART0_VCOM_printf();
#endif
/*
  ADCS to trig ADC convert 
  * include adc.c in Library for ADC initial setting
*/  
    VREF_Open(LEVEL1);
    ADC_Open(ADC_SINGLE,5);
    ADC_SamplingTime(3,7);
  
/* find ADC result in ADC interrupt*/
     set_ADCCON0_ADCS;                           // Software trig adc start
     while(!(ADCCON0&SET_BIT7));;                // wait ADCF = 1;
     ADCRESULT = (ADCRH<<4)+ADCRL;
#ifdef print_function
  /*printf must in SFR page 0 */
      _push_(SFRS);
      SFRS = 0;
      printf("\n ADC result = 0x%X  ", ADCRESULT);
      _pop_(SFRS);
#endif
    while(1);
  
}

