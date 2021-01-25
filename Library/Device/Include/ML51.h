/*--------------------------------------------------------------------------
ML56.H

Header file for Nuvoton ML56 Series
--------------------------------------------------------------------------*/

/******************************************************************************/
/*                         Macro define header files                          */
/******************************************************************************/
#include "SFR_Macro_ML51.h"

/* ML56 SFR BYTE page 0  */
sfr P0                         =0x80;
sfr SP                         =0x81;
sfr DPL                        =0x82;
sfr DPH                        =0x83;
sfr RCTRIM0                    =0x84;
sfr RCTRIM1                    =0x85;
sfr RWKL                       =0x86;
sfr PCON                       =0x87;

sfr TCON                       =0x88;
sfr TMOD                       =0x89;
sfr TL0                        =0x8A;
sfr TL1                        =0x8B;
sfr TH0                        =0x8C;
sfr TH1                        =0x8D;
sfr CKCON                      =0x8E;
sfr WKCON                      =0x8F;

sfr P1                         =0x90;
sfr SFRS                       =0x91;
sfr DMA0CR0                    =0x92;
sfr DMA0MAL                    =0x93;
sfr DMA0CNT                    =0x94;
sfr DMA0CCNT                   =0x95;
sfr CKSWT                      =0x96;
sfr CKEN                       =0x97;

sfr SCON                       =0x98;
sfr SBUF                       =0x99;
sfr SBUF1                      =0x9A;
sfr EIE0                       =0x9B;
sfr EIE1                       =0x9C;
sfr RSR                        =0x9D;
sfr CHPCON                     =0x9F;

sfr P2                         =0xA0;
sfr ADCCON0                    =0xA1;
sfr AUXR0                      =0xA2;
sfr BODCON0                    =0xA3;
sfr IAPTRG                     =0xA4;
sfr IAPUEN                     =0xA5;
sfr IAPAL                      =0xA6;
sfr IAPAH                      =0xA7;

sfr IE                         =0xA8;
sfr SADDR                      =0xA9;
sfr WDCON                      =0xAA;
sfr BODCON1                    =0xAB;
sfr EIP2                       =0xAC;
sfr EIPH2                      =0xAD;
sfr IAPFD                      =0xAE;
sfr IAPCN                      =0xAF;

sfr P3                         =0xB0;
sfr P5                         =0xB1;
sfr I2C1ADDR0                  =0xB2;
sfr I2C1DAT                    =0xB3;
sfr I2C1STAT                   =0xB4;
sfr I2C1CLK                    =0xB5;
sfr I2C1TOC                    =0xB6;
sfr IPH                        =0xB7;

sfr IP                         =0xB8;
sfr SADEN                      =0xB9;
sfr SADEN1                     =0xBA;
sfr SADDR1                     =0xBB;
sfr I2C0DAT                    =0xBC;
sfr I2C0STAT                   =0xBD;
sfr I2C0CLK                    =0xBE;
sfr I2C0TOC                    =0xBF;

sfr I2C0CON                    =0xC0;
sfr I2C0ADDR0                  =0xC1;
sfr ADCRL                      =0xC2;
sfr ADCRH                      =0xC3;
sfr T3CON                      =0xC4;
sfr RL3                        =0xC5;
sfr RH3                        =0xC6;
sfr TA                         =0xC7;

sfr T2CON                      =0xC8;
sfr T2MOD                      =0xC9;
sfr PIF                        =0xCA;
sfr ADCBAL                     =0xCB;
sfr TL2                        =0xCC;
sfr TH2                        =0xCD;
sfr ADCMPL                     =0xCE;
sfr ADCMPH                     =0xCF;

sfr PSW                        =0xD0;
sfr PWM0CON0                   =0xD1;
sfr ACMPCR0                    =0xD2;
sfr ACMPCR1                    =0xD3;
sfr ACMPSR                     =0xD4;
sfr ACMPVREF                   =0xD5;
sfr SC0CR0                     =0xD6;
sfr SC0CR1                     =0xD7;

sfr P4                         =0xD8;
sfr SC0DR                      =0xD9;
sfr SC0EGT                     =0xDA;
sfr SC0ETURD0                  =0xDB;
sfr SC0ETURD1                  =0xDC;
sfr SC0IE                      =0xDD;
sfr SC0IS                      =0xDE;
sfr SC0TSR                     =0xDF;

