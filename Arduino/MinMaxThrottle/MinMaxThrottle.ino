#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define MOTOR_PIN1 12 //pin 1
//#define MOTOR_PIN2 11 //pin 1

Servo motor1;
Servo motor2;
void setup() {
  Serial.begin(9600);
  Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");
  //pinMode(12, OUTPUT);
  motor1.attach(MOTOR_PIN1);
  //motor2.attach(MOTOR_PIN2);
  
  Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  motor1.writeMicroseconds(MAX_SIGNAL);
  //motor2.writeMicroseconds(MAX_SIGNAL);
  //analogWrite(12, 255);
  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("Sending minimum output");
  motor1.writeMicroseconds(MIN_SIGNAL);
  //motor2.writeMicroseconds(MIN_SIGNAL);
  
  Serial.println("Calibrated");
  while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(700);
  Serial.println("700");
  while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(830);
Serial.println("830");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(960);
Serial.println("960");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1090);
    Serial.println("1090");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1220);
  Serial.println("1220");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1350);
  Serial.println("1350");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1480);
//motor2.writeMicroseconds(1200);
Serial.println("1480");
  while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1610);
Serial.println("1610");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1740);
Serial.println("1740");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1870);
Serial.println("1870");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(2000);
Serial.println("2000");
}

void loop() {  
  
}
