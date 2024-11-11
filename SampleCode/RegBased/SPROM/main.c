/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: MS51 locate data in APROM simple demo 
//***********************************************************************************************************
#include "ml51.h"
#include "SPROM.h"


void main (void) 
{


    Enable_UART0_VCOM_printf();
    
    set_IAPUEN_SPMEN;             //Enable SPROM memory mapping only for check SPROM in memory window
    SFRS=0; printf ("\n protect bit is 0x%BX", protect);
    while(1)
    {
      SPROM_CODE();
      SFRS=0; printf ("\n SPTEMP= 0x%BX", SPTEMP);
      Timer0_Delay(24000000,500,1000);
    }

}
