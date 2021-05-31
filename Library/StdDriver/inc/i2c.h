#define I2C0    0
#define I2C1    1

#define      I2C_R    1
#define      I2C_W    0

void I2C_Master_Open(unsigned char u8I2CSel, unsigned long u32SYSCLK, unsigned long u32I2CCLK);
void I2C_Slave_Open(unsigned char u8I2CSel, unsigned char u8SlaveAddress0, unsigned char u8SlaveAddress1, unsigned char u8SlaveAddress2, unsigned char u8SlaveAddress3);
void I2C_Close(unsigned char u8I2CSel);
void I2C_Interrupt(unsigned char u8I2CSel,unsigned char u8I2CStatus);
unsigned char I2C_GetStatus(unsigned char u8I2CSel);
void I2C_SetSlaveAddrMask(unsigned char u8I2CSel, unsigned char u8SlaveNo, unsigned char u8SlaveAddrMask);
void I2C_Timeout(unsigned char u8I2CSel, unsigned char u8I2CTRStatus );
void I2C_ClearTimeoutFlag(unsigned char u8I2CSel);
void I2C_Slave_Address_Mask(unsigned char u8I2CSel, unsigned char u8I2CAddMaskStatus, unsigned char u8I2CAddMaskBit);
void I2C0_SI_Check(void);