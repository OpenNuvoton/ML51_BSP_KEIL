/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************
  File Function: ML51 LCD charge pump mode driving test sample code

 *  @brief LCD connect and LCD module circuit shor test based on charge pump interrupt.
 *  @param  u8LCDPowerType  / u8LCDVSource  / u8DrivingType  / u8BiasLevel   / u8ComNum    /u8DrivingVol 
 *  @param   printftemp value adjust is based on LCD panel status adjust, the largest value is 0x3FF.
 *  @return LCD charge pump counter over 0x20 com/seg. 
//***********************************************************************************************************/

#include "ml51.h"

bit lcdintflag;
unsigned int printftemp=0;
unsigned char lcderrorcounter=0;

void LCD_ISR (void) interrupt 31
{
PUSH_SFRS;
  SFRS=3;
  printftemp = ((LCDCPCT1<<8)&0xFF00) + LCDCPCT0;
  if (printftemp>0x40)
  {
      lcdintflag = 1;
  }
  EA = 0 ;
  CALL_NOP;
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
//    MFP_P31_LCD_SEG13;   /* Since MPF same as UART TX  */
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

  unsigned char i,j;
  Enable_UART0_VCOM_printf();
  SFRS=0; printf(" \n LCD Charge Pump Test Start ... "); 
  ALL_GPIO_QUASI_MODE;
  /* As defaut all multi function define as GPIO */ 

  LCD_IO_Init();

  LCD_Clock_Setting(LIRC, LCD_FREQ_DIV2);
  LCD_Open(TYPE_A, Internal_VCP, LCD_CPVOL_4_6V, BIAS_1_4, LCD_8COM);
  LCD_Current_Mode(Buffer_Mode,TurnOn_All);

  LCD_PowerDown_Display(LCD_ON);
  LCD_Enable();
  LCD_SetAllPixels(Enable);

  Timer0_Delay(24000000,500,1000);
  LCD_SetAllPixels(Disable);

  /* Enable LCD chargepump interrupt */
  LCD_Interrupt_Initial(Enable, LCD_CPRD_INT,0);
  ENABLE_GLOBAL_INTERRUPT;
  


/* Routine driving each seg to test LCD module */

  for (i=0;i<8;i++)
    {
      for (j=0;j<32;j++)
        {
           LCD_SetOnePixel(i,j,Enable);
           if (lcdintflag)
            {
              SFRS=0; printf(" \n LCD pump counter = 0x%x",  printftemp);
              printf(" \n LCD com = %bd",  j);printf("     LCD seg = %bd",  i);
              lcderrorcounter++;
              lcdintflag = 0;
            }
            Timer0_Delay(24000000,50,1000);
            EA = 1;
        }
      SFRS=0; printf(" \n LCD test continue ... COM %bx", i); 
    LCD_SetAllPixels(Disable);
    }

    if (lcderrorcounter==0)
    {
       SFRS=0; printf(" \n LCD test all pass ! ");
    }
    else
    {
       SFRS=0; printf(" \n LCD test finish ! Total error = %bd", lcderrorcounter);
    }
    LCD_SetAllPixels(Enable);
    while(1);
}
