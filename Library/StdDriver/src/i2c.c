/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "ML51.h"

/**
  * @brief      Enable specify I2C controller and set divider
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @param[in]  u32SYSCLK: Define Fsys clock value in Hz.
  *                  - \ref 8000000
  * @param[in]  u32I2CCLK: The target I2C bus clock in Hz. Use HIRC the I2C clock is from 23473 ~ 2000000
  * @return     None
  * @details    The function enable the specify I2C controller and set proper clock divider
  *             in I2C CLOCK DIVIDED REGISTER (I2CLK) according to the target I2C Bus clock.
  *             I2C bus clock = PCLK / (4*(u32I2CCLK+1).
  * @exmaple :  I2C_Open(I2C0,24000000,100000);
  */
void I2C_Master_Open(unsigned char u8I2CSel, unsigned long u32SYSCLK, unsigned long u32I2CCLK)
{
    SFRS = 0x00;
    switch (u8I2CSel)
    {
      case I2C0: I2C0CLK = (u32SYSCLK/4/u32I2CCLK-1); set_I2C0CON_I2CEN; break;
      case I2C1: I2C1CLK = (u32SYSCLK/4/u32I2CCLK-1); set_I2C1CON_I2CEN; break;
      default: break;
    }
}

/**
  * @brief      Enable specify I2C Slave address
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @param[in]  u32SYSCLK: Define Fsys clock value in Hz.
  *                  - \ref 8000000
  * @param[in]  u32I2CCLK: The target I2C bus clock in Hz. Use HIRC the I2C clock is from 23473 ~ 2000000
  * @return     None
  * @details    The function enable the specify I2C controller and set proper clock divider
  *             in I2C CLOCK DIVIDED REGISTER (I2CLK) according to the target I2C Bus clock.
  *             I2C bus clock = PCLK / (4*(u32I2CCLK+1).
  * @exmaple :  I2C_Open(I2C0,24000000,100000);
  */
void I2C_Slave_Open(unsigned char u8I2CSel, unsigned char u8SlaveAddress0, unsigned char u8SlaveAddress1, unsigned char u8SlaveAddress2, unsigned char u8SlaveAddress3)
{

    switch (u8I2CSel)
    {
      case I2C0: 
        SFRS = 0; 
        I2C0ADDR0 = u8SlaveAddress0; 
        SFRS = 2; 
        I2C0ADDR1 = u8SlaveAddress1; 
        I2C0ADDR2 = u8SlaveAddress2; 
        I2C0ADDR3 = u8SlaveAddress3;
        set_I2C0CON_I2CEN;      
        set_I2C0CON_AA;
      break;
      case I2C1: 
        SFRS = 0;
        I2C1ADDR0 = u8SlaveAddress0; 
        SFRS = 2; 
        I2C1ADDR1 = u8SlaveAddress1; 
        I2C1ADDR2 = u8SlaveAddress2; 
        I2C1ADDR3 = u8SlaveAddress3;
        set_I2C1CON_I2CEN;
        set_I2C1CON_AA;
      break;
      default: break;

    }
}
/**
  * @brief      Disable I2C function
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @exmaple :  I2C0_Close(I2C0);
*/
void I2C_Close(unsigned char u8I2CSel)
{
    SFRS = 0;
    switch (u8I2CSel)
    {
      case I2C0: clr_I2C0CON_I2CEN; break;
      case I2C1: clr_I2C1CON_I2CEN; break;
      default: break;
    }
}

/**
  * @brief      Enable specify I2C controller interrupt, also need enable globle interrupt in main loop.
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @param[in]  u8I2CStatus:  Specify I2C interrupt status
  *                  - \ref Enable
  *                  - \ref Disable
  * @exmaple :  I2C_Interrupt(I2C0, Enable);
*/
void I2C_Interrupt(unsigned char u8I2CSel,unsigned char u8I2CStatus)
{
    SFRS = 0;
    switch (u8I2CSel)
    {
      case I2C0: 
         switch (u8I2CStatus)
         {
           case Enable: set_EIE0_EI2C0; break;
           case Disable: clr_EIE0_EI2C0; break;
         }
      break;
      case I2C1:
        switch (u8I2CStatus)
        {
          case Enable: set_EIE1_EI2C1; break;
           case Disable: clr_EIE1_EI2C1; break;
        }
      break;
      default: break;
    }
}

/**
  * @brief      Get I2C bus status value
  * @param[in]  u8I2CSel:  Specify I2C port
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @return     I2C status data 
  * @exmaple :  I2C_GetStatus(I2C0);
*/
unsigned char I2C_GetStatus(unsigned char u8I2CSel)
{
    unsigned char u8i2cstat;
    SFRS = 0;
    switch (u8I2CSel)
    {
      case I2C0: u8i2cstat=I2C0STAT; break;
      case I2C1: u8i2cstat=I2C1STAT; break;
      default: break;
    }
    return (u8i2cstat);
}

