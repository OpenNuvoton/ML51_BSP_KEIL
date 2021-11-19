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

 /**
  * @brief GPIO Mode setting
  * @param[in] u8Port Decides the GPIO port number Port0 ~ Port5
  * @param[in] u8Port Decides the GPIO port number Port0 ~ Port5
  *                  - \ref Port 0
  *                  - \ref Port 1
  *                  - \ref Port 2
  *                  - \ref Port 3
  *                  - \ref Port 4
  *                  - \ref Port 5
  *                  - \ref Port 6
  * @param[in] u8PinMask Decides  bit of the port (SET_BIT0~SET_BIT7 use "|" to define multi bit).
  *                  - \ref SET_BIT0
  *                  - \ref SET_BIT1
  *                  - \ref SET_BIT2
  *                  - \ref SET_BIT3
  *                  - \ref SET_BIT4
  *                  - \ref SET_BIT5
  *                  - \ref SET_BIT6
  *                  - \ref SET_BIT7
  *                  - \ref SET_BIT0|SET_BIT7
  * @param[in] u8Mode Decides the GPIO mode to select.
  *                  - \ref GPIO_MODE_INPUT
  *                  - \ref GPIO_MODE_PUSHPULL
  *                  - \ref GPIO_MODE_QUASI
  *                  - \ref GPIO_MODE_OPENDRAI
  * @return  None
  * @note Confirm multi function pin is defined as GPIO first. call function_define_ML51.h to define.
  * @exmaple :   GPIO_SetMode(Port1, BIT0|BIT7, GPIO_MODE_QUASI);
  */
void GPIO_SetMode(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8Mode)
{
    unsigned char u8PnM1, u8PnM2;

    SFRS = 1;
    switch(u8Port)
    {
        case Port0:  u8PnM1 = P0M1;  u8PnM2 = P0M2;  break;
        case Port1:  u8PnM1 = P1M1;  u8PnM2 = P1M2;  break;
        case Port2:  u8PnM1 = P2M1;  u8PnM2 = P2M2;  break;
        case Port3:  u8PnM1 = P3M1;  u8PnM2 = P3M2;  break;
        case Port4:  u8PnM1 = P4M1;  u8PnM2 = P4M2;  break;
        case Port5:  u8PnM1 = P5M1;  u8PnM2 = P5M2;  break;
        case Port6:  SFRS=2; u8PnM1 = P6M1;  u8PnM2 = P6M2;  break;
    }
    switch(u8Mode)
    {
        case GPIO_MODE_QUASI:
            u8PnM1 &= ~u8PinMask;
            u8PnM2 &= ~u8PinMask;
            break;
        case GPIO_MODE_PUSHPULL:
            u8PnM1 &= ~u8PinMask;
            u8PnM2 |= u8PinMask;
            break;
        case GPIO_MODE_INPUT:
            u8PnM1 |= u8PinMask; 
            u8PnM2 &= ~u8PinMask;
            break;
        case GPIO_MODE_OPENDRAIN:
            u8PnM1 |= u8PinMask;
            u8PnM2 |= u8PinMask;
            break;
    }
    switch(u8Port)
    {
        case Port0:  P0M1 = u8PnM1;  P0M2 = u8PnM2;  break;
        case Port1:  P1M1 = u8PnM1;  P1M2 = u8PnM2;  break;
        case Port2:  P2M1 = u8PnM1;  P2M2 = u8PnM2;  break;
        case Port3:  P3M1 = u8PnM1;  P3M2 = u8PnM2;  break;
        case Port4:  P4M1 = u8PnM1;  P4M2 = u8PnM2;  break;
        case Port5:  P5M1 = u8PnM1;  P5M2 = u8PnM2;  break;
        case Port6:  SFRS=2;P6M1 = u8PnM1;  P6M2 = u8PnM2;  break;
    }
}

