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
#include "LCDView.h"

/* from M258 */
#define ZONE_MAIN_DIGIT             0   /*!< Main digit display zone index  */
#define ZONE_PPM_DIGIT              1   /*!< PPM or percentage digit display zone index  */
#define ZONE_TEMP_DIGIT             2   /*!< Temperature digit display zone index  */
#define ZONE_VER_DIGIT              3   /*!< Version number digit display zone index  */
#define ZONE_TIME_DIGIT             4   /*!< Time display on COM 4, SEG 10 */
#define ZONE_NUMICRO_DIGIT          5   /*!< NuMicro VER. display on COM 4, SEG 10 */

#define ZONE_MAIN_DIG_CNT           7   // Number of digits/texts, for number and alphabet display
#define ZONE_MAIN_SEG_NUM           14  // Number of segments on each digit number

#define ZONE_PPM_DIG_CNT            3   // Number of digits, for ppm display
#define ZONE_PPM_SEG_NUM            7   // Number of segments on each digit number

#define ZONE_TEMP_DIG_CNT           3   // Number of digits, for c/f display
#define ZONE_TEMP_SEG_NUM           7   // Number of segments on each digit number

#define ZONE_VER_DIG_CNT            6   // Number of digits, for version display
#define ZONE_VER_SEG_NUM            7   // Number of segments on each digit number

#define ZONE_TIME_DIG_CNT           4   // Number of digits
#define ZONE_TIME_SEG_NUM           7   // Number of segments on each digit number

#define ZONE_NUMICRO_DIG_CNT        3   // Number of digits
#define ZONE_NUMICRO_SEG_NUM        7   // Number of segments on each digit number

/*new api for ML56 */
const char acMAINDigitRawData[ZONE_MAIN_DIG_CNT][ZONE_MAIN_SEG_NUM][2] =
{
        //{com, seg}
    {
        // 2         (LCD Character Group 2)
        // A     // B     // C     // D
        {3,  2}, {3,  3}, {0,  3}, {0,  2},
        // E     // F     // G     // H
        {1,  0}, {3,  0}, {3,  1}, {2,  2},
        // I     // J     // K     // L
        {2,  3}, {2,  1}, {1,  3}, {0, 1},
        // M       // N
        {1,  1}, {1,  2},
    },
    {
        // 3        (LCD Character Group 3)
        // A     // B     // C     // D
        {3,  7}, {3,  8}, {0,  8}, {0,  7},
        // E     // F     // G     // H
        {1,  4}, {3,  4}, {3,  5}, {2,  7},
        // I     // J     // K     // L
        {2,  8}, {2,  5}, {1,  8}, {0, 5},
        // M       // N
        {1,  5}, {1,  7},
    },
    {
        // 4  ok    (LCD Character Group 4)
        // A     // B     // C     // D
        {3,  11}, {3,  14}, {0,  14}, {0,  11},
        // E     // F     // G     // H
        {1,  9}, {3,  9}, {3,  10}, {2,  11},
        // I     // J     // K     // L
        {2,  14}, {2,  10}, {1,  14}, {0, 10},
        // M       // N
        {1,  10}, {1,  11},
    },
    {
        // 5  ok    (LCD Character Group 4)
        // A     // B     // C     // D
        {3,  17}, {3,  18}, {0,  18}, {0,  17},
        // E     // F     // G     // H
        {1,  15}, {3,  15}, {3,  16}, {2,  17},
        // I     // J     // K     // L
        {2,  18}, {2,  16}, {1,  18}, {0, 16},
        // M       // N
        {1,  16}, {1,  17},
    },
    {
        // 6       (LCD Character Group 6)
        // A     // B     // C     // D
        {3,  21}, {3,  22}, {0,  22}, {0,  21},
        // E     // F     // G     // H
        {1,  19}, {3,  19}, {3,  20}, {2,  21},
        // I     // J     // K     // L
        {2,  22}, {2,  20}, {1,  22}, {0, 20},
        // M       // N
        {1,  20}, {1,  21},
    },
    {
        // 7       (LCD Character Group 7)
        // A     // B     // C     // D
        {3,  25}, {3,  26}, {0,  26}, {0,  25},
        // E     // F     // G     // H
        {1,  23}, {3,  23}, {3,  24}, {2,  25},
        // I     // J     // K     // L
        {2,  26}, {2,  24}, {1,  26}, {0, 24},
        // M       // N
        {1,  24}, {1,  25},
    },
};
/**************************************************************************//**
 *
 * Defines each text's segment (numeric) in terms of COM and BIT numbers,
 * Using this way that text segment can be consisted of each bit in the
 * following bit pattern:
 *
 *         ---A---
 *         |     |
 *         F     B
 *         |     |
 *         ---G---
 *         |     |
 *         E     C
 *         |     |
 *         ---D---
 *
 *         ---0---
 *         |     |
 *         5     1
 *         |     |
 *         ---6---
 *         |     |
 *         4     2
 *         |     |
 *         ---3---
 *
 *****************************************************************************/
