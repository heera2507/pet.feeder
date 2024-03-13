#include <Servo.h>

#define P_PIN 11
#define UPPER_B 2
#define DOWN_B 3
#define UPPER_LED 7
#define DOWN_LED 8
#define LED_ON HIGH
#define LED_OFF LOW
#define MAX_VAL 180
#define MIN_VAL 0

Servo myServo;

int BCount = 0;

int UPPERLedStatus;
int downLedStatus;
int UPPERPrevBStatus;
int downPrevBStatus;

void setUPPER() {
  // put your setUPPER code here, to run once:
  myServo.attach(P_PIN);
  pinMode(UPPER_LED, OUTPUT);
  pinMode(DOWN_LED, OUTPUT);
  pinMode(UPPER_B, INPUT);
  pinMode(DOWN_B, INPUT);
  myServo.write(0);

  Serial.begin(115200);
  Serial.println("DU Cruise Control!");
}

void loop() {

  int UPPERBState = digitalRead(UPPER_B);
  int downBState = digitalRead(DOWN_B);

  Serial.println(UPPERBState);
  if ((UPPERPrevBStatus == LOW) && (UPPERBState == HIGH))
{
  UPPERLedStatus = !UPPERLedStatus;
  BCount = BCount + 10;

  if (BCount <= MAX_VAL)
  {
    myServo.write(BCount);
  }
  else if (BCount > MAX_VAL)
  {
    BCount = 180;
  }
  Serial.print("Speed:");
  Serial.println(BCount);

  delay(100);
}
  digitalWrite(UPPER_LED, UPPERLedStatus);
  UPPERPrevBStatus = UPPERBState;

  if ((downPrevBStatus == LOW) && (downBState == HIGH))
{
  downLedStatus = !downLedStatus;
  BCount = BCount - 10;

  if (BCount >= MIN_VAL)
  {
    myServo.write(BCount);
  }
  else if (BCount < MIN_VAL)
  {
    BCount = 0;
  }
  Serial.print("Speed:");
  Serial.println(BCount);

  delay(100);

}
  digitalWrite(DOWN_LED, downLedStatus);
  downPrevBStatus = downBState;
}
