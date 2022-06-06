#ifndef GPIO_PWM_API_H
#define GPIO_PWM_API_H

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

#endif // GPIO_PWM_API_H
