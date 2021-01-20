extern volatile unsigned char xdata TKCON0;
extern volatile unsigned char xdata TKCON1;
extern volatile unsigned char xdata TKCON2;
extern volatile unsigned char xdata TKSEN0;
extern volatile unsigned char xdata TKSEN1;
extern volatile unsigned char xdata TKREN0;
extern volatile unsigned char xdata TKREN1;
extern volatile unsigned char xdata TKINTEN;
extern volatile unsigned char xdata TKSTA0;
extern volatile unsigned char xdata TKSTA1;
extern volatile unsigned char xdata TKSTA2;

extern volatile unsigned char xdata TKCCBD0;
extern volatile unsigned char xdata TKCCBD1;
extern volatile unsigned char xdata TKCCBD2;
extern volatile unsigned char xdata TKCCBD3;
extern volatile unsigned char xdata TKCCBD4;
extern volatile unsigned char xdata TKCCBD5;
extern volatile unsigned char xdata TKCCBD6;
extern volatile unsigned char xdata TKCCBD7;
extern volatile unsigned char xdata TKCCBD8;
extern volatile unsigned char xdata TKCCBD9;
extern volatile unsigned char xdata TKCCBD10;
extern volatile unsigned char xdata TKCCBD11;
extern volatile unsigned char xdata TKCCBD12;
extern volatile unsigned char xdata TKCCBD13;
extern volatile unsigned char xdata TKCCBD14;
extern volatile unsigned char xdata TKCCBDALL;
extern volatile unsigned char xdata REFCBD0;
extern volatile unsigned char xdata REFCBD1;
extern volatile unsigned char xdata REFCBD2;
extern volatile unsigned char xdata REFCBD3;
extern volatile unsigned char xdata REFCBD4;
extern volatile unsigned char xdata REFCBD5;
extern volatile unsigned char xdata REFCBD6;
extern volatile unsigned char xdata REFCBD7;
extern volatile unsigned char xdata REFCBD8;
extern volatile unsigned char xdata REFCBD9;
extern volatile unsigned char xdata REFCBD10;
extern volatile unsigned char xdata REFCBD11;
extern volatile unsigned char xdata REFCBD12;
extern volatile unsigned char xdata REFCBD13;
extern volatile unsigned char xdata REFCBD14;
extern volatile unsigned char xdata REFCBDALL;
extern volatile unsigned char xdata TKIDLPOL0;
extern volatile unsigned char xdata TKIDLPOL1;
extern volatile unsigned char xdata TKIDLPOL2;
extern volatile unsigned char xdata TKIDLPOL3;
extern volatile unsigned char xdata TKIDLPOL4;
extern volatile unsigned char xdata TKIDLPOL5;
extern volatile unsigned char xdata TKIDLPOL6;
extern volatile unsigned char xdata TKIDLPOL7;
extern volatile unsigned char xdata TKIDLPOL8;
extern volatile unsigned char xdata TKIDLPOL9;
extern volatile unsigned char xdata TKIDLPOL10;
extern volatile unsigned char xdata TKIDLPOL11;
extern volatile unsigned char xdata TKIDLPOL12;
extern volatile unsigned char xdata TKIDLPOL13;
extern volatile unsigned char xdata TKIDLPOL14;

extern volatile unsigned char xdata TKDAT0;
extern volatile unsigned char xdata TKDAT1;
extern volatile unsigned char xdata TKDAT2;
extern volatile unsigned char xdata TKDAT3;
extern volatile unsigned char xdata TKDAT4;
extern volatile unsigned char xdata TKDAT5;
extern volatile unsigned char xdata TKDAT6;
extern volatile unsigned char xdata TKDAT7;
extern volatile unsigned char xdata TKDAT8;
extern volatile unsigned char xdata TKDAT9;
extern volatile unsigned char xdata TKDAT10;
extern volatile unsigned char xdata TKDAT11;
extern volatile unsigned char xdata TKDAT12;
extern volatile unsigned char xdata TKDAT13;
extern volatile unsigned char xdata TKDAT14;
extern volatile unsigned char xdata TKDATALL;
extern volatile unsigned char xdata TKHTH0;
extern volatile unsigned char xdata TKHTH1;
extern volatile unsigned char xdata TKHTH2;
extern volatile unsigned char xdata TKHTH3;
extern volatile unsigned char xdata TKHTH4;
extern volatile unsigned char xdata TKHTH5;
extern volatile unsigned char xdata TKHTH6;
extern volatile unsigned char xdata TKHTH7;
extern volatile unsigned char xdata TKHTH8;
extern volatile unsigned char xdata TKHTH9;
extern volatile unsigned char xdata TKHTH10;
extern volatile unsigned char xdata TKHTH11;
extern volatile unsigned char xdata TKHTH12;
extern volatile unsigned char xdata TKHTH13;
extern volatile unsigned char xdata TKHTH14;
extern volatile unsigned char xdata TKHTHALL;


/**** SFR in XRAM 0x8000 bit define  ****/
/* TKCON0  0x8000  */
#define set_TKCON0_TKEN                         TKCON0|=SET_BIT2
#define set_TKCON0_TMRTRG_EN                    TKCON0|=SET_BIT1
#define set_TKCON0_SCAN                         TKCON0|=SET_BIT0

#define clr_TKCON0_TKEN                         TKCON0&=CLR_BIT2
#define clr_TKCON0_TMRTRG_EN                    TKCON0&=CLR_BIT1
#define clr_TKCON0_SCAN                         TKCON0&=CLR_BIT0 

/* TKCON1  0x8001  */
/* TKCON2  0x8002  */
#define set_TKCON2_POL_INT                      TKCON2|=SET_BIT2
#define set_TKCON2_POL_CAP_1                    TKCON2|=SET_BIT1
#define set_TKCON2_POL_CAP_0                    TKCON2|=SET_BIT0

#define clr_TKCON2_POL_INT                      TKCON2&=CLR_BIT2
#define clr_TKCON2_POL_CAP_1                    TKCON2&=CLR_BIT1
#define clr_TKCON2_POL_CAP_0                    TKCON2&=CLR_BIT0

/* TKSEN0  0x8003  */
#define set_TKSEN0_TK7SEN                       TKSEN0|=SET_BIT7
#define set_TKSEN0_TK6SEN                       TKSEN0|=SET_BIT6
#define set_TKSEN0_TK5SEN                       TKSEN0|=SET_BIT5
#define set_TKSEN0_TK4SEN                       TKSEN0|=SET_BIT4
#define set_TKSEN0_TK3SEN                       TKSEN0|=SET_BIT3
#define set_TKSEN0_TK2SEN                       TKSEN0|=SET_BIT2
#define set_TKSEN0_TK1SEN                       TKSEN0|=SET_BIT1
#define set_TKSEN0_TK0SEN                       TKSEN0|=SET_BIT0

