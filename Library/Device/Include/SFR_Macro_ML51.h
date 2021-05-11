/********************************************************************/
/*  <Define rule I> set or clr _ regsiter name _ register bit name  */
/********************************************************************/
/******************************************************************************/
/*                         Keil C51 include files                            */
/******************************************************************************/
#include <intrins.h>
#include <stdio.h>
#include <absacc.h>
#include <string.h>
#include <stdlib.h>

/******************************************************************************/
/******************************************************************************/
/*                         Peripheral header files                            */
/******************************************************************************/
#include "ML51_XSFR.h"
#include "Function_define_ML51.h"

#include "acmp.h"
#include "adc.h"
#include "bod.h"
#include "capture.h"
#include "common.h"
#include "delay.h"
#include "eeprom.h"
#include "eeprom_sprom.h"
#include "exint.h"
#include "gpio.h"
#include "i2c.h"
#include "IAP.h"
#include "IAP_sprom.h"
#include "lcd.h"
#include "lowpower.h"
#include "pdma.h"
#include "pinint.h"
#include "power.h"
#include "pwm0.h"
#include "pwm123.h"
#include "rtc.h"
#include "spi.h"
#include "sys.h"
#include "TrimLIRC.h"
#include "uart.h"
#include "uart2.h"
#include "uart3.h"
#include "vref.h"
#include "wdt.h"
#include "wkt.h"

/********SFR ALL PAGES*************/
/**** PCON  87H  PAGE A ****/
#define set_PCON_SMOD                    PCON|=0x80
#define set_PCON_SMOD0                   PCON|=0x40
#define set_PCON_LPR                     PCON|=0x20
#define set_PCON_POF                     PCON|=0x10
#define set_PCON_GF1                     PCON|=0x08
#define set_PCON_GF0                     PCON|=0x04
#define set_PCON_PD                      PCON|=0x02
#define set_PCON_IDLE                    PCON|=0x01

#define clr_PCON_SMOD                    PCON&=0x7F
#define clr_PCON_SMOD0                   PCON&=0xBF
#define clr_PCON_LPR                     PCON&=0xDF
#define clr_PCON_POF                     PCON&=0xEF
#define clr_PCON_GF1                     PCON&=0xF7
#define clr_PCON_GF0                     PCON&=0xFB
#define clr_PCON_PD                      PCON&=0xFD
#define clr_PCON_IDLE                    PCON&=0xFE

/**** TCON  88H  PAGE A ****/
#define set_TCON_TF1                     TCON|=0x80
#define set_TCON_TR1                     TCON|=0x40
#define set_TCON_TF0                     TCON|=0x20
#define set_TCON_TR0                     TCON|=0x10
#define set_TCON_IE1                     TCON|=0x08
#define set_TCON_IT1                     TCON|=0x04
#define set_TCON_IE0                     TCON|=0x02
#define set_TCON_IT0                     TCON|=0x01

#define clr_TCON_TF1                     TCON&=0x7F
#define clr_TCON_TR1                     TCON&=0xBF
#define clr_TCON_TF0                     TCON&=0xDF
#define clr_TCON_TR0                     TCON&=0xEF
#define clr_TCON_IE1                     TCON&=0xF7
#define clr_TCON_IT1                     TCON&=0xFB
#define clr_TCON_IE0                     TCON&=0xFD
#define clr_TCON_IT0                     TCON&=0xFE

/**** TMOD  89H  PAGE A ****/
#define set_TMOD_0_GATE                  TMOD|=0x80
#define set_TMOD_0_C_T                   TMOD|=0x40
#define set_TMOD_0_M1                    TMOD|=0x20
#define set_TMOD_0_M0                    TMOD|=0x10
#define set_TMOD_1_GATE                  TMOD|=0x08
#define set_TMOD_1_C_T                   TMOD|=0x04
#define set_TMOD_1_M1                    TMOD|=0x02
#define set_TMOD_1_M0                    TMOD|=0x01

#define clr_TMOD_0_GATE                  TMOD&=0x7F
#define clr_TMOD_0_C_T                   TMOD&=0xBF
#define clr_TMOD_0_M1                    TMOD&=0xDF
#define clr_TMOD_0_M0                    TMOD&=0xEF
#define clr_TMOD_1_GATE                  TMOD&=0xF7
#define clr_TMOD_1_C_T                   TMOD&=0xFB
#define clr_TMOD_1_M1                    TMOD&=0xFD
#define clr_TMOD_1_M0                    TMOD&=0xFE

/**** P1  90H  PAGE A ****/
#define set_P1_7                         P1|=0x80
#define set_P1_6                         P1|=0x40
#define set_P1_5                         P1|=0x20
#define set_P1_4                         P1|=0x10
#define set_P1_3                         P1|=0x08
#define set_P1_2                         P1|=0x04
#define set_P1_1                         P1|=0x02
#define set_P1_0                         P1|=0x01

#define clr_P1_7                         P1&=0x7F
#define clr_P1_6                         P1&=0xBF
#define clr_P1_5                         P1&=0xDF
#define clr_P1_4                         P1&=0xEF
#define clr_P1_3                         P1&=0xF7
#define clr_P1_2                         P1&=0xFB
#define clr_P1_1                         P1&=0xFD
#define clr_P1_0                         P1&=0xFE

/**** SCON  98H  PAGE A ****/
#define set_SCON_SM0                     SCON|=0x80
#define set_SCON_FE                      SCON|=0x80
#define set_SCON_SM1                     SCON|=0x40
#define set_SCON_SM2                     SCON|=0x20
#define set_SCON_REN                     SCON|=0x10
#define set_SCON_TB8                     SCON|=0x08
#define set_SCON_RB8                     SCON|=0x04
#define set_SCON_TI                      SCON|=0x02
#define set_SCON_RI                      SCON|=0x01

#define clr_SCON_SM0                     SCON&=0x7F
#define clr_SCON_FE                      SCON&=0x7F
#define clr_SCON_SM1                     SCON&=0xBF
#define clr_SCON_SM2                     SCON&=0xDF
#define clr_SCON_REN                     SCON&=0xEF
#define clr_SCON_TB8                     SCON&=0xF7
#define clr_SCON_RB8                     SCON&=0xFB
#define clr_SCON_TI                      SCON&=0xFD
#define clr_SCON_RI                      SCON&=0xFE

/**** P2  A0H  PAGE A ****/
#define set_P2_7                         P2|=0x80
#define set_P2_6                         P2|=0x40
#define set_P2_5                         P2|=0x20
#define set_P2_4                         P2|=0x10
#define set_P2_3                         P2|=0x08
#define set_P2_2                         P2|=0x04
#define set_P2_1                         P2|=0x02
#define set_P2_0                         P2|=0x01

#define clr_P2_7                         P2&=0x7F
#define clr_P2_6                         P2&=0xBF
#define clr_P2_5                         P2&=0xDF
#define clr_P2_4                         P2&=0xEF
#define clr_P2_3                         P2&=0xF7
#define clr_P2_2                         P2&=0xFB
#define clr_P2_1                         P2&=0xFD
#define clr_P2_0                         P2&=0xFE

/**** IE  A8H  PAGE A ****/
#define set_IE_EA                        IE|=0x80
#define set_IE_EADC                      IE|=0x40
#define set_IE_EBOD                      IE|=0x20
#define set_IE_ES                        IE|=0x10
#define set_IE_ET1                       IE|=0x08
#define set_IE_EX1                       IE|=0x04
#define set_IE_ET0                       IE|=0x02
#define set_IE_EX0                       IE|=0x01

#define clr_IE_EA                        IE&=0x7F
#define clr_IE_EADC                      IE&=0xBF
#define clr_IE_EBOD                      IE&=0xDF
#define clr_IE_ES                        IE&=0xEF
#define clr_IE_ET1                       IE&=0xF7
#define clr_IE_EX1                       IE&=0xFB
#define clr_IE_ET0                       IE&=0xFD
#define clr_IE_EX0                       IE&=0xFE

/**** P3  B0H  PAGE A ****/
#define set_P3_7                         P3|=0x80
#define set_P3_6                         P3|=0x40
#define set_P3_5                         P3|=0x20
#define set_P3_4                         P3|=0x10
#define set_P3_3                         P3|=0x08
#define set_P3_2                         P3|=0x04
#define set_P3_1                         P3|=0x02
#define set_P3_0                         P3|=0x01

#define clr_P3_7                         P3&=0x7F
#define clr_P3_6                         P3&=0xBF
#define clr_P3_5                         P3&=0xDF
#define clr_P3_4                         P3&=0xEF
#define clr_P3_3                         P3&=0xF7
#define clr_P3_2                         P3&=0xFB
#define clr_P3_1                         P3&=0xFD
#define clr_P3_0                         P3&=0xFE

/**** IP  B8H  PAGE A ****/
#define set_IP_PADC                      IP|=0x40
#define set_IP_PBOD                      IP|=0x20
#define set_IP_PS                        IP|=0x10
#define set_IP_PT1                       IP|=0x08
#define set_IP_PX1                       IP|=0x04
#define set_IP_PT0                       IP|=0x02
#define set_IP_PX0                       IP|=0x01

#define clr_IP_PADC                      IP&=0xBF
#define clr_IP_PBOD                      IP&=0xDF
#define clr_IP_PS                        IP&=0xEF
#define clr_IP_PT1                       IP&=0xF7
#define clr_IP_PX1                       IP&=0xFB
#define clr_IP_PT0                       IP&=0xFD
#define clr_IP_PX0                       IP&=0xFE

/**** I2C0CON  C0H  PAGE A ****/
#define set_I2C0CON_I2CEN                I2C0CON|=0x40
#define set_I2C0CON_STA                  I2C0CON|=0x20
#define set_I2C0CON_STO                  I2C0CON|=0x10
#define set_I2C0CON_SI                   I2C0CON|=0x08
#define set_I2C0CON_AA                   I2C0CON|=0x04
#define set_I2C0CON_I2CPX                I2C0CON|=0x01

#define clr_I2C0CON_I2CEN                I2C0CON&=0xBF
#define clr_I2C0CON_STA                  I2C0CON&=0xDF
#define clr_I2C0CON_STO                  I2C0CON&=0xEF
#define clr_I2C0CON_SI                   I2C0CON&=0xF7
#define clr_I2C0CON_AA                   I2C0CON&=0xFB
#define clr_I2C0CON_I2CPX                I2C0CON&=0xFE

/**** T2CON  C8H  PAGE A ****/
#define set_T2CON_TF2                    T2CON|=0x80
#define set_T2CON_TR2                    T2CON|=0x04
#define set_T2CON_CMRL2                  T2CON|=0x01

#define clr_T2CON_TF2                    T2CON&=0x7F
#define clr_T2CON_TR2                    T2CON&=0xFB
#define clr_T2CON_CMRL2                  T2CON&=0xFE

/**** PSW  D0H  PAGE A ****/
#define set_PSW_CY                       PSW|=0x80
#define set_PSW_AC                       PSW|=0x40
#define set_PSW_F0                       PSW|=0x20
#define set_PSW_RS1                      PSW|=0x10
#define set_PSW_RS0                      PSW|=0x08
#define set_PSW_OV                       PSW|=0x04
#define set_PSW_P                        PSW|=0x01

#define clr_PSW_CY                       PSW&=0x7F
#define clr_PSW_AC                       PSW&=0xBF
#define clr_PSW_F0                       PSW&=0xDF
#define clr_PSW_RS1                      PSW&=0xEF
#define clr_PSW_RS0                      PSW&=0xF7
#define clr_PSW_OV                       PSW&=0xFB
#define clr_PSW_P                        PSW&=0xFE

/**** P4  D8H  PAGE A ****/
#define set_P4_7                         P4|=0x80
#define set_P4_6                         P4|=0x40
#define set_P4_5                         P4|=0x20
#define set_P4_4                         P4|=0x10
#define set_P4_3                         P4|=0x08
#define set_P4_2                         P4|=0x04
#define set_P4_1                         P4|=0x02
#define set_P4_0                         P4|=0x01

#define clr_P4_7                         P4&=0x7F
#define clr_P4_6                         P4&=0xBF
#define clr_P4_5                         P4&=0xDF
#define clr_P4_4                         P4&=0xEF
#define clr_P4_3                         P4&=0xF7
#define clr_P4_2                         P4&=0xFB
#define clr_P4_1                         P4&=0xFD
#define clr_P4_0                         P4&=0xFE

/**** ACC  E0H  PAGE A ****/
#define set_ACC_7                        ACC|=0x80
#define set_ACC_6                        ACC|=0x40
#define set_ACC_5                        ACC|=0x20
#define set_ACC_4                        ACC|=0x10
#define set_ACC_3                        ACC|=0x08
#define set_ACC_2                        ACC|=0x04
#define set_ACC_1                        ACC|=0x02
#define set_ACC_0                        ACC|=0x01

#define clr_ACC_7                        ACC&=0x7F
#define clr_ACC_6                        ACC&=0xBF
#define clr_ACC_5                        ACC&=0xDF
#define clr_ACC_4                        ACC&=0xEF
#define clr_ACC_3                        ACC&=0xF7
#define clr_ACC_2                        ACC&=0xFB
#define clr_ACC_1                        ACC&=0xFD
#define clr_ACC_0                        ACC&=0xFE

/**** I2C1CON  E8H  PAGE A ****/
#define set_I2C1CON_I                    I2C1CON|=0x80
#define set_I2C1CON_I2CEN                I2C1CON|=0x40
#define set_I2C1CON_STA                  I2C1CON|=0x20
#define set_I2C1CON_STO                  I2C1CON|=0x10
#define set_I2C1CON_SI                   I2C1CON|=0x08
#define set_I2C1CON_AA                   I2C1CON|=0x04

#define clr_I2C1CON_I                    I2C1CON&=0x7F
#define clr_I2C1CON_I2CEN                I2C1CON&=0xBF
#define clr_I2C1CON_STA                  I2C1CON&=0xDF
#define clr_I2C1CON_STO                  I2C1CON&=0xEF
#define clr_I2C1CON_SI                   I2C1CON&=0xF7
#define clr_I2C1CON_AA                   I2C1CON&=0xFB

/**** S1CON  F8H  PAGE A ****/
#define set_S1CON_FE_1                   SFRS=0;S1CON|=SET_BIT7 
#define set_S1CON_SM1_1                  SFRS=0;S1CON|=SET_BIT6 
#define set_S1CON_SM2_1                  SFRS=0;S1CON|=SET_BIT5 
#define set_S1CON_REN_1                  SFRS=0;S1CON|=SET_BIT4 
#define set_S1CON_TB8_1                  SFRS=0;S1CON|=SET_BIT3 
#define set_S1CON_RB8_1                  SFRS=0;S1CON|=SET_BIT2 
#define set_S1CON_TI_1                   SFRS=0;S1CON|=SET_BIT1 
#define set_S1CON_RI_1                   SFRS=0;S1CON|=SET_BIT0 
                                         
#define clr_S1CON_FE_1                   SFRS=0;S1CON&=CLR_BIT7
#define clr_S1CON_SM1_1                  SFRS=0;S1CON&=CLR_BIT6
#define clr_S1CON_SM2_1                  SFRS=0;S1CON&=CLR_BIT5
#define clr_S1CON_REN_1                  SFRS=0;S1CON&=CLR_BIT4
#define clr_S1CON_TB8_1                  SFRS=0;S1CON&=CLR_BIT3
#define clr_S1CON_RB8_1                  SFRS=0;S1CON&=CLR_BIT2
#define clr_S1CON_TI_1                   SFRS=0;S1CON&=CLR_BIT1
#define clr_S1CON_RI_1                   SFRS=0;S1CON&=CLR_BIT0
/********SFR PAGE 0*************/
/**** RCTRIM1  85H  PAGE 0 TA protect register ****/
#define set_RCTRIM1_HIRCTRIM_0           SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;RCTRIM1|=0x01;EA=BIT_TMP

#define clr_RCTRIM1_HIRCTRIM_0           SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;RCTRIM1&=0xFE;EA=BIT_TMP

/**** CKCON  8EH  PAGE 0 ****/
#define set_CKCON_FASTWK                 SFRS=0;CKCON|=0x80
#define set_CKCON_PWMCKS                 SFRS=0;CKCON|=0x40
#define set_CKCON_T1OE                   SFRS=0;CKCON|=0x20
#define set_CKCON_T1M                    SFRS=0;CKCON|=0x10
#define set_CKCON_T0M                    SFRS=0;CKCON|=0x08
#define set_CKCON_T0OE                   SFRS=0;CKCON|=0x04
#define set_CKCON_CLOEN                  SFRS=0;CKCON|=0x02

#define clr_CKCON_FASTWK                 SFRS=0;CKCON&=0x7F
#define clr_CKCON_PWMCKS                 SFRS=0;CKCON&=0xBF
#define clr_CKCON_T1OE                   SFRS=0;CKCON&=0xDF
#define clr_CKCON_T1M                    SFRS=0;CKCON&=0xEF
#define clr_CKCON_T0M                    SFRS=0;CKCON&=0xF7
#define clr_CKCON_T0OE                   SFRS=0;CKCON&=0xFB
#define clr_CKCON_CLOEN                  SFRS=0;CKCON&=0xFD

/**** WKCON  8FH  PAGE 0 ****/
#define set_WKCON_WKTCK                  SFRS=0;WKCON|=0x20
#define set_WKCON_WKTF                   SFRS=0;WKCON|=0x10
#define set_WKCON_WKTR                   SFRS=0;WKCON|=0x08
#define set_WKCON_WKPS_2                 SFRS=0;WKCON|=0x04
#define set_WKCON_WKPS_1                 SFRS=0;WKCON|=0x02
#define set_WKCON_WKPS_0                 SFRS=0;WKCON|=0x01

#define clr_WKCON_WKTCK                  SFRS=0;WKCON&=0xDF
#define clr_WKCON_WKTF                   SFRS=0;WKCON&=0xEF
#define clr_WKCON_WKTR                   SFRS=0;WKCON&=0xF7
#define clr_WKCON_WKPS_2                 SFRS=0;WKCON&=0xFB
#define clr_WKCON_WKPS_1                 SFRS=0;WKCON&=0xFD
#define clr_WKCON_WKPS_0                 SFRS=0;WKCON&=0xFE

/**** DMA0CR0  92H  PAGE 0 ****/
#define set_DMA0CR0_PSSEL_3              SFRS=0;DMA0CR0|=0x80
#define set_DMA0CR0_PSSEL_2              SFRS=0;DMA0CR0|=0x40
#define set_DMA0CR0_PSSEL_1              SFRS=0;DMA0CR0|=0x20
#define set_DMA0CR0_PSSEL_0              SFRS=0;DMA0CR0|=0x10
#define set_DMA0CR0_HIE                  SFRS=0;DMA0CR0|=0x08
#define set_DMA0CR0_FIE                  SFRS=0;DMA0CR0|=0x04
#define set_DMA0CR0_RUN                  SFRS=0;DMA0CR0|=0x02
#define set_DMA0CR0_EN                   SFRS=0;DMA0CR0|=0x01

#define clr_DMA0CR0_PSSEL_3              SFRS=0;DMA0CR0&=0x7F
#define clr_DMA0CR0_PSSEL_2              SFRS=0;DMA0CR0&=0xBF
#define clr_DMA0CR0_PSSEL_1              SFRS=0;DMA0CR0&=0xDF
#define clr_DMA0CR0_PSSEL_0              SFRS=0;DMA0CR0&=0xEF
#define clr_DMA0CR0_HIE                  SFRS=0;DMA0CR0&=0xF7
#define clr_DMA0CR0_FIE                  SFRS=0;DMA0CR0&=0xFB
#define clr_DMA0CR0_RUN                  SFRS=0;DMA0CR0&=0xFD
#define clr_DMA0CR0_EN                   SFRS=0;DMA0CR0&=0xFE

/**** CKSWT  96H  PAGE 0 TA protect register ****/
#define set_CKSWT_HXTST                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT|=0x80;EA=BIT_TMP
#define set_CKSWT_LXTST                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT|=0x40;EA=BIT_TMP
#define set_CKSWT_HIRCST                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT|=0x20;EA=BIT_TMP
#define set_CKSWT_LIRCST                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT|=0x10;EA=BIT_TMP
#define set_CKSWT_ECLKST                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT|=0x08;EA=BIT_TMP
#define set_CKSWT_OSC_2                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT|=0x04;EA=BIT_TMP
#define set_CKSWT_OSC_1                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT|=0x02;EA=BIT_TMP
#define set_CKSWT_OSC_0                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT|=0x01;EA=BIT_TMP

#define clr_CKSWT_HXTST                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT&=0x7F;EA=BIT_TMP
#define clr_CKSWT_LXTST                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT&=0xBF;EA=BIT_TMP
#define clr_CKSWT_HIRCST                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT&=0xDF;EA=BIT_TMP
#define clr_CKSWT_LIRCST                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT&=0xEF;EA=BIT_TMP
#define clr_CKSWT_ECLKST                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT&=0xF7;EA=BIT_TMP
#define clr_CKSWT_OSC_2                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT&=0xFB;EA=BIT_TMP
#define clr_CKSWT_OSC_1                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT&=0xFD;EA=BIT_TMP
#define clr_CKSWT_OSC_0                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKSWT&=0xFE;EA=BIT_TMP

/**** CKEN  97H  PAGE 0 TA protect register ****/
#define set_CKEN_EHXTEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN|=0x80;EA=BIT_TMP
#define set_CKEN_ELXTEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN|=0x40;EA=BIT_TMP
#define set_CKEN_HIRCEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN|=0x20;EA=BIT_TMP
#define set_CKEN_LIRCEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN|=0x10;EA=BIT_TMP
#define set_CKEN_ECLKEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN|=0x08;EA=BIT_TMP
#define set_CKEN_CKSWTF                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN|=0x01;EA=BIT_TMP

#define clr_CKEN_EHXTEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN&=0x7F;EA=BIT_TMP
#define clr_CKEN_ELXTEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN&=0xBF;EA=BIT_TMP
#define clr_CKEN_HIRCEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN&=0xDF;EA=BIT_TMP
#define clr_CKEN_LIRCEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN&=0xEF;EA=BIT_TMP
#define clr_CKEN_ECLKEN                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN&=0xF7;EA=BIT_TMP
#define clr_CKEN_CKSWTF                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CKEN&=0xFE;EA=BIT_TMP

/**** EIE0  9BH  PAGE 0 ****/
#define set_EIE0_ET2                     SFRS=0;EIE0|=0x80
#define set_EIE0_ESPI0                   SFRS=0;EIE0|=0x40
#define set_EIE0_EFB0                    SFRS=0;EIE0|=0x20
#define set_EIE0_EWDT                    SFRS=0;EIE0|=0x10
#define set_EIE0_EPWM0                   SFRS=0;EIE0|=0x08
#define set_EIE0_ECAP                    SFRS=0;EIE0|=0x04
#define set_EIE0_EPI                     SFRS=0;EIE0|=0x02
#define set_EIE0_EI2C0                   SFRS=0;EIE0|=0x01

#define clr_EIE0_ET2                     SFRS=0;EIE0&=0x7F
#define clr_EIE0_ESPI0                   SFRS=0;EIE0&=0xBF
#define clr_EIE0_EFB0                    SFRS=0;EIE0&=0xDF
#define clr_EIE0_EWDT                    SFRS=0;EIE0&=0xEF
#define clr_EIE0_EPWM0                   SFRS=0;EIE0&=0xF7
#define clr_EIE0_ECAP                    SFRS=0;EIE0&=0xFB
#define clr_EIE0_EPI                     SFRS=0;EIE0&=0xFD
#define clr_EIE0_EI2C0                   SFRS=0;EIE0&=0xFE

/**** EIE1  9CH  PAGE 0 ****/
#define set_EIE1_EPWM123                 SFRS=0;EIE1|=0x40
#define set_EIE1_EI2C1                   SFRS=0;EIE1|=0x20
#define set_EIE1_ESPI1                   SFRS=0;EIE1|=0x10
#define set_EIE1_EHFI                    SFRS=0;EIE1|=0x08
#define set_EIE1_EWKT                    SFRS=0;EIE1|=0x04
#define set_EIE1_ET3                     SFRS=0;EIE1|=0x02
#define set_EIE1_ES1                     SFRS=0;EIE1|=0x01

#define clr_EIE1_EPWM123                 SFRS=0;EIE1&=0xBF
#define clr_EIE1_EI2C1                   SFRS=0;EIE1&=0xDF
#define clr_EIE1_ESPI1                   SFRS=0;EIE1&=0xEF
#define clr_EIE1_EHFI                    SFRS=0;EIE1&=0xF7
#define clr_EIE1_EWKT                    SFRS=0;EIE1&=0xFB
#define clr_EIE1_ET3                     SFRS=0;EIE1&=0xFD
#define clr_EIE1_ES1                     SFRS=0;EIE1&=0xFE

/**** RSR  9DH  PAGE 0 ****/
#define set_RSR_LVRF                     SFRS=0;RSR|=0x80
#define set_RSR_PORF                     SFRS=0;RSR|=0x40
#define set_RSR_HFRF                     SFRS=0;RSR|=0x20
#define set_RSR_POF                      SFRS=0;RSR|=0x10
#define set_RSR_RSTPINF                  SFRS=0;RSR|=0x08
#define set_RSR_BOR                      SFRS=0;RSR|=0x04
#define set_RSR_WDTRF                    SFRS=0;RSR|=0x02
#define set_RSR_SWRF                     SFRS=0;RSR|=0x01

#define clr_RSR_LVRF                     SFRS=0;RSR&=0x7F
#define clr_RSR_PORF                     SFRS=0;RSR&=0xBF
#define clr_RSR_HFRF                     SFRS=0;RSR&=0xDF
#define clr_RSR_POF                      SFRS=0;RSR&=0xEF
#define clr_RSR_RSTPINF                  SFRS=0;RSR&=0xF7
#define clr_RSR_BOR                      SFRS=0;RSR&=0xFB
#define clr_RSR_WDTRF                    SFRS=0;RSR&=0xFD
#define clr_RSR_SWRF                     SFRS=0;RSR&=0xFE

/**** CHPCON  9FH  PAGE 0 TA protect register ****/
#define set_CHPCON_SWRST                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON|=0x80;EA=BIT_TMP
#define set_CHPCON_IAPFF                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON|=0x40;EA=BIT_TMP
#define set_CHPCON_BS                    SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON|=0x02;EA=BIT_TMP
#define set_CHPCON_IAPEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON|=0x01;EA=BIT_TMP

#define clr_CHPCON_SWRST                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON&=0x7F;EA=BIT_TMP
#define clr_CHPCON_IAPFF                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON&=0xBF;EA=BIT_TMP
#define clr_CHPCON_BS                    SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON&=0xFD;EA=BIT_TMP
#define clr_CHPCON_IAPEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;CHPCON&=0xFE;EA=BIT_TMP

/**** ADCCON0  A0H  PAGE 0 ****/
#define set_ADCCON0_ADCF                 SFRS=0;ADCCON0|=0x80
#define set_ADCCON0_ADCS                 SFRS=0;ADCCON0|=0x40
#define set_ADCCON0_ETGSEL1              SFRS=0;ADCCON0|=0x20
#define set_ADCCON0_ETGSEL0              SFRS=0;ADCCON0|=0x10
#define set_ADCCON0_ADCHS3               SFRS=0;ADCCON0|=0x08
#define set_ADCCON0_ADCHS2               SFRS=0;ADCCON0|=0x04
#define set_ADCCON0_ADCHS1               SFRS=0;ADCCON0|=0x02
#define set_ADCCON0_ADCHS0               SFRS=0;ADCCON0|=0x01

#define clr_ADCCON0_ADCF                 SFRS=0;ADCCON0&=0x7F
#define clr_ADCCON0_ADCS                 SFRS=0;ADCCON0&=0xBF
#define clr_ADCCON0_ETGSEL1              SFRS=0;ADCCON0&=0xDF
#define clr_ADCCON0_ETGSEL0              SFRS=0;ADCCON0&=0xEF
#define clr_ADCCON0_ADCHS3               SFRS=0;ADCCON0&=0xF7
#define clr_ADCCON0_ADCHS2               SFRS=0;ADCCON0&=0xFB
#define clr_ADCCON0_ADCHS1               SFRS=0;ADCCON0&=0xFD
#define clr_ADCCON0_ADCHS0               SFRS=0;ADCCON0&=0xFE

/**** AUXR0  A2H  PAGE 0 ****/
#define set_AUXR0_SWRF                   SFRS=0;AUXR0|=0x80
#define set_AUXR0_RSTPINF                SFRS=0;AUXR0|=0x40
#define set_AUXR0_HFRF                   SFRS=0;AUXR0|=0x20
#define set_AUXR0_HFIF                   SFRS=0;AUXR0|=0x10
#define set_AUXR0_GF2                    SFRS=0;AUXR0|=0x08
#define set_AUXR0_0                      SFRS=0;AUXR0|=0x02
#define set_AUXR0_DPS                    SFRS=0;AUXR0|=0x01

#define clr_AUXR0_SWRF                   SFRS=0;AUXR0&=0x7F
#define clr_AUXR0_RSTPINF                SFRS=0;AUXR0&=0xBF
#define clr_AUXR0_HFRF                   SFRS=0;AUXR0&=0xDF
#define clr_AUXR0_HFIF                   SFRS=0;AUXR0&=0xEF
#define clr_AUXR0_GF2                    SFRS=0;AUXR0&=0xF7
#define clr_AUXR0_0                      SFRS=0;AUXR0&=0xFD
#define clr_AUXR0_DPS                    SFRS=0;AUXR0&=0xFE

/**** BODCON0  A3H  PAGE 0 TA protect register ****/
#define set_BODCON0_BODEN                SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0|=0x80;EA=BIT_TMP
#define set_BODCON0_BOV2                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0|=0x40;EA=BIT_TMP
#define set_BODCON0_BOV1                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0|=0x20;EA=BIT_TMP
#define set_BODCON0_BOV0                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0|=0x10;EA=BIT_TMP
#define set_BODCON0_BOF                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0|=0x08;EA=BIT_TMP
#define set_BODCON0_BORST                SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0|=0x04;EA=BIT_TMP
#define set_BODCON0_BORF                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0|=0x02;EA=BIT_TMP
#define set_BODCON0_BOS                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0|=0x01;EA=BIT_TMP

#define clr_BODCON0_BODEN                SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0&=0x7F;EA=BIT_TMP
#define clr_BODCON0_BOV2                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0&=0xBF;EA=BIT_TMP
#define clr_BODCON0_BOV1                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0&=0xDF;EA=BIT_TMP
#define clr_BODCON0_BOV0                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0&=0xEF;EA=BIT_TMP
#define clr_BODCON0_BOF                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0&=0xF7;EA=BIT_TMP
#define clr_BODCON0_BORST                SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0&=0xFB;EA=BIT_TMP
#define clr_BODCON0_BORF                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0&=0xFD;EA=BIT_TMP
#define clr_BODCON0_BOS                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON0&=0xFE;EA=BIT_TMP

