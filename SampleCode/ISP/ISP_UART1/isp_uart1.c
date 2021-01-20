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
bit BIT_TMP;
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
  TH0=TL0=0;    //interrupt timer 140us
  set_TCON_TR0;      //Start timer0
  set_IPH_PSH;       // Serial port 0 interrupt level2
  set_IE_ET0;
}


void UART1_ini_115200(void)
{
    MFP_P23_UART1_TXD;                              /* set P2.3 and P2.2 as Quasi mode for UART0 trasnfer */
    MFP_P22_UART1_RXD;
    P23_QUASI_MODE;                                  
    P22_INPUT_MODE;
  
    SFRS = 0x00;
    S1CON = 0x50;           /*UART1 Mode1,REN_1=1 */
    T3CON = 0x88;           /*T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1*/
    clr_T3CON_BRCK;
    RH3    = HIBYTE(65536 - 13);;
    RL3    = LOBYTE(65536 - 13);
    set_T3CON_TR3;             //Trigger Timer3 
    set_EIE1_ES1;
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


void Send_64byte_To_UART1(void)
{
  SFRS=0;
   for(count=0;count<64;count++)
  {
     TI_1 = 0;  
    SBUF1 = uart_txbuf[count];
    while(TI_1==0);
  }
}

void UART1_ISR (void) interrupt 15
{
  SFRS=0;
    if (RI_1 == 1)
    {   
      uart_rcvbuf[bufhead++]=  SBUF1;    
      clr_S1CON_RI_1;                                         // Clear RI (Receive Interrupt).
    }
    if (TI_1 == 1)
    {       
        clr_S1CON_TI_1;                                         // Clear TI (Transmit Interrupt).
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
