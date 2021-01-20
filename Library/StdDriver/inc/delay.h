
#define TIMER0        0
#define TIMER1        1
#define TIMER2        2
#define TIMER3        3


#define UNIT_1US      0
#define UNIT_10US     1
#define UNIT_100US   2
#define UNIT_1MS     3
#define UNIT_10MS     4
#define UNIT_100MS    5
#define UNIT_1S       6


/*****************************************************************************************
* For TIMER VALUE setting is base on " option -> C51 -> Preprocesser Symbols -> Define "
*****************************************************************************************/
// define timer base value Fsys = 11.0592MHz 
  #define TIMER_DIV12_VALUE_10us_FOSC_110592      65536-9      //9*12/11.0592 = 10 uS,      // Timer divider = 12   for TM0/TM1
  #define TIMER_DIV12_VALUE_1ms_FOSC_110592        65536-923    //923*12/11.0592 = 1 mS      // Timer divider = 12
  #define TIMER_DIV12_VALUE_10ms_FOSC_110592      65536-9216    //18432*12/22118400 = 10 ms    // Timer divider = 12
  #define TIMER_DIV4_VALUE_10us_FOSC_110592        65536-28    //28*4/11.0592 = 10 uS      // Timer divider = 4  for TM2/TM3
  #define TIMER_DIV4_VALUE_1ms_FOSC_110592        65536-2765    //2765*4/11.0592 = 1 mS      // Timer divider = 4
  #define TIMER_DIV4_VALUE_100us_FOSC_110592      65536-277    //553*4/22118400 = 100 us    // Timer divider = 4
  #define TIMER_DIV4_VALUE_200us_FOSC_110592      65536-553    //1106*4/22118400 = 200 us    // Timer divider = 4
  #define TIMER_DIV4_VALUE_500us_FOSC_110592      65536-1383    //2765*4/22118400 = 500 us    // Timer divider = 4    
  #define TIMER_DIV16_VALUE_10ms_FOSC_110592      65536-6912    //1500*16/22118400 = 10 ms    // Timer divider = 16
  #define TIMER_DIV64_VALUE_30ms_FOSC_110592      65536-5184    //10368*64/22118400 = 30 ms    // Timer divider = 64
  #define TIMER_DIV128_VALUE_100ms_FOSC_110592    65536-8640    //17280*128/22118400 = 100 ms    // Timer divider = 128
  #define TIMER_DIV128_VALUE_200ms_FOSC_110592    65536-17280    //34560*128/22118400 = 200 ms    // Timer divider = 128
  #define TIMER_DIV256_VALUE_500ms_FOSC_110592    65536-21600    //43200*256/22118400 = 500 ms     // Timer divider = 256
  #define TIMER_DIV512_VALUE_1s_FOSC_110592        65536-21600    //43200*512/22118400 = 1 s    // Timer divider = 512