/**** IAPTRG  A4H  PAGE 0 TA protect register ****/
#define set_IAPTRG_IAPGO                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPTRG|=0x01;EA=BIT_TMP
#define set_IAPTRG_IAPGO_WDCLR           SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=0x40;TA=0xAA;TA=0x55;IAPTRG|=0x01;EA=BIT_TMP
#define clr_IAPTRG_IAPGO                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPTRG&=0xFE;EA=BIT_TMP

/**** IAPUEN  A5H  PAGE 0 TA protect register ****/
#define set_IAPUEN_SPMEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN|=0x10;EA=BIT_TMP
#define set_IAPUEN_SPUEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN|=0x08;EA=BIT_TMP
#define set_IAPUEN_CFUEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN|=0x04;EA=BIT_TMP
#define set_IAPUEN_LDUEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN|=0x02;EA=BIT_TMP
#define set_IAPUEN_APUEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN|=0x01;EA=BIT_TMP

#define clr_IAPUEN_SPMEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN&=0xEF;EA=BIT_TMP
#define clr_IAPUEN_SPUEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN&=0xF7;EA=BIT_TMP
#define clr_IAPUEN_CFUEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN&=0xFB;EA=BIT_TMP
#define clr_IAPUEN_LDUEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN&=0xFD;EA=BIT_TMP
#define clr_IAPUEN_APUEN                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;IAPUEN&=0xFE;EA=BIT_TMP

/**** WDCON  AAH  PAGE 0 TA protect register ****/
#define set_WDCON_WDTR                   SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=0x80;EA=BIT_TMP
#define set_WDCON_WDCLR                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=0x40;EA=BIT_TMP
#define set_WDCON_WDTF                   SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=0x20;EA=BIT_TMP
#define set_WDCON_WIDPD                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=0x10;EA=BIT_TMP
#define set_WDCON_WDTRF                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=0x08;EA=BIT_TMP
#define set_WDCON_WDPS_2                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=0x04;EA=BIT_TMP
#define set_WDCON_WDPS_1                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=0x02;EA=BIT_TMP
#define set_WDCON_WDPS_0                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON|=0x01;EA=BIT_TMP

#define clr_WDCON_WDTR                   SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON&=0x7F;EA=BIT_TMP
#define clr_WDCON_WDCLR                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON&=0xBF;EA=BIT_TMP
#define clr_WDCON_WDTF                   SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON&=0xDF;EA=BIT_TMP
#define clr_WDCON_WIDPD                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON&=0xEF;EA=BIT_TMP
#define clr_WDCON_WDTRF                  SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON&=0xF7;EA=BIT_TMP
#define clr_WDCON_WDPS_2                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON&=0xFB;EA=BIT_TMP
#define clr_WDCON_WDPS_1                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON&=0xFD;EA=BIT_TMP
#define clr_WDCON_WDPS_0                 SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCON&=0xFE;EA=BIT_TMP

/**** BODCON1  ABH  PAGE 0 TA protect register ****/
#define set_BODCON1_LPBOD_1              SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON1|=0x04;EA=BIT_TMP
#define set_BODCON1_LPBOD_0              SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON1|=0x02;EA=BIT_TMP
#define set_BODCON1_BODFLT               SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON1|=0x01;EA=BIT_TMP

#define clr_BODCON1_LPBOD_1              SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON1&=0xFB;EA=BIT_TMP
#define clr_BODCON1_LPBOD_0              SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON1&=0xFD;EA=BIT_TMP
#define clr_BODCON1_BODFLT               SFRS=0;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;BODCON1&=0xFE;EA=BIT_TMP

/**** EIP2  ACH  PAGE 0 ****/
#define set_EIP2_RTC                     SFRS=0;EIP2|=0x80
#define set_EIP2_PDMA3                   SFRS=0;EIP2|=0x40
#define set_EIP2_PDMA2                   SFRS=0;EIP2|=0x20
#define set_EIP2_SMC1                    SFRS=0;EIP2|=0x10
#define set_EIP2_TK                      SFRS=0;EIP2|=0x08
#define set_EIP2_PPWM1                   SFRS=0;EIP2|=0x04
#define set_EIP2_PI2C1                   SFRS=0;EIP2|=0x02
#define set_EIP2_PACMP                   SFRS=0;EIP2|=0x01

#define clr_EIP2_RTC                     SFRS=0;EIP2&=0x7F
#define clr_EIP2_PDMA3                   SFRS=0;EIP2&=0xBF
#define clr_EIP2_PDMA2                   SFRS=0;EIP2&=0xDF
#define clr_EIP2_SMC1                    SFRS=0;EIP2&=0xEF
#define clr_EIP2_TK                      SFRS=0;EIP2&=0xF7
#define clr_EIP2_PPWM1                   SFRS=0;EIP2&=0xFB
#define clr_EIP2_PI2C1                   SFRS=0;EIP2&=0xFD
#define clr_EIP2_PACMP                   SFRS=0;EIP2&=0xFE

/**** EIPH2  ADH  PAGE 0 ****/
#define set_EIPH2_RTCH                   SFRS=0;EIPH2|=0x80
#define set_EIPH2_PDMA3H                 SFRS=0;EIPH2|=0x40
#define set_EIPH2_PDMA2H                 SFRS=0;EIPH2|=0x20
#define set_EIPH2_SMC1H                  SFRS=0;EIPH2|=0x10
#define set_EIPH2_TKH                    SFRS=0;EIPH2|=0x08
#define set_EIPH2_PPWM1H                 SFRS=0;EIPH2|=0x04
#define set_EIPH2_PI2C1H                 SFRS=0;EIPH2|=0x02
#define set_EIPH2_PACMPH                 SFRS=0;EIPH2|=0x01

#define clr_EIPH2_RTCH                   SFRS=0;EIPH2&=0x7F
#define clr_EIPH2_PDMA3H                 SFRS=0;EIPH2&=0xBF
#define clr_EIPH2_PDMA2H                 SFRS=0;EIPH2&=0xDF
#define clr_EIPH2_SMC1H                  SFRS=0;EIPH2&=0xEF
#define clr_EIPH2_TKH                    SFRS=0;EIPH2&=0xF7
#define clr_EIPH2_PPWM1H                 SFRS=0;EIPH2&=0xFB
#define clr_EIPH2_PI2C1H                 SFRS=0;EIPH2&=0xFD
#define clr_EIPH2_PACMPH                 SFRS=0;EIPH2&=0xFE

/**** IAPCN  AFH  PAGE 0 ****/
#define set_IAPCN_IAPA_17                SFRS=0;IAPCN|=0x80
#define set_IAPCN_IAPA_16                SFRS=0;IAPCN|=0x40
#define set_IAPCN_FOEN                   SFRS=0;IAPCN|=0x20
#define set_IAPCN_FCEN                   SFRS=0;IAPCN|=0x10
#define set_IAPCN_FCTRL_3                SFRS=0;IAPCN|=0x08
#define set_IAPCN_FCTRL_2                SFRS=0;IAPCN|=0x04
#define set_IAPCN_FCTRL_1                SFRS=0;IAPCN|=0x02
#define set_IAPCN_FCTRL_0                SFRS=0;IAPCN|=0x01

#define clr_IAPCN_IAPA_17                SFRS=0;IAPCN&=0x7F
#define clr_IAPCN_IAPA_16                SFRS=0;IAPCN&=0xBF
#define clr_IAPCN_FOEN                   SFRS=0;IAPCN&=0xDF
#define clr_IAPCN_FCEN                   SFRS=0;IAPCN&=0xEF
#define clr_IAPCN_FCTRL_3                SFRS=0;IAPCN&=0xF7
#define clr_IAPCN_FCTRL_2                SFRS=0;IAPCN&=0xFB
#define clr_IAPCN_FCTRL_1                SFRS=0;IAPCN&=0xFD
#define clr_IAPCN_FCTRL_0                SFRS=0;IAPCN&=0xFE

/**** P5  B1H  PAGE 0 ****/
#define set_P5_7                         SFRS=0;P5|=0x80
#define set_P5_6                         SFRS=0;P5|=0x40
#define set_P5_5                         SFRS=0;P5|=0x20
#define set_P5_4                         SFRS=0;P5|=0x10
#define set_P5_3                         SFRS=0;P5|=0x08
#define set_P5_2                         SFRS=0;P5|=0x04
#define set_P5_1                         SFRS=0;P5|=0x02
#define set_P5_0                         SFRS=0;P5|=0x01

#define clr_P5_7                         SFRS=0;P5&=0x7F
#define clr_P5_6                         SFRS=0;P5&=0xBF
#define clr_P5_5                         SFRS=0;P5&=0xDF
#define clr_P5_4                         SFRS=0;P5&=0xEF
#define clr_P5_3                         SFRS=0;P5&=0xF7
#define clr_P5_2                         SFRS=0;P5&=0xFB
#define clr_P5_1                         SFRS=0;P5&=0xFD
#define clr_P5_0                         SFRS=0;P5&=0xFE

/**** I2C1ADDR  B2H  PAGE 0 ****/
#define set_I2C1ADDR_GC                  SFRS=0;I2C1ADDR|=0x01
#define clr_I2C1ADDR_GC                  SFRS=0;I2C1ADDR&=0xFE

/**** I2C1STAT  B4H  PAGE 0 ****/

/**** I2C1TOC  B6H  PAGE 0 ****/
#define set_I2C1TOC_I2TOCEN              SFRS=0;I2C1TOC|=0x04
#define set_I2C1TOC_DIV                  SFRS=0;I2C1TOC|=0x02
#define set_I2C1TOC_I2TOF                SFRS=0;I2C1TOC|=0x01

#define clr_I2C1TOC_I2TOCEN              SFRS=0;I2C1TOC&=0xFB
#define clr_I2C1TOC_DIV                  SFRS=0;I2C1TOC&=0xFD
#define clr_I2C1TOC_I2TOF                SFRS=0;I2C1TOC&=0xFE

/**** IPH  B7H  PAGE 0 ****/
#define set_IPH_PADCH                    SFRS=0;IPH|=0x40
#define set_IPH_PBODH                    SFRS=0;IPH|=0x20
#define set_IPH_PSH                      SFRS=0;IPH|=0x10
#define set_IPH_PT1H                     SFRS=0;IPH|=0x08
#define set_IPH_PX1H                     SFRS=0;IPH|=0x04
#define set_IPH_PT0H                     SFRS=0;IPH|=0x02
#define set_IPH_PX0H                     SFRS=0;IPH|=0x01

#define clr_IPH_PADCH                    SFRS=0;IPH&=0xBF
#define clr_IPH_PBODH                    SFRS=0;IPH&=0xDF
#define clr_IPH_PSH                      SFRS=0;IPH&=0xEF
#define clr_IPH_PT1H                     SFRS=0;IPH&=0xF7
#define clr_IPH_PX1H                     SFRS=0;IPH&=0xFB
#define clr_IPH_PT0H                     SFRS=0;IPH&=0xFD
#define clr_IPH_PX0H                     SFRS=0;IPH&=0xFE

/**** I2C0STAT  BDH  PAGE 0 ****/
/**** I2C0TOC  BFH  PAGE 0 ****/
#define set_I2C0TOC_I2TOCEN              SFRS=0;I2C0TOC|=0x04
#define set_I2C0TOC_DIV                  SFRS=0;I2C0TOC|=0x02
#define set_I2C0TOC_I2TOF                SFRS=0;I2C0TOC|=0x01

#define clr_I2C0TOC_I2TOCEN              SFRS=0;I2C0TOC&=0xFB
#define clr_I2C0TOC_DIV                  SFRS=0;I2C0TOC&=0xFD
#define clr_I2C0TOC_I2TOF                SFRS=0;I2C0TOC&=0xFE

/**** I2ADDR  C1H  PAGE 0 ****/
#define set_I2ADDR_I2ADDR                SFRS=0;I2ADDR|=0x80
#define set_I2ADDR_GC                    SFRS=0;I2ADDR|=0x01

#define clr_I2ADDR_I2ADDR                SFRS=0;I2ADDR&=0x7F
#define clr_I2ADDR_GC                    SFRS=0;I2ADDR&=0xFE

/**** ADCRL  C2H  PAGE 0 ****/
#define set_ADCRL_ADCR_3                 SFRS=0;ADCRL|=0x08
#define set_ADCRL_ADCR_2                 SFRS=0;ADCRL|=0x04
#define set_ADCRL_ADCR_1                 SFRS=0;ADCRL|=0x02
#define set_ADCRL_ADCR_0                 SFRS=0;ADCRL|=0x01

#define clr_ADCRL_ADCR_3                 SFRS=0;ADCRL&=0xF7
#define clr_ADCRL_ADCR_2                 SFRS=0;ADCRL&=0xFB
#define clr_ADCRL_ADCR_1                 SFRS=0;ADCRL&=0xFD
#define clr_ADCRL_ADCR_0                 SFRS=0;ADCRL&=0xFE

/**** T3CON  C4H  PAGE 0 ****/
#define set_T3CON_SMOD_1                 SFRS=0;T3CON|=0x80
#define set_T3CON_SMOD0_1                SFRS=0;T3CON|=0x40
#define set_T3CON_BRCK                   SFRS=0;T3CON|=0x20
#define set_T3CON_TF3                    SFRS=0;T3CON|=0x10
#define set_T3CON_TR3                    SFRS=0;T3CON|=0x08
#define set_T3CON_T3PS_2                 SFRS=0;T3CON|=0x04
#define set_T3CON_T3PS_1                 SFRS=0;T3CON|=0x02
#define set_T3CON_T3PS_0                 SFRS=0;T3CON|=0x01

#define clr_T3CON_SMOD_1                 SFRS=0;T3CON&=0x7F
#define clr_T3CON_SMOD0_1                SFRS=0;T3CON&=0xBF
#define clr_T3CON_BRCK                   SFRS=0;T3CON&=0xDF
#define clr_T3CON_TF3                    SFRS=0;T3CON&=0xEF
#define clr_T3CON_TR3                    SFRS=0;T3CON&=0xF7
#define clr_T3CON_T3PS_2                 SFRS=0;T3CON&=0xFB
#define clr_T3CON_T3PS_1                 SFRS=0;T3CON&=0xFD
#define clr_T3CON_T3PS_0                 SFRS=0;T3CON&=0xFE

/**** T2MOD  C9H  PAGE 0 ****/
#define set_T2MOD_LDEN                   SFRS=0;T2MOD|=0x80
#define set_T2MOD_T2DIV_2                SFRS=0;T2MOD|=0x40
#define set_T2MOD_T2DIV_1                SFRS=0;T2MOD|=0x20
#define set_T2MOD_T2DIV_0                SFRS=0;T2MOD|=0x10
#define set_T2MOD_CAPCR                  SFRS=0;T2MOD|=0x08
#define set_T2MOD_CMPCR                  SFRS=0;T2MOD|=0x04
#define set_T2MOD_LDTS_1                 SFRS=0;T2MOD|=0x02
#define set_T2MOD_LDTS_0                 SFRS=0;T2MOD|=0x01

#define clr_T2MOD_LDEN                   SFRS=0;T2MOD&=0x7F
#define clr_T2MOD_T2DIV_2                SFRS=0;T2MOD&=0xBF
#define clr_T2MOD_T2DIV_1                SFRS=0;T2MOD&=0xDF
#define clr_T2MOD_T2DIV_0                SFRS=0;T2MOD&=0xEF
#define clr_T2MOD_CAPCR                  SFRS=0;T2MOD&=0xF7
#define clr_T2MOD_CMPCR                  SFRS=0;T2MOD&=0xFB
#define clr_T2MOD_LDTS_1                 SFRS=0;T2MOD&=0xFD
#define clr_T2MOD_LDTS_0                 SFRS=0;T2MOD&=0xFE

/**** PIF  CAH  PAGE 0 ****/
#define set_PIF_PIF7                     SFRS=0;PIF|=0x80
#define set_PIF_PIF6                     SFRS=0;PIF|=0x40
#define set_PIF_PIF5                     SFRS=0;PIF|=0x20
#define set_PIF_PIF4                     SFRS=0;PIF|=0x10
#define set_PIF_PIF3                     SFRS=0;PIF|=0x08
#define set_PIF_PIF2                     SFRS=0;PIF|=0x04
#define set_PIF_PIF1                     SFRS=0;PIF|=0x02
#define set_PIF_PIF0                     SFRS=0;PIF|=0x01

#define clr_PIF_PIF7                     SFRS=0;PIF&=0x7F
#define clr_PIF_PIF6                     SFRS=0;PIF&=0xBF
#define clr_PIF_PIF5                     SFRS=0;PIF&=0xDF
#define clr_PIF_PIF4                     SFRS=0;PIF&=0xEF
#define clr_PIF_PIF3                     SFRS=0;PIF&=0xF7
#define clr_PIF_PIF2                     SFRS=0;PIF&=0xFB
#define clr_PIF_PIF1                     SFRS=0;PIF&=0xFD
#define clr_PIF_PIF0                     SFRS=0;PIF&=0xFE

/**** PWM0CON0  D1H  PAGE 0 ****/
#define set_PWM0CON0_PWMRUN              SFRS=0;PWM0CON0|=0x80
#define set_PWM0CON0_LOAD                SFRS=0;PWM0CON0|=0x40
#define set_PWM0CON0_PWMF                SFRS=0;PWM0CON0|=0x20
#define set_PWM0CON0_CLRPWM              SFRS=0;PWM0CON0|=0x10

#define clr_PWM0CON0_PWMRUN              SFRS=0;PWM0CON0&=0x7F
#define clr_PWM0CON0_LOAD                SFRS=0;PWM0CON0&=0xBF
#define clr_PWM0CON0_PWMF                SFRS=0;PWM0CON0&=0xDF
#define clr_PWM0CON0_CLRPWM              SFRS=0;PWM0CON0&=0xEF

/**** ACMPCR0  D2H  PAGE 0 ****/
#define set_ACMPCR0_POSSEL_1             SFRS=0;ACMPCR0|=0x80
#define set_ACMPCR0_POSSEL_0             SFRS=0;ACMPCR0|=0x40
#define set_ACMPCR0_NEGSEL_1             SFRS=0;ACMPCR0|=0x20
#define set_ACMPCR0_NEGSEL_0             SFRS=0;ACMPCR0|=0x10
#define set_ACMPCR0_WKEN                 SFRS=0;ACMPCR0|=0x08
#define set_ACMPCR0_HYSEN                SFRS=0;ACMPCR0|=0x04
#define set_ACMPCR0_ACMPIE               SFRS=0;ACMPCR0|=0x02
#define set_ACMPCR0_ACMPEN               SFRS=0;ACMPCR0|=0x01

#define clr_ACMPCR0_POSSEL_1             SFRS=0;ACMPCR0&=0x7F
#define clr_ACMPCR0_POSSEL_0             SFRS=0;ACMPCR0&=0xBF
#define clr_ACMPCR0_NEGSEL_1             SFRS=0;ACMPCR0&=0xDF
#define clr_ACMPCR0_NEGSEL_0             SFRS=0;ACMPCR0&=0xEF
#define clr_ACMPCR0_WKEN                 SFRS=0;ACMPCR0&=0xF7
#define clr_ACMPCR0_HYSEN                SFRS=0;ACMPCR0&=0xFB
#define clr_ACMPCR0_ACMPIE               SFRS=0;ACMPCR0&=0xFD
#define clr_ACMPCR0_ACMPEN               SFRS=0;ACMPCR0&=0xFE

/**** ACMPCR1  D3H  PAGE 0 ****/
#define set_ACMPCR1_POSSEL_1             SFRS=0;ACMPCR1|=0x80
#define set_ACMPCR1_POSSEL_0             SFRS=0;ACMPCR1|=0x40
#define set_ACMPCR1_NEGSEL_1             SFRS=0;ACMPCR1|=0x20
#define set_ACMPCR1_NEGSEL_0             SFRS=0;ACMPCR1|=0x10
#define set_ACMPCR1_WKEN                 SFRS=0;ACMPCR1|=0x08
#define set_ACMPCR1_HYSEN                SFRS=0;ACMPCR1|=0x04
#define set_ACMPCR1_ACMPIE               SFRS=0;ACMPCR1|=0x02
#define set_ACMPCR1_ACMPEN               SFRS=0;ACMPCR1|=0x01

#define clr_ACMPCR1_POSSEL_1             SFRS=0;ACMPCR1&=0x7F
#define clr_ACMPCR1_POSSEL_0             SFRS=0;ACMPCR1&=0xBF
#define clr_ACMPCR1_NEGSEL_1             SFRS=0;ACMPCR1&=0xDF
#define clr_ACMPCR1_NEGSEL_0             SFRS=0;ACMPCR1&=0xEF
#define clr_ACMPCR1_WKEN                 SFRS=0;ACMPCR1&=0xF7
#define clr_ACMPCR1_HYSEN                SFRS=0;ACMPCR1&=0xFB
#define clr_ACMPCR1_ACMPIE               SFRS=0;ACMPCR1&=0xFD
#define clr_ACMPCR1_ACMPEN               SFRS=0;ACMPCR1&=0xFE

/**** ACMPSR  D4H  PAGE 0 ****/
#define set_ACMPSR_ACMP1O                SFRS=0;ACMPSR|=0x08
#define set_ACMPSR_ACMP1IF               SFRS=0;ACMPSR|=0x04
#define set_ACMPSR_ACMP0O                SFRS=0;ACMPSR|=0x02
#define set_ACMPSR_ACMP0IF               SFRS=0;ACMPSR|=0x01

#define clr_ACMPSR_ACMP1O                SFRS=0;ACMPSR&=0xF7
#define clr_ACMPSR_ACMP1IF               SFRS=0;ACMPSR&=0xFB
#define clr_ACMPSR_ACMP0O                SFRS=0;ACMPSR&=0xFD
#define clr_ACMPSR_ACMP0IF               SFRS=0;ACMPSR&=0xFE

/**** ACMPVREF  D5H  PAGE 0 ****/
#define set_ACMPVREF_AO1PIV              SFRS=0;ACMPVREF|=0x80
#define set_ACMPVREF_CRV1CTL_2           SFRS=0;ACMPVREF|=0x40
#define set_ACMPVREF_CRV1CTL__1          SFRS=0;ACMPVREF|=0x20
#define set_ACMPVREF_CRV1CTL_0           SFRS=0;ACMPVREF|=0x10
#define set_ACMPVREF_AO0PIV              SFRS=0;ACMPVREF|=0x08
#define set_ACMPVREF_CRV0CTL_2           SFRS=0;ACMPVREF|=0x04
#define set_ACMPVREF_CRV0CTL_1           SFRS=0;ACMPVREF|=0x02
#define set_ACMPVREF_CRV0CTL_0           SFRS=0;ACMPVREF|=0x01

#define clr_ACMPVREF_AO1PIV              SFRS=0;ACMPVREF&=0x7F
#define clr_ACMPVREF_CRV1CTL_2           SFRS=0;ACMPVREF&=0xBF
#define clr_ACMPVREF_CRV1CTL__1          SFRS=0;ACMPVREF&=0xDF
#define clr_ACMPVREF_CRV1CTL_0           SFRS=0;ACMPVREF&=0xEF
#define clr_ACMPVREF_AO0PIV              SFRS=0;ACMPVREF&=0xF7
#define clr_ACMPVREF_CRV0CTL_2           SFRS=0;ACMPVREF&=0xFB
#define clr_ACMPVREF_CRV0CTL_1           SFRS=0;ACMPVREF&=0xFD
#define clr_ACMPVREF_CRV0CTL_0           SFRS=0;ACMPVREF&=0xFE

/**** SC0CR0  D6H  PAGE 0 ****/
#define set_SC0CR0_NSB                   SFRS=0;SC0CR0|=0x80
#define set_SC0CR0_T                     SFRS=0;SC0CR0|=0x40
#define set_SC0CR0_RXBGTEN               SFRS=0;SC0CR0|=0x20
#define set_SC0CR0_CONSEL                SFRS=0;SC0CR0|=0x10
#define set_SC0CR0_AUTOCEN               SFRS=0;SC0CR0|=0x08
#define set_SC0CR0_TXOFF                 SFRS=0;SC0CR0|=0x04
#define set_SC0CR0_RXOFF                 SFRS=0;SC0CR0|=0x02
#define set_SC0CR0_SCEN                  SFRS=0;SC0CR0|=0x01

#define clr_SC0CR0_NSB                   SFRS=0;SC0CR0&=0x7F
#define clr_SC0CR0_T                     SFRS=0;SC0CR0&=0xBF
#define clr_SC0CR0_RXBGTEN               SFRS=0;SC0CR0&=0xDF
#define clr_SC0CR0_CONSEL                SFRS=0;SC0CR0&=0xEF
#define clr_SC0CR0_AUTOCEN               SFRS=0;SC0CR0&=0xF7
#define clr_SC0CR0_TXOFF                 SFRS=0;SC0CR0&=0xFB
#define clr_SC0CR0_RXOFF                 SFRS=0;SC0CR0&=0xFD
#define clr_SC0CR0_SCEN                  SFRS=0;SC0CR0&=0xFE

/**** SC0CR1  D7H  PAGE 0 ****/
#define set_SC0CR1_OPE                   SFRS=0;SC0CR1|=0x80
#define set_SC0CR1_PBOFF                 SFRS=0;SC0CR1|=0x40
#define set_SC0CR1_WLS1                  SFRS=0;SC0CR1|=0x20
#define set_SC0CR1_WLS0                  SFRS=0;SC0CR1|=0x10
#define set_SC0CR1_TXDMAEN               SFRS=0;SC0CR1|=0x08
#define set_SC0CR1_RXDMAEN               SFRS=0;SC0CR1|=0x04
#define set_SC0CR1_CLKKEEP               SFRS=0;SC0CR1|=0x02
#define set_SC0CR1_UARTEN                SFRS=0;SC0CR1|=0x01

#define clr_SC0CR1_OPE                   SFRS=0;SC0CR1&=0x7F
#define clr_SC0CR1_PBOFF                 SFRS=0;SC0CR1&=0xBF
#define clr_SC0CR1_WLS1                  SFRS=0;SC0CR1&=0xDF
#define clr_SC0CR1_WLS0                  SFRS=0;SC0CR1&=0xEF
#define clr_SC0CR1_TXDMAEN               SFRS=0;SC0CR1&=0xF7
#define clr_SC0CR1_RXDMAEN               SFRS=0;SC0CR1&=0xFB
#define clr_SC0CR1_CLKKEEP               SFRS=0;SC0CR1&=0xFD
#define clr_SC0CR1_UARTEN                SFRS=0;SC0CR1&=0xFE

/**** SC0ETURD1  DCH  PAGE 0 ****/
#define set_SC0ETURD1_SCDIV_2            SFRS=0;SC0ETURD1|=0x40
#define set_SC0ETURD1_SCDIV_1            SFRS=0;SC0ETURD1|=0x20
#define set_SC0ETURD1_SCDIV_0            SFRS=0;SC0ETURD1|=0x10
#define set_SC0ETURD1_ETURDIV_11         SFRS=0;SC0ETURD1|=0x08
#define set_SC0ETURD1_ETURDIV_10         SFRS=0;SC0ETURD1|=0x04
#define set_SC0ETURD1_ETURDIV_9          SFRS=0;SC0ETURD1|=0x02
#define set_SC0ETURD1_ETURDIV_8          SFRS=0;SC0ETURD1|=0x01

#define clr_SC0ETURD1_SCDIV_2            SFRS=0;SC0ETURD1&=0xBF
#define clr_SC0ETURD1_SCDIV_1            SFRS=0;SC0ETURD1&=0xDF
#define clr_SC0ETURD1_SCDIV_0            SFRS=0;SC0ETURD1&=0xEF
#define clr_SC0ETURD1_ETURDIV_11         SFRS=0;SC0ETURD1&=0xF7
#define clr_SC0ETURD1_ETURDIV_10         SFRS=0;SC0ETURD1&=0xFB
#define clr_SC0ETURD1_ETURDIV_9          SFRS=0;SC0ETURD1&=0xFD
#define clr_SC0ETURD1_ETURDIV_8          SFRS=0;SC0ETURD1&=0xFE

/**** SC0IE  DDH  PAGE 0 ****/
#define set_SC0IE_ACERRIEN               SFRS=0;SC0IE|=0x10
#define set_SC0IE_BGTIEN                 SFRS=0;SC0IE|=0x08
#define set_SC0IE_TERRIEN                SFRS=0;SC0IE|=0x04
#define set_SC0IE_TBEIEN                 SFRS=0;SC0IE|=0x02
#define set_SC0IE_RDAIEN                 SFRS=0;SC0IE|=0x01

#define clr_SC0IE_ACERRIEN               SFRS=0;SC0IE&=0xEF
#define clr_SC0IE_BGTIEN                 SFRS=0;SC0IE&=0xF7
#define clr_SC0IE_TERRIEN                SFRS=0;SC0IE&=0xFB
#define clr_SC0IE_TBEIEN                 SFRS=0;SC0IE&=0xFD
#define clr_SC0IE_RDAIEN                 SFRS=0;SC0IE&=0xFE

/**** SC0IS  DEH  PAGE 0 ****/
#define set_SC0IS_TXERF                  SFRS=0;SC0IS|=0x20
#define set_SC0IS_ACERRIF                SFRS=0;SC0IS|=0x10
#define set_SC0IS_BGTIF                  SFRS=0;SC0IS|=0x08
#define set_SC0IS_TERRIF                 SFRS=0;SC0IS|=0x04
#define set_SC0IS_TBEIF                  SFRS=0;SC0IS|=0x02
#define set_SC0IS_RDAIF                  SFRS=0;SC0IS|=0x01

#define clr_SC0IS_Tx_Er                  SFRS=0;SC0IS&=0xDF
#define clr_SC0IS_ACERRIF                SFRS=0;SC0IS&=0xEF
#define clr_SC0IS_BGTIF                  SFRS=0;SC0IS&=0xF7
#define clr_SC0IS_TERRIF                 SFRS=0;SC0IS&=0xFB
#define clr_SC0IS_TBEIF                  SFRS=0;SC0IS&=0xFD
#define clr_SC0IS_RDAIF                  SFRS=0;SC0IS&=0xFE

