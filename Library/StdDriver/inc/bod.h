
#define   VBOD_1_8           0x70
#define   VBOD_2_0           0x50
#define   VBOD_2_4           0x40
#define   VBOD_2_7           0x30
#define   VBOD_3_0           0x20
#define   VBOD_3_7           0x10
#define   VBOD_4_4           0x00

#define   BOD_RESET   0x04
#define   BOD_NO_RESET  0

#define   LPBOD_MODE_NORMAL  0
#define   LPBOD_MODE_1       0x02
#define   LPBOD_MODE_2       0x04
#define   LPBOD_MODE_3       0x06


void BOD_Open(unsigned char u8bodstatus, unsigned char u8bodlevel, unsigned char u8bodresetstatus);
void BOD_LowPower(unsigned char u8LPBDD);
void BOD_Interrupt (unsigned char u8bodINTstatus);

