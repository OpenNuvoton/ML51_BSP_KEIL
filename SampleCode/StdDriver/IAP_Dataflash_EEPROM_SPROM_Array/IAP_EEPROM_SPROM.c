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
//  File Function: MlL51 IAP Dataflash SPROM demo code 
//***********************************************************************************************************

#include "ML51.h"

 /* @note        BOD reset maybe cause IAP process error. Disable BOD reset function and enable BOD interrupt to check and reset.   */
#define print_function
#define  BOR_Enabled_in_CONFIG

unsigned char ArrayData[50];
unsigned char i;
struct
{
    unsigned int a;
    unsigned long b;
    unsigned char  c;
} StructData;


#ifdef  BOR_Enabled_in_CONFIG
void BOD_ISR(void) interrupt 8        // Vector @  0x43
{
    TA=0xAA;TA=0x55;IAPUEN=0;         //Disable all Write enable
    clr_CHPCON_IAPEN;
    clr_BODCON0_BOF;                  //clear BOD flag
    set_CHPCON_SWRST;                 //Software reset
}
#endif

/**
 * @brief       IAP program SPROM as EEPROM main
 * @param       None
 * @return      None
 * @details     define dataflash need be modify address and value
 * @note        Download select Update SPROM 
 */
void main(void)
{
    unsigned int system16highsite;
  
#ifdef BOR_Enabled_in_CONFIG
    ENABLE_BOD_INTERRUPT;
    DISABLE_BOD_RESET;
#endif
  
/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
#ifdef print_function  
/* Initial UART0 for printf */  
/*
 For UART0 P3.1 as TXD output setting 
 * include uart.c in Common Setting for UART0 
*/
    MFP_P31_UART0_TXD;                              // UART0 TXD use P3.1
    P31_QUASI_MODE;                                 // set P3.1 as Quasi mode for UART0 trasnfer
    UART_Open(24000000,UART0_Timer1,115200);        // Open UART0 use timer1 as baudrate generate and baud rate = 115200
    ENABLE_UART0_PRINTF;
#endif  
    /*loop here while P46 = 1; */
    P46_QUASI_MODE;
    while (P46);

    /** IAP program as EEPROM way * include eeprom.c in Library       */
    for (i = 0; i < 50; i++)
    {
        ArrayData[i] = i;
    }
    StructData.a = 0x5555;
    StructData.b = 0x55555555;
    StructData.c = 0x55;

    Write_SPROM_DATAFLASH_ARRAY(0, ArrayData, 50); //write 50 bytes
    Write_SPROM_DATAFLASH_ARRAY(40, (unsigned char *)&StructData, sizeof(StructData)); //write structure

    /*call read byte */
    system16highsite = Read_SPROM_BYTE(31);
    system16highsite = (Read_SPROM_BYTE(31) << 8)+ Read_SPROM_BYTE(32);
#ifdef print_function
    /*printf must in SFR page 0 */
    _push_(SFRS);
    SFRS = 0;
    printf("\n system 16 high site = 0x%X", system16highsite);
    _pop_(SFRS);
#endif 
    while(1);
}
