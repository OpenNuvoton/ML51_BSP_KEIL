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
#include "TK_Demo.h"

#define TARGET_APROM
void FMC_Open(void)
{
    set_CHPCON_IAPEN;
#ifdef TARGET_APROM
    set_IAPUEN_APUEN;
#else
    set_IAPUEN_SPUEN;
#endif
}

signed char FMC_Erase(unsigned int u16Addr)
{
    /* Erase APROM DATAFLASH page */
    IAPAL = u16Addr&0xff;
    IAPAH = (u16Addr>>8)&0xff;
    IAPFD = 0xFF;
    //set_CHPCON_IAPEN;
    //set_IAPUEN_APUEN;
#ifdef TARGET_APROM
    IAPCN = 0x22;     /* APROM Page Erase */
#else
    IAPCN = 0xA2;       /* SPROM Page Erase */
#endif
    /* CPU will be blocked in hear until flash erase complete */
    set_IAPTRG_IAPGO;
    return 0;
}

signed char FMC_Write(unsigned int u16Addr, unsigned long u32Data)
{
    unsigned char looptmp;

    //set_CHPCON_IAPEN;
    //set_IAPUEN_APUEN;
#ifdef TARGET_APROM
    IAPCN = 0x21;         /* APROM Program */
#else
    IAPCN = 0xA1;         /* SPROM Program */
#endif
#if 0
    for(looptmp=0; looptmp<=3; looptmp++)
    {
        IAPAL = (u16Addr&0xff)+looptmp;
        IAPAH = (u16Addr>>8)&0xff;
        IAPFD = u32Data>>(looptmp*8);
        set_IAPTRG_IAPGO;
    }
#else
    for(looptmp=3; looptmp!=0xFF; looptmp--)
    {
        IAPAL = (u16Addr&0xff)+looptmp;
        IAPAH = (u16Addr>>8)&0xff;
        IAPFD = u32Data>>((3-looptmp)*8);
        set_IAPTRG_IAPGO;
    }
#endif
    return 0;
}

signed char FMC_Write16(unsigned int u16Addr, unsigned int u16Data)
{
    unsigned char looptmp;

#ifdef TARGET_APROM
    IAPCN = 0x21;         /* APROM Program */
#else
    IAPCN = 0xA1;         /* SPROM Program */
#endif
#if 0
    for(looptmp=0; looptmp<=3; looptmp++)
    {
        IAPAL = (u16Addr&0xff)+looptmp;
        IAPAH = (u16Addr>>8)&0xff;
        IAPFD = u32Data>>(looptmp*8);
        set_IAPTRG_IAPGO;
    }
#else
    for(looptmp=2; looptmp!=0xFF; looptmp--)
    {
        IAPAL = (u16Addr&0xff)+looptmp;
        IAPAH = (u16Addr>>8)&0xff;
        IAPFD = u16Data>>((2-looptmp)*8);
        set_IAPTRG_IAPGO;
    }
#endif
    return 0;
}