/**** SC0TSR  DFH  PAGE 0 ****/
#define set_SC0TSR_ACT                   SFRS=0;SC0TSR|=0x80
#define set_SC0TSR_BEF                   SFRS=0;SC0TSR|=0x40
#define set_SC0TSR_FEF                   SFRS=0;SC0TSR|=0x20
#define set_SC0TSR_PEF                   SFRS=0;SC0TSR|=0x10
#define set_SC0TSR_TXEMPTY               SFRS=0;SC0TSR|=0x08
#define set_SC0TSR_TXOV                  SFRS=0;SC0TSR|=0x04
#define set_SC0TSR_RXEMPTY               SFRS=0;SC0TSR|=0x02
#define set_SC0TSR_RXOV                  SFRS=0;SC0TSR|=0x01

#define clr_SC0TSR_ACT                   SFRS=0;SC0TSR&=0x7F
#define clr_SC0TSR_BEF                   SFRS=0;SC0TSR&=0xBF
#define clr_SC0TSR_FEF                   SFRS=0;SC0TSR&=0xDF
#define clr_SC0TSR_PEF                   SFRS=0;SC0TSR&=0xEF
#define clr_SC0TSR_TXEMPTY               SFRS=0;SC0TSR&=0xF7
#define clr_SC0TSR_TXOV                  SFRS=0;SC0TSR&=0xFB
#define clr_SC0TSR_RXEMPTY               SFRS=0;SC0TSR&=0xFD
#define clr_SC0TSR_RXOV                  SFRS=0;SC0TSR&=0xFE

/**** ADCCON1  E1H  PAGE 0 ****/
#define set_ADCCON1_HIE                  SFRS=0;ADCCON1|=0x20
#define set_ADCCON1_CONT                 SFRS=0;ADCCON1|=0x10
#define set_ADCCON1_ETGTYP_1             SFRS=0;ADCCON1|=0x08
#define set_ADCCON1_ETGTYP_0             SFRS=0;ADCCON1|=0x04
#define set_ADCCON1_ADCEX                SFRS=0;ADCCON1|=0x02
#define set_ADCCON1_ADCEN                SFRS=0;ADCCON1|=0x01

#define clr_ADCCON1_HIE                  SFRS=0;ADCCON1&=0xDF
#define clr_ADCCON1_CONT                 SFRS=0;ADCCON1&=0xEF
#define clr_ADCCON1_ETGTYP_1             SFRS=0;ADCCON1&=0xF7
#define clr_ADCCON1_ETGTYP_0             SFRS=0;ADCCON1&=0xFB
#define clr_ADCCON1_ADCEX                SFRS=0;ADCCON1&=0xFD
#define clr_ADCCON1_ADCEN                SFRS=0;ADCCON1&=0xFE

/**** ADCCON2  E2H  PAGE 0 ****/
#define set_ADCCON2_ADFBEN               SFRS=0;ADCCON2|=0x80
#define set_ADCCON2_ADCMPOP              SFRS=0;ADCCON2|=0x40
#define set_ADCCON2_ADCMPEN              SFRS=0;ADCCON2|=0x20
#define set_ADCCON2_ADCMPO               SFRS=0;ADCCON2|=0x10
#define set_ADCCON2_ADCAQT_2             SFRS=0;ADCCON2|=0x08
#define set_ADCCON2_ADCAQT_1             SFRS=0;ADCCON2|=0x04
#define set_ADCCON2_ADCAQT_0             SFRS=0;ADCCON2|=0x02
#define set_ADCCON2_ADCDLY_8             SFRS=0;ADCCON2|=0x01

#define clr_ADCCON2_ADFBEN               SFRS=0;ADCCON2&=0x7F
#define clr_ADCCON2_ADCMPOP              SFRS=0;ADCCON2&=0xBF
#define clr_ADCCON2_ADCMPEN              SFRS=0;ADCCON2&=0xDF
#define clr_ADCCON2_ADCMPO               SFRS=0;ADCCON2&=0xEF
#define clr_ADCCON2_ADCAQT_2             SFRS=0;ADCCON2&=0xF7
#define clr_ADCCON2_ADCAQT_1             SFRS=0;ADCCON2&=0xFB
#define clr_ADCCON2_ADCAQT_0             SFRS=0;ADCCON2&=0xFD
#define clr_ADCCON2_ADCDLY_8             SFRS=0;ADCCON2&=0xFE

/**** ADCBAH  E4H  PAGE 0 ****/
#define set_ADCBAH_ADCBAH_3              SFRS=0;ADCBAH|=0x08
#define set_ADCBAH_ADCBAH_2              SFRS=0;ADCBAH|=0x04
#define set_ADCBAH_ADCBAH_1              SFRS=0;ADCBAH|=0x02
#define set_ADCBAH_ADCBAH_0              SFRS=0;ADCBAH|=0x01

#define clr_ADCBAH_ADCBAH_3              SFRS=0;ADCBAH&=0xF7
#define clr_ADCBAH_ADCBAH_2              SFRS=0;ADCBAH&=0xFB
#define clr_ADCBAH_ADCBAH_1              SFRS=0;ADCBAH&=0xFD
#define clr_ADCBAH_ADCBAH_0              SFRS=0;ADCBAH&=0xFE

/**** ADCSR  E7H  PAGE 0 ****/
#define set_ADCSR_SLOW                   SFRS=0;ADCSR|=0x80
#define set_ADCSR_ADCDIV_2               SFRS=0;ADCSR|=0x40
#define set_ADCSR_ADCDIV_1               SFRS=0;ADCSR|=0x20
#define set_ADCSR_ADCDIV_0               SFRS=0;ADCSR|=0x10
#define set_ADCSR_CMPHIT                 SFRS=0;ADCSR|=0x04
#define set_ADCSR_HDONE                  SFRS=0;ADCSR|=0x02
#define set_ADCSR_FDONE                  SFRS=0;ADCSR|=0x01

#define clr_ADCSR_SLOW                   SFRS=0;ADCSR&=0x7F
#define clr_ADCSR_ADCDIV_2               SFRS=0;ADCSR&=0xBF
#define clr_ADCSR_ADCDIV_1               SFRS=0;ADCSR&=0xDF
#define clr_ADCSR_ADCDIV_0               SFRS=0;ADCSR&=0xEF
#define clr_ADCSR_CMPHIT                 SFRS=0;ADCSR&=0xFB
#define clr_ADCSR_HDONE                  SFRS=0;ADCSR&=0xFD
#define clr_ADCSR_FDONE                  SFRS=0;ADCSR&=0xFE

/**** DMA0TSR  E9H  PAGE 0 ****/
#define set_DMA0TSR_ACT                  SFRS=0;DMA0TSR|=0x04
#define set_DMA0TSR_HDONE                SFRS=0;DMA0TSR|=0x02
#define set_DMA0TSR_FDONE                SFRS=0;DMA0TSR|=0x01

#define clr_DMA0TSR_ACT                  SFRS=0;DMA0TSR&=0xFB
#define clr_DMA0TSR_HDONE                SFRS=0;DMA0TSR&=0xFD
#define clr_DMA0TSR_FDONE                SFRS=0;DMA0TSR&=0xFE

/**** EIP0  EFH  PAGE 0 ****/
#define set_EIP0_PT2                     SFRS=0;EIP0|=0x80
#define set_EIP0_PSPI                    SFRS=0;EIP0|=0x40
#define set_EIP0_PFB                     SFRS=0;EIP0|=0x20
#define set_EIP0_PWDT                    SFRS=0;EIP0|=0x10
#define set_EIP0_PPWM                    SFRS=0;EIP0|=0x08
#define set_EIP0_PCAP                    SFRS=0;EIP0|=0x04
#define set_EIP0_PPI                     SFRS=0;EIP0|=0x02
#define set_EIP0_PI2C                    SFRS=0;EIP0|=0x01

#define clr_EIP0_PT2                     SFRS=0;EIP0&=0x7F
#define clr_EIP0_PSPI                    SFRS=0;EIP0&=0xBF
#define clr_EIP0_PFB                     SFRS=0;EIP0&=0xDF
#define clr_EIP0_PWDT                    SFRS=0;EIP0&=0xEF
#define clr_EIP0_PPWM                    SFRS=0;EIP0&=0xF7
#define clr_EIP0_PCAP                    SFRS=0;EIP0&=0xFB
#define clr_EIP0_PPI                     SFRS=0;EIP0&=0xFD
#define clr_EIP0_PI2C                    SFRS=0;EIP0&=0xFE

/**** DMA1TSR  F1H  PAGE 0 ****/
#define set_DMA1TSR_ACT                  SFRS=0;DMA1TSR|=0x04
#define set_DMA1TSR_HDONE                SFRS=0;DMA1TSR|=0x02
#define set_DMA1TSR_FDONE                SFRS=0;DMA1TSR|=0x01

#define clr_DMA1TSR_ACT                  SFRS=0;DMA1TSR&=0xFB
#define clr_DMA1TSR_HDONE                SFRS=0;DMA1TSR&=0xFD
#define clr_DMA1TSR_FDONE                SFRS=0;DMA1TSR&=0xFE

/**** SPI0CR0  F3H  PAGE 0 ****/
#define set_SPI0CR0_SSOE                 SFRS=0;SPI0CR0|=0x80
#define set_SPI0CR0_SPIEN                SFRS=0;SPI0CR0|=0x40
#define set_SPI0CR0_LSBFE                SFRS=0;SPI0CR0|=0x20
#define set_SPI0CR0_MSTR                 SFRS=0;SPI0CR0|=0x10
#define set_SPI0CR0_CPOL                 SFRS=0;SPI0CR0|=0x08
#define set_SPI0CR0_CPHA                 SFRS=0;SPI0CR0|=0x04
#define set_SPI0CR0_SPR1                 SFRS=0;SPI0CR0|=0x02
#define set_SPI0CR0_SPR0                 SFRS=0;SPI0CR0|=0x01

#define clr_SPI0CR0_SSOE                 SFRS=0;SPI0CR0&=0x7F
#define clr_SPI0CR0_SPIEN                SFRS=0;SPI0CR0&=0xBF
#define clr_SPI0CR0_LSBFE                SFRS=0;SPI0CR0&=0xDF
#define clr_SPI0CR0_MSTR                 SFRS=0;SPI0CR0&=0xEF
#define clr_SPI0CR0_CPOL                 SFRS=0;SPI0CR0&=0xF7
#define clr_SPI0CR0_CPHA                 SFRS=0;SPI0CR0&=0xFB
#define clr_SPI0CR0_SPR1                 SFRS=0;SPI0CR0&=0xFD
#define clr_SPI0CR0_SPR0                 SFRS=0;SPI0CR0&=0xFE

/**** SPI0SR  F4H  PAGE 0 ****/
#define set_SPI0SR_SPIF                  SFRS=0;SPI0SR|=0x80
#define set_SPI0SR_WCOL                  SFRS=0;SPI0SR|=0x40
#define set_SPI0SR_SPIOVF                SFRS=0;SPI0SR|=0x20
#define set_SPI0SR_MODF                  SFRS=0;SPI0SR|=0x10
#define set_SPI0SR_DISMODF               SFRS=0;SPI0SR|=0x08
#define set_SPI0SR_DISSPIF               SFRS=0;SPI0SR|=0x04
#define set_SPI0SR_TXBFF                 SFRS=0;SPI0SR|=0x02

#define clr_SPI0SR_SPIF                  SFRS=0;SPI0SR&=0x7F
#define clr_SPI0SR_WCOL                  SFRS=0;SPI0SR&=0xBF
#define clr_SPI0SR_SPIOVF                SFRS=0;SPI0SR&=0xDF
#define clr_SPI0SR_MODF                  SFRS=0;SPI0SR&=0xEF
#define clr_SPI0SR_DISMODF               SFRS=0;SPI0SR&=0xF7
#define clr_SPI0SR_DISSPIF               SFRS=0;SPI0SR&=0xFB
#define clr_SPI0SR_TXBFF                 SFRS=0;SPI0SR&=0xFD

/**** DMA0BAH  F6H  PAGE 0 ****/
#define set_DMA0BAH_XRAMA[7:4]           SFRS=0;DMA0BAH|=0x40
#define set_DMA0BAH_00000000b            SFRS=0;DMA0BAH|=0x20

#define clr_DMA0BAH_XRAMA[7:4]           SFRS=0;DMA0BAH&=0xBF
#define clr_DMA0BAH_00000000b            SFRS=0;DMA0BAH&=0xDF

/**** EIPH0  F7H  PAGE 0 ****/
#define set_EIPH0_PT2H                   SFRS=0;EIPH0|=0x80
#define set_EIPH0_PSPIH                  SFRS=0;EIPH0|=0x40
#define set_EIPH0_PFBH                   SFRS=0;EIPH0|=0x20
#define set_EIPH0_PWDTH                  SFRS=0;EIPH0|=0x10
#define set_EIPH0_PPWMH                  SFRS=0;EIPH0|=0x08
#define set_EIPH0_PCAPH                  SFRS=0;EIPH0|=0x04
#define set_EIPH0_PPIH                   SFRS=0;EIPH0|=0x02
#define set_EIPH0_PI2CH                  SFRS=0;EIPH0|=0x01

#define clr_EIPH0_PT2H                   SFRS=0;EIPH0&=0x7F
#define clr_EIPH0_PSPIH                  SFRS=0;EIPH0&=0xBF
#define clr_EIPH0_PFBH                   SFRS=0;EIPH0&=0xDF
#define clr_EIPH0_PWDTH                  SFRS=0;EIPH0&=0xEF
#define clr_EIPH0_PPWMH                  SFRS=0;EIPH0&=0xF7
#define clr_EIPH0_PCAPH                  SFRS=0;EIPH0&=0xFB
#define clr_EIPH0_PPIH                   SFRS=0;EIPH0&=0xFD
#define clr_EIPH0_PI2CH                  SFRS=0;EIPH0&=0xFE

/**** SPI1CR0  F9H  PAGE 0 ****/
#define set_SPI1CR0_SSOE                 SFRS=0;SPI1CR0|=0x80
#define set_SPI1CR0_SPIEN                SFRS=0;SPI1CR0|=0x40
#define set_SPI1CR0_LSBFE                SFRS=0;SPI1CR0|=0x20
#define set_SPI1CR0_MSTR                 SFRS=0;SPI1CR0|=0x10
#define set_SPI1CR0_CPOL                 SFRS=0;SPI1CR0|=0x08
#define set_SPI1CR0_CPHA                 SFRS=0;SPI1CR0|=0x04
#define set_SPI1CR0_SPR1                 SFRS=0;SPI1CR0|=0x02
#define set_SPI1CR0_SPR0                 SFRS=0;SPI1CR0|=0x01

#define clr_SPI1CR0_SSOE                 SFRS=0;SPI1CR0&=0x7F
#define clr_SPI1CR0_SPIEN                SFRS=0;SPI1CR0&=0xBF
#define clr_SPI1CR0_LSBFE                SFRS=0;SPI1CR0&=0xDF
#define clr_SPI1CR0_MSTR                 SFRS=0;SPI1CR0&=0xEF
#define clr_SPI1CR0_CPOL                 SFRS=0;SPI1CR0&=0xF7
#define clr_SPI1CR0_CPHA                 SFRS=0;SPI1CR0&=0xFB
#define clr_SPI1CR0_SPR1                 SFRS=0;SPI1CR0&=0xFD
#define clr_SPI1CR0_SPR0                 SFRS=0;SPI1CR0&=0xFE

/**** SPI1CR1  FAH  PAGE 0 ****/
#define set_SPI1CR1_SPR3                 SFRS=0;SPI1CR1|=0x20
#define set_SPI1CR1_SPR2                 SFRS=0;SPI1CR1|=0x10
#define set_SPI1CR1_TXDMAEN              SFRS=0;SPI1CR1|=0x08
#define set_SPI1CR1_RXDMAEN              SFRS=0;SPI1CR1|=0x04
#define set_SPI1CR1_SPIS1                SFRS=0;SPI1CR1|=0x02
#define set_SPI1CR1_SPIS0                SFRS=0;SPI1CR1|=0x01

#define clr_SPI1CR1_SPR3                 SFRS=0;SPI1CR1&=0xDF
#define clr_SPI1CR1_SPR2                 SFRS=0;SPI1CR1&=0xEF
#define clr_SPI1CR1_TXDMAEN              SFRS=0;SPI1CR1&=0xF7
#define clr_SPI1CR1_RXDMAEN              SFRS=0;SPI1CR1&=0xFB
#define clr_SPI1CR1_SPIS1                SFRS=0;SPI1CR1&=0xFD
#define clr_SPI1CR1_SPIS0                SFRS=0;SPI1CR1&=0xFE

/**** SPI1SR  FBH  PAGE 0 ****/
#define set_SPI1SR_SPIF                  SFRS=0;SPI1SR|=0x80
#define set_SPI1SR_WCOL                  SFRS=0;SPI1SR|=0x40
#define set_SPI1SR_SPIOVF                SFRS=0;SPI1SR|=0x20
#define set_SPI1SR_MODF                  SFRS=0;SPI1SR|=0x10
#define set_SPI1SR_DISMODF               SFRS=0;SPI1SR|=0x08
#define set_SPI1SR_DISSPIF               SFRS=0;SPI1SR|=0x04
#define set_SPI1SR_TXBFF                 SFRS=0;SPI1SR|=0x02

#define clr_SPI1SR_SPIF                  SFRS=0;SPI1SR&=0x7F
#define clr_SPI1SR_WCOL                  SFRS=0;SPI1SR&=0xBF
#define clr_SPI1SR_SPIOVF                SFRS=0;SPI1SR&=0xDF
#define clr_SPI1SR_MODF                  SFRS=0;SPI1SR&=0xEF
#define clr_SPI1SR_DISMODF               SFRS=0;SPI1SR&=0xF7
#define clr_SPI1SR_DISSPIF               SFRS=0;SPI1SR&=0xFB
#define clr_SPI1SR_TXBFF                 SFRS=0;SPI1SR&=0xFD

/**** DMA1BAH  FDH  PAGE 0 ****/
/**** EIP1  FEH  PAGE 0 ****/
#define set_EIP1_PSPI1                   SFRS=0;EIP1|=0x80
#define set_EIP1_PDMA1                   SFRS=0;EIP1|=0x40
#define set_EIP1_PDMA0                   SFRS=0;EIP1|=0x20
#define set_EIP1_PSMC                    SFRS=0;EIP1|=0x10
#define set_EIP1_PHF                     SFRS=0;EIP1|=0x08
#define set_EIP1_PWKT                    SFRS=0;EIP1|=0x04
#define set_EIP1_PT3                     SFRS=0;EIP1|=0x02
#define set_EIP1_PS_1                    SFRS=0;EIP1|=0x01

#define clr_EIP1_PSPI1                   SFRS=0;EIP1&=0x7F
#define clr_EIP1_PDMA1                   SFRS=0;EIP1&=0xBF
#define clr_EIP1_PDMA0                   SFRS=0;EIP1&=0xDF
#define clr_EIP1_PSMC                    SFRS=0;EIP1&=0xEF
#define clr_EIP1_PHF                     SFRS=0;EIP1&=0xF7
#define clr_EIP1_PWKT                    SFRS=0;EIP1&=0xFB
#define clr_EIP1_PT3                     SFRS=0;EIP1&=0xFD
#define clr_EIP1_PS_1                    SFRS=0;EIP1&=0xFE

/**** EIPH1  FFH  PAGE 0 ****/
#define set_EIPH1_PSPI1H                 SFRS=0;EIPH1|=0x80
#define set_EIPH1_PDMA1H                 SFRS=0;EIPH1|=0x40
#define set_EIPH1_PDMA0H                 SFRS=0;EIPH1|=0x20
#define set_EIPH1_PSMCH                  SFRS=0;EIPH1|=0x10
#define set_EIPH1_PHFH                   SFRS=0;EIPH1|=0x08
#define set_EIPH1_PWKTH                  SFRS=0;EIPH1|=0x04
#define set_EIPH1_PT3H                   SFRS=0;EIPH1|=0x02
#define set_EIPH1_PSH_1                  SFRS=0;EIPH1|=0x01

#define clr_EIPH1_PSPI1H                 SFRS=0;EIPH1&=0x7F
#define clr_EIPH1_PDMA1H                 SFRS=0;EIPH1&=0xBF
#define clr_EIPH1_PDMA0H                 SFRS=0;EIPH1&=0xDF
#define clr_EIPH1_PSMCH                  SFRS=0;EIPH1&=0xEF
#define clr_EIPH1_PHFH                   SFRS=0;EIPH1&=0xF7
#define clr_EIPH1_PWKTH                  SFRS=0;EIPH1&=0xFB
#define clr_EIPH1_PT3H                   SFRS=0;EIPH1&=0xFD
#define clr_EIPH1_PSH_1                  SFRS=0;EIPH1&=0xFE

/**** EIPH1  FFH  PAGE 0 ****/
#define set_EIPH1_7                      SFRS=0;EIPH1|=0x80
#define set_EIPH1_6                      SFRS=0;EIPH1|=0x40
#define set_EIPH1_5                      SFRS=0;EIPH1|=0x20
#define set_EIPH1_4                      SFRS=0;EIPH1|=0x10
#define set_EIPH1_3                      SFRS=0;EIPH1|=0x08
#define set_EIPH1_2                      SFRS=0;EIPH1|=0x04
#define set_EIPH1_1                      SFRS=0;EIPH1|=0x02
#define set_EIPH1_0                      SFRS=0;EIPH1|=0x01

#define clr_EIPH1_7                      SFRS=0;EIPH1&=0x7F
#define clr_EIPH1_6                      SFRS=0;EIPH1&=0xBF
#define clr_EIPH1_5                      SFRS=0;EIPH1&=0xDF
#define clr_EIPH1_4                      SFRS=0;EIPH1&=0xEF
#define clr_EIPH1_3                      SFRS=0;EIPH1&=0xF7
#define clr_EIPH1_2                      SFRS=0;EIPH1&=0xFB
#define clr_EIPH1_1                      SFRS=0;EIPH1&=0xFD
#define clr_EIPH1_0                      SFRS=0;EIPH1&=0xFE

/********SFR PAGE 1*************/
/**** P1DW  8BH  PAGE 1 ****/
#define set_P1DW_7                       SFRS=1;P1DW|=0x80
#define set_P1DW_6                       SFRS=1;P1DW|=0x40
#define set_P1DW_5                       SFRS=1;P1DW|=0x20
#define set_P1DW_4                       SFRS=1;P1DW|=0x10
#define set_P1DW_3                       SFRS=1;P1DW|=0x08
#define set_P1DW_2                       SFRS=1;P1DW|=0x04
#define set_P1DW_1                       SFRS=1;P1DW|=0x02
#define set_P1DW_0                       SFRS=1;P1DW|=0x01

#define clr_P1DW_7                       SFRS=1;P1DW&=0x7F
#define clr_P1DW_6                       SFRS=1;P1DW&=0xBF
#define clr_P1DW_5                       SFRS=1;P1DW&=0xDF
#define clr_P1DW_4                       SFRS=1;P1DW&=0xEF
#define clr_P1DW_3                       SFRS=1;P1DW&=0xF7
#define clr_P1DW_2                       SFRS=1;P1DW&=0xFB
#define clr_P1DW_1                       SFRS=1;P1DW&=0xFD
#define clr_P1DW_0                       SFRS=1;P1DW&=0xFE

/**** P2DW  8CH  PAGE 1 ****/
#define set_P2DW_7                       SFRS=1;P2DW|=0x80
#define set_P2DW_6                       SFRS=1;P2DW|=0x40
#define set_P2DW_5                       SFRS=1;P2DW|=0x20
#define set_P2DW_4                       SFRS=1;P2DW|=0x10
#define set_P2DW_3                       SFRS=1;P2DW|=0x08
#define set_P2DW_2                       SFRS=1;P2DW|=0x04
#define set_P2DW_1                       SFRS=1;P2DW|=0x02
#define set_P2DW_0                       SFRS=1;P2DW|=0x01

#define clr_P2DW_7                       SFRS=1;P2DW&=0x7F
#define clr_P2DW_6                       SFRS=1;P2DW&=0xBF
#define clr_P2DW_5                       SFRS=1;P2DW&=0xDF
#define clr_P2DW_4                       SFRS=1;P2DW&=0xEF
#define clr_P2DW_3                       SFRS=1;P2DW&=0xF7
#define clr_P2DW_2                       SFRS=1;P2DW&=0xFB
#define clr_P2DW_1                       SFRS=1;P2DW&=0xFD
#define clr_P2DW_0                       SFRS=1;P2DW&=0xFE

/**** P3DW  8DH  PAGE 1 ****/
#define set_P3DW_7                       SFRS=1;P3DW|=0x80
#define set_P3DW_6                       SFRS=1;P3DW|=0x40
#define set_P3DW_5                       SFRS=1;P3DW|=0x20
#define set_P3DW_4                       SFRS=1;P3DW|=0x10
#define set_P3DW_3                       SFRS=1;P3DW|=0x08
#define set_P3DW_2                       SFRS=1;P3DW|=0x04
#define set_P3DW_1                       SFRS=1;P3DW|=0x02
#define set_P3DW_0                       SFRS=1;P3DW|=0x01

#define clr_P3DW_7                       SFRS=1;P3DW&=0x7F
#define clr_P3DW_6                       SFRS=1;P3DW&=0xBF
#define clr_P3DW_5                       SFRS=1;P3DW&=0xDF
#define clr_P3DW_4                       SFRS=1;P3DW&=0xEF
#define clr_P3DW_3                       SFRS=1;P3DW&=0xF7
#define clr_P3DW_2                       SFRS=1;P3DW&=0xFB
#define clr_P3DW_1                       SFRS=1;P3DW&=0xFD
#define clr_P3DW_0                       SFRS=1;P3DW&=0xFE

/**** P4DW  8EH  PAGE 1 ****/
#define set_P4DW_7                       SFRS=1;P4DW|=0x80
#define set_P4DW_6                       SFRS=1;P4DW|=0x40
#define set_P4DW_5                       SFRS=1;P4DW|=0x20
#define set_P4DW_4                       SFRS=1;P4DW|=0x10
#define set_P4DW_3                       SFRS=1;P4DW|=0x08
#define set_P4DW_2                       SFRS=1;P4DW|=0x04
#define set_P4DW_1                       SFRS=1;P4DW|=0x02
#define set_P4DW_0                       SFRS=1;P4DW|=0x01

#define clr_P4DW_7                       SFRS=1;P4DW&=0x7F
#define clr_P4DW_6                       SFRS=1;P4DW&=0xBF
#define clr_P4DW_5                       SFRS=1;P4DW&=0xDF
#define clr_P4DW_4                       SFRS=1;P4DW&=0xEF
#define clr_P4DW_3                       SFRS=1;P4DW&=0xF7
#define clr_P4DW_2                       SFRS=1;P4DW&=0xFB
#define clr_P4DW_1                       SFRS=1;P4DW&=0xFD
#define clr_P4DW_0                       SFRS=1;P4DW&=0xFE

/**** P5DW  8FH  PAGE 1 ****/
#define set_P5DW_7                       SFRS=1;P5DW|=0x80
#define set_P5DW_6                       SFRS=1;P5DW|=0x40
#define set_P5DW_5                       SFRS=1;P5DW|=0x20
#define set_P5DW_4                       SFRS=1;P5DW|=0x10
#define set_P5DW_3                       SFRS=1;P5DW|=0x08
#define set_P5DW_2                       SFRS=1;P5DW|=0x04
#define set_P5DW_1                       SFRS=1;P5DW|=0x02
#define set_P5DW_0                       SFRS=1;P5DW|=0x01

#define clr_P5DW_7                       SFRS=1;P5DW&=0x7F
#define clr_P5DW_6                       SFRS=1;P5DW&=0xBF
#define clr_P5DW_5                       SFRS=1;P5DW&=0xDF
#define clr_P5DW_4                       SFRS=1;P5DW&=0xEF
#define clr_P5DW_3                       SFRS=1;P5DW&=0xF7
#define clr_P5DW_2                       SFRS=1;P5DW&=0xFB
#define clr_P5DW_1                       SFRS=1;P5DW&=0xFD
#define clr_P5DW_0                       SFRS=1;P5DW&=0xFE

/**** P0SR  92H  PAGE 1 ****/
#define set_P0SR_7                       SFRS=1;P0SR|=0x80
#define set_P0SR_6                       SFRS=1;P0SR|=0x40
#define set_P0SR_5                       SFRS=1;P0SR|=0x20
#define set_P0SR_4                       SFRS=1;P0SR|=0x10
#define set_P0SR_3                       SFRS=1;P0SR|=0x08
#define set_P0SR_2                       SFRS=1;P0SR|=0x04
#define set_P0SR_1                       SFRS=1;P0SR|=0x02
#define set_P0SR_0                       SFRS=1;P0SR|=0x01

#define clr_P0SR_7                       SFRS=1;P0SR&=0x7F
#define clr_P0SR_6                       SFRS=1;P0SR&=0xBF
#define clr_P0SR_5                       SFRS=1;P0SR&=0xDF
#define clr_P0SR_4                       SFRS=1;P0SR&=0xEF
#define clr_P0SR_3                       SFRS=1;P0SR&=0xF7
#define clr_P0SR_2                       SFRS=1;P0SR&=0xFB
#define clr_P0SR_1                       SFRS=1;P0SR&=0xFD
#define clr_P0SR_0                       SFRS=1;P0SR&=0xFE

/**** P1UP  93H  PAGE 1 ****/
#define set_P1UP_7                       SFRS=1;P1UP|=0x80
#define set_P1UP_6                       SFRS=1;P1UP|=0x40
#define set_P1UP_5                       SFRS=1;P1UP|=0x20
#define set_P1UP_4                       SFRS=1;P1UP|=0x10
#define set_P1UP_3                       SFRS=1;P1UP|=0x08
#define set_P1UP_2                       SFRS=1;P1UP|=0x04
#define set_P1UP_1                       SFRS=1;P1UP|=0x02
#define set_P1UP_0                       SFRS=1;P1UP|=0x01

#define clr_P1UP_7                       SFRS=1;P1UP&=0x7F
#define clr_P1UP_6                       SFRS=1;P1UP&=0xBF
#define clr_P1UP_5                       SFRS=1;P1UP&=0xDF
#define clr_P1UP_4                       SFRS=1;P1UP&=0xEF
#define clr_P1UP_3                       SFRS=1;P1UP&=0xF7
#define clr_P1UP_2                       SFRS=1;P1UP&=0xFB
#define clr_P1UP_1                       SFRS=1;P1UP&=0xFD
#define clr_P1UP_0                       SFRS=1;P1UP&=0xFE