sfr ACC                        =0xE0;
sfr ADCCON1                    =0xE1;
sfr ADCCON2                    =0xE2;
sfr ADCDLY                     =0xE3;
sfr ADCBAH                     =0xE4;
sfr ADCSN                      =0xE5;
sfr ADCCN                      =0xE6;
sfr ADCSR                      =0xE7;

sfr I2C1CON                    =0xE8;
sfr DMA0TSR                    =0xE9;
sfr MTM0DAL                     =0xEA;
sfr DMA1CR0                    =0xEB;
sfr DMA1MAL                    =0xEC;
sfr DMA1CNT                    =0xED;
sfr DMA1CCNT                   =0xEE;
sfr EIP0                       =0xEF;

sfr B                          =0xF0;
sfr DMA1TSR                    =0xF1;
sfr MTM1DAL                     =0xF2;
sfr SPI0CR0                    =0xF3;
sfr SPI0SR                     =0xF4;
sfr SPI0DR                     =0xF5;
sfr DMA0BAH                    =0xF6;
sfr EIPH0                      =0xF7;

sfr S1CON                      =0xF8;
sfr SPI1CR0                    =0xF9;
sfr SPI1CR1                    =0xFA;
sfr SPI1SR                     =0xFB;
sfr SPI1DR                     =0xFC;
sfr DMA1BAH                    =0xFD;
sfr EIP1                       =0xFE;
sfr EIPH1                      =0xFF;

/* ML56 SFR BYTE page 1  */
sfr LIRCTRIM                   =0x84;
sfr XLTCON                     =0x85;
sfr CWKL                       =0x86;

sfr P0DW                       =0x8A;
sfr P1DW                       =0x8B;
sfr P2DW                       =0x8C;
sfr P3DW                       =0x8D;
sfr P4DW                       =0x8E;
sfr P5DW                       =0x8F;

sfr P0UP                       =0x92;
sfr P1UP                       =0x93;
sfr P2UP                       =0x94;
sfr P3UP                       =0x95;
sfr P4UP                       =0x96;
sfr P5UP                       =0x97;

sfr P0S                        =0x99;
sfr P0SR                       =0x9A;
sfr P1S                        =0x9B;
sfr P1SR                       =0x9C;
sfr P2S                        =0x9D;
sfr P2SR                       =0x9E;

sfr PIPS0                      =0xA1;
sfr PIPS1                      =0xA2;
sfr PIPS2                      =0xA3;
sfr PIPS3                      =0xA4;
sfr PIPS4                      =0xA5;
sfr PIPS5                      =0xA6;
sfr PIPS6                      =0xA7;

sfr VRFCON                     =0xA9;
sfr VRFTRIM                    =0xAA;
sfr ACMPCR2                    =0xAB;
sfr P3S                        =0xAC;
sfr P3SR                       =0xAD;
sfr P5SR                       =0xAE;
sfr PIPS7                      =0xAF;

sfr P0M1                       =0xB1;
sfr P0M2                       =0xB2;
sfr P1M1                       =0xB3;
sfr P1M2                       =0xB4;
sfr P2M1                       =0xB5;
sfr P2M2                       =0xB6;
sfr PWM0INTC                   =0xB7;

sfr P4M1                       =0xB9;
sfr P4M2                       =0xBA;
sfr P4S                        =0xBB;
sfr P4SR                       =0xBC;
sfr P5M1                       =0xBD;
sfr P5M2                       =0xBE;
sfr P5S                        =0xBF;

sfr CKDIV                      =0xC1;
sfr P3M1                       =0xC2;
sfr P3M2                       =0xC3;
sfr PWM0C4H                    =0xC4;
sfr PWM0C5H                    =0xC5;
sfr PORDIS                     =0xC6;

sfr AUXR1                      =0xC9;
sfr RCMP2L                     =0xCA;
sfr RCMP2H                     =0xCB;
sfr PWM0C4L                    =0xCC;
sfr PWM0C5L                    =0xCD;
sfr AINDIDS0                   =0xCE;

sfr PWM0PH                     =0xD1;
sfr PWM0C0H                    =0xD2;
sfr PWM0C1H                    =0xD3;
sfr PWM0C2H                    =0xD4;
sfr PWM0C3H                    =0xD5;
sfr PWM0NP                     =0xD6;
sfr PWM0FBD                    =0xD7;

