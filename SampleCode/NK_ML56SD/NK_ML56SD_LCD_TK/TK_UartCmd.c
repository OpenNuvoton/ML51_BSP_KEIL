/**************************************************************************//**
 * @file     TK_UartCmd.c
 * @version  V1.00
 * $Revision: 6 $
 * $Date: 9/15/20 10:28a $
 * @brief     UART command to communicate with PC tool that for evaluate the Touch Key.
 * @note
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ML51.h"
#include "TKLib.h"
#include "TK_Demo.h"

//extern S_KEYINFO S_KeyInfo[];
//extern S_TKFEAT S_TkFeat;
extern S_TKINFO *psTkInfo;
extern volatile int8_t i8SliderPercentage;
extern volatile int8_t i8WheelPercentage;
extern int8_t i8KeyScanId;
extern void TickCallback_KeyScan(void);

//static APPTIME_T tAppTime[1];
/* CMD Type 1 */
#define E_CMD_TYPE1_SPECIFY_CHANNEL_MSK     (0x0)
#define E_CMD_TYPE1_SPECIFY_SLIDER_MSK      (0x1)
#define E_CMD_TYPE1_SPECIFY_WHEEL_MSK       (0x2)
#define E_CMD_TYPE1_SPECIFY_REF_SHIELD_NO   (0x3)
#define E_CMD_TYPE1_SPECIFY_FEATURE         (0x4)
#define E_CMD_TYPE1_SPECIFY_SENSE           (0x5)
#define E_CMD_TYPE1_SPECIFY_RESET_VOL       (0x6)
#define E_CMD_TYPE1_SPECIFY_STORE_ADDR      (0x7)
#define E_CMD_TYPE1_SPECIFY_NEIGHBORING     (0x8)
#define E_CMD_TYPE1_NUM_LAST_COMMAND        E_CMD_TYPE1_SPECIFY_NEIGHBORING

#define E_CMD_TYPE1_START_CALIBRATION       ('A')
#define E_CMD_TYPE1_RESET_CALIBRATION1      ('B')
#define E_CMD_TYPE1_RESET_CALIBRATION2      ('C')
#define E_CMD_TYPE1_WRITE_CALIBRATION       ('D')
#define E_CMD_TYPE1_LOAD_CALIBRATION        ('E')
#define E_CMD_TYPE1_START_RUN_TIME_SCAN_KEY ('F')
#define E_CMD_TYPE1_ESCAPE_RUN_TIME_SCAN_KEY ('G')
#define E_CMD_TYPE1_ESCAPE_APPLICATION      ('H')
#define E_CMD_TYPE1_IIR_PARAMETER           ('I')
#define E_CMD_TYPE1_DEBOUNCE_PARAMETER      ('J')
#define E_CMD_TYPE1_LAST_COMMAND            E_CMD_TYPE1_DEBOUNCE_PARAMETER

/* CMD Type 2 */
#define E_CMD_TYPE2_READ_CHANNEL_MSK        (0x10)
#define E_CMD_TYPE2_READ_SLIDER_MSK         (0x11)
#define E_CMD_TYPE2_READ_WHEEL_MSK          (0x12)
#define E_CMD_TYPE2_READ_REF_SHIELD_NO      (0x13)
#define E_CMD_TYPE2_READ_FEATURE            (0x14)
#define E_CMD_TYPE2_READ_SENSE              (0x15)
#define E_CMD_TYPE2_READ_RESET_VOL          (0x16)
#define E_CMD_TYPE2_READ_STORE_ADDR         (0x17)
#define E_CMD_TYPE2_READ_NEIGHBORING        (0x18)

#define E_CMD_TYPE2_CHECK_CALIBRATION_DONE  ('a')
#define E_CMD_TYPE2_GET_CALIBRATION1        ('b')
#define E_CMD_TYPE2_GET_CALIBRATION2        ('c')
#define E_CMD_TYPE2_RUNTIME_KEY_INFO        ('d')
#define E_CMD_TYPE2_GET_IIR_PARAMETER       ('i')
#define E_CMD_TYPE2_GET_DEBOUNCE_PARAMETER  ('j')
#define E_CMD_TYPE2_SET_SCAN_KEY            ('k')

#ifdef MASS_FINETUNE
#define E_CMD_TYPE2_GET_UID                 ('l')
void TK_MP_Open(void);                              /* Used for internal mass production */
volatile uint8_t xdata gbIsFineTuneDone = 0;
volatile uint8_t xdata gFineTuneDoneTimeOut = 0;
#endif

#define E_CMD_TYPE2_FIRMWARE_VERSION        ('v')
#define E_CMD_TYPE2_LAST_COMMAND            E_CMD_TYPE2_FIRMWARE_VERSION

