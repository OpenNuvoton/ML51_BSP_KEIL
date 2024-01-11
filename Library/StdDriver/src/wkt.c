/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ml51.h"


#if 0
/**
  * @brief WKT  interrupt vector 
  * @param[in] none
  * @note      none
  * @example   none
*/
void WKT_ISR (void) interrupt 17            /* Vector @  0x8B  */
{
PUSH_SFRS;
    clr_WKCON_WKTF;
POP_SFRS;
}
#endif


/**
  * @NOTICE    ONLY FOR ML56/ML54/ML51 64KB series
  * @brief     WKT delay "ms" level application lib with interrupt initial
  * @param[in] u8WKTCLKSouce define wkt clock source
  *                       - \ref LIRC clock base is 38.4k 
  *                       - \ref LXT clock base is 32.768k
  * @param[in] u16WKTRLData. define the WKT wakeup ms value define. 
  *                       - \ref  value range is 2 ~ 1000.  means wakeupt time from about 2 ~ 1000ms
  * @note      limitation of the  delay time range is 2 ~ 1000ms.the MINIMUM VALUE IS 2MS 
  *            Since fixed with divide 64 means for LIRC the min. step is 1.66ms. for LXT minimum step is 1.95ms
  *            u16WKTRLData = 65536 - (DefineValue * (38400/Divider))/1000
  * @example   ML56_WKT_AutoReload_Interrupt_Initial_MS(100);
*/
void ML56_WKT_AutoReload_Interrupt_Initial_MS(unsigned char u8WKTCLKSouce, unsigned int u16WKTRLData)
{
   unsigned long WKTCT;

   SFRS = 0; WKCON &= 0xF8; WKCON |= 0x03;           //Fix divider 64
    switch (u8WKTCLKSouce)
    {
      case LIRC:
        WKCON &= 0xDF;
        WKTCT = 65535ul-(u16WKTRLData*6ul/10ul);       // 38400/64/1000 = *6ul/10
        SFRS=2; RWKH = HIBYTE(WKTCT);
        SFRS=0; RWKL = LOBYTE (WKTCT);
      break;
      case LXT:
        MFP_P55_X32_IN;
        MFP_P54_X32_OUT;
        set_CKEN_ELXTEN;
        while(!(CKSWT&SET_BIT6));
        WKCON |= 0x20;
        WKTCT = 65535ul-(u16WKTRLData*512ul/1000ul);  // 32768/64/1000 
        SFRS=2; RWKH = HIBYTE (WKTCT);
        SFRS=0; RWKL = LOBYTE (WKTCT);
      break;
    }
    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}

/**
  * @NOTICE    ONLY FOR ML56/ML54/ML51 64KB series
  * @brief     WKT delay "s" level application lib with interrupt initial
  * @param[in] u8WKTCLKSouce define wkt clock source
  *                       - \ref LIRC clock base is 38.4k 
  *                       - \ref LXT clock base is 32.768k
  * @param[in] u16WKTRLData. define the WKT wakeup s value define. 
  *                       - \ref  for LIRC base value range is 1 ~ 3495s. (2048*65535/38400)
  *                       - \ref  for LXT base value range is 1 ~ 4095s. (2048*65535/32768)
  * @note      3600s is one hour.
  * @example   ML56_WKT_AutoReload_Interrupt_Initial_S(100);
*/
void ML56_WKT_AutoReload_Interrupt_Initial_S(unsigned char u8WKTCLKSouce, unsigned int u16WKTRLData)
{
   unsigned long WKTCT;

    SFRS = 0; WKCON &= 0xF8; WKCON |= 0x07;    // Fixed divider 2048
    switch (u8WKTCLKSouce)
    {
      case LIRC:
        WKCON &= 0xDF;
        WKTCT = 65535ul-(u16WKTRLData*75ul/4ul);  // 38400/(512*4)/1000 
        SFRS=2; RWKH = HIBYTE (WKTCT);
        SFRS=0; RWKL = LOBYTE (WKTCT);
      break;
      case LXT:
        MFP_P55_X32_IN;
        MFP_P54_X32_OUT;
        set_CKEN_ELXTEN;
        while(!(CKSWT&SET_BIT6));
        WKCON |= 0x20;
        WKTCT = 65535ul-(u16WKTRLData*64ul/4ul); // 32768/(512*4)/1000 
        SFRS=2; RWKH = HIBYTE (WKTCT);
        SFRS=0; RWKL = LOBYTE (WKTCT);
      break;
    }
    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}



/**
  * @NOTICE    ONLY FOR ML51 32KB/16KB series
  * @brief     WKT delay "ms" level application lib with interrupt initial
  * @param[in] u8WKTCLKSouce define wkt clock source
  *                       - \ref LIRC clock base is 38.4k 
  *                       - \ref LXT clock base is 32.768k
  * @param[in] u16WKTRLData. define the WKT wakeup ms value define. 
  *                       - \ref  value range is 7 ~ 1000.  means wakeupt time from about 2 ~ 1000ms
  * @note      limitation of the  delay time range is 7 ~ 1000ms.the MINIMUM VALUE IS 7MS 
  *            Since fixed with divide 256 means for LIRC the min. step is 6.66ms. for LXT minimum step is 7.81ms
  * @example   ML51_WKT_AutoReload_Interrupt_Initial_MS(300);
*/
void ML51_WKT_AutoReload_Interrupt_Initial_MS(unsigned char u8WKTCLKSouce, unsigned char u8WKTRLData)
{
    unsigned long WKTCT;

    SFRS = 0; WKCON &= 0xF8; WKCON |= 0x04;           //Fix divider 256
    switch (u8WKTCLKSouce)
    {
      case LIRC:
        WKCON &= 0xDF;
        WKTCT = 256ul-(u8WKTRLData*15ul/100);       // 38400/256/1000= *150ul/1000
        SFRS=2; RWKH = 0xFF;
        SFRS=0; RWKL = WKTCT;
      break;
      case LXT:
        MFP_P55_X32_IN;
        MFP_P54_X32_OUT;
        set_CKEN_ELXTEN;
        while(!(CKSWT&SET_BIT6));
        WKCON |= 0x20;
        WKTCT = 256ul-(u8WKTRLData*128ul);         // 32768/64/1000 
        SFRS=2; RWKH = 0xFF;
        SFRS=0; RWKL = WKTCT;
      break;
    }
    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}

