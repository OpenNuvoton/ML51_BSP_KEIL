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
 * @brief       I2C0 master demo. 
 * @param       None
 * @return      None
 * @details     please confirm enable LXT and check work stable if use LXT as WKT clock source.
*/

unsigned char xdata RxDatabuffer[100];
unsigned char loopcount=100;

void PDMA0_ISR(void) interrupt 20          // Vector @  0xA3
{
    clr_DMA0TSR_FDONE;
}

void main (void) 
{

    MFP_P13_GPIO;
    P13_PUSHPULL_MODE;
  
    MFP_P00_SPI0_MOSI;
    P00_QUASI_MODE;
    MFP_P01_SPI0_MISO;
    P01_QUASI_MODE;
    MFP_P02_SPI0_CLK;
    P02_QUASI_MODE;
  
    SPI_Open(SPI0,SPI_SLAVE,10,SPI_MODE_3,MSB_FIRST);
    PDMA_Open(PDMA0,SPI0RX,0x00,100);
    PDMA_Interrupt_Enable(PDMA0,PDMAFULLINT);
    ENABLE_GLOBAL_INTERRUPT;
    PDMA_Run(PDMA0);

    while(1);
}



