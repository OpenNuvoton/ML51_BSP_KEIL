/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2021 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MUG51 I2C Slave demo code
//***********************************************************************************************************

#include "ML51.h"


//***********************************************************************************************************
//  ML51-series I2C slave mode demo code, the Slave address = 0xA4
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
//  The protocol of I2C is same the "24LC64"
//***********************************************************************************************************


#define I2C_SLAVE_ADDRESS         0xA0
#define LOOP_SIZE                 10 

#define SDA                       P40
#define SCL                       P41

unsigned char data_received[34], data_num = 0 ; 
unsigned int u16PageOffset_HB,u16ReadAddress;
bit I2CWOVERFLAG = 0;

//========================================================================================================
void I2C0_ISR(void) interrupt 6
{
  _push_(SFRS);
  SFRS = 0;
  switch (I2C0STAT)
    {
        case 0x00:
            set_I2C0CON_STO;
        break;

        case 0x60:
            set_I2C0CON_AA;
        break;
        
        case 0x68:
            clr_I2C0CON_AA;
        break;

        case 0x80:
            data_received[data_num] = I2C0DAT;
            u16ReadAddress = (data_received[0]<<8) + data_received[1];  //This for read process
            data_num++;
            if (data_num == 32)   /* 2 byte address + 30 bytes Data */
            {
                clr_I2C0CON_AA;
            }
            else
                set_I2C0CON_AA;
        break;

        case 0x88:
            data_received[data_num] = I2C0DAT;
            data_num = 0;
            clr_I2C0CON_AA;
        break;

        case 0xA0:

            if (data_num>20)
            {
               I2CWOVERFLAG = 1 ;
            }
            data_num =0;
            set_I2C0CON_AA;
        break;

        case 0xA8:
            I2C0DAT = Read_APROM_BYTE((unsigned int code *)(u16ReadAddress+data_num));
            data_num++;
            set_I2C0CON_AA;
        break;
        
        case 0xB8: 
            I2C0DAT = Read_APROM_BYTE((unsigned int code *)(u16ReadAddress+data_num));
            data_num++;
            set_I2C0CON_AA;
        break;

        case 0xC0:
            data_num = 0;
            set_I2C0CON_AA;
        break; 

        case 0xC8:
            set_I2C0CON_AA;
        break;
    }

    I2C0_SI_Check();
_pop_(SFRS);
}

//========================================================================================================
void Init_I2C_Slave_Interrupt(void)
{
    MFP_P41_I2C0_SCL;
    MFP_P40_I2C0_SDA;
    GPIO_SetMode(Port4 , SET_BIT0 | SET_BIT1, GPIO_MODE_OPENDRAIN);  /* External pull up resister is necessary. */
    GPIO_SchmittTrigger(Port4, SET_BIT0 | SET_BIT1, ENABLE);
  
    SDA = 1;                                    /* set SDA and SCL pins high */
    SCL = 1;
  
    I2C_Slave_Open(I2C0, I2C_SLAVE_ADDRESS,0 , 0, 0) ;
    I2C_Interrupt(I2C0, ENABLE);
}

//========================================================================================================
void main(void)
{

    /* Initial I2C function */
    Init_I2C_Slave_Interrupt();                                 //initial I2C circuit
    Global_Interrupt(Enable);

/* =================== */
    while (1)
    {
         if (I2CWOVERFLAG )
        {
           u16PageOffset_HB =  (data_received[0]<<8) + data_received[1];
           Write_DATAFLASH_ARRAY(u16PageOffset_HB, data_received+2, 32);
           I2CWOVERFLAG = 0;
        }
     }

}