// define timer base value Fsys = 16MHz 
  #define TIMER_DIV12_VALUE_10us_FOSC_160000      65536-8    //13*12/16000000 = 10 uS,        // Timer divider = 12 for TM0/TM1
  #define TIMER_DIV12_VALUE_100us_FOSC_160000      65536-130    //130*12/16000000 = 10 uS,      // Timer divider = 12 
  #define TIMER_DIV12_VALUE_1ms_FOSC_160000        65536-1334    //1334*12/16000000 = 1 mS,       // Timer divider = 12 
  #define TIMER_DIV12_VALUE_10ms_FOSC_160000      65536-13334    //13334*12/16000000 = 10 mS     // Timer divider = 12 
  #define TIMER_DIV12_VALUE_40ms_FOSC_160000      65536-53336    //53336*12/16000000 = 40 ms      // Timer divider = 12 
  #define TIMER_DIV4_VALUE_10us_FOSC_160000        65536-30    //40*4/16000000 = 10 uS,        // Timer divider = 4  for TM2/TM3
  #define TIMER_DIV4_VALUE_100us_FOSC_160000      65536-400    //400*4/16000000 = 100 us        // Timer divider = 4
  #define TIMER_DIV4_VALUE_200us_FOSC_160000      65536-800    //800*4/16000000 = 200 us        // Timer divider = 4
  #define TIMER_DIV4_VALUE_416us_FOSC_160000      65536-1650
  #define TIMER_DIV4_VALUE_500us_FOSC_160000      65536-2000    //2000*4/16000000 = 500 us      // Timer divider = 4
  #define TIMER_DIV4_VALUE_1ms_FOSC_160000        65536-4000    //4000*4/16000000 = 1 mS,       // Timer divider = 4
  #define TIMER_DIV4_VALUE_10ms_FOSC_160000        65536-40000    //40000*4/16000000 = 10 mS,       // Timer divider = 4
  #define TIMER_DIV16_VALUE_10ms_FOSC_160000      65536-10000    //10000*16/16000000 = 10 ms      // Timer  divider = 16
  #define TIMER_DIV64_VALUE_30ms_FOSC_160000      65536-7500    //7500*64/16000000 = 30 ms      // Timer divider = 64
  #define TIMER_DIV128_VALUE_1ms_FOSC_160000      65536-125      //125*128/16000000 = 1 ms    // Timer divider = 128
  #define TIMER_DIV128_VALUE_10ms_FOSC_160000      65536-1250    //1250*128/16000000 = 10 ms    // Timer divider = 128
  #define TIMER_DIV128_VALUE_100ms_FOSC_160000    65536-12500    //12500*128/16000000 = 100 ms    // Timer divider = 128
  #define TIMER_DIV128_VALUE_200ms_FOSC_160000    65536-25000    //25000*128/16000000 = 200 ms    // Timer divider = 128
  #define TIMER_DIV256_VALUE_500ms_FOSC_160000    65536-31250    //31250*256/16000000 = 500 ms   // Timer divider = 256
  #define TIMER_DIV512_VALUE_100ms_FOSC_160000    65536-3125    //3125*512/16000000 = 100ms.      // Timer Divider = 512
  #define TIMER_DIV512_VALUE_1s_FOSC_160000        65536-31250    //31250*512/16000000 = 1 s.      // Timer Divider = 512
// define timer base value Fsys = 16.6MHz 
  #define TIMER_DIV12_VALUE_10us_FOSC_166000      65536-14    //14*12/16600000 = 10 uS,        // Timer divider = 12 for TM0/TM1
  #define TIMER_DIV12_VALUE_100us_FOSC_166000      65536-138    //138*12/16600000 = 100 uS,      // Timer divider = 12 
  #define TIMER_DIV12_VALUE_1ms_FOSC_166000        65536-1384  //1384*12/16600000 = 1 mS,       // Timer divider = 12 
  #define TIMER_DIV12_VALUE_10ms_FOSC_166000      65536-13834  //13834*12/16600000 = 10 mS     // Timer divider = 12 
  #define TIMER_DIV12_VALUE_40ms_FOSC_166000      65536-55333  //55333*12/16600000 = 40 ms      // Timer divider = 12 
  #define TIMER_DIV4_VALUE_10us_FOSC_166000        65536-41    //41*4/16600000 = 10 uS,        // Timer divider = 4  for TM2/TM3
  #define TIMER_DIV4_VALUE_100us_FOSC_166000      65536-415    //415*4/16600000 = 100 us        // Timer divider = 4
  #define TIMER_DIV4_VALUE_200us_FOSC_166000      65536-830    //830*4/16600000 = 200 us        // Timer divider = 4
  #define TIMER_DIV4_VALUE_500us_FOSC_166000      65536-2075  //2075*4/16600000 = 500 us      // Timer divider = 4
  #define TIMER_DIV4_VALUE_1ms_FOSC_166000        65536-4150  //4150*4/16600000 = 1 mS,       // Timer divider = 4
  #define TIMER_DIV16_VALUE_10ms_FOSC_166000      65536-10375  //10375*16/16600000 = 10 ms      // Timer  divider = 16
  #define TIMER_DIV64_VALUE_30ms_FOSC_166000      65536-7781  //7781*64/16600000 = 30 ms      // Timer divider = 64
  #define TIMER_DIV128_VALUE_100ms_FOSC_166000    65536-12969  //12969*128/16600000 = 100 ms    // Timer divider = 128
  #define TIMER_DIV128_VALUE_200ms_FOSC_166000    65536-25937  //25937*128/16600000 = 200 ms    // Timer divider = 128
  #define TIMER_DIV256_VALUE_500ms_FOSC_166000    65536-32422  //32422*256/16600000 = 500 ms   // Timer divider = 256
  #define TIMER_DIV512_VALUE_1s_FOSC_166000        65536-32421  //32421*512/16600000 = 1 s.      // Timer Divider = 512
