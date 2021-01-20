/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

#include "ML51.h"
static volatile unsigned char g_u8Reg, g_u8Reg1,g_u8hiYear,g_u8loYear,g_u8hiMonth,g_u8loMonth,g_u8hiDay,g_u8loDay;
static volatile unsigned char g_u8hiHour,g_u8loHour,g_u8hiMin,g_u8loMin,g_u8hiSec,g_u8loSec,g_u8DataTmp;

void _RTC_RWEN_(void)
{
    while(!(RTCRWEN&SET_BIT0));
}

void RTC_Initial_Run(void)
{
   SFRS=3;TA=0xAA;TA=0x55;RTCINIT=0x57; 
}

void RTC_Initial_Pause(void)
{
   SFRS=3;TA=0xAA;TA=0x55;RTCINIT=0x5F;
}

/**
 *  @brief    RTC clock source select
 *  @param[in]    u8RTCClockSource \n
 *                     Specify the RTC clock source. It includes: \n
 *                     LIRC: RTC clock source is LIRC                      \n
 *                     LXT: RTC clock source is LXT                        \n
 *  @return   None
 *  @example RTC_Clock_Select(LIRC);
 */
void RTC_Clock_Select(unsigned char u8RTCClockSource)
{
    switch (u8RTCClockSource)
    {
        case LIRC: set_RTCCLKSEL_C32KS; break;
        case LXT:  clr_RTCCLKSEL_C32KS; break;
    }
}

/**
 *  @brief    RTC tick time select
 *  @param[in]    u8RTCTickSel \n
 *                     Specify the RTC tick base . It includes: \n
 *                     For TK (touch key) power down scan  base suggest 3 or 4 \n
 *                     0 = Time tick is 1 second.                      \n
 *                     1 = Time tick is 1/2 second.                    \n
 *                     2 = Time tick is 1/4 second.                    \n
 *                     3 = Time tick is 1/8 second.                    \n
 *                     4 = Time tick is 1/16 second.                   \n
 *                     5 = Time tick is 1/32 second.                   \n
 *                     6 = Time tick is 1/64 second.                   \n
 *                     7 = Time tick is 1/128 second.                  \n
 *  @return   None
 *  @example RTC_Tick_Select(3);
 */
void RTC_Tick_Select(unsigned char u8RTCTickSel)
{
    SFRS=3; 
    RTC_RWEN;RTCTICK=0;
    RTC_RWEN;RTCTICK|=u8RTCTickSel;
}

/**
 *  @brief    RTC Interrupt enable setting
 *  @param[in]    u8RTCIntType \n
 *                     Specify the Interrupt type. It includes: \n
 *                     RTC_TIME_TICK: interrupt base on tick select             \n
 *                     RTC_ALARM: interrupt base on alarm setting               \n
 *  @return   None
 *  @example RTC_Interrupt_Enable(RTC_ALARM);
 */
void RTC_Interrupt_Enable(unsigned char u8RTCIntType)
{
    SFRS=3; RTC_RWEN;
    switch (u8RTCIntType)
    {
      case RTC_TIME_TICK: clr_RTCINTSTS_TICKIF; set_RTCINTEN_TICKIEN; break;
      case RTC_ALARM: clr_RTCINTSTS_ALMIF;set_RTCINTEN_ALMIEN;clr_RTCINTEN_TICKIEN; break;
    }
}

/**
 *  @brief    RTC Interrupt disable setting
 *
 *  @param[in]    u8RTCIntType \n
 *                     Specify the Interrupt should be disable type. It includes: \n
 *                     RTC_TIME_TICK: interrupt base on tick                      \n
 *                     RTC_ALARM: interrupt base on alarm setting                 \n
 *  @return   None
 *  @example RTC_Interrupt_Disable(RTC_ALARM);
 */
void RTC_Interrupt_Disable(unsigned char u8RTCIntType)
{
    SFRS=3; RTC_RWEN;
    switch (u8RTCIntType)
    {
      case RTC_TIME_TICK: clr_RTCINTEN_TICKIEN; break;
      case RTC_ALARM: clr_RTCINTEN_ALMIEN; break;
    }
}

