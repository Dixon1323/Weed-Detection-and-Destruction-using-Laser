#include <Servo.h>


Servo myservo;
Servo myservo1;
int prev=0,current=0,interval=300;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  myservo.attach(D1);
  myservo1.attach(D2);
  myservo1.write(90);
  
  while (!Serial) {
    ;
  }
}

void loop() {
current=millis();
if(current-prev>=interval){
  prev=current;
  int val=analogRead(A0);
  int angle=map(val,0,1023,0,180);
  myservo.write(99);
  Serial.print("X Axis Value: ");
  Serial.println("99");
}
  if (Serial.available() > 0) {
    int value = Serial.parseInt();
    Serial.print("Y Axis : ");
    Serial.println(value);
    if(value!=0)
    myservo1.write(value);   
  }
}
