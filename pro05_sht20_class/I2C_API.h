#ifndef I2C_API_H
#define I2C_API_H

// I2C 주소
#define SHT20_I2C_ADDR      0x40

// SHT20 관련 설정
#define SHT20_I2C_CMD_MEASURE_TEMP  0xF3
#define SHT20_I2C_CMD_MEASURE_HUMI  0xF5
#define SHT20_I2C_CMD_SOFT_RESET    0xFE

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

#endif // I2C_API_H
