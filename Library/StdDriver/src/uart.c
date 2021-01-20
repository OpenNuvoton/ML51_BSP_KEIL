/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/29/2020
//***********************************************************************************************************

#include "ML51.h"
bit UART0PRINTFG=0,UART1PRINTFG=0, uart0_receive_flag = 0, uart1_receive_flag;
unsigned char uart0_receive_data, uart1_receive_data;


void Enable_UART0_VCOM_printf(void)
{
  /* UART0 initial setting
  ** include uart.c in Library for UART initial setting
  **UART0 define P3.1 TXD multi function setting
  **/
    MFP_P31_UART0_TXD;
    P31_QUASI_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
}
/* UART0 interrupt subroutine */
/**
 * @brief       UART0 interrupt subroutine
 * @param       UART0~3, baudrate value
 * @return      none
 * @details     none
 * @note        Since printf function TI must be 1. Check with printf flag, for printf enable, not clear TI . 
 */
void UART0_ISR(void) interrupt 4
{
    _push_(SFRS);
    if (RI)
    {
        uart0_receive_flag = 1;
        uart0_receive_data = SBUF;
        clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }
    if (TI)
    {
//        if (!UART0PRINTFG)
//            TI = 0;
    }
    _pop_(SFRS);
}


/* UART1 interrupt subroutine */
void UART1_ISR(void) interrupt 15
{
    _push_(SFRS);
    if (RI_1)
    {
        uart1_receive_flag = 1;
        uart1_receive_data = SBUF1;
        RI_1=0;                             /* clear reception flag for next reception */
    }
    if (TI_1)
        if (!UART1PRINTFG)
            TI_1 = 0;                       /* if emission occur */
    _pop_(SFRS);
}

/**
 * @brief       UART no interrupt enable setting 
 * @param       UART0~3, baudrate value
 * @return      none
 * @details     none
 * @note        max baud rate = 1.5MHz when Fsys = 24MHz
 */
//****************************************************************************************************************  
//**** UART Enable Setting  
//**** 1. Define Fsys value(value)
//**** 2. Select UART port(UART0_Timer1 / UART0_Timer3 / UART1_Timer3 / UART2/UART3) 
//**** 3. Define baudrate (value)
//**** For example: UART_Open(24000000,UART0_Timer1,115200)
void UART_Open(unsigned long u32SysClock, unsigned char u8UARTPort,unsigned long u32Baudrate)
{
  switch(u8UARTPort)
  {
      case UART0_Timer1:
      case UART0:
          SFRS = 0x00;
          SCON = 0x50;             /*UART0 Mode1,REN=1,TI=1 */
          TMOD |= 0x20;            /*Timer1 Mode1*/
          set_PCON_SMOD;          /*UART0 Double Rate Enable*/
          set_CKCON_T1M;
          clr_T3CON_BRCK;          /*Serial port 0 baud rate clock source = Timer1*/
          TH1 = 256 - (u32SysClock/16/u32Baudrate);
          set_TCON_TR1;
      break;
      case UART0_Timer3:
          SFRS = 0x00;
          SCON = 0x50;            /*UART0 Mode1,REN=1,TI=1*/
          set_PCON_SMOD;          /*UART0 Double Rate Enable*/
          T3CON &= 0xF8;          /*T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)*/
          set_T3CON_BRCK;         /*UART0 baud rate clock source = Timer3*/
          RH3    = HIBYTE(65536 - (u32SysClock/16/u32Baudrate));
          RL3    = LOBYTE(65536 - (u32SysClock/16/u32Baudrate));
          set_T3CON_TR3;          /*Trigger Timer3*/
      break;
      case UART1_Timer3:
      case UART1:
          SFRS = 0x00;
          S1CON = 0x50;           /*UART1 Mode1,REN_1=1 */
          T3CON = 0x88;           /*T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1*/
          RH3    = HIBYTE(65536 - (u32SysClock/16/u32Baudrate));
          RL3    = LOBYTE(65536 - (u32SysClock/16/u32Baudrate));
          set_T3CON_TR3;          /* Trigger Timer3 */
      break; 

  }
}
//****************************************************************************************************************  
//**** UART Receive data without interrupt  
//**** For example: UART_Open(UART0_Timer1,1200)
unsigned char UART_Receive_Data(unsigned char UARTPort)
{
    unsigned char c;
    SFRS = 0x00;
    switch (UARTPort)
    {
      case UART0:
        while (!RI);
        c = SBUF;
        RI = 0;
      break;
      case UART1:
        while (!RI_1);
        c = SBUF1;
        RI_1 = 0;
      break;
    }
    return (c);
}
//****************************************************************************************************************  
//**** UART transfer data without interrupt  
//**** For example: UART_Send_Data(UART0,0x55)
void UART_Send_Data(unsigned char UARTPort, unsigned char c)
{
    SFRS = 0x00;
    switch (UARTPort)
    {
      case UART0:
        TI = 0;
        SBUF = c;
        while(TI==0);
        TI = 0;
      break;
      case UART1:
        TI_1 = 0;
        SBUF1 = c;
        while(TI_1==0);
        TI_1 = 0;
      break;
    }
}


/**
 * @brief       UART interrupt enable setting 
 * @param       u8UARTPort: UART0/UART1/UART2/UART3 baudrate value
 * @param       u8UARTINTStatus: Disable/Enable
 * @return      none
 * @details     none
 * @note        max baud rate = 1.5MHz when Fsys = 24MHz
 */
void UART_Interrupt_Enable(unsigned char u8UARTPort, unsigned char u8UARTINTStatus)
{
    switch (u8UARTPort)
    {
        case UART0: 
          switch(u8UARTINTStatus)
          {
            case Disable: clr_IE_ES; break;
            case Enable:  set_IE_ES; break;
          }
        break;
        case UART1:
          switch(u8UARTINTStatus)
          {
            case Disable: clr_EIE1_ES1; break;
            case Enable:  set_EIE1_ES1; break;
          }
        break;
    }
}


