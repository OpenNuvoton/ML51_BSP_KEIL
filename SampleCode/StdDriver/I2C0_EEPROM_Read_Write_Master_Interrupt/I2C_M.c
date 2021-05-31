/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2021 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/29/2021                                                        
//***********************************************************************************************************


#include "ML51.h"
//***********************************************************************************************************
//  File Function: MUG51 I2C master mode demo code, the Slave address = 0xA4
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

#define EEPROM_ADDRESS          0xA0
#define I2C_WR                     0
#define I2C_RD                     1

#define LOOP_SIZE                 10

unsigned int Tx_Addr = 0;
unsigned char Tx_Dat = 0;
unsigned int Rx_Addr = 0;
unsigned char Rx_Dat = 0;
bit Write_End_Flag = 0;
bit Read_End_Flag = 0;


void (*I2C_Func)(void);
void I2C_ISR(void) interrupt 6
{
    I2C_Func();
}

/*========================================================================================================*/
void I2C0_Master_Tx_Isr(void)
{
    static uint8_t addr_flag = 0;
    static uint8_t count = 0;

_push_(SFRS);
    SFRS = 0;
    printf ("\n I2C Transmit Interrupt" );
    printf("\n I2STAT = 0x%BD", I2C0STAT);
    switch (I2C0STAT)
    {
       /* Bus error */
       case 0x00: set_I2C0CON_STO; break;
        
      /* I2C start */
       case 0x08:
            clr_I2C0CON_STA;
            I2C0DAT = (EEPROM_ADDRESS | I2C_WR);
       break;

       /* Master Transmit Address ACK  */
       case 0x18:
            I2C0DAT = HIBYTE(Rx_Addr);          //address high byte of I2C EEPROM
            addr_flag = 1;
       break;

       /* Master Transmit Data ACK  */
       case 0x28:
            if(addr_flag)
            {
                I2C0DAT = LOBYTE(Tx_Addr);      //address low byte of I2C EEPROM
                addr_flag = 0;
                count = 0;
            }
            else
            {
                if(count == 0)
                {
                    I2C0DAT = Tx_Dat;
                    count++;
                }
                else
                {
                    Write_End_Flag = 1;
                    set_I2C0CON_STO;
                }
            }
        break;
    }

    I2C0_SI_Check();
    //while(STO);
_pop_(SFRS);
}

/*========================================================================================================*/
void I2C0_Master_Rx_Isr(void)
{
    static uint8_t addr_flag = 0;
    static uint8_t count = 0;
_push_(SFRS);

    SFRS = 0;
    printf ("\n I2C Receive Interrupt" );
    printf("\n I2STAT = 0x%BD", I2C0STAT);
    switch (I2C0STAT)
    {
       /* Bus error */
       case 0x00: set_I2C0CON_STO; break;

      /* I2C start */
       case 0x08:
            clr_I2C0CON_STA;
            I2C0DAT = (EEPROM_ADDRESS | I2C_WR);
       break;

       /* Master Transmit Address ACK  */
       case 0x18:
            I2C0DAT = HIBYTE(Rx_Addr);          //address high byte of I2C EEPROM
            addr_flag = 1;
       break;

       /* Master Transmit Data ACK */ 
       case 0x28:
            if(addr_flag)
            {
                I2C0DAT = LOBYTE(Rx_Addr);       //address low byte of I2C EEPROM
                addr_flag = 0;
                count = 0;
            }
            else
            {
                set_I2C0CON_STA;
            }
       break;  

       /* Master Repeat Start  */
       case 0x10: 
           clr_I2C0CON_STA;
           I2C0DAT = (EEPROM_ADDRESS | I2C_RD);
       break;

      /* Master Receive Address ACK  */
       case 0x40:  set_I2C0CON_AA; break;
       
      /* Master Receive Data ACK  */
       case 0x50:
            Rx_Dat = I2C0DAT;
            set_I2C0CON_STO;
            Read_End_Flag = 1;
       break;
    }

    I2C0_SI_Check();
    //while(STO);

_pop_(SFRS);
}


//========================================================================================================
bit I2C0_Write(unsigned int u16I2Caddr, unsigned char u8I2Cdat)
{
    unsigned long count = 0;

    Write_End_Flag = 0;
    I2C_Func = I2C0_Master_Tx_Isr;
    Tx_Addr = u16I2Caddr;
    Tx_Dat = u8I2Cdat;

    SFRS=0; printf ("\n Write n24LC64 data 0x%bd", u8I2Cdat);
    set_I2C0CON_STA;             /* Start transmit */
    while(1)
    {
        count++;
        if(Write_End_Flag == 1)
        {
            return 1;
        }
        
        if(count > 100000)
        {
            return 0;
        }
    }
}

/*========================================================================================================*/
bit I2C0_Read(unsigned int u8I2Caddr, unsigned char *u8I2Cdat)
{
    uint32_t count = 0;
    Read_End_Flag = 0;
    I2C_Func = I2C0_Master_Rx_Isr;
    Rx_Addr = u8I2Caddr;
  
    SFRS=0; printf ("\n Receive data from n24LC64" );
    set_I2C0CON_STA; 
    
    while(1)
    {
        count++;
        if(Read_End_Flag == 1)
        {
            *u8I2Cdat = Rx_Dat;
            return 1;
        }
        
        if(count > 100000)
        {
            return 0;
        }
    }
}
/*========================================================================================================*/
void Init_I2C(void)
{
    /* Set I2C GPIO */
    MFP_P41_I2C0_SCL;
    MFP_P40_I2C0_SDA;
    GPIO_SetMode(Port4, SET_BIT0|SET_BIT1, GPIO_MODE_OPENDRAIN);      /* External pull high resister in circuit */
    GPIO_SchmittTrigger(Port4, SET_BIT0|SET_BIT1, ENABLE);        /* Setting Schmitt Trigger type input */

    /* Set I2C clock rate and enable*/
     I2C_Master_Open(I2C0,24000000,100000);
    /* Set I2C Interrupt enable*/
     I2C_Interrupt(I2C0, ENABLE);
     Global_Interrupt(ENABLE);
}

/*========================================================================================================*/
void main(void)
{
    uint8_t dat;
  
//  Enable_UART0_VCOM_38400_printf();
    Enable_UART0_VCOM_printf();
    printf("\n I2C EEPROM intial...");
    Init_I2C();  
    

        if(I2C0_Write(0x0000, 0x55) == 1)
        {
            Timer0_Delay(24000000,5,1000);
            if(I2C0_Read(0x0000, &dat) == 1)
            {
                if(dat == 0x55)
                {
                    SFRS=0; printf("\n EEPROM write and read Pass! ");
                }
                else
                {
                    printf("\n FAIL! ");
                }
            }
        }
        I2C_Close(I2C0); 
            
//    }
        while(1);

}

