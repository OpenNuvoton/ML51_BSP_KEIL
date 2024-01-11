/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/* Same format with LCD VIEW output */
#ifndef __ML51_LCDLIB_H
#define __ML51_LCDLIB_H

#define ZONE_MAIN_DIGIT             0   /*!< Main digit display zone index  */
#define ZONE_PPM_DIGIT              1   /*!< PPM or percentage digit display zone index  */
#define ZONE_TEMP_DIGIT             2   /*!< Temperature digit display zone index  */
#define ZONE_VER_DIGIT              3   /*!< Version number digit display zone index  */
#define ZONE_TIME_DIGIT             4   /*!< Time display on COM 4, SEG 10 */
#define ZONE_NUMICRO_DIGIT          5   /*!< NuMicro VER. display on COM 4, SEG 10 */

/* Character define format(SEG)<<4|(COM)<<0) */
/* ZONE_MAIN_DIGIT */
#define SYMBOL_COL_55                       ((4)<<4 | (2)<<0)       // (":" Character between Group 2&3)
#define SYMBOL_COL_59                       ((9)<<4 | (2)<<0)       // (":" Character between Group 3&4)
#define SYMBOL_COL_61                       ((15)<<4 | (2)<<0)      // (":" Character between Group 4&5)
#define SYMBOL_COL_63                       ((19)<<4 | (2)<<0)      // (":" Character between Group 5&6)
#define SYMBOL_COL_65                       ((23)<<4 | (2)<<0)      // (":" Character between Group 6&7)
#define SYMBOL_P_50                         ((4)<<4 | (0)<<0)       // ("." Character between Group 2&3)
#define SYMBOL_P_51                         ((9)<<4 | (0)<<0)       // ("." Character between Group 3&4)
#define SYMBOL_P_52                         ((15)<<4 | (0)<<0)      // ("." Character between Group 4&5)
#define SYMBOL_P_53                         ((19)<<4 | (0)<<0)      // ("." Character between Group 5&6)
#define SYMBOL_P_54                         ((23)<<4 | (0)<<0)      // ("." Character between Group 5&6)
#define SYMBOL_V_11                         ((26)<<4 | (7)<<0)      // ("V" Character T26)
#define SYMBOL_A_12                         ((24)<<4 | (7)<<0)      // ("A" Character T27)
#define SYMBOL_W_13                         ((11)<<4 | (7)<<0)      // ("W" Character T28)
/* ZONE_PPM_DIGIT */
#define SYMBOL_PERCENTAGE_30                ((8)<<4 | (7)<<0)       // ("%" Character Y2)
#define SYMBOL_PPM_31                       ((5)<<4 | (7)<<0)       // ("ppm" Character Y1)
/* ZONE_TEMP_DIGIT */
#define SYMBOL_TEMP_C_35                    ((10)<<4 | (7)<<0)      // ("C" Character T37)
#define SYMBOL_TEMP_F_36                    ((14)<<4 | (7)<<0)      // ("F" Character T38)
/* ZONE_VER_DIGIT */
#define SYMBOL_VERSION_37                   ((18)<<4 | (7)<<0)      // (""Version:" Character )
#define SYMBOL_P_67                         ((16)<<4 | (7)<<0)      // (First "." Character in ZONE_VER_DIGIT )
#define SYMBOL_P_68                         ((20)<<4 | (7)<<0)      // (Second "." Character in ZONE_VER_DIGIT)
/* ZONE_NUMICRO_DIGIT */
#define SYMBOL_NVT_14                       ((6)<<4 | (7)<<0)       // ("nuvoTon" Character T1)
#define SYMBOL_WIFI_16                      ((6)<<4 | (6)<<0)       // (wifi LOGO T2)
#define SYMBOL_SOUND_17                     ((6)<<4 | (5)<<0)       // (Buzzer LOGO T3)
#define SYMBOL_BAT_FRAME_18                 ((6)<<4 | (3)<<0)       // (Battery frame T7)
#define SYMBOL_BAT_1_18                     ((6)<<4 | (1)<<0)       // (Battery level 1 T6)
#define SYMBOL_BAT_2_18                     ((6)<<4 | (0)<<0)       // (Battery leve2 1 T5)
#define SYMBOL_BAT_3_18                     ((6)<<4 | (2)<<0)       // (Battery leve3 1 T4)


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    uint32_t Sub_Zone_Num;      ///< Sub zone number
    uint32_t Zone_Digit_SegNum; ///< Segment number
} ZoneInfo_TypeDef;


/** @addtogroup ML51_LCDVIEW_EXPORTED_FUNCTIONS LCDLIB Exported Functions
  @{
*/
void LCDLIB_Printf(unsigned long u32Zone, char *InputStr);
void LCDLIB_PrintNumber(uint32_t u32Zone, uint32_t InputNum);
void LCDLIB_SetSymbol(uint32_t u32Symbol, uint32_t u32OnOff);

#ifdef __cplusplus
}
#endif

#endif  /* __ML51_LCDLIB_H */

extern char *Zone[];
extern const ZoneInfo_TypeDef LCD_ZoneInfo[];
extern const uint16_t *Zone_TextDisplay[];



