#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ML56.h"
#include "TKLib.h"
#include "TK_Demo.h"

#define TARGET_APROM

extern S_NEIGHBOR s_neighbor[];

int8_t TK_LoadPara(uint32_t* pu32ChanelMsk)
{
    uint32_t u32Data, i;
    uint32_t *ptr;
    S_TKFEAT* psTkFeat;
    S_KEYINFO* pKeyInfo;
    S_TKINFO* psTkInfo;

    //psTkInfo = &sTKInfo;

    psTkFeat = TK_GetFeaturePtr();
    pKeyInfo = TK_GetKeyInfoPtr();
    psTkInfo = TK_GetTKInfoPtr();

    FMC_Open();

    u32Data = inp32(TK_ADDR_PARAM_DFLASH);
    if (u32Data != 0x4E544B62)
    {
        return -1;
    }

    psTkInfo->u32EnChanMsk = (uint32_t)inp32(TK_ADDR_PARAM_DFLASH + 4);
    u32Data = inp32(TK_ADDR_PARAM_DFLASH + 0x08);
#if 0
    psTkInfo->u8RefChan = u32Data >> 24;
    psTkInfo->u8SenPulse = u32Data >> 16;
    psTkInfo->u8SenPulse = u32Data >> 8;
    psTkInfo->u8SenTimes = u32Data;
#else
    ptr = (uint32_t *) & (psTkInfo->u8RefChan);
    *ptr = u32Data;
#endif

    *pu32ChanelMsk = psTkInfo->u32EnChanMsk| (1<<psTkInfo->u8RefChan) | (1<<psTkInfo->u8ShieldChan);


    u32Data = inp32(TK_ADDR_PARAM_DFLASH + 0x0C);
#if 0
    psTkInfo->u8IdleState = u32Data >> 24;
    psTkInfo->u8PolarityState = u32Data >> 16;
    psTkInfo->u8PolarityCapacitorBank = u32Data >> 8;
    psTkInfo->u8AvcchLevel = u32Data;
#else
    ptr = (uint32_t *) & (psTkInfo->u8IdleState);
    *ptr = u32Data;
#endif

    ////////////////////////////////////////
    psTkInfo->u32EnSliderMsk = inp32(TK_ADDR_PARAM_DFLASH + 0x10);
    psTkInfo->u32EnWheelMsk = inp32(TK_ADDR_PARAM_DFLASH + 0x14);
    psTkInfo->u32StoreAddr = inp32(TK_ADDR_PARAM_DFLASH + 0x18);
    psTkInfo->u8NoiseImmunity = inp32(TK_ADDR_PARAM_DFLASH + 0x1C)&0xFF;   /* Noise Immunity Factor: 1/3, 1/2, 2/3 */
    ////////////////////////////////////////

    u32Data = inp32(TK_ADDR_PARAM_DFLASH + 0x20);
    ptr = (uint32_t *) & (psTkFeat->u8EnIIR);
    *ptr = u32Data;
    u32Data = inp32(TK_ADDR_PARAM_DFLASH + 0x24);
    ptr = (uint32_t *) & (psTkFeat->u16ResetTime);
    *ptr = u32Data;

    u32Data = inp32(TK_ADDR_PARAM_DFLASH + 0x28);       //2020-0325
    ptr = (uint32_t *) & (psTkFeat->u8Entry);
    *ptr = u32Data;
    ////////////////////////////////////////
    for (i = 0 ; i < TKLIB_TOL_NUM_KEY ; i++)
    {
        u32Data = inp32(TK_ADDR_KEY_PARM + i * 4);
#if 0
        S_KeyInfo[i].ccb = u32Data >> 24;
        S_KeyInfo[i].refcb = u32Data >> 16;
        S_KeyInfo[i].level = u32Data >> 8;
#else
        ptr = (uint32_t *)&((pKeyInfo+i)->ccb);
        *ptr = u32Data;
#endif
    }

    return 0;
}