/**** P2UP  94H  PAGE 1 ****/
#define set_P2UP_7                       SFRS=1;P2UP|=0x80
#define set_P2UP_6                       SFRS=1;P2UP|=0x40
#define set_P2UP_5                       SFRS=1;P2UP|=0x20
#define set_P2UP_4                       SFRS=1;P2UP|=0x10
#define set_P2UP_3                       SFRS=1;P2UP|=0x08
#define set_P2UP_2                       SFRS=1;P2UP|=0x04
#define set_P2UP_1                       SFRS=1;P2UP|=0x02
#define set_P2UP_0                       SFRS=1;P2UP|=0x01

#define clr_P2UP_7                       SFRS=1;P2UP&=0x7F
#define clr_P2UP_6                       SFRS=1;P2UP&=0xBF
#define clr_P2UP_5                       SFRS=1;P2UP&=0xDF
#define clr_P2UP_4                       SFRS=1;P2UP&=0xEF
#define clr_P2UP_3                       SFRS=1;P2UP&=0xF7
#define clr_P2UP_2                       SFRS=1;P2UP&=0xFB
#define clr_P2UP_1                       SFRS=1;P2UP&=0xFD
#define clr_P2UP_0                       SFRS=1;P2UP&=0xFE

/**** P3UP  95H  PAGE 1 ****/
#define set_P3UP_7                       SFRS=1;P3UP|=0x80
#define set_P3UP_6                       SFRS=1;P3UP|=0x40
#define set_P3UP_5                       SFRS=1;P3UP|=0x20
#define set_P3UP_4                       SFRS=1;P3UP|=0x10
#define set_P3UP_3                       SFRS=1;P3UP|=0x08
#define set_P3UP_2                       SFRS=1;P3UP|=0x04
#define set_P3UP_1                       SFRS=1;P3UP|=0x02
#define set_P3UP_0                       SFRS=1;P3UP|=0x01

#define clr_P3UP_7                       SFRS=1;P3UP&=0x7F
#define clr_P3UP_6                       SFRS=1;P3UP&=0xBF
#define clr_P3UP_5                       SFRS=1;P3UP&=0xDF
#define clr_P3UP_4                       SFRS=1;P3UP&=0xEF
#define clr_P3UP_3                       SFRS=1;P3UP&=0xF7
#define clr_P3UP_2                       SFRS=1;P3UP&=0xFB
#define clr_P3UP_1                       SFRS=1;P3UP&=0xFD
#define clr_P3UP_0                       SFRS=1;P3UP&=0xFE

/**** P4UP  96H  PAGE 1 ****/
#define set_P4UP_7                       SFRS=1;P4UP|=0x80
#define set_P4UP_6                       SFRS=1;P4UP|=0x40
#define set_P4UP_5                       SFRS=1;P4UP|=0x20
#define set_P4UP_4                       SFRS=1;P4UP|=0x10
#define set_P4UP_3                       SFRS=1;P4UP|=0x08
#define set_P4UP_2                       SFRS=1;P4UP|=0x04
#define set_P4UP_1                       SFRS=1;P4UP|=0x02
#define set_P4UP_0                       SFRS=1;P4UP|=0x01

#define clr_P4UP_7                       SFRS=1;P4UP&=0x7F
#define clr_P4UP_6                       SFRS=1;P4UP&=0xBF
#define clr_P4UP_5                       SFRS=1;P4UP&=0xDF
#define clr_P4UP_4                       SFRS=1;P4UP&=0xEF
#define clr_P4UP_3                       SFRS=1;P4UP&=0xF7
#define clr_P4UP_2                       SFRS=1;P4UP&=0xFB
#define clr_P4UP_1                       SFRS=1;P4UP&=0xFD
#define clr_P4UP_0                       SFRS=1;P4UP&=0xFE

/**** P5UP  97H  PAGE 1 ****/
#define set_P5UP_7                       SFRS=1;P5UP|=0x80
#define set_P5UP_6                       SFRS=1;P5UP|=0x40
#define set_P5UP_5                       SFRS=1;P5UP|=0x20
#define set_P5UP_4                       SFRS=1;P5UP|=0x10
#define set_P5UP_3                       SFRS=1;P5UP|=0x08
#define set_P5UP_2                       SFRS=1;P5UP|=0x04
#define set_P5UP_1                       SFRS=1;P5UP|=0x02
#define set_P5UP_0                       SFRS=1;P5UP|=0x01

#define clr_P5UP_7                       SFRS=1;P5UP&=0x7F
#define clr_P5UP_6                       SFRS=1;P5UP&=0xBF
#define clr_P5UP_5                       SFRS=1;P5UP&=0xDF
#define clr_P5UP_4                       SFRS=1;P5UP&=0xEF
#define clr_P5UP_3                       SFRS=1;P5UP&=0xF7
#define clr_P5UP_2                       SFRS=1;P5UP&=0xFB
#define clr_P5UP_1                       SFRS=1;P5UP&=0xFD
#define clr_P5UP_0                       SFRS=1;P5UP&=0xFE

/**** P0S  99H  PAGE 1 ****/
#define set_P0S_P0SR_7                   SFRS=1;P0S|=0x80
#define set_P0S_P0SR_6                   SFRS=1;P0S|=0x40
#define set_P0S_P0SR_5                   SFRS=1;P0S|=0x20
#define set_P0S_P0SR_4                   SFRS=1;P0S|=0x10
#define set_P0S_P0SR_3                   SFRS=1;P0S|=0x08
#define set_P0S_P0SR_2                   SFRS=1;P0S|=0x04
#define set_P0S_P0SR_1                   SFRS=1;P0S|=0x02
#define set_P0S_P0SR_0                   SFRS=1;P0S|=0x01

#define clr_P0S_P0SR_7                   SFRS=1;P0S&=0x7F
#define clr_P0S_P0SR_6                   SFRS=1;P0S&=0xBF
#define clr_P0S_P0SR_5                   SFRS=1;P0S&=0xDF
#define clr_P0S_P0SR_4                   SFRS=1;P0S&=0xEF
#define clr_P0S_P0SR_3                   SFRS=1;P0S&=0xF7
#define clr_P0S_P0SR_2                   SFRS=1;P0S&=0xFB
#define clr_P0S_P0SR_1                   SFRS=1;P0S&=0xFD
#define clr_P0S_P0SR_0                   SFRS=1;P0S&=0xFE

/**** P0UP  9AH  PAGE 1 ****/
#define set_P0UP_7                       SFRS=1;P0UP|=0x80
#define set_P0UP_6                       SFRS=1;P0UP|=0x40
#define set_P0UP_5                       SFRS=1;P0UP|=0x20
#define set_P0UP_4                       SFRS=1;P0UP|=0x10
#define set_P0UP_3                       SFRS=1;P0UP|=0x08
#define set_P0UP_2                       SFRS=1;P0UP|=0x04
#define set_P0UP_1                       SFRS=1;P0UP|=0x02
#define set_P0UP_0                       SFRS=1;P0UP|=0x01

#define clr_P0UP_7                       SFRS=1;P0UP&=0x7F
#define clr_P0UP_6                       SFRS=1;P0UP&=0xBF
#define clr_P0UP_5                       SFRS=1;P0UP&=0xDF
#define clr_P0UP_4                       SFRS=1;P0UP&=0xEF
#define clr_P0UP_3                       SFRS=1;P0UP&=0xF7
#define clr_P0UP_2                       SFRS=1;P0UP&=0xFB
#define clr_P0UP_1                       SFRS=1;P0UP&=0xFD
#define clr_P0UP_0                       SFRS=1;P0UP&=0xFE

/**** P1S  9BH  PAGE 1 ****/
#define set_P1S_P1SR_7                   SFRS=1;P1S|=0x80
#define set_P1S_P1SR_6                   SFRS=1;P1S|=0x40
#define set_P1S_P1SR_5                   SFRS=1;P1S|=0x20
#define set_P1S_P1SR_4                   SFRS=1;P1S|=0x10
#define set_P1S_P1SR_3                   SFRS=1;P1S|=0x08
#define set_P1S_P1SR_2                   SFRS=1;P1S|=0x04
#define set_P1S_P1SR_1                   SFRS=1;P1S|=0x02
#define set_P1S_P1SR_0                   SFRS=1;P1S|=0x01

#define clr_P1S_P1SR_7                   SFRS=1;P1S&=0x7F
#define clr_P1S_P1SR_6                   SFRS=1;P1S&=0xBF
#define clr_P1S_P1SR_5                   SFRS=1;P1S&=0xDF
#define clr_P1S_P1SR_4                   SFRS=1;P1S&=0xEF
#define clr_P1S_P1SR_3                   SFRS=1;P1S&=0xF7
#define clr_P1S_P1SR_2                   SFRS=1;P1S&=0xFB
#define clr_P1S_P1SR_1                   SFRS=1;P1S&=0xFD
#define clr_P1S_P1SR_0                   SFRS=1;P1S&=0xFE

/**** P1SR  9CH  PAGE 1 ****/
#define set_P1SR_P2SR_7                  SFRS=1;P1SR|=0x80
#define set_P1SR_P2SR_6                  SFRS=1;P1SR|=0x40
#define set_P1SR_P2SR_5                  SFRS=1;P1SR|=0x20
#define set_P1SR_P2SR_4                  SFRS=1;P1SR|=0x10
#define set_P1SR_P2SR_3                  SFRS=1;P1SR|=0x08
#define set_P1SR_P2SR_2                  SFRS=1;P1SR|=0x04
#define set_P1SR_P2SR_1                  SFRS=1;P1SR|=0x02
#define set_P1SR_P2SR_0                  SFRS=1;P1SR|=0x01

#define clr_P1SR_P2SR_7                  SFRS=1;P1SR&=0x7F
#define clr_P1SR_P2SR_6                  SFRS=1;P1SR&=0xBF
#define clr_P1SR_P2SR_5                  SFRS=1;P1SR&=0xDF
#define clr_P1SR_P2SR_4                  SFRS=1;P1SR&=0xEF
#define clr_P1SR_P2SR_3                  SFRS=1;P1SR&=0xF7
#define clr_P1SR_P2SR_2                  SFRS=1;P1SR&=0xFB
#define clr_P1SR_P2SR_1                  SFRS=1;P1SR&=0xFD
#define clr_P1SR_P2SR_0                  SFRS=1;P1SR&=0xFE

/**** P2S  9DH  PAGE 1 ****/
#define set_P2S_7                        SFRS=1;P2S|=0x80
#define set_P2S_6                        SFRS=1;P2S|=0x40
#define set_P2S_5                        SFRS=1;P2S|=0x20
#define set_P2S_4                        SFRS=1;P2S|=0x10
#define set_P2S_3                        SFRS=1;P2S|=0x08
#define set_P2S_2                        SFRS=1;P2S|=0x04
#define set_P2S_1                        SFRS=1;P2S|=0x02
#define set_P2S_0                        SFRS=1;P2S|=0x01

#define clr_P2S_7                        SFRS=1;P2S&=0x7F
#define clr_P2S_6                        SFRS=1;P2S&=0xBF
#define clr_P2S_5                        SFRS=1;P2S&=0xDF
#define clr_P2S_4                        SFRS=1;P2S&=0xEF
#define clr_P2S_3                        SFRS=1;P2S&=0xF7
#define clr_P2S_2                        SFRS=1;P2S&=0xFB
#define clr_P2S_1                        SFRS=1;P2S&=0xFD
#define clr_P2S_0                        SFRS=1;P2S&=0xFE

/**** P2SR  9EH  PAGE 1 ****/
#define set_P2SR_7                       SFRS=1;P2SR|=0x80
#define set_P2SR_6                       SFRS=1;P2SR|=0x40
#define set_P2SR_5                       SFRS=1;P2SR|=0x20
#define set_P2SR_4                       SFRS=1;P2SR|=0x10
#define set_P2SR_3                       SFRS=1;P2SR|=0x08
#define set_P2SR_2                       SFRS=1;P2SR|=0x04
#define set_P2SR_1                       SFRS=1;P2SR|=0x02
#define set_P2SR_0                       SFRS=1;P2SR|=0x01

#define clr_P2SR_7                       SFRS=1;P2SR&=0x7F
#define clr_P2SR_6                       SFRS=1;P2SR&=0xBF
#define clr_P2SR_5                       SFRS=1;P2SR&=0xDF
#define clr_P2SR_4                       SFRS=1;P2SR&=0xEF
#define clr_P2SR_3                       SFRS=1;P2SR&=0xF7
#define clr_P2SR_2                       SFRS=1;P2SR&=0xFB
#define clr_P2SR_1                       SFRS=1;P2SR&=0xFD
#define clr_P2SR_0                       SFRS=1;P2SR&=0xFE

/**** PIPS0  A1H  PAGE 1 ****/
#define set_PIPS0_PSEL_2                 SFRS=1;PIPS0|=0x40
#define set_PIPS0_PSEL_1                 SFRS=1;PIPS0|=0x20
#define set_PIPS0_PSEL_0                 SFRS=1;PIPS0|=0x10
#define set_PIPS0_BSEL_2                 SFRS=1;PIPS0|=0x04
#define set_PIPS0_BSEL_1                 SFRS=1;PIPS0|=0x02
#define set_PIPS0_BSEL_0                 SFRS=1;PIPS0|=0x01

#define clr_PIPS0_PSEL_2                 SFRS=1;PIPS0&=0xBF
#define clr_PIPS0_PSEL_1                 SFRS=1;PIPS0&=0xDF
#define clr_PIPS0_PSEL_0                 SFRS=1;PIPS0&=0xEF
#define clr_PIPS0_BSEL_2                 SFRS=1;PIPS0&=0xFB
#define clr_PIPS0_BSEL_1                 SFRS=1;PIPS0&=0xFD
#define clr_PIPS0_BSEL_0                 SFRS=1;PIPS0&=0xFE

/**** PIPS1  A2H  PAGE 1 ****/
#define set_PIPS1_PSEL_2                 SFRS=1;PIPS1|=0x40
#define set_PIPS1_PSEL_1                 SFRS=1;PIPS1|=0x20
#define set_PIPS1_PSEL_0                 SFRS=1;PIPS1|=0x10
#define set_PIPS1_BSEL_2                 SFRS=1;PIPS1|=0x04
#define set_PIPS1_BSEL_1                 SFRS=1;PIPS1|=0x02
#define set_PIPS1_BSEL_0                 SFRS=1;PIPS1|=0x01

#define clr_PIPS1_PSEL_2                 SFRS=1;PIPS1&=0xBF
#define clr_PIPS1_PSEL_1                 SFRS=1;PIPS1&=0xDF
#define clr_PIPS1_PSEL_0                 SFRS=1;PIPS1&=0xEF
#define clr_PIPS1_BSEL_2                 SFRS=1;PIPS1&=0xFB
#define clr_PIPS1_BSEL_1                 SFRS=1;PIPS1&=0xFD
#define clr_PIPS1_BSEL_0                 SFRS=1;PIPS1&=0xFE

/**** PIPS2  A3H  PAGE 1 ****/
#define set_PIPS2_PSEL_2                 SFRS=1;PIPS2|=0x40
#define set_PIPS2_PSEL_1                 SFRS=1;PIPS2|=0x20
#define set_PIPS2_PSEL_0                 SFRS=1;PIPS2|=0x10
#define set_PIPS2_BSEL_2                 SFRS=1;PIPS2|=0x04
#define set_PIPS2_BSEL_1                 SFRS=1;PIPS2|=0x02
#define set_PIPS2_BSEL_0                 SFRS=1;PIPS2|=0x01

#define clr_PIPS2_PSEL_2                 SFRS=1;PIPS2&=0xBF
#define clr_PIPS2_PSEL_1                 SFRS=1;PIPS2&=0xDF
#define clr_PIPS2_PSEL_0                 SFRS=1;PIPS2&=0xEF
#define clr_PIPS2_BSEL_2                 SFRS=1;PIPS2&=0xFB
#define clr_PIPS2_BSEL_1                 SFRS=1;PIPS2&=0xFD
#define clr_PIPS2_BSEL_0                 SFRS=1;PIPS2&=0xFE

/**** PIPS3  A4H  PAGE 1 ****/
#define set_PIPS3_PSEL_2                 SFRS=1;PIPS3|=0x40
#define set_PIPS3_PSEL_1                 SFRS=1;PIPS3|=0x20
#define set_PIPS3_PSEL_0                 SFRS=1;PIPS3|=0x10
#define set_PIPS3_BSEL_2                 SFRS=1;PIPS3|=0x04
#define set_PIPS3_BSEL_1                 SFRS=1;PIPS3|=0x02
#define set_PIPS3_BSEL_0                 SFRS=1;PIPS3|=0x01

#define clr_PIPS3_PSEL_2                 SFRS=1;PIPS3&=0xBF
#define clr_PIPS3_PSEL_1                 SFRS=1;PIPS3&=0xDF
#define clr_PIPS3_PSEL_0                 SFRS=1;PIPS3&=0xEF
#define clr_PIPS3_BSEL_2                 SFRS=1;PIPS3&=0xFB
#define clr_PIPS3_BSEL_1                 SFRS=1;PIPS3&=0xFD
#define clr_PIPS3_BSEL_0                 SFRS=1;PIPS3&=0xFE

/**** PIPS4  A5H  PAGE 1 ****/
#define set_PIPS4_PSEL_2                 SFRS=1;PIPS4|=0x40
#define set_PIPS4_PSEL_1                 SFRS=1;PIPS4|=0x20
#define set_PIPS4_PSEL_0                 SFRS=1;PIPS4|=0x10
#define set_PIPS4_BSEL_2                 SFRS=1;PIPS4|=0x04
#define set_PIPS4_BSEL_1                 SFRS=1;PIPS4|=0x02
#define set_PIPS4_BSEL_0                 SFRS=1;PIPS4|=0x01

#define clr_PIPS4_PSEL_2                 SFRS=1;PIPS4&=0xBF
#define clr_PIPS4_PSEL_1                 SFRS=1;PIPS4&=0xDF
#define clr_PIPS4_PSEL_0                 SFRS=1;PIPS4&=0xEF
#define clr_PIPS4_BSEL_2                 SFRS=1;PIPS4&=0xFB
#define clr_PIPS4_BSEL_1                 SFRS=1;PIPS4&=0xFD
#define clr_PIPS4_BSEL_0                 SFRS=1;PIPS4&=0xFE

/**** PIPS5  A6H  PAGE 1 ****/
#define set_PIPS5_PSEL_2                 SFRS=1;PIPS5|=0x40
#define set_PIPS5_PSEL_1                 SFRS=1;PIPS5|=0x20
#define set_PIPS5_PSEL_0                 SFRS=1;PIPS5|=0x10
#define set_PIPS5_BSEL_2                 SFRS=1;PIPS5|=0x04
#define set_PIPS5_BSEL_1                 SFRS=1;PIPS5|=0x02
#define set_PIPS5_BSEL_0                 SFRS=1;PIPS5|=0x01

#define clr_PIPS5_PSEL_2                 SFRS=1;PIPS5&=0xBF
#define clr_PIPS5_PSEL_1                 SFRS=1;PIPS5&=0xDF
#define clr_PIPS5_PSEL_0                 SFRS=1;PIPS5&=0xEF
#define clr_PIPS5_BSEL_2                 SFRS=1;PIPS5&=0xFB
#define clr_PIPS5_BSEL_1                 SFRS=1;PIPS5&=0xFD
#define clr_PIPS5_BSEL_0                 SFRS=1;PIPS5&=0xFE

/**** PIPS6  A7H  PAGE 1 ****/
#define set_PIPS6_PSEL_2                 SFRS=1;PIPS6|=0x40
#define set_PIPS6_PSEL_1                 SFRS=1;PIPS6|=0x20
#define set_PIPS6_PSEL_0                 SFRS=1;PIPS6|=0x10
#define set_PIPS6_BSEL_2                 SFRS=1;PIPS6|=0x04
#define set_PIPS6_BSEL_1                 SFRS=1;PIPS6|=0x02
#define set_PIPS6_BSEL_0                 SFRS=1;PIPS6|=0x01

#define clr_PIPS6_PSEL_2                 SFRS=1;PIPS6&=0xBF
#define clr_PIPS6_PSEL_1                 SFRS=1;PIPS6&=0xDF
#define clr_PIPS6_PSEL_0                 SFRS=1;PIPS6&=0xEF
#define clr_PIPS6_BSEL_2                 SFRS=1;PIPS6&=0xFB
#define clr_PIPS6_BSEL_1                 SFRS=1;PIPS6&=0xFD
#define clr_PIPS6_BSEL_0                 SFRS=1;PIPS6&=0xFE

/**** VRFCON  A9H  PAGE 1 TA protect register ****/
#define set_VRFCON_VRFSEL_2              SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON|=0x40;EA=BIT_TMP
#define set_VRFCON_VRFSEL_1              SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON|=0x20;EA=BIT_TMP
#define set_VRFCON_VRFSEL_0              SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON|=0x10;EA=BIT_TMP
#define set_VRFCON_ENLOAD                SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON|=0x02;EA=BIT_TMP
#define set_VRFCON_ENVRF                 SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON|=0x01;EA=BIT_TMP

#define clr_VRFCON_VRFSEL_2              SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON&=0xBF;EA=BIT_TMP
#define clr_VRFCON_VRFSEL_1              SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON&=0xDF;EA=BIT_TMP
#define clr_VRFCON_VRFSEL_0              SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON&=0xEF;EA=BIT_TMP
#define clr_VRFCON_ENLOAD                SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON&=0xFD;EA=BIT_TMP
#define clr_VRFCON_ENVRF                 SFRS=1;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;VRFCON&=0xFE;EA=BIT_TMP

/**** ACMPCR2  ABH  PAGE 1 ****/
#define set_ACMPCR2_SPEED1_1             SFRS=1;ACMPCR2|=0x80
#define set_ACMPCR2_SPEED1_0             SFRS=1;ACMPCR2|=0x40
#define set_ACMPCR2_POE1                 SFRS=1;ACMPCR2|=0x20
#define set_ACMPCR2_POE0                 SFRS=1;ACMPCR2|=0x10
#define set_ACMPCR2_SPEED0_1             SFRS=1;ACMPCR2|=0x08
#define set_ACMPCR2_SPEED0_0             SFRS=1;ACMPCR2|=0x04
#define set_ACMPCR2_CRVSSEL              SFRS=1;ACMPCR2|=0x02
#define set_ACMPCR2_CRVEN                SFRS=1;ACMPCR2|=0x01

#define clr_ACMPCR2_SPEED1_1             SFRS=1;ACMPCR2&=0x7F
#define clr_ACMPCR2_SPEED1_0             SFRS=1;ACMPCR2&=0xBF
#define clr_ACMPCR2_POE1                 SFRS=1;ACMPCR2&=0xDF
#define clr_ACMPCR2_POE0                 SFRS=1;ACMPCR2&=0xEF
#define clr_ACMPCR2_SPEED0_1             SFRS=1;ACMPCR2&=0xF7
#define clr_ACMPCR2_SPEED0_0             SFRS=1;ACMPCR2&=0xFB
#define clr_ACMPCR2_CRVSSEL              SFRS=1;ACMPCR2&=0xFD
#define clr_ACMPCR2_CRVEN                SFRS=1;ACMPCR2&=0xFE

/**** P3S  ACH  PAGE 1 ****/
#define set_P3S_7                        SFRS=1;P3S|=0x80
#define set_P3S_6                        SFRS=1;P3S|=0x40
#define set_P3S_5                        SFRS=1;P3S|=0x20
#define set_P3S_4                        SFRS=1;P3S|=0x10
#define set_P3S_3                        SFRS=1;P3S|=0x08
#define set_P3S_2                        SFRS=1;P3S|=0x04
#define set_P3S_1                        SFRS=1;P3S|=0x02
#define set_P3S_0                        SFRS=1;P3S|=0x01

#define clr_P3S_7                        SFRS=1;P3S&=0x7F
#define clr_P3S_6                        SFRS=1;P3S&=0xBF
#define clr_P3S_5                        SFRS=1;P3S&=0xDF
#define clr_P3S_4                        SFRS=1;P3S&=0xEF
#define clr_P3S_3                        SFRS=1;P3S&=0xF7
#define clr_P3S_2                        SFRS=1;P3S&=0xFB
#define clr_P3S_1                        SFRS=1;P3S&=0xFD
#define clr_P3S_0                        SFRS=1;P3S&=0xFE

/**** P3SR  ADH  PAGE 1 ****/
#define set_P3SR_7                       SFRS=1;P3SR|=0x80
#define set_P3SR_6                       SFRS=1;P3SR|=0x40
#define set_P3SR_5                       SFRS=1;P3SR|=0x20
#define set_P3SR_4                       SFRS=1;P3SR|=0x10
#define set_P3SR_3                       SFRS=1;P3SR|=0x08
#define set_P3SR_2                       SFRS=1;P3SR|=0x04
#define set_P3SR_1                       SFRS=1;P3SR|=0x02
#define set_P3SR_0                       SFRS=1;P3SR|=0x01

#define clr_P3SR_7                       SFRS=1;P3SR&=0x7F
#define clr_P3SR_6                       SFRS=1;P3SR&=0xBF
#define clr_P3SR_5                       SFRS=1;P3SR&=0xDF
#define clr_P3SR_4                       SFRS=1;P3SR&=0xEF
#define clr_P3SR_3                       SFRS=1;P3SR&=0xF7
#define clr_P3SR_2                       SFRS=1;P3SR&=0xFB
#define clr_P3SR_1                       SFRS=1;P3SR&=0xFD
#define clr_P3SR_0                       SFRS=1;P3SR&=0xFE

/**** P5SR  AEH  PAGE 1 ****/
#define set_P5SR_7                       SFRS=1;P5SR|=0x80
#define set_P5SR_6                       SFRS=1;P5SR|=0x40
#define set_P5SR_5                       SFRS=1;P5SR|=0x20
#define set_P5SR_4                       SFRS=1;P5SR|=0x10
#define set_P5SR_3                       SFRS=1;P5SR|=0x08
#define set_P5SR_2                       SFRS=1;P5SR|=0x04
#define set_P5SR_1                       SFRS=1;P5SR|=0x02
#define set_P5SR_0                       SFRS=1;P5SR|=0x01

#define clr_P5SR_7                       SFRS=1;P5SR&=0x7F
#define clr_P5SR_6                       SFRS=1;P5SR&=0xBF
#define clr_P5SR_5                       SFRS=1;P5SR&=0xDF
#define clr_P5SR_4                       SFRS=1;P5SR&=0xEF
#define clr_P5SR_3                       SFRS=1;P5SR&=0xF7
#define clr_P5SR_2                       SFRS=1;P5SR&=0xFB
#define clr_P5SR_1                       SFRS=1;P5SR&=0xFD
#define clr_P5SR_0                       SFRS=1;P5SR&=0xFE

/**** PIPS7  AFH  PAGE 1 ****/
#define set_PIPS7_PSEL_2                 SFRS=1;PIPS7|=0x40
#define set_PIPS7_PSEL_1                 SFRS=1;PIPS7|=0x20
#define set_PIPS7_PSEL_0                 SFRS=1;PIPS7|=0x10
#define set_PIPS7_BSEL_2                 SFRS=1;PIPS7|=0x04
#define set_PIPS7_BSEL_1                 SFRS=1;PIPS7|=0x02
#define set_PIPS7_BSEL_0                 SFRS=1;PIPS7|=0x01

#define clr_PIPS7_PSEL_2                 SFRS=1;PIPS7&=0xBF
#define clr_PIPS7_PSEL_1                 SFRS=1;PIPS7&=0xDF
#define clr_PIPS7_PSEL_0                 SFRS=1;PIPS7&=0xEF
#define clr_PIPS7_BSEL_2                 SFRS=1;PIPS7&=0xFB
#define clr_PIPS7_BSEL_1                 SFRS=1;PIPS7&=0xFD
#define clr_PIPS7_BSEL_0                 SFRS=1;PIPS7&=0xFE

/**** P0M1  B1H  PAGE 1 ****/
#define set_P0M1_7                       SFRS=1;P0M1|=0x80
#define set_P0M1_6                       SFRS=1;P0M1|=0x40
#define set_P0M1_5                       SFRS=1;P0M1|=0x20
#define set_P0M1_4                       SFRS=1;P0M1|=0x10
#define set_P0M1_3                       SFRS=1;P0M1|=0x08
#define set_P0M1_2                       SFRS=1;P0M1|=0x04
#define set_P0M1_1                       SFRS=1;P0M1|=0x02
#define set_P0M1_0                       SFRS=1;P0M1|=0x01

#define clr_P0M1_7                       SFRS=1;P0M1&=0x7F
#define clr_P0M1_6                       SFRS=1;P0M1&=0xBF
#define clr_P0M1_5                       SFRS=1;P0M1&=0xDF
#define clr_P0M1_4                       SFRS=1;P0M1&=0xEF
#define clr_P0M1_3                       SFRS=1;P0M1&=0xF7
#define clr_P0M1_2                       SFRS=1;P0M1&=0xFB
#define clr_P0M1_1                       SFRS=1;P0M1&=0xFD
#define clr_P0M1_0                       SFRS=1;P0M1&=0xFE

/**** P0M2  B2H  PAGE 1 ****/
#define set_P0M2_7                       SFRS=1;P0M2|=0x80
#define set_P0M2_6                       SFRS=1;P0M2|=0x40
#define set_P0M2_5                       SFRS=1;P0M2|=0x20
#define set_P0M2_4                       SFRS=1;P0M2|=0x10
#define set_P0M2_3                       SFRS=1;P0M2|=0x08
#define set_P0M2_2                       SFRS=1;P0M2|=0x04
#define set_P0M2_1                       SFRS=1;P0M2|=0x02
#define set_P0M2_0                       SFRS=1;P0M2|=0x01

#define clr_P0M2_7                       SFRS=1;P0M2&=0x7F
#define clr_P0M2_6                       SFRS=1;P0M2&=0xBF
#define clr_P0M2_5                       SFRS=1;P0M2&=0xDF
#define clr_P0M2_4                       SFRS=1;P0M2&=0xEF
#define clr_P0M2_3                       SFRS=1;P0M2&=0xF7
#define clr_P0M2_2                       SFRS=1;P0M2&=0xFB
#define clr_P0M2_1                       SFRS=1;P0M2&=0xFD
#define clr_P0M2_0                       SFRS=1;P0M2&=0xFE

/**** P1M1  B3H  PAGE 1 ****/
#define set_P1M1_7                       SFRS=1;P1M1|=0x80
#define set_P1M1_6                       SFRS=1;P1M1|=0x40
#define set_P1M1_5                       SFRS=1;P1M1|=0x20
#define set_P1M1_4                       SFRS=1;P1M1|=0x10
#define set_P1M1_3                       SFRS=1;P1M1|=0x08
#define set_P1M1_2                       SFRS=1;P1M1|=0x04
#define set_P1M1_1                       SFRS=1;P1M1|=0x02
#define set_P1M1_0                       SFRS=1;P1M1|=0x01

