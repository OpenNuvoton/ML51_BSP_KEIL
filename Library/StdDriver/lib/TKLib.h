#ifndef __TKLIB_H__
#define __TKLIB_H__

#define DBG_PRINTF                  //printf

#define OPT_NEIGHBOR                                       /* Using for neighboring keys as shielding */
#define TKLIB_TOL_NUM_KEY           (15)                   /* TK0 ~ TK14 */

#define TK_ADDR_PARAM_DFLASH        (0x00EE80)             /* Reserved 4K LDROM + 3 Pages */
//#define TK_ADDR_PARAM_DFLASH        (0x00F680)             /* Reserved 2K LDROM + 3 Pages */
//#define TK_ADDR_KEY_PARM            (0x00FF00)
//#define TK_ADDR_NEIGHBOR            (0x00FF80)
#define TK_MAX_STOR_ADDR            TK_ADDR_PARAM_DFLASH   /* Reserved 4K LDROM */

#define TK_CCB_OFFSET               (0)
#define TK_REFCB_OFFSET             (1)
#define TK_LEVEL_OFFSET             (2)
#define TK_THRESHOLD_OFFSET         (3)

#define DEBOUNCE_ENTRY              (5)
#define DEBOUNCE_ESCAPE             (6)

#define E_NOISE_OVER_DEBOUNCED      (0)
#define E_SIGNAL_UNDER_DEBOUNCED    (1)
#define E_SIGNAL_OVER_DEBOUNCED     (2)

#define TRACK_SIGNAL_MIN_RANGE      (30)         /* Signal < MIN_LEVEL will be tracked Baseline */
#define TRACK_BASELINE_RELOAD_TIME  (25)         /* Detect count over TRACK_BASELINE_RELOAD_TIME will trace baseline */


#define TRACK_BASELINE_UP_BOUND     (20)         /* CCB will be limited above (FACTORY_CCB-TRACK_BASELINE_LOW_BOUND) */
#define TRACK_BASELINE_LOW_BOUND    (30)

#define TKLIB_MAJOR_VERSION         (0x01)
#define TKLIB_MINOR_VERSION         (0x10)       /* Add Wheel function */
//#define TOUCHKEY_VERSION          (0)          /* M4TK */
#define TOUCHKEY_VERSION            (1)          /* ML56 or later */


#define TK_KEY                      (0)
#define TK_SLIDER                   (1)
#define TK_WHEEL                    (2)
#define TK_SHIELDING                (3)
#define TK_REFERENCE                (4)

typedef struct tagTkInfo
{
    uint32_t u32EnChanMsk;             /* Channel Enable Bit Mask */

    uint8_t u8RefChan;                 /* Reference Channel no# */
    uint8_t u8ShieldChan;              /* Shield Channel no# */
    uint8_t u8SenPulse;                /* Sense Pulse Width 500ns or 1/2/4/8 us */
    uint8_t u8SenTimes;                /* Sense Times  16/32/64/128/255/511/1023 times */

    uint8_t u8SliderRes;               /* Specified the resolution of slider */
    uint8_t u8WheelRes;                /* Specified the resolution of wheel  */
    uint8_t u8PolarityCapacitorBank;   /* Specified the level for capacitor bank  */
    uint8_t u8AvcchLevel;              /* Specified the level for enabled channels on non-measured period */

    uint32_t u32EnSliderMsk;           /* Channel Enable Slider Bit Mask */
    uint32_t u32EnWheelMsk;            /* Channel Enable Wheel Bit Mask */
    uint32_t u32StoreAddr;             /* Parameters Store Addr */

    uint8_t u8NoiseImmunity;           /* Noise Immunity Factor: 1/3, 1/2, 2/3 */
    uint8_t u8Reserved;
    uint8_t u8RefCbAll;                /* u8RefCbAll  */
    uint8_t u8CcbAll;                  /* u8CcbAll    */
} S_TKINFO;

