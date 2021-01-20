/**************************************************************************//**
 * @file     tk.h
 * @version  V1.00
 * $Revision: 6 $
 * $Date: 15/04/30 4:52p $
 * @brief    ML56 Series TK Driver Header File
 *
 * @note
 * Copyright (C) 2019~2020 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __TK_H__
#define __TK_H__
//#include "TK_Reg.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern xdata volatile unsigned char TK_BA[0x60];  
/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup TK_Driver TK Driver
  @{
*/

/** @addtogroup TK_EXPORTED_CONSTANTS TK Exported Constants
  @{
*/

#define TK_SCAN_MODE_SINGLE                 (0UL)  /*!< Touch key single scan mode */
#define TK_SCAN_MODE_PERIODIC               (TK_TKCON0_TMRTRG_EN_Msk)  /*!< Touch key periodic scan mode */
#define TK_SCAN_MODE_ALL_KEY                (TK_TKCON0_SCAN_ALL_Msk)  /*!< Touch key all keys scan mode */
#define TK_SCAN_MODE_PERIODIC_ALL_KEY       (TK_TKCON0_TMRTRG_EN_Msk | TK_TKCON0_SCAN_ALL_Msk)  /*!< Touch key periodic with all keys scan mode */

#define TK_SENSE_PULSE_P5                   (0UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 500ns */
#define TK_SENSE_PULSE_1                    (1UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 1us */
#define TK_SENSE_PULSE_2                    (2UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 2us */
#define TK_SENSE_PULSE_4                    (3UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 4us */
#define TK_SENSE_PULSE_8                    (4UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 8us */

#define TK_SENSE_CNT_16                     (0UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 128 */
#define TK_SENSE_CNT_32                     (1UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 255 */
#define TK_SENSE_CNT_64                     (2UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 511 */
#define TK_SENSE_CNT_128                    (3UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 128 */
#define TK_SENSE_CNT_255                    (4UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 255 */
#define TK_SENSE_CNT_511                    (5UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 511 */
#define TK_SENSE_CNT_1023                   (6UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 1023 */


#define TK_AVCCH_1_DIV_16                   (0UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 2/32 VDD */
#define TK_AVCCH_1_DIV_8                    (1UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 4/32 VDD */
#define TK_AVCCH_3_DIV_16                   (2UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 6/32 VDD */
#define TK_AVCCH_1_DIV_4                    (3UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 8/32 VDD */
#define TK_AVCCH_5_DIV_16                   (4UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 10/32 VDD */
#define TK_AVCCH_3_DIV_8                    (5UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 12/32 VDD */
#define TK_AVCCH_7_DIV_16                   (6UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 14/32 VDD */
#define TK_AVCCH_1_DIV_2                    (7UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 16/32 VDD */
#define TK_AVCCH_1_DIV_32                   (8UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 1/32 VDD */
#define TK_AVCCH_2_DIV_32                   (9UL << TK_TKCON0_AVDDH_S_Pos)  /*!< Touch key AVCCH voltage is 2/32 VDD */
#define TK_AVCCH_3_DIV_32                   (0xAUL << TK_TKCON0_AVDDH_S_Pos)/*!< Touch key AVCCH voltage is 3/32 VDD */
#define TK_AVCCH_4_DIV_32                   (0xBUL << TK_TKCON0_AVDDH_S_Pos)/*!< Touch key AVCCH voltage is 4/32 VDD */
#define TK_AVCCH_5_DIV_32                   (0xCUL << TK_TKCON0_AVDDH_S_Pos)/*!< Touch key AVCCH voltage is 5/32 VDD */
#define TK_AVCCH_6_DIV_32                   (0xDUL << TK_TKCON0_AVDDH_S_Pos)/*!< Touch key AVCCH voltage is 6/32 VDD */
#define TK_AVCCH_7_DIV_32                   (0xEUL << TK_TKCON0_AVDDH_S_Pos)/*!< Touch key AVCCH voltage is 7/32 VDD */
#define TK_AVCCH_8_DIV_32                   (0xFUL << TK_TKCON0_AVDDH_S_Pos)/*!< Touch key AVCCH voltage is 8/32 VDD */