/**
 *  @brief    This function is used to update date to RTC
 *
 *  @param[in]    u32Year       The Year Calendar Digit of Alarm Setting
 *  @param[in]    u32Month      The Month Calendar Digit of Alarm Setting
 *  @param[in]    u32Day        The Day Calendar Digit of Alarm Setting
 *  @param[in]    u32DayOfWeek  The Day of Week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                 \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                 \ref RTC_SATURDAY ]
 *  @return   None
 *  @Example  RTC_SetDate(2016,10,21,6);
 */
void RTC_SetDate(unsigned int u16Year, unsigned int u8Month, unsigned int u8Day, unsigned char u8DayOfWeek)
{
    SFRS = 3;
    RTC_RWEN;  RTCWEEKDAY = u8DayOfWeek; 
      g_u8DataTmp  = (((u16Year - RTC_YEAR2000) / 10) << 4);
      g_u8DataTmp |= (((u16Year - RTC_YEAR2000) % 10)& 0x0F);
    RTC_RWEN; RTCCALYEAR = g_u8DataTmp; 
      g_u8DataTmp  = ((u8Month  / 10) << 4);
      g_u8DataTmp |= ((u8Month  % 10) & 0x0F); 
    RTC_RWEN; RTCCALMON = g_u8DataTmp; 
      g_u8DataTmp  = ((u8Day/ 10) << 4);
      g_u8DataTmp |= ((u8Day    % 10) & 0x0F);
    RTC_RWEN; RTCCALDAY = g_u8DataTmp; 
}


/**
 *  @brief    This function is used to update time to RTC.
 *
 *  @param[in]    u8Hour     The Hour Time Digit of Alarm Setting.
 *  @param[in]    u8Minute   The Month Calendar Digit of Alarm Setting
 *  @param[in]    u8Second   The Day Calendar Digit of Alarm Setting
 *  @param[in]    u8TimeMode The 24-Hour / 12-Hour Time Scale Selection. [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]
 *  @param[in]    u8AmPm     12-hour time scale with AM and PM indication. Only Time Scale select 12-hour used. [ \ref RTC_AM / \ref RTC_PM]
 *  @return       None
 *  @example      RTC_SetTime(23,59,58,RTC_CLOCK_24,0);
 *
 */
void RTC_SetTime(unsigned int u8Hour, unsigned int u8Minute, unsigned char u8Second, unsigned char u8TimeMode, unsigned char u8AmPm)
{
  SFRS = 3;
    if (u8TimeMode == RTC_CLOCK_12) 
    {
      RTC_RWEN; clr_RTCCLKFMT_24HEN;
        if (u8AmPm == RTC_PM)    /* important, range of 12-hour PM mode is 21 upto 32 */
            u8Hour += 20;
    } 
    else if(u8TimeMode == RTC_CLOCK_24) 
    {
       RTC_RWEN; set_RTCCLKFMT_24HEN;
    }
      g_u8DataTmp   = ((u8Hour / 10) << 4);
      g_u8DataTmp  |= ((u8Hour % 10) & 0x0F);
    RTC_RWEN;  RTCTIMEHR =  g_u8DataTmp;
      g_u8DataTmp   = ((u8Minute / 10) << 4);
      g_u8DataTmp  |= ((u8Minute % 10) & 0x0F);
    RTC_RWEN;  RTCTIMEMIN = g_u8DataTmp;
      g_u8DataTmp   = ((u8Second / 10) << 4);
      g_u8DataTmp  |= ((u8Second % 10) & 0x0F);
    RTC_RWEN;  RTCTIMESEC = g_u8DataTmp;
}


/**
 *  @brief    This function is used to set alarm date to RTC
 *  @param[in]    u16Year    The Year Calendar Digit of Alarm Setting
 *  @param[in]    u8month   The Month Calendar Digit of Alarm Setting
 *  @param[in]    u8Day     The Day Calendar Digit of Alarm Setting
 *  @return   None
 *  @example      RTC_SetAlarmDate(2016,10,22);
 */
