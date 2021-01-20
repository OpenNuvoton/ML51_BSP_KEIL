/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/29/2020
//***********************************************************************************************************

/***********************************************************************************************************
*  File Function: ML51 RTC Alarm code
* @Note 12-Hour Time 12:00:00 AM ~ 11:59:59AM / 12:00:00PM ~ 11:59:59PM
*       24-Hour Time 00:00:00    ~ 11:59:59   / 12:00:00 ~ 23:59:59
*       For 12-Hour Time avoid 00:00:00 AM/PM 
*       For all Time setting avoid 25:61:61 
*       For Year data avoid 19xx/13/32
***********************************************************************************************************/

#include "ML51.H"

bit rtc_alarm_flag=0;

void RTC_ISR(void) interrupt 30
{
    clr_RTCINTSTS_ALMIF;
    rtc_alarm_flag = 1;
    RTC_Interrupt_Disable(RTC_ALARM);
}

//----------------------------------------------------------------------------------------------//
void main (void)
{
    S_RTC_TIME_DATA_T sCurTime;
    Enable_UART0_VCOM_printf();

/*RTC clock source setting  */ /* system clock is HIRC */
  ClockEnable(FSYS_LXT);     /* Before select LXT as RTC clock source. Only enable LXT for RTC */ 
  RTC_Clock_Select(LXT);
/*RTC initial  */
  RTC_Initial_Pause();
  RTC_SetDate(2020,8,11,2);
  RTC_SetTime(23,59,58,RTC_CLOCK_24,0);
/*RTC Alarm timing setting   */
  RTC_SetAlarmDate(2020,8,12);
  RTC_SetAlarmTime(12,00,11,RTC_CLOCK_12,RTC_AM);
/*RTC interrupt setting   */
  RTC_Interrupt_Enable(RTC_ALARM);
  ENABLE_GLOBAL_INTERRUPT;
/*RTC run  */
  RTC_Initial_Run();

/*RTC result print  */
  RTC_GetDateAndTime(&sCurTime);    /* Print initial setting data & time */
  SFRS=0;  printf(" Current Time:%d/%bd/%bd %bd:%bd:%bd",sCurTime.u16Year,sCurTime.u8Month,sCurTime.u8Day,sCurTime.u8Hour,sCurTime.u8Minute,sCurTime.u8Second);
        if (sCurTime.u8AmPm==1)
        printf("  AM");
      else if (sCurTime.u8AmPm==2)
        printf("  PM");
      printf("\n");

  RTC_GetAlarmDateAndTime(&sCurTime); /* Print setting alarm data & time */
  SFRS=0;  printf(" RTC Alarm setting Time:%d/%bd/%bd %bd:%bd:%bd",sCurTime.u16Year,sCurTime.u8Month,sCurTime.u8Day,sCurTime.u8Hour,sCurTime.u8Minute,sCurTime.u8Second);
        if (sCurTime.u8AmPm==1)
          printf("  AM");
        else if (sCurTime.u8AmPm==2)
          printf("  PM");
        printf("\n");

  SFRS=0;printf(" RTC Start Tick and Wait Alarm.... \n");

  while(!rtc_alarm_flag);
  RTC_GetDateAndTime(&sCurTime);    /* When alarm interrupt print current time */  SFRS=0;   printf(" Current Time:%d/%bd/%bd %bd:%bd:%bd",sCurTime.u16Year,sCurTime.u8Month,sCurTime.u8Day,sCurTime.u8Hour,sCurTime.u8Minute,sCurTime.u8Second);
      if (sCurTime.u8AmPm==1)
        printf("  AM");
      else if (sCurTime.u8AmPm==2)
        printf("  PM");
      printf("\n");
      printf("\n");

  while(1);

}

