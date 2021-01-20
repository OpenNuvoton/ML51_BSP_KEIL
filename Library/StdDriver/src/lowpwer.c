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



void LowPower_LIRC_UART2_9600_init(void)
{
    set_SC0CR0_SCEN;         /* Enable SC module */
    set_SC0CR1_UARTEN;       /* set as UART mode */
    set_SC0CR1_CLKKEEP;      
    clr_SC0CR0_CONSEL;       /* clr CONSEL and AUTOCEN*/
    clr_SC0CR0_AUTOCEN;
    SC0ETURD0 = 3;           /* define baud rate low byte    38400/4=9600  */
    SC0ETURD1 &= 0x00;       /* define baud rate high byte */
    set_SC0CR1_PBOFF;        //parity bit disable
    SC0CR1&=0XCF;            //datalegth 8bit
    clr_SC0CR0_NSB;          //stop bit = 2bit must for 9600
    clr_SC0CR0_RXOFF;
}
void onestop_9600(void)
{
    set_SC0CR0_NSB;
}

void twostop_9600(void)
{
    clr_SC0CR0_NSB;
}

void LowPower_LIRC_UART2_4800_init(void)
{
    set_SC0CR0_SCEN;         /* Enable SC module */
    set_SC0CR1_UARTEN;       /* set as UART mode */
    set_SC0CR1_CLKKEEP;      
    clr_SC0CR0_CONSEL;       /* clr CONSEL and AUTOCEN*/
    clr_SC0CR0_AUTOCEN;
    SC0ETURD0 = 7;           /* define baud rate low byte    38400/8=4800  */
    SC0ETURD1 &= 0x00;       /* define baud rate high byte */
    set_SC0CR1_PBOFF;        //parity bit disable
    SC0CR1&=0XCF;            //datalegth 8bit
    set_SC0CR0_NSB;          //stop bit = 1bit
    clr_SC0CR0_RXOFF;
}

void UART0_LIRC_Baudrate2400_Open(void)
{
    SFRS = 0x00;
    SCON = 0x50;             //UART0 Mode1,REN=1,TI=1
    TMOD |= 0x20;            //Timer1 Mode1
    set_PCON_SMOD;          //UART0 Double Rate Enable
    clr_CKCON_T1M;
    clr_T3CON_BRCK;          //Serial port 0 baud rate clock source = Timer1
    TH1 = 255;
    set_TCON_TR1;
//    set_SCON_TI;           //For printf function must setting TI = 1
}

void LowPower_UART2_Send_Data( unsigned char c)
{
    clr_SC0CR0_TXOFF;
    SC0DR = c;
    while((SC0TSR|CLR_BIT3)==CLR_BIT3);
    clr_SC0CR0_TXOFF;
}