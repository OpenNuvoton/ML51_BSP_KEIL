
#define     PAGE_SIZE               128

extern unsigned char xdata DIDBuffer[2];
extern unsigned char xdata PIDBuffer[2];
extern unsigned char xdata UIDBuffer[9];
extern unsigned char xdata UCIDBuffer[12];
extern unsigned char xdata IAPDataBuf[128];
extern unsigned char xdata IAPCFBuf[5];
extern unsigned char xdata CHECKSUMBuf[1];

void LDROM_Erase(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void LDROM_Blank_Check(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void LDROM_Program(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void LDROM_Read_Verify(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void APROM_Erase(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void APROM_Blank_Check(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void APROM_Program(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void APROM_Read_Verify(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void UID_Read(void);
void UCID_Read(void);
void DID_Read(void);
void PID_Read(void);
void APROM_Checksum_Run(unsigned int u16IAPStartAddress,unsigned char u8ChecksumSize);
unsigned char APROM_Checksum_Read(unsigned int u16IAPStartAddress);
void LDROM_Checksum_Run(unsigned int u16IAPStartAddress,unsigned char u8ChecksumSize);
unsigned char LDROM_Checksum_Read(unsigned int u16IAPStartAddress);
void SPROM_Checksum_Run(void);
unsigned char SPROM_Checksum_Read(void);
void CONFIG_Checksum_Run(void);
unsigned char CONFIG_Checksum_Read(void);