void RTC_SetAlarmDate(unsigned int u16Year, unsigned char u8Month, unsigned char u8Day)
{
    SFRS = 3;
      g_u8DataTmp  = (((u16Year - RTC_YEAR2000) / 10) << 4);
      g_u8DataTmp |= (((u16Year - RTC_YEAR2000) % 10)& 0x0F);
    RTC_RWEN; RTCCALMYEAR = g_u8DataTmp;
      g_u8DataTmp  = ((u8Month  / 10) << 4);
      g_u8DataTmp |= ((u8Month  % 10) & 0x0F); 
    RTC_RWEN; RTCCALMMON = g_u8DataTmp;
      g_u8DataTmp  = ((u8Day    / 10) << 4);
      g_u8DataTmp |= ((u8Day    % 10) & 0x0F);
    RTC_RWEN; RTCCALMDAY = g_u8DataTmp;
}


/**
 *  @brief    This function is used to set alarm date to RTC
 *  @param[in]     u8Hour     The Hour Time Digit of Alarm Setting.
 *  @param[in]     u8Minute   The Month Calendar Digit of Alarm Setting
 *  @param[in]     u8Second   The Day Calendar Digit of Alarm Setting
 *  @param[in]     u8TimeMode The 24-Hour / 12-Hour Time Scale Selection. [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]
 *  @param[in]     u8AmPm     12-hour time scale with AM and PM indication. Only Time Scale select 12-hour used. [ \ref RTC_AM / \ref RTC_PM]
 *  @return   None
 *  @example        RTC_SetAlarmTime(12,00,5,RTC_CLOCK_12,RTC_AM);
 */
void RTC_SetAlarmTime(unsigned char u8Hour, unsigned char u8Minute, unsigned char u8Second, unsigned char u8TimeMode, unsigned char u8AmPm)
{
   SFRS=3;
   if (u8TimeMode == RTC_CLOCK_12) 
    {
      RTC_RWEN; clr_RTCCLKFMT_24HEN;
        if (u8AmPm == RTC_PM)    /* important, range of 12-hour PM mode is 0x21 upto 0x32 */
            u8Hour += 20;
    } 
    else if(u8TimeMode == RTC_CLOCK_24) 
    {
        RTC_RWEN; set_RTCCLKFMT_24HEN; u8AmPm =0;
    }
      g_u8DataTmp   = ((u8Hour / 10) << 4);
      g_u8DataTmp  |= ((u8Hour % 10) & 0x0F);
    RTC_RWEN;  RTCTALMHR =  g_u8DataTmp;
      g_u8DataTmp   = ((u8Minute / 10) << 4);
      g_u8DataTmp  |= ((u8Minute % 10) & 0x0F);
    RTC_RWEN;  RTCTALMMIN = g_u8DataTmp;
      g_u8DataTmp   = ((u8Second / 10) << 4);
      g_u8DataTmp  |= ((u8Second % 10) & 0x0F);
    RTC_RWEN;  RTCTALMSEC = g_u8DataTmp;
}


/**
 *  @brief    Read current date/time from RTC setting
 *  @param[out]    sPt \n
 *                     Specify the time property and current time. It includes: \n
 *                     u16Year: Year value                                      \n
 *                     u8Month: Month value                                    \n
 *                     u8Day: Day value                                        \n
 *                     u8DayOfWeek: Day of week                                \n
 *                     u8Hour: Hour value                                      \n
 *                     u8Minute: Minute value                                  \n
 *                     u8Second: Second value                                  \n
 *                     u8TimeScale: \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24          \n
 *                     u8AmPm: \ref RTC_AM / \ref RTC_PM                            \n
 *  @return   None
 *  @example RTC_GetDateAndTime(&sCurTime);
 */
