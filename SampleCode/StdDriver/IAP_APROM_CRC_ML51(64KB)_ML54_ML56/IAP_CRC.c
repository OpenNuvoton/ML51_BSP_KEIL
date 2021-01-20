/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Sep/16/2020
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: ML51 IAP program DATAFLASH demo code
//***********************************************************************************************************
#include "ML51.h"


/* @note    For printf code only. Disable this define to reduce code size. */
#if 1
#define  print_function
#endif 
/* @note    BOD reset maybe cause IAP process error. Disable BOD reset function and enable BOD interrupt to check and reset. */
#if 0
#define  BOR_Enabled_in_CONFIG
#endif 

#ifdef  BOR_Enabled_in_CONFIG
void BOD_ISR(void) interrupt 8        // Vector @  0x43
{
    TA=0xAA;TA=0x55;IAPUEN=0;         //Disable all Write enable
    clr_CHPCON_IAPEN;
    clr_BODCON0_BOF;                  //clear BOD flag
    set_CHPCON_SWRST;                 //Software reset
}
#endif


//-----------------------------------------------------------------------------------------------------------
void main (void) 
{
/*****************************************************************************************************************
 Define RAM buffer data
******************************************************************************************************************/   
    unsigned  char i,temp1,temp2;
  
  
#ifdef BOR_Enabled_in_CONFIG
    ENABLE_BOD_INTERRUPT;
    DISABLE_BOD_RESET;
#endif
#ifdef print_function
  /* UART0 settting for printf function */
    MFP_P31_UART0_TXD;
    P31_QUASI_MODE;
    UART_Open(24000000,UART0_Timer1,115200);
    ENABLE_UART0_PRINTF;
#endif

    ENABLE_P32_PULLUP;
    while(P32);

  for (i=0;i<128;i++)
  {
    IAPDataBuf[i]=i;
  }

    APROM_Erase(0x3800,128);
    APROM_Blank_Check(0x3800,128);
    APROM_Program(0x3800,128);
    APROM_Read_Verify(0x3800,128);

    APROM_Checksum_Run(0x3800,1);
    temp1 = APROM_Checksum_Read(0);

  for (i=0;i<128;i++)
  {
    IAPDataBuf[i]=55;
  }
    LDROM_Erase(0,128);
    LDROM_Program(0,128);
    LDROM_Read_Verify(0,128);
    LDROM_Checksum_Run(0,1);
    temp2 = LDROM_Checksum_Read(0);

#ifdef print_function
  /*printf must in SFR page 0 */
      _push_(SFRS);
      SFRS = 0;
      printf ("\n APROM 3800H Checksum = 0x%bX\n", temp1);
      printf ("\n LDROM Checksum = 0x%bX\n",temp2);
      _pop_(SFRS);
#endif
    while(1);
}
//-----------------------------------------------------------------------------------------------------------