/**
 * @brief       Send chars by UART interface
 * @param[i]    pu8buf  buffer pointer that contain the characters to be sent.
 * @param[i]    u32len  length of characters to be sent.
 * @return      None
 * @details     This Function used to send chars by UART interface
 */
//bdata int ibase;
volatile unsigned char td_flag=1;
void TK_SendChars(uint8_t *pu8buf, uint32_t u32len)
{
    int i = 0;

    for (i = 0; i < u32len; i++)
    {
#if 1
        while (td_flag!=1);    /* wait until transmitter complete */
        td_flag = 0;
        SBUF = pu8buf[i];      /* output character */
#else
        while (UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);
        UART0->DAT = pu8buf[i];
#endif
    }
#if 1
    while (td_flag!=1);    /* wait until transmitter complete */
#else
    while (UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);
#endif
}

/**
  * @brief      Get packet from AP tool and check if the header, data length and checksum are all correct
  * @param      None.
  * @retval     0:success.
  *             -1:fail
  * @details    This function is used to get command packet from AP tool
  *             AP transmission format:
  *             | HEADER BYTES('N''T''K') | CMD(1 byte) | LEN(2 bytes) | PAYLOAD(n bytes) | checkSum(1 byte) |
  *             Firmware would return status immediately
  *
  */

/* RX: PC--> DUT,
   TX: DUT--> PC */
/* Cmd = 0x0 ~ 0x8, 'A' ~ 'J'  */
#define E_RX_CMD_TYPE1_SIZE (6)         /* PC-->DUT */
/* DUT reply 'A' or 'N' only  */
#define E_TX_CMD_TYPE1_SIZE (1)         /* DUT-->PC */

/* Cmd = 0x10 ~ 0x16, 'a' ~ 'v' */
#define E_RX_CMD_TYPE2_SIZE (3)         /* PC-->DUT */
/* DUT reply parameter + 'A' or 'N' only  */
#define E_TX_CMD_TYPE2_SIZE (5)         /* DUT-->PC */


#define TXBUFSIZE   E_TX_CMD_TYPE2_SIZE
#define RXBUFSIZE   E_RX_CMD_TYPE1_SIZE
#define E_UART_TIME_OUT     (0x200000)
uint8_t xdata gu8TXBuf[TXBUFSIZE];
uint8_t xdata gu8RXBuf[RXBUFSIZE];


#ifdef OPT_NEIGHBOR
//S_NEIGHBOR s_neighbor[TKLIB_TOL_NUM_KEY];
#endif

typedef enum
{
    E_CMD_WAIT = 0,
    E_CMD_TYPE1_READY,
    E_CMD_TYPE2_READY,
    E_CMD_TYPE1_WRONG = 0xFE,
    E_CMD_TYPE2_WRONG = 0xFF,
} E_CMDSTS;

#define E_CALIBRATION_DONE          (0)                         /* Calibration done only */
#define E_UNDER_CALIBRATION         (1)                         /* Under calibration done */
#define E_CALIBRATION_DONE_FREERUN  (0xFF)                      /* Calibration done and save to flash */
volatile uint8_t gu8Calibration = E_CALIBRATION_DONE_FREERUN;

volatile uint8_t gu8CmdSts = E_CMD_WAIT;
volatile uint8_t gu8comRtail = 0;
volatile uint8_t gu8ChkSum = 0;
volatile uint8_t gu8RunTimeKeyInfo = 0;
extern volatile uint8_t u8EventKeyScan;

//int TK_REFCB_AutoTune_Touch(uint8_t chan);
//int TK_Calibration_Touch(uint8_t chan, uint8_t n, uint8_t m);
//int TK_Calibration_Untouch(void);
/* 8051 platform needs to take care. Due to the function is also called in ISR */
void UART_StateInit(void)
{
    gu8CmdSts = E_CMD_WAIT;
    gu8ChkSum = 0;
    gu8comRtail = 0;
}
/**
  * @brief  There are totoal 6 bytes transfer from PC.
  *         PC : Cmd + 4 paramters + Checksum
  *         DUT: ACK/NACK only
  *
  * @param[in]  Touch key information pointer
  * @param[in]  RX buffer to receive data from PC
  * @param[in]  Length
  *
  * @return     0: Continue receive.
  *             1: Escape to do calibration
  * @details    Receive command from PC
  */