#define TK_CAP_BANK_POL_SEL_GND             (0UL << TK_TKCON2_POL_CAP_Pos)  /*!< Touch key capacitor bank polarity is GND */
#define TK_CAP_BANK_POL_SEL_AVCCH           (1UL << TK_TKCON2_POL_CAP_Pos)  /*!< Touch key capacitor bank polarity is AVCCH */
#define TK_CAP_BANK_POL_SEL_VDD             (3UL << TK_TKCON2_POL_CAP_Pos)  /*!< Touch key capacitor bank polarity is VDD */


#define TK_TKn_POL_SEL_GND                  (0UL)  /*!< Touch key polarity is GND */
#define TK_TKn_POL_SEL_AVCCH                (1UL)  /*!< Touch key polarity is AVCCH */
#define TK_TKn_POL_SEL_VDD                  ( 3UL )  /*!< Touch key polarity is VDD */

#define TK_INT_EN_SCAN_COMPLETE             (TK_TKINTEN_SCIE_Msk)   /*!< Touch key enable scan complete interrupt */
#define TK_INT_EN_SCAN_COMPLETE_EDGE_TH     (TK_TKINTEN_SCTHIE_Msk) /*!< Touch key enable scan complete with threshold interrupt of edge trigger mode */


#define TK_INT_SCAN_COMPLETE                (TK_TKSTA0_SCIF_Msk)  /*!< Touch key scan complete interrupt */
#define TK_INT_SCAN_COMPLETE_TH_ALL         (0x1FFFF02UL)  /*!< Touch key scan complete or all touch keys threshold control interrupt */
#define TK_INT_SCAN_TH_ALL                  (0x1FFFF00UL)  /*!< ALL Touch key threshold control interrupt */
#define TK_INT_SCAN_TH_TK0                  (TK_TKSTA1_TKIF0_Msk)  /*!< Touch key 0 threshold control interrupt */
#define TK_INT_SCAN_TH_TK1                  (TK_TKSTA1_TKIF1_Msk)  /*!< Touch key 1 threshold control interrupt */
#define TK_INT_SCAN_TH_TK2                  (TK_TKSTA1_TKIF2_Msk)  /*!< Touch key 2 threshold control interrupt */
#define TK_INT_SCAN_TH_TK3                  (TK_TKSTA1_TKIF3_Msk)  /*!< Touch key 3 threshold control interrupt */
#define TK_INT_SCAN_TH_TK4                  (TK_TKSTA1_TKIF4_Msk)  /*!< Touch key 4 threshold control interrupt */
#define TK_INT_SCAN_TH_TK5                  (TK_TKSTA1_TKIF5_Msk)  /*!< Touch key 5 threshold control interrupt */
#define TK_INT_SCAN_TH_TK6                  (TK_TKSTA1_TKIF6_Msk)  /*!< Touch key 6 threshold control interrupt */
#define TK_INT_SCAN_TH_TK7                  (TK_TKSTA1_TKIF7_Msk)  /*!< Touch key 7 threshold control interrupt */
#define TK_INT_SCAN_TH_TK8                  (TK_TKSTA2_TKIF8_Msk)  /*!< Touch key 8 threshold control interrupt */
#define TK_INT_SCAN_TH_TK9                  (TK_TKSTA2_TKIF9_Msk)  /*!< Touch key 9 threshold control interrupt */
#define TK_INT_SCAN_TH_TK10                 (TK_TKSTA2_TKIF10_Msk) /*!< Touch key 10 threshold control interrupt */
#define TK_INT_SCAN_TH_TK11                 (TK_TKSTA2_TKIF11_Msk) /*!< Touch key 11 threshold control interrupt */
#define TK_INT_SCAN_TH_TK12                 (TK_TKSTA2_TKIF12_Msk) /*!< Touch key 12 threshold control interrupt */
#define TK_INT_SCAN_TH_TK13                 (TK_TKSTA2_TKIF13_Msk) /*!< Touch key 13 threshold control interrupt */
#define TK_INT_SCAN_TH_TK14                 (TK_TKSTA2_TKIF14_Msk) /*!< Touch key 14 threshold control interrupt */

