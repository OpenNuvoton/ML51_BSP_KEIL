/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

#include "ML51.h"

/**
 *  @brief LCD Initialization routine.
 *  @param[in]  u8LCDPowerType  LCD Power type: \ref TYPE_A (Standard) / \ref TYPE_B (LowPower)
 *  @param[in]  u8LCDVSource    LCD VLCD source: \ref AVDD_PIN / \ref VLCD_PIN / \ref Internal_VCP  \ref LCD_VSource_Disable
 *  @param[in]  u8DrivingVol    LCD driving voltage: \ref LCD_CPVOL_5_4V / \ref LCD_CPVOL_5_2V / \ref LCD_CPVOL_5_0V / 
 *                                                   \ref LCD_CPVOL_4_8V / \ref LCD_CPVOL_4_6V / \ref LCD_CPVOL_4_4V / 
 *                                                   \ref LCD_CPVOL_4_2V / \ref LCD_CPVOL_4_0V / \ref LCD_CPVOL_3_8V /
 *                                                   \ref LCD_CPVOL_3_6V / \ref LCD_CPVOL_3_4V / \ref LCD_CPVOL_3_2V /
 *                                                   \ref LCD_CPVOL_3_0V / \ref LCD_CPVOL_2_8V
 *  @param[in]  u8BiasLevel     LCD bias level: \ref BIAS_1_2 (1/2 bias) / \ref BIAS_1_3 (1/3 bias) / \ref BIAS_1_4 (1/4 bias)
 *  @param[in]  u8ComNum        LCD Com number: \ref LCD_4COM (1/4 Duty)/ \ref LCD_6COM (1/6 Duty)/ \ref LCD_8COM ((1/8 Duty)
 *  @return None.
 *  @example LCD_Open(TYPE_A, Internal_VCP, LCD_CPVOL_3_6V, BIAS_1_4, LCD_8COM );
 */
void LCD_Open(unsigned char u8LCDPowerType, unsigned char u8LCDVSource, unsigned char u8DrivingVol, unsigned char u8BiasLevel, unsigned char u8ComNum)
{
    LCD_Disable();
    /* Turn all segments off */
    LCD_SetAllPixels(Disable);

    switch(u8LCDPowerType)
    {
      case TYPE_A: clr_LCDCON0_TYPE; break;
      case TYPE_B: set_LCDCON0_TYPE; break;
    }

      LCDCON0&=0xC0; LCDCON0|=u8BiasLevel;    //Setting bias 
      LCDCON0&=0xF3; LCDCON0|=u8ComNum;       //Setting com
      LCDCPUMP = u8DrivingVol;                //Setting charge pump voltage
      LCDMODE = u8LCDVSource;                 // VLCD source select

}


/**
 *  @brief LCD Current Mode Select.
 *  @param[in]  u8LCDCurrentSel   LCD Current type: \ref Resistor_Enhance_Mode/
 *                                                  \ref Resistor_PowerSave_Mode /
 *                                                  \ref Buffer_PowerSave_Mode /
 *                                                  \ref Resistor_Mode /
 *                                                  \ref Buffer_Mode /
 *  @param[in]  u8LCDPSSel        LCD Power Saving Select\: \ref TurnOn_All / \ref TurnOn_1_4 / \ref TurnOn_2_4 / \ref TurnOn_3_4 /
 *  @Note    (Resistor_Enhance_Mode + TurnOn_All), (Buffer_Mode + TurnOn_All), (PowerSave_Mode + TurnOn_x_4)
 *  @example LCD_Current_Mode(Buffer_Mode, TurnOn_All);
 */
void LCD_Current_Mode(unsigned char u8LCDCurrentSel, unsigned char u8LCDPSSel)
{
    SFRS=3;
    LCDMODE |= (u8LCDCurrentSel&0xc0);               // lcd Driving type
    switch (u8LCDCurrentSel)
    {
      case Buffer_PowerSave_Mode: 
      case Resistor_PowerSave_Mode: 
        LCDPWR = u8LCDPSSel; break;
      case Resistor_Enhance_Mode:
        LCDMODE|=Resistor_Mode;
        set_LCDCON1_RE_MODE;
      case Buffer_Mode: 
      case Resistor_Mode: 
        LCDPWR=0; break;
    }
}

/**
 *  @brief VLCD source control subrution for Power Down power consumption contorl 
 *  @param[in]  u8LCDVSource    LCD VLCD source: \ref AVDD_PIN / \ref VLCD_PIN / \ref Internal_VCP  \ref LCD_VSource_Disable
 *  @return None.
 *  @return LCD_VSource_Control(LCD_VSource_Disable);
 */
void LCD_VSource_Control(unsigned char u8LCDVSource)
{       
    SFRS = 3;    //switch sfrs to page3
    LCDMODE &= 0xFC;
    LCDMODE |= u8LCDVSource;                 // VLCD source select
}

/**
 *  @brief LCD clock Setting.
 *  @param[in]  u8LCDCLKSource  LCD Clock source select: \ref LIRC (lirc/16) / \ref LXT (lxt/16) 
 *  @param[in]  u8LCDCLKDiv     LCD clock divider value: \ref LCD_FREQ_DIV1 / \ref LCD_FREQ_DIV2 / \ref LCD_FREQ_DIV4 / \ref LCD_FREQ_DIV8 /
 *                                                       \ref LCD_FREQ_DIV16 / \ref LCD_FREQ_DIV32
 *  @return LCD frame rate.
 *  @example LCD_Clock_Setting(LIRC, LCD_FREQ_DIV2);
 */
