#include "ML51.h"
/******************************************************************************
 * SysTick is used as system time base.
 * It provided upper to install/remove callback function.
 * Initial sysTick function: Init_SysTick()
 * Install callback function: TickSetTickEvent()
 * Remove callback function: TickClearTickEvent()
 ******************************************************************************/
typedef void (*sys_pvTimeFunPtr)(void);   /* function pointer */
typedef struct timeEvent_t
{
    uint8_t             active;
    unsigned long       initTick;
    unsigned long       curTick;
    sys_pvTimeFunPtr    funPtr;
} TimeEvent_T;

#define TRUE                    1
#define FALSE                   0
#define TICKEVENTCOUNT         (3)                      /* 1 ~ 3 */
volatile  TimeEvent_T tTime0Event[TICKEVENTCOUNT];
volatile uint8_t xdata _sys_uTime0EventCount = 0;             /* Speed up interrupt reponse time if no callback function */
volatile uint32_t xdata u32Tick = 0;

#if 1 /* 45 byte */
void TickClearTickEvent(uint8_t u8TimeEventID)
{
    if(u8TimeEventID > TICKEVENTCOUNT)
        return;
    if (tTime0Event[u8TimeEventID].active == TRUE)
    {
        tTime0Event[u8TimeEventID].active = FALSE;
        _sys_uTime0EventCount--;
    }
}
#endif
#if 1  //(1124-846= 278)
char TickSetTickEvent(unsigned long uTimeTick, void* pvFun)
{
    int  i;
    int u8TimeEventID = 0;

    for (i = 0; i < TICKEVENTCOUNT; i++)
    {
        if (tTime0Event[i].active == FALSE)
        {
            tTime0Event[i].active = TRUE;
            tTime0Event[i].initTick = uTimeTick;
            tTime0Event[i].curTick = uTimeTick;
            tTime0Event[i].funPtr = (sys_pvTimeFunPtr)pvFun;
            u8TimeEventID = i;
            _sys_uTime0EventCount += 1;
            break;
        }
    }

    if (i == TICKEVENTCOUNT)
    {
        return -1;    /* -1 means invalid channel */
    }
    else
    {
        return u8TimeEventID;    /* Event ID start from 0*/
    }
}

#endif


/******************************************************************************
 Using Timer 2 Auto Reload as systick

 ******************************************************************************/
#if 0 // 1536 - 1124 = 412 
uint16_t Timer2_AutoReload(uint16_t u16SysKHz, uint16_t u16CallbackPerHz, uint8_t u32PreDiv)
{
    uint16_t u16Reload = 0xFFFF - ((1000/u16CallbackPerHz)*(u16SysKHz/u32PreDiv));
    return u16Reload;
}
void Init_SysTick(void)
{
    uint8_t i;
    uint16_t u16Reload;


    /* Init systick */
    TIMER2_DIV_16;
    TIMER2_DELAY_MODE;                              /* Timer2 Auto Reload Mode */
    u16Reload = Timer2_AutoReload(24000, 50, 16);
	  
    SFRS = 1;                                       /* Following register located on page 1 */
    RCMP2H = u16Reload>>8;
    RCMP2L = (uint8_t)u16Reload;
    SFRS = 0;

    /* Remove all callback function */
    for (i = 0; i < TICKEVENTCOUNT; i++)
        TickClearTickEvent(i);
    _sys_uTime0EventCount = 0;

    set_EIE0_ET2;     //Enable timer 2
    set_T2CON_TR2;    //Start timer 2
}
#else // 1155 - 1124 = 31 
void Init_SysTick(void)
{
    uint8_t i;
    _sys_uTime0EventCount = 0;
    TIMER2_DIV_16;
    TIMER2_DELAY_MODE;

    SFRS=1;    /* Page 1 */
    RCMP2H = 0x8A;
    RCMP2L = 0xCF;
    SFRS=0;    /* Page 1 */

    /* Remove all callback function */
    for (i = 0; i < TICKEVENTCOUNT; i++)
        TickClearTickEvent(i);
    _sys_uTime0EventCount = 0;

    set_EIE0_ET2;     //Enable timer 2
    set_T2CON_TR2;    //Start timer 2
}
#endif


#if 1  //1459 - 1155 = 304
void Timer2_ISR (void) interrupt 5
{
    uint8_t i;

    clr_T2CON_TF2;                                //Clear Timer2 Interrupt Flag

    u32Tick += 1;
    if (u32Tick >= 0xfffffff)
    {
        u32Tick = 0;
    }

    if (_sys_uTime0EventCount)
    {
        for (i = 0; i < TICKEVENTCOUNT; i++)
        {
            if (tTime0Event[i].active)
            {
                tTime0Event[i].curTick--;

                if (tTime0Event[i].curTick == 0)
                {
                    (*tTime0Event[i].funPtr)();
                    tTime0Event[i].curTick = tTime0Event[i].initTick;
                }
            }
        }
    }
}
#endif