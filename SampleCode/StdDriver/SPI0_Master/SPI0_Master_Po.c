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
//  File Function: ML51 SPI in Master mode demo code
//***********************************************************************************************************
#include "ML51.h"

 /* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
#define print_function 
#define  spi_trans_delay

#define  SPI0_SS_PIN       P03

//-----------------------------------------------------------------------------------------------------------
void SPI_Error(void)
{
#ifdef print_function
    printf (" \n SPI transmit error!");
#endif
    while(1);                                       // SPI error 
}

//-----------------------------------------------------------------------------------------------------------
void SPI0_Initial(void)
{      
    MFP_P00_SPI0_MOSI;      /*define  SPI0 MOSI pin */
    P00_QUASI_MODE;
    MFP_P01_SPI0_MISO;      /*define  SPI0 MISO pin */
    P01_QUASI_MODE;
    MFP_P02_SPI0_CLK;       /*define  SPI0 CLK pin */
    P02_QUASI_MODE;
    MFP_P03_GPIO;           /*define  SPI0 SS pin as normal GPIO*/
    P03_PUSHPULL_MODE;
    
    set_SPI0SR_DISMODF;                                 // SS General purpose I/O ( No Mode Fault ) 
    clr_SPI0CR0_SSOE;
   
    clr_SPI0CR0_LSBFE;                                  // MSB first

    clr_SPI0CR0_CPOL;                                   // The SPI clock is low in idle mode
    set_SPI0CR0_CPHA;                                   // The data is sample on the second edge of SPI clock 
    
    set_SPI0CR0_MSTR;                                   // SPI in Master mode 
    SPI0_CLOCK_DIV_16;                                  // Select SPI clock 
    set_SPI0CR0_SPIEN;                                  // Enable SPI function 
    clr_SPI0SR_SPIF;
}
//-----------------------------------------------------------------------------------------------------------
void Start_SPI0_process(UINT8 *pu8MID,UINT8 *pu8DID)
{
    SPI0_SS_PIN = 0;

    Spi_Write_Byte(SPI0,0x90);
    if(SPI0DR != 0x4E)
       SPI_Error(); 
#ifdef spi_trans_delay                      /* if slave is interrupt mode, add delay to wait */
    _delay_();                              /* remark #define spi_trans_delay for normal polling transmittion */
#endif

    Spi_Write_Byte(SPI0,0x01);
    if(SPI0DR != 0x55)
       SPI_Error();
#ifdef spi_trans_delay
    _delay_();
#endif

    Spi_Write_Byte(SPI0,0x02);
    if(SPI0DR != 0x56)
       SPI_Error();
#ifdef spi_trans_delay
    _delay_();
#endif

    Spi_Write_Byte(SPI0,0x03);
    if(SPI0DR != 0x4F)
       SPI_Error();
#ifdef spi_trans_delay
    _delay_();
#endif

    Spi_Write_Byte(SPI0,0x04);
    if(SPI0DR != 0x54)
       SPI_Error();
#ifdef spi_trans_delay
    _delay_();
#endif

   /* Slave Polling receive data*/
    *pu8MID = Spi_Read_Byte(SPI0,0xFF);                             // Receive Slave 1st DATA from Slave
    *pu8DID = Spi_Read_Byte(SPI0,0xFF);                             // Receive Slave 2nd DATA from Slave

    SPI0_SS_PIN = 1;    
}
//-----------------------------------------------------------------------------------------------------------
void main(void)
{      
    unsigned char u8MID,u8DID;

#ifdef print_function
  /* UART0 initial setting
  ** include uart.c in Library for UART initial setting
  **UART0 define P3.1 TXD multi function setting
  **/
  Enable_UART0_VCOM_printf();
  printf("\n SPI0 intial...");
#endif

    SPI0_Initial();
    Start_SPI0_process(&u8MID,&u8DID);
  
    if((u8MID != 0x4F)&&(u8DID != 0x4E))
        SPI_Error();

#ifdef print_function
  printf("\n SPI0 transmit finish.");
#endif
    while(1);                                                         // SPI transmission finish and P0.6 flash
}
//-----------------------------------------------------------------------------------------------------------
