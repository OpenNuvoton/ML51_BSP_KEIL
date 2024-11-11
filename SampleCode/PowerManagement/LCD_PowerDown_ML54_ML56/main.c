/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 GPIO toggle demo code
//***********************************************************************************************************
#include "ml51.h"

unsigned char WKTCT;


void WakeUp_Timer_ISR (void)   interrupt 17     //ISR for self wake-up timer
{

    PUSH_SFRS; 
      WKTCT++;
      clr_WKCON_WKTF;                                   //clear interrupt flag
    POP_SFRS;
}

void LCD_IO_Init(void)
{

/* Enable COM pin MFP */
    MFP_P25_LCD_COM0;
    MFP_P24_LCD_COM1;
    MFP_P23_LCD_COM2;
    MFP_P22_LCD_COM3;
    MFP_P45_LCD_COM4;
    MFP_P44_LCD_COM5;
    MFP_P43_LCD_COM6;
    MFP_P42_LCD_COM7;
/* Enable SEG pin MFP */
    MFP_P41_LCD_SEG27;
    MFP_P40_LCD_SEG26;
    MFP_P63_LCD_SEG25;
    MFP_P62_LCD_SEG24;
    MFP_P61_LCD_SEG23;
    MFP_P60_LCD_SEG22;
    MFP_P14_LCD_SEG21;
    MFP_P15_LCD_SEG20;
    MFP_P16_LCD_SEG19;
    MFP_P17_LCD_SEG18;
    MFP_P46_LCD_SEG17;
    MFP_P47_LCD_SEG16;
    MFP_P33_LCD_SEG15;
    MFP_P32_LCD_SEG14;
    MFP_P31_LCD_SEG13;
    MFP_P30_LCD_SEG12;
    MFP_P67_LCD_SEG11;
    MFP_P66_LCD_SEG10;
    MFP_P65_LCD_SEG9;
    MFP_P64_LCD_SEG8;
    MFP_P27_LCD_SEG7;
    MFP_P26_LCD_SEG6;
    MFP_P21_LCD_SEG5;
    MFP_P20_LCD_SEG4;
    MFP_P35_LCD_SEG3;
    MFP_P34_LCD_SEG2;
    MFP_P07_LCD_SEG1;
    MFP_P06_LCD_SEG0;

    MFP_P11_LCD_DH1;
    MFP_P12_LCD_DH2;
}


//----------------------------------------------------------------------------------------------//
void main (void)
{

  WKT_Open(LIRC, 512, 500);
  WKT_Interrupt(Enable);             // enable WKT interrupt

/* As defaut all multi function define as GPIO */ 
  LCD_IO_Init();

  LCD_Clock_Setting(LIRC, LCD_FREQ_DIV2);
  LCD_Open(TYPE_B, Internal_VCP, LCD_CPVOL_4_6V, BIAS_1_4, LCD_8COM);
  LCD_Current_Mode(Buffer_PowerSave_Mode, TurnOn_1_4);
  LCD_PowerDown_Display(LCD_ON);
  LCD_Enable();

  LCD_SetAllPixels(Enable);
  DISABLE_BOD;
  Timer0_Delay(24000000,2000,1000);
  ENABLE_GLOBAL_INTERRUPT;

/*Disable BOD for the power down current test */
  DISABLE_BOD;
	
  while(1)
  {
/* LCD ON when Powen down. Power consumption under 20uA without LCD panel */
    if (WKTCT&SET_BIT0)
    {
      LCD_PowerDown_Display(LCD_ON);
      set_PCON_PD;
      Timer0_Delay(24000000,1000,1000);
    }
    else if (!(WKTCT&SET_BIT0))
    {
/* LCD OFF Powen down mode with the minimum power consumption. Under 3uA with WKT */
      LCD_VSource_Control(LCD_VSource_Disable);
      LCD_PowerDown_Display(LCD_OFF);
      set_PCON_PD;
      LCD_VSource_Control(Internal_VCP);
      Timer0_Delay(24000000,1000,1000);
    }
  }
while(1);

}



