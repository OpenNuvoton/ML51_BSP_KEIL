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
//  File Function: ML51 SPI in Slave mode demo code
//***********************************************************************************************************
#include "ML51.h"

/* For printf code only. Disable this define to reduce code size. */
//#define print_function 

unsigned char   u8Receive_Data[5];
code char       u8Transmit_Data[5] = {0x4E, 0x55, 0x56, 0x4F, 0x54};
unsigned char   u8CNT = 0;
bit             SPI_Send_Flag = 0, SPI_Receive_Finish_Flag = 0;

//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
    while (1);
}
//-----------------------------------------------------------------------------------------------------------
void SPI_Initial(void)
{ 
    MFP_P00_SPI0_MOSI;                     /*define  SPI0 MOSI pin */
    P00_QUASI_MODE;
    MFP_P01_SPI0_MISO;                     /*define  SPI0 MISO pin */
    P01_QUASI_MODE;
    MFP_P02_SPI0_CLK;                      /*define  SPI0 CLK pin */
    P02_QUASI_MODE;
    MFP_P03_SPI0_SS;                       /*define  SPI0 SS pin as normal GPIO*/
    P03_QUASI_MODE;

    clr_SPI0CR0_MSTR;                      /* SPI in Slave mode  */
    clr_SPI0CR0_LSBFE;                     /* MSB first  */

    clr_SPI0CR0_CPOL;                      /* The SPI clock is low in idle mode */
    set_SPI0CR0_CPHA;                      /* The data is sample on the second edge of SPI clock */
       
    set_SPI0CR0_SPIEN;                     /* Enable SPI function */
    
    clr_SPI0SR_SPIF;                       /* Clear SPI flag */
    SPI0DR = u8Transmit_Data[0];
}

//-----------------------------------------------------------------------------------------------------------

void Slave_Polling_Receive_Data(void)
{
      u8Receive_Data[0] = Spi_Read_Byte(SPI0,u8Transmit_Data[0]);
      u8Receive_Data[1] = Spi_Read_Byte(SPI0,u8Transmit_Data[1]);
      u8Receive_Data[2] = Spi_Read_Byte(SPI0,u8Transmit_Data[2]);
      u8Receive_Data[3] = Spi_Read_Byte(SPI0,u8Transmit_Data[3]);
      u8Receive_Data[4] = Spi_Read_Byte(SPI0,u8Transmit_Data[4]);
}
//-----------------------------------------------------------------------------------------------------------
void Slave_Polling_Send_Data(void)
{

    DISABLE_SPI0_INTERRUPT;
    SPI_Send_Flag = 1;

    Spi_Write_Byte(SPI0,0x4F);
    Spi_Write_Byte(SPI0,0x4E);

    ENABLE_SPI0_INTERRUPT;
}
//-----------------------------------------------------------------------------------------------------------

void main(void)
{   
    SPI_Initial();
    /* Slave interrupt receive data */
    Slave_Polling_Receive_Data();           // Wait Slave receive data from master use the interrupt

    /* Slave interrupt receive data */
    Slave_Polling_Send_Data();                  // Slave transmit data to master
    clr_SPI0SR_SPIF;
    SPI0DR = 0x00;

    if(u8Receive_Data[0] != 0x90)               // Receive 1st DATA form master 
        SPI_Error(); 
    if(u8Receive_Data[1] != 0x01)               // Receive 2nd DATA form master 
        SPI_Error();
    if(u8Receive_Data[2] != 0x02)               // Receive 3rd DATA form master 
        SPI_Error();
    if(u8Receive_Data[3] != 0x03)               // Receive 4th DATA form master 
        SPI_Error();
    if(u8Receive_Data[4] != 0x04)               // Receive 5th DATA form master 
        SPI_Error();

    while(1);                                    // SPI transmission finish
}

