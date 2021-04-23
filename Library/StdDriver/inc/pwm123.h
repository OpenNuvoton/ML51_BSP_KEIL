#define PWM1   1
#define PWM2   2
#define PWM3   3

void PWM123_ClockSource(unsigned char u8PWMNum, unsigned char u8PWMCLKDIV);
void PWM123_ConfigOutputChannel(unsigned char u8PWMNum,
                                unsigned char u8PWMChannelNum,
                                unsigned int u16PWMFrequency,
                                unsigned int u16PWMDutyCycle);
void PWM123_RUN(unsigned char u8PWM123Sel);
