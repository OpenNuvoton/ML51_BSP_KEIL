#define TRUE       1
#define FALSE     0

#define SCL   P25
#define SDA   P24

#define CMD_CONNECT          0xAE
#define CMD_SYNC_PACKNO      0xA4
#define CMD_GET_FWVER        0xA6
#define FW_VERSION           0x28
#define CMD_RUN_APROM        0xAB
#define CMD_GET_DEVICEID     0xB1
#define CMD_ERASE_ALL        0xA3
#define CMD_READ_CONFIG      0xA2
#define CMD_UPDATE_CONFIG    0xA1
#define CMD_UPDATE_APROM     0xA0
#define PAGE_ERASE_AP        0x22
#define BYTE_READ_AP         0x00
#define BYTE_PROGRAM_AP      0x21
#define BYTE_READ_ID         0x0C
#define PAGE_ERASE_CONFIG    0xE2
#define BYTE_READ_CONFIG     0xC0
#define BYTE_PROGRAM_CONFIG  0xE1
#define READ_UID             0x04
#define PAGE_SIZE            128
///#define APROM_SIZE           61440   /* 60K bytes AP size , 4K LD size*/
#define APROM_SIZE           62464   /* 61K bytes AP size, 3K LD size */
//#define APROM_SIZE           63488   /* 62K bytes PA size, 2K LD size */
#define trig_iap             TA=0xAA;TA=0x55;IAPTRG|=0x01
 
extern  xdata volatile uint8_t rx_buf[64]; 
extern  xdata volatile uint8_t tx_buf[64];
extern  data volatile uint8_t bufhead;
extern  data volatile uint16_t flash_address; 
extern  data volatile uint16_t AP_size;
extern  data volatile uint8_t g_timer1Counter;
extern  data volatile uint16_t count; 
extern  data volatile uint16_t g_timer0Counter;
extern  data volatile uint32_t g_checksum;
extern  data volatile uint32_t g_totalchecksum;
extern  bit volatile bI2CDataReady;
extern  bit volatile bISPDataReady;
extern  bit volatile g_timer0Over;
extern  bit volatile g_timer1Over;
extern  bit volatile g_progarmflag;

extern unsigned char PID_highB,PID_lowB,DID_highB,DID_lowB,CONF0,CONF1,CONF2,CONF4;
extern unsigned char recv_CONF0,recv_CONF1,recv_CONF2,recv_CONF4;
void Init_I2C1(void);
void TM0_ini(void);
void Package_checksum(void);
void READ_ID(void);
void READ_CONFIG(void);
void Timer1_Delay10ms(UINT32 u32CNT);