sfr PWM0PL                     =0xD9;
sfr PWM0C0L                    =0xDA;
sfr PWM0C1L                    =0xDB;
sfr PWM0C2L                    =0xDC;
sfr PWM0C3L                    =0xDD;
sfr PWM0CON1                   =0xDF;

sfr CAPCON0                    =0xE1;
sfr CAPCON1                    =0xE2;
sfr CAPCON2                    =0xE3;
sfr C0L                        =0xE4;
sfr C0H                        =0xE5;
sfr C1L                        =0xE6;
sfr C1H                        =0xE7;

sfr PICON                      =0xE9;
sfr PINEN                      =0xEA;
sfr PIPEN                      =0xEB;
sfr C2L                        =0xED;
sfr C2H                        =0xEE;
sfr LDOTRIM                    =0xEF;

sfr SPI0CR1                    =0xF3;

sfr PWM0DTEN                   =0xF9;
sfr PWM0DTCNT                  =0xFA;
sfr PWM0MEN                    =0xFB;
sfr PWM0MD                     =0xFC;
sfr LVRFLTEN                   =0xFD;
sfr LVRDIS                     =0xFF;

/* ML56 SFR BYTE page 2  */
sfr P6M1                       =0x84;
sfr P6M2                       =0x85;
sfr PWM1PH                     =0x86;

sfr PWM1C0H                    =0x8A;
sfr PWM1C1H                    =0x8B;
sfr PWM1MD                     =0x8C;
sfr PWM1MEN                    =0x8D;
sfr P6SR                       =0x8E;
sfr P6DW                       =0x8F;

sfr P6MF10                     =0x92;
sfr P6MF32                     =0x93;
sfr P6MF54                     =0x94;
sfr P6MF76                     =0x95;
sfr P6S                        =0x96;
sfr P6UP                       =0x97;

sfr PWM1PL                     =0x99;
sfr PWM1C0L                    =0x9A;
sfr PWM1C1L                    =0x9B;
sfr PWM1CON0                   =0x9C;
sfr PWM1CON1                   =0x9D;
sfr PWM1INTC                   =0x9E;

sfr I2C0ADDR1                  =0xA1;
sfr I2C0ADDR2                  =0xA2;
sfr I2C0ADDR3                  =0xA3;
sfr I2C1ADDR1                  =0xA4;
sfr I2C1ADDR2                  =0xA5;
sfr I2C1ADDR3                  =0xA6;
sfr P6                         =0xA7;

sfr DMA3TSR                    =0xA9;
sfr DMA3BAH                    =0xAA;
sfr DMA3CR0                    =0xAB;
sfr DMA3MAL                    =0xAC;
sfr DMA3CNT                    =0xAD;
sfr DMA3CCNT                   =0xAE;
sfr MTM3DAL                    =0xAF;

sfr DMA2TSR                    =0xB1;
sfr DMA2BAH                    =0xB2;
sfr DMA2CR0                    =0xB3;
sfr DMA2MAL                    =0xB4;
sfr DMA2CNT                    =0xB5;
sfr DMA2CCNT                   =0xB6;
sfr MTM2DAL                    =0xB7;

sfr PWM2PH                     =0xB9;
sfr PWM2C0H                    =0xBA;
sfr PWM2C1H                    =0xBB;
sfr PWM2MD                     =0xBC;
sfr PWM2MEN                    =0xBD;
sfr CWKH                       =0xBE;
sfr RWKH                       =0xBF;

sfr PWM2PL                     =0xC1;
sfr PWM2C0L                    =0xC2;
sfr PWM2C1L                    =0xC3;
sfr PWM2CON0                   =0xC4;
sfr PWM2CON1                   =0xC5;
sfr PWM2INTC                   =0xC6;

sfr PWM3PH                     =0xC9;
sfr PWM3C0H                    =0xCA;
sfr PWM3C1H                    =0xCB;
sfr PWM3MD                     =0xCC;
sfr PWM3MEN                    =0xCD;
sfr AINDIDS1                   =0xCE;
sfr I2C0ADDRM                  =0xCF;

sfr PWM3PL                     =0xD1;
sfr PWM3C0L                    =0xD2;
sfr PWM3C1L                    =0xD3;
sfr PWM3CON0                   =0xD4;
sfr PWM3CON1                   =0xD5;
sfr PWM3INTC                   =0xD6;
sfr I2C1ADDRM                  =0xD7;

