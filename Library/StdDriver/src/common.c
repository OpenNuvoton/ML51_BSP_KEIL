/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ML51.h"
bit BIT_TMP;
unsigned char data  TA_REG_TMP,SFRS_TMP,BYTE_TMP;

/**
 * @brief       Read Dataflash
 * @param       Dataflash start address
 * @return      Dataflash Value
 * @details     None
 */
 unsigned char Read_APROM_BYTE(unsigned int code *u16_addr)
{
    unsigned char rdata;
    rdata = *u16_addr >> 8;
    return rdata;
}

/**
 * @brief       Global Interrupt Status (EA)
 * @param       Enable / Disable
 * @return      None
 * @details     after all IP interrupt enable. Must enable gloabl interrupt.
 * @Example     Global_Interrupt(ENABLE);
 */
void Global_Interrupt(unsigned char u8IntStatus)
{
    EA = u8IntStatus;
}
