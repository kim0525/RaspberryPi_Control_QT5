#ifndef GPIO_PWM_API_H
#define GPIO_PWM_API_H

#include "piezo.h"

// GPIO_LED
class GPIO_LED {
    private:
        int mPinNum;
        int mState;
    public:
        GPIO_LED(int pin);
        GPIO_LED(int pin, bool value);
        ~GPIO_LED();
        void ledWrite(bool value);
        bool ledRead(void);
};

// PWM_LED
class PWM_LED {
    private:
        int mPinNum;
        int mDuty;
        int mPeriod;
    public:
        PWM_LED(int pin);
        PWM_LED(int pin, int duty);
        PWM_LED(int pin, int duty, int period);
        ~PWM_LED();
        void setLedBright(int duty);
        void setLedPeriod(int period);
};

// TONE_PIEZO
class TONE_PIEZO {
    private:
        int mPinNum;
        int mScale;
        int mTime;
    public:
        TONE_PIEZO(int pin);
        ~TONE_PIEZO();
        void setScaleOn(int scale);
        void setScaleOnTime(int scale, int time);
        void setScaleOFF(void);
        void setMelody(int scale[], int time[], int cnt);
};

#endif // GPIO_PWM_API_H
