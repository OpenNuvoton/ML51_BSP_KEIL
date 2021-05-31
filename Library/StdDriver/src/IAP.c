/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/************************************************************************************************************
  Website: http://www.nuvoton.com
  E-Mail : MicroC-8bit@nuvoton.com
************************************************************************************************************/

#include "ML51.h"
unsigned char xdata DIDBuffer[2];
unsigned char xdata PIDBuffer[2];
unsigned char xdata UIDBuffer[9];
unsigned char xdata UCIDBuffer[12];
unsigned char xdata IAPDataBuf[128];
unsigned char xdata IAPCFBuf[5];


/**
 * @brief       Erase LDROM  
 * @param       u16IAPStartAddress define LDROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Page erase LDROM area base on data start address 
 * @example      Erase_LDROM(0x0000,2048);
 */
void LDROM_Erase(unsigned int u16IAPStartAddress,unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;                    // Enable IAP function
    set_IAPUEN_LDUEN;                    //  LDROM modify Enable
    IAPFD = 0xFF;                        // IMPORTANT !! To erase function must setting IAPFD = 0xFF 
    IAPCN = PAGE_ERASE_LDROM;
    for(u16Count=0x0000;u16Count<(u16IAPDataSize/PAGE_SIZE);u16Count++)            // Loop page erase LDROM special define address area.
    {        
        IAPAL = LOBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        IAPAH = HIBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        set_IAPTRG_IAPGO_WDCLR;
    } 
    clr_IAPUEN_LDUEN;                    // Disable LDROM modify 
    clr_CHPCON_IAPEN;                    // Disable IAP
}

/**
 * @brief       LDROM blank check
 * @param       u16IAPStartAddress define LDROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Check each byte of LDROM is FFH or not.
 * @example      LDROM_BlanckCheck(0x0000,2048);
 */
