/***********************************************************************/
/*  This file is part of the C51 Compiler package                      */
/*  Copyright KEIL ELEKTRONIK GmbH 1990 - 2002                         */
/***********************************************************************/
/*                                                                     */
/*  PUTCHAR.C:  This routine is the general character output of C51.   */
/*  You may add this file to a uVision2 project.                       */
/*                                                                     */
/*  To translate this file use C51 with the following invocation:      */
/*     C51 PUTCHAR.C <memory model>                                    */
/*                                                                     */
/*  To link the modified PUTCHAR.OBJ file to your application use the  */
/*  following Lx51 invocation:                                         */
/*     Lx51 <your object file list>, PUTCHAR.OBJ <controls>            */
/*                                                                     */
/***********************************************************************/
#include "ml51.h"

/****************************************************************************/
/* Define putchar send from UART1, printf function will send from P1.6(TXD_1)
/* NOTICE: Since UART1 pin is multi-function with OCD DATA/CLK pin.
/* Suggest download than use run with realchip but not OCD mode.
/****************************************************************************/
#if 1
char putchar (char c)        //for UART1_printf
{
    while (!TI_1);  /* wait until transmitter ready */
    TI_1 = 0;
    SBUF1 = c;      /* output character */
    return (c);
}
#else
/*
 * putchar (mini version): outputs charcter only
 */
char putchar (char c)        //for UART0_printf
{        
  while (!TI);
  TI = 0;
  return (SBUF = c);
}

#endif
