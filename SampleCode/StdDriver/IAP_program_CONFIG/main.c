/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ml51.h"


/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/* Note:  Try to avoid modify CONFIG in the program. Define CONFIG in ICP PROGRAMMER !!                     */ 
/* NEVER modify config immediately after RESET                                                              */
/************************************************************************************************************/
void main (void) 
{
    uint8_t   ct;
  
    Enable_UART0_VCOM_printf();
    printf ("\n\r MCU Reset.   ");
    printf ("\n\r Toggle P1.2 to low to start test... \n\r ");

  
    /* printf  now CONFIG value */ 
    Read_CONFIG();
    printf ("\n\r Now config value is :   ");
    for(ct=0;ct<5;ct++)
    {
        printf ("\r 0x%bX", IAPCFBuf[ct]);
    }
    printf ("\n\r ");

    /* Start modify CONFIG */
    GPIO_LED_QUASI_MODE;
    while(GPIO_LED);
    Timer0_Delay(24000000,200,1000);
    Modify_CONFIG(0xEF,0xFB,0x6B,0xFF,0xFF);

    SFRS=0;
    if(ConfigModifyFlag)        /* Check with power on flag. Only the first power on check with CONFIG */
    {
        SFRS=0;printf ("\n\r CONFIG MODIFY to 0xEF,0xFB,0x6B,0xFF,0xFF !!!");
        printf ("\n\r Reset MCU to take effect...  \n\r ");
        ConfigModifyFlag=0;
        Software_Reset(BOOT_APROM);    // IMPORTANT !! only after reset the modify  take effect
    }
    else
    {
         SFRS=0;
         printf ("\n\r CONFIG same as last time modify value ... not Modify again");
         printf ("\n\r or Modify_CONFIG API Only allowed ONCE after Power ON reset");
    }
    
    while(1);
}

