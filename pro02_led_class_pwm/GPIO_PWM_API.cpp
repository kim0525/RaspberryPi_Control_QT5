#include <iostream>
using namespace std;

#include "GPIO_PWM_API.h"
#include <wiringPi.h>
#include <softPwm.h>

// ====================  GPIO_LED ========================
// 생성자
GPIO_LED::GPIO_LED(int pin) : GPIO_LED(pin, LOW){}

GPIO_LED::GPIO_LED(int pin, bool value) {
    mPinNum = pin;
    mState = value;

    wiringPiSetupGpio();

    pinMode(mPinNum, OUTPUT);
    digitalWrite(mPinNum, mState);
}

// 소멸자
GPIO_LED::~GPIO_LED()
{
    digitalWrite(mPinNum, LOW);
}

// 멤버 함수
void GPIO_LED::ledWrite(bool value)
{
    mState = value;
    digitalWrite(mPinNum, mState);
}

bool GPIO_LED::ledRead(void)
{
    return digitalRead(mPinNum);
}




// ====================  PWM_LED ========================
// 생성자
PWM_LED::PWM_LED(int pin) : PWM_LED(pin, 0, 100){}

PWM_LED::PWM_LED(int pin, int duty) : PWM_LED(pin, duty, 100) {	}

PWM_LED::PWM_LED(int pin, int duty, int period) {
    mPinNum = pin;
    mDuty = duty;
    mPeriod = period;

    wiringPiSetupGpio();

    softPwmCreate(mPinNum, mDuty, mPeriod);
}

// 소멸자
PWM_LED::~PWM_LED()
{
    softPwmStop(mPinNum);
}

// 멤버 함수
void PWM_LED::setLedBright(int duty)
{
    mDuty = duty;
    softPwmWrite (mPinNum, mDuty);
}

void PWM_LED::setLedPeriod(int period)
{
    mPeriod = period;
    softPwmStop(mPinNum);
    softPwmCreate(mPinNum, mDuty, mPeriod);
}