sfr SC1DR                      =0xD9;
sfr SC1EGT                     =0xDA;
sfr SC1ETURD0                  =0xDB;
sfr SC1ETURD1                  =0xDC;
sfr SC1IE                      =0xDD;
sfr SC1IS                      =0xDE;
sfr SC1TSR                     =0xDF;

sfr P5MF32                     =0xE1;
sfr P5MF54                     =0xE2;
sfr P5MF76                     =0xE3;
sfr BRCTRIM                    =0xE4;
sfr ADCCAL                     =0xE5;
sfr SC1CR0                     =0xE6;
sfr SC1CR1                     =0xE7;

sfr P3MF54                     =0xE9;
sfr P3MF76                     =0xEA;
sfr P4MF10                     =0xEB;
sfr P4MF32                     =0xEC;
sfr P4MF54                     =0xED;
sfr P4MF76                     =0xEE;
sfr P5MF10                     =0xEF;

sfr P1MF76                     =0xF1;
sfr P2MF10                     =0xF2;
sfr P2MF32                     =0xF3;
sfr P2MF54                     =0xF4;
sfr P2MF76                     =0xF5;
sfr P3MF10                     =0xF6;
sfr P3MF32                     =0xF7;

sfr P0MF10                     =0xF9;
sfr P0MF32                     =0xFA;
sfr P0MF54                     =0xFB;
sfr P0MF76                     =0xFC;
sfr P1MF10                     =0xFD;
sfr P1MF32                     =0xFE;
sfr P1MF54                     =0xFF;

/* ML56 SFR BYTE page 3  */

sfr DMA0CR1                    =0x8A;
sfr DMA1CR1                    =0x8B;
sfr DMA2CR1                    =0x8C;
sfr DMA3CR1                    =0x8D;

sfr DMA0CRC                    =0x92;
sfr DMA1CRC                    =0x93;
sfr DMA2CRC                    =0x94;
sfr DMA3CRC                    =0x95;

sfr WDCONH                     =0x99;
sfr DMA0SEED                   =0x9A;
sfr DMA1SEED                   =0x9B;
sfr DMA2SEED                   =0x9C;
sfr DMA3SEED                   =0x9D;

sfr RTCINIT                    =0xA1;
sfr RTCRWEN                    =0xA2;
sfr RTCCLKSEL                  =0xA3;
sfr RTCFREQADJ0                =0xA4;
sfr RTCFREQADJ1                =0xA5;
sfr RTCINTEN                   =0xA6;
sfr RTCINTSTS                  =0xA7;

sfr RTCTIMESEC                 =0xA9;
sfr RTCTIMEMIN                 =0xAA;
sfr RTCTIMEHR                  =0xAB;
sfr RTCCALDAY                  =0xAD;
sfr RTCCALMON                  =0xAE;
sfr RTCCALYEAR                 =0xAF;

sfr RTCTALMSEC                 =0xB1;
sfr RTCTALMMIN                 =0xB2;
sfr RTCTALMHR                  =0xB3;
sfr RTCTALMHZ                  =0xB4;
sfr RTCCALMDAY                 =0xB5;
sfr RTCCALMMON                 =0xB6;
sfr RTCCALMYEAR                =0xB7;

sfr RTCCLKFMT                  =0xB9;
sfr RTCWEEKDAY                 =0xBB;
sfr RTCLEAPYEAR                =0xBC;
sfr RTCTICK                    =0xBD;
sfr RTCTAMSK                   =0xBE;
sfr RTCCAMSK                   =0xBF;

sfr PWM0FBS                    =0xCE;
sfr AUXR3                      =0xCF;

sfr LCDCPALCT1                 =0xE9;
sfr LCDCPCT1                   =0xEA;

sfr LCDCPUMP                   =0xF1;
sfr LCDCON1                    =0xF4;
sfr LCDCPALCT0                 =0xF5;
sfr LCDCPCT0                   =0xF6;

sfr LCDCON0                    =0xF9;
sfr LCDCLK                     =0xFA;
sfr LCDPTR                     =0xFB;
sfr LCDDAT                     =0xFC;
sfr LCDPWR                     =0xFD;
sfr LCDBL                      =0xFE;
sfr LCDMODE                   =0xFF;



