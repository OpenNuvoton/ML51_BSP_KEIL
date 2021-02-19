/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

#include "ML51.h"

/**
 * @brief       Watchdog time delay setting 
 * @param       u8WDTDIV WKT counter divider select  (1/4/8/16/32/64/128/256) 
 * @return      none
 * @details     none
 * @note        none
 * @example      WDT_Open(256);
 */
 void WDT_Open(unsigned int u8WDTDIV)
{
    SFRS=0;
    BIT_TMP=EA;
    EA=0;
    switch (u8WDTDIV)
    {
        case 1: TA=0xAA;TA=0x55;WDCON&=0xF8; break;
        case 4: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x01; break;
        case 8: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x02; break;
        case 16: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x03; break;
        case 32: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x04; break;
        case 64: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x05; break;
        case 128: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x06; break;
        case 256: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x07; break;
        case 512: TA=0xAA;TA=0x55;WDCON&=0xF8;SFRS=3;TA=0xAA;TA=0x55;WDCONH|=0x01; break;
        case 1024: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x01;SFRS=3;TA=0xAA;TA=0x55;WDCONH|=0x01; break;
        case 2048: TA=0xAA;TA=0x55;WDCON&=0xF8;TA=0xAA;TA=0x55;WDCON|=0x02;SFRS=3;TA=0xAA;TA=0x55;WDCONH|=0x01; break;
        default: break;
    }
    EA = BIT_TMP;
    set_WDCON_WIDPD;
    set_WDCON_WDTR;
}

/**
 * @brief       Watchdog time interrupt setting 
 * @param       u8WDTINT (Enable/Disable) 
 * @return      none
 * @details     none
 * @note        none
 * @example      WDT_Interrupt(Enable);
 */
void WDT_Interrupt(unsigned char u8WDTINT)
{
    switch (u8WDTINT)
    {
        case Disable: clr_EIE0_EWDT; break;    
        case Enable: set_EIE0_EWDT; break;
    }
}

