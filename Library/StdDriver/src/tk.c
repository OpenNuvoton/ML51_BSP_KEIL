/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ML51.h"

/**
  * @brief      Enable touch key function
  * @param[in]  none
  * @return     none
  * @example    TK_Open();
  */  
void TK_Open(void)
{
    unsigned int i;
    unsigned char* ptr; 
    TKCON0 |= TK_TKCON0_TK_EN_Msk;
    ptr = &TKIDLPOL0;
    for (i=0; i<=14; i=i+1)
    {
        *(ptr+i) &= ~(TK_TKIDLPOL_IDLSx_Msk | TK_TKIDLPOL_POLx_Msk);
    }
}

/**
  * @brief      Disable touch key function
  * @param      None
  * @return     None
  * @example    TK_Close();
  */
void TK_Close(void)
{
    TKCON0 &= ~TK_TKCON0_TK_EN_Msk; 
}

/**
  * @brief      Set touch key scan mode
  * @param[in]  u32Mode Single ,periodic or all key scan mode
  *                   - \ref TK_SCAN_MODE_SINGLE
  *                   - \ref TK_SCAN_MODE_PERIODIC
  *                   - \ref TK_SCAN_MODE_ALL_KEY
  *                   - \ref TK_SCAN_MODE_PERIODIC_ALL_KEY
  * @return     None
  * @details    This function is used to set touch key scan mode.
  * @note       If touch key controller sets as periodic mode, touch key will be trigger scan by RTC timer. So RTC timer must be enabled and operated in periodic mode.
  *             If touch key controller sets as single scan mode, touch key can be trigger scan by calling TK_START_SCAN().
  * @example    TK_SetScanMode(TK_SCAN_MODE_SINGLE);
  */
void TK_SetScanMode(unsigned long u32Mode)
{
    TKCON0 &= ~(TK_TKCON0_TMRTRG_EN_Msk | TK_TKCON0_SCAN_ALL_Msk);
    if(u32Mode == TK_SCAN_MODE_PERIODIC)
    {
        TKCON0 |= TK_TKCON0_TMRTRG_EN_Msk;
    }
    else if(u32Mode == TK_SCAN_MODE_ALL_KEY)
    {
        TKCON0 |= TK_TKCON0_SCAN_ALL_Msk;
    }
    else if(u32Mode == TK_SCAN_MODE_PERIODIC_ALL_KEY)
    {
        TKCON0 |= (TK_TKCON0_TMRTRG_EN_Msk | TK_TKCON0_SCAN_ALL_Msk);
    }
}

/**
  * @brief      Configure touch key scan sensitivity
  * @param[in]  u32PulseWidth Sensing pulse width
  *                   - \ref TK_SENSE_PULSE_P5
  *                   - \ref TK_SENSE_PULSE_1
  *                   - \ref TK_SENSE_PULSE_2
  *                   - \ref TK_SENSE_PULSE_4
  *                   - \ref TK_SENSE_PULSE_8
  * @param[in]  u32SenseCnt Sensing count
  *                   - \ref TK_SENSE_CNT_16
  *                   - \ref TK_SENSE_CNT_32
  *                   - \ref TK_SENSE_CNT_64
  *                   - \ref TK_SENSE_CNT_128
  *                   - \ref TK_SENSE_CNT_255
  *                   - \ref TK_SENSE_CNT_511
  *                   - \ref TK_SENSE_CNT_1023
  * @param[in]  u32AVCCHSel voltage selection
  *                   - \ref TK_AVCCH_1_DIV_16
  *                   - \ref TK_AVCCH_1_DIV_8
  *                   - \ref TK_AVCCH_3_DIV_16
  *                   - \ref TK_AVCCH_1_DIV_4
  *                   - \ref TK_AVCCH_5_DIV_16
  *                   - \ref TK_AVCCH_3_DIV_8
  *                   - \ref TK_AVCCH_7_DIV_16
  *                   - \ref TK_AVCCH_1_DIV_2
  *                   - \ref TK_AVCCH_1_DIV_32
  *                   - \ref TK_AVCCH_2_DIV_32
  *                   - \ref TK_AVCCH_3_DIV_32
  *                   - \ref TK_AVCCH_4_DIV_32
  *                   - \ref TK_AVCCH_5_DIV_32
  *                   - \ref TK_AVCCH_6_DIV_32
  *                   - \ref TK_AVCCH_7_DIV_32
  *                   - \ref TK_AVCCH_8_DIV_32
  * @return     None
  * @details    This function is used to configure touch key scan sensitivity.
  * @example    TK_ConfigSensitivity(TK_SENSE_PULSE_1, TK_SENSE_CNT_128, TK_AVCCH_1_DIV_2);
  */
