#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define MOTOR_PIN1 12 //pin 1
#define MOTOR_PIN2 11 //pin 1

Servo motor1;
Servo motor2;
void setup() {
  Serial.begin(9600);
  Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");
  //pinMode(12, OUTPUT);
  motor1.attach(MOTOR_PIN1);
  motor2.attach(MOTOR_PIN2);
  
  Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  motor1.writeMicroseconds(MAX_SIGNAL);
  motor2.writeMicroseconds(MAX_SIGNAL);
  //analogWrite(12, 255);
  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("Sending minimum output");
  motor1.writeMicroseconds(MIN_SIGNAL);
  motor2.writeMicroseconds(MIN_SIGNAL);
  
  Serial.println("Calibrated");
  while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(800);
  Serial.println("800");
  while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(900);
Serial.println("900");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1000);
Serial.println("1000");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1100);
    Serial.println("1100");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1200);
  Serial.println("1200");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1300);
  Serial.println("1300");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1400);
//motor2.writeMicroseconds(1200);
Serial.println("1400");
  while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1500);
Serial.println("1500");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1600);
Serial.println("1600");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1700);
Serial.println("1700");
    while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1800);
Serial.println("1800");
 while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(1900);
Serial.println("1900");
 while (!Serial.available());
  Serial.read();
  //analogWrite(12, 255);
  motor1.writeMicroseconds(2000);
Serial.println("2000");
}

void loop() {  
  
}
