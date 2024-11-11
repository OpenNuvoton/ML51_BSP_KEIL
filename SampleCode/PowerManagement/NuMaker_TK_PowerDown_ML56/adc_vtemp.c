/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* SPDX-License-Identifier: Apache-2.0                                                                     */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "ml51.h"

/* When Temperatue 25C, temperature voltage = 675mV, 1.83mV /per C */
/* TemperatureVoltage = ADC_result*VREF / 4096                     */
/* Temperature = 25 + ((673 - TemperatureVoltage)/1.83)            */
/* so Temperture = 25 + (TTMPCAL - ADC_result*VREF)/VTEMPCOMDIV    */

unsigned long  internal_Temperature()
{
    /* GPIO initial setting
      * include gpio.c in Library for GPIO mode setting
    */
    double   RealTemperature;

     return (RealTemperature);

    while (1);
}


