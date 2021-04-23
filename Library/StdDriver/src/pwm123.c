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

/****** PWM123 SETTING ********/
 /**
 * @brief This function config PWM clock base

 * @param[in] u8PWMCLKDIV the divider value of PWM clock.  - \ref (1\2\4\8\16\32\64\128) 
 * @return none
 * @note        
 * @example PWM0_ClockSource(PWM1,128);
  */
void PWM123_ClockSource(unsigned char u8PWMNum, unsigned char u8PWMCLKDIV)
{
_push_(SFRS);
    switch (u8PWMNum)
    {
      case PWM1: 
        switch (u8PWMCLKDIV)
        {
            case 1:    PWM1_CLOCK_DIV_1; break;
            case 2:    PWM1_CLOCK_DIV_2; break;
            case 4:    PWM1_CLOCK_DIV_4; break;
            case 8:    PWM1_CLOCK_DIV_8; break;
            case 16:   PWM1_CLOCK_DIV_16; break;
            case 32:   PWM1_CLOCK_DIV_32; break;
            case 64:   PWM1_CLOCK_DIV_64; break;
            case 128:  PWM1_CLOCK_DIV_128; break;
        }
      break;
      case PWM2:
        switch (u8PWMCLKDIV)
        {
            case 1:    PWM2_CLOCK_DIV_1; break;
            case 2:    PWM2_CLOCK_DIV_2; break;
            case 4:    PWM2_CLOCK_DIV_4; break;
            case 8:    PWM2_CLOCK_DIV_8; break;
            case 16:   PWM2_CLOCK_DIV_16; break;
            case 32:   PWM2_CLOCK_DIV_32; break;
            case 64:   PWM2_CLOCK_DIV_64; break;
            case 128:  PWM2_CLOCK_DIV_128; break;
        }
      break;
      case PWM3:
        switch (u8PWMCLKDIV)
        {
            case 1:    PWM3_CLOCK_DIV_1; break;
            case 2:    PWM3_CLOCK_DIV_2; break;
            case 4:    PWM3_CLOCK_DIV_4; break;
            case 8:    PWM3_CLOCK_DIV_8; break;
            case 16:   PWM3_CLOCK_DIV_16; break;
            case 32:   PWM3_CLOCK_DIV_32; break;
            case 64:   PWM3_CLOCK_DIV_64; break;
            case 128:  PWM3_CLOCK_DIV_128; break;
        }
      break;
      }
_pop_(SFRS);
}

 /**
 * @brief This function config PWM generator 
 * @param[in] u8PWMNum PWM module.
                   - \ref  PWM1 \ PWM2 \ PWM3 
 * @param[in] u8ChannelNum PWM channel number. Valid values are between 0~1
 * @param[in] u16PWMFrequency Target generator frequency, note the actually PWM period is 16bit value. from 0x0000 ~ 0xFFFF
 * @param[in] u16DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return none
 * @note  none
 * @example PWM123_ConfigOutputChannel(PWM1,0,0x6FF,10);
 * @example PWM123_ConfigOutputChannel(PWM1,1,0x6FF,20);
  */
void PWM123_ConfigOutputChannel(unsigned char u8PWMNum,
                                unsigned char u8PWMChannelNum,
                                unsigned int u16PWMFrequency,
                                unsigned int u16PWMDutyCycle)
{
_push_(SFRS);
  SFRS = 2;
  switch (u8PWMNum)
  {
    case PWM1:
      switch (u8PWMChannelNum)
      {
          case 0:  PWM1C0H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM1C0L=(u16PWMFrequency*u16PWMDutyCycle/100);break;
          case 1:  PWM1C1H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM1C1L=(u16PWMFrequency*u16PWMDutyCycle/100);break;
      }
      PWM1PH = u16PWMFrequency>>8;
      PWM1PL = u16PWMFrequency;
      break;
    case PWM2:
      switch (u8PWMChannelNum)
      {
          case 0:  PWM2C0H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM2C0L=(u16PWMFrequency*u16PWMDutyCycle/100);break;
          case 1:  PWM2C1H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM2C1L=(u16PWMFrequency*u16PWMDutyCycle/100);break;
      }
      PWM2PH = u16PWMFrequency>>8;
      PWM2PL = u16PWMFrequency;
    break;
    case PWM3:
      switch (u8PWMChannelNum)
      {
          case 0:  PWM3C0H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM3C0L=(u16PWMFrequency*u16PWMDutyCycle/100);break;
          case 1:  PWM3C1H=(u16PWMFrequency*u16PWMDutyCycle/100)>>8;PWM3C1L=(u16PWMFrequency*u16PWMDutyCycle/100);break;
      }
      PWM3PH = u16PWMFrequency>>8;
      PWM3PL = u16PWMFrequency;
    break;
  }
_pop_(SFRS);
}

/**
* @brief This function action all PWM1 run
* @param[in] none
* @return none
* @note        
* @example PWM1_RUN();
*/
void PWM123_RUN(unsigned char u8PWM123Sel)
{
  switch (u8PWM123Sel)
  {
    case PWM1: set_PWM1CON0_LOAD;set_PWM1CON0_PWMRUN; break;
    case PWM2: set_PWM2CON0_LOAD;set_PWM2CON0_PWMRUN; break;
    case PWM3: set_PWM3CON0_LOAD;set_PWM3CON0_PWMRUN; break;
    case PWM1+PWM2+PWM3:
               set_PWM1CON0_LOAD;set_PWM1CON0_PWMRUN;
               set_PWM2CON0_LOAD;set_PWM2CON0_PWMRUN;
               set_PWM3CON0_LOAD;set_PWM3CON0_PWMRUN; break;
  }
}


