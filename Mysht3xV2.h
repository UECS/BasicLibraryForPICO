//2024/6/7 Ver.2.0
//マルチプラットフォーム化しました

#ifndef _SHT3x_H_
#define _SHT3x_H_

#include "Arduino.h"
#include "Wire.h"

#define SHT3x_ADDR    0x45

class SHT3x {
  public:
    SHT3x();
    SHT3x(TwoWire &w);
    bool autoRead1Sec(); 
    bool begin(unsigned char i2caddr = SHT3x_ADDR);
    bool startMeasure(void);
    bool getTempHumid(void);
    double humidity, temp,humiddiff;
    int retryCount;
  private:
	TwoWire *wire;
    int writeCommand(unsigned short cmd);
    bool reset(void);
    unsigned char crc8Dallas(const unsigned char *data, int len);
    unsigned char _i2caddr;
    
};

#endif
