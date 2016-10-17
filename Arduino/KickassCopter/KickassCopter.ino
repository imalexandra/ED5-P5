//#include <math.h>
//#include <stdio.h>
//#include <stdarg.h> 

//#include <AP_MOTORS.h>
//#include <Arduino.h>

#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define MOTOR_1_PIN 12
#define MOTOR_2_PIN 11
#define MOTOR_3_PIN 8
#define MOTOR_4_PIN 7

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

void setup() {
//    digitalWrite(12,HIGH);  // pulling high before changing to output avoids a momentary drop of the pin to low because the ESCs have a pull-down resistor it seems
//    digitalWrite(11,HIGH);
//    pinMode(12,OUTPUT); // OUT1 (PB6/OC1B)
//    pinMode(11,OUTPUT); // OUT2 (PB5/OC1A)
//    digitalWrite(12,HIGH);  // pulling high before changing to output avoids a momentary drop of the pin to low because the ESCs have a pull-down resistor it seems
//    digitalWrite(11,HIGH);
//    digitalWrite(8,HIGH);
//    digitalWrite(7,HIGH);
//    digitalWrite(6,HIGH);
//    pinMode(8,OUTPUT); // OUT3 (PH5/OC4C)
//    pinMode(7,OUTPUT); // OUT4 (PH4/OC4B)
//    pinMode(6,OUTPUT); // OUT5 (PH3/OC4A)
//    digitalWrite(8,HIGH);
//    digitalWrite(7,HIGH);
//    digitalWrite(6,HIGH);
//    digitalWrite(3,HIGH);
//    digitalWrite(2,HIGH);
//    digitalWrite(5,HIGH);
//    pinMode(3,OUTPUT); // OUT6 (PE5/OC3C)
//    pinMode(2,OUTPUT); // OUT7 (PE4/OC3B)
//    pinMode(5,OUTPUT); // OUT8 (PE3/OC3A)
//    digitalWrite(3,HIGH);
//    digitalWrite(2,HIGH);
//    digitalWrite(5,HIGH);
//    digitalWrite(45,HIGH);
//    digitalWrite(44,HIGH);
//    pinMode(45, OUTPUT); // OUT10 (PL4/OC5B)
//    pinMode(44, OUTPUT); // OUT11 (PL5/OC5C)
//    digitalWrite(45,HIGH);
//    digitalWrite(44,HIGH);

    Serial.begin(9600);
    Serial.println("Program begin...");
    Serial.println("This program will calibrate the ESC.");

    motor1.attach(MOTOR_1_PIN);
    motor2.attach(MOTOR_2_PIN);
    motor3.attach(MOTOR_3_PIN);
//    motor4.attach(MOTOR_4_PIN);

    Serial.println("Now writing maximum output.");
    Serial.println("Turn on power source, then wait 2 seconds and press any key.");
    motor1.writeMicroseconds(MAX_SIGNAL);
    motor2.writeMicroseconds(MAX_SIGNAL);
    motor3.writeMicroseconds(MAX_SIGNAL);
//    motor4.writeMicroseconds(MAX_SIGNAL);

    while (!Serial.available());
    Serial.read();

    Serial.println("Sending minimum output");
    motor1.writeMicroseconds(MIN_SIGNAL);
    motor2.writeMicroseconds(MIN_SIGNAL);
    motor3.writeMicroseconds(MIN_SIGNAL);
//    motor4.writeMicroseconds(MIN_SIGNAL);

    while (!Serial.available());
    Serial.read();

    motor1.writeMicroseconds(820);
    motor2.writeMicroseconds(820);
    motor3.writeMicroseconds(820);
//    motor4.writeMicroseconds(820);

}

void loop() {
  // put your main code here, to run repeatedly:

}
