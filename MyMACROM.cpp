/*
  93C46.h - Library for the 93C46 EEPROM chip in 64x16 mode
  Created by Joey Haas, Juli 7, 2018
  Released under the GNU General Public License v3.0
*/
#include "Arduino.h"
#include "MyMACROM.h"

enum OP { // Operations
};
enum CC { // Control Codes
};

MACROM93C46::MACROM93C46(int pDI, int pDO,int pSK,int pCS) {
	pinMode(pSK, OUTPUT);
	pinMode(pDI, OUTPUT); 
	pinMode(pDO, INPUT);
	pinMode(pCS, OUTPUT);
	pinSK = pSK;
	pinDI = pDI;
	pinDO = pDO;
	pinCS = pCS;
	_WRITE_ENABLED = false;
	_BITMODE = true;

};

void MACROM93C46::begin(bool longMode) 
{
	_BITMODE = longMode;
}

word MACROM93C46::read(byte addr) 
{
	word val = 0;
	digitalWrite(pinCS, HIGH);
	bitsSend(HIGH, 1);
	
	int amtBits;
	if(_BITMODE == EEPROM_93C46_16BITMODE) 
	{
		bitsSend(EEPROM_93C46_READ | (addr & 0x3F), 8);
		amtBits = 16;
	}
	else 
	{
		bitsSend(EEPROM_93C46_READ<<1 | (addr & 0x7F), 9);
		amtBits = 8;
	}
	// Read bits
	for(int i = amtBits; i>0; i--) 
	{
		delayMicroseconds(1);
		digitalWrite(pinSK, HIGH);
		delayMicroseconds(1);
		byte in = digitalRead(pinDO) ? 1 : 0;
		digitalWrite(pinSK, LOW);
		val |= (in << (i-1));
	}
	digitalWrite(pinCS, LOW);
	return val;
}

void MACROM93C46::writeEnable() 
{
	digitalWrite(pinCS, HIGH);
	bitsSend(HIGH, 1);
	if(_BITMODE == EEPROM_93C46_16BITMODE) 
	{
		bitsSend(EEPROM_93C46_EW_ENABLE, 8);
	}
	else
	{
		bitsSend(EEPROM_93C46_EW_ENABLE<<1, 9);
	}
	digitalWrite(pinCS, LOW);
	_WRITE_ENABLED = true;
};

void MACROM93C46::writeDisable() 
{
	digitalWrite(pinCS, HIGH);
	bitsSend(HIGH, 1);
	if(_BITMODE == EEPROM_93C46_16BITMODE) {
		bitsSend(EEPROM_93C46_EW_DISABLE, 8);
	} else {
		bitsSend(EEPROM_93C46_EW_DISABLE<<1, 9);
	}
	digitalWrite(pinCS, LOW);
	_WRITE_ENABLED = false;
}


bool MACROM93C46::write(byte addr, word value) 
{
	if(!_WRITE_ENABLED) {
		return false;
	}
	digitalWrite(pinCS, HIGH);
	bitsSend(HIGH, 1);
	if(_BITMODE == EEPROM_93C46_16BITMODE) {
		bitsSend(EEPROM_93C46_WRITE | (addr & 0x3F), 8);
		bitsSend(0xFFFF & value, 16);
	} else {
		bitsSend(EEPROM_93C46_WRITE<<1 | (addr & 0x7F), 9);
		bitsSend(0xFF & value, 8);
	}
	digitalWrite(pinCS, LOW);
	return wait();
}


void MACROM93C46::bitsSend(word val, int len) 
{
	for(int i = len-1; i>=0; i--)
	{
		bool out = (val & 1<<i);
		// Send bit
		digitalWrite(pinDI, out);
		delayMicroseconds(1);
		digitalWrite(pinSK, HIGH);
		delayMicroseconds(1);
		digitalWrite(pinSK, LOW);
		digitalWrite(pinDI, LOW);
	}
}

bool MACROM93C46::wait() 
{
unsigned int timeout=0;
bool errorFlag=false;

	delayMicroseconds(1);
digitalWrite(pinCS, HIGH);
	while(digitalRead(pinDO) != HIGH) 
	{
		delay(1);
		timeout++;
		if(timeout>20)
			{
			errorFlag=true;
			break;
			}
	}
	digitalWrite(pinCS, LOW);
	return errorFlag;
}