const char acPPMDigitRawData[ZONE_PPM_DIG_CNT][ZONE_PPM_SEG_NUM][2] =
{
    {
        // 1     (LCD Character Group 12)
        // A     // B     // C     // D
        {7,  0}, {6,  1}, {4,  1}, {4,  0},
        // E     // F     // G
        {5,  0}, {6,  0}, {5,  1},
    },
    {
        // 2     (LCD Character Group 13)
        // A     // B     // C     // D
        {7,  2}, {6,  3}, {4,  3}, {4,  2},
        // E     // F     // G
        {5,  2}, {6,  2}, {5,  3},
    },
    {
        // 3      (LCD Character Group 14)
        // A     // B     // C     // D
        {7,  4}, {6,  5}, {4,  5}, {4,  4},
        // E     // F     // G
        {5,  4}, {6,  4}, {5, 5},
    },

};

static const char acTEMPDigitRawData[ZONE_TEMP_DIG_CNT][ZONE_TEMP_SEG_NUM][2] =
{
    {
        // 1      (LCD Character Group 15)
        // A     // B     // C     // D
        {7,  7}, {6,  8}, {4,  8}, {4,  7},
        // E     // F     // G
        {5,  7}, {6,  7}, {5,  8},
    },
    {
        // 2      (LCD Character Group 16)
        // A     // B     // C     // D
        {7,  9}, {6,  10}, {4,  10}, {4,  9},
        // E     // F     // G
        {5,  9}, {6,  9}, {5,  10},
    },
    {
        // 3      (LCD Character Group 17)
        // A     // B     // C     // D
        {7,  11}, {6,  14}, {4,  14}, {4,  11},
        // E     // F     // G
        {5,  11}, {6,  11}, {5,  14},
    },};

const char acVERDigitRawData[ZONE_VER_DIG_CNT][ZONE_VER_SEG_NUM][2] =
{
    {
        // 1     (LCD Character Group 18)OK
        // A     // B     // C     // D
        {7,  15}, {6,  16}, {4,  16}, {4,  15},
        // E     // F     // G
        {5,  15}, {6,  15}, {5,  16},
    },
    {
        // 2     (LCD Character Group 19)
        // A     // B     // C     // D
        {7,  17}, {6,  18}, {4,  18}, {4,  17},
        // E     // F     // G
        {5,  17}, {6,  17}, {5, 18},
    },
    {
        // 3      (LCD Character Group 20)
        // A     // B     // C     // D
        {7,  19}, {6,  20}, {4,  20}, {4,  19},
        // E     // F     // G
        {5,  19}, {6,  19}, {5, 20},
    },
    {
        // 4      (LCD Character Group 21)
        // A     // B     // C     // D
        {7,  21}, {6,  22}, {4,  22}, {4,  21},
        // E     // F     // G
        {5,  21}, {6,  21}, {5, 22},
    },
    {
        // 5      (LCD Character Group 22)
        // A     // B     // C     // D
        {7,  23}, {6,  24}, {4,  24}, {4,  23},
        // E     // F     // G
        {5,  23}, {6,  23}, {5, 24},
    },
    {
        // 6      (LCD Character Group 23)
        // A     // B     // C     // D
        {7,  25}, {6,  26}, {4,  26}, {4,  25},
        // E     // F     // G
        {5,  25}, {6,  25}, {5, 26},
    },
};

static const char acTIMEDigitRawData[ZONE_TIME_DIG_CNT][ZONE_TIME_SEG_NUM][2] =
{
    {
        // digit 1, {com, seg}
        // A     // B     // C     // D
        {7,  2}, {6,  3}, {4,  3}, {4,  2},
        // E     // F     // G
        {5,  2}, {6,  2}, {5, 3},
    },
    {
        // digit 2, {com, seg}
        // A     // B     // C     // D
        {7,  4}, {6,  5}, {4,  5}, {4,  4},
        // E     // F     // G
        {5,  4}, {6,  4}, {5, 5},
    },
    {
        // digit 3, {com, seg}
        // A     // B     // C     // D
        {7,  6}, {6,  7}, {4,  7}, {4,  6},
        // E     // F     // G
        {5,  6}, {6,  6}, {5, 7},
    },
    {
        // digit 4, {com, seg}
        // A     // B     // C     // D
        {7,  8}, {6,  9}, {4,  9}, {4,  8},
        // E     // F     // G
        {5,  8}, {6,  8}, {5, 9},
    },
};

static const char acNUMICRODigitRawData[ZONE_NUMICRO_DIG_CNT][ZONE_NUMICRO_SEG_NUM][2] =
{
    {
        // digit 1, {com, seg}
        // A     // B     // C     // D
        {3,  4}, {2,  5}, {0,  5}, {0,  4},
        // E     // F     // G
        {1,  4}, {2,  4}, {1,  5},
    },
    {
        // digit 2, {com, seg}
        // A     // B     // C     // D
        {3,  6}, {2,  7}, {0,  7}, {0,  6},
        // E     // F     // G
        {1,  6}, {2,  6}, {1,  7},
    },
    {
        // digit 3, {com, seg}
        // A     // B     // C     // D
        {3,  8}, {2,  9}, {0,  9}, {0,  8},
        // E     // F     // G
        {1,  8}, {2,  8}, {1,  9},
    },
};

