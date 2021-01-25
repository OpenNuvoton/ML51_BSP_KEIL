/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

#include "ML56.h"
#include "TKLib.h"
extern S_TKINFO sTKInfo;
extern S_TKINFO *psTKInfo;

void TouchKey_ISR(void) interrupt 26 using 0        // Vector @  0xD3
{
    TKSTA0 &= ~0x0A;	/* Scan complete and TKIF_ALL, write 0 clear both */
    TKSTA1 = 0;
    TKSTA2 = 0;
    TKINTEN = 0;
    TKCON0 &= ~0x0A;    /* Disable TMRTRG */
}




/**
  * @brief      Configure TK for power down wake up setting 
  * @param[in]  u8Sensitivity     u8Sensitivity 
  * @param[in]  u8HighThAll       u8HighThAll
  * @retval     none
  * @details    This function is used to auto-tune for finding the appropriate REFCB for the group of enabled channels
  *             and make the raw of each channels should be greater than lowBoundREFCB and smaller than upBoundREFCB
  */
void TK_ConfigPowerDown(uint8_t u8Sensitivity)
{
    //TK_REFCB_AutoTune_ScanAll();

    TKSTA1 = 0;			/* Clear All TKIF */
    TKSTA2 = 0;
    TKSTA0 &= ~BIT3;   
    
    TK_EnableChannel(psTKInfo->u32EnChanMsk | psTKInfo->u32EnSliderMsk | psTKInfo->u32EnWheelMsk);

    REFCBDALL = psTKInfo->u8RefCbAll - u8Sensitivity;
    TKCCBDALL = psTKInfo->u8CcbAll;

    TKCON0 |= 0x0A;		/* Enable TMRTRG and SCANA-ALL*/

    TKHTHALL = 100; 

    clr_CHPCON_IAPEN;   /* Disable IAP */
    TKINTEN |= 0x1;	    /* Enable Interrupt */
}