int8_t TK_CmdType1(uint8_t *pu8RXBuf)
{
    int8_t i8Ret = 0;
    //uint16_t *pu16Addr;
    uint8_t u8Chan;
    uint32_t u32Data;

    S_TKFEAT* psTkFeat;
    S_KEYINFO* psKeyInfo;

#ifdef OPT_NEIGHBOR
    S_NEIGHBOR* psKeyNeighbor;
    psKeyNeighbor = TK_GetNeighborInfoPtr();
#endif

    psTkFeat = TK_GetFeaturePtr();
    psKeyInfo = TK_GetKeyInfoPtr();
#if 0
    u32Data = pu8RXBuf[1] | ((uint32_t)(pu8RXBuf[2]) << 8) | ((uint32_t)(pu8RXBuf[3]) << 16) | ((uint32_t)(pu8RXBuf[4]) << 24);
#else
    *((uint8_t *)&u32Data) = pu8RXBuf[4];   //H //8051 big endian
    *((uint8_t *)&u32Data+1) = pu8RXBuf[3];
    *((uint8_t *)&u32Data+2) = pu8RXBuf[2];
    *((uint8_t *)&u32Data+3) = pu8RXBuf[1];
#endif
    switch (*pu8RXBuf)
    {
    case E_CMD_TYPE1_SPECIFY_CHANNEL_MSK:
        psTkInfo->u32EnChanMsk = u32Data;
        break;


    case E_CMD_TYPE1_SPECIFY_SLIDER_MSK:
        psTkInfo->u32EnSliderMsk = u32Data;
        break;

    case E_CMD_TYPE1_SPECIFY_WHEEL_MSK:
        psTkInfo->u32EnWheelMsk = u32Data;
        break;

    case E_CMD_TYPE1_SPECIFY_REF_SHIELD_NO:
        psTkInfo->u8RefChan = pu8RXBuf[1];
        psTkInfo->u8ShieldChan = pu8RXBuf[2];
        psTkInfo->u8SliderRes = pu8RXBuf[3];
        psTkInfo->u8WheelRes = pu8RXBuf[4];
        break;

    case E_CMD_TYPE1_SPECIFY_FEATURE:
        psTkFeat->u8EnIIR = pu8RXBuf[1];
        psTkFeat->u8EnDebounce = pu8RXBuf[2];
        psTkFeat->u8EnBaseLineTrace = pu8RXBuf[3];
        break;

    case E_CMD_TYPE1_SPECIFY_SENSE:
        psTkInfo->u8SenPulse = pu8RXBuf[1];             /* Sense Pulse Width  */
        psTkInfo->u8SenTimes = pu8RXBuf[2];             /* Sense Times  */
        psTkInfo->u8PolarityCapacitorBank = 2; //(20200807 removed)//pu8RXBuf[3];    /* Specified the level for enabled channels on non-measured period */
        break;

    case E_CMD_TYPE1_SPECIFY_RESET_VOL:
        psTkFeat->u16ResetTime = pu8RXBuf[1] | ((uint16_t)(pu8RXBuf[2]) << 8);
        psTkInfo->u8AvcchLevel = 7; //(20200807 removed) //pu8RXBuf[3];
        break;
		
		case E_CMD_TYPE1_SPECIFY_STORE_ADDR:
        psTkInfo->u32StoreAddr = u32Data;
				break;

    case E_CMD_TYPE1_SPECIFY_NEIGHBORING:
#ifdef OPT_NEIGHBOR
#if 0
        s_neighbor[pu8RXBuf[1]].left = pu8RXBuf[2];
        s_neighbor[pu8RXBuf[1]].right = pu8RXBuf[3];
#else
        psKeyNeighbor[pu8RXBuf[1]].left = pu8RXBuf[2];
        psKeyNeighbor[pu8RXBuf[1]].right = pu8RXBuf[3];
#endif
#endif
        break;

    case E_CMD_TYPE1_START_CALIBRATION:     /* It took a long time to calibration */
#if 1                       //Light NoiseImmunity
        if (pu8RXBuf[1] == 0)
            psTkInfo->u8NoiseImmunity = 0x13;
        else if (pu8RXBuf[1] == 1)
            psTkInfo->u8NoiseImmunity = 0x12;
        else
            psTkInfo->u8NoiseImmunity = 0x23;
#else
        if (pu8RXBuf[1] == 0)   //Heavy NoiseImmunity
            psTkInfo->u8NoiseImmunity = 0x23;
        else if (pu8RXBuf[1] == 1)
            psTkInfo->u8NoiseImmunity = 0x12;
        else
            psTkInfo->u8NoiseImmunity = 0x13;
#endif
        if (pu8RXBuf[2] == 0)
        {
            /* Start Calibration */
            gu8Calibration = E_UNDER_CALIBRATION;   //20200723
            i8Ret = 1;        /* Escape code */
        }
        else
        {
            /* Start Mass-Production Test */
#ifdef MASS_FINETUNE
            gu8Calibration = E_CALIBRATION_DONE_FREERUN;   //20200723
            psTkFeat->u8BaseLineRound = 1;
            /* Install Fine Tue Time out function for Mass Producttion*/
            TK_MP_Open();
#endif
        }
        break;

    case E_CMD_TYPE1_RESET_CALIBRATION1:    /* May be after calibration stage, user fine tune these parameter */
        u8Chan = pu8RXBuf[1];
        //S_KeyInfo[u8Chan].ccb = pu8RXBuf[2];
        //S_KeyInfo[u8Chan].refcb = pu8RXBuf[3];
        (psKeyInfo+u8Chan)->ccb  = pu8RXBuf[2];
        (psKeyInfo+u8Chan)->refcb = pu8RXBuf[3];
        break;

    case E_CMD_TYPE1_RESET_CALIBRATION2:
        u8Chan = pu8RXBuf[1];
        //S_KeyInfo[u8Chan].level = pu8RXBuf[2];
        //S_KeyInfo[u8Chan].threshold = pu8RXBuf[3];
        (psKeyInfo+u8Chan)->level  = pu8RXBuf[2];
        (psKeyInfo+u8Chan)->threshold = pu8RXBuf[3];

        break;

    case E_CMD_TYPE1_WRITE_CALIBRATION:
        TK_SavePara();                                  /* After save parameter, Enable free run */
        //gu8Calibration = E_CALIBRATION_DONE_FREERUN;    /* Calibration done, enable free run */ //20200723
        break;

    case E_CMD_TYPE1_LOAD_CALIBRATION:
        TK_LoadPara(&u32Data);
        break;
    case E_CMD_TYPE1_START_RUN_TIME_SCAN_KEY:
        gu8RunTimeKeyInfo = 1;
        {
            uint8_t chan; 
            for(chan = 0; chan < TKLIB_TOL_NUM_KEY; chan = chan+1)
            {	
                (psKeyInfo+chan)->level = 0;
            }
        }
        i8Ret = 2;
        break;
    case E_CMD_TYPE1_ESCAPE_RUN_TIME_SCAN_KEY:
        gu8RunTimeKeyInfo = 0;
        i8Ret = 3;
        break;
    case E_CMD_TYPE1_ESCAPE_APPLICATION:
        /* Escap to free run case */
        break;
    case E_CMD_TYPE1_IIR_PARAMETER:
        //S_TkFeat.u8IIRNew = pu8RXBuf[1];
        //S_TkFeat.u8IIROld = pu8RXBuf[2];
        psTkFeat->u8IIRNew = pu8RXBuf[1];
        psTkFeat->u8IIROld = pu8RXBuf[2];
        break;
    case E_CMD_TYPE1_DEBOUNCE_PARAMETER:
        //S_TkFeat.u8Entry = pu8RXBuf[1];
        //S_TkFeat.u8Escape = pu8RXBuf[2];
        psTkFeat->u8Entry = pu8RXBuf[1];
        psTkFeat->u8Escape = pu8RXBuf[2];
        break;
    default:
        gu8TXBuf[0] = 'N';
        TK_SendChars(gu8TXBuf, 1);
        return i8Ret;
    }

    gu8TXBuf[0] = 'A';
    TK_SendChars(gu8TXBuf, 1);

    //UART_WAIT_TX_EMPTY(UART0);  /* Unnecessary due TK_SendChars() will wait until complete */
    return i8Ret;
}

