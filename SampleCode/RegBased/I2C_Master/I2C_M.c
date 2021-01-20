/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/29/2020                                                        
//***********************************************************************************************************


#include "ML51.h"
//***********************************************************************************************************
//  File Function: ML51 I2C master mode demo code, the Slave address = 0xA4
//
//   ____________            _____________ 
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  |ML51(M)     |          | ML51(S)     |
//  |(I2C_Master)|          | (I2C_Slave) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
//  The protocol of I2C is master: start -> write 10 byte(ACK) ->stop -> start ->read 10 byte(ACK) -> stop
//***********************************************************************************************************

/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function 

#define I2C_CLOCK                 13
#define I2C_SLAVE_ADDRESS         0xA4
#define I2C_WR                    0
#define I2C_RD                    1

#define LOOP_SIZE                 10

//========================================================================================================
void Init_I2C(void)
{
    MFP_P25_I2C0_SCL;
    P25_OPENDRAIN_MODE;          // Modify SCL pin to Open drain mode. don't forget the pull high resister in circuit
    MFP_P24_I2C0_SDA;
    P24_OPENDRAIN_MODE;          // Modify SDA pin to Open drain mode. don't forget the pull high resister in circuit

    SFRS = 0;
    /* Set I2C clock rate */
    I2C0CLK = I2C_CLOCK; 

    /* Enable I2C */
    set_I2C0CON_I2CEN;                                   
}
//========================================================================================================
void I2C_Error(void)
{
    while (1);    
}
//========================================================================================================

//--------------------------------------------------------------------------------------------
//----  Page Write----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void I2C_Write_Process(UINT8 u8DAT)
{
    unsigned char  u8Count;
    /* Write Step1 */
    set_I2C0CON_STA;                                    /* Send Start bit to I2C EEPROM */
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));                                /*Check SI set or not  */
    if (I2C0STAT != 0x08)                         /*Check status value after every step   */
        I2C_Error();
    
    /* Write Step2 */
    clr_I2C0CON_STA;                                    /*STA=0*/
    I2C0DAT = (I2C_SLAVE_ADDRESS | I2C_WR);
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));                                /*Check SI set or not */
    if (I2C0STAT != 0x18)              
        I2C_Error();

    /* Write Step3 */
    for (u8Count = 0; u8Count < LOOP_SIZE; u8Count++)
    {
        I2C0DAT = u8DAT;
        clr_I2C0CON_SI;
        while (!(I2C0CON&SET_BIT3));                            /*Check SI set or not*/
        if (I2C0STAT != 0x28)
            I2C_Error();

        u8DAT = ~u8DAT;
    }

    /* Write Step4 */
    set_I2C0CON_STO;
    clr_I2C0CON_SI;
    while (I2C0CON&SET_BIT4);                                /* Check STOP signal */
}
  
//--------------------------------------------------------------------------------------------
//----  Page Read ----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void I2C_Read_Process(UINT8 u8DAT)
{
    unsigned char  u8Count;
    /* Read Step1 */
    set_I2C0CON_STA;
    clr_I2C0CON_SI;          
    while (!(I2C0CON&SET_BIT3));                                //Check SI set or not
    if (I2C0STAT != 0x08)                         //Check status value after every step
        I2C_Error();

    /* Step13 */
    clr_I2C0CON_STA;                                    //STA needs to be cleared after START codition is generated
    I2C0DAT = (I2C_SLAVE_ADDRESS | I2C_RD);
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));                                //Check SI set or not
    if (I2C0STAT != 0x40)
        I2C_Error();
    
    /* Step14 */
    for (u8Count = 0; u8Count <LOOP_SIZE; u8Count++)
    {
        set_I2C0CON_AA;
        clr_I2C0CON_SI;        
        while (!(I2C0CON&SET_BIT3));                            //Check SI set or not

        if (I2C0STAT != 0x50)              
            I2C_Error();
        
        if (I2C0DAT != u8DAT)             
            I2C_Error();
        u8DAT = ~u8DAT; 
    } 
    
    /* Step15 */
    clr_I2C0CON_AA;
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));                                //Check SI set or not
    if (I2C0STAT != 0x58)
        I2C_Error();

    /* Step16 */
    set_I2C0CON_STO;
    clr_I2C0CON_SI;
    while (I2C0CON&SET_BIT4);                                /* Check STOP signal */ 
}
//========================================================================================================
void main(void)
{
    /* Note
       MCU power on system clock is HIRC (22.1184MHz), so Fsys = 22.1184MHz
    */
/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */

#ifdef print_function 
    Enable_UART0_VCOM_printf();
    printf ("\n i2c initial ");
#endif
    Init_I2C();                                 /* initial I2C circuit  */
    I2C_Write_Process(0x55);                          /* I2C Master will send 10 byte 0x55,0xAA,.... to slave */
    I2C_Read_Process(0x55);
    printf ("\n i2c test pass ");
    while (1);
/* =================== */
}

