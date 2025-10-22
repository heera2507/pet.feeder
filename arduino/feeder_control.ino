#include <Servo.h>

int CatSwitch;       // Sensor input pin
Servo servo1;

void setup() {
  pinMode(3, OUTPUT);     // LED indicator
  pinMode(11, OUTPUT);    // PWM for servo
  servo1.attach(9);       // Servo pin

  analogWrite(11, 20);    // Initial servo movement
  servo1.write(10);
  delay(250);
  analogWrite(11, 0);
}

void loop() {
  CatSwitch = analogRead(A0);

  if (CatSwitch > 700) {
    analogWrite(11, 20);
    digitalWrite(3, HIGH);
    servo1.write(map(analogRead(A1), 0, 1024, 0, 180));
    delay(250);
    servo1.write(10);
    delay(250);
    digitalWrite(3, LOW);
    analogWrite(11, 0);
    delay(500);
  }
}