/**
  * @brief  There are totoal 3 bytes transfer from PC.
  *         PC : Cmd + 1 parametr + Checksum
  *         DUT: 4 parameters + 1 byte ACK/NACK only
  *
  * @param[in]  Touch key information pointer
  * @param[in]  RX buffer to receive data from PC
  * @param[in]  Length
  *
  * @return     0: Continue receive.
  *             1: Escape to do calibration
  * @details    Receive command from PC
  */
int8_t TK_CmdType2(uint8_t *pu8RXBuf)
{
    int8_t i8Ret = 0;
    uint8_t chan;
    uint32_t u32KeyStoreAddr;
    S_TKINFO* psTkInfo;
    S_TKFEAT* psTkFeat;
    S_KEYINFO* psKeyInfo;
	
#ifdef OPT_NEIGHBOR
    S_NEIGHBOR* psKeyNeighbor;
    psKeyNeighbor = TK_GetNeighborInfoPtr();
#endif
    psTkFeat = TK_GetFeaturePtr();
    psKeyInfo = TK_GetKeyInfoPtr();
    psTkInfo = TK_GetTKInfoPtr();
	
    u32KeyStoreAddr = psTkInfo->u32StoreAddr + PAGE_SIZE; 
	
#if 0
    memset(&gu8TXBuf, 0x0, 5);
#else
    for(chan = 0; chan<5; chan=chan+1)
    {
        gu8TXBuf[chan] = 0x0;
    }
#endif

    switch (*pu8RXBuf)
    {
    case E_CMD_TYPE2_READ_CHANNEL_MSK:
#if 0
        gu8TXBuf[0] = psTkInfo->u32EnChanMsk;
        gu8TXBuf[1] = psTkInfo->u32EnChanMsk >> 8;
        gu8TXBuf[2] = psTkInfo->u32EnChanMsk >> 16;
        gu8TXBuf[3] = psTkInfo->u32EnChanMsk >> 24;
#else
        //gu8TXBuf[0] = *((uint8_t *)&psTkInfo->u32EnChanMsk);
        //gu8TXBuf[1] = *((uint8_t *)&psTkInfo->u32EnChanMsk+1);
        //gu8TXBuf[2] = *((uint8_t *)&psTkInfo->u32EnChanMsk+2);
        //gu8TXBuf[3] = *((uint8_t *)&psTkInfo->u32EnChanMsk+3);
        gu8TXBuf[0] = *((uint8_t *)&psTkInfo->u32EnChanMsk+3);
        gu8TXBuf[1] = *((uint8_t *)&psTkInfo->u32EnChanMsk+2);
        gu8TXBuf[2] = *((uint8_t *)&psTkInfo->u32EnChanMsk+1);
        gu8TXBuf[3] = *((uint8_t *)&psTkInfo->u32EnChanMsk);
#endif
        break;

    case E_CMD_TYPE2_READ_SLIDER_MSK:
#if 0
        gu8TXBuf[0] = psTkInfo->u32EnSliderMsk;
        gu8TXBuf[1] = psTkInfo->u32EnSliderMsk >> 8;
        gu8TXBuf[2] = psTkInfo->u32EnSliderMsk >> 16;
        gu8TXBuf[3] = psTkInfo->u32EnSliderMsk >> 24;
#else
        //gu8TXBuf[0] = *((uint8_t *)&psTkInfo->u32EnSliderMsk);
        //gu8TXBuf[1] = *((uint8_t *)&psTkInfo->u32EnSliderMsk+1);
        //gu8TXBuf[2] = *((uint8_t *)&psTkInfo->u32EnSliderMsk+2);
        //gu8TXBuf[3] = *((uint8_t *)&psTkInfo->u32EnSliderMsk+3);
        gu8TXBuf[0] = *((uint8_t *)&psTkInfo->u32EnSliderMsk+3);
        gu8TXBuf[1] = *((uint8_t *)&psTkInfo->u32EnSliderMsk+2);
        gu8TXBuf[2] = *((uint8_t *)&psTkInfo->u32EnSliderMsk+1);
        gu8TXBuf[3] = *((uint8_t *)&psTkInfo->u32EnSliderMsk);
#endif
        break;

    case E_CMD_TYPE2_READ_WHEEL_MSK:
#if 0
        gu8TXBuf[0] = psTkInfo->u32EnWheelMsk;
        gu8TXBuf[1] = psTkInfo->u32EnWheelMsk >> 8;
        gu8TXBuf[2] = psTkInfo->u32EnWheelMsk >> 16;
        gu8TXBuf[3] = psTkInfo->u32EnWheelMsk >> 24;
#else
        //gu8TXBuf[0] = *((uint8_t *)&psTkInfo->u32EnWheelMsk);
        //gu8TXBuf[1] = *((uint8_t *)&psTkInfo->u32EnWheelMsk+1);
        //gu8TXBuf[2] = *((uint8_t *)&psTkInfo->u32EnWheelMsk+2);
        //gu8TXBuf[3] = *((uint8_t *)&psTkInfo->u32EnWheelMsk+3);
        gu8TXBuf[0] = *((uint8_t *)&psTkInfo->u32EnWheelMsk+3);
        gu8TXBuf[1] = *((uint8_t *)&psTkInfo->u32EnWheelMsk+2);
        gu8TXBuf[2] = *((uint8_t *)&psTkInfo->u32EnWheelMsk+1);
        gu8TXBuf[3] = *((uint8_t *)&psTkInfo->u32EnWheelMsk);
#endif
        gu8TXBuf[4] = 'A';
        break;

    case E_CMD_TYPE2_READ_REF_SHIELD_NO:
        gu8TXBuf[0] = psTkInfo->u8RefChan;
        gu8TXBuf[1] = psTkInfo->u8ShieldChan;
        if(pu8RXBuf[1] == 0)
        {
            gu8TXBuf[2] = psTkInfo->u8SliderRes;
            gu8TXBuf[3] = i8SliderPercentage;
        }
        else
        {
            gu8TXBuf[2] = psTkInfo->u8WheelRes;
            gu8TXBuf[3] = i8WheelPercentage;
        }
        break;

    case E_CMD_TYPE2_READ_FEATURE:
        gu8TXBuf[0] = psTkFeat->u8EnIIR;
        gu8TXBuf[1] = psTkFeat->u8EnDebounce;
        gu8TXBuf[2] = psTkFeat->u8EnBaseLineTrace;
        //gu8TXBuf[3] = 0x0;
        break;

    case E_CMD_TYPE2_READ_SENSE:
        gu8TXBuf[0] = psTkInfo->u8SenPulse;
        gu8TXBuf[1] = psTkInfo->u8SenTimes;
        gu8TXBuf[2] = psTkInfo->u8PolarityCapacitorBank;
        //gu8TXBuf[3] = 0x0;
        break;

    case E_CMD_TYPE2_READ_RESET_VOL:
        gu8TXBuf[0] = psTkFeat->u16ResetTime;
        gu8TXBuf[1] = psTkFeat->u16ResetTime >> 8;
        gu8TXBuf[2] = psTkInfo->u8AvcchLevel;
        //gu8TXBuf[3] = 0x0;
        break;
		case E_CMD_TYPE2_READ_STORE_ADDR:
        gu8TXBuf[0] = *((uint8_t *)&psTkInfo->u32StoreAddr+3);
        gu8TXBuf[1] = *((uint8_t *)&psTkInfo->u32StoreAddr+2);
        gu8TXBuf[2] = *((uint8_t *)&psTkInfo->u32StoreAddr+1);
        gu8TXBuf[3] = *((uint8_t *)&psTkInfo->u32StoreAddr);
        break;

    case E_CMD_TYPE2_READ_NEIGHBORING:
#ifdef OPT_NEIGHBOR
        gu8TXBuf[0] = psKeyNeighbor[pu8RXBuf[1]].left;
        gu8TXBuf[1] = psKeyNeighbor[pu8RXBuf[1]].right;
#endif
        break;

    //case E_CMD_TYPE2_CHECK_CALIBRATION_DONE:      /* Handle in interrupt handler */
    //   break;
    case E_CMD_TYPE2_GET_CALIBRATION1:
        chan = *(pu8RXBuf + 1);
        if(chan & 0x80)
        {
            chan &= ~0x80;
            gu8TXBuf[0] = inp8(u32KeyStoreAddr + TK_CCB_OFFSET + chan * 4);
            gu8TXBuf[1] = inp8(u32KeyStoreAddr + TK_REFCB_OFFSET + chan * 4);
        }
        else
        {
            gu8TXBuf[0] = (psKeyInfo+chan)->ccb;
            gu8TXBuf[1] = (psKeyInfo+chan)->refcb;
        }
        break;

    case E_CMD_TYPE2_GET_CALIBRATION2:
        chan = *(pu8RXBuf + 1);
        if(chan & 0x80)
        {
            /* MSB bit = 1 to get manufactory setting */
            uint8_t u8Level;

            chan &= ~0x80;
            u8Level = inp8(u32KeyStoreAddr + TK_LEVEL_OFFSET + chan * 4);
            gu8TXBuf[0] = u8Level;
            u8Level = inp8(u32KeyStoreAddr + TK_THRESHOLD_OFFSET + chan * 4);
            gu8TXBuf[1] = u8Level;
        }
        else
        {
            /* MSB bit = 0 to do calibration flow for signal and threshold */
            TK_Calibration_Touch(chan, (psTkInfo->u8NoiseImmunity>>4), (psTkInfo->u8NoiseImmunity&0x0F));
            gu8TXBuf[0] = (psKeyInfo+chan)->level;
            gu8TXBuf[1] = (psKeyInfo+chan)->threshold;
        }
        break;

    case E_CMD_TYPE2_RUNTIME_KEY_INFO:
        i8Ret = 1;
        break;
    case E_CMD_TYPE2_GET_IIR_PARAMETER:
        gu8TXBuf[0] = psTkFeat->u8IIRNew;
        gu8TXBuf[1] = psTkFeat->u8IIROld;
        break;
    case E_CMD_TYPE2_GET_DEBOUNCE_PARAMETER:
        gu8TXBuf[0] = psTkFeat->u8Entry;
        gu8TXBuf[1] = psTkFeat->u8Escape;
        break;
    case E_CMD_TYPE2_SET_SCAN_KEY:
        if(pu8RXBuf[1] == 0)
        {
            gu8Calibration = E_CALIBRATION_DONE;
					  TickClearTickEvent(i8KeyScanId);
        }
        else
        {
            gu8Calibration = E_CALIBRATION_DONE_FREERUN;
					  i8KeyScanId = TickSetTickEvent(1, TickCallback_KeyScan);
        }
        break;

#if defined(MASS_FINETUNE)
    case E_CMD_TYPE2_GET_UID:
        gu8TXBuf[0] = (USER_ID&&0xFF000000)>>24;
        gu8TXBuf[1] = (USER_ID&0xFF0000)>>16;
        gu8TXBuf[2] = (USER_ID&0xFF00)>>8;
        gu8TXBuf[3] = (USER_ID&0xFF);
        break;

#endif
    case E_CMD_TYPE2_FIRMWARE_VERSION:/* 2020-0324 */
        if(pu8RXBuf[1] == 0)
        {
            gu8TXBuf[0] = FIRMWARE_MAJOR_VERSION;
            gu8TXBuf[1] = FIRMWARE_MINOR_VERSION;
        }
        else
        {
            gu8TXBuf[0] = TKLIB_MAJOR_VERSION;
            gu8TXBuf[1] = TKLIB_MINOR_VERSION;
        }
        gu8TXBuf[2] = TOUCHKEY_VERSION;
        break;
    default:
        gu8TXBuf[4] = 'N';
        TK_SendChars(gu8TXBuf, 5);
        return i8Ret;
    }
    gu8TXBuf[4] = 'A';
    TK_SendChars(gu8TXBuf, 5);
    return i8Ret;
}
xdata void (code *f)(void);
void TK_RawDataView(void);
int8_t TK_GetPacket(uint32_t* pu32ChanelMsk)
{
    int8_t i8Ret = 0;
    uint8_t u8checkSum = 0;

    //S_KEYINFO* psKeyInfo;
    //psKeyInfo = TK_GetKeyInfoPtr();
    do
    {
        if (gu8CmdSts == E_CMD_TYPE1_READY)
        {
            /* i8Ret will be set to 1 if E_CMD_TYPE1_START_CALIBRATION command */
            i8Ret = TK_CmdType1(gu8RXBuf);
            UART_StateInit();
        }

        if (gu8CmdSts == E_CMD_TYPE2_READY)
        {
            /* i8Ret will always 0 */

            i8Ret = TK_CmdType2(gu8RXBuf);
            UART_StateInit();
        }

        if (gu8CmdSts == E_CMD_TYPE1_WRONG)
        {
#if 0
            while (UART_IS_TX_FULL(UART0)); /* Wait Tx is not full to transmit data */
            UART_WRITE(UART0, 'N');
#else
            gu8TXBuf[0] = 'N';
            TK_SendChars(gu8TXBuf, 1);
#endif
            UART_StateInit();
        }

        if (gu8CmdSts == E_CMD_TYPE2_WRONG)
        {
            uint8_t i;
            uint8_t u8Arry[5] = {0};

            u8Arry[4] = 'N';

            for (i = 0; i < 5; i = i + 1)
                TK_SendChars(&u8Arry[i], 1);
            UART_StateInit();
        }
        
        if(gu8Calibration == E_CALIBRATION_DONE_FREERUN)
        {
            TK_RawDataView();
        }

#ifdef OPT_USE_SEVEN_SEGMENT
        if (u8EventDisp7Segment == 1)
        {

        }
#endif
    }
    while (i8Ret == 0);  /* Escape the loop until E_CMD_TYPE1_START_CALIBRATION command */

    *pu32ChanelMsk = (psTkInfo->u32EnChanMsk) | ((psTkInfo->u32EnSliderMsk | psTkInfo->u32EnWheelMsk)\
                     | (1UL<<psTkInfo->u8RefChan));

    if(psTkInfo->u8ShieldChan != 0xFF)
        *pu32ChanelMsk = *pu32ChanelMsk | (1UL<<psTkInfo->u8ShieldChan);

    return i8Ret;
    /* Escape as receive start cablibration */
}


