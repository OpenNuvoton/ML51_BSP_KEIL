/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/29/2020
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: ML51 
//***********************************************************************************************************
#include "ML51.h"

//***********************************************************************************************************
//  File Function: ML51 I2C demo code, Slave Address of 24LC64 = 0xA0
//
//   ____________           ______________ 
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  | MS56(M)    |          |   24LC64(S) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
//  Microchip I2C EEPROM 24xx64 (64K Bit) is used as the slave device.  
//  The page size are 32Byte. Total are 256 page.
//  If verification passes, Port3 will show 0x78. If there is any failure
//  occured during the progress, Port3 will show 0x00.
//***********************************************************************************************************

/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function 


#define I2C_CLOCK               2
#define EEPROM_SLA              0xA0
#define EEPROM_WR               0
#define EEPROM_RD               1
#define EEPROM_PAGE_SIZE        32
#define PAGE_NUMBER             4
#define ERROR_CODE              0x78
#define TEST_OK                 0x00

bit I2C_Reset_Flag;
//========================================================================================================
void Init_I2C(void)
{
      MFP_P25_I2C0_SCL;
      P25_OPENDRAIN_MODE;     /*I2C_SCL*/ 
      MFP_P24_I2C0_SDA;
      P24_OPENDRAIN_MODE;     /*I2C_SDA*/

    /* Set I2C clock rate */
    SFRS = 0;
    I2C0CLK = I2C_CLOCK; 
    /* Enable I2C */
    set_I2C0CON_I2CEN;
}
//========================================================================================================
void I2C_SI_Check(void)
{
    if (I2C0STAT == 0x00)
    {
        I2C_Reset_Flag = 1;
        set_I2C0CON_STO;
        clr_I2C0CON_SI;
        if(I2C0CON|CLR_BIT3)
        {
            clr_I2C0CON_I2CEN;
            set_I2C0CON_I2CEN;
            clr_I2C0CON_SI;
            clr_I2C0CON_I2CEN;    
        }   
    }  
}

void One_Page_Read(unsigned char u8PageNumber,unsigned char u8DAT)
{
    unsigned char  u8Count;
    unsigned int u16Address;

    u16Address = (unsigned int)u8PageNumber*32;

    /* Step1 */
    set_I2C0CON_STA;                                /* Send Start bit to I2C EEPROM */
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send STA' error");
#endif
        goto Read_Error_Stop;
    }

    /* Step2 */
    I2C0DAT = (EEPROM_SLA | EEPROM_WR);       /* Send (SLA+W) to EEPROM */
    clr_I2C0CON_STA;                                /* Clear STA and Keep SI value in I2C0CON */    
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */              
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send SLA+W' error");
#endif
        goto Read_Error_Stop;
    }

    /* Step3 */
    I2C0DAT = HIBYTE(u16Address);             /* Send I2C EEPROM's High Byte Address */
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */              
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send I2C High Byte Address' error");
#endif
        goto Read_Error_Stop;
    }

    /* Step4 */
    I2C0DAT = LOBYTE(u16Address);             /* Send I2C EEPROM's Low Byte Address */
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */             
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send I2C Low Byte Address' error");
#endif
        goto Read_Error_Stop;
    }

    /* Step5 */
    set_I2C0CON_STA;                          /* Repeated START */
    clr_I2C0CON_SI; 
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x10)                     /* 0x10: A repeated START condition has been transmitted */
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send STA' error");
#endif
        goto Read_Error_Stop;
    }

    /* Step6 */
    clr_I2C0CON_STA;                          /* Clear STA and Keep SI value in I2C0CON */
    I2C0DAT = (EEPROM_SLA | EEPROM_RD);       /* Send (SLA+R) to EEPROM */
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x40)                     /* 0x40:  SLA+R has been transmitted; ACK has been received */              
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send SLA+R' error");
#endif
        goto Read_Error_Stop;
    }

    /* Step7 */                              /* Verify I2C EEPROM data */
    for (u8Count = 0; u8Count <EEPROM_PAGE_SIZE; u8Count++)
    {
        set_I2C0CON_AA;                      /* Set Assert Acknowledge Control Bit */
        clr_I2C0CON_SI;
        while (!(I2C0CON&SET_BIT3));
        if (I2C0STAT != 0x50)                /* 0x50:Data byte has been received; NOT ACK has been returned */              
        {
            I2C_Reset_Flag = 1;
#ifdef print_function
            printf("\nI2C 'No Ack' error");
#endif
            goto Read_Error_Stop;
        }
       
        if (I2C0DAT != u8DAT)                 /* Send the Data to EEPROM */    
        {
            I2C_Reset_Flag = 1;
#ifdef print_function
            printf("\nI2C 'Read data' error");
#endif
            goto Read_Error_Stop;
        }
        u8DAT = ~u8DAT; 
    }

    /* Step8 */
    clr_I2C0CON_AA;                           /* Send a NACK to disconnect 24xx64 */
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x58)                     /* 0x58:Data byte has been received; ACK has been returned */
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Ack' error");
#endif
        goto Read_Error_Stop;
    }
    
  /* Step9 */    
    clr_I2C0CON_SI;
    set_I2C0CON_STO;
    while (I2C0CON|CLR_BIT4)                  /* Check STOP signal */
    {
      I2C_SI_Check();
      if (I2C_Reset_Flag)
        goto Read_Error_Stop;
    }
    
