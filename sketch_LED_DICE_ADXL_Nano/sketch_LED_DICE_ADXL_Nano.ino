//Test Sketch for Arduino Nano + 74HC595 + ADXL345
// with Serial debugging

#include <Wire.h>
#include <avr/power.h>

#define ROLL_THRESHOLD  25

float x, y, z;

int dataPin = 4;
int clockPin = 3;

void setup ()
{
  Serial.begin(9600);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 0);
  //randomSeed(analogRead(0));
  // On-board Red LED

  // Setup ADXL345
  adxl345_init();
  Serial.println("initialized");
}

float X, Y, Z, totalAccel;

void loop(){
  // Update accelerometer values

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

  //Serial.print("X: ");
  /* Serial.print(X);
    Serial.print(" ");
    Serial.print(Y);
    Serial.print(" ");
    Serial.print(Z);
    Serial.println();
     Serial.println(totalAccel);
  */
  // Enable LED of tilted over mid-point of y-axis
  if (sqrt(y * y) > 20) {
    setLeds(6);
  }
  else {
    setLeds(1);
  }

  if (totalAccel > ROLL_THRESHOLD) {
    Serial.println("Roll");
    delay(2000);
  }
  //delay(100);
}

byte leds = 0;
void setLeds(int number) {
  if (number == 1) {
    leds = B10000001;
  }
  else if (number == 2) {
    leds = B10000010;
  }
  else if (number == 3) {
    leds = B10000011;
  }
  else if (number == 4) {
    leds = B10000110;
  }
  else if (number == 5) {
    leds = B10000111;
  }
  else if (number == 6) {
    leds = B10001110;
  }
  shiftLeds(leds);
}

// the heart of the program
void shiftLeds(byte dataOut) {
  int i = 0;
  int pinState;
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 0);

  for (i = 7; i >= 0; i--)  {
    digitalWrite(clockPin, 0);
    if ( dataOut & (1 << i) ) {
      pinState = 1;
    }
    else {
      pinState = 0;
    }

    digitalWrite(dataPin, pinState);
    digitalWrite(clockPin, 1);
    digitalWrite(dataPin, 0);
  }
  //stop shifting
  digitalWrite(clockPin, 0);
  //latch with dataPin
  digitalWrite(dataPin, 1);
  delay(10);
  digitalWrite(dataPin, 0);
}
void rollDice() {
  setLeds( random(1, 7));
}
