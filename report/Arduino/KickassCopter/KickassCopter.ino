#include <Servo.h> //servo library
#include <Wire.h> //I2C library
#include <NewPing.h>
#include <SPI.h>
#include <math.h>

#define MAX_SIGNAL 2000 //max pwm signal, need to recalibrate ESCs if changed
#define MIN_SIGNAL 700 //min pwm signal, "-"
#define OUT_SIGNAL 850 //pwm signal we'll be sending out to motors during the rest of the program

#define MOTOR_1_PIN 12 //motor pins, APM board has weird layout
#define MOTOR_2_PIN 11
#define MOTOR_3_PIN 8
#define MOTOR_4_PIN 7

#define TRIGGER_PIN1  A0
#define ECHO_PIN1     A1
#define TRIGGER_PIN2  A2
#define ECHO_PIN2     A3
#define TRIGGER_PIN3  A4
#define ECHO_PIN3     A5
#define TRIGGER_PIN4  A6
#define ECHO_PIN4     A7
#define MAX_DISTANCE 200

#define ToD(x) (x/131) //gyro 131-LSB Sensitivity
#define ToG(x) (x*9.9000/16384) //acc  16384-LSB Sensitivity
#define Aoffset 0.8 

#define xAxis 0
#define yAxis 1
#define zAxis 2

int time=0;
int time_old=0;

const int ChipSelPin1 = 53;

float angle=0;
float angleX=0;
float angleY=0;
float angleZ=0;

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE);

Servo motor1; //define servo variables for motors
Servo motor2;
Servo motor3;
Servo motor4;

long prevTimer = 0; //initial timer
long currTimer = 100; //initial timer
const long initTime = 4000; //4 seconds to turn on ESCs
const long runTime = 10000000000000; //10 seconds to run program
bool escCalibrate = false; //have we calibrated ESCs yet?
bool programStarted = false; //check when connected to PC over USB

void setup() {
    Serial.begin(115200);
    Serial.println("Program begins...");
    Wire.begin();
    motor1.attach(MOTOR_1_PIN); //connect servo variables to pins
    motor2.attach(MOTOR_2_PIN);
    motor3.attach(MOTOR_3_PIN);
    motor4.attach(MOTOR_4_PIN);
    //As per APM standard code, stop the barometer from holding the SPI bus
    pinMode(40, OUTPUT);
    digitalWrite(40, HIGH);
    SPI.begin();  
    SPI.setClockDivider(SPI_CLOCK_DIV16); 
    SPI.setBitOrder(MSBFIRST); 
    SPI.setDataMode(SPI_MODE0);
    delay(100);
    pinMode(ChipSelPin1, OUTPUT);
    ConfigureMPU6000();  // configure chip 
}
void loop() {
    long currTimer = millis(); //get time
//  Only need this part if calibrating ESCs. The ones used in our prototype
//  need only min signal on startup to run
//    Serial.println("Now writing maximum output.");
//    Serial.println("Turn on power source, then wait 2 seconds and press any key.");
//    motor1.writeMicroseconds(MAX_SIGNAL);
//    motor2.writeMicroseconds(MAX_SIGNAL);
//    motor3.writeMicroseconds(MAX_SIGNAL);
//    motor4.writeMicroseconds(MAX_SIGNAL);
//
    // Can remove this program once APM is connected to battery too
    if(programStarted == false){
      Serial.println("Waiting for input.");
      while (!Serial.available());
      Serial.read();
      programStarted = true;
      prevTimer = millis();
      Serial.println("Program will now start");
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
            delay(100);
            //Serial.print("Ping1: ");
            //Serial.print(sonar1.ping_cm());
            //Serial.println("cm");
            //Serial.print("Ping2: ");
            //Serial.print(sonar2.ping_cm());
            //Serial.println("cm");
            //Serial.print("Ping3: ");
            //Serial.print(sonar3.ping_cm());
            //Serial.println("cm");
            //Serial.print("Ping4: ");
            //Serial.print(sonar4.ping_cm());
            //Serial.println("cm");
            Serial.print("Acc X ");
            Serial.print(AcceDeg(ChipSelPin1, xAxis));
            Serial.print("   ");
            Serial.print("Acc Y ");
            Serial.print(AcceDeg(ChipSelPin1, yAxis));
            Serial.print("   ");
            Serial.print("Acc Z ");  
            Serial.print(AcceDeg(ChipSelPin1, zAxis));
            Serial.print("   ");  
            Serial.print("Gyro X ");  
            Serial.print(GyroDeg(ChipSelPin1, xAxis));
            Serial.print("   ");  
            Serial.print("Gyro Y ");  
            Serial.print(GyroDeg(ChipSelPin1, yAxis)); 
            Serial.print("   "); 
            Serial.print("Gyro Z ");  
            Serial.println(GyroDeg(ChipSelPin1, zAxis));  
          }else{
            motor1.writeMicroseconds(MIN_SIGNAL); //program ends, time to stop
            motor2.writeMicroseconds(MIN_SIGNAL);
            motor3.writeMicroseconds(MIN_SIGNAL);
            motor4.writeMicroseconds(MIN_SIGNAL);
          }
      }
   }
}

