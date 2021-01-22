/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2018 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

#include "ML51.h"

/* When Temperatue 25C, temperature voltage = 675mV, 1.83mV /per C */
/* TemperatureVoltage = ADC_result*VREF / 4096                     */
/* Temperature = 25 + ((673 - TemperatureVoltage)/1.83)            */
/* so Temperture = 25 + (TTMPCAL - ADC_result*VREF)/VTEMPCOMDIV    */

#define   TMPCAL        0x2A3000       /*    675*4096     */
#define   VTEMPCOMDIV   7694           /*    4096*1.83    */


unsigned long internal_Temperature () 
{
/* GPIO initial setting 
  * include gpio.c in Library for GPIO mode setting 
*/
    unsigned int  u16bgvalue,ADC_BG_Result;
    double  VREF_Voltage,RealTemperature; 


    
/* ADC initial setting 
  * include adc.c in Library for ADC setting.
*/
/* Base on internal VREF 2560mV */  
    VREF_Open(LEVEL3);
    ADC_Open(ADC_SINGLE,VBG);  
/* For the best result wait 10us delay for each sampling, ADCDIV=3, ADCAQT=7 is better */
    ADC_SamplingTime(7,7);
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;
    while(!(ADCCON0&SET_BIT7));
    ADC_BG_Result = (ADCRH<<4) + ADCRL;
 
/***************************************************************************************/
/*                  VDD  Now                         READ_BANDGAP() VALUE
/*    ------------------------------------- = ----------------------------------
/*    3072mV(Storage value test condition)      NOW ADC Bandgap convert reuslt
/***************************************************************************************/
    VREF_Voltage = ((float)READ_BANDGAP()/(float)ADC_BG_Result)*3072;
//    VREF_Voltage = 2048;
/* ADC temperature calculate */
    ADC_SamplingTime(3,7);
    ADC_Open(ADC_SINGLE,VTEMP);

    clr_ADCCON0_ADCF;                              /*Clear ADC flag before ADC start */
    set_ADCCON0_ADCS;                              /* Each time ADC start trig signal*/
    
    while(!(ADCCON0&SET_BIT7));                    /* wait ADCF = 1 */
    u16bgvalue = (ADCRH<<4)+ADCRL;

    RealTemperature = 25 + ((TMPCAL - (u16bgvalue * VREF_Voltage))/VTEMPCOMDIV);
    RealTemperature = abs(RealTemperature);

    return (RealTemperature);
    while(1);
}


