#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define MOTOR_PIN 9

Servo motor;

void setup() {
  Serial.begin(9600);
  Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");

  motor.attach(MOTOR_PIN);

  Serial.println("Now writing maximum output.");
  Serial.println("Wait 2+5 seconds for programming mode. Press key after first beep for brake mode");
  motor.writeMicroseconds(MAX_SIGNAL);

  while (!Serial.available());
  Serial.read();

  Serial.println("Selecting brake progamming mode. Press key again after first beep.");
  motor.writeMicroseconds(MIN_SIGNAL);
  
  while (!Serial.available());
  Serial.read();
  
  Serial.println("Brake mode off. Wait to go back to menu. Press key after 2 beeps for battery type.");
  motor.writeMicroseconds(MAX_SIGNAL);
  
  while (!Serial.available());
  Serial.read();

  Serial.println("Selecting battery type. Press key again after first beep.");
  motor.writeMicroseconds(MIN_SIGNAL);

  while (!Serial.available());
  Serial.read();

  Serial.println("Battery set to li-ion. Press key after a second to exit programming mode.");
  motor.writeMicroseconds(MAX_SIGNAL);
  
  while (!Serial.available());
  Serial.read();

  motor.writeMicroseconds(MIN_SIGNAL);
}

void loop() {  

}
