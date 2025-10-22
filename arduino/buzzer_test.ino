int buzz = 2; // Buzzer pin

void setup() { 
  pinMode(buzz, OUTPUT);
}

void loop() {
  tone(buzz, 300);
  delay(4000);
  tone(buzz, 350);
  delay(4000);
}
