/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 I2C Slave demo code
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


#define I2C_CLOCK                 13
#define I2C_SLAVE_ADDRESS         0xA4
#define LOOP_SIZE                 10 

#define SDA                       P24
#define SCL                       P25

UINT8 data_received[34], data_num = 0;

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
            P02 = 0;
            while(1);
            break;

        case 0x80:
            data_received[data_num] = I2C0DAT;
            data_num++;

            if (data_num == LOOP_SIZE)
           {
              data_num = 0;
              clr_I2C0CON_AA;
           }
            else
                set_I2C0CON_AA;
            break;

        case 0x88:
            data_received[data_num] = I2C0DAT;
            data_num = 0;
            set_I2C0CON_AA;
            break;

        case 0xA0:
            set_I2C0CON_AA;
            break;

        case 0xA8:
            I2C0DAT = data_received[data_num];
            data_num++;
            set_I2C0CON_AA;
            break;
        
        case 0xB8:
            I2C0DAT = data_received[data_num];
            data_num++;
            set_I2C0CON_AA;
            break;

        case 0xC0:
            set_I2C0CON_AA;
            break; 

        case 0xC8:
            set_I2C0CON_AA;
            break;        
    }

    clr_I2C0CON_SI;
    _pop_(SFRS);
}

//========================================================================================================
void Init_I2C_SLAVE(void)
{
    MFP_P25_I2C0_SCL;
    P25_OPENDRAIN_MODE;          // Modify SCL pin to Open drain mode. don't forget the pull high resister in circuit
    MFP_P24_I2C0_SDA;
    P24_OPENDRAIN_MODE;          // Modify SDA pin to Open drain mode. don't forget the pull high resister in circuit

    SFRS = 0;
    SDA = 1;                                    //set SDA and SCL pins high
    SCL = 1;

    set_EIE0_EI2C0;                             //enable I2C interrupt by setting IE1 bit 0
    set_IE_EA;

    I2C0ADDR0 = I2C_SLAVE_ADDRESS;              //define own slave address
    set_I2C0CON_I2CEN;                          //enable I2C circuit
    set_I2C0CON_AA;
}

//========================================================================================================
void main(void)
{

    /* Initial I2C function */
    Init_I2C_SLAVE();                                 //initial I2C circuit

    while (1);
/* =================== */
}

