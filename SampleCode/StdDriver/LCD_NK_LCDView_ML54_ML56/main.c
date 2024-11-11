/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ml51.h"
#include "lcd_nk.h"
#include "lcdlib.h"
#include "lcdzone.h"

void main(void)
{

    /* Initial LCD Sub board */
    LCD_Init_Setting();
    
    /* Init TK Controller */  
    ENABLE_GLOBAL_INTERRUPT;

    LCD_frame2();

    while (1)
    {
      LCD_frame1();
      Timer0_Delay(24000000,800,1000);
      LCD_frame2();
      Timer0_Delay(24000000,800,1000);
    }
}