/**
  * @NOTICE    ONLY FOR ML51 32KB/16KB series
  * @brief     WKT delay "s" level application lib with interrupt initial
  * @param[in] u8WKTCLKSouce define wkt clock source
  *                       - \ref LIRC clock base is 38.4k 
  *                       - \ref LXT clock base is 32.768k
  * @param[in] u16WKTRLData. define the WKT wakeup s value define. (3600s is one hour)
  *                       - \ref  for LIRC base value range is 1 ~ 13s. (2048*255/38400)
  *                       - \ref  for LXT base value range is 1 ~ 16s. (2048*255/32768)
  * @note      For ML51 32KB and under without RWKH product the " MAXIMUM VALUE IS 16s" 
  * @example   ML51_WKT_AutoReload_Interrupt_Initial_S(10);
*/
void ML51_WKT_AutoReload_Interrupt_Initial_S(unsigned char u8WKTCLKSouce, unsigned char u8WKTRLData)
{
   unsigned long WKTCT;

    SFRS = 0; WKCON &= 0xF8; WKCON |= 0x07;      // Fix divider 2048: 
    switch (u8WKTCLKSouce)
    {
      case LIRC:
        WKCON &= 0xDF;
        WKTCT = 256ul-(u8WKTRLData*75ul/4ul);  // 38400/(512*4)/1000
        SFRS=2; RWKH = 0xFF;
        SFRS=0; RWKL = WKTCT;
      break;
      case LXT:
        MFP_P55_X32_IN;
        MFP_P54_X32_OUT;
        set_CKEN_ELXTEN;
        while(!(CKSWT&SET_BIT6));
        WKCON |= 0x20;
        WKTCT = 256ul-(u8WKTRLData*64ul/4ul);  // 32768/(512*4)/1000 
        SFRS=2; RWKH = 0xFF;
        SFRS=0; RWKL = WKTCT;
      break;
      break;
    }
    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}

/**
 * @brief       Wakeup time setting 
 * @param       u8WKTCLKSouce clock source select define (LIRC / LXT)
 * @param       u16WKTDIV WKT counter divider select  (1/4/16/64/256/512/1024/2048)
 * @param       u8WKTRLData reload counter value(Value < 256) for ML51 32K/16KB series 
 * @param       u8WKTRLData reload counter value(Value < 65536) for ML56/ML54/ML51 64KB series 
 * @return      none
 * @details     Wakeup delay time calculate  = u8WKTRLData * u16WKTDIV  / 38400 or 32768
 * @note        Once timer1 or timer3 use as baudrate generator, please not define as timer delay.
 * @example      WKT_Open (LIRC,256,100);
 */

void WKT_Open(unsigned char  u8WKTCLKSouce, unsigned int u16WKTDIV, unsigned int u8WKTRLData)
{
    SFRS = 0;
    switch (u8WKTCLKSouce)
    {
      case LIRC: WKCON &= 0xDF; break;
      case LXT:  MFP_P55_X32_IN;
                MFP_P54_X32_OUT;
                set_CKEN_ELXTEN;                        //step3: Enable LXT.
                while(!(CKSWT&SET_BIT6));      //step4: check clock source status and wait for ready
                WKCON |= 0x20; break;
    }
    switch (u16WKTDIV)
    {
      case 1: WKCON &= 0xF8; break;
      case 4: WKCON &= 0xF8; WKCON |= 0x01; break;
      case 16: WKCON &= 0xF8; WKCON |= 0x02; break;
      case 64: WKCON &= 0xF8; WKCON |= 0x03; break;
      case 256: WKCON &= 0xF8; WKCON |= 0x04; break;
      case 512: WKCON &= 0xF8; WKCON |= 0x05; break;
      case 1024: WKCON &= 0xF8; WKCON |= 0x06; break;
      case 2048: WKCON &= 0xF8; WKCON |= 0x07; break;
    }
    SFRS=2;
    RWKH = HIBYTE (65535 - u8WKTRLData);
    SFRS=0;
    RWKL = LOBYTE (65535 - u8WKTRLData);
    set_WKCON_WKTR;
}


/**
  * @brief WKT close disable 
*/
void WKT_Close()
{
    clr_WKCON_WKTR;
}


/**
 * @brief       Wakeup time interrupt Enable/disable 
 * @return      WKT_Current_Value
 * @example      WKT_Interrupt(Enable);
 */
void WKT_Interrupt(unsigned char u8WKTINT)
{
    switch (u8WKTINT)
    {
        case Disable: clr_EIE1_EWKT;
        case Enable: set_EIE1_EWKT;
    }
}