/*@}*/ /* end of group TK_EXPORTED_CONSTANTS */


/** @addtogroup TK_EXPORTED_FUNCTIONS TK Exported Functions
  @{
*/

/**
 * @brief Enable scan key(s)
 * @param[in] u32Mask Combination of enabled scan keys. Each bit corresponds to a touch key.
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * @note Touch key 16 is the default reference key, so touch key 16 is enabled.
 * \hideinitializer
 */

#define TK_ENABLE_SCAN_KEY(u32Mask) {\
                                      if( (u32Mask&0xFF) != 0 )\
	                                      TKSEN0 = (u32Mask&0xFF);\
	                                  if( ((u32Mask>>8)&0xFF) != 0 )\
                                          TKSEN1 = ((u32Mask>>8)&0xFF);\
                                    }
/**
 * @brief Disable scan key(s)
 * @param[in] u32Mask Combination of disabled scan keys. Each bit corresponds to a touch key.
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * \hideinitializer
 */

#define TK_DISABLE_SCAN_KEY(u32Mask) {\
                                        if( (u32Mask&0xFF) != 0 )\
	                                        TKSEN0 &= ~(u32Mask&0xFF);\
	                                    if( ((u32Mask>>8)&0xFF) != 0 )\
                                            TKSEN1 &= ~((u32Mask>>8)&0xFF);\
                                     }									

/**
 * @brief Enable reference key(s)
 * @param[in] u32Mask Combination of enabled reference keys. Each bit corresponds to a touch key.
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * @note Touch key 16 is the default reference key, so touch key 16 is enabled.
 * \hideinitializer
 */
#define TK_ENABLE_REF_KEY(u32Mask) {\
                                       if( (u32Mask&0xFF) != 0 )\
	                                       TKREN0 = (u32Mask&0xFF);\
	                                   if( ((u32Mask>>8)&0xFF) != 0 )\
                                           TKREN1 = ((u32Mask>>8)&0xFF);\
                                   }									
/**
 * @brief Disable reference key(s)
 * @param[in] u32Mask Combination of disabled reference keys. Each bit corresponds to a touch key.
 *                           Bit 0 represents touch key 0, bit 1 represents touch key 1...
 * @return None
 * @note It must enable a reference key and touch key 16 is the default reference key.
 *       If no any one touch key as reference key except touch key 16, then reference Touch key 16 can't be disable.
 * \hideinitializer
 */
#define TK_DISABLE_REF_KEY(u32Mask) {\ 
                                      if( (u32Mask&0xFF) != 0 )\
	                                      TKREN0 &= ~(u32Mask&0xFF);\
	                                  if( ((u32Mask>>8)&0xFF) != 0 )\
                                          TKREN1 &= ~((u32Mask>>8)&0xFF);\
                                    }
/**
 * @brief Initiate enabled key(s) scan immediately.
 * @param None
 * @return None
 * \hideinitializer
 */
#define TK_START_SCAN() (TKCON0 |= TK_TKCON0_SCAN_Msk)									

/**
 * @brief Set touch key Sensing pulse width.
 * @param[in] u32PulseWidth Sensing pulse width.
			    - \ref TK_SENSE_PULSE_P5
 *              - \ref TK_SENSE_PULSE_1
 *              - \ref TK_SENSE_PULSE_2
 *              - \ref TK_SENSE_PULSE_4
 *              - \ref TK_SENSE_PULSE_8
 * @return None
 * \hideinitializer
 */
#define TK_SET_PULSE_WIDTH(u32PulseWidth) (TKCON1 = (TKCON1 & ~TK_TKCON1_PULSET_Msk) | (u32PulseWidth))

