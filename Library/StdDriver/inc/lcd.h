#define  TYPE_A  0
#define  TYPE_B  1

#define  VLCD_PIN               0
#define  AVDD_PIN               1
#define  Internal_VCP           2
#define  LCD_VSource_Disable    3

#define  Resistor_Mode            0x80
#define  Buffer_Mode              0x40
#define  Resistor_PowerSave_Mode  0x81
#define  Buffer_PowerSave_Mode    0x41
#define  Resistor_Enhance_Mode    0x82

#define  BIAS_1_2     0x10
#define  BIAS_1_3     0x20
#define  BIAS_1_4     0x30

#define  LCD_4COM      0x00
#define  LCD_6COM      0x04
#define  LCD_8COM      0x08

#define  LCD_FREQ_DIV1    0
#define  LCD_FREQ_DIV2    1
#define  LCD_FREQ_DIV4    2
#define  LCD_FREQ_DIV8    3
#define  LCD_FREQ_DIV16   4
#define  LCD_FREQ_DIV32   5

#define   LCD_CPVOL_5_4V     0x00 
#define   LCD_CPVOL_5_2V     0x05
#define   LCD_CPVOL_5_0V     0x0A
#define   LCD_CPVOL_4_8V     0x0E 
#define   LCD_CPVOL_4_6V     0x13 
#define   LCD_CPVOL_4_4V     0x18 
#define   LCD_CPVOL_4_2V     0x1D 
#define   LCD_CPVOL_4_0V     0x22 
#define   LCD_CPVOL_3_8V     0x27 
#define   LCD_CPVOL_3_6V     0x2C 
#define   LCD_CPVOL_3_4V     0x30 
#define   LCD_CPVOL_3_2V     0x35
#define   LCD_CPVOL_3_0V     0x3A
#define   LCD_CPVOL_2_8V     0x3F

#define   TurnOn_All        0
#define   TurnOn_1_4        1
#define   TurnOn_2_4        2
#define   TurnOn_3_4        3

#define   LCD_CPALARM_INT   0
#define   LCD_CPRD_INT      0x08

#define   LCD_OFF           3
#define   LCD_ON            4

void LCD_Open(unsigned char u8LCDPowerType, unsigned char u8LCDVSource, unsigned char u8DrivingVol, unsigned char u8BiasLevel, unsigned char u8ComNum );
void LCD_Current_Mode(unsigned char u8LCDCurrentSel, unsigned char u8LCDPSSel);
void LCD_VSource_Control(unsigned char u8LCDVSource);
void LCD_Clock_Setting(unsigned char u8LCDCLKSource, unsigned char u8LCDCLKDiv);
void LCD_Blink(unsigned char u8LCDBKStatus, unsigned char u8LCDBKFEQ);
void LCD_PowerSaving(unsigned char u8LCDPowerStatus);
void LCD_Interrupt_Initial(unsigned char u8lcdIntStatus, unsigned char u8lcdIntSel, unsigned int u8lcdAlmValue);
void LCD_SetAllPixels(unsigned char u8OnOff);
void LCD_PowerDown_Display(unsigned char u8LCDDisplay);
void LCD_SetOnePixel(unsigned char u8LCDCOM, unsigned char u8LCDSEG, unsigned char u8OnOff);
void LCD_Enable(void);
void LCD_Disable(void);


