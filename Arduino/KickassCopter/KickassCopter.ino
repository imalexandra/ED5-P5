#include <Servo.h> //servo library

#define MAX_SIGNAL 2000 //max pwm signal, need to recalibrate ESCs if changed
#define MIN_SIGNAL 700 //min pwm signal, "-"
#define OUT_SIGNAL 850 //pwm signal we'll be sending out to motors during the rest of the program
#define MOTOR_1_PIN 12 //motor pins, APM board has weird layout
#define MOTOR_2_PIN 11
#define MOTOR_3_PIN 8
#define MOTOR_4_PIN 7

Servo motor1; //define servo variables for motors
Servo motor2;
Servo motor3;
Servo motor4;

long prevTimer = 0; //initial timer
long currTimer = 100; //initial timer
const long initTime = 4000; //4 seconds to turn on ESCs
const long runTime = 10000; //10 seconds to run program
bool escCalibrate = false; //have we calibrated ESCs yet?
bool programStarted = false;

void setup() {
    Serial.begin(9600);
    Serial.println("Program begins...");
    
    motor1.attach(MOTOR_1_PIN); //connect servo variables to pins
    motor2.attach(MOTOR_2_PIN);
    motor3.attach(MOTOR_3_PIN);
    motor4.attach(MOTOR_4_PIN);

}

void loop() {
    long currTimer = millis(); //get time
    Serial.println(currTimer);
//  Only need this part if calibrating ESCs. The ones used in our prototype
//  need only min signal on startup to run
//    Serial.println("Now writing maximum output.");
//    Serial.println("Turn on power source, then wait 2 seconds and press any key.");
//    motor1.writeMicroseconds(MAX_SIGNAL);
//    motor2.writeMicroseconds(MAX_SIGNAL);
//    motor3.writeMicroseconds(MAX_SIGNAL);
//    motor4.writeMicroseconds(MAX_SIGNAL);
//
    if(programStarted == false){
      Serial.println("Waiting for input.");
      while (!Serial.available());
      Serial.read();
      programStarted = true;
      prevTimer = millis();
      Serial.println("Program will now start");
      Serial.println(currTimer);
      Serial.println(prevTimer);
    }
    if(programStarted == true){
      //Check if we're < 4 seconds and ESCs havent been calibrated yet
      if ((currTimer - prevTimer <= initTime) && (escCalibrate == false)) {
        motor1.writeMicroseconds(MIN_SIGNAL); //send out calib. signal
        motor2.writeMicroseconds(MIN_SIGNAL);
        motor3.writeMicroseconds(MIN_SIGNAL);
        motor4.writeMicroseconds(MIN_SIGNAL);
      }else if((currTimer - prevTimer >= initTime) && (escCalibrate == false)){
        escCalibrate = true; //otherwise, say that we calibrated
        Serial.println("ESCs calibrated");
        prevTimer = currTimer; //reset timer and never repeat this step again
      }
      if(escCalibrate == true){ //probably the rest of the program will be under here
          if(currTimer - prevTimer <= runTime){ //check if < 10 seconds
            motor1.writeMicroseconds(OUT_SIGNAL); // let's fly!
            motor2.writeMicroseconds(OUT_SIGNAL);
            motor3.writeMicroseconds(OUT_SIGNAL);
            motor4.writeMicroseconds(OUT_SIGNAL);
          }else{
            motor1.writeMicroseconds(MIN_SIGNAL); //program ends, time to stop
            motor2.writeMicroseconds(MIN_SIGNAL);
            motor3.writeMicroseconds(MIN_SIGNAL);
            motor4.writeMicroseconds(MIN_SIGNAL);
          }
      }
    }
}
