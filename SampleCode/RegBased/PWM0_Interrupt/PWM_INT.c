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
//  File Function: ML51 PWM output falling edge trig interrupt demo
//***********************************************************************************************************
#include "ML51.h"

/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */

#if 0
#define print_function 
#endif

bit pwmintflag =0;
/************************************************************************************************************
*   PWM interrupt subroutine
************************************************************************************************************/
void PWM_ISR (void) interrupt 13
{
    _push_(SFRS);
  
    clr_PWM0CON0_PWMF;               // clear PWM interrupt flag
    pwmintflag = 1;

    _pop_(SFRS);
}  

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
#ifdef print_function
  /* UART0 initial setting
  ** include uart.c in Library for UART initial setting
  **UART0 define P3.1 TXD multi function setting
  **/
  Enable_UART0_VCOM_printf();
  printf("\n ADC trig by GPIO intial...");
#endif

/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (24MHz/8)/(PWMH+PWML + 1)
***********************************************************************/
    MFP_P24_PWM0_CH1;
    P24_PUSHPULL_MODE;
  
    PWM0_IMDEPENDENT_MODE;
    PWM0_CLOCK_DIV_128;
    PWM0PH = 0x07;
    PWM0PL = 0xCF;
  
    ENABLE_PWM0_CHANNEL1_INT;
    PWM0_FALLING_INT;                  /* Setting Interrupt happen when PWM0 channel 1falling signal */
  
    PWM0_CLOCK_DIV_8;
    PWM0PH = 0xF0;                     /* Setting PWM period */
    PWM0PL = 0xFF;
    PWM0C1H = 0xE0;                    /* PWM0 high duty = 1/2 PWM period  */
    PWM0C1L = 0xFF;  

    ENABLE_PWMM0_INTERRUPT;            /* Enable PWM interrupt */
    ENABLE_GLOBAL_INTERRUPT;
    set_PWM0CON0_LOAD;
    set_PWM0CON0_PWMRUN;

    while(1)
    { 
       if(pwmintflag)
      {
        pwmintflag=0;
#ifdef   print_function
        _push_(SFRS); SFRS = 0;
        printf ("\n PWM interrupt !!");
        _pop_(SFRS);
#endif
      }
    }
}