void RTC_GetDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    unsigned long u32Tmp;
    SFRS = 3;
    RTC_RWEN; g_u8DataTmp = RTCCLKFMT;
      sPt->u8TimeScale = (g_u8DataTmp&SET_BIT0);    /* 12/24-hour */
    RTC_RWEN;
      sPt->u8DayOfWeek = RTCWEEKDAY;           /* Day of week */

    RTC_RWEN; g_u8DataTmp = RTCCALYEAR;
      g_u8hiYear  = ((g_u8DataTmp&0xF0)>>4);
      g_u8loYear  = (g_u8DataTmp&0x0F);
    RTC_RWEN; g_u8DataTmp = RTCCALMON;
      g_u8hiMonth = ((g_u8DataTmp&0xF0)>>4);
      g_u8loMonth = (g_u8DataTmp&0x0F);
    RTC_RWEN; g_u8DataTmp = RTCCALDAY;
      g_u8hiDay   = ((g_u8DataTmp&0xF0)>>4);
      g_u8loDay   = (g_u8DataTmp&0x0F);

    RTC_RWEN; g_u8DataTmp = RTCTIMEHR;
      g_u8hiHour =  ((g_u8DataTmp&0xF0)>>4);
      g_u8loHour =  (g_u8DataTmp&0x0F);
    RTC_RWEN; g_u8DataTmp = RTCTIMEMIN;
      g_u8hiMin  =  ((g_u8DataTmp&0xF0)>>4);
      g_u8loMin  =  (g_u8DataTmp&0x0F);
    RTC_RWEN; g_u8DataTmp = RTCTIMESEC;
      g_u8hiSec  =  ((g_u8DataTmp&0xF0)>>4);
      g_u8loSec  =  (g_u8DataTmp&0x0F);

    u32Tmp  = (g_u8hiYear * 10);              /* Compute to 20XX year */
    u32Tmp += g_u8loYear;
    sPt->u16Year = (u32Tmp&0x0000FFFF) + RTC_YEAR2000;

    u32Tmp = (g_u8hiMonth * 10);              /* Compute 0~12 month */
    sPt->u8Month =  (u32Tmp&0x000000FF) + g_u8loMonth;

    u32Tmp = (g_u8hiDay * 10);                /* Compute 0~31 day */
    sPt->u8Day   =   (u32Tmp&0x000000FF)  + g_u8loDay;

    if (sPt->u8TimeScale == RTC_CLOCK_12) { /* Compute12/24 hour */
        u32Tmp = (g_u8hiHour * 10);
        u32Tmp+= g_u8loHour;
        sPt->u8Hour =  (u32Tmp&0x000000FF);                 /* AM: 1~12. PM: 0x21~0x32. */

        if (sPt->u8Hour > 20) {
            sPt->u8AmPm = RTC_PM;
            sPt->u8Hour -= 20;
        } else {
            sPt->u8AmPm = RTC_AM;
        }

        u32Tmp = (g_u8hiMin  * 10);
        u32Tmp+= g_u8loMin;
        sPt->u8Minute =  (u32Tmp&0x000000FF);

        u32Tmp = (g_u8hiSec  * 10);
        u32Tmp+= g_u8loSec;
        sPt->u8Second =  (u32Tmp&0x000000FF);

    } else {
        u32Tmp  = (g_u8hiHour * 10);
        u32Tmp += g_u8loHour;
        sPt->u8Hour = (u32Tmp&0x000000FF);

        u32Tmp  = (g_u8hiMin * 10);
        u32Tmp +=  g_u8loMin;
        sPt->u8Minute = (u32Tmp&0x000000FF);

        u32Tmp  = (g_u8hiSec * 10);
        u32Tmp += g_u8loSec;
        sPt->u8Second = (u32Tmp&0x000000FF);
    }

}

/**
 *  @brief    Read alarm date/time from RTC setting
 *  @param[out]    sPt \n
 *                     Specify the time property and current time. It includes: \n
 *                     u16Year: Year value                                      \n
 *                     u32Month: Month value                                    \n
 *                     u32Day: Day value                                        \n
 *                     u32DayOfWeek: Day of week                                \n
 *                     u32Hour: Hour value                                      \n
 *                     u32Minute: Minute value                                  \n
 *                     u32Second: Second value                                  \n
 *                     u32TimeScale: \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24          \n
 *                     u8AmPm: \ref RTC_AM / \ref RTC_PM                            \n
 *
 *  @return   None
 *  @example RTC_GetAlarmDateAndTime(&sCurTime);
 */
