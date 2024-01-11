/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define  GPIO_LED               P32    /* the NuMaker board GPIO LED pin define */ 
#define  GPIO_LED_QUASI_MODE    P32_QUASI_MODE
#define  GPIO_PRINTF            P31

#define  BOOT_APROM     0
#define  BOOT_LDROM     2

extern BIT BIT_TMP;
extern unsigned char data  TA_REG_TMP,SFRS_TMP,BYTE_TMP;

unsigned char Read_APROM_BYTE(unsigned int code *u16_addr);
void Global_Interrupt(unsigned char u8IntStatus);
void Software_Reset(unsigned char u8Bootarea);
void PowerDown_Mode(bit PDStatus);
void Idle_Mode(bit IdleStatus);