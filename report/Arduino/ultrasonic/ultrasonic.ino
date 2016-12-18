#include <NewPing.h>
 
#define TRIGGER_PIN  A0
#define ECHO_PIN     A1
#define MAX_DISTANCE 200
long prevTimer = 0; //initial timer
long currTimer = 100; //initial timer
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  Serial.print("Ping: ");
  long currTimer = millis(); //get time
  if(currTimer - prevTimer < 30000){
    Serial.print(sonar.ping_cm());
    Serial.println("cm");
  }
}
