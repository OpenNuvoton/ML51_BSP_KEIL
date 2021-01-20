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
//  File Function: ML51 simple GPIO toggle out demo code
//***********************************************************************************************************

#include "ML51.h"
/**
 * @brief       ACMP interrupt subroutine
 * @param       None
 * @return      None
 * @details     None
 */
void ACMP_ISR (void) interrupt 23
{
    _push_(SFRS);
 
  if ((ACMPSR&SET_BIT2)==SET_BIT2)
  {
    ACMPSR&=CLR_BIT2;
    SFRS = 0;
    P13 ^=1;
  }
  else if ((ACMPSR&SET_BIT0)==SET_BIT0)
  {
    ACMPSR&=CLR_BIT0;
    SFRS = 0;
    P14 ^=1;
  }  
  
    _pop_(SFRS);
}	


/**
 * @brief       ACMP negtive input use Bandgap voltage main loop
 * @param       None
 * @return      None
 * @details     None
 */
void main (void) 
{
/* Setting Multi function pin setting for GPIO toggle 
   * include gipo.c in Common for GPIO mode setting
*/  MFP_P13_GPIO;
    P13_QUASI_MODE;
  
    MFP_P23_ACMP0_P1;
    MFP_P24_ACMP0_N0;
    MFP_P41_ACMP0_O;
    
/* ACMP intial 
   * include acmp.c in Library for ACMP initial and interrupt setting.
*/
// Initial ACMP0 P2.3 as positive and Bandgap as negetive input, Output to P4.1 
    ACMP_Open(ACMP0, ACMP_CTL_POSSEL_P1, ACMP_CTL_NEGSEL_PIN_N0,0, ACMP_CTL_ACMP0_OUTPUT_ENABLE, ACMP_CTL_HYSTERESIS_ENABLE);
/* Initial ACMP interrupt enable, wakeup function disable.*/
    ACMP_INTEnable(ACMP0, ACMP_CTL_WAKEUP_ENABLE, ACMP_CTL_INT_ENABLE);
/*To use interrupt function, must enable blobal interrupt after all setting.*/
    ENABLE_GLOBAL_INTERRUPT;
  
    while (1)
    {
      set_PCON_PD;
      Timer0_Delay(24000000,100,10000);
    }

}