// define timer base value Fsys = 18.432MHz 
  #define TIMER_DIV12_VALUE_10us_FOSC_184320      65536-15        //15*12/18.432 = 10 uS,  Timer Clock = Fsys/12
  #define TIMER_DIV12_VALUE_1ms_FOSC_184320        65536-1536      //1536*12/18.432 = 1 mS, Timer Clock = Fsys/12
  #define TIMER_DIV4_VALUE_10us_FOSC_184320        65536-46        //46*4/18.432 = 10 uS,   Timer Clock = Fsys/4
  #define TIMER_DIV4_VALUE_1ms_FOSC_184320        65536-4608      //4608*4/18.432 = 1 mS,  Timer Clock = Fsys/4
// define timer base value Fsys = 20 MHz
  #define TIMER_DIV12_VALUE_10us_FOSC_200000      65536-17    //17*12/20000000 = 10 uS,  Timer Clock = Fsys/12
  #define TIMER_DIV12_VALUE_1ms_FOSC_200000        65536-1667      //1667*12/20000000 = 1 mS, Timer Clock = Fsys/12
  #define TIMER_DIV4_VALUE_10us_FOSC_200000        65536-50        //50*4/20000000 = 10 uS,    Timer Clock = Fsys/4
  #define TIMER_DIV4_VALUE_1ms_FOSC_200000        65536-5000      //5000*4/20000000 = 1 mS,   Timer Clock = Fsys/4
// define timer base value Fsys = 22.1184 MHz 
  #define TIMER_DIV12_VALUE_10us_FOSC_221184      65536-18         //18*12/22118400 = 10 uS,        // Timer divider = 12
  #define TIMER_DIV12_VALUE_100us_FOSC_221184      65536-184       //184*12/22118400 = 10 uS,        // Timer divider = 12
  #define TIMER_DIV12_VALUE_1ms_FOSC_221184        65536-1843      //1843*12/22118400 = 1 mS,       // Timer divider = 12
  #define TIMER_DIV12_VALUE_10ms_FOSC_221184      65536-18432      //18432*12/22118400 = 10 ms      // Timer divider = 12
  #define TIMER_DIV4_VALUE_10us_FOSC_221184        65536-56      //9*4/22118400 = 10 uS,          // Timer divider = 4
  #define TIMER_DIV4_VALUE_1ms_FOSC_221184        65536-5530      //923*4/22118400 = 1 mS,         // Timer divider = 4
  #define TIMER_DIV4_VALUE_100us_FOSC_221184      65536-553      //553*4/22118400 = 100 us      // Timer divider = 4
  #define TIMER_DIV4_VALUE_200us_FOSC_221184      65536-1106      //1106*4/22118400 = 200 us      // Timer divider = 4
  #define TIMER_DIV4_VALUE_500us_FOSC_221184      65536-2765      //2765*4/22118400 = 500 us      // Timer divider = 4    
  #define TIMER_DIV16_VALUE_10ms_FOSC_221184      65536-13824      //1500*16/22118400 = 10 ms      // Timer divider = 16
  #define TIMER_DIV64_VALUE_30ms_FOSC_221184      65536-10368      //10368*64/22118400 = 30 ms      // Timer divider = 64
  #define TIMER_DIV128_VALUE_100ms_FOSC_221184    65536-17280      //17280*128/22118400 = 100 ms      // Timer divider = 128
  #define TIMER_DIV128_VALUE_200ms_FOSC_221184    65536-34560      //34560*128/22118400 = 200 ms      // Timer divider = 128
  #define TIMER_DIV256_VALUE_500ms_FOSC_221184    65536-43200      //43200*256/22118400 = 500 ms       // Timer divider = 256
  #define TIMER_DIV512_VALUE_1s_FOSC_221184        65536-43200      //43200*512/22118400 = 1 s      // Timer divider = 512