/**
  * @brief GPIO Pull up or Pull down enable setting
  * @param[in] u8Port Decides the GPIO port number Port0 ~ Port5
  *                  - \ref Port 0
  *                  - \ref Port 1
  *                  - \ref Port 2
  *                  - \ref Port 3
  *                  - \ref Port 4
  *                  - \ref Port 5
  *                  - \ref Port 6
  * @param[in] u8PinMask Decides  bit of the port (SET_BIT0~SET_BIT7 use "|" to define multi bit).
  *                  - \ref SET_BIT0
  *                  - \ref SET_BIT1
  *                  - \ref SET_BIT2
  *                  - \ref SET_BIT3
  *                  - \ref SET_BIT4
  *                  - \ref SET_BIT5
  *                  - \ref SET_BIT6
  *                  - \ref SET_BIT7
  *                  - \ref SET_BIT0|SET_BIT7
  * @param[in] u8PullMode Decides the GPIO Pull up or pull down (PullUp/PullDown)
  *                  - \ref PULLUP
  *                  - \ref PULLDOWN
  * @return  None
  * @note none
  * @exmaple :   GPIO_Pull_Enable(Port1, BIT0|BIT5|BIT7, PullUp);
  */
void GPIO_Pull_Enable(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8PullMode)
{
  SFRS=1;
  switch (u8PullMode)
  {
    case PULLUP:
        switch(u8Port)
        {
          case Port0:  P0UP |= u8PinMask;  break;
          case Port1:  P1UP |= u8PinMask;  break;
          case Port2:  P2UP |= u8PinMask;  break;
          case Port3:  P3UP |= u8PinMask;  break;
          case Port4:  P4UP |= u8PinMask;  break;
          case Port5:  P5UP |= u8PinMask;  break;
          case Port6:  SFRS=2;P6UP |= u8PinMask;  break;
        }
    break;
    case PULLDOWN:
        switch(u8Port)
        {
          case Port0:  P0DW |= u8PinMask;  break;
          case Port1:  P1DW |= u8PinMask;  break;
          case Port2:  P2DW |= u8PinMask;  break;
          case Port3:  P3DW |= u8PinMask;  break;
          case Port4:  P4DW |= u8PinMask;  break;
          case Port5:  P5DW |= u8PinMask;  break;
          case Port6:  SFRS=2;P5DW |= u8PinMask;  break;
        }
    break;
    }
}


 /**
  * @brief GPIO Pull up or Pull down disable 
  * @param[in] u8Port Decides the GPIO port number Port0 ~ Port5
  *                  - \ref Port 0
  *                  - \ref Port 1
  *                  - \ref Port 2
  *                  - \ref Port 3
  *                  - \ref Port 4
  *                  - \ref Port 5
  *                  - \ref Port 6
  * @param[in] u8PinMask Decides  bit of the port (SET_BIT0~SET_BIT7 use "|" to define multi bit).
  *                  - \ref SET_BIT0
  *                  - \ref SET_BIT1
  *                  - \ref SET_BIT2
  *                  - \ref SET_BIT3
  *                  - \ref SET_BIT4
  *                  - \ref SET_BIT5
  *                  - \ref SET_BIT6
  *                  - \ref SET_BIT7
  *                  - \ref SET_BIT0|SET_BIT7
  * @param[in] u8PullMode Decides the GPIO Pull up or pull down (PullUp/PullDown)
  *                  - \ref PULLUP
  *                  - \ref PULLDOWN
  * @return  None
  * @note none
  * @exmaple :   GPIO_Pull_Enable(P1,BIT0|BIT5,PullUp);
  */
void GPIO_Pull_Disable(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8PullMode)
{
  SFRS=1;
  switch (u8PullMode)
  {
    case PULLUP:
        switch(u8Port)
        {
          case Port0:  P0UP &= ~u8PinMask;  break;
          case Port1:  P1UP &= ~u8PinMask;  break;
          case Port2:  P2UP &= ~u8PinMask;  break;
          case Port3:  P3UP &= ~u8PinMask;  break;
          case Port4:  P4UP &= ~u8PinMask;  break;
          case Port5:  P5UP &= ~u8PinMask;  break;
          case Port6:  SFRS=2;P6UP &= ~u8PinMask;  break;
        }
    break;
    case PULLDOWN:
        switch(u8Port)
        {
          case Port0:  P0DW &= ~u8PinMask;  break;
          case Port1:  P1DW &= ~u8PinMask;  break;
          case Port2:  P2DW &= ~u8PinMask;  break;
          case Port3:  P3DW &= ~u8PinMask;  break;
          case Port4:  P4DW &= ~u8PinMask;  break;
          case Port5:  P5DW &= ~u8PinMask;  break;
          case Port6:  SFRS=2;P6DW &= ~u8PinMask;  break;
        }
    break;
    }
}

 /**
  * @brief GPIO Schmitt Triggered Input enable / disable. 
  * @param[in] u8Port Decides the GPIO port number 
  *                  - \ref Port 0
  *                  - \ref Port 1
  *                  - \ref Port 2
  *                  - \ref Port 3
  *                  - \ref Port 4
  *                  - \ref Port 5
  *                  - \ref Port 6
  * @param[in] u8PinMask Decides  bit of the port (SET_BIT0~SET_BIT7 use "|" to define multi bit).
  *                  - \ref SET_BIT0
  *                  - \ref SET_BIT1
  *                  - \ref SET_BIT2
  *                  - \ref SET_BIT3
  *                  - \ref SET_BIT4
  *                  - \ref SET_BIT5
  *                  - \ref SET_BIT6
  *                  - \ref SET_BIT7
  *                  - \ref SET_BIT0|SET_BIT7
  * @param[in] u8SStauts Decides the GPIO Schmitt Triggered status
  *                  - \ref Enable
  *                  - \ref Disable
  * @return  None
  * @note none
  * @exmaple :   GPIO_Pull_Enable(P1,BIT0|BIT5,PullUp);
  */
