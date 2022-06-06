#ifndef I2C_API_H
#define I2C_API_H

// I2C 주소
#define SHT20_I2C_ADDR      0x40
#define FND_I2C_ADDR        0x5E
#define PCA9685_I2C_ADDR      0x5E

// SHT20 관련 설정
#define SHT20_I2C_CMD_MEASURE_TEMP  0xF3
#define SHT20_I2C_CMD_MEASURE_HUMI  0xF5
#define SHT20_I2C_CMD_SOFT_RESET    0xFE

//PCA9685
#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50       //t = 1/f  100이면 0.01sc

#include <wiringPi.h>
#include <wiringPiI2C.h>




// I2C_SHT20
class I2C_SHT20 {
    private:
        int mFd;
        int mDevId;
        float mTemp;
        float mHumi;
    public:
        I2C_SHT20(int addr);
        ~I2C_SHT20();
        float measureTemp(void);
        float measureHumi(void);
        float getTemp(void);
        float getHumi(void);
};

class I2C_PCA9685 {
    private:
        static int mNum;
        static int mFd;
        static int mDevId;

        int mVal;
        int mPinNum;     // 0~15
   
    public:
        I2C_PCA9685(int addr, int pinNum);
        ~I2C_PCA9685();
        int getPwm(void);

        void setPwm(int val);
        void setPwm(bool val);


};


#endif // GPIO_PWM_API_H
