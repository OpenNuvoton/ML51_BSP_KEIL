/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/


//***********************************************************************************************************
//  File Function: ML51 UART0 ISP demo code
//***********************************************************************************************************
#include "ML51.h"
#include "isp_spi0.h"

//#define  isp_with_wdt
unsigned int xdata start_address,u16_addr;

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{

  set_CHPCON_IAPEN;  
  TA=0X55;TA=0XAA;WDCON=0x07;
//SPI0 initial for ISP programmer GUI
  SPI0_ini();
  TM0_ini();
  g_timer0Over=0;
  g_timer0Counter=Timer0Out_Counter;
  g_programflag=0;
  P32_QUASI_MODE;P32 = 0;
  P33_QUASI_MODE;P33 = 0;  
  bSPISendFlag = FALSE;
  bufhead = 0;

while(1)
{
        
        SPI0_Polling_Receive_Data();
        if(bSPIDataReady == TRUE)
        {
          EA=0; //DISABLE ALL INTERRUPT

          if(g_programflag==1)
          {
            while(1)
            {
APPRO:    //   _delay_();       
              SPI0_Polling_Receive_Data1();
              if(bSPIDataReady == TRUE)
              {
                 EA=0;
                 WordChangeByte14();
                  for(count=0;count<56;count++)
                  {

                    g_timer0Counter=Timer0Out_Counter;

                    IAPCN = BYTE_PROGRAM_AP;          //program byte
                    IAPAL = flash_address&0xff;
                    IAPAH = (flash_address>>8)&0xff;
                    IAPFD=rxcgbuf[count];

      #ifdef isp_with_wdt
                    set_IAPTRG_IAPGO_WDCLR;
      #else
                    set_IAPTRG_IAPGO;
      #endif
                
                    IAPCN = BYTE_READ_AP;              //program byte verify
                    if(IAPFD!=rxcgbuf[count])
                    while(1);               
                    if (CHPCON==0x43)              //if error flag set, program error stop ISP
                    while(1);
                    
                   // g_totalchecksum=g_totalchecksum+rxbuf[count];
                    flash_address++;
       
                    if(flash_address==AP_size)
                    {
                       g_programflag=0;
                       g_timer0Over =1;
                       goto END_2;
                    }
                  
                  } 
                
      END_2:        
                    Package_checksum2();
                    Send_64byte_To_SPI0();
                    bSPIDataReady = FALSE;
                    bufhead = 0;
//                    EA=1;    
              }
         }
        }
          switch(rxbuf[3])
          {                
            case CMD_CONNECT:
            case CMD_SYNC_PACKNO:
            {
              Package_checksum();
              Send_64byte_To_SPI0();    
              g_timer0Counter=0; //clear timer 0 for no reset
              g_timer0Over=0;
            break;
            }

            case CMD_GET_FWVER:
            {
              Package_checksum();
              txbuf[14]=FW_VERSION;  
              Send_64byte_To_SPI0();  
            break;
            }
            
            case CMD_RUN_APROM:
            {
              goto _APROM;
            break;
            }

            //please for ISP programmer GUI, ID always use following rule to transmit.
            case CMD_GET_DEVICEID:
            {
              READ_ID();
              Package_checksum();
              txbuf[14]=DID_lowB;  
              txbuf[13]=DID_highB;  
              txbuf[12]=PID_lowB;  
              txbuf[11]=PID_highB;  

              Send_64byte_To_SPI0();  
            break;
            }
            case CMD_ERASE_ALL:
            {
//              set_CHPCON_IAPEN;
              set_IAPUEN_APUEN;
              IAPFD = 0xFF;          //Erase must set IAPFD = 0xFF
              IAPCN = PAGE_ERASE_AP;
              for(flash_address=0x0000;flash_address<APROM_SIZE/PAGE_SIZE;flash_address++)
              {        
                IAPAL = LOBYTE(flash_address*PAGE_SIZE);
                IAPAH = HIBYTE(flash_address*PAGE_SIZE);
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              set_IAPTRG_IAPGO;
#endif
              }
              Package_checksum();
              Send_64byte_To_SPI0();  
              break;
            }
            case CMD_READ_CONFIG:
            {
              READ_CONFIG();
              Package_checksum();
              txbuf[14]=CONF0;
              txbuf[13]=CONF1;
              txbuf[12]=CONF2;
              txbuf[11]=0xff;
              txbuf[18]=CONF4;
              txbuf[17]=0xff;
              txbuf[16]=0xff;
              txbuf[15]=0xff;
              
            
              Send_64byte_To_SPI0();
            break;
            }
            
            case CMD_UPDATE_CONFIG:
            {
              recv_CONF0 = rxbuf[14];
              recv_CONF1 = rxbuf[13];
              recv_CONF2 = rxbuf[12];
              recv_CONF4 = rxbuf[11];
/*Erase CONFIG */              
//              set_CHPCON_IAPEN;
              set_IAPUEN_CFUEN;
              IAPCN = PAGE_ERASE_CONFIG;
              IAPAL = 0x00;
              IAPAH = 0x00;
              IAPFD = 0xFF;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              set_IAPTRG_IAPGO;
#endif
/*Program CONFIG*/  
              IAPCN = BYTE_PROGRAM_CONFIG;
              IAPAL = 0x00;
              IAPAH = 0x00;
              IAPFD = recv_CONF0;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              set_IAPTRG_IAPGO;
#endif
              IAPFD = recv_CONF1;
              IAPAL = 0x01;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              set_IAPTRG_IAPGO;
#endif
              IAPAL = 0x02;
              IAPFD = recv_CONF2;
  #ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              set_IAPTRG_IAPGO;
#endif
              IAPAL = 0x04;
              IAPFD = recv_CONF4;
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              set_IAPTRG_IAPGO;
#endif
              clr_IAPUEN_CFUEN;
/*Read new CONFIG*/  
              READ_CONFIG();
              Package_checksum();
              txbuf[14]=CONF0;
              txbuf[13]=CONF1;
              txbuf[12]=CONF2;
              txbuf[11]=0xff;
              txbuf[18]=CONF4;
              txbuf[17]=0xff;
              txbuf[16]=0xff;
              txbuf[15]=0xff;
              Send_64byte_To_SPI0();
              break;
            }
            
            case CMD_UPDATE_APROM:
            {

              g_timer0Counter=Timer0Out_Counter;
              set_IAPUEN_APUEN;
              IAPFD = 0xFF;          //Erase must set IAPFD = 0xFF
              IAPCN = PAGE_ERASE_AP;
              
              start_address = 0;
              
              AP_size = 0;
              AP_size = rxbuf[15];
              AP_size |= ((rxbuf[14]<<8)&0xFF00);

              u16_addr = start_address + AP_size;
              flash_address = (start_address&0xFF00);

              while(flash_address< u16_addr)
              {
                IAPAL = LOBYTE(flash_address);
                IAPAH = HIBYTE(flash_address);
#ifdef isp_with_wdt
                set_IAPTRG_IAPGO_WDCLR;
#else
                set_IAPTRG_IAPGO;
#endif
                flash_address += PAGE_SIZE;
              }
              
              g_totalchecksum = 0;
              flash_address = 0;//start_address;
              g_programflag = 1;
              WordChangeByte12();
              for(count=0;count<48;count++)
              {
                IAPCN = BYTE_PROGRAM_AP;
                IAPAL = flash_address&0xff;
                IAPAH = (flash_address>>8)&0xff;
                IAPFD = rxcgbuf[count];
#ifdef isp_with_wdt
              set_IAPTRG_IAPGO_WDCLR;
#else
              set_IAPTRG_IAPGO;
#endif
                IAPCN = BYTE_READ_AP;                //program byte verify
                set_IAPTRG_IAPGO;

                if(IAPFD!=rxcgbuf[count])
                while(1);  

                if (CHPCON==0x43)                //if error flag set, program error stop ISP
                while(1);
    
               // g_totalchecksum=g_totalchecksum+rxbuf[count];
                flash_address++;

                if(flash_address==AP_size)
                {
                    g_programflag=0;
                   goto END_1;
                }
              }
END_1:             
              Package_checksum2();
              Send_64byte_To_SPI0();
              bSPIDataReady = FALSE;
              bufhead = 0;
//          EA=1;                
              goto APPRO;
              break;
            }
          }  
          bSPIDataReady = FALSE;
          bufhead = 0;
     //     EA=1;      
      }
      /*For connect timer out     */
      if(g_timer0Over==1)
      {
       goto _APROM;
      }
}   

_APROM:
    clr_CHPCON_IAPEN;
    TA = 0xAA;
    TA = 0x55;
    CHPCON &= 0xFD;                  //set boot from AP
    TA = 0xAA;
    TA = 0x55;
    CHPCON |= 0x80;                   //software reset enable

    /* Trap the CPU */
    while(1);  
}


