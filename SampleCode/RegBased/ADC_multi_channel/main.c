/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 ADC multi channel input demo code
//***********************************************************************************************************
#include "ml51.h"

/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function

unsigned int xdata ADCdataAIN5;
unsigned int xdata ADCdataVBG;

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    unsigned char i;
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

  /*Enable channel 5 */ 
      ENABLE_ADC_CH5;
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;
      while(!(ADCCON0&SET_BIT7)); 
      ADCdataAIN5 = (ADCRH<<4)|(ADCRL&0x0F);
      DISABLE_ADC;
 #ifdef print_function
  /*printf must in SFR page 0 */
     PUSH_SFRS;
     SFRS = 0;
     printf("\n ADC channel 5 = %D", ADCdataAIN5);
    POP_SFRS;
#endif

  /*Enable Bandgap */
      ENABLE_ADC_BANDGAP;
  /* IMPORTANT !!! multi channel convert must delay for ADC maocro ready */ 
      for (i=0;i<10;i++)
      _nopDelay_();
      ADCCON1|=0X30;            /* clock divider */
      ADCCON2|=0X0E;            /* AQT time */
      clr_ADCCON0_ADCF;
      set_ADCCON0_ADCS;
      while(!(ADCCON0&SET_BIT7)); 
      ADCdataVBG = (ADCRH<<4)|(ADCRL&0x0F);

#ifdef print_function
  /*printf must in SFR page 0 */
     PUSH_SFRS;
     SFRS = 0;
     printf("\n ADC channel bandgap = %D", ADCdataVBG);
    POP_SFRS;
#endif

    while(1);
}