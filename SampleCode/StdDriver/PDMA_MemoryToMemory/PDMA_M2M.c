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

/* IMPORTANT !! This define for printf code only. Disable this define to reduce code size. */
//#define print_function 

/**
 * @brief        I2C0 master demo. 
 * @param       None
 * @return      None
 * @details     please confirm enable LXT and check work stable if use LXT as WKT clock source.
*/

unsigned char xdata RxDatabuffer[100] _at_ 0x100;
unsigned char xdata finalbuffer _at_ 0x263;
unsigned char i;
bit pdmaflag = 0;

void PDMA1_ISR(void) interrupt 21          // Vector @  0xAB
{
  PDMA_Close(PDMA1);
  clr_DMA1TSR_FDONE;
  clr_DMA1TSR_HDONE;
  pdmaflag = 1;
}

void main (void) 
{

#ifdef print_function
  /* UART0 initial setting
  ** include uart.c in Library for UART initial setting
  **UART0 define P3.1 TXD multi function setting
  **/
  Enable_UART0_VCOM_printf();
  printf("\n ADC trig by GPIO intial...");
#endif
    for(i=0;i<100;i++)
    {
      RxDatabuffer[i]=i;
    }
/* Define PMDA function as memory to memory, and setting base address */    
    PDMA_Open(PDMA1,XRAM_XRAM,0x100,0x80);
/* Define destination memory address */    
    PDMA_MTM_DestinationAddress(PDMA1,0x200);
/* Define interrupt after full transfer */    
    PDMA_Interrupt_Enable(PDMA1,PDMAFULLINT);
    ENABLE_GLOBAL_INTERRUPT;
    PDMA_Run(PDMA1);
    while(!pdmaflag);
#ifdef print_function
    printf (" \n PDMA Tranfer Finish! 0x%bx", finalbuffer);
#endif
    while(1);
}



