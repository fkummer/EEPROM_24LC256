/*
  EEPROM_24LC256.h - Library for eeprom.
  Created by Fred Kummer, August 4th, 2016.
  Released into the public domain.
  A Chewie Labs Creation!
*/
#ifndef EEPROM_24LC256_h
#define EEPROM_24LC256_h

#include "Arduino.h"

class EEPROM_24LC256{
public:
  EEPROM_24LC256(int devAddr);
  void writeEEPROM(unsigned int eeaddress, byte data );
  void writeEEPROM(unsigned int eeaddress, byte data[], int length);
  byte readEEPROM(unsigned int eeaddress );
  void readEEPROM(unsigned int eeaddress, byte *buffer, int length);
private:
  int deviceAddress;
};

#endif
