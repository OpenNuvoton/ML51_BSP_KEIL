#define RTC_INIT_KEY         0x57           /*!< RTC Access Key     */
#define RTC_WRITE_KEY        0xA965         /*!< RTC Access Key  */

#define RTC_WAIT_COUNT       0xFFFFFFFF     /*!< Initial Time Out Value  */

#define RTC_YEAR2000         2000            /*!< RTC Reference */

#define RTC_CLOCK_12         0                /*!< RTC 12 Hour */
#define RTC_CLOCK_24         1                /*!< RTC 24 Hour */

#define RTC_AM               1                /*!< RTC AM */
#define RTC_PM               2                /*!< RTC PM */

#define RTC_TIME_TICK        0
#define RTC_ALARM            1

#define RTC_TICK_1_SEC       (0x00)   /*!< Time tick is 1 second */
#define RTC_TICK_1_2_SEC     (0x01)   /*!< Time tick is 1/2 second */
#define RTC_TICK_1_4_SEC     (0x02)   /*!< Time tick is 1/4 second */
#define RTC_TICK_1_8_SEC     (0x03)   /*!< Time tick is 1/8 second */
#define RTC_TICK_1_16_SEC    (0x04)   /*!< Time tick is 1/16 second */
#define RTC_TICK_1_32_SEC    (0x05)   /*!< Time tick is 1/32 second */
#define RTC_TICK_1_64_SEC    (0x06)   /*!< Time tick is 1/64 second */
#define RTC_TICK_1_128_SEC   (0x07)   /*!< Time tick is 1/128 second */

#define RTC_SUNDAY       (0x00)   /*!< Day of week is sunday */
#define RTC_MONDAY       (0x01)   /*!< Day of week is monday */
#define RTC_TUESDAY      (0x02)   /*!< Day of week is tuesday */
#define RTC_WEDNESDAY    (0x03)   /*!< Day of week is wednesday */
#define RTC_THURSDAY     (0x04)   /*!< Day of week is thursday */
#define RTC_FRIDAY       (0x05)   /*!< Day of week is friday */
#define RTC_SATURDAY     (0x06)   /*!< Day of week is saturday */

#define RTC_SNOOPER_RISING   0      /*!< Snooper Active Rising Edge */
#define RTC_SNOOPER_FALLING  1      /*!< Snooper Active Falling Edge */


typedef struct {
    unsigned int  u16Year;          /*!<  Year value */
    unsigned char u8Month;         /*!<  Month value */
    unsigned char u8Day;           /*!<  Day value */
    unsigned char u8DayOfWeek;     /*!<  Day of week value */
    unsigned char u8Hour;          /*!<  Hour value */
    unsigned char u8Minute;        /*!<  Minute value */
    unsigned char u8Second;        /*!<  Second value */
    unsigned char u8TimeScale;     /*!<  12-Hour, 24-Hour */
    unsigned char u8AmPm;          /*!<  Only Time Scale select 12-hr used */
} S_RTC_TIME_DATA_T;


void _RTC_RWEN_(void);
void RTC_Initial_Run(void);
void RTC_Initial_Pause(void);
void RTC_SetDate(unsigned int u16Year, unsigned int u8Month, unsigned int u8Day, unsigned char u8DayOfWeek);
void RTC_SetTime(unsigned int u8Hour, unsigned int u8Minute, unsigned char u8Second, unsigned char u8TimeMode, unsigned char u8AmPm);
void RTC_SetAlarmDate(unsigned int u16Year, unsigned char u8month, unsigned char u8Day);
void RTC_SetAlarmTime(unsigned char u8Hour, unsigned char u8Minute, unsigned char u8Second, unsigned char u8TimeMode, unsigned char u8AmPm);
void RTC_GetDateAndTime(S_RTC_TIME_DATA_T *sPt);
void RTC_GetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt);
void RTC_Interrupt_Enable(unsigned char u8RTCIntType);
void RTC_Interrupt_Disable(unsigned char u8RTCIntType);
void RTC_Clock_Select(unsigned char u8RTCClockSource);
void RTC_Tick_Select(unsigned char u8RTCTickSel);

#define RTC_RWEN  _RTC_RWEN_();