/**
  * @brief      Configure the mask bits of 7-bit Slave Address
  * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @param[in]  u8SlaveNo        Set the number of I2C address mask register (0~3)
  *                  - \ref 0
  *                  - \ref 1
  *                  - \ref 2
  *                  - \ref 3
  * @param[in]  u8SlaveAddrMask  A byte for slave address mask
  * @return     None
  * @details    This function is used to set 7-bit slave addresses.
  * @example    I2C_SetSlaveAddrMask(I2C0,0,0x33);
 */
void I2C_SetSlaveAddrMask(unsigned char u8I2CSel, unsigned char u8SlaveNo, unsigned char u8SlaveAddrMask)
{
    switch (u8I2CSel)
    {
      case I2C0: 
        switch (u8SlaveNo)
        {
          case 0: SFRS=0;I2C0ADDR0=u8SlaveAddrMask; break;
          case 1: SFRS=2;I2C0ADDR1=u8SlaveAddrMask; break;
          case 2: SFRS=2;I2C0ADDR2=u8SlaveAddrMask; break;
          case 3: SFRS=2;I2C0ADDR3=u8SlaveAddrMask; break;
        }
      case I2C1:
        switch (u8SlaveNo)
        {
          case 0: SFRS=0;I2C1ADDR0=u8SlaveAddrMask; break;
          case 1: SFRS=2;I2C1ADDR1=u8SlaveAddrMask; break;
          case 2: SFRS=2;I2C1ADDR2=u8SlaveAddrMask; break;
          case 3: SFRS=2;I2C1ADDR3=u8SlaveAddrMask; break;
        }      
      break;
      }
}

/**
 * @brief      Enable Time-out Function with support long time-out
 * @param[in]  u8I2CSel:  Specify I2C port
  *                  - \ref I2C0
  *                  - \ref I2C1
  * @param[in]  u8I2CTRStatus:  Specify I2C Timer status
  *                  - \ref Enable
  *                  - \ref Disable
 * @return     None
 * @Note       This function enable time-out function and configure DIV4 to support longer time-out.
 * @example    I2C_Timeout(I2C0,Enable);
 */
void I2C_Timeout(unsigned char u8I2CSel, unsigned char u8I2CTRStatus )
{
_push_(SFRS);

    SFRS = 0;
    switch (u8I2CSel)
    {
      case I2C0:
        switch (u8I2CTRStatus)
        {
          case Enable: set_I2C0TOC_DIV; set_I2C0TOC_I2TOCEN; break;
          case Disable: clr_I2C0TOC_I2TOCEN; break;
        }
      break;
      case I2C1: 
        switch (u8I2CTRStatus)
        {
          case Enable: set_I2C1TOC_DIV; set_I2C1TOC_I2TOCEN; break;
          case Disable: clr_I2C1TOC_I2TOCEN; break;
        }
      default: break;
      break;
    }
_pop_(SFRS);
}


void I2C_ClearTimeoutFlag(unsigned char u8I2CSel)
{
    SFRS = 0;
    switch (u8I2CSel)
    {
      case I2C0: I2C0TOC&=0xFE; break;
      case I2C1: I2C1TOC&=0xFE; break;
      default: break;
    }
}

/**
 * @brief      I2C slave address mask function enable / disable.
 * @param[in]  u8I2CSel:  Specify I2C port
 * @param[in]  u8I2CAddMaskBit: I2C slave address mask bit define
 * @return     None
 * @details    This function setting the slave address mask bit.
 *
 */
void I2C_Slave_Address_Mask(unsigned char u8I2CSel, unsigned char u8I2CAddMaskStatus, unsigned char u8I2CAddMaskBit)
{
    SFRS=2;
    switch (u8I2CSel)
    {
      case I2C0:
        switch (u8I2CAddMaskStatus)
        {
          case Enable:  I2C0ADDRM|=u8I2CAddMaskBit; break;
          case Disable: I2C0ADDRM&=~u8I2CAddMaskBit; break;
        }
      break;
      case I2C1:
        switch (u8I2CAddMaskStatus)
        {
          case Enable: I2C1ADDRM|=u8I2CAddMaskBit; break;
          case Disable:I2C1ADDRM=~u8I2CAddMaskBit; break;
        }
      default: break;
    }
}

/**
 * @brief      Special design for 8051 I2C SI check
 * @param[in]  none
 * @return     None
 * @details    This function setting the slave address mask bit.
 */
void I2C0_SI_Check(void)
{
    clr_I2C0CON_SI;
    
    while(I2C0CON&SET_BIT3)     /* while SI==0; */
    {
        if(I2C0STAT == 0x00)
        {
            set_I2C0CON_STO;
        }
        SI0 = 0;
        if(!SI0)
        {
            clr_I2C0CON_I2CEN;
            set_I2C0CON_I2CEN;
            clr_I2C0CON_SI;
        } 
    }
}