#define clr_P1M1_7                       SFRS=1;P1M1&=0x7F
#define clr_P1M1_6                       SFRS=1;P1M1&=0xBF
#define clr_P1M1_5                       SFRS=1;P1M1&=0xDF
#define clr_P1M1_4                       SFRS=1;P1M1&=0xEF
#define clr_P1M1_3                       SFRS=1;P1M1&=0xF7
#define clr_P1M1_2                       SFRS=1;P1M1&=0xFB
#define clr_P1M1_1                       SFRS=1;P1M1&=0xFD
#define clr_P1M1_0                       SFRS=1;P1M1&=0xFE

/**** P1M2  B4H  PAGE 1 ****/
#define set_P1M2_7                       SFRS=1;P1M2|=0x80
#define set_P1M2_6                       SFRS=1;P1M2|=0x40
#define set_P1M2_5                       SFRS=1;P1M2|=0x20
#define set_P1M2_4                       SFRS=1;P1M2|=0x10
#define set_P1M2_3                       SFRS=1;P1M2|=0x08
#define set_P1M2_2                       SFRS=1;P1M2|=0x04
#define set_P1M2_1                       SFRS=1;P1M2|=0x02
#define set_P1M2_0                       SFRS=1;P1M2|=0x01

#define clr_P1M2_7                       SFRS=1;P1M2&=0x7F
#define clr_P1M2_6                       SFRS=1;P1M2&=0xBF
#define clr_P1M2_5                       SFRS=1;P1M2&=0xDF
#define clr_P1M2_4                       SFRS=1;P1M2&=0xEF
#define clr_P1M2_3                       SFRS=1;P1M2&=0xF7
#define clr_P1M2_2                       SFRS=1;P1M2&=0xFB
#define clr_P1M2_1                       SFRS=1;P1M2&=0xFD
#define clr_P1M2_0                       SFRS=1;P1M2&=0xFE

/**** P2M1  B5H  PAGE 1 ****/
#define set_P2M1_7                       SFRS=1;P2M1|=0x80
#define set_P2M1_6                       SFRS=1;P2M1|=0x40
#define set_P2M1_5                       SFRS=1;P2M1|=0x20
#define set_P2M1_4                       SFRS=1;P2M1|=0x10
#define set_P2M1_3                       SFRS=1;P2M1|=0x08
#define set_P2M1_2                       SFRS=1;P2M1|=0x04
#define set_P2M1_1                       SFRS=1;P2M1|=0x02
#define set_P2M1_0                       SFRS=1;P2M1|=0x01

#define clr_P2M1_7                       SFRS=1;P2M1&=0x7F
#define clr_P2M1_6                       SFRS=1;P2M1&=0xBF
#define clr_P2M1_5                       SFRS=1;P2M1&=0xDF
#define clr_P2M1_4                       SFRS=1;P2M1&=0xEF
#define clr_P2M1_3                       SFRS=1;P2M1&=0xF7
#define clr_P2M1_2                       SFRS=1;P2M1&=0xFB
#define clr_P2M1_1                       SFRS=1;P2M1&=0xFD
#define clr_P2M1_0                       SFRS=1;P2M1&=0xFE

/**** P2M2  B6H  PAGE 1 ****/
#define set_P2M2_7                       SFRS=1;P2M2|=0x80
#define set_P2M2_6                       SFRS=1;P2M2|=0x40
#define set_P2M2_5                       SFRS=1;P2M2|=0x20
#define set_P2M2_4                       SFRS=1;P2M2|=0x10
#define set_P2M2_3                       SFRS=1;P2M2|=0x08
#define set_P2M2_2                       SFRS=1;P2M2|=0x04
#define set_P2M2_1                       SFRS=1;P2M2|=0x02
#define set_P2M2_0                       SFRS=1;P2M2|=0x01

#define clr_P2M2_7                       SFRS=1;P2M2&=0x7F
#define clr_P2M2_6                       SFRS=1;P2M2&=0xBF
#define clr_P2M2_5                       SFRS=1;P2M2&=0xDF
#define clr_P2M2_4                       SFRS=1;P2M2&=0xEF
#define clr_P2M2_3                       SFRS=1;P2M2&=0xF7
#define clr_P2M2_2                       SFRS=1;P2M2&=0xFB
#define clr_P2M2_1                       SFRS=1;P2M2&=0xFD
#define clr_P2M2_0                       SFRS=1;P2M2&=0xFE

/**** PWM0INTC  B7H  PAGE 1 ****/
#define set_PWM0INTC_INTTYP1             SFRS=1;PWM0INTC|=0x20
#define set_PWM0INTC_INTTYP0             SFRS=1;PWM0INTC|=0x10
#define set_PWM0INTC_INTSEL2             SFRS=1;PWM0INTC|=0x04
#define set_PWM0INTC_INTSEL1             SFRS=1;PWM0INTC|=0x02
#define set_PWM0INTC_INTSEL0             SFRS=1;PWM0INTC|=0x01

#define clr_PWM0INTC_INTTYP1             SFRS=1;PWM0INTC&=0xDF
#define clr_PWM0INTC_INTTYP0             SFRS=1;PWM0INTC&=0xEF
#define clr_PWM0INTC_INTSEL2             SFRS=1;PWM0INTC&=0xFB
#define clr_PWM0INTC_INTSEL1             SFRS=1;PWM0INTC&=0xFD
#define clr_PWM0INTC_INTSEL0             SFRS=1;PWM0INTC&=0xFE

/**** P4M1  B9H  PAGE 1 ****/
#define set_P4M1_7                       SFRS=1;P4M1|=0x80
#define set_P4M1_6                       SFRS=1;P4M1|=0x40
#define set_P4M1_5                       SFRS=1;P4M1|=0x20
#define set_P4M1_4                       SFRS=1;P4M1|=0x10
#define set_P4M1_3                       SFRS=1;P4M1|=0x08
#define set_P4M1_2                       SFRS=1;P4M1|=0x04
#define set_P4M1_1                       SFRS=1;P4M1|=0x02
#define set_P4M1_0                       SFRS=1;P4M1|=0x01

#define clr_P4M1_7                       SFRS=1;P4M1&=0x7F
#define clr_P4M1_6                       SFRS=1;P4M1&=0xBF
#define clr_P4M1_5                       SFRS=1;P4M1&=0xDF
#define clr_P4M1_4                       SFRS=1;P4M1&=0xEF
#define clr_P4M1_3                       SFRS=1;P4M1&=0xF7
#define clr_P4M1_2                       SFRS=1;P4M1&=0xFB
#define clr_P4M1_1                       SFRS=1;P4M1&=0xFD
#define clr_P4M1_0                       SFRS=1;P4M1&=0xFE

/**** P0DW  BAH  PAGE 1 ****/
#define set_P0DW_7                       SFRS=1;P0DW|=0x80
#define set_P0DW_6                       SFRS=1;P0DW|=0x40
#define set_P0DW_5                       SFRS=1;P0DW|=0x20
#define set_P0DW_4                       SFRS=1;P0DW|=0x10
#define set_P0DW_3                       SFRS=1;P0DW|=0x08
#define set_P0DW_2                       SFRS=1;P0DW|=0x04
#define set_P0DW_1                       SFRS=1;P0DW|=0x02
#define set_P0DW_0                       SFRS=1;P0DW|=0x01

#define clr_P0DW_7                       SFRS=1;P0DW&=0x7F
#define clr_P0DW_6                       SFRS=1;P0DW&=0xBF
#define clr_P0DW_5                       SFRS=1;P0DW&=0xDF
#define clr_P0DW_4                       SFRS=1;P0DW&=0xEF
#define clr_P0DW_3                       SFRS=1;P0DW&=0xF7
#define clr_P0DW_2                       SFRS=1;P0DW&=0xFB
#define clr_P0DW_1                       SFRS=1;P0DW&=0xFD
#define clr_P0DW_0                       SFRS=1;P0DW&=0xFE

/**** P4M2  BAH  PAGE 1 ****/
#define set_P4M2_7                       SFRS=1;P4M2|=0x80
#define set_P4M2_6                       SFRS=1;P4M2|=0x40
#define set_P4M2_5                       SFRS=1;P4M2|=0x20
#define set_P4M2_4                       SFRS=1;P4M2|=0x10
#define set_P4M2_3                       SFRS=1;P4M2|=0x08
#define set_P4M2_2                       SFRS=1;P4M2|=0x04
#define set_P4M2_1                       SFRS=1;P4M2|=0x02
#define set_P4M2_0                       SFRS=1;P4M2|=0x01

#define clr_P4M2_7                       SFRS=1;P4M2&=0x7F
#define clr_P4M2_6                       SFRS=1;P4M2&=0xBF
#define clr_P4M2_5                       SFRS=1;P4M2&=0xDF
#define clr_P4M2_4                       SFRS=1;P4M2&=0xEF
#define clr_P4M2_3                       SFRS=1;P4M2&=0xF7
#define clr_P4M2_2                       SFRS=1;P4M2&=0xFB
#define clr_P4M2_1                       SFRS=1;P4M2&=0xFD
#define clr_P4M2_0                       SFRS=1;P4M2&=0xFE

/**** P4S  BBH  PAGE 1 ****/
#define set_P4S_7                        SFRS=1;P4S|=0x80
#define set_P4S_6                        SFRS=1;P4S|=0x40
#define set_P4S_5                        SFRS=1;P4S|=0x20
#define set_P4S_4                        SFRS=1;P4S|=0x10
#define set_P4S_3                        SFRS=1;P4S|=0x08
#define set_P4S_2                        SFRS=1;P4S|=0x04
#define set_P4S_1                        SFRS=1;P4S|=0x02
#define set_P4S_0                        SFRS=1;P4S|=0x01

#define clr_P4S_7                        SFRS=1;P4S&=0x7F
#define clr_P4S_6                        SFRS=1;P4S&=0xBF
#define clr_P4S_5                        SFRS=1;P4S&=0xDF
#define clr_P4S_4                        SFRS=1;P4S&=0xEF
#define clr_P4S_3                        SFRS=1;P4S&=0xF7
#define clr_P4S_2                        SFRS=1;P4S&=0xFB
#define clr_P4S_1                        SFRS=1;P4S&=0xFD
#define clr_P4S_0                        SFRS=1;P4S&=0xFE

/**** PMW1INTC  BCH  PAGE 1 ****/
#define set_PMW1INTC_INTTYP1             SFRS=1;PMW1INTC|=0x20
#define set_PMW1INTC_INTTYP0             SFRS=1;PMW1INTC|=0x10
#define set_PMW1INTC_INTSEL2             SFRS=1;PMW1INTC|=0x04
#define set_PMW1INTC_INTSEL1             SFRS=1;PMW1INTC|=0x02
#define set_PMW1INTC_INTSEL0             SFRS=1;PMW1INTC|=0x01

#define clr_PMW1INTC_INTTYP1             SFRS=1;PMW1INTC&=0xDF
#define clr_PMW1INTC_INTTYP0             SFRS=1;PMW1INTC&=0xEF
#define clr_PMW1INTC_INTSEL2             SFRS=1;PMW1INTC&=0xFB
#define clr_PMW1INTC_INTSEL1             SFRS=1;PMW1INTC&=0xFD
#define clr_PMW1INTC_INTSEL0             SFRS=1;PMW1INTC&=0xFE

/**** P4SR  BCH  PAGE 1 ****/
#define set_P4SR_7                       SFRS=1;P4SR|=0x80
#define set_P4SR_6                       SFRS=1;P4SR|=0x40
#define set_P4SR_5                       SFRS=1;P4SR|=0x20
#define set_P4SR_4                       SFRS=1;P4SR|=0x10
#define set_P4SR_3                       SFRS=1;P4SR|=0x08
#define set_P4SR_2                       SFRS=1;P4SR|=0x04
#define set_P4SR_1                       SFRS=1;P4SR|=0x02
#define set_P4SR_0                       SFRS=1;P4SR|=0x01

#define clr_P4SR_7                       SFRS=1;P4SR&=0x7F
#define clr_P4SR_6                       SFRS=1;P4SR&=0xBF
#define clr_P4SR_5                       SFRS=1;P4SR&=0xDF
#define clr_P4SR_4                       SFRS=1;P4SR&=0xEF
#define clr_P4SR_3                       SFRS=1;P4SR&=0xF7
#define clr_P4SR_2                       SFRS=1;P4SR&=0xFB
#define clr_P4SR_1                       SFRS=1;P4SR&=0xFD
#define clr_P4SR_0                       SFRS=1;P4SR&=0xFE

/**** P5M1  BDH  PAGE 1 ****/
#define set_P5M1_7                       SFRS=1;P5M1|=0x80
#define set_P5M1_6                       SFRS=1;P5M1|=0x40
#define set_P5M1_5                       SFRS=1;P5M1|=0x20
#define set_P5M1_4                       SFRS=1;P5M1|=0x10
#define set_P5M1_3                       SFRS=1;P5M1|=0x08
#define set_P5M1_2                       SFRS=1;P5M1|=0x04
#define set_P5M1_1                       SFRS=1;P5M1|=0x02
#define set_P5M1_0                       SFRS=1;P5M1|=0x01

#define clr_P5M1_7                       SFRS=1;P5M1&=0x7F
#define clr_P5M1_6                       SFRS=1;P5M1&=0xBF
#define clr_P5M1_5                       SFRS=1;P5M1&=0xDF
#define clr_P5M1_4                       SFRS=1;P5M1&=0xEF
#define clr_P5M1_3                       SFRS=1;P5M1&=0xF7
#define clr_P5M1_2                       SFRS=1;P5M1&=0xFB
#define clr_P5M1_1                       SFRS=1;P5M1&=0xFD
#define clr_P5M1_0                       SFRS=1;P5M1&=0xFE

/**** P5M2  BEH  PAGE 1 ****/
#define set_P5M2_7                       SFRS=1;P5M2|=0x80
#define set_P5M2_6                       SFRS=1;P5M2|=0x40
#define set_P5M2_5                       SFRS=1;P5M2|=0x20
#define set_P5M2_4                       SFRS=1;P5M2|=0x10
#define set_P5M2_3                       SFRS=1;P5M2|=0x08
#define set_P5M2_2                       SFRS=1;P5M2|=0x04
#define set_P5M2_1                       SFRS=1;P5M2|=0x02
#define set_P5M2_0                       SFRS=1;P5M2|=0x01

#define clr_P5M2_7                       SFRS=1;P5M2&=0x7F
#define clr_P5M2_6                       SFRS=1;P5M2&=0xBF
#define clr_P5M2_5                       SFRS=1;P5M2&=0xDF
#define clr_P5M2_4                       SFRS=1;P5M2&=0xEF
#define clr_P5M2_3                       SFRS=1;P5M2&=0xF7
#define clr_P5M2_2                       SFRS=1;P5M2&=0xFB
#define clr_P5M2_1                       SFRS=1;P5M2&=0xFD
#define clr_P5M2_0                       SFRS=1;P5M2&=0xFE

/**** P5S  BFH  PAGE 1 ****/
#define set_P5S_7                        SFRS=1;P5S|=0x80
#define set_P5S_6                        SFRS=1;P5S|=0x40
#define set_P5S_5                        SFRS=1;P5S|=0x20
#define set_P5S_4                        SFRS=1;P5S|=0x10
#define set_P5S_3                        SFRS=1;P5S|=0x08
#define set_P5S_2                        SFRS=1;P5S|=0x04
#define set_P5S_1                        SFRS=1;P5S|=0x02
#define set_P5S_0                        SFRS=1;P5S|=0x01

#define clr_P5S_7                        SFRS=1;P5S&=0x7F
#define clr_P5S_6                        SFRS=1;P5S&=0xBF
#define clr_P5S_5                        SFRS=1;P5S&=0xDF
#define clr_P5S_4                        SFRS=1;P5S&=0xEF
#define clr_P5S_3                        SFRS=1;P5S&=0xF7
#define clr_P5S_2                        SFRS=1;P5S&=0xFB
#define clr_P5S_1                        SFRS=1;P5S&=0xFD
#define clr_P5S_0                        SFRS=1;P5S&=0xFE

/**** P3M1  C2H  PAGE 1 ****/
#define set_P3M1_7                       SFRS=1;P3M1|=0x80
#define set_P3M1_6                       SFRS=1;P3M1|=0x40
#define set_P3M1_5                       SFRS=1;P3M1|=0x20
#define set_P3M1_4                       SFRS=1;P3M1|=0x10
#define set_P3M1_3                       SFRS=1;P3M1|=0x08
#define set_P3M1_2                       SFRS=1;P3M1|=0x04
#define set_P3M1_1                       SFRS=1;P3M1|=0x02
#define set_P3M1_0                       SFRS=1;P3M1|=0x01

#define clr_P3M1_7                       SFRS=1;P3M1&=0x7F
#define clr_P3M1_6                       SFRS=1;P3M1&=0xBF
#define clr_P3M1_5                       SFRS=1;P3M1&=0xDF
#define clr_P3M1_4                       SFRS=1;P3M1&=0xEF
#define clr_P3M1_3                       SFRS=1;P3M1&=0xF7
#define clr_P3M1_2                       SFRS=1;P3M1&=0xFB
#define clr_P3M1_1                       SFRS=1;P3M1&=0xFD
#define clr_P3M1_0                       SFRS=1;P3M1&=0xFE

/**** P3M2  C3H  PAGE 1 ****/
#define set_P3M2_7                       SFRS=1;P3M2|=0x80
#define set_P3M2_6                       SFRS=1;P3M2|=0x40
#define set_P3M2_5                       SFRS=1;P3M2|=0x20
#define set_P3M2_4                       SFRS=1;P3M2|=0x10
#define set_P3M2_3                       SFRS=1;P3M2|=0x08
#define set_P3M2_2                       SFRS=1;P3M2|=0x04
#define set_P3M2_1                       SFRS=1;P3M2|=0x02
#define set_P3M2_0                       SFRS=1;P3M2|=0x01

#define clr_P3M2_7                       SFRS=1;P3M2&=0x7F
#define clr_P3M2_6                       SFRS=1;P3M2&=0xBF
#define clr_P3M2_5                       SFRS=1;P3M2&=0xDF
#define clr_P3M2_4                       SFRS=1;P3M2&=0xEF
#define clr_P3M2_3                       SFRS=1;P3M2&=0xF7
#define clr_P3M2_2                       SFRS=1;P3M2&=0xFB
#define clr_P3M2_1                       SFRS=1;P3M2&=0xFD
#define clr_P3M2_0                       SFRS=1;P3M2&=0xFE

/**** AUXR1  C9H  PAGE 1 ****/
#define set_AUXR1_UART3PX                SFRS=1;AUXR1|=0x08
#define set_AUXR1_UART2PX                SFRS=1;AUXR1|=0x04
#define set_AUXR1_UART1PX                SFRS=1;AUXR1|=0x02
#define set_AUXR1_UART0PX                SFRS=1;AUXR1|=0x01

#define clr_AUXR1_UART3PX                SFRS=1;AUXR1&=0xF7
#define clr_AUXR1_UART2PX                SFRS=1;AUXR1&=0xFB
#define clr_AUXR1_UART1PX                SFRS=1;AUXR1&=0xFD
#define clr_AUXR1_UART0PX                SFRS=1;AUXR1&=0xFE

/**** AINDIDS0  CEH  PAGE 1 ****/
#define set_AINDIDS0_AIN7DIDS            SFRS=1;AINDIDS0|=0x80
#define set_AINDIDS0_AIN6DIDS            SFRS=1;AINDIDS0|=0x40
#define set_AINDIDS0_AIN5DIDS            SFRS=1;AINDIDS0|=0x20
#define set_AINDIDS0_AIN4DIDS            SFRS=1;AINDIDS0|=0x10
#define set_AINDIDS0_AIN3DIDS            SFRS=1;AINDIDS0|=0x08
#define set_AINDIDS0_AIN2DIDS            SFRS=1;AINDIDS0|=0x04
#define set_AINDIDS0_AIN1DIDS            SFRS=1;AINDIDS0|=0x02
#define set_AINDIDS0_AIN0DIDS            SFRS=1;AINDIDS0|=0x01

#define clr_AINDIDS0_AIN7DIDS            SFRS=1;AINDIDS0&=0x7F
#define clr_AINDIDS0_AIN6DIDS            SFRS=1;AINDIDS0&=0xBF
#define clr_AINDIDS0_AIN5DIDS            SFRS=1;AINDIDS0&=0xDF
#define clr_AINDIDS0_AIN4DIDS            SFRS=1;AINDIDS0&=0xEF
#define clr_AINDIDS0_AIN3DIDS            SFRS=1;AINDIDS0&=0xF7
#define clr_AINDIDS0_AIN2DIDS            SFRS=1;AINDIDS0&=0xFB
#define clr_AINDIDS0_AIN1DIDS            SFRS=1;AINDIDS0&=0xFD
#define clr_AINDIDS0_AIN0DIDS            SFRS=1;AINDIDS0&=0xFE

/**** PWM0NP  D6H  PAGE 1 ****/
#define set_PWM0NP_PNP5                  SFRS=1;PWM0NP|=0x20
#define set_PWM0NP_PNP4                  SFRS=1;PWM0NP|=0x10
#define set_PWM0NP_PNP3                  SFRS=1;PWM0NP|=0x08
#define set_PWM0NP_PNP2                  SFRS=1;PWM0NP|=0x04
#define set_PWM0NP_PNP1                  SFRS=1;PWM0NP|=0x02
#define set_PWM0NP_PNP0                  SFRS=1;PWM0NP|=0x01

#define clr_PWM0NP_PNP5                  SFRS=1;PWM0NP&=0xDF
#define clr_PWM0NP_PNP4                  SFRS=1;PWM0NP&=0xEF
#define clr_PWM0NP_PNP3                  SFRS=1;PWM0NP&=0xF7
#define clr_PWM0NP_PNP2                  SFRS=1;PWM0NP&=0xFB
#define clr_PWM0NP_PNP1                  SFRS=1;PWM0NP&=0xFD
#define clr_PWM0NP_PNP0                  SFRS=1;PWM0NP&=0xFE

/**** PWM0FBD  D7H  PAGE 1 ****/
#define set_PWM0FBD_FBF                  SFRS=1;PWM0FBD|=0x80
#define set_PWM0FBD_FBINLS               SFRS=1;PWM0FBD|=0x40
#define set_PWM0FBD_FBD5                 SFRS=1;PWM0FBD|=0x20
#define set_PWM0FBD_FBD4                 SFRS=1;PWM0FBD|=0x10
#define set_PWM0FBD_FBD3                 SFRS=1;PWM0FBD|=0x08
#define set_PWM0FBD_FBD2                 SFRS=1;PWM0FBD|=0x04
#define set_PWM0FBD_FBD1                 SFRS=1;PWM0FBD|=0x02
#define set_PWM0FBD_FBD0                 SFRS=1;PWM0FBD|=0x01

#define clr_PWM0FBD_FBF                  SFRS=1;PWM0FBD&=0x7F
#define clr_PWM0FBD_FBINLS               SFRS=1;PWM0FBD&=0xBF
#define clr_PWM0FBD_FBD5                 SFRS=1;PWM0FBD&=0xDF
#define clr_PWM0FBD_FBD4                 SFRS=1;PWM0FBD&=0xEF
#define clr_PWM0FBD_FBD3                 SFRS=1;PWM0FBD&=0xF7
#define clr_PWM0FBD_FBD2                 SFRS=1;PWM0FBD&=0xFB
#define clr_PWM0FBD_FBD1                 SFRS=1;PWM0FBD&=0xFD
#define clr_PWM0FBD_FBD0                 SFRS=1;PWM0FBD&=0xFE

/**** PWM0CON1  DFH  PAGE 1 ****/
#define set_PWM0CON1_PWMMOD_1            SFRS=1;PWM0CON1|=0x80
#define set_PWM0CON1_PWMMOD_0            SFRS=1;PWM0CON1|=0x40
#define set_PWM0CON1_GP                  SFRS=1;PWM0CON1|=0x20
#define set_PWM0CON1_PWMTYP              SFRS=1;PWM0CON1|=0x10
#define set_PWM0CON1_FBINEN              SFRS=1;PWM0CON1|=0x08
#define set_PWM0CON1_PWMDIV_2            SFRS=1;PWM0CON1|=0x04
#define set_PWM0CON1_PWMDIV_1            SFRS=1;PWM0CON1|=0x02
#define set_PWM0CON1_PWMDIV_0            SFRS=1;PWM0CON1|=0x01

#define clr_PWM0CON1_PWMMOD_1            SFRS=1;PWM0CON1&=0x7F
#define clr_PWM0CON1_PWMMOD_0            SFRS=1;PWM0CON1&=0xBF
#define clr_PWM0CON1_GP                  SFRS=1;PWM0CON1&=0xDF
#define clr_PWM0CON1_PWMTYP              SFRS=1;PWM0CON1&=0xEF
#define clr_PWM0CON1_FBINEN              SFRS=1;PWM0CON1&=0xF7
#define clr_PWM0CON1_PWMDIV_2            SFRS=1;PWM0CON1&=0xFB
#define clr_PWM0CON1_PWMDIV_1            SFRS=1;PWM0CON1&=0xFD
#define clr_PWM0CON1_PWMDIV_0            SFRS=1;PWM0CON1&=0xFE

/**** CAPCON0  E1H  PAGE 1 ****/
#define set_CAPCON0_CAPEN2               SFRS=1;CAPCON0|=0x40
#define set_CAPCON0_CAPEN1               SFRS=1;CAPCON0|=0x20
#define set_CAPCON0_CAPEN0               SFRS=1;CAPCON0|=0x10
#define set_CAPCON0_CAPF2                SFRS=1;CAPCON0|=0x04
#define set_CAPCON0_CAPF1                SFRS=1;CAPCON0|=0x02
#define set_CAPCON0_CAPF0                SFRS=1;CAPCON0|=0x01

#define clr_CAPCON0_CAPEN2               SFRS=1;CAPCON0&=0xBF
#define clr_CAPCON0_CAPEN1               SFRS=1;CAPCON0&=0xDF
#define clr_CAPCON0_CAPEN0               SFRS=1;CAPCON0&=0xEF
#define clr_CAPCON0_CAPF2                SFRS=1;CAPCON0&=0xFB
#define clr_CAPCON0_CAPF1                SFRS=1;CAPCON0&=0xFD
#define clr_CAPCON0_CAPF0                SFRS=1;CAPCON0&=0xFE

/**** CAPCON1  E2H  PAGE 1 ****/
#define set_CAPCON1_CAP2LS_1             SFRS=1;CAPCON1|=0x20
#define set_CAPCON1_CAP2LS_0             SFRS=1;CAPCON1|=0x10
#define set_CAPCON1_CAP1LS_1             SFRS=1;CAPCON1|=0x08
#define set_CAPCON1_CAP1LS_0             SFRS=1;CAPCON1|=0x04
#define set_CAPCON1_CAP0LS_1             SFRS=1;CAPCON1|=0x02
#define set_CAPCON1_CAP0LS_0             SFRS=1;CAPCON1|=0x01

#define clr_CAPCON1_CAP2LS_1             SFRS=1;CAPCON1&=0xDF
#define clr_CAPCON1_CAP2LS_0             SFRS=1;CAPCON1&=0xEF
#define clr_CAPCON1_CAP1LS_1             SFRS=1;CAPCON1&=0xF7
#define clr_CAPCON1_CAP1LS_0             SFRS=1;CAPCON1&=0xFB
#define clr_CAPCON1_CAP0LS_1             SFRS=1;CAPCON1&=0xFD
#define clr_CAPCON1_CAP0LS_0             SFRS=1;CAPCON1&=0xFE

/**** CAPCON2  E3H  PAGE 1 ****/
#define set_CAPCON2_ENF2                 SFRS=1;CAPCON2|=0x40
#define set_CAPCON2_ENF1                 SFRS=1;CAPCON2|=0x20
#define set_CAPCON2_ENF0                 SFRS=1;CAPCON2|=0x10

#define clr_CAPCON2_ENF2                 SFRS=1;CAPCON2&=0xBF
#define clr_CAPCON2_ENF1                 SFRS=1;CAPCON2&=0xDF
#define clr_CAPCON2_ENF0                 SFRS=1;CAPCON2&=0xEF

/**** PICON  E9H  PAGE 1 ****/
#define set_PICON_PIT7                   SFRS=1;PICON|=0x80
#define set_PICON_PIT6                   SFRS=1;PICON|=0x40
#define set_PICON_PIT5                   SFRS=1;PICON|=0x20
#define set_PICON_PIT4                   SFRS=1;PICON|=0x10
#define set_PICON_PIT3                   SFRS=1;PICON|=0x08
#define set_PICON_PIT2                   SFRS=1;PICON|=0x04
#define set_PICON_PIT1                   SFRS=1;PICON|=0x02
#define set_PICON_PIT0                   SFRS=1;PICON|=0x01

#define clr_PICON_PIT7                   SFRS=1;PICON&=0x7F
#define clr_PICON_PIT6                   SFRS=1;PICON&=0xBF
#define clr_PICON_PIT5                   SFRS=1;PICON&=0xDF
#define clr_PICON_PIT4                   SFRS=1;PICON&=0xEF
#define clr_PICON_PIT3                   SFRS=1;PICON&=0xF7
#define clr_PICON_PIT2                   SFRS=1;PICON&=0xFB
#define clr_PICON_PIT1                   SFRS=1;PICON&=0xFD
#define clr_PICON_PIT0                   SFRS=1;PICON&=0xFE

/**** PINEN  EAH  PAGE 1 ****/
#define set_PINEN_PINEN7                 SFRS=1;PINEN|=0x80
#define set_PINEN_PINEN6                 SFRS=1;PINEN|=0x40
#define set_PINEN_PINEN5                 SFRS=1;PINEN|=0x20
#define set_PINEN_PINEN4                 SFRS=1;PINEN|=0x10
#define set_PINEN_PINEN3                 SFRS=1;PINEN|=0x08
#define set_PINEN_PINEN2                 SFRS=1;PINEN|=0x04
#define set_PINEN_PINEN1                 SFRS=1;PINEN|=0x02
#define set_PINEN_PINEN0                 SFRS=1;PINEN|=0x01

#define clr_PINEN_PINEN7                 SFRS=1;PINEN&=0x7F
#define clr_PINEN_PINEN6                 SFRS=1;PINEN&=0xBF
#define clr_PINEN_PINEN5                 SFRS=1;PINEN&=0xDF
#define clr_PINEN_PINEN4                 SFRS=1;PINEN&=0xEF
#define clr_PINEN_PINEN3                 SFRS=1;PINEN&=0xF7
#define clr_PINEN_PINEN2                 SFRS=1;PINEN&=0xFB
#define clr_PINEN_PINEN1                 SFRS=1;PINEN&=0xFD
#define clr_PINEN_PINEN0                 SFRS=1;PINEN&=0xFE

