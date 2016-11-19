#define MAX_SIGNAL 2000 //define max and min signal length
#define MIN_SIGNAL 700
#define MOTOR_PIN1 12 //pin 1 on the board
Servo motor1;
void setup() {
  Serial.begin(9600); //begin serial communication at 9600 rate
  Serial.println("Program begin...");
  motor1.attach(MOTOR_PIN1); //attach the pin to the servo variable
  Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  motor1.writeMicroseconds(MAX_SIGNAL); //this signal should only be sent when calibrating for the first time
  while (!Serial.available()); //wait for an input, so you have time to plug in the ESC
  Serial.read();
  Serial.println("Sending minimum output");
  motor1.writeMicroseconds(MIN_SIGNAL); //send the min signal, which is the only needed signal when already calibrated
  while (!Serial.available()); //wait for the beeps to indicate calibration is done
  Serial.read();
  Serial.println("Calibrated");
}

void loop() {  
   
}
