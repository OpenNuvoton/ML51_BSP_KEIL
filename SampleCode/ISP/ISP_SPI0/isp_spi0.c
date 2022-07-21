/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 UART0 ISP subroutine
//***********************************************************************************************************
#include "ML51.h"
#include "isp_spi0.h"

xdata volatile uint8_t rxbuf[64];
xdata volatile uint8_t rxcgbuf[56];
xdata volatile uint8_t txbuf[64];
data volatile uint8_t bufhead;
data volatile uint16_t flash_address;
data volatile uint16_t AP_size;
data volatile uint8_t g_timer1Counter;
data volatile uint8_t count;
data volatile uint16_t g_timer0Counter;
data volatile uint32_t g_checksum;
data volatile uint32_t g_totalchecksum;
bit volatile bSPIDataReady;
bit volatile bSPISendFlag = 0;
bit volatile g_timer0Over;
bit volatile g_timer1Over;
bit volatile g_programflag;
bit  BIT_TMP;
unsigned char PID_highB, PID_lowB, DID_highB, DID_lowB, CONF0, CONF1, CONF2, CONF4;
unsigned char recv_CONF0, recv_CONF1, recv_CONF2, recv_CONF4;

void READ_ID(void)
{
//    set_CHPCON_IAPEN;
    IAPCN = READ_DID;
    IAPAH = 0x00;
    IAPAL = 0x00;
    set_IAPTRG_IAPGO;
    DID_lowB = IAPFD;
    IAPAL = 0x01;
    set_IAPTRG_IAPGO;
    DID_highB = IAPFD;
    IAPAL = 0x02;
    set_IAPTRG_IAPGO;
    PID_lowB = IAPFD;
    IAPAL = 0x03;
    set_IAPTRG_IAPGO;
    PID_highB = IAPFD;
}
void READ_CONFIG(void)
{
    IAPCN = BYTE_READ_CONFIG;
    IAPAL = 0x00;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    CONF0 = IAPFD;
    IAPAL = 0x01;
    set_IAPTRG_IAPGO;
    CONF1 = IAPFD;
    IAPAL = 0x02;
    set_IAPTRG_IAPGO;
    CONF2 = IAPFD;
    IAPAL = 0x04;
    set_IAPTRG_IAPGO;
    CONF4 = IAPFD;
//    clr_CHPCON_IAPEN;
}

void TM0_ini(void)
{
    TH0 = TL0 = 0;     //interrupt timer 140us
    set_TCON_TR0;      //Start timer0
    set_IPH_PSH;       // Serial port 0 interrupt level2
    set_IE_ET0;
}


void SPI0_ini(void)
{
    MFP_P00_SPI0_MOSI;      /*define  SPI0 MOSI pin */
    P00_QUASI_MODE;
    MFP_P01_SPI0_MISO;      /*define  SPI0 MISO pin */
    P01_QUASI_MODE;
    MFP_P02_SPI0_CLK;       /*define  SPI0 CLK pin */
    P02_QUASI_MODE;
    MFP_P03_SPI0_SS;        /*define  SPI0 SS pin as normal GPIO*/
    P03_QUASI_MODE;

    clr_SPI0CR0_MSTR;                                   // SPI in Slave mode 
    clr_SPI0CR0_LSBFE;                                  // MSB first 

    set_SPI0CR0_CPOL;                                   // The SPI clock is low in idle mode
    set_SPI0CR0_CPHA;  

    set_SPI0CR0_SPIEN;
    clr_SPI0SR_SPIF;                          // Clear SPI flag   
}

void Package_checksum(void)
{
    g_checksum = 0;

    for (count = 3; count < 64; count++)
    {
        g_checksum = g_checksum + rxbuf[count];

    }
    txbuf[6] = g_checksum & 0xff;
    txbuf[7] = (g_checksum >> 8) & 0xff;
    txbuf[10] = rxbuf[4+3] + 1;
    txbuf[11] = rxbuf[5+3];  
    if (txbuf[4+6] == 0x00)
        txbuf[5+6]++;    
}
void Package_checksum2(void)
{
    g_checksum = 0;

    for (count = 3; count < 64; count++)
    {
        g_checksum = g_checksum + rxbuf[count];
        txbuf[count] = 0x00;
    }
      txbuf[6] = (g_checksum >> 8) & 0xff;
      txbuf[7] = g_checksum & 0xff;    
      txbuf[11] = rxbuf[4+3] + 1;    
}