#define clr_TKSEN0_TK7SEN                       TKSEN0&=CLR_BIT7
#define clr_TKSEN0_TK6SEN                       TKSEN0&=CLR_BIT6
#define clr_TKSEN0_TK5SEN                       TKSEN0&=CLR_BIT5
#define clr_TKSEN0_TK4SEN                       TKSEN0&=CLR_BIT4
#define clr_TKSEN0_TK3SEN                       TKSEN0&=CLR_BIT3
#define clr_TKSEN0_TK2SEN                       TKSEN0&=CLR_BIT2
#define clr_TKSEN0_TK1SEN                       TKSEN0&=CLR_BIT1
#define clr_TKSEN0_TK0SEN                       TKSEN0&=CLR_BIT0

/* TKSEN1  0x8004  */
#define set_TKSEN1_TK14SEN                      TKSEN1|=SET_BIT7
#define set_TKSEN1_TK13SEN                      TKSEN1|=SET_BIT6
#define set_TKSEN1_TK12SEN                      TKSEN1|=SET_BIT5
#define set_TKSEN1_TK11SEN                      TKSEN1|=SET_BIT4
#define set_TKSEN1_TK10SEN                      TKSEN1|=SET_BIT3
#define set_TKSEN1_TK9SEN                       TKSEN1|=SET_BIT2
#define set_TKSEN1_TK8SEN                       TKSEN1|=SET_BIT1
#define set_TKSEN1_TK7SEN                       TKSEN1|=SET_BIT0

#define clr_TKSEN1_TK14SEN                      TKSEN1&=CLR_BIT7
#define clr_TKSEN1_TK13SEN                      TKSEN1&=CLR_BIT6
#define clr_TKSEN1_TK12SEN                      TKSEN1&=CLR_BIT5
#define clr_TKSEN1_TK11SEN                      TKSEN1&=CLR_BIT4
#define clr_TKSEN1_TK10SEN                      TKSEN1&=CLR_BIT3
#define clr_TKSEN1_TK9SEN                       TKSEN1&=CLR_BIT2
#define clr_TKSEN1_TK8SEN                       TKSEN1&=CLR_BIT1
#define clr_TKSEN1_TK7SEN                       TKSEN1&=CLR_BIT0

/* TKREN0  0x8005  */
#define set_TKREN0_TK7REN                       TKREN0|=SET_BIT7
#define set_TKREN0_TK6REN                       TKREN0|=SET_BIT6
#define set_TKREN0_TK5REN                       TKREN0|=SET_BIT5
#define set_TKREN0_TK4REN                       TKREN0|=SET_BIT4
#define set_TKREN0_TK3REN                       TKREN0|=SET_BIT3
#define set_TKREN0_TK2REN                       TKREN0|=SET_BIT2
#define set_TKREN0_TK1REN                       TKREN0|=SET_BIT1
#define set_TKREN0_TK0REN                       TKREN0|=SET_BIT0

#define clr_TKREN0_TK7REN                       TKREN0&=CLR_BIT7
#define clr_TKREN0_TK6REN                       TKREN0&=CLR_BIT6
#define clr_TKREN0_TK5REN                       TKREN0&=CLR_BIT5
#define clr_TKREN0_TK4REN                       TKREN0&=CLR_BIT4
#define clr_TKREN0_TK3REN                       TKREN0&=CLR_BIT3
#define clr_TKREN0_TK2REN                       TKREN0&=CLR_BIT2
#define clr_TKREN0_TK1REN                       TKREN0&=CLR_BIT1
#define clr_TKREN0_TK0REN                       TKREN0&=CLR_BIT0

/* TKREN1  0x8006  */
#define set_TKREN1_TK14REN                      TKREN1|=SET_BIT7
#define set_TKREN1_TK13REN                      TKREN1|=SET_BIT6
#define set_TKREN1_TK12REN                      TKREN1|=SET_BIT5
#define set_TKREN1_TK11REN                      TKREN1|=SET_BIT4
#define set_TKREN1_TK10REN                      TKREN1|=SET_BIT3
#define set_TKREN1_TK9REN                       TKREN1|=SET_BIT2
#define set_TKREN1_TK8REN                       TKREN1|=SET_BIT1
#define set_TKREN1_TK7REN                       TKREN1|=SET_BIT0
             
#define clr_TKREN1_TK14REN                      TKREN1&=CLR_BIT7
#define clr_TKREN1_TK13REN                      TKREN1&=CLR_BIT6
#define clr_TKREN1_TK12REN                      TKREN1&=CLR_BIT5
#define clr_TKREN1_TK11REN                      TKREN1&=CLR_BIT4
#define clr_TKREN1_TK10REN                      TKREN1&=CLR_BIT3
#define clr_TKREN1_TK9REN                       TKREN1&=CLR_BIT2
#define clr_TKREN1_TK8REN                       TKREN1&=CLR_BIT1
#define clr_TKREN1_TK7REN                       TKREN1&=CLR_BIT0

/* TKINTEN  0x8007  */
#define set_TKINTEN_TKSCIE                      TKINTEN|=SET_BIT1
#define set_TKINTEN_TKSCTHIE                    TKINTEN|=SET_BIT0

#define clr_TKINTEN_TKSCIE                      TKINTEN&=CLR_BIT1
#define clr_TKINTEN_TKSCTHIE                    TKINTEN&=CLR_BIT0

/* TKSTA0   0x8008  */
#define set_TKSTA0_TKIF_ALL                     TKINTEN|=SET_BIT3
#define set_TKSTA0_TKIF                         TKINTEN|=SET_BIT2
#define set_TKSTA0_TKSCIF                       TKINTEN|=SET_BIT1
#define set_TKSTA0_TKBUSY                       TKINTEN|=SET_BIT0

#define clr_TKSTA0_TKIF_ALL                     TKINTEN&=CLR_BIT3
#define clr_TKSTA0_TKIF                         TKINTEN&=CLR_BIT2
#define clr_TKSTA0_TKSCIF                       TKINTEN&=CLR_BIT1
#define clr_TKSTA0_TKBUSY                       TKINTEN&=CLR_BIT0

