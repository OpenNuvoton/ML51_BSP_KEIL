/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 clock out demo
//***********************************************************************************************************
#include "ML51.h"


void main(void)
{
/* Enable 3 pin of clock out multi function pin define */
    MFP_P32_CLKO;
    P32_PUSHPULL_MODE;

    MFP_P46_CLKO;
    P46_PUSHPULL_MODE;

    MFP_P56_CLKO;
    P56_PUSHPULL_MODE;

    set_CKCON_CLOEN;                                  //System Clock Output Enable
    SFRS=1;CKDIV = 0x78;                              //System clock divider 240 for scope check
	
    while(1);
	/* =================== */
}

