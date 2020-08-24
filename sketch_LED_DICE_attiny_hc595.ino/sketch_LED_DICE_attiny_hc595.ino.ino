int dataPin = 0;
int clockPin = 3;

void setup () {
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 0);
}

void loop()
{
  /*
  int i = 0;
  for (i = 1; i < 7; i++) {
    setLeds(i);
    delay(2000);
  }*/
   delay(2000);
   rollDice();
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
