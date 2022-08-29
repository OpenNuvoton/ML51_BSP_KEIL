
#include "ML51.h"
#include "LCD_NK.h"


void main(void)
{

    /* Initial LCD Sub board */
    LCD_Init_Setting();
    
    /* Init TK Controller */  
    ENABLE_GLOBAL_INTERRUPT;

    LCD_frame2();

    while (1)
		{
			LCD_frame1();
			Timer0_Delay(24000000,800,1000);
			LCD_frame2();
			Timer0_Delay(24000000,800,1000);
		}
}

