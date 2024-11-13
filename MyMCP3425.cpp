#include "MyMCP3425.h"


MCP3425::MCP3425(TwoWire &w) {
  wire = &w;
}

void MCP3425::begin(void) 
{
mode=16;
	wire->beginTransmission(MCP3425_address);
wire->write(MCP3425_configRegister16bit);
wire->endTransmission();
}


void MCP3425::begin(int bitmode) 
{
mode=bitmode;

	wire->beginTransmission(MCP3425_address);

	if(mode==16)
	{	
	wire->write(MCP3425_configRegister16bit);
	}
	else if(mode==14)
	{	
	wire->write(MCP3425_configRegister14bit);
	}
	else
	{
	mode=12;
	wire->write(MCP3425_configRegister12bit);
	}

	
	wire->endTransmission();
}


double MCP3425::readVolt(void) {
	
if(mode==16)
	{
	return (double)(readADC()) * MCP3425_VREF / 32767.0 ;
	}
	else if(mode==14)
	{
	return (double)(readADC()) * MCP3425_VREF / 8191.0 ;
	}
	
	return (double)(readADC()) * MCP3425_VREF / 2047.0 ;	
}

int16_t MCP3425::readADC(void) {
    wire->requestFrom(MCP3425_address, 2);
    int16_t result=(wire->read() << 8 ) + wire->read();
    return result;
}
  
