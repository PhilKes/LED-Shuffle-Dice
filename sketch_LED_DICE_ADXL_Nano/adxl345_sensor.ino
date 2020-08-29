/************************************************************************
* This program is free software; you can redistribute it and/or modify *
* it under the terms of the GNU License V2.                            *
* This program is distributed in the hope that it will be useful,      *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU General Public License, version 2 for more details               *
*                                                                      *
* Bare bones ADXL345 i2c example for Arduino 1.0                       *
* by Jens C Brynildsen <http://www.flashgamer.com>                     *
* This version is not reliant of any external lib                      *
* (Adapted for Arduino 1.0 from http://code.google.com/p/adxl345driver)*
*                                                                      *
* Demonstrates use of ADXL345 (using the Sparkfun ADXL345 breakout)    *
* with i2c communication. Datasheet:                                   *
* http://www.sparkfun.com/datasheets/Sensors/Accelerometer/ADXL345.pdf *
* If you need more advanced features such as freefall and tap          *
* detection, check out:                                                *
* https://github.com/jenschr/Arduino-libraries                         *
***********************************************************************/
#include <Wire.h>

#define DEVICE (0x53) // Device address as specified in datasheet 
#define SENSORS_GRAVITY_STANDARD (9.80665F) // Const float
#define MG2G_MULTIPLIER (0.004) // 1 LSB represents about 3.9 mg

byte _buff[2]; // Buffer array

char POWER_CTL = 0x2D;  //Power Control Register
char DATA_FORMAT = 0x31; // Data format control
char DATAX0 = 0x32; // X-Axis Data 0
char DATAX1 = 0x33; // X-Axis Data 1
char DATAY0 = 0x34; // Y-Axis Data 0
char DATAY1 = 0x35; // Y-Axis Data 1
char DATAZ0 = 0x36; // Z-Axis Data 0
char DATAZ1 = 0x37; // Z-Axis Data 1
char BW_RATE = 0x2C;    // Data rate and power mode control

void adxl345_init()
{
  Wire.begin(); // Join i2c bus (address optional for master)

  // Setup ADXL345 registers, see datahsheet to configure for your liking
  writeTo(DATA_FORMAT, B00001000); // Enable full resolution 10-bit, B3, and most sensitive 2g range, B1B0
  writeTo(BW_RATE, B00001100); // Set 400Hz output update rate - not I2C but data update rate, B4B3B2B1
  writeTo(POWER_CTL, 0); // Always be sure to zero out register, don't asume it's zero
  writeTo(POWER_CTL, B00001000); // Enter measurement mode, B4
}

void readAccel(float *x, float *y, float *z)
{
  // How many bytes to request from ADXL345 - it seems there are problems doing more than 4 bytes, keep it at 2 bytes.
  uint8_t howManyBytesToRead = 2; 
  
  // Each axis reading comes in 10 bit resolution, i.e. 2 bytes, least significat byte first!! 
  // Thus we are converting both bytes in to one int - shift bytes to align like DATAX1DATAX0
  // If the bytes seem switched from the sensor, change [1] to [0] and verse visa
  //readFrom( DATAX0, howManyBytesToRead, _buff); //read the acceleration data from the ADXL345
  //*x = ((((int)_buff[0]) << 8) | _buff[1]) * MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;   
  *x = read16(DATAX0) * MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;   

  //readFrom( DATAY0, howManyBytesToRead, _buff); //read the acceleration data from the ADXL345
  //*y = ((((int)_buff[0]) << 8) | _buff[1]) * MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;   
  *y = read16(DATAY0) * MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;   

  //readFrom( DATAZ0, howManyBytesToRead, _buff); //read the acceleration data from the ADXL345
  //*z = ((((int)_buff[0]) << 8) | _buff[1]) * MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
  // Does not always seem to work - some units have a defective z-component I've noticed
  *z = read16(DATAZ0) * MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;   

  // Test single bit
  //if ( (_buff[0] & 0B10000000) ) digitalWrite(PB1, HIGH); 
  //else digitalWrite(PB1, LOW);
}

// Write vale to register address
void writeTo(byte address, byte val) {
  Wire.beginTransmission(DEVICE);  // start transmission to device 
  Wire.write(address);             // send register address
  Wire.write(val);                 // send value to write
  Wire.endTransmission();          // end transmission
}

// Reads num bytes starting from address register on device in to _buff array
void readFrom(byte address, int num, byte _buff[]) {
  Wire.beginTransmission(DEVICE); // start transmission to device 
  Wire.write(address);             // sends address to read from
  Wire.endTransmission();         // end transmission

  //Wire.beginTransmission(DEVICE); // start transmission to device
  Wire.requestFrom(DEVICE, num);    // request 6 bytes from device

  int i = 0;
  while(Wire.available())         // device may send less than requested (abnormal)
  { 
    _buff[i] = Wire.read();    // receive a byte
    i++;
  }
 //Wire.endTransmission();         // end transmission
}

// Reads 2 bytes (16bits) from first x, y, or z register
int16_t read16(byte address) {
   Wire.beginTransmission(DEVICE);
   Wire.write(address);             // sends address to read from
   Wire.endTransmission();
   Wire.requestFrom(DEVICE, 2); // request 2 bytes from device
   //return (uint16_t)(Wire.read() << 8) | (Wire.read()); // DATAx0DATAx1
   return (uint16_t)(Wire.read() | (Wire.read() << 8)); // DATAx1DATAx0
  }
