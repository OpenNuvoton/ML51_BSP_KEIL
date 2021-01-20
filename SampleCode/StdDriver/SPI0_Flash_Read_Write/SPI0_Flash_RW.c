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
//  File Function: ML51 Access SPI Flash (W25Q16BV) demo code
//***********************************************************************************************************
#include "ML51.h"


#define SPI_CMD_WRITE_ENABLE    0x06
#define SPI_CMD_WRITE_DISABLE   0x04
#define SPI_CMD_READ_DATA       0x03
#define SPI_CMD_PAGE_PROGRAM    0x02
#define SPI_CMD_CHIP_ERASE      0xC7
#define SPI_CMD_SECTOR_ERASE    0x20
#define SPI_CMD_READ_STATUS1    0x05

#define SPI0_SS_PIN             P03   /* also copy this define in spi.h */
/***************************************************/
void SPI_Error(void)
{
    while(1);
}
/***************************************************/
void SPI_Initial(void)
{
    MFP_P00_SPI0_MOSI;      /*define  SPI0 MOSI pin */
    P00_QUASI_MODE;
    MFP_P01_SPI0_MISO;      /*define  SPI0 MISO pin */
    P01_QUASI_MODE;
    MFP_P02_SPI0_CLK;       /*define  SPI0 CLK pin */
    P02_QUASI_MODE;
    MFP_P03_GPIO;           /*define  SPI0 SS pin as normal GPIO*/
    P03_PUSHPULL_MODE; 

    clr_SPI0CR0_SPR1;
    clr_SPI0CR0_SPR0;
/* /SS General purpose I/O ( No Mode Fault ) */
    set_SPI0SR_DISMODF;
    clr_SPI0CR0_SSOE;

    /* SPI in Master mode */
    set_SPI0CR0_MSTR;

    /* MSB first */
    clr_SPI0CR0_LSBFE;

    clr_SPI0CR0_CPOL;
    clr_SPI0CR0_CPHA;
    
    /* Enable SPI function */
    set_SPI0CR0_SPIEN;
}
/****************************************************************/
void Flash_Check_StatusBusy(unsigned char u8SPISel)
{
    unsigned char u8Status;

    SPI0_SS_PIN = 0;
    do{
        Spi_Write_Byte(u8SPISel,SPI_CMD_READ_STATUS1);
        u8Status = Spi_Read_Byte(u8SPISel,0xFF);
    }while((u8Status&0x01)==0x01);
    SPI0_SS_PIN = 1;
}
/****************************************************************/
void SpiFlash_Write_Enable(unsigned char u8SPISel)
{
    SPI0_SS_PIN = 0;
    Spi_Write_Byte(u8SPISel,SPI_CMD_WRITE_ENABLE);
    SPI0_SS_PIN = 1;
}
/****************************************************************/
void SpiFlash_Write_Disable(unsigned char u8SPISel)
{
    SPI0_SS_PIN = 0;
    Spi_Write_Byte(u8SPISel,SPI_CMD_WRITE_DISABLE);
    SPI0_SS_PIN = 1; 
}