Read_Error_Stop: 
    if (I2C_Reset_Flag)
    {
        I2C_SI_Check();
#ifdef print_function
        printf("\nI2C Read error, test stop");
#endif
        I2C_Reset_Flag = 0;
    }
}
//========================================================================================================
void One_Page_Write(unsigned char u8PageNumber,unsigned char u8DAT)
{
    unsigned char  u8Count;
    unsigned int u16Address;

    u16Address = (unsigned int)u8PageNumber*32;

    /* Step1 */
    set_I2C0CON_STA;                          /* Send Start bit to I2C EEPROM */         
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send STA' error");
#endif
        goto Write_Error_Stop;
    }

    /* Step2 */
    clr_I2C0CON_STA;                          /* Clear STA and Keep SI value in I2C0CON */
    I2C0DAT = EEPROM_SLA | EEPROM_WR;         /* Send (SLA+W) to EEPROM */
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */             
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send SLA+W' error");
#endif
        goto Write_Error_Stop;
    }

    /* Step3 */
    I2C0DAT = HIBYTE(u16Address);             /* Send EEPROM's High Byte Address */
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send High byte address' error");
#endif
        goto Write_Error_Stop;
    }

    /* Step4 */
    I2C0DAT = LOBYTE(u16Address);             /* Send EEPROM's Low Byte Address */
    clr_I2C0CON_SI;
    while (!(I2C0CON&SET_BIT3));
    if (I2C0STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        I2C_Reset_Flag = 1;
#ifdef print_function
        printf("\nI2C 'Send Low byte address' error");
#endif
        goto Write_Error_Stop;
    }

    /* Step5 */
                                              /* Write data to I2C EEPROM */
    for (u8Count = 0; u8Count < EEPROM_PAGE_SIZE; u8Count++)
    {
        I2C0DAT = u8DAT;                      /* Send data to EEPROM */
        clr_I2C0CON_SI;
        while (!(I2C0CON&SET_BIT3));
        if (I2C0STAT != 0x28)                 /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
        {
            I2C_Reset_Flag = 1;
#ifdef print_function
            printf("\nI2C 'Write Data' error");
#endif
            goto Write_Error_Stop;
        }   
        u8DAT = ~u8DAT;        
    }
  /*After STOP condition, a inner EEPROM timed-write-cycle 
  /*will occure and EEPROM will not response to outside command
  /* 0x18: SLA+W has been transmitted; ACK has been received */
    /* Step6 */
    do
    {
        set_I2C0CON_STO;                    /* Set I2C STOP Control Bit */
        clr_I2C0CON_SI;
        while (I2C0CON|CLR_BIT4)            /* Check STOP signal */
        {
          I2C_SI_Check();
          if (I2C_Reset_Flag)
            goto Write_Error_Stop;
        }
        
        set_I2C0CON_STA;                      /* Check if no ACK is returned by EEPROM, it is under timed-write cycle */
        clr_I2C0CON_SI;
        while (!(I2C0CON&SET_BIT3));
        if (I2C0STAT != 0x08)                 /* 0x08:  A START condition has been transmitted*/
        {
            I2C_Reset_Flag = 1;
#ifdef print_function
            printf("\nI2C 'Wait Ready' error");
#endif
            goto Write_Error_Stop;
        }

        clr_I2C0CON_STA;                      /* Clear STA and Keep SI value in I2C0CON */
        I2C0DAT = (EEPROM_SLA | EEPROM_WR);   /* Send (SLA+W) to EEPROM */
        clr_I2C0CON_SI;
        while (!(I2C0CON&SET_BIT3));
    }while(I2C0STAT != 0x18);

    /* Step7 */
    set_I2C0CON_STO;                          /* Set STOP Bit to I2C EEPROM */
    clr_I2C0CON_SI;
    while (I2C0CON|CLR_BIT4)                  /* Check STOP signal */
    {
      I2C_SI_Check();
      if (I2C_Reset_Flag)
        goto Write_Error_Stop;
    }
    
