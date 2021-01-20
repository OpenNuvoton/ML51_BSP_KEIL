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
//  File Function: ML51 PWM demo with dead time
//***********************************************************************************************************
#include "ML51.h"


void main(void)
{
    ALL_GPIO_QUASI_MODE;
/*-----------------------------------------------------------------------------------------------------------------
  PWM frequency   = Fpwm/((PWMPH,PWMPL)+1) = (24MHz/8)/(0xBB7+1) = 1KHz (1ms)
  PWM4 high duty  = PWM4H,PWM4L = 0x02EE = 1/4 PWM period
  PWM0 high duty  = PWM0H,PMW0L = 0x03CF = 1/2 PWM period
  Dead time       = 0x180 <PDTEN.4+PDTCNT[7:0]>/Fsys = 0x1FF/Fsys = 512/24000000 = 16 us (max value)
  Dead time       = 0x180 <PDTEN.4+PDTCNT[7:0]>/Fsys = 0x180/Fsys = 384/24000000 = 16 us (sample value)
-----------------------------------------------------------------------------------------------------------------*/
    MFP_P25_PWM0_CH0;
    MFP_P24_PWM0_CH1;
    MFP_P01_PWM0_CH4;
    MFP_P00_PWM0_CH5;
  
    PWM0_COMPLEMENTARY_MODE;                /* Only this mode support dead time function */
    PWM0_CLOCK_DIV_8;
    PWM0PH = 0x0B;
    PWM0PL = 0xB7;

    SFRS = 1;                               /* PWM Channel duty is in SFRS page 1 */
    PWM0C0H = 0x05;
    PWM0C0L = 0xDC;
    PWM0C4H = 0x02;
    PWM0C4L = 0xEE;

    TA=0xAA;TA=0x55;PWM0DTCNT = 0x80;       /* for Dead time setting */
    TA=0xAA;TA=0x55;PWM0DTEN |= 0x10;
    ENABLE_PWM0_CHANNEL01_DEADTIME;
    ENABLE_PWM0_CHANNEL45_DEADTIME;

 /*Please always setting Dead time before PWM run. */
    set_PWM0CON0_LOAD;
    set_PWM0CON0_PWMRUN;
    while(1);
}