/* TKSTA1   0x8009  */
#define clr_TKSTA1_TKIF7                        TKSTA1&=CLR_BIT7
#define clr_TKSTA1_TKIF6                        TKSTA1&=CLR_BIT6
#define clr_TKSTA1_TKIF5                        TKSTA1&=CLR_BIT5
#define clr_TKSTA1_TKIF4                        TKSTA1&=CLR_BIT4
#define clr_TKSTA1_TKIF3                        TKSTA1&=CLR_BIT3
#define clr_TKSTA1_TKIF2                        TKSTA1&=CLR_BIT2
#define clr_TKSTA1_TKIF1                        TKSTA1&=CLR_BIT1
#define clr_TKSTA1_TKIF0                        TKSTA1&=CLR_BIT0

/* TKSTA2   0x800A  */
#define clr_TKSTA2_TKIF14                       TKSTA2&=CLR_BIT6
#define clr_TKSTA2_TKIF13                       TKSTA2&=CLR_BIT5
#define clr_TKSTA2_TKIF12                       TKSTA2&=CLR_BIT4
#define clr_TKSTA2_TKIF11                       TKSTA2&=CLR_BIT3
#define clr_TKSTA2_TKIF10                       TKSTA2&=CLR_BIT2
#define clr_TKSTA2_TKIF9                        TKSTA2&=CLR_BIT1
#define clr_TKSTA2_TKIF8                        TKSTA2&=CLR_BIT0

/* TKCCBD0   0x8010  */
/* TKCCBD1   0x8011  */
/* TKCCBD2   0x8012  */
/* TKCCBD3   0x8013  */
/* TKCCBD4   0x8014  */
/* TKCCBD5   0x8015  */
/* TKCCBD6   0x8016  */
/* TKCCBD7   0x8017  */
/* TKCCBD8   0x8018  */
/* TKCCBD9   0x8019  */
/* TKCCBD10  0x801A  */
/* TKCCBD11  0x801B  */
/* TKCCBD12  0x801C  */
/* TKCCBD13  0x801D  */
/* TKCCBD14  0x801E  */
/* TKCCBDALL 0x801F  */

/* REFCBD0   0x8020  */
/* REFCBD1   0x8021  */
/* REFCBD2   0x8022  */
/* REFCBD3   0x8023  */
/* REFCBD4   0x8024  */
/* REFCBD5   0x8025  */
/* REFCBD6   0x8026  */
/* REFCBD7   0x8027  */
/* REFCBD8   0x8028  */
/* REFCBD9   0x8029  */
/* REFCBD10  0x802A  */
/* REFCBD11  0x802B  */
/* REFCBD12  0x802C  */
/* REFCBD13  0x802D  */
/* REFCBD14  0x802E  */
/* REFCBDALL 0x802F  */

/* TKIDLPOL0   0x8030  */
#define set_TKIDLPOL0_TKSCIE               TKIDLPOL0|=SET_BIT4
#define set_TKIDLPOL0_POL_1                TKIDLPOL0|=SET_BIT3
#define set_TKIDLPOL0_POL_0                TKIDLPOL0|=SET_BIT2
#define set_TKIDLPOL0_IDLS_1               TKIDLPOL0|=SET_BIT1
#define set_TKIDLPOL0_IDLS_0               TKIDLPOL0|=SET_BIT0

#define clr_TKIDLPOL0_TKSCIE               TKIDLPOL0&=CLR_BIT4
#define clr_TKIDLPOL0_POL_1                TKIDLPOL0&=CLR_BIT3
#define clr_TKIDLPOL0_POL_0                TKIDLPOL0&=CLR_BIT2
#define clr_TKIDLPOL0_IDLS_1               TKIDLPOL0&=CLR_BIT1
#define clr_TKIDLPOL0_IDLS_0               TKIDLPOL0&=CLR_BIT0

/* TKIDLPOL1   0x8031  */
#define set_TKIDLPOL1_TKSCIE               TKIDLPOL1|=SET_BIT4
#define set_TKIDLPOL1_POL_1                TKIDLPOL1|=SET_BIT3
#define set_TKIDLPOL1_POL_0                TKIDLPOL1|=SET_BIT2
#define set_TKIDLPOL1_IDLS_1               TKIDLPOL1|=SET_BIT1
#define set_TKIDLPOL1_IDLS_0               TKIDLPOL1|=SET_BIT0

#define clr_TKIDLPOL1_TKSCIE               TKIDLPOL1&=CLR_BIT4
#define clr_TKIDLPOL1_POL_1                TKIDLPOL1&=CLR_BIT3
#define clr_TKIDLPOL1_POL_0                TKIDLPOL1&=CLR_BIT2
#define clr_TKIDLPOL1_IDLS_1               TKIDLPOL1&=CLR_BIT1
#define clr_TKIDLPOL1_IDLS_0               TKIDLPOL1&=CLR_BIT0

/* TKIDLPOL2   0x8032  */
#define set_TKIDLPOL2_TKSCIE               TKIDLPOL2|=SET_BIT4
#define set_TKIDLPOL2_POL_1                TKIDLPOL2|=SET_BIT3
#define set_TKIDLPOL2_POL_0                TKIDLPOL2|=SET_BIT2
#define set_TKIDLPOL2_IDLS_1               TKIDLPOL2|=SET_BIT1
#define set_TKIDLPOL2_IDLS_0               TKIDLPOL2|=SET_BIT0

#define clr_TKIDLPOL2_TKSCIE               TKIDLPOL2&=CLR_BIT4
#define clr_TKIDLPOL2_POL_1                TKIDLPOL2&=CLR_BIT3
#define clr_TKIDLPOL2_POL_0                TKIDLPOL2&=CLR_BIT2
#define clr_TKIDLPOL2_IDLS_1               TKIDLPOL2&=CLR_BIT1
#define clr_TKIDLPOL2_IDLS_0               TKIDLPOL2&=CLR_BIT0

/* TKIDLPOL3   0x8033  */
#define set_TKIDLPOL3_TKSCIE               TKIDLPOL3|=SET_BIT4
#define set_TKIDLPOL3_POL_1                TKIDLPOL3|=SET_BIT3
#define set_TKIDLPOL3_POL_0                TKIDLPOL3|=SET_BIT2
#define set_TKIDLPOL3_IDLS_1               TKIDLPOL3|=SET_BIT1
#define set_TKIDLPOL3_IDLS_0               TKIDLPOL3|=SET_BIT0