#ifdef DEMO_CALIBRATION
int8_t TK_SavePara(void)
{
    uint32_t TK_DFLASH_Tag[1] = 0x4E544B62; //{'N','T','K','b'};
    uint32_t u32Data;
    uint8_t i;
    S_TKFEAT* psTkFeat;
    S_KEYINFO* pKeyInfo;
    S_TKINFO* psTkInfo;

    psTkFeat = TK_GetFeaturePtr();
    pKeyInfo = TK_GetKeyInfoPtr();
    psTkInfo = TK_GetTKInfoPtr();

    FMC_Open();

    if (FMC_Erase(TK_ADDR_PARAM_DFLASH))
    {
        return -1;
    }

    FMC_Write(TK_ADDR_PARAM_DFLASH + 4, (uint32_t)psTkInfo->u32EnChanMsk);
#if 0
    u32Data = ((uint32_t)psTkInfo->u8RefChan << 24) || ((uint32_t)psTkInfo->u8SenPulse << 16) || \
              ((uint32_t)psTkInfo->u8SenPulse << 8) || ((uint32_t)psTkInfo->u8SenTimes);
#else
    u32Data = *((uint32_t *) & (psTkInfo->u8RefChan));
#endif
    FMC_Write(TK_ADDR_PARAM_DFLASH + 8, u32Data);
#if 0
    u32Data = ((uint32_t)psTkInfo->u8IdleState << 24) || ((uint32_t)psTkInfo->u8PolarityState << 16) || \
              ((uint32_t)psTkInfo->u8PolarityCapacitorBank << 8) || ((uint32_t)psTkInfo->u8AvcchLevel);
#else
    u32Data = *((uint32_t *) & (psTkInfo->u8IdleState));
#endif
    FMC_Write(TK_ADDR_PARAM_DFLASH + 0xC, u32Data);

    ////////////////////////////////////////
    FMC_Write(TK_ADDR_PARAM_DFLASH + 0x10, psTkInfo->u32EnSliderMsk);
    FMC_Write(TK_ADDR_PARAM_DFLASH + 0x14, psTkInfo->u32EnWheelMsk);
    FMC_Write(TK_ADDR_PARAM_DFLASH + 0x18, psTkInfo->u32StoreAddr);
    FMC_Write(TK_ADDR_PARAM_DFLASH + 0x1C, (uint32_t)psTkInfo->u8NoiseImmunity);
    ////////////////////////////////////////

    //u32Data = *((uint32_t *) & (S_TkFeat.u8EnIIR));
    u32Data = *((uint32_t *) & (psTkFeat->u8EnIIR));
    FMC_Write(TK_ADDR_PARAM_DFLASH + 0x20, u32Data);
    //u32Data = *((uint32_t *) & (S_TkFeat.u16ResetTime));
    u32Data = *((uint32_t *) & (psTkFeat->u16ResetTime));
    FMC_Write(TK_ADDR_PARAM_DFLASH + 0x24, u32Data);

    //u32Data = *((uint32_t *) & (S_TkFeat.u8Entry));       //2020-0325
    u32Data = *((uint32_t *) & (psTkFeat->u8Entry));
    FMC_Write(TK_ADDR_PARAM_DFLASH + 0x28, u32Data);

#ifdef BOARD_TIM
    u32Data = (0xFFL<<24) | (0x01L<<16) | (0x00L<<8) | 0x2;     //XXX<--TK0-->TK1, TK0<--TK1-->TK2
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0x0, u32Data);

    u32Data = (0x01L<<24) | (0x05L<<16) | (0xFFL<<8) | 0xFF;    //TK1<--TK2-->TK5, XXX<--TK3-->XXX
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0x4, u32Data);

    u32Data = (0xFFL<<24) | (0xFFL<<16) | (0x02L<<8) | 0x06;    //XXX<--TK4-->XXX, TK2<--TK5-->TK6
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0x8, u32Data);

    u32Data = (0x05L<<24) | (0xFFL<<16) | (0xFFL<<8) | 0xFF;    //TK1<--TK6-->XXX, XXX<--TK7-->XXX
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0xC, u32Data);
#else
#if 0
    if (FMC_Erase(TK_ADDR_NEIGHBOR))
    {
        return -1;
    }
    u32Data = (0x01L<<24) | (0x0CL<<16) | (0x02L<<8) | 0x0;     //TK1 <--TK0--> TK12, TK2<--TK1-->TK0
    printf("Write Data = 0x%lx\n", u32Data);                    //Flash will be highest byte write to low addres.
    FMC_Write(TK_ADDR_NEIGHBOR + 0x0, u32Data);

    u32Data = (0xFFL<<24) | (0x01L<<16) | (0xFFL<<8) | 0xFF;    //TK2 and TK3
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0x4, u32Data);

    //
    u32Data = (0xFFL<<24) | (0xFFL<<16) | (0xFFL<<8) | 0xFF;    //TK4 and TK5
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0x8, u32Data);

    u32Data = (0xFFL<<24) | (0xFFL<<16) | (0xFFL<<8) | 0xFF;    //TK6 and TK7
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0xC, u32Data);

    u32Data = (0xFFL<<24) | (0xFFL<<16) | (0xFFL<<8) | 0xFF;    //TK8 and TK9
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0x10, u32Data);

    u32Data = (0xFFL<<24) | (0xFFL<<16) | (0xFFL<<8) | 0xFF;    //TK10 and TK11
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0x14, u32Data);

    u32Data = (0x0L<<24) | (0x0DL<<16) | (0x0CL<<8) | 0x0E;     //TK12 and TK13
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0x18, u32Data);

    u32Data = (0x0DL<<24) | (0x08L<<16) | (0xFFL<<8) | 0xFF;    //TK14
    printf("Write Data = 0x%lx\n", u32Data);
    FMC_Write(TK_ADDR_NEIGHBOR + 0x1C, u32Data);
#endif
#endif

#ifdef TARGET_APROM
    ////////////////////////////////////////
    if (FMC_Erase(TK_ADDR_KEY_PARM))
    {
        return -1;
    }
#endif

    for (i = 0 ; i < TKLIB_TOL_NUM_KEY ; i++)
    {
#if 0
        u32Data = 0;
        u32Data |= (uint32_t)S_KeyInfo[i].ccb << 24;
        u32Data |= (uint32_t)S_KeyInfo[i].refcb << 16;
        u32Data |= (uint32_t)S_KeyInfo[i].level << 8;
#else
        //u32Data = *((uint32_t *)&S_KeyInfo[i]);
        u32Data = *((uint32_t *)& (*(pKeyInfo+i)));
#endif
        FMC_Write(TK_ADDR_KEY_PARM + i * 4, u32Data);
    }

    FMC_Write(TK_ADDR_PARAM_DFLASH, TK_DFLASH_Tag[0]);
    return 0;
}
#endif