/**
 * @brief Set touch key Sensing count.
 * @param[in] u32SenseCnt Sensing count.
 *              - \ref TK_SENSE_CNT_128
 *              - \ref TK_SENSE_CNT_255
 *              - \ref TK_SENSE_CNT_511
 *              - \ref TK_SENSE_CNT_1023
 * @return None
 * \hideinitializer
 */
#define TK_SET_SENSING_CNT(u32SenseCnt) (TKCON1 = (TKCON1 & ~TK_TKCON1_SENSET_Msk) | (u32SenseCnt))


/**
 * @brief Set touch key AVCCH voltage.
 * @param[in] u32AVCCHSel voltage selection.
 *              - \ref TK_AVCCH_1_DIV_16
 *              - \ref TK_AVCCH_1_DIV_8
 *              - \ref TK_AVCCH_3_DIV_16
 *              - \ref TK_AVCCH_1_DIV_4
 *              - \ref TK_AVCCH_5_DIV_16
 *              - \ref TK_AVCCH_3_DIV_8
 *              - \ref TK_AVCCH_7_DIV_16
 *              - \ref TK_AVCCH_1_DIV_2
 *
 *              - \ref TK_AVCCH_1_DIV_32
 *              - \ref TK_AVCCH_2_DIV_32
 *              - \ref TK_AVCCH_3_DIV_32
 *              - \ref TK_AVCCH_4_DIV_32
 *              - \ref TK_AVCCH_5_DIV_32
 *              - \ref TK_AVCCH_6_DIV_32
 *              - \ref TK_AVCCH_7_DIV_32
 *              - \ref TK_AVCCH_8_DIV_32
 * @return None
 * \hideinitializer
 */
#define TK_SET_AVCCH(u32AVCCHSel) (TKCON0 = (TKCON0 & ~TK_TKCON0_AVDDH_S_Msk) | (u32AVCCHSel))

/**
 * @brief Get touch key busy status.
 * @param None
 * @retval 0 Touch key is scan completed or stopped.
 * @retval 1 Touch key is busy.
 * \hideinitializer
 */
#define TK_IS_BUSY() ((TKSTA0 & TK_TKSTA0_BUSY_Msk) ? 1: 0)									

/**
 * @brief Get touch key interrupt flag.
 * @param[in] u32Mask Interrupt flag type selection.
 *              - \ref TK_INT_SCAN_COMPLETE
 *              - \ref TK_INT_SCAN_COMPLETE_TH_ALL
 *              - \ref TK_INT_SCAN_TH_ALL
 *              - \ref TK_INT_SCAN_TH_TK0
 *              - \ref TK_INT_SCAN_TH_TK1
 *              - \ref TK_INT_SCAN_TH_TK2
 *              - \ref TK_INT_SCAN_TH_TK3
 *              - \ref TK_INT_SCAN_TH_TK4
 *              - \ref TK_INT_SCAN_TH_TK5
 *              - \ref TK_INT_SCAN_TH_TK6
 *              - \ref TK_INT_SCAN_TH_TK7
 *              - \ref TK_INT_SCAN_TH_TK8
 *              - \ref TK_INT_SCAN_TH_TK9
 *              - \ref TK_INT_SCAN_TH_TK10
 *              - \ref TK_INT_SCAN_TH_TK11
 *              - \ref TK_INT_SCAN_TH_TK12
 *              - \ref TK_INT_SCAN_TH_TK13
 *              - \ref TK_INT_SCAN_TH_TK14
 * @retval 0 Touch key has no interrupt.
 * @retval 1 Touch key is scan completed or threshold control event occurs.
 * \hideinitializer
 */

