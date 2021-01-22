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

//***********************************************************************************************************
//  File Function: ML51 GPIO toggle demo code
//***********************************************************************************************************
#include "ML51.H"
#include "LCDSubCommon.h"
#include "NKML56.H"

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
void LCD_Init_Setting (void)
{

/* As defaut all multi function define as GPIO */ 
  LCD_IO_Init();

  LCD_Open(TYPE_B, Internal_VCP, LCD_CPVOL_4_6V, BIAS_1_4, LCD_8COM );
  LCD_Clock_Setting(LIRC, LCD_FREQ_DIV2);
  LCD_Current_Mode(Buffer_Mode,TurnOn_All);
  LCD_Blink(Disable,4);
  LCD_PowerDown_Display(LCD_ON);
  LCD_Enable();

}
	
void LCD_frame1 (void)
{
	unsigned long temp;
	LCD_SetOnePixel(0,27,0);
/* Show logo and battery level */
    LCDLIB_SetSymbol(3, 20, 1);
    LCDLIB_SetSymbol(3, 23, 1);
    LCDLIB_SetSymbol(3, 24, 1);
    LCDLIB_SetSymbol(3, 26, 1);
    
/*Show Zone0 */
  LCDLIB_PrintCharacter(0, "*ML56*");
   
/* Show temperature */  
  temp = internal_Temperature(); 
  LCDLIB_PrintNumber(1,temp,1);
  LCDLIB_SetSymbol(3, 15, 1);

/* Show bsp version */
  LCDLIB_PrintNumber(2,200001,1);
  LCDLIB_SetSymbol(3, 17, 1);
  LCDLIB_SetSymbol(3, 18, 1);
  LCDLIB_SetSymbol(3, 19, 1);

}

void LCD_frame2 (void)
{

//  LCD_SetAllPixels(Enable);
/* Show logo and battery level */
    LCDLIB_SetSymbol(3, 20, 1);
    LCDLIB_SetSymbol(3, 23, 1);
    LCDLIB_SetSymbol(3, 24, 1);
    LCDLIB_SetSymbol(3, 26, 1);
    
/*Show Zone0 */
  LCDLIB_PrintCharacter(0, "TOUCH");

/* Show counter */
  LCDLIB_PrintNumber(1,(tkct<<12),0);
  LCDLIB_SetSymbol(3, 15, 0);
/* Show bsp version */
  LCDLIB_PrintNumber(2,200001,1);
  LCDLIB_SetSymbol(3, 17, 1);
  LCDLIB_SetSymbol(3, 18, 1);
  LCDLIB_SetSymbol(3, 19, 1);
}

void LCD_RTC_Display (void)
{
}
