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
 * @brief        I2C0 master demo. 
 * @param       None
 * @return      None
 * @details     please confirm enable LXT and check work stable if use LXT as WKT clock source.
*/

unsigned char xdata RxDatabuffer[100] _at_ 0;

void SPI0_ISR(void) interrupt 9           // Vector @  0x4B
{
    _push_(SFRS);

    clr_SPI0SR_SPIF;
//    clr_SPI0SR_MODF;
//    clr_SPI0SR_SPIOVF;
//    SPI0SR &= 0x4F;
    _pop_(SFRS);
}

void main (void) 
{
    unsigned char loopcount;
    MFP_P13_GPIO;
    P13_PUSHPULL_MODE;

  for(loopcount=0;loopcount<100;loopcount++)
    {
        RxDatabuffer[loopcount] = 0x55;
    }
  
  
    MFP_P00_SPI0_MOSI;
    P00_QUASI_MODE;

    MFP_P02_SPI0_CLK;
    P02_QUASI_MODE;

    SPI_Open(SPI0,SPI_MASTER,0,SPI_MODE_3,MSB_FIRST);  /* SPI set as master mode 2Mbis/s */
    PDMA_Open(PDMA0,SPI0TX,0x1000,100);
    PDMA_Run(PDMA0);

    while(1);
  
}



