/**************************************************************************//**
 * @file     LCDSub_Panel.c
 * @version  V1.00
 * $Revision: 6 $
 * $Date: 2020/05/02 7:10p $
 * @brief    ML56 series LCDSub board panel display zone source file
 *
 * @note
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "ML51.H"
#include "LCDSubCommon.h"

#define sub_Zone0 6
#define Zone0_Digit_SegNum 14

#define sub_Zone1  6
#define Zone1_Digit_SegNum  7

#define sub_Zone2  6
#define Zone2_Digit_SegNum  7

#define sub_Zone3  1
#define Zone3_Digit_SegNum  29

const ZoneInfo_TypeDef LCD_ZoneInfo[]=
{
    {sub_Zone0, Zone0_Digit_SegNum},
    {sub_Zone1, Zone1_Digit_SegNum},
    {sub_Zone2, Zone2_Digit_SegNum},
    {sub_Zone3, Zone3_Digit_SegNum},
};

const char Zone0[sub_Zone0][Zone0_Digit_SegNum][2] =
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

const char Zone1[sub_Zone1][Zone1_Digit_SegNum][2] =
{
        //{com, seg}
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
    {
        // 4      (LCD Character Group 15)
        // A     // B     // C     // D
        {7,  7}, {6,  8}, {4,  8}, {4,  7},
        // E     // F     // G
        {5,  7}, {6,  7}, {5,  8},
    },
    {
        // 5      (LCD Character Group 16)
        // A     // B     // C     // D
        {7,  9}, {6,  10}, {4,  10}, {4,  9},
        // E     // F     // G
        {5,  9}, {6,  9}, {5,  10},
    },
    {
        // 6      (LCD Character Group 17)
        // A     // B     // C     // D
        {7,  11}, {6,  14}, {4,  14}, {4,  11},
        // E     // F     // G
        {5,  11}, {6,  11}, {5,  14},
    },


};

const char Zone2[sub_Zone2][Zone2_Digit_SegNum][2] =
{
        //{com, seg}
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


//Symbol Zone
const char Zone3[sub_Zone3][Zone3_Digit_SegNum][2] =
{
   {
/*  Zone 0 area  */ 
        {2,  4},  // ":"(LCD Character Group 2)           /* 0 */
        {0,  4},  // "."(LCD Character Group 2)           /* 1 */
        {2,  9},  // ":"(LCD Character Group 3)           /* 2 */
        {0,  9},  // "."(LCD Character Group 3)           /* 3 */
        {2,  15}, // ":"(LCD Character Group 4)           /* 4 */
        {0,  15}, // "."(LCD Character Group 4)           /* 5 */
        {2,  19}, // ":"(LCD Character Group 5)           /* 6 */
        {0,  19}, // "."(LCD Character Group 5)           /* 7 */
        {2,  23}, // ":"(LCD Character Group 6)           /* 8 */
        {0,  23}, // "."(LCD Character Group 6)           /* 9 */
        {7,  26}, // "V"(LCD Character T26)               /* 10 */
        {7,  24}, // "A"(LCD Character T27)               /* 11 */
        {7,  22}, // "W"(LCD Character T28)               /* 12 */
                 
 /*  Zone 1 area */         
        {7,  8},  // "%"   (LCD Character Y2)             /* 13 */
        {7,  5},  // "ppm" (LCD Character Y1)             /* 14 */
        {7,  10}, // "C"  (LCD Character T37)             /* 15 */
        {7,  14}, // "F"  (LCD Character T38)             /* 16 */
                 
/*  Zone 2 area  */         
        {7,  18}, // "Version:"                           /* 17 */
        {7,  16}, // .(LCD Character Group 18)            /* 18 */
        {7,  20}, // .(LCD Character Group 20)            /* 19 */
                 
/*Zone 3 area */         
        {7, 6}, // nuvoTon LOGO (T1)                      /* 20 */
        {6, 6}, // wifi LOGO (T2)                         /* 21 */
        {5, 6}, // buzzer LOGO (T3)                       /* 22 */
        {1, 6}, // battery level 3 (T4)                   /* 23 */
        {0, 6}, // battery level 2 (T5)                   /* 24 */
        {2, 6}, // battery level 1 (T6)                   /* 25*/
        {3, 6}, // battery (T7)                           /* 26 */
    }
};

char *Zone[] =
{
    (char*)(Zone0),
    (char*)(Zone1),
    (char*)(Zone2),
    (char*)(Zone3),
};


/**************************************************************************//**
 *
 * Defines segments for the alphabet
 * Bit pattern below defined for alphabet (text segments)
 *
 *****************************************************************************/
/**************************************************************************//**
 *
 * Defines each text's segment (alphabet+numeric) in terms of COM and BIT numbers,
 * Using this way that text segment can be consisted of each bit in the
 * following bit pattern for zone0
 * @illustration
 *
 *              A
 *         ----------
 *         |\   |H  /|
 *        F| G  |  I |B
 *         |  \ | /  |
 *         --J-- --K--      ML56
 *         |   /| \  |
 *       E |  L |  N |C
 *         | /  |M  \|
 *         -----------
 *              D
 *
 *         -------0------
 *
 *        |   \6  |7  /8 |
 *        |5   \  |  /   |1
 *
 *         --9---  ---10--
 *
 *        |    /  |  \13 |
 *        |4  /11 |12 \  |2
 *
 *         -------3------
 * For example show 2 should enable bit 0/1/10/6/4/3 = 0000 0100 1001 1011 = 0x45b
 *****************************************************************************/

