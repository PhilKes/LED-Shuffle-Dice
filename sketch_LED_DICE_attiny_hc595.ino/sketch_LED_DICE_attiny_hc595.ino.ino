

void setup (){
}

int dataPin=3;
int clockPin=4;
void loop()
{
  int i = 0;
  for (i = 1; i < 7; i++) {
    setLeds(i);
      delay(2000);
  }
 // delay(2000);
 // rollDice();
}
byte leds=0;
void setLeds(int number) {
  if (number == 1) {
    leds= B01000001;
  }
  else if (number == 2) {
    leds= B01000010;
  }
  else if (number == 3) {
    leds= B01000011;
  }
  else if (number == 4) {
    leds= B01000110;
  }
  else if (number == 5) {
    leds= B01000111;
  }
  else if (number == 6) {
    leds= B01001110;
  }

  shiftOut(dataPin, clockPin,LSBFIRST, 0);
}
void rollDice() {
  setLeds( random(1, 7));
}
