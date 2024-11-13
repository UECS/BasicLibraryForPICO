
#ifndef _MCP3425_H_
#define _MCP3425_H_

#include "Arduino.h"
#include "Wire.h"

#define MCP3425_address 0x68
#define MCP3425_VREF    2.048
#define MCP3425_configRegister16bit 0b10011000 //16bit(15times/s) 15sps PGA x1 
#define MCP3425_configRegister14bit 0b10010100 //14bit(60times/s) PGA x1 
#define MCP3425_configRegister12bit 0b10010000 //12bit(240times/s) PGA x1 

class MCP3425 {
  public:
  MCP3425(TwoWire &w);
	void begin(void);
	void begin(int bitmode);
	double readVolt(void);
	int16_t readADC(void);
  private:
	TwoWire *wire;
    int mode;
};

#endif