#define clr_TKIDLPOL3_TKSCIE               TKIDLPOL3&=CLR_BIT4
#define clr_TKIDLPOL3_POL_1                TKIDLPOL3&=CLR_BIT3
#define clr_TKIDLPOL3_POL_0                TKIDLPOL3&=CLR_BIT2
#define clr_TKIDLPOL3_IDLS_1               TKIDLPOL3&=CLR_BIT1
#define clr_TKIDLPOL3_IDLS_0               TKIDLPOL3&=CLR_BIT0

/* TKIDLPOL4   0x8034  */
#define set_TKIDLPOL4_TKSCIE               TKIDLPOL4|=SET_BIT4
#define set_TKIDLPOL4_POL_1                TKIDLPOL4|=SET_BIT3
#define set_TKIDLPOL4_POL_0                TKIDLPOL4|=SET_BIT2
#define set_TKIDLPOL4_IDLS_1               TKIDLPOL4|=SET_BIT1
#define set_TKIDLPOL4_IDLS_0               TKIDLPOL4|=SET_BIT0

#define clr_TKIDLPOL4_TKSCIE               TKIDLPOL4&=CLR_BIT4
#define clr_TKIDLPOL4_POL_1                TKIDLPOL4&=CLR_BIT3
#define clr_TKIDLPOL4_POL_0                TKIDLPOL4&=CLR_BIT2
#define clr_TKIDLPOL4_IDLS_1               TKIDLPOL4&=CLR_BIT1
#define clr_TKIDLPOL4_IDLS_0               TKIDLPOL4&=CLR_BIT0

/* TKIDLPOL5   0x8035  */
#define set_TKIDLPOL5_TKSCIE               TKIDLPOL5|=SET_BIT4
#define set_TKIDLPOL5_POL_1                TKIDLPOL5|=SET_BIT3
#define set_TKIDLPOL5_POL_0                TKIDLPOL5|=SET_BIT2
#define set_TKIDLPOL5_IDLS_1               TKIDLPOL5|=SET_BIT1
#define set_TKIDLPOL5_IDLS_0               TKIDLPOL5|=SET_BIT0

#define clr_TKIDLPOL5_TKSCIE               TKIDLPOL5&=CLR_BIT4
#define clr_TKIDLPOL5_POL_1                TKIDLPOL5&=CLR_BIT3
#define clr_TKIDLPOL5_POL_0                TKIDLPOL5&=CLR_BIT2
#define clr_TKIDLPOL5_IDLS_1               TKIDLPOL5&=CLR_BIT1
#define clr_TKIDLPOL5_IDLS_0               TKIDLPOL5&=CLR_BIT0

/* TKIDLPOL6   0x8036  */
#define set_TKIDLPOL6_TKSCIE               TKIDLPOL6|=SET_BIT4
#define set_TKIDLPOL6_POL_1                TKIDLPOL6|=SET_BIT3
#define set_TKIDLPOL6_POL_0                TKIDLPOL6|=SET_BIT2
#define set_TKIDLPOL6_IDLS_1               TKIDLPOL6|=SET_BIT1
#define set_TKIDLPOL6_IDLS_0               TKIDLPOL6|=SET_BIT0

#define clr_TKIDLPOL6_TKSCIE               TKIDLPOL6&=CLR_BIT4
#define clr_TKIDLPOL6_POL_1                TKIDLPOL6&=CLR_BIT3
#define clr_TKIDLPOL6_POL_0                TKIDLPOL6&=CLR_BIT2
#define clr_TKIDLPOL6_IDLS_1               TKIDLPOL6&=CLR_BIT1
#define clr_TKIDLPOL6_IDLS_0               TKIDLPOL6&=CLR_BIT0

/* TKIDLPOL7   0x8037  */
#define set_TKIDLPOL7_TKSCIE               TKIDLPOL7|=SET_BIT4
#define set_TKIDLPOL7_POL_1                TKIDLPOL7|=SET_BIT3
#define set_TKIDLPOL7_POL_0                TKIDLPOL7|=SET_BIT2
#define set_TKIDLPOL7_IDLS_1               TKIDLPOL7|=SET_BIT1
#define set_TKIDLPOL7_IDLS_0               TKIDLPOL7|=SET_BIT0

#define clr_TKIDLPOL7_TKSCIE               TKIDLPOL7&=CLR_BIT4
#define clr_TKIDLPOL7_POL_1                TKIDLPOL7&=CLR_BIT3
#define clr_TKIDLPOL7_POL_0                TKIDLPOL7&=CLR_BIT2
#define clr_TKIDLPOL7_IDLS_1               TKIDLPOL7&=CLR_BIT1
#define clr_TKIDLPOL7_IDLS_0               TKIDLPOL7&=CLR_BIT0

/* TKIDLPOL8   0x8038  */
#define set_TKIDLPOL8_TKSCIE               TKIDLPOL8|=SET_BIT4
#define set_TKIDLPOL8_POL_1                TKIDLPOL8|=SET_BIT3
#define set_TKIDLPOL8_POL_0                TKIDLPOL8|=SET_BIT2
#define set_TKIDLPOL8_IDLS_1               TKIDLPOL8|=SET_BIT1
#define set_TKIDLPOL8_IDLS_0               TKIDLPOL8|=SET_BIT0

#define clr_TKIDLPOL8_TKSCIE               TKIDLPOL8&=CLR_BIT4
#define clr_TKIDLPOL8_POL_1                TKIDLPOL8&=CLR_BIT3
#define clr_TKIDLPOL8_POL_0                TKIDLPOL8&=CLR_BIT2
#define clr_TKIDLPOL8_IDLS_1               TKIDLPOL8&=CLR_BIT1
#define clr_TKIDLPOL8_IDLS_0               TKIDLPOL8&=CLR_BIT0

/* TKIDLPOL9   0x8039  */
#define set_TKIDLPOL9_TKSCIE               TKIDLPOL9|=SET_BIT4
#define set_TKIDLPOL9_POL_1                TKIDLPOL9|=SET_BIT3
#define set_TKIDLPOL9_POL_0                TKIDLPOL9|=SET_BIT2
#define set_TKIDLPOL9_IDLS_1               TKIDLPOL9|=SET_BIT1
#define set_TKIDLPOL9_IDLS_0               TKIDLPOL9|=SET_BIT0

#define clr_TKIDLPOL9_TKSCIE               TKIDLPOL9&=CLR_BIT4
#define clr_TKIDLPOL9_POL_1                TKIDLPOL9&=CLR_BIT3
#define clr_TKIDLPOL9_POL_0                TKIDLPOL9&=CLR_BIT2
#define clr_TKIDLPOL9_IDLS_1               TKIDLPOL9&=CLR_BIT1
#define clr_TKIDLPOL9_IDLS_0               TKIDLPOL9&=CLR_BIT0

