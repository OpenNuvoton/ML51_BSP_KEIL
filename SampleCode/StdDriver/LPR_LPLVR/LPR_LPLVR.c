/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: ML51 simple GPIO toggle out demo code
//***********************************************************************************************************

#include "ML51.h"

/**
 * @brief       For low power current testing
 * @param       None
 * @return      None
 * @details     
 */
//void WKT_ISR(void) interrupt 17            // Vector @  0x8B
//{
//    clr_WKCON_WKTF;
//}

void main (void) 
{

/* Setting Multi function pin setting for GPIO toggle 
   * include gipo.c in Common for GPIO mode setting
*/
    while(P46);

//    WKT_Open(38400,256,256);
//    WKT_Interrupt(Enable);

    BOD_Enable(VBOD24,BOD_RESET_ENABLE);
    BOD_LowPower_Enable(LPBOD_MODE2,BOD_FT_ENABLE);

    BOD_Disable();
    POR_Disable();
    LVR_Disable();
    LowPowerLVR_Enable();
    ENABLE_GLOBAL_INTERRUPT;

/* Enable Low power run mode */ 
    FsysSelect(FSYS_LIRC);
    set_PCON_LPR;
    set_PCON_PD; 

    while(1)
     set_PCON_PD;
}



