int pinLeds1 = 1;
int pinLeds2 = 4;
int pinLeds3 = 3;
int pinLeds4 = 0;


void setup ()
{
  pinMode (pinLeds1, OUTPUT);
  pinMode (pinLeds2, OUTPUT);
  pinMode (pinLeds3, OUTPUT);
  pinMode (pinLeds4, OUTPUT);
}

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

void setLeds(int number) {
  if (number == 1) {
    digitalWrite (pinLeds1, HIGH);
    digitalWrite (pinLeds2, LOW);
    digitalWrite (pinLeds3, LOW);
    digitalWrite (pinLeds4, LOW);
  }
  else if (number == 2) {
    digitalWrite (pinLeds1, LOW);
    digitalWrite (pinLeds2, HIGH);
    digitalWrite (pinLeds3, LOW);
    digitalWrite (pinLeds4, LOW);
  }
  else if (number == 3) {
    digitalWrite (pinLeds1, HIGH);
    digitalWrite (pinLeds2, HIGH);
    digitalWrite (pinLeds3, LOW);
    digitalWrite (pinLeds4, LOW);
  }
  else if (number == 4) {
    digitalWrite (pinLeds1, LOW);
    digitalWrite (pinLeds2, HIGH);
    digitalWrite (pinLeds3, HIGH);
    digitalWrite (pinLeds4, LOW);
  }
  else if (number == 5) {
    digitalWrite (pinLeds1, HIGH);
    digitalWrite (pinLeds2, HIGH);
    digitalWrite (pinLeds3, HIGH);
    digitalWrite (pinLeds4, LOW);
  }
  else if (number == 6) {
    digitalWrite (pinLeds1, LOW);
    digitalWrite (pinLeds2, HIGH);
    digitalWrite (pinLeds3, HIGH);
    digitalWrite (pinLeds4, HIGH);
  }
}
void rollDice() {
  setLeds( random(1, 7));
}