/****************************************************************/
void SpiFlash_Read_MID_DID(unsigned char u8SPISel, unsigned char *pu8A, unsigned char *pu8B)
{
    SPI0_SS_PIN = 0;
    Spi_Write_Byte(u8SPISel,0x90);
    Spi_Write_Byte(u8SPISel,0x00);
    Spi_Write_Byte(u8SPISel,0x00);
    Spi_Write_Byte(u8SPISel,0x00);
    *pu8A = Spi_Read_Byte(u8SPISel,0xFF);
    *pu8B = Spi_Read_Byte(u8SPISel,0xFF);
    SPI0_SS_PIN = 1;
}
/****************************************************************/
void SpiFlash_Chip_Erase(unsigned char u8SPISel)
{
    SpiFlash_Write_Enable(u8SPISel);
    SPI0_SS_PIN = 0;
    Spi_Write_Byte(u8SPISel,SPI_CMD_CHIP_ERASE);
    SPI0_SS_PIN = 1;
    Flash_Check_StatusBusy(u8SPISel);
    SpiFlash_Write_Disable(u8SPISel);
}
/****************************************************************/
void SpiFlash_Sector_Erase(unsigned char u8SPISel, unsigned char u8add0,unsigned char u8add1,unsigned char u8add2)
{
    SpiFlash_Write_Enable(u8SPISel);
    SPI0_SS_PIN = 0;
    Spi_Write_Byte(u8SPISel,SPI_CMD_SECTOR_ERASE);
    Spi_Write_Byte(u8SPISel,u8add0);
    Spi_Write_Byte(u8SPISel,u8add1);
    Spi_Write_Byte(u8SPISel,u8add2);
    SPI0_SS_PIN = 1;
    Flash_Check_StatusBusy(u8SPISel);
    SpiFlash_Write_Disable(u8SPISel);
}
/***************************************************/
void SpiFlash_Erase_Verify(unsigned char u8SPISel)
{
    unsigned int  u16CNT;
    unsigned char u8Data;

    SPI0_SS_PIN = 0;
    Spi_Write_Byte(u8SPISel,SPI_CMD_READ_DATA);
    /* 24-bit Address */
    Spi_Write_Byte(u8SPISel,0x00);
    Spi_Write_Byte(u8SPISel,0x00);
    Spi_Write_Byte(u8SPISel,0x00);
    for(u16CNT=0;u16CNT<256;u16CNT++)
    {
        u8Data = Spi_Read_Byte(u8SPISel,0x00);
        if(u8Data != 0xFF)
            SPI_Error();
    }
     SPI0_SS_PIN = 1; 
}

/***************************************************/
void SpiFlash_Program(unsigned char u8SPISel)
{
    unsigned int  u16CNT;

    SpiFlash_Write_Enable(u8SPISel);
    SPI0_SS_PIN = 0;
    Spi_Write_Byte(u8SPISel,SPI_CMD_PAGE_PROGRAM);
    /* 24-bit Address */
    Spi_Write_Byte(u8SPISel,0x00);
    Spi_Write_Byte(u8SPISel,0x00);
    Spi_Write_Byte(u8SPISel,0x00);
    for(u16CNT=0;u16CNT<256;u16CNT++)
        Spi_Write_Byte(u8SPISel,(unsigned char)u16CNT);
    SPI0_SS_PIN = 1;

    Flash_Check_StatusBusy(u8SPISel);
    SpiFlash_Write_Disable(u8SPISel);
}

void SpiFlash_Program_Verify(unsigned char u8SPISel)
{
    unsigned int  u16CNT;
    unsigned char u8Data;

    SPI0_SS_PIN = 0;
    Spi_Write_Byte(u8SPISel,SPI_CMD_READ_DATA);
    /* 24-bit Address */
    Spi_Write_Byte(u8SPISel,0x00);
    Spi_Write_Byte(u8SPISel,0x00);
    Spi_Write_Byte(u8SPISel,0x00);
    for(u16CNT=0;u16CNT<256;u16CNT++)
    {
        u8Data = Spi_Read_Byte(u8SPISel,0x00);
        if(u8Data != (unsigned char)u16CNT)
            SPI_Error();
    }
    SPI0_SS_PIN = 1;
}
/************ main loop **************/
void main(void)
{
    unsigned char u8MID,u8DID;

    SPI_Initial();

    SpiFlash_Read_MID_DID(SPI0,&u8MID,&u8DID);
    if((u8MID != 0xEF)&&(u8DID != 0x14))
        SPI_Error();

/* The procedure of SPI Flash at erase mode */
    SpiFlash_Sector_Erase(SPI0,0,0,0);
    SpiFlash_Erase_Verify(SPI0);

/* The procedure of SPI Flash at program mode */
    SpiFlash_Program(SPI0);
    SpiFlash_Program_Verify(SPI0);

    while(1);
}
