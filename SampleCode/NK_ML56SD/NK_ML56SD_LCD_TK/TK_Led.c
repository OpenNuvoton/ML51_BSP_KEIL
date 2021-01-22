
#include "ML51.h"
#include "TK_Demo.h"

#define OPT_USE_LED
/**********************************************************************************
Tim:
 P25 = LED3 for TK3
 P24 = LED2 for TK4
 P23 = LED1 for TK5
 P22 = LED0 for TK6

 PY:
 P13 = LED3 for TK3
 P12 = LED2 for TK4
 P11 = LED1 for TK5
 P10 = LED0 for TK6
 **********************************************************************************/
#ifdef OPT_USE_LED
typedef struct tagLEG
{
    unsigned char u8Addr;
    unsigned char u8Msk;
} LED_T;

/**
  * @brief      Light the led(s)
  * @param[in]  onOff    0: Touch Key LED turn off
  *                      1: Touch Key LED turn on
  * @param[in]  chanN    the channel number to be configured. (TK1 = 1, TK2 = 2, TK3 = 3, TK4 = 4)
  * @retval     None.
  * @details    This function is used to light the led(s)
  */
void TK_lightLED(bit onOff, int chanN)
{
	unsigned char temp;
#ifdef BOARD_NUMAKER
    P00 = onOff;
    temp = chanN;
#endif
}

/**
  * @brief      Initialize touch key LED output state
  * @param      None.
  * @retval     None.
  * @details    This function is used to initialize touch key LED output state. Default MFP is GPIO
  *             Foe code size, not to set MFP regster.
  */
void InitLEDIO(void)
{

#ifdef BOARD_NUMAKER   /*For NuMaker */
    P00_QUASI_MODE;
    P00 = 0;
#endif
}
#endif
