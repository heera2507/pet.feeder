int buzz = 2; //pin

void setup() { 
  pinMode(buzz, OUTPUT); //setup pin buzzer  output
}

void loop() {
  tone(buzz, 300); //buzzer sebesar 200Hz, 
  delay(4000);
  tone(buzz, 350);
  delay(4000);
}
