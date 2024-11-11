/**************************************************************************//**
 * @file     lcdlib.h
 * @version  V3.00
 * @brief    RHE6616TP01(8-COM, 40-SEG, 1/4 Bias) LCD library header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2022 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __LCDLIB_H
#define __LCDLIB_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lcdzone.h"

/** @addtogroup Library Library
  @{
*/

/** @addtogroup LCDLIB LCD Library
  @{
*/

/** @addtogroup LCDLIB_EXPORTED_FUNCTIONS LCD Library Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*Digital constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define DIGITAL_SEG_NUM_14         14      /*!< LCD Com Seg Table Number */
#define DIGITAL_SEG_NUM_7           7      /*!< LCD Com Seg Table Number */


void LCDLIB_Printf(uint32_t u32Zone, char *InputStr);
void LCDLIB_PutChar(uint32_t u32Zone, uint32_t u32Index, uint8_t u8Ch);
void LCDLIB_PrintNumber(uint32_t u32Zone, uint32_t InputNum);
void LCDLIB_SetSymbol(uint32_t u32Symbol, uint32_t u32OnOff);


/** @} end of group LCDLIB_EXPORTED_FUNCTIONS */
/** @} end of group LCDLIB */
/** @} end of group Library */

#ifdef __cplusplus
}
#endif

#endif  /* __LCDLIB_H */
