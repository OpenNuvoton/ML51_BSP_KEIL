/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define SPI0         0
#define SPI1         1
#define SPI_SLAVE    0
#define SPI_MASTER   1
#define MSB_FIRST    0
#define LSB_FIRST    1

#define SPI_MODE_0   0          /*!< CPOL=0; CPHA = 0; */
#define SPI_MODE_1   1          /*!< CPOL=0; CPHA = 1; */
#define SPI_MODE_2   2          /*!< CPOL=1; CPHA = 0; */
#define SPI_MODE_3   3          /*!< CPOL=1; CPHA = 1; */


void SPI_Open(unsigned char u8SPISel, unsigned char u8MasterSlave, unsigned char u8SPICLKDIV,unsigned char u8SPIMode,unsigned char u8MSBLSB);
void SPI_Interrupt(unsigned char u8SPISel, unsigned char u8SPIINTStatus);
void Spi_Write_Byte(unsigned char u8SPISel, unsigned char u8SpiWB);
unsigned char Spi_Read_Byte(unsigned char u8SPISel, unsigned char u8SpiWB);