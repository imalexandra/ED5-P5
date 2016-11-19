#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define MOTOR_PIN1 12 //pin 1
#define MOTOR_PIN2 11 //pin 1
int loopVar = 0;
int incomingByte = MIN_SIGNAL;

Servo motor1;
Servo motor2;
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500) ;
  Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");
  motor1.attach(MOTOR_PIN1);
  motor2.attach(MOTOR_PIN2);
  
  Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  //motor1.writeMicroseconds(MAX_SIGNAL);
  //motor2.writeMicroseconds(MAX_SIGNAL);
  //while (!Serial.available());
  //Serial.read();

  Serial.println("Sending minimum output");
  motor1.writeMicroseconds(MIN_SIGNAL);
  motor2.writeMicroseconds(MIN_SIGNAL);
  while (!Serial.available());
  Serial.read();
  Serial.println("Calibrated");

  while(loopVar == 0){
    while (!Serial.available());
    incomingByte = Serial.parseInt();
    motor1.writeMicroseconds(incomingByte);
    Serial.println(incomingByte);
  }
}

void loop() {  
  
}
