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
//  File Function: ML51 comparater base on internal Vref demo
//***********************************************************************************************************

#include "ML51.h"


/**
 * @brief       ACMP interrupt subroutine
 * @param       None
 * @return      None
 * @details     
 */
void PinInterrupt_ISR (void) interrupt 23
{
    _push_(SFRS);

  if (ACMPSR|=SET_BIT2)
  {
    ACMPSR&=CLR_BIT2;
    P31 ^=1;
  }
  else if (ACMPSR|=SET_BIT0)
  {
    ACMPSR&=CLR_BIT0;
    P31 ^=1;
  }  

    _pop_(SFRS);
}	


/**
 * @brief       ACMP negtive input use Bandgap voltage 
 * @param       None
 * @return      None
 * @details     
 */

void main (void) 
{

/* Setting Multi function pin setting for GPIO toggle 
   * include gipo.c in Common for GPIO mode setting
*/  MFP_P31_GPIO;
    P31_PUSHPULL_MODE;

    MFP_P23_ACMP0_P1;
    MFP_P41_ACMP0_O;
    P41_QUASI_MODE;

/* ACMP intial 
   * include acmp.c in Library for ACMP initial and interrupt setting.
*/
    VREF_Open(LEVEL2);
/* Initial ACMP0 P2.3 as positive and Bandgap as negetive input, Output to P4.1 */
    ACMP_Open(ACMP0, ACMP_CTL_POSSEL_P1, ACMP_CTL_NEGSEL_CRV, ACMP_CTL_CRV_VREF, ACMP_CTL_ACMP0_OUTPUT_ENABLE, ACMP_CTL_HYSTERESIS_ENABLE);
/* CRV Value = CRV source voltage * (2/12+CRV1CTL/12). so for this example = VREF/2.*/
    ACMP_CRVValue(ACMP0, 4);  
/* Initial ACMP interrupt enable, wakeup function disable.*/
    ACMP_INTEnable(ACMP0, ACMP_CTL_WAKEUP_DISABLE, ACMP_CTL_INT_ENABLE);
    ENABLE_GLOBAL_INTERRUPT;
    
    while(1);
}