void LDROM_Blank_Check(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;
    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_LDROM;

    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;    
        set_IAPTRG_IAPGO;
        if(IAPFD != 0xFF)
          while(1);
        IAPAL++;
        if(IAPAL == 0x00)
          IAPAH++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       LDROM program loop
 * @param       u16IAPStartAddress define LDROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Copy IAPDataBuf to LDROM
 * @example      LDROM_Program(0x0000,1024);
 */
void LDROM_Program(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    set_IAPUEN_LDUEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_PROGRAM_LDROM;
    
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = IAPDataBuf[u16Count];
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_IAPUEN_LDUEN;
    clr_CHPCON_IAPEN;
}


/**
 * @brief       LDROM check loop
 * @param       u16IAPStartAddress define LDROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Check with XRAM IAPDataBuf with LDROM
 * @example     LDROM_Program_Verify(0x0000,1024);
 */
void LDROM_Read_Verify(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_LDROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        if (IAPFD != IAPDataBuf[u16Count])    
            while(1);
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Erase APROM  
 * @param       u16IAPStartAddress define APROM area start address
 * @param       u16IAPDataSize define LDROM need be erase bytes size
 * @return      none
 * @details     Page erase APROM area base on data start address 
 * @example     Erase_APROM(0x0000,2048);
 */
void APROM_Erase(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;                    // Enable IAP function
    set_IAPUEN_APUEN;                    // APROM modify Enable
    IAPFD = 0xFF;                        // IMPORTANT !! To erase function must setting IAPFD = 0xFF 
    IAPCN = PAGE_ERASE_APROM;
    for(u16Count=0x0000;u16Count<u16IAPDataSize/PAGE_SIZE;u16Count++)            // Loop page erase APROM special define address area.
    {        
        IAPAL = LOBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        IAPAH = HIBYTE(u16Count*PAGE_SIZE + u16IAPStartAddress);
        set_IAPTRG_IAPGO_WDCLR; 
    } 
    clr_IAPUEN_APUEN;                    // Disable APROM modify 
    clr_CHPCON_IAPEN;                    // Disable IAP
}

/**
 * @brief       APROM blank check
 * @param       u16IAPStartAddress define APROM area start address
 * @param       u16IAPDataSize define APROM need be erase bytes size
 * @return      none
 * @details     Check each byte of APPROM is FFH or not.
 * @example     APROM_Blank_Check(0x0000,2048);
 */
void APROM_Blank_Check(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;
  
    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_APROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;    
        set_IAPTRG_IAPGO;
        if(IAPFD != 0xFF)
          while(1);
        IAPAL++;
        if(IAPAL == 0x00)
          IAPAH++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       APROM program loop
 * @param       u16IAPStartAddress define APROM area start address
 * @param       u16IAPDataSize define APROM need be erase bytes size
 * @return      none
 * @details     Copy APDataBuf to APROM
 * @example     APROM_Program(0x0000,1024);
 */
void APROM_Program(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    set_IAPUEN_APUEN;    
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_PROGRAM_APROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD=IAPDataBuf[u16Count];
        set_IAPTRG_IAPGO_WDCLR;
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_IAPUEN_APUEN;
    clr_CHPCON_IAPEN;
}

/**
 * @brief       APROM check loop
 * @param       u16IAPStartAddress define APROM area start address
 * @param       u16IAPDataSize define APROM need be erase bytes size
 * @return      none
 * @details     Check with XRAM IAPDataBuf with APROM
 * @example     APROM_Program_Verify(0x0000,1024);
 */
void APROM_Read_Verify(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize)
{   
    unsigned int u16Count;

    set_CHPCON_IAPEN;
    IAPAL = LOBYTE(u16IAPStartAddress);
    IAPAH = HIBYTE(u16IAPStartAddress);
    IAPCN = BYTE_READ_APROM;
    for(u16Count=0;u16Count<u16IAPDataSize;u16Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO_WDCLR;
        if (IAPFD != IAPDataBuf[u16Count])
            while(1);
        IAPAL++;
        if(IAPAL == 0)
        {
            IAPAH++;
        }
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read UID loop
 * @param       none
 * @return      none
 * @details     IAP command read UID area storage data in XRAM LIB_UIDBuffer[0:8]
 * @example     UID_Read();
*/
void UID_Read(void)
{   
    unsigned char u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    for(u8Count=0;u8Count<12;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        UIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read UCID loop
 * @param       none
 * @return      none
 * @details     IAP command read UCID area storage data in XRAM UCIDBuffer[0:8]
 * @example      UCID_Read();
 */
void UCID_Read(void)
{   
    unsigned char u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x20;
    IAPAH = 0x00;
    IAPCN = READ_UID;
    for(u8Count=0;u8Count<12;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        UCIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read DID loop
 * @param       none
 * @return      none
 * @details     IAP command read UID area storage data in XRAM LIB_UIDBuffer[0:8]
 * @example      UID_Read();
*/
void DID_Read(void)
{   
    unsigned char u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = 0x00;
    IAPCN = READ_DID;
    for(u8Count=0;u8Count<2;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        DIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read UID loop
 * @param       none
 * @return      none
 * @details     IAP command read UID area storage data in XRAM LIB_UIDBuffer[0:8]
 * @example      UID_Read();
*/
void PID_Read(void)
{   
    unsigned char u8Count;

    set_CHPCON_IAPEN;
    IAPAL = 0x02;
    IAPAH = 0x00;
    IAPCN = READ_DID;
    for(u8Count=0;u8Count<2;u8Count++)
    {   
        IAPFD = 0x00;
        set_IAPTRG_IAPGO;
        PIDBuffer[u8Count] = IAPFD ;
        IAPAL++;
    } 
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Calculate APROM Checksum
 * @param       u8IAPStartAddressHiByte: start address high byte
   @param       u8ChecksumSize. 0 means full Flash area. size = u8ChecksumSize*256 bytes  
 * @return      none
 * @details     Calculate APROM Checksum for 256 bytes based on start address. 
 * @example     APROM_Checksum_Run(0x3800,1) when start address is 0x3800.
*/
void APROM_Checksum_Run(unsigned int u16IAPStartAddress,unsigned char u8ChecksumSize)
{   
    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = u16IAPStartAddress>>8;
    IAPFD = u8ChecksumSize;
    IAPCN = RUN_APROM_CHECKSUM;
    set_IAPTRG_IAPGO;
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read APROM Checksum
 * @param       u8IAPStartAddressHiByte: start address high byte
 * @return      Checksum value based on APROM_Checksum_Run setting.
 * @details     Read APROM Checksum based on start address.
 * @example     APROM_Checksum_Read(0x3800) when start address is 0x3800.
*/
unsigned char APROM_Checksum_Read(unsigned int u16IAPStartAddress)
{   
    unsigned char CheckSumValue;
    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = u16IAPStartAddress>>8;
    IAPCN = READ_APROM_CHECKSUM;
    IAPFD = 0x00;
    set_IAPTRG_IAPGO;
    CheckSumValue = IAPFD ;
    clr_CHPCON_IAPEN;
    return CheckSumValue;
}

/**
 * @brief       Calculate LDROM Checksum
 * @param       u8IAPStartAddressHiByte: start address high byte
 * @return      none
 * @details     Calculate LDROM Checksum for 256 bytes based on start address.
 * @example     LDROM_Checksum_Run(0x0000,1) when start address is 0x0000 and check 256 bytes.
*/
void LDROM_Checksum_Run(unsigned int u16IAPStartAddress, unsigned char u8ChecksumSize)
{   
    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = u16IAPStartAddress>>8;
    IAPFD = u8ChecksumSize;
    IAPCN = RUN_LDROM_CHECKSUM;
    set_IAPTRG_IAPGO;
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read LDROM Checksum
 * @param       u8IAPStartAddressHiByte: start address high byte
 * @return      Checksum value based on LDROM_Checksum_Run setting.
 * @details     Read LDROM Checksum based on start address.
 * @example     LDROM_Checksum_Read(0x00) when start address is 0x0000.
*/
unsigned char LDROM_Checksum_Read(unsigned int u16IAPStartAddress)
{   
    unsigned char CheckSumValue;
    set_CHPCON_IAPEN;
    IAPAL = 0x00;
    IAPAH = u16IAPStartAddress>>8;
    IAPCN = READ_LDROM_CHECKSUM;
    IAPFD = 0x00;
    set_IAPTRG_IAPGO;
    CheckSumValue = IAPFD ;
    clr_CHPCON_IAPEN;
    return CheckSumValue;
}
/**
 * @brief       Calculate SPROM Checksum
 * @param       none
 * @return      none
 * @details     Calculate SPROM Checksum at 0x0180.
 * @example     SPROM_Checksum_Run()
*/
void SPROM_Checksum_Run(void)
{   
    set_CHPCON_IAPEN;
    IAPAL = 0x80;
    IAPAH = 0x01;
    IAPCN = RUN_SPROM_CHECKSUM;
    set_IAPTRG_IAPGO;//set_IAPTRG_IAPGO;
    clr_CHPCON_IAPEN;
}

/**
 * @brief       Read SPROM Checksum
 * @param       none
 * @return      checksum value based on SPROM setting.
 * @details     Read SPROM Checksum at 0x0180.
 * @example     SPROM_Checksum_Read()
*/
unsigned char SPROM_Checksum_Read(void)
{   
    unsigned char CheckSumValue;
    set_CHPCON_IAPEN;
    IAPAL = 0x80;
    IAPAH = 0x01;
    IAPCN = READ_SPROM_CHECKSUM;
    IAPFD = 1;
    set_IAPTRG_IAPGO;
    CheckSumValue = IAPFD ;
    clr_CHPCON_IAPEN;
    return CheckSumValue;
}