/**** PIPEN  EBH  PAGE 1 ****/
#define set_PIPEN_PIPEN7                 SFRS=1;PIPEN|=0x80
#define set_PIPEN_PIPEN6                 SFRS=1;PIPEN|=0x40
#define set_PIPEN_PIPEN5                 SFRS=1;PIPEN|=0x20
#define set_PIPEN_PIPEN4                 SFRS=1;PIPEN|=0x10
#define set_PIPEN_PIPEN3                 SFRS=1;PIPEN|=0x08
#define set_PIPEN_PIPEN2                 SFRS=1;PIPEN|=0x04
#define set_PIPEN_PIPEN1                 SFRS=1;PIPEN|=0x02
#define set_PIPEN_PIPEN0                 SFRS=1;PIPEN|=0x01

#define clr_PIPEN_PIPEN7                 SFRS=1;PIPEN&=0x7F
#define clr_PIPEN_PIPEN6                 SFRS=1;PIPEN&=0xBF
#define clr_PIPEN_PIPEN5                 SFRS=1;PIPEN&=0xDF
#define clr_PIPEN_PIPEN4                 SFRS=1;PIPEN&=0xEF
#define clr_PIPEN_PIPEN3                 SFRS=1;PIPEN&=0xF7
#define clr_PIPEN_PIPEN2                 SFRS=1;PIPEN&=0xFB
#define clr_PIPEN_PIPEN1                 SFRS=1;PIPEN&=0xFD
#define clr_PIPEN_PIPEN0                 SFRS=1;PIPEN&=0xFE

/**** DMA1CR0  EBH  PAGE 1 ****/
#define set_DMA1CR0_PSSEL_3              SFRS=1;DMA1CR0|=0x80
#define set_DMA1CR0_PSSEL_2              SFRS=1;DMA1CR0|=0x40
#define set_DMA1CR0_PSSEL_1              SFRS=1;DMA1CR0|=0x20
#define set_DMA1CR0_PSSEL_0              SFRS=1;DMA1CR0|=0x10
#define set_DMA1CR0_HIE                  SFRS=1;DMA1CR0|=0x08
#define set_DMA1CR0_FIE                  SFRS=1;DMA1CR0|=0x04
#define set_DMA1CR0_RUN                  SFRS=1;DMA1CR0|=0x02
#define set_DMA1CR0_EN                   SFRS=1;DMA1CR0|=0x01

#define clr_DMA1CR0_PSSEL_3              SFRS=1;DMA1CR0&=0x7F
#define clr_DMA1CR0_PSSEL_2              SFRS=1;DMA1CR0&=0xBF
#define clr_DMA1CR0_PSSEL_1              SFRS=1;DMA1CR0&=0xDF
#define clr_DMA1CR0_PSSEL_0              SFRS=1;DMA1CR0&=0xEF
#define clr_DMA1CR0_HIE                  SFRS=1;DMA1CR0&=0xF7
#define clr_DMA1CR0_FIE                  SFRS=1;DMA1CR0&=0xFB
#define clr_DMA1CR0_RUN                  SFRS=1;DMA1CR0&=0xFD
#define clr_DMA1CR0_EN                   SFRS=1;DMA1CR0&=0xFE

/**** SPI0CR1  F3H  PAGE 1 ****/
#define set_SPI0CR1_SPR3                 SFRS=1;SPI0CR1|=0x20
#define set_SPI0CR1_SPR2                 SFRS=1;SPI0CR1|=0x10
#define set_SPI0CR1_TXDMAEN              SFRS=1;SPI0CR1|=0x08
#define set_SPI0CR1_RXDMAEN              SFRS=1;SPI0CR1|=0x04
#define set_SPI0CR1_SPIS1                SFRS=1;SPI0CR1|=0x02
#define set_SPI0CR1_SPIS0                SFRS=1;SPI0CR1|=0x01

#define clr_SPI0CR1_SPR3                 SFRS=1;SPI0CR1&=0xDF
#define clr_SPI0CR1_SPR2                 SFRS=1;SPI0CR1&=0xEF
#define clr_SPI0CR1_TXDMAEN              SFRS=1;SPI0CR1&=0xF7
#define clr_SPI0CR1_RXDMAEN              SFRS=1;SPI0CR1&=0xFB
#define clr_SPI0CR1_SPIS1                SFRS=1;SPI0CR1&=0xFD
#define clr_SPI0CR1_SPIS0                SFRS=1;SPI0CR1&=0xFE

/**** PWM0DTEN  F9H  PAGE 1 ****/
#define set_PWM0DTEN_PWMnDTCNT_8         SFRS=1;PWM0DTEN|=0x10
#define set_PWM0DTEN_PDT45EN             SFRS=1;PWM0DTEN|=0x04
#define set_PWM0DTEN_PDT23EN             SFRS=1;PWM0DTEN|=0x02
#define set_PWM0DTEN_PDT01EN             SFRS=1;PWM0DTEN|=0x01

#define clr_PWM0DTEN_PWMnDTCNT_8         SFRS=1;PWM0DTEN&=0xEF
#define clr_PWM0DTEN_PDT45EN             SFRS=1;PWM0DTEN&=0xFB
#define clr_PWM0DTEN_PDT23EN             SFRS=1;PWM0DTEN&=0xFD
#define clr_PWM0DTEN_PDT01EN             SFRS=1;PWM0DTEN&=0xFE

/**** PWM0MEN  FBH  PAGE 1 ****/
#define set_PWM0MEN_PMEN5                SFRS=1;PWM0MEN|=0x20
#define set_PWM0MEN_PMEN4                SFRS=1;PWM0MEN|=0x10
#define set_PWM0MEN_PMEN3                SFRS=1;PWM0MEN|=0x08
#define set_PWM0MEN_PMEN2                SFRS=1;PWM0MEN|=0x04
#define set_PWM0MEN_PMEN1                SFRS=1;PWM0MEN|=0x02
#define set_PWM0MEN_PMEN0                SFRS=1;PWM0MEN|=0x01

#define clr_PWM0MEN_PMEN5                SFRS=1;PWM0MEN&=0xDF
#define clr_PWM0MEN_PMEN4                SFRS=1;PWM0MEN&=0xEF
#define clr_PWM0MEN_PMEN3                SFRS=1;PWM0MEN&=0xF7
#define clr_PWM0MEN_PMEN2                SFRS=1;PWM0MEN&=0xFB
#define clr_PWM0MEN_PMEN1                SFRS=1;PWM0MEN&=0xFD
#define clr_PWM0MEN_PMEN0                SFRS=1;PWM0MEN&=0xFE

/**** PWM0MD  FCH  PAGE 1 ****/
#define set_PWM0MD_PMD5                  SFRS=1;PWM0MD|=0x20
#define set_PWM0MD_PMD4                  SFRS=1;PWM0MD|=0x10
#define set_PWM0MD_PMD3                  SFRS=1;PWM0MD|=0x08
#define set_PWM0MD_PMD2                  SFRS=1;PWM0MD|=0x04
#define set_PWM0MD_PMD1                  SFRS=1;PWM0MD|=0x02
#define set_PWM0MD_PMD0                  SFRS=1;PWM0MD|=0x01

#define clr_PWM0MD_PMD5                  SFRS=1;PWM0MD&=0xDF
#define clr_PWM0MD_PMD4                  SFRS=1;PWM0MD&=0xEF
#define clr_PWM0MD_PMD3                  SFRS=1;PWM0MD&=0xF7
#define clr_PWM0MD_PMD2                  SFRS=1;PWM0MD&=0xFB
#define clr_PWM0MD_PMD1                  SFRS=1;PWM0MD&=0xFD
#define clr_PWM0MD_PMD0                  SFRS=1;PWM0MD&=0xFE

/********SFR PAGE 2*************/
/**** P6M1  84H  PAGE 2 ****/
#define set_P6M1_7                       SFRS=2;P6M1|=0x80
#define set_P6M1_6                       SFRS=2;P6M1|=0x40
#define set_P6M1_5                       SFRS=2;P6M1|=0x20
#define set_P6M1_4                       SFRS=2;P6M1|=0x10
#define set_P6M1_3                       SFRS=2;P6M1|=0x08
#define set_P6M1_2                       SFRS=2;P6M1|=0x04
#define set_P6M1_1                       SFRS=2;P6M1|=0x02
#define set_P6M1_0                       SFRS=2;P6M1|=0x01

#define clr_P6M1_7                       SFRS=2;P6M1&=0x7F
#define clr_P6M1_6                       SFRS=2;P6M1&=0xBF
#define clr_P6M1_5                       SFRS=2;P6M1&=0xDF
#define clr_P6M1_4                       SFRS=2;P6M1&=0xEF
#define clr_P6M1_3                       SFRS=2;P6M1&=0xF7
#define clr_P6M1_2                       SFRS=2;P6M1&=0xFB
#define clr_P6M1_1                       SFRS=2;P6M1&=0xFD
#define clr_P6M1_0                       SFRS=2;P6M1&=0xFE

/**** P6M2  85H  PAGE 2 ****/
#define set_P6M2_7                       SFRS=2;P6M2|=0x80
#define set_P6M2_6                       SFRS=2;P6M2|=0x40
#define set_P6M2_5                       SFRS=2;P6M2|=0x20
#define set_P6M2_4                       SFRS=2;P6M2|=0x10
#define set_P6M2_3                       SFRS=2;P6M2|=0x08
#define set_P6M2_2                       SFRS=2;P6M2|=0x04
#define set_P6M2_1                       SFRS=2;P6M2|=0x02
#define set_P6M2_0                       SFRS=2;P6M2|=0x01

#define clr_P6M2_7                       SFRS=2;P6M2&=0x7F
#define clr_P6M2_6                       SFRS=2;P6M2&=0xBF
#define clr_P6M2_5                       SFRS=2;P6M2&=0xDF
#define clr_P6M2_4                       SFRS=2;P6M2&=0xEF
#define clr_P6M2_3                       SFRS=2;P6M2&=0xF7
#define clr_P6M2_2                       SFRS=2;P6M2&=0xFB
#define clr_P6M2_1                       SFRS=2;P6M2&=0xFD
#define clr_P6M2_0                       SFRS=2;P6M2&=0xFE

/**** PWM1MD  8CH  PAGE 2 ****/
#define set_PWM1MD_PMD1                  SFRS=2;PWM1MD|=0x02
#define set_PWM1MD_PMD0                  SFRS=2;PWM1MD|=0x01

#define clr_PWM1MD_PMD1                  SFRS=2;PWM1MD&=0xFD
#define clr_PWM1MD_PMD0                  SFRS=2;PWM1MD&=0xFE

/**** PWM1MEN  8DH  PAGE 2 ****/
#define set_PWM1MEN_PMEN1                SFRS=2;PWM1MEN|=0x02
#define set_PWM1MEN_PMEN0                SFRS=2;PWM1MEN|=0x01

#define clr_PWM1MEN_PMEN1                SFRS=2;PWM1MEN&=0xFD
#define clr_PWM1MEN_PMEN0                SFRS=2;PWM1MEN&=0xFE

/**** P6SR  8EH  PAGE 2 ****/
#define set_P6SR_7                       SFRS=2;P6SR|=0x80
#define set_P6SR_6                       SFRS=2;P6SR|=0x40
#define set_P6SR_5                       SFRS=2;P6SR|=0x20
#define set_P6SR_4                       SFRS=2;P6SR|=0x10
#define set_P6SR_3                       SFRS=2;P6SR|=0x08
#define set_P6SR_2                       SFRS=2;P6SR|=0x04
#define set_P6SR_1                       SFRS=2;P6SR|=0x02
#define set_P6SR_0                       SFRS=2;P6SR|=0x01

#define clr_P6SR_7                       SFRS=2;P6SR&=0x7F
#define clr_P6SR_6                       SFRS=2;P6SR&=0xBF
#define clr_P6SR_5                       SFRS=2;P6SR&=0xDF
#define clr_P6SR_4                       SFRS=2;P6SR&=0xEF
#define clr_P6SR_3                       SFRS=2;P6SR&=0xF7
#define clr_P6SR_2                       SFRS=2;P6SR&=0xFB
#define clr_P6SR_1                       SFRS=2;P6SR&=0xFD
#define clr_P6SR_0                       SFRS=2;P6SR&=0xFE

/**** P6DW  8FH  PAGE 2 ****/
#define set_P6DW_7                       SFRS=2;P6DW|=0x80
#define set_P6DW_6                       SFRS=2;P6DW|=0x40
#define set_P6DW_5                       SFRS=2;P6DW|=0x20
#define set_P6DW_4                       SFRS=2;P6DW|=0x10
#define set_P6DW_3                       SFRS=2;P6DW|=0x08
#define set_P6DW_2                       SFRS=2;P6DW|=0x04
#define set_P6DW_1                       SFRS=2;P6DW|=0x02
#define set_P6DW_0                       SFRS=2;P6DW|=0x01

#define clr_P6DW_7                       SFRS=2;P6DW&=0x7F
#define clr_P6DW_6                       SFRS=2;P6DW&=0xBF
#define clr_P6DW_5                       SFRS=2;P6DW&=0xDF
#define clr_P6DW_4                       SFRS=2;P6DW&=0xEF
#define clr_P6DW_3                       SFRS=2;P6DW&=0xF7
#define clr_P6DW_2                       SFRS=2;P6DW&=0xFB
#define clr_P6DW_1                       SFRS=2;P6DW&=0xFD
#define clr_P6DW_0                       SFRS=2;P6DW&=0xFE

/**** P6MF10  92H  PAGE 2 ****/
#define set_P6MF10_P6MF0[3:0]            SFRS=2;P6MF10|=0x40
#define set_P6MF10_00000000b             SFRS=2;P6MF10|=0x20

#define clr_P6MF10_P6MF0[3:0]            SFRS=2;P6MF10&=0xBF
#define clr_P6MF10_00000000b             SFRS=2;P6MF10&=0xDF

/**** P6MF32  93H  PAGE 2 ****/
#define set_P6MF32_P6MF2[3:0]            SFRS=2;P6MF32|=0x40
#define set_P6MF32_00000000b             SFRS=2;P6MF32|=0x20

#define clr_P6MF32_P6MF2[3:0]            SFRS=2;P6MF32&=0xBF
#define clr_P6MF32_00000000b             SFRS=2;P6MF32&=0xDF

/**** P6MF54  94H  PAGE 2 ****/
#define set_P6MF54_P6MF4[3:0]            SFRS=2;P6MF54|=0x40
#define set_P6MF54_00000000b             SFRS=2;P6MF54|=0x20

#define clr_P6MF54_P6MF4[3:0]            SFRS=2;P6MF54&=0xBF
#define clr_P6MF54_00000000b             SFRS=2;P6MF54&=0xDF

/**** P6MF76  95H  PAGE 2 ****/
#define set_P6MF76_P6MF6[3:0]            SFRS=2;P6MF76|=0x40
#define set_P6MF76_00000000b             SFRS=2;P6MF76|=0x20

#define clr_P6MF76_P6MF6[3:0]            SFRS=2;P6MF76&=0xBF
#define clr_P6MF76_00000000b             SFRS=2;P6MF76&=0xDF

/**** P6S  96H  PAGE 2 ****/
#define set_P6S_7                        SFRS=2;P6S|=0x80
#define set_P6S_6                        SFRS=2;P6S|=0x40
#define set_P6S_5                        SFRS=2;P6S|=0x20
#define set_P6S_4                        SFRS=2;P6S|=0x10
#define set_P6S_3                        SFRS=2;P6S|=0x08
#define set_P6S_2                        SFRS=2;P6S|=0x04
#define set_P6S_1                        SFRS=2;P6S|=0x02
#define set_P6S_0                        SFRS=2;P6S|=0x01

#define clr_P6S_7                        SFRS=2;P6S&=0x7F
#define clr_P6S_6                        SFRS=2;P6S&=0xBF
#define clr_P6S_5                        SFRS=2;P6S&=0xDF
#define clr_P6S_4                        SFRS=2;P6S&=0xEF
#define clr_P6S_3                        SFRS=2;P6S&=0xF7
#define clr_P6S_2                        SFRS=2;P6S&=0xFB
#define clr_P6S_1                        SFRS=2;P6S&=0xFD
#define clr_P6S_0                        SFRS=2;P6S&=0xFE

/**** P6UP  97H  PAGE 2 ****/
#define set_P6UP_7                       SFRS=2;P6UP|=0x80
#define set_P6UP_6                       SFRS=2;P6UP|=0x40
#define set_P6UP_5                       SFRS=2;P6UP|=0x20
#define set_P6UP_4                       SFRS=2;P6UP|=0x10
#define set_P6UP_3                       SFRS=2;P6UP|=0x08
#define set_P6UP_2                       SFRS=2;P6UP|=0x04
#define set_P6UP_1                       SFRS=2;P6UP|=0x02
#define set_P6UP_0                       SFRS=2;P6UP|=0x01

#define clr_P6UP_7                       SFRS=2;P6UP&=0x7F
#define clr_P6UP_6                       SFRS=2;P6UP&=0xBF
#define clr_P6UP_5                       SFRS=2;P6UP&=0xDF
#define clr_P6UP_4                       SFRS=2;P6UP&=0xEF
#define clr_P6UP_3                       SFRS=2;P6UP&=0xF7
#define clr_P6UP_2                       SFRS=2;P6UP&=0xFB
#define clr_P6UP_1                       SFRS=2;P6UP&=0xFD
#define clr_P6UP_0                       SFRS=2;P6UP&=0xFE

/**** PWM1CON0  9CH  PAGE 2 ****/
#define set_PWM1CON0_PWMRUN             SFRS=2;PWM1CON0|=0x80
#define set_PWM1CON0_LOAD                SFRS=2;PWM1CON0|=0x40
#define set_PWM1CON0_PWMF                SFRS=2;PWM1CON0|=0x20
#define set_PWM1CON0_CLRPWM              SFRS=2;PWM1CON0|=0x10

#define clr_PWM1CON0_PWM1RUN             SFRS=2;PWM1CON0&=0x7F
#define clr_PWM1CON0_LOAD                SFRS=2;PWM1CON0&=0xBF
#define clr_PWM1CON0_PWMF                SFRS=2;PWM1CON0&=0xDF
#define clr_PWM1CON0_CLRPWM              SFRS=2;PWM1CON0&=0xEF

/**** PWM1CON1  9DH  PAGE 2 ****/
#define set_PWM1CON1_PWMMOD_1            SFRS=2;PWM1CON1|=0x80
#define set_PWM1CON1_PWMMOD_0            SFRS=2;PWM1CON1|=0x40
#define set_PWM1CON1_GP                  SFRS=2;PWM1CON1|=0x20
#define set_PWM1CON1_PWMTYP              SFRS=2;PWM1CON1|=0x10
#define set_PWM1CON1_PWMDIV_2            SFRS=2;PWM1CON1|=0x04
#define set_PWM1CON1_PWMDIV_1            SFRS=2;PWM1CON1|=0x02
#define set_PWM1CON1_PWMDIV_0            SFRS=2;PWM1CON1|=0x01

#define clr_PWM1CON1_PWMMOD_1            SFRS=2;PWM1CON1&=0x7F
#define clr_PWM1CON1_PWMMOD_0            SFRS=2;PWM1CON1&=0xBF
#define clr_PWM1CON1_GP                  SFRS=2;PWM1CON1&=0xDF
#define clr_PWM1CON1_PWMTYP              SFRS=2;PWM1CON1&=0xEF
#define clr_PWM1CON1_PWMDIV_2            SFRS=2;PWM1CON1&=0xFB
#define clr_PWM1CON1_PWMDIV_1            SFRS=2;PWM1CON1&=0xFD
#define clr_PWM1CON1_PWMDIV_0            SFRS=2;PWM1CON1&=0xFE

/**** PWM1INTC  9EH  PAGE 2 ****/
#define set_PWM1INTC_INTTYP1             SFRS=2;PWM1INTC|=0x20
#define set_PWM1INTC_INTTYP0             SFRS=2;PWM1INTC|=0x10
#define set_PWM1INTC_INTSEL2             SFRS=2;PWM1INTC|=0x04
#define set_PWM1INTC_INTSEL1             SFRS=2;PWM1INTC|=0x02
#define set_PWM1INTC_INTSEL0             SFRS=2;PWM1INTC|=0x01

#define clr_PWM1INTC_INTTYP1             SFRS=2;PWM1INTC&=0xDF
#define clr_PWM1INTC_INTTYP0             SFRS=2;PWM1INTC&=0xEF
#define clr_PWM1INTC_INTSEL2             SFRS=2;PWM1INTC&=0xFB
#define clr_PWM1INTC_INTSEL1             SFRS=2;PWM1INTC&=0xFD
#define clr_PWM1INTC_INTSEL0             SFRS=2;PWM1INTC&=0xFE

/**** I2C0ADDR1  A1H  PAGE 2 ****/
#define set_I2C0ADDR1_GC                 SFRS=2;I2C0ADDR1|=0x01

#define clr_I2C0ADDR1_GC                 SFRS=2;I2C0ADDR1&=0xFE

/**** I2C0ADDR2  A2H  PAGE 2 ****/
#define set_I2C0ADDR2_GC                 SFRS=2;I2C0ADDR2|=0x01

#define clr_I2C0ADDR2_GC                 SFRS=2;I2C0ADDR2&=0xFE

/**** I2C0ADDR3  A3H  PAGE 2 ****/
#define set_I2C0ADDR3_GC                 SFRS=2;I2C0ADDR3|=0x01

#define clr_I2C0ADDR3_GC                 SFRS=2;I2C0ADDR3&=0xFE

/**** I2C1ADDR1  A4H  PAGE 2 ****/
#define set_I2C1ADDR1_GC                 SFRS=2;I2C1ADDR1|=0x01

#define clr_I2C1ADDR1_GC                 SFRS=2;I2C1ADDR1&=0xFE

/**** I2C1ADDR2  A5H  PAGE 2 ****/
#define set_I2C1ADDR2_GC                 SFRS=2;I2C1ADDR2|=0x01

#define clr_I2C1ADDR2_GC                 SFRS=2;I2C1ADDR2&=0xFE

/**** I2C1ADDR3  A6H  PAGE 2 ****/
#define set_I2C1ADDR3_GC                 SFRS=2;I2C1ADDR3|=0x01

#define clr_I2C1ADDR3_GC                 SFRS=2;I2C1ADDR3&=0xFE

/**** P6  A7H  PAGE 2 ****/
#define set_P6_7                         SFRS=2;P6|=0x80
#define set_P6_6                         SFRS=2;P6|=0x40
#define set_P6_5                         SFRS=2;P6|=0x20
#define set_P6_4                         SFRS=2;P6|=0x10
#define set_P6_3                         SFRS=2;P6|=0x08
#define set_P6_2                         SFRS=2;P6|=0x04
#define set_P6_1                         SFRS=2;P6|=0x02
#define set_P6_0                         SFRS=2;P6|=0x01

#define clr_P6_7                         SFRS=2;P6&=0x7F
#define clr_P6_6                         SFRS=2;P6&=0xBF
#define clr_P6_5                         SFRS=2;P6&=0xDF
#define clr_P6_4                         SFRS=2;P6&=0xEF
#define clr_P6_3                         SFRS=2;P6&=0xF7
#define clr_P6_2                         SFRS=2;P6&=0xFB
#define clr_P6_1                         SFRS=2;P6&=0xFD
#define clr_P6_0                         SFRS=2;P6&=0xFE

/**** DMA3TSR  A9H  PAGE 2 ****/
#define set_DMA3TSR_ACT                  SFRS=2;DMA3TSR|=0x04
#define set_DMA3TSR_HDONE                SFRS=2;DMA3TSR|=0x02
#define set_DMA3TSR_FDONE                SFRS=2;DMA3TSR|=0x01

#define clr_DMA3TSR_ACT                  SFRS=2;DMA3TSR&=0xFB
#define clr_DMA3TSR_HDONE                SFRS=2;DMA3TSR&=0xFD
#define clr_DMA3TSR_FDONE                SFRS=2;DMA3TSR&=0xFE

/**** DMA3BAH  AAH  PAGE 2 ****/
/**** DMA2BAH  AAH  PAGE 2 ****/
/**** DMA3CR0  ABH  PAGE 2 ****/
#define set_DMA3CR0_PSSEL_3              SFRS=2;DMA3CR0|=0x80
#define set_DMA3CR0_PSSEL_2              SFRS=2;DMA3CR0|=0x40
#define set_DMA3CR0_PSSEL_1              SFRS=2;DMA3CR0|=0x20
#define set_DMA3CR0_PSSEL_0              SFRS=2;DMA3CR0|=0x10
#define set_DMA3CR0_HIE                  SFRS=2;DMA3CR0|=0x08
#define set_DMA3CR0_FIE                  SFRS=2;DMA3CR0|=0x04
#define set_DMA3CR0_RUN                  SFRS=2;DMA3CR0|=0x02
#define set_DMA3CR0_EN                   SFRS=2;DMA3CR0|=0x01

#define clr_DMA3CR0_PSSEL_3              SFRS=2;DMA3CR0&=0x7F
#define clr_DMA3CR0_PSSEL_2              SFRS=2;DMA3CR0&=0xBF
#define clr_DMA3CR0_PSSEL_1              SFRS=2;DMA3CR0&=0xDF
#define clr_DMA3CR0_PSSEL_0              SFRS=2;DMA3CR0&=0xEF
#define clr_DMA3CR0_HIE                  SFRS=2;DMA3CR0&=0xF7
#define clr_DMA3CR0_FIE                  SFRS=2;DMA3CR0&=0xFB
#define clr_DMA3CR0_RUN                  SFRS=2;DMA3CR0&=0xFD
#define clr_DMA3CR0_EN                   SFRS=2;DMA3CR0&=0xFE

/**** DMA2TSR  B1H  PAGE 2 ****/
#define set_DMA2TSR_ACT                  SFRS=2;DMA2TSR|=0x04
#define set_DMA2TSR_HDONE                SFRS=2;DMA2TSR|=0x02
#define set_DMA2TSR_FDONE                SFRS=2;DMA2TSR|=0x01

#define clr_DMA2TSR_ACT                  SFRS=2;DMA2TSR&=0xFB
#define clr_DMA2TSR_HDONE                SFRS=2;DMA2TSR&=0xFD
#define clr_DMA2TSR_FDONE                SFRS=2;DMA2TSR&=0xFE

/**** DMA2CR0  B3H  PAGE 2 ****/
#define set_DMA2CR0_PSSEL_3              SFRS=2;DMA2CR0|=0x80
#define set_DMA2CR0_PSSEL_2              SFRS=2;DMA2CR0|=0x40
#define set_DMA2CR0_PSSEL_1              SFRS=2;DMA2CR0|=0x20
#define set_DMA2CR0_PSSEL_0              SFRS=2;DMA2CR0|=0x10
#define set_DMA2CR0_HIE                  SFRS=2;DMA2CR0|=0x08
#define set_DMA2CR0_FIE                  SFRS=2;DMA2CR0|=0x04
#define set_DMA2CR0_RUN                  SFRS=2;DMA2CR0|=0x02
#define set_DMA2CR0_EN                   SFRS=2;DMA2CR0|=0x01

#define clr_DMA2CR0_PSSEL_3              SFRS=2;DMA2CR0&=0x7F
#define clr_DMA2CR0_PSSEL_2              SFRS=2;DMA2CR0&=0xBF
#define clr_DMA2CR0_PSSEL_1              SFRS=2;DMA2CR0&=0xDF
#define clr_DMA2CR0_PSSEL_0              SFRS=2;DMA2CR0&=0xEF
#define clr_DMA2CR0_HIE                  SFRS=2;DMA2CR0&=0xF7
#define clr_DMA2CR0_FIE                  SFRS=2;DMA2CR0&=0xFB
#define clr_DMA2CR0_RUN                  SFRS=2;DMA2CR0&=0xFD
#define clr_DMA2CR0_EN                   SFRS=2;DMA2CR0&=0xFE

/**** PWM2MD  BCH  PAGE 2 ****/
#define set_PWM2MD_PMD1                  SFRS=2;PWM2MD|=0x02
#define set_PWM2MD_PMD0                  SFRS=2;PWM2MD|=0x01

#define clr_PWM2MD_PMD1                  SFRS=2;PWM2MD&=0xFD
#define clr_PWM2MD_PMD0                  SFRS=2;PWM2MD&=0xFE

/**** PWM2MEN  BDH  PAGE 2 ****/
#define set_PWM2MEN_PMEN1                SFRS=2;PWM2MEN|=0x02
#define set_PWM2MEN_PMEN0                SFRS=2;PWM2MEN|=0x01

#define clr_PWM2MEN_PMEN1                SFRS=2;PWM2MEN&=0xFD
#define clr_PWM2MEN_PMEN0                SFRS=2;PWM2MEN&=0xFE

/**** PWM2CON0  C4H  PAGE 2 ****/
#define set_PWM2CON0_PWMRUN             SFRS=2;PWM2CON0|=0x80
#define set_PWM2CON0_LOAD                SFRS=2;PWM2CON0|=0x40
#define set_PWM2CON0_PWMF                SFRS=2;PWM2CON0|=0x20
#define set_PWM2CON0_CLRPWM              SFRS=2;PWM2CON0|=0x10

#define clr_PWM2CON0_PWM2RUN             SFRS=2;PWM2CON0&=0x7F
#define clr_PWM2CON0_LOAD                SFRS=2;PWM2CON0&=0xBF
#define clr_PWM2CON0_PWMF                SFRS=2;PWM2CON0&=0xDF
#define clr_PWM2CON0_CLRPWM              SFRS=2;PWM2CON0&=0xEF

/**** PWM2CON1  C5H  PAGE 2 ****/
#define set_PWM2CON1_PWMMOD_1            SFRS=2;PWM2CON1|=0x80
#define set_PWM2CON1_PWMMOD_0            SFRS=2;PWM2CON1|=0x40
#define set_PWM2CON1_GP                  SFRS=2;PWM2CON1|=0x20
#define set_PWM2CON1_PWMTYP              SFRS=2;PWM2CON1|=0x10
#define set_PWM2CON1_PWMDIV_2            SFRS=2;PWM2CON1|=0x04
#define set_PWM2CON1_PWMDIV_1            SFRS=2;PWM2CON1|=0x02
#define set_PWM2CON1_PWMDIV_0            SFRS=2;PWM2CON1|=0x01

