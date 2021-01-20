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
//  File Function: MlL51 IAP program APROM demo code 
//***********************************************************************************************************

#include "ML51.h"

/* For printf code only. Disable this define to reduce code size. */
#define print_function 
/* @note        BOD reset maybe cause IAP process error. Disable BOD reset function and enable BOD interrupt to check and reset.   */
 #define  BOR_Enabled_in_CONFIG

#ifdef  BOR_Enabled_in_CONFIG
void BOD_ISR(void) interrupt 8        // Vector @  0x43
{
    TA=0xAA;TA=0x55;IAPUEN=0;         //Disable all Write enable
    clr_CHPCON_IAPEN;
    clr_BODCON0_BOF;                  //clear BOD flag
    set_CHPCON_SWRST;                 //Software reset
}
#endif

void main (void) 
{
    unsigned char count;
#ifdef BOR_Enabled_in_CONFIG
    ENABLE_BOD_INTERRUPT;
    DISABLE_BOD_RESET;
#endif
#ifdef print_function	
/* Initial UART0 for printf */  
    MFP_P31_UART0_TXD;
    P31_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
#endif

    MFP_P46_GPIO;
    P46_INPUT_MODE;
    while(P46);                              //loop here while P13 = 1;
  
    for(count=0;count<128;count++)          // define buffer data
    {
      IAPDataBuf[count]=count;
    }
        
/** IAP program APROM, this code only run in LDROM.
   * include IAP.c in Library for IAP function
   * @note  now maxima buffer size for program is 128 byte. buffer is locate in XRAM please check in "iap.h" IAPDataBuf[128] define.
*/
    APROM_Erase(0x1000,128);
    APROM_Blank_Check(0x1000,128);
    APROM_Program(0x1000,128);
    APROM_Read_Verify(0x1000,128);

    while(1);
}



