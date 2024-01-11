/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include "ml51.h"

BIT  wktIntFlag;

/************************************************************************************************************/
/* FUNCTION_PURPOSE: WKT Interrupt Service Routine                                                          */
/************************************************************************************************************/
void WKT_ISR (void) interrupt 17            /* Vector @  0x8B  */
{
PUSH_SFRS;
    clr_WKCON_WKTF;
    wktIntFlag = 1;
    GPIO_LED ^= 1;

POP_SFRS;
}

/************************************************************************************************************/
/* FUNCTION_PURPOSE: Main Loop                                                                              */
/************************************************************************************************************/
void main (void)
{
    unsigned char ct;

    GPIO_LED_QUASI_MODE;
    Enable_UART0_VCOM_printf();
    printf ("\n test start");
/*FOR ML51 Series */
    ML51_WKT_AutoReload_Interrupt_Initial_S(LIRC,2);       /* WKT delay 2s */
/*FOR ML56 / ML54  Series */
//    ML56_WKT_AutoReload_Interrupt_Initial_S(LIRC,2);      /* WKT delay 2s */
    ENABLE_GLOBAL_INTERRUPT;

    while(ct<4)
    {
      if (wktIntFlag)
      {
        printf ("\n WKT INT");
        wktIntFlag=0;
              ct++;
      }
    }
    WKT_Close();
    while(1)
    {
      if (wktIntFlag)
      {
        printf ("\n WKT error");
        wktIntFlag=0;
      }
    }
}