void Serial_ISR (void) interrupt 4 //using 1
{
    uint8_t u8CmdType;
    S_KEYINFO* psKeyInfo;
    S_TKFEAT* psTkFeat;

    psKeyInfo = TK_GetKeyInfoPtr();
    psTkFeat = TK_GetFeaturePtr();
    if (TI)
    {
        td_flag = 1;
        clr_SCON_TI;                                       /* Clear TI (Transmit Interrupt) */
        return;
    }
    if (RI)
    {
        gu8RXBuf[gu8comRtail] = SBUF;
        clr_SCON_RI;                                       /* Clear RI (Receive Interrupt) */
        gu8ChkSum += gu8RXBuf[gu8comRtail];
        gu8comRtail = gu8comRtail + 1;
    }
    if ((gu8RXBuf[0] >= 0x0) && (gu8RXBuf[0] <= E_CMD_TYPE1_NUM_LAST_COMMAND))
    {
        u8CmdType = 1;
    }
    else if ((gu8RXBuf[0] >= 'A') && (gu8RXBuf[0] <= E_CMD_TYPE1_LAST_COMMAND))
    {
        u8CmdType = 1;
    }
    else
    {
        u8CmdType = 2;    /* Cmd = 0x10 ~ 0x16, 'a' ~ 'd' */
    }

    if (u8CmdType == 1)
    {
        do
        {
            if (RI)
            {
                gu8RXBuf[gu8comRtail] = SBUF;
                clr_SCON_RI;                                         /* Clear RI (Receive Interrupt) */
                if(gu8comRtail < 5)
                    gu8ChkSum += gu8RXBuf[gu8comRtail];
                gu8comRtail++;
            }
        }
        while(gu8comRtail<6);

        if (gu8RXBuf[5] == gu8ChkSum)
        {
            gu8CmdSts = E_CMD_TYPE1_READY;
        }
        else
        {
            gu8CmdSts = E_CMD_TYPE1_WRONG;
        }
    }

    if (u8CmdType == 2)
    {
        /* E_RX_CMD_TYPE2_SIZE (3) */
        do
        {
            if (RI)
            {
                gu8RXBuf[gu8comRtail] = SBUF;
                clr_SCON_RI;                                         /* Clear RI (Receive Interrupt) */
                if(gu8comRtail < 2)
                    gu8ChkSum += gu8RXBuf[gu8comRtail];
                gu8comRtail++;
            }
        }
        while(gu8comRtail<3);

        if (gu8RXBuf[2] == gu8ChkSum)
            gu8CmdSts = E_CMD_TYPE2_READY;
        else
            gu8CmdSts = E_CMD_TYPE2_WRONG;
    }

    /* Process the run-time event - E_CMD_TYPE2_CHECK_CALIBRATION_DONE */
    if ((gu8RXBuf[0] == E_CMD_TYPE2_CHECK_CALIBRATION_DONE) &&
            (gu8CmdSts == E_CMD_TYPE2_READY))
    {
        /* Run time get calibration status */
        uint8_t i;
        uint8_t u8Arry[5] = {0};
        if(psTkFeat->u8BaseLineRound != 1)
        {
            /* Polling Calibration done */
            if(gu8Calibration == E_UNDER_CALIBRATION)
                u8Arry[0] = 0;      /* return 0 means under calibration (untouch calibration) */
            else if(gu8Calibration == E_CALIBRATION_DONE)
                u8Arry[0] = 1;      /* return 1 means calibration done */
        }
        else
        {
#if defined(MASS_FINETUNE)
            /* Polling Mass-Productio done */
            if(gbIsFineTuneDone == 1)
            {
                u8Arry[0]  = 1;                      /* done    */
                if(gFineTuneDoneTimeOut == 1)
                    u8Arry[1] = 0;                   /* result: 1:pass, 0:fail  */
                else
                    u8Arry[1] = 1;
                psTkFeat->u8BaseLineRound = TRACK_BASELINE_RELOAD_TIME;
            }
            else
            {
                u8Arry[0]  = 0;   /* not done */
                u8Arry[1] = 0;    /* result   */
            }
#endif
        }
        u8Arry[4] = 'A';

        UART_StateInit();
        for (i = 0; i < 5; i = i + 1)
        {
            SBUF = u8Arry[i];      /* output character */
            while (!TI);           /* wait until transmitter complete */
            clr_SCON_TI;
        }
    }

    /* Process the run-time event - E_CMD_TYPE2_RUNTIME_KEY_INFO */
    if ((gu8RXBuf[0] == E_CMD_TYPE2_RUNTIME_KEY_INFO) &&
            (gu8CmdSts == E_CMD_TYPE2_READY))  /* Run time get Touch data */
    {

        uint8_t i;
        uint8_t u8Arry[5] = {0};
        uint8_t ch = gu8RXBuf[1];
	#if 1			
        u8Arry[0] = (psKeyInfo+ch)->ccb;
        u8Arry[1] = (psKeyInfo+ch)->refcb;
        u8Arry[2] = (psKeyInfo+ch)->level;
        u8Arry[3] = (psKeyInfo+ch)->threshold;
	#else /* Save 11 bytes ROM space. inc 6 bytes RAM space. But not verify yet */
        uint32_t *pu32Src, *pu32Dst;
        pu32Src = (psKeyInfo+ch);
        pu32Dst = (uint32_t*)u8Arry;
				*pu32Dst = *pu32Src;
  #endif				

        u8Arry[4] = 'A';
        for (i = 0; i < 5; i = i + 1)
        {
            SBUF = u8Arry[i];      /* output character */
            while (!TI);           /* wait until transmitter complete */
            clr_SCON_TI;
        }
        UART_StateInit();
    }
}

void UART_SetCalibrationDone(void)
{
    gu8Calibration = E_CALIBRATION_DONE;     /* 0 mean not under calibration */
}


