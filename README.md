# EEPROM_24LC256
Arduino Library for interfacing with the 24LC56 EEPROM chip. Uses the Wire library for I2C
-------------------------------------------------------------------------------------------

This library is intended to allow people to easily use the 24LC256 EEPROM chip with the Arduino. The chip has a few funky properties, such as wrapping back around if a write hits the end of a page and having a limited write buffer, and this takes care of all that for you. You should not really need to know anything about the hardware specifics of the chip now, you can simply treat it as 256,000 bits for you to write!

It can be installed like a normal Arduino library, i.e. download the repository and place it in the libraries directory in your Arduino directory. Then you can just use import library, and there it is! You will however need to also include the Wire library for the I2C to work!

You can write and read single bytes at a time, or you can write and read arbitrarily long sections (even across multiple pages) all at once. 

Look in the EEPROM_24LC56 folder for the source code if you'd like to take a look, and the examples folder has examples of how to use it.

More documentation is on the way!

And just to get you the absolute basics, here's the signatures for all the functions in the library:

  //Constructor
  EEPROM_24LC256(int devAddr);
  
  //Write a single byte at address eeaddress in the chips memory
  void writeEEPROM(unsigned int eeaddress, byte data );
  
  //Write length bytes from the array data starting at address eeaddress and incrementing up.
  void writeEEPROM(unsigned int eeaddress, byte data[], int length);
  
  //Read a single byte at address eeaddress in the chips memory
  byte readEEPROM(unsigned int eeaddress );
  
  //Read length bytes from the address eeaddress and incrementing up into the array pointed to by buffer.
  void readEEPROM(unsigned int eeaddress, byte *buffer, int length);
  
By Fred Kummer

A Chewie Labs Creation!