/**************************************************************************//**
 *
 * Defines segments for the alphabet - ASCII table 0x20 to 0x7A
 * Bit pattern below defined for alphabet (text segments)
 *
 *****************************************************************************/
static const uint16_t auMAINDigitMap[] =
{
    0x0000, /* space */
    0x1100, /* ! */
    0x0280, /* " */
    0x0000, /* # */
    0x0000, /* $ */
    0x0000, /* % */
    0x0000, /* & */
    0x0000, /* ? */
    0x0039, /* ( */
    0x000f, /* ) */
    0x3fc0, /* * */
    0x1540, /* + */
    0x0000, /* , */
    0x0440, /* - */
    0x8000, /* . */
    0x2200, /* / */

    0x003F, /* 0 */
    0x0006, /* 1 */
    0x061B, /* 2 */
    0x060F, /* 3 */
    0x0626, /* 4 */
    0x062D, /* 5 */
    0x063D, /* 6 */
    0x0007, /* 7 */
    0x063F, /* 8 */
    0x062F, /* 9 */

    0x0000, /* : */
    0x0000, /* ; */
    0x2100, /* < */
    0x0000, /* = */
    0x0840, /* > */
    0x1403, /* ? */
    0x3FFF, /* @ */

    0x0637, /* A */
    0x2339, /* B */
    0x0039, /* C */
    0x2139, /* D */
    0x0639, /* E */
    0x0631, /* F */
    0x043D, /* G */
    0x0636, /* H */
    0x1080, /* I */
    0x000E, /* J */
    0x2330, /* K */
    0x0038, /* L */
    0x0176, /* M */
    0x2076, /* N */
    0x003F, /* O */
    0x0633, /* P */
    0x203F, /* Q */
    0x2331, /* R */
    0x062D, /* S */
    0x1081, /* T */
    0x003E, /* U */
    0x0930, /* V */
    0x2836, /* W */
    0x2940, /* X */
    0x1140, /* Y */
    0x0909, /* Z */

    0x0039, /* [ */
    0x0900, /* backslash */
    0x000F, /* ] */
    0x2800, /* ^ */
    0x0008, /* _ */
    0x0040, /* ` */

    0x1218, /* a */
    0x063C, /* b */
    0x0618, /* c */
    0x061E, /* d */
    0x0A18, /* e */
    0x0231, /* f */
    0x048F, /* g */
    0x1230, /* h */
    0x1000, /* i */
    0x000E, /* j */
    0x2330, /* k */
    0x0038, /* l */
    0x1614, /* m */
    0x1404, /* n */
    0x061C, /* o */
    0x0331, /* p */
    0x0447, /* q */
    0x1400, /* r */
    0x2408, /* s */
    0x0238, /* t */
    0x1018, /* u */
    0x0810, /* v */
    0x2814, /* w */
    0x2940, /* x */
    0x0446, /* y */
    0x0A08, /* z */

    0x0000,
};

/**************************************************************************//**
 * Defines segments for the numeric display
 *****************************************************************************/
static const unsigned short auPPMDigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

static const unsigned short auTEMPDigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

static const unsigned short auVERDigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

static const unsigned short auTIMEDigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

static const unsigned short auNUMICRODigitMap[] =
{
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};

typedef struct
{
    unsigned char   u8LCDDispTableNum;          /*!< LCD Display Table Number */
    unsigned char   u8GetLCDComSegNum;          /*!< LCD Com Seg Table Number */
    unsigned short  *pu16LCDDispTable;          /*!< LCD Display Table Pointer */
    unsigned char   *pu8GetLCDComSeg;           /*!< LCD Com Seg Table Pointer */

} code LCD_ZONE_INFO_T;


LCD_ZONE_INFO_T g_LCDZoneInfo[] =
{
    {ZONE_MAIN_DIG_CNT,      ZONE_MAIN_SEG_NUM,      (unsigned short *)auMAINDigitMap,      (unsigned char *)acMAINDigitRawData},
    {ZONE_PPM_DIG_CNT,       ZONE_PPM_SEG_NUM,       (unsigned short *)auPPMDigitMap,       (unsigned char *)acPPMDigitRawData},
    {ZONE_TEMP_DIG_CNT,      ZONE_TEMP_SEG_NUM,      (unsigned short *)auTEMPDigitMap,      (unsigned char *)acTEMPDigitRawData},
    {ZONE_VER_DIG_CNT,       ZONE_VER_SEG_NUM,       (unsigned short *)auVERDigitMap,       (unsigned char *)acVERDigitRawData},

    {ZONE_TIME_DIG_CNT,      ZONE_TIME_SEG_NUM,      (unsigned short *)auTIMEDigitMap,      (unsigned char *)acTIMEDigitRawData},
    {ZONE_NUMICRO_DIG_CNT,   ZONE_NUMICRO_SEG_NUM,   (unsigned short *)auNUMICRODigitMap,   (unsigned char *)acNUMICRODigitRawData},

};


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