void Send_64byte_To_SPI0(void)
{
_push_(SFRS);
    SFRS = 0;
      clr_SPI0CR0_CPOL;                                   // The SPI clock is low in idle mode
      clr_SPI0CR0_CPHA;    

    bSPISendFlag = 1;

    for (count = 0; count < 64; count++)
    {              
        SPI0DR = txbuf[count];
        while(!(SPI0SR&0x80));
        clr_SPI0SR_SPIF;            
    }
    set_SPI0CR0_CPOL;                                   // The SPI clock is low in idle mode
    set_SPI0CR0_CPHA;    
    bSPISendFlag = 0;
_pop_(SFRS);
}

void SPI0_Polling_Receive_Data(void)
{
_push_(SFRS);

  if(bSPISendFlag == 0) 
  {
      SFRS = 0;

      while(!(SPI0SR&0x80));
      clr_SPI0SR_SPIF;      

      rxbuf[bufhead] = SPI0DR;
    
      if(rxbuf[0] == 0x53)
      {
          //  txbuf[bufhead] = 0x00;  
            bufhead++;  
            if(bufhead == 64)
            {      
              bSPIDataReady = TRUE;

              g_timer1Counter=0;
              g_timer1Over=0;
              bufhead = 0;      
            }          
      }
      if(bufhead == 1)
      {
            g_timer1Over=0;
            g_timer1Counter=90; 
      }  
  }

_pop_(SFRS);
}
void SPI0_Polling_Receive_Data1(void)
{
    _push_(SFRS);
  if(bSPISendFlag == 0) 
  {

    SFRS = 0;  
    SPI0SR &=0x8F;
        while(!(SPI0SR&0x80));
                rxbuf[bufhead] = SPI0DR;
        clr_SPI0SR_SPIF;
        if(rxbuf[0] == 0x53)
        {
            //  txbuf[bufhead] = 0x00;  
              bufhead++;  
              if(bufhead == 64)
              {      

                bSPIDataReady = TRUE;

                g_timer1Counter=0;
                g_timer1Over=0;
                bufhead = 0;
              }
            }
  }
_pop_(SFRS);
}

void WordChangeByte12(void)
{
  unsigned char ct,ct1,ct2;
  for (ct=0;ct<12;ct++)
  {
    ct1 = ct*4;
    ct2 = (ct+4)*4;
    rxcgbuf[ct1]=rxbuf[ct2+3];
    rxcgbuf[ct1+1]=rxbuf[ct2+2];
    rxcgbuf[ct1+2]=rxbuf[ct2+1];
    rxcgbuf[ct1+3]=rxbuf[ct2];
  }
}

void WordChangeByte14(void)
{
  unsigned char ct,ct1,ct2;
  for (ct=0;ct<14;ct++)
  {
    ct1 = ct*4;
    ct2 = (ct+2)*4;
    rxcgbuf[ct1]=rxbuf[ct2+3];
    rxcgbuf[ct1+1]=rxbuf[ct2+2];
    rxcgbuf[ct1+2]=rxbuf[ct2+1];
    rxcgbuf[ct1+3]=rxbuf[ct2];
  }
}
void Timer0_ISR(void) interrupt 1
{
      _push_(SFRS);
  SFRS = 0;    
    if (!g_timer0Over)
    {
        g_timer0Counter--;
        if (!g_timer0Counter)
        {
            g_timer0Over = 1;
        }
    }
    if (g_timer1Counter)
    {
        g_timer1Counter--;
        if (!g_timer1Counter)
        {
            g_timer1Over = 1;
        }
    }
  _pop_(SFRS);  
}