/* TKIDLPOL10  0x803A  */
#define set_TKIDLPOL10_TKSCIE              TKIDLPOL10|=SET_BIT4
#define set_TKIDLPOL10_POL_1               TKIDLPOL10|=SET_BIT3
#define set_TKIDLPOL10_POL_0               TKIDLPOL10|=SET_BIT2
#define set_TKIDLPOL10_IDLS_1              TKIDLPOL10|=SET_BIT1
#define set_TKIDLPOL10_IDLS_0              TKIDLPOL10|=SET_BIT0

#define clr_TKIDLPOL10_TKSCIE              TKIDLPOL10&=CLR_BIT4
#define clr_TKIDLPOL10_POL_1               TKIDLPOL10&=CLR_BIT3
#define clr_TKIDLPOL10_POL_0               TKIDLPOL10&=CLR_BIT2
#define clr_TKIDLPOL10_IDLS_1              TKIDLPOL10&=CLR_BIT1
#define clr_TKIDLPOL10_IDLS_0              TKIDLPOL10&=CLR_BIT0

/* TKIDLPOL11  0x803B  */
#define set_TKIDLPOL11_TKSCIE              TKIDLPOL11|=SET_BIT4
#define set_TKIDLPOL11_POL_1               TKIDLPOL11|=SET_BIT3
#define set_TKIDLPOL11_POL_0               TKIDLPOL11|=SET_BIT2
#define set_TKIDLPOL11_IDLS_1              TKIDLPOL11|=SET_BIT1
#define set_TKIDLPOL11_IDLS_0              TKIDLPOL11|=SET_BIT0

#define clr_TKIDLPOL11_TKSCIE              TKIDLPOL11&=CLR_BIT4
#define clr_TKIDLPOL11_POL_1               TKIDLPOL11&=CLR_BIT3
#define clr_TKIDLPOL11_POL_0               TKIDLPOL11&=CLR_BIT2
#define clr_TKIDLPOL11_IDLS_1              TKIDLPOL11&=CLR_BIT1
#define clr_TKIDLPOL11_IDLS_0              TKIDLPOL11&=CLR_BIT0

/* TKIDLPOL12  0x803C  */
#define set_TKIDLPOL12_TKSCIE              TKIDLPOL12|=SET_BIT4
#define set_TKIDLPOL12_POL_1               TKIDLPOL12|=SET_BIT3
#define set_TKIDLPOL12_POL_0               TKIDLPOL12|=SET_BIT2
#define set_TKIDLPOL12_IDLS_1              TKIDLPOL12|=SET_BIT1
#define set_TKIDLPOL12_IDLS_0              TKIDLPOL12|=SET_BIT0

#define clr_TKIDLPOL12_TKSCIE              TKIDLPOL12&=CLR_BIT4
#define clr_TKIDLPOL12_POL_1               TKIDLPOL12&=CLR_BIT3
#define clr_TKIDLPOL12_POL_0               TKIDLPOL12&=CLR_BIT2
#define clr_TKIDLPOL12_IDLS_1              TKIDLPOL12&=CLR_BIT1
#define clr_TKIDLPOL12_IDLS_0              TKIDLPOL12&=CLR_BIT0

/* TKIDLPOL13  0x803D  */
#define set_TKIDLPOL13_TKSCIE              TKIDLPOL13|=SET_BIT4
#define set_TKIDLPOL13_POL_1               TKIDLPOL13|=SET_BIT3
#define set_TKIDLPOL13_POL_0               TKIDLPOL13|=SET_BIT2
#define set_TKIDLPOL13_IDLS_1              TKIDLPOL13|=SET_BIT1
#define set_TKIDLPOL13_IDLS_0              TKIDLPOL13|=SET_BIT0

#define clr_TKIDLPOL13_TKSCIE              TKIDLPOL13&=CLR_BIT4
#define clr_TKIDLPOL13_POL_1               TKIDLPOL13&=CLR_BIT3
#define clr_TKIDLPOL13_POL_0               TKIDLPOL13&=CLR_BIT2
#define clr_TKIDLPOL13_IDLS_1              TKIDLPOL13&=CLR_BIT1
#define clr_TKIDLPOL13_IDLS_0              TKIDLPOL13&=CLR_BIT0

/* TKIDLPOL14  0x803E  */
#define set_TKIDLPOL14_TKSCIE              TKIDLPOL14|=SET_BIT4
#define set_TKIDLPOL14_POL_1               TKIDLPOL14|=SET_BIT3
#define set_TKIDLPOL14_POL_0               TKIDLPOL14|=SET_BIT2
#define set_TKIDLPOL14_IDLS_1              TKIDLPOL14|=SET_BIT1
#define set_TKIDLPOL14_IDLS_0              TKIDLPOL14|=SET_BIT0

#define clr_TKIDLPOL14_TKSCIE              TKIDLPOL14&=CLR_BIT4
#define clr_TKIDLPOL14_POL_1               TKIDLPOL14&=CLR_BIT3
#define clr_TKIDLPOL14_POL_0               TKIDLPOL14&=CLR_BIT2
#define clr_TKIDLPOL14_IDLS_1              TKIDLPOL14&=CLR_BIT1
#define clr_TKIDLPOL14_IDLS_0              TKIDLPOL14&=CLR_BIT0

/* TKIDLPOLALL 0x803F  */
#define set_TKIDLPOLALL_TKSCIE             TKIDLPOLALL|=SET_BIT4
#define set_TKIDLPOLALL_POL_1              TKIDLPOLALL|=SET_BIT3
#define set_TKIDLPOLALL_POL_0              TKIDLPOLALL|=SET_BIT2
#define set_TKIDLPOLALL_IDLS_1             TKIDLPOLALL|=SET_BIT1
#define set_TKIDLPOLALL_IDLS_0             TKIDLPOLALL|=SET_BIT0

#define clr_TKIDLPOLALL_TKSCIE             TKIDLPOLALL&=CLR_BIT4
#define clr_TKIDLPOLALL_POL_1              TKIDLPOLALL&=CLR_BIT3
#define clr_TKIDLPOLALL_POL_0              TKIDLPOLALL&=CLR_BIT2
#define clr_TKIDLPOLALL_IDLS_1             TKIDLPOLALL&=CLR_BIT1
#define clr_TKIDLPOLALL_IDLS_0             TKIDLPOLALL&=CLR_BIT0