#define clr_PWM2CON1_PWMMOD_1            SFRS=2;PWM2CON1&=0x7F
#define clr_PWM2CON1_PWMMOD_0            SFRS=2;PWM2CON1&=0xBF
#define clr_PWM2CON1_GP                  SFRS=2;PWM2CON1&=0xDF
#define clr_PWM2CON1_PWMTYP              SFRS=2;PWM2CON1&=0xEF
#define clr_PWM2CON1_PWMDIV_2            SFRS=2;PWM2CON1&=0xFB
#define clr_PWM2CON1_PWMDIV_1            SFRS=2;PWM2CON1&=0xFD
#define clr_PWM2CON1_PWMDIV_0            SFRS=2;PWM2CON1&=0xFE

/**** PWM2INTC  C6H  PAGE 2 ****/
#define set_PWM2INTC_INTTYP1             SFRS=2;PWM2INTC|=0x20
#define set_PWM2INTC_INTTYP0             SFRS=2;PWM2INTC|=0x10
#define set_PWM2INTC_INTSEL2             SFRS=2;PWM2INTC|=0x04
#define set_PWM2INTC_INTSEL1             SFRS=2;PWM2INTC|=0x02
#define set_PWM2INTC_INTSEL0             SFRS=2;PWM2INTC|=0x01

#define clr_PWM2INTC_INTTYP1             SFRS=2;PWM2INTC&=0xDF
#define clr_PWM2INTC_INTTYP0             SFRS=2;PWM2INTC&=0xEF
#define clr_PWM2INTC_INTSEL2             SFRS=2;PWM2INTC&=0xFB
#define clr_PWM2INTC_INTSEL1             SFRS=2;PWM2INTC&=0xFD
#define clr_PWM2INTC_INTSEL0             SFRS=2;PWM2INTC&=0xFE

/**** PWM3MD  CCH  PAGE 2 ****/
#define set_PWM3MD_PMD1                  SFRS=2;PWM3MD|=0x02
#define set_PWM3MD_PMD0                  SFRS=2;PWM3MD|=0x01

#define clr_PWM3MD_PMD1                  SFRS=2;PWM3MD&=0xFD
#define clr_PWM3MD_PMD0                  SFRS=2;PWM3MD&=0xFE

/**** PWM3MEN  CDH  PAGE 2 ****/
#define set_PWM3MEN_PMEN1                SFRS=2;PWM3MEN|=0x02
#define set_PWM3MEN_PMEN0                SFRS=2;PWM3MEN|=0x01

#define clr_PWM3MEN_PMEN1                SFRS=2;PWM3MEN&=0xFD
#define clr_PWM3MEN_PMEN0                SFRS=2;PWM3MEN&=0xFE

/**** AINDIDS1  CEH  PAGE 2 ****/
#define set_AINDIDS1_AIN15DIDS           SFRS=2;AINDIDS1|=0x80
#define set_AINDIDS1_AIN14DIDS           SFRS=2;AINDIDS1|=0x40
#define set_AINDIDS1_AIN13DIDS           SFRS=2;AINDIDS1|=0x20
#define set_AINDIDS1_AIN12DIDS           SFRS=2;AINDIDS1|=0x10
#define set_AINDIDS1_AIN11DIDS           SFRS=2;AINDIDS1|=0x08
#define set_AINDIDS1_AIN10DIDS           SFRS=2;AINDIDS1|=0x04

#define clr_AINDIDS1_AIN15DIDS           SFRS=2;AINDIDS1&=0x7F
#define clr_AINDIDS1_AIN14DIDS           SFRS=2;AINDIDS1&=0xBF
#define clr_AINDIDS1_AIN13DIDS           SFRS=2;AINDIDS1&=0xDF
#define clr_AINDIDS1_AIN12DIDS           SFRS=2;AINDIDS1&=0xEF
#define clr_AINDIDS1_AIN11DIDS           SFRS=2;AINDIDS1&=0xF7
#define clr_AINDIDS1_AIN10DIDS           SFRS=2;AINDIDS1&=0xFB

/**** I2C0ADDRM  CFH  PAGE 2 ****/
#define set_I2C0ADDRM_I2C0ADDRM          SFRS=2;I2C0ADDRM|=0x80
#define set_I2C0ADDRM_00000000b          SFRS=2;I2C0ADDRM|=0x40

#define clr_I2C0ADDRM_I2C0ADDRM          SFRS=2;I2C0ADDRM&=0x7F
#define clr_I2C0ADDRM_00000000b          SFRS=2;I2C0ADDRM&=0xBF

/**** PWM3CON0  D4H  PAGE 2 ****/
#define set_PWM3CON0_PWMRUN             SFRS=2;PWM3CON0|=0x80
#define set_PWM3CON0_LOAD                SFRS=2;PWM3CON0|=0x40
#define set_PWM3CON0_PWMF                SFRS=2;PWM3CON0|=0x20
#define set_PWM3CON0_CLRPWM              SFRS=2;PWM3CON0|=0x10

#define clr_PWM3CON0_PWM3RUN             SFRS=2;PWM3CON0&=0x7F
#define clr_PWM3CON0_LOAD                SFRS=2;PWM3CON0&=0xBF
#define clr_PWM3CON0_PWMF                SFRS=2;PWM3CON0&=0xDF
#define clr_PWM3CON0_CLRPWM              SFRS=2;PWM3CON0&=0xEF

/**** PWM3CON1  D5H  PAGE 2 ****/
#define set_PWM3CON1_PWMMOD_1            SFRS=2;PWM3CON1|=0x80
#define set_PWM3CON1_PWMMOD_0            SFRS=2;PWM3CON1|=0x40
#define set_PWM3CON1_GP                  SFRS=2;PWM3CON1|=0x20
#define set_PWM3CON1_PWMTYP              SFRS=2;PWM3CON1|=0x10
#define set_PWM3CON1_PWMDIV_2            SFRS=2;PWM3CON1|=0x04
#define set_PWM3CON1_PWMDIV_1            SFRS=2;PWM3CON1|=0x02
#define set_PWM3CON1_PWMDIV_0            SFRS=2;PWM3CON1|=0x01

#define clr_PWM3CON1_PWMMOD_1            SFRS=2;PWM3CON1&=0x7F
#define clr_PWM3CON1_PWMMOD_0            SFRS=2;PWM3CON1&=0xBF
#define clr_PWM3CON1_GP                  SFRS=2;PWM3CON1&=0xDF
#define clr_PWM3CON1_PWMTYP              SFRS=2;PWM3CON1&=0xEF
#define clr_PWM3CON1_PWMDIV_2            SFRS=2;PWM3CON1&=0xFB
#define clr_PWM3CON1_PWMDIV_1            SFRS=2;PWM3CON1&=0xFD
#define clr_PWM3CON1_PWMDIV_0            SFRS=2;PWM3CON1&=0xFE

/**** PWM3INTC  D6H  PAGE 2 ****/
#define set_PWM3INTC_INTTYP1             SFRS=2;PWM3INTC|=0x20
#define set_PWM3INTC_INTTYP0             SFRS=2;PWM3INTC|=0x10
#define set_PWM3INTC_INTSEL2             SFRS=2;PWM3INTC|=0x04
#define set_PWM3INTC_INTSEL1             SFRS=2;PWM3INTC|=0x02
#define set_PWM3INTC_INTSEL0             SFRS=2;PWM3INTC|=0x01

#define clr_PWM3INTC_INTTYP1             SFRS=2;PWM3INTC&=0xDF
#define clr_PWM3INTC_INTTYP0             SFRS=2;PWM3INTC&=0xEF
#define clr_PWM3INTC_INTSEL2             SFRS=2;PWM3INTC&=0xFB
#define clr_PWM3INTC_INTSEL1             SFRS=2;PWM3INTC&=0xFD
#define clr_PWM3INTC_INTSEL0             SFRS=2;PWM3INTC&=0xFE

/**** I2C1ADDRM  D7H  PAGE 2 ****/
#define set_I2C1ADDRM_I2C1ADDRM          SFRS=2;I2C1ADDRM|=0x80
#define set_I2C1ADDRM_00000000b          SFRS=2;I2C1ADDRM|=0x40

#define clr_I2C1ADDRM_I2C1ADDRM          SFRS=2;I2C1ADDRM&=0x7F
#define clr_I2C1ADDRM_00000000b          SFRS=2;I2C1ADDRM&=0xBF

/**** SC1ETURD1  DCH  PAGE 2 ****/
#define set_SC1ETURD1_CMPEN              SFRS=2;SC1ETURD1|=0x80
#define set_SC1ETURD1_SCDIV_2            SFRS=2;SC1ETURD1|=0x40
#define set_SC1ETURD1_SCDIV_1            SFRS=2;SC1ETURD1|=0x20
#define set_SC1ETURD1_SCDIV_0            SFRS=2;SC1ETURD1|=0x10
#define set_SC1ETURD1_ETURDIV_11         SFRS=2;SC1ETURD1|=0x08
#define set_SC1ETURD1_ETURDIV_10         SFRS=2;SC1ETURD1|=0x04
#define set_SC1ETURD1_ETURDIV_9          SFRS=2;SC1ETURD1|=0x02
#define set_SC1ETURD1_ETURDIV_8          SFRS=2;SC1ETURD1|=0x01

#define clr_SC1ETURD1_CMPEN              SFRS=2;SC1ETURD1&=0x7F
#define clr_SC1ETURD1_SCDIV_2            SFRS=2;SC1ETURD1&=0xBF
#define clr_SC1ETURD1_SCDIV_1            SFRS=2;SC1ETURD1&=0xDF
#define clr_SC1ETURD1_SCDIV_0            SFRS=2;SC1ETURD1&=0xEF
#define clr_SC1ETURD1_ETURDIV_11         SFRS=2;SC1ETURD1&=0xF7
#define clr_SC1ETURD1_ETURDIV_10         SFRS=2;SC1ETURD1&=0xFB
#define clr_SC1ETURD1_ETURDIV_9          SFRS=2;SC1ETURD1&=0xFD
#define clr_SC1ETURD1_ETURDIV_8          SFRS=2;SC1ETURD1&=0xFE

/**** SC1IE  DDH  PAGE 2 ****/
#define set_SC1IE_ACERRIEN               SFRS=2;SC1IE|=0x10
#define set_SC1IE_BGTIEN                 SFRS=2;SC1IE|=0x08
#define set_SC1IE_TERRIEN                SFRS=2;SC1IE|=0x04
#define set_SC1IE_TBEIEN                 SFRS=2;SC1IE|=0x02
#define set_SC1IE_RDAIEN                 SFRS=2;SC1IE|=0x01

#define clr_SC1IE_ACERRIEN               SFRS=2;SC1IE&=0xEF
#define clr_SC1IE_BGTIEN                 SFRS=2;SC1IE&=0xF7
#define clr_SC1IE_TERRIEN                SFRS=2;SC1IE&=0xFB
#define clr_SC1IE_TBEIEN                 SFRS=2;SC1IE&=0xFD
#define clr_SC1IE_RDAIEN                 SFRS=2;SC1IE&=0xFE

/**** SC1IS  DEH  PAGE 2 ****/
#define set_SC1IS_Tx_Er                  SFRS=2;SC1IS|=0x20
#define set_SC1IS_ACERRIF                SFRS=2;SC1IS|=0x10
#define set_SC1IS_BGTIF                  SFRS=2;SC1IS|=0x08
#define set_SC1IS_TERRIF                 SFRS=2;SC1IS|=0x04
#define set_SC1IS_TBEIF                  SFRS=2;SC1IS|=0x02
#define set_SC1IS_RDAIF                  SFRS=2;SC1IS|=0x01

#define clr_SC1IS_Tx_Er                  SFRS=2;SC1IS&=0xDF
#define clr_SC1IS_ACERRIF                SFRS=2;SC1IS&=0xEF
#define clr_SC1IS_BGTIF                  SFRS=2;SC1IS&=0xF7
#define clr_SC1IS_TERRIF                 SFRS=2;SC1IS&=0xFB
#define clr_SC1IS_TBEIF                  SFRS=2;SC1IS&=0xFD
#define clr_SC1IS_RDAIF                  SFRS=2;SC1IS&=0xFE

/**** SC1TSR  DFH  PAGE 2 ****/
#define set_SC1TSR_ACT                   SFRS=2;SC1TSR|=0x80
#define set_SC1TSR_BEF                   SFRS=2;SC1TSR|=0x40
#define set_SC1TSR_FEF                   SFRS=2;SC1TSR|=0x20
#define set_SC1TSR_PEF                   SFRS=2;SC1TSR|=0x10
#define set_SC1TSR_TXEMPTY               SFRS=2;SC1TSR|=0x08
#define set_SC1TSR_TXOV                  SFRS=2;SC1TSR|=0x04
#define set_SC1TSR_RXEMPTY               SFRS=2;SC1TSR|=0x02
#define set_SC1TSR_RXOV                  SFRS=2;SC1TSR|=0x01

#define clr_SC1TSR_ACT                   SFRS=2;SC1TSR&=0x7F
#define clr_SC1TSR_BEF                   SFRS=2;SC1TSR&=0xBF
#define clr_SC1TSR_FEF                   SFRS=2;SC1TSR&=0xDF
#define clr_SC1TSR_PEF                   SFRS=2;SC1TSR&=0xEF
#define clr_SC1TSR_TXEMPTY               SFRS=2;SC1TSR&=0xF7
#define clr_SC1TSR_TXOV                  SFRS=2;SC1TSR&=0xFB
#define clr_SC1TSR_RXEMPTY               SFRS=2;SC1TSR&=0xFD
#define clr_SC1TSR_RXOV                  SFRS=2;SC1TSR&=0xFE

/**** P5MF32  E1H  PAGE 2 ****/
/**** P5MF54  E2H  PAGE 2 ****/
/**** P5MF76  E3H  PAGE 2 ****/
/**** BRCTRIM  E4H  PAGE 2 ****/
#define set_BRCTRIM_IBOOST_2             SFRS=2;BRCTRIM|=0x80
#define set_BRCTRIM_IBOOST_1             SFRS=2;BRCTRIM|=0x40
#define set_BRCTRIM_IBOOST_0             SFRS=2;BRCTRIM|=0x20
#define set_BRCTRIM_BRCTRIM_4            SFRS=2;BRCTRIM|=0x10
#define set_BRCTRIM_BRCTRIM_3            SFRS=2;BRCTRIM|=0x08
#define set_BRCTRIM_BRCTRIM_2            SFRS=2;BRCTRIM|=0x04
#define set_BRCTRIM_BRCTRIM_1            SFRS=2;BRCTRIM|=0x02
#define set_BRCTRIM_BRCTRIM_0            SFRS=2;BRCTRIM|=0x01

#define clr_BRCTRIM_IBOOST_2             SFRS=2;BRCTRIM&=0x7F
#define clr_BRCTRIM_IBOOST_1             SFRS=2;BRCTRIM&=0xBF
#define clr_BRCTRIM_IBOOST_0             SFRS=2;BRCTRIM&=0xDF
#define clr_BRCTRIM_BRCTRIM_4            SFRS=2;BRCTRIM&=0xEF
#define clr_BRCTRIM_BRCTRIM_3            SFRS=2;BRCTRIM&=0xF7
#define clr_BRCTRIM_BRCTRIM_2            SFRS=2;BRCTRIM&=0xFB
#define clr_BRCTRIM_BRCTRIM_1            SFRS=2;BRCTRIM&=0xFD
#define clr_BRCTRIM_BRCTRIM_0            SFRS=2;BRCTRIM&=0xFE

/**** ADCCAL  E5H  PAGE 2 ****/
#define set_ADCCAL_CALI_EN               SFRS=2;ADCCAL|=0x80
#define set_ADCCAL_SIGN_2                SFRS=2;ADCCAL|=0x40
#define set_ADCCAL_SIGN_1                SFRS=2;ADCCAL|=0x20
#define set_ADCCAL_SIGN_0                SFRS=2;ADCCAL|=0x10
#define set_ADCCAL_ADCCALI_3             SFRS=2;ADCCAL|=0x08
#define set_ADCCAL_ADCCALI_2             SFRS=2;ADCCAL|=0x04
#define set_ADCCAL_ADCCALI_1             SFRS=2;ADCCAL|=0x02
#define set_ADCCAL_ADCCALI_0             SFRS=2;ADCCAL|=0x01

#define clr_ADCCAL_CALI_EN               SFRS=2;ADCCAL&=0x7F
#define clr_ADCCAL_SIGN_2                SFRS=2;ADCCAL&=0xBF
#define clr_ADCCAL_SIGN_1                SFRS=2;ADCCAL&=0xDF
#define clr_ADCCAL_SIGN_0                SFRS=2;ADCCAL&=0xEF
#define clr_ADCCAL_ADCCALI_3             SFRS=2;ADCCAL&=0xF7
#define clr_ADCCAL_ADCCALI_2             SFRS=2;ADCCAL&=0xFB
#define clr_ADCCAL_ADCCALI_1             SFRS=2;ADCCAL&=0xFD
#define clr_ADCCAL_ADCCALI_0             SFRS=2;ADCCAL&=0xFE

/**** SC1CR0  E6H  PAGE 2 ****/
#define set_SC1CR0_NSB                   SFRS=2;SC1CR0|=0x80
#define set_SC1CR0_T                     SFRS=2;SC1CR0|=0x40
#define set_SC1CR0_RXBGTEN               SFRS=2;SC1CR0|=0x20
#define set_SC1CR0_CONSEL                SFRS=2;SC1CR0|=0x10
#define set_SC1CR0_AUTOCEN               SFRS=2;SC1CR0|=0x08
#define set_SC1CR0_TXOFF                 SFRS=2;SC1CR0|=0x04
#define set_SC1CR0_RXOFF                 SFRS=2;SC1CR0|=0x02
#define set_SC1CR0_SCEN                  SFRS=2;SC1CR0|=0x01

#define clr_SC1CR0_NSB                   SFRS=2;SC1CR0&=0x7F
#define clr_SC1CR0_T                     SFRS=2;SC1CR0&=0xBF
#define clr_SC1CR0_RXBGTEN               SFRS=2;SC1CR0&=0xDF
#define clr_SC1CR0_CONSEL                SFRS=2;SC1CR0&=0xEF
#define clr_SC1CR0_AUTOCEN               SFRS=2;SC1CR0&=0xF7
#define clr_SC1CR0_TXOFF                 SFRS=2;SC1CR0&=0xFB
#define clr_SC1CR0_RXOFF                 SFRS=2;SC1CR0&=0xFD
#define clr_SC1CR0_SCEN                  SFRS=2;SC1CR0&=0xFE

/**** SC1CR1  E7H  PAGE 2 ****/
#define set_SC1CR1_OPE                   SFRS=2;SC1CR1|=0x80
#define set_SC1CR1_PBOFF                 SFRS=2;SC1CR1|=0x40
#define set_SC1CR1_WLS1                  SFRS=2;SC1CR1|=0x20
#define set_SC1CR1_WLS0                  SFRS=2;SC1CR1|=0x10
#define set_SC1CR1_TXDMAEN               SFRS=2;SC1CR1|=0x08
#define set_SC1CR1_RXDMAEN               SFRS=2;SC1CR1|=0x04
#define set_SC1CR1_CLKKEEP               SFRS=2;SC1CR1|=0x02
#define set_SC1CR1_UARTEN                SFRS=2;SC1CR1|=0x01

#define clr_SC1CR1_OPE                   SFRS=2;SC1CR1&=0x7F
#define clr_SC1CR1_PBOFF                 SFRS=2;SC1CR1&=0xBF
#define clr_SC1CR1_WLS1                  SFRS=2;SC1CR1&=0xDF
#define clr_SC1CR1_WLS0                  SFRS=2;SC1CR1&=0xEF
#define clr_SC1CR1_TXDMAEN               SFRS=2;SC1CR1&=0xF7
#define clr_SC1CR1_RXDMAEN               SFRS=2;SC1CR1&=0xFB
#define clr_SC1CR1_CLKKEEP               SFRS=2;SC1CR1&=0xFD
#define clr_SC1CR1_UARTEN                SFRS=2;SC1CR1&=0xFE

/**** P3MF54  E9H  PAGE 2 ****/
/**** P3MF76  EAH  PAGE 2 ****/
/**** P4MF10  EBH  PAGE 2 ****/
/**** P4MF32  ECH  PAGE 2 ****/
/**** P4MF54  EDH  PAGE 2 ****/
/**** P4MF76  EEH  PAGE 2 ****/
/**** P5MF10  EFH  PAGE 2 ****/
/**** P1MF76  F1H  PAGE 2 ****/
/**** P2MF10  F2H  PAGE 2 ****/
/**** P2MF32  F3H  PAGE 2 ****/
/**** P2MF54  F4H  PAGE 2 ****/
/**** P2MF76  F5H  PAGE 2 ****/
/**** P3MF10  F6H  PAGE 2 ****/
/**** P3MF32  F7H  PAGE 2 ****/
/**** P0MF10  F9H  PAGE 2 ****/
/**** P0MF32  FAH  PAGE 2 ****/
/**** P0MF54  FBH  PAGE 2 ****/
/**** P0MF76  FCH  PAGE 2 ****/
/**** P1MF10  FDH  PAGE 2 ****/
/**** P1MF32  FEH  PAGE 2 ****/
/**** P1MF54  FFH  PAGE 2 ****/


/********SFR PAGE 3*************/
/**** DMA0CR1  8AH  PAGE 3 ****/
#define set_DMA0CR1_XOROUT               SFRS=3;DMA0CR1|=0x08
#define set_DMA0CR1_REFOUT               SFRS=3;DMA0CR1|=0x04
#define set_DMA0CR1_REFIN                SFRS=3;DMA0CR1|=0x02
#define set_DMA0CR1_CRCEN                SFRS=3;DMA0CR1|=0x01

#define clr_DMA0CR1_XOROUT               SFRS=3;DMA0CR1&=0xF7
#define clr_DMA0CR1_REFOUT               SFRS=3;DMA0CR1&=0xFB
#define clr_DMA0CR1_REFIN                SFRS=3;DMA0CR1&=0xFD
#define clr_DMA0CR1_CRCEN                SFRS=3;DMA0CR1&=0xFE

/**** DMA1CR1  8BH  PAGE 3 ****/
#define set_DMA1CR1_XOROUT               SFRS=3;DMA1CR1|=0x08
#define set_DMA1CR1_REFOUT               SFRS=3;DMA1CR1|=0x04
#define set_DMA1CR1_REFIN                SFRS=3;DMA1CR1|=0x02
#define set_DMA1CR1_CRCEN                SFRS=3;DMA1CR1|=0x01

#define clr_DMA1CR1_XOROUT               SFRS=3;DMA1CR1&=0xF7
#define clr_DMA1CR1_REFOUT               SFRS=3;DMA1CR1&=0xFB
#define clr_DMA1CR1_REFIN                SFRS=3;DMA1CR1&=0xFD
#define clr_DMA1CR1_CRCEN                SFRS=3;DMA1CR1&=0xFE

/**** DMA2CR1  8CH  PAGE 3 ****/
#define set_DMA2CR1_XOROUT               SFRS=3;DMA2CR1|=0x08
#define set_DMA2CR1_REFOUT               SFRS=3;DMA2CR1|=0x04
#define set_DMA2CR1_REFIN                SFRS=3;DMA2CR1|=0x02
#define set_DMA2CR1_CRCEN                SFRS=3;DMA2CR1|=0x01

#define clr_DMA2CR1_XOROUT               SFRS=3;DMA2CR1&=0xF7
#define clr_DMA2CR1_REFOUT               SFRS=3;DMA2CR1&=0xFB
#define clr_DMA2CR1_REFIN                SFRS=3;DMA2CR1&=0xFD
#define clr_DMA2CR1_CRCEN                SFRS=3;DMA2CR1&=0xFE

/**** DMA3CR1  8DH  PAGE 3 ****/
#define set_DMA3CR1_XOROUT               SFRS=3;DMA3CR1|=0x08
#define set_DMA3CR1_REFOUT               SFRS=3;DMA3CR1|=0x04
#define set_DMA3CR1_REFIN                SFRS=3;DMA3CR1|=0x02
#define set_DMA3CR1_CRCEN                SFRS=3;DMA3CR1|=0x01

#define clr_DMA3CR1_XOROUT               SFRS=3;DMA3CR1&=0xF7
#define clr_DMA3CR1_REFOUT               SFRS=3;DMA3CR1&=0xFB
#define clr_DMA3CR1_REFIN                SFRS=3;DMA3CR1&=0xFD
#define clr_DMA3CR1_CRCEN                SFRS=3;DMA3CR1&=0xFE

/**** WDCONH  99H  PAGE 3 TA protect register ****/
#define set_WDCONH_WDPS                  SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCONH|=0x01;EA=BIT_TMP

#define clr_WDCONH_WDPS                  SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;WDCONH&=0xFE;EA=BIT_TMP

/**** RTCINIT  A1H  PAGE 3 ****/

/**** RTCRWEN  A2H  PAGE 3 ****/
#define set_RTCRWEN_FADJTG               SFRS=3;RTCRWEN|=0x02
#define set_RTCRWEN_RWENF                SFRS=3;RTCRWEN|=0x01

#define clr_RTCRWEN_FADJTG               SFRS=3;RTCRWEN&=0xFD
#define clr_RTCRWEN_RWENF                SFRS=3;RTCRWEN&=0xFE

/**** RTCCLKSEL  A3H  PAGE 3 ****/
#define set_RTCCLKSEL_C32KS              SFRS=3;RTCCLKSEL|=0x01

#define clr_RTCCLKSEL_C32KS              SFRS=3;RTCCLKSEL&=0xFE

/**** RTCFREQADJ0  A4H  PAGE 3 ****/
#define set_RTCFREQADJ0_FRACTION         SFRS=3;RTCFREQADJ0|=0x20

#define clr_RTCFREQADJ0_FRACTION         SFRS=3;RTCFREQADJ0&=0xDF

/**** RTCFREQADJ1  A5H  PAGE 3 TA protect register ****/
#define set_RTCFREQADJ1_INTEGER          SFRS=3;RTCFREQADJ1|=0x40
#define set_RTCFREQADJ1_00010000b        SFRS=3;RTCFREQADJ1|=0x20

#define clr_RTCFREQADJ1_INTEGER          SFRS=3;RTCFREQADJ1&=0xBF
#define clr_RTCFREQADJ1_00010000b        SFRS=3;RTCFREQADJ1&=0xDF

/**** RTCINTEN  A6H  PAGE 3 ****/
#define set_RTCINTEN_TICKIEN             SFRS=3;RTCINTEN|=0x02
#define set_RTCINTEN_ALMIEN              SFRS=3;RTCINTEN|=0x01

#define clr_RTCINTEN_TICKIEN             SFRS=3;RTCINTEN&=0xFD
#define clr_RTCINTEN_ALMIEN              SFRS=3;RTCINTEN&=0xFE

/**** RTCINTSTS  A7H  PAGE 3 ****/
#define set_RTCINTSTS_TICKIF             SFRS=3;RTCINTSTS|=0x02
#define set_RTCINTSTS_ALMIF              SFRS=3;RTCINTSTS|=0x01

#define clr_RTCINTSTS_TICKIF             SFRS=3;RTCINTSTS&=0xFD
#define clr_RTCINTSTS_ALMIF              SFRS=3;RTCINTSTS&=0xFE

/**** RTCTIMESEC  A9H  PAGE 3 ****/
#define set_RTCTIMESEC_TENSEC_2          SFRS=3;RTCTIMESEC|=0x40
#define set_RTCTIMESEC_TENSEC_1          SFRS=3;RTCTIMESEC|=0x20
#define set_RTCTIMESEC_TENSEC_0          SFRS=3;RTCTIMESEC|=0x10
#define set_RTCTIMESEC_SEC_3             SFRS=3;RTCTIMESEC|=0x08
#define set_RTCTIMESEC_SEC_2             SFRS=3;RTCTIMESEC|=0x04
#define set_RTCTIMESEC_SEC_1             SFRS=3;RTCTIMESEC|=0x02
#define set_RTCTIMESEC_SEC_0             SFRS=3;RTCTIMESEC|=0x01

#define clr_RTCTIMESEC_TENSEC_2          SFRS=3;RTCTIMESEC&=0xBF
#define clr_RTCTIMESEC_TENSEC_1          SFRS=3;RTCTIMESEC&=0xDF
#define clr_RTCTIMESEC_TENSEC_0          SFRS=3;RTCTIMESEC&=0xEF
#define clr_RTCTIMESEC_SEC_3             SFRS=3;RTCTIMESEC&=0xF7
#define clr_RTCTIMESEC_SEC_2             SFRS=3;RTCTIMESEC&=0xFB
#define clr_RTCTIMESEC_SEC_1             SFRS=3;RTCTIMESEC&=0xFD
#define clr_RTCTIMESEC_SEC_0             SFRS=3;RTCTIMESEC&=0xFE

/**** RTCTIMEMIN  AAH  PAGE 3 ****/
#define set_RTCTIMEMIN_TENMIN_2          SFRS=3;RTCTIMEMIN|=0x40
#define set_RTCTIMEMIN_TENMIN_1          SFRS=3;RTCTIMEMIN|=0x20
#define set_RTCTIMEMIN_TENMIN_0          SFRS=3;RTCTIMEMIN|=0x10
#define set_RTCTIMEMIN_MIN_3             SFRS=3;RTCTIMEMIN|=0x08
#define set_RTCTIMEMIN_MIN_2             SFRS=3;RTCTIMEMIN|=0x04
#define set_RTCTIMEMIN_MIN_1             SFRS=3;RTCTIMEMIN|=0x02
#define set_RTCTIMEMIN_MIN_0             SFRS=3;RTCTIMEMIN|=0x01

#define clr_RTCTIMEMIN_TENMIN_2          SFRS=3;RTCTIMEMIN&=0xBF
#define clr_RTCTIMEMIN_TENMIN_1          SFRS=3;RTCTIMEMIN&=0xDF
#define clr_RTCTIMEMIN_TENMIN_0          SFRS=3;RTCTIMEMIN&=0xEF
#define clr_RTCTIMEMIN_MIN_3             SFRS=3;RTCTIMEMIN&=0xF7
#define clr_RTCTIMEMIN_MIN_2             SFRS=3;RTCTIMEMIN&=0xFB
#define clr_RTCTIMEMIN_MIN_1             SFRS=3;RTCTIMEMIN&=0xFD
#define clr_RTCTIMEMIN_MIN_0             SFRS=3;RTCTIMEMIN&=0xFE

