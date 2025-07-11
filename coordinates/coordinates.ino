#include <Servo.h>


Servo x_sevo;
Servo y_servo;

bool status=false;
long int current=0,previous=0;
int interval=20000;

int x_angle = 0;
int y_angle = 0;
int x_axis[257] = { 0, 99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 41, 26, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 28, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    99, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    100, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    100, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    100, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    100, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16,
                    100, 91, 87, 81, 75, 71, 65, 58, 52, 48, 43, 38, 31, 26, 21, 16 };


int y_axis[257] = { 0, 58, 57, 57, 57, 57, 57, 57, 57, 57, 60, 60, 60, 60, 60, 60, 60,                 //first row 1 - 16
                    60, 60, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 65, 65,                    //second row 17 - 32
                    64, 64, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 68, 69,                    //third row 33 - 48
                    68, 68, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 72, 73,                    //fourth row 49 - 64
                    72, 72, 75, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 76, 76,                    //fifth row 65 - 80
                    76, 76, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 80, 80,                    //81 - 96
                    79, 79, 82, 82, 82, 82, 82, 81, 82, 82, 83, 82, 82, 82, 83, 83,                    //97 - 112
                    84, 84, 86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 86, 87,                    //113 - 128
                    88, 88, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91,                    //129 - 144
                    92, 92, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95,                    //145 - 160
                    97, 97, 99, 99, 99, 100, 100, 100, 100, 100, 100, 100, 99, 100, 100, 100,          //161 - 176
                    100, 100, 103, 103, 103, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104,    // 177 - 192
                    105, 105, 108, 108, 108, 108, 108, 109, 109, 109, 109, 109, 108, 108, 108, 108,    //193 - 208
                    109, 109, 112, 112, 112, 113, 113, 113, 113, 113, 113, 113, 113, 113, 112, 112,    //209 - 224
                    113, 113, 116, 117, 117, 117, 117, 117, 118, 118, 118, 117, 117, 117, 117, 117,    //225 - 240
                    118, 118, 120, 120, 122, 122, 122, 122, 122, 123, 123, 122, 121, 121, 121, 121 };  //241 - 256


void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(D4,OUTPUT);
  digitalWrite(D4,HIGH);
  x_sevo.attach(D1);
  y_servo.attach(D2);
  x_sevo.write(90);
  y_servo.write(90);

  while (!Serial) {
    ;
  }
}

void loop() {
  current=millis();
  if (Serial.available() > 0) {
    digitalWrite(D4,LOW);
    status=true;
    int value = Serial.parseInt();
    Serial.print("Received Value : ");
    Serial.println(value);
    if (value != 0 && value<=256) {
      x_angle = x_axis[value];
      y_angle = y_axis[value];
      Serial.print("X Axis : ");
      Serial.println(x_angle);
      Serial.print("Y Axis : ");
      Serial.println(y_angle);
      x_sevo.write(x_angle);
      delay(15);
      y_servo.write(y_angle);
      delay(15);
    }
    // delay(500);
  }
  if ((current-previous>=interval) && (status==true)){
    previous=current;
    digitalWrite(D4, HIGH);
    status=false;
  }
}

// void loop() {
//   int number = random(1, 257);
//   Serial.println("**********************************");
//   Serial.print("Random number : ");
//   Serial.println(number);
//   Serial.println("**********************************");
//   x_angle = x_axis[number];
//   y_angle = y_axis[number];
//   Serial.print("X Axis : ");
//   Serial.println(x_angle);
//   Serial.print("Y Axis : ");
//   Serial.println(y_angle);
//   x_sevo.write(x_angle);
//   delay(50);
//   y_servo.write(y_angle);
//   delay(5000);
// }