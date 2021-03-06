#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ML51.h"
//#include "TK_Demo.h"

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
void TK_lightLED(unsigned char onOff, int chanN)
{
#ifdef BOARD_TIM
    /* Removed @ 20200828 */    
#else
    /* PY */
    if( (chanN >= 3) && (chanN <= 6) )
    {
        if(onOff == 1)      //On
            P1 = P1 & ~(1UL<<(6-chanN));
        else                //Off
            P1 = P1 | (1UL<<(6-chanN));
    }
    //TK3 --> P1.3
    //TK4 --> P1.2
    //TK5 --> P1.1
    //TK6 --> P1.0
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

#ifdef BOARD_TIM
    /* Removed @ 20200828 */
#else
    /* PY */
    /*
    If P13 set to 1,  KEY4 LED will be turn off. If P13 set to 0,  KEY4 LED will be turn on.
    If P12 set to 1,  KEY3 LED will be turn off. If P12 set to 0,  KEY3 LED will be turn on.
    If P11 set to 1,  KEY2 LED will be turn off. If P11 set to 0,  KEY2 LED will be turn on.
    If P10 set to 1,  KEY1 LED will be turn off. If P10 set to 0,  KEY1 LED will be turn on.
    */
    P1 = P1 | 0x0F;
    //P10_PUSHPULL_MODE;
    //P11_PUSHPULL_MODE;
    //P12_PUSHPULL_MODE;
    //P13_PUSHPULL_MODE;
    P10_QUASI_MODE;
    P11_QUASI_MODE;
    P12_QUASI_MODE;
    P13_QUASI_MODE;
#endif
}
#endif