Write_Error_Stop: 
    if (I2C_Reset_Flag)
    {
        I2C_SI_Check();
        I2C_Reset_Flag  = 0;
#ifdef print_function
        printf("\nI2C Write error, test stop");
#endif
    }
    
    
}
//========================================================================================================
void main(void)
{

#ifdef print_function
  /* UART0 initial setting
  ** include uart.c in Library for UART initial setting
  **UART0 define P3.1 TXD multi function setting
  **/
  Enable_UART0_VCOM_printf();
  printf("\n I2C read EEPROM intial...");
#endif

    /* Initial I2C function */
    Init_I2C();                                 //initial I2C circuit
    
    /* page0 R/W */
#ifdef print_function
    printf ("\n\n24LC64 Page0 Write (0x55,0xAA...)...");
#endif
    One_Page_Write(0,0x55);                     //page0, write 0x55,0xAA,........

#ifdef print_function
    printf ("\n\n24LC64 Page0 Read...");
#endif
    One_Page_Read (0,0x55);                     //page0, read  0x55,0xAA,........

    /* page1 R/W */
#ifdef print_function
    printf ("\n\n24LC64 Page1 Write (0x00,0xFF...)...");
#endif
    One_Page_Write(1,0x00);                     //page1, write 0x00,0xFF,........
#ifdef print_function
    printf ("\n\n24LC64 Page1 Read...");
#endif
    One_Page_Read (1,0x00);                     //page1, read  0x00,0xFF,........

    /* page2 R/W */
#ifdef print_function
    printf ("\n\n24LC64 Page2 Write (0xAA,0x55...)...");
#endif
    One_Page_Write(2,0xAA);                     //page2, write 0xAA,0x55,........
#ifdef print_function
    printf ("\n\n24LC64 Page2 Read...");
#endif
    One_Page_Read (2,0xAA);                     //page2, read  0xAA,0x55,........

    /* page3 R/W */
#ifdef print_function
    printf ("\n\n24LC64 Page3 Write (0xFF,0x00...)...");
#endif
    One_Page_Write(3,0xFF);                     //page3, write 0xFF,0x00,........
#ifdef print_function
    printf ("\n\n24LC64 Page3 Read...");
#endif
    One_Page_Read (3,0xFF);                     //page3, read  0xFF,0x00,........

    /* page255 R/W */
#ifdef print_function
    printf ("\n\n24LC64 Page255 Write (0x0F,0xF0...)...");
#endif
    One_Page_Write(255,0x0F);                   //page255, write 0x0F,0xF0,........
#ifdef print_function
    printf ("\n\n24LC64 Page255 Read...");
#endif
    One_Page_Read (255,0x0F);                   //page255, read  0x0F,0xF0,........

    /* ==== Test Pass ==== */      
#ifdef print_function
    printf ("\n\ML51 <--> 24LC64, I2C Demo Code test pass...");
#endif

    while (1);
/* =================== */
}