void GPIO_SchmittTrigger(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8SStauts)
{
_push_(SFRS);
  SFRS=1;
  switch (u8SStauts)
  {
    case Enable:
        switch(u8Port)
        {
          case Port0:  P0S |= u8PinMask;  break;
          case Port1:  P1S |= u8PinMask;  break;
          case Port2:  P2S |= u8PinMask;  break;
          case Port3:  P3S |= u8PinMask;  break;
          case Port4:  P4S |= u8PinMask;  break;
          case Port5:  P5S |= u8PinMask;  break;
          case Port6:  SFRS=2; P5S |= u8PinMask;  break;
        }
    break;
    case Disable:
        switch(u8Port)
        {
          case Port0:  P0S &= ~u8PinMask;  break;
          case Port1:  P1S &= ~u8PinMask;  break;
          case Port2:  P2S &= ~u8PinMask;  break;
          case Port3:  P3S &= ~u8PinMask;  break;
          case Port4:  P4S &= ~u8PinMask;  break;
          case Port5:  P5S &= ~u8PinMask;  break;
          case Port6:  SFRS=2; P6S &= ~u8PinMask;  break;
        }
    break;
    }
_pop_(SFRS);
}

 /**
  * @brief GPIO Slew rate Status enable / disable. 
  * @param[in] u8Port Decides the GPIO port number 
  *                  - \ref Port 0
  *                  - \ref Port 1
  *                  - \ref Port 2
  *                  - \ref Port 3
  *                  - \ref Port 4
  *                  - \ref Port 5
  * @param[in] u8PinMask Decides  bit of the port (SET_BIT0~SET_BIT7 use "|" to define multi bit).
  *                  - \ref SET_BIT0
  *                  - \ref SET_BIT1
  *                  - \ref SET_BIT2
  *                  - \ref SET_BIT3
  *                  - \ref SET_BIT4
  *                  - \ref SET_BIT5
  *                  - \ref SET_BIT6
  *                  - \ref SET_BIT7
  *                  - \ref SET_BIT0|SET_BIT7
  * @param[in] u8SRStauts Decides the GPIO Slew rate status
  *                  - \ref Enable
  *                  - \ref Disable
  * @return  None
  * @note none
  * @exmaple :   GPIO_Pull_Enable(P1,BIT0|BIT5,PullUp);
  */
void GPIO_SlewRate(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8SRStauts)
{
_push_(SFRS);
  SFRS=1;
  switch (u8SRStauts)
  {
    case Enable:
        switch(u8Port)
        {
          case Port0:  P0SR |= u8PinMask;  break;
          case Port1:  P1SR |= u8PinMask;  break;
          case Port2:  P2SR |= u8PinMask;  break;
          case Port3:  P3SR |= u8PinMask;  break;
          case Port4:  P4SR |= u8PinMask;  break;
          case Port5:  P5SR |= u8PinMask;  break;
        }
    break;
    case Disable:
        switch(u8Port)
        {
          case Port0:  P0SR &= ~u8PinMask;  break;
          case Port1:  P1SR &= ~u8PinMask;  break;
          case Port2:  P2SR &= ~u8PinMask;  break;
          case Port3:  P3SR &= ~u8PinMask;  break;
          case Port4:  P4SR &= ~u8PinMask;  break;
          case Port5:  P5SR &= ~u8PinMask;  break;
        }
    break;
    }
_pop_(SFRS);
}
