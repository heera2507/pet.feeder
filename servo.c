#include <Servo.h>

#define PWM_PIN 11
#define UP_BUTTON 2
#define DOWN_BUTTON 3
#define UP_LED 7
#define DOWN_LED 8
#define LED_ON HIGH
#define LED_OFF LOW
#define MAX_VALUE 180
#define MIN_VALUE 0

Servo myServo;

int buttonCount = 0;

int upLedStatus;
int downLedStatus;
int upPrevButtonStatus;
int downPrevButtonStatus;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(PWM_PIN);
  pinMode(UP_LED, OUTPUT);
  pinMode(DOWN_LED, OUTPUT);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);
  myServo.write(0);

  Serial.begin(115200);
  Serial.println("DU Cruise Control!");
}

void loop() {

  int upButtonState = digitalRead(UP_BUTTON);
  int downButtonState = digitalRead(DOWN_BUTTON);

  Serial.println(upButtonState);
  if ((upPrevButtonStatus == LOW) && (upButtonState == HIGH))
{
  upLedStatus = !upLedStatus;
  buttonCount = buttonCount + 10;

  if (buttonCount <= MAX_VALUE)
  {
    myServo.write(buttonCount);
  }
  else if (buttonCount > MAX_VALUE)
  {
    buttonCount = 180;
  }
  Serial.print("Speed:");
  Serial.println(buttonCount);

  delay(100);
}
  digitalWrite(UP_LED, upLedStatus);
  upPrevButtonStatus = upButtonState;

  if ((downPrevButtonStatus == LOW) && (downButtonState == HIGH))
{
  downLedStatus = !downLedStatus;
  buttonCount = buttonCount - 10;

  if (buttonCount >= MIN_VALUE)
  {
    myServo.write(buttonCount);
  }
  else if (buttonCount < MIN_VALUE)
  {
    buttonCount = 0;
  }
  Serial.print("Speed:");
  Serial.println(buttonCount);

  delay(100);

}
  digitalWrite(DOWN_LED, downLedStatus);
  downPrevButtonStatus = downButtonState;
}
