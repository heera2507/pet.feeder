#include <Servo.h>
int CatButton;  //  
Servo servo1;   //  servo  Servo attached to arduino

void setup() {

  pinMode(3, OUTPUT);     //  3 
  pinMode(11, OUTPUT);    // 
  servo1.attach(9);       //     

// 
  analogWrite(11, 20); //   
  servo1.write(10);    //       
  delay(250);          //       
  analogWrite(11, 0);  //   

}

void loop() {

  CatButton = analogRead(A0); //      

  if (CatButton > 700) {      //       
    analogWrite(11, 20);      //     ()     
    digitalWrite(3, HIGH);    //    
    servo1.write((map(analogRead(A1), 0, 1024, 0, 180))); //    
    delay(250);               //     
    servo1.write(10);         //  
    delay(250);               //     
    digitalWrite(3, LOW);     //    pinmode
    analogWrite(11, 0);       //    
    delay(500);               //       
  }

}
