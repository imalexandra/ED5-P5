#include <Servo.h>

#define MAX_SIGNAL 2400
#define MIN_SIGNAL 700
#define MOTOR_PIN1 12 //pin 1
#define MOTOR_PIN2 11 //pin 1
#define MOTOR_PIN3 8 //pin 1
#define MOTOR_PIN4 7 //pin 1
int loopVar = 0;
int incomingByte = MIN_SIGNAL;
int prevTimer = 0;
int currTimer = 0;
int target1 = 1501;
int target2 = 1760;
int target3 = 1559;
int target4 = 1857;
int output1 = 700;
int output2 = 700;
int output3 = 700;
int output4 = 700;

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
    motorFL.writeMicroseconds(incomingByte);
    motorFR.writeMicroseconds(incomingByte);
    motorBR.writeMicroseconds(incomingByte);
    motorBL.writeMicroseconds(incomingByte);
    Serial.println(incomingByte);
  }
  //motorFL.writeMicroseconds(1501);
  //motorFR.writeMicroseconds(1760);
  //motorBR.writeMicroseconds(1559);
  //motorBL.writeMicroseconds(1857);
  //Serial.println("1545");
  //while (!Serial.available());
  //Serial.read();
//  Serial.println("700");
//  motorFL.writeMicroseconds(incomingByte);
//  motorFR.writeMicroseconds(incomingByte);
//  motorBR.writeMicroseconds(incomingByte);
//  motorBL.writeMicroseconds(incomingByte);
//  while (!Serial.available());
//  Serial.read();
}

void loop() {  
//  long currTimer = millis(); //get time
//  if(currTimer - prevTimer >= 400){
//    if(output1 < target1){
//      output1 += 100;
//    }
//    if(output2 < target2){
//      output2 += 100;
//    }
//    if(output3 < target3){
//      output3 += 100;
//    }
//    if(output4 < target4){
//      output4 += 100;
//    }
//    if(output1 > target1){
//      output1 = target1;
//    }
//    if(output2 > target2){
//      output2 = target2;
//    }
//    if(output3 > target3){
//      output3 = target3;
//    }
//    if(output4 > target4){
//      output4 = target4;
//    }
//    prevTimer = currTimer;
//  }
//  motorFL.writeMicroseconds(output1);
//  motorFR.writeMicroseconds(output2);
//  motorBR.writeMicroseconds(output3);
//  motorBL.writeMicroseconds(output4);
//  Serial.println(output1);
//  Serial.println(output2);
//  Serial.println(output3);
//  Serial.println(output4);
}
