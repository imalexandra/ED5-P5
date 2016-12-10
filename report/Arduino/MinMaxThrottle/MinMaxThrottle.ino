#include <Servo.h>

#define MAX_SIGNAL 2400
#define MIN_SIGNAL 700
#define MOTOR_PIN1 12 //pin 1
#define MOTOR_PIN2 11 //pin 1
#define MOTOR_PIN3 8 //pin 1
#define MOTOR_PIN4 7 //pin 1
int loopVar = 0;
int incomingByte = MIN_SIGNAL;

Servo motorFL;
Servo motorFR;
Servo motorBR;
Servo motorBL;
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50) ;
  Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");
  motorFR.attach(MOTOR_PIN1);
  motorBR.attach(MOTOR_PIN2);
  motorBL.attach(MOTOR_PIN3);
  motorFL.attach(MOTOR_PIN4);
  
  Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  //motorFL.writeMicroseconds(MAX_SIGNAL);
  //motorFR.writeMicroseconds(MAX_SIGNAL);
  //motorBR.writeMicroseconds(MAX_SIGNAL);
  //motorBL.writeMicroseconds(MAX_SIGNAL);
  //while (!Serial.available());
  //Serial.read();

  Serial.println("Sending minimum output");
  motorFL.writeMicroseconds(MIN_SIGNAL);
  motorFR.writeMicroseconds(MIN_SIGNAL);
  motorBR.writeMicroseconds(MIN_SIGNAL);
  motorBL.writeMicroseconds(MIN_SIGNAL);
  while (!Serial.available());
  Serial.read();
  Serial.println("Calibrated");

  while(loopVar == 0){
    while (!Serial.available());
    incomingByte = Serial.parseInt();
    //motorFL.writeMicroseconds(incomingByte);
    //motorFR.writeMicroseconds(incomingByte);
    //motorBR.writeMicroseconds(incomingByte);
    motorBL.writeMicroseconds(incomingByte);
    Serial.println(incomingByte);
  }
}

void loop() {  
  
}
