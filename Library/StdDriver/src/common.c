/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ml51.h"
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

/**
 * @brief       Software reset API
 * @param       Run in APROM/LDROM after reset
 *                       - \ref BOOT_APROM: Run in APROM after reset .
 *                       - \ref BOOT_LDROM: Run in LDROM after reset.
 * @return      None
 * @details     None
 */
void Software_Reset(unsigned char u8Bootarea)
{
    unsigned char boottemp;
    boottemp = (0x80|u8Bootarea);
    TA = 0xAA;
    TA = 0x55;
    CHPCON = boottemp;                   //software reset enable
}

/**
 * @brief       MCU power down mode enable API
 * @param       Enable power down mode
 *                       - \ref ENABLE: Run into power down mode .
 * @return      None
 * @details     None
 */
void PowerDown_Mode(bit PDStatus)
{
    if (PDStatus)
    {
       POWERDOWN_MODE_ENABLE;
       CALL_NOP;
       CALL_NOP;
    }
}

/**
 * @brief       MCU idle mode enable API
 * @param       Enable idle mode
 *                       - \ref ENABLE: Run into idle mode .
 * @return      None
 * @details     None
 */
void Idle_Mode(bit IdleStatus)
{
    if (IdleStatus)
    {
       IDLE_MODE_ENABLE;
       CALL_NOP;
       CALL_NOP;
    }
}