void SPIwrite(byte reg, byte data, int ChipSelPin) {
  uint8_t dump;
  digitalWrite(ChipSelPin,LOW);
  dump=SPI.transfer(reg);
  dump=SPI.transfer(data);
  digitalWrite(ChipSelPin,HIGH);
}


uint8_t SPIread(byte reg,int ChipSelPin) {
  uint8_t dump;
  uint8_t return_value;
  uint8_t addr=reg|0x80;
  digitalWrite(ChipSelPin,LOW);
  dump=SPI.transfer(addr);
  return_value=SPI.transfer(0x00);
  digitalWrite(ChipSelPin,HIGH);
  return(return_value);
}


int AcceX(int ChipSelPin) {
  uint8_t AcceX_H=SPIread(0x3B,ChipSelPin);
  uint8_t AcceX_L=SPIread(0x3C,ChipSelPin);
  int16_t AcceX=AcceX_H<<8|AcceX_L;
  return(AcceX);
}


int AcceY(int ChipSelPin) {
  uint8_t AcceY_H=SPIread(0x3D,ChipSelPin);
  uint8_t AcceY_L=SPIread(0x3E,ChipSelPin);
  int16_t AcceY=AcceY_H<<8|AcceY_L;
  return(AcceY);
}


int AcceZ(int ChipSelPin) {
  uint8_t AcceZ_H=SPIread(0x3F,ChipSelPin);
  uint8_t AcceZ_L=SPIread(0x40,ChipSelPin);
  int16_t AcceZ=AcceZ_H<<8|AcceZ_L;
  return(AcceZ);
}


int GyroX(int ChipSelPin) {
  uint8_t GyroX_H=SPIread(0x43,ChipSelPin);
  uint8_t GyroX_L=SPIread(0x44,ChipSelPin);
  int16_t GyroX=GyroX_H<<8|GyroX_L;
  return(GyroX);
}


int GyroY(int ChipSelPin) {
  uint8_t GyroY_H=SPIread(0x45,ChipSelPin);
  uint8_t GyroY_L=SPIread(0x46,ChipSelPin);
  int16_t GyroY=GyroY_H<<8|GyroY_L;
  return(GyroY);
}


int GyroZ(int ChipSelPin) {
  uint8_t GyroZ_H=SPIread(0x47,ChipSelPin);
  uint8_t GyroZ_L=SPIread(0x48,ChipSelPin);
  int16_t GyroZ=GyroZ_H<<8|GyroZ_L;
  return(GyroZ);
}


//--- Function to obtain angles based on accelerometer readings ---//
float AcceDeg(int ChipSelPin,int AxisSelect) {
  float Ax=ToG(AcceX(ChipSelPin));
  float Ay=ToG(AcceY(ChipSelPin));
  float Az=ToG(AcceZ(ChipSelPin));
  float ADegX=((atan(Ax/(sqrt((Ay*Ay)+(Az*Az)))))/PI)*180; //correct
  float ADegY=((atan(Ay/(sqrt((Ax*Ax)+(Az*Az)))))/PI)*180; //correct
  float ADegZ=((atan((sqrt((Ax*Ax)+(Ay*Ay)))/Az))/PI)*180; //correct
  switch (AxisSelect)
  {
    case 0:
    return ADegX;
    break;
    case 1:
    return ADegY;
    break;
    case 2:
    return ADegZ;
    break;
  }
}


//--- Function to obtain angles based on gyroscope readings ---//
float GyroDeg(int ChipSelPin, int AxisSelect) {
  time_old=time;
  time=millis();
  float dt=time-time_old;
  if (dt>=1000)
  {
    dt=0;
  }
  float Gx=ToD(GyroX(ChipSelPin));
  if (Gx>0 && Gx<1.4)
  {
    Gx=0;
  }
  float Gy=1-ToD(GyroY(ChipSelPin));
  float Gz=ToD(GyroZ(ChipSelPin));
  angleX+=Gx*(dt/1000);
  angleY+=Gy*(dt/1000);
  angleZ+=Gz*(dt/1000);
  switch (AxisSelect)
  {
    case 0:
    return angleX;
    break;
    case 1:
    return angleY;
    break;
    case 2:
    return angleZ;
    break;
  }
}


void ConfigureMPU6000()
{
  // DEVICE_RESET @ PWR_MGMT_1, reset device
  SPIwrite(0x6B,0x80,ChipSelPin1);
  delay(150);

  // TEMP_DIS @ PWR_MGMT_1, wake device and select GyroZ clock
  SPIwrite(0x6B,0x03,ChipSelPin1);
  delay(150);

  // I2C_IF_DIS @ USER_CTRL, disable I2C interface
  SPIwrite(0x6A,0x10,ChipSelPin1);
  delay(150);

  // SMPRT_DIV @ SMPRT_DIV, sample rate at 1000Hz
  SPIwrite(0x19,0x00,ChipSelPin1);
  delay(150);

  // DLPF_CFG @ CONFIG, digital low pass filter at 42Hz
  SPIwrite(0x1A,0x03,ChipSelPin1);
  delay(150);

  // FS_SEL @ GYRO_CONFIG, gyro scale at 250dps
  SPIwrite(0x1B,0x00,ChipSelPin1);
  delay(150);

  // AFS_SEL @ ACCEL_CONFIG, accel scale at 2g (1g=8192)
  SPIwrite(0x1C,0x00,ChipSelPin1);
  delay(150);
}