void TK_ConfigSensitivity(unsigned long u32PulseWidth, unsigned long u32SenseCnt, unsigned long u32AVCCHSel)
{
    TKCON1 = (TKCON1 & ~(TK_TKCON1_PULSET_Msk| TK_TKCON1_SENSET_Msk)) |\
	                 (u32PulseWidth | u32SenseCnt);
    TKCON0 = (TKCON0 & ~TK_TKCON0_AVDDH_S_Msk) | u32AVCCHSel; 
}

/**
  * @brief      Set touch key capacitor bank polarity
  * @param[in]  u32CapBankPolSel capacitor bank polarity selection
  *                   - \ref TK_CAP_BANK_POL_SEL_GND
  *                   - \ref TK_CAP_BANK_POL_SEL_AVCCH
  *                   - \ref TK_CAP_BANK_POL_SEL_VDD
  * @return     None
  * @details    This function is used to set touch key capacitor bank polarity.
  * @example    TK_SetCapBankPol(TK_CAP_BANK_POL_SEL_VDD);
  */
void TK_SetCapBankPol(unsigned long u32CapBankPolSel)
{
    TKCON2 = (TKCON2 & ~TK_TKCON2_POL_CAP_Msk) | u32CapBankPolSel;	
}

/**
  * @brief      Configure touch key polarity
  * @param[in]  u32Mask: Combination of touch keys which need to be configured
  *                      Bit 0 represents touch key 0, bit 1 represents touch key 1...
  * @param[in]  u32PolSel: Touch key polarity selection
  *                   - \ref TK_TKn_POL_SEL_GND
  *                   - \ref TK_TKn_POL_SEL_AVCCH
  *                   - \ref TK_TKn_POL_SEL_VDD
  * @return     None
  * @details    This function is used to configure touch key polarity.
  * @example    TK_SetTkPol(1<<14, TK_TKn_POL_SEL_VDD);
  */
void TK_SetTkPol(unsigned long u32Mask, unsigned long u32PolSel)
{
    unsigned long i;
    unsigned char *ptr;

    ptr = &TKIDLPOL0;
    for(i = 0 ; i <= 14 ; i++)
    {
        if((1ul << i) & u32Mask)
            *(ptr+i) = ( *(ptr+i) & ~(TK_TKIDLPOL_POLx_Msk) |  (u32PolSel << TK_TKIDLPOL_POLx_Pos));
    }
}

/**
  * @brief      Enable the polarity of specified touch key(s)
  * @param[in]  u32Mask: Combination of enabled scan keys. Each bit corresponds to a touch key
  *                      Bit 0 represents touch key 0, bit 1 represents touch key 1...
  * @return     None
  * @details    This function is used to enable the polarity of specified touch key(s).
  * @example    TK_EnableTkPolarity(u32Mask);
  */
void TK_EnableTkPolarity(unsigned long u32Mask)
{
    unsigned int i;
    unsigned char *ptr;
    ptr = &TKIDLPOL0;
    for(i = 0; i <= 14; i = i+1)
    {
        if(u32Mask & (1<<i))
            *(ptr+i) |= TK_TKIDLPOL_POLENx_Msk;
    }
}

/* Never used, remove for 8051 code size due to C51 didn't support One ELF Section per Function*/
#if 1 
/**
  * @brief      Disable the polarity of specified touch key(s)
  * @param[in]  u32Mask: Combination of enabled scan keys. Each bit corresponds to a touch key
  *                      Bit 0 represents touch key 0, bit 1 represents touch key 1...
  * @return     None
  * @details    This function is used to disable the polarity of specified touch key(s).
  * @example    TK_DisableTkPolarity(u32Mask);
  */
void TK_DisableTkPolarity(unsigned long u32Mask)
{
    uint32_t i;
    unsigned char *ptr;
    ptr = &TKIDLPOL0;
    for(i = 0; i <= 14; i = i+1)
    {
        if(u32Mask & (1<<i))
            *(ptr+i) &= ~TK_TKIDLPOL_POLENx_Msk;
    }	
}
#endif

/**
  * @brief      Set complement capacitor bank data of specified touch key
  * @param[in]  u32TKNum: Touch key number. The valid value is 0~15.  if u32TKNum = 15, it means to set TKCCBDALL register for SCAN_ALL function.  
  * @param[in]  u32CapData: Complement capacitor bank data. The valid value is 0~0xFF.
  * @return     None
  * @details    This function is used to set complement capacitor bank data of specified touch key.
  * @example    TK_SetCompCapBankData(u32TKNum);
  */
