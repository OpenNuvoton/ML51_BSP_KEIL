/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 UART0 ISP subroutine
//***********************************************************************************************************
#include "ML51.h"
#include "isp_uart2.h"

  xdata volatile uint8_t uart_rcvbuf[64]; 
  xdata volatile uint8_t uart_txbuf[64];
  data volatile uint8_t bufhead;
  data volatile uint16_t flash_address; 
  data volatile uint16_t AP_size;
  data volatile uint8_t g_timer1Counter;
  data volatile uint8_t count; 
  data volatile uint16_t g_timer0Counter;
  data volatile uint32_t g_checksum;
  data volatile uint32_t g_totalchecksum;
  bit volatile bUartDataReady;
  bit volatile g_timer0Over;
  bit volatile g_timer1Over;
  bit volatile g_programflag;

unsigned char PID_highB,PID_lowB,DID_highB,DID_lowB,CONF0,CONF1,CONF2,CONF4;
unsigned char recv_CONF0,recv_CONF1,recv_CONF2,recv_CONF4;


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
    IAPAH = 0x00;
    IAPAL = 0x00;
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
  TH0=TL0=0;    //interrupt timer 140us
  set_TCON_TR0;      //Start timer0
  set_IPH_PSH;       // Serial port 0 interrupt level2
  set_IE_ET0;
}


void UART2_ini_115200(void)
{
    MFP_P25_UART2_TXD;                              /* set P2.5 and P2.4 as Quasi mode for UART0 trasnfer */
    MFP_P24_UART2_RXD;
    P25_PUSHPULL_MODE;
    P24_INPUT_MODE;
  
  set_SC0CR0_SCEN;         /* Enable SC module */
  set_SC0CR1_UARTEN;       /* set as UART mode */
  set_SC0CR1_CLKKEEP;      
  clr_SC0CR0_CONSEL;       /* clr CONSEL and AUTOCEN*/
  clr_SC0CR0_AUTOCEN;
  SC0ETURD0 = LOBYTE(24000000/8/115200-1);  /* define baud rate low byte */
  SC0ETURD1 &= 0xF0;                                /* define baud rate high byte */
  SC0ETURD1 |= (HIBYTE(24000000/8/115200-1))&0x0F; 
  set_SC0CR1_PBOFF;     //parity bit disable
  SC0CR1&=0XCF;        //datalegth 8bit
  set_SC0CR0_NSB;      //stop bit = 1bit  
  set_SC0IE_TBEIEN;
  set_SC0IE_RDAIEN;
  EA=1;
}


void Package_checksum(void)
{
  g_checksum=0;
   for(count=0;count<64;count++)
  {
    g_checksum =g_checksum+ uart_rcvbuf[count];    
  }
  uart_txbuf[0]=g_checksum&0xff;
  uart_txbuf[1]=(g_checksum>>8)&0xff;
  uart_txbuf[4]=uart_rcvbuf[4]+1;
  uart_txbuf[5]=uart_rcvbuf[5];
  if(uart_txbuf[4]==0x00)
  uart_txbuf[5]++;
}


void Send_64byte_To_UART2(void)
{
   for(count=0;count<64;count++)
  {
    clr_SC0CR0_TXOFF;
    SC0DR = uart_txbuf[count];
    while((SC0TSR|CLR_BIT3)==CLR_BIT3);
    clr_SC0CR0_TXOFF;
  }
}

void SMC0_ISR (void) interrupt 19  
{
    SFRS=0;
    if((SC0IS|CLR_BIT0)==0xFF)
    {   
      uart_rcvbuf[bufhead++]=  SC0DR;
      clr_SC0IS_RDAIF;                                         // Clear RI (Receive Interrupt).
    }
    if ((SC0IS|CLR_BIT1)==0xFF)
    {       
        clr_SC0IS_TBEIF;                                         // Clear TI (Transmit Interrupt).
    }
    if(bufhead ==1)
    {
      g_timer1Over=0;
      g_timer1Counter=90; //for check uart timeout using
    }
  if(bufhead == 64)
    {
      bUartDataReady = TRUE;
      g_timer1Counter=0;
      g_timer1Over=0;
      bufhead = 0;
    }    
}

void Timer0_ISR (void) interrupt 1
{
//    _push_(SFRS);
  
if(g_timer0Counter)
  {
  g_timer0Counter--;
    if(!g_timer0Counter)
    {
    g_timer0Over=1;
    }
  }
  
  if(g_timer1Counter)
  {
  g_timer1Counter--;
    if(!g_timer1Counter)
    {
    g_timer1Over=1;
    }
  }
  
//    _pop_(SFRS);
}