void RTC_GetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    unsigned long u32Tmp;
    SFRS=3;
    RTC_RWEN;  g_u8DataTmp = RTCCLKFMT;
      sPt->u8TimeScale = (g_u8DataTmp&SET_BIT0);    /* 12/24-hour */
    RTC_RWEN;
      sPt->u8DayOfWeek = RTCWEEKDAY;          /* Day of week */

    RTC_RWEN; g_u8DataTmp = RTCCALMYEAR;
      g_u8hiYear  = ((g_u8DataTmp&0xF0)>>4);
      g_u8loYear  = (g_u8DataTmp&0x0F);
    RTC_RWEN; g_u8DataTmp = RTCCALMMON;
      g_u8hiMonth = ((g_u8DataTmp&0xF0)>>4);
      g_u8loMonth = (g_u8DataTmp&0x0F);
    RTC_RWEN; g_u8DataTmp = RTCCALMDAY;
      g_u8hiDay   = ((g_u8DataTmp&0xF0)>>4);
      g_u8loDay   = (g_u8DataTmp&0x0F);

    RTC_RWEN; g_u8DataTmp = RTCTALMHR;
      g_u8hiHour =  ((g_u8DataTmp&0xF0)>>4);
      g_u8loHour =  (g_u8DataTmp&0x0F);
    RTC_RWEN; g_u8DataTmp = RTCTALMMIN;
      g_u8hiMin  =  ((g_u8DataTmp&0xF0)>>4);
      g_u8loMin  =  (g_u8DataTmp&0x0F);
    RTC_RWEN; g_u8DataTmp = RTCTALMSEC;
      g_u8hiSec  =  ((g_u8DataTmp&0xF0)>>4);
      g_u8loSec  =  (g_u8DataTmp&0x0F);
  
   u32Tmp  = (g_u8hiYear * 10);              /* Compute to 20XX year */
    u32Tmp += g_u8loYear;
    sPt->u16Year = (u32Tmp&0x0000FFFF) + RTC_YEAR2000;

    u32Tmp = (g_u8hiMonth * 10);              /* Compute 0~12 month */
    sPt->u8Month =  (u32Tmp&0x000000FF) + g_u8loMonth;

    u32Tmp = (g_u8hiDay * 10);                /* Compute 0~31 day */
    sPt->u8Day   =   (u32Tmp&0x000000FF)  + g_u8loDay;

    if (sPt->u8TimeScale == RTC_CLOCK_12) { /* Compute12/24 hour */
        u32Tmp = (g_u8hiHour * 10);
        u32Tmp+= g_u8loHour;
        sPt->u8Hour =  (u32Tmp&0x000000FF);                 /* AM: 1~12. PM: 21~32. */

        if (sPt->u8Hour >  20) {
            sPt->u8AmPm = RTC_PM;
            sPt->u8Hour -= 20;
        } else {
            sPt->u8AmPm = RTC_AM;
        }

        u32Tmp = (g_u8hiMin  * 10);
        u32Tmp+= g_u8loMin;
        sPt->u8Minute =  (u32Tmp&0x000000FF);

        u32Tmp = (g_u8hiSec  * 10);
        u32Tmp+= g_u8loSec;
        sPt->u8Second =  (u32Tmp&0x000000FF);

    } else {
        u32Tmp  = (g_u8hiHour * 10);
        u32Tmp += g_u8loHour;
        sPt->u8Hour = (u32Tmp&0x000000FF);

        u32Tmp  = (g_u8hiMin * 10);
        u32Tmp +=  g_u8loMin;
        sPt->u8Minute = (u32Tmp&0x000000FF);

        u32Tmp  = (g_u8hiSec * 10);
        u32Tmp += g_u8loSec;
        sPt->u8Second = (u32Tmp&0x000000FF);
        sPt->u8AmPm = 0;
    }
}
 
