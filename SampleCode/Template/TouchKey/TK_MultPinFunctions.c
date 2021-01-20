/**************************************************************************//**
 * @file     TK_Utility.c
 * @version  V1.00
 * $Revision: 4 $
 * $Date: 9/15/20 10:28a $
 * @brief    Some Utility Funcion for Calibration Using.
 * @note
 * Copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "ML51.h"
#include "TKLib.h"
#include "TK_Demo.h"

/**************************************************************************//**
 * P0MF10 means The multiple function pin register for P0's pin 1 & pin 0. So on and so forth.
 * All Multiple function pin use SFR Page 2
 *
 * P0MF10 Base F9H, P0MF32 Base FAH, P0MF54 Base FBH, P0MF76 Base FCH,
 * P1MF10 Base FDH, P1MF32 Base FEH. P1MF54 Base FFH, P1MF76 Base F1H,
 * P2MF10 Base F2H, P2MF32 Base F3H, P2MF54 Base F4H, P2MF76 Base F5H,
 * P3MF10 Base F6H, P3MF32 Base F7H, P3MF54 Base E9H, P3MF76 Base EAH,
 * P4MF10 Base EBH, P4MF32 Base FCH, P4MF54 Base EDH, P4MF76 Base EEH,
 * P5MF10 Base EFH, P5MF32 Base E1H, P5MF54 Base E2H, P5MF76 Base E3H,
 * P6MF10 Base 92H, P6MF32 Base 93H, P6MF54 Base 94H, P6MF76 Base 95H,
 ******************************************************************************/

/**************************************************************************//**
  * @brief      Configure multi-function pin to touch key function
  * @param[in]  u16TkMsk Combination of enabled scan keys. Each bit corresponds to a touch key.
  *             Bit 0 represents touch key 0, bit 1 represents touch key 1...
  * @retval     None.
  * @details    This function is used to configure multi-function pin to touch key function
 ******************************************************************************/
void SetTkMultiFun(uint32_t u32TkMsk)
{
    /* Avoid using the pointer to set multiple pin function registers */
    uint32_t i;
	uint32_t u32Shielding;
	
	u32Shielding = TK_GetEnabledChannelMask(TK_SHIELDING);
	
    SFRS=0x02;
    for (i = 0; i < (TKLIB_TOL_NUM_KEY + 3); i++)
    {
        if ((1ul << i) & u32TkMsk)
        {
            switch(i)
            {
            case 0:/* P5.6 */
                P5MF76 = (P5MF76 & 0xF0) | 10;
                if(u32Shielding == 0x1)
                {
					//DBG_PRINTF("Shielding TK0 CKO\n");
                    MFP_P56_CLKO;
                    P56_QUASI_MODE;
                    TKCON1 |= 0x8;
                }
                break;
            case 1:/* P0.0 */
                P0MF10 = (P0MF10 & 0xF0) | 10;
                break;
            case 2:/* P0.1 */
                P0MF10 = (P0MF10 & 0x0F) | (10<<4);
                break;
            case 3:/* P0.2 */
                P0MF32 = (P0MF32 & 0xF0) | 10;
                break;
            case 4:/* P0.3 */
                P0MF32 = (P0MF32 & 0x0F) | (10<<4);
                if(u32Shielding == 0x10)
                {
					//DBG_PRINTF("Shielding TK4 CKO\n");
                    MFP_P03_CLKO;
                    P03_QUASI_MODE;
                    TKCON1 |= 0x8;
                }
                break;
            case 5:/* P0.4 */
                P0MF54 = (P0MF54 & 0xF0) | 10;
                break;
            case 6:/* P0.5 */
                P0MF54 = (P0MF54 & 0x0F) | (10<<4);
                break;
            case 7:/* P3.6 */
                P3MF76 = (P3MF76 & 0xF0) | 10;
                break;
            case 8:/* P6.3 */
                P6MF32 = (P6MF32 & 0x0F) | (10<<4);
                break;
            case 9:/* P6.2 */
                P6MF32 = (P6MF32 & 0xF0) | 10;
                break;
            case 10:/* P6.1 */
                P6MF10 = (P6MF10 & 0x0F) | (10<<4);
                break;
            case 11:/* P6.0 */
                P6MF10 = (P6MF10 & 0xF0) | 10;
                break;

            case 12:/* P4.4 */
                P4MF54 = (P4MF54 & 0xF0) | 10;
                break;
            case 13:/* P4.3 */
                P4MF32 = (P4MF32 & 0x0F) | (10<<4);
                break;
            case 14:/* P4.2 */
                P4MF32 = (P4MF32 & 0xF0) | 10;
                break;
            case 15:/* P3.2 CKO shielding only*/
				//DBG_PRINTF("Shielding 32 CKO\n");
                MFP_P32_CLKO;
                P32_QUASI_MODE;
                TKCON1 |= 0x8;
                break;
            case 16:/* P4.6 CKO shielding only */
				//DBG_PRINTF("Shielding P46 CKO\n");
                MFP_P46_CLKO;
                P46_QUASI_MODE;
                TKCON1 |= 0x8;
                break;
            case 17:/* P5.7 CKO shielding only*/
				//DBG_PRINTF("Shielding 57 CKO\n");
                MFP_P57_CLKO;
                P57_QUASI_MODE;
                TKCON1 |= 0x8;
                break;
            }
        }
    }
    SFRS=0x00;
}