typedef struct
{
    uint8_t ccb;                       /* Range should be in 0 ~ 255 */       /* LSB */
    uint8_t refcb;                     /* Range should be in 0 ~ 255 */
    int8_t level;                      /* Range should be less than 128 */
    int8_t threshold;                  /* Range should be less than 128 */    /* MSB */
} S_KEYINFO;

typedef struct
{
    uint8_t u8EnIIR;
    uint8_t u8EnDebounce;
    uint8_t u8EnBaseLineTrace;
    uint8_t u8BaseLineRound;   //u8Reserved;
    uint16_t u16ResetTime;
    uint8_t u8IIROld;
    uint8_t u8IIRNew;
    uint8_t u8Entry;
    uint8_t u8Escape;
} S_TKFEAT;                        /* These features was assigned by  */

typedef struct
{
    uint8_t left;                  /* Left key */
    uint8_t right;                 /* Right Key */
} S_NEIGHBOR;                      /* All information is stored in flash. It is loaded after power on */

/* Application filed API */
int8_t TK_LoadPara(uint32_t* pu32ChanelMsk);                        /* Load TK Calibration Data                         */
void TK_Init(void);                                                 /* Touch Key Initialization                         */
int8_t TK_ScanKey(int8_t* pai8Buf);                                 /* Scan All Key Channel                             */
int8_t TK_GetChannelThreshold(uint8_t u8chan);                      /* Report the key's Threshold                       */
uint32_t TK_GetEnabledChannelMask(uint8_t u8TkType);                /* Get Enabled Channels Mask by Touch Key Type      */
uint8_t TK_CheckSliderPressed(void);                                /* Check Slider Channels pressed ?                  */
uint8_t TK_CheckSliderWheelPressed(uint8_t u8TkType);               /* Check Slider/Wheel Channels pressed ?            */
int8_t TK_SliderPercentage(int8_t *i8SignalBuf, uint8_t u8ChnNum);  /* Get the position percentage of slider            */
int8_t TK_WheelPercentage(int8_t *i8SignalBuf, uint8_t u8ChnNum);   /* Get the position percentage of wheel             */
void TK_ConfigPowerDown(uint8_t u8Sensitivity);                     /* Configuration TK for power down wake up setting  */
/* Small value is more sensitivity than big value   */
void TK_SetMaxSignal(int8_t i8ChansMaxSignal);                                          /* Specify the maxmiun signal from calibration done */
/* It was used to fine tune CCB and REFCB.          */
/* Fine tune's strategy dependsons on the max signal*/



/* Calibration Tool API */
int8_t TK_GetPacket(uint32_t* pu32ChanelMsk);                       /* Communication With PC Through UART               */
int8_t TK_SavePara(void);                                           /* Save TK Calibration Data                         */
S_TKFEAT* TK_GetFeaturePtr(void);                                   /* Get Touch-Key Feature Structure Pointer          */
S_KEYINFO* TK_GetKeyInfoPtr(void);                                  /* Get Touch-Key Keys Information Structure Pointer */
S_TKINFO* TK_GetTKInfoPtr(void);                                    /* Get Touch-Key IP Setting Structure Pointer       */
S_NEIGHBOR* TK_GetNeighborInfoPtr(void);                            /* Get Touch-Key neighboring keys Structure Pointer */
int TK_Calibration_Untouch(void);                                   /* Calibration Touch Key Without Figner Touching    */
int TK_Calibration_Touch(uint8_t u8chan, uint8_t u8n, uint8_t u8m); /* Calibration Touch Key With Figner Touching       */

void FMC_Open(void);                                                /* Open FMC driver to erase/write APROM area        */
signed char FMC_Erase(unsigned int u16Addr);                        /* Erase FMC APROM Page                             */
signed char FMC_Write(unsigned int u16Addr, unsigned long u32Data); /* Write FMC APROM Page                             */

#define E_RESET_BASELINE    (0)
#define E_TRACE_BASELINE    (1)

#endif /* __TKLIB_H__ */