#define TK_GET_INT_STATUS(u32Mask) ( (TKSTA0 & u32Mask) ? 1 : 0 )
/**
 * @brief Clear touch key interrupt flag.
 * @param[in] u32Mask Interrupt flag type selection.
 *              - \ref TK_INT_SCAN_COMPLETE
 *              - \ref TK_INT_SCAN_COMPLETE_TH_ALL
 *              - \ref TK_INT_SCAN_TH_ALL
 *              - \ref TK_INT_SCAN_TH_TK0
 *              - \ref TK_INT_SCAN_TH_TK1
 *              - \ref TK_INT_SCAN_TH_TK2
 *              - \ref TK_INT_SCAN_TH_TK3
 *              - \ref TK_INT_SCAN_TH_TK4
 *              - \ref TK_INT_SCAN_TH_TK5
 *              - \ref TK_INT_SCAN_TH_TK6
 *              - \ref TK_INT_SCAN_TH_TK7
 *              - \ref TK_INT_SCAN_TH_TK8
 *              - \ref TK_INT_SCAN_TH_TK9
 *              - \ref TK_INT_SCAN_TH_TK10
 *              - \ref TK_INT_SCAN_TH_TK11
 *              - \ref TK_INT_SCAN_TH_TK12
 *              - \ref TK_INT_SCAN_TH_TK13
 *              - \ref TK_INT_SCAN_TH_TK14
 * @return None
 * \hideinitializer
 */
/* Write 0 clear */
#define TK_CLR_INT_FLAG(u32Mask) {\
    switch(u32Mask)\
    {\
        case TK_INT_SCAN_COMPLETE:\
	    TKSTA0 &= ~TK_TKSTA0_SCIF_Msk;\
        break;\
        case TK_INT_SCAN_COMPLETE_TH_ALL:\
            TKSTA0 &= ~(TK_TKSTA0_SCIF_Msk|TK_TKSTA0_TKIF_Msk|TK_TKSTA0_TKIF_ALL_Msk);\
            TKSTA1 = 0;\
            TKSTA2 = 0;\
        break;\
        default:\
        if(u32Mask&0xFF)\
            TKSTA1 = TKSTA1&~(u32Mask&0xFF);\
	if((u32Mask>>8)&0xFF)\
            TKSTA2 = TKSTA2&~((u32Mask>>8)&0xFF);\
        break;\
    }\	
 }


/*---------------------------------------------------------------------------------------------------------*/
/* Define TK functions prototype                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
void TK_Open(void);
void TK_Close(void);
void TK_SetScanMode(unsigned long u32Mode);
void TK_ConfigSensitivity(unsigned long  u32PulseWidth, unsigned long  u32SenseCnt, unsigned long  u32AVCCHSel);
void TK_SetCapBankPol(unsigned long  u32CapBankPolSel);
void TK_EnableTkPolarity(unsigned long  u32Mask);
void TK_DisableTkPolarity(unsigned long  u32Mask);
void TK_SetCompCapBankData(unsigned long  u32TKNum, unsigned long  u32CapData);
void TK_SetChannelRefKeyCapBankData(unsigned long  u32TKNum, unsigned long  u32CapData);
void TK_SetTkPol(unsigned long  u32Mask, unsigned long  u32PolSel);
void TK_SetRefKeyCapBankData(unsigned long  u32CapData);
void TK_SetRefCapBankData(unsigned long  u32TKNum, unsigned long  u32CapData);
void TK_SetScanThreshold(unsigned long  u32TKNum, unsigned long  u32HighLevel, unsigned long  u32LowLevel);
void TK_EnableInt(unsigned long  u32Msk);
void TK_DisableInt(unsigned long  u32Msk);
unsigned char TK_GET_SENSE_DATA(unsigned char u32TKNum);
							 
								 
void TK_SetReferenceChannel(unsigned int  u16TKChanBitMsk);
void TK_EnableChannel(unsigned int u16TKChanBitMsk);
void TK_DisableChannel(unsigned int u16TKChanBitMsk);
void TK_DisableAllChannel(void);

/*@}*/ /* end of group TK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group TK_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__TK_H__

/*** (C) COPYRIGHT 2014~2015 Nuvoton Technology Corp. ***/
