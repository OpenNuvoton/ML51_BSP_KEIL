#ifndef __TK_DEMO_H__
#define __TK_DEMO_H__

#define OPT_SLIDER
#define OPT_WHEEL
//#define UART1_DBG                                     /* Trace code with UART1 message */
#define DBG_PRINTF          //printf

//#define Enable_TK0_CKO_SHIELDING                    /* Enable it if using CKO as shielding */

#define FIRMWARE_MAJOR_VERSION      (0x01)
#define FIRMWARE_MINOR_VERSION      (0x10)            /* Add Wheel example code and CKO shielding */

#define USER_ID                     (('N'<<24) | ('U'<<16) | ('V'<<8) | 'O')

//TK_Param.c
int8_t TK_LoadPara(uint32_t* pu32ChanelMsk);
int8_t TK_SavePara(void);

//TK_Led.c
void InitLEDIO(void);
void TK_lightLED(uint8_t onOff, int chanN);

//TK_MultPinFunctions.c
void SetTkMultiFun(uint32_t u32TkMsk);

void FMC_Open(void);
signed char FMC_Erase(unsigned int u16Addr);
signed char FMC_Write(unsigned int u32Addr, unsigned long u32Data);

void UART0_Init(void);
void UART1_Init(void);

void Init_SysTick(void);
char TickSetTickEvent(unsigned long uTimeTick, void* pvFun);
void TickClearTickEvent(uint8_t u8TimeEventID);

/* TK_UartCmd.c */
void UART_SetCalibrationDone(void);

#endif /* __TK_DEMO_H__ */


