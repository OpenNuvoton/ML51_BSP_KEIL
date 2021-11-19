#define GPIO_MODE_QUASI      0
#define	GPIO_MODE_PUSHPULL   1
#define GPIO_MODE_INPUT      2
#define GPIO_MODE_OPENDRAIN  3

#define  PORT0     0
#define  PORT1     1
#define  PORT2     2
#define  PORT3     3
#define  PORT4     4
#define  PORT5     5
#define  PORT6     6

#define  Port0  0
#define  Port1  1
#define  Port2  2
#define  Port3  3
#define  Port4  4
#define  Port5  5
#define  Port6  6

#define  BIT0    0x01
#define  BIT1    0x02
#define  BIT2    0x04
#define  BIT3    0x08
#define  BIT4    0x10
#define  BIT5    0x20
#define  BIT6    0x40
#define  BIT7    0x80

#define  PULLUP     0
#define  PULLDOWN   1
#define  PullUp     0
#define  PullDown   1

#define  Port40     0
#define  Port30     1
#define  Port21     2
#define  Port20     3

void GPIO_SetMode(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8Mode);
void GPIO_Pull_Enable(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8PullMode);
void GPIO_Pull_Disable(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8PullMode);
void GPIO_SchmittTrigger(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8SStauts);
void GPIO_SlewRate(unsigned char u8Port, unsigned char u8PinMask, unsigned char u8SStauts);
void GPIO_AutoReturnHigh(unsigned char u8Port, unsigned char u8RTtime);