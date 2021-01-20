/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/*  Website: http://www.nuvoton.com                                                                        */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Apr/29/2020                                                                                   */
/***********************************************************************************************************/


#include "ML51.h"

/**
 * @brief       PWM indepedent mode PWM0 channel 0~5 output demo
 * @param       None
 * @return      None
 * @details     Channel 0 high duty 10%, Channel 1 high duty 20% ..... Channel 5 high duty 60%.
 */

void main (void) 
{

/* PWM0 initial setting  
   * include pwm.c in Library for PWM mode setting
   @note: the period setting of all PWM0 should be same, for example following 0x6FF.
*/
    PWM0_ClockSource(PWM_FSYS,128);                                  // define PWM0 clock source and divider.
  
    MFP_P05_PWM0_CH0;                                                // multi function pin define P0.5 as PWM0 channel 0 output
    P05_PUSHPULL_MODE;                                              
    PWM0_ConfigOutputChannel(0,Independent,EdgeAligned,0x6FF,10);    // setting PWM channel 0 as 10% duty high of 0x6FF PWM period = 0x00B3
  
    MFP_P24_PWM0_CH1;                                                // multi function pin define P2.4 as PWM0 channel 1 output
    P24_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(1,Independent,EdgeAligned,0x6FF,20);    // setting PWM channel 1 as 20% duty high of 0x6FF PWM period = 0x0166
  
    MFP_P03_PWM0_CH2;                                                // multi function pin define P0.3 as PWM0 channel 2 output
    P03_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(2,Independent,EdgeAligned,0x6FF,30);    // setting PWM channel 2 as 30% duty high of 0x6FF PWM period = 0x0219
  
    MFP_P22_PWM0_CH3;                                                // multi function pin define P2.2 as PWM0 channel 3
    P22_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(3,Independent,EdgeAligned,0x6FF,40);    // setting PWM channel 3 as 40% duty high of 0x6FF PWM period = 0x02CC
  
    MFP_P01_PWM0_CH4;                                                // multi function pin define P0.1 as PWM0 channel 4
    P01_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(4,Independent,EdgeAligned,0x6FF,50);    // setting PWM channel 4 as 50% duty high of 0x6FF PWM period = 0x037F
    
    MFP_P20_PWM0_CH5;                                                // multi function pin define P0.5 as PWM0 channel 0
    P20_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(5,Independent,EdgeAligned,0x6FF,60);    // setting PWM channel 5 as 60% duty high of 0x6FF PWM period = 0x0432
    
    PWM0_RUN();
    
    while(1);
}