void LCD_Clock_Setting(unsigned char u8LCDCLKSource, unsigned char u8LCDCLKDiv)
{
    SFRS=3;
    switch (u8LCDCLKSource)
    {
      case LIRC: clr_LCDCLK_LCDCKS;  break;
      case LXT: set_LCDCLK_LCDCKS;   break;
    }
    LCDCLK&=0xF8; LCDCLK|=u8LCDCLKDiv;
}

/**
 *  @brief LCD blink frequrency seetting.
 *  @param[in]  u8LCDBKStatus  LCD blink enalbe: \ref Enable or 1 / \ref Disable or 0 
 *  @param[in]  u8LCDBKFEQ     LCD blink frequency set: \ref 0~7 / LCD Clock source /2 * (11 + u8LCDBKFEQ )^
 *                                                      \ref LCD clock = LIRC , LCD blink frequency =  16/8/4/2/1/0.5/0.25/0.125
 *                                                      \ref                    LCD blink timing = 62.5ms/125.0ms/250ms/500ms/1s/2s/4s/8s
 *                                                      \ref LCD clock = LXT , LCD blink frequency = 18.750/9.375/4.688/2.344/1.172/0.586/0.293/0.146
 *                                                      \ref                   LCD blink timing = 53ms/107ms/213ms/427ms/853ms/1.707s/3.413s/6.827s
 *  @return None.
 *  @return LCD_Blink(Enable,7);
 */
void LCD_Blink(unsigned char u8LCDBKStatus, unsigned char u8LCDBKFEQ)
{
    SFRS=3;
    LCDBL |= u8LCDBKFEQ;
    LCDBL=(u8LCDBKStatus<<3)|LCDBL;
}

/**
 *  @brief LCD interrupt initial.
 *  @param[in]  u8lcdIntStatus     LCD interrupt : \ref Enable / \ref Disable/
 *  @param[in]  u8lcdIntSel        LCD interrupt select: \ref LCD_CPRD_INT / \ref LCD_CPALARM_INT/
 *  @param[in]  u8lcdAlmValue      LCD charge pump alarm value
 *  @return None
 */
void LCD_Interrupt_Initial(unsigned char u8lcdIntStatus, unsigned char u8lcdIntSel, unsigned int u8lcdAlmValue)
{
  unsigned char datatemp;
    SFRS=3;
    datatemp|= ((u8lcdIntStatus<<2)|u8lcdIntSel);
    TA=0xAA; TA=0x55; LCDCON1 = datatemp;
    datatemp = LOBYTE(u8lcdAlmValue);
    TA=0xAA; TA=0x55; LCDCPALCT0 = datatemp;
    datatemp = HIBYTE(u8lcdAlmValue);
    TA=0xAA; TA=0x55; LCDCPALCT1 = datatemp;
    LCDCON0 |= SET_BIT0;
}

/**
 *  @brief LCD Enable/Disable all segments
 *  @param[in] u8OnOff  Disable or 0: Disable all segments
 *                      Enable or 1: Enable all segments
 *  @return None
 */
void LCD_SetAllPixels(unsigned char u8OnOff)
{
    unsigned char u8SetValue, i;
  
    if(u8OnOff)
        u8SetValue = 0xFF;
    else
        u8SetValue = 0x00;

    SFRS = 3;
    for(i = 0;i<32;i++)
    {
      LCDPTR = i;                  /* all SEG  */
      LCDDAT = u8SetValue;         /* all COM  */
    }
}

/**
 *  @brief LCD Display mode when MCU in power down mode
 *  @param[in] u8LCDDisplay  Disable or 0: Disable display in power down mode
 *                           Enable or 1: Enable display in power down mode
 *  @return None
 */
void LCD_PowerDown_Display(unsigned char u8LCDDisplay)
{
    switch(u8LCDDisplay)
    {
      case Enable:
      case LCD_ON: set_LCDCLK_DISP; break;
      case Disable:
      case LCD_OFF: clr_LCDCLK_DISP; break;
    }
}

/**
 *  @brief LCD on dot disaplay setting 
 *  @param[in]  u8LCDCOM  LCD COM select: \ref 0~7 / LCD COM number
 *  @param[in]  u8LCDSEG  LCD SEG select: \ref 0~31 / LCD segment value
 *  @param[in]  u8OnOff   LCD display status: \ref Enable / 1
 *                                            \ref Disable / 0
 *  @return None.
 *  @return LCD_SetPixel(0,0,Enable);
 */
void LCD_SetOnePixel(unsigned char u8LCDCOM, unsigned char u8LCDSEG, unsigned char u8OnOff)
{       
    SFRS = 3;    //switch sfrs to page3
    LCDPTR = u8LCDSEG;
    if(u8OnOff)
       LCDDAT |= (1 << u8LCDCOM);
    else
       LCDDAT &= ~(1 << u8LCDCOM); 
}




void LCD_Enable(void)
{
    set_LCDCON0_LCDEN;
}

void LCD_Disable(void)
{
    clr_LCDCON0_LCDEN;
}


