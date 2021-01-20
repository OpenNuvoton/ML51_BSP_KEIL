/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


#include "ML51.h"

/**
  * @brief      Enable specify PDMA controller and set address
  * @param[in]  u8PDMASel:  Specify PDMA channel (PDMA0,PDMA1,PDMA2,PDMA3)
  * @param[in]  u8PDMASourceSel decides the SPI module is operating in master mode or in slave mode. (SPI_SLAVE, SPI_MASTER)
                      - \ref  Value      PSSEL[2:0] 
                      - \ref  XRAM_XRAM   000   
                      - \ref  SPI0RX      001   
                      - \ref  SMCRX       010    
                      - \ref  SPI1RX      011    
                      - \ref   4          100    
                      - \ref  SPI0TX      101    
                      - \ref  SMCTX       110    
                      - \ref  SPI1TX      111    
  * @param[in]  u8PDMAINTSel: (PDMAHALFINT/PDMAFULINT/ALLINT)
  * @param[in]  u16PDMABAddress: PDMA 12bit base address in XRAM define.
  * @param[in]  u8PDMACOUNT: PDMA counter .
  * @return     None
  * @exmaple :  PDMA_Open(PDMA0,SPI0RX,0x1000,100);
  */
void PDMA_Open( unsigned char u8PDMASel, 
                unsigned char u8PDMASourceSel,
                unsigned int  u16PDMABAddress,
                unsigned char u8PDMACOUNTER)
{
    switch (u8PDMASel)
    {
        case PDMA0: SFRS=0;DMA0CR0=0; DMA0CR0|=(u8PDMASourceSel<<4)| 0x01;
                    DMA0MAL = u16PDMABAddress; DMA0BAH |= ((u16PDMABAddress&0x0F00)>>8); 
                    DMA0CNT = u8PDMACOUNTER-1; break;
      
        case PDMA1: SFRS=0;DMA1CR0=0; DMA1CR0|=(u8PDMASourceSel<<4)| 0x01; 
                    DMA1MAL = u16PDMABAddress; DMA1BAH|= ((u16PDMABAddress&0x0F00)>>8); 
                    DMA1CNT = u8PDMACOUNTER-1; break;
      
        case PDMA2: SFRS=2;DMA2CR0=0; DMA2CR0 |= (u8PDMASourceSel<<4)| 0x01;
                    DMA2MAL = u16PDMABAddress; DMA2BAH|= ((u16PDMABAddress&0x0F00)>>8); 
                    DMA2CNT = u8PDMACOUNTER-1; break;
      
        case PDMA3: SFRS=2;DMA3CR0=0; DMA3CR0 |= (u8PDMASourceSel<<4)| 0x01;
                    DMA3MAL = u16PDMABAddress; DMA3BAH|= ((u16PDMABAddress&0x0F00)>>8); 
                    DMA2CNT = u8PDMACOUNTER-1; break;
    }
    switch (u8PDMASourceSel)
    {
        case SPI0RX: set_SPI0CR1_RXDMAEN; break;
        case SMCRX:  set_SC0CR1_RXDMAEN; break;
        case SPI1RX: set_SPI1CR1_RXDMAEN; break;
        case SPI0TX: set_SPI0CR1_TXDMAEN; break;
        case SMCTX:  set_SC0CR1_TXDMAEN; break;
        case SPI1TX: set_SPI1CR1_TXDMAEN; break;
    }    
}

/**
  * @brief      Enable specify PDMA memory to memory destination address 
  * @param[in]  u8PDMASel:  Specify PDMA channel (PDMA0,PDMA1,PDMA2,PDMA3)
  * @param[in]  u16PDMABAddress: PDMA 12bit base address in XRAM define.
  * @return     None
  * @exmaple :  PDMA_MTM_DestinationAddress(PDMA1,0x2000);
  */
void PDMA_MTM_DestinationAddress(unsigned char u8PDMASel, unsigned int u16PDMADAddress)
{
     switch (u8PDMASel)
    {
        case PDMA0:SFRS=0; MTM0DAL = u16PDMADAddress; DMA0BAH |= ((u16PDMADAddress&0x0F00)>>4); break;
        case PDMA1:SFRS=0; MTM1DAL = u16PDMADAddress; DMA1BAH |= ((u16PDMADAddress&0x0F00)>>4); break;
        case PDMA2:SFRS=2; MTM2DAL = u16PDMADAddress; DMA2BAH |= ((u16PDMADAddress&0x0F00)>>4); break;
        case PDMA3:SFRS=2; MTM3DAL = u16PDMADAddress; DMA3BAH |= ((u16PDMADAddress&0x0F00)>>4); break;
    }
  }

/**
  * @brief      Enable specify PDMA Interrupt enable 
  * @param[in]  u8PDMASel:  Specify PDMA channel port (PDMA0,PDMA1,PDMA2,PDMA3)
  * @param[in]  u8PDMAINTSel: Interrupt mode define (PDMAFULLINT/PDMAHALFINT/PDMAALLINT).
  * @return     None
  * @exmaple :  PDMA_MTM_DestinationAddress(PDMA1,0x2000);
  */
void PDMA_Interrupt_Enable(unsigned char u8PDMASel,unsigned char u8PDMAINTSel)
{
    switch (u8PDMASel)
    {
        case PDMA0: SFRS=0;DMA0CR0|=(u8PDMAINTSel<<2); break;
        case PDMA1: SFRS=0;DMA1CR0|=(u8PDMAINTSel<<2); break;
        case PDMA2: SFRS=2;DMA2CR0|=(u8PDMAINTSel<<2); break;
        case PDMA3: SFRS=2;DMA3CR0|=(u8PDMAINTSel<<2); break;
    }
}

void PDMA_Run(unsigned char u8PDMASel)
{
    switch (u8PDMASel)
    {
        case PDMA0: SFRS=0;DMA0CR0|=SET_BIT1; break;
        case PDMA1: SFRS=0;DMA1CR0|=SET_BIT1; break;
        case PDMA2: SFRS=2;DMA2CR0|=SET_BIT1; break;
        case PDMA3: SFRS=2;DMA3CR0|=SET_BIT1; break;
    }
}
void PDMA_Close(unsigned char u8PDMASel)
{
    switch (u8PDMASel)
    {
        case PDMA0: SFRS=0;DMA0CR0&=CLR_BIT0; break;
        case PDMA1: SFRS=0;DMA1CR0&=CLR_BIT0; DMA1CR0&=0xF0;break;
        case PDMA2: SFRS=2;DMA2CR0&=CLR_BIT0; DMA2CR0&=0xF0;break;
        case PDMA3: SFRS=2;DMA3CR0&=CLR_BIT0; DMA3CR0&=0xF0;break;
    }
}
//void PDMA_Close(unsigned char u8PDMASel)
//{
//	switch (u8PDMASel)
//	{
//			case PDMA0: SFRS=0;DMA0CR0&=CLR_BIT0; DMA0CR0&=0xF0; break;
//			case PDMA1: SFRS=0;DMA1CR0&=CLR_BIT0; DMA1CR0&=0xF0;break;
//			case PDMA2: SFRS=2;DMA2CR0&=CLR_BIT0; DMA2CR0&=0xF0;break;
//			case PDMA3: SFRS=2;DMA3CR0&=CLR_BIT0; DMA3CR0&=0xF0;break;
//	}
//}