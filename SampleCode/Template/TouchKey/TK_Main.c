#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ML51.h"
#include "TKLib.h"
#include "TK_Demo.h"

volatile uint8_t u8EventKeyScan = 0;
volatile int8_t i8SliderPercentage = 0;
volatile int8_t i8WheelPercentage = 0;
volatile int8_t i8KeyScanId;

#ifdef MASS_FINETUNE
void TK_MassProduction(int8_t* pai8Signal);
#endif

void TickCallback_KeyScan(void)
{
    u8EventKeyScan = 1;
}

/**
  *  Report touching or un-touching state depends on debounce parameter you set on calibration statge
  *  For example,
  *      TK_ScanKey() may report someone key pressed but its signal is less than threshold of the key.
  *      The root cause is the key still under debouce stage.
  */
void TK_RawDataView(void)
{

#ifndef BOARD_TIM
    static int8_t i8LedChan = 0;
    uint8_t u8ch;
#endif
    int8_t i8Ret = 0;
    xdata int8_t ai8Signal[TKLIB_TOL_NUM_KEY];
    int8_t ai8TmpSignal[TKLIB_TOL_NUM_KEY];
    if (u8EventKeyScan == 1)
    {
        uint8_t i;
        u8EventKeyScan = 0;
        /**
          * TK_ScanKey() scan all enable key, slider and wheel channels.
          * i8Ret : Key/slider/wheel channel with max amplitude. -1: means no any key's amplitude over the key's threshold.
          * ai8Signal[]: The buffer size is equal to the ML56 TK channels. It reports the signal amplitude on this round
          */
        i8Ret = TK_ScanKey(&ai8Signal[0]);
			
#ifndef BOARD_TIM
        if (i8Ret != -1)
        {
            if (i8LedChan != i8Ret)
            {
                TK_lightLED(FALSE, i8LedChan);
                i8LedChan = i8Ret;
            }
            TK_lightLED(TRUE, i8Ret);
        }
        else
        {
            TK_lightLED(FALSE, 3);
            TK_lightLED(FALSE, 4);
            TK_lightLED(FALSE, 5);
            TK_lightLED(FALSE, 6);
        }
#endif

#ifdef MASS_FINETUNE
        TK_MassProduction(ai8Signal);
#endif

#if defined(OPT_SLIDER)
        {
            /** To save buffer size, re-used the ai8Signal[] buffer
              * Remember that the buffer will be destroied
              */
            uint16_t u16ChnMsk; /* ML56 is only 15 TK channels */
            uint8_t u8Count = 0, i;
            static uint8_t updatecount = 0;

            updatecount = updatecount+1;
            if(updatecount < 5)
                return;
            updatecount = 0;

            u16ChnMsk = TK_GetEnabledChannelMask(TK_SLIDER);

            if(TK_CheckSliderWheelPressed(TK_SLIDER) == 1)
            {
                for (i = 0; i < TKLIB_TOL_NUM_KEY ; i++)
                {
                    if (u16ChnMsk & (1ul << i))
                    {
                        ai8TmpSignal[u8Count] = ai8Signal[i];
                        u8Count = u8Count+1;
                    }
                }
                i8SliderPercentage = TK_SliderPercentage(ai8TmpSignal, u8Count);
            }
        }
#endif
#if defined(OPT_WHEEL)
        {
            /** To save buffer size, re-used the ai8Signal[] buffer
              * Remember that the buffer will be destroied
              */
            uint32_t u32ChnMsk; /* ML56 is only 15 TK channels */
            uint8_t u8Count = 0, i;

            u32ChnMsk = TK_GetEnabledChannelMask(TK_WHEEL);

            if(TK_CheckSliderWheelPressed(TK_WHEEL)  == 1)
            {
                for (i = 0; i < TKLIB_TOL_NUM_KEY ; i++)
                {
                    if (u32ChnMsk & (1ul << i))
                    {
                        ai8TmpSignal[u8Count] = ai8Signal[i];
                        u8Count = u8Count+1;
                    }
                }
                i8WheelPercentage = TK_WheelPercentage(ai8TmpSignal, u8Count);
                DBG_PRINTF("Wheel %bd\n", i8WheelPercentage);
            }
        }
#endif
    }
}


void main(void)
{
    uint32_t u32ChanelMsk;
    int8_t i8Ret = 0;

#ifdef  DEMO_CALIBRATION
    UART0_Init();
#endif

#ifdef UART1_DBG
    UART1_Init();
#endif

#ifndef BOARD_TIM
    InitLEDIO();
#endif

    /* Initialize FMC to Load TK setting and calibration data from flash */
    FMC_Open();
	 
    i8Ret = TK_LoadPara(&u32ChanelMsk);
#ifdef DEMO_CALIBRATION
    
    EA=1;
    if(i8Ret == -1)
    {
        /** i8Ret = -1 means that no any calibration data stored in flash
          * If no any data stored in flash. Get TK setting and calibration data from UART port
          * Program will be blocked in the function until received START_CALIBRATION command. The return vlue will be 1
          */
        i8Ret = TK_GetPacket(&u32ChanelMsk);
    }
    /* Init TK Controller */
    TK_Init();

    /* Initialize Multiple Function Pins for TK */
    SetTkMultiFun(u32ChanelMsk);

    /* Init systick 20ms/tick */
    Init_SysTick();

    /* Install Tick Event Handler To Drive Key Scan */
    i8KeyScanId = TickSetTickEvent(1, TickCallback_KeyScan);

    do
    {
        if(i8Ret == 1)
        {
            /** Receive Start calibration command
              * The function will be blocked until calibration done
              */
            TK_Calibration_Untouch();
            /* Inform UART module calibration done */
            UART_SetCalibrationDone();
        }
        i8Ret = TK_GetPacket(&u32ChanelMsk);

        /** May change configurations through UART port
          * Init TK Controller again
          */
        TK_Init();

        /* Initialize Multiple Function Pins for TK again */
        SetTkMultiFun(u32ChanelMsk);
    }
    while(1);
#endif /* DEMO_CALIBRATION */

#ifdef DEMO_FREERUN
    if(i8Ret < 0)
    {
        /* DBG_PRINTF("Please run target TK_Application first to calibrate touchkey\n"); */
        while(1);
    }

    /* Init TK Controller */
    TK_Init();

    /* Initialize Multiple Function Pins for TK */
    SetTkMultiFun(u32ChanelMsk);

    /* Init systick 20ms/tick */
    Init_SysTick();

    /* Install Tick Event Handler To Drive Key Scan */
    TickSetTickEvent(1, TickCallback_KeyScan);

    set_IE_EA;
    do
    {
        TK_RawDataView();
    }
    while (1);
#endif  /* DEMO_FREERUN */

}


