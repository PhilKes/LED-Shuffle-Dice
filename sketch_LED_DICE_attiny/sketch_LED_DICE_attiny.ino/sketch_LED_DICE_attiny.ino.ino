#include <SparkFun_ADXL345.h>
int pinLeds1 = 0;
int pinLeds2 = 2;
int pinLeds3 = 3;
int pinLeds4 = 1;

long ran;
int time = 2000;

ADXL345 adxl = ADXL345(); //SDA A4,SCL A5
void setup ()
{
  //Serial.begin(9600);                 // Start the serial terminal
  //Serial.println("SparkFun ADXL345 Accelerometer Hook Up Guide Example");
  //Serial.println();

  pinMode (pinLeds1, OUTPUT);
  pinMode (pinLeds2, OUTPUT);
  pinMode (pinLeds3, OUTPUT);
  pinMode (pinLeds4, OUTPUT);
  digitalWrite(pinLeds1, HIGH);
  //randomSeed(analogRead(0));
  adxlSetup();
}
void adxlSetup()
{
  adxl.powerOn();                     // Power on the ADXL345
  adxl.setRangeSetting(4);           // Give the range settings

  adxl.setSpiBit(0);                  // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1

  adxl.setActivityXYZ(1, 1, 1);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setActivityThreshold(65);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)

  adxl.ActivityINT(1);


  //attachInterrupt(digitalPinToInterrupt(interruptPin), ADXL_ISR, RISING);   // Attach Interrupt

}
void loop()
{

  if (adxl.triggered(adxl.getInterruptSource(), ADXL345_ACTIVITY)) {
    //adxl.ActivityINT(0);
    //    Serial.println("*** ACTIVITY ***");
    delay(300);
    rollDice();
    delay(50);
    while (adxl.triggered(adxl.getInterruptSource(), ADXL345_ACTIVITY))
    {
    }

  }
}

void rollDice()
{
  ran = random(1, 7);
  if (ran == 1) {
    digitalWrite (pinLeds1, LOW);
  }
  else if (ran == 2) {
    digitalWrite (pinLeds4, HIGH);
  }
  else if (ran == 3) {
    digitalWrite (pinLeds4, HIGH);
    digitalWrite (pinLeds1, HIGH);
  }
  else if (ran == 4) {
    digitalWrite (pinLeds2, HIGH);
    digitalWrite (pinLeds4, HIGH);
  }
  else if (ran == 5) {
    digitalWrite (pinLeds1, LOW);
    digitalWrite (pinLeds2, HIGH);
    digitalWrite (pinLeds4, HIGH);
  }
  else if (ran == 6) {
    digitalWrite (pinLeds2, HIGH);
    digitalWrite (pinLeds4, HIGH);
    digitalWrite (pinLeds3, HIGH);
  }
  delay (time);
  digitalWrite (pinLeds1, HIGH);
  digitalWrite (pinLeds2, LOW);
  digitalWrite (pinLeds3, LOW);
  digitalWrite (pinLeds4, LOW);
}