void TK_SetCompCapBankData(unsigned long u32TKNum, unsigned long u32CapData)
{
    unsigned char *ptr = &TKCCBD0+u32TKNum;
    *ptr = (unsigned char)u32CapData;
}

/**
  * @brief      Set complement capacitor bank data of reference touch key for scan all function 
  * @param[in]  u32CapData Complement capacitor bank data. The valid value is 0~0xFF.
  * @return     None
  * @details    This function is used to set complement capacitor bank data of reference touch key.
  * @example    TK_SetCompCapBankData(u32Mask);
  */
void TK_SetRefKeyCapBankData(unsigned long u32CapData)
{/* In ML56, each channel has own reference capacitor data. The funcution will be used if SCAN_ALL */
    REFCBDALL = (unsigned char)u32CapData;
}


/** 
  * ML56 Only
  * @brief      Set reference capacitor bank data of specified touch key
  * @param[in]  u32TKNum: Touch key number. The valid value is 0~15. if u32TKNum = 15, it means to set REFCBDALL register for SCAN_ALL function.  
  * @param[in]  u32CapData: Complement capacitor bank data. The valid value is 0~0xFF.
  * @return     None
  * @details    This function is used to set complement capacitor bank data of reference touch key.
  * @example    TK_SetRefCapBankData(u32ChannelNo, u32CapData);
  */
     
void TK_SetRefCapBankData(unsigned long u32TKNum, unsigned long u32CapData)
{
    unsigned char *ptr = &REFCBD0;
    ptr = ptr+u32TKNum;
    *ptr = (unsigned char)u32CapData;
}
/**
  * @brief      Set high and low threshold of specified touch key for threshold control interrupt
  * @param[in]  u32TKNum: Touch key number. The valid value is 0~15. if u32TKNum = 15, it means to set the high thresohld for SCAN_ALL function
  * @param[in]  u32HighLevel: High level for touch key threshold control. The valid value is 0~0xFF.
  * @param[in]  u32LowLevel: Low level for touch key threshold control. ML56 had removes low threshold setting
  * @return     None
  * @details    This function is used to set high and low threshold of specified touch key for threshold control interrupt.
  * @example    TK_SetScanThreshold(u32ChannelNo, u32HighTHreshold, NULL);
  */
void TK_SetScanThreshold(unsigned long u32TKNum, unsigned long u32HighLevel, unsigned long u32LowLevel)
{
    unsigned char *ptr = &TKHTH0;
    ptr = ptr+u32TKNum;
    *ptr = (unsigned char)u32HighLevel;
    u32HighLevel = u32LowLevel;
}

/**
  * @brief      Enable touch key scan interrupts
  * @param[in]  u32Msk Interrupt type selection.
  *                   - \ref TK_INT_EN_SCAN_COMPLETE
  *                   - \ref TK_INT_EN_SCAN_COMPLETE_EDGE_TH
  * @return     None
  * @details    This function is used to enable touch key scan interrupt.
  * @note       It need disable the enabled interrupt type first by TK_DisableInt() before to change enabled interrupt type.
  * @example    TK_EnableInt(TK_INT_EN_SCAN_COMPLETE);
  */
void TK_EnableInt(unsigned long u32Msk)
{
    TKINTEN |= u32Msk;
}

/**
  * @brief      Disable touch key scan interrupts
  * @param[in]  u32Msk Interrupt type selection.
  *                   - \ref TK_INT_EN_SCAN_COMPLETE
  *                   - \ref TK_INT_EN_SCAN_COMPLETE_EDGE_TH
  * @return     None
  * @details    This function is used to disable touch key scan interrupt.
  * @example :  TK_DisableInt(TK_INT_EN_SCAN_COMPLETE);
  */
void TK_DisableInt(unsigned long u32IntMsk)
{
    TKINTEN &= ~u32IntMsk;	
}


/**
  * @brief      To get the TK data after scan complete
  * @param[in]  u32TKNum: Touch key number. The valid value is 0~15. if u32TKNum = 15, it means to get the TKDATALL register for SCAN_ALL function
  * @return     Scan data for specified channel or scan all function. 
  * @details    This function is used to get scan data after scan complete
  * @example :  u8Data = TK_GET_SENSE_DATA(1);
  */
unsigned char TK_GET_SENSE_DATA(unsigned char u8TKNum)                            
{                          
    unsigned char *ptr;     
    ptr = &TKDAT0+(unsigned int)u8TKNum; 
    return *ptr;            
}


