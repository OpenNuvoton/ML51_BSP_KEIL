/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


/**************************************************************************//**
 * @file     LCDSubCommon.c
 * @version  V1.00
 * $Revision: 6 $
 * $Date: 2020/05/02 7:10p $
 * @brief    ML56 series LCDSubCommon source file
 *
 * @note
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "ML51.H"
#include "lcdlib.h"


void LCDLIB_Printf(uint32_t u32Zone, char *InputStr)
{
    uint32_t    i, index, ch, len;
    uint32_t    com, seg;
    uint16_t    DispData;

    len = strlen(InputStr);

    /* Fill out all characters on display */
    for (index = 0; index < g_LCDZoneInfo[u32Zone].u8LCDDispTableNum; index++)
    {
        if (index < len)
        {
            ch = *InputStr;
        }
        else
        {
            /* Padding with SPACE */
            ch = 0x20;
        }

        /* For Main Zone */
        if (u32Zone == ZONE_MAIN_DIGIT)
        {
            /* The Main Digit Table is an ASCII table beginning with "SPACE" (hex is 0x20) */
            ch       = ch - 0x20;
            DispData =*(g_LCDZoneInfo[u32Zone].pu16LCDDispTable + ch);
        }
        /* For Other Zones (Support '0' ~ '9' only) */
        else if ((ch >= '0') && (ch <= '9'))
        {
            ch = ch - '0';
            DispData = *(g_LCDZoneInfo[u32Zone].pu16LCDDispTable + ch);
        }
        /* Out of definition. Will show "SPACE" */
        else
        {
            DispData = 0;
        }

        for (i = 0; i < g_LCDZoneInfo[u32Zone].u8GetLCDComSegNum; i++)
        {
            com = *(g_LCDZoneInfo[u32Zone].pu8GetLCDComSeg
                    + (index * g_LCDZoneInfo[u32Zone].u8GetLCDComSegNum * 2)
                    + (i * 2) + 0);
            seg = *(g_LCDZoneInfo[u32Zone].pu8GetLCDComSeg
                    + (index * g_LCDZoneInfo[u32Zone].u8GetLCDComSegNum * 2)
                    + (i * 2) + 1);

            if (DispData & (1 << i))
            {
                /* Turn on display */
                LCD_SetOnePixel(com, seg, 1);
            }
            else
            {
                /* Turn off display */
                LCD_SetOnePixel(com, seg, 0);
            }

        }

        InputStr++;
    }
}

/**
 *  @brief Display number on LCD
 *
 *  @param[in]  u32Zone     the assigned number of display area
 *  @param[in]  InputNum    number to show on display
 *
 *  @return None
 */
void LCDLIB_PrintNumber(uint32_t u32Zone, uint32_t InputNum)
{
    uint32_t    i, div;
    uint32_t    com, seg;
    uint32_t    index;
    uint32_t    val;
    uint16_t    DispData;

    /* Extract useful digits */
    div = 1;

    /* Fill out all characters on display */

    index = g_LCDZoneInfo[u32Zone].u8LCDDispTableNum;

    while (index != 0)
    {
        index--;

        val = (InputNum / div) % 10;

        if (u32Zone == ZONE_MAIN_DIGIT)
            val += 16; /* The Main Digit Table is an ASCII table beginning with "SPACE" */

         DispData = *(g_LCDZoneInfo[u32Zone].pu16LCDDispTable + val);

        for (i = 0; i < g_LCDZoneInfo[u32Zone].u8GetLCDComSegNum; i++)
        {
            com = *(g_LCDZoneInfo[u32Zone].pu8GetLCDComSeg
                    + (index * g_LCDZoneInfo[u32Zone].u8GetLCDComSegNum * 2)
                    + (i * 2) + 0);
            seg = *(g_LCDZoneInfo[u32Zone].pu8GetLCDComSeg
                    + (index * g_LCDZoneInfo[u32Zone].u8GetLCDComSegNum * 2)
                    + (i * 2) + 1);

            if (DispData & (1 << i))
            {
                /* Turn on display */
                LCD_SetOnePixel(com, seg, 1);
            }
            else
            {
                /* Turn off display */
                LCD_SetOnePixel(com, seg, 0);
            }

        }

        div = div * 10;
    }
}


void LCDLIB_SetSymbol(uint32_t u32Symbol, uint32_t u32OnOff)
{
    uint32_t com, seg;

    com = (u32Symbol & 0xF);
    seg = ((u32Symbol & 0xFF0) >> 4);

    if (u32OnOff)
        LCD_SetOnePixel(com, seg, 1); /* Turn on display */
    else
        LCD_SetOnePixel(com, seg, 0); /* Turn off display */

}