/* TKDAT0   0x8040  */
/* TKDAT1   0x8041  */
/* TKDAT2   0x8042  */
/* TKDAT3   0x8043  */
/* TKDAT4   0x8044  */
/* TKDAT5   0x8045  */
/* TKDAT6   0x8046  */
/* TKDAT7   0x8047  */
/* TKDAT8   0x8048  */
/* TKDAT9   0x8049  */
/* TKDAT10  0x804A  */
/* TKDAT11  0x804B  */
/* TKDAT12  0x804C  */
/* TKDAT13  0x804D  */
/* TKDAT14  0x804E  */
/* TKDATALL 0x804F  */

/* TKHTH0   0x8050  */
/* TKHTH1   0x8051  */
/* TKHTH2   0x8052  */
/* TKHTH3   0x8053  */
/* TKHTH4   0x8054  */
/* TKHTH5   0x8055  */
/* TKHTH6   0x8056  */
/* TKHTH7   0x8057  */
/* TKHTH8   0x8058  */
/* TKHTH9   0x8059  */
/* TKHTH10  0x805A  */
/* TKHTH11  0x805B  */
/* TKHTH12  0x805C  */
/* TKHTH13  0x805D  */
/* TKHTH14  0x805E  */
/* TKHTHALL 0x805F  */



#define TK_TKCON0_SCAN_Pos                (0)                                               
#define TK_TKCON0_SCAN_Msk                (0x1ul << TK_TKCON0_SCAN_Pos)     

#define TK_TKCON0_TMRTRG_EN_Pos           (1)                                            
#define TK_TKCON0_TMRTRG_EN_Msk           (0x1ul << TK_TKCON0_TMRTRG_EN_Pos)  

#define TK_TKCON0_TK_EN_Pos               (2)                                
#define TK_TKCON0_TK_EN_Msk               (0x1ul << TK_TKCON0_TK_EN_Pos) 

#define TK_TKCON0_SCAN_ALL_Pos            (3)                            
#define TK_TKCON0_SCAN_ALL_Msk            (0x1ul << TK_TKCON0_SCAN_ALL_Pos) 

#define TK_TKCON0_AVDDH_S_Pos             (4) 
#define TK_TKCON0_AVDDH_S_Msk             (0xFul << TK_TKCON0_AVDDH_S_Pos) 

#define TK_TKCON1_SENSET_Pos              (0)                           
#define TK_TKCON1_SENSET_Msk              (0x7ul << TK_TKCON1_SENSET_Pos) 
         
#define TK_TKCON1_PULSET_Pos              (4)                             
#define TK_TKCON1_PULSET_Msk              (0x7ul << TK_TKCON1_PULSET_Pos) 

#define TK_TKCON1_IRVEN_Pos               (7)                            
#define TK_TKCON1_IRVEN_Msk               (0x1ul << TK_TKCON1_PULSET_Pos) 

#define TK_TKCON2_POL_CAP_Pos             (0)                            
#define TK_TKCON2_POL_CAP_Msk             (0x3ul << TK_TKCON2_POL_CAP_Pos)

#define TK_TKCON2_POL_INIT_Pos            (2)                            
#define TK_TKCON2_POL_INIT_Msk            (0x1ul << TK_TKCON2_POL_INIT_Pos)

#define TK_TKSEN0_TK0SEN_Pos              (0)                            
#define TK_TKSEN0_TK0SEN_Msk              (0x1ul << TK_TKSEN0_TK0SEN_Pos)

#define TK_TKSEN0_TK1SEN_Pos              (1)                            
#define TK_TKSEN0_TK1SEN_Msk              (0x1ul << TK_TKSEN0_TK1SEN_Pos)

#define TK_TKSEN0_TK2SEN_Pos              (2)                            
#define TK_TKSEN0_TK2SEN_Msk              (0x1ul << TK_TKSEN0_TK2SEN_Pos)

#define TK_TKSEN0_TK3SEN_Pos              (3)                            
#define TK_TKSEN0_TK3SEN_Msk              (0x1ul << TK_TKSEN0_TK3SEN_Pos)

#define TK_TKSEN0_TK4SEN_Pos              (4)                            
#define TK_TKSEN0_TK4SEN_Msk              (0x1ul << TK_TKSEN0_TK4SEN_Pos)

#define TK_TKSEN0_TK5SEN_Pos              (5)                            
#define TK_TKSEN0_TK5SEN_Msk              (0x1ul << TK_TKSEN0_TK5SEN_Pos)

#define TK_TKSEN0_TK6SEN_Pos              (6)                            
#define TK_TKSEN0_TK6SEN_Msk              (0x1ul << TK_TKSEN0_TK6SEN_Pos)

#define TK_TKSEN0_TK7SEN_Pos              (7)                            
#define TK_TKSEN0_TK7SEN_Msk              (0x1ul << TK_TKSEN0_TK7SEN_Pos)


#define TK_TKSEN1_TK8SEN_Pos              (0)                            
#define TK_TKSEN1_TK8SEN_Msk              (0x1ul << TK_TKSEN1_TK8SEN_Pos)

#define TK_TKSEN1_TK9SEN_Pos              (1)                            
#define TK_TKSEN1_TK9SEN_Msk              (0x1ul << TK_TKSEN1_TK9SEN_Pos)

#define TK_TKSEN1_TK10SEN_Pos             (2)                            
#define TK_TKSEN1_TK10SEN_Msk             (0x1ul << TK_TKSEN1_TK10SEN_Pos)

#define TK_TKSEN1_TK11SEN_Pos             (3)                            
#define TK_TKSEN1_TK11SEN_Msk             (0x1ul << TK_TKSEN1_TK11SEN_Pos)

#define TK_TKSEN1_TK12SEN_Pos             (4)                            
#define TK_TKSEN1_TK12SEN_Msk             (0x1ul << TK_TKSEN1_TK12SEN_Pos)

#define TK_TKSEN1_TK13SEN_Pos             (5)                            
#define TK_TKSEN1_TK13SEN_Msk             (0x1ul << TK_TKSEN1_TK13SEN_Pos)

#define TK_TKSEN1_TK14SEN_Pos             (6)                            
#define TK_TKSEN1_TK14SEN_Msk             (0x1ul << TK_TKSEN1_TK14SEN_Pos)



#define TK_TKREN0_TK0REN_Pos              (0)                            
#define TK_TKREN0_TK0REN_Msk              (0x1ul << TK_TKREN0_TK0REN_Pos)

#define TK_TKREN0_TK1REN_Pos              (1)                            
#define TK_TKREN0_TK1REN_Msk              (0x1ul << TK_TKREN0_TK1REN_Pos)

#define TK_TKREN0_TK2REN_Pos              (2)                            
#define TK_TKREN0_TK2REN_Msk              (0x1ul << TK_TKREN0_TK2REN_Pos)

#define TK_TKREN0_TK3REN_Pos              (3)                            
#define TK_TKREN0_TK3REN_Msk              (0x1ul << TK_TKREN0_TK3REN_Pos)

#define TK_TKREN0_TK4REN_Pos              (4)                            
#define TK_TKREN0_TK4REN_Msk              (0x1ul << TK_TKREN0_TK4REN_Pos)

#define TK_TKREN0_TK5REN_Pos              (5)                            
#define TK_TKREN0_TK5REN_Msk              (0x1ul << TK_TKREN0_TK5REN_Pos)

#define TK_TKREN0_TK6REN_Pos              (6)                            
#define TK_TKREN0_TK6REN_Msk              (0x1ul << TK_TKREN0_TK6REN_Pos)

#define TK_TKREN0_TK7REN_Pos              (7)                            
#define TK_TKREN0_TK7REN_Msk              (0x1ul << TK_TKREN0_TK7REN_Pos)


#define TK_TKREN1_TK8REN_Pos              (0)                            
#define TK_TKREN1_TK8REN_Msk              (0x1ul << TK_TKREN1_TK8REN_Pos)

#define TK_TKREN1_TK9REN_Pos              (1)                            
#define TK_TKREN1_TK9REN_Msk              (0x1ul << TK_TKREN1_TK9REN_Pos)

#define TK_TKREN1_TK10REN_Pos             (2)                            
#define TK_TKREN1_TK10REN_Msk             (0x1ul << TK_TKREN1_TK10REN_Pos)

#define TK_TKREN1_TK11REN_Pos             (3)                            
#define TK_TKREN1_TK11REN_Msk             (0x1ul << TK_TKREN1_TK11REN_Pos)

#define TK_TKREN1_TK12REN_Pos             (4)                            
#define TK_TKREN1_TK12REN_Msk             (0x1ul << TK_TKREN1_TK12REN_Pos)

#define TK_TKREN1_TK13REN_Pos             (5)                            
#define TK_TKREN1_TK13REN_Msk             (0x1ul << TK_TKREN1_TK13REN_Pos)

#define TK_TKREN1_TK14REN_Pos             (6)                            
#define TK_TKREN1_TK14REN_Msk             (0x1ul << TK_TKREN1_TK14REN_Pos)


#define TK_TKINTEN_SCTHIE_Pos             (0)                            
#define TK_TKINTEN_SCTHIE_Msk             (0x1ul << TK_TKINTEN_SCTHIE_Pos)

#define TK_TKINTEN_SCIE_Pos               (1)                            
#define TK_TKINTEN_SCIE_Msk               (0x1ul << TK_TKINTEN_SCIE_Pos)

#define TK_TKSTA0_BUSY_Pos                (0)                            
#define TK_TKSTA0_BUSY_Msk                (0x1ul << TK_TKSTA0_BUSY_Pos)

#define TK_TKSTA0_SCIF_Pos                (1)                            
#define TK_TKSTA0_SCIF_Msk                (0x1ul << TK_TKSTA0_SCIF_Pos)

#define TK_TKSTA0_TKIF_Pos                (2)                            
#define TK_TKSTA0_TKIF_Msk                (0x1ul << TK_TKSTA0_TKIF_Pos)

#define TK_TKSTA0_TKIF_ALL_Pos            (3)                            
#define TK_TKSTA0_TKIF_ALL_Msk            (0x1ul << TK_TKSTA0_TKIF_ALL_Pos)


#define TK_TKSTA1_TKIF0_Pos               (0)                            
#define TK_TKSTA1_TKIF0_Msk               (0x1ul << TK_TKSTA1_TKIF0_Pos)

#define TK_TKSTA1_TKIF1_Pos               (1)                            
#define TK_TKSTA1_TKIF1_Msk               (0x1ul << TK_TKSTA1_TKIF1_Pos)

#define TK_TKSTA1_TKIF2_Pos               (2)                            
#define TK_TKSTA1_TKIF2_Msk               (0x1ul << TK_TKSTA1_TKIF2_Pos)

#define TK_TKSTA1_TKIF3_Pos               (3)                            
#define TK_TKSTA1_TKIF3_Msk               (0x1ul << TK_TKSTA1_TKIF3_Pos)

#define TK_TKSTA1_TKIF4_Pos               (4)                            
#define TK_TKSTA1_TKIF4_Msk               (0x1ul << TK_TKSTA1_TKIF4_Pos)

#define TK_TKSTA1_TKIF5_Pos               (5)                            
#define TK_TKSTA1_TKIF5_Msk               (0x1ul << TK_TKSTA1_TKIF5_Pos)

#define TK_TKSTA1_TKIF6_Pos               (6)                            
#define TK_TKSTA1_TKIF6_Msk               (0x1ul << TK_TKSTA1_TKIF6_Pos)

#define TK_TKSTA1_TKIF7_Pos               (7)                            
#define TK_TKSTA1_TKIF7_Msk               (0x1ul << TK_TKSTA1_TKIF7_Pos)


#define TK_TKSTA2_TKIF8_Pos               (0)                            
#define TK_TKSTA2_TKIF8_Msk               (0x1ul << TK_TKSTA2_TKIF8_Pos)

#define TK_TKSTA2_TKIF9_Pos               (1)                            
#define TK_TKSTA2_TKIF9_Msk               (0x1ul << TK_TKSTA2_TKIF9_Pos)

#define TK_TKSTA2_TKIF10_Pos               (2)                            
#define TK_TKSTA2_TKIF10_Msk               (0x1ul << TK_TKSTA2_TKIF10_Pos)

#define TK_TKSTA2_TKIF11_Pos               (3)                            
#define TK_TKSTA2_TKIF11_Msk               (0x1ul << TK_TKSTA2_TKIF11_Pos)

#define TK_TKSTA2_TKIF12_Pos               (4)                            
#define TK_TKSTA2_TKIF12_Msk               (0x1ul << TK_TKSTA2_TKIF11_Pos)

#define TK_TKSTA2_TKIF13_Pos               (5)                            
#define TK_TKSTA2_TKIF13_Msk               (0x1ul << TK_TKSTA2_TKIF13_Pos)

#define TK_TKSTA2_TKIF14_Pos               (6)                            
#define TK_TKSTA2_TKIF14_Msk               (0x1ul << TK_TKSTA2_TKIF14_Pos)

