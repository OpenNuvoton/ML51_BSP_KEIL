#define LIRC   1
#define LXT    2

void WKT_Open(unsigned char  u8WKTCLKSouce, unsigned int u16WKTDIV, unsigned int u8WKTRLData);
void WKT_Interrupt(unsigned char u8WKTINT);
void WKT_Close();
unsigned char WKT_Current_Value();
void WKT_AutoReload_Interrupt_Initial_MS(unsigned char u8WKTCLKSouce, unsigned int u8WKTRLData);
void WKT_AutoReload_Interrupt_Initial_S(unsigned char u8WKTCLKSouce, unsigned int u8WKTRLData);