/**** RTCTIMEHR  ABH  PAGE 3 ****/
#define set_RTCTIMEHR_TENHR_1            SFRS=3;RTCTIMEHR|=0x20
#define set_RTCTIMEHR_TENHR_0            SFRS=3;RTCTIMEHR|=0x10
#define set_RTCTIMEHR_HR_3               SFRS=3;RTCTIMEHR|=0x08
#define set_RTCTIMEHR_HR_2               SFRS=3;RTCTIMEHR|=0x04
#define set_RTCTIMEHR_HR_1               SFRS=3;RTCTIMEHR|=0x02
#define set_RTCTIMEHR_HR_0               SFRS=3;RTCTIMEHR|=0x01

#define clr_RTCTIMEHR_TENHR_1            SFRS=3;RTCTIMEHR&=0xDF
#define clr_RTCTIMEHR_TENHR_0            SFRS=3;RTCTIMEHR&=0xEF
#define clr_RTCTIMEHR_HR_3               SFRS=3;RTCTIMEHR&=0xF7
#define clr_RTCTIMEHR_HR_2               SFRS=3;RTCTIMEHR&=0xFB
#define clr_RTCTIMEHR_HR_1               SFRS=3;RTCTIMEHR&=0xFD
#define clr_RTCTIMEHR_HR_0               SFRS=3;RTCTIMEHR&=0xFE

/**** RTCTIMEHZ  ACH  PAGE 3 ****/
#define set_RTCTIMEHZ_HZCNT              SFRS=3;RTCTIMEHZ|=0x40

#define clr_RTCTIMEHZ_HZCNT              SFRS=3;RTCTIMEHZ&=0xBF

/**** RTCCALDAY  ADH  PAGE 3 ****/
#define set_RTCCALDAY_TENDAY             SFRS=3;RTCCALDAY|=0x20
#define set_RTCCALDAY_DAY                SFRS=3;RTCCALDAY|=0x08

#define clr_RTCCALDAY_TENDAY             SFRS=3;RTCCALDAY&=0xDF
#define clr_RTCCALDAY_DAY                SFRS=3;RTCCALDAY&=0xF7

/**** RTCCALMON  AEH  PAGE 3 ****/
#define set_RTCCALMON_TENMON_1           SFRS=3;RTCCALMON|=0x20
#define set_RTCCALMON_TENMON_0           SFRS=3;RTCCALMON|=0x10
#define set_RTCCALMON_MON_3              SFRS=3;RTCCALMON|=0x08
#define set_RTCCALMON_MON_2              SFRS=3;RTCCALMON|=0x04
#define set_RTCCALMON_MON_1              SFRS=3;RTCCALMON|=0x02
#define set_RTCCALMON_MON_0              SFRS=3;RTCCALMON|=0x01

#define clr_RTCCALMON_TENMON_1           SFRS=3;RTCCALMON&=0xDF
#define clr_RTCCALMON_TENMON_0           SFRS=3;RTCCALMON&=0xEF
#define clr_RTCCALMON_MON_3              SFRS=3;RTCCALMON&=0xF7
#define clr_RTCCALMON_MON_2              SFRS=3;RTCCALMON&=0xFB
#define clr_RTCCALMON_MON_1              SFRS=3;RTCCALMON&=0xFD
#define clr_RTCCALMON_MON_0              SFRS=3;RTCCALMON&=0xFE

/**** RTCCALYEAR  AFH  PAGE 3 ****/
#define set_RTCCALYEAR_TENYEAR           SFRS=3;RTCCALYEAR|=0x80
#define set_RTCCALYEAR_YEAR              SFRS=3;RTCCALYEAR|=0x40
#define set_RTCCALYEAR_00010101b         SFRS=3;RTCCALYEAR|=0x20

#define clr_RTCCALYEAR_TENYEAR           SFRS=3;RTCCALYEAR&=0x7F
#define clr_RTCCALYEAR_YEAR              SFRS=3;RTCCALYEAR&=0xBF
#define clr_RTCCALYEAR_00010101b         SFRS=3;RTCCALYEAR&=0xDF

/**** RTCTALMSEC  B1H  PAGE 3 ****/
#define set_RTCTALMSEC_TENSEC_2          SFRS=3;RTCTALMSEC|=0x40
#define set_RTCTALMSEC_TENSEC_1          SFRS=3;RTCTALMSEC|=0x20
#define set_RTCTALMSEC_TENSEC_0          SFRS=3;RTCTALMSEC|=0x10
#define set_RTCTALMSEC_SEC_3             SFRS=3;RTCTALMSEC|=0x08
#define set_RTCTALMSEC_SEC_2             SFRS=3;RTCTALMSEC|=0x04
#define set_RTCTALMSEC_SEC_1             SFRS=3;RTCTALMSEC|=0x02
#define set_RTCTALMSEC_SEC_0             SFRS=3;RTCTALMSEC|=0x01

#define clr_RTCTALMSEC_TENSEC_2          SFRS=3;RTCTALMSEC&=0xBF
#define clr_RTCTALMSEC_TENSEC_1          SFRS=3;RTCTALMSEC&=0xDF
#define clr_RTCTALMSEC_TENSEC_0          SFRS=3;RTCTALMSEC&=0xEF
#define clr_RTCTALMSEC_SEC_3             SFRS=3;RTCTALMSEC&=0xF7
#define clr_RTCTALMSEC_SEC_2             SFRS=3;RTCTALMSEC&=0xFB
#define clr_RTCTALMSEC_SEC_1             SFRS=3;RTCTALMSEC&=0xFD
#define clr_RTCTALMSEC_SEC_0             SFRS=3;RTCTALMSEC&=0xFE

/**** RTCTALMMIN  B2H  PAGE 3 ****/
#define set_RTCTALMMIN_TENMIN_2          SFRS=3;RTCTALMMIN|=0x40
#define set_RTCTALMMIN_TENMIN_1          SFRS=3;RTCTALMMIN|=0x20
#define set_RTCTALMMIN_TENMIN_0          SFRS=3;RTCTALMMIN|=0x10
#define set_RTCTALMMIN_MIN_3             SFRS=3;RTCTALMMIN|=0x08
#define set_RTCTALMMIN_MIN_2             SFRS=3;RTCTALMMIN|=0x04
#define set_RTCTALMMIN_MIN_1             SFRS=3;RTCTALMMIN|=0x02
#define set_RTCTALMMIN_MIN_0             SFRS=3;RTCTALMMIN|=0x01

#define clr_RTCTALMMIN_TENMIN_2          SFRS=3;RTCTALMMIN&=0xBF
#define clr_RTCTALMMIN_TENMIN_1          SFRS=3;RTCTALMMIN&=0xDF
#define clr_RTCTALMMIN_TENMIN_0          SFRS=3;RTCTALMMIN&=0xEF
#define clr_RTCTALMMIN_MIN_3             SFRS=3;RTCTALMMIN&=0xF7
#define clr_RTCTALMMIN_MIN_2             SFRS=3;RTCTALMMIN&=0xFB
#define clr_RTCTALMMIN_MIN_1             SFRS=3;RTCTALMMIN&=0xFD
#define clr_RTCTALMMIN_MIN_0             SFRS=3;RTCTALMMIN&=0xFE

/**** RTCTALMHR  B3H  PAGE 3 ****/
#define set_RTCTALMHR_TENHR_1            SFRS=3;RTCTALMHR|=0x20
#define set_RTCTALMHR_TENHR_0            SFRS=3;RTCTALMHR|=0x10
#define set_RTCTALMHR_HR_3               SFRS=3;RTCTALMHR|=0x08
#define set_RTCTALMHR_HR_2               SFRS=3;RTCTALMHR|=0x04
#define set_RTCTALMHR_HR_1               SFRS=3;RTCTALMHR|=0x02
#define set_RTCTALMHR_HR_0               SFRS=3;RTCTALMHR|=0x01

#define clr_RTCTALMHR_TENHR_1            SFRS=3;RTCTALMHR&=0xDF
#define clr_RTCTALMHR_TENHR_0            SFRS=3;RTCTALMHR&=0xEF
#define clr_RTCTALMHR_HR_3               SFRS=3;RTCTALMHR&=0xF7
#define clr_RTCTALMHR_HR_2               SFRS=3;RTCTALMHR&=0xFB
#define clr_RTCTALMHR_HR_1               SFRS=3;RTCTALMHR&=0xFD
#define clr_RTCTALMHR_HR_0               SFRS=3;RTCTALMHR&=0xFE

/**** RTCTALMHz  B4H  PAGE 3 ****/
#define set_RTCTALMHz_HZCNT              SFRS=3;RTCTALMHz|=0x40

#define clr_RTCTALMHz_HZCNT              SFRS=3;RTCTALMHz&=0xBF

/**** RTCCALMDAY  B5H  PAGE 3 ****/
#define set_RTCCALMDAY_TENDAY_1          SFRS=3;RTCCALMDAY|=0x20
#define set_RTCCALMDAY_TENDAY_0          SFRS=3;RTCCALMDAY|=0x10
#define set_RTCCALMDAY_DAY_3             SFRS=3;RTCCALMDAY|=0x08
#define set_RTCCALMDAY_DAY_2             SFRS=3;RTCCALMDAY|=0x04
#define set_RTCCALMDAY_DAY_1             SFRS=3;RTCCALMDAY|=0x02
#define set_RTCCALMDAY_DAY_0             SFRS=3;RTCCALMDAY|=0x01

#define clr_RTCCALMDAY_TENDAY_1          SFRS=3;RTCCALMDAY&=0xDF
#define clr_RTCCALMDAY_TENDAY_0          SFRS=3;RTCCALMDAY&=0xEF
#define clr_RTCCALMDAY_DAY_3             SFRS=3;RTCCALMDAY&=0xF7
#define clr_RTCCALMDAY_DAY_2             SFRS=3;RTCCALMDAY&=0xFB
#define clr_RTCCALMDAY_DAY_1             SFRS=3;RTCCALMDAY&=0xFD
#define clr_RTCCALMDAY_DAY_0             SFRS=3;RTCCALMDAY&=0xFE

/**** RTCCALMMON  B6H  PAGE 3 ****/
#define set_RTCCALMMON_TENMON            SFRS=3;RTCCALMMON|=0x10
#define set_RTCCALMMON_MON_3             SFRS=3;RTCCALMMON|=0x08
#define set_RTCCALMMON_MON_2             SFRS=3;RTCCALMMON|=0x04
#define set_RTCCALMMON_MON_1             SFRS=3;RTCCALMMON|=0x02
#define set_RTCCALMMON_MON_0             SFRS=3;RTCCALMMON|=0x01

#define clr_RTCCALMMON_TENMON            SFRS=3;RTCCALMMON&=0xEF
#define clr_RTCCALMMON_MON_3             SFRS=3;RTCCALMMON&=0xF7
#define clr_RTCCALMMON_MON_2             SFRS=3;RTCCALMMON&=0xFB
#define clr_RTCCALMMON_MON_1             SFRS=3;RTCCALMMON&=0xFD
#define clr_RTCCALMMON_MON_0             SFRS=3;RTCCALMMON&=0xFE

/**** RTCCALMYEAR  BBH  PAGE 3 ****/
#define set_RTCCALMYEAR_TENYEAR_3        SFRS=3;RTCCALMYEAR|=0x80
#define set_RTCCALMYEAR_TENYEAR_2        SFRS=3;RTCCALMYEAR|=0x40
#define set_RTCCALMYEAR_TENYEAR_1        SFRS=3;RTCCALMYEAR|=0x20
#define set_RTCCALMYEAR_TENYEAR_0        SFRS=3;RTCCALMYEAR|=0x10
#define set_RTCCALMYEAR_YEAR_3           SFRS=3;RTCCALMYEAR|=0x08
#define set_RTCCALMYEAR_YEAR_2           SFRS=3;RTCCALMYEAR|=0x04
#define set_RTCCALMYEAR_YEAR_1           SFRS=3;RTCCALMYEAR|=0x02
#define set_RTCCALMYEAR_YEAR_0           SFRS=3;RTCCALMYEAR|=0x01

#define clr_RTCCALMYEAR_TENYEAR_3        SFRS=3;RTCCALMYEAR&=0x7F
#define clr_RTCCALMYEAR_TENYEAR_2        SFRS=3;RTCCALMYEAR&=0xBF
#define clr_RTCCALMYEAR_TENYEAR_1        SFRS=3;RTCCALMYEAR&=0xDF
#define clr_RTCCALMYEAR_TENYEAR_0        SFRS=3;RTCCALMYEAR&=0xEF
#define clr_RTCCALMYEAR_YEAR_3           SFRS=3;RTCCALMYEAR&=0xF7
#define clr_RTCCALMYEAR_YEAR_2           SFRS=3;RTCCALMYEAR&=0xFB
#define clr_RTCCALMYEAR_YEAR_1           SFRS=3;RTCCALMYEAR&=0xFD
#define clr_RTCCALMYEAR_YEAR_0           SFRS=3;RTCCALMYEAR&=0xFE

/**** RTCCLKFMT  B9H  PAGE 3 ****/
#define set_RTCCLKFMT_HZCNTEN            SFRS=3;RTCCLKFMT|=0x02
#define set_RTCCLKFMT_24HEN              SFRS=3;RTCCLKFMT|=0x01

#define clr_RTCCLKFMT_HZCNTEN            SFRS=3;RTCCLKFMT&=0xFD
#define clr_RTCCLKFMT_24HEN              SFRS=3;RTCCLKFMT&=0xFE

/**** RTCCLKTEST  BAH  PAGE 3 TA protect register ****/
#define set_RTCCLKTEST_X64EN             SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;RTCCLKTEST|=0x01;EA=BIT_TMP

#define clr_RTCCLKTEST_X64EN             SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;RTCCLKTEST&=0xFE;EA=BIT_TMP

/**** RTCWEEKDAY  BBH  PAGE 3 ****/
#define set_RTCWEEKDAY_WEEKDAY_2         SFRS=3;RTCWEEKDAY|=0x04
#define set_RTCWEEKDAY_WEEKDAY_1         SFRS=3;RTCWEEKDAY|=0x02
#define set_RTCWEEKDAY_WEEKDAY_0         SFRS=3;RTCWEEKDAY|=0x01

#define clr_RTCWEEKDAY_WEEKDAY_2         SFRS=3;RTCWEEKDAY&=0xFB
#define clr_RTCWEEKDAY_WEEKDAY_1         SFRS=3;RTCWEEKDAY&=0xFD
#define clr_RTCWEEKDAY_WEEKDAY_0         SFRS=3;RTCWEEKDAY&=0xFE

/**** RTCLEAPYEAR  BCH  PAGE 3 ****/
#define set_RTCLEAPYEAR_LEAPYEAR         SFRS=3;RTCLEAPYEAR|=0x01

#define clr_RTCLEAPYEAR_LEAPYEAR         SFRS=3;RTCLEAPYEAR&=0xFE

/**** RTCTICK  BDH  PAGE 3 ****/
#define set_RTCTICK_TICK_2               SFRS=3;RTCTICK|=0x04
#define set_RTCTICK_TICK_1               SFRS=3;RTCTICK|=0x02
#define set_RTCTICK_TICK_0               SFRS=3;RTCTICK|=0x01

#define clr_RTCTICK_TICK_2               SFRS=3;RTCTICK&=0xFB
#define clr_RTCTICK_TICK_1               SFRS=3;RTCTICK&=0xFD
#define clr_RTCTICK_TICK_0               SFRS=3;RTCTICK&=0xFE

/**** RTCTAMSK  BEH  PAGE 3 ****/
#define set_RTCTAMSK_MTENHR              SFRS=3;RTCTAMSK|=0x20
#define set_RTCTAMSK_MHR                 SFRS=3;RTCTAMSK|=0x10
#define set_RTCTAMSK_MTENMIN             SFRS=3;RTCTAMSK|=0x08
#define set_RTCTAMSK_MMIN                SFRS=3;RTCTAMSK|=0x04
#define set_RTCTAMSK_MTENSEC             SFRS=3;RTCTAMSK|=0x02
#define set_RTCTAMSK_MSEC                SFRS=3;RTCTAMSK|=0x01

#define clr_RTCTAMSK_MTENHR              SFRS=3;RTCTAMSK&=0xDF
#define clr_RTCTAMSK_MHR                 SFRS=3;RTCTAMSK&=0xEF
#define clr_RTCTAMSK_MTENMIN             SFRS=3;RTCTAMSK&=0xF7
#define clr_RTCTAMSK_MMIN                SFRS=3;RTCTAMSK&=0xFB
#define clr_RTCTAMSK_MTENSEC             SFRS=3;RTCTAMSK&=0xFD
#define clr_RTCTAMSK_MSEC                SFRS=3;RTCTAMSK&=0xFE

/**** RTCCAMSK  BFH  PAGE 3 ****/
#define set_RTCCAMSK_MTENYEAR            SFRS=3;RTCCAMSK|=0x20
#define set_RTCCAMSK_MYEAR               SFRS=3;RTCCAMSK|=0x10
#define set_RTCCAMSK_MTENMON             SFRS=3;RTCCAMSK|=0x08
#define set_RTCCAMSK_MMON                SFRS=3;RTCCAMSK|=0x04
#define set_RTCCAMSK_MTENDAY             SFRS=3;RTCCAMSK|=0x02
#define set_RTCCAMSK_MDAY                SFRS=3;RTCCAMSK|=0x01

#define clr_RTCCAMSK_MTENYEAR            SFRS=3;RTCCAMSK&=0xDF
#define clr_RTCCAMSK_MYEAR               SFRS=3;RTCCAMSK&=0xEF
#define clr_RTCCAMSK_MTENMON             SFRS=3;RTCCAMSK&=0xF7
#define clr_RTCCAMSK_MMON                SFRS=3;RTCCAMSK&=0xFB
#define clr_RTCCAMSK_MTENDAY             SFRS=3;RTCCAMSK&=0xFD
#define clr_RTCCAMSK_MDAY                SFRS=3;RTCCAMSK&=0xFE

/**** HIRCTEST  CDH  PAGE 3 TA protect register ****/
#define set_HIRCTEST_TRIMOS              SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;HIRCTEST|=0x08;EA=BIT_TMP
#define set_HIRCTEST_ICOMP               SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;HIRCTEST|=0x02;EA=BIT_TMP

#define clr_HIRCTEST_TRIMOS              SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;HIRCTEST&=0xF7;EA=BIT_TMP
#define clr_HIRCTEST_ICOMP               SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;HIRCTEST&=0xFD;EA=BIT_TMP

/**** PWM0FBS  CEH  PAGE 3 ****/
#define set_PWM0FBS_PWM0FBS_1            SFRS=3;PWM0FBS|=0x02
#define set_PWM0FBS_PWM0FBS_0            SFRS=3;PWM0FBS|=0x01

#define clr_PWM0FBS_PWM0FBS_1            SFRS=3;PWM0FBS&=0xFD
#define clr_PWM0FBS_PWM0FBS_0            SFRS=3;PWM0FBS&=0xFE

/**** AUXR3  CFH  PAGE 3 ****/
#define set_AUXR3_UART3DG                SFRS=3;AUXR3|=0x08
#define set_AUXR3_UART2DG                SFRS=3;AUXR3|=0x04
#define set_AUXR3_UART1DG                SFRS=3;AUXR3|=0x02
#define set_AUXR3_UART0DG                SFRS=3;AUXR3|=0x01

#define clr_AUXR3_UART3DG                SFRS=3;AUXR3&=0xF7
#define clr_AUXR3_UART2DG                SFRS=3;AUXR3&=0xFB
#define clr_AUXR3_UART1DG                SFRS=3;AUXR3&=0xFD
#define clr_AUXR3_UART0DG                SFRS=3;AUXR3&=0xFE

/**** LCDPCNTS1  E9H  PAGE 3 TA protect register ****/
#define set_LCDPCNTS1_LCDPCNTS_9         SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDPCNTS1|=0x02;EA=BIT_TMP
#define set_LCDPCNTS1_LCDPCNTS_8         SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDPCNTS1|=0x01;EA=BIT_TMP

#define clr_LCDPCNTS1_LCDPCNTS_9         SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDPCNTS1&=0xFD;EA=BIT_TMP
#define clr_LCDPCNTS1_LCDPCNTS_8         SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDPCNTS1&=0xFE;EA=BIT_TMP

/**** LCDPCNTV1  EAH  PAGE 3 TA protect register ****/
#define set_LCDPCNTV1_LCDPCNTV_9         SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDPCNTV1|=0x02;EA=BIT_TMP
#define set_LCDPCNTV1_LCDPCNTV_8         SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDPCNTV1|=0x01;EA=BIT_TMP

#define clr_LCDPCNTV1_LCDPCNTV_9         SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDPCNTV1&=0xFD;EA=BIT_TMP
#define clr_LCDPCNTV1_LCDPCNTV_8         SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDPCNTV1&=0xFE;EA=BIT_TMP

/**** LCDCPUMP  F1H  PAGE 3 ****/
#define set_LCDCPUMP_CP_VSET             SFRS=3;LCDCPUMP|=0x20

#define clr_LCDCPUMP_CP_VSET             SFRS=3;LCDCPUMP&=0xDF

/**** LCDADJUST  F2H  PAGE 3 TA protect register ****/
#define set_LCDADJUST_BUF_V3_iset        SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST|=0x80;EA=BIT_TMP
#define set_LCDADJUST_BUF_V2_iset        SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST|=0x40;EA=BIT_TMP
#define set_LCDADJUST_BUF_V1_iset        SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST|=0x20;EA=BIT_TMP
#define set_LCDADJUST_PUMP_HYS           SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST|=0x10;EA=BIT_TMP
#define set_LCDADJUST_SYN_SAV            SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST|=0x08;EA=BIT_TMP
#define set_LCDADJUST_L_ICMP             SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST|=0x04;EA=BIT_TMP
#define set_LCDADJUST_CP_ILOAD           SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST|=0x02;EA=BIT_TMP
#define set_LCDADJUST_IBOOST             SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST|=0x01;EA=BIT_TMP

#define clr_LCDADJUST_BUF_V3_iset        SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST&=0x7F;EA=BIT_TMP
#define clr_LCDADJUST_BUF_V2_iset        SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST&=0xBF;EA=BIT_TMP
#define clr_LCDADJUST_BUF_V1_iset        SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST&=0xDF;EA=BIT_TMP
#define clr_LCDADJUST_PUMP_HYS           SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST&=0xEF;EA=BIT_TMP
#define clr_LCDADJUST_SYN_SAV            SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST&=0xF7;EA=BIT_TMP
#define clr_LCDADJUST_L_ICMP             SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST&=0xFB;EA=BIT_TMP
#define clr_LCDADJUST_CP_ILOAD           SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST&=0xFD;EA=BIT_TMP
#define clr_LCDADJUST_IBOOST             SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDADJUST&=0xFE;EA=BIT_TMP

/**** LCDTest0  F3H  PAGE 3 TA protect register ****/
#define set_LCDTest0_V41_trim            SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDTest0|=0x80;EA=BIT_TMP
#define set_LCDTest0_V31_trim            SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDTest0|=0x20;EA=BIT_TMP
#define set_LCDTest0_LCD_T_DATA          SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDTest0|=0x08;EA=BIT_TMP
#define set_LCDTest0_BIN_TEST            SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDTest0|=0x01;EA=BIT_TMP

#define clr_LCDTest0_V41_trim            SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDTest0&=0x7F;EA=BIT_TMP
#define clr_LCDTest0_V31_trim            SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDTest0&=0xDF;EA=BIT_TMP
#define clr_LCDTest0_LCD_T_DATA          SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDTest0&=0xF7;EA=BIT_TMP
#define clr_LCDTest0_BIN_TEST            SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDTest0&=0xFE;EA=BIT_TMP

/**** LCDTest1  F4H  PAGE 3 TA protect register ****/
#define set_LCDCON1_LCDIS                SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDCON1|=0x08;EA=BIT_TMP
#define set_LCDCON1_LCDIE                SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDCON1|=0x04;EA=BIT_TMP
#define set_LCDCON1_RE_MODE              SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDCON1|=0x02;EA=BIT_TMP

#define clr_LCDCON1_LCDIS                SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDCON1&=0xF7;EA=BIT_TMP
#define clr_LCDCON1_LCDIE                SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDCON1&=0xFB;EA=BIT_TMP
#define clr_LCDCON1_RE_MODE              SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDCON1&=0xFD;EA=BIT_TMP

/**** LCDIS  F7H  PAGE 3 TA protect register ****/
#define set_LCDIS_LCDPO_INT              SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDIS|=0x02;EA=BIT_TMP
#define set_LCDIS_LCD_INT                SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDIS|=0x01;EA=BIT_TMP

#define clr_LCDIS_LCDPO_INT              SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDIS&=0xFD;EA=BIT_TMP
#define clr_LCDIS_LCD_INT                SFRS=3;BIT_TMP=EA;EA=0;TA=0xAA;TA=0x55;LCDIS&=0xFE;EA=BIT_TMP

/**** LCDCON0  F9H  PAGE 3 ****/
#define set_LCDCON0_LCDEN                SFRS=3;LCDCON0|=0x80
#define set_LCDCON0_TYPE                 SFRS=3;LCDCON0|=0x40
#define set_LCDCON0_BIAS_1               SFRS=3;LCDCON0|=0x20
#define set_LCDCON0_BIAS_0               SFRS=3;LCDCON0|=0x10
#define set_LCDCON0_DUTY_1               SFRS=3;LCDCON0|=0x08
#define set_LCDCON0_DUTY_0               SFRS=3;LCDCON0|=0x04
#define set_LCDCON0_LCD_IE               SFRS=3;LCDCON0|=0x01

#define clr_LCDCON0_LCDEN                SFRS=3;LCDCON0&=0x7F
#define clr_LCDCON0_TYPE                 SFRS=3;LCDCON0&=0xBF
#define clr_LCDCON0_BIAS_1               SFRS=3;LCDCON0&=0xDF
#define clr_LCDCON0_BIAS_0               SFRS=3;LCDCON0&=0xEF
#define clr_LCDCON0_DUTY_1               SFRS=3;LCDCON0&=0xF7
#define clr_LCDCON0_DUTY_0               SFRS=3;LCDCON0&=0xFB
#define clr_LCDCON0_LCD_IE               SFRS=3;LCDCON0&=0xFE

/**** LCDCLK  FAH  PAGE 3 ****/
#define set_LCDCLK_LCDCKS                SFRS=3;LCDCLK|=0x10
#define set_LCDCLK_DISP                  SFRS=3;LCDCLK|=0x08
#define set_LCDCLK_LCDDIV_2              SFRS=3;LCDCLK|=0x04
#define set_LCDCLK_LCDDIV_1              SFRS=3;LCDCLK|=0x02
#define set_LCDCLK_LCDDIV_0              SFRS=3;LCDCLK|=0x01

#define clr_LCDCLK_LCDCKS                SFRS=3;LCDCLK&=0xEF
#define clr_LCDCLK_DISP                  SFRS=3;LCDCLK&=0xF7
#define clr_LCDCLK_LCDDIV_2              SFRS=3;LCDCLK&=0xFB
#define clr_LCDCLK_LCDDIV_1              SFRS=3;LCDCLK&=0xFD
#define clr_LCDCLK_LCDDIV_0              SFRS=3;LCDCLK&=0xFE

/**** LCDPTR  FBH  PAGE 3 ****/
#define set_LCDPTR_LCDPTR_4              SFRS=3;LCDPTR|=0x10
#define set_LCDPTR_LCDPTR_3              SFRS=3;LCDPTR|=0x08
#define set_LCDPTR_LCDPTR_2              SFRS=3;LCDPTR|=0x04
#define set_LCDPTR_LCDPTR_1              SFRS=3;LCDPTR|=0x02
#define set_LCDPTR_LCDPTR_0              SFRS=3;LCDPTR|=0x01

#define clr_LCDPTR_LCDPTR_4              SFRS=3;LCDPTR&=0xEF
#define clr_LCDPTR_LCDPTR_3              SFRS=3;LCDPTR&=0xF7
#define clr_LCDPTR_LCDPTR_2              SFRS=3;LCDPTR&=0xFB
#define clr_LCDPTR_LCDPTR_1              SFRS=3;LCDPTR&=0xFD
#define clr_LCDPTR_LCDPTR_0              SFRS=3;LCDPTR&=0xFE

/**** LCDPWR  FDH  PAGE 3 ****/
#define set_LCDPWR_PWR_SAVE_1            SFRS=3;LCDPWR|=0x02
#define set_LCDPWR_PWR_SAVE_0            SFRS=3;LCDPWR|=0x01

#define clr_LCDPWR_PWR_SAVE_1            SFRS=3;LCDPWR&=0xFD
#define clr_LCDPWR_PWR_SAVE_0            SFRS=3;LCDPWR&=0xFE

/**** LCDBL  FEH  PAGE 3 ****/
#define set_LCDBL_DT_2                   SFRS=3;LCDBL|=0x40
#define set_LCDBL_DT_1                   SFRS=3;LCDBL|=0x20
#define set_LCDBL_DT_0                   SFRS=3;LCDBL|=0x10
#define set_LCDBL_BLINK                  SFRS=3;LCDBL|=0x08
#define set_LCDBL_BLF_2                  SFRS=3;LCDBL|=0x04
#define set_LCDBL_BLF_1                  SFRS=3;LCDBL|=0x02
#define set_LCDBL_BLF_0                  SFRS=3;LCDBL|=0x01

#define clr_LCDBL_DT_2                   SFRS=3;LCDBL&=0xBF
#define clr_LCDBL_DT_1                   SFRS=3;LCDBL&=0xDF
#define clr_LCDBL_DT_0                   SFRS=3;LCDBL&=0xEF
#define clr_LCDBL_BLINK                  SFRS=3;LCDBL&=0xF7
#define clr_LCDBL_BLF_2                  SFRS=3;LCDBL&=0xFB
#define clr_LCDBL_BLF_1                  SFRS=3;LCDBL&=0xFD
#define clr_LCDBL_BLF_0                  SFRS=3;LCDBL&=0xFE

/**** LCDMODE  FFH  PAGE 3 ****/
#define set_LCDMODE_R_MODE               SFRS=3;LCDMODE|=0x80
#define set_LCDMODE_SELBUF               SFRS=3;LCDMODE|=0x40
#define set_LCDMODE_VLCD_MODE_1          SFRS=3;LCDMODE|=0x02
#define set_LCDMODE_VLCD_MODE_0          SFRS=3;LCDMODE|=0x01

#define clr_LCDMODE_R_MODE               SFRS=3;LCDMODE&=0x7F
#define clr_LCDMODE_SELBUF               SFRS=3;LCDMODE&=0xBF
#define clr_LCDMODE_VLCD_MODE_1          SFRS=3;LCDMODE&=0xFD
#define clr_LCDMODE_VLCD_MODE_0          SFRS=3;LCDMODE&=0xFE

