#include "MyMCP3425.h"


MCP3425::MCP3425(TwoWire &w) {
  wire = &w;
}

void MCP3425::begin(void) 
{
wire->beginTransmission(MCP3425_address);
wire->write(MCP3425_configRegister);
wire->endTransmission();
}

double MCP3425::readVolt(void) {
return (double)(readADC()) * MCP3425_VREF / 32767.0 ;
}

int16_t MCP3425::readADC(void) {
    wire->requestFrom(MCP3425_address, 2);
    int16_t result=(wire->read() << 8 ) + wire->read();
    return result;
}
  