/**
  * @brief      To specified the bit mask for the reference channel
  * @param[in]  u16TKChanBitMsk: The bit mask of touch key number. The valid value is (1<<0) or (1<<1).... or (1<<14). 
  *                              Bit 0 represents touch key 0, bit 1 represents touch key 1...
  * @return     None
  * @details    This function is used to specified the reference channel. 
  * @example :  TK_SetReferenceChannel(0x4000);
  */
void TK_SetReferenceChannel(unsigned int u16TKChanBitMsk)
{
    if(u16TKChanBitMsk <= 0x80)
    {
        TKREN0 = (unsigned char)u16TKChanBitMsk;
        TKREN1 = 0;
    }
    else
    {
        TKREN1 = (u16TKChanBitMsk>>8);
        TKREN0 = 0;
    }
}

/**
  * @brief      To enable the scan channels
  * @param[in]  u16TKChanBitMsk: The combination bits mask of touch key channels. 
  *                              Bit 0 represents touch key 0, bit 1 represents touch key 1...
  * @return     None
  * @details    This function is used to enable the channels for key scan. 
  * @example :  TK_EnableChannel(0x001E);
  */
void TK_EnableChannel(unsigned int u16TKChanBitMsk)
{
    if( (u16TKChanBitMsk&0xFF) != 0)
        TKSEN0 = TKSEN0 | (u16TKChanBitMsk&0xFF);
    if( ((u16TKChanBitMsk>>8)&0xFF) != 0)
        TKSEN1 = TKSEN1 | (u16TKChanBitMsk>>8);
}

/**
  * @brief      To disable the scan channels
  * @param[in]  u16TKChanBitMsk the combination bits mask of touch key channels. 
  * @return     None
  * @details    This function is used to disable the channels for key scan. 
  * @example :  TK_DisableChannel(0x001E);
  */
void TK_DisableChannel(unsigned int u16TKChanBitMsk)
{
    if( (u16TKChanBitMsk&0xFF) != 0)
        TKSEN0 &= ~(u16TKChanBitMsk&0xFF);
    if( ((u16TKChanBitMsk>>8)&0xFF) != 0)
        TKSEN1 &= ~(u16TKChanBitMsk>>8);
}

/**
  * @brief      To disable all channels
  * @param[in]  None
  * @return     None
  * @details    This function is used to disable all channels for key scan. 
  * @example :  TK_DisableAllChannel();
  */
void TK_DisableAllChannel(void)
{
    TKSEN0 = 0;
    TKSEN1 = 0;
}


/**
  * @brief      To clear all interrupts that were caused if the conversion TK data over the high threshold. 
  * @param[in]  None
  * @return     None
  * @details    This function is used to clear all interrupts that were caused if the conversion TK data over the high threshold. 
  * @example :  TK_ClearTKIF();
  */
void TK_ClearTKIF(void)
{
    TKSTA1 = 0;
    TKSTA2 = 0;
}


/**
  * @brief      To enable scan all function to wake up system by any touch keys as low power mode  
  * @param[in]  u8RefcbAll: The value co-works with u8CcbAll to make conversion all enabled touch keys' data - TKDATALL close to 0.
  * @param[in]  u8CcbAll: The value co-works with u8RefcbAll to make conversion all enabled touch keys' data - TKDATALL close to 0.
  * @param[in]  u8HThAll: Threshold to wake up system by any touch keys as low power mode
  * @return     None
  * @details    The u8RefcbAll and u8CcbAll are the calibration values was generate by calibration flow
  *	            The flow makes the TKDATALL close to 0 after scan all enabled all touch keys.
  * @example :  TK_EnableScanAll(165, 110, 30);
  */
void TK_EnableScanAll(unsigned char u8RefcbAll, unsigned char u8CcbAll, unsigned char u8HThAll)
{
    TKCON0 |= TK_TKCON0_SCAN_ALL_Msk;
	REFCBDALL = u8RefcbAll;
	TKCCBDALL = u8CcbAll;
	TKHTHALL = u8HThAll;
}


/**
  * @brief      To disable scan all function to wake up system by any touch keys as low power mode  
  * @param[in]  None
  * @return     None
  * @example :  TK_DisableScanAll();
  */
void TK_DisableScanAll(void)
{
    TKCON0 &= ~TK_TKCON0_SCAN_ALL_Msk;
}
/*** (C) COPYRIGHT 2019~2020 Nuvoton Technology Corp. ***/

