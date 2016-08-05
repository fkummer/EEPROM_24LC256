/*
  EEPROM_24LC256.cpp - Library for eeprom.
  Created by Fred Kummer, August 4th, 2016.
  Released into the public domain.
  A Chewie Labs Creation!
*/
#include "Arduino.h"
#include "EEPROM_24LC256.h"
#include <Wire.h>

EEPROM_24LC256::EEPROM_24LC256(int devAddr)
{
  deviceAddress = 0x50 | devAddr;
  Wire.begin();
}

void EEPROM_24LC256::writeEEPROM(unsigned int eeaddress, byte data ) {
  int stat = 2;
  //0 is a successful transmit, added to force it to go through properly
  while(stat != 0){
    Wire.beginTransmission(deviceAddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(data);
    stat = Wire.endTransmission();
    //Write cycle time is 5 ms for both byte and page, since page needs to be refreshed if even one byte is rewritten
    delay(5);
  }

}

void EEPROM_24LC256::writeEEPROM(unsigned int eeaddress, byte data[], int length) {
  int status;
  int bytes_remaining = length;
  int slice_size;
  int index = 0;
  while(bytes_remaining > 0){
    status = 2;

    if(bytes_remaining > 16){
      slice_size = 16;
    }
    else{
      slice_size = bytes_remaining;
    }

    if((eeaddress/64) != ((eeaddress + slice_size)/64)){
      slice_size = 64 - (eeaddress%64);
    }

    //0 is a successful transmit, added to force it to go through properly
    while(status != 0){
      Wire.beginTransmission(deviceAddress);
      Wire.write((int)(eeaddress >> 8));   // MSB
      Wire.write((int)(eeaddress & 0xFF)); // LSB
      //Can I put these in an array instead? Should I?
      for(int slice_ptr = 0; slice_ptr < slice_size; slice_ptr++){
        Wire.write(data[index]);
        index++;
      }
      status = Wire.endTransmission();
      //Write cycle time is 5 ms for both byte and page, since page needs to be refreshed if even one byte is rewritten
      delay(5);
    }

    bytes_remaining = bytes_remaining - slice_size;
    eeaddress = eeaddress + slice_size;
  }
}

byte EEPROM_24LC256::readEEPROM(unsigned int eeaddress ) {
  byte c;
  int ret = 0;
  while(ret < 1){
    Wire.beginTransmission(deviceAddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    ret = Wire.requestFrom(deviceAddress,1);
  }
  if(Wire.available()) { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
  }
  return c;
}

void EEPROM_24LC256::readEEPROM(unsigned int eeaddress, byte *buffer, int length){
  //Limited buffer size of Wire library means we can't get everything in one go.
  //Take 16 bytes at a time.
  int index = 0;
  int status;
  int bytes_remaining = length;
  int slice_size;

  while(bytes_remaining > 0){
    status = 2;

    if(bytes_remaining > 16){
      slice_size = 16;
    }
    else{
      slice_size = bytes_remaining;
    }

    while(status != 0){
      Wire.beginTransmission(deviceAddress);
      Wire.write((int)(eeaddress >> 8));   // MSB
      Wire.write((int)(eeaddress & 0xFF)); // LSB
      status = Wire.endTransmission();
      Wire.requestFrom(deviceAddress, slice_size);
    }

    while(Wire.available() && index < length) { // slave may send less than requested
      buffer[index] = Wire.read(); // receive a byte as character
      index++;
    }

    bytes_remaining = bytes_remaining - slice_size;
    eeaddress = eeaddress + slice_size;
  }

}
