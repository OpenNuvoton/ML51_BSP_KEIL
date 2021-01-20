/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2018 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  File Function: ML51 UART0 ISP subroutine
//***********************************************************************************************************
#include "ML51.H"
#include "ISP_I2C.h"
bit BIT_TMP;

  xdata volatile uint8_t rx_buf[64]; 
  xdata volatile uint8_t tx_buf[64];
  data volatile uint16_t flash_address; 
  data volatile uint16_t AP_size;
  data volatile uint8_t g_timer1Counter;
  data volatile uint8_t count; 
  data volatile uint16_t g_timer0Counter;
  data volatile uint32_t g_checksum;
  data volatile uint32_t g_totalchecksum;
  bit volatile bI2CDataReady;
  bit volatile bISPDataReady;//for ack
  volatile uint8_t g_u8SlvDataLen;
  bit volatile g_timer0Over;
  bit volatile g_timer1Over;
  bit volatile g_progarmflag;

unsigned char PID_highB,PID_lowB,DID_highB,DID_lowB,CONF0,CONF1,CONF2,CONF4;
unsigned char recv_CONF0,recv_CONF1,recv_CONF2,recv_CONF4;
#define ADDR_SLA              0x60<<1


void READ_ID(void)
{
//    set_CHPCON_IAPEN;
    IAPCN = READ_DID;
    IAPAH = 0x00;
    IAPAL = 0x00;
    set_IAPTRG_IAPGO;
    DID_lowB = IAPFD;
    IAPAL = 0x01;
    set_IAPTRG_IAPGO;
    DID_highB = IAPFD;
    IAPAL = 0x02;
    set_IAPTRG_IAPGO;
    PID_lowB = IAPFD;
    IAPAL = 0x03;
    set_IAPTRG_IAPGO;
    PID_highB = IAPFD;
}
void READ_CONFIG(void)
{
    IAPCN = BYTE_READ_CONFIG;
    IAPAL = 0x00;
    IAPAH = 0x00;
    set_IAPTRG_IAPGO;
    CONF0 = IAPFD;
    IAPAL = 0x01;
    set_IAPTRG_IAPGO;
    CONF1 = IAPFD;
    IAPAL = 0x02;
    set_IAPTRG_IAPGO;
    CONF2 = IAPFD;
    IAPAL = 0x04;
    set_IAPTRG_IAPGO;
    CONF4 = IAPFD;
//    clr_CHPCON_IAPEN;
}

void TM0_ini(void)
{    
  TH0=TL0=0;    //interrupt timer 140us
  set_TCON_TR0;      //Start timer0
  set_IPH_PSH;       // Serial port 0 interrupt level2
  set_IE_ET0;
}


void Package_checksum(void)
{
  g_checksum=0;
   for(count=0;count<64;count++)
  {
    g_checksum =g_checksum+ rx_buf[count];    
  }
  tx_buf[0]=g_checksum&0xff;
  tx_buf[1]=(g_checksum>>8)&0xff;
  tx_buf[4]=rx_buf[4]+1;
  tx_buf[5]=rx_buf[5];
  if(tx_buf[4]==0x00)
  tx_buf[5]++;
  
}


void Timer0_ISR (void) interrupt 1
{
if(g_timer0Counter)
  {
  g_timer0Counter--;
    if(!g_timer0Counter)
    {
    g_timer0Over=1;
    }
  }
  
  if(g_timer1Counter)
  {
  g_timer1Counter--;
    if(!g_timer1Counter)
    {
    g_timer1Over=1;
    }
  }
}

void Init_I2C(void)
{
    MFP_P25_I2C0_SCL;
    MFP_P24_I2C0_SDA;
    P25_OPENDRAIN_MODE;                         //set SCL (P13) is Quasi mode
    P24_OPENDRAIN_MODE;                         //set SDA (P24) is Quasi mode
    
    SDA = 1;                                    //set SDA and SCL pins high
    SCL = 1;
    set_EIE0_EI2C0;                               //enable I2C interrupt by setting EIE bit 0
    set_I2C0CON_I2CEN;                            //enable I2C circuit 
    I2C0ADDR0 = ADDR_SLA;                          //define own slave address    
    clr_I2C0CON_SI;
    set_I2C0CON_AA;
    set_IE_EA;
}

void I2C_ISR(void) interrupt 6
{
    static uint8_t _bISPDataReady;
    uint8_t u8data;

    if (I2C0STAT == 0x60) {                    /* Own SLA+W has been receive; ACK has been return */
        bI2CDataReady = 0;
        bISPDataReady = 0;
        g_u8SlvDataLen = 0;
        //I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
        set_I2C0CON_AA;;
    } else if (I2C0STAT == 0x80)                 /* Previously address with own SLA address
                                                   Data has been received; ACK has been returned*/
    {
        rx_buf[g_u8SlvDataLen] = I2C0DAT;
        g_u8SlvDataLen++;
        g_u8SlvDataLen &= 0x3F;
        bI2CDataReady = (g_u8SlvDataLen == 0);

        if (g_u8SlvDataLen == 0x3F) {
            //I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI);
        } else {
            //I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
          set_I2C0CON_AA;
        }
    } else if (I2C0STAT == 0xA8) {             /* Own SLA+R has been receive; ACK has been return */
        g_u8SlvDataLen = 0;
        _bISPDataReady = bISPDataReady;

        if (_bISPDataReady == 0) {
            u8data = 0xCC;
        } else {
            u8data = tx_buf[g_u8SlvDataLen];
        }

        
        I2C0DAT=u8data;
        g_u8SlvDataLen++;
       // I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
        set_I2C0CON_AA;
    } else if (I2C0STAT == 0xB8) {
        if (_bISPDataReady == 0) {
            u8data = 0xDD;
        } else {
            u8data = tx_buf[g_u8SlvDataLen];
        }

        
        I2C0DAT=u8data;
        g_u8SlvDataLen++;
        g_u8SlvDataLen &= 0x3F;

        if (g_u8SlvDataLen == 0x00) {
           // I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI);
        } else {
          //  I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
          set_I2C0CON_AA;
        }
    } else if (I2C0STAT == 0xC8) {
       // I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
      set_I2C0CON_AA;
    } else if (I2C0STAT == 0xC0)                 /* Data byte or last data in I2CDAT has been transmitted
                                                   Not ACK has been received */
    {
       // I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
      set_I2C0CON_AA;
    } else if (I2C0STAT == 0x88)                 /* Previously addressed with own SLA address; NOT ACK has
                                                   been returned */
    {
        rx_buf[g_u8SlvDataLen] = I2C0DAT;
        g_u8SlvDataLen++;
        bI2CDataReady = (g_u8SlvDataLen == 64);
        g_u8SlvDataLen = 0;
      //  I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
      set_I2C0CON_AA;
    } else if (I2C0STAT == 0xA0)                 /* A STOP or repeated START has been received while still
                                                   addressed as Slave/Receiver*/
    {
        g_u8SlvDataLen = 0;
        //I2C_SET_CONTROL_REG(i2c, I2C_CTL_SI_AA);
      set_I2C0CON_AA;
    } else {
        /* TO DO */
        // printf("Status 0x%x is NOT processed\n", u32Status);
    }
    clr_I2C0CON_SI;

}
