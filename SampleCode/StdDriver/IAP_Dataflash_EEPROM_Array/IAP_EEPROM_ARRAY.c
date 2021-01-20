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
//  File Function: MlL51  IAP program dataflash as EEPROM demo code
//***********************************************************************************************************

#include "ML51.h"

/* For printf code only. Disable this define to reduce code size. */
#define print_function 

struct
{
    unsigned int a;
    unsigned long b;
    unsigned char  c;

} StructData;

unsigned char ArrayData[50];
unsigned char i;

/**
 * @brief       IAP program dataflash as EEPROM
 * @param       None
 * @return      None
 * @details     define dataflash need be modify address and value,
 */

void main(void)
{
    unsigned int system16highsite;

#ifdef print_function  
/*
 For UART0 P3.1 as TXD output setting 
 * include uart.c in Common Setting for UART0 
*/
    MFP_P31_UART0_TXD;                              // UART0 TXD use P1.6
    P31_QUASI_MODE;                                  // set P1.6 as Quasi mode for UART0 trasnfer
    UART_Open(24000000,UART0_Timer1,115200);        // Open UART0 use timer1 as baudrate generate and baud rate = 115200
    ENABLE_UART0_PRINTF;
#endif  

    MFP_P46_GPIO;
    P46_INPUT_MODE;
    while(P46);                              //loop here while P13 = 1;

    /** IAP program APROM as EEPROM way * include eeprom.c in Library       */

    Write_DATAFLASH_BYTE(0x3882, 0x34);

    for (i = 0; i < 50; i++)
    {
        ArrayData[i] = i;
    }

    StructData.a = 0x1D55;
    StructData.b = 0x55555555;
    StructData.c = 0x55;

    Write_DATAFLASH_ARRAY(0x38E0, ArrayData, 50); //write 50 bytes
    Write_DATAFLASH_ARRAY(0x38FD, (unsigned char *)&StructData, sizeof(StructData)); //write structure


    /*call read byte */
    system16highsite = ((Read_APROM_BYTE(0x38FD) << 8) + Read_APROM_BYTE(0x38FE));

#ifdef print_function
    /*printf must in SFR page 0 */
    _push_(SFRS);
    SFRS = 0;
    printf("\n System 16 high site = 0x%X", system16highsite);
    DISABLE_UART0_PRINTF;
    _pop_(SFRS);
#endif


    while (1);
}



