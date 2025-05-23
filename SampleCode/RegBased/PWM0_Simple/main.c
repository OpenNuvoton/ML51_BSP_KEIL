/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 PWM  Simple output demo.
//***********************************************************************************************************
#include "ml51.h"


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
    MFP_P25_PWM0_CH0;
    MFP_P24_PWM0_CH1;
    MFP_P01_PWM0_CH4;
    MFP_P00_PWM0_CH5;
    P25_PUSHPULL_MODE;
    P24_PUSHPULL_MODE;
    P01_PUSHPULL_MODE;
    P00_PUSHPULL_MODE;
    
    PWM0_IMDEPENDENT_MODE;
    PWM0_CLOCK_DIV_8;
    PWM0PH = 0x30;
    PWM0PL = 0x0f;
/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (16MHz/8)/(0x7CF + 1)
                = 1KHz (1ms)
***********************************************************************/
    SFRS = 1;                 //Duty is in SFRS page 1
    PWM0C0H = 0x10;          
    PWM0C0L = 0x08;
    PWM0C1H = 0x00;            
    PWM0C1L = 0x25;
    
    PWM0C4H = 0x03;            
    PWM0C4L = 0xCF;
    PWM0C5H = 0x05;            
    PWM0C5L = 0xCF;
    
/* PWM output inversly enable */
    PWM0_CHANNEL1_OUTPUT_INVERSE;

/*-------- PWM start run--------------*/ 
    set_PWM0CON0_LOAD;
    set_PWM0CON0_PWMRUN;
    while(1);

}