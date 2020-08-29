// Attiny85 + 74HC595 + ADXL345
#include <TinyWireM.h>
#include <avr/power.h>

#define ROLL_THRESHOLD  16

float x, y, z;

int dataPin = PB4;
int clockPin = PB3;

/*
 * Attiny - 74hc595
 * PB3 - SHCP (Clock)
 * PB4 - DS (Data) + STCP (Latch)
 * VCC - MR
 * GND - OE
 * 
 * Attiny - ADXL345
 * VCC - CS
 * PB0 - SDA
 * PB2 - SCL
 */


void setup ()
{
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 0);
  randomSeed(analogRead(0));
  // Setup ADXL345
  adxl345_init();
  setLeds(0);
}

float X, Y, Z, totalAccel;

void loop()
{

  //rollDice();
  //delay(2000);

  /* for (int i = 1; i < 7; i++) {
     setLeds(i);
     delay(2000);
    }*/

  X = 0;
  Y = 0;
  Z = 0;
  for (int i = 0; i < 10; i++) {
    readAccel(&x, &y, &z);
    X += x;
    Y += y;
    Z += z;
    delay(1);
  }
  X /= 10;
  Y /= 10;
  Z /= 10;

  totalAccel = sqrt(X * X + Y * Y + Z * Z);
  if (totalAccel > ROLL_THRESHOLD) {
    rollDice();
    delay(2000);
  }

}

byte leds = 0;
void setLeds(int number) {
  if (number == 0) {
    leds = 0;
  }
  else if (number == 1) {
    leds = B00000001;
  }
  else if (number == 2) {
    leds = B00000010;
  }
  else if (number == 3) {
    leds = B00000011;
  }
  else if (number == 4) {
    leds = B00000110;
  }
  else if (number == 5) {
    leds = B00000111;
  }
  else if (number == 6) {
    leds = B00001110;
  }
  //shiftLeds(leds);
  shiftOut(dataPin, clockPin, MSBFIRST, leds);
  digitalWrite(clockPin, 0);
  //latch with dataPin
  digitalWrite(dataPin, 0);
  delay(10);
  digitalWrite(dataPin, 1);
  delay(10);
  digitalWrite(dataPin, 0);
}

void rollDice() {
  setLeds( random(1, 7));
}
