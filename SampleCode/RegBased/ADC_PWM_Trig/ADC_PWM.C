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

//***********************************************************************************************************
//  File Function: ML51 ADC trig by PWM demo
//***********************************************************************************************************
#include "ML51.h"

#define   print_function
//#define   pwm0_falling_trig_adc
//#define   pwm0_rising_trig_adc
//#define   pwm0_central_trig_adc
#define     pwm0_end_trig_adc
bit  adc_flag=0;

/******************************************************************************
 * FUNCTION_PURPOSE: ADC interrupt Service Routine
 ******************************************************************************/
void ADC_ISR (void) interrupt 11
{
    _push_(SFRS);
    adc_flag = 1;
    clr_ADCCON0_ADCF;                       // Clear ADC interrupt flag
    P30 ^= 1;                                // Check the P3.0 toggle at falling edge of PWM
    _pop_(SFRS);
}

/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    ALL_GPIO_QUASI_MODE;

  /* UART0 settting for printf function */
    MFP_P31_UART0_TXD;
    P31_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
/*-------------------------------------------------
  ADC trig initial setting
  Please modify #if value to open diffent type
--------------------------------------------------*/
#ifdef pwm0_falling_trig_adc
    MFP_P05_PWM0_CH0;
    P05_PUSHPULL_MODE;
    ENABLE_ADC_CH10;
    ADC_EXTTRIG_PWM0_FALLINGEDGE;

#elif defined pwm0_rising_trig_adc
    MFP_P05_PWM0_CH0;
    P05_PUSHPULL_MODE;
    ENABLE_ADC_CH10;
    ADC_EXTTRIG_PWM0_RISINGEDGE;

#elif defined pwm0_central_trig_adc
    MFP_P05_PWM0_CH0;
    P05_PUSHPULL_MODE;
    ENABLE_ADC_CH10;
    PWM_CENTER_TYPE;
    PWM0_CENTRAL_TRIG_ADC;

#elif defined pwm0_end_trig_adc
    MFP_P05_PWM0_CH0;
    P05_PUSHPULL_MODE;
    ENABLE_ADC_CH10; 
    PWM0_CENTER_TYPE;
    ADC_EXTTRIG_PWM_END;
    
#endif
  
  /* Setting PWM value  */
    SFRS = 1;
    PWM0PH = 0x07;                                //Setting PWM value
    PWM0PL = 0xFF;
    PWM0C0H = 0x02;
    PWM0C0L = 0xFF;
    set_PWM0CON0_LOAD;                            // PWM run
    set_PWM0CON0_PWMRUN;
  /* Setting ADC        */
    ENABLE_ADC_INTERRUPT;                         // Enable ADC interrupt (if use interrupt)
    ENABLE_GLOBAL_INTERRUPT;  
    while(1)
    {
      if (adc_flag)
      {
        adc_flag=0;
#ifdef print_function
  /*printf must in SFR page 0 */
      _push_(SFRS);
      SFRS = 0;
      printf ("\n Value = 0x%bx",ADCRH);      // printf display will cause delay in ADC interrupt
      _pop_(SFRS);
#endif
      }
    }
}


