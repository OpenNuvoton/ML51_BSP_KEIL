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
#define print_function 
/**
 * @brief        PDMA receiv from UART2(SC0) RX demo. 
 * @param       None
 * @return      None
 * @details     after PDMA transfer done UART2 RX data in XRAM 0x100 start area.
*/

unsigned char xdata RxDatabuffer[100] _at_ 0x100;
unsigned char ct;
bit pdmaflag = 0;

void PDMA0_ISR(void) interrupt 20          // Vector @  0xA3
{
  PDMA_Close(PDMA0);
  SFRS=0;DMA0TSR=0;
}

void main (void) 
{

#ifdef print_function
  /* UART0 initial setting
  ** include uart.c in Library for UART initial setting
  **UART0 define P3.1 TXD multi function setting
  **/
  Enable_UART0_VCOM_printf();
  printf("\n PDMA receiv UART2 RX intial...");
#endif
    
 /* Enable UART2 RX */      
    MFP_P55_UART2_RXD;
    P55_INPUT_MODE;
    UART_Open(24000000,UART2,115200);
  
 /* Clear XRAM base address area to 00h */
    for(ct=0;ct<10;ct++)
    {
      RxDatabuffer[ct]=0;
    }
 /* Define PMDA function as UART RX to memory, define base address and PDMA receive length */    
    PDMA_Open(PDMA0,SMCRX,0x100,100);
 /* Define interrupt after full transfer */
    PDMA_Interrupt_Enable(PDMA0,PDMAFULLINT);
 /* Global interrupt enable */
    ENABLE_GLOBAL_INTERRUPT;
 /* Start PDMA transfer */
    PDMA_Run(PDMA0);
    
    while(!pdmaflag);
#ifdef print_function
    printf (" \n PDMA receiv UART2 RX finish! " );
#endif

    while(1);

}



