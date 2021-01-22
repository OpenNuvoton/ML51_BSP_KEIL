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
#include "LCDSubCommon.h"

void LCDLIB_PrintCharacter(uint16_t u16Zone, char *string)
{
    int      data_1, length, index;
    uint16_t bitfield;
    unsigned long com, bit_1;
    int      i;

    length = strlen(string);
    index  = 0;

    /* fill out all characters on display */
    for (index = 0; index < LCD_ZoneInfo[u16Zone].Sub_Zone_Num; index++) {
        if (index < length) {
            data_1 = (int) *string;
        } else {       /* padding with space */
            data_1 = 0x20; /* SPACE */
        }
        /* defined letters currently starts at "SPACE" - 0x20; */
        data_1     = data_1 - 0x20;
        bitfield = *(Zone_TextDisplay[u16Zone] + data_1);

        for (i = 0; i < LCD_ZoneInfo[u16Zone].Zone_Digit_SegNum; i++) {
            bit_1 = *(Zone[u16Zone]
                    + index*LCD_ZoneInfo[u16Zone].Zone_Digit_SegNum*2
                    + i*2 + 1);

            com = *(Zone[u16Zone]
                    + index*LCD_ZoneInfo[u16Zone].Zone_Digit_SegNum*2
                    + i*2 + 0);

            LCD_SetOnePixel(com, bit_1, 0);

            if (bitfield & (1 << i)) {
                /* Turn on segment */
                LCD_SetOnePixel(com, bit_1, 1);
            }
        }
        string++;
    }

}

/**
 *  @brief Display number on LCD
 *
 *  @param[in] u32Zone  the assigned number of display area
 *  @param[in] value  number to show on display
 *
 *  @return None
 *
 */
void LCDLIB_PrintNumber(uint16_t  u16Zone, long value, unsigned char u8OnOff)

{
    int      index;
    long num, i, com, bit_1, div, len, tmp;
    uint16_t bitpattern;

    if (value < 0)
    {
        value = abs(value);
    }
    /* Length of number */
    len = 0;
    tmp = value;
    while( 1 )
    {
        if( (tmp/10) || (tmp%10) )
        {
            tmp = tmp / 10;
            len++;
        }
        else
            break;
    }
    /* Extract useful digits */
    div = 1;

    /* fill out all characters on display */
    for (index = (LCD_ZoneInfo[u16Zone].Sub_Zone_Num-1); index >= 0; index--)
    {

        num = (value / div) % 10;
      //  num += 16;
        bitpattern = *(Zone_TextDisplay[u16Zone] + num);

        for (i = 0; i < LCD_ZoneInfo[u16Zone].Zone_Digit_SegNum; i++)
        {
            bit_1 = *(Zone[u16Zone]
                    + index*LCD_ZoneInfo[u16Zone].Zone_Digit_SegNum*2
                    + i*2 + 1);
            com = *(Zone[u16Zone]
                    + index*LCD_ZoneInfo[u16Zone].Zone_Digit_SegNum*2
                    + i*2 + 0);
            LCD_SetOnePixel(com, bit_1, 0);

            if (bitpattern & (1 << i))
            {
                LCD_SetOnePixel(com, bit_1, u8OnOff);
            }
        }
        div = div * 10;

    }
}

/**
 *  @brief Display symbol on LCD
 *
 *  @param[in] u32Zone   the assigned number of display area
 *  @param[in] u32Index  the requested display position in zone
 *  @param[in] u32OnOff  1: display symbol
 *                   0: not display symbol
 *
 *  @return None
 *
 */
void LCDLIB_SetSymbol(unsigned char u8Zone, unsigned char u8Index, unsigned char u8OnOff)
{
    unsigned long com, seg;

    seg = *(Zone[u8Zone] + u8Index*2 + 1);

    com = *(Zone[u8Zone] + u8Index*2 + 0);

    if (u8OnOff)
        LCD_SetOnePixel(com, seg, 1); /* Turn on segment */
    else
        LCD_SetOnePixel(com, seg, 0); /* Turn off segment */

}