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
//  File Function: ML51 System clock modify demo
//***********************************************************************************************************
#include "ML51.h"


//========================================================================
//  The test process:
//  1. Power on is run as default HIRC,
//  2. if P4.6 toggle to GND system clock run in LIRC.
//  3. if P4.6 toggle to GND Again system clock run in HXT.
//  PLEASE CONFIRM THE EXTERNAL XTAL IS CONNECT
//========================================================================
void main(void)
{

/* Note
  MCU power on system clock is HIRC (24 MHz)
*/
    MFP_P46_GPIO;
    P46_INPUT_MODE;
    ENABLE_P46_PULLUP;
  
    MFP_P32_CLKO;
    P32_PUSHPULL_MODE;
    set_CKCON_CLOEN;                                  // Also can check P3.2 CLKO pin for clock to find the Fsys change.
    MFP_P46_GPIO;
    ENABLE_P46_PULLUP;
    while (P46);
    FsysSelect(FSYS_LIRC);
    while (P46);/* Note
  please confirm extenral oscillator is connected. 
*/      
    FsysSelect(FSYS_HXT);;
    while(1);

}

