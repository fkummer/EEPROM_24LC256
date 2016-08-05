#include <EEPROM_24LC256.h>
//MUST INCLUDE WIRE LIBRARY
#include <Wire.h>

//The constructor requires the value of the A0, A1, A2 pins passed into it.
//A0 is the zeroth bit, A1 the first bit, and A2 the second bit, and that gives you the decimal number to pass in.
//All those pins are grounded in the setup from this example, so its a 0.
//If A0 were pulled high, then we would pass in a 1 (001). If A1 and A0 were pulled high, we would pass in a 3 (011).
//This sets the address on the I2C bus.
EEPROM_24LC256 eepOne(0);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //Write one byte of data to eeprom address 0
  eepOne.writeEEPROM(0,0xaa);
  
  //Read one byte from eeprom address 0 and print it out
  Serial.println(eepOne.readEEPROM(0));
  delay(2000);
}
