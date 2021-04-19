/**************************************************************************//**
 * @file     LCDLIB.h
 * @version  V1.01
 * $Revision: 4 $
 * $Date: 14/11/28 1:48p $
 * @brief    Nano 102/112 series LCDLIB header file
 *
 * @note
 * Copyright (C) 2013~2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NANO1X2_LCDLIB_H
#define __NANO1X2_LCDLIB_H

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup NANO1X2_Library NANO102/112 Library
  @{
*/

/** @addtogroup NANO1X2_LCDLIB_Driver LCD Library
  @{
*/


/** @addtogroup NANO1X2_LCDLIB_EXPORTED_STRUCTS LCDLIB Exported Structs
  @{
*/

typedef struct
{
    uint32_t Sub_Zone_Num;      ///< Sub zone number
    uint32_t Zone_Digit_SegNum; ///< Segment number
} ZoneInfo_TypeDef;

/*@}*/ /* end of group NANO1X2_LCDLIB_EXPORTED_STRUCTS */


/** @addtogroup NANO1X2_LCDLIB_EXPORTED_FUNCTIONS LCDLIB Exported Functions
  @{
*/

void LCDLIB_PrintCharacter(uint16_t  u16Zone, char *string);
void LCDLIB_Zone0PutChar(uint16_t u16Zone, uint16_t u16Index, uint8_t u8Ch);
void LCDLIB_SetSymbol(unsigned char u8Zone, unsigned char u8Index, unsigned char u8OnOff);
void LCDLIB_PrintNumber(uint16_t  u16Zone, long value, unsigned char u8OnOff);
void LCDLIB_SetScale(uint16_t u16Zone, uint16_t u16Index);




#ifdef __cplusplus
}
#endif

#endif  /* __NANO1X2_LCDLIB_H */


extern char *Zone[];
extern const ZoneInfo_TypeDef LCD_ZoneInfo[];
extern const uint16_t *Zone_TextDisplay[];

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/

