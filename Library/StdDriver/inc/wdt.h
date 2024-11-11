/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

void WDT_Open(unsigned int u8WDTDIV);
void WDT_Interrupt(unsigned char u8WDTIntStatus);
void WDT_Reset(unsigned char u8WDTRST);
void WDT_Close();
void WDT_Clear(void);