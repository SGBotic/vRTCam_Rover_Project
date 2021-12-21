/*
   This sketch read the joystick data from the vRTCam and use the "left motor"
   and "right motor" data to drive two-wheeled robot. The project uses L298
   motor driver.

   Wiring of Rover and vRTCam:
   Refer to the project tutorial on SGBotic website.

   Download the sketch to Arduino board.

   Connect your mobile phone to SSID vRTCam-xxxxxxxx, where xxxxxxxx is the SSID of your vRTCam.
   Run web brower and set the URL address to 192.168.4.1

   You can use the joystick to move your robot

*/

#include "SGBotic_vRTCam.h"

#define rcvPin 8
#define txPin 9

// left motor
#define enA 10
#define in1 2
#define in2 3

//right motor
#define enB 11
#define in3 4
#define in4 5

//joystick output value
#define jsFwdMaxVal 510
#define jsCenterVal 255
#define jsRevMaxVal 0

// set the maximum speed of motor
unsigned char maxPWMValue = 120;

unsigned char  dataType;
unsigned int vRTCamData[VRTCAM_DATA_SIZE];

SoftwareSerial mySerial(rcvPin, txPin);  // RX, TX
SGBotic_vRTCam vRTCam = SGBotic_vRTCam(&mySerial);

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(19200);
  Serial.print("ready");
  vRTCam.begin();
}

void loop() {
  dataType = vRTCam.readData(vRTCamData);

  if (dataType == VRTCAM_DATA_JOYSTICK) {
    unsigned int leftMotorData = vRTCamData[VRTCAM_LEFT_MOTOR];
    unsigned int rightMotorData = vRTCamData[VRTCAM_RIGHT_MOTOR];

    //Serial.print("left motor: ");
    //Serial.print(leftMotorData);
    //Serial.print("   right motor: ");
    //Serial.println(rightMotorData);

    // move left motor
    if (leftMotorData == jsCenterVal) {
      leftMotorStop();

    } else if (leftMotorData > jsCenterVal) {
      leftMotorFwd(leftMotorData - jsCenterVal);

    } else if (leftMotorData < jsCenterVal) {
      leftMotorRev(leftMotorData - jsCenterVal);
    }

    //move right motor
    if (rightMotorData == jsCenterVal) {
      rightMotorStop();

    } else if (rightMotorData > jsCenterVal) {
      rightMotorFwd(rightMotorData - jsCenterVal);

    } else if (rightMotorData < jsCenterVal) {
      rightMotorRev(rightMotorData - jsCenterVal);
    }
  }
}

void leftMotorStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //Serial.println("left motor stopped ");
  analogWrite(enA, 0); // stop left motor
}

void leftMotorRev(int val) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // mapping the output of vRTCam's left motor to PWM
  // val is positive value
  int pwmOutput = map(val, 0, 255, 0 , maxPWMValue);
  analogWrite(enA, pwmOutput); // Send PWM signal to left motor
  //Serial.print("left motor fwd: ");
  //Serial.println(pwmOutput);
}

void leftMotorFwd(int val) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // mapping the output of vRTCam's left motor to PWM
  // val is negative value
  int pwmOutput = map(val, 0, -255, 0 , maxPWMValue);
  analogWrite(enA, pwmOutput); // Send PWM signal to left motor

  //Serial.print("left motor rev: ");
  //Serial.println(pwmOutput);
}
void rightMotorStop() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enB, 0); // stop right motor
  //Serial.println("right motor stopped ");
}

void rightMotorRev(int val) {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // mapping the output of vRTCam's right motor to PWM
  // val is positive value
  int pwmOutput = map(val, 0, 255, 0 , maxPWMValue);
  analogWrite(enB, pwmOutput);
  //Serial.print("right motor fwd: ");
  //Serial.println(pwmOutput);
}

void rightMotorFwd(int val) {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // mapping the output of vRTCam's right motor to PWM
  // val is negative value
  int pwmOutput = map(val, 0, -255, 0 , maxPWMValue);
  analogWrite(enB, pwmOutput);
  //Serial.print("right motor rev: ");
  //Serial.println(pwmOutput);
}
