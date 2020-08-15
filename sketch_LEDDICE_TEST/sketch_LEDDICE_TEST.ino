
 int pinLeds1 = 3;
int pinLeds2 = 4;
int pinLeds3 = 1;

int pinLed4 = 0;
int buttonPin = 2;
int buttonState;
long ran;
int time = 2000;

void setup(){
 pinMode (pinLeds1, OUTPUT);
  pinMode (pinLeds2, OUTPUT);
  pinMode (pinLeds3, OUTPUT);
  pinMode (pinLed4, OUTPUT);
  }

void loop() 
{
  digitalWrite (pinLeds1, HIGH);
  delay(1000);
  digitalWrite (pinLeds1, LOW);
  digitalWrite (pinLeds2, HIGH);
  delay(1000);
  digitalWrite (pinLeds3, HIGH);
  digitalWrite (pinLeds2, LOW);
  delay(1000);
  digitalWrite (pinLeds3, LOW);
  digitalWrite (pinLed4, HIGH);
  delay(1000);
   digitalWrite (pinLed4, LOW);
   delay(1000);
  // put your main code here, to run repeatedly:

}