const uint16_t Zone0_TextDisplay[] =
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

    0x003f, /* 0 * 00 0000 0011 1111 */
    0x0006, /* 1 * 00 0000 0000 0110 */
    0x001b, /* 2 * 00 0000 0001 1011 */
    0x060f, /* 3 * 00 0110 0000 1111 */
    0x16b0, /* 4 * 01 0110 1011 0000 */
    0x062d, /* 5 * 00 0110 0010 1101 */
    0x063d, /* 6 * 00 0110 0011 1101 */
    0x1081, /* 7 * 01 0000 1000 0001 */
    0x2949, /* 8 * 10 1001 0100 1001 */
    0x062f, /* 9 * 00 0110 0010 1111 */

    0x0000, /* : */
    0x0000, /* ; */
    0x0a00, /* < */
    0x0000, /* = */
    0x2080, /* > */
    0x0000, /* ? */
    0xffff, /* @ */

    0x0637, /* A 00 0110 0011 0111 */
    0x2339, /* B 10 0011 0011 1001 */
    0x0039, /* C 00 0000 0011 1001 */
    0x0870, /* D 00 1000 0111 0000 */
    0x0639, /* E 00 0110 0011 1001 */
    0x0631, /* F 00 0110 0011 0001 */
    0x043d, /* G 00 0100 0011 1101 */
    0x0636, /* H 00 0110 0011 0110 */
    0x1089, /* I 01 0000 1000 1001 */
    0x000e, /* J 00 0000 0000 1110 */
    0x2330, /* K 10 0011 0011 0000 */
    0x0038, /* L 00 0000 0011 1000 */
    0x0176, /* M 00 0001 0111 0110 */
    0x2076, /* N 10 0000 0111 0110 */
    0x003f, /* O 00 0000 0011 1111 */
    0x0633, /* P 00 0110 0011 0011 */
    0x203f, /* Q 10 0000 0011 1111 */
    0x2331, /* R 10 0011 0011 0001 */
    0x062d, /* S 00 0110 0010 1101 */
    0x1081, /* T 01 0000 1000 0001 */
    0x003e, /* U 00 0000 0011 1110 */
    0x0930, /* V 00 1001 0011 0000 */
    0x2836, /* W 10 1000 0011 0110 */
    0x2940, /* X 10 1001 0100 0000 */
    0x1140, /* Y 01 0001 0100 0000 */
    0x0909, /* Z 00 1001 0000 1001 */

    0x0039, /* [ */
    0x0880, /* backslash */
    0x000f, /* ] */
    0x0001, /* ^ */
    0x0008, /* _ */
    0x0000, /* ` */

    0x2070, /* a 10 0000 0111 0000 */
    0x047c, /* b */
    0x0618, /* c 00 0110 0001 1000 */
    0x0606, /* d 00 1100 0000 0110 */
    0x2058, /* e */
    0x0471, /* f */
    0x044e, /* g 00 0100 0100 1110 */
    0x0474, /* h */
    0x1001, /* i 01 0000 0000 0001 */
    0x000d, /* j 00 0000 0000 1101 */
    0xc180, /* k 11 0001 1000 0000 */
    0x1080, /* l 01 0000 1000 0000 */
    0x1454, /* m */
    0x0614, /* n 00 0110 0001 0100 */
    0x045c, /* o */
    0x0331, /* p 00 0011 0011 0001 */
    0x0447, /* q 00 0100 0100 0111 */
    0x0450, /* r */
    0x2408, /* s 10 0100 0000 1000*/
    0x0078, /* t */
    0x001c, /* u */
    0x2010, /* v */
    0x2814, /* w */
    0x2a80, /* x */
    0x044e, /* y 00 0100 0100 1110*/
    0x2048, /* z */


    0x0000,
};

/**************************************************************************//**
 * Defines segments for the numeric display
 *****************************************************************************/
/**************************************************************************//**
 *
 * Defines each text's segment (alphabet+numeric) in terms of COM and BIT numbers,
 * Using this way that text segment can be consisted of each bit in the
 * following bit pattern for zone1 and zone2
 * @illustration
 *              A
 *         -----------
 *         |         |
 *        F|         |B
 *         |         |
 *         ---- G-----
 *         |         |
 *        E|         |C
 *         |         |
 *         -----------
 *              D
 *
 *        -----0-----
 *        |          |
 *       5|          |1
 *        |          |
 *        -----6------
 *        |          |
 *       4|          |2
 *        |          |
 *        -----3-----
 *
 *
 *
 *****************************************************************************/
const uint16_t Zone1_TextDisplay[] =
{
    0x3f, /* 0 */
    0x06, /* 1 */
    0xdb, /* 2 */
    0xcf, /* 3 */
    0xe6, /* 4 */
    0xed, /* 5 */
    0xfd, /* 6 */
    0x07, /* 7 */
    0xff, /* 8 */
    0xef, /* 9 */
    0xc0, /* - */
};


const uint16_t *Zone_TextDisplay[] =
{
    (uint16_t*)(Zone0_TextDisplay),
    (uint16_t*)(Zone1_TextDisplay),
    (uint16_t*)(Zone1_TextDisplay),
};
