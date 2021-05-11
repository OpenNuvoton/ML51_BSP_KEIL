/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "ML51.h"

/**
  * @brief WKT delay interrupt initial setting and timer 1 interrupt vector  
  * @param[in] u32SYSCLK define Fsys clock value. for example 8, use the real Fsys value.
  *                       - \ref LIRC clock base is 38.4k 
  *                       - \ref LXT clock base is 32.768k
  * @param[in] u6DLYUnit define delay time base is us. the minimum delay value not less than 100us, the maxima value base on u32SYSCLK
  *                       - \ref  value range is 10 ~ 100000.  means wakeupt time from about 10ms ~ 100s
  *                       - \ref value range is 1 ~ 100000.  means delay time from about 1ms ~ 100s
  * @note      Delay time value from 10 ~ 100000.  means wakeupt time from about 10mS ~ 100s.
  * @example   WKT_AutoReload_Interrupt_Initial_MS(LIRC,2000);
*/
void WKT_ISR (void) interrupt 17            /* Vector @  0x8B  */
{
_push_(SFRS);
    clr_WKCON_WKTF;
_pop_(SFRS);
}
void WKT_AutoReload_Interrupt_Initial_MS(unsigned char u8WKTCLKSouce, unsigned int u8WKTRLData)
{
   unsigned long WKTCT;

   SFRS = 0; WKCON &= 0xF8; WKCON |= 0x03;     /*fix divider 64: */
    switch (u8WKTCLKSouce)
    {
      case LIRC:
        WKCON &= 0xDF;
        WKTCT = 65535ul-(u8WKTRLData*6ul/10ul);
        SFRS=2; RWKH = HIBYTE (WKTCT);
        SFRS=0; RWKL = LOBYTE (WKTCT);
      break;
      case LXT:
        MFP_P55_X32_IN;
        MFP_P54_X32_OUT;
        set_CKEN_ELXTEN;                        //step3: Enable LXT.
        while(!(CKSWT&SET_BIT6));      //step4: check clock source status and wait for ready
        WKCON |= 0x20;
        WKTCT = 65535ul-(u8WKTRLData*512ul/1000ul);
        SFRS=2; RWKH = HIBYTE (WKTCT);
        SFRS=0; RWKL = LOBYTE (WKTCT);
      break;
    }
    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}
/**
  * @brief WKT delay interrupt initial setting and timer 1 interrupt vector  
  * @param[in] u32SYSCLK define Fsys clock value. for example 8, use the real Fsys value.
  *                       - \ref LIRC clock base is 38.4k 
  *                       - \ref LXT clock base is 32.768k
  * @param[in] u6DLYUnit define delay time base is us. the minimum delay value not less than 100us, the maxima value base on u32SYSCLK
  *                       - \ref  value range is 1 ~ 870.  means wakeupt time from about 10ms ~ 100s
  *                       - \ref value range is 1 ~ 1023.  means delay time from about 1s ~ 100s
  * @note      Always check delay range setting.
  * @example   WKT_AutoReload_Interrupt_Initial_S(LIRC,2);
*/
void WKT_AutoReload_Interrupt_Initial_S(unsigned char u8WKTCLKSouce, unsigned int u8WKTRLData)
{
   unsigned long WKTCT;

   SFRS = 0; WKCON &= 0xF8; WKCON |= 0x05;     /*fix divider 512: */
    switch (u8WKTCLKSouce)
    {
      case LIRC:
        WKCON &= 0xDF;
        WKTCT = 65535ul-(u8WKTRLData*75ul);
        SFRS=2; RWKH = HIBYTE (WKTCT);
        SFRS=0; RWKL = LOBYTE (WKTCT);
      break;
      case LXT:
        MFP_P55_X32_IN;
        MFP_P54_X32_OUT;
        set_CKEN_ELXTEN;                        //step3: Enable LXT.
        while(!(CKSWT&SET_BIT6));      //step4: check clock source status and wait for ready
        WKCON |= 0x20;
        WKTCT = 65535ul-(u8WKTRLData*64ul);
        SFRS=2; RWKH = HIBYTE (WKTCT);
        SFRS=0; RWKL = LOBYTE (WKTCT);
      break;
    }
    ENABLE_WKT_INTERRUPT;
    set_WKCON_WKTR;
}

/**
 * @brief       Wakeup time setting 
 * @param       u8WKTCLKSouce clock source select define (LIRC / LXT)
 * @param       u16WKTDIV WKT counter divider select  (1/4/16/64/256/512/1024/2048)
 * @param       u8WKTRLData reload counter value(Value < 256) 
 * @return      none
 * @details     timer0/1 max_unit=10ms; timer2 max_unit=1s; timer3 max_unit=100ms; all min_unit = 10us;
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
                while((CKSWT|CLR_BIT6)==CLR_BIT6);      //step4: check clock source status and wait for ready
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

