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
//  File Function: ML51 power down code for test power down current, BOD disabled.
//***********************************************************************************************************
#include "ML51.h"


void main (void) 
{
  unsigned char i;

/*As Default all GPIO multi function is GPIO mode */ 
/*Quasi mode better for power down power comsuption */  
  ALL_GPIO_QUASI_MODE;
  P0=0;
  P1=0;
  P2=0;
  P3=0;
  P4=0;
  P5=0;
  SFRS=2;P6=0;SFRS=0;
/* clock only for reference, real chip please don't output clock*/  
  set_CKCON_CLOEN;
/*MUST DISABLE BOD to low power */
  DISABLE_BOD;              //BOD enable power down current please check datasheet DC charactor.
  
  while(P01);
  for (i=0;i<0x05;i++)
  {
    P3 = ~P3;
    _delay_();
  }
/* Real into power down mode */
  set_PCON_PD;
  while(1);
  
}



