/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.        */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/*  Website: http://www.nuvoton.com                                                                        */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Aug/21/2020                                                                                   */
/***********************************************************************************************************/

#include "ML51.h"

/**
 * @brief       PWM indepedent mode PWM1 PWM2 PWM3 output demo
 * @param       None
 * @return      None
 * @details     Channel 0 high duty 10%, Channel 1 high duty 20% ..... Channel 5 high duty 60%.
 */


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (16MHz/8)/(0x3FF + 1)
                = 2.7KHz
***********************************************************************/
    PWM123_ClockSource(PWM1,8);
    PWM123_ClockSource(PWM2,4);
    PWM123_ClockSource(PWM3,2);

    MFP_P45_PWM1_CH0;                               // multi function pin define P0.5 as PWM0 channel 0 output
    P45_PUSHPULL_MODE;
    PWM123_ConfigOutputChannel(PWM1,0,0x6FF,10);    // setting PWM channel 0 as 10% duty high of 0x6FF PWM period = 0x00B3
  
    MFP_P44_PWM1_CH1;                               // multi function pin define P2.4 as PWM0 channel 1 output
    P44_PUSHPULL_MODE;
    PWM123_ConfigOutputChannel(PWM1,1,0x6FF,20);    // setting PWM channel 1 as 20% duty high of 0x6FF PWM period = 0x0166
  
    MFP_P43_PWM2_CH0;                               // multi function pin define P0.3 as PWM0 channel 2 output
    P43_PUSHPULL_MODE;
    PWM123_ConfigOutputChannel(PWM2,0,0x6FF,30);    // setting PWM channel 2 as 30% duty high of 0x6FF PWM period = 0x0219
  
    MFP_P42_PWM2_CH1;                               // multi function pin define P2.2 as PWM0 channel 3
    P42_PUSHPULL_MODE;
    PWM123_ConfigOutputChannel(PWM2,1,0x6FF,40);    // setting PWM channel 3 as 40% duty high of 0x6FF PWM period = 0x02CC
  
    MFP_P41_PWM3_CH0;                               // multi function pin define P0.1 as PWM0 channel 4
    P41_PUSHPULL_MODE;
    PWM123_ConfigOutputChannel(PWM3,0,0x6FF,50);    // setting PWM channel 4 as 50% duty high of 0x6FF PWM period = 0x037F
    
    MFP_P40_PWM3_CH1;                               // multi function pin define P0.5 as PWM0 channel 0
    P40_PUSHPULL_MODE;
    PWM123_ConfigOutputChannel(PWM3,1,0x6FF,60);    // setting PWM channel 5 as 60% duty high of 0x6FF PWM period = 0x0432
    
    set_PWM1CON0_LOAD;
    set_PWM2CON0_LOAD;
    set_PWM3CON0_LOAD;
    
    while(1);
}

