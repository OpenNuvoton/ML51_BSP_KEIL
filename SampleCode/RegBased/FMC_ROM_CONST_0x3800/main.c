/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 Data table special location @0x2C00 and 0x3400 demo
//***********************************************************************************************************
#include "ml51.h"

//=========================================================================================================
void main(void)
{
    unsigned char code *Table_Address_Locate;
    unsigned char code *Table_Data_Locate;
    unsigned char readtemp, readtemp1;
   
    Table_Address_Locate = 0x2C00;
    readtemp = *Table_Address_Locate;
    Table_Data_Locate = 0x3404;
    readtemp1 = *Table_Data_Locate;
  
    while(1);
}