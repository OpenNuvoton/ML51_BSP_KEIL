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

/**
 * @brief       IAP program LDROM sample 
 * @param       None
 * @return      None
 * @details     include erase whole LDROM area -> erase verify check blank -> program 128 byte in LDROM from 0x0000 -> verify programed data.
 * @note         PLEASE CONFIRM ENABLE CONFIG AREA FIRST BERFORE PROGRAM LDROM.
 * @note        BOD reset maybe cause IAP process error. Disable BOD reset function and enable BOD interrupt to check and reset. 
 */


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
    unsigned char datatemp,count;
	
#ifdef BOR_Enabled_in_CONFIG
    ENABLE_BOD_INTERRUPT;
    DISABLE_BOD_RESET;
#endif

    MFP_P46_GPIO;
    P46_INPUT_MODE;
    while(P46);                              //loop here while P46 = 1;
  
    for(count=0;count<128;count++)          // define buffer data
    {
      IAPDataBuf[count]=count;
    }

/** IAP program LDROM, this code only run in APROM.
   * include IAP.c in Library for IAP function
   * @note  now maxima buffer size for program is 128 byte. buffer is locate in XRAM please check iap.h IAPDataBuf[128] define.
*/
    LDROM_Erase(0x0000,128);
    LDROM_Blank_Check(0x0000,2048);
    LDROM_Program(0x0000,128);
    LDROM_Read_Verify(0x0000,128);
      
/*flash read byte can't read LDROM area, following can't read LDROM data.*/
/* use ICP tool to read LDROM area, and always keep P46 = 1 except want to erase LDROM */
    datatemp = Read_APROM_BYTE(0x7802);
    while(1);
}



