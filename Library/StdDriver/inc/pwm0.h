#define PWM_FSYS         0
#define PWM_TIMER1       1

#define Independent      0
#define Complementary    1
#define Synchronous      2

#define EdgeAligned      0
#define CenterAligned    1

#define PWM0_CH01        0
#define PWM0_CH23        1
#define PWM0_CH45        2
#define PWM0_ALL         3

void PWM0_ClockSource(unsigned char u8PWMCLKSource, unsigned char u8PWM0CLKDIV);
void PWM0_ConfigOutputChannel(unsigned char u8PWM0ChannelNum,
                              unsigned char u8PWM0OPMode,
                              unsigned char u8PWM0PwmType,
                              unsigned long u32PWM0Frequency,
                              unsigned int u16PWM0DutyCycle);
void PWM0_DeadZoneEnable(unsigned char u8PWM0Pair, unsigned int u16PWM0DZValue);
void PWM0_DeadZone_ALL_Disable(void);
void PWM0_RUN(void);
void PWM0_STOP(void);