// define timer base value Fsys = 24 MHz
  #define TIMER_DIV12_VALUE_10us_FOSC_240000      65536-20      //20*12/24000000 = 10 uS,        // Timer divider = 12
  #define TIMER_DIV12_VALUE_100us_FOSC_240000      65536-200    //130*12/16000000 = 10 uS,      // Timer divider = 12 
  #define TIMER_DIV12_VALUE_1ms_FOSC_240000        65536-2000      //2000*12/24000000 = 1 mS,       // Timer divider = 12
  #define TIMER_DIV12_VALUE_10ms_FOSC_240000      65536-20000      //2000*12/24000000 = 10 mS       // Timer divider = 12
  #define TIMER_DIV4_VALUE_10us_FOSC_240000        65536-60      //60*4/24000000 = 10 uS,          // Timer divider = 4
  #define TIMER_DIV4_VALUE_100us_FOSC_240000      65536-600      //600*4/24000000 = 100 us      // Timer divider = 4
  #define TIMER_DIV4_VALUE_200us_FOSC_240000      65536-1200      //1200*4/24000000 = 200 us      // Timer divider = 4
  #define TIMER_DIV4_VALUE_500us_FOSC_240000      65536-3000      //3000*4/24000000 = 500 us      // Timer divider = 4
  #define TIMER_DIV4_VALUE_1ms_FOSC_240000        65536-6000      //6000*4/24000000 = 1 mS,         // Timer divider = 4
  #define TIMER_DIV16_VALUE_10ms_FOSC_240000      65536-15000      //15000*16/24000000 = 10 ms      // Timer divider = 16
  #define TIMER_DIV64_VALUE_30ms_FOSC_240000      65536-11250      //11250*64/24000000 = 30 ms      // Timer divider = 64
  #define TIMER_DIV128_VALUE_100ms_FOSC_240000    65536-18750      //37500*128/24000000 = 200 ms      // Timer divider = 128
  #define TIMER_DIV128_VALUE_200ms_FOSC_240000    65536-37500      //37500*128/24000000 = 200 ms      // Timer divider = 128
  #define TIMER_DIV256_VALUE_500ms_FOSC_240000    65536-46875      //46875*256/24000000 = 500 ms       // Timer divider = 256
  #define TIMER_DIV512_VALUE_100ms_FOSC_240000    65536-4687      //4687*512/24000000 = 100 ms       // Timer divider = 512
  #define TIMER_DIV512_VALUE_500ms_FOSC_240000    65536-23437      //4687*512/24000000 = 100 ms       // Timer divider = 512
  #define TIMER_DIV512_VALUE_1s_FOSC_240000        65536-46875      //46875*512/24000000 = 1 s.        // Timer Divider = 512



void Timer0_Delay(unsigned long u32SYSCLK, unsigned int u16CNT, unsigned int u6DLYUnit);
void Timer1_Delay(unsigned long u32SYSCLK, unsigned int u16CNT, unsigned int u6DLYUnit);
void Timer2_Delay(unsigned long u32SYSCLK,unsigned int u16TMDIV, unsigned int u16CNT, unsigned long u32DLYUnit);
void Timer3_Delay(unsigned long u32SYSCLK,unsigned char u8TMDIV, unsigned int u16CNT, unsigned long u32DLYUnit);
void Timer_Interrupt_Enable(unsigned char u8TM);