/* TKIDLPOL0 ~ TKIDLPOL14 */
#define TK_TKIDLPOL_IDLSx_Pos              (0)                            
#define TK_TKIDLPOL_IDLSx_Msk              (0x3ul << TK_TKIDLPOL_IDLSx_Pos)

#define TK_TKIDLPOL_POLx_Pos               (2)                            
#define TK_TKIDLPOL_POLx_Msk               (0x3ul << TK_TKIDLPOL_POLx_Pos)

#define TK_TKIDLPOL_POLENx_Pos             (4)                            
#define TK_TKIDLPOL_POLENx_Msk             (0x1ul << TK_TKIDLPOL_POLENx_Pos)

/* 8 bit Sensing Data TKDATA0 ~ TKDATA14, TKDATALL */

/* 8 bit Threshold  TKHTH0 ~ TKHTH14, TKHTHALL */



/* Due to original parameter is 32 bits. But 8051's register is only 4 8-bits registers */
#define TK_SCAN_MODE_SINGLE                 (0UL)  /*!< Touch key single scan mode */
#define TK_SCAN_MODE_PERIODIC               (TK_TKCON0_TMRTRG_EN_Msk)  /*!< Touch key periodic scan mode */
#define TK_SCAN_MODE_ALL_KEY                (TK_TKCON0_SCAN_ALL_Msk)  /*!< Touch key all keys scan mode */
#define TK_SCAN_MODE_PERIODIC_ALL_KEY       (TK_TKCON0_TMRTRG_EN_Msk | TK_TKCON0_SCAN_ALL_Msk)  /*!< Touch key periodic with all keys scan mode */

#define TK_SENSE_PULSE_P5                   (0UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 500ns */
#define TK_SENSE_PULSE_1                    (1UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 1us */
#define TK_SENSE_PULSE_2                    (2UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 2us */
#define TK_SENSE_PULSE_4                    (3UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 4us */
#define TK_SENSE_PULSE_8                    (4UL << TK_TKCON1_PULSET_Pos)  /*!< Touch key sensing pulse width is 8us */

#define TK_SENSE_CNT_16                     (0UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 128 */
#define TK_SENSE_CNT_32                     (1UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 255 */
#define TK_SENSE_CNT_64                     (2UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 511 */
#define TK_SENSE_CNT_128                    (3UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 128 */
#define TK_SENSE_CNT_255                    (4UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 255 */
#define TK_SENSE_CNT_511                    (5UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 511 */
#define TK_SENSE_CNT_1023                   (6UL << TK_TKCON1_SENSET_Pos)  /*!< Touch key sensing count is 1023 */

#define TK_CAP_BANK_POL_SEL_GND             (0UL << TK_TKCON2_POL_CAP_Pos)  /*!< Touch key capacitor bank polarity is GND */
#define TK_CAP_BANK_POL_SEL_AVCCH           (1UL << TK_TKCON2_POL_CAP_Pos)  /*!< Touch key capacitor bank polarity is AVCCH */
#define TK_CAP_BANK_POL_SEL_VDD             (3UL << TK_TKCON2_POL_CAP_Pos)  /*!< Touch key capacitor bank polarity is VDD */

#define TK_INT_EN_SCAN_COMPLETE             (TK_TKINTEN_SCIE_Msk)            /*!< Touch key enable scan complete interrupt */
#define TK_INT_EN_SCAN_COMPLETE_EDGE_TH     (TK_TKINTEN_SCTHIE_Msk)          /*!< Touch key enable scan complete with threshold interrupt of edge trigger mode */
//#define TK_INT_EN_SCAN_COMPLETE_LEVEL_TH    (TK_INTEN_THIMOD_Msk | TK_INTEN_SCTHIEN_Msk)  /*!< Touch key enable scan complete with threshold interrupt of level trigger mode */

#define TK_INT_SCAN_COMPLETE                (TK_TKSTA0_SCIF_Msk)            /*!< Touch key scan complete interrupt */
#define TK_INT_SCAN_COMPLETE_TH_ALL         (0x1FFFF02UL)                   /*!< Touch key scan complete or all touch keys threshold control interrupt */
#define TK_INT_SCAN_TH_ALL                  (0x1FFFF00UL)                   /*!< ALL Touch key threshold control interrupt */
#define TK_INT_SCAN_TH_TK0                  (TK_TKSTA1_TKIF0_Msk)           /*!< Touch key 0 threshold control interrupt */
#define TK_INT_SCAN_TH_TK1                  (TK_TKSTA1_TKIF1_Msk)           /*!< Touch key 1 threshold control interrupt */
#define TK_INT_SCAN_TH_TK2                  (TK_TKSTA1_TKIF2_Msk)           /*!< Touch key 2 threshold control interrupt */
#define TK_INT_SCAN_TH_TK3                  (TK_TKSTA1_TKIF3_Msk)           /*!< Touch key 3 threshold control interrupt */
#define TK_INT_SCAN_TH_TK4                  (TK_TKSTA1_TKIF4_Msk)           /*!< Touch key 4 threshold control interrupt */
#define TK_INT_SCAN_TH_TK5                  (TK_TKSTA1_TKIF5_Msk)           /*!< Touch key 5 threshold control interrupt */
#define TK_INT_SCAN_TH_TK6                  (TK_TKSTA1_TKIF6_Msk)           /*!< Touch key 6 threshold control interrupt */
#define TK_INT_SCAN_TH_TK7                  (TK_TKSTA1_TKIF7_Msk)           /*!< Touch key 7 threshold control interrupt */
#define TK_INT_SCAN_TH_TK8                  (TK_TKSTA2_TKIF8_Msk)           /*!< Touch key 8 threshold control interrupt */
#define TK_INT_SCAN_TH_TK9                  (TK_TKSTA2_TKIF9_Msk)           /*!< Touch key 9 threshold control interrupt */
#define TK_INT_SCAN_TH_TK10                 (TK_TKSTA2_TKIF10_Msk)          /*!< Touch key 10 threshold control interrupt */
#define TK_INT_SCAN_TH_TK11                 (TK_TKSTA2_TKIF11_Msk)          /*!< Touch key 11 threshold control interrupt */
#define TK_INT_SCAN_TH_TK12                 (TK_TKSTA2_TKIF12_Msk)          /*!< Touch key 12 threshold control interrupt */
#define TK_INT_SCAN_TH_TK13                 (TK_TKSTA2_TKIF13_Msk)          /*!< Touch key 13 threshold control interrupt */
#define TK_INT_SCAN_TH_TK14                 (TK_TKSTA2_TKIF14_Msk)          /*!< Touch key 14 threshold control interrupt */
