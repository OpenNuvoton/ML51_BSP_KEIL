/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 UART3 ISP subroutine
//***********************************************************************************************************
#include "ML51.h"
#include "isp_uart3.h"
#define SYS_CLK 24000000
#define uart_baudrate 115200
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

unsigned char PID_highB, PID_lowB, DID_highB, DID_lowB, CONF0, CONF1, CONF2, CONF4;
unsigned char recv_CONF0, recv_CONF1, recv_CONF2, recv_CONF4;


void READ_ID(void)
{
    //    set_CHPCON_IAPEN;
    SFRS = 0;
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
    SFRS = 0;
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
    TH0 = TL0 = 0; //interrupt timer 140us
    set_TCON_TR0;      //Start timer0
    //set_IPH_PSH;       // Serial port 0 interrupt level2
    set_IE_ET0;
}


void UART3_ini_115200(void)
{
    MFP_P12_UART3_TXD;
    P12_QUASI_MODE;
    MFP_P11_UART3_RXD;
    P11_INPUT_MODE;

    set_SC1CR0_SCEN;         /* Enable SC module */
    set_SC1CR1_UARTEN;       /* set as UART mode */
    set_SC1CR1_CLKKEEP;
    clr_SC1CR0_CONSEL;       /* clr CONSEL and AUTOCEN*/
    clr_SC1CR0_AUTOCEN;
    SC1ETURD0 = LOBYTE(SYS_CLK / 8 / uart_baudrate - 1); /* define baud rate low byte */
    SC1ETURD1 &= 0xF0;                                /* define baud rate high byte */
    SC1ETURD1 |= (HIBYTE(SYS_CLK / 8 / uart_baudrate - 1)) & 0x0F;
    set_SC1CR1_PBOFF;     //parity bit disable
    SC1CR1 &= 0xCF;      //datalegth 8bit
    set_SC1CR0_NSB;      //stop bit = 1bit

    ENABLE_SC1_RECEIVE_DATA_REACH_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
}


void Package_checksum(void)
{
    g_checksum = 0;

    for (count = 0; count < 64; count++)
    {
        g_checksum = g_checksum + uart_rcvbuf[count];
    }

    uart_txbuf[0] = g_checksum & 0xff;
    uart_txbuf[1] = (g_checksum >> 8) & 0xff;
    uart_txbuf[4] = uart_rcvbuf[4] + 1;
    uart_txbuf[5] = uart_rcvbuf[5];

    if (uart_txbuf[4] == 0x00)
        uart_txbuf[5]++;
}


void Send_64byte_To_UART3(void)
{
    for (count = 0; count < 64; count++)
    {
        clr_SC1CR0_TXOFF;
        SC1DR = uart_txbuf[count];

        while ((SC1TSR | CLR_BIT3) == CLR_BIT3);

        clr_SC1CR0_TXOFF;
    }
}

void SMC1_ISR(void) interrupt 27          // Vector @  0xDB
{
    _push_(SFRS);
    SFRS = 2;

    if ((SC1IS | CLR_BIT0) == 0xFF)
    {
        uart_rcvbuf[bufhead++] =  SC1DR;
        clr_SC1IS_RDAIF;                                         // Clear RI (Receive Interrupt).
    }

    if (bufhead == 1)
    {
        g_timer1Over = 0;
        g_timer1Counter = 90; //for check uart timeout using
    }

    if (bufhead == 64)
    {
        bUartDataReady = TRUE;
        g_timer1Counter = 0;
        g_timer1Over = 0;
        bufhead = 0;
    }

    _pop_(SFRS);
}

void Timer0_ISR(void) interrupt 1
{
    _push_(SFRS);

    if (g_timer0Counter)
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
