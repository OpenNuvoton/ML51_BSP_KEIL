/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

#include "ML51.h"
/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function 

void main (void) 
{
   unsigned int xdata u16value;
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
  
/* ADC initial setting 
  * include adc.c in Library for ADC setting.
*/  
    VREF_Open(LEVEL3);
    ENABLE_ADC_VTEMP;

    clr_ADCCON0_ADCF;                              /*Clear ADC flag before ADC start */
    set_ADCCON0_ADCS;                              /* Each time ADC start trig signal*/
    while(!(ADCCON0&SET_BIT7));                    /* wait ADCF = 1 */
    u16value = (ADCRH<<4)+ADCRL;

#ifdef print_function
  /*printf must in SFR page 0 */
      _push_(SFRS);
      SFRS = 0;
      printf ("\n VTEMP = 0x%X",u16value);
      _pop_(SFRS);
#endif

    while(1);
}