/*  BIT Registers  */
/*  P0  */
sbit P00        = P0^0;
sbit P01        = P0^1;
sbit P02        = P0^2;
sbit P03        = P0^3;
sbit P04        = P0^4;
sbit P05        = P0^5;
sbit P06        = P0^6;
sbit P07        = P0^7;

/*  TCON  */
sbit TF1        = TCON^7;
sbit TR1        = TCON^6;
sbit TF0        = TCON^5;
sbit TR0        = TCON^4;
sbit IE1        = TCON^3;
sbit IT1        = TCON^2;
sbit IE0        = TCON^1;
sbit IT0        = TCON^0;

/*  P1  */
sbit P10        = P1^0;
sbit P11        = P1^1;
sbit P12        = P1^2;
sbit P13        = P1^3;
sbit P14        = P1^4;
sbit P15        = P1^5;
sbit P16        = P1^6;
sbit P17        = P1^7;

/*  SCON  */
sbit SM0        = SCON^7;
sbit FE         = SCON^7;
sbit SM1        = SCON^6;
sbit SM2        = SCON^5;
sbit REN        = SCON^4;
sbit TB8        = SCON^3;
sbit RB8        = SCON^2;
sbit TI         = SCON^1;
sbit RI         = SCON^0;

/*  P2  */
sbit P20        = P2^0;
sbit P21        = P2^1;
sbit P22        = P2^2;
sbit P23        = P2^3;
sbit P24        = P2^4;
sbit P25        = P2^5;
sbit P26        = P2^6;
sbit P27        = P2^7;

/*  IE  */
sbit EA         = IE^7;
sbit EADC       = IE^6;
sbit EBOD       = IE^5;
sbit ES         = IE^4;
sbit ET1        = IE^3;
sbit EX1        = IE^2;
sbit ET0        = IE^1;
sbit EX0        = IE^0;

/*  P3  */
sbit P30        = P3^0;
sbit P31        = P3^1;
sbit P32        = P3^2;
sbit P33        = P3^3;
sbit P34        = P3^4;
sbit P35        = P3^5;
sbit P36        = P3^6;
sbit P37        = P3^7;

/*  IP  */
sbit PADC       = IP^6;
sbit PBOD       = IP^5;
sbit PS         = IP^4;
sbit PT1        = IP^3;
sbit PX1        = IP^2;
sbit PT0        = IP^1;
sbit PX0        = IP^0;

/*  I2CON  */
sbit I2CEN0     = I2C0CON^6;
sbit STA0       = I2C0CON^5;
sbit STO0       = I2C0CON^4;
sbit SI0        = I2C0CON^3;
sbit AA0        = I2C0CON^2;
sbit I2C0PX     = I2C0CON^0;

/*  I2C1CON  */
sbit I2CEN1      = I2C1CON^6;
sbit STA1        = I2C1CON^5;
sbit STO1        = I2C1CON^4;
sbit SI1         = I2C1CON^3;
sbit AA1         = I2C1CON^2;
sbit I2CPX1      = I2C1CON^0;

/*  T2CON  */
sbit TF2        = T2CON^7;
sbit TR2        = T2CON^2;
sbit CM_RL2     = T2CON^0;

/*  PSW */
sbit CY         = PSW^7;
sbit AC         = PSW^6;
sbit F0         = PSW^5;
sbit RS1        = PSW^4;
sbit RS0        = PSW^3;
sbit OV         = PSW^2;
sbit P          = PSW^0;

/*  P4  */
sbit P40        = P4^0;
sbit P41        = P4^1;
sbit P42        = P4^2;
sbit P43        = P4^3;
sbit P44        = P4^4;
sbit P45        = P4^5;
sbit P46        = P4^6;
sbit P47        = P4^7;


/*  SCON_1  */
sbit SM0_1      = S1CON^7;
sbit FE_1       = S1CON^7;
sbit SM1_1      = S1CON^6;
sbit SM2_1      = S1CON^5;
sbit REN_1      = S1CON^4;
sbit TB8_1      = S1CON^3;
sbit RB8_1      = S1CON^2;
sbit TI_1       = S1CON^1;
sbit RI_1       = S1CON^0;


// /*  Other Pin Name  */
sbit AIN0       = P2^5;
sbit AIN1       = P2^4;
sbit AIN2       = P2^3;
sbit AIN3       = P2^2;
sbit AIN4       = P2^1;
sbit AIN5       = P2^0;
sbit AIN6       = P3^1;
sbit AIN7       = P3^2;

