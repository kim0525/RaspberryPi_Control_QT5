#include <iostream>
using namespace std;

//#include <QDebug>
#include "GPIO_PWM_API.h"
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>
#include "piezo.h"

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


// ====================  TONE_PIEZO ========================
// 생성자
TONE_PIEZO::TONE_PIEZO(int pin) {
    mPinNum = pin;

    wiringPiSetupGpio();

    softToneCreate(pin);
}

// 소멸자
TONE_PIEZO::~TONE_PIEZO()
{
    softToneStop(mPinNum);
}

// 멤버 함수
void TONE_PIEZO::setScaleOn(int scale)
{
    mScale = scale;
    softToneWrite(mPinNum, mScale);
}

void TONE_PIEZO::setScaleOnTime(int scale, int time)
{
    mScale = scale;
    softToneWrite(mPinNum, mScale);
    delay(time);
    setScaleOFF();
}

void TONE_PIEZO::setScaleOFF(void)
{
    softToneWrite(mPinNum, S_mute);
}

void TONE_PIEZO::setMelody(int *scale, int *time, int cnt)
{
    for(int i=0;i<cnt; i++)
    {
        setScaleOnTime( scale[i], time[i]);
    }

}

void TONE_PIEZO::setMelodyStruct(struct scaleTime song)
{
    for(int i=0;i<song.cnt; i++)
    {
        setScaleOnTime( song.scale[i], song.time[i]);
    }
}


// ====================  GPIO_SW ========================
// 생성자
GPIO_SW::GPIO_SW(int pin) {
    mPinNum = pin;
    mMode = 0;

    wiringPiSetupGpio();

    pinMode(mPinNum, INPUT);
}

GPIO_SW::GPIO_SW(int pin, int edge, void (*function)(void) ) {
    mPinNum = pin;
    mEdge = edge;
    mMode = 1;

    wiringPiSetupGpio();
    pinMode(mPinNum, INPUT);

    wiringPiISR(mPinNum, mEdge, function);
}

// 소멸자
GPIO_SW::~GPIO_SW()
{

}

// 멤버 함수
bool GPIO_SW::swRead(void)
{
    return digitalRead(mPinNum);
}

bool GPIO_SW::swModeRead(void)
{
    return